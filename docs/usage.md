<!-- SPDX-License-Identifier: MPL-2.0 -->
# NBT toolchain

Clang and LLD for building NBT application modules and guests (ARMv7-A, for
the NBT head unit's QNX 6.5), with the runtime they link statically, and for
building ordinary QNX 6.5 programs without the QNX SDP. It is
used through the NBT SDK: the SDK's `make toolchain` installs the release it is
pinned to, or set `NBT_TOOLCHAIN` to this directory. `VERSION` names the
release, the host and the sources it was built from.

Built by NBTFoundry from LLVM and picolibc sources; not an LLVM release.

## Contents

- `bin/`: `clang`, `clang++`, `ld.lld`, and `llvm-ar`, `-ranlib`, `-nm`,
  `-objcopy`, `-strip`, `-objdump`, `-readobj`, `-readelf`, `-size`,
  `-symbolizer`, `-addr2line`, `-cxxfilt`. Their only target is ARM.
- `armv7a-nbt/include/`: the NBT C library headers (threads, semaphores, the
  bridge's sockets, directories, anonymous and executable memory mappings,
  ARM CPU feature bits), implemented by the SDK's module runtime.
- `armv7a-nbt/aligned/` and `armv7a-nbt/unaligned/`: picolibc, compiler-rt
  builtins (with emulated TLS; `__clear_cache` comes from the SDK's module
  runtime) and libc++, libc++abi and libunwind, built with
  strict alignment or allowing unaligned accesses. Each `target.mk` holds the
  flags code linking that runtime must be compiled with.
- `armv7a-nbt/qnx/`: the QNX 6.5 target, for ordinary programs of the head
  unit built without the QNX SDP. A program built with it is a QNX
  executable that links the car's own shared libraries when it starts.
  - `include/`: headers for the car's C library and QNX's own interfaces
    (message passing, resource managers, `devctl`, the USB stack, sound),
    written for this toolchain; and OpenSSL 1.0.1l's, the car's `libssl.so.2`
    and `libcrypto.so.2`.
  - `lib/`: `crt1.o`; link stubs of the car's libraries (`libc`, `libm`,
    `libsocket`, `libusbdi`, `libasound`, `libscreen`, `libEGL`, `libGLESv2`,
    `libz`, `libssl`, `libcrypto`, `liba2i_client`): their names only, no
    code; `libnbtqnx.a` (C library functions QNX programs link statically,
    such as `popen`); compiler-rt builtins.
  - `cxx/`: libc++, libc++abi and libunwind, with exceptions, linked
    statically (no iostreams or locales: QNX 6.5 has no `locale_t`).
  - `target.mk`: the compile and link flags (`NBT_QNX_CXXFLAGS`,
    `NBT_QNX_LDFLAGS`, `NBT_QNX_LDLIBS`; set `NBT_QNX` to this directory).
- `share/licenses/`: the licences of everything above.

## Licences

- The tools, compiler-rt, libc++, libc++abi and libunwind: Apache-2.0 WITH
  LLVM-exception (`share/licenses/llvm-project/`). By the exception, a payload
  that contains these runtime libraries owes no attribution for them.
- picolibc: BSD-style licences (`share/licenses/picolibc/`). Every payload
  contains picolibc: ship these notices with it.
- The NBT C library headers, the QNX target's headers, `crt1.o`, the link
  stubs and `libnbtqnx.a`: MPL-2.0 (`share/licenses/nbt-toolchain/`).
- OpenSSL's headers: the OpenSSL and SSLeay licences
  (`share/licenses/openssl/`).

## Hosts

Linux x86-64 with glibc 2.28 or newer, macOS 11 or newer on Apple silicon,
Windows 10 or newer on x86-64 (the SDK's makefiles run under MSYS2).
