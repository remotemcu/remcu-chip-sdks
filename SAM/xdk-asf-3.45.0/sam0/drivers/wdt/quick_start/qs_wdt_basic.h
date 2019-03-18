/**
 * \file
 *
 * \brief SAM Watchdog Driver Quick Start
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
 * \page asfdoc_sam0_wdt_basic_use_case Quick Start Guide for WDT - Basic
 *
 * In this use case, the Watchdog module is configured for:
 *  \li System reset after 2048 clocks of the Watchdog generic clock
 *  \li Always on mode disabled
 *  \li Basic mode, with no window or early warning periods
 *
 * This use case sets up the Watchdog to force a system reset after every 2048
 * clocks of the Watchdog's Generic Clock channel, unless the user periodically
 * resets the Watchdog counter via a button before the timer expires. If the
 * Watchdog resets the device, a LED on the board is turned off.
 *
 * \section asfdoc_sam0_wdt_basic_use_case_setup Setup
 *
 * \subsection asfdoc_sam0_wdt_basic_use_case_setup_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_sam0_wdt_basic_use_case_setup_code Code
 * Copy-paste the following setup code to your user application:
 * \snippet qs_wdt_basic.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_wdt_basic.c setup_init
 *
 * \subsection asfdoc_sam0_wdt_basic_use_case_setup_flow Workflow
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
 * -# Adjust the configuration struct to set the timeout period and lock mode
 *    of the Watchdog.
 *    \snippet qs_wdt_basic.c setup_3
 * -# Setups the WDT hardware module with the requested settings.
 *    \snippet qs_wdt_basic.c setup_4
 *
 * \section asfdoc_sam0_wdt_basic_use_case Use Case
 *
 * \subsection asfdoc_sam0_wdt_basic_use_case_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_wdt_basic.c main
 *
 * \subsection asfdoc_sam0_wdt_basic_use_case_main Workflow
 * -# Retrieve the cause of the system reset to determine if the Watchdog module
 *    was the cause of the last reset.
 *    \snippet qs_wdt_basic.c main_1
 * -# Turn on or off the board LED based on whether the Watchdog reset the device.
 *    \snippet qs_wdt_basic.c main_2
 * -# Enter an infinite loop to hold the main program logic.
 *    \snippet qs_wdt_basic.c main_3
 * -# Test to see if the board button is currently being pressed.
 *    \snippet qs_wdt_basic.c main_4
 * -# If the button is pressed, turn on the board LED and reset the Watchdog
 *    timer.
 *    \snippet qs_wdt_basic.c main_5
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
