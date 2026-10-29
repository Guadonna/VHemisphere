#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
test_binary=$(mktemp /tmp/vhemisphere-test.XXXXXX)
trap 'rm -f "$test_binary"' EXIT
${CXX:-g++} -std=c++17 -Wall -Wextra -Werror -fsanitize=undefined -fno-sanitize-recover=undefined \
  software/test/vhemisphere/output_test.cpp software/src/src/extern/braids_quantizer.cpp -o "$test_binary"
"$test_binary"
