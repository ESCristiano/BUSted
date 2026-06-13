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
    # rm -rf ${BUILD_DIR} || true
    echo "Clean completed."
    exit 0
fi

cmake --build ${BUILD_DIR} -- install
