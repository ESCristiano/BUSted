/*
 * Copyright (c) 2021, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __MMIO_DEFS_H__
#define __MMIO_DEFS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "tfm_peripherals_def.h"

/* Boundary handle binding macros. */
#define HANDLE_PER_ATTR_BITS            (0x4)
#define HANDLE_ATTR_PRIV_MASK           ((1 << HANDLE_PER_ATTR_BITS) - 1)
#if TFM_LVL == 3
#define HANDLE_ATTR_RW_POS              (1 << (HANDLE_PER_ATTR_BITS - 1))
#define HANDLE_ATTR_INDEX_MASK          (HANDLE_ATTR_RW_POS - 1)
#define HANDLE_INDEX_BITS               (0x8)
#define HANDLE_INDEX_MASK               (((1 << HANDLE_INDEX_BITS) -1) << 24)
#define HANDLE_ENCODE_INDEX(attr, idx)                              \
    do {                                                            \
        (attr) |= (((idx) << 24) & HANDLE_INDEX_MASK);              \
        (idx)++;                                                    \
    } while (0)
#endif

/* Allowed named MMIO of this platform */
const uintptr_t partition_named_mmio_list[] = {
    (uintptr_t)TFM_PERIPHERAL_TIMER0,
    (uintptr_t)TFM_PERIPHERAL_STD_UART,
    //added by cris
    (uintptr_t) TFM_PERIPHERAL_GPIOA,
    (uintptr_t) TFM_PERIPHERAL_GPIOB,
    (uintptr_t) TFM_PERIPHERAL_GPIOC,
    (uintptr_t) TFM_PERIPHERAL_GPIOD,
    (uintptr_t) TFM_PERIPHERAL_GPIOG,
    (uintptr_t) TFM_PERIPHERAL_PWR,
    (uintptr_t) TFM_PERIPHERAL_RCC,
};

#ifdef __cplusplus
}
#endif

#endif /* __MMIO_DEFS_H__ */
