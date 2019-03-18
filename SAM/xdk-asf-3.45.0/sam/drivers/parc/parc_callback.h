/**
 * \file
 *
 * \brief SAM4L PARC driver(callback) for SAM.
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

#ifndef PARC_CALLBACK_H_INCLUDED
#define PARC_CALLBACK_H_INCLUDED

#include <parc.h>

/** \addtogroup asfdoc_sam_drivers_parc_group
 * @{
 */

/// @cond
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

enum status_code parc_register_callback(struct parc_module *const module,
		parc_callback_t const callback_func,
		enum parc_callback_type callback_type);

enum status_code parc_unregister_callback(struct parc_module *const module,
		enum parc_callback_type callback_type);
		
/**
 * \brief Enable a PARC interrupt callback function.
 *
 * \note The callback function will be called from the PARC interrupt handler
 * when the callback's corresponding interrupt is asserted.
 *
 * \param[in,out] module_inst Driver structure pointer
 * \param[in]  type           \ref parc_callback_type "Interrupt callback" to enable
 *
 * \return The status of the interrupt callback enable operation.
 * \retval STATUS_OK Interrupt callback enabled successfully
 */
static inline enum status_code parc_enable_callback(
	struct parc_module *const module_inst,
	enum parc_callback_type type)
{
	/* Sanity check arguments */
	Assert(module_inst);

	/* Enable callback */
	module_inst->enabled_callback_mask |= (1 << type);

	return STATUS_OK;
}

/**
 * \brief Disable a PARC interrupt callback function.
 *
 * \param[in,out] module_inst Driver structure pointer
 * \param[in]  type           \ref parc_callback_type "Interrupt callback" to disable
 *
 * \return The status of the interrupt callback disable operation.
 * \retval STATUS_OK Interrupt callback disabled successfully
 */
static inline enum status_code parc_disable_callback(
	struct parc_module *const module_inst,
	enum parc_callback_type type)
{
	/* Sanity check arguments */
	Assert(module_inst);

	/* Disable callback */
	module_inst->enabled_callback_mask &= ~(1 << type);

	return STATUS_OK;
}

/// @cond
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

/** @} */

#endif  /* PARC_CALLBACK_H_INCLUDED */
