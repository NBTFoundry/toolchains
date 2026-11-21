#!/usr/bin/env python3
# SPDX-License-Identifier: MPL-2.0
"""Compare the QNX 6.5 target's headers (qnx/include) with the QNX SDP's.

For maintainers who have the QNX 6.5 SP1 SDP (it is never needed to build):

  check-qnx-abi.py --llvm-bin BIN --qnx-env ENV.sh [--headers qnx/include]

It lists, from our headers, every struct and union (size and each field's
offset), every scalar typedef (size and signedness), every integer macro and
every function prototype, then compiles the same questions with clang over our
headers and with the SDP's qcc over its own, and reports each answer that
differs. A function is compared by redeclaring our prototype after the SDP's
headers: the SDP's compiler rejects one that conflicts. Items the SDP does not
know are listed apart (they are ours alone: fine for helpers, suspicious for
the C library's names).
"""
import argparse
import json
import os
import re
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

TRIPLE = ["--target=armv7a-none-eabi", "-marm", "-march=armv7-a", "-mfpu=vfpv3-d16", "-mfloat-abi=softfp",
          "-fno-short-enums"]
DEFS = ["-D__QNXNTO__", "-D__QNX__", "-D__unix__", "-D__ELF__", "-D__ARM__", "-D__LITTLEENDIAN__", "-D_QNX_SOURCE"]


def headers(root):
    return sorted(str(p.relative_to(root)) for p in root.rglob("*.h") if "/_" not in "/" + str(p.relative_to(root))
                  and not p.name.startswith("_") and not str(p.relative_to(root)).startswith("bits/"))


def run(cmd, **kw):
    return subprocess.run(cmd, capture_output=True, text=True, **kw)


def our_items(clang, root, hdrs, work):
    tu = work / "all.c"
    tu.write_text("".join(f"#include <{h}>\n" for h in hdrs))
    base = [clang] + TRIPLE + DEFS + ["-std=gnu11", "-nostdlibinc", "-isystem", str(root), "-w"]
    ast = run(base + ["-Xclang", "-ast-dump=json", "-fsyntax-only", str(tu)])
    if ast.returncode:
        sys.exit("our headers do not compile:\n" + ast.stderr[:4000])
    items, funcs = [], {}
    rootstr = str(root)
    typedef_of = {}
    records = {}

    def located(node):
        loc = node.get("loc", {})
        f = loc.get("file") or loc.get("expansionLoc", {}).get("file") or loc.get("spellingLoc", {}).get("file")
        return f

    last_file = [None]

    def visit(node):
        f = located(node)
        if f:
            last_file[0] = f
        ours = last_file[0] and last_file[0].startswith(rootstr)
        kind = node.get("kind")
        if ours and kind == "RecordDecl" and node.get("completeDefinition"):
            records[node["id"]] = node
        if ours and kind == "TypedefDecl":
            typedef_of[node["name"]] = node
        if ours and kind == "FunctionDecl" and not node.get("isImplicit"):
            funcs[node["name"]] = node["type"]["qualType"]
        for c in node.get("inner", []):
            visit(c)

    visit(json.loads(ast.stdout))
    # Name each record: its tag, else the typedef that names it.
    names = {}
    for tname, td in typedef_of.items():
        owned = td.get("inner", [{}])[0]
        decl = owned.get("decl", {}) if owned.get("kind") == "ElaboratedType" else {}
        for inner in owned.get("inner", []):
            decl = inner.get("decl", decl)
        if decl.get("id") in records:
            names.setdefault(decl["id"], tname)
    for rid, rec in records.items():
        if rec.get("name"):
            names[rid] = f"{rec['tagUsed']} {rec['name']}"
    for rid, rec in records.items():
        tname = names.get(rid)
        if not tname:
            continue
        items.append((f"sizeof({tname})", f"sizeof({tname})"))
        for fld in rec.get("inner", []):
            if fld.get("kind") == "FieldDecl" and fld.get("name") and not fld.get("isBitfield"):
                items.append((f"offsetof({tname}, {fld['name']})", f"__builtin_offsetof({tname}, {fld['name']})"))
    for tname, td in typedef_of.items():
        if tname.startswith("__") or tname.startswith("_Int") or tname.startswith("_Uint"):
            continue
        q = td["type"]["qualType"]
        if re.search(r"\b(struct|union|enum)\b|\(", q) and "*" not in q:
            continue
        items.append((f"sizeof({tname})", f"sizeof({tname})"))
        if "*" not in q:
            items.append((f"signed({tname})", f"(({tname})-1 < ({tname})0)"))
    # Integer macros defined in our files.
    defined = set()
    for h in root.rglob("*.h"):
        for m in re.finditer(r"^#define\s+([A-Za-z_][A-Za-z0-9_]*)\s+\S", h.read_text(), re.M):
            defined.add(m.group(1))
    macros = run(base + ["-dM", "-E", str(tu)]).stdout
    for line in macros.splitlines():
        m = re.match(r"#define ([A-Za-z_][A-Za-z0-9_]*) (.+)$", line)
        if m and m.group(1) in defined and not m.group(1).startswith("_NBT") and not m.group(1).startswith("__NBT"):
            items.append((m.group(1), f"(long long)({m.group(1)})"))
    return items, funcs


def probe_source(includes, items):
    lines = ["#include <stddef.h>"] + [f"#include <{h}>" for h in includes]
    first = len(lines) + 1
    for i, (_, expr) in enumerate(items):
        lines.append(f"__attribute__((section(\".nbtabi\"))) const long long nbtabi_{i} = (long long)({expr});")
    return "\n".join(lines) + "\n", first


def compile_dropping(cmd_for, src_path, includes, items):
    """Compile, dropping items on lines with errors, until it builds."""
    alive = list(range(len(items)))
    for _ in range(40):
        text, first = probe_source(includes, [items[i] for i in alive])
        src_path.write_text(text)
        r = run(cmd_for(src_path))
        if r.returncode == 0:
            return alive
        bad = set()
        for m in re.finditer(re.escape(src_path.name) + r":(\d+):(?:\d+:)? (?:fatal )?error", r.stderr):
            n = int(m.group(1)) - first
            if 0 <= n < len(alive):
                bad.add(n)
        if not bad:
            sys.exit(f"{cmd_for(src_path)[0]} failed outside the items:\n{r.stderr[:3000]}")
        alive = [a for k, a in enumerate(alive) if k not in bad]
    sys.exit("too many rounds of errors")


def read_values(obj):
    data = Path(obj).read_bytes()
    shoff, = struct.unpack_from("<I", data, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from("<HHH", data, 0x2e)
    secs = [struct.unpack_from("<IIIIIIIIII", data, shoff + i * shentsize) for i in range(shnum)]
    strtab_of = lambda s: data[s[4]:s[4] + s[5]]
    shstr = strtab_of(secs[shstrndx])
    name = lambda tab, off: tab[off:tab.index(b"\0", off)].decode()
    values = {}
    for s in secs:
        if s[1] != 2:  # SHT_SYMTAB
            continue
        names = strtab_of(secs[s[6]])
        for k in range(s[5] // 16):
            st_name, st_value, st_size, st_info, st_other, st_shndx = struct.unpack_from("<IIIBBH", data, s[4] + k * 16)
            sym = name(names, st_name)
            if sym.startswith("nbtabi_") and st_shndx < len(secs):
                sec = secs[st_shndx]
                values[int(sym[7:])] = struct.unpack_from("<q", data, sec[4] + st_value)[0]
    return values


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("--llvm-bin", required=True)
    p.add_argument("--qnx-env", required=True, help="the SDP's env.sh (qcc on the PATH)")
    p.add_argument("--headers", default=str(Path(__file__).resolve().parents[1] / "qnx" / "include"))
    args = p.parse_args()
    root = Path(args.headers).resolve()
    clang = str(Path(args.llvm_bin) / "clang")
    sdp_inc = run(["bash", "-c", f'. "{args.qnx_env}" >/dev/null 2>&1; echo "$QNX_TARGET"']).stdout.strip()
    sdp_root = Path(sdp_inc) / "usr" / "include"
    with tempfile.TemporaryDirectory() as tmp:
        work = Path(tmp)
        hdrs = headers(root)
        items, funcs = our_items(clang, root, hdrs, work)
        ours_cmd = lambda src: [clang] + TRIPLE + DEFS + ["-std=gnu11", "-nostdlibinc", "-isystem", str(root), "-w",
                                                        "-c", str(src), "-o", str(work / "ours.o")]
        sdp_hdrs = [h for h in hdrs if (sdp_root / h).exists()]
        sdp_cmd = lambda src: ["bash", "-c", f'. "{args.qnx_env}" >/dev/null 2>&1; exec qcc -Vgcc_ntoarmv7le '
                                             f'-D_QNX_SOURCE -std=gnu99 -w -c "{src}" -o "{work / "sdp.o"}"']
        ours_alive = compile_dropping(ours_cmd, work / "ours.c", hdrs, items)
        ours_vals = read_values(work / "ours.o")
        ours = {items[i][0]: ours_vals[k] for k, i in enumerate(ours_alive) if k in ours_vals}
        sdp_alive = compile_dropping(sdp_cmd, work / "sdp.c", sdp_hdrs, items)
        sdp_vals = read_values(work / "sdp.o")
        sdp = {items[i][0]: sdp_vals[k] for k, i in enumerate(sdp_alive) if k in sdp_vals}

        def same(a, b):
            # A 32-bit value (a pointer constant) widened with or without its sign.
            return a == b or (a - b) % (1 << 32) == 0 and a >> 32 in (0, -1) and b >> 32 in (0, -1)
        diffs = [(n, ours[n], sdp[n]) for n in ours if n in sdp and not same(ours[n], sdp[n])]
        missing = sorted(n for n in ours if n not in sdp)

        # Prototypes: ours, redeclared after the SDP's headers.
        decls = []
        for name, qt in sorted(funcs.items()):
            m = re.match(r"^(.*?)\s*\((.*)\)$", qt)
            if not m or "(" in m.group(1):
                continue
            decls.append((name, f"#undef {name}\n{m.group(1)} {name}({m.group(2)});"))
        src = work / "protos.c"
        conflicts, unknown = [], []
        alive = list(range(len(decls)))
        for _ in range(40):
            head = [f"#include <{h}>" for h in sdp_hdrs]
            lines = []
            for i in alive:
                lines.append(decls[i][1].split("\n")[0])
                lines.append(decls[i][1].split("\n")[1])
            src.write_text("\n".join(head + lines) + "\n")
            r = run(sdp_cmd(src))
            if r.returncode == 0:
                break
            bad = {}
            for m in re.finditer(r"protos\.c:(\d+):(?:\d+:)? (?:fatal )?error: (.*)", r.stderr):
                n = (int(m.group(1)) - len(head) - 1) // 2
                if 0 <= n < len(alive):
                    bad.setdefault(n, m.group(2))
            if not bad:
                sys.exit("prototype check failed:\n" + r.stderr[:3000])
            for n, why in bad.items():
                (conflicts if "conflicting" in why else unknown).append((decls[alive[n]][0], why))
            alive = [a for k, a in enumerate(alive) if k not in bad]

    print(f"compared {len(ours)} layouts and constants, {len(decls)} prototypes")
    for n, a, b in sorted(diffs):
        print(f"DIFF  {n}: ours {a}, SDP {b}")
    for name, why in sorted(conflicts):
        print(f"PROTO {name}: {why}")
    if missing:
        print("not in the SDP's headers (ours alone): " + ", ".join(missing))
    if unknown:
        print("prototypes not comparable: " + ", ".join(f"{n} ({w})" for n, w in sorted(unknown)))
    return 1 if diffs or conflicts else 0


if __name__ == "__main__":
    sys.exit(main())
