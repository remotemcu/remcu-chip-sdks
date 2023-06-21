/**
 * \file
 *
 * \brief SAM Peripheral Access Controller Driver
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

#include "pac.h"

/**
 * \brief Lock a given peripheral's control registers.
 *
 * Locks a given peripheral's control registers, to deny write access to the
 * peripheral to prevent accidental changes to the module's configuration.
 *
 * \warning Locking an already locked peripheral will cause a CPU
 *          exception, and terminate program execution.
 *
 * \param[in] peripheral_id  ID for the peripheral to be locked, sourced via the
 *                           \ref SYSTEM_PERIPHERAL_ID macro
 * \param[in] key  Bitwise inverse of peripheral ID, used as key to
 *                 reduce the chance of accidental locking. See
 *                 \ref asfdoc_sam0_pac_bitwise_code
 *
 * \return Status of the peripheral lock procedure.
 * \retval STATUS_OK                If the peripheral was successfully locked
 * \retval STATUS_ERR_INVALID_ARG	If invalid argument(s) were supplied
 */
__no_inline enum status_code system_peripheral_lock(
		const uint32_t peripheral_id,
		const uint32_t key)
{
	/* Check if key is correct. */
	if (~peripheral_id != key) {
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}

	PAC->WRCTRL.reg = peripheral_id | PAC_WRCTRL_KEY(PAC_WRCTRL_KEY_SET_Val);

	return STATUS_OK;
}

/**
 * \brief Lock a given peripheral's control registers until hardware reset.
 *
 * Locks a given peripheral's control registers, to deny write access to the
 * peripheral to prevent accidental changes to the module's configuration.
 * After lock, the only way to unlock is hardware reset.
 *
 * \warning Locking an already locked peripheral will cause a CPU
 *          exception, and terminate program execution.
 *
 * \param[in] peripheral_id  ID for the peripheral to be locked, sourced via the
 *                           \ref SYSTEM_PERIPHERAL_ID macro
 * \param[in] key  Bitwise inverse of peripheral ID, used as key to
 *                 reduce the chance of accidental locking. See
 *                 \ref asfdoc_sam0_pac_bitwise_code
 *
 * \return Status of the peripheral lock procedure.
 * \retval STATUS_OK                If the peripheral was successfully locked
 * \retval STATUS_ERR_INVALID_ARG	If invalid argument(s) were supplied
 */
__no_inline enum status_code system_peripheral_lock_always(
		const uint32_t peripheral_id,
		const uint32_t key)
{
	/* Check if key is correct. */
	if (~peripheral_id != key) {
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}

	PAC->WRCTRL.reg = peripheral_id | PAC_WRCTRL_KEY(PAC_WRCTRL_KEY_SETLCK_Val);

	return STATUS_OK;
}

/**
 * \brief Unlock a given peripheral's control registers.
 *
 * Unlocks a given peripheral's control registers, allowing write access to the
 * peripheral so that changes can be made to the module's configuration.
 *
 * \warning Unlocking an already locked peripheral will cause a CUP
 *          exception, and terminate program execution.
 *
 * \param[in] peripheral_id  ID for the peripheral to be unlocked, sourced via the
 *                          \ref SYSTEM_PERIPHERAL_ID macro
 * \param[in] key  Bitwise inverse of peripheral ID, used as key to
 *                 reduce the chance of accidental unlocking. See
 *                 \ref asfdoc_sam0_pac_bitwise_code
 *
 * \return Status of the peripheral unlock procedure.
 * \retval STATUS_OK                If the peripheral was successfully locked
 * \retval STATUS_ERR_INVALID_ARG	If invalid argument(s) were supplied
 */
__no_inline enum status_code system_peripheral_unlock(
		const uint32_t peripheral_id,
		const uint32_t key)
{
	/* Check if key is correct. */
	if (~peripheral_id != key) {
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}

	PAC->WRCTRL.reg = peripheral_id | PAC_WRCTRL_KEY(PAC_WRCTRL_KEY_CLR_Val);

	return STATUS_OK;
}
