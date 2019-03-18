/**
 *
 * \file
 *
 * \brief SAM DSU CRC32 driver.
 *
 * This file defines a useful set of functions for DSU CRC32 on SAM devices.
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

#include <system_interrupt.h>
#include <pac.h>
#include <crc32.h>

/**
 * \brief Calculate CRC32 value of the input memory
 *
 * Calculate CRC32 value of the input memory.
 *
 * The read value must be complemented to match standard CRC32 implementations
 * or kept non-inverted if used as starting point for subsequent CRC32 calculations.
 *
 * \param[in] addr    Memory address to calculate CRC32
 * \param[in] len     Memory length to calculate CRC32
 * \param[in,out] pcrc32 Initial value used for the CRC32 calculation, and CRC32 result after calculation
 *
 * \return Status of the configuration procedure.
 *
 * \retval STATUS_OK      If CRC32 calculation OK
 * \retval STATUS_ERR_BAD_ADDRESS  The address was not aligned with 4 bytes.
 
 * \retval STATUS_ERR_IO  A bus error is detected
 */
enum status_code dsu_crc32_cal(const uint32_t addr, const uint32_t len, uint32_t *pcrc32)
{
	if (addr & 0x00000003) {
		return STATUS_ERR_BAD_ADDRESS;
	}

	system_interrupt_disable_global();
	system_peripheral_unlock(SYSTEM_PERIPHERAL_ID(DSU), ~SYSTEM_PERIPHERAL_ID(DSU));

	DSU->DATA.reg = *pcrc32;
	DSU->ADDR.reg = addr;
	DSU->LENGTH.reg = len;

	DSU->CTRL.bit.CRC = 1;
	while ((DSU->STATUSA.reg & DSU_STATUSA_DONE) != 1) {	
	}

	if (DSU->STATUSA.reg & DSU_STATUSA_BERR) {
		system_peripheral_lock(SYSTEM_PERIPHERAL_ID(DSU), ~SYSTEM_PERIPHERAL_ID(DSU));
		system_interrupt_enable_global();
		return STATUS_ERR_IO;
	}

	*pcrc32 = DSU->DATA.reg;
	DSU->STATUSA.reg = DSU_STATUSA_DONE;

	system_peripheral_lock(SYSTEM_PERIPHERAL_ID(DSU), ~SYSTEM_PERIPHERAL_ID(DSU));
	system_interrupt_enable_global();
	return STATUS_OK;
}