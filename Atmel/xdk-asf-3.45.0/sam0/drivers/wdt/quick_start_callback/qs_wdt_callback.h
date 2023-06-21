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

/**
 * \page asfdoc_sam0_wdt_callback_use_case Quick Start Guide for WDT - Callback
 *
 * In this use case, the Watchdog module is configured for:
 *  \li System reset after 4096 clocks of the Watchdog generic clock
 *  \li Always on mode disabled
 *  \li Early warning period of 2048 clocks of the Watchdog generic clock
 *
 * This use case sets up the Watchdog to force a system reset after every 4096
 * clocks of the Watchdog's Generic Clock channel, with an Early Warning
 * callback being generated every 2048 clocks. Each time the Early Warning
 * interrupt fires the board LED is turned on, and each time the device resets
 * the board LED is turned off, giving a periodic flashing pattern.
 *
 *
 * \section asfdoc_sam0_wdt_callback_use_case_setup Setup
 *
 * \subsection asfdoc_sam0_wdt_callback_use_case_setup_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_sam0_wdt_callback_use_case_setup_code Code
 * Copy-paste the following setup code to your user application:
 * \snippet qs_wdt_callback.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_wdt_callback.c setup_init
 *
 * \subsection asfdoc_sam0_wdt_callback_use_case_setup_flow Workflow
 * -# Configure and enable the Watchdog driver.
 *  -# Create a Watchdog module configuration struct, which can be filled out to
 *     adjust the configuration of the Watchdog.
 *     \snippet qs_wdt_callback.c setup_1
 *  -# Initialize the Watchdog configuration struct with the module's default
 *     values.
 *     \snippet qs_wdt_callback.c setup_2
 *     \note This should always be performed before using the configuration
 *           struct to ensure that all values are initialized to known default
 *           settings.
 *
 *  -# Adjust the configuration struct to set the timeout and early warning
 *     periods of the Watchdog.
 *     \snippet qs_wdt_callback.c setup_3
 *  -# Sets up the WDT hardware module with the requested settings.
 *     \snippet qs_wdt_callback.c setup_4
 * -# Register and enable the Early Warning callback handler.
 *  -# Register the user-provided Early Warning callback function with the
 *     driver, so that it will be run when an Early Warning condition occurs.
 *     \snippet qs_wdt_callback.c setup_5
 *  -# Enable the Early Warning callback so that it will generate callbacks.
 *     \snippet qs_wdt_callback.c setup_6
 *
 * \section asfdoc_sam0_wdt_callback_use_case Use Case
 *
 * \subsection asfdoc_sam0_wdt_callback_use_case_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_wdt_callback.c main
 *
 * \subsection asfdoc_sam0_wdt_callback_use_case_main Workflow
 * -# Turn off the board LED when the application starts.
 *    \snippet qs_wdt_callback.c main_1
 * -# Enable global interrupts so that callbacks can be generated.
 *    \snippet qs_wdt_callback.c main_2
 * -# Enter an infinite loop to hold the main program logic.
 *    \snippet qs_wdt_callback.c main_3
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
