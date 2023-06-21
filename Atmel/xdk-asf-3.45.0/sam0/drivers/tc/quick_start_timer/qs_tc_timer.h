/**
 * \file
 *
 * \brief SAM TC - Timer Counter Driver Quick Start
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

/**
 * \page asfdoc_sam0_tc_timer_use_case Quick Start Guide for TC - Timer
 *
 * In this use case, the TC will be used as a timer to generate overflow and
 * compare match callbacks. In the callbacks the on-board LED is toggled.
 *
 * The TC module will be set up as follows:
 *
 * - GCLK generator 1 (GCLK 32K) clock source
 * - 16-bit resolution on the counter
 * - Prescaler is divided by 64
 * - GCLK reload action
 * - Count upward
 * - Don't run in standby
 * - No waveform outputs
 * - No capture enabled
 * - Don't perform one-shot operations
 * - No event input enabled
 * - No event action
 * - No event generation enabled
 * - Counter starts on 0
 * - Counter top set to 2000 (about 4s) and generate overflow callback
 * - Channel 0 is set to compare and match value 900 and generate callback
 * - Channel 1 is set to compare and match value 930 and generate callback
 *
 * \section asfdoc_sam0_tc_timer_use_case_setup Quick Start
 *
 * \subsection asfdoc_sam0_tc_timer_use_case_prereq Prerequisites
 * For this use case, XOSC32K should be enabled and available through GCLK
 * generator 1 clock source selection. Within Atmel Software Framework (ASF)
 * it can be done through modifying <i>conf_clocks.h</i>.
 * See \ref asfdoc_sam0_system_clock_group "System Clock Management Driver" for
 * more details about clock configuration.
 *
 * \subsection asfdoc_sam0_tc_timer_use_case_setup_code Code
 *
 * Add to the main application source file, before any functions, according to
 * the kit used:
 * - SAM D20 Xplained Pro.
 *   \snippet samd20_xplained_pro/conf_qs_tc_timer.h definition_tc
 * - SAM D21 Xplained Pro.
 *   \snippet samd21_xplained_pro/conf_qs_tc_timer.h definition_tc
 * - SAM R21 Xplained Pro.
 *   \snippet samr21_xplained_pro/conf_qs_tc_timer.h definition_tc
 * - SAM D11 Xplained Pro.
 *   \snippet samd11_xplained_pro/conf_qs_tc_timer.h definition_tc
 * - SAM L21 Xplained Pro.
 *   \snippet saml21_xplained_pro/conf_qs_tc_timer.h definition_tc
 * - SAM L22 Xplained Pro.
 *   \snippet saml22_xplained_pro/conf_qs_tc_timer.h definition_tc
 * - SAM DA1 Xplained Pro.
 *   \snippet samda1_xplained_pro/conf_qs_tc_timer.h definition_tc
 * - SAM HA1G16A Xplained Pro.
 *   \snippet samda1_xplained_pro/conf_qs_tc_timer.h definition_tc
 * - SAM C21 Xplained Pro.
 *   \snippet samc21_xplained_pro/conf_qs_tc_timer.h definition_tc
 *
 * Add to the main application source file, outside of any functions:
 * \snippet qs_tc_timer.c module_inst
 *
 * Copy-paste the following callback function code to your user application:
 * \snippet qs_tc_timer.c callback_funcs
 *
 * Copy-paste the following setup code to your user application:
 * \snippet qs_tc_timer.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_tc_timer.c setup_init
 *
 * \subsection asfdoc_sam0_tc_timer_use_case_setup_flow Workflow
 * -# Create a module software instance structure for the TC module to store
 *    the TC driver state while it is in use.
 *    \snippet qs_tc_timer.c module_inst
 *    \note This should never go out of scope as long as the module is in use.
 *          In most cases, this should be global.
 *
 * -# Configure the TC module.
 *  -# Create a TC module configuration struct, which can be filled out to
 *     adjust the configuration of a physical TC peripheral.
 *     \snippet qs_tc_timer.c setup_config
 *  -# Initialize the TC configuration struct with the module's default values.
 *     \snippet qs_tc_timer.c setup_config_defaults
 *     \note This should always be performed before using the configuration
 *           struct to ensure that all values are initialized to known default
 *           settings.
 *
 *  -# Alter the TC settings to configure the GCLK source, prescaler, period,
 *     and compare channel values.
 *     \snippet qs_tc_timer.c setup_change_config
 *  -# Configure the TC module with the desired settings.
 *     \snippet qs_tc_timer.c setup_set_config
 *  -# Enable the TC module to start the timer.
 *     \snippet qs_tc_timer.c setup_enable
 * -# Configure the TC callbacks.
 *  -# Register the Overflow and Compare Channel Match callback functions with
 *     the driver.
 *     \snippet qs_tc_timer.c setup_register_callback
 *  -# Enable the Overflow and Compare Channel Match callbacks so that it will
 *     be called by the driver when appropriate.
 *     \snippet qs_tc_timer.c setup_enable_callback
 *
 *
 * \section asfdoc_sam0_tc_timer_use_case_main Use Case
 *
 * \subsection asfdoc_sam0_tc_timer_use_case_main_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_tc_timer.c main
 *
 * \subsection asfdoc_sam0_tc_timer_use_case_main_flow Workflow
 * -# Enter an infinite loop while the timer is running.
 *    \snippet qs_tc_timer.c main_loop
 */


#include <asf.h>
#include <conf_clocks.h>
