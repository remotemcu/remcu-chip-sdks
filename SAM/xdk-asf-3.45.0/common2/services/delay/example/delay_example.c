/**
 * \file
 *
 * \mainpage
 *
 * \section title Delay service example
 *
 * \section file File(s)
 * - \ref delay_example.c
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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
	delay_init();

	struct port_config pin;
	port_get_config_defaults(&pin);
	pin.direction = PORT_PIN_DIR_OUTPUT;

	port_pin_set_config(LED0_PIN, &pin);
	port_pin_set_output_level(LED0_PIN, LED0_INACTIVE);

	while (true) {
		for (int i = 0; i < 5; i++) {
			port_pin_toggle_output_level(LED0_PIN);
			delay_s(1);
		}

		for (int i = 0; i < 50; i++) {
			port_pin_toggle_output_level(LED0_PIN);
			delay_ms(100);
		}

		for (int i = 0; i < 5000; i++) {
			port_pin_toggle_output_level(LED0_PIN);
			delay_cycles(100);
		}
	}
}
