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

#ifndef AC_CALLBACK_H_INCLUDED
#define AC_CALLBACK_H_INCLUDED

#include <compiler.h>
#include <system_interrupt.h>
#include "ac.h"

#ifdef __cplusplus
extern "C" {
#endif

#if (AC_INST_NUM > 1) && !defined(__DOXYGEN__)
/**
 * \internal Get the interrupt vector for the given device instance
 *
 * \param[in] TC module instance number
 *
 * \return Interrupt vector for of the given TC module instance.
 */
static enum system_interrupt_vector _ac_interrupt_get_interrupt_vector(
		uint32_t inst_num)
{
	static uint8_t ac_interrupt_vectors[AC_INST_NUM] =
		{
			SYSTEM_INTERRUPT_MODULE_AC,
#if (AC_INST_NUM == 2)
			SYSTEM_INTERRUPT_MODULE_AC1,
#endif
#if (AC_INST_NUM >= 3)
#  error This driver is not support more than three AC instances.
#endif
		};

	return ac_interrupt_vectors[inst_num];
}
#endif /* (AC_INST_NUM > 1) !defined(__DOXYGEN__)*/

/**
 * \name Callback Management
 * {@
 */

enum status_code ac_register_callback(
		struct ac_module *const module,
		ac_callback_t callback_func,
		const enum ac_callback callback_type);

enum status_code ac_unregister_callback(
		struct ac_module *const module,
		const enum ac_callback callback_type);

/**
 * \brief Enables callback.
 *
 * Enables the callback function registered by the \ref
 * ac_register_callback. The callback function will be called from the
 * interrupt handler when the conditions for the callback type are
 * met. This function will also enable the appropriate interrupts.
 *
 * \param[in]     module Pointer to AC software instance struct
 * \param[in]     callback_type Callback type given by an enum
 */
static inline void ac_enable_callback(
		struct ac_module *const module,
		const enum ac_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);

	/* Set software flag for the callback */
	module->enable_callback_mask |= (1 << callback_type);

	uint32_t inenset_temp = 0;

	switch (callback_type)
	{
		case AC_CALLBACK_COMPARATOR_0:
			inenset_temp |= AC_INTFLAG_COMP0;
			break;
		case AC_CALLBACK_COMPARATOR_1:
			inenset_temp |= AC_INTFLAG_COMP1;
			break;
		case AC_CALLBACK_WINDOW_0:
			inenset_temp |= AC_INTFLAG_WIN0;
			break;
#if (AC_NUM_CMP > 2)
		case AC_CALLBACK_COMPARATOR_2:
			inenset_temp |= AC_INTFLAG_COMP2;
			break;
		case AC_CALLBACK_COMPARATOR_3:
			inenset_temp |= AC_INTFLAG_COMP3;
			break;
#  if !(SAMC20)
		case AC_CALLBACK_WINDOW_1:
			inenset_temp |= AC_INTFLAG_WIN1;
			break;
#  endif
#endif
		default:
			break;
	}

	/* Enable the interrupt for the callback */
	module->hw->INTENSET.reg = inenset_temp;

#if (AC_INST_NUM == 1)
	/* Enable interrupts for AC module */
	system_interrupt_enable(SYSTEM_INTERRUPT_MODULE_AC);
#elif (AC_INST_NUM > 1)
	system_interrupt_enable(_ac_interrupt_get_interrupt_vector(_ac_get_inst_index(module->hw)));
#endif /* (AC_INST_NUM > 1) */
}

/**
 * \brief Disables callback.
 *
 * Disables the callback function registered by the \ref
 * ac_register_callback, and the callback will not be called from the
 * interrupt routine. The function will also disable the appropriate
 * interrupts.
 *
 * \param[in]     module Pointer to AC software instance struct
 * \param[in]     callback_type Callback type given by an enum
 */
static inline void ac_disable_callback(
		struct ac_module *const module,
		const enum ac_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);

	/* Clear software flag for the callback */
	module->enable_callback_mask &= ~(1 << callback_type);

	uint32_t inenclr_temp = 0;

	switch (callback_type)
	{
		case AC_CALLBACK_COMPARATOR_0:
			inenclr_temp |= AC_INTFLAG_COMP0;
			break;
		case AC_CALLBACK_COMPARATOR_1:
			inenclr_temp |= AC_INTFLAG_COMP1;
			break;
		case AC_CALLBACK_WINDOW_0:
			inenclr_temp |= AC_INTFLAG_WIN0;
			break;
#if (AC_NUM_CMP > 2)
		case AC_CALLBACK_COMPARATOR_2:
			inenclr_temp |= AC_INTFLAG_COMP2;
			break;
		case AC_CALLBACK_COMPARATOR_3:
			inenclr_temp |= AC_INTFLAG_COMP3;
			break;
#  if !(SAMC20)
		case AC_CALLBACK_WINDOW_1:
			inenclr_temp |= AC_INTFLAG_WIN1;
			break;
#  endif
#endif
		default:
			break;
	}

	/* Disable the interrupt for the callback */
	module->hw->INTENCLR.reg = inenclr_temp;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* AC_CALLBACK_H_INCLUDED */
