#!/bin/sh
# SPDX-License-Identifier: MPL-2.0
# Run a command in the Linux build image (scripts/linux.Dockerfile), as the
# calling user, with this checkout mounted at the same path:
#
#   scripts/linux-run.sh <command> [argument...]
#
# Run it from inside the checkout. NBT_JOBS is passed on.
set -eu
ROOT=$(cd "$(dirname "$0")/.." && pwd)
IMAGE=nbt-toolchain-linux
docker build -q -t "$IMAGE" -f "$ROOT/scripts/linux.Dockerfile" "$ROOT/scripts" >/dev/null
exec docker run --rm -u "$(id -u):$(id -g)" -e HOME=/tmp -e NBT_JOBS \
    -v "$ROOT:$ROOT" -w "$PWD" "$IMAGE" "$@"
