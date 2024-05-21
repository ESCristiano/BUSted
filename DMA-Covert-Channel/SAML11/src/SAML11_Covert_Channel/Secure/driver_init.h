/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef DRIVER_INIT_INCLUDED
#define DRIVER_INIT_INCLUDED

#include "atmel_start_pins.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <hal_atomic.h>
#include <hal_delay.h>
#include <hal_gpio.h>
#include <hal_init.h>
#include <hal_io.h>
#include <hal_sleep.h>
#include <hpl_crya.h>

#include <tc_lite.h>

#include <hal_i2c_m_sync.h>

extern struct i2c_m_sync_desc I2C_INSTANCE;

void TIMER_0_CLOCK_init(void);

int8_t TIMER_0_init(void);

void I2C_INSTANCE_CLOCK_init(void);
void I2C_INSTANCE_init(void);
void I2C_INSTANCE_PORT_init(void);

/**
 * \brief Perform system initialization, initialize pins and clocks for
 * peripherals
 */
void system_init(void);

#ifdef __cplusplus
}
#endif
#endif // DRIVER_INIT_INCLUDED
