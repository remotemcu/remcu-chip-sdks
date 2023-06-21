/**
 *
 * \file
 *
 * \brief SAM Advanced Encryption Standard driver.
 *
 * This file defines a useful set of functions for the AES on SAM devices.
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

#ifndef AES_CALLBACK_H_INCLUDED
#define AES_CALLBACK_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <compiler.h>
#include <system_interrupt.h>
/**
 * \addtogroup asfdoc_sam0_drivers_aes_group
 *
 * @{
 */

/** AES interrupt callback function type. */
typedef void (*aes_callback_t)(void); 

/** AES callback type. */
enum aes_callback_type {
	/** Encryption complete callback */
	AES_CALLBACK_ENCRYPTION_COMPLETE = 0,
	/** GF Multiplication Complete callback */
	AES_CALLBACK_GF_MULTI_COMPLETE = 1,
};
 
/** \name Callback Configuration and Initialization
 * @{
 */
 
enum status_code aes_register_callback(
	const aes_callback_t callback,
	const enum aes_callback_type type);

enum status_code aes_unregister_callback(
	const aes_callback_t callback,
	const enum aes_callback_type type);

/** @} */


/** \name Callback Enabling and Disabling
 * @{
 */

/**
 * \brief Enable an AES callback.
 *
 * \param[in,out] module  Pointer to the software instance struct
 * \param[in] type Callback source type
 *
 * \return Status of the callback enable operation.
 * \retval STATUS_OK The callback was enabled successfully
 * \retval STATUS_ERR_INVALID_ARG If an invalid callback type was supplied
 */
static inline enum status_code aes_enable_callback(struct aes_module *const module,
		const enum aes_callback_type type)
{
	system_interrupt_enable(SYSTEM_INTERRUPT_MODULE_AES);
	if (type == AES_CALLBACK_ENCRYPTION_COMPLETE){
		module->hw->INTENSET.reg = AES_INTENSET_ENCCMP;
	} else if (type == AES_CALLBACK_GF_MULTI_COMPLETE){
		module->hw->INTENSET.reg = AES_INTENSET_GFMCMP;
	} else {
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}

	return STATUS_OK;
}

/**
 * \brief Disable an AES callback.
 *
 * \param[in,out] module  Pointer to the software instance struct
 * \param[in]  type Callback source type
 *
 * \return Status of the callback enable operation.
 * \retval STATUS_OK The callback was enabled successfully
 * \retval STATUS_ERR_INVALID_ARG If an invalid callback type was supplied
 */
static inline enum status_code aes_disable_callback(struct aes_module *const module,
		 const enum aes_callback_type type)
{
	system_interrupt_disable(SYSTEM_INTERRUPT_MODULE_AES);
	if (type == AES_CALLBACK_ENCRYPTION_COMPLETE){
		module->hw->INTENCLR.reg = AES_INTENCLR_ENCCMP;
	} else if (type == AES_CALLBACK_GF_MULTI_COMPLETE){
		module->hw->INTENCLR.reg = AES_INTENCLR_GFMCMP;
	} else {
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}

	return STATUS_OK;
}

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* AES_CALLBACK_H_INCLUDED */
