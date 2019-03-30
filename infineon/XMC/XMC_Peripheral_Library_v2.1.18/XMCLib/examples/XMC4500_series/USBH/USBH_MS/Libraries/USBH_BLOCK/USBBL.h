
/* CODE_BLOCK_BEGIN[USBBL.h]*/
/******************************************************************************
 *
 * Copyright (C) 2011 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use
 * with Infineon's microcontrollers.
 * This file can be freely distributed within development
 * tools that are supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS,
 * IMPLIED * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS
 * SOFTWARE.INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL,
 * INCIDENTAL, OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *****************************************************************************
 **                                                                         **
 **                                                                         **
 ** PLATFORM : Infineon XMC4000 Series                                      **
 **                                                                         **
 ** COMPILER : Compiler Independent                                         **
 **                                                                         **
 ** AUTHOR : App Developer                                                  **
 **                                                                         **
 ** MAY BE CHANGED BY USER [yes/no]: Yes                                    **
 **                                                                         **
 ** MODIFICATION DATE : Aug 1, 2012                                         **
 **                                                                         **
 *****************************************************************************/

/*****************************************************************************
 **                       Author(s) Identity                                **
 *****************************************************************************
 **                                                                         **
 ** Initials    Name                                                        **
 ** ------------------------------------------------------------------------**
 ** CM          App Developer                                               **
 *****************************************************************************/

#ifndef _USBBL_H_
#define _USBBL_H_
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @file  USBBL.h
 *
 * @brief This file contains all public data structures,enums and function
 *        prototypes for USB Block Layer App.
 *
 */

/*****************************************************************************
 **                      INCLUDE FILES                                      **
 *****************************************************************************/
#include <xmc_common.h>



/*****************************************************************************
 **                      Global Macro Definitions                           **
 *****************************************************************************/

/**
 * @ingroup USBH_IOCTL_publicparam
 * @{
 */

/* USB Block Layer Error Codes */
/** Successful */
#define USBBL_RES_OK                               0
/**  R/W Error */
#define USBBL_RES_ERROR                            1
/**  Write Protected  */
#define USBBL_RES_WRPRT                            2
/** Not Ready  */
#define USBBL_RES_NOTRDY                           3
/** Invalid Parameter */
#define USBBL_RES_PARERR                           4
/** Initialization error */
#define USBBL_INIT_ERROR                           5

/** Drive not initialized */
#define USBBL_STA_NOINIT                         0x01
/** No medium in the drive */
#define USBBL_STA_NODISK                         0x02
/** Write protected */
#define USBBL_STA_PROTECT                        0x04

/* Generic command (defined for FatFs) */
/** Flush disk cache (for write functions) */
#define USBH_IOCTL_CTRL_SYNC               0

/** Get media size (for only f_mkfs()) */
#define USBH_IOCTL_GET_SECTOR_COUNT        1

/** Get sector size (for multiple sector size (_MAX_SS >= 1024)) */
#define USBH_IOCTL_GET_SECTOR_SIZE         2

/** Get erase block size (for only f_mkfs()) */
#define USBH_IOCTL_GET_BLOCK_SIZE          3

/** Force erased a block of sectors (for only _USE_ERASE) */
#define USBH_IOCTL_CTRL_ERASE_SECTOR       4

/**
 * @}
 */


/**
 * @ingroup USBBL_apidoc
 * @{
 */

/*******************************************************************************
 **                           FUNCTION PROTOTYPES                             **
 *******************************************************************************/

/**
 * The function enumerates the attached device as a mass storage device.\n
 *
 */
uint8_t USBBL_Process(void);

/**
 * This function initializes the attached USB device as a mass storage
 * and reads\n the device capacity.\n
 *  
 */
uint8_t USBBL_Initialize(void);

/**
 * This function gives the status of attached USB mass storage device.\n
 *
 */
uint8_t USBBL_GetStatus(void);

/**
 * This function reads data blocks from the attached USB mass storage
 *        device.\n
 *  
 */
uint32_t USBBL_ReadBlock
(
		uint8_t *ReadBuf,
		uint32_t SectorNumber,
		uint8_t  SectorCount
);

/**
 * @brief This function writes data blocks to the attached
 *        USB mass storage device.\n
 *  
 */
uint32_t USBBL_WriteBlock
(
		const uint8_t *WriteBuf,
		uint32_t SectorNumber,
		uint8_t SectorCount
);

/**
 * @brief This function performs the basic initialization of the 
 * Ioctl Command's such as :\n
 * USBH_IOCTL_GET_SECTOR_COUNT: Get media size.\n
 * USBH_IOCTL_GET_SECTOR_SIZE: Get sector size.\n
 * USBH_IOCTL_GET_BLOCK_SIZE: Get Erase Block size.\n
 * USBH_IOCTL_CTRL_SYNC: Flush the Disk Cache.\n
 * USBH_IOCTL_CTRL_ERASE_SECTOR: Force erased a block of sectors.\n
 * 
 */
uint32_t USBBL_Ioctl(uint8_t Command, void *Buffer );


#ifdef __cplusplus
}
#endif
#endif /* _USBBL_H_ */

