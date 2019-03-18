/**
 * \file
 *
 * \brief I2C Master Driver for SAMB
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

#ifndef I2C_MASTER_H_INCLUDED
#define I2C_MASTER_H_INCLUDED

#include <compiler.h>
#include "i2c_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup asfdoc_samb_i2c_group
 *
 * @{
 */


/**
 * \brief I<SUP>2</SUP>C master packet for read/write
 *
 * Structure to be used when transferring I<SUP>2</SUP>C master packets.
 */
struct i2c_master_packet {
	/** Address to slave device */
	uint16_t address;
	/** Length of data array */
	uint16_t data_length;
	/** Data array containing all data to be transferred */
	uint8_t *data;
};

/** \brief Interrupt flags
 *
 * Flags used when reading or setting interrupt flags.
 */
enum i2c_master_interrupt_flag {
	/** Interrupt flag used for write */
	I2C_MASTER_INTERRUPT_WRITE = 0,
	/** Interrupt flag used for read */
	I2C_MASTER_INTERRUPT_READ  = 1,
};

/**
 * \brief I<SUP>2</SUP>C frequencies
 *
 * Values for I<SUP>2</SUP>C speeds supported by the module. 
 *
 */
enum i2c_master_baud_rate {
	/** Baud rate at 100KHz (Standard-mode) */
	I2C_MASTER_BAUD_RATE_100KHZ = 100,
	/** Baud rate at 400KHz (Fast-mode) */
	I2C_MASTER_BAUD_RATE_400KHZ = 400,
};


#if I2C_MASTER_CALLBACK_MODE == true
/**
 * \brief Callback types
 *
 * The available callback types for the I<SUP>2</SUP>C master module.
 */
enum i2c_master_callback {
	/** Callback for packet write complete */
	I2C_MASTER_CALLBACK_WRITE_COMPLETE = 0,
	/** Callback for packet read complete */
	I2C_MASTER_CALLBACK_READ_COMPLETE  = 1,
#  if !defined(__DOXYGEN__)
	/** Total number of callbacks */
	_I2C_MASTER_CALLBACK_N             = 2,
#  endif
};

#  if !defined(__DOXYGEN__)
/** Prototype for software module. */
struct i2c_master_module;

/** Prototype for I2C Callback function */
typedef void (*i2c_master_callback_t)(
		struct i2c_master_module *const module);
#  endif
#endif

/**
 * \brief  I<SUP>2</SUP>C driver software device instance structure.
 *
 *  I<SUP>2</SUP>C driver software instance structure, used to
 * retain software state information of an associated hardware module instance.
 *
 * \note The fields of this structure should not be altered by the user
 *       application; they are reserved for module-internal use only.
 */
struct i2c_master_module {
#if !defined(__DOXYGEN__)
	/** Hardware instance initialized for the struct */
	I2c *hw;
	/** Module lock */
	volatile bool locked;
	/** If true, stop condition will be sent after a read/write */
	bool no_stop;
#  if I2C_MASTER_CALLBACK_MODE == true
	/** Pointers to callback functions */
	volatile i2c_master_callback_t callbacks[_I2C_MASTER_CALLBACK_N];
	/** Mask for registered callbacks */
	volatile uint8_t registered_callback;
	/** Mask for enabled callbacks */
	volatile uint8_t enabled_callback;
	/** The total number of bytes to transfer */
	volatile uint16_t buffer_length;
	/**
	 * Counter used for bytes left to send in write and to count number of
	 * obtained bytes in read
	 */
	volatile uint16_t buffer_remaining;
	/** Data buffer for packet write and read */
	volatile uint8_t *buffer;
	/** Save direction of async request. 1 = read, 0 = write */
	volatile enum i2c_transfer_direction transfer_direction;
	/** Status for status read back in error callback */
	volatile enum status_code status;
#  endif
#endif
};

/**
 * \brief Configuration structure for the I<SUP>2</SUP>C Master device
 *
 * This is the configuration structure for the I<SUP>2</SUP>C Master device. It
 * is used as an argument for \ref i2c_master_init to provide the desired
 * configurations for the module. The structure should be initialized using the
 * \ref i2c_master_get_config_defaults .
 */
struct i2c_master_config {
	/** CLOCK INPUT to use as clock source */
	enum i2c_clock_input clock_source;
	/** Divide ratio used to generate the sck clock */
	uint16_t clock_divider;
	/** PAD0 (SDA) pin number */
	uint32_t pin_number_pad0;
	/** PAD0 (SDA) pinmux selection */
	uint32_t pinmux_sel_pad0;
	/** PAD1 (SCL) pin numer */
	uint32_t pin_number_pad1;
	/** PAD1 (SCL) pinmux selection */
	uint32_t pinmux_sel_pad1;
};

void i2c_master_get_config_defaults(
		struct i2c_master_config *const config);

 enum status_code i2c_master_init(
		struct i2c_master_module *const module,
		I2c *const hw,
		const struct i2c_master_config *const config);

void i2c_master_reset(struct i2c_master_module *const module);

enum status_code i2c_master_write_address(
		struct i2c_master_module *const module,
		uint8_t address,
		uint8_t command);

enum status_code i2c_master_read_packet_wait(
		struct i2c_master_module *const module,
		struct i2c_master_packet *const packet);

enum status_code i2c_master_read_packet_wait_no_stop(
		struct i2c_master_module *const module,
		struct i2c_master_packet *const packet);

enum status_code i2c_master_write_packet_wait(
		struct i2c_master_module *const module,
		struct i2c_master_packet *const packet);

enum status_code i2c_master_write_packet_wait_no_stop(
		struct i2c_master_module *const module,
		struct i2c_master_packet *const packet);

void i2c_master_send_stop(struct i2c_master_module *const module);

void i2c_master_send_start(struct i2c_master_module *const module);

enum status_code i2c_master_read_byte(
		struct i2c_master_module *const module,
		uint8_t *byte);

enum status_code i2c_master_write_byte(
		struct i2c_master_module *const module,
		uint8_t byte);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* I2C_MASTER_H_INCLUDED */

