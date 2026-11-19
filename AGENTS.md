# Repository guide

The NBT toolchain: Clang/LLD and the target runtime for NBT modules and guests
(README.md). Releases are consumed by NBTFoundry/sdk, which pins a version.

- Keep every QNX file out: no SDP header, library or tool, here or in a
  release. GPL code must not enter the runtime.
- The ABI is fixed by `scripts/build-runtime.sh` (target flags, written to
  `target.mk`) and `libc/include/` (types the SDK's module runtime shares
  with libc++). Changing either needs the matching SDK change and a new
  release; never change a released version.
- Keep releases reproducible: archives come from `scripts/package.py` only,
  built by CI from a tag. Payloads must stay byte-identical across hosts.
- Third-party code goes in as submodules with SSH URLs.
- Shell scripts are POSIX sh; they run on Linux, macOS and Git Bash/MSYS2.
