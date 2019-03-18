/**
 * \file
 *
 * \brief SAM Power Driver Quick Start
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include "conf_test.h"

//! [setup]

//! [switch_pl]
/**
 * \brief Switch performance level to PL2 and GCLK0 is running at 48MHz.
 */
static void performance_level_switch_test(void)
{
	struct system_gclk_gen_config gclk_conf;

	/* Switch to PL2 */
	system_switch_performance_level(SYSTEM_PERFORMANCE_LEVEL_2);
	system_flash_set_waitstates(2);

	/* Switch GCLK0 to 48MHz */
	system_gclk_gen_get_config_defaults(&gclk_conf);
	gclk_conf.source_clock = SYSTEM_CLOCK_SOURCE_DFLL;
	gclk_conf.division_factor = 1;
	gclk_conf.run_in_standby  = false;
	gclk_conf.output_enable   = true;
	system_gclk_gen_set_config(GCLK_GENERATOR_0, &gclk_conf);
}
//! [switch_pl]

//! [pin_mux]
/**
 * \brief Config GCLK0/GCLK1 output pin and extwakeup pin.
 */
static void config_clock_output_and_extwake_pin(void)
{
	struct system_pinmux_config pin_conf;
	system_pinmux_get_config_defaults(&pin_conf);

	pin_conf.mux_position = CONF_GCLK0_OUTPUT_PINMUX;
	pin_conf.direction    = SYSTEM_PINMUX_PIN_DIR_OUTPUT;
	system_pinmux_pin_set_config(CONF_GCLK0_OUTPUT_PIN, &pin_conf);
	pin_conf.mux_position = CONF_GCLK1_OUTPUT_PINMUX;
	system_pinmux_pin_set_config(CONF_GCLK1_OUTPUT_PIN, &pin_conf);
#if SAML21 || SAMR30
	pin_conf.direction = SYSTEM_PINMUX_PIN_DIR_INPUT;
	pin_conf.input_pull = SYSTEM_PINMUX_PIN_PULL_UP;
	pin_conf.mux_position = CONF_EXT_WAKEUP_PINMUX;
	system_pinmux_pin_set_config(CONF_EXT_WAKEUP_PIN, &pin_conf);
#endif
}
//! [pin_mux]

//! [config_extint]
/**
 * \brief Config external interrupt.
 */
static void configure_extint_channel(void)
{

	struct extint_chan_conf config_extint_chan;
	extint_chan_get_config_defaults(&config_extint_chan);
	config_extint_chan.gpio_pin           = BUTTON_0_EIC_PIN;
	config_extint_chan.gpio_pin_mux       = BUTTON_0_EIC_MUX;
	config_extint_chan.gpio_pin_pull      = EXTINT_PULL_UP;
	config_extint_chan.detection_criteria = EXTINT_DETECT_BOTH;
	extint_chan_set_config(BUTTON_0_EIC_LINE, &config_extint_chan);
 	extint_chan_enable_callback(BUTTON_0_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);
	system_interrupt_enable_global();
	while (extint_chan_is_detected(BUTTON_0_EIC_LINE)) {
		extint_chan_clear_detected(BUTTON_0_EIC_LINE);
	}
}
//! [config_extint]

/**
 * \brief Turn LED ON and OFF as an indication.
 */
static void led_toggle_indication(uint32_t count)
{
	for (uint32_t i = 0; i < count; i++) {
		port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
		delay_ms(200);
		port_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);
		delay_ms(200);
	}
}
//! [setup]

int main(void)
{
//! [setup_init]

//! [ext_wakeup]
#if SAML21 || SAMR30
	/* Check if the RESET is caused by external wakeup pin */
	if (system_get_reset_cause() == SYSTEM_RESET_CAUSE_BACKUP
		&& system_get_backup_exit_source() == SYSTEM_RESET_BACKKUP_EXIT_EXTWAKE
		&& (system_get_pin_wakeup_cause() & (1 << CONF_EXT_WAKEUP_PIN))
		) {
		system_init();
		delay_init();
		config_clock_output_and_extwake_pin();
		/* Now GCLK0/GCLK1 are running at 4MHz , using LED0 ON/OFF as an indication */
		led_toggle_indication(4);
		port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
		while(1);
	}
#endif
//! [ext_wakeup]

//! [backup_stanby_mode]

	/* Disable I/O retention*/
	system_io_retension_disable();

	system_init();
	delay_init();

	port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);

	/* Config GCLK0/GCLK1 output pin and extwakeup pin */
	config_clock_output_and_extwake_pin();

	/* Config external interrupt for wakeup system from standby mode*/
	configure_extint_channel();
	delay_s(1);

	/* Turn off LED0 before enter standby mode */
	port_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);

	/* Set and enter standby mode, using default stanby config */
	system_set_sleepmode(SYSTEM_SLEEPMODE_STANDBY);
	system_sleep();

	/* Detect BUTTON pressed and system  wakeup from standby mode,
		turn on led */
	port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);

	/* Disable external interrupt to avoid any impact */
	extint_chan_disable_callback(BUTTON_0_EIC_LINE,
				EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_clear_detected(BUTTON_0_EIC_LINE);

	/* Switch GCLK0 to 48MHz */
	performance_level_switch_test();

	/* GCLK0 is runing at 48MHz and GCLK1 is running at 4MHz ,
		use led ON/OFF as an indication */
	led_toggle_indication(2);

#if SAML21 || SAMR30
	/* Set external wakeup pin polarity */
	system_set_pin_wakeup_polarity_low(1<<CONF_EXT_WAKEUP_PIN);

	/* Set external wakeup detector */
	system_enable_pin_wakeup(1<<CONF_EXT_WAKEUP_PIN);
	system_set_pin_wakeup_debounce_counter(SYSTEM_WAKEUP_DEBOUNCE_2CK32);

	/* Enter BACKUP mode */
	system_set_sleepmode(SYSTEM_SLEEPMODE_BACKUP);
	system_sleep();

	/* Now system is in BACKUP mode and wait for extwakeup pin to low */
#endif
//! [backup_stanby_mode]

//! [setup_init]
	while(1){
		;
	}

}
