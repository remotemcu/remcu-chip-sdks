/**
 * \file
 *
 * \brief SAM TC - Timer Counter Driver Quick Start
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
#include "conf_qs_tc_timer.h"

void configure_tc(void);
void configure_tc_callbacks(void);
void tc_callback_to_toggle_led(
		struct tc_module *const module_inst);


//! [module_inst]
struct tc_module tc_instance;
//! [module_inst]

//! [callback_funcs]
void tc_callback_to_toggle_led(
		struct tc_module *const module_inst)
{
	port_pin_toggle_output_level(LED0_PIN);
}
//! [callback_funcs]

//! [setup]
void configure_tc(void)
{
	//! [setup_config]
	struct tc_config config_tc;
	//! [setup_config]
	//! [setup_config_defaults]
	tc_get_config_defaults(&config_tc);
	//! [setup_config_defaults]

	//! [setup_change_config]
	config_tc.counter_size = TC_COUNTER_SIZE_8BIT;
	#if (SAMR30E)
	config_tc.clock_source = GCLK_GENERATOR_0;
	#else
	config_tc.clock_source = GCLK_GENERATOR_1;
	#endif
	config_tc.clock_prescaler = TC_CLOCK_PRESCALER_DIV1024;
	config_tc.counter_8_bit.period = 100;
	config_tc.counter_8_bit.compare_capture_channel[0] = 50;
	config_tc.counter_8_bit.compare_capture_channel[1] = 54;
	//! [setup_change_config]

	//! [setup_set_config]
	tc_init(&tc_instance, CONF_TC_MODULE, &config_tc);
	//! [setup_set_config]

	//! [setup_enable]
	tc_enable(&tc_instance);
	//! [setup_enable]
}

void configure_tc_callbacks(void)
{
	//! [setup_register_callback]
	tc_register_callback(&tc_instance, tc_callback_to_toggle_led,
			TC_CALLBACK_OVERFLOW);
	tc_register_callback(&tc_instance, tc_callback_to_toggle_led,
			TC_CALLBACK_CC_CHANNEL0);
	tc_register_callback(&tc_instance, tc_callback_to_toggle_led,
			TC_CALLBACK_CC_CHANNEL1);
	//! [setup_register_callback]

	//! [setup_enable_callback]
	tc_enable_callback(&tc_instance, TC_CALLBACK_OVERFLOW);
	tc_enable_callback(&tc_instance, TC_CALLBACK_CC_CHANNEL0);
	tc_enable_callback(&tc_instance, TC_CALLBACK_CC_CHANNEL1);
	//! [setup_enable_callback]
}
//! [setup]

int main(void)
{
	system_init();

//! [setup_init]
	configure_tc();
	configure_tc_callbacks();
//! [setup_init]

//! [main]
	//! [enable_global_interrupts]
	system_interrupt_enable_global();
	//! [enable_global_interrupts]

	//! [main_loop]
	while (true) {
	}
	//! [main_loop]
//! [main]
}
