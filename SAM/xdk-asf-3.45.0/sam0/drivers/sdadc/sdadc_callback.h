/**
 * \file
 *
 * \brief SAM Sigma-Delta Analog-to-Digital Converter Driver
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
/**
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef SDADC_CALLBACK_H_INCLUDED
#define SDADC_CALLBACK_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup asfdoc_sam0_sdadc_group
 *
 * @{
 */

#include <sdadc.h>

/**
 * Enum for the possible types of SDADC asynchronous jobs that may be issued to
 * the driver.
 */
enum sdadc_job_type {
	/** Asynchronous SDADC read into a user provided buffer */
	SDADC_JOB_READ_BUFFER,
};

/**
 * \name Callback Management
 * @{
 */
void sdadc_register_callback(
		struct sdadc_module *const module,
		sdadc_callback_t callback_func,
		enum sdadc_callback callback_type);

void sdadc_unregister_callback(
		struct sdadc_module *module,
		enum sdadc_callback callback_type);

/**
 * \brief Enables callback.
 *
 * Enables the callback function registered by \ref
 * sdadc_register_callback. The callback function will be called from the
 * interrupt handler when the conditions for the callback type are met.
 *
 * \param[in]     module Pointer to SDADC software instance struct
 * \param[in]     callback_type Callback type given by an enum
 *
 * \returns    Status of the operation.
 * \retval     STATUS_OK              If operation was completed
 * \retval     STATUS_ERR_INVALID     If operation was not completed,
 *                                    due to invalid callback_type
 *
 */
static inline void sdadc_enable_callback(
		struct sdadc_module *const module,
		enum sdadc_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);

	/* Enable callback */
	module->enabled_callback_mask |= (1 << callback_type);

	/* Enable window interrupt if this is a window callback */
	if (callback_type == SDADC_CALLBACK_WINDOW) {
		sdadc_enable_interrupt(module, SDADC_INTERRUPT_WINDOW);
	}
	/* Enable overrun interrupt if error callback is registered */
	if (callback_type == SDADC_CALLBACK_ERROR) {
		sdadc_enable_interrupt(module, SDADC_INTERRUPT_OVERRUN);
	}
}

/**
 * \brief Disables callback.
 *
 * Disables the callback function registered by the \ref
 * sdadc_register_callback.
 *
 * \param[in]     module Pointer to SDADC software instance struct
 * \param[in]     callback_type Callback type given by an enum
 *
 * \returns    Status of the operation.
 * \retval     STATUS_OK              If operation was completed
 * \retval     STATUS_ERR_INVALID     If operation was not completed,
 *                                    due to invalid callback_type
 *
 */
static inline void sdadc_disable_callback(
		struct sdadc_module *const module,
		enum sdadc_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);

	/* Disable callback */
	module->enabled_callback_mask &= ~(1 << callback_type);

	/* Disable window interrupt if this is a window callback */
	if (callback_type == SDADC_CALLBACK_WINDOW) {
		sdadc_disable_interrupt(module, SDADC_INTERRUPT_WINDOW);
	}
	/* Disable overrun interrupt if this is the error callback */
	if (callback_type == SDADC_CALLBACK_ERROR) {
		sdadc_disable_interrupt(module, SDADC_INTERRUPT_OVERRUN);
	}
}

/** @} */


/**
 * \name Job Management
 * @{
 */
enum status_code sdadc_read_buffer_job(
		struct sdadc_module *const module_inst,
		int32_t *buffer,
		uint16_t samples);

enum status_code sdadc_get_job_status(
		struct sdadc_module *module_inst,
		enum sdadc_job_type type);

void sdadc_abort_job(
		struct sdadc_module *module_inst,
		enum sdadc_job_type type);
/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* SDADC_CALLBACK_H_INCLUDED */
