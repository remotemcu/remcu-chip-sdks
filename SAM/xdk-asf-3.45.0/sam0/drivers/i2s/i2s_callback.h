/**
 * \file
 *
 * \brief SAM I2S - Inter-IC Sound Controller
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef I2S_CALLBACK_H_INCLUDED
#define I2S_CALLBACK_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup asfdoc_sam0_i2s_group
 *
 * @{
 */

#include <i2s.h>

/**
 * Enum for the possible types of I<SUP>2</SUP>S asynchronous jobs that may be issued to
 * the driver.
 */
enum i2s_job_type {
	/** Asynchronous I<SUP>2</SUP>S write from a user provided buffer */
	I2S_JOB_WRITE_BUFFER,
	/** Asynchronous I<SUP>2</SUP>S read into a user provided buffer */
	I2S_JOB_READ_BUFFER
};

/**
 * \name Callback Management
 * @{
 */

/**
 * \brief Registers a callback for serializer
 *
 * Registers a callback function which is implemented by the user.
 *
 * \note The callback must be enabled by for the interrupt handler to call it
 * when the condition for the callback is met.
 *
 * \param[in] module         Pointer to ADC software instance struct
 * \param[in] serializer     The serializer that generates callback
 * \param[in] callback_func  Pointer to callback function
 * \param[in] callback_type  Callback type given by an enum
 *
 */
static inline void i2s_serializer_register_callback(
		struct i2s_module *const module_inst,
		const enum i2s_serializer serializer,
		const i2s_serializer_callback_t callback_func,
		const enum i2s_serializer_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(serializer < I2S_SERIALIZER_N);

	module_inst->serializer[serializer].callback[callback_type] = callback_func;
	module_inst->serializer[serializer].registered_callback_mask |=
			(1u << callback_type);
}

/**
 * \brief Unregisters a callback for serializer
 *
 * Unregisters a callback function which is implemented by the user.
 *
 * \param[in] module         Pointer to ADC software instance struct
 * \param[in] serializer     The serializer that generates callback
 * \param[in] callback_type  Callback type given by an enum
 *
 */
static inline void i2s_serializer_unregister_callback(
		struct i2s_module *const module_inst,
		const enum i2s_serializer serializer,
		const enum i2s_serializer_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(serializer < I2S_SERIALIZER_N);

	module_inst->serializer[serializer].callback[callback_type] = NULL;
	module_inst->serializer[serializer].registered_callback_mask &=
			~(1u << callback_type);
}

/**
 * \brief Enables callback for serializer
 *
 * Enables the callback function registered by \ref
 * i2s_serializer_register_callback. The callback function will be called from
 * the interrupt handler when the conditions for the callback type are met.
 *
 * \param[in] module         Pointer to ADC software instance struct
 * \param[in] serializer     The serializer that generates callback
 * \param[in] callback_type  Callback type given by an enum
 *
 */
static inline void i2s_serializer_enable_callback(
		struct i2s_module *const module_inst,
		const enum i2s_serializer serializer,
		const enum i2s_serializer_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);
	Assert(serializer < I2S_SERIALIZER_N);

	module_inst->serializer[serializer].enabled_callback_mask |=
			(1u << callback_type);
	if (I2S_SERIALIZER_CALLBACK_OVER_UNDER_RUN != callback_type) {
		return;
	}
	module_inst->hw->INTENSET.reg =
		(module_inst->serializer[serializer].mode == I2S_SERIALIZER_TRANSMIT) ?
			(I2S_INTFLAG_TXUR0 << serializer) :
			(I2S_INTFLAG_RXOR0 << serializer);
}

/**
 * \brief Disables callback for Serializer
 *
 * Disables the callback function registered by the \ref
 * i2s_serializer_register_callback.
 *
 * \param[in] module         Pointer to ADC software instance struct
 * \param[in] serializer     The serializer that generates callback
 * \param[in] callback_type  Callback type given by an enum
 *
 */
static inline void i2s_serializer_disable_callback(
		struct i2s_module *const module_inst,
		const enum i2s_serializer serializer,
		const enum i2s_serializer_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);
	Assert(serializer < I2S_SERIALIZER_N);

	module_inst->serializer[serializer].enabled_callback_mask &=
			~(1u << callback_type);
	if (I2S_SERIALIZER_CALLBACK_OVER_UNDER_RUN != callback_type) {
		return;
	}
	module_inst->hw->INTENCLR.reg =
		(module_inst->serializer[serializer].mode == I2S_SERIALIZER_TRANSMIT) ?
			(I2S_INTFLAG_TXUR0 << serializer) :
			(I2S_INTFLAG_RXOR0 << serializer);
}

/** @} */

/**
 * \name Job Management
 *
 * @{
 */

enum status_code i2s_serializer_write_buffer_job(
		struct i2s_module *const module_inst,
		const enum i2s_serializer serializer,
		const void *buffer,
		const uint32_t size);

enum status_code i2s_serializer_read_buffer_job(
		struct i2s_module *const module_inst,
		const enum i2s_serializer serializer,
		void *buffer,
		const uint32_t size);

void i2s_serializer_abort_job(
		struct i2s_module *const module_inst,
		const enum i2s_serializer serializer,
		const enum i2s_job_type job_type);

enum status_code i2s_serializer_get_job_status(
		const struct i2s_module *const module_inst,
		const enum i2s_serializer serializer,
		const enum i2s_job_type job_type);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef I2S_CALLBACK_H_INCLUDED */
