/**
 * \file
 *
 * \brief SAM OPAMP Driver Quick Start
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

void configure_non_inverting_pga_opamp0(void);

//! [setup]
void configure_non_inverting_pga_opamp0(void)
{
	/** Creates a new configuration structure for the OPAMP0. */
	//! [setup_1]
	struct opamp0_config conf;
	//! [setup_1]

	/** Initializes OPAMP module. */
	//! [setup_2]
	opamp_module_init();
	//! [setup_2]

	/** Settings and fill with the default settings. */
	//! [setup_3]
	opamp0_get_config_defaults(&conf);
	//! [setup_3]

	/* Set the the OPAMP0 as "Non-Inverting PGA" mode. */
	//! [setup_4]
	conf.negative_input = OPAMP0_NEG_MUX_TAP0;
	conf.positive_input = OPAMP0_POS_MUX_PIN0;
	conf.r1_connection = OPAMP0_RES1_MUX_GND;
	conf.config_common.r1_enable = true;
	conf.config_common.r2_out = true;
	//! [setup_4]

	/* Set up OA0POS pin and OA0OUT pin. */
	//! [setup_5]
	struct system_pinmux_config opamp0_pos_pin_conf;
	system_pinmux_get_config_defaults(&opamp0_pos_pin_conf);
	opamp0_pos_pin_conf.direction    = SYSTEM_PINMUX_PIN_DIR_INPUT;
	opamp0_pos_pin_conf.mux_position = MUX_PA06B_OPAMP_OAPOS0;
	system_pinmux_pin_set_config(PIN_PA06B_OPAMP_OAPOS0, &opamp0_pos_pin_conf);
	struct system_pinmux_config opamp0_out_pin_conf;
	system_pinmux_get_config_defaults(&opamp0_out_pin_conf);
	opamp0_out_pin_conf.direction    = SYSTEM_PINMUX_PIN_DIR_OUTPUT;
	opamp0_out_pin_conf.mux_position = MUX_PA07B_OPAMP_OAOUT0;
	system_pinmux_pin_set_config(PIN_PA07B_OPAMP_OAOUT0, &opamp0_out_pin_conf);
	//! [setup_5]

	/** Initialize and enable the OPAMP0 with the user settings. */
	//! [setup_6]
	opamp0_set_config(&conf);
	//! [setup_6]
	//! [setup_7]
	opamp_enable(OPAMP_0);
	//! [setup_7]

	/* Wait for the output ready. */
	//! [setup_8]
	while(!opamp_is_ready(OPAMP_0));
	//! [setup_8]
}
//! [setup]

int main(void)
{
	system_init();

	//! [setup_init]
	configure_non_inverting_pga_opamp0();
	//! [setup_init]

	//! [main]
	while (true) {
		/* Do nothing */
	}
	//! [main]
}
