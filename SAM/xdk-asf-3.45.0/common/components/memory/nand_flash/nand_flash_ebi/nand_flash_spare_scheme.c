/**
 * \file
 *
 * \brief Flash spare area scheme.
 *
 * This file contains definitions and functions to do NAND Flash device's
 * spare area operations.
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

#include "nand_flash_spare_scheme.h"

/* Spare area placement scheme for 256 byte pages. */
const struct nand_flash_spare_scheme nand_flash_spare_scheme_256 = {

	/* Bad block marker is at position #5 */
	5,
	/* 3 ecc bytes */
	3,
	/* Ecc bytes positions */
	{0, 1, 2},
	/* 4 extra bytes */
	4,
	/* Extra bytes positions */
	{3, 4, 6, 7}
};

/* Spare area placement scheme for 512 byte pages. */
const struct nand_flash_spare_scheme nand_flash_spare_scheme_512 = {

	/* Bad block marker is at position #5 */
	5,
	/* 6 ecc bytes */
	6,
	/* Ecc bytes positions */
	{0, 1, 2, 3, 6, 7},
	/* 8 extra bytes */
	8,
	/* Extra bytes positions */
	{8, 9, 10, 11, 12, 13, 14, 15}
};

/* Spare area placement scheme for 2048 byte pages. */
const struct nand_flash_spare_scheme nand_flash_spare_scheme_2048 = {

	/* Bad block marker is at position #0 */
	0,
	/* 24 ecc bytes */
	24,
	/* Ecc bytes positions */
	{40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
	 58, 59, 60, 61, 62, 63},
	/* 38 extra bytes */
	38,
	/* Extra bytes positions */
	{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
	 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39}
};

/* Spare area placement scheme for 4096 byte pages. */
const struct nand_flash_spare_scheme nand_flash_spare_scheme_4096 = {

	/* Bad block marker is at position #0 */
	0,
	/* 48 ecc bytes */
	48,
	/* Ecc bytes positions */
	{80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97,
	 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112,
	 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126,
	 127},
	/* 78 extra bytes */
	78,
	/* Extra bytes positions */
	{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
	 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
	 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
	 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75,
	 76, 77, 78, 79}
};

/**
 * \brief Read the bad block marker inside a spare area buffer using the given
 * scheme.
 *
 * \param scheme Pointer to a nand_flash_spare_scheme instance.
 * \param spare  Spare area buffer.
 * \param marker Pointer to the variable to store the bad block marker.
 */
void nand_flash_spare_scheme_read_bad_block_marker(const struct
		nand_flash_spare_scheme *scheme, const uint8_t *spare,
		uint8_t *marker)
{
	*marker = spare[scheme->bad_block_marker_position];
}

/**
 * \brief Modify the bad block marker inside a spare area, using the given
 * scheme.
 *
 * \param scheme Pointer to a nand_flash_spare_scheme instance.
 * \param spare  Spare area buffer.
 * \param marker Bad block marker to write.
 */
void nand_flash_spare_scheme_write_bad_block_marker(const struct
		nand_flash_spare_scheme *scheme, uint8_t *spare,
		uint8_t marker)
{
	spare[scheme->bad_block_marker_position] = marker;
}

/**
 * \brief Read ECC information from a spare area using the given scheme.
 *
 * \param scheme Pointer to a nand_flash_spare_scheme instance.
 * \param spare  Spare area buffer.
 * \param ecc  ECC buffer.
 */
void nand_flash_spare_scheme_read_ecc(const struct nand_flash_spare_scheme
		*scheme, const uint8_t *spare, uint8_t *ecc)
{
	uint32_t i;
	for (i = 0; i < scheme->ecc_byte_number; i++) {
		ecc[i] = spare[scheme->ecc_bytes_positions[i]];
	}
}

/**
 * \brief Write ECC information in a spare area, using the given scheme.
 *
 * \param scheme Pointer to a nand_flash_spare_scheme instance.
 * \param spare  Spare area buffer.
 * \param ecc  ECC buffer.
 */
void nand_flash_spare_scheme_write_ecc(const struct nand_flash_spare_scheme
		*scheme, uint8_t *spare, const uint8_t *ecc)
{
	uint32_t i;
	for (i = 0; i < scheme->ecc_byte_number; i++) {
		spare[scheme->ecc_bytes_positions[i]] = ecc[i];
	}
}

/**
 * \brief Read extra bytes of information from a spare area, using the given
 * scheme.
 *
 * \param scheme Pointer to a nand_flash_spare_scheme instance.
 * \param spare  Spare area buffer.
 * \param extra  Extra bytes buffer.
 * \param size  Number of extra bytes to read.
 * \param offset  Index where to read the first extra byte.
 */
void nand_flash_spare_scheme_read_extra(const struct nand_flash_spare_scheme
		*scheme, const uint8_t *spare, void *extra, uint8_t size,
		uint8_t offset)
{
	/* "nand_flash_spare_scheme_read_extra: Too many bytes" */
	Assert((size + offset) < scheme->extra_byte_number);

	uint32_t i;
	for (i = 0; i < size; i++) {
		((uint8_t *)extra)[i] =
				spare[scheme->extra_bytes_positions[i + offset]];
	}
}

/**
 * \brief Write extra bytes of information from a spare area, using the given
 * scheme.
 *
 * \param scheme Pointer to a nand_flash_spare_scheme instance.
 * \param spare  Spare area buffer.
 * \param extra  Extra bytes buffer to write.
 * \param size  Number of extra bytes to write.
 * \param offset  Index where to read the first extra byte.
 */
void nand_flash_spare_scheme_write_extra(const struct nand_flash_spare_scheme
		*scheme, uint8_t *spare, const void *extra, uint8_t size,
		uint8_t offset)
{
	/* "nand_flash_spare_scheme_write_extra: Too many bytes\n\r" */
	Assert((size + offset) < scheme->extra_byte_number);

	uint32_t i;
	for (i = 0; i < size; i++) {
		spare[scheme->extra_bytes_positions[i + offset]]
				= ((uint8_t *) extra)[i];
	}
}
