/**
 * \file
 *
 * \brief SAM RTC Basic Usage Example
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

void configure_rtc_count(void);

//! [rtc_module_instance]
struct rtc_module rtc_instance;
//! [rtc_module_instance]

//! [initiate]
void configure_rtc_count(void)
{
//! [set_conf]
	struct rtc_count_config config_rtc_count;
//! [set_conf]

//! [get_default]
	rtc_count_get_config_defaults(&config_rtc_count);
//! [get_default]

//! [set_config]
	config_rtc_count.prescaler           = RTC_COUNT_PRESCALER_DIV_1;
	config_rtc_count.mode                = RTC_COUNT_MODE_16BIT;
#ifdef FEATURE_RTC_CONTINUOUSLY_UPDATED
	config_rtc_count.continuously_update = true;
#endif
	config_rtc_count.compare_values[0]   = 1000;
//! [set_config]
//! [init_rtc]
	rtc_count_init(&rtc_instance, RTC, &config_rtc_count);
//! [init_rtc]

//! [enable]
	rtc_count_enable(&rtc_instance);
//! [enable]
}
//! [initiate]

int main(void)
{
	/* Initialize system. Must configure conf_clocks.h first. */
//! [system]
	system_init();
//! [system]

//! [add_main]
	configure_rtc_count();
//! [add_main]

//! [implementation_code]
//! [period]
	rtc_count_set_period(&rtc_instance, 2000);
//! [period]

//! [main_loop]
	while (true) {
//! [main_loop]
//! [check_match]
		if (rtc_count_is_compare_match(&rtc_instance, RTC_COUNT_COMPARE_0)) {
//! [check_match]
//! [compare_match_action]
			/* Do something on RTC count match here */
			port_pin_toggle_output_level(LED_0_PIN);
//! [compare_match_action]

//! [clear_compare_match]
			rtc_count_clear_compare_match(&rtc_instance, RTC_COUNT_COMPARE_0);
//! [clear_compare_match]
		}
	}
//! [implementation_code]

}
