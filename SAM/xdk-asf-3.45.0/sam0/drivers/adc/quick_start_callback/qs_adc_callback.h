/**
 * \file
 *
 * \brief SAM ADC Quick Start
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

/**
 * \page asfdoc_sam0_adc_basic_use_case_callback Quick Start Guide for ADC - Callback
 *
 * In this use case, the ADC will convert 128 samples using interrupt driven conversion.
 * When all samples have been sampled, a callback will be called that signals the main
 * application that conversion is complete.
 *
 * The ADC will be set up as follows:
 * - V<SUB>CC</SUB> /2 as reference
 * - Div 8 clock prescaler
 * - 12-bit resolution
 * - Window monitor disabled
 * - 1/2 gain
 * - Positive input on ADC PIN 0
 * - Negative input to GND (single ended)
 * - Averaging disabled
 * - Oversampling disabled
 * - Right adjust data
 * - Single-ended mode
 * - Free running disabled
 * - All events (input and generation) disabled
 * - Sleep operation disabled
 * - No reference compensation
 * - No gain/offset correction
 * - No added sampling time
 * - Pin scan mode disabled
 *
 * \section asfdoc_sam0_adc_callback_basic_use_case_callback_setup Setup
 *
 * \subsection asfdoc_sam0_adc_callback_basic_use_case_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_sam0_adc_callback_basic_use_case_callback_code Code
 * Add to the main application source file, outside of any functions:
 * \snippet qs_adc_callback.c module_inst
 * \snippet qs_adc_callback.c result_buffer
 *
 * Callback function:
 * \snippet qs_adc_callback.c job_complete_callback
 *
 * Copy-paste the following setup code to your user application:
 * \snippet qs_adc_callback.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_adc_callback.c setup_init
 *
 * \subsection asfdoc_sam0_adc_basic_use_case_callback_workflow Workflow
 * -# Create a module software instance structure for the ADC module to store
 *    the ADC driver state while in use.
 *    \snippet qs_adc_callback.c module_inst
 *    \note This should never go out of scope as long as the module is in use.
 *          In most cases, this should be global.
 *
 * -# Create a buffer for the ADC samples to be stored in by the driver
 *    asynchronously.
 *    \snippet qs_adc_callback.c result_buffer
 * -# Create a callback function that will be called each time the ADC completes
 *    an asynchronous read job.
 * \snippet qs_adc_callback.c job_complete_callback
 * -# Configure the ADC module.
 *  -# Create an ADC module configuration struct, which can be filled out to
 *     adjust the configuration of a physical ADC peripheral.
 *     \snippet qs_adc_callback.c setup_config
 *  -# Initialize the ADC configuration struct with the module's default values.
 *     \snippet qs_adc_callback.c setup_config_defaults
 *     \note This should always be performed before using the configuration
 *           struct to ensure that all values are initialized to known default
 *           settings.
 *
 *  -# Change the ADC module configuration to suit the application.
 *     \snippet qs_adc_callback.c setup_modify_conf
 *  -# Set ADC configurations.
 *     \snippet qs_adc_callback.c setup_set_config
 *  -# Enable the ADC module so that conversions can be made.
 *     \snippet qs_adc_callback.c setup_enable
 * -# Register and enable the ADC Read Buffer Complete callback handler.
 *  -# Register the user-provided Read Buffer Complete callback function with
 *     the driver, so that it will be run when an asynchronous buffer read job
 *     completes.
 *     \snippet qs_adc_callback.c setup_register_callback
 *  -# Enable the Read Buffer Complete callback so that it will generate
 *     callbacks.
 *     \snippet qs_adc_callback.c setup_enable_callback
 *
 * \section asfdoc_sam0_adc_basic_use_case_callback_use Use Case
 *
 * \subsection asfdoc_sam0_adc_basic_use_case_callback_use_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_adc_callback.c main
 *
 * \subsection asfdoc_sam0_adc_basic_use_case_callback_use_workflow Workflow
 *  -# Enable global interrupts, so that callbacks can be generated by the
 *     driver.
 *     \snippet qs_adc_callback.c enable_global_interrupts
 *  -# Start an asynchronous ADC conversion, to store ADC samples into the
 *     global buffer and generate a callback when complete.
 *     \snippet qs_adc_callback.c start_adc_job
 *  -# Wait until the asynchronous conversion is complete.
 *     \snippet qs_adc_callback.c job_complete_poll
 *  -# Enter an infinite loop once the conversion is complete.
 *     \snippet qs_adc_callback.c inf_loop
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
