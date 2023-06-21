/**
 * \file
 *
 * \brief NAND Flash configuration.
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

#ifndef CONF_NF_H_INCLUDED
#define CONF_NF_H_INCLUDED

/* Number of tries for erasing a block */
#define CONF_NF_ERASE_NUM_TRY           2
/* Number of tries for writing a block */
#define CONF_NF_WRITE_NUM_TRY           2
/* Number of tries for copying a block */
#define CONF_NF_COPY_NUM_TRY            2

/* Maximum number of blocks in a device. */
#define NAND_COMMON_MAX_BLOCK_NUMBER       2048

/* Maximum number of pages in one block. */
#define NAND_COMMON_MAX_PAGES_PER_BLOCK    256

/* Maximum size of the data area of one page, in bytes. */
#define NAND_COMMON_MAX_PAGE_SIZE          2048

/* Maximum size of the spare area of one page, in bytes. */
#define NAND_COMMON_MAX_PAGE_SPARE_SIZE    128

/* Maximum number of ecc bytes stored in the spare for one single page. */
#define NAND_COMMON_MAX_SPARE_ECC_BYTES    48

/* Maximum number of extra free bytes inside the spare area of a page. */
#define NAND_COMMON_MAX_SPARE_EXTRA_BYTES  78

#endif /* CONF_NF_H_INCLUDED */
