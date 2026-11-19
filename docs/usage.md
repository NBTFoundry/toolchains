<!-- SPDX-License-Identifier: MPL-2.0 -->
# NBT toolchain

Clang and LLD for building NBT application modules and guests (ARMv7-A, for
the NBT head unit's QNX 6.5), with the runtime they link statically. It is
used through the NBT SDK: the SDK's `make toolchain` installs the release it is
pinned to, or set `NBT_TOOLCHAIN` to this directory. `VERSION` names the
release, the host and the sources it was built from.

Built by NBTFoundry from LLVM and picolibc sources; not an LLVM release.

## Contents

- `bin/`: `clang`, `clang++`, `ld.lld`, and `llvm-ar`, `-ranlib`, `-nm`,
  `-objcopy`, `-strip`, `-objdump`, `-readobj`, `-readelf`, `-size`,
  `-symbolizer`, `-addr2line`, `-cxxfilt`. Their only target is ARM.
- `armv7a-nbt/include/`: the NBT C library headers (threads, semaphores, the
  bridge's sockets, directories), implemented by the SDK's module runtime.
- `armv7a-nbt/aligned/` and `armv7a-nbt/unaligned/`: picolibc, compiler-rt
  builtins (with emulated TLS) and libc++, libc++abi and libunwind, built with
  strict alignment or allowing unaligned accesses. Each `target.mk` holds the
  flags code linking that runtime must be compiled with.
- `share/licenses/`: the licences of everything above.

## Licences

- The tools, compiler-rt, libc++, libc++abi and libunwind: Apache-2.0 WITH
  LLVM-exception (`share/licenses/llvm-project/`). By the exception, a payload
  that contains these runtime libraries owes no attribution for them.
- picolibc: BSD-style licences (`share/licenses/picolibc/`). Every payload
  contains picolibc: ship these notices with it.
- The NBT C library headers: MPL-2.0 (`share/licenses/nbt-toolchain/`).

## Hosts

Linux x86-64 with glibc 2.28 or newer, macOS 11 or newer on Apple silicon,
Windows 10 or newer on x86-64 (the SDK's makefiles run under MSYS2).
