/**
 * \file
 *
 * \brief SAM AC - Analog Comparator Callback Driver
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

#include "ac_callback.h"

struct ac_module *_ac_instance[AC_INST_NUM];

void _ac_interrupt_handler(const uint32_t instance_index);

/**
 * \brief Registers a callback.
 *
 * Registers a callback function which is implemented by the user.
 *
 * \note The callback must be enabled by \ref ac_enable_callback,
 * in order for the interrupt handler to call it when the conditions for the
 * callback type is met.
 *
 * \param[in]     module      Pointer to software instance struct
 * \param[in]     callback_func Pointer to callback function
 * \param[in]     callback_type Callback type given by an enum
 *
 * \retval STATUS_OK  The function exited successfully
 */
enum status_code ac_register_callback(
		struct ac_module *const module,
		ac_callback_t callback_func,
		const enum ac_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(callback_func);

	/* Register callback function */
	module->callback[callback_type] = callback_func;

	/* Set software flag for callback */
	module->register_callback_mask |= (1 << callback_type);

	return STATUS_OK;
}

/**
 * \brief Unregisters a callback.
 *
 * Unregisters a callback function implemented by the user.
 *
 * \param[in]     module Pointer to AC software instance struct
 * \param[in]     callback_type Callback type given by an enum
 *
 * \retval STATUS_OK  The function exited successfully
 */
enum status_code ac_unregister_callback(
		struct ac_module *const module,
		const enum ac_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);
	/* Unregister callback function */
	module->callback[callback_type] = NULL;

	/* Clear software flag for callback */
	module->register_callback_mask &= ~(1 << callback_type);

	return STATUS_OK;
}

/**
 * \internal ISR handler for AC
 */
#if (AC_INST_NUM == 1)
void AC_Handler(void)
{
	_ac_interrupt_handler(0);
}
#elif (AC_INST_NUM == 2)
void AC_Handler(void)
{
	_ac_interrupt_handler(0);
}

void AC1_Handler(void)
{
	_ac_interrupt_handler(1);
}
#else
#  error This driver is not support more than three AC instances.
#endif

/**
 * \brief Interrupt Handler for AC module.
 *
 * Handles interrupts as they occur, it will run the callback functions
 * that are registered and enabled.
 *
 * \param [in] instance_index  Default value 0
 */
void _ac_interrupt_handler(const uint32_t instance_index)
{
	/* Temporary variable */
	uint8_t interrupt_and_callback_status_mask;

	/* Get device instance from the look-up table */

	struct ac_module *module = _ac_instance[instance_index];

	/* Read and mask interrupt flag register */
	interrupt_and_callback_status_mask =
			_ac_instance[instance_index]->hw->INTFLAG.reg &
			(module->register_callback_mask & module->enable_callback_mask);

	/* Check if comparator channel 0 needs to be serviced */
	if (interrupt_and_callback_status_mask & AC_INTFLAG_COMP0) {
		/* Invoke registered and enabled callback function */
		(module->callback[AC_CALLBACK_COMPARATOR_0])(module);
		/* Clear interrupt flag */
		module->hw->INTFLAG.reg = AC_INTFLAG_COMP0;
	}

	/* Check if comparator channel 1 needs to be serviced */
	if (interrupt_and_callback_status_mask & AC_INTFLAG_COMP1) {
		/* Invoke registered and enabled callback function */
		(module->callback[AC_CALLBACK_COMPARATOR_1])(module);
		/* Clear interrupt flag */
		module->hw->INTFLAG.reg = AC_INTFLAG_COMP1;
	}

	/* Check if window 0 needs to be serviced */
	if (interrupt_and_callback_status_mask & AC_INTFLAG_WIN0) {
		/* Invoke registered and enabled callback function */
		(module->callback[AC_CALLBACK_WINDOW_0])(module);
		/* Clear interrupt flag */
		module->hw->INTFLAG.reg = AC_INTFLAG_WIN0;
	}

#if (AC_NUM_CMP > 2)
		/* Check if comparator channel 2 needs to be serviced */
	if (interrupt_and_callback_status_mask & AC_INTFLAG_COMP2) {
		/* Invoke registered and enabled callback function */
		(module->callback[AC_CALLBACK_COMPARATOR_2])(module);
		/* Clear interrupt flag */
		module->hw->INTFLAG.reg = AC_INTFLAG_COMP2;
	}

	/* Check if comparator channel 3 needs to be serviced */
	if (interrupt_and_callback_status_mask & AC_INTFLAG_COMP3) {
		/* Invoke registered and enabled callback function */
		(module->callback[AC_CALLBACK_COMPARATOR_3])(module);
		/* Clear interrupt flag */
		module->hw->INTFLAG.reg = AC_INTFLAG_COMP3;
	}

#  if !(SAMC20)
		/* Check if window 1 needs to be serviced */
	if (interrupt_and_callback_status_mask & AC_INTFLAG_WIN1) {
		/* Invoke registered and enabled callback function */
		(module->callback[AC_CALLBACK_WINDOW_1])(module);
		/* Clear interrupt flag */
		module->hw->INTFLAG.reg = AC_INTFLAG_WIN1;
	}
#  endif
#endif /* (AC_NUM_CMP > 2) */
}
