/**
 * \file
 *
 * \brief NAND Flash ctrl access interface definition.
 *
 * This file contains ctrl access interface functions of NAND Flash module.
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

#ifndef NAND_FLASH_MEM_H_INCLUDED
#define NAND_FLASH_MEM_H_INCLUDED

#include "ctrl_access.h"

#define NAND_FLASH_VERSION     "1.0"

#define NAND_FLASH_NOT_INIT    0
#define NAND_FLASH_READY       1
#define NAND_FLASH_BUSY        2
#define NAND_FLASH_UNLOADED    3

/* ---- CONTROL FUNCTIONS ---- */
/**
 * \brief This function tests memory state, and starts memory initialization
 *
 * \return Ctrl_status
 */
Ctrl_status  nand_flash_test_unit_ready(void);
/**
 * \brief This function returns the address of the last valid sector
 *
 * \param uint32_t_nb_sector  Pointer to number of sectors (sector=512 bytes)
 *
 * \return Ctrl_status
 */
Ctrl_status  nand_flash_read_capacity(uint32_t *u32_nb_sector);
/**
 * \brief This function returns the write-protected mode
 *
 * \return true if the memory is protected
 */
bool         nand_flash_wr_protect(void);
/**
 * \brief This function informs about the memory type
 *
 * \return true if the memory is removable
 */
bool         nand_flash_removal(void);
/**
 * \brief This function unloads/loads the memory
 *
 * \return true if memory unload/load success
 */
bool         nand_flash_unload(bool unload);

/* ---- ACCESS DATA FUNCTIONS ---- */

/* USB interface */
#if ACCESS_USB == true
/**
 * \brief This function transfers the memory data to the USB MSC interface
 *
 * \param addr Sector address to start read
 * \param nb_sector Number of sectors to transfer (sector=512 bytes)
 *
 * \return Ctrl_status
 */
Ctrl_status  nand_flash_usb_read_10(uint32_t addr, uint16_t nb_sector);
/**
 * \brief This function transfers the USB MSC data to the memory
 *
 * \param addr Sector address to start write
 * \param nb_sector Number of sectors to transfer (sector=512 bytes)
 *
 * \return Ctrl_status
 */
Ctrl_status  nand_flash_usb_write_10(uint32_t addr, uint16_t nb_sector);

#endif

/* RAM interface */
#if ACCESS_MEM_TO_RAM == true
/**
 * \brief This function transfers 1 data sector from memory to RAM
 *
 * \param addr Sector address to start read
 * \param ram Address of RAM buffer
 *
 * \return Ctrl_status
 */
Ctrl_status  nand_flash_mem_2_ram(uint32_t addr, void *ram);
/**
 * \brief This function transfers 1 data sector from RAM to memory
 *
 * \param addr Sector address to start write
 * \param ram Address of RAM buffer
 *
 * \return Ctrl_status
 */
Ctrl_status  nand_flash_ram_2_mem(uint32_t addr, const void *ram);

#endif

#endif /* NAND_FLASH_MEM_H_INCLUDED */
