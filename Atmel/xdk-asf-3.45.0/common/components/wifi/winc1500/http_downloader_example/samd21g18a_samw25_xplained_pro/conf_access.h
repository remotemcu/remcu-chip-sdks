/**
 * \file
 *
 * \brief Memory access control configuration file.
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _CONF_ACCESS_H_
#define _CONF_ACCESS_H_

#include "compiler.h"
#include "board.h"


/*! \name Activation of Logical Unit Numbers
 */
//! @{
#define LUN_0                DISABLE   //!< On-Chip Virtual Memory.
#define LUN_1                DISABLE   //!< AT45DBX Data Flash.
#define LUN_2                ENABLE    //!< SD/MMC Card over Slot 0
#define LUN_3                DISABLE   //!< Spare
#define LUN_4                DISABLE   //!< Spare
#define LUN_5                DISABLE   //!< Spare
#define LUN_6                DISABLE   //!< Spare
#define LUN_7                DISABLE   //!< Spare
#define LUN_USB              DISABLE   //!< Host Mass-Storage Memory.
//! @}

/*! \name LUN 0 Definitions
 */
//! @{
#define VIRTUAL_MEM                             LUN_0
#define LUN_ID_VIRTUAL_MEM                      LUN_ID_0
#define LUN_0_INCLUDE                           "virtual_mem.h"
#define Lun_0_test_unit_ready                   virtual_test_unit_ready
#define Lun_0_read_capacity                     virtual_read_capacity
#define Lun_0_unload                            NULL /* Can not be unloaded */
#define Lun_0_wr_protect                        virtual_wr_protect
#define Lun_0_removal                           virtual_removal
#define Lun_0_usb_read_10                       virtual_usb_read_10
#define Lun_0_usb_write_10                      virtual_usb_write_10
#define Lun_0_mem_2_ram                         virtual_mem_2_ram
#define Lun_0_ram_2_mem                         virtual_ram_2_mem
#define LUN_0_NAME                              "\"On-Chip Virtual Memory\""
//! @}

/*! \name LUN 1 Definitions
 */
//! @{
#define AT45DBX_MEM                             LUN_1
#define LUN_ID_AT45DBX_MEM                      LUN_ID_1
#define LUN_1_INCLUDE                           "at45dbx_mem.h"
#define Lun_1_test_unit_ready                   at45dbx_test_unit_ready
#define Lun_1_read_capacity                     at45dbx_read_capacity
#define Lun_1_unload                            NULL /* Can not be unloaded */
#define Lun_1_wr_protect                        at45dbx_wr_protect
#define Lun_1_removal                           at45dbx_removal
#define Lun_1_usb_read_10                       at45dbx_usb_read_10
#define Lun_1_usb_write_10                      at45dbx_usb_write_10
#define Lun_1_mem_2_ram                         at45dbx_df_2_ram
#define Lun_1_ram_2_mem                         at45dbx_ram_2_df
#define LUN_1_NAME                              "\"AT45DBX Data Flash\""
//! @}

/*! \name LUN 2 Definitions
 */
//! @{
#define SD_MMC_0_MEM                            LUN_2
#define LUN_ID_SD_MMC_0_MEM                     LUN_ID_2
#define LUN_2_INCLUDE                           "sd_mmc_mem.h"
#define Lun_2_test_unit_ready                   sd_mmc_test_unit_ready_0
#define Lun_2_read_capacity                     sd_mmc_read_capacity_0
#define Lun_2_unload                            sd_mmc_unload_0
#define Lun_2_wr_protect                        sd_mmc_wr_protect_0
#define Lun_2_removal                           sd_mmc_removal_0
#define Lun_2_usb_read_10                       sd_mmc_usb_read_10_0
#define Lun_2_usb_write_10                      sd_mmc_usb_write_10_0
#define Lun_2_mem_2_ram                         sd_mmc_mem_2_ram_0
#define Lun_2_ram_2_mem                         sd_mmc_ram_2_mem_0
#define LUN_2_NAME                              "\"SD/MMC Card Slot 0\""
//! @}

/*! \name USB LUNs Definitions
 */
//! @{
#define MEM_USB                                 LUN_USB
#define LUN_ID_MEM_USB                          LUN_ID_USB
#define LUN_USB_INCLUDE                         "uhi_msc_mem.h"
#define Lun_usb_get_lun()                       uhi_msc_mem_get_lun()
#define Lun_usb_test_unit_ready(lun)            uhi_msc_mem_test_unit_ready(lun)
#define Lun_usb_read_capacity(lun, nb_sect)     uhi_msc_mem_read_capacity(lun, nb_sect)
#define Lun_usb_read_sector_size(lun)           uhi_msc_mem_read_sector_size(lun)
#define Lun_usb_wr_protect(lun)                 uhi_msc_mem_wr_protect(lun)
#define Lun_usb_removal()                       uhi_msc_mem_removal()
#define Lun_usb_mem_2_ram(addr, ram)            uhi_msc_mem_read_10_ram(addr, ram)
#define Lun_usb_ram_2_mem(addr, ram)            uhi_msc_mem_write_10_ram(addr, ram)
#define LUN_USB_NAME                            "\"Host Mass-Storage Memory\""
//! @}

/*! \name Actions Associated with Memory Accesses
 *
 * Write here the action to associate with each memory access.
 *
 * \warning Be careful not to waste time in order not to disturb the functions.
 */
//! @{
#define memory_start_read_action(nb_sectors)
#define memory_stop_read_action()
#define memory_start_write_action(nb_sectors)
#define memory_stop_write_action()
//! @}

/*! \name Activation of Interface Features
 */
//! @{
#define ACCESS_USB           false   //!< MEM <-> USB interface.
#define ACCESS_MEM_TO_RAM    true    //!< MEM <-> RAM interface.
#define ACCESS_STREAM        false   //!< Streaming MEM <-> MEM interface.
#define ACCESS_STREAM_RECORD false   //!< Streaming MEM <-> MEM interface in record mode.
#define ACCESS_MEM_TO_MEM    false   //!< MEM <-> MEM interface.
#define ACCESS_CODEC         false   //!< Codec interface.
//! @}

/*! \name Specific Options for Access Control
 */
//! @{
#define GLOBAL_WR_PROTECT    false   //!< Management of a global write protection.
//! @}


#endif // _CONF_ACCESS_H_
