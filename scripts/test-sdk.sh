#!/bin/sh
# SPDX-License-Identifier: MPL-2.0
# Test a toolchain by building the SDK's test payloads with it, as modules and
# as guests, with each runtime variant; the SDK's link step checks every
# payload. A second make must find nothing to do. Writes the payloads'
# SHA-256 to <build-dir>/payloads.sha256: every host must produce the same.
#
#   scripts/test-sdk.sh <toolchain-dir> <sdk-dir> <build-dir>
#
# MAKE: GNU make 4.3 or newer (default make). JOBS: parallel jobs.
set -eu
usage="usage: test-sdk.sh <toolchain-dir> <sdk-dir> <build-dir>"
TOOLCHAIN=$(cd "${1:?$usage}" && pwd)
SDK=$(cd "${2:?$usage}" && pwd)
mkdir -p "${3:?$usage}"
OUT=$(cd "$3" && pwd)
MAKE=${MAKE:-make}
JOBS=${JOBS:-$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 2)}
PAYLOADS="probe car-probe smoke"

"$TOOLCHAIN/bin/clang" --version | head -n 1
for variant in aligned unaligned; do
    unaligned=0
    [ "$variant" = unaligned ] && unaligned=1
    TARGETS=
    for p in $PAYLOADS; do TARGETS="$TARGETS $OUT/$variant/$p.so $OUT/$variant/$p.guest"; done
    set -- -C "$SDK" BUILD_DIR="$OUT/$variant" NBT_TOOLCHAIN="$TOOLCHAIN" NBT_MOD_UNALIGNED=$unaligned
    # shellcheck disable=SC2086
    "$MAKE" "$@" -j"$JOBS" $TARGETS
    # shellcheck disable=SC2086
    if "$MAKE" "$@" -q $TARGETS; then :; else
        echo "test-sdk: a second make would rebuild ($variant)" >&2
        exit 1
    fi
done

cd "$OUT"
if command -v sha256sum >/dev/null 2>&1; then sum="sha256sum"; else sum="shasum -a 256"; fi
# (MSYS2's sha256sum marks binary mode with "*")
# shellcheck disable=SC2086
$sum aligned/*.so aligned/*.guest unaligned/*.so unaligned/*.guest | sed 's/ \*/  /' > payloads.sha256
cat payloads.sha256
