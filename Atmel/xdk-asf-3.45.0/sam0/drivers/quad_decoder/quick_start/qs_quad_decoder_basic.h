/**
 * \file
 *
 * \brief SAM QUAD DECODER Driver Quick Start for SAMB11
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
 * \page asfdoc_samb_quad_decoder_basic_use_case Quick Start Guide for QUAD DECODER - Basic
 *
 * In this use case, the QUAD DECODER module is configured for quad decoder.
 *
 * \section asfdoc_samb_quad_decoder_basic_use_case_setup Setup
 *
 * \subsection asfdoc_samb_quad_decoder_basic_use_case_setup_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_samb_quad_decoder_basic_use_case_setup_code Code
 * Copy-paste the following setup code to your user application:
 * \snippet qs_quad_decoder_basic.c setup
 *
 * \subsection asfdoc_samb_quad_decoder_use_case_main_code Add to Main
 * Add the following to \c main().
 * \snippet qs_quad_decoder_basic.c add_main
 *
 * \subsection asfdoc_samb_quad_decoder_basic_use_case_setup_flow Workflow
 * -# Make configuration structure.
 *    \snippet qs_quad_decoder_basic.c set_conf
 *
 * -# Fill the configuration structure with the default driver configuration.
 *    \snippet qs_quad_decoder_basic.c get_def
 *    \note This should always be performed before using the configuration
 *          struct to ensure that all values are initialized to known default
 *          settings.
 *
 * -# Change configurations pinmux as desired.
 *    \snippet qs_quad_decoder_basic.c setup_pinmux
 *
 * -# Initialize axis module.
 *    \snippet qs_quad_decoder_basic.c init_qdec
 *
 * -# Register callback.
 *    \snippet qs_quad_decoder_basic.c setup_register_callback
 *
 * -# Enable IRQ.
 *    \snippet qs_quad_decoder_basic.c enable_IRQ
 *
 * \section asfdoc_samb_quad_decoder_basic_use_case_basic_implement Implementation
 * Add the following to \c main().
 * \snippet qs_quad_decoder_basic.c main_imp
 *
 * \subsection asfdoc_samb_quad_decoder_basic_use_case_basic_workflow Workflow
 * -# Start an infinite loop, to continuously get quad decoder counter.
 *    \snippet qs_quad_decoder_basic.c main_loop
 *
 * -# Get the x,y,z counter
 *    \snippet qs_quad_decoder_basic.c get_counter
 */