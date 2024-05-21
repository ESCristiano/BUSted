/**
 * \file
 *
 * \brief TrustZone secure gateway veneer header file.
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#ifndef _TRUSTZONE_VENEER_H_INCLUDED
#define _TRUSTZONE_VENEER_H_INCLUDED

#include <compiler.h>

/* ======== Non-secure callable common driver functions ======== */

/**
 *  \brief External IRQ settings for EIC
 */
//@{
struct ext_irq_setting {
	uint32_t evctrl;    /** EIC.EVCTRL register value */
	uint32_t config[1]; /** EIC.CONFIG register value */
	uint32_t asynch;    /** EIC.ASYNCH register value */
	uint32_t debouncen; /** EIC.DEBOUNCEN register value */
};
//@}

/**
 * \brief Initialize peripheral clock.
 *
 * \param[in] gclk_id    GCLK ID for the peripheral
 * \param[in] gclk_src   GCLK source for the peripheral
 *
 * \return The status of operation request
 * \retval  0 The operation is completed successfully
 * \retval  1 No operation needed, the peripheral clock is enabled already
 */
extern int32_t nsc_periph_clock_init(uint32_t gclk_id, uint32_t gclk_src);

/**
 * \brief Initialize non-secure external interrupt.
 *
 * \param[in] irq_setting    Non-secure external IRQ settings
 *
 * \return 0 if the operation is completed successfully
 */
extern int32_t nsc_ext_irq_init(struct ext_irq_setting irq_setting);

/* ======== Non-secure callable functions for Secure Driver Example ======== */

/**
 * \brief Get value from temperature sensor
 *
 * \return temperature
 */
extern uint32_t nsc_temperature_sensor_read(void);

/* ======== Non-secure callable functions defined by customer ======== */
/* Add your function declaration here */

extern void trojan_s(int input_symbol);

#endif /* _TRUSTZONE_VENEER_H_INCLUDED */
