# SPDX-License-Identifier: MPL-2.0
# The toolchain's host tools (scripts/build-llvm.sh loads this as CMake's
# initial cache): clang and lld for ARM only, and the binary utilities NBT
# builds use. No optional host library is linked, so the tools need nothing
# installed beside them.

set(CMAKE_BUILD_TYPE Release CACHE STRING "")
set(LLVM_ENABLE_PROJECTS "clang;lld" CACHE STRING "")
set(LLVM_TARGETS_TO_BUILD ARM CACHE STRING "")
set(LLVM_DEFAULT_TARGET_TRIPLE armv7a-none-eabi CACHE STRING "")
set(LLVM_ENABLE_ASSERTIONS OFF CACHE BOOL "")
set(LLVM_PARALLEL_LINK_JOBS 4 CACHE STRING "")

# "NBT clang version 17.0.6": our build, not an LLVM release. No repository
# path or revision in version strings, so every host's compiler writes the
# same .comment section.
set(PACKAGE_VENDOR NBT CACHE STRING "")
set(CLANG_VENDOR NBT CACHE STRING "")
set(LLD_VENDOR NBT CACHE STRING "")
set(LLVM_APPEND_VC_REV OFF CACHE BOOL "")

foreach(lib ZLIB ZSTD LIBXML2 TERMINFO LIBEDIT LIBPFM CURL HTTPLIB)
  set(LLVM_ENABLE_${lib} OFF CACHE STRING "")
endforeach()
set(LLVM_ENABLE_BINDINGS OFF CACHE BOOL "")
foreach(part TESTS EXAMPLES BENCHMARKS DOCS)
  set(LLVM_INCLUDE_${part} OFF CACHE BOOL "")
endforeach()
set(CLANG_INCLUDE_TESTS OFF CACHE BOOL "")
set(CLANG_INCLUDE_DOCS OFF CACHE BOOL "")
set(CLANG_ENABLE_ARCMT OFF CACHE BOOL "")
set(CLANG_ENABLE_STATIC_ANALYZER OFF CACHE BOOL "")
set(CLANG_PLUGIN_SUPPORT OFF CACHE BOOL "")

# What install-distribution installs. clang brings clang++ and lld brings
# ld.lld; the other aliases (llvm-ranlib, llvm-readelf, llvm-strip,
# llvm-addr2line) are components of their own. scripts/package.py keeps only
# these.
set(LLVM_DISTRIBUTION_COMPONENTS
  clang clang-resource-headers lld
  llvm-ar llvm-ranlib llvm-nm llvm-objcopy llvm-strip llvm-objdump llvm-readobj llvm-readelf
  llvm-size llvm-symbolizer llvm-addr2line llvm-cxxfilt
  CACHE STRING "")
