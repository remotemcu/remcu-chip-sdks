/**
 * \file
 *
 * \brief NAND Flash Management.
 *
 * This file contains definitions and functions for NAND Flash block management.
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

/**
 * The lower layer of NAND Flash block management, it is called by NAND Flash
 * translation layer, and it will call NAND Flash ECC layer.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef NAND_FLASH_MANAGEMENT_H_INCLUDED
#define NAND_FLASH_MANAGEMENT_H_INCLUDED

#include "nand_flash_ecc.h"

/* Block status definition */
#define BLOCK_STATUS_DEFAULT         0xFF
#define BLOCK_STATUS_FREE            0x0E
#define BLOCK_STATUS_LIVE            0x0C
#define BLOCK_STATUS_DIRTY           0x08
#define BLOCK_STATUS_BAD             0x00

/* Erase dirty blocks only */
#define ERASE_DIRTY                  0
/* Erase all data, calculate count */
#define ERASE_DATA                   1
/* Erase all, reset erase count */
#define ERASE_FULL                   2

struct block_status {
	uint32_t status : 8,
			erase_count : 24;
};

struct nand_flash_management {
	struct nand_flash_ecc ecc;
	struct block_status block_status_array[NAND_COMMON_MAX_BLOCK_NUMBER];
	uint16_t base_block;
	uint16_t size_in_block;
};
/**
 * \brief  Initialize a nand_flash_management instance. Scans the device to
 * retrieve or create block status information.
 *
 * \param managed  Pointer to a nand_flash_management instance.
 * \param model  Pointer to the underlying NAND Flash chip model. Can be 0.
 * \param command_address  Address at which commands are sent.
 * \param address_address  Address at which addresses are sent.
 * \param data_address  Address at which data is sent.
 * \param base_block Base physical block address of managed area, managed 0.
 * \param size_in_block Number of blocks that is managed.
 *
 * \return 0 if the initialization is done; or return the error code.
 */
uint32_t nand_flash_management_initialize(
		struct nand_flash_management *managed,
		const struct nand_flash_model *model, uint32_t command_address,
		uint32_t address_address, uint32_t data_address,
		uint16_t base_block, uint16_t size_in_block);
/**
 * \brief Allocate a FREE block of a managed NAND Flash and mark it as LIVE.
 *
 * \param managed Pointer to a nand_flash_management instance.
 * \param block Block to allocate, in managed area.
 *
 * \return 0 if successful; otherwise returns NAND_COMMON_ERROR_WRONGSTATUS if
 * the block is not FREE, or another error code..
 */
uint32_t nand_flash_management_allocate_block(
		struct nand_flash_management *managed, uint16_t block);
/**
 * \brief Release a LIVE block of a NAND Flash and marks it as DIRTY.
 *
 * \param managed Pointer to a nand_flash_management instance.
 * \param block Block to release, based on managed area.
 *
 * \return 0 if successful; otherwise returns NAND_COMMON_ERROR_WRONGSTATUS if
 * the block is not LIVE, or another error code.
 */
uint32_t nand_flash_management_release_block(
		struct nand_flash_management *managed, uint16_t block);
/**
 * \brief Erase a DIRTY block of a managed NAND Flash.
 *
 * \param managed  Pointer to a nand_flash_management instance.
 * \param block  Block to erase, in managed area.
 *
 * \return NAND_COMMON_ERROR_WRONGSTATUS or another error code.
 */
uint32_t nand_flash_management_erase_block(
		struct nand_flash_management *managed, uint16_t block);
/**
 * \brief  Read the data and/or the spare area of a page on a managed
 * NAND Flash. If the data pointer is not 0, then the block MUST be LIVE.
 *
 * \param managed  Pointer to a nand_flash_management instance.
 * \param block  Number of block to read from.
 * \param page  Number of page to read inside given block.
 * \param data  Data area buffer, can be 0.
 * \param spare  Spare area buffer, can be 0.
 *
 * \return NAND_COMMON_ERROR_WRONGSTATUS if the block is not LIVE and the data
 * pointer is not null; Otherwise, return another error code.
 */
uint32_t nand_flash_management_read_page(
		const struct nand_flash_management *managed, uint16_t block,
		uint16_t page, void *data, void *spare);
/**
 * \brief  Writes the data and/or spare area of a LIVE page on a managed
 * NAND Flash. ECC for the data area and storing it in the spare. If no data
 * buffer is provided, the ECC is read from the existing page spare. If no
 * spare buffer is provided, the spare area is still written with the ECC
 * information calculated on the data buffer.
 *
 * \param managed  Pointer to a nand_flash_management instance.
 * \param block  Number of block to read from.
 * \param page  Number of page to read inside given block.
 * \param data  Data area buffer.
 * \param spare  Spare area buffer.
 *
 * \return NAND_COMMON_ERROR_WRONGSTATUS if the page is not LIVE; otherwise,
 * return another error code.
 */
uint32_t nand_flash_management_write_page(
		const struct nand_flash_management *managed, uint16_t block,
		uint16_t page, void *data, void *spare);
/**
 * \brief Copy the data & spare area of one page to another page. The source
 * block can be either LIVE or DIRTY, and the destination block must be LIVE;
 * they must both have the same parity.
 *
 * \param managed  Pointer to a nand_flash_management instance.
 * \param source_block  Source block number based on managed area.
 * \param source_page  Number of source page inside the source block.
 * \param dest_block  Destination block number based on managed area.
 * \param dest_page  Number of destination page inside the dest block.
 *
 * \return 0 if successful; NAND_COMMON_ERROR_WRONGSTATUS if one or more page
 * is not live; otherwise return another error code.
 */
uint32_t nand_flash_management_copy_page(
		const struct nand_flash_management *managed,
		uint16_t source_block, uint16_t source_page,
		uint16_t dest_block, uint16_t dest_page);
/**
 * \brief Copy the data from a whole block to another block in NAND Flash.
 * Both blocks must be LIVE.
 *
 * \param managed  Pointer to a nand_flash_management instance.
 * \param source_block  Source block number.
 * \param dest_block  Destination block number.
 *
 * \return 0 if successful; NAND_COMMON_ERROR_WRONGSTATUS if one or more page
 * is not live; otherwise return another error code.
 */
uint32_t nand_flash_management_copy_block(
		const struct nand_flash_management *managed,
		uint16_t source_block, uint16_t dest_block);
/**
 * \brief Erases all the blocks which are currently marked as DIRTY.
 *
 * \param managed  Pointer to a nand_flash_management instance.
 *
 * \return 0 if successful; otherwise, return the error code.
 */
uint32_t nand_flash_management_erase_dirty_blocks(
		struct nand_flash_management *managed);
/**
 * \brief Look for the youngest block having the desired status among the
 * blocks of a managed NAND Flash. If a block is found, its index is stored
 * inside the provided variable (if pointer is not 0).
 *
 * \param managed  Pointer to a nand_flash_management instance.
 * \param block  Pointer to the block number variable, based on managed area.
 *
 * \return 0 if a block has been found; otherwise return the error code.
 */
uint32_t nand_flash_management_find_youngest_block(
		const struct nand_flash_management *managed, uint8_t status,
		uint16_t *block);
/**
 * \brief Count and return the number of blocks having the given status in a
 * managed NAND Flash.
 *
 * \param managed  Pointer to a nand_flash_management instance.
 * \param status  Desired block status.
 *
 * \return the number of blocks.
 */
uint16_t nand_flash_management_count_blocks(
		const struct nand_flash_management *managed, uint8_t status);
/**
 * \brief Return the number of available blocks in a managed NAND Flash.
 *
 * \param managed  Pointer to a nand_flash_management instance.
 *
 * \return the number of blocks.
 */
uint16_t nand_flash_management_get_managed_blocks(
		const struct nand_flash_management *managed);
/**
 * \brief Erase all blocks in the managed area of NAND Flash.
 *
 * \param managed  Pointer to a nand_flash_management instance.
 * \param level    Erase level.
 * \return  the nand_flash_raw_erase_block code.
 */
uint32_t nand_flash_management_erase_all(
		struct nand_flash_management *managed, uint8_t level);

#endif /*#ifndef NAND_FLASH_MANAGEMENT_H_INCLUDED */
