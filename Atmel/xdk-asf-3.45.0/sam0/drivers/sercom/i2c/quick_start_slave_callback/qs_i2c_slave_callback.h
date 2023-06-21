/**
 * \file
 *
 * \brief SAM SERCOM I2C Slave Quick Start Guide with Callbacks
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
 * \page asfdoc_sam0_sercom_i2c_slave_callback_use_case Quick Start Guide for SERCOM I2C Slave - Callback
 *
 * In this use case, the I<SUP>2</SUP>C will used and set up as follows:
 *  - Slave mode
 *  - 100KHz operation speed
 *  - Not operational in standby
 *  - 10000 packet timeout value
 *
 * \section asfdoc_sam0_sercom_i2c_slave_callback_use_case_prereq Prerequisites
 * The device must be connected to an I<SUP>2</SUP>C master.
 *
 * \section asfdoc_sam0_sercom_i2c_slave_callback_use_case_setup_code Setup
 *
 * \subsection asfdoc_sam0_sercom_i2c_slave_callback_use_setup_code Code
 * The following must be added to the user application:
 *
 * A sample buffer to write from, a sample buffer to read to and length of buffers:
 * \snippet qs_i2c_slave_callback.c packet_data
 *
 * Address to respond to:
 * \snippet qs_i2c_slave_callback.c address
 *
 * Globally accessible module structure:
 * \snippet qs_i2c_slave_callback.c module
 *
 * Globally accessible packet:
 * \snippet qs_i2c_slave_callback.c packet
 *
 * Function for setting up the module:
 * \snippet qs_i2c_slave_callback.c initialize_i2c
 *
 * Callback function for read request from a master:
 * \snippet qs_i2c_slave_callback.c read_request
 *
 * Callback function for write request from a master:
 * \snippet qs_i2c_slave_callback.c write_request
 *
 * Function for setting up the callback functionality of the driver:
 * \snippet qs_i2c_slave_callback.c setup_i2c_callback
 *
 * Add to user application \c main():
 * \snippet qs_i2c_slave_callback.c run_initialize_i2c
 *
 * \subsection asfdoc_sam0_sercom_i2c_slave_callback_use_setup_workflow Workflow
 * -# Configure and enable module.
 *    \snippet qs_i2c_slave_callback.c config
 *   -# Create and initialize configuration structure.
 *      \snippet qs_i2c_slave_callback.c init_conf
 *   -# Change address and address mode settings in the configuration.
 *      \snippet qs_i2c_slave_callback.c conf_changes
 *   -# Initialize the module with the set configurations.
 *      \snippet qs_i2c_slave_callback.c init_module
 *   -# Enable the module.
 *      \snippet qs_i2c_slave_callback.c enable_module
 * -# Register and enable callback functions.
 *    \snippet qs_i2c_slave_callback.c config_callback
 *   -# Register and enable callbacks for read and write requests from master.
 *      \snippet qs_i2c_slave_callback.c reg_en_i2c_callback
 *
 * \section asfdoc_sam0_sercom_i2c_slave_callback_use_implementation Implementation
 * \subsection asfdoc_sam0_sercom_i2c_slave_callback_use_implementation_code Code
 * Add to user application \c main():
 * \snippet qs_i2c_slave_callback.c while
 * \subsection i2c_slave_callback_use_implementation_workflow Workflow
 * -# Infinite while loop, while waiting for interaction from master.
 *    \snippet qs_i2c_slave_callback.c while
 *
 * \section asfdoc_sam0_sercom_i2c_slave_callback_use_callback Callback
 * When an address packet is received, one of the callback functions will be
  * called, depending on the DIR bit in the received packet.
 *
 * \subsection asfdoc_sam0_sercom_i2c_slave_callback_use_callback_workflow Workflow
 * - Read request callback:
 *  -# Length of buffer and buffer to be sent to master is initialized.
 *     \snippet qs_i2c_slave_callback.c packet_write
 *  -# Write packet to master.
 *     \snippet qs_i2c_slave_callback.c write_packet
 *
 * - Write request callback:
 *  -# Length of buffer and buffer to be read from master is initialized.
 *     \snippet qs_i2c_slave_callback.c packet_read
 *  -# Read packet from master.
 *     \snippet qs_i2c_slave_callback.c read_packet
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <conf_clocks.h>

