/**
 * \file
 *
 * \brief SAM True Random Number Generator Driver Quick Start
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
 * \page asfdoc_sam0_trng_basic_use_case Quick Start Guide for TRNG - Basic
 *
 * In this use case, the True Random Number Generator (TRNG) module is configured for:
 *  \li The TRNG peripheral will not be stopped in standby sleep mode
 *
 * This use case will read random data in polling mode repeatedly. After reading
 * a data, the board LED will be toggled.
 *
 * \section asfdoc_sam0_trng_basic_use_case_setup Setup
 *
 * \subsection asfdoc_sam0_trng_basic_use_case_setup_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_sam0_trng_basic_use_case_setup_code Code
 * Copy-paste the following setup code to your user application:
 * \snippet qs_trng_basic.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_trng_basic.c setup_init
 *
 * \subsection asfdoc_sam0_trng_basic_use_case_setup_flow Workflow
 * -# Create a TRNG device instance struct, which will be associated with a
 *    TRNG peripheral hardware instance.
 *    \snippet qs_trng_basic.c setup_1
 *    \note Device instance structures shall \b never go out of scope when in
 *          use.
 *
 * -# Create a new function \c configure_trng(), which will be used to configure
 *    the overall TRNG peripheral.
 *    \snippet qs_trng_basic.c setup_2
 * -# Create a TRNG peripheral configuration structure that will
 *    be filled out to set the module configuration.
 *    \snippet qs_trng_basic.c setup_2_1
 * -# Fill the TRNG peripheral configuration structure with the
 *    default module configuration values.
 *    \snippet qs_trng_basic.c setup_2_2
 * -# Initialize the TRNG peripheral and associate it with the
 *    software instance structure that was defined previously.
 *    \snippet qs_trng_basic.c setup_2_3
 *
 * -# Enable the now initialized TRNG peripheral.
 *    \snippet qs_trng_basic.c setup_init_1
 *
 * \section asfdoc_sam0_trng_basic_use_case_imp Implementation
 *
 * \subsection asfdoc_sam0_trng_basic_use_case_imp_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_trng_basic.c main
 *
 * \subsection asfdoc_sam0_trng_basic_use_case_imp_flow Workflow
 * -# Make the application loop infinitely.
 *    \snippet qs_trng_basic.c main_1
 * -# Start to read a random data from TRNG until success.
 *    \snippet qs_trng_basic.c main_2
 * -# Toggle the board LED to indicate a random data is read.
 *    \snippet qs_trng_basic.c main_3
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
