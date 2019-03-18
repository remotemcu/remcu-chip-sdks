/**
 * \file
 *
 * \brief ECC flash operation.
 *
 * This file contains definitions and functions for ECC NAND Flash operation.
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
#include "nand_flash_ecc.h"
#include "ecc-sw.h"

/* Casts */
#define MODEL(ecc)  ((struct nand_flash_model *)ecc)
#define RAW(ecc)    ((struct nand_flash_raw *)ecc)

/**
 * \brief  Initialize a nand_flash_ecc instance.
 *
 * \param ecc  Pointer to an nand_flash_ecc instance.
 * \param model  Pointer to the underlying NAND chip model. Can be 0.
 * \param command_address  Address at which commands are sent.
 * \param address_address  Address at which addresses are sent.
 * \param data_address  Address at which data is sent.
 *
 * \return 0 if the initialization is done; or return the error code.
 */
uint32_t nand_flash_ecc_initialize(struct nand_flash_ecc *ecc,
		const struct nand_flash_model *model,
		uint32_t command_address,
		uint32_t address_address, uint32_t data_address)
{
	uint32_t rc;
	rc = nand_flash_raw_initialize(RAW(ecc),
			model, command_address, address_address, data_address);
	return rc;
}

/**
 * \brief  Read the data and/or spare of a page of a NAND Flash chip, and verify
 * that the data is valid using the ECC information contained in the spare. If
 * one buffer pointer is 0, the corresponding area is not saved.
 *
 * \param ecc  Pointer to an nand_flash_ecc instance.
 * \param block  Number of block to read from.
 * \param page  Number of page to read inside given block.
 * \param data  Data area buffer.
 * \param spare  Spare area buffer.
 *
 * \return 0 if the data has been read and is valid; otherwise returns either
 * NAND_COMMON_ERROR_CORRUPTEDDATA or ...
 */
uint32_t nand_flash_ecc_read_page(const struct nand_flash_ecc *ecc,
		uint16_t block, uint16_t page, uint8_t *data, uint8_t *spare)
{
	uint32_t error;

	uint8_t hamming_code[NAND_COMMON_MAX_SPARE_ECC_BYTES];
	uint8_t spare_buffer[NAND_COMMON_MAX_PAGE_SPARE_SIZE];

	uint16_t page_data_size
		= nand_flash_model_get_page_data_size(MODEL(ecc));

	/* if no buffer provided, use a temp one */
	if (!spare) {
		spare = spare_buffer;
	}

	memset(spare, 0xFF, NAND_COMMON_MAX_PAGE_SPARE_SIZE);

	/* Start by reading the spare and the data */
	nand_flash_raw_read_page(RAW(ecc), block, page, data, spare);

	/* Retrieve ECC information from page and verify the data */
	nand_flash_spare_scheme_read_ecc(nand_flash_model_get_scheme(MODEL(ecc)),
			spare, hamming_code);
	error = hamming_verify_256x(data, page_data_size, hamming_code);
	if (error && (error != HAMMING_ERROR_SINGLE_BIT)) {
		return NAND_COMMON_ERROR_CORRUPTEDDATA;
	}

	return 0;
}

/**
 * \brief  Write the data and/or spare area of a NAND Flash page, after
 * calculating an ECC for the data area and storing it in the spare. If no
 * data buffer is provided, the ECC is read from the existing page spare. If
 * no spare buffer is provided, the spare area is still written with the ECC
 * information calculated on the data buffer.
 *
 * \param ecc  Pointer to an nand_flash_ecc instance.
 * \param block  Number of block to read from.
 * \param page  Number of page to read inside given block.
 * \param data  Data area buffer.
 * \param spare  Spare area buffer.
 *
 * \return 0 if successful; otherwise return the error code.
 */
uint32_t nand_flash_ecc_write_page(const struct nand_flash_ecc *ecc,
		uint16_t block, uint16_t page, uint8_t *data, uint8_t *spare)
{
	uint32_t error;

	uint16_t page_data_size
		= nand_flash_model_get_page_data_size(MODEL(ecc));

	uint8_t hamming_code[NAND_COMMON_MAX_SPARE_ECC_BYTES];
	uint8_t spare_buffer[NAND_COMMON_MAX_PAGE_SPARE_SIZE];

	/**
	 * Compute ECC on the new data, if provided. If not provided, hamming
	 * code set to 0xFFFF.. to keep existing bytes.
	 */
	memset(hamming_code, 0xFF, NAND_COMMON_MAX_SPARE_ECC_BYTES);
	if (data) {
		/* Compute hamming code on data */
		hamming_compute_256x(data, page_data_size, hamming_code);
	}

	/* if no buffer provided, use a temp one */
	if (!spare) {
		spare = spare_buffer;
	}

	memset(spare, 0xFF, NAND_COMMON_MAX_PAGE_SPARE_SIZE);

	nand_flash_spare_scheme_write_ecc(nand_flash_model_get_scheme(MODEL(ecc)),
			spare, hamming_code);

	/* Perform write operation */
	error = nand_flash_raw_write_page(RAW(ecc), block, page, data, spare);
	if (error) {
		return error;
	}

	return 0;
}
