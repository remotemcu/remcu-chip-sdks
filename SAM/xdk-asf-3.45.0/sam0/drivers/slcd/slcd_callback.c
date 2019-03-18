/**
 *
 * \file
 *
 * \brief SAM Segment Liquid Crystal Display(SLCD) Controller.
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

#include "slcd.h"
#include "slcd_callback.h"

/**
* \internal
* \brief slcd callback function pointer
*/
slcd_callback_t slcd_callback_pointer[SLCD_CALLBACK_TYPE_NUM];


/**
 * \brief Registers a callback
 *
 * Registers a callback function which is implemented by the user.
 *
 * \note The callback must be enabled by \ref slcd_enable_callback,
 * in order for the interrupt handler to call it when the conditions for the
 * callback type is met.
 *
 * \param[in]     callback_func Pointer to callback function
 * \param[in]     callback_type Callback type given by an enum
 *
 * \retval STATUS_OK  The function exited successfully
 * \retval STATUS_ERR_INVALID_ARG  If an invalid callback type was supplied
 */

enum status_code slcd_register_callback(
	const slcd_callback_t callback,
	const enum slcd_callback_type type)
{
	if (type >= SLCD_CALLBACK_TYPE_NUM){
		return STATUS_ERR_INVALID_ARG;
	}

	slcd_callback_pointer[type] = callback;
	return STATUS_OK;
}

/**
 * \brief Unregisters a callback
 *
 * Unregisters a callback function implemented by the user.
 *
 * \param[in]  callback_type Callback type given by an enum
 *
 * \retval STATUS_OK  The function exited successfully
 * \retval STATUS_ERR_INVALID_ARG  If an invalid callback type was supplied
 */

enum status_code slcd_unregister_callback(
	const slcd_callback_t callback,
	const enum slcd_callback_type type)
{
	if (type >= SLCD_CALLBACK_TYPE_NUM){
		return STATUS_ERR_INVALID_ARG;
	}

	slcd_callback_pointer[type] = NULL;
	return STATUS_OK;
}

/**
* \internal The SLCD interrupt handler.
*/
void SLCD_Handler(void)
{
	uint32_t status = SLCD->INTFLAG.reg;
	for (uint8_t i = 0; i < SLCD_CALLBACK_TYPE_NUM; i++) {
		if (status & (1 << i)) {
			/* Clear the INTFLAG anyway */
			SLCD->INTFLAG.reg = 1 << i;

			if (slcd_callback_pointer[i]) {
				slcd_callback_pointer[i]((enum slcd_callback_type)i);
			}
		}
	}
}
