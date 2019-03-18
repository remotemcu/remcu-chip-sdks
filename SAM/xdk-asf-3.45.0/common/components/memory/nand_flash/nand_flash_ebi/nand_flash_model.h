/**
 * \file
 *
 * \brief Flash model definition.
 *
 * This file contains flash model definitions and functions for NAND Flash
 * module.
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

#ifndef NAND_FLASH_MODEL_H_INCLUDED
#define NAND_FLASH_MODEL_H_INCLUDED

#include "nand_flash_spare_scheme.h"

/**
 *
 * \{
 */

/**
 * Nand_Flash_Model_opts NAND Flash Model options
 * - NAND_FLASH_MODEL_DATA_BUS_8
 * - NAND_FLASH_MODEL_DATA_BUS_16
 * - NAND_FLASH_MODEL_COPY_BACK
 */

/* Indicate the NAND Flash uses an 8-bit databus. */
#define NAND_FLASH_MODEL_DATA_BUS_8     (0 << 0)

/* Indicate the NAND Flash uses a 16-bit databus. */
#define NAND_FLASH_MODEL_DATA_BUS_16    (1 << 0)

/* The NAND Flash supports the copy-back (internal page-to-page copy). */
#define NAND_FLASH_MODEL_COPY_BACK     (1 << 1)

/* Model of NAND Flash device. */
struct nand_flash_model {
	/* Identifier for the device. */
	uint8_t device_id;
	/* Special options for the NAND Flash. */
	uint8_t options;
	/* Size of the data area of a page, in bytes. */
	uint16_t page_size_in_bytes;
	/* Size of the device in MB. */
	uint16_t device_size_in_megabytes;
	/* Size of one block in kilobytes. */
	uint16_t block_size_in_kilobytes;
	/* Spare area placement scheme. */
	const struct nand_flash_spare_scheme *scheme;
};

/* Number of NAND Flash model inside the list. */
#define NAND_FLASH_MODEL_LIST_SIZE         58

/* List of NAND Flash model which can be recognized by the software.*/
extern const struct nand_flash_model
		nand_flash_model_list[NAND_FLASH_MODEL_LIST_SIZE];

uint32_t nand_flash_model_find(const struct nand_flash_model *model_list,
		uint32_t size, uint32_t chip_id, struct nand_flash_model *model);
uint32_t nand_flash_model_translate_access(const struct nand_flash_model *model,
		uint32_t address, uint32_t size, uint16_t *block,
		uint16_t *page, uint16_t *offset);
const struct nand_flash_spare_scheme *nand_flash_model_get_scheme(const struct
		nand_flash_model *model);
uint8_t nand_flash_model_get_device_id(const struct nand_flash_model *model);
uint16_t nand_flash_model_get_device_size_in_blocks(const struct
		nand_flash_model *model);
uint32_t nand_flash_model_get_device_size_in_pages(const struct nand_flash_model
		*model);
uint64_t nand_flash_model_get_device_size_in_bytes(const struct nand_flash_model
		*model);
uint16_t nand_flash_model_get_device_size_in_megabytes(const struct
		nand_flash_model *model);
uint32_t nand_flash_model_get_block_size_in_pages(const struct nand_flash_model
		*model);
uint32_t nand_flash_model_get_block_size_in_bytes(const struct nand_flash_model
		*model);
uint16_t nand_flash_model_get_page_data_size(const struct nand_flash_model
		*model);
uint16_t nand_flash_model_get_page_spare_size(const struct nand_flash_model
		*model);
uint32_t nand_flash_model_get_data_bus_width(const struct nand_flash_model
		*model);
uint32_t nand_flash_model_small_block(const struct nand_flash_model *model);
uint32_t nand_flash_model_copy_back(const struct nand_flash_model *model);

/**
 * \}
 */

#endif /* NAND_FLASH_MODEL_H_INCLUDED */
