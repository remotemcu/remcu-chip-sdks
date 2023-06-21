/**
 * \file
 *
 * \brief SAM SPI Quick Start for SAMB
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
 * \page asfdoc_samb_spi_slave_callback_use Quick Start Guide for SPI Slave - Callback
 *
 * In this use case, the SPI on extension header of the Xplained Pro board
 * will configured with the following settings:
 * - Slave mode enabled
 * - Preloading of shift register enabled
 * - MSB of the data is transmitted first
 * - Transfer mode 0
 * - 8-bit character size
 * - Not enabled in sleep mode
 *
 *
 * \section asfdoc_samb_spi_slave_callback_use_setup Setup
 *
 * \subsection asfdoc_samb_spi_slave_callback_use_prereq Prerequisites
 * The device must be connected to a SPI master which must read from the device.
 *
 * \subsection asfdoc_samb_spi_slave_callback_use_setup_code Code
 * The following must be added to the user application source file, outside
 * any functions:
 *
 * A sample buffer to send via SPI.
 * \snippet qs_spi_slave_callback.c buffer
 * Number of entries in the sample buffer.
 * \snippet qs_spi_slave_callback.c buf_length
 * A global variable that can flag to the application that the buffer has been
 * transferred.
 * \snippet qs_spi_slave_callback.c var
 * A globally available software device instance struct to store the SPI driver
 * state while it is in use.
 * \snippet qs_spi_slave_callback.c dev_inst
 * Callback function.
 * \snippet qs_spi_slave_callback.c callback
 * A function for configuring the GPIO.
 * \snippet qs_spi_slave_callback.c configure_gpio
 * A function for configuring the SPI.
 * \snippet qs_spi_slave_callback.c configure_spi
 *
 * Add to user application \c main().
 * \snippet qs_spi_slave_callback.c main_start
 *
 * \subsection asfdoc_samb_spi_slave_callback_use_workflow Workflow
 * -# Initialize system.
 *    \snippet qs_spi_slave_callback.c system_init
 * -# Setup the GPIO.
 *    \snippet qs_spi_slave_callback.c run_config_gpio
 * -# Setup the SPI.
 *    \snippet qs_spi_slave_callback.c run_config_spi
 *   -# Create configuration struct.
 *      \snippet qs_spi_slave_callback.c config
 *   -# Get default configuration to edit.
 *      \snippet qs_spi_slave_callback.c conf_defaults
 *   -# Set the SPI in slave mode.
 *      \snippet qs_spi_slave_callback.c conf_spi_slave_instance
 *   -# Set transfer mode 0.
 *      \snippet qs_spi_master_basic.c transfer_mode
 *   -# Set pinmux for pad 0 (SCK).
 *      \snippet qs_spi_master_basic.c sck
 *   -# Set pinmux for pad 1 (data out (MOSI))
 *      \snippet qs_spi_master_basic.c mosi
 *   -# Set pinmux for pad 2 (SSN).
 *      \snippet qs_spi_master_basic.c ssn
 *   -# Set pinmux for pad 3 (data in (MISO)).
 *      \snippet qs_spi_master_basic.c miso
 *   -# Initialize SPI module with configuration.
 *      \snippet qs_spi_slave_callback.c init
 *   -# Enable SPI module.
 *      \snippet qs_spi_slave_callback.c enable
 * -# Setup the callback functionality.
 *    \snippet qs_spi_slave_callback.c run_callback_config
 *   -# Register callback function for buffer transmitted.
 *      \snippet qs_spi_slave_callback.c reg_callback
 *   -# Enable callback for buffer transmitted.
 *      \snippet qs_spi_slave_callback.c en_callback
 *
 * \section asfdoc_samb_spi_slave_callback_use_case Use Case
 * \subsection asfdoc_samb_spi_slave_callback_use_case_code Code
 * Add the following to your user application \c main().
 * \snippet qs_spi_slave_callback.c main_use_case
 * \subsection asfdoc_samb_spi_slave_callback_use_case_workflow Workflow
 * -# Read data from SPI master.
 *    \snippet qs_spi_slave_callback.c read
 * -# Compare the received data with the transmitted data from SPI master.
 *    \snippet qs_spi_slave_callback.c compare
 * -# Infinite loop. If the data is matched, LED0 will flash slowly. Otherwise,
 *    LED will flash quickly.
 *    \snippet qs_spi_slave_callback.c inf_loop
 *
 * \section asfdoc_samb_drivers_spi_slave_callback_use_callback Callback
 * When the buffer is successfully transmitted from the master, the callback
 * function will be called.
 * \subsection asfdoc_samb_drivers_spi_slave_callback_use_callback_workflow Workflow
 * -# Let the application know that the buffer is transmitted by setting the
 *    global variable to true.
 *    \snippet qs_spi_slave_callback.c callback_var
 */

