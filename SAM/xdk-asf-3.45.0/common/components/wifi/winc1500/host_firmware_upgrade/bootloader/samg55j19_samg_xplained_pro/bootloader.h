/**
 * \file
 *
 * \brief Bootloader configuration.
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
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
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#ifndef CONF_BOOTLOADER_H_INCLUDED
#define CONF_BOOTLOADER_H_INCLUDED

/** memory blank value */
#define MEM_BLANK_VALUE 0xFF
/** memory block size */
#define MEM_BLOCK_SIZE (IFLASH_PAGE_SIZE)
/** memory erase block size (4K) */
#define MEM_ERASE_SIZE (IFLASH_PAGE_SIZE * 16)
/* memory aligned  */
#define mem_align(addr) \
	(((addr) % MEM_ERASE_SIZE) ? ((addr) - ((addr) % MEM_ERASE_SIZE)) : (addr))
/** boot region size */
#define BOOTLOAD_SIZE      (32*1024)
/** Info region size */
#define INFO_SIZE   (MEM_ERASE_SIZE)
/** application region size */
#define APP_SIZE       mem_align((IFLASH_SIZE - BOOTLOAD_SIZE - INFO_SIZE) / 1)

/* memory address */
#define MEM_ADDR      IFLASH_ADDR

/* Boot region (single) */
#define BOOTLOAD_CODE_SIZE (BOOTLOAD_SIZE - MEM_BLOCK_SIZE) /* reserve last page */
#define BOOTLOAD_START    mem_align(MEM_ADDR)
#define BOOTLOAD_END      (BOOTLOAD_START + BOOTLOAD_SIZE - 1)

/* Information page  */
#define INFO_ADDR  (BOOTLOAD_END + 1)
#define INFO_ADDR_START (INFO_ADDR)
#define INFO_ADDR_END       (INFO_ADDR_START + INFO_SIZE - 1)

/* Application region */
#define APP_CODE_SIZE  (APP_SIZE) /* reserve last pages */
#define APP_START     mem_align(MEM_ADDR + BOOTLOAD_SIZE+INFO_SIZE)
#define APP_END       (APP_START + APP_CODE_SIZE - 1)

#endif /* CONF_BOOTLOADER_H_INCLUDED */

