/**
 *
 * \file
 *
 * \brief SAM Frequency Meter driver.
 *
 * This file defines a useful set of functions for the FREQM on SAM devices.
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

#ifndef FREQM_CALLBACK_H_INCLUDED
#define FREQM_CALLBACK_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <compiler.h>
#include <system_interrupt.h>
/**
 * \addtogroup asfdoc_sam0_freqm_group
 *
 * @{
 */

/** FREQM callback type. */
enum freqm_callback_type {
	/** Measurement done callback.*/
	FREQM_CALLBACK_MEASURE_DONE = 0,
};
 
/** \name Callback Configuration and Initialization
 * @{
 */
 
enum status_code freqm_register_callback(
		struct freqm_module *const module,
		freqm_callback_t callback_func,
		enum freqm_callback callback_type);

enum status_code freqm_unregister_callback(
		struct freqm_module *module,
		enum freqm_callback callback_type);

/** @} */


/** \name Callback Enabling and Disabling
 * @{
 */

/**
 * \brief Enable an FREQM callback.
 *
 * \param[in,out] module  Pointer to the software instance struct
 * \param[in] type Callback source type
 *
 * \return Status of the callback enable operation.
 * \retval STATUS_OK The callback was enabled successfully
 * \retval STATUS_ERR_INVALID_ARG If an invalid callback type was supplied
 */
static inline enum status_code freqm_enable_callback(struct freqm_module *const module,
		const enum freqm_callback_type type)
{
	/* Sanity check arguments */
	Assert(module);

	if (type == FREQM_CALLBACK_MEASURE_DONE){
		module->hw->INTENSET.reg = FREQM_INTENSET_DONE;
	} else {
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}

	system_interrupt_enable(SYSTEM_INTERRUPT_MODULE_FREQM);
	return STATUS_OK;
}

/**
 * \brief Disable an FREQM callback.
 *
 * \param[in,out] module  Pointer to the software instance struct
 * \param[in]  type Callback source type
 *
 * \return Status of the callback enable operation.
 * \retval STATUS_OK The callback was enabled successfully
 * \retval STATUS_ERR_INVALID_ARG If an invalid callback type was supplied
 */
static inline enum status_code freqm_disable_callback(struct freqm_module *const module,
		 const enum freqm_callback_type type)
{
	/* Sanity check arguments */
	Assert(module);

	if (type == FREQM_CALLBACK_MEASURE_DONE){
		module->hw->INTENCLR.reg = FREQM_INTENCLR_DONE;
	} else {
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}

	system_interrupt_disable(SYSTEM_INTERRUPT_MODULE_FREQM);
	return STATUS_OK;
}

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* FREQM_CALLBACK_H_INCLUDED */
