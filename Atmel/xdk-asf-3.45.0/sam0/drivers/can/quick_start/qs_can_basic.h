/**
 * \file
 *
 * \brief SAM CAN basic Quick Start
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
 * \page asfdoc_sam0_can_basic_use_case Quick Start Guide for CAN normal mode
 *
 * The supported board list:
 *    - SAMC21 Xplained Pro
 *
 * This quick start need two SAMC21 Xplained Pro boards with CAN interface
 * connected by the jump wire: CANH - CANH and CANL - CANL.
 *
 * It show how to handle standard message in a normal CAN network
 * with filter setting, message sending, receive buffer and FIFO usage and
 * interrupt handling.
 *
 * User can choose to set up two standard filter id and two extended filter id
 * as receive filter.
 * And then user can choose to send messages with the standard or
 * extended filter id.
 * If the message has been received, it will print the received data on the
 * console.
 * The configuration is defined in conf_can.h file with message max data
 * length 8 and baudrate 500KHz.
 *
 * \section asfdoc_sam0_can_basic_use_case_setup Setup
 *
 * \subsection asfdoc_sam0_can_basic_use_case_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_sam0_can_basic_use_case_setup_code Code
 * Add to the main application source file, outside of any functions:
 * \snippet qs_can_basic.c module_var
 *
 * Copy-paste the following setup code to your user application:
 * \snippet qs_can_basic.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_can_basic.c setup_init
 *
 * \subsection asfdoc_sam0_can_basic_use_case_setup_flow Workflow
 * -# Create USART CDC module and CAN module software instance structure.
 *    \snippet qs_can_basic.c module_inst
 *
 * -# Define CAN standard filter setting.
 *    \snippet qs_can_basic.c can_filter_setting
 *
 * -# Define CAN standard transfer message setting.
 *    \snippet qs_can_basic.c can_transfer_message_setting
 *
 * -# Define CAN standard receive message setting.
 *    \snippet qs_can_basic.c can_receive_message_setting
 *
 * -# Configure the USART CDC for output message.
 *     \snippet qs_can_basic.c cdc_setup
 *
 * -# Configure the CAN module.
 *     \snippet qs_can_basic.c can_init_setup
 *
 * -# Configure the CAN standard receive filter.
 *     \snippet qs_can_basic.c can_receive_filter_setup
 *
 * -# Configure the CAN transfer message.
 *     \snippet qs_can_basic.c can_transfer_message_setup
 *
 * -# Implement the interrupt handler function.
 *     \snippet qs_can_basic.c can_interrupt_handler
 *
 * -# User menu function.
 *     \snippet qs_can_basic.c user_menu
 *
 * \section asfdoc_sam0_can_basic_use_case_main Use Case
 *
 * \subsection asfdoc_sam0_can_basic_use_case_main_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_can_basic.c main_setup
 *
 * \subsection asfdoc_sam0_can_basic_use_case_main_flow Workflow
 * -# Set up CAN module.
 *     \snippet qs_can_basic.c configure_can
 * -# Display user menu .
 *     \snippet qs_can_basic.c display_user_menu
 * -# Enter the main loop, wait for the user input .
 *     \snippet qs_can_basic.c main_loop
 */
