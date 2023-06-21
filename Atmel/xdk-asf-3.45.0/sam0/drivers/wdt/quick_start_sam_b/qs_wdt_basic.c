/**
 * \file
 *
 * \brief SAM Watchdog Driver Quick Start for SAMB
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

//! [module_inst]
struct wdt_module wdt_instance;
//! [module_inst]

//! [setup]
static void watchdog_early_warning_callback(void)
{
	gpio_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
}

static void configure_gpio(void)
{
	struct gpio_config config_gpio;

	gpio_get_config_defaults(&config_gpio);
	
	gpio_pin_set_config(BUTTON_0_PIN, &config_gpio);

	config_gpio.direction  = GPIO_PIN_DIR_OUTPUT;
	config_gpio.input_pull = GPIO_PIN_PULL_NONE;
	gpio_pin_set_config(LED_0_PIN, &config_gpio);
}

static void configure_wdt(void)
{
	/* Create a new configuration structure for the Watchdog settings and fill
	 * with the default module settings. */
	//! [setup_1]
	struct wdt_config config_wdt;
	//! [setup_1]
	//! [setup_2]
	wdt_get_config_defaults(&config_wdt);
	//! [setup_2]
	//! [setup_3]
	config_wdt.load_value = CONF_WDT_LOAD_VALUE;
	config_wdt.enable_reset = true;
	//! [setup_3]

	/* Initialize and enable the Watchdog with the user settings */
	//! [setup_4]
	wdt_set_config(&wdt_instance, CONF_WDT_MODULE, &config_wdt);
	//! [setup_4]
}

static void configure_wdt_callback(void)
{
	//! [setup_5]
	wdt_register_callback(&wdt_instance, watchdog_early_warning_callback,
			WDT_CALLBACK_EARLY_WARNING);
	//! [setup_5]

	//! [setup_6]
	wdt_enable_callback(&wdt_instance, WDT_CALLBACK_EARLY_WARNING);
	//! [setup_6]
}
//! [setup]
//! [setup]

int main(void)
{
	uint32_t current_value;
	uint16_t i;
	uint32_t j;

	system_clock_config(CLOCK_RESOURCE_XO_26_MHZ, CLOCK_FREQ_26_MHZ);

	//! [setup_init]
	configure_gpio();
	for(i = 0; i < 5; i++) {
		gpio_pin_toggle_output_level(LED_0_PIN);
		for (j = 0; j < 1000000; j++) {
			/* Delay time */
		}
	}
	configure_wdt();
	configure_wdt_callback();
	//! [setup_init]

	//! [main]
	//! [main_1]
	gpio_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);
	//! [main_1]
	//! [main_2]
	while (true) {
	//! [main_2]

		//! [main_3]
		if (gpio_pin_get_input_level(BUTTON_0_PIN) == false) {
		//! [main_3]
		//! [main_4]
			wdt_get_current_count(&wdt_instance, &current_value);
		//! [main_4]
		//! [main_5]
			wdt_set_reload_count(&wdt_instance, CONF_WDT_LOAD_VALUE);
		//! [main_5]
		}
	}
	//! [main]
}
