/**
 * \file
 *
 * \brief SAM RTC Calendar Quick Start
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

/**
 * \page asfdoc_sam0_rtc_calendar_basic_use_case Quick Start Guide for RTC (CAL) - Basic
 * In this use case, the RTC is set up in calendar mode. The time is set and
 * also an alarm is set to show a general use of the RTC in calendar mode. Also
 * the clock is swapped from 24h to 12h mode after initialization. The board LED
 * will be toggled once the current time matches the set time.
 *
 * \section asfdoc_sam0_rtc_calendar_basic_use_case_prereq Prerequisites
 * The Generic Clock Generator for the RTC should be configured and enabled; if
 * you are using the System Clock driver, this may be done via \c conf_clocks.h.
 *
 * \subsection asfdoc_sam0_rtc_calendar_basic_use_case_setup_clocks Clocks and Oscillators
 * The \c conf_clock.h file needs to be changed with the different values to
 * configure the clocks and oscillators for the module according to the used device.
 *
 * For example, the following oscillator settings are needed for SAMD21:
 * \snippet conf_clocks.h oscillator_settings
 * The following generic clock settings are needed for SAMD21:
 * \snippet conf_clocks.h gclk_settings
 *
 * \section asfdoc_sam0_rtc_calendar_basic_use_case_setup Setup
 *
 * \subsection asfdoc_sam0_rtc_calendar_basic_use_case_init_code Initialization Code
 * Create an rtc_module struct and add to the main application source file,
 * outside of any functions:
 * \snippet qs_rtc_calendar_basic.c rtc_module_instance
 *
 * Copy-paste the following setup code to your application:
 * \snippet qs_rtc_calendar_basic.c initiate
 *
 * \subsection asfdoc_sam0_rtc_calendar_basic_use_case_main_code Add to Main
 * Add the following to \c main().
 * \snippet qs_rtc_calendar_basic.c add_main
 *
 * \subsection asfdoc_sam0_rtc_calendar_basic_use_case_cal_basic_use_workflow Workflow
 * -# Make configuration structure.
 *    \snippet qs_rtc_calendar_basic.c set_conf
 * -# Fill the configuration structure with the default driver configuration.
 *    \snippet qs_rtc_calendar_basic.c get_default
 *    \note This should always be performed before using the configuration
 *          struct to ensure that all values are initialized to known default
 *          settings.
 *
 * -# Make time structure for alarm and set with default and desired values.
 *    \snippet qs_rtc_calendar_basic.c time_struct
 * -# Change configurations as desired.
 *    \snippet qs_rtc_calendar_basic.c set_config
 * -# Initialize module.
 *    \snippet qs_rtc_calendar_basic.c init_rtc
 * -# Enable module.
 *    \snippet qs_rtc_calendar_basic.c enable
 *
 * \section asfdoc_sam0_rtc_calendar_basic_use_case_count_basic_implement Implementation
 * Add the following to \c main().
 * \snippet qs_rtc_calendar_basic.c main_imp
 *
 * \subsection asfdoc_sam0_rtc_calendar_basic_use_case_count_basic_workflow Workflow
 * -# Start an infinite loop, to continuously poll for a RTC alarm match.
 *    \snippet qs_rtc_calendar_basic.c main_loop
 * -# Check to see if a RTC alarm match has occurred.
 *    \snippet qs_rtc_calendar_basic.c check_alarm_match
 * -# Once an alarm match occurs, perform the desired user action.
 *    \snippet qs_rtc_calendar_basic.c alarm_match_action
 * -# Clear the alarm match, so that future alarms may occur.
 *    \snippet qs_rtc_calendar_basic.c clear_alarm_match
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
