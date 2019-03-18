/**
 * \file
 *
 * \brief SAM TC Driver Quick Start
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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
 * \page asfdoc_sam0_tc_basic_use_case Quick Start Guide for TC - Basic
 *
 * In this use case, the TC will be used to generate a PWM signal. Here
 * the pulse width is set to one quarter of the period. The TC module will be
 * set up as follows:
 *
 * - GCLK generator 0 (GCLK main) clock source
 * - 16-bit resolution on the counter
 * - No prescaler
 * - Normal PWM wave generation
 * - GCLK reload action
 * - Don't run in standby
 * - No inversion of waveform output
 * - No capture enabled
 * - Count upward
 * - Don't perform one-shot operations
 * - No event input enabled
 * - No event action
 * - No event generation enabled
 * - Counter starts on 0
 * - Capture compare channel 0 set to 0xFFFF/4
 *
 * \section asfdoc_sam0_tc_basic_use_case_setup Quick Start
 *
 * \subsection asfdoc_sam0_tc_basic_use_case_prereq Prerequisites
 * There are no prerequisites for this use case.
 *
 * \subsection asfdoc_sam0_tc_basic_use_case_setup_code Code
 * Add to the main application source file, before any functions:
 * - SAM D21 Xplained Pro.
 *   \snippet quick_start/samd21_xplained_pro/conf_quick_start.h definition_pwm
 * - SAM D20 Xplained Pro.
 *   \snippet quick_start/samd20_xplained_pro/conf_quick_start.h definition_pwm
 * - SAM R21 Xplained Pro.
 *   \snippet quick_start/samr21_xplained_pro/conf_quick_start.h definition_pwm
 * - SAM D11 Xplained Pro.
 *   \snippet quick_start/samd11_xplained_pro/conf_quick_start.h definition_pwm
 * - SAM L21 Xplained Pro.
 *   \snippet quick_start/saml21_xplained_pro/conf_quick_start.h definition_pwm
 * - SAM L22 Xplained Pro.
 *   \snippet quick_start/saml22_xplained_pro/conf_quick_start.h definition_pwm
 * - SAM DA1 Xplained Pro.
 *   \snippet quick_start/samda1_xplained_pro/conf_quick_start.h definition_pwm
 * - SAM HA1G16A Xplained Pro.
 *   \snippet quick_start/samda1_xplained_pro/conf_quick_start.h definition_pwm
 * - SAM C21 Xplained Pro.
 *   \snippet quick_start/samc21_xplained_pro/conf_quick_start.h definition_pwm
 *
 * Add to the main application source file, outside of any functions:
 * \snippet qs_tc_basic.c module_inst
 *
 * Copy-paste the following setup code to your user application:
 * \snippet qs_tc_basic.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_tc_basic.c setup_init
 *
 * \subsection asfdoc_sam0_tc_basic_use_case_setup_flow Workflow
 * -# Create a module software instance structure for the TC module to store
 *    the TC driver state while it is in use.
 *    \snippet qs_tc_basic.c module_inst
 *    \note This should never go out of scope as long as the module is in use.
 *          In most cases, this should be global.
 *
 * -# Configure the TC module.
 *  -# Create a TC module configuration struct, which can be filled out to
 *     adjust the configuration of a physical TC peripheral.
 *     \snippet qs_tc_basic.c setup_config
 *  -# Initialize the TC configuration struct with the module's default values.
 *     \snippet qs_tc_basic.c setup_config_defaults
 *     \note This should always be performed before using the configuration
 *           struct to ensure that all values are initialized to known default
 *           settings.
 *
 *  -# Alter the TC settings to configure the counter width, wave generation
 *     mode, and the compare channel 0 value.
 *     \snippet qs_tc_basic.c setup_change_config
 *  -# Alter the TC settings to configure the PWM output on a physical device
 *     pin.
 *     \snippet qs_tc_basic.c setup_change_config_pwm
 *  -# Configure the TC module with the desired settings.
 *     \snippet qs_tc_basic.c setup_set_config
 *  -# Enable the TC module to start the timer and begin PWM signal generation.
 *     \snippet qs_tc_basic.c setup_enable
 *
 *
 * \section asfdoc_sam0_tc_basic_use_case_main Use Case
 *
 * \subsection asfdoc_sam0_tc_basic_use_case_main_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_tc_basic.c main
 *
 * \subsection asfdoc_sam0_tc_basic_use_case_main_flow Workflow
 * -# Enter an infinite loop while the PWM wave is generated via the TC module.
 *    \snippet qs_tc_basic.c main_loop
 */

