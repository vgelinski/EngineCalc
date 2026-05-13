#!/usr/bin/env bash
set -euo pipefail

BUILD_DIR=build-coverage
COV_DIR=coverage
LCOV_OUT="${COV_DIR}/app.info"

cmake -S . -B "${BUILD_DIR}" \
    -DCMAKE_BUILD_TYPE=Debug \
    -DENGINECALC_COVERAGE=ON

cmake --build "${BUILD_DIR}" -j --target testRunner

find "${BUILD_DIR}" -name '*.gcda' -delete

"./${BUILD_DIR}/testRunner"

mkdir -p "${COV_DIR}"

lcov --capture \
     --directory "${BUILD_DIR}" \
     --base-directory "$(pwd)" \
     --output-file "${LCOV_OUT}" \
     --rc branch_coverage=1 \
     --ignore-errors mismatch,inconsistent,unused,gcov,source,negative

lcov --remove "${LCOV_OUT}" \
     '/usr/*' \
     "$(pwd)/${BUILD_DIR}/_deps/*" \
     "$(pwd)/test/*" \
     --output-file "${LCOV_OUT}" \
     --rc branch_coverage=1 \
     --ignore-errors unused

genhtml "${LCOV_OUT}" \
        --output-directory "${COV_DIR}" \
        --branch-coverage \
        --ignore-errors inconsistent,unmapped,source,category

echo "Coverage report: ${COV_DIR}/index.html"
