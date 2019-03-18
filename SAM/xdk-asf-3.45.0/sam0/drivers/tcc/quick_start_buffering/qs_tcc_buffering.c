/**
 * \file
 *
 * \brief SAM Timer/Counter Driver for Control Applications Double Buffering Quickstart
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
#include <conf_quick_start_buffering.h>

#if CONF_PWM_CHANNEL > 3
#  error Only the four lowest channels support circular option, please check CONF_PWM_CHANNEL
#endif

static void configure_tcc(void);

//! [module_inst]
struct tcc_module tcc_instance;
//! [module_inst]

//! [setup]
static void configure_tcc(void)
{
	//! [setup_config]
	struct tcc_config config_tcc;
	//! [setup_config]
	//! [setup_config_defaults]
	tcc_get_config_defaults(&config_tcc, CONF_PWM_MODULE);
	//! [setup_config_defaults]

	//! [setup_change_config]
	config_tcc.counter.clock_prescaler = TCC_CLOCK_PRESCALER_DIV1024;
	config_tcc.counter.period = 8000;
	config_tcc.compare.wave_generation = TCC_WAVE_GENERATION_SINGLE_SLOPE_PWM;
	config_tcc.compare.match[CONF_PWM_CHANNEL] = (8000 / 4);
	//! [setup_change_config]

	//! [setup_change_config_pwm]
	config_tcc.pins.enable_wave_out_pin[CONF_PWM_OUTPUT] = true;
	config_tcc.pins.wave_out_pin[CONF_PWM_OUTPUT]        = CONF_PWM_OUT_PIN;
	config_tcc.pins.wave_out_pin_mux[CONF_PWM_OUTPUT]    = CONF_PWM_OUT_MUX;
	//! [setup_change_config_pwm]

	//! [setup_set_config]
	tcc_init(&tcc_instance, CONF_PWM_MODULE, &config_tcc);
	//! [setup_set_config]

	//! [setup_set_buffering]
	tcc_set_compare_value(&tcc_instance,
			(enum tcc_match_capture_channel)CONF_PWM_CHANNEL, 8000*3/4);
	tcc_enable_circular_buffer_compare(&tcc_instance,
			(enum tcc_match_capture_channel)CONF_PWM_CHANNEL);
	//! [setup_set_buffering]

	//! [setup_enable]
	tcc_enable(&tcc_instance);
	//! [setup_enable]
}
//! [setup]

int main(void)
{
	system_init();

	//! [setup_init]
	configure_tcc();
	//! [setup_init]

//! [main]
	//! [main_loop]
	while (true) {
		/* Infinite loop */
	}
	//! [main_loop]
//! [main]
}
