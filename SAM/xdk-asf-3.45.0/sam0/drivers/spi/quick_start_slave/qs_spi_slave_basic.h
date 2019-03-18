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
 * \page asfdoc_samb_spi_slave_basic_use Quick Start Guide for SPI Slave - Polled
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
 * \section asfdoc_samb_spi_slave_basic_use_setup Setup
 *
 * \subsection asfdoc_samb_spi_slave_basic_use_prereq Prerequisites
 * The device must be connected to a SPI master which must read from the device.
 *
 * \subsection asfdoc_samb_spi_slave_basic_use_setup_code Code
 * The following must be added to the user application source file, outside
 * any functions:
 *
 * A sample buffer to send via SPI.
 * \snippet qs_spi_slave_basic.c buffer
 * Number of entries in the sample buffer.
 * \snippet qs_spi_slave_basic.c buf_length
 * A globally available software device instance struct to store the SPI driver
 * state while it is in use.
 * \snippet qs_spi_slave_basic.c dev_inst
 * A function for configuring the GPIO.
 * \snippet qs_spi_slave_basic.c configure_gpio
 * A function for configuring the SPI.
 * \snippet qs_spi_slave_basic.c configure_spi
 *
 * Add to user application \c main().
 * \snippet qs_spi_slave_basic.c main_start
 *
 * \subsection asfdoc_samb_spi_slave_basic_use_workflow Workflow
 * -# Initialize system.
 *    \snippet qs_spi_slave_basic.c system_init
 * -# Setup the GPIO.
 *    \snippet qs_spi_slave_basic.c run_config_gpio
 * -# Setup the SPI.
 *    \snippet qs_spi_slave_basic.c run_config_spi
 *   -# Create configuration struct.
 *      \snippet qs_spi_slave_basic.c config
 *   -# Get default configuration to edit.
 *      \snippet qs_spi_slave_basic.c conf_defaults
 *   -# Set the SPI in slave mode.
 *      \snippet qs_spi_slave_basic.c conf_spi_slave_instance
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
 *      \snippet qs_spi_slave_basic.c init
 *   -# Enable SPI module.
 *      \snippet qs_spi_slave_basic.c enable
 *
 * \section asfdoc_samb_spi_slave_basic_use_case Use Case
 * \subsection asfdoc_samb_spi_slave_basic_use_case_code Code
 * Add the following to your user application \c main().
 * \snippet qs_spi_slave_basic.c main_use_case
 * \subsection asfdoc_samb_spi_slave_basic_use_case_workflow Workflow
 * -# Read data from SPI master.
 *    \snippet qs_spi_slave_basic.c read
 * -# Compare the received data with the transmitted data from SPI master.
 *    \snippet qs_spi_slave_basic.c compare
 * -# Infinite loop. If the data is matched, LED0 will flash slowly. Otherwise,
 *    LED will flash quickly.
 *    \snippet qs_spi_slave_basic.c inf_loop
 */

