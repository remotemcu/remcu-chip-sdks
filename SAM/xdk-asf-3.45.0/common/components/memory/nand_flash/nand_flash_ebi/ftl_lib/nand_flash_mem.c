/**
 * \file
 *
 * \brief NAND Flash ctrl access interface definition.
 *
 * This file contains ctrl access interface functions of NAND Flash module.
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

#include "nand_flash_mem.h"
#include "nand_flash_translation.h"
#include <string.h>

#define MODEL(translated)     ((struct nand_flash_model *)translated)

/* NAND Flash device structure. */
static struct nand_flash_translation nf_translation;

#ifdef BOARD_NF_DATA_ADDR
/* Address for transferring command to the NAND Flash. */
static uint32_t cmd_address = BOARD_NF_COMMAND_ADDR;
/* Address for transferring address to the NAND Flash. */
static uint32_t addr_address = BOARD_NF_ADDRESS_ADDR;
/* Address for transferring data to the NAND Flash. */
static uint32_t data_address = BOARD_NF_DATA_ADDR;
#else
# warning There is no NAND Flash module on the board.
/* default address for pass the jenkins. */
static uint32_t cmd_address = 0x60400000;
static uint32_t addr_address = 0x60200000;
static uint32_t data_address = 0x60000000;
#endif

#if ACCESS_USB == true
/** Global NAND Flash temp buffer */
static uint8_t nand_flash_usb_buffer[NAND_COMMON_MAX_PAGE_SIZE];
#endif

/* NAND Flash status. */
static uint32_t nand_flash_status = NAND_FLASH_NOT_INIT;

/* Buffer needed in FTL */
static uint8_t page_write_buffer[NAND_COMMON_MAX_PAGE_SIZE];
static uint8_t page_read_buffer[NAND_COMMON_MAX_PAGE_SIZE];

/**
 * \brief This function tests memory state, and starts memory initialization
 *
 * \return Ctrl_status
 */
Ctrl_status nand_flash_test_unit_ready(void)
{
	switch (nand_flash_status) {
	case NAND_FLASH_NOT_INIT:
		if (nand_flash_translation_initialize(&nf_translation, 0,
				cmd_address, addr_address, data_address, 0,
				0, page_write_buffer, page_read_buffer)) {
			return CTRL_NO_PRESENT;
		}

		nand_flash_status = NAND_FLASH_READY;
		return CTRL_GOOD;

	case NAND_FLASH_READY:
		nand_flash_flush();
		return CTRL_GOOD;

	case NAND_FLASH_BUSY:
		return CTRL_BUSY;

	case NAND_FLASH_UNLOADED:
		return CTRL_NO_PRESENT;

	default:
		return CTRL_BUSY;
	}
}

/**
 * \brief This function returns the address of the last valid sector
 *
 * \param nb_sector  Pointer to number of sectors (sector=512 bytes)
 *
 * \return Ctrl_status
 */
Ctrl_status nand_flash_read_capacity(uint32_t *nb_sector)
{
	if (nand_flash_status == NAND_FLASH_UNLOADED) {
		return CTRL_NO_PRESENT;
	}

	if (nand_flash_status == NAND_FLASH_NOT_INIT) {
		if (nand_flash_translation_initialize(&nf_translation, 0,
				cmd_address, addr_address, data_address, 0,
				0, page_write_buffer, page_read_buffer)) {
			return CTRL_NO_PRESENT;
		}

		nand_flash_status = NAND_FLASH_READY;
	}

	if (nand_flash_status == NAND_FLASH_READY) {
		*nb_sector
			= nand_flash_translation_get_device_size_in_byte(
				&nf_translation) / SECTOR_SIZE;
		return CTRL_GOOD;
	}

	return CTRL_BUSY;
}

/**
 * \brief This function returns the write-protected mode
 *
 * \return true if the memory is protected
 */
bool nand_flash_wr_protect(void)
{
	return false;
}

/**
 * \brief This function informs about the memory type
 *
 * \return true if the memory is removable
 */
bool nand_flash_removal(void)
{
	return true;
}

/**
 * \brief This function unloads/loads the memory
 *
 * \return true if memory unload/load success
 */
bool nand_flash_unload(bool unload)
{
	if (!unload && nand_flash_status == NAND_FLASH_UNLOADED) {
		nand_flash_status = NAND_FLASH_NOT_INIT;
		return false;
	} else {
		switch (nand_flash_status) {
		case NAND_FLASH_NOT_INIT:
			nand_flash_status = NAND_FLASH_UNLOADED;
			return true;

		case NAND_FLASH_READY:
			nand_flash_flush();
			nand_flash_status = NAND_FLASH_UNLOADED;
			return true;

		case NAND_FLASH_UNLOADED:
			return true;

		default:
			return false;
		}
	}
}

/* ------------ SPECIFIC FUNCTIONS FOR TRANSFER BY USB --------------- */

#if ACCESS_USB == true

#include "udi_msc.h"

/**
 * \brief This function transfers the memory data to the USB MSC interface
 *
 * \param addr Sector address to start read
 * \param nb_sector Number of sectors to transfer (sector=512 bytes)
 *
 * \return Ctrl_status
 */
Ctrl_status nand_flash_usb_read_10(uint32_t addr, uint16_t nb_sector)
{
	uint8_t nb_sector_trans;
	uint16_t page_data_size
		= nand_flash_model_get_page_data_size(MODEL(&nf_translation));

	if (nand_flash_status == NAND_FLASH_READY) {
		while (nb_sector) {
			nb_sector_trans
				= min(nb_sector,
					(page_data_size / SECTOR_SIZE));
			if (!nand_flash_read((addr * SECTOR_SIZE),
					nand_flash_usb_buffer,
					(nb_sector_trans * SECTOR_SIZE))) {
				udi_msc_trans_block(true,
						(uint8_t *)nand_flash_usb_buffer,
						(nb_sector_trans * SECTOR_SIZE),
						NULL);
				nb_sector -= nb_sector_trans;
				addr += nb_sector_trans;
			} else {
				return CTRL_FAIL;
			}
		}
		return CTRL_GOOD;
	}

	return CTRL_BUSY;
}

/**
 * \brief This function transfers the USB MSC data to the memory
 *
 * \param addr Sector address to start write
 * \param nb_sector Number of sectors to transfer (sector=512 bytes)
 *
 * \return Ctrl_status
 */
Ctrl_status nand_flash_usb_write_10(uint32_t addr, uint16_t nb_sector)
{
	uint8_t nb_sector_trans;
	uint16_t page_data_size
		= nand_flash_model_get_page_data_size(MODEL(&nf_translation));

	if (nand_flash_status == NAND_FLASH_READY) {
		while (nb_sector) {
			nb_sector_trans
				= min(nb_sector,
					(page_data_size / SECTOR_SIZE));
			udi_msc_trans_block(false,
					(uint8_t *)nand_flash_usb_buffer,
					(nb_sector_trans * SECTOR_SIZE), NULL);
			if (nand_flash_write((addr * SECTOR_SIZE),
					nand_flash_usb_buffer,
					(nb_sector_trans * SECTOR_SIZE))) {
				return CTRL_FAIL;
			}

			nb_sector -= nb_sector_trans;
			addr += nb_sector_trans;
		}
		return CTRL_GOOD;
	}

	return CTRL_BUSY;
}

#endif  /* ACCESS_USB == true */

/* ------------ SPECIFIC FUNCTIONS FOR TRANSFER BY RAM ----------------- */

#if ACCESS_MEM_TO_RAM == true

#include <string.h>

/**
 * \brief This function tranfers 1 data sector from memory to RAM
 *
 * \param addr Sector address to start read
 * \param ram Address of RAM buffer
 *
 * \return Ctrl_status
 */
Ctrl_status nand_flash_mem_2_ram(uint32_t addr, void *ram)
{
	if (nand_flash_status == NAND_FLASH_READY) {
		if (!nand_flash_read((addr * SECTOR_SIZE), ram, SECTOR_SIZE)) {
			return CTRL_GOOD;
		}

		return CTRL_FAIL;
	}

	return CTRL_BUSY;
}

/**
 * \brief This function tranfers 1 data sector from RAM to memory
 *
 * \param addr Sector address to start write
 * \param ram Address of RAM buffer
 *
 * \return Ctrl_status
 */
Ctrl_status nand_flash_ram_2_mem(uint32_t addr, const void *ram)
{
	if (nand_flash_status == NAND_FLASH_READY) {
		if (!nand_flash_write((addr * SECTOR_SIZE), ram, SECTOR_SIZE)) {
			return CTRL_GOOD;
		}

		return CTRL_FAIL;
	}

	return CTRL_BUSY;
}

#endif  /* ACCESS_MEM_TO_RAM == true */
