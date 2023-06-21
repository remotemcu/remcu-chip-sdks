/**
 * \file
 *
 * \brief SAM External Interrupt Driver Quick Start
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

void configure_extint_channel(void);

//! [setup]
void configure_extint_channel(void)
{
//! [setup_1]
	struct extint_chan_conf config_extint_chan;
//! [setup_1]
//! [setup_2]
	extint_chan_get_config_defaults(&config_extint_chan);
//! [setup_2]

//! [setup_3]
	config_extint_chan.gpio_pin           = BUTTON_0_EIC_PIN;
	config_extint_chan.gpio_pin_mux       = BUTTON_0_EIC_MUX;
	config_extint_chan.gpio_pin_pull      = EXTINT_PULL_UP;
	config_extint_chan.detection_criteria = EXTINT_DETECT_BOTH;
//! [setup_3]
//! [setup_4]
	extint_chan_set_config(BUTTON_0_EIC_LINE, &config_extint_chan);
//! [setup_4]
}
//! [setup]

int main(void)
{
	system_init();

	//! [setup_init]
	configure_extint_channel();
	//! [setup_init]

	//! [main]
	while (true) {
		//! [main_1]
		if (extint_chan_is_detected(BUTTON_0_EIC_LINE)) {
		//! [main_1]

		//! [main_2]
			// Do something in response to EXTINT edge detection
			bool button_pin_state = port_pin_get_input_level(BUTTON_0_PIN);
			port_pin_set_output_level(LED_0_PIN, button_pin_state);
		//! [main_2]

		//! [main_3]
			extint_chan_clear_detected(BUTTON_0_EIC_LINE);
		//! [main_3]
		}
	}
	//! [main]
}
