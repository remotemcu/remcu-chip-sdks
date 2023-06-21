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

#ifndef NAND_FLASH_SPARE_SCHEME_H_INCLUDED
#define NAND_FLASH_SPARE_SCHEME_H_INCLUDED

#include "nand_flash_common.h"

struct nand_flash_spare_scheme {
	uint8_t bad_block_marker_position;
	uint8_t ecc_byte_number;
	uint8_t ecc_bytes_positions[NAND_COMMON_MAX_SPARE_ECC_BYTES];
	uint8_t extra_byte_number;
	uint8_t extra_bytes_positions[NAND_COMMON_MAX_SPARE_EXTRA_BYTES];
};

extern const struct nand_flash_spare_scheme nand_flash_spare_scheme_256;
extern const struct nand_flash_spare_scheme nand_flash_spare_scheme_512;
extern const struct nand_flash_spare_scheme nand_flash_spare_scheme_2048;
extern const struct nand_flash_spare_scheme nand_flash_spare_scheme_4096;

void nand_flash_spare_scheme_read_bad_block_marker(const struct
		nand_flash_spare_scheme *scheme, const uint8_t *spare,
		uint8_t *marker);
void nand_flash_spare_scheme_write_bad_block_marker(const struct
		nand_flash_spare_scheme *scheme, uint8_t *spare,
		uint8_t marker);
void nand_flash_spare_scheme_read_ecc(const struct nand_flash_spare_scheme
		*scheme, const uint8_t *spare, uint8_t *ecc);
void nand_flash_spare_scheme_write_ecc(const struct nand_flash_spare_scheme
		*scheme, uint8_t *spare, const uint8_t *ecc);
void nand_flash_spare_scheme_read_extra(const struct nand_flash_spare_scheme
		*scheme, const uint8_t *spare, void *extra, uint8_t size,
		uint8_t offset);
void nand_flash_spare_scheme_write_extra(const struct nand_flash_spare_scheme
		*scheme, uint8_t *spare, const void *extra, uint8_t size,
		uint8_t offset);

#endif /* NAND_FLASH_SPARE_SCHEME_H_INCLUDED */

