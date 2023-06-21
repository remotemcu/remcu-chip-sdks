/**
 * \file
 *
 * \brief SAM Peripheral Access Controller Driver
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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
 * \warning Locking an already locked peripheral will cause a hard fault
 *          exception, and terminate program execution.
 *
 * \param[in] peripheral_id  ID for the peripheral to be locked, sourced via the
 *                           \ref SYSTEM_PERIPHERAL_ID macro.
 * \param[in] key  Bitwise inverse of peripheral ID, used as key to
 *                 reduce the chance of accidental locking. See
 *                 \ref asfdoc_sam0_pac_bitwise_code.
 *
 * \return Status of the peripheral lock procedure.
 * \retval STATUS_OK                If the peripheral was successfully locked.
 * \retval STATUS_ERR_INVALID_ARG	If invalid argument(s) were supplied.
 */
__no_inline enum status_code system_peripheral_lock(
		const uint32_t peripheral_id,
		const uint32_t key)
{
	/* Bit to be set in desired register is given by bit 5:0 */
	uint8_t register_bit_pos = peripheral_id % 32;
	UNUSED(register_bit_pos);

	/* Value of which PAC register to use is given by bit 31:6 */
	uint8_t register_pos = peripheral_id / 32;

	/* Check if key is correct. */
	if (~peripheral_id != key) {
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}

	switch (register_pos) {
#ifdef PAC0
		case 0:
			PAC0->WPSET.reg = (1 << register_bit_pos);
			break;
#endif
#ifdef PAC1
		case 1:
			PAC1->WPSET.reg = (1 << register_bit_pos);
			break;
#endif
#ifdef PAC2
		case 2:
			/* Turn on the digital interface clock */
			system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBC, PM_APBCMASK_PAC2);
			PAC2->WPSET.reg = (1 << register_bit_pos);
			break;
#endif
		default:
			Assert(false);
			return STATUS_ERR_INVALID_ARG;
	}

	return STATUS_OK;
}

/**
 * \brief Unlock a given peripheral's control registers.
 *
 * Unlocks a given peripheral's control registers, allowing write access to the
 * peripheral so that changes can be made to the module's configuration.
 *
 * \warning Unlocking an already locked peripheral will cause a hard fault
 *          exception, and terminate program execution.
 *
 * \param[in] peripheral_id  ID for the peripheral to be unlocked, sourced via the
 *                          \ref SYSTEM_PERIPHERAL_ID macro.
 * \param[in] key  Bitwise inverse of peripheral ID, used as key to
 *                 reduce the chance of accidental unlocking. See
 *                 \ref asfdoc_sam0_pac_bitwise_code.
 *
 * \return Status of the peripheral unlock procedure.
 * \retval STATUS_OK                If the peripheral was successfully locked.
 * \retval STATUS_ERR_INVALID_ARG	If invalid argument(s) were supplied.
 */
__no_inline enum status_code system_peripheral_unlock(
		const uint32_t peripheral_id,
		const uint32_t key)
{
	/* Bit to be set in desired register is given by bit 5:0 */
	uint8_t register_bit_pos = peripheral_id % 32;
	UNUSED(register_bit_pos);

	/* Value of which PAC register to use is given by bit 31:6 */
	uint8_t register_pos = peripheral_id / 32;

	/* Check if key is correct. */
	if (~peripheral_id != key) {
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}

	switch (register_pos) {
#ifdef PAC0
		case 0:
			PAC0->WPCLR.reg = (1 << register_bit_pos);
			break;
#endif
#ifdef PAC1
		case 1:
			PAC1->WPCLR.reg = (1 << register_bit_pos);
			break;
#endif
#ifdef PAC2
		case 2:
			/* Turn on the digital interface clock */
			system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBC, PM_APBCMASK_PAC2);
			PAC2->WPCLR.reg = (1 << register_bit_pos);
			break;
#endif
		default:
			Assert(false);
			return STATUS_ERR_INVALID_ARG;
	}

	return STATUS_OK;
}
