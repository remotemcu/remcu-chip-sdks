/**
 * \file
 *
 * \brief QTouch component driver with I2C interface.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef QT_I2C_H_INCLUDED
#define QT_I2C_H_INCLUDED

#include "compiler.h"
#include "status_codes.h"
#include "twi_master.h"
#include "conf_qt_i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup qt_device_i2c_group QTouch device driver for I2C interface
 *
 * See \ref qt_device_i2c_quickstart.
 *
 * This component driver provides low-level read/write access to the
 * configuration and data registers on a QTouch device. It has only been
 * tested on AT42QT2160 parts, but it should be easy to add support for other
 * QTouch devices with I2C interface.
 *
 * @{
 */

/**
 *  \defgroup qt_device_i2c_support_list QT Device list support by the driver
 *  @{
 */

#define QT2160    1    /**< AT42QT2160 device support */
/** @}  */

#if (CONF_QT_DEVICE == QT2160)
	#include "QT2160.h"
#else
	#error "Device not supported"
#endif

/** Checking board configuration of the QTouch device */
#if !defined(BOARD_QT_TWI_INSTANCE)
# warning The QTouch TWI instance has not been defined. Using default settings.
# define BOARD_QT_TWI_INSTANCE  0    /* TWI instance */
#endif
#if !defined(BOARD_QT_DEVICE_ADDRESS)
# warning The QTouch device address has not been defined. Using default settings.
# define BOARD_QT_DEVICE_ADDRESS    0    /* QTouch device address */
#endif

void qt_hardware_reset(void);
enum status_code qt_get_comm_ready(void);
enum status_code qt_read_setup_block(struct qt_setup_block *setup_block);
enum status_code qt_write_setup_block(struct qt_setup_block *setup_block);
enum status_code qt_get_status(struct qt_status *qt_status);
bool qt_is_change_line_low(void);
enum status_code qt_read_regs(uint8_t reg_addr, uint8_t *read_buffer,
		uint8_t length);
enum status_code qt_write_regs(uint8_t reg_addr, uint8_t *write_buffer,
		uint8_t length);

/** @} */
#ifdef __cplusplus
}
#endif

/**
 * \page qt_device_i2c_quickstart Quick start guide for QTouch component
 *
 * This is the quick start guide for the \ref qt_device_i2c_group, with
 * step-by-step instructions on how to configure and use the driver for
 * a specific use case.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section qt_i2c_basic_use_case Basic use case
 *
 * This basic use case will demonstrate how to use the host TWI interface to
 * read real time touch information from QT devices. It also demonstrates the
 * procedure to read and write the setup block which helps to tune the
 * operating parameters of the device.
 *
 * \section qt_i2c_basic_setup Basic Setup Steps
 *
 * \subsection qt_i2c_basic_prereq Prerequisites
 *
 * This module requires the following service
 * - \ref clk_group
 * - \ref ioport_group
 * - \ref twi_group
 * - \ref group_common_services_delay
 *
 * \subsection qt_i2c_basic_setup_code Setup Code Example
 *
 * Add this to the main loop or a setup function:
 * \code
	   struct qt_status status;
	   struct qt_setup_block setup_block;
	   enum status_code ret;
	   twi_master_options_t twi_opt;

	   // Initialize I2C communication interface
	   memset((void *)&twi_opt, 0, sizeof(twi_master_options_t));
	   twi_opt.speed = 50000;    // 50K for I2C speed
	   twi_master_setup(BOARD_QT_TWI_INSTANCE, &twi_opt);

	   // Reset QT device
	   qt_hardware_reset();

	   // Check communication is ready and able to read Chip ID
	   ret = qt_get_comm_ready();
	   if (ret != STATUS_OK) {
	       while (1) {
	           // Infinite loop here
	       }
	   }

	   // Read setup block
	   qt_read_setup_block(&setup_block);

	   // TODO:Modify setup block parameters according to application

	   // Write setup block
	   qt_write_setup_block(&setup_block);

\endcode
 *
 * \subsection qt_i2c_basic_setup_workflow Setup Workflow
 *
 * -# Initialize I2C communication interface
 *  \code
	   twi_master_options_t twi_opt;

	   memset((void *)&twi_opt, 0, sizeof(twi_master_options_t));
	   twi_opt.speed = 50000;    // 50K for I2C speed
	   twi_master_setup(BOARD_QT_TWI_INSTANCE, &twi_opt);
\endcode
 * -# Reset QT device (optional)
 *  \code
	qt_hardware_reset();
\endcode
 * -# Check communication is ready and able to read Chip ID
 *  \code
	ret = qt_get_comm_ready();
	if (ret != STATUS_OK) {
	    while (1) {
	        // Infinite loop here
	    }
	}
\endcode
 * -# Read setup block from QT device
 *  \code
	qt_read_setup_block(&setup_block);
\endcode
 * -# Modify parameters in setup block if desired
 *  \code
	// For example, to set Detect Integrator to 5.
	setup_block.detect_integrator = 5;
\endcode
 * -# Wrtie setup block to QT device
 *  \code
	qt_write_setup_block(&setup_block);
\endcode
 *
 * \section qt_i2c_basic_usage Basic Usage Steps
 * \subsection qt_i2c_basic_usage_sample_code Basic Usage Example
 * \code
	  while (1) {
	       // Read Qtouch status if CHANGE pin is asserted
	       if (qt_is_change_line_low()) {
	           // Read all status bytes
	           qt_get_status(&status);

	           // TODO: process the received data by application
	           // Add application code here
	       }
	   }
\endcode
 */

#endif /* QT_I2C_H_INCLUDED */
