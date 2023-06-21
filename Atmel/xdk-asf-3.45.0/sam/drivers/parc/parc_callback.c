/**
 * \file
 *
 * \brief SAM4L PARC driver (callback).
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

#include <parc.h>
#include <parc_callback.h>
#include <sysclk.h>

struct parc_module *parc_module_instance;
void _parc_interrupt_handler(void);

/**
 * \internal PARC interrupt entry handler.
 */
void PARC_Handler(void)
{
	_parc_interrupt_handler();
}

/**
 * \internal PARC interrupt handler.
 */
void _parc_interrupt_handler(void)
{
	struct parc_module *module = parc_module_instance;

	/* get interrupt flags and mask out enabled callbacks */
	uint32_t flags = module->hw->PARC_SR;

	if (flags & PARC_INTERRUPT_DRDY) {
		if(module->enabled_callback_mask & (1 << PARC_CALLBACK_DATA_READY)) {
			(*(module->callback[PARC_CALLBACK_DATA_READY]))(module);
		}
		parc_clear_status(module, PARC_STATUS_DRDY);
	}

	if (flags & PARC_INTERRUPT_OVR) {
		if(module->enabled_callback_mask & (1 << PARC_CALLBACK_OVERRUN)) {
			(*(module->callback[PARC_CALLBACK_OVERRUN]))(module);
		}
		parc_clear_status(module, PARC_STATUS_OVR);
	}
}

/**
 * \brief Register a PARC interrupt callback function.
 *
 * \note The callback must be enabled by using \ref parc_enable_callback.
 *
 * \param[in,out] module    Driver structure pointer
 * \param[in] callback_func Pointer to a callback function
 * \param[in] callback_type \ref parc_callback_type "Interrupt callback" type
 *
 * \return The status of the interrupt callback register operation.
 * \retval STATUS_OK PARC interrupt callback was registered successfully
 */
enum status_code parc_register_callback(
		struct parc_module *const module,
		parc_callback_t const callback_func,
		enum parc_callback_type callback_type)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(callback_func);

	/* Register callback function */
	module->callback[callback_type] = callback_func;

	/* Set the bit corresponding to the callback_type */
	module->registered_callback_mask |= (1 << callback_type);

	return STATUS_OK;
}

/**
 * \brief Unregister a PARC interrupt callback.
 *
 * \param[in,out] module    Driver structure pointer
 * \param[in] callback_type \ref parc_callback_type "Interrupt callback" type
 *
 * \return The status of the interrupt callback unregister operation.
 * \retval STATUS_OK PARC interrupt callback was unregistered successfully
 */
enum status_code  parc_unregister_callback(
		struct parc_module *const module,
		enum parc_callback_type callback_type)
{
	/* Sanity check arguments */
	Assert(module);

	/* Unregister callback function */
	module->callback[callback_type] = NULL;

	/* Clear the bit corresponding to the callback_type */
	module->registered_callback_mask &= ~(1 << callback_type);

	return STATUS_OK;
}
