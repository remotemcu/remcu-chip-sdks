/**
 * \file
 *
 * \brief USB host Mass Storage interface for control access module..
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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

#include "uhi_msc.h"
#include "uhi_msc_mem.h"

/**
 * \ingroup uhi_msc_mem_group
 * \defgroup uhi_msc_mem_group_internal Implementation of USB host Mass Storage
 * interface for control access module
 *
 * Internal implementation 
 * @{
 */

/**
 * \name Internal variables
 */
//@{
//! Current LUN selected
static uint8_t uhi_msc_mem_lun;
//! \name Volatile flag tested by functions in pooling mode and updated by a callback
//@{
static volatile bool uhi_msc_mem_command_ongoing;
static volatile bool uhi_msc_mem_command_status;
//@}
//@}

/**
 * \name Internal functions
 */
//@{
static void uhi_msc_mem_stop_pooling(bool b_success);
static Ctrl_status uhi_msc_mem_translate_status(lun_status_t status);
//@}


/**
 * \name External functions
 */
//@{

uint8_t uhi_msc_mem_get_lun(void)
{
	while (!uhi_msc_is_available());
	return uhi_msc_get_lun();
}

Ctrl_status uhi_msc_mem_test_unit_ready(uint8_t lun)
{
	uhi_msc_lun_t *lun_desc;

	while (!uhi_msc_is_available());

	uhi_msc_mem_command_ongoing = true;
	uhi_msc_mem_lun = lun;
	if (!uhi_msc_scsi_test_unit_ready(uhi_msc_mem_lun, uhi_msc_mem_stop_pooling)) {
		return CTRL_FAIL;
	}
	while (uhi_msc_mem_command_ongoing);
	if (!uhi_msc_mem_command_status) {
		return CTRL_FAIL;
	}
	lun_desc = uhi_msc_get_lun_desc(uhi_msc_mem_lun);
	return uhi_msc_mem_translate_status(lun_desc->status);
}

Ctrl_status uhi_msc_mem_read_capacity(uint8_t lun, uint32_t * u32_nb_sector)
{
	uhi_msc_lun_t *lun_desc;

	while (!uhi_msc_is_available());
	uhi_msc_mem_lun = lun;
	lun_desc = uhi_msc_get_lun_desc(uhi_msc_mem_lun);
	if (lun_desc == NULL) {
		return CTRL_FAIL;
	}
	if (lun_desc->capacity.block_len != 512) {
		// Note: The ctrl_access module uses only the data transfer size of 512 bytes.
		// The uhi_msc_mem module does not implement a RAM cache 
		// to support the transfer size more than 512 bytes.
		return CTRL_FAIL; // Not supported
	}
	*u32_nb_sector = lun_desc->capacity.max_lba;
	return uhi_msc_mem_translate_status(lun_desc->status);
}

uint8_t uhi_msc_mem_read_sector_size(uint8_t lun)
{
	uhi_msc_lun_t *lun_desc;

	while (!uhi_msc_is_available());
	uhi_msc_mem_lun = lun;
	lun_desc = uhi_msc_get_lun_desc(uhi_msc_mem_lun);
	if (lun_desc == NULL) {
		return 0;
	}
	return lun_desc->capacity.block_len / 512;
}

bool uhi_msc_mem_wr_protect(uint8_t lun)
{
	uhi_msc_lun_t *lun_desc;

	while (!uhi_msc_is_available());
	uhi_msc_mem_lun = lun;
	lun_desc = uhi_msc_get_lun_desc(uhi_msc_mem_lun);
	if (lun_desc == NULL) {
		return true;
	}
	if (lun_desc->capacity.block_len != 512) {
		return true;
	}
	return lun_desc->b_write_protected;
}

bool uhi_msc_mem_removal(void)
{
	return true;
}

Ctrl_status uhi_msc_mem_read_10_ram(uint32_t addr, void *ram)
{
	uhi_msc_lun_t *lun_desc;

	while (!uhi_msc_is_available());
	// uhi_msc_mem_lun already selected by a previous command
	lun_desc = uhi_msc_get_lun_desc(uhi_msc_mem_lun);
	if (lun_desc == NULL) {
		return CTRL_FAIL;
	}
	if (uhi_msc_mem_translate_status(lun_desc->status) != CTRL_GOOD) {
		return uhi_msc_mem_translate_status(lun_desc->status);
	}
	if (lun_desc->capacity.block_len != 512) {
		return CTRL_FAIL; // Not supported
	}
	uhi_msc_mem_command_ongoing = true;
	uhi_msc_scsi_read_10(uhi_msc_mem_lun, addr, ram, 1,
			uhi_msc_mem_stop_pooling);
	while (uhi_msc_mem_command_ongoing);
	if (!uhi_msc_mem_command_status) {
		return CTRL_FAIL;
	}
	return uhi_msc_mem_translate_status(lun_desc->status);

}

Ctrl_status uhi_msc_mem_write_10_ram(uint32_t addr, const void *ram)
{
	uhi_msc_lun_t *lun_desc;

	while (!uhi_msc_is_available());
	// uhi_msc_mem_lun already selected by a previous command
	lun_desc = uhi_msc_get_lun_desc(uhi_msc_mem_lun);
	if (lun_desc == NULL) {
		return CTRL_FAIL;
	}
	if (uhi_msc_mem_translate_status(lun_desc->status) != CTRL_GOOD) {
		return uhi_msc_mem_translate_status(lun_desc->status);
	}
	if (lun_desc->capacity.block_len != 512) {
		return CTRL_FAIL; // Not supported
	}
	uhi_msc_mem_command_ongoing = true;
	uhi_msc_scsi_write_10(uhi_msc_mem_lun, addr, ram, 1,
			uhi_msc_mem_stop_pooling);
	while (uhi_msc_mem_command_ongoing);
	if (!uhi_msc_mem_command_status) {
		return CTRL_FAIL;
	}
	return uhi_msc_mem_translate_status(lun_desc->status);
}

//@}

/**
 * \name Internal functions
 */
//@{

/**
 * \brief Callback to update volatile variable used by pooling
 *
 * \param b_success true, if the scsi command is successful
 */
static void uhi_msc_mem_stop_pooling(bool b_success)
{
	uhi_msc_mem_command_ongoing = false;
	uhi_msc_mem_command_status = b_success;
}

/**
 * \brief Translates the LUN status from UHI MSC to CTRL ACCESS module
 *
 * \param status   UHI MSC LUN status
 *
 * \return CTRL ACCESS LUN status
 */
static Ctrl_status uhi_msc_mem_translate_status(lun_status_t status)
{
	switch (status) {
	case LUN_GOOD:
		return CTRL_GOOD;
	case LUN_NOT_PRESENT:
		return CTRL_NO_PRESENT;
	case LUN_BUSY:
		return CTRL_BUSY;
	case LUN_FAIL:
	default:
		return CTRL_FAIL;
	}
}

//@}

//@}
