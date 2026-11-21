#!/bin/sh
# SPDX-License-Identifier: MPL-2.0
# Build the QNX 6.5 target: what an ordinary program for the head unit links
# against when it is built without the QNX SDP. No QNX file is used.
#
#   scripts/build-qnx.sh <llvm-bin> <build-dir> <out-dir>
#
# <out-dir>/qnx gets:
#   include/   the headers of qnx/include (the car's C library and QNX APIs)
#   lib/       crt1.o, link stubs of the car's shared libraries (qnx/stubs),
#              compiler-rt builtins with emulated TLS, libc++, libc++abi and
#              libunwind (static, exceptions on)
#   target.mk  the flags programs compile and link with
# The program links the car's own libc.so.3 and other libraries at run time
# (ldqnx.so.2). Needs CMake, Ninja and Python 3.
set -eu
ROOT=$(cd "$(dirname "$0")/.." && pwd)
usage="usage: build-qnx.sh <llvm-bin> <build-dir> <out-dir>"
LLVM_BIN=$(cd "${1:?$usage}" && pwd)
mkdir -p "${2:?$usage}" "${3:?$usage}"
WORK=$(cd "$2" && pwd)/qnx
OUT=$(cd "$3" && pwd)/qnx
SRC=$ROOT/third_party/llvm-project

# ARMv7-A, soft-float calling convention with VFPv3-D16, ARM state, int-size
# enums: the car's ABI (as the runtime of modules and guests).
TRIPLE=armv7a-none-eabi
ARCH="-marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=softfp -fno-short-enums"
# Position-independent code: data of the car's libraries is reached through
# the GOT, so no copy relocation depends on the size of their objects. QNX 6.5
# has no ELF TLS: thread_local is emulated over pthread keys.
CODEGEN="-fPIC -femulated-tls"
DEFS="-D__QNXNTO__ -D__QNX__ -D__unix__ -D__unix -D__ELF__ -D__ARM__ -D__LITTLEENDIAN__ -D_QNX_SOURCE -D_LIBCPP_HAS_NO_C11_ALIGNED_ALLOC"
FLAGS="$ARCH $CODEGEN -ffunction-sections -fdata-sections -ffile-prefix-map=$ROOT/="
INC="-nostdlibinc -isystem $OUT/include"

rm -rf "$OUT" "$WORK"
mkdir -p "$OUT/lib" "$WORK"
cp -R "$ROOT/qnx/include" "$OUT/include"

# --- the headers of the car's OpenSSL (libssl.so.2, libcrypto.so.2: 1.0.1l),
# from its source (third_party/openssl), configured for 32-bit ARM ---
mkdir -p "$WORK/openssl"
cp -R "$ROOT/third_party/openssl/." "$WORK/openssl"
rm -rf "$WORK/openssl/.git"
(cd "$WORK/openssl" && ./Configure linux-armv4 no-asm no-shared >/dev/null && make links >/dev/null)
mkdir -p "$OUT/include/openssl"
cp -L "$WORK/openssl/include/openssl/"*.h "$OUT/include/openssl/"

# --- startup and link stubs ---
# shellcheck disable=SC2086
"$LLVM_BIN/clang" --target=$TRIPLE $ARCH -c "$ROOT/qnx/crt/crt1.S" -o "$OUT/lib/crt1.o"
python3 "$ROOT/scripts/qnx-stubs.py" build --lists "$ROOT/qnx/stubs" --llvm-bin "$LLVM_BIN" --out "$OUT/lib"

# --- libnbtqnx.a: C library functions QNX programs link statically (the
# car's libc.so.3 lacks them), written for this target (qnx/libc) ---
mkdir -p "$WORK/libnbtqnx"
for src in "$ROOT"/qnx/libc/*.c; do
    # shellcheck disable=SC2086
    "$LLVM_BIN/clang" --target=$TRIPLE $FLAGS $DEFS $INC -O2 -std=gnu11 -Wall -Wextra -Werror \
        -c "$src" -o "$WORK/libnbtqnx/$(basename "$src" .c).o"
done
"$LLVM_BIN/llvm-ar" rcs "$OUT/lib/libnbtqnx.a" "$WORK"/libnbtqnx/*.o

CMAKE_TOOLS="-DCMAKE_C_COMPILER=$LLVM_BIN/clang -DCMAKE_CXX_COMPILER=$LLVM_BIN/clang++
    -DCMAKE_ASM_COMPILER=$LLVM_BIN/clang -DCMAKE_AR=$LLVM_BIN/llvm-ar -DCMAKE_NM=$LLVM_BIN/llvm-nm
    -DCMAKE_RANLIB=$LLVM_BIN/llvm-ranlib -DCMAKE_BUILD_TYPE=Release -DCMAKE_SYSTEM_NAME=Generic
    -DCMAKE_SYSTEM_PROCESSOR=arm -DCMAKE_TRY_COMPILE_TARGET_TYPE=STATIC_LIBRARY"

# --- compiler-rt builtins, and emulated TLS over the car's pthread keys ---
# shellcheck disable=SC2086
cmake -S "$SRC/compiler-rt/lib/builtins" -B "$WORK/builtins" -G Ninja $CMAKE_TOOLS \
    -DCMAKE_C_COMPILER_TARGET=armv7-none-eabi -DCMAKE_ASM_COMPILER_TARGET=armv7-none-eabi \
    -DCMAKE_C_FLAGS="$FLAGS" -DCMAKE_ASM_FLAGS="$FLAGS" \
    -DCOMPILER_RT_BAREMETAL_BUILD=ON -DCOMPILER_RT_DEFAULT_TARGET_ONLY=ON \
    -DCOMPILER_RT_OS_DIR=. -DLLVM_ENABLE_PER_TARGET_RUNTIME_DIR=OFF
cmake --build "$WORK/builtins"
find "$WORK/builtins" -name 'libclang_rt.builtins*.a' -exec cp {} "$OUT/lib/libclang_rt.builtins.a" \;
# shellcheck disable=SC2086
"$LLVM_BIN/clang" --target=$TRIPLE $FLAGS $DEFS $INC -O2 -std=gnu11 -fvisibility=hidden \
    -I"$SRC/compiler-rt/lib/builtins" -c "$SRC/compiler-rt/lib/builtins/emutls.c" -o "$WORK/emutls.o"
"$LLVM_BIN/llvm-ar" rs "$OUT/lib/libclang_rt.builtins.a" "$WORK/emutls.o"

# --- libc++, libc++abi, libunwind ---
# Static, over the car's C library. QNX 6.5 has no locale_t: no localization
# (no iostreams), no wide characters, no filesystem. Exceptions use the
# program's own EHABI tables (__exidx_start/__exidx_end): they never cross into
# the car's libraries.
CXX_FLAGS="$FLAGS $DEFS $INC"
# shellcheck disable=SC2086
cmake -S "$SRC/runtimes" -B "$WORK/cxx" -G Ninja $CMAKE_TOOLS \
    -DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi;libunwind" \
    -DCMAKE_C_COMPILER_TARGET=$TRIPLE -DCMAKE_CXX_COMPILER_TARGET=$TRIPLE -DCMAKE_ASM_COMPILER_TARGET=$TRIPLE \
    -DCMAKE_C_FLAGS="$CXX_FLAGS" -DCMAKE_CXX_FLAGS="$CXX_FLAGS" -DCMAKE_ASM_FLAGS="$FLAGS" \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DCMAKE_INSTALL_PREFIX="$OUT/cxx" \
    -DLLVM_INCLUDE_TESTS=OFF -DLLVM_INCLUDE_DOCS=OFF \
    -DLIBCXX_ENABLE_SHARED=OFF -DLIBCXXABI_ENABLE_SHARED=OFF -DLIBUNWIND_ENABLE_SHARED=OFF \
    -DLIBCXX_CXX_ABI=libcxxabi -DLIBCXX_ENABLE_STATIC_ABI_LIBRARY=ON \
    -DLIBCXXABI_USE_LLVM_UNWINDER=ON -DLIBCXXABI_ENABLE_STATIC_UNWINDER=ON \
    -DLIBCXXABI_BAREMETAL=OFF -DLIBUNWIND_IS_BAREMETAL=ON \
    -DLIBCXX_HAS_PTHREAD_LIB=OFF -DLIBCXX_HAS_RT_LIB=OFF -DLIBCXXABI_HAS_PTHREAD_LIB=OFF \
    -DLIBCXX_ENABLE_THREADS=ON -DLIBCXX_HAS_PTHREAD_API=ON \
    -DLIBCXXABI_ENABLE_THREADS=ON -DLIBCXXABI_HAS_PTHREAD_API=ON \
    -DLIBUNWIND_ENABLE_THREADS=OFF -DLIBCXXABI_HAS_CXA_THREAD_ATEXIT_IMPL=OFF \
    -DLIBCXX_ENABLE_EXCEPTIONS=ON -DLIBCXXABI_ENABLE_EXCEPTIONS=ON -DLIBCXX_ENABLE_RTTI=ON \
    -DLIBCXX_ENABLE_FILESYSTEM=OFF -DLIBCXX_ENABLE_RANDOM_DEVICE=OFF \
    -DLIBCXX_ENABLE_LOCALIZATION=OFF -DLIBCXX_ENABLE_WIDE_CHARACTERS=OFF \
    -DLIBCXX_ENABLE_MONOTONIC_CLOCK=ON \
    -DLIBCXX_USE_COMPILER_RT=ON -DLIBCXXABI_USE_COMPILER_RT=ON -DLIBUNWIND_USE_COMPILER_RT=ON \
    -DLIBCXX_INCLUDE_TESTS=OFF -DLIBCXX_INCLUDE_BENCHMARKS=OFF -DLIBCXXABI_INCLUDE_TESTS=OFF \
    -DLIBUNWIND_INCLUDE_TESTS=OFF -DLIBCXX_INCLUDE_DOCS=OFF -DLIBUNWIND_INCLUDE_DOCS=OFF
cmake --build "$WORK/cxx"
cmake --install "$WORK/cxx"

cat > "$OUT/target.mk" <<EOF
# Generated by scripts/build-qnx.sh: how programs for the QNX 6.5 target are
# compiled and linked (NBT_QNX is this directory). Link with
# \$(NBT_QNX_LD) \$(NBT_QNX_LDFLAGS) OBJECTS... -lsocket ... \$(NBT_QNX_LDLIBS).
NBT_QNX_ARCH := --target=$TRIPLE $ARCH
NBT_QNX_CODEGEN := $CODEGEN
NBT_QNX_DEFS := $DEFS
NBT_QNX_CFLAGS = \$(NBT_QNX_ARCH) \$(NBT_QNX_CODEGEN) \$(NBT_QNX_DEFS) -nostdlibinc -isystem \$(NBT_QNX)/include
NBT_QNX_CXXFLAGS = \$(NBT_QNX_ARCH) \$(NBT_QNX_CODEGEN) \$(NBT_QNX_DEFS) -nostdlibinc \\
	-isystem \$(NBT_QNX)/cxx/include/c++/v1 -isystem \$(NBT_QNX)/include
# --no-rosegment: QNX 6.5's loader wants the text segment first; it reads
# DT_RPATH, not DT_RUNPATH (-rpath DIR adds one). crt1.o names the loader
# (/usr/lib/ldqnx.so.2) in its .interp section.
NBT_QNX_LDFLAGS = --no-rosegment --disable-new-dtags --hash-style=both -z norelro \\
	-z max-page-size=4096 --image-base=0x100000 --eh-frame-hdr -e _start --gc-sections --build-id \\
	--target2=got-rel -L\$(NBT_QNX)/lib \$(NBT_QNX)/lib/crt1.o
NBT_QNX_LDLIBS = \$(NBT_QNX)/cxx/lib/libc++.a \$(NBT_QNX)/cxx/lib/libc++abi.a \$(NBT_QNX)/cxx/lib/libunwind.a \\
	\$(NBT_QNX)/lib/libnbtqnx.a -lc \$(NBT_QNX)/lib/libclang_rt.builtins.a
EOF
echo "qnx target: $OUT"
