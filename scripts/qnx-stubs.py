#!/usr/bin/env python3
# SPDX-License-Identifier: MPL-2.0
"""Link stubs of the head unit's shared libraries, for the QNX 6.5 target.

A program built for the car links against these stubs: each has the real
library's SONAME and exports its symbols, but holds no code, so the program
records what it needs and the car's own library provides it at run time.

  qnx-stubs.py build --lists qnx/stubs --llvm-bin BIN --out DIR
      writes DIR/lib<name>.so for every qnx/stubs/<soname>.syms

  qnx-stubs.py extract --readelf llvm-readelf --out qnx/stubs LIB...
      (maintainers, with copies of the car's libraries) rewrites the lists:
      one line per exported symbol, "F name" for code, "O name size" for data.

The lists hold names and sizes only, never anything of the libraries.
"""
import argparse
import re
import subprocess
import sys
import tempfile
from pathlib import Path


def soname_of(readelf, lib):
    out = subprocess.run([readelf, "-d", str(lib)], check=True, capture_output=True, text=True).stdout
    m = re.search(r"\(SONAME\)\s+Library soname: \[([^\]]+)\]", out)
    return m.group(1) if m else Path(lib).name


# The car's libraries carry (and export) GCC's unwinder and C++ support. A
# program gets its own from the toolchain (libunwind, libc++abi): a stub that
# exported them would make the linker bind the program's exceptions to the
# car's copies.
RUNTIME_OWN = re.compile(r"^(_Unwind_|__gnu_|__aeabi_unwind_cpp_pr|__gxx_personality|__register_frame|"
                         r"__deregister_frame|_ZSt|_ZN10__cxxabiv|_ZNSt|__cxa_(?!atexit$|finalize$))")


def extract(args):
    out_dir = Path(args.out)
    out_dir.mkdir(parents=True, exist_ok=True)
    for lib in args.libs:
        soname = soname_of(args.readelf, lib)
        dyn = subprocess.run([args.readelf, "--dyn-syms", "-W", str(lib)], check=True,
                             capture_output=True, text=True).stdout
        lines = set()
        for row in dyn.splitlines():
            f = row.split()
            # Num: Value Size Type Bind Vis Ndx Name
            if len(f) < 8 or not f[0].endswith(":") or f[6] == "UND":
                continue
            name = f[7].split("@")[0]
            if f[4] not in ("GLOBAL", "WEAK") or not name or RUNTIME_OWN.match(name):
                continue
            if f[3] == "FUNC":
                lines.add(f"F {name}")
            elif f[3] in ("OBJECT", "TLS", "COMMON"):
                lines.add(f"O {name} {int(f[2], 0)}")
            elif f[3] == "NOTYPE" and f[6] != "ABS":
                lines.add(f"F {name}")
        path = out_dir / f"{soname}.syms"
        path.write_text(f"# {soname}: exported symbols (names and sizes), for link stubs\n"
                        + "\n".join(sorted(lines, key=lambda s: s.split()[1])) + "\n")
        print(f"{path}: {len(lines)} symbols")


def link_name(soname):
    """libc.so.3 -> libc.so, liba2i_client.so -> liba2i_client.so."""
    m = re.match(r"(lib[^.]+(?:\.[^.0-9][^.]*)*\.so)", soname)
    return m.group(1) if m else soname


def build(args):
    bin_dir = Path(args.llvm_bin)
    out_dir = Path(args.out)
    out_dir.mkdir(parents=True, exist_ok=True)
    for syms in sorted(Path(args.lists).glob("*.syms")):
        soname = syms.name[:-len(".syms")]
        asm = [".syntax unified", ".arm", ".text"]
        data = [".data"]
        for line in syms.read_text().splitlines():
            if not line or line.startswith("#"):
                continue
            f = line.split()
            if f[0] == "F":
                asm += [f".globl {f[1]}", f".type {f[1]}, %function", f"{f[1]}:", "bx lr"]
            else:
                size = max(int(f[2]), 1)
                data += [f".globl {f[1]}", f".type {f[1]}, %object", f".size {f[1]}, {size}",
                         ".balign 4", f"{f[1]}:", f".zero {size}"]
        with tempfile.TemporaryDirectory() as tmp:
            src = Path(tmp) / "stub.s"
            obj = Path(tmp) / "stub.o"
            src.write_text("\n".join(asm + data) + "\n")
            subprocess.run([str(bin_dir / "clang"), "--target=armv7a-none-eabi", "-c", str(src), "-o", str(obj)],
                           check=True)
            target = out_dir / link_name(soname)
            subprocess.run([str(bin_dir / "ld.lld"), "-shared", "--hash-style=both", "-soname", soname,
                            "-o", str(target), str(obj)], check=True)
        print(f"{target} ({soname})")


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest="cmd", required=True)
    b = sub.add_parser("build")
    b.add_argument("--lists", required=True)
    b.add_argument("--llvm-bin", required=True)
    b.add_argument("--out", required=True)
    e = sub.add_parser("extract")
    e.add_argument("--readelf", default="llvm-readelf")
    e.add_argument("--out", required=True)
    e.add_argument("libs", nargs="+")
    args = p.parse_args()
    (build if args.cmd == "build" else extract)(args)


if __name__ == "__main__":
    sys.exit(main())
