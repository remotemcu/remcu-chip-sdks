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

void configure_rtc_calendar(void);

//! [rtc_module_instance]
struct rtc_module rtc_instance;
//! [rtc_module_instance]

//! [initiate]
void configure_rtc_calendar(void)
{
	/* Initialize RTC in calendar mode. */
//! [set_conf]
	struct rtc_calendar_config config_rtc_calendar;
//! [set_conf]
//! [get_default]
	rtc_calendar_get_config_defaults(&config_rtc_calendar);
//! [get_default]

//! [time_struct]
	struct rtc_calendar_time alarm;
	rtc_calendar_get_time_defaults(&alarm);
	alarm.year   = 2013;
	alarm.month  = 1;
	alarm.day    = 1;
	alarm.hour   = 0;
	alarm.minute = 0;
	alarm.second = 4;
//! [time_struct]

//! [set_config]
	config_rtc_calendar.clock_24h     = true;
	config_rtc_calendar.alarm[0].time = alarm;
	config_rtc_calendar.alarm[0].mask = RTC_CALENDAR_ALARM_MASK_YEAR;
//! [set_config]

//! [init_rtc]
	rtc_calendar_init(&rtc_instance, RTC, &config_rtc_calendar);
//! [init_rtc]

//! [enable]
	rtc_calendar_enable(&rtc_instance);
//! [enable]
}
//! [initiate]

int main(void)
{
//! [add_main]
	system_init();

	struct rtc_calendar_time time;
	time.year   = 2012;
	time.month  = 12;
	time.day    = 31;
	time.hour   = 23;
	time.minute = 59;
	time.second = 59;

	configure_rtc_calendar();

	/* Set current time. */
	rtc_calendar_set_time(&rtc_instance, &time);

	rtc_calendar_swap_time_mode(&rtc_instance);
//! [add_main]

//! [main_imp]
//! [main_loop]
	while (true) {
//! [main_loop]
//! [check_alarm_match]
		if (rtc_calendar_is_alarm_match(&rtc_instance, RTC_CALENDAR_ALARM_0)) {
//! [check_alarm_match]
//! [alarm_match_action]
			/* Do something on RTC alarm match here */
			port_pin_toggle_output_level(LED_0_PIN);
//! [alarm_match_action]

//! [clear_alarm_match]
			rtc_calendar_clear_alarm_match(&rtc_instance, RTC_CALENDAR_ALARM_0);
//! [clear_alarm_match]
		}
	}
//! [main_imp]
}
