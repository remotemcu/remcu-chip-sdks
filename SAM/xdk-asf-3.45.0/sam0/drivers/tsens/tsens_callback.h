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
/**
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef TSENS_CALLBACK_H_INCLUDED
#define TSENS_CALLBACK_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <compiler.h>
#include <system_interrupt.h>
#include "tsens.h"

/**
 * \addtogroup asfdoc_sam0_tsens_group
 *
 * @{
 */

/**
 * \brief TSENS Callback Types.
 *
 * Callback types for TSENS callback driver.
 *
 */
enum tsens_callback {
	/** Callback for result ready */
	TSENS_CALLBACK_RESULT_READY,
	/** Callback when result overwritten before read */
	TSENS_CALLBACK_OVERRUN,
	/** Callback when window is hit */
	TSENS_CALLBACK_WINDOW,
	/** Callback when the result overflows */
	TSENS_CALLBACK_OVF,
#  if !defined(__DOXYGEN__)
	/** Number of available callbacks */
	TSENS_CALLBACK_NUM,
#  endif
};

/** Type of the callback functions. */
typedef void (*tsens_callback_t)(enum tsens_callback);

/**
 * \brief TSENS software device instance structure.
 *
 * TSENS software instance structure, used to retain software state information
 * of an associated hardware module instance.
 *
 * \note The fields of this structure should not be altered by the user
 *       application; they are reserved for module-internal use only.
 */
struct tsens_module {
#if !defined(__DOXYGEN__)
	/** Array to store callback functions. */
	tsens_callback_t callback[TSENS_CALLBACK_NUM];
	/** Pointer to used for TSENS results. */
	volatile int32_t *value;
#endif
};

/**
 * \name Callback Management
 * @{
 */
enum status_code tsens_register_callback(
			struct tsens_module *const module,
			tsens_callback_t callback_func,
			enum tsens_callback callback_type);

enum status_code tsens_unregister_callback(
			struct tsens_module *const module,
			enum tsens_callback callback_type);

/**
 * \brief Enables callback.
 *
 * Enables the callback function registered by \ref
 * tsens_register_callback. The callback function will be called from the
 * interrupt handler when the conditions for the callback type are met.
 *
 * \param[in]     callback_type Callback type given by an enum
 *
 */
static inline void tsens_enable_callback(enum tsens_callback callback_type)
{
	uint32_t inenset_temp = 0;

	switch (callback_type) {
		case TSENS_CALLBACK_RESULT_READY:
			inenset_temp |= TSENS_INTFLAG_RESRDY;
			break;
		case TSENS_CALLBACK_OVERRUN:
			inenset_temp |= TSENS_INTENSET_OVERRUN;
			break;
		case TSENS_CALLBACK_WINDOW:
			inenset_temp |= TSENS_INTENSET_WINMON;
			break;
		case TSENS_CALLBACK_OVF:
			inenset_temp |= TSENS_INTENSET_OVF;
			break;

		default:
			break;
	}

	/* Enable the interrupt for the callback */
	TSENS->INTENSET.reg = inenset_temp;
}

/**
 * \brief Disables callback.
 *
 * Disables the callback function registered by the \ref
 * tsens_register_callback.
 *
 * \param[in]     callback_type Callback type given by an enum
 *
 */
static inline void tsens_disable_callback(enum tsens_callback callback_type)
{
	uint32_t inenclr_temp = 0;

	switch (callback_type) {
		case TSENS_CALLBACK_RESULT_READY:
			inenclr_temp |= TSENS_INTENCLR_OVERRUN;
			break;
		case TSENS_CALLBACK_OVERRUN:
			inenclr_temp |= TSENS_INTENSET_OVERRUN;
			break;
		case TSENS_CALLBACK_WINDOW:
			inenclr_temp |= TSENS_INTENSET_WINMON;
			break;
		case TSENS_CALLBACK_OVF:
			inenclr_temp |= TSENS_INTENSET_OVF;
			break;

		default:
			break;
	}

	/* Disable the interrupt for the callback */
	TSENS->INTENCLR.reg = inenclr_temp;
}

void tsens_read_job(struct tsens_module *const module_inst, int32_t *result);
/** @} */

/** @} */
#ifdef __cplusplus
}
#endif

#endif /* TSENS_CALLBACK_H_INCLUDED */
