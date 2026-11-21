#!/usr/bin/env python3
# SPDX-License-Identifier: MPL-2.0
"""Assemble the NBT toolchain for one host and archive it.

  package.py --host HOST --llvm DIR --runtime DIR --out DIR

HOST is one of HOSTS. --llvm is scripts/build-llvm.sh's install directory
built on that host, --runtime scripts/build-runtime.sh's output (the same for
every host). Writes OUT/nbt-toolchain-VERSION/ and its archive (.zip for
Windows, .tar.xz otherwise) with a .sha256 beside it. Archives are
reproducible: sorted entries, the commit's time, no owners.
"""
import argparse
import hashlib
import lzma
import os
import re
import shutil
import stat
import subprocess
import sys
import tarfile
import time
import zipfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LLVM_SRC = os.path.join(ROOT, "third_party", "llvm-project")
PICOLIBC_SRC = os.path.join(ROOT, "third_party", "picolibc")
OPENSSL_SRC = os.path.join(ROOT, "third_party", "openssl")

HOSTS = ("linux-x86_64", "macos-arm64", "windows-x86_64")
# The host tools NBT builds use (cmake/llvm.cmake); the rest of bin/ is left out.
TOOLS = {"clang", "clang++", "ld.lld", "llvm-ar", "llvm-ranlib", "llvm-nm", "llvm-objcopy",
         "llvm-strip", "llvm-objdump", "llvm-readobj", "llvm-readelf", "llvm-size",
         "llvm-symbolizer", "llvm-addr2line", "llvm-cxxfilt"}
# What the tools and the runtime are made of. picolibc's COPYING.GPL2 covers
# build scripts only, which nothing here contains.
LICENSES = [(LLVM_SRC, "llvm-project", p) for p in (
    "llvm/LICENSE.TXT", "clang/LICENSE.TXT", "lld/LICENSE.TXT", "compiler-rt/LICENSE.TXT",
    "libcxx/LICENSE.TXT", "libcxxabi/LICENSE.TXT", "libunwind/LICENSE.TXT",
    "llvm/include/llvm/Support/LICENSE.TXT", "llvm/lib/Support/BLAKE3/LICENSE")] + \
    [(PICOLIBC_SRC, "picolibc", p) for p in ("COPYING.picolibc", "COPYING.NEWLIB")] + \
    [(OPENSSL_SRC, "openssl", "LICENSE")] + \
    [(ROOT, "nbt-toolchain", "LICENSE")]


def git(*args):
    return subprocess.run(["git", "-C", ROOT, *args], check=True, capture_output=True,
                          text=True).stdout.strip()


def source_version(path, pattern):
    with open(path, encoding="utf-8") as f:
        return ".".join(re.findall(pattern, f.read(), re.M))


def components():
    llvm = source_version(os.path.join(LLVM_SRC, "llvm", "CMakeLists.txt"),
                          r"^\s*set\(LLVM_VERSION_(?:MAJOR|MINOR|PATCH) (\d+)\)")
    picolibc = source_version(os.path.join(PICOLIBC_SRC, "meson.build"),
                              r"^\s*version\s*:\s*'([\d.]+)'")
    with open(os.path.join(OPENSSL_SRC, "crypto", "opensslv.h"), encoding="utf-8") as f:
        openssl = re.findall(r'^#\s*define OPENSSL_VERSION_TEXT\s+"OpenSSL ([^ ]+) ', f.read(), re.M)[-1]
    return [("llvm", llvm, git("rev-parse", "HEAD:third_party/llvm-project")),
            ("picolibc", picolibc, git("rev-parse", "HEAD:third_party/picolibc")),
            ("openssl-headers", openssl, git("rev-parse", "HEAD:third_party/openssl"))]


def copy_tools(src_bin, dst_bin):
    """The TOOLS, and on hosts with symbolic links the files they point to."""
    os.makedirs(dst_bin)
    wanted = set()
    for name in sorted(os.listdir(src_bin)):
        if os.path.splitext(name)[0] not in TOOLS and name not in TOOLS:
            continue
        wanted.add(name)
        path = os.path.join(src_bin, name)
        while os.path.islink(path):
            target = os.readlink(path)
            if os.path.isabs(target) or os.sep in target:
                sys.exit("%s: link outside bin/: %s" % (path, target))
            wanted.add(target)
            path = os.path.join(src_bin, target)
    for name in sorted(wanted):
        src = os.path.join(src_bin, name)
        if os.path.islink(src):
            os.symlink(os.readlink(src), os.path.join(dst_bin, name))
        else:
            shutil.copy2(src, os.path.join(dst_bin, name))
    missing = TOOLS - {os.path.splitext(n)[0] for n in wanted} - wanted
    if missing:
        sys.exit("%s lacks %s" % (src_bin, ", ".join(sorted(missing))))


def assemble(host, llvm, runtime, top):
    if os.path.exists(top):
        shutil.rmtree(top)
    copy_tools(os.path.join(llvm, "bin"), os.path.join(top, "bin"))
    shutil.copytree(os.path.join(llvm, "lib", "clang"), os.path.join(top, "lib", "clang"),
                    symlinks=True)
    shutil.copytree(runtime, os.path.join(top, "armv7a-nbt"), symlinks=True)
    for src_root, name, rel in LICENSES:
        dst = os.path.join(top, "share", "licenses", name, rel)
        os.makedirs(os.path.dirname(dst), exist_ok=True)
        shutil.copy2(os.path.join(src_root, rel), dst)
    shutil.copy2(os.path.join(ROOT, "docs", "usage.md"), os.path.join(top, "README.md"))
    with open(os.path.join(top, "VERSION"), "w", encoding="utf-8", newline="\n") as f:
        f.write("nbt-toolchain %s\nhost %s\n" % (version(), host))
        for name, ver, commit in components():
            f.write("%s %s %s\n" % (name, ver, commit))


def entries(top):
    """(archive name, path) for every file and directory under top, sorted."""
    base = os.path.dirname(top)
    out = []
    for dirpath, dirnames, filenames in os.walk(top):
        dirnames.sort()
        for name in [dirpath] + [os.path.join(dirpath, f) for f in sorted(filenames)]:
            out.append((os.path.relpath(name, base).replace(os.sep, "/"), name))
        # symbolic links to directories are listed as files
        for d in list(dirnames):
            if os.path.islink(os.path.join(dirpath, d)):
                dirnames.remove(d)
                out.append((os.path.relpath(os.path.join(dirpath, d), base).replace(os.sep, "/"),
                            os.path.join(dirpath, d)))
    return out


def mode_of(path):
    st = os.lstat(path)
    if stat.S_ISDIR(st.st_mode) or st.st_mode & stat.S_IXUSR:
        return 0o755
    return 0o644


def write_tar(top, archive, mtime):
    with lzma.open(archive, "wb", preset=9) as xz, \
            tarfile.open(fileobj=xz, mode="w", format=tarfile.PAX_FORMAT) as tar:
        for name, path in entries(top):
            info = tar.gettarinfo(path, name)
            info.uid = info.gid = 0
            info.uname = info.gname = ""
            info.mtime = mtime
            if not info.issym():
                info.mode = mode_of(path)
            if info.isreg():
                with open(path, "rb") as f:
                    tar.addfile(info, f)
            else:
                tar.addfile(info)


def write_zip(top, archive, mtime):
    stamp = time.gmtime(max(mtime, 315532800))[:6]  # zip times start in 1980
    with zipfile.ZipFile(archive, "w", zipfile.ZIP_DEFLATED, compresslevel=9) as z:
        for name, path in entries(top):
            if os.path.islink(path):
                sys.exit("%s: symbolic link in a Windows archive" % path)
            is_dir = os.path.isdir(path)
            info = zipfile.ZipInfo(name + "/" if is_dir else name, stamp)
            info.external_attr = ((stat.S_IFDIR if is_dir else stat.S_IFREG) | mode_of(path)) << 16
            if is_dir:
                z.writestr(info, b"")
            else:
                info.compress_type = zipfile.ZIP_DEFLATED
                with open(path, "rb") as f:
                    z.writestr(info, f.read())


def version():
    with open(os.path.join(ROOT, "VERSION"), encoding="utf-8") as f:
        return f.read().strip()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--host", required=True, choices=HOSTS)
    parser.add_argument("--llvm", required=True)
    parser.add_argument("--runtime", required=True)
    parser.add_argument("--out", required=True)
    args = parser.parse_args()
    name = "nbt-toolchain-" + version()
    top = os.path.join(os.path.abspath(args.out), args.host, name)
    assemble(args.host, args.llvm, args.runtime, top)
    mtime = int(git("log", "-1", "--format=%ct"))
    ext = ".zip" if args.host.startswith("windows") else ".tar.xz"
    archive = os.path.join(os.path.abspath(args.out), "%s-%s%s" % (name, args.host, ext))
    (write_zip if ext == ".zip" else write_tar)(top, archive, mtime)
    h = hashlib.sha256()
    with open(archive, "rb") as f:
        for block in iter(lambda: f.read(1 << 20), b""):
            h.update(block)
    with open(archive + ".sha256", "w", encoding="utf-8", newline="\n") as f:
        f.write("%s  %s\n" % (h.hexdigest(), os.path.basename(archive)))
    print("%s: %s" % (archive, h.hexdigest()))
    return 0


if __name__ == "__main__":
    sys.exit(main())
