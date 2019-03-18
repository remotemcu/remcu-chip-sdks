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

#include "aes.h"
#include "aes_callback.h"

/** \internal Max number of callback type. */
#define AES_CALLBACK_TYPE_NUM 2

/**
* \internal
* \brief AES callback function pointer
*/
aes_callback_t aes_callback_pointer[AES_CALLBACK_TYPE_NUM]={NULL,NULL};


enum status_code aes_register_callback(
	const aes_callback_t callback,
	const enum aes_callback_type type)
{
	if (type >= AES_CALLBACK_TYPE_NUM){
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}

	aes_callback_pointer[type] = callback;
	return STATUS_OK;
}

enum status_code aes_unregister_callback(
	const aes_callback_t callback,
	const enum aes_callback_type type)
{
	if (type >= AES_CALLBACK_TYPE_NUM){
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}

	aes_callback_pointer[type] = NULL;
	return STATUS_OK;
}



/**
* \internal The AES interrupt handler.
*/
void AES_Handler(void)
{
	uint32_t status = AES->INTFLAG.reg;

	if (status & AES_INTFLAG_ENCCMP) {
		if (aes_callback_pointer[AES_CALLBACK_ENCRYPTION_COMPLETE]) {
			AES->INTFLAG.reg = AES_INTFLAG_ENCCMP;
			aes_callback_pointer[AES_CALLBACK_ENCRYPTION_COMPLETE]();
		}
	}

	if (status & AES_INTFLAG_GFMCMP) {
		if (aes_callback_pointer[AES_CALLBACK_ENCRYPTION_COMPLETE]) {
			AES->INTFLAG.reg = AES_INTFLAG_GFMCMP;
			aes_callback_pointer[AES_CALLBACK_ENCRYPTION_COMPLETE]();
		}
	}
}
