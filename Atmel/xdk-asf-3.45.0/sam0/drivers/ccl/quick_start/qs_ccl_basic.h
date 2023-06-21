/**
 * \file
 *
 * \brief SAM CCL Driver Quick Start
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
 * \page asfdoc_sam0_ccl_basic_use_case Quick Start Guide for CCL - Basic
 *
 * In this use case, the LUT0 and LUT1 input source is configured as I/O pin.
 * The LUT0 and LUT1 pair is connected to internal sequential logic, which is configured
 * as D flip flop mode.
 *
 * \section asfdoc_sam0_ccl_basic_use_case_setup Setup
 *
 * \subsection asfdoc_sam0_ccl_basic_use_case_setup_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_sam0_ccl_basic_use_case_setup_code Code
 * Copy-paste the following setup code to your user application:
 * \snippet qs_ccl_basic.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_ccl_basic.c setup_init
 * \snippet qs_ccl_basic.c setup_enable
 *
 * \subsection asfdoc_sam0_ccl_basic_use_case_setup_flow Workflow
 * -# Creates a CCL configuration struct, which can be filled out to
 *    adjust the configuration of CCL.
 *    \snippet qs_ccl_basic.c setup_1
 *
 * -# Settings and fill the CCL configuration struct with the default settings.
 *    \snippet qs_ccl_basic.c setup_2
 *
 * -# Initializes CCL module.
 *    \snippet qs_ccl_basic.c setup_3
 *
 * -# Creates a LUT configuration struct, which can be filled out to
 *    adjust the configuration of LUT0.
 *    \snippet qs_ccl_basic.c setup_4
 *
  * -# Fill the LUT0 configuration struct with the default settings.
 *    \snippet qs_ccl_basic.c setup_5
 *
 * -# Adjust the LUT0 configuration struct.
 *    \snippet qs_ccl_basic.c setup_6
 *
 * -# Set up LUT0 input and output pin.
 *    \snippet qs_ccl_basic.c setup_7
 *
 * -# Writes LUT0 configuration to the hardware module.
 *    \snippet qs_ccl_basic.c setup_8
 *
 * -# Creates a LUT configuration struct, which can be filled out to
 *    adjust the configuration of LUT1.
 *    \snippet qs_ccl_basic.c setup_9
 *
  * -# Fill the LUT1 configuration struct with the default settings.
 *    \snippet qs_ccl_basic.c setup_10
 *
 * -# Adjust the LUT1 configuration struct.
 *    \snippet qs_ccl_basic.c setup_11
 *
 * -# Set up LUT1 input and output pin.
 *    \snippet qs_ccl_basic.c setup_12
 *
 * -# Writes LUT1 configuration to the hardware module.
 *    \snippet qs_ccl_basic.c setup_13
 *
 * -# Configure the sequential logic with the D flip flop mode.
 *    \snippet qs_ccl_basic.c setup_14
 *
 * \section asfdoc_sam0_ccl_basic_use_case_use_main Use Case
 *
 * \subsection asfdoc_sam0_ccl_basic_use_case_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_ccl_basic.c main
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
