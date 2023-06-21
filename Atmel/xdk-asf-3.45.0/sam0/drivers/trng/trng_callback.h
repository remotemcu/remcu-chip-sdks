/**
 * \file
 *
 * \brief SAM True Random Number Generator (TRNG) Driver
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

#ifndef TRNG_CALLBACK_H_INCLUDED
#define TRNG_CALLBACK_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup asfdoc_sam0_trng_group
 *
 * @{
 */

#include <trng.h>

/**
 * Enum for the possible types of TRNG asynchronous jobs that may be issued to
 * the driver.
 */
enum trng_job_type {
	/** Asynchronous TRNG read into a user provided buffer */
	TRNG_JOB_READ_BUFFER,
};

/**
 * \name Callback Management
 * @{
 */
enum status_code trng_register_callback(
		struct trng_module *const module,
		trng_callback_t callback_func,
		enum trng_callback callback_type);

enum status_code trng_unregister_callback(
		struct trng_module *module,
		enum trng_callback callback_type);

/**
 * \brief Enables callback
 *
 * Enables the callback function registered by \ref
 * trng_register_callback. The callback function will be called from the
 * interrupt handler when the conditions for the callback type are met.
 *
 * \param[in]     module        Pointer to TRNG software instance struct
 * \param[in]     callback_type Callback type given by an enum
 */
static inline void trng_enable_callback(
		struct trng_module *const module,
		enum trng_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);

	/* Enable callback */
	module->enable_callback_mask |= (1 << callback_type);
}

/**
 * \brief Disables callback
 *
 * Disables the callback function registered by the \ref
 * trng_register_callback.
 *
 * \param[in]     module        Pointer to TRNG software instance struct
 * \param[in]     callback_type Callback type given by an enum
 */
static inline void trng_disable_callback(
		struct trng_module *const module,
		enum trng_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);

	/* Disable callback */
	module->enable_callback_mask &= ~(1UL << callback_type);

	/* Disable data ready interrupt */
	if (callback_type == TRNG_CALLBACK_READ_BUFFER) {
		module->hw->INTENCLR.reg = TRNG_INTENCLR_DATARDY;
	}
}

/** @} */

/**
 * \name Job Management
 * @{
 */
enum status_code trng_read_buffer_job(
		struct trng_module *const module_inst,
		uint32_t *buffer,
		uint32_t number);

enum status_code trng_get_job_status(
		struct trng_module *module_inst,
		enum trng_job_type type);

void trng_abort_job(
		struct trng_module *module_inst,
		enum trng_job_type type);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* TRNG_CALLBACK_H_INCLUDED */

