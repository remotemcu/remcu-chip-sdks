/**
 * \file
 *
 * \brief SAM DAC Callback Quick Start
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
 * \page asfdoc_sam0_dac_basic_use_case_callback Quick Start Guide for DAC - Callback
 *
 * In this use case, the DAC will convert 16 samples using interrupt driven conversion.
 * When all samples have been sampled, a callback will be called that signals the main
 * application that conversion is compete.
 *
 * The DAC will be set up as follows:
 * - Analog V<SUB>CC</SUB> as reference
 * - Internal output disabled
 * - Drive the DAC output to the V<sub>OUT</sub> pin
 * - Right adjust data
 * - The output buffer is disabled when the chip enters STANDBY sleep mode
 * - DAC conversion is started with RTC overflow event
 *
 * \section asfdoc_sam0_dac_callback_basic_use_case_callback_setup Setup
 *
 * \subsection asfdoc_sam0_dac_callback_basic_use_case_prereq Prerequisites
 * There are no special setup requirements for this use case.
 *
 * \subsection asfdoc_sam0_dac_callback_basic_use_case_callback_code Code
 * Add to the main application source file, outside of any functions:
 * \snippet qs_dac_callback.c transfer_length
 * \snippet qs_dac_callback.c dac_module_inst
 * \snippet qs_dac_callback.c rtc_module_inst
 * \snippet qs_dac_callback.c event_res
 * \snippet qs_dac_callback.c transfer_done_flag
 * \snippet qs_dac_callback.c dac_data
 *
 * Callback function:
 * \snippet qs_dac_callback.c job_complete_callback
 *
 * Copy-paste the following setup code to your user application:
 * \snippet qs_dac_callback.c setup_rtc
 * \snippet qs_dac_callback.c setup_dac
 * \snippet qs_dac_callback.c setup_dac_channel
 *
 * Define a  data length variables and add to user application (typically the start of \c main()):
 * \snippet qs_dac_callback.c data_length_var
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_dac_callback.c setup_init
 *
 * \subsection asfdoc_sam0_dac_basic_use_case_callback_workflow Workflow
 * -# Create a module software instance structure for the DAC module to store
 *    the DAC driver state while in use.
 *    \snippet qs_dac_callback.c dac_module_inst
 *    \note This should never go out of scope as long as the module is in use.
 *          In most cases, this should be global.
 *
 * -# RTC module is used as the event trigger for DAC in this case, create a module
 *    software instance structure for the RTC module to store the RTC driver state.
 *    \snippet qs_dac_callback.c rtc_module_inst
 *    \note This should never go out of scope as long as the module is in use.
 *          In most cases, this should be global.
 *
 * -# Create a buffer for the DAC samples to be converted by the driver.
 *    \snippet qs_dac_callback.c dac_data
 * -# Create a callback function that will be called when DAC completes convert job.
 *    \snippet qs_dac_callback.c job_complete_callback
 * -# Configure the DAC module.
 *  -# Create a DAC module configuration struct, which can be filled out to
 *     adjust the configuration of a physical DAC peripheral.
 *     \snippet qs_dac_callback.c setup_dac_config
 *  -# Initialize the DAC configuration struct with the module's default values.
 *     \snippet qs_dac_callback.c setup_dac_config_default
 *     \note This should always be performed before using the configuration
 *           struct to ensure that all values are initialized to known default
 *           settings.
 *
 *  -# Configure the DAC module with starting conversion on event.
 *     \snippet qs_dac_callback.c setup_dac_start_on_event
 *  -# Initialize the DAC module.
 *     \snippet qs_dac_callback.c setup_dac_instance
 *  -# Enable DAC start on conversion mode.
 *     \snippet qs_dac_callback.c setup_dac_on_event_start_conversion
 *  -# Enable DAC event.
 *     \snippet qs_dac_callback.c enable_dac_event
 *
 * -# Configure the DAC channel.
 *  -# Create a DAC channel configuration struct, which can be filled out to
 *     adjust the configuration of a physical DAC output channel.
 *     \snippet qs_dac_callback.c setup_dac_chan_config
 *  -# Initialize the DAC channel configuration struct with the module's default
 *     values.
 *     \snippet qs_dac_callback.c setup_dac_chan_config_default
 *     \note This should always be performed before using the configuration
 *           struct to ensure that all values are initialized to known default
 *           settings.
 *
 *  -# Configure the DAC channel with the desired channel settings.
 *     \snippet qs_dac_callback.c set_dac_chan_config
 *  -# Enable the DAC channel so that it can output a voltage.
 *     \snippet qs_dac_callback.c enable_dac_channel
 *
 * -# Enable DAC module.
 *    \snippet qs_dac_callback.c enable_dac
 *
 * -# Configure the RTC module.
 *  -# Create an RTC module event struct, which can be filled out to
 *     adjust the configuration of a physical RTC peripheral.
 *     \snippet qs_dac_callback.c setup_rtc_event
 *  -# Create an RTC module configuration struct, which can be filled out to
 *     adjust the configuration of a physical RTC peripheral.
 *     \snippet qs_dac_callback.c setup_rtc_config
 *  -# Initialize the RTC configuration struct with the module's default values.
 *     \snippet qs_dac_callback.c setup_rtc_config_defaults
 *     \note This should always be performed before using the configuration
 *           struct to ensure that all values are initialized to known default
 *           settings.
 *
 *  -# Change the RTC module configuration to suit the application.
 *     \snippet qs_dac_callback.c setup_rtc_modify_conf
 *  -# Initialize the RTC module.
 *     \snippet qs_dac_callback.c init_rtc_count
 *
 *  -# Configure the RTC module with overflow event.
 *     \snippet qs_dac_callback.c setup_rtc_overflow_event
 *  -# Enable RTC module overflow event.
 *     \snippet qs_dac_callback.c enable_rtc_overflow_event
 *  -# Enable RTC module.
 *     \snippet qs_dac_callback.c enable_rtc

 * -# Configure the Event resource.
 *  -# Create an event resource config struct, which can be filled out to
 *     adjust the configuration of a physical event peripheral.
 *     \snippet qs_dac_callback.c event_config
 *  -# Initialize the event configuration struct with the module's default values.
 *     \snippet qs_dac_callback.c get_event_default
 *     \note This should always be performed before using the configuration
 *           struct to ensure that all values are initialized to known default
 *           settings.
 *
 *  -# Change the event module configuration to suit the application.
 *     \snippet qs_dac_callback.c set_event_modify_conf
 *  -# Allocate the event resource.
 *     \snippet qs_dac_callback.c allocate_event_resource
 *  -# Attach the event resource with user DAC start.
 *     \snippet qs_dac_callback.c attach_event_to_dac
 *
 * -# Register and enable the DAC Write Buffer Complete callback handler.
 *  -# Register the user-provided Write Buffer Complete callback function with
 *     the driver, so that it will be run when an asynchronous buffer write job
 *     completes.
 *     \snippet qs_dac_callback.c register_dac_callback
 *  -# Enable the Read Buffer Complete callback so that it will generate
 *     callbacks.
 *     \snippet qs_dac_callback.c enable_dac_callback
 *
 * \section asfdoc_sam0_dac_basic_use_case_callback_use Use Case
 *
 * \subsection asfdoc_sam0_dac_basic_use_case_callback_use_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_dac_callback.c main_start
 *
 * \subsection asfdoc_sam0_dac_basic_use_case_callback_use_workflow Workflow
 *  -# Start a DAC conversion and generate a callback when complete.
 *  \snippet qs_dac_callback.c main_write
 *  -# Wait until the conversion is complete.
 *  \snippet qs_dac_callback.c main_check_transfer_done
 *  -# Enter an infinite loop once the conversion is complete.
 *  \snippet qs_dac_callback.c main_loop
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

