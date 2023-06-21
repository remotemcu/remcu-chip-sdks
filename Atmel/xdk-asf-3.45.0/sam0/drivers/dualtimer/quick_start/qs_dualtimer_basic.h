/**
 * \file
 *
 * \brief SAM DUALTIMER Driver Quick Start for SAMB11
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
 * \page asfdoc_samb_dualtimer_basic_use_case Quick Start Guide for DUALTIMER - Basic
 *
 * In this use case, the DUALTIMER module is configured for two general downward timer.
 *
 * \section asfdoc_samb_dualtimer_basic_use_case_setup Setup
 *
 * \subsection asfdoc_samb_dualtimer_basic_use_case_setup_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_samb_dualtimer_basic_use_case_setup_code Code
 * Copy-paste the following setup code to your user application:
 * \snippet qs_dualtimer_basic.c setup
 *
 * \subsection asfdoc_samb_dualtimer_basic_use_case_basic_callback Callback
 * -# Print the time1 trigger.
 *    \snippet qs_dualtimer_basic.c print_timer1
 *
 * -# Print the timer2 trigger.
 *    \snippet qs_dualtimer_basic.c print_timer2
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_dualtimer_basic.c setup_init
 *
 * \subsection asfdoc_samb_dualtimer_basic_use_case_setup_flow Workflow
 * -# Create a new function \c configure_uart(), which will be used to configure
 *    the UART peripheral.
 *    \snippet qs_dualtimer_basic.c config_uart
 *   -# Create a UART module instance struct.
 *    \snippet qs_dualtimer_basic.c module_inst
 *   -# Create a UART module configuration struct, which can be filled out to
 *      adjust the configuration of a physical UART peripheral.
 *    \snippet qs_dualtimer_basic.c setup_uart_1
 *   -# Initialize the UART configuration struct with the module's default values.
 *    \snippet qs_dualtimer_basic.c setup_uart_2
 *   -# Change configurations uart as desired.
 *    \snippet qs_dualtimer_basic.c setup_uart_3
 *   -# Change configurations uart as desired.
 *    \snippet qs_dualtimer_basic.c setup_uart_4
 *
 * -# Create a new function \c configure_dualtimer(), which will be used to configure
 *    the DUALTIMER peripheral.
 *    \snippet qs_dualtimer_basic.c config_dualtimer
 *   -# Create a DUALTIMER module configuration struct, which can be filled out to
 *    adjust the configuration of a physical DUALTIMER peripheral.
 *    \snippet qs_dualtimer_basic.c setup_dualtimer_1
 *   -# Initialize the DUALTIMER configuration struct with the module's default values.
 *    \snippet qs_dualtimer_basic.c setup_dualtimer_2
 *   -# Change configurations timer1 as desired.
 *    \snippet qs_dualtimer_basic.c setup_dualtimer_3
 *   -# Change configurations timer2 as desired.
 *    \snippet qs_dualtimer_basic.c setup_dualtimer_4
 *   -# Configure the DUALTIMER module with the desired settings.
 *    \snippet qs_dualtimer_basic.c setup_timer_5
 *
 * -# Create a new function \c configure_dualtimer_callback(), which will be used to configure
 *    the DUALTIMER callback.
 *    \snippet qs_dualtimer_basic.c config_callback
 *   -# Register dualtimer1 and dualtimer2 callback
 *    \snippet qs_dualtimer_basic.c setup_register_callback
 *   -# Enable callback
 *    \snippet qs_dualtimer_basic.c enable_IRQ
 *
 * \section asfdoc_samb_dualtimer_basic_use_case_basic_implement Implementation
 * Add the following to \c main().
 * \snippet qs_dualtimer_basic.c main_imp
 *
 * \subsection asfdoc_samb_dualtimer_basic_use_case_basic_workflow Workflow
 * -# Start an infinite loop, to get timer1/timer2 counter.
 *    \snippet qs_dualtimer_basic.c main_loop
 *
 */