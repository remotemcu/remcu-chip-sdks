/**
 * \file
 *
 * \brief Flash model definition.
 *
 * This file contains flash model definitions and functions for NAND Flash
 * module.
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

#include <string.h>
#include "nand_flash_model.h"

/** List of NAND Flash models which can be recognized by the software.*/
const struct nand_flash_model nand_flash_model_list[NAND_FLASH_MODEL_LIST_SIZE]
		= {

/* |  ID    | Options                 | Page    | Mo  | Block   |BlkPg   |DevBlk */
	{0x6e, NAND_FLASH_MODEL_DATA_BUS_8, 256, 1, 4,
			&nand_flash_spare_scheme_256},
	{0x64, NAND_FLASH_MODEL_DATA_BUS_8, 256, 2, 4,
			&nand_flash_spare_scheme_256},
	{0x6b, NAND_FLASH_MODEL_DATA_BUS_8, 512, 4, 8,
			&nand_flash_spare_scheme_512},
	{0xe8, NAND_FLASH_MODEL_DATA_BUS_8, 256, 1, 4,
			&nand_flash_spare_scheme_256},
	{0xec, NAND_FLASH_MODEL_DATA_BUS_8, 256, 1, 4,
			&nand_flash_spare_scheme_256},
	{0xea, NAND_FLASH_MODEL_DATA_BUS_8, 256, 2, 4,
			&nand_flash_spare_scheme_256},
	{0xd5, NAND_FLASH_MODEL_DATA_BUS_8, 512, 4, 8,
			&nand_flash_spare_scheme_512},
	{0xe3, NAND_FLASH_MODEL_DATA_BUS_8, 512, 4, 8,
			&nand_flash_spare_scheme_512},
	{0xe5, NAND_FLASH_MODEL_DATA_BUS_8, 512, 4, 8,
			&nand_flash_spare_scheme_512},
	{0xd6, NAND_FLASH_MODEL_DATA_BUS_8, 512, 8, 8,
			&nand_flash_spare_scheme_512},

	{0x39, NAND_FLASH_MODEL_DATA_BUS_8, 512, 8, 8,
			&nand_flash_spare_scheme_512},
	{0xe6, NAND_FLASH_MODEL_DATA_BUS_8, 512, 8, 8,
			&nand_flash_spare_scheme_512},
	{0x49, NAND_FLASH_MODEL_DATA_BUS_16, 512, 8, 8,
			&nand_flash_spare_scheme_512},
	{0x59, NAND_FLASH_MODEL_DATA_BUS_16, 512, 8, 8,
			&nand_flash_spare_scheme_512},

	{0x33, NAND_FLASH_MODEL_DATA_BUS_8, 512, 16, 16,
			&nand_flash_spare_scheme_512},
	{0x73, NAND_FLASH_MODEL_DATA_BUS_8, 512, 16, 16,
			&nand_flash_spare_scheme_512},
	{0x43, NAND_FLASH_MODEL_DATA_BUS_16, 512, 16, 16,
			&nand_flash_spare_scheme_512},
	{0x53, NAND_FLASH_MODEL_DATA_BUS_16, 512, 16, 16,
			&nand_flash_spare_scheme_512},

	{0x35, NAND_FLASH_MODEL_DATA_BUS_8, 512, 32, 16,
			&nand_flash_spare_scheme_512},
	{0x75, NAND_FLASH_MODEL_DATA_BUS_8, 512, 32, 16,
			&nand_flash_spare_scheme_512},
	{0x45, NAND_FLASH_MODEL_DATA_BUS_16, 512, 32, 16,
			&nand_flash_spare_scheme_512},
	{0x55, NAND_FLASH_MODEL_DATA_BUS_16, 512, 32, 16,
			&nand_flash_spare_scheme_512},

	{0x36, NAND_FLASH_MODEL_DATA_BUS_8, 512, 64, 16,
			&nand_flash_spare_scheme_512},
	{0x76, NAND_FLASH_MODEL_DATA_BUS_8, 512, 64, 16,
			&nand_flash_spare_scheme_512},
	{0x46, NAND_FLASH_MODEL_DATA_BUS_16, 512, 64, 16,
			&nand_flash_spare_scheme_512},
	{0x56, NAND_FLASH_MODEL_DATA_BUS_16, 512, 64, 16,
			&nand_flash_spare_scheme_512},

	{0x78, NAND_FLASH_MODEL_DATA_BUS_8, 512, 128, 16,
			&nand_flash_spare_scheme_512},
	{0x39, NAND_FLASH_MODEL_DATA_BUS_8, 512, 128, 16,
			&nand_flash_spare_scheme_512},
	{0x79, NAND_FLASH_MODEL_DATA_BUS_8, 512, 128, 16,
			&nand_flash_spare_scheme_512},
	{0x72, NAND_FLASH_MODEL_DATA_BUS_16, 512, 128, 16,
			&nand_flash_spare_scheme_512},
	{0x49, NAND_FLASH_MODEL_DATA_BUS_16, 512, 128, 16,
			&nand_flash_spare_scheme_512},
	{0x74, NAND_FLASH_MODEL_DATA_BUS_16, 512, 128, 16,
			&nand_flash_spare_scheme_512},
	{0x59, NAND_FLASH_MODEL_DATA_BUS_16, 512, 128, 16,
			&nand_flash_spare_scheme_512},

	{0x71, NAND_FLASH_MODEL_DATA_BUS_8, 512, 256, 16,
			&nand_flash_spare_scheme_512},

/* Large blocks devices. Parameters must be fetched from the extended I */
//#define OPTIONS     NAND_FLASH_MODEL_COPY_BACK
/* the list need update */
#define OPTIONS     0

	{0xA2, NAND_FLASH_MODEL_DATA_BUS_8 | OPTIONS, 0, 64, 0,
			&nand_flash_spare_scheme_2048},
	{0xF2, NAND_FLASH_MODEL_DATA_BUS_8 | OPTIONS, 0, 64, 0,
			&nand_flash_spare_scheme_2048},
	{0xB2, NAND_FLASH_MODEL_DATA_BUS_16 | OPTIONS, 0, 64, 0,
			&nand_flash_spare_scheme_2048},
	{0xC2, NAND_FLASH_MODEL_DATA_BUS_16 | OPTIONS, 0, 64, 0,
			&nand_flash_spare_scheme_2048},

	{0xA1, NAND_FLASH_MODEL_DATA_BUS_8 | OPTIONS, 0, 128, 0,
			&nand_flash_spare_scheme_2048},
	{0xF1, NAND_FLASH_MODEL_DATA_BUS_8 | OPTIONS, 0, 128, 0,
			&nand_flash_spare_scheme_2048},
	{0xB1, NAND_FLASH_MODEL_DATA_BUS_16 | OPTIONS, 0, 128, 0,
			&nand_flash_spare_scheme_2048},
	{0xC1, NAND_FLASH_MODEL_DATA_BUS_16 | OPTIONS, 0, 128, 0,
			&nand_flash_spare_scheme_2048},

	{0xAA, NAND_FLASH_MODEL_DATA_BUS_8 | OPTIONS, 0, 256, 0,
			&nand_flash_spare_scheme_2048},
	{0xDA, NAND_FLASH_MODEL_DATA_BUS_8 | OPTIONS, 0, 256, 0,
			&nand_flash_spare_scheme_2048},
	{0xBA, NAND_FLASH_MODEL_DATA_BUS_16 | OPTIONS, 0, 256, 0,
			&nand_flash_spare_scheme_2048},
	{0xCA, NAND_FLASH_MODEL_DATA_BUS_16 | OPTIONS, 0, 256, 0,
			&nand_flash_spare_scheme_2048},

	{0xAC, NAND_FLASH_MODEL_DATA_BUS_8 | OPTIONS, 0, 512, 0,
			&nand_flash_spare_scheme_2048},
	{0xDC, NAND_FLASH_MODEL_DATA_BUS_8 | OPTIONS, 0, 512, 0,
			&nand_flash_spare_scheme_2048},
	{0xBC, NAND_FLASH_MODEL_DATA_BUS_16 | OPTIONS, 0, 512, 0,
			&nand_flash_spare_scheme_2048},
	{0xCC, NAND_FLASH_MODEL_DATA_BUS_16 | OPTIONS, 0, 512, 0,
			&nand_flash_spare_scheme_2048},

	{0xA3, NAND_FLASH_MODEL_DATA_BUS_8 | OPTIONS, 0, 1024, 0,
			&nand_flash_spare_scheme_2048},
	{0xD3, NAND_FLASH_MODEL_DATA_BUS_8 | OPTIONS, 0, 1024, 0,
			&nand_flash_spare_scheme_2048},
	{0xB3, NAND_FLASH_MODEL_DATA_BUS_16 | OPTIONS, 0, 1024, 0,
			&nand_flash_spare_scheme_2048},
	{0xC3, NAND_FLASH_MODEL_DATA_BUS_16 | OPTIONS, 0, 1024, 0,
			&nand_flash_spare_scheme_2048},

	{0xA5, NAND_FLASH_MODEL_DATA_BUS_8 | OPTIONS, 0, 2048, 0,
			&nand_flash_spare_scheme_2048},
	{0xD5, NAND_FLASH_MODEL_DATA_BUS_8 | OPTIONS, 0, 2048, 0,
			&nand_flash_spare_scheme_2048},
	{0xB5, NAND_FLASH_MODEL_DATA_BUS_16 | OPTIONS, 0, 2048, 0,
			&nand_flash_spare_scheme_2048},
	{0xC5, NAND_FLASH_MODEL_DATA_BUS_16 | OPTIONS, 0, 2048, 0,
			&nand_flash_spare_scheme_2048},
};


/**
 * \brief Looks for a NAND Flash Model corresponding to the given ID inside a
 * list of model. If found, the model variable is filled with the correct
 * values.
 *
 * \param model_list  List of nand_flash_model instances.
 * \param size  Number of models in list.
 * \param chip_id  Identifier returned by the NAND
 * (id1|(id2<<8)|(id3<<16)|(id4<<24)).
 * \param model  nand_flash_model instance to update with the model parameters.
 *
 * \return 0 if  a matching model has been found; otherwise returns
 * NAND_COMMON_ERROR_UNKNOWNMODEL.
 */
uint32_t nand_flash_model_find(const struct nand_flash_model *model_list,
		uint32_t size, uint32_t chip_id, struct nand_flash_model *model)
{
	uint8_t found = 0, id2, id4;
	uint32_t i;
	id2 = (uint8_t)(chip_id >> 8);
	id4 = (uint8_t)(chip_id >> 24);

	for (i = 0; i < size; i++) {
		if (model_list[i].device_id == id2) {
			found = 1;

			if (model) {
				memcpy(model, &model_list[i], sizeof(struct nand_flash_model));

				if ((model->block_size_in_kilobytes == 0)
						|| (model->page_size_in_bytes == 0)) {
					/* Fetch from the extended ID4
					 * D5  D4 BlockSize || D1  D0  PageSize
					 * 0   0   64K      || 0   0   1K
					 * 0   1   128K     || 0   1   2K
					 * 1   0   256K     || 1   0   4K
					 * 1   1   512K     || 1   1   8k
					 */
					switch (id4 & 0x03) {
					case 0x00:
						model->page_size_in_bytes =	1024;
						break;
					case 0x01:
						model->page_size_in_bytes =	2048;
						break;
					case 0x02:
						model->page_size_in_bytes =	4096;
						break;
					case 0x03:
						model->page_size_in_bytes =	8192;
						break;
					}
					switch (id4 & 0x30) {
					case 0x00:
						model->block_size_in_kilobytes = 64;
						break;
					case 0x10:
						model->block_size_in_kilobytes = 128;
						break;
					case 0x20:
						model->block_size_in_kilobytes = 256;
						break;
					case 0x30:
						model->block_size_in_kilobytes = 512;
						break;
					}
				}
			}
			break;
		}
	}

	/* Check if chip has been detected */
	if (found) {
		return 0;
	} else {
		return NAND_COMMON_ERROR_UNKNOWNMODEL;
	}
}

/**
 * \brief Translates address/size access of a nand_flash_model to block, page
 * and offset values.
 *
 * \param model  nand_flash_model instance.
 * \param address  Access address.
 * \param size  Access size in bytes.
 * \param block  Stores the first accessed block number.
 * \param page  Stores the first accessed page number inside the first block.
 * \param offset  Stores the byte offset inside the first accessed page.
 *
 * \return 0 if the access is correct; otherwise returns
 * NAND_COMMON_ERROR_OUTOFBOUNDS.
 *
 * \note The values are stored in the provided variables if their pointer is
 * not 0.
 */
uint32_t nand_flash_model_translate_access(const struct nand_flash_model
		*model, uint32_t address, uint32_t size, uint16_t *block,
		uint16_t *page, uint16_t *offset)
{
	/* Check that access is not too big */
	if ((address + size) > nand_flash_model_get_device_size_in_bytes(model)) {
		return NAND_COMMON_ERROR_OUTOFBOUNDS;
	}

	/* Get NAND info */
	uint32_t block_size = nand_flash_model_get_block_size_in_bytes(model);
	uint32_t page_size = nand_flash_model_get_page_data_size(model);

	/* Translate address */
	uint16_t temp_block = address / block_size;
	address -= (temp_block * block_size);
	uint16_t temp_page = address / page_size;
	address -= (temp_page * page_size);
	uint16_t temp_Offset = address;

	/* Save results */
	if (block) {
		*block = temp_block;
	}
	if (page) {
		*page = temp_page;
	}
	if (offset) {
		*offset = temp_Offset;
	}

	return 0;
}


/**
 * \brief Returns the spare area placement scheme used by a particular
 * NAND Flash model.
 *
 * \param model  Pointer to a nand_flash_model instance.
 */
const struct nand_flash_spare_scheme *nand_flash_model_get_scheme(const struct
		nand_flash_model *model)
{
	return model->scheme;
}

/**
 * \brief Returns the device ID of a particular NAND Flash model.
 *
 * \param model  Pointer to a nand_flash_model instance.
 */
uint8_t nand_flash_model_get_device_id(const struct nand_flash_model *model)
{
	return model->device_id;
}

/**
 * \brief Returns the number of blocks in the entire device.
 *
 * \param model  Pointer to a nand_flash_model instance.
 */
uint16_t nand_flash_model_get_device_size_in_blocks(const struct
		nand_flash_model *model)
{
	return (1024 * model->device_size_in_megabytes) /
			model->block_size_in_kilobytes;
}

/**
 * \brief Returns the number of pages in the entire device.
 *
 * \param model  Pointer to a nand_flash_model instance.
 */
uint32_t nand_flash_model_get_device_size_in_pages(const struct nand_flash_model
		*model)
{
	return (uint32_t) nand_flash_model_get_device_size_in_blocks(model) *
			nand_flash_model_get_block_size_in_pages(model);
}

/**
 * \brief Returns the size of the whole device in bytes (this does not include
 * the size of the spare zones).
 *
 * \param model  Pointer to a nand_flash_model instance.
 */
uint64_t nand_flash_model_get_device_size_in_bytes(const struct nand_flash_model
		*model)
{
	return ((uint64_t) model->device_size_in_megabytes) << 20;
}

/**
 * \brief Returns the size of the whole device in Mega bytes (this does not
 * include the size of the spare zones).
 *
 * \param model  Pointer to a nand_flash_model instance.
 */
uint16_t nand_flash_model_get_device_size_in_megabytes(const struct
		nand_flash_model *model)
{
	return (model->device_size_in_megabytes);
}

/**
 * \brief Returns the number of pages in one single block of a device.
 *
 * \param model  Pointer to a nand_flash_model instance.
 */
uint32_t nand_flash_model_get_block_size_in_pages(const struct nand_flash_model
		*model)
{
	return (model->block_size_in_kilobytes * 1024) /
			model->page_size_in_bytes;
}

/**
 * \brief Returns the size in bytes of one single block of a device. This does
 * not take into account the spare zones size.
 *
 * \param model  Pointer to a nand_flash_model instance.
 */
uint32_t nand_flash_model_get_block_size_in_bytes(const struct nand_flash_model
		*model)
{
	return (model->block_size_in_kilobytes * 1024);
}

/**
 * \brief  Returns the size of the data area of a page in bytes.
 * take into account the spare zones size.
 *
 * \param model  Pointer to a nand_flash_model instance.
 */
uint16_t nand_flash_model_get_page_data_size(const struct nand_flash_model
		*model)
{
	return model->page_size_in_bytes;
}

/**
 * \brief  Returns the size of the spare area of a page in bytes.
 *
 * \param model  Pointer to a nand_flash_model instance.
 */
uint16_t nand_flash_model_get_page_spare_size(const struct nand_flash_model
		*model)
{
	/* Spare size is 16/512 of data size */
	return (model->page_size_in_bytes >> 5);
}

/**
 * \brief  Returns the number of bits used by the data bus of a NAND Flash
 * device.
 *
 * \param model  Pointer to a nand_flash_model instance.
 */
uint32_t nand_flash_model_get_data_bus_width(const struct nand_flash_model
		*model)
{
	return (model->options & NAND_FLASH_MODEL_DATA_BUS_16) ? 16 : 8;
}

/**
 * \brief  Check if the given NAND Flash model uses the "small blocks/pages"
 *
 * \param model  Pointer to a nand_flash_model instance.
 * \return 1 if the model uses the "small blocks/pages"; otherwise return 0.
 */
uint32_t nand_flash_model_small_block(const struct nand_flash_model *model)
{
	return (model->page_size_in_bytes <= 512) ? 1 : 0;
}

/**
 * \brief  Check if if the device supports the copy-back operation.
 *
 * \param model  Pointer to a nand_flash_model instance.
 * \return 1 if the model supports the copy-back operation; otherwise return 0.
 */
uint32_t nand_flash_model_copy_back(const struct nand_flash_model *model)
{
	return ((model->options & NAND_FLASH_MODEL_COPY_BACK) != 0);
}
