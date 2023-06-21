/*****************************************************************************
 *
 * \file
 *
 * \brief CTRL_ACCESS interface for the AT45DBX data flash controller.
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
 ******************************************************************************/
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */


#ifndef _AT45DBX_MEM_H_
#define _AT45DBX_MEM_H_


#include "conf_access.h"

#if AT45DBX_MEM == DISABLE
  #error at45dbx_mem.h is #included although AT45DBX_MEM is disabled
#endif


#include "ctrl_access.h"


//_____ D E C L A R A T I O N S ____________________________________________

/*! \name Control Interface
 */
//! @{

/*! \brief Tests the memory state and initializes the memory if required.
 *
 * The TEST UNIT READY SCSI primary command allows an application client to poll
 * a LUN until it is ready without having to allocate memory for returned data.
 *
 * This command may be used to check the media status of LUNs with removable
 * media.
 *
 * \return Status.
 */
extern Ctrl_status at45dbx_test_unit_ready(void);

/*! \brief Returns the address of the last valid sector in the memory.
 *
 * \param u32_nb_sector Pointer to the address of the last valid sector.
 *
 * \return Status.
 */
extern Ctrl_status at45dbx_read_capacity(U32 *u32_nb_sector);

/*! \brief Returns the write-protection state of the memory.
 *
 * \return \c true if the memory is write-protected, else \c false.
 *
 * \note Only used by removable memories with hardware-specific write
 *       protection.
 */
extern bool at45dbx_wr_protect(void);

/*! \brief Tells whether the memory is removable.
 *
 * \return \c true if the memory is removable, else \c false.
 */
extern bool at45dbx_removal(void);

//! @}


#if ACCESS_USB == true

/*! \name MEM <-> USB Interface
 */
//! @{

/*! \brief Transfers data from the memory to USB.
 *
 * \param addr      Address of first memory sector to read.
 * \param nb_sector Number of sectors to transfer.
 *
 * \return Status.
 */
extern Ctrl_status at45dbx_usb_read_10(U32 addr, U16 nb_sector);

/*! \brief Transfers data from USB to the memory.
 *
 * \param addr      Address of first memory sector to write.
 * \param nb_sector Number of sectors to transfer.
 *
 * \return Status.
 */
extern Ctrl_status at45dbx_usb_write_10(U32 addr, U16 nb_sector);

//! @}

#endif


#if ACCESS_MEM_TO_RAM == true

/*! \name MEM <-> RAM Interface
 */
//! @{

/*! \brief Copies 1 data sector from the memory to RAM.
 *
 * \param addr  Address of first memory sector to read.
 * \param ram   Pointer to RAM buffer to write.
 *
 * \return Status.
 */
extern Ctrl_status at45dbx_df_2_ram(U32 addr, void *ram);

/*! \brief Copies 1 data sector from RAM to the memory.
 *
 * \param addr  Address of first memory sector to write.
 * \param ram   Pointer to RAM buffer to read.
 *
 * \return Status.
 */
extern Ctrl_status at45dbx_ram_2_df(U32 addr, const void *ram);

//! @}

#endif


#endif  // _AT45DBX_MEM_H_
