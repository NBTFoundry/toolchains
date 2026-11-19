# SPDX-License-Identifier: MPL-2.0
# Build, package and test the NBT toolchain for this host, Linux or macOS
# (README.md). Windows runs the scripts directly (.github/workflows/ci.yml).

VERSION := $(shell cat VERSION)
OUT := out
UNAME := $(shell uname -s)
ifeq ($(UNAME),Linux)
HOST := linux-x86_64
# Built in the manylinux image, so the tools need only glibc 2.28.
RUN := scripts/linux-run.sh
else ifeq ($(UNAME),Darwin)
HOST := macos-arm64
RUN :=
else
$(error Linux or macOS only: on Windows run the scripts as .github/workflows/ci.yml does)
endif

LLVM := $(OUT)/llvm-$(HOST)
RUNTIME := $(OUT)/runtime
TOOLCHAIN := $(OUT)/dist/$(HOST)/nbt-toolchain-$(VERSION)
LIBC_HEADERS := $(shell find libc/include -name '*.h')

.PHONY: all llvm runtime package test clean
all: package

llvm: $(LLVM)/bin/clang
$(LLVM)/bin/clang: cmake/llvm.cmake scripts/build-llvm.sh
	$(RUN) scripts/build-llvm.sh $(OUT)/llvm-build-$(HOST) $(LLVM)
	touch $@

runtime: $(RUNTIME)/aligned/target.mk
$(RUNTIME)/aligned/target.mk: $(LLVM)/bin/clang scripts/build-runtime.sh $(LIBC_HEADERS)
	$(RUN) scripts/build-runtime.sh $(LLVM)/bin $(OUT)/runtime-build $(RUNTIME)

package: $(RUNTIME)/aligned/target.mk
	python3 scripts/package.py --host $(HOST) --llvm $(LLVM) --runtime $(RUNTIME) --out $(OUT)/dist

# The SDK's test payloads (tests/sdk, a submodule) built with the packaged tree.
test: package
	scripts/test-sdk.sh $(TOOLCHAIN) tests/sdk $(OUT)/test

clean:
	rm -rf $(OUT)
