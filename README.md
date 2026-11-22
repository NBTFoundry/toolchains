<!-- SPDX-License-Identifier: MPL-2.0 -->
# NBT toolchains

The compiler for NBT applications built without the QNX SDP (the SDK's
`docs/native-apps.md`): Clang and LLD 17.0.6 for ARM only, and the runtime
every module and guest links statically (picolibc, compiler-rt, libc++). One
release per version, for Linux x86-64, macOS arm64 and Windows x86-64. What a
release contains, and its licences: [docs/usage.md](docs/usage.md), which
ships in every archive as its README.

It also has a QNX 6.5 target: ordinary programs for the head unit (an
application that must stay a native QNX program, such as a daemon that loads
the car's own libraries), built without the QNX SDP and linked at run time
against the car's libraries.

Nothing here comes from QNX: the module and guest runtime only meets QNX
through the runner, and the QNX target's headers, startup file and link stubs
are written for this toolchain from the car's ABI (layouts, constants, symbol
names).

Not affiliated with or endorsed by BlackBerry Limited or BMW AG. QNX is a
trademark of BlackBerry Limited; BMW and NBT are trademarks of BMW AG.

## Layout

- `cmake/llvm.cmake`: how Clang and LLD are configured.
- `libc/include/`: the NBT C library headers. The SDK's module runtime
  (`module/runtime/`) implements them; libc++ is built against them, which is
  why they live here.
- `scripts/build-llvm.sh`: the host tools, on the host they are for.
- `scripts/build-runtime.sh`: the target runtime, once for every host, in two
  variants (strict alignment and unaligned accesses), each with the
  `target.mk` the SDK compiles with.
- `qnx/`: the QNX 6.5 target. `include/` the headers (the car's C library
  and QNX interfaces), `crt/crt1.S` the program entry, `stubs/*.syms` the
  symbols the car's shared libraries export (names and sizes, for link
  stubs), `libc/` functions QNX programs normally link statically.
- `scripts/build-qnx.sh`: the QNX target (stubs, `crt1.o`, `libnbtqnx.a`,
  builtins, libc++ over `qnx/include`, OpenSSL's headers, `target.mk`).
- `scripts/qnx-stubs.py`: builds the link stubs; `extract` rewrites the
  lists from copies of the car's libraries.
- `scripts/check-qnx-abi.py` (`make check-qnx-abi QNX_ENV=...`): for
  maintainers with the QNX 6.5 SP1 SDP, compares every layout, constant and
  prototype of `qnx/include` with the SDP's headers. It must report no
  difference; no build needs the SDP.
- `tests/qnx/`: a C++ probe (exceptions, threads, the C library); run it in
  the SDK's QNX 6.5 VM (`tools/qnx65-vm/run.sh`) or on the car.
- `scripts/package.py`: one host's archive, reproducibly.
- `scripts/test-sdk.sh`: builds the SDK's test payloads with a packaged
  toolchain (`tests/sdk`, a submodule pinned to an SDK commit).
- `third_party/`: LLVM, picolibc and OpenSSL 1.0.1l (headers only, the
  car's version), as shallow submodules.

## Building

Linux (Docker; the tools are built in a manylinux image so they need only
glibc 2.28) or macOS (Xcode, CMake, Ninja; Meson for the runtime):

```sh
git submodule update --init --recursive --depth 1
make            # out/dist/<host>/nbt-toolchain-<version>/ and its archive
make test       # the SDK's payloads, built with it
```

`NBT_JOBS` limits parallel jobs. The first LLVM build takes a while; later
ones are incremental. Windows builds run in CI only
(`.github/workflows/ci.yml` shows the steps: Git Bash with the MSVC
environment).

## CI and releases

Every push to `main` and every pull request builds LLVM on each host (cached
until its sources or configuration change), the runtime once, the three
archives, and then builds the SDK's payloads with each archive on its own
host. The payloads must come out byte-identical on all three.

To release: bump `VERSION`, update `tests/sdk` if needed, merge, then push the
tag `v<VERSION>`. The tag's run publishes the archives and `SHA256SUMS` once
every test passes. Then, in the SDK, set `NBT_TOOLCHAIN_VERSION` in
`module/flags.mk` and copy the release's `SHA256SUMS` to
`module/toolchain.sha256`: `make toolchain` installs only what it pins.

A change to `libc/include/` changes what the SDK's module runtime must
implement: release it with the matching SDK change. A change to
`qnx/include/` passes `make check-qnx-abi` before it is merged.

## Not yet

- More hosts (Linux arm64, macOS x86-64): another matrix entry in CI.
- Rust. No stable Rust target matches the payload ABI: `armv7a-none-eabi`
  ships non-PIC `core` (modules allow only relative relocations), 8-bit C
  enums and software floating point; `armv7-unknown-linux-gnueabi` is PIC
  but also soft-float and allows unaligned accesses. It needs a custom target
  (softfp with VFPv3-D16, int-size enums, PIC, strict alignment), nightly
  `-Zbuild-std=core,alloc`, and a crate with the SDK bindings, an allocator
  and a panic handler.
