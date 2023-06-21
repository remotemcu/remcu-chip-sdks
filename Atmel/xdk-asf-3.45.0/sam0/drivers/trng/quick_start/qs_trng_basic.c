/**
 * \file
 *
 * \brief SAM True Random Number Generator Driver Quick Start
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

void configure_trng(void);

//! [setup]
/* TRNG module software instance (must not go out of scope while in use) */
//! [setup_1]
static struct trng_module trng_instance;
//! [setup_1]

//! [setup_2]
void configure_trng(void)
//! [setup_2]
{
	/* Create a new configuration structure for the TRNG settings
	 * and fill with the default module settings. */
	//! [setup_2_1]
	struct trng_config config_trng;
	//! [setup_2_1]
	//! [setup_2_2]
	trng_get_config_defaults(&config_trng);
	//! [setup_2_2]

	/* Alter any TRNG configuration settings here if required */

	/* Initialize TRNG with the user settings */
	//! [setup_2_3]
	trng_init(&trng_instance, TRNG, &config_trng);
	//! [setup_2_3]
}
//! [setup]

int main(void)
{
	//! [setup_init]
	system_init();
	configure_trng();
	//! [setup_init_1]
	trng_enable(&trng_instance);
	//! [setup_init_1]
	//! [setup_init]

	//! [main]
	uint32_t random_result;

	//! [main_1]
	while (true) {
	//! [main_1]
		//! [main_2]
		while (trng_read(&trng_instance, &random_result) != STATUS_OK) {
		}
		//! [main_2]
		//! [main_3]
		port_pin_toggle_output_level(LED_0_PIN);
		/* Add a short delay to see LED toggle */
		volatile uint32_t delay = 50000;
		while(delay--) {
		}
		//! [main_3]
	}
	//! [main]
}

