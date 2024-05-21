/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>
#include <hpl_gclk_base.h>
#include <hpl_pm_base.h>

struct usart_sync_descriptor EDBG_COM;

void EDBG_COM_PORT_init(void)
{

	gpio_set_pin_function(EDBG_COM_TX, PINMUX_PA22C_SERCOM3_PAD0);

	gpio_set_pin_function(EDBG_COM_RX, PINMUX_PA23C_SERCOM3_PAD1);
}

void EDBG_COM_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM3);
	_gclk_enable_channel(SERCOM3_GCLK_ID_CORE, CONF_GCLK_SERCOM3_CORE_SRC);
}

void EDBG_COM_init(void)
{
	EDBG_COM_CLOCK_init();
	usart_sync_init(&EDBG_COM, SERCOM3, (void *)NULL);
	EDBG_COM_PORT_init();
}

void TIMER_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, TC4);

	_pm_enable_bus_clock(PM_BUS_APBC, TC5);

	_gclk_enable_channel(TC4_GCLK_ID, CONF_GCLK_TC4_SRC);
}

void system_init(void)
{
	init_mcu();

	// GPIO on PB30

	gpio_set_pin_level(LED0,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	// Set pin direction to output
	gpio_set_pin_direction(LED0, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(LED0, GPIO_PIN_FUNCTION_OFF);

	EDBG_COM_init();

	TIMER_0_CLOCK_init();

	TIMER_0_init();
}
