/**
 * \file
 *
 * \brief SAM DAC Quick Start
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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
 * \page asfdoc_sam0_dac_basic_use_case Quick Start Guide for DAC - Basic
 *
 * In this use case, the DAC will be configured with the following settings:
 * - Analog V<SUB>CC</SUB> as reference
 * - Internal output disabled
 * - Drive the DAC output to the V<sub>OUT</sub> pin
 * - Right adjust data
 * - The output buffer is disabled when the chip enters STANDBY sleep mode
 *
 * \section asfdoc_sam0_dac_basic_use_case_setup Quick Start
 *
 * \subsection asfdoc_sam0_dac_basic_use_case_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_sam0_dac_basic_use_case_setup_code Code
 * Add to the main application source file, outside of any functions:
 * \snippet qs_dac_basic.c module_inst
 *
 * Copy-paste the following setup code to your user application:
 * \snippet qs_dac_basic.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_dac_basic.c setup_init
 *
 * \subsection asfdoc_sam0_dac_basic_use_case_setup_flow Workflow
 * -# Create a module software instance structure for the DAC module to store
 *    the DAC driver state while in use.
 *    \snippet qs_dac_basic.c module_inst
 *    \note This should never go out of scope as long as the module is in use.
 *          In most cases, this should be global.
 *
 * -# Configure the DAC module.
 *  -# Create a DAC module configuration struct, which can be filled out to
 *     adjust the configuration of a physical DAC peripheral.
 *     \snippet qs_dac_basic.c setup_config
 *  -# Initialize the DAC configuration struct with the module's default values.
 *     \snippet qs_dac_basic.c setup_config_defaults
 *     \note This should always be performed before using the configuration
 *           struct to ensure that all values are initialized to known default
 *           settings.
 *
 * -# Configure the DAC channel.
 *  -# Create a DAC channel configuration struct, which can be filled out to
 *     adjust the configuration of a physical DAC output channel.
 *     \snippet qs_dac_basic.c setup_ch_config
 *  -# Initialize the DAC channel configuration struct with the module's default
 *     values.
 *     \snippet qs_dac_basic.c setup_ch_config_defaults
 *     \note This should always be performed before using the configuration
 *           struct to ensure that all values are initialized to known default
 *           settings.
 *
 *  -# Configure the DAC channel with the desired channel settings.
 *     \snippet qs_dac_basic.c setup_ch_set_config
 *  -# Enable the DAC channel so that it can output a voltage.
 *     \snippet qs_dac_basic.c setup_ch_enable
 *
 * -# Enable the DAC module.
 *    \snippet qs_dac_basic.c setup_enable
 *
 * \section asfdoc_sam0_dac_basic_use_case_main Use Case
 *
 * \subsection asfdoc_sam0_dac_basic_use_case_main_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_dac_basic.c main
 *
 * \subsection asfdoc_sam0_dac_basic_use_case_main_flow Workflow
 * -# Create a temporary variable to track the current DAC output value.
 *    \snippet qs_dac_basic.c main_output_var
 * -# Enter an infinite loop to continuously output new conversion values to
 *    the DAC.
 *    \snippet qs_dac_basic.c main_loop
 * -# Write the next conversion value to the DAC, so that it will be output on
 *    the device's DAC analog output pin.
 *    \snippet qs_dac_basic.c main_write
 * -# Increment and wrap the DAC output conversion value, so that a ramp pattern
 *    will be generated.
 *    \snippet qs_dac_basic.c main_inc_val
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
