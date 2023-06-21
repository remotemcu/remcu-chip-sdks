/**
 * \file
 *
 * \brief Raw flash operation.
 *
 * This file contains definitions and functions for raw NAND Flash operation.
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
 *
 * The raw NAND Flash layer drives hardware-specific Bus Read and Bus Write
 * operations to communicate with the NAND Flash device. It directly interacts
 * with hardware's register to operate NAND Flash interface.The raw NAND Flash
 * layer code implement procedures to program basic NAND Flash operations.
 * It takes care of issuing the correct sequences of write/read operations for
 * each command. All functions in the layer are blocked i.e. they wait for
 * the completion of an operation. Raw NAND Flash layer access NAND Flash
 * device by EBI.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef NAND_FLASH_RAW_H_INCLUDED
#define NAND_FLASH_RAW_H_INCLUDED

#include "nand_flash_model.h"

/* Describes a physical Raw NAND Flash chip connected to the microcontroller. */
struct nand_flash_raw {
	/* Model describing this NAND Flash characteristics. */
	struct nand_flash_model model;
	/* Address for sending commands to the NAND Flash. */
	uint32_t command_address;
	/* Address for sending addresses to the NAND Flash. */
	uint32_t address_address;
	/* Address for sending data to the NAND Flash. */
	uint32_t data_address;
};

uint32_t nand_flash_raw_initialize(struct nand_flash_raw *raw,
		const struct nand_flash_model *model, uint32_t command_address,
		uint32_t address_address, uint32_t data_address);
void nand_flash_raw_reset(const struct nand_flash_raw *raw);
uint32_t nand_flash_raw_read_id(const struct nand_flash_raw *raw);
uint32_t nand_flash_raw_erase_block(const struct nand_flash_raw *raw,
		uint16_t block);
void nand_flash_raw_read_page(const struct nand_flash_raw *raw,
		uint16_t block, uint16_t page, uint8_t *data, uint8_t *spare);
uint32_t nand_flash_raw_write_page(const struct nand_flash_raw *raw,
		uint16_t block, uint16_t page, uint8_t *data, uint8_t *spare);
uint32_t nand_flash_raw_copy_page(const struct nand_flash_raw *raw,
		uint16_t source_block, uint16_t source_page,
		uint16_t dest_block, uint16_t dest_page);
uint32_t nand_flash_raw_copy_block(const struct nand_flash_raw *raw,
		uint16_t source_block, uint16_t dest_block);

#endif /* NAND_FLASH_RAW_H_INCLUDED */

