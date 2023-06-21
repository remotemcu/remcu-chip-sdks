/**
 * \file
 *
 * \brief ECC flash operation.
 *
 * This file contains definitions and functions for ECC NAND Flash operation.
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

#ifndef NAND_FLASH_ECC_H_INCLUDED
#define NAND_FLASH_ECC_H_INCLUDED

/**
 * NAND Flash ECC layer is called by upper layer, it will call the raw layer
 * to do write/read operations, and do ECC check to the write/read result,
 * it then will feedback the ECC check result to the upper layer.
 *
 * -# nand_flash_ecc_initialize is used to initializes an nand_flash_ecc
 * instance.
 * -# nand_flash_ecc_write_page is used to write a NAND Flash page with ECC
 * result, the function will calculate ECC for the data that is going to be
 * written, and write data and spare(with calculated ECC) to NAND Flash device.
 * -# nand_flash_ecc_read_page is used to read a NAND Flash page with ECC
 * check, the function will read out data and spare first, then it calculates
 * ecc with data and then compare with the readout ECC, and feedback the ECC
 * check result to upper layer.
 */

#include "nand_flash_raw.h"

struct nand_flash_ecc {
	struct nand_flash_raw raw;
};

uint32_t nand_flash_ecc_initialize(struct nand_flash_ecc *ecc,
		const struct nand_flash_model *model,
		uint32_t command_address,
		uint32_t address_address, uint32_t data_address);

uint32_t nand_flash_ecc_read_page(const struct nand_flash_ecc *ecc,
		uint16_t block, uint16_t page, uint8_t *data, uint8_t *spare);

uint32_t nand_flash_ecc_write_page(const struct nand_flash_ecc *ecc,
		uint16_t block, uint16_t page, uint8_t *data, uint8_t *spare);

#endif /* NAND_FLASH_ECC_H_INCLUDED */
