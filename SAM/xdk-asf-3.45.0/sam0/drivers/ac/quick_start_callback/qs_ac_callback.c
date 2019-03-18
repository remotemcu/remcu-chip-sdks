/**
 * \file
 *
 * \brief SAM Analog Comparator Driver Quick Start
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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

//! [callback_3]
bool volatile callback_status = false;
//! [callback_3]

void configure_ac(void);
void configure_ac_channel(void);
void configure_ac_callback(void);
void callback_function_ac(struct ac_module *const module_inst);

//! [setup]
/* AC module software instance (must not go out of scope while in use). */
//! [setup_1]
static struct ac_module ac_instance;
//! [setup_1]

/* Comparator channel that will be used. */
//! [setup_2]
#define AC_COMPARATOR_CHANNEL   AC_CHAN_CHANNEL_0
//! [setup_2]

//! [setup_3]
void configure_ac(void)
{
//! [setup_3]
	/* Create a new configuration structure for the Analog Comparator settings
	 * and fill with the default module settings. */
	//! [setup_4]
	struct ac_config config_ac;
	//! [setup_4]
	//! [setup_5]
	ac_get_config_defaults(&config_ac);
	//! [setup_5]

	/* Alter any Analog Comparator configuration settings here if required. */

	/* Initialize and enable the Analog Comparator with the user settings. */
	//! [setup_6]
	ac_init(&ac_instance, AC, &config_ac);
	//! [setup_6]
}

//! [setup_7]
void configure_ac_channel(void)
{
//! [setup_7]
	/* Create a new configuration structure for the Analog Comparator channel
	 * settings and fill with the default module channel settings. */
	//! [setup_8]
	struct ac_chan_config config_ac_chan;
	//! [setup_8]
	//! [setup_9]
	ac_chan_get_config_defaults(&config_ac_chan);
	//! [setup_9]

	/* Set the Analog Comparator channel configuration settings. */
	//! [setup_10]
	config_ac_chan.sample_mode         = AC_CHAN_MODE_SINGLE_SHOT;
	#if (SAMR30E)
	config_ac_chan.positive_input   = AC_CHAN_POS_MUX_PIN2;
	#else
	config_ac_chan.positive_input   = AC_CHAN_POS_MUX_PIN0;
	#endif
	config_ac_chan.negative_input      = AC_CHAN_NEG_MUX_SCALED_VCC;
	config_ac_chan.vcc_scale_factor    = 32;
	config_ac_chan.interrupt_selection = AC_CHAN_INTERRUPT_SELECTION_END_OF_COMPARE;
	//! [setup_10]

	/* Set up a pin as an AC channel input. */
	//! [setup_11]
	struct system_pinmux_config ac0_pin_conf;
	system_pinmux_get_config_defaults(&ac0_pin_conf);
	ac0_pin_conf.direction    = SYSTEM_PINMUX_PIN_DIR_INPUT;
	ac0_pin_conf.mux_position = CONF_AC_MUX;
	system_pinmux_pin_set_config(CONF_AC_PIN, &ac0_pin_conf);
	//! [setup_11]

	/* Initialize and enable the Analog Comparator channel with the user
	 * settings. */
	//! [setup_12]
	ac_chan_set_config(&ac_instance, AC_COMPARATOR_CHANNEL, &config_ac_chan);
	//! [setup_12]
	//! [setup_13]
	ac_chan_enable(&ac_instance, AC_COMPARATOR_CHANNEL);
	//! [setup_13]
}

//! [callback_1]
void callback_function_ac(struct ac_module *const module_inst)
{
	//! [callback_2]
	callback_status = true;
	//! [callback_2]
}
//! [callback_1]

//! [setup_14]
void configure_ac_callback(void)
{
	//! [setup_15]
	ac_register_callback(&ac_instance, callback_function_ac, AC_CALLBACK_COMPARATOR_0);
	//! [setup_15]
	//! [setup_16]
	ac_enable_callback(&ac_instance, AC_CALLBACK_COMPARATOR_0);
	//! [setup_16]
}
//! [setup_14]

//! [setup]
int main(void)
{
	//! [setup_init]
	system_init();
	configure_ac();
	configure_ac_channel();
	configure_ac_callback();

	//! [setup_17]
	ac_enable(&ac_instance);
	//! [setup_17]
	//! [setup_init]

	//! [main]
	//! [main_1]
	ac_chan_trigger_single_shot(&ac_instance, AC_COMPARATOR_CHANNEL);
	//! [main_1]

	//! [main_2]
	uint8_t last_comparison = AC_CHAN_STATUS_UNKNOWN;
	//! [main_2]
	port_pin_set_output_level(LED_0_PIN, true);
	//! [main_3]
	while (true) {
	//! [main_3]
	//! [main_4]
		if (callback_status == true) {
	//! [main_4]
			//! [main_5]
			do
			{
				last_comparison = ac_chan_get_status(&ac_instance,
						AC_COMPARATOR_CHANNEL);
			} while (last_comparison & AC_CHAN_STATUS_UNKNOWN);
			//! [main_5]
			//! [main_6]
			port_pin_set_output_level(LED_0_PIN,
					(last_comparison & AC_CHAN_STATUS_NEG_ABOVE_POS));
			//! [main_6]
			//! [main_7]
			callback_status = false;
			//! [main_7]
			//! [main_8]
			ac_chan_trigger_single_shot(&ac_instance, AC_COMPARATOR_CHANNEL);
			//! [main_8]
		}
	}
	//! [main]
}
