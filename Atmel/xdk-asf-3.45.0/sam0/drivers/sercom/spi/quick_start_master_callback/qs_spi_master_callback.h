/**
 * \file
 *
 * \brief SAM SPI Quick Start
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
 * \page asfdoc_sam0_sercom_spi_master_callback_use Quick Start Guide for SERCOM SPI Master - Callback
 *
 * In this use case, the SPI on extension header 1 of the Xplained Pro board
 * will be configured with the following settings:
 * - Master Mode enabled
 * - MSB of the data is transmitted first
 * - Transfer mode 0
 * - SPI MUX Setting E (see \ref asfdoc_sam0_sercom_spi_mux_settings_master)
 * - 8-bit character size
 * - Not enabled in sleep mode
 * - Baudrate 100000
 * - GLCK generator 0
 *
 *
 * \section asfdoc_sam0_sercom_spi_master_callback_use_setup Setup
 *
 * \subsection asfdoc_sam0_sercom_spi_master_callback_use_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_sam0_sercom_spi_master_callback_use_setup_code Code
 * The following must be added to the user application.
 *
 * A sample buffer to send via SPI.
 * \snippet qs_spi_master_callback.c buffer
 * Number of entries in the sample buffer.
 * \snippet qs_spi_master_callback.c buf_length
 * GPIO pin to use as Slave Select.
 * \snippet qs_spi_master_callback.c slave_select_pin
 * A globally available software device instance struct to store the SPI driver
 * state while it is in use.
 * \snippet qs_spi_master_callback.c dev_inst
 * A globally available peripheral slave software device instance struct.
 * \snippet qs_spi_master_callback.c slave_dev_inst
 * A function for configuring the SPI.
 * \snippet qs_spi_master_callback.c configure_spi
 * A function for configuring the callback functionality of the SPI.
 * \snippet qs_spi_master_callback.c conf_callback
 * A global variable that can flag to the application that the buffer has been
 * transferred.
 * \snippet qs_spi_master_callback.c var
 * Callback function.
 * \snippet qs_spi_master_callback.c callback
 *
 * Add to user application \c main().
 * \snippet qs_spi_master_callback.c main_start
 *
 * \section asfdoc_sam0_sercom_spi_master_callback_use_workflow Workflow
 * -# Initialize system.
 *    \snippet qs_spi_master_callback.c system_init
 * -# Set-up the SPI.
 *    \snippet qs_spi_master_callback.c run_config
 *   -# Create configuration struct.
 *      \snippet qs_spi_master_callback.c config
 *   -# Create peripheral slave configuration struct.
 *      \snippet qs_spi_master_callback.c slave_config
 *   -# Get default peripheral slave configuration.
 *      \snippet qs_spi_master_callback.c slave_conf_defaults
 *   -# Set Slave Select pin.
 *      \snippet qs_spi_master_callback.c ss_pin
 *   -# Initialize peripheral slave software instance with configuration.
 *      \snippet qs_spi_master_callback.c slave_init
 *   -# Get default configuration to edit.
 *      \snippet qs_spi_master_callback.c conf_defaults
 *   -# Set MUX setting E.
 *      \snippet qs_spi_master_callback.c mux_setting
 *   -# Set pinmux for pad 0 (data in MISO).
 *      \snippet qs_spi_master_callback.c di
 *   -# Set pinmux for pad 1 as unused, so the pin can be used for other purposes.
 *      \snippet qs_spi_master_callback.c ss
 *   -# Set pinmux for pad 2 (data out MOSI).
 *      \snippet qs_spi_master_callback.c do
 *   -# Set pinmux for pad 3 (SCK).
 *      \snippet qs_spi_master_callback.c sck
 *   -# Initialize SPI module with configuration.
 *      \snippet qs_spi_master_callback.c init
 *   -# Enable SPI module.
 *      \snippet qs_spi_master_callback.c enable
 * -# Setup the callback functionality.
 *    \snippet qs_spi_master_callback.c run_callback_config
 *   -# Register callback function for buffer transmitted.
 *      \snippet qs_spi_master_callback.c reg_callback
 *   -# Enable callback for buffer transmitted.
 *      \snippet qs_spi_master_callback.c en_callback
 *
 * \section asfdoc_sam0_sercom_spi_master_callback_use_case Use Case
 * \subsection asfdoc_sam0_sercom_spi_master_callback_use_case_code Code
 * Add the following to your user application \c main().
 * \snippet qs_spi_master_callback.c main_use_case
 * \subsection asfdoc_sam0_sercom_spi_master_callback_use_case_workflow Workflow
 * -# Select slave.
 *    \snippet qs_spi_master_callback.c select_slave
 * -# Write buffer to SPI slave.
 *    \snippet qs_spi_master_callback.c write and read
 * -# Wait for the transfer to be complete.
 *    \snippet qs_spi_master_callback.c wait
 * -# Deselect slave.
 *    \snippet qs_spi_master_callback.c deselect_slave
 * -# Infinite loop.
 *    \snippet qs_spi_master_callback.c inf_loop
 *
 * \section asfdoc_sam0_sercom_spi_master_callback_use_callback Callback
 * When the buffer is successfully transmitted to the slave, the callback
 * function will be called.
 * \subsection asfdoc_sam0_sercom_spi_master_callback_use_callback_workflow Workflow
 * -# Let the application know that the buffer is transmitted by setting the
 *    global variable to true.
 *    \snippet qs_spi_master_callback.c callback_var
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
