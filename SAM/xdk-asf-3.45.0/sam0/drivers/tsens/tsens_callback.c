/**
 * \file
 *
 * \brief SAM Temperature Sensor Driver
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

#include "tsens_callback.h"

struct tsens_module *_tsens_instances;

/** Interrupt handler for the TSENS module. */
void TSENS_Handler(void)
{
	struct tsens_module *module = _tsens_instances;
	Assert(module);

	/* get interrupt flags and mask out enabled callbacks */
	uint32_t flags = TSENS->INTFLAG.reg;

	/* store TSENS result in job buffer */
	uint32_t temp = TSENS->VALUE.reg;
	if(temp & 0x00800000) {
		temp |= ~TSENS_VALUE_MASK;
	}

#if (ERRATA_14476)
	*(module->value) = temp * (-1);
#else
	*(module->value) = temp;
#endif

	for(uint8_t i = 0; i < TSENS_CALLBACK_NUM; i++)
	{
		if (flags & ((uint32_t)0x01 << i)) {
			/* Clear the INTFLAG anyway */
			TSENS->INTFLAG.reg = (uint32_t)0x01 << i;

			if(module->callback[i] != NULL) {
				module->callback[i]((enum tsens_callback)i);
			}
		}
	}
}

/**
 * \brief Registers a callback.
 *
 * Registers a callback function which is implemented by the user.
 *
 * \note The callback must be enabled by for the interrupt handler to call it
 * when the condition for the callback is met.
 *
 * \param[in] module         Pointer to TSENS software instance struct
 * \param[in] callback_func  Pointer to callback function
 * \param[in] callback_type  Callback type given by an enum
 *
 */
enum status_code tsens_register_callback(
		struct tsens_module *const module,
		tsens_callback_t callback_func,
		enum tsens_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(callback_func);

	if(callback_type > TSENS_CALLBACK_NUM) {
		return STATUS_ERR_INVALID_ARG;
	}

	/* Register callback function */
	module->callback[callback_type] = callback_func;
	_tsens_instances = module;

	return STATUS_OK;
}

/**
 * \brief Unregisters a callback.
 *
 * Unregisters a callback function which is implemented by the user.
 *
 * \param[in] module         Pointer to TSENS software instance struct
 * \param[in] callback_type  Callback type given by an enum
 *
 */
enum status_code tsens_unregister_callback(
		struct tsens_module *const module,
		enum tsens_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);

	if(callback_type > TSENS_CALLBACK_NUM) {
		return STATUS_ERR_INVALID_ARG;
	}

	/* Register callback function */
	module->callback[callback_type] = NULL;

	return STATUS_OK;
}

/**
 * \brief Read result from TSENS.
 *
 * \param[in]  module_inst  Pointer to the TSENS software instance struct
 * \param[out] result       Pointer to store the TSENS result
 *
 */
void tsens_read_job(
		struct tsens_module *const module_inst,
		int32_t *result)
{
	Assert(module_inst);
	Assert(result);

	module_inst->value = result;

	if(!(TSENS->CTRLC.reg & TSENS_CTRLC_FREERUN)) {
		tsens_start_conversion();
	}
}
