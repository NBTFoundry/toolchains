# SPDX-License-Identifier: MPL-2.0
# The QNX 6.5 target's probe (probe.cpp), built with a packaged toolchain:
#   make -f tests/qnx/Makefile NBT_TOOLCHAIN=<toolchain> OUT=<dir>
# Run $(OUT)/qnx-probe-bundle in the QNX 6.5 VM or on the car: it prints
# "qnx-probe: PASS". (The "-bundle" suffix keeps the VM's image builder from
# rewriting it.)
HERE := $(dir $(lastword $(MAKEFILE_LIST)))
NBT_QNX := $(NBT_TOOLCHAIN)/armv7a-nbt/qnx
include $(NBT_QNX)/target.mk
OUT ?= .

# A changed toolchain rebuilds the probe.
TOOLCHAIN_ID := $(NBT_QNX)/target.mk $(NBT_QNX)/lib/crt1.o

$(OUT)/qnx-probe-bundle: $(OUT)/probe.o $(TOOLCHAIN_ID)
	$(NBT_TOOLCHAIN)/bin/ld.lld $(NBT_QNX_LDFLAGS) -o $@ $< -lm $(NBT_QNX_LDLIBS)

$(OUT)/probe.o: $(HERE)probe.cpp $(TOOLCHAIN_ID)
	@mkdir -p $(OUT)
	$(NBT_TOOLCHAIN)/bin/clang++ $(NBT_QNX_CXXFLAGS) -std=c++17 -O2 -ffile-prefix-map=$(abspath $(HERE))/=tests/qnx/ \
		-c $< -o $@
