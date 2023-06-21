/**
 * \file
 *
 * \brief SAM BOD Driver Quick Start
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
 */

/**
 * \page asfdoc_sam0_bod_basic_use_case Quick Start Guide for BOD - Basic
 *
 * In this use case, the BOD33 will be configured with the following settings:
 * - Continuous sampling mode
 * - Prescaler setting of two
 * - Reset action on low voltage detect
 *
 * \section asfdoc_sam0_bod_basic_use_case_setup Quick Start
 *
 * \subsection asfdoc_sam0_bod_basic_use_case_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_sam0_bod_basic_use_case_setup_code Code
 * Copy-paste the following setup code to your user application:
 * \snippet qs_bod_basic_use.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_bod_basic_use.c setup_init
 *
 * \subsection asfdoc_sam0_bod_basic_use_case_setup_flow Workflow
 * -# Create a BOD module configuration struct, which can be filled out to
 *    adjust the configuration of a physical BOD peripheral.
 *    \snippet qs_bod_basic_use.c setup_config
 * -# Initialize the BOD configuration struct with the module's default values.
 *    \snippet qs_bod_basic_use.c setup_config_defaults
 *    \note This should always be performed before using the configuration
 *          struct to ensure that all values are initialized to known default
 *          settings.
 *
 * -# Configure the BOD module with the desired settings.
 *    \snippet qs_bod_basic_use.c setup_set_config
 * -# Enable the BOD module so that it will monitor the power supply voltage.
 *    \snippet qs_bod_basic_use.c setup_enable
 *
 *
 * \section asfdoc_sam0_bod_basic_use_case_main Use Case
 *
 * \subsection asfdoc_sam0_bod_basic_use_case_main_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_bod_basic_use.c main
 *
 * \subsection asfdoc_sam0_bod_basic_use_case_main_flow Workflow
 * -# Enter an infinite loop so that the BOD can continue to monitor the supply
 *    voltage level.
 *    \snippet qs_bod_basic_use.c main_loop
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
