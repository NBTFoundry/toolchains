#!/bin/sh
# SPDX-License-Identifier: MPL-2.0
# CI: check out public submodules (all of them by default) at depth 1. They
# are recorded with SSH URLs; CI has no SSH key for them, so fetch over HTTPS.
#
#   scripts/ci-fetch.sh [path...]
set -eu
exec git -c url.https://github.com/.insteadOf=git@github.com: submodule update --init --depth 1 "$@"
