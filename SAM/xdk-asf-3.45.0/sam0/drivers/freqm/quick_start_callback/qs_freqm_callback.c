/**
 * \file
 *
 * \brief SAM Frequency Meter Driver Quick Start
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

//! [setup]

//! [callback_2]
bool volatile freqm_read_done = false;
//! [callback_2]

void configure_freqm(void);
void configure_freqm_callback(void);
void freqm_complete_callback(void);

/* FREQM module software instance (must not go out of scope while in use) */
//! [setup_1]
static struct freqm_module freqm_instance;
//! [setup_1]

//! [setup_2]
void configure_freqm(void)
//! [setup_2]
{
	/* Create a new configuration structure for the FREQM settings
	 * and fill with the default module settings. */
	//! [setup_2_1]
	struct freqm_config config_freqm;
	//! [setup_2_1]
	//! [setup_2_2]
	freqm_get_config_defaults(&config_freqm);
	config_freqm.ref_clock_circles = 255;
	//! [setup_2_2]

	/* Alter any FREQM configuration settings here if required */

	/* Initialize FREQM with the user settings */
	//! [setup_2_3]
	freqm_init(&freqm_instance, FREQM, &config_freqm);
	//! [setup_2_3]
}

//! [callback_1]
void freqm_complete_callback(void)
{
	//! [callback_1_1]
	freqm_read_done = true;
	//! [callback_1_1]
}
//! [callback_1]

//! [setup_3]
void configure_freqm_callback(void)
{
	//! [setup_3_1]
	freqm_register_callback(&freqm_instance, freqm_complete_callback,
			FREQM_CALLBACK_MEASURE_DONE);
	//! [setup_3_1]
	//! [setup_3_2]
	freqm_enable_callback(&freqm_instance, FREQM_CALLBACK_MEASURE_DONE);
	//! [setup_3_2]
}
//! [setup_3]
//! [setup]

int main(void)
{
	//! [setup_init]
	system_init();
	configure_freqm();
	configure_freqm_callback();

	//! [setup_init_1]
	freqm_enable(&freqm_instance);
	//! [setup_init_1]
	//! [setup_init]

	//! [main]
	uint32_t measure_result;
	enum freqm_status status;
	//! [main_1]
	freqm_start_measure(&freqm_instance);
	//! [main_1]

	//! [main_2]
	while (!freqm_read_done) {
	}
	status = freqm_get_result_value(&freqm_instance, &measure_result);
	//! [main_2]
	switch(status) {
	//! [main_3]
		case FREQM_STATUS_MEASURE_DONE:
			LED_On(LED_0_PIN);
			while (true) {
			}
	//! [main_3]
	//! [main_4]
		case FREQM_STATUS_CNT_OVERFLOW:
			freqm_clear_overflow(&freqm_instance);
			while (true) {
				LED_Toggle(LED_0_PIN);
				volatile uint32_t delay = 50000;
				while(delay--) {
				}
			}
	//! [main_4]
		default:
			Assert(false);
			break;
	}
	//! [main]
}
