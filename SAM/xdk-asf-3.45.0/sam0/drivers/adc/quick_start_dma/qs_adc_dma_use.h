/**
 * \file
 *
 * \brief SAM D21/D11/L21/DA1/C21/HA1G16A Quick Start Guide for Using ADC/DAC driver with DMA
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
 * \page asfdoc_sam0_adc_dma_use_case Quick Start Guide for Using DMA with ADC/DAC
 *
 * The supported board list:
 *    - SAM D21 Xplained Pro
 *    - SAM D11 Xplained Pro
 *    - SAM L21 Xplained Pro
 *    - SAM DA1 Xplained Pro
 *    - SAM C21 Xplained Pro
 *    - SAM HA1G16A Xplained Pro
 *
 * This quick start will convert an analog input signal from AIN4 and output
 * the converted value to DAC on PA2. The data between ADC and DAC with be
 * transferred through DMA instead of a CPU intervene.
 *
 * The ADC will be configured with the following settings:
 * - 1/2 VDDANA
 * - Div 16 clock prescaler
 * - 10-bit resolution
 * - Window monitor disabled
 * - No gain
 * - Positive input on ADC AIN4
 * - Averaging disabled
 * - Oversampling disabled
 * - Right adjust data
 * - Single-ended mode
 * - Free running enable
 * - All events (input and generation) disabled
 * - Sleep operation disabled
 * - No reference compensation
 * - No gain/offset correction
 * - No added sampling time
 * - Pin scan mode disabled
 *
 * The DAC will be configured with the following settings:
 * - Analog V<SUB>CC</SUB> as reference
 * - Internal output disabled
 * - Drive the DAC output to PA2
 * - Right adjust data
 * - The output buffer is disabled when the chip enters STANDBY sleep mode
 *
 * The DMA will be configured with the following settings:
 * - Move data from peripheral to peripheral
 * - Using ADC result ready trigger
 * - Using DMA priority level 0
 * - Beat transfer will be triggered on each trigger
 * - Loopback descriptor for DAC conversion
 *
 * \section asfdoc_sam0_adc_dma_use_case_setup Setup
 *
 * \subsection asfdoc_sam0_adc_dma_use_case_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_sam0_adc_dma_use_case_setup_code Code
 * Add to the main application source file, outside of any functions:
 * \snippet qs_adc_dma_use.c dac_module_inst
 * \snippet qs_adc_dma_use.c adc_module_inst
 * \snippet qs_adc_dma_use.c dma_resource
 * \snippet qs_adc_dma_use.c transfer_descriptor
 *
 * Copy-paste the following setup code to your user application:
 * \snippet qs_adc_dma_use.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_adc_dma_use.c setup_init
 *
 * \subsection asfdoc_sam0_adc_dma_use_case_setup_flow Workflow
 *
 * \subsubsection asfdoc_sam0_adc_dma_use_case_setup_flow_adc Configure the ADC
 * -# Create a module software instance structure for the ADC module to store
 *    the ADC driver state while it is in use.
 *    \snippet qs_adc_dma_use.c adc_module_inst
 *    \note This should never go out of scope as long as the module is in use.
 *          In most cases, this should be global.
 *
 * -# Configure the ADC module.
 *  -# Create an ADC module configuration struct, which can be filled out to
 *     adjust the configuration of a physical ADC peripheral.
 *     \snippet qs_adc_dma_use.c setup_adc_config
 *  -# Initialize the ADC configuration struct with the module's default values.
 *     \snippet qs_adc_dma_use.c setup_adc_config_defaults
 *     \note This should always be performed before using the configuration
 *           struct to ensure that all values are initialized to known default
 *           settings.
 *
 *  -# Set extra configurations.
 *     \snippet qs_adc_dma_use.c setup_adc_config_extra
 *  -# Set ADC configurations.
 *     \snippet qs_adc_dma_use.c setup_adc_set_config

 *  -# Enable the ADC module so that conversions can be made.
 *     \snippet qs_adc_dma_use.c setup_adc_enable
 *
 * \subsubsection asfdoc_sam0_adc_dma_use_case_setup_flow_dac Configure the DAC
 * -# Create a module software instance structure for the DAC module to store
 *    the DAC driver state while it is in use.
 *    \snippet qs_adc_dma_use.c dac_module_inst
 *    \note This should never go out of scope as long as the module is in use.
 *          In most cases, this should be global.
 *
 * -# Configure the DAC module.
 *  -# Create a DAC module configuration struct, which can be filled out to
 *     adjust the configuration of a physical DAC peripheral.
 *     \snippet qs_adc_dma_use.c setup_dac_config
 *  -# Initialize the DAC configuration struct with the module's default values.
 *     \snippet qs_adc_dma_use.c setup_dac_config_defaults
 *     \note This should always be performed before using the configuration
 *           struct to ensure that all values are initialized to known default
 *           settings.
 *
 *  -# Set extra DAC configurations.
 *     \snippet qs_adc_dma_use.c setup_dac_config_extra
 *  -# Set DAC configurations to DAC instance.
 *     \snippet qs_adc_dma_use.c setup_dac_set_config
 *  -# Enable the DAC module so that channels can be configured.
 *     \snippet qs_adc_dma_use.c setup_dac_enable
 * -# Configure the DAC channel.
 *  -# Create a DAC channel configuration struct, which can be filled out to
 *     adjust the configuration of a physical DAC output channel.
 *     \snippet qs_adc_dma_use.c setup_dac_ch_config
 *  -# Initialize the DAC channel configuration struct with the module's default
 *     values.
 *     \snippet qs_adc_dma_use.c setup_dac_ch_config_defaults
 *     \note This should always be performed before using the configuration
 *           struct to ensure that all values are initialized to known default
 *           settings.
 *
 *  -# Configure the DAC channel with the desired channel settings.
 *     \snippet qs_adc_dma_use.c setup_dac_ch_set_config
 *  -# Enable the DAC channel so that it can output a voltage.
 *     \snippet qs_adc_dma_use.c setup_dac_ch_enable
 *
 * \subsubsection asfdoc_sam0_adc_dma_use_case_setup_flow_dma Configure the DMA
 * -# Create a DMA resource configuration structure, which can be filled out to
 *    adjust the configuration of a single DMA transfer.
 *  \snippet qs_adc_dma_use.c setup_dma_config
 *
 * -# Initialize the DMA resource configuration struct with the module's
 *    default values.
 *    \snippet qs_adc_dma_use.c setup_dma_set_config_default
 *    \note This should always be performed before using the configuration
 *          struct to ensure that all values are initialized to known default
 *          settings.
 *
 * -# Set extra configurations for the DMA resource. ADC_DMAC_ID_RESRDY trigger
 *      causes a beat transfer in this example.
 *    \snippet qs_adc_dma_use.c setup_dma_set_config_extra
 *
 * -# Allocate a DMA resource with the configurations.
 *    \snippet qs_adc_dma_use.c allocate_dma_resource
 *
 * -# Create a DMA transfer descriptor configuration structure, which can be
 *    filled out to adjust the configuration of a single DMA transfer.
 *    \snippet qs_adc_dma_use.c setup_dma_desc_config
 *
 * -# Initialize the DMA transfer descriptor configuration struct with the module's
 *    default values.
 *    \snippet qs_adc_dma_use.c setup_dma_desc_config_set_default
 *    \note This should always be performed before using the configuration
 *          struct to ensure that all values are initialized to known default
 *          settings.
 *
 * -# Set the specific parameters for a DMA transfer with transfer size, source
 *    address, and destination address.
 *    \snippet qs_adc_dma_use.c setup_dma_desc_config_set_extra
 *
 * -# Create the DMA transfer descriptor.
 *    \snippet qs_adc_dma_use.c setup_dma_desc_config_create
 *
 * -# Add DMA descriptor to DMA resource.
 *    \snippet qs_adc_dma_use.c add_descriptor_to_resource
 *
 * \section asfdoc_sam0_adc_dma_use_case_main Use Case
 *
 * \subsection asfdoc_sam0_adc_dma_use_case_main_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_adc_dma_use.c main
 *
 * \subsection asfdoc_sam0_adc_dma_use_case_main_flow Workflow
 * -# Start ADC conversion.
 *  \snippet qs_adc_dma_use.c start_adc_conversion
 *
 * -# Start the transfer job.
 *  \snippet qs_adc_dma_use.c start_transfer
 *
 * -# Enter endless loop.
 *  \snippet qs_adc_dma_use.c endless_loop
 */

/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

