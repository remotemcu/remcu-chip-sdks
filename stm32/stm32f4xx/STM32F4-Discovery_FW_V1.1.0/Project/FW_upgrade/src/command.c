/**
  ******************************************************************************
  * @file    FW_upgrade/src/command.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    28-October-2011
  * @brief   This file provides all the IAP command functions.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "command.h"

/** @addtogroup STM32F4-Discovery_FW_Upgrade
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
#define UPLOAD_FILENAME            "0:UPLOAD.BIN"
#define DOWNLOAD_FILENAME          "0:image.BIN"

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t RAM_Buf[BUFFER_SIZE] =
  {
    0x00
  };
static uint32_t TmpProgramCounter = 0x00, TmpReadSize = 0x00 , RamAddress = 0x00;
static uint32_t LastPGAddress = APPLICATION_ADDRESS;

extern FATFS fatfs;
extern FIL file;
extern FIL fileR;
extern DIR dir;
extern FILINFO fno;

extern USB_OTG_CORE_HANDLE          USB_OTG_Core;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief IAP Read all flash memory
  * @param  None
  * @retval None
  */
void COMMAND_UPLOAD(void)
{
  __IO uint32_t address = APPLICATION_ADDRESS;
  __IO uint32_t counterread = 0x00;
  
  uint32_t tmpcounter = 0x00, indexoffset = 0x00;
  FlagStatus readoutstatus = SET;
  uint16_t bytesWritten;
  
  /* Get the read out protection status */
  readoutstatus = FLASH_If_ReadOutProtectionStatus();
  if (readoutstatus == RESET)
  {
    /* Remove UPLOAD file if exist on flash disk */
    f_unlink (UPLOAD_FILENAME);
    
    /* Init written byte counter */
    indexoffset = (APPLICATION_ADDRESS - USER_FLASH_STARTADDRESS);
    
    /* Open binary file to write on it */
    if ((HCD_IsDeviceConnected(&USB_OTG_Core) == 1) && (f_open(&file, UPLOAD_FILENAME, FA_CREATE_ALWAYS | FA_WRITE) == FR_OK))
    {
      /* Upload On Going: Set Blue LED ON */
      STM_EVAL_LEDOn(LED6); 
      
      /* Read flash memory */
      while ((indexoffset != USER_FLASH_SIZE) && (HCD_IsDeviceConnected(&USB_OTG_Core) == 1))
      {
        for (counterread = 0; counterread < BUFFER_SIZE; counterread++)
        {
          /* Check the read bytes versus the end of flash */
          if (indexoffset + counterread != USER_FLASH_SIZE)
          {
            tmpcounter = counterread;
            RAM_Buf[tmpcounter] = (*(uint8_t*)(address++));
          }
          /* In this case all flash was read */
          else
          {
            break;
          }
        }

        /* Write buffer to file */
        f_write (&file, RAM_Buf, BUFFER_SIZE, (void *)&bytesWritten);
        
        /* Number of byte written  */
        indexoffset = indexoffset + counterread;
      }
      
      /* Set Green LED ON: Upload Done */
      STM_EVAL_LEDOff(LED6); 
      STM_EVAL_LEDOn(LED4); 
      
      /* Close file and filesystem */
      f_close (&file);
      f_mount(0, NULL);
    }
  }
  else
  {
    /* Message ROP active: Set Orange LED ON and Toggle Red LED in infinite loop */
    STM_EVAL_LEDOn(LED3);
    Fail_Handler();
  }
}

/**
  * @brief  IAP write memory
  * @param  None
  * @retval None
  */
void COMMAND_DOWNLOAD(void)
{
  /* Open the binary file to be downloaded */
  if (f_open(&fileR, DOWNLOAD_FILENAME, FA_READ) == FR_OK)
  {
    if (fileR.fsize > USER_FLASH_SIZE)
    {
      /* Set Blue LED ON */
      STM_EVAL_LEDOn(LED6); 
      /* Toggle Red LED in infinite loop: No available Flash memory size for 
         the binary file */
      Fail_Handler();
    }
    else
    {
      /* Download On Going: Set Blue LED ON */
      STM_EVAL_LEDOn(LED6); 
      
      /* Erase FLASH sectors to download image */
      if (FLASH_If_EraseSectors(APPLICATION_ADDRESS) != 0x00)
      {
        /* Set Blue LED ON */
        STM_EVAL_LEDOn(LED6); 
        /* Set Orange LED ON */
        STM_EVAL_LEDOn(LED3);
        /* Toggle Red LED in infinite loop: Flash erase error */
        Fail_Handler();
      }
      /* Program flash memory */
      COMMAND_ProgramFlashMemory();
      
      /* Set Orange LED ON: Download Done */
      /* Set Blue LED OFF */
      STM_EVAL_LEDOff(LED6); 
      STM_EVAL_LEDOn(LED3); 

      /* Close file and filesystem */
      f_close (&fileR);
    }
  }
  else
  {
    /* Toggle Red LED in infinite loop: the binary file is not available */
    Fail_Handler();
  }
}

/**
  * @brief  IAP jump to user program
  * @param  None
  * @retval None
  */
void COMMAND_JUMP(void)
{
  /* Software reset */
  NVIC_SystemReset();
}

/**
  * @brief  Programs the internal Flash memory 
  * @param  None
  * @retval None
  */
void COMMAND_ProgramFlashMemory(void)
{
  __IO uint32_t programcounter = 0x00;
  uint8_t readflag = TRUE;
  uint16_t BytesRead;
  
  /* RAM Address Initialization */
  RamAddress = (uint32_t) & RAM_Buf;
  
  /* Erase address init */
  LastPGAddress = APPLICATION_ADDRESS;
  
  /* While file still contain data */
  while ((readflag == TRUE) && (HCD_IsDeviceConnected(&USB_OTG_Core) == 1))
  {
    /* Read maximum 512 Kbyte from the selected file */
    f_read (&fileR, RAM_Buf, BUFFER_SIZE, (void *)&BytesRead);
    
    /* Temp variable */
    TmpReadSize = BytesRead;
    
    /* The read data < "BUFFER_SIZE" Kbyte */
    if (TmpReadSize < BUFFER_SIZE)
    {
      readflag = FALSE;
    }
    
    /* Program flash memory */
    for (programcounter = TmpReadSize; programcounter != 0; programcounter -= 4)
    {
      TmpProgramCounter = programcounter;
      /* Write word into flash memory */
      if (FLASH_If_ProgramWord((LastPGAddress - TmpProgramCounter + TmpReadSize), \
        *(__IO uint32_t *)(RamAddress - programcounter + TmpReadSize)) != FLASH_COMPLETE)
      {
        /* Toggle Red LED in infinite loop: Flash programming error */
        Fail_Handler();
      }
    }
    /* Update last programmed address value */
    LastPGAddress = LastPGAddress + TmpReadSize;
  }
}

/**
  * @}
  */

/*******************(C)COPYRIGHT 2011 STMicroelectronics *****END OF FILE******/
