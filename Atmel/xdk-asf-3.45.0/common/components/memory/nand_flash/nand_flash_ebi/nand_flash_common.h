/**
 * \file
 *
 * \brief Common definition of NAND Flash.
 *
 * This file contains some common definition for NAND Flash module.
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

#ifndef NAND_FLASH_COMMON_H_INCLUDED
#define NAND_FLASH_COMMON_H_INCLUDED

#include "compiler.h"
#include "conf_nf.h"
#include "board.h"

/**
 * \defgroup common_components_nand_flash_group NAND Flash on EBI
 *
 * See \ref common_components_nand_flash_quickstart
 *
 * Driver for parallel NAND Flash connected to the External Bus Interface (EBI).
 * Provides functions for initializing and accessing a NAND Flash.
 *
 */

/* NAND Flash chip status codes */
#define NAND_STATUS_READY                    (1 << 6)
#define NAND_STATUS_ERROR                    (1 << 0)

/* NAND Flash commands */
#define NAND_COMMAND_READ_1                  0x00
#define NAND_COMMAND_READ_2                  0x30
#define NAND_COMMAND_COPYBACK_READ_1         0x00
#define NAND_COMMAND_COPYBACK_READ_2         0x35
#define NAND_COMMAND_COPYBACK_PROGRAM_1      0x85
#define NAND_COMMAND_COPYBACK_PROGRAM_2      0x10
#define NAND_COMMAND_RANDOM_OUT              0x05
#define NAND_COMMAND_RANDOM_OUT_2            0xE0
#define NAND_COMMAND_RANDOM_IN               0x85
#define NAND_COMMAND_READID                  0x90
#define NAND_COMMAND_WRITE_1                 0x80
#define NAND_COMMAND_WRITE_2                 0x10
#define NAND_COMMAND_ERASE_1                 0x60
#define NAND_COMMAND_ERASE_2                 0xD0
#define NAND_COMMAND_STATUS                  0x70
#define NAND_COMMAND_RESET                   0xFF

/* NAND Flash commands (small blocks) */
#define NAND_COMMAND_READ_A                  0x00
#define NAND_COMMAND_READ_C                  0x50

/**
 * NAND Flash maximum supported values
 * Since no memory allocation is available, limits have been set on various
 * characteristics of a NAND Flash chip:
 *
 * Maximums
 * - NAND_COMMON_MAX_BLOCK_NUMBER
 * - NAND_COMMON_MAX_PAGES_PER_BLOCK
 * - NAND_COMMON_MAX_PAGE_SIZE
 * - NAND_COMMON_MAX_PAGE_SPARE_SIZE
 * - NAND_COMMON_MAX_SPARE_ECC_BYTES
 * - NAND_COMMON_MAX_SPARE_EXTRA_BYTES
 */

#ifndef NAND_COMMON_MAX_BLOCK_NUMBER
#warning Use the common setting for NAND_COMMON_MAX_BLOCK_NUMBER
/* Maximum number of blocks in a device. */
#define NAND_COMMON_MAX_BLOCK_NUMBER       2048
#endif

#ifndef NAND_COMMON_MAX_PAGES_PER_BLOCK
#warning Use the common setting for NAND_COMMON_MAX_PAGES_PER_BLOCK
/* Maximum number of pages in one block. */
#define NAND_COMMON_MAX_PAGES_PER_BLOCK    256
#endif

#ifndef NAND_COMMON_MAX_PAGE_SIZE
#warning Use the common setting for NAND_COMMON_MAX_PAGE_SIZE
/* Maximum size of the data area of one page, in bytes. */
#define NAND_COMMON_MAX_PAGE_SIZE          4096
#endif

#ifndef NAND_COMMON_MAX_PAGE_SPARE_SIZE
#warning Use the common setting for NAND_COMMON_MAX_PAGE_SPARE_SIZE
/* Maximum size of the spare area of one page, in bytes. */
#define NAND_COMMON_MAX_PAGE_SPARE_SIZE    128
#endif

#ifndef NAND_COMMON_MAX_SPARE_ECC_BYTES
#warning Use the common setting for NAND_COMMON_MAX_SPARE_ECC_BYTES
/* Maximum number of ecc bytes stored in the spare for one single page. */
#define NAND_COMMON_MAX_SPARE_ECC_BYTES    48
#endif

#ifndef NAND_COMMON_MAX_SPARE_EXTRA_BYTES
#warning Use the common setting for NAND_COMMON_MAX_SPARE_EXTRA_BYTES
/* Maximum number of extra free bytes inside the spare area of a page. */
#define NAND_COMMON_MAX_SPARE_EXTRA_BYTES  78
#endif

/**
 * NAND Flash error codes
 * NAND Flash API methods return either 0 (indicating that there was no error),
 * or one of the following error codes:
 *
 * - NAND_COMMON_ERROR_NOMOREBLOCKS
 * - NAND_COMMON_ERROR_BLOCKNOTMAPPED
 * - NAND_COMMON_ERROR_OUTOFBOUNDS
 * - NAND_COMMON_ERROR_NOBLOCKFOUND
 * - NAND_COMMON_ERROR_MAPPINGNOTFOUND
 * - NAND_COMMON_ERROR_CANNOTREAD
 * - NAND_COMMON_ERROR_CANNOTWRITE
 * - NAND_COMMON_ERROR_UNKNOWNMODEL
 * - NAND_COMMON_ERROR_CORRUPTEDDATA
 * - NAND_COMMON_ERROR_WRONGSTATUS
 * - NAND_COMMON_ERROR_NOMAPPING
 * - NAND_COMMON_ERROR_BADBLOCK
 * - NAND_COMMON_ERROR_CANNOTERASE
 * - NAND_COMMON_ERROR_CANNOTCOPY
 * - NAND_COMMON_ERROR_ECC_NOT_COMPATIBLE
 */

/* No more blocks can be allocated for a write operation. */
#define NAND_COMMON_ERROR_NOMOREBLOCKS       1

/* The desired logical block has no current physical mapping. */
#define NAND_COMMON_ERROR_BLOCKNOTMAPPED     2

/* Access if out-of-bounds. */
#define NAND_COMMON_ERROR_OUTOFBOUNDS        3

/* There are no block having the desired property. */
#define NAND_COMMON_ERROR_NOBLOCKFOUND       4

/* The NAND Flash device has no logical mapping information on it. */
#define NAND_COMMON_ERROR_MAPPINGNOTFOUND    5

/* A read operation cannot be carried out. */
#define NAND_COMMON_ERROR_CANNOTREAD         6

/* A write operation cannot be carried out. */
#define NAND_COMMON_ERROR_CANNOTWRITE        7

/* NAND Flash chip model cannot be recognized. */
#define NAND_COMMON_ERROR_UNKNOWNMODEL       8

/* Page data is corrupted according to ECC */
#define NAND_COMMON_ERROR_CORRUPTEDDATA      9

/* Block is not in the required status. */
#define NAND_COMMON_ERROR_WRONGSTATUS        10

/* Device has no logical mapping stored in it. */
#define NAND_COMMON_ERROR_NOMAPPING          11

/* The block being accessed is bad and must be replaced. */
#define NAND_COMMON_ERROR_BADBLOCK           12

/* Failed to perform an erase operation. */
#define NAND_COMMON_ERROR_CANNOTERASE        13

/* A hardware copyback operation failed. */
#define NAND_COMMON_ERROR_CANNOTCOPY         14

/* HW Ecc Not compatible with the NAND Model. */
#define NAND_COMMON_ERROR_ECC_NOT_COMPATIBLE 15

/**
 * \page common_components_nand_flash_quickstart Quick start guide for the
 * NAND Flash module
 *
 * This is the quick start guide for the \ref
 * common_components_nand_flash_group, with step-by-step instructions on how
 * to configure and use the driver in a selection of use cases.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section common_components_nand_flash_use_cases NAND Flash use cases
 * - \ref common_components_nand_flash_basic_use_case Basic use case -
 * Initialize the NAND Flash and perform read/write operation.
 *
 * \section common_components_nand_flash_basic_use_case Basic use case -
 * Initialize the NAND Flash and perform read/write operation.
 *
 * \section common_components_nand_flash_basic_use_case_setup Setup
 *
 * \subsection common_components_nand_flash_basic_use_case_setup_prereq
 * Prerequisites
 * -# \ref gpio_group "General Purpose I/O Management (gpio)"
 *
 * \subsection common_components_nand_flash_basic_use_case_setup_code Code
 * The following function needs to be added to the user application, to
 * initialize the NAND Flash.
 *
 * \code
	 if (nand_flash_raw_initialize(&nf_raw, 0, cmd_address,
	         addr_address, data_address)) {
	     printf("-E- Device Unknown\n\r");
	     return 0;
	 }

\endcode
 *
 * \section common_components_nand_flash_basic_use_case_workflow Workflow
 *
 * -# Erase a block first before write:
 *    - \code error = nand_flash_raw_erase_block(&nf_raw, num_block);; \endcode
 * -# Write the data buffer to the defined page of block:
 *    - \code error = nand_flash_raw_write_page(&nf_raw, block, page,
	write_buffer, 0);
\endcode
 * -# Read the data to the buffer from the defined page of block:
 *    - \code nand_flash_raw_read_page(&nf_raw, block, page, read_buffer, 0);
\endcode
 */

#endif /*NAND_FLASH_COMMON_H_INCLUDED */
