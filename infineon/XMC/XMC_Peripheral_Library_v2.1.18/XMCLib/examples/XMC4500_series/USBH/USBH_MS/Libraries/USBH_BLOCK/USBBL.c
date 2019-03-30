
/* CODE_BLOCK_BEGIN[USBBL.c] */

/*******************************************************************************
 Copyright (c) 2016, Infineon Technologies AG                                 **
 All rights reserved.                                                         **
                                                                              **
 Redistribution and use in source and binary forms, with or without           **
 modification,are permitted provided that the following conditions are met:   **
                                                                              **
 *Redistributions of source code must retain the above copyright notice,      **
 this list of conditions and the following disclaimer.                        **
 *Redistributions in binary form must reproduce the above copyright notice,   **
 this list of conditions and the following disclaimer in the documentation    **
 and/or other materials provided with the distribution.                       **
 *Neither the name of the copyright holders nor the names of its contributors **
 may be used to endorse or promote products derived from this software without**
 specific prior written permission.                                           **
                                                                              **
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  **
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    **
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   **
 ARE  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE   **
 LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         **
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         **
 SUBSTITUTE GOODS OR  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    **
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      **
 CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)       **
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   **
 POSSIBILITY OF SUCH DAMAGE.                                                  **
                                                                              **
 To improve the quality of the software, users are encouraged to share        **
 modifications, enhancements or bug fixes with Infineon Technologies AG       **
 dave@infineon.com).                                                          **
                                                                              **
********************************************************************************
**                                                                            **
**                                                                            **
*******************************************************************************/

/**
 * @file  USBBL.c
 *
 * @brief This file contains functions related to USB BlockLayer.
 *
 */
/*******************************************************************************
**                      Include Files                                         **
*******************************************************************************/
#include <xmc_common.h>
#include "USBBL.h"
#include "USB/Class/MassStorageClass.h"
#include "USB/GLUE/USB_Glue.h"
#include "FatFs/integer.h"


/**
 * @cond INTERNAL_DOCS
 */
/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
/**
 * @ingroup USBBL_privateparam
 * @{
 */


/** LUFA Mass Storage Class driver interface configuration and state
 *  information. This structure is passed to all Mass Storage Class driver
 *  functions, so that multiple instances of the same class within a device
 *  can be differentiated from one another.
 */

USB_ClassInfo_MS_Host_t FlashDisk_MS_Interface;


/* Store the received size of Configuration Descriptor */

uint16_t ConfigDescriptorSize;

/* Store the received Configuration Descriptor */
uint8_t  ConfigDescriptorData[512];

/**
 * Holds storage capacity of attached mass storage device.
 */
#if defined __ICCARM__/*IAR*/
#pragma data_alignment=8
SCSI_Capacity_t DiskCapacity;
#pragma data_alignment=8
SCSI_Inquiry_Response_t InquiryData;
#else   
SCSI_Capacity_t DiskCapacity __attribute__ ((aligned (64)));
/* Sends SCSI INQUIRY command to the attached device */
SCSI_Inquiry_Response_t InquiryData __attribute__ ((aligned (64)));
#endif

/**
 * @}
 */

/*******************************************************************************
**                     Public Function Definitions                            **
*******************************************************************************/

/*
 * The function enumerates the attached device as a mass storage device.
 */
uint8_t USBBL_Process(void)
{
  uint8_t Status, enum_status = HOST_ENUMERROR_ControlError;

  /* Get the USB Host status */
  USB_GetHostState(&Status);

  if(Status != HOST_STATE_Addressed)
    return USBBL_GetStatus();

	/* Get USB Configuration descriptor */
  memset(ConfigDescriptorData, 0x00, sizeof(ConfigDescriptorData));
  Status = USB_Host_GetDeviceConfigDescriptor(1, &ConfigDescriptorSize,
      ConfigDescriptorData,
        sizeof(ConfigDescriptorData));

  if(Status == HOST_GETCONFIG_Successful)
  {
    /* Set the PIPE configuration for further USB communication */
    Status = MS_Host_ConfigurePipes(&FlashDisk_MS_Interface,
        ConfigDescriptorSize, ConfigDescriptorData);
    if(Status == HOST_GETCONFIG_Successful)
    {
      /* Set device configuration to one */
      Status = USB_Host_SetDeviceConfiguration(1);
      if(Status == HOST_GETCONFIG_Successful)
      {
        /* Set the status of the USB host to configured */
        Status = HOST_STATE_Configured;
        USB_SetHostState(Status);
        enum_status = HOST_ENUMERROR_NoError;
      }
    }
  }

  if((USBH_EventCB != NULL) && (USBH_EventCB->EnumerationCompleteCb != NULL))
  {
    USBH_EventCB->EnumerationCompleteCb(enum_status, Status);
  }

  return USBBL_GetStatus();
}


/*
 * The function initializes the attached mass storage device and reads
 * the device capacity.
 */
uint8_t USBBL_Initialize(void)
{
  uint8_t Status;
  uint8_t MaxLUNIndex = 0;

  /* Get the USB Host status */
  USB_GetHostState(&Status);

  if(Status != HOST_STATE_Configured)
    return USBBL_GetStatus();

  XMC_USBH_osDelay(100);

  DiskCapacity.Blocks = 0;
  DiskCapacity.BlockSize = 0;

  /* Get the Maximum logical unit */
  if (MS_Host_GetMaxLUN(&FlashDisk_MS_Interface, &MaxLUNIndex))
  {
    USB_Host_SetDeviceConfiguration(0);
    return USBBL_GetStatus();
  }

  /* Resets the mass storage interface. */
  if (MS_Host_ResetMSInterface(&FlashDisk_MS_Interface))
  {
    USB_Host_SetDeviceConfiguration(0);
        return USBBL_GetStatus();;
  }

  for (;;)
  {
	/* Checks if  attached device is ready */
    uint8_t ErrorCode = MS_Host_TestUnitReady(&FlashDisk_MS_Interface, 0);

    if (!(ErrorCode))
      break;

	/* Sends sense request to the attached device */
    SCSI_Request_Sense_Response_t SenseData;
    if (MS_Host_RequestSense(&FlashDisk_MS_Interface, 0, &SenseData) != 0)
    {
      USB_Host_SetDeviceConfiguration(0);
      return USBBL_GetStatus();
    }

    /* Check if an error other than a logical command error (device busy)
     * received.
     */
    if (ErrorCode != MS_ERROR_LOGICAL_CMD_FAILED)
    {
      USB_Host_SetDeviceConfiguration(0);
      return USBBL_GetStatus();
    }
  }


  if (MS_Host_GetInquiryData(&FlashDisk_MS_Interface, 0, &InquiryData))
  {
    USB_Host_SetDeviceConfiguration(0);
    return USBBL_GetStatus();
  }

	/* Reads device capacity */
  if (MS_Host_ReadDeviceCapacity(&FlashDisk_MS_Interface, 0, &DiskCapacity))
  {
    USB_Host_SetDeviceConfiguration(0);
    return USBBL_GetStatus();
  }

  return USBBL_GetStatus();
}


/*
 * The function gets the status of attached mass storage device.
 */
uint8_t USBBL_GetStatus(void)
{
  uint8_t USBHostStat;
  uint8_t  DiskStatus = 0;
  /* Get the USB Host status */
  USB_GetHostState(&USBHostStat);

  do
  {
    if(USBHostStat < HOST_STATE_Configured)
    {
      DiskStatus = USBBL_STA_NOINIT | USBBL_STA_NODISK;
      break;
    }
  } while(0);

  return DiskStatus;
}

/*
 * The function reads specified number of blocks from the attached mass
 * storage device.
 */
uint32_t USBBL_ReadBlock
(
  uint8_t *ReadBuf,
  uint32_t SectorNumber,
  uint8_t  SectorCount
)
{
  uint32_t Status;
  uint8_t DiskStatus;
  uint32_t Result;

  /* Get the USB Host status */
  DiskStatus = USBBL_GetStatus();

  if ((DiskStatus & (uint8_t)USBBL_STA_NOINIT) != 0)
  {
    Result = USBBL_RES_NOTRDY;
  }
  else if (SectorNumber > DiskCapacity.Blocks)
  {
    Result = USBBL_RES_PARERR;
  }
  else
  {
    /* Reads data from the attached device */
    Status = MS_Host_ReadDeviceBlocks(&FlashDisk_MS_Interface, 0,
							SectorNumber, SectorCount,
							DiskCapacity.BlockSize, ReadBuf);

    if (Status == USBBL_RES_OK)
    {
      Result = USBBL_RES_OK;
    }
    else
    {
      Result = USBBL_RES_ERROR;
      USB_Host_SetDeviceConfiguration(0);
    }
  }
  return Result;
}


/*
 * The function writes specified number of blocks to the attached mass
 * storage device.
 */
uint32_t USBBL_WriteBlock
(
  const uint8_t *WriteBuf,
  uint32_t SectorNumber,
  uint8_t SectorCount
)
{
  uint32_t Status;
  uint8_t DiskStatus;
  uint32_t Result;

  /* Get the USB Host status */
  DiskStatus = USBBL_GetStatus();

  if ((DiskStatus & (uint8_t)USBBL_STA_NOINIT) != 0)
  {
    Result = USBBL_RES_NOTRDY;
  }
  else if (SectorNumber > DiskCapacity.Blocks)
  {
    Result = USBBL_RES_PARERR;
  }  
  else
  {
  /* Writes data to the attached device */
  Status = MS_Host_WriteDeviceBlocks(&FlashDisk_MS_Interface, 0,
							SectorNumber, SectorCount,
							(uint16_t)DiskCapacity.BlockSize, WriteBuf);

    if (Status == USBBL_RES_OK)
    {
      Result = USBBL_RES_OK;
    }
    else
    {
      Result = USBBL_RES_ERROR;
      USB_Host_SetDeviceConfiguration(0);
    }
  }
  return Result;
}


uint32_t USBBL_Ioctl(uint8_t Command, void *Buffer )
{
  uint8_t DiskStatus;
  uint32_t Result = USBBL_RES_OK;

  do
  {
	/* Get the USB Host status */
	DiskStatus = USBBL_GetStatus();

  if ((DiskStatus & (uint8_t)USBBL_STA_NOINIT) != 0)
  {
    Result = USBBL_RES_NOTRDY;
    break;
  }

  switch (Command)
    {
	/* Gets sector size of attached device */
    case USBH_IOCTL_GET_SECTOR_SIZE:
    *(uint32_t *)Buffer = DiskCapacity.BlockSize;
    break;

	/* Gets sector count of attached device */
    case USBH_IOCTL_GET_SECTOR_COUNT:
    *(uint32_t *)Buffer = DiskCapacity.Blocks;
    break;

    /* Gets Erase block size of attached device
     * This is dummy implementation as needed by FATFS.
     */
    case USBH_IOCTL_GET_BLOCK_SIZE:
    Result = USBBL_RES_PARERR;
    break;

	/*
	 * Checks no pending write process in the physical drive.
     * This is dummy implementation as needed by FATFS.
  	 */
    case USBH_IOCTL_CTRL_SYNC:
    Result = USBBL_RES_OK;
    break;

    /* Force erased a block of sectors.
     * This is dummy implementation as needed by FATFS.
     */
    case USBH_IOCTL_CTRL_ERASE_SECTOR:
    Result = USBBL_RES_PARERR;
    break;

    default:
    Result = USBBL_RES_PARERR;
    break;
     }
  } while (0);

  return Result;
}



/*CODE_BLOCK_END*/

