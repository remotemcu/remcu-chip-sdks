/**
 * \file
 *
 * \brief SAM AON Sleep Timer Driver Quick Start for SAMB11
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
 * \page asfdoc_samb_aon_sleep_timer_basic_use_case Quick Start Guide for AON Sleep Timer - Basic
 *
 * In this use case, the AON Sleep Timer module is configured for wakeup MCU at defined interval 
 * and set the LED for indication.
 *
 * \section asfdoc_samb_aon_sleep_timer_basic_use_case_setup Setup
 *
 * \subsection asfdoc_samb_aon_sleep_timer_basic_use_case_setup_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_samb_aon_sleep_timer_basic_use_case_setup_code Code
 * Copy-paste the following setup code to your user application:
 * \snippet qs_aon_sleep_timer_basic.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_aon_sleep_timer_basic.c setup_init
 *
 * \subsection asfdoc_samb_aon_sleep_timer_basic_use_case_setup_flow Workflow
 * -# Create a new function \c configure_gpio_pins(), which will be used to configure
 *    the GPIO peripheral.
 *    \snippet qs_aon_sleep_timer_basic.c config_gpio
 *
 *   -# Create a GPIO module configuration struct, which can be filled out to
 *      adjust the configuration of a physical GPIO peripheral.
 *    \snippet qs_aon_sleep_timer_basic.c setup_1
 *   -# Initialize the GPIO configuration struct with the module's default values.
 *    \snippet qs_aon_sleep_timer_basic.c setup_2
 *
 *   -# Configure the GPIO module as output.
 *    \snippet qs_aon_sleep_timer_basic.c setup_3
 *
 *   -# Set the GPIO module enable.
 *    \snippet qs_aon_sleep_timer_basic.c setup_4
 *
 *   -# Set the LED on.
 *    \snippet qs_aon_sleep_timer_basic.c setup_5
 *
 * -# Create a new function \c configure_aon_sleep_timer(), which will be used to configure
 *    the AON Sleep Timer peripheral.
 *    \snippet qs_aon_sleep_timer_basic.c config_timer
 *
 *   -# Create a AON Sleep Timer module configuration struct, which can be filled out to
 *      adjust the configuration of a physical  AON Sleep Timer peripheral.
 *    \snippet qs_aon_sleep_timer_basic.c setup_6
 *
 *   -# Initialize the  AON Sleep Timer configuration struct with the module's default values.
 *    \snippet qs_aon_sleep_timer_basic.c setup_7
 *
 *   -# Configure the AON Sleep Timer module with the desired settings.
 *    \snippet qs_aon_sleep_timer_basic.c setup_8
 *
 *   -# Initialize and enable the AON Sleep Timer module.
 *    \snippet qs_aon_sleep_timer_basic.c setup_9
 *
 *   -# Register Enable the AON Sleep Timer callback.
 *    \snippet qs_aon_sleep_timer_basic.c setup_register_callback
 *
 * -# Waiting for the AON Sleep Timer module active.
 *    \snippet qs_aon_sleep_timer_basic.c timer_active
 *
 * -# Waiting for the AON Sleep Timer interrupt.
 *    \snippet qs_aon_sleep_timer_basic.c wait_wfi
 *
 * -# Unregister callback and Disable Timer module.
 *    \snippet qs_aon_sleep_timer_basic.c timer_disable
 *
 * \section asfdoc_samb_aon_sleep_timer_basic_use_case_basic_implement Implementation
 * Add the following to \c main().
 * \snippet qs_aon_sleep_timer_basic.c main_imp
 *
 * \subsection asfdoc_samb_aon_sleep_timer_basic_use_case_basic_workflow Workflow
 * -# Start an infinite loop.
 *    \snippet qs_aon_sleep_timer_basic.c main_loop
 *
 */