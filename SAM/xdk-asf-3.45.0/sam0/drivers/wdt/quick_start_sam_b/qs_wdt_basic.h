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

/**
 * \page asfdoc_samb_wdt_basic_use_case Quick Start Guide for WDT - Basic
 *
 * In this use case, the Watchdog module is configured for:
 *   \li Load register value
 *   \li Enable reset output
 *   \li Open write access
 *
 *
 * \section asfdoc_samb_wdt_basic_use_case_setup Setup
 *
 * \subsection asfdoc_samb_wdt_basic_use_case_setup_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_samb_wdt_basic_use_case_setup_code Code
 * Copy-paste the following setup code to your user application:
 * \snippet qs_wdt_basic.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_wdt_basic.c setup_init
 *
 * \subsection asfdoc_samb_wdt_basic_use_case_setup_flow Workflow
 * -# Create a module software instance structure for the WDT module to store
 *    the WDT driver state while it is in use.
 *    \snippet qs_wdt_basic.c module_inst
 *    \note This should never go out of scope as long as the module is in use.
 *          In most cases, this should be global.
 *
 * -# Create a Watchdog module configuration struct, which can be filled out to
 *    adjust the configuration of the Watchdog.
 *    \snippet qs_wdt_basic.c setup_1
 * -# Initialize the Watchdog configuration struct with the module's default
 *    values.
 *    \snippet qs_wdt_basic.c setup_2
 *    \note This should always be performed before using the configuration
 *          struct to ensure that all values are initialized to known default
 *          settings.
 *
 * -# Adjust the configuration struct to set the load value of the Watchdog.
 *    \snippet qs_wdt_basic.c setup_3
 * -# Setup the WDT hardware module with the requested settings.
 *    \snippet qs_wdt_basic.c setup_4
 * -# Register and enable the Early Warning callback handler.
 *  -# Register the user-provided Early Warning callback function with the
 *     driver, so that it will be run when an Early Warning condition occurs.
 *     \snippet qs_wdt_basic.c setup_5
 *  -# Enable the Early Warning callback so that it will generate callbacks.
 *     \snippet qs_wdt_basic.c setup_6
 *
 * \section asfdoc_samb_wdt_basic_use_case Use Case
 *
 * \subsection asfdoc_samb_wdt_basic_use_case_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_wdt_basic.c main
 *
 * \subsection asfdoc_samb_wdt_basic_use_case_main Workflow
 * -# Turn on the board LED
 *    \snippet qs_wdt_basic.c main_1
 * -# Enter an infinite loop to hold the main program logic.
 *    \snippet qs_wdt_basic.c main_2
 * -# Test to see if the board button is currently being pressed.
 *    \snippet qs_wdt_basic.c main_3
 * -# Read the Watchdog current count value.
 *    \snippet qs_wdt_basic.c main_4
 * -# Reload the Watchdog count value.
 *    \snippet qs_wdt_basic.c main_5
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
