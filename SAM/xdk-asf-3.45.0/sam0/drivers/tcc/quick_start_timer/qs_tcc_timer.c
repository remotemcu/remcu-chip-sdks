/**
 * \file
 *
 * \brief SAM TCC - Timer Counter for Control Applications Driver Quick Start
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

static void configure_tcc(void);
static void configure_tcc_callbacks(void);
static void tcc_callback_to_toggle_led(
		struct tcc_module *const module_inst);


//! [module_inst]
struct tcc_module tcc_instance;
//! [module_inst]

//! [callback_funcs]
static void tcc_callback_to_toggle_led(
		struct tcc_module *const module_inst)
{
	port_pin_toggle_output_level(LED0_PIN);
}
//! [callback_funcs]

//! [setup]
static void configure_tcc(void)
{
	//! [setup_config]
	struct tcc_config config_tcc;
	//! [setup_config]
	//! [setup_config_defaults]
	tcc_get_config_defaults(&config_tcc, TCC0);
	//! [setup_config_defaults]

	//! [setup_change_config]
	#if (SAMR30E)
	config_tcc.counter.clock_source = GCLK_GENERATOR_0;
	#else
	config_tcc.counter.clock_source = GCLK_GENERATOR_1;
	#endif
	config_tcc.counter.clock_prescaler = TCC_CLOCK_PRESCALER_DIV64;
	config_tcc.counter.period =   2000;
	config_tcc.compare.match[0] =  900;
	config_tcc.compare.match[1] =  930;
	config_tcc.compare.match[2] = 1100;
	config_tcc.compare.match[3] = 1250;
	//! [setup_change_config]

	//! [setup_set_config]
	tcc_init(&tcc_instance, TCC0, &config_tcc);
	//! [setup_set_config]

	//! [setup_enable]
	tcc_enable(&tcc_instance);
	//! [setup_enable]
}

static void configure_tcc_callbacks(void)
{
	//! [setup_register_callback]
	tcc_register_callback(&tcc_instance, tcc_callback_to_toggle_led,
			TCC_CALLBACK_OVERFLOW);
	tcc_register_callback(&tcc_instance, tcc_callback_to_toggle_led,
			TCC_CALLBACK_CHANNEL_0);
	tcc_register_callback(&tcc_instance, tcc_callback_to_toggle_led,
			TCC_CALLBACK_CHANNEL_1);
	tcc_register_callback(&tcc_instance, tcc_callback_to_toggle_led,
			TCC_CALLBACK_CHANNEL_2);
	tcc_register_callback(&tcc_instance, tcc_callback_to_toggle_led,
			TCC_CALLBACK_CHANNEL_3);
	//! [setup_register_callback]

	//! [setup_enable_callback]
	tcc_enable_callback(&tcc_instance, TCC_CALLBACK_OVERFLOW);
	tcc_enable_callback(&tcc_instance, TCC_CALLBACK_CHANNEL_0);
	tcc_enable_callback(&tcc_instance, TCC_CALLBACK_CHANNEL_1);
	tcc_enable_callback(&tcc_instance, TCC_CALLBACK_CHANNEL_2);
	tcc_enable_callback(&tcc_instance, TCC_CALLBACK_CHANNEL_3);
	//! [setup_enable_callback]
}
//! [setup]

int main(void)
{
	system_init();

//! [setup_init]
	configure_tcc();
	configure_tcc_callbacks();
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
