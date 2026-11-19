# SPDX-License-Identifier: MPL-2.0
# The Linux build image (scripts/linux-run.sh): glibc 2.28, so what it builds
# runs on RHEL 8, Debian 10, Ubuntu 20.04 and later; GCC 14 and CMake, plus
# Ninja and Meson.
FROM quay.io/pypa/manylinux_2_28_x86_64@sha256:d086f64cddcace250ef0f0073583c51b8298159303290a730c9f59bd91edfd2c
RUN pipx install ninja==1.11.1.1 && pipx install meson==1.6.1
