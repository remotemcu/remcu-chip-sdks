/**
 * \file
 *
 * \brief SAM GPIO Driver Quick Start for SAMB11
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

void configure_gpio_pins(void);

//! [setup]
void configure_gpio_pins(void)
{
//! [setup_1]
	struct gpio_config config_gpio_pin;
//! [setup_1]
//! [setup_2]
	gpio_get_config_defaults(&config_gpio_pin);
//! [setup_2]

//! [setup_3]
	config_gpio_pin.direction  = GPIO_PIN_DIR_INPUT;
	config_gpio_pin.input_pull = GPIO_PIN_PULL_UP;
//! [setup_3]
//! [setup_4]
	gpio_pin_set_config(BUTTON_0_PIN, &config_gpio_pin);
//! [setup_4]

//! [setup_5]
	config_gpio_pin.direction = GPIO_PIN_DIR_OUTPUT;
//! [setup_5]
//! [setup_6]
	gpio_pin_set_config(LED_0_PIN, &config_gpio_pin);
//! [setup_6]
}
//! [setup]

int main(void)
{
	system_clock_config(CLOCK_RESOURCE_XO_26_MHZ, CLOCK_FREQ_26_MHZ);

	//! [setup_init]
	configure_gpio_pins();
	//! [setup_init]

	//! [main]
	while (true) {
		//! [main_1]
		bool pin_state = gpio_pin_get_input_level(BUTTON_0_PIN);
		//! [main_1]

		//! [main_2]
		gpio_pin_set_output_level(LED_0_PIN, !pin_state);
		//! [main_2]
	}
	//! [main]
}
