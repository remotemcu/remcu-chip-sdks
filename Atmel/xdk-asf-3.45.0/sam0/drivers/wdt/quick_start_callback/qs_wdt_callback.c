/**
 * \file
 *
 * \brief SAM Watchdog Driver Callback Quick Start
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

void watchdog_early_warning_callback(void);
void configure_wdt(void);
void configure_wdt_callbacks(void);

//! [setup]
void watchdog_early_warning_callback(void)
{
	port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
}

void configure_wdt(void)
{
	/* Create a new configuration structure for the Watchdog settings and fill
	 * with the default module settings. */
	//! [setup_1]
	struct wdt_conf config_wdt;
	//! [setup_1]
	//! [setup_2]
	wdt_get_config_defaults(&config_wdt);
	//! [setup_2]

	/* Set the Watchdog configuration settings */
	//! [setup_3]
	config_wdt.always_on            = false;
#if !((SAML21) || (SAMC21) || (SAML22) || (SAMR30))
	config_wdt.clock_source         = GCLK_GENERATOR_4;
#endif
	config_wdt.timeout_period       = WDT_PERIOD_4096CLK;
	config_wdt.early_warning_period = WDT_PERIOD_2048CLK;
	//! [setup_3]

	/* Initialize and enable the Watchdog with the user settings */
	//! [setup_4]
	wdt_set_config(&config_wdt);
	//! [setup_4]
}

void configure_wdt_callbacks(void)
{
	//! [setup_5]
	wdt_register_callback(watchdog_early_warning_callback,
		WDT_CALLBACK_EARLY_WARNING);
	//! [setup_5]

	//! [setup_6]
	wdt_enable_callback(WDT_CALLBACK_EARLY_WARNING);
	//! [setup_6]
}
//! [setup]

int main(void)
{
	system_init();

	//! [setup_init]
	configure_wdt();
	configure_wdt_callbacks();
	//! [setup_init]

//! [main]
//! [main_1]
	port_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);
//! [main_1]

//! [main_2]
	system_interrupt_enable_global();
//! [main_2]

	//! [main_3]
	while (true) {
		/* Wait for callback */
	}
	//! [main_3]
//! [main]
}
