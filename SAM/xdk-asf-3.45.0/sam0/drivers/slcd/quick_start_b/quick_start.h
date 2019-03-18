/**
 *
 * \file
 *
 * \brief SAM SLCD Driver Quick Start
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

/** \page asfdoc_sam0_slcd_basic_use_case Quick Start Guide for SLCD
 *
 * The supported board list:
 *    - SAM L22 Xplained Pro B
 *
 * The TSLCD1 Xplained Pro extension board must be connected to extension
 * header 5 on the SAM L22 Xplained Pro B.
 *
 * This example demonstrates how to use the SLCD driver, it covers the following cases:
 * - Display Memory Mapping(Direct Access and Indirect Access)
 * - Character Mapping
 * - Blinking
 *
 * Upon startup, the program uses the USART driver to display application
 * output message.
 *
 * \section asfdoc_sam0_slcd_basic_use_case_setup Quick Start
 *
 * \subsection asfdoc_sam0_slcd_basic_use_case_prereq Prerequisites
 * There are no prerequisites for this use case.
 *
 * \subsection asfdoc_sam0_slcd_basic_use_case_setup_code Code
 *
 * Add to the main application source file, outside of any functions:
 * \snippet quick_start.c slcd_data
 *
 * Add to the main application source file, outside of any functions:
 * \snippet quick_start.c slcd_var

 * Copy-paste the following setup code to your user application:
 * \snippet quick_start.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet quick_start.c setup_init
 *
 * \subsection asfdoc_sam0_slcd_basic_use_case_setup_flow Workflow
 * -# Define charactor map data.
 *    \snippet quick_start.c slcd_data
 *
 * -# Create related module variable and software instance structure.
 *    \snippet quick_start.c slcd_var
 *
 * -# Configure, initialize, and enable slcd module.
 *  -# Configuration slcd struct, which can be filled out to
 *     adjust the configuration of a physical slcd peripheral.
 *     \snippet quick_start.c setup_config
 *  -# Enable the slcd module.
 *     \snippet quick_start.c module_enable
 *
 *
 * \section asfdoc_sam0_slcd_basic_use_case_main Use Case
 *
 * \subsection asfdoc_sam0_slcd_basic_use_case_main_code Code
 * Copy-paste the following code to your user application:
 * \snippet quick_start.c  use_cases
 *
 * \subsection asfdoc_sam0_slcd_basic_use_case_main_flow Workflow
 * -# Display all case.
 *    \snippet quick_start.c use_cases_1
 * -# Display icon.
 *    \snippet quick_start.c use_cases_2
 * -# Character map case.
 *    \snippet quick_start.c use_cases_3
 * -# Didital map case.
 *    \snippet quick_start.c use_cases_4
 * -# SLCD blinking.
 *    \snippet quick_start.c use_cases_5
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
