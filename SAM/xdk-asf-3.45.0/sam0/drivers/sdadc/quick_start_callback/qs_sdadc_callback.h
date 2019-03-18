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
 * \page asfdoc_sam0_sdadc_basic_use_case_callback Quick Start Guide for SDADC - Callback
 *
 * In this use case, the SDADC will convert 128 samples using interrupt driven conversion.
 * When all samples have been sampled, a callback will be called that signals the main
 * application that conversion is compete.
 *
 * The SDADC will be set up as follows:
 *  - GCLK generator 0 (GCLK main) clock source
 *  - Internal bandgap reference 1V
 *  - Div 2 clock prescaler
 *  - Over Sampling Ratio is 1024
 *  - Skip 2 samples
 *  - MUX input on SDADC AIN2
 *  - All events (input and generation) disabled
 *  - Free running disabled
 *  - Run in standby disabled
 *  - On command disabled
 *  - Disable all positive input in sequence
 *  - Window monitor disabled
 *  - No gain/offset/shift correction
 *
 * \section asfdoc_sam0_sdadc_callback_basic_use_case_callback_setup Setup
 *
 * \subsection asfdoc_sam0_sdadc_callback_basic_use_case_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_sam0_sdadc_callback_basic_use_case_callback_code Code
 * Add to the main application source file, outside of any functions:
 * \snippet qs_sdadc_callback.c module_inst
 * \snippet qs_sdadc_callback.c result_buffer
 *
 * Callback function:
 * \snippet qs_sdadc_callback.c job_complete_callback
 *
 * Copy-paste the following setup code to your user application:
 * \snippet qs_sdadc_callback.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_sdadc_callback.c setup_init
 *
 * \subsection asfdoc_sam0_sdadc_basic_use_case_callback_workflow Workflow
 * -# Create a module software instance structure for the SDADC module to store
 *    the SDADC driver state while it is in use.
 *    \snippet qs_sdadc_callback.c module_inst
 *    \note This should never go out of scope as long as the module is in use.
 *          In most cases, this should be global.
 *
 * -# Create a buffer for the SDADC samples to be stored in by the driver
 *    asynchronously.
 *    \snippet qs_sdadc_callback.c result_buffer
 * -# Create a callback function that will be called each time the SDADC completes
 *    an asynchronous read job.
 * \snippet qs_sdadc_callback.c job_complete_callback
 * -# Configure the SDADC module.
 *  - Create a SDADC module configuration struct, which can be filled out to
 *     adjust the configuration of a physical SDADC peripheral.
 *     \snippet qs_sdadc_callback.c setup_config
 *  - Initialize the SDADC configuration struct with the module's default values.
 *     \snippet qs_sdadc_callback.c setup_config_defaults
 *     \note This should always be performed before using the configuration
 *           struct to ensure that all values are initialized to known default
 *           settings.
 *
 *  - Change the SDADC module configuration to suit the application.
 *     \snippet qs_sdadc_callback.c setup_modify_conf
 *  - Set SDADC configurations.
 *     \snippet qs_sdadc_callback.c setup_set_config
 *  - Enable the SDADC module so that conversions can be made.
 *     \snippet qs_sdadc_callback.c setup_enable
 * -# Register and enable the SDADC read buffer complete callback handler.
 *  - Register the user-provided read buffer complete callback function with
 *     the driver, so that it will be run when an asynchronous buffer read job
 *     completes.
 *     \snippet qs_sdadc_callback.c setup_register_callback
 *  - Enable the read buffer complete callback so that it will generate
 *     callbacks.
 *     \snippet qs_sdadc_callback.c setup_enable_callback
 *
 * \section asfdoc_sam0_sdadc_basic_use_case_callback_use Use Case
 *
 * \subsection asfdoc_sam0_sdadc_basic_use_case_callback_use_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_sdadc_callback.c main
 *
 * \subsection asfdoc_sam0_sdadc_basic_use_case_callback_use_workflow Workflow
 *  - Enable global interrupts, so that callbacks can be generated by the
 *     driver.
 *     \snippet qs_sdadc_callback.c enable_global_interrupts
 *  - Start an asynchronous SDADC conversion, to store SDADC samples into the
 *     global buffer and generate a callback when complete.
 *     \snippet qs_sdadc_callback.c start_sdadc_job
 *  - Wait until the asynchronous conversion is complete.
 *     \snippet qs_sdadc_callback.c job_complete_poll
 *  - Enter an infinite loop once the conversion is complete.
 *     \snippet qs_sdadc_callback.c inf_loop
 */
