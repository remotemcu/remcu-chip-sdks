/**
 * \file
 *
 * \brief SAM PWM Driver Quick Start for SAMB11
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
 * \page asfdoc_samb_pwm_basic_use_case Quick Start Guide for PWM - Basic
 *
 * In this use case, the PWM module is configured for:
 *   \li 1 not to inverse the polarity
 *   \li Sample method 0
 *   \li PWM period is 4
 *   \li Duty cycle is 50%
 *   \li No use agcupdate
 *   \li Clock is 26MHz
 *   \li Output frequency is 25.4KHz
 *   \li Pinmux pad
 *
 * This use case sets up the PWM to configure the PWM output on a physical device
 * pin.
 *
 * \section asfdoc_samb_pwm_basic_use_case_setup Setup
 *
 * \subsection asfdoc_samb_pwm_basic_use_case_setup_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_samb_pwm_basic_use_case_setup_code Code
 * Copy-paste the following setup code to your user application:
 * \snippet qs_pwm_basic.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_pwm_basic.c setup_init
 *
 * \subsection asfdoc_samb_pwm_basic_use_case_setup_flow Workflow
 * -# Create a PWM module pin configuration struct, which can be filled out to
 *    adjust the configuration of a single pwm.
 *    \snippet qs_pwm_basic.c setup_1
 * -# Initialize the pwm configuration struct with the module's default values.
 *    \snippet qs_pwm_basic.c setup_2
 *    \note This should always be performed before using the configuration
 *          struct to ensure that all values are initialized to known default
 *          settings.
 *
 * -# Adjust the configuration struct to request an output pin.
 *    \snippet qs_pwm_basic.c setup_3
 * -# Configure the PWM module with the desired settings.
 *    \snippet qs_pwm_basic.c setup_4
 * -# Enable the PWM module to start and begin PWM signal generation.
 *    \snippet qs_pwm_basic.c setup_5
 *
 * \section asfdoc_samb_pwm_basic_use_case_use_main Use Case
 *
 * \subsection asfdoc_samb_pwm_basic_use_case_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_pwm_basic.c main
 *
 * \subsection asfdoc_samb_pwm_basic_use_case_flow Workflow
 * -# Enter an infinite loop while the PWM wave is generated via the PWM module.
 *    \snippet qs_pwm_basic.c main
 */

