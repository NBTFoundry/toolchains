<!-- SPDX-License-Identifier: MPL-2.0 -->
# NBT toolchains

The compiler for NBT applications built without the QNX SDP (the SDK's
`docs/native-apps.md`): Clang and LLD 17.0.6 for ARM only, and the runtime
every module and guest links statically (picolibc, compiler-rt, libc++). One
release per version, for Linux x86-64, macOS arm64 and Windows x86-64. What a
release contains, and its licences: [docs/usage.md](docs/usage.md), which
ships in every archive as its README.

Nothing here comes from QNX: the runtime only meets QNX through the runner.

## Layout

- `cmake/llvm.cmake`: how Clang and LLD are configured.
- `libc/include/`: the NBT C library headers. The SDK's module runtime
  (`module/runtime/`) implements them; libc++ is built against them, which is
  why they live here.
- `scripts/build-llvm.sh`: the host tools, on the host they are for.
- `scripts/build-runtime.sh`: the target runtime, once for every host, in two
  variants (strict alignment and unaligned accesses), each with the
  `target.mk` the SDK compiles with.
- `scripts/package.py`: one host's archive, reproducibly.
- `scripts/test-sdk.sh`: builds the SDK's test payloads with a packaged
  toolchain (`tests/sdk`, a submodule pinned to an SDK commit).
- `third_party/`: LLVM and picolibc, as shallow submodules.

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

The test job reads the private SDK with a read-only deploy key: the
`SDK_DEPLOY_KEY` secret here, whose public half is a deploy key on
NBTFoundry/sdk.

To release: bump `VERSION`, update `tests/sdk` if needed, merge, then push the
tag `v<VERSION>`. The tag's run publishes the archives and `SHA256SUMS` once
every test passes. Then update `NBT_TOOLCHAIN_VERSION` in the SDK's
`module/flags.mk`.

A change to `libc/include/` changes what the SDK's module runtime must
implement: release it with the matching SDK change.

## Not yet

- More hosts (Linux arm64, macOS x86-64): another matrix entry in CI.
- Rust. No stable Rust target matches the payload ABI: `armv7a-none-eabi`
  ships non-PIC `core` (modules allow only relative relocations), 8-bit C
  enums and software floating point; `armv7-unknown-linux-gnueabi` is PIC
  but also soft-float and allows unaligned accesses. It needs a custom target
  (softfp with VFPv3-D16, int-size enums, PIC, strict alignment), nightly
  `-Zbuild-std=core,alloc`, and a crate with the SDK bindings, an allocator
  and a panic handler.
