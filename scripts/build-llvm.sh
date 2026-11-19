#!/bin/sh
# SPDX-License-Identifier: MPL-2.0
# Build the toolchain's host tools (cmake/llvm.cmake) from
# third_party/llvm-project for the host this runs on:
#
#   scripts/build-llvm.sh <build-dir> <install-dir>
#
# Linux: run it through scripts/linux-run.sh, so the tools need only glibc
# 2.28. macOS: Xcode's clang, CMake and Ninja. Windows: Git Bash with the
# MSVC environment set (vcvars64), CMake and Ninja. NBT_JOBS limits parallel
# jobs (default: one per CPU).
set -eu
ROOT=$(cd "$(dirname "$0")/.." && pwd)
BUILD=${1:?usage: build-llvm.sh <build-dir> <install-dir>}
PREFIX=${2:?usage: build-llvm.sh <build-dir> <install-dir>}
mkdir -p "$BUILD" "$PREFIX"

# Native Windows programs take Windows paths.
native() {
    if command -v cygpath >/dev/null 2>&1; then cygpath -m "$1"; else printf '%s\n' "$1"; fi
}

TARGET=install-distribution-stripped
case $(uname -s) in
Darwin)
    set -- -DCMAKE_OSX_DEPLOYMENT_TARGET=11.0 ;;
MINGW* | MSYS* | CYGWIN*)
    # Static C runtime: no Visual C++ redistributable to install. Git's
    # coreutils "link" can come before MSVC's linker on PATH.
    CL=$(command -v cl)
    set -- -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded \
        -DCMAKE_LINKER="$(native "$(dirname "$CL")/link.exe")"
    TARGET=install-distribution ;;
*)
    set -- ;;
esac

cmake -S "$(native "$ROOT/third_party/llvm-project/llvm")" -B "$(native "$BUILD")" -G Ninja \
    -C "$(native "$ROOT/cmake/llvm.cmake")" -DCMAKE_INSTALL_PREFIX="$(native "$PREFIX")" "$@"
cmake --build "$(native "$BUILD")" --target "$TARGET" ${NBT_JOBS:+--parallel "$NBT_JOBS"}
