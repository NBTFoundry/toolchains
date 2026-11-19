#!/bin/sh
# SPDX-License-Identifier: MPL-2.0
# CI: check out submodules (all of them by default) at depth 1. They are
# recorded with SSH URLs; CI has no SSH key, and every one is public, so fetch
# over HTTPS (nested submodules too, with --recursive).
#
#   scripts/ci-fetch.sh [--recursive] [path...]
set -eu
exec git -c url.https://github.com/.insteadOf=git@github.com: submodule update --init --depth 1 "$@"
