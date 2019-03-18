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

#include "freqm.h"
#include "freqm_callback.h"

/** \internal Max number of callback type. */
#define FREQM_CALLBACK_TYPE_NUM 1

struct freqm_module *_freqm_instance;


/**
 * \brief Registers a callback
 *
 * Registers a callback function which is implemented by the user.
 *
 * \note The callback must be enabled by \ref freqm_enable_callback,
 * in order for the interrupt handler to call it when the conditions for the
 * callback type is met.
 *
 * \param[in]     module        Pointer to FREQM software instance struct
 * \param[in]     callback_func Pointer to callback function
 * \param[in]     callback_type Callback type given by an enum
 *
 * \retval STATUS_OK  The function exited successfully
 */
enum status_code freqm_register_callback(
		struct freqm_module *const module,
		freqm_callback_t callback_func,
		enum freqm_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(callback_func);

	if (callback_type >= FREQM_CALLBACK_TYPE_NUM) {
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}
	/* Register callback function */
	module->callback[callback_type] = callback_func;

	return STATUS_OK;
}

/**
 * \brief Unregisters a callback
 *
 * Unregisters a callback function implemented by the user. The callback should be
 * disabled before it is unregistered.
 *
 * \param[in]     module        Pointer to FREQM software instance struct
 * \param[in]     callback_type Callback type given by an enum
 *
 * \retval STATUS_OK  The function exited successfully
 */
enum status_code freqm_unregister_callback(
		struct freqm_module *module,
		enum freqm_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);

	if (callback_type >= FREQM_CALLBACK_TYPE_NUM) {
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}
	/* Unregister callback function */
	module->callback[callback_type] = NULL;

	return STATUS_OK;
}



/**
* \internal The FREQM interrupt handler.
*/
void FREQM_Handler(void)
{
	/* Get device instance from the look-up table */
	struct freqm_module *module = _freqm_instance;

	/* Read and mask interrupt flag register */
	uint32_t status = FREQM->INTFLAG.reg;

	/* Check if data ready needs to be serviced */
	if (status & FREQM_INTFLAG_DONE) {
		if (module->callback[FREQM_CALLBACK_MEASURE_DONE]) {
			FREQM->INTFLAG.reg = FREQM_INTFLAG_DONE;
			module->callback[FREQM_CALLBACK_MEASURE_DONE]();
		}
	}

}
