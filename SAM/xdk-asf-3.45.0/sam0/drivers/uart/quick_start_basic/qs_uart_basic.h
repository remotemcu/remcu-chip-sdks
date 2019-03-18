/**
 * \file
 *
 * \brief SAM UART Quick Start for SAMB11
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

/**
 * \page asfdoc_samb_uart_basic_use_case Quick Start Guide for UART - Basic
 *
 * This quick start will show how to use both polled and callback interfaces.
 * It will echo back characters typed into the terminal. In this
 * use case the UART will be configured with the following settings:
 * - Asynchronous mode
 * - 9600 Baudrate
 * - 8-bits, No Parity and one Stop Bit
 * - TX and RX enabled and connected to the Xplained Pro Embedded Debugger virtual COM port
 *
 * \section asfdoc_samb_uart_basic_use_case_setup Setup
 *
 * \subsection asfdoc_samb_uart_basic_use_case_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_samb_uart_basic_use_case_setup_code Code
 * Add to the main application source file, outside of any functions:
 * \snippet qs_uart_basic.c module_inst
 * \snippet qs_uart_basic.c variable_inst
 *
 * Copy-paste the following setup code to your user application:
 * \snippet qs_uart_basic.c callback_functions
 * \snippet qs_uart_basic.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_uart_basic.c setup_init
 *
 * \subsection asfdoc_samb_uart_basic_use_case_setup_flow Workflow
 * -# Create a module software instance structure for the UART module to store
 *    the UART driver state while it is in use.
 *    \snippet qs_uart_basic.c module_inst
 *    \note This should never go out of scope as long as the module is in use.
 *          In most cases, this should be global.
 *
 * -# Create some global variables.
 *    \snippet qs_uart_basic.c variable_inst
 *
 * -# Create the callback functions.
 *    \snippet qs_uart_basic.c callback_functions
 *
 * -# Configure the UART module.
 *  -# Create a UART module configuration struct, which can be filled out to
 *     adjust the configuration of a physical UART peripheral.
 *     \snippet qs_uart_basic.c setup_config
 *  -# Initialize the UART configuration struct with the module's default values.
 *     \snippet qs_uart_basic.c setup_config_defaults
 *     \note This should always be performed before using the configuration
 *           struct to ensure that all values are initialized to known default
 *           settings.
 *
 *  -# Alter the UART settings to configure the physical pinout, baudrate, and
 *     other relevant parameters.
 *     \snippet qs_uart_basic.c setup_change_config
 *  -# Configure the UART module with the desired settings, retrying while the
 *     driver is busy until the configuration is stressfully set.
 *     \snippet qs_uart_basic.c setup_set_config
 *
 * \section asfdoc_samb_uart_basic_use_case_main Use Case
 *
 * \subsection asfdoc_samb_uart_basic_use_case_main_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_uart_basic.c main
 *
 * \subsection asfdoc_samb_uart_basic_use_case_main_flow Workflow
 * -# Send a string to the UART to show the demo is running, blocking until
 *    all characters have been sent.
 *    \snippet qs_uart_basic.c main_send_string1
 * -# Send the information to the UART and get the user input.
 *    \snippet qs_uart_basic.c test_callback_functions
 * -# Send a string to the UART to show enter the while loop, blocking until
 *    all characters have been sent.
 *    \snippet qs_uart_basic.c main_send_string2
 * -# Enter an infinite loop to continuously echo received values on the UART.
 *    \snippet qs_uart_basic.c main_loop
 * -# Perform a blocking read of the UART, storing the received character into
 *    the previously declared temporary variable.
 *    \snippet qs_uart_basic.c main_read
 * -# Echo the received variable back to the UART via a blocking write.
 *    \snippet qs_uart_basic.c main_write
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
