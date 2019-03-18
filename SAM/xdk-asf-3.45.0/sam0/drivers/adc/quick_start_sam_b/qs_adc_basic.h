/**
 * \file
 *
 * \brief ADC Quick Start for SAMB11
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
 * \page asfdoc_samb_adc_basic_use_case Quick Start Guide for ADC - Basic
 *
 * In this use case, the ADC will be configured with the following settings:
 *  \li VBATT/2 as voltage reference
 *  \li Internal reference voltage level 0.7V
 *  \li On GPIO_MS1 input channel
 *  \li Select one external input channels
 *  \li Input channel time multiplexing selection mode
 *  \li Comparator biasing current selection
 *  \li No invert ADC clock
 *  \li Fractional part for the clock divider is 0
 *  \li Integer part for the clock divider is 0x12
 *
 * \section asfdoc_samb_adc_basic_use_case_setup Setup
 *
 * \subsection asfdoc_samb_adc_basic_use_case_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_samb_adc_basic_use_case_code Code
 *
 * Copy-paste the following setup code to your user application:
 * \snippet qs_adc_basic.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_adc_basic.c setup_init
 *
 * \subsection asfdoc_samb_adc_basic_use_case_workflow Workflow
 *
 * -# Configure the ADC module.
 *  -# Create an ADC module configuration struct, which can be filled out to
 *     adjust the configuration of a physical ADC peripheral.
 *     \snippet qs_adc_basic.c setup_config
 *  -# Initialize the ADC configuration struct with the module's default values.
 *     \snippet qs_adc_basic.c setup_config_defaults
 *     \note This should always be performed before using the configuration
 *           struct to ensure that all values are initialized to known default
 *           settings.
 *  -# Change input channel selection.
 *     \snippet qs_adc_basic.c setup_config_ch
 *
 *  -# Set ADC configurations.
 *     \snippet qs_adc_basic.c setup_set_config
 *  -# Enable the ADC module so that conversions can be made.
 *     \snippet qs_adc_basic.c setup_enable
 *
 * \section asfdoc_samb_adc_basic_use_case_use Use Case
 *
 * \subsection asfdoc_samb_adc_basic_use_case_use_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_adc_basic.c main
 *
 * \subsection asfdoc_samb_adc_basic_use_case_use_workflow Workflow
 *  -# Wait until conversion is done and read result.
 *  \snippet qs_adc_basic.c get_res
 *  -# Enter an infinite loop once the conversion is complete.
 *  \snippet qs_adc_basic.c inf_loop
 */

