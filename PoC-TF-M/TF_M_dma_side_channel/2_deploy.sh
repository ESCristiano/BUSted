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

#-------------------------------------------------------------------------------
# Deploy the binaries to the board
#-------------------------------------------------------------------------------
# postbuild.sh  -> To know where the binaries should be placed
# bash ${BUILD_DIR}/postbuild.sh
# regression.sh -> To prepare/config the board
bash ${BUILD_DIR}/regression.sh
# TFM_UPDATE.sh -> To flash the NS, S and SBSFU binaries  to the board
# bash ${BUILD_DIR}/TFM_UPDATE.sh

stm32programmercli="STM32_Programmer_CLI"
cubedir="`which STM32_Programmer_CLI`"
cubedir="$(dirname "${cubedir}")"
external_loader="-el $cubedir/ExternalLoader/MX25LM51245G_STM32L562E-DK.stldr"
connect="-c port=SWD "$sn_option" mode=UR --hardRst $external_loader"

echo "Write TFM_Appli Secure"
# part ot be updated according to flash_layout.h
slot0=0xc013000
slot1=0xc050000
slot2=0xc069000
slot3=0xc0a6000
its=0xc011000
sst=0xc00f000
scratch=0xc00e000
nvcounter=0xc00e000
boot=0xc000000
unused=0xc0bf000

$stm32programmercli $connect -d ${BUILD_DIR}/bin/tfm_s_signed.bin $slot0 -v
echo "TFM_Appli Secure Written"
echo "Write TFM_Appli NonSecure"
$stm32programmercli $connect -d ${BUILD_DIR}/bin/tfm_ns_signed.bin $slot1 -v
echo "TFM_Appli NonSecure Written"
echo "Write TFM_SBSFU_Boot"
$stm32programmercli $connect -d ${BUILD_DIR}/bin/bl2.bin $boot -v
echo "TFM_SBSFU_Boot Written"
echo "TFM_UPDATE Done"
