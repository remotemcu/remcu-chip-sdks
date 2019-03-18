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
 * \page asfdoc_samb_spi_master_basic_use Quick Start Guide for SPI Master - Polled
 *
 * In this use case, the SPI on extension header of the Xplained Pro board
 * will configured with the following settings:
 * - Master Mode enabled
 * - MSB of the data is transmitted first
 * - Transfer mode 0
 * - 8-bit character size
 * - Not enabled in sleep mode
 * - Baudrate
 *
 *
 * \section asfdoc_samb_spi_master_basic_use_setup Setup
 *
 * \subsection asfdoc_samb_spi_master_basic_use_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_samb_spi_master_basic_use_setup_code Code
 * The following must be added to the user application:
 *
 * A sample buffer to send via SPI.
 * \snippet qs_spi_master_basic.c buffer
 * Number of entries in the sample buffer.
 * \snippet qs_spi_master_basic.c buf_length
 * GPIO pin to use as Slave Select.
 * \snippet qs_spi_master_basic.c slave_select_pin
 * A globally available software device instance struct to store the SPI driver
 * state while it is in use.
 * \snippet qs_spi_master_basic.c dev_inst
 * A globally available peripheral slave software device instance struct.
 * \snippet qs_spi_master_basic.c slave_dev_inst
 * A function for configuring the GPIO.
 * \snippet qs_spi_master_basic.c configure_gpio
 * A function for configuring the SPI.
 * \snippet qs_spi_master_basic.c configure_spi
 *
 * Add to user application \c main().
 * \snippet qs_spi_master_basic.c main_setup
 *
 * \section asfdoc_samb_spi_master_basic_use_workflow Workflow
 * -# Initialize system.
 *    \snippet qs_spi_master_basic.c system_init
 * -# Setup GPIO.
 *    \snippet qs_spi_master_basic.c run_config_gpio 
 * -# Setup SPI.
 *    \snippet qs_spi_master_basic.c run_config_spi
 *   -# Create configuration struct.
 *      \snippet qs_spi_master_basic.c config
 *   -# Create peripheral slave configuration struct.
 *      \snippet qs_spi_master_basic.c slave_config
 *   -# Create peripheral slave software device instance struct.
 *      \snippet qs_spi_master_basic.c slave_dev_inst
 *   -# Get default peripheral slave configuration.
 *      \snippet qs_spi_master_basic.c slave_conf_defaults
 *   -# Set Slave Select pin.
 *      \snippet qs_spi_master_basic.c ss_pin
 *   -# Initialize peripheral slave software instance with configuration.
 *      \snippet qs_spi_master_basic.c slave_init
 *   -# Get default configuration to edit.
 *      \snippet qs_spi_master_basic.c conf_defaults
 *   -# Set transfer mode 0.
 *      \snippet qs_spi_master_basic.c transfer_mode
 *   -# Set clock divider.
 *      \snippet qs_spi_master_basic.c clock_divider
 *   -# Set pinmux for pad 0 (SCK).
 *      \snippet qs_spi_master_basic.c sck
 *   -# Set pinmux for pad 1 (data out (MOSI))
 *      \snippet qs_spi_master_basic.c mosi
 *   -# Set pinmux for pad 2 as unused, so the pin can be used for other purposes.
 *      \snippet qs_spi_master_basic.c ssn
 *   -# Set pinmux for pad 3 (data in (MISO)).
 *      \snippet qs_spi_master_basic.c miso
 *   -# Initialize SPI module with configuration.
 *      \snippet qs_spi_master_basic.c init
 *   -# Enable SPI module.
 *      \snippet qs_spi_master_basic.c enable
 *
 * \section asfdoc_samb_spi_master_basic_use_case Use Case
 * \subsection asfdoc_samb_spi_master_basic_use_case_code Code
 * Add the following to your user application \c main().
 * \snippet qs_spi_master_basic.c main_use_case
 * \subsection asfdoc_samb_spi_master_basic_use_case_workflow Workflow
 * -# Select slave.
 *    \snippet qs_spi_master_basic.c select_slave
 * -# Write buffer to SPI slave.
 *    \snippet qs_spi_master_basic.c write
 * -# Wait for the transfer to be complete.
 *    \snippet qs_spi_master_basic.c delay
 * -# Deselect slave.
 *    \snippet qs_spi_master_basic.c deselect_slave
 * -# Light up.
 *    \snippet qs_spi_master_basic.c light_up
 * -# Infinite loop.
 *    \snippet qs_spi_master_basic.c inf_loop
 */

