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

struct usart_sync_descriptor EDBG_COM;

void EDBG_COM_PORT_init(void)
{

	gpio_set_pin_function(EDBG_COM_TX, PINMUX_PB25D_SERCOM2_PAD0);

	gpio_set_pin_function(EDBG_COM_RX, PINMUX_PB24D_SERCOM2_PAD1);
}

void EDBG_COM_CLOCK_init(void)
{
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM2_GCLK_ID_CORE, CONF_GCLK_SERCOM2_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM2_GCLK_ID_SLOW, CONF_GCLK_SERCOM2_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	hri_mclk_set_APBBMASK_SERCOM2_bit(MCLK);
}

void EDBG_COM_init(void)
{
	EDBG_COM_CLOCK_init();
	usart_sync_init(&EDBG_COM, SERCOM2, (void *)NULL);
	EDBG_COM_PORT_init();
}

void TIMER_0_CLOCK_init(void)
{
	hri_mclk_set_APBAMASK_TC0_bit(MCLK);

	hri_mclk_set_APBAMASK_TC1_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, TC0_GCLK_ID, CONF_GCLK_TC0_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
}

void system_init(void)
{
	init_mcu();

	// GPIO on PC18

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
