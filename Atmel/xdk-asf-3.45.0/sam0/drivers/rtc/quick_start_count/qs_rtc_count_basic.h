/**
 * \file
 *
 * \brief SAM RTC Count Quick Start
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
 * \page asfdoc_sam0_rtc_count_basic_use_case Quick Start Guide for RTC (COUNT) - Basic
 * In this use case, the RTC is set up in count mode. The example configures the
 * RTC in 16-bit mode, with continuous updates to the COUNT register, together
 * with a set compare register value. Every 2000ms a LED on the board is
 * toggled.
 *
 * \section asfdoc_sam0_rtc_count_basic_use_case_prereq Prerequisites
 * The Generic Clock Generator for the RTC should be configured and enabled; if
 * you are using the System Clock driver, this may be done via \c conf_clocks.h.
 *
 * \subsection asfdoc_sam0_rtc_count_basic_use_case_setup_clocks Clocks and Oscillators
 * The \c conf_clock.h file needs to be changed with the different values to
 * configure the clocks and oscillators for the module according to the used device.
 *
 * For example, the following oscillator settings are needed for SAMD21:
 * \snippet conf_clocks.h oscillator_settings
 * The following generic clock settings are needed for SAMD21:
 * \snippet conf_clocks.h gclk_settings
 *
 * \section asfdoc_sam0_rtc_count_basic_use_case_setup Setup
 *
 * \subsection asfdoc_sam0_rtc_count_basic_use_case_init_code Initialization Code
 * Create an rtc_module struct and add to the main application source file,
 * outside of any functions:
 * \snippet qs_rtc_count_basic.c rtc_module_instance
 *
 * Copy-paste the following setup code to your applications \c main():
 * \snippet qs_rtc_count_basic.c initiate
 *
 * \subsection asfdoc_sam0_rtc_count_basic_use_case_main_code Add to Main
 * Add the following to your \c main().
 * \snippet qs_rtc_count_basic.c add_main
 *
 * \subsection rtc_count_basic_use_workflow Workflow
 * -# Create an RTC configuration structure to hold the desired RTC driver
 *    settings.
 *    \snippet qs_rtc_count_basic.c set_conf
 * -# Fill the configuration structure with the default driver configuration.
 *    \snippet qs_rtc_count_basic.c get_default
 *    \note This should always be performed before using the configuration
 *          struct to ensure that all values are initialized to known default
 *          settings.
 *
 * -# Alter the RTC driver configuration to run in 16-bit counting mode, with
 *    continuous counter register updates.
 *    \snippet qs_rtc_count_basic.c set_config
 * -# Initialize the RTC module.
 *    \snippet qs_rtc_count_basic.c init_rtc
 * -# Enable the RTC module, so that it may begin counting.
 *    \snippet qs_rtc_count_basic.c enable
 *
 * \section asfdoc_sam0_rtc_count_basic_use_case_implement Implementation
 * Code used to implement the initialized module.
 *
 * \subsection asfdoc_sam0_rtc_count_basic_use_case_imp_code Code
 * Add after initialization in main().
 * \snippet qs_rtc_count_basic.c implementation_code
 *
 * \subsection asfdoc_sam0_rtc_count_basic_use_case_imp_workflow Workflow
 * -# Set RTC period to 2000ms (two seconds) so that it will overflow and reset
 *    back to zero every two seconds.
 *    \snippet qs_rtc_count_basic.c period
 * -# Enter an infinite loop to poll the RTC driver to check when a comparison
 *    match occurs.
 *    \snippet qs_rtc_count_basic.c main_loop
 * -# Check if the RTC driver has found a match on compare channel 0 against the
 *    current RTC count value.
 *    \snippet qs_rtc_count_basic.c check_match
 * -# Once a compare match occurs, perform the desired user action.
 *    \snippet qs_rtc_count_basic.c compare_match_action
 * -# Clear the compare match, so that future matches may occur.
 *    \snippet qs_rtc_count_basic.c clear_compare_match
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
