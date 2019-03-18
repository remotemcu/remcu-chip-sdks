/**
 * \file
 *
 * \brief SAM TIMER Driver Quick Start for SAMB11
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
 * \page asfdoc_samb_timer_basic_use_case Quick Start Guide for TIMER - Basic
 *
 * In this use case, the TIMER module is configured for general downward timer.
 * The TIMER module will be set up as follows:
 * - Disable external input as enable
 * - Disable external input as clock
 * - Enable interrupt
 *
 * \section asfdoc_samb_timer_basic_use_case_setup Setup
 *
 * \subsection asfdoc_samb_timer_basic_use_case_setup_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_samb_timer_basic_use_case_setup_code Code
 * Copy-paste the following setup code to your user application:
 * \snippet qs_timer_basic.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_timer_basic.c setup_init
 *
 * \subsection asfdoc_samb_timer_basic_use_case_setup_flow Workflow
 * -# Create a new function \c configure_gpio_pins(), which will be used to configure
 *    the GPIO peripheral.
 *    \snippet qs_timer_basic.c config_gpio
 * -# Create a new function \c configure_timer(), which will be used to configure
 *    the TIMER peripheral.
 *    \snippet qs_timer_basic.c config_timer
 * -# Create a GPIO module pin configuration struct, which can be filled out to
 *    adjust the configuration of a single gpio pin.
 *    \snippet qs_timer_basic.c setup_gpio_1
 * -# Initialize the pin configuration struct with the module's default values.
 *    \snippet qs_timer_basic.c setup_gpio_2
 *
 * -# Adjust the configuration struct to request an output pin.
 *    \snippet qs_timer_basic.c setup_gpio_3
 * -# Configure LED pin with the initialized pin configuration struct, to enable
 *    the output driver on the pin.
 *    \snippet qs_timer_basic.c setup_gpio_4
 *
 * -# Create a TIMER module configuration struct, which can be filled out to
 *    adjust the configuration of a physical TIMER peripheral.
 *    \snippet qs_timer_basic.c setup_timer_1
 * -# Initialize the TIMER configuration struct with the module's default values.
 *    \snippet qs_timer_basic.c setup_timer_2
 *
 * -# Configure the TIMER module with the desired settings.
 *    \snippet qs_timer_basic.c setup_timer_3
 * -# Configure TIMER module with the initialized configuration struct.
 *    \snippet qs_timer_basic.c setup_timer_4
 *
 * -# Set the TIMER module enable.
 *    \snippet qs_timer_basic.c setup_timer_5
 *
 * \section asfdoc_samb_timer_basic_use_case_use_main Use Case
 *
 * \subsection asfdoc_samb_timer_basic_use_case_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_timer_basic.c main_loop
 *
 */