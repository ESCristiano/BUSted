#-------------------------------------------------------------------------------
# Copyright (c) 2021, Arm Limited. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#
#-------------------------------------------------------------------------------
if (NOT KEYPAD)
    return()
endif()

cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0079 NEW)

add_library(tfm_app_rot_partition_keypad STATIC)

target_sources(tfm_app_rot_partition_keypad
    PRIVATE
        ./Src/main.c
        ./Src/keypad.c
        ./Src/gpio.c
)

# The generated sources
target_sources(tfm_app_rot_partition_keypad
    PRIVATE
        ${CMAKE_BINARY_DIR}/generated/secure_fw/partitions/keypad/auto_generated/intermedia_keypad.c
)
target_sources(tfm_partitions
    INTERFACE
        $<$<BOOL:${TFM_PSA_API}>:
            ${CMAKE_BINARY_DIR}/generated/secure_fw/partitions/keypad/auto_generated/load_info_keypad.c>
)

# Set include directory
target_include_directories(tfm_app_rot_partition_keypad
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        ${CMAKE_BINARY_DIR}/generated/secure_fw/partitions/keypad
        ./Inc
)
target_include_directories(tfm_partitions
    INTERFACE
        ${CMAKE_BINARY_DIR}/generated/secure_fw/partitions/keypad
)

target_link_libraries(tfm_app_rot_partition_keypad
    PRIVATE
        tfm_secure_api
        psa_interface
        platform_s
        tfm_sprt
)

############################ Partition Defs ####################################
target_link_libraries(tfm_partitions
    INTERFACE
        tfm_app_rot_partition_keypad
)
target_compile_definitions(tfm_partition_defs
    INTERFACE
        keypad
)
