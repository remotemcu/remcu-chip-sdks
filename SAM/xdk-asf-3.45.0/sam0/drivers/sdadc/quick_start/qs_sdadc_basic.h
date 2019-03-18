/**
 * \file
 *
 * \brief SAM SDADC Quick Start
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
 * \page asfdoc_sam0_sdadc_basic_use_case Quick Start Guide for SDADC - Basic
 *
 * In this use case, the SDADC will be configured with the following settings:
 *  - GCLK generator 0 (GCLK main) clock source
 *  - Internal bandgap reference 1V
 *  - Div 2 clock prescaler
 *  - Over Sampling Ratio is 64
 *  - Skip 2 samples
 *  - MUX input on SDADC AIN1
 *  - All events (input and generation) disabled
 *  - Free running disabled
 *  - Run in standby disabled
 *  - On command disabled
 *  - Disable all positive input in sequence
 *  - Window monitor disabled
 *  - No gain/offset/shift correction
 *
 * \section asfdoc_sam0_sdadc_basic_use_case_setup Setup
 *
 * \subsection asfdoc_sam0_sdadc_basic_use_case_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_sam0_sdadc_basic_use_case_code Code
 * Add to the main application source file, outside of any functions:
 * \snippet qs_sdadc_basic.c module_inst
 *
 * Copy-paste the following setup code to your user application:
 * \snippet qs_sdadc_basic.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_sdadc_basic.c setup_init
 *
 * \subsection asfdoc_sam0_sdadc_basic_use_case_workflow Workflow
 * -# Create a module software instance structure for the SDADC module to store
 *    the SDADC driver state while it is in use.
 *    \snippet qs_sdadc_basic.c module_inst
 *    \note This should never go out of scope as long as the module is in use.
 *          In most cases, this should be global.
 *
 * -# Configure the SDADC module.
 *  - Create a SDADC module configuration struct, which can be filled out to
 *     adjust the configuration of a physical SDADC peripheral.
 *     \snippet qs_sdadc_basic.c setup_config
 *  - Initialize the SDADC configuration struct with the module's default values.
 *     \snippet qs_sdadc_basic.c setup_config_defaults
 *     \note This should always be performed before using the configuration
 *           struct to ensure that all values are initialized to known default
 *           settings.
 *
 *  - Set SDADC configurations.
 *     \snippet qs_sdadc_basic.c setup_set_config
 *  - Enable the SDADC module so that conversions can be made.
 *     \snippet qs_sdadc_basic.c setup_enable
 *
 * \section asfdoc_sam0_sdadc_basic_use_case_use Use Case
 *
 * \subsection asfdoc_sam0_sdadc_basic_use_case_use_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_sdadc_basic.c main
 *
 * \subsection asfdoc_sam0_sdadc_basic_use_case_use_workflow Workflow
 *  -# Start conversion.
 *  \snippet qs_sdadc_basic.c start_conv
 *  -# Wait until conversion is done and read result.
 *  \snippet qs_sdadc_basic.c get_res
 *  -# Enter an infinite loop once the conversion is complete.
 *  \snippet qs_sdadc_basic.c inf_loop
 */
