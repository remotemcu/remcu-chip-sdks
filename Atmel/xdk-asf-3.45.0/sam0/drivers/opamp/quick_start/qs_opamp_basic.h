/**
 * \file
 *
 * \brief SAM OPAMP Driver Quick Start
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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
 * \page asfdoc_sam0_opamp_basic_use_case Quick Start Guide for OPAMP - Basic
 *
 * In this use case, the OPAMP0 is configured as "Non-Inverting PGA" mode,
 * refer to the second mode of "Built-in Modes" in the device datasheet.
 *
 * You can give a signal on OA0POS and watch the output on OA0OUT
 * through an oscilloscope.
 *
 * \section asfdoc_sam0_opamp_basic_use_case_setup Setup
 *
 * \subsection asfdoc_sam0_opamp_basic_use_case_setup_prereq Prerequisites
 * There are no special setup requirements for this use case.
 *
 * \subsection asfdoc_sam0_opamp_basic_use_case_setup_code Code
 * Copy-paste the following setup code to your user application:
 * \snippet qs_opamp_basic.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_opamp_basic.c setup_init
 *
 * \subsection asfdoc_sam0_opamp_basic_use_case_setup_flow Workflow
 * -# Create an OPAMP0 configuration struct, which can be filled out to
 *    adjust the configuration of OPAMP0.
 *    \snippet qs_opamp_basic.c setup_1
 *
 * -# Initialize the OPAMP module.
 *    \snippet qs_opamp_basic.c setup_2
 *
 * -# Initialize the OPAMP0 configuration struct with the module's default values.
 *    \snippet qs_opamp_basic.c setup_3
 *    \note This should always be performed before using the configuration
 *          struct to ensure that all values are initialized to known default
 *          settings.
 *
 * -# Adjust the configuration struct to set the OPAMP0 as "Non-Inverting PGA" mode.
 *    \snippet qs_opamp_basic.c setup_4
 *    \note The existing configuration struct may be re-used, as long as any
 *          values that have been altered from the default settings are taken
 *          into account by the user application.
 *
 * -# Set up OA0POS pin and OA0OUT pin.
 *    \snippet qs_opamp_basic.c setup_5
 *
 * -# Write OPAMP0 configuration to the hardware module.
 *    \snippet qs_opamp_basic.c setup_6
 *
 * -# Enable OPAMP0.
 *    \snippet qs_opamp_basic.c setup_7
 *
 * -# Wait for the output ready.
 *    \snippet qs_opamp_basic.c setup_8
 *
 * \section asfdoc_sam0_opamp_basic_use_case_use_main Use Case
 *
 * \subsection asfdoc_sam0_opamp_basic_use_case_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_opamp_basic.c main
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
