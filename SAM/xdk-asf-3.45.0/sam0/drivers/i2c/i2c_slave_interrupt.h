/**
 * \file
 *
 * \brief I2C Slave Interrupt Driver for SAMB
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

#ifndef I2C_SLAVE_INTERRUPT_H_INCLUDED
#define I2C_SLAVE_INTERRUPT_H_INCLUDED

#include "i2c_slave.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup asfdoc_samb_i2c_group
 * @{
 *
 */

/**
 * \name Callbacks
 * @{
 */
#if !defined(__DOXYGEN__)
extern void *_i2c_instances;
void _i2c_slave_rx_isr_handler(void);
void _i2c_slave_tx_isr_handler(void);
#endif

void i2c_slave_register_callback(
		struct i2c_slave_module *const module,
		i2c_slave_callback_t callback,
		enum i2c_slave_callback callback_type);

void i2c_slave_unregister_callback(
		struct i2c_slave_module *const module,
		enum i2c_slave_callback callback_type);

/**
 * \brief Enables callback
 *
 * Enables the callback specified by the callback_type.
 *
 * \param[in,out]  module         Pointer to the software module struct
 * \param[in]      callback_type  Callback type to enable
 */
static inline void i2c_slave_enable_callback(
		struct i2c_slave_module *const module,
		enum i2c_slave_callback callback_type)
{
	/* Sanity check */
	Assert(module);
	Assert(module->hw);

	/* Mark callback as enabled */
	module->enabled_callback |= (1 << callback_type);
}

/**
 * \brief Disables callback
 *
 * Disables the callback specified by the callback_type.
 *
 * \param[in,out]  module         Pointer to the software module struct
 * \param[in]      callback_type  Callback type to disable
 */
static inline void i2c_slave_disable_callback(
		struct i2c_slave_module *const module,
		enum i2c_slave_callback callback_type)
{
	/* Sanity check */
	Assert(module);
	Assert(module->hw);

	/* Mark callback as disabled */
	module->enabled_callback &= ~(1 << callback_type);
}

/** @} */

/**
 * \name Read and Write, Interrupt-Driven
 * @{
 */


enum status_code i2c_slave_read_packet_job(
		struct i2c_slave_module *const module,
		struct i2c_slave_packet *const packet);

enum status_code i2c_slave_write_packet_job(
		struct i2c_slave_module *const module,
		struct i2c_slave_packet *const packet);


/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* I2C_SLAVE_INTERRUPT_H_INCLUDED */
