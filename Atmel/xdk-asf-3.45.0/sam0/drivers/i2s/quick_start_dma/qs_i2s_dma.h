/**
 * \file
 *
 * \brief SAM I2S - Inter-IC Sound Controller Driver Quick Start with DMA
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
 * \page asfdoc_sam0_i2s_dma_use_case Quick Start Guide for I2S - DMA
 *
 * In this use case, the I<SUP>2</SUP>S will be used to generate Master Clock (MCK), Serial
 * Clock (SCK), Frame Sync (FS), and Serial Data (SD) signals.
 *
 * Here MCK is set to the half of processor clock. SCK is set to a quarter of
 * the frequency of processor. FS generates half-half square wave for left and
 * right audio channel data. The output serial data of channels toggle from two
 * values to generate square wave, if codec or DAC is connected.
 *
 * The output SD is also fed back to another I<SUP>2</SUP>S channel by internal loop back,
 * and transfer to values buffer by DMA.
 *
 * The I<SUP>2</SUP>S module will be setup as follows:
 *
 * - GCLK generator 0 (GCLK main) clock source
 * - MCK, SCK, and FS clocks outputs are enabled
 * - MCK output divider set to 2
 * - SCK generation divider set to 4
 * - Each frame will contain two 32-bit slots
 * - Data will be left adjusted and start transmit without delay
 *
 * \section asfdoc_sam0_i2s_dma_use_case_setup Quick Start
 *
 * \subsection asfdoc_sam0_i2s_dma_use_case_prereq Prerequisites
 * There are no prerequisites for this use case.
 *
 * \subsection asfdoc_sam0_i2s_dma_use_case_setup_code Code
 *
 * Add to the main application source file, before any functions:
 * \snippet conf_i2s_quick_start_dma.h definition_i2s
 * \snippet conf_i2s_quick_start_dma.h definition_dma_receive_trigger
 * \snippet conf_i2s_quick_start_dma.h definition_dma_transmit_trigger
 *
 * Add to the main application source file, outside of any functions:
 * \snippet qs_i2s_dma.c module_inst
 * \snippet qs_i2s_dma.c rx_variables
 * \snippet qs_i2s_dma.c tx_variables
 *
 * Copy-paste the following setup code to your user application:
 * \snippet qs_i2s_dma.c config_dma_for_rx
 * \snippet qs_i2s_dma.c config_dma_for_tx
 * \snippet qs_i2s_dma.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_i2s_dma.c setup_init
 *
 * \subsection asfdoc_sam0_i2s_dma_use_case_setup_flow Workflow
 * \subsubsection asfdoc_sam0_i2s_dma_use_case_setup_flow_dma_rx Configure the DMAC module to obtain received value from I2S Serializer 1.
 * -# Allocate and configure the DMA resource
 *  -# Create a DMA resource instance.
 *     \snippet qs_i2s_dma.c rx_dma_resource
 *     \note This should never go out of scope as long as the resource is in
 *           use. In most cases, this should be global.
 *
 *  -# Create a DMA resource configuration struct.
 *     \snippet qs_i2s_dma.c dma_setup_1
 *  -# Initialize the DMA resource configuration struct with default values.
 *     \snippet qs_i2s_dma.c dma_setup_2
 *     \note This should always be performed before using the configuration
 *           struct to ensure that all values are initialized to known default
 *           settings.
 *
 *  -# Adjust the DMA resource configurations.
 *     \snippet qs_i2s_dma.c dma_setup_3
 *  -# Allocate a DMA resource with the configurations.
 *     \snippet qs_i2s_dma.c dma_setup_4
 * -# Prepare DMA transfer descriptor
 *  -# Create a DMA transfer descriptor.
 *     \snippet qs_i2s_dma.c rx_dma_descriptor
 *     \note When multiple descriptors are linked. The linked item should
 *           never go out of scope before it's loaded (to DMA Write-Back
 *           memory section). In most cases, if more than one descriptors are
 *           used, they should be global except the very first one.
 *
 *  -# Create a DMA transfer descriptor configuration struct, which can be
 *     filled out to adjust the configuration of a single DMA transfer.
 *     \snippet qs_i2s_dma.c dma_setup_5
 *  -# Initialize the DMA transfer descriptor configuration struct with
 *     default values.
 *     \snippet qs_i2s_dma.c dma_setup_6
 *     \note This should always be performed before using the configuration
 *           struct to ensure that all values are initialized to known default
 *           settings.
 *
 *  -# Adjust the DMA transfer descriptor configurations.
 *     \snippet qs_i2s_dma.c dma_setup_7
 *  -# Create the DMA transfer descriptor with configuration.
 *     \snippet qs_i2s_dma.c dma_setup_8
 *  -# Adjust the DMA transfer descriptor if multiple DMA transfer will be
 *      performed.
 *     \snippet qs_i2s_dma.c dma_setup_9
 * -# Start DMA transfer job with prepared descriptor
 *  -# Add the DMA transfer descriptor to the allocated DMA resource.
 *     \snippet qs_i2s_dma.c dma_setup_10
 *  -# Start the DMA transfer job with the allocated DMA resource and
 *     transfer descriptor.
 *     \snippet qs_i2s_dma.c dma_setup_11
 * \subsubsection asfdoc_sam0_i2s_dma_use_case_setup_flow_dma_tx Configure the DMAC module to transmit data through I2S serializer 0.
 * The flow is similar to last DMA configure step for receive.
 *  -# Allocate and configure the DMA resource
 *    \snippet qs_i2s_dma.c tx_dma_resource
 *    \snippet qs_i2s_dma.c config_dma_resource_for_tx
 *  -# Prepare DMA transfer descriptor
 *    \snippet qs_i2s_dma.c tx_dma_descriptor
 *    \snippet qs_i2s_dma.c config_dma_descriptor_for_tx
 *  -# Start DMA transfer job with prepared descriptor
 *    \snippet qs_i2s_dma.c config_dma_job_for_tx
 *
 * \subsubsection asfdoc_sam0_i2s_dma_use_case_setup_flow_i2s Configure the I2S.
 * -# Create I<SUP>2</SUP>S module software instance structure for the I<SUP>2</SUP>S module to store
 *    the I<SUP>2</SUP>S driver state while it is in use.
 *    \snippet qs_i2s_dma.c module_inst
 *    \note This should never go out of scope as long as the module is in use.
 *          In most cases, this should be global.
 *
 * -# Configure the I<SUP>2</SUP>S module.
 *  -# Initialize the I<SUP>2</SUP>S module.
       \snippet qs_i2s_dma.c setup_i2s_init
 *  -# Initialize the I<SUP>2</SUP>S Clock Unit.
 *   -# Create a I<SUP>2</SUP>S module configuration struct, which can be filled out to
 *      adjust the configuration of a physical I<SUP>2</SUP>S Clock Unit.
 *      \snippet qs_i2s_dma.c setup_clock_unit_config
 *   -# Initialize the I<SUP>2</SUP>S Clock Unit configuration struct with the module's
 *      default values.
 *      \snippet qs_i2s_dma.c setup_clock_unit_config_defaults
 *      \note This should always be performed before using the configuration
 *            struct to ensure that all values are initialized to known default
 *            settings.
 *
 *   -# Alter the I<SUP>2</SUP>S Clock Unit settings to configure the general clock source,
 *      MCK, SCK, and FS generation.
 *      \snippet qs_i2s_dma.c setup_clock_unit_change_config
 *   -# Alter the I<SUP>2</SUP>S Clock Unit settings to configure the MCK, SCK, and FS
 *      output on physical device pins.
 *      \snippet qs_i2s_dma.c setup_clock_unit_change_pins
 *   -# Configure the I<SUP>2</SUP>S Clock Unit with the desired settings.
 *      \snippet qs_i2s_dma.c setup_clock_unit_set_config
 *  -# Initialize the I<SUP>2</SUP>S Serializers.
 *   -# Create a I<SUP>2</SUP>S Serializer configuration struct, which can be filled out to
 *      adjust the configuration of a physical I<SUP>2</SUP>S Serializer.
 *      \snippet qs_i2s_dma.c setup_serializer_config
 *   -# Initialize the I<SUP>2</SUP>S Serializer configuration struct with the module's
 *      default values.
 *      \snippet qs_i2s_dma.c setup_serializer_config_defaults
 *      \note This should always be performed before using the configuration
 *            struct to ensure that all values are initialized to known default
 *            settings.
 *
 *   -# Alter the I<SUP>2</SUP>S Serializer settings to configure the SD transmit
 *      generation.
 *      \snippet qs_i2s_dma.c setup_serializer_change_config_tx
 *   -# Alter the I<SUP>2</SUP>S Serializer settings to configure the SD transmit on a
 *      physical device pin.
 *      \snippet qs_i2s_dma.c setup_serializer_change_config_pin_tx
 *   -# Configure the I<SUP>2</SUP>S Serializer 0 with the desired transmit settings.
 *      \snippet qs_i2s_dma.c setup_serializer_set_config_tx
 *   -# Alter the I<SUP>2</SUP>S Serializer settings to configure the SD receive.
 *      \snippet qs_i2s_dma.c setup_serializer_change_config_rx
 *   -# Alter the I<SUP>2</SUP>S Serializer settings to configure the SD receive on a
 *      physical device pin (here it's disabled since we use internal loopback).
 *      \snippet qs_i2s_dma.c setup_serializer_change_config_pin_rx
 *   -# Configure the I<SUP>2</SUP>S Serializer 1 with the desired transmit settings.
 *      \snippet qs_i2s_dma.c setup_serializer_set_config_rx
 *  -# Enable the I<SUP>2</SUP>S module, the Clock Unit and Serializer to start the clocks
 *     and ready to transmit data.
 *     \snippet qs_i2s_dma.c setup_enable
 *
 * \section asfdoc_sam0_i2s_dma_use_case_main Use Case
 *
 * \subsection asfdoc_sam0_i2s_dma_use_case_main_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_i2s_dma.c main
 *
 * \subsection asfdoc_sam0_i2s_dma_use_case_main_flow Workflow
 * -# Enter an infinite loop while the signals are generated via the I<SUP>2</SUP>S module.
 *    \snippet qs_i2s_dma.c main_loop
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
