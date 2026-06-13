#-------------------------------------------------------------------------------
# Copyright (c) 2021, Arm Limited. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#
#-------------------------------------------------------------------------------
if (NOT APPROT)
    return()
endif()

cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0079 NEW)

add_library(tfm_app_rot_partition_appRoT STATIC)

target_sources(tfm_app_rot_partition_appRoT
    PRIVATE
        appRoT.c
)

# The generated sources
target_sources(tfm_app_rot_partition_appRoT
    PRIVATE
        ${CMAKE_BINARY_DIR}/generated/secure_fw/partitions/appRoT/auto_generated/intermedia_appRoT.c
)
target_sources(tfm_partitions
    INTERFACE
        $<$<BOOL:${TFM_PSA_API}>:
            ${CMAKE_BINARY_DIR}/generated/secure_fw/partitions/appRoT/auto_generated/load_info_appRoT.c>
)

# Set include directory
target_include_directories(tfm_app_rot_partition_appRoT
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        ${CMAKE_BINARY_DIR}/generated/secure_fw/partitions/appRoT
)
target_include_directories(tfm_partitions
    INTERFACE
        ${CMAKE_BINARY_DIR}/generated/secure_fw/partitions/appRoT
)

target_link_libraries(tfm_app_rot_partition_appRoT
    PRIVATE
        tfm_secure_api
        psa_interface
        platform_s
        tfm_sprt
)

############################ Partition Defs ####################################
target_link_libraries(tfm_partitions
    INTERFACE
        tfm_app_rot_partition_appRoT
)
target_compile_definitions(tfm_partition_defs
    INTERFACE
        APPROT
)
