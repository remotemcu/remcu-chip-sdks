/**
 * \file
 *
 * \brief SAM GPIO PINMUX Driver Quick Start
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

int main(void)
{
	system_init();

	//! [setup]
	//! [pinmux_config]
	struct system_pinmux_config config_pinmux;
	//! [pinmux_config]
	//! [pinmux_config_defaults]
	system_pinmux_get_config_defaults(&config_pinmux);
	//! [pinmux_config_defaults]

	//! [pinmux_update_config_values]
	config_pinmux.mux_position = SYSTEM_PINMUX_GPIO;
	config_pinmux.direction    = SYSTEM_PINMUX_PIN_DIR_INPUT;
	config_pinmux.input_pull   = SYSTEM_PINMUX_PIN_PULL_UP;
	//! [pinmux_update_config_values]

	//! [pinmux_set_config]
	system_pinmux_pin_set_config(10, &config_pinmux);
	//! [pinmux_set_config]
	//! [setup]

	//! [main]
	//! [pinmux_change_input_sampling]
	system_pinmux_pin_set_input_sample_mode(10,
			SYSTEM_PINMUX_PIN_SAMPLE_ONDEMAND);
	//! [pinmux_change_input_sampling]

	while (true) {
		/* Infinite loop */
	}
	//! [main]
}
