#!/usr/bin/env bash
ROOT="$(realpath "$(dirname "$0")")"

TFM_DIR="$(realpath "${ROOT}/../TF-M")"
BUILD_DIR="$(realpath "${ROOT}/../Build_STM32L552_level2")"
PLATFORM_DIR="$(realpath "${TFM_DIR}/platform/ext/target/stm/nucleo_l552ze_q")"

# Static Configuration Values
CLEAN=false

#-------------------------------------------------------------------------------
# Parse arguments
#-------------------------------------------------------------------------------
set -e

while [[ $# -gt 0 ]]; do
    case "$1" in
        -c|--clean)
            CLEAN=true
            shift
            ;;
        -h|--help)
            echo "Usage: $0 [-c|--clean]"
            exit 0
            ;;
        *)
            echo "Unknown argument: $1"
            echo "Usage: $0 [-c|--clean]"
            exit 1
            ;;
    esac
done

#-------------------------------------------------------------------------------
# Clean up if requested
#-------------------------------------------------------------------------------
if [ "$CLEAN" = true ]; then
    echo "Cleaning build directory..."
    rm -rf ${BUILD_DIR} || true
    echo "Clean completed."
    exit 0
fi

#-------------------------------------------------------------------------------
# Configure S build system 
#-------------------------------------------------------------------------------
cmake   -S ${TFM_DIR}                                           \
        -B ${BUILD_DIR}                                         \
        -DKEYPAD=ON                                             \
        -DCOVERT=OFF                                            \
        -DAPPROT=OFF                                            \
        -DTFM_ISOLATION_LEVEL=2                                 \
        -DTFM_PSA_API=ON                                        \
        -DCMAKE_BUILD_TYPE=Debug                                \
        -DTFM_PLATFORM=${PLATFORM_DIR}                          \
        -DTFM_TOOLCHAIN_FILE=${TFM_DIR}/toolchain_GNUARM.cmake  \
        -G"Unix Makefiles"

#-------------------------------------------------------------------------------
# Configure TAS build system 
#-------------------------------------------------------------------------------
cp -R ${ROOT}/src/NS/* ${BUILD_DIR}/lib/ext/tfm_test_repo-src/app/
cp -R ${ROOT}/src/busSideChannel_lib ${BUILD_DIR}/lib/ext/tfm_test_repo-src/

cp -R ${ROOT}/src/TAs/keypad/* ${TFM_DIR}/secure_fw/partitions/keypad
