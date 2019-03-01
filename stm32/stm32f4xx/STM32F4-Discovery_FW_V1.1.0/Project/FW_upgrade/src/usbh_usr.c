/**
  ******************************************************************************
  * @file    FW_upgrade/src/usbh_usr.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    28-October-2011
  * @brief   This file includes the usb host user callbacks
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
#include "usbh_usr.h"
#include "flash_if.h"
#include "command.h"

/** @addtogroup STM32F4-Discovery_FW_Upgrade
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/*  Points to the DEVICE_PROP structure of current device */
/*  The purpose of this register is to speed up the execution */

USBH_Usr_cb_TypeDef USR_Callbacks =
{
  USBH_USR_Init,
  USBH_USR_DeInit,
  USBH_USR_DeviceAttached,
  USBH_USR_ResetDevice,
  USBH_USR_DeviceDisconnected,
  USBH_USR_OverCurrentDetected,
  USBH_USR_DeviceSpeedDetected,
  USBH_USR_Device_DescAvailable,
  USBH_USR_DeviceAddressAssigned,
  USBH_USR_Configuration_DescAvailable,
  USBH_USR_Manufacturer_String,
  USBH_USR_Product_String,
  USBH_USR_SerialNum_String,
  USBH_USR_EnumerationDone,
  USBH_USR_UserInput,
  USBH_USR_MSC_Application,
  USBH_USR_DeviceNotSupported,
  USBH_USR_UnrecoveredError
};

FATFS fatfs;
FIL file;
FIL fileR;
DIR dir;
FILINFO fno;

static uint8_t USBH_USR_ApplicationState = USH_USR_FS_INIT;
extern USB_OTG_CORE_HANDLE          USB_OTG_Core;
__IO uint32_t TimingDelay;
__IO uint32_t UploadCondition = 0x00;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  USBH_USR_Init
  *         Displays the message on LCD for host lib initialization
  * @param  None
  * @retval None
  */
void USBH_USR_Init(void)
{
  static uint8_t startup = 0;  
  
  if(startup == 0 )
  {
    startup = 1;
    /* Initialize LEDs and Push_Button on STM32F4-Discovery**************************/
    STM_EVAL_LEDInit(LED3);
    STM_EVAL_LEDInit(LED4);
    STM_EVAL_LEDInit(LED5);
    STM_EVAL_LEDInit(LED6);
    
    STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);
  }
  
  /* Setup SysTick Timer for 1 msec interrupts.
     ------------------------------------------
    1. The SysTick_Config() function is a CMSIS function which configure:
       - The SysTick Reload register with value passed as function parameter.
       - Configure the SysTick IRQ priority to the lowest value (0x0F).
       - Reset the SysTick Counter register.
       - Configure the SysTick Counter clock source to be Core Clock Source (HCLK).
       - Enable the SysTick Interrupt.
       - Start the SysTick Counter.
    
    2. You can change the SysTick Clock source to be HCLK_Div8 by calling the
       SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8) just after the
       SysTick_Config() function call. The SysTick_CLKSourceConfig() is defined
       inside the misc.c file.

    3. You can change the SysTick IRQ priority by calling the
       NVIC_SetPriority(SysTick_IRQn,...) just after the SysTick_Config() function 
       call. The NVIC_SetPriority() is defined inside the core_cm4.h file.

    4. To adjust the SysTick time base, use the following formula:
                            
         Reload Value = SysTick Counter Clock (Hz) x  Desired Time base (s)
    
       - Reload Value is the parameter to be passed for SysTick_Config() function
       - Reload Value should not exceed 0xFFFFFF
   */
  if (SysTick_Config(SystemCoreClock / 1000))
  { 
    /* Capture error */ 
    while (1);
  }
}

/**
  * @brief  USBH_USR_DeviceAttached
  *         Displays the message on LCD on device attached
  * @param  None
  * @retval None
  */
void USBH_USR_DeviceAttached(void)
{
  
}

/**
  * @brief  USBH_USR_UnrecoveredError
  * @param  None
  * @retval None
  */
void USBH_USR_UnrecoveredError (void)
{
  /* Toggle Red LED in infinite loop */
  Fail_Handler();
}

/**
  * @brief  USBH_DisconnectEvent
  *         Device disconnect event
  * @param  None
  * @retval Staus
  */
void USBH_USR_DeviceDisconnected (void)
{
  /* Toggle Red LED in infinite loop: USB device disconnected */
  Fail_Handler();
}

/**
  * @brief  USBH_USR_ResetUSBDevice
  * @param  None
  * @retval None
  */
void USBH_USR_ResetDevice(void)
{
  /* callback for USB-Reset */
}

/**
  * @brief  USBH_USR_DeviceSpeedDetected
  *         Displays the message on LCD for device speed
  * @param  Device speed:
  * @retval None
  */
void USBH_USR_DeviceSpeedDetected(uint8_t DeviceSpeed)
{
  if ((DeviceSpeed != HPRT0_PRTSPD_FULL_SPEED)&&(DeviceSpeed != HPRT0_PRTSPD_LOW_SPEED))
  {
    /* Toggle Red LED in infinite loop: USB device disconnected */
    Fail_Handler();
  }
}

/**
  * @brief  USBH_USR_Device_DescAvailable
  * @param  device descriptor
  * @retval None
  */
void USBH_USR_Device_DescAvailable(void *DeviceDesc)
{
  /* callback for device descriptor */
}

/**
  * @brief  USBH_USR_DeviceAddressAssigned
  *         USB device is successfully assigned the Address
  * @param  None
  * @retval None
  */
void USBH_USR_DeviceAddressAssigned(void)
{
  /* callback for device successfully assigned the Address */
}


/**
  * @brief  USBH_USR_Conf_Desc
  * @param  Configuration descriptor
  * @retval None
  */
void USBH_USR_Configuration_DescAvailable(USBH_CfgDesc_TypeDef * cfgDesc,
    USBH_InterfaceDesc_TypeDef *itfDesc,
    USBH_EpDesc_TypeDef *epDesc)
{
  /* callback for configuration descriptor */
}

/**
  * @brief  USBH_USR_Manufacturer_String
  * @param  Manufacturer String
  * @retval None
  */
void USBH_USR_Manufacturer_String(void *ManufacturerString)
{
  /* callback for  Manufacturer String */
}

/**
  * @brief  USBH_USR_Product_String
  * @param  Product String
  * @retval None
  */
void USBH_USR_Product_String(void *ProductString)
{
  /* callback for Product String */
}

/**
  * @brief  USBH_USR_SerialNum_String
  * @param  SerialNum_String
  * @retval None
  */
void USBH_USR_SerialNum_String(void *SerialNumString)
{
  /* callback for SerialNum_String */
}

/**
  * @brief  EnumerationDone 
  *         User response request is displayed to ask application jump to class
  * @param  None
  * @retval None
  */
void USBH_USR_EnumerationDone(void)
{
} 

/**
  * @brief  USBH_USR_DeviceNotSupported
  *         Device is not supported
  * @param  None
  * @retval None
  */
void USBH_USR_DeviceNotSupported(void)
{
  /* Toggle Red LED in infinite loop */
  Fail_Handler();
}


/**
  * @brief  USBH_USR_UserInput
  *         User Action for application state entry
  * @param  None
  * @retval USBH_USR_Status : User response for key button
  */
USBH_USR_Status USBH_USR_UserInput(void)
{
  /* callback for Key botton: set by software in this case */
  return USBH_USR_RESP_OK;
}

/**
  * @brief  USBH_USR_OverCurrentDetected
  *         Over Current Detected on VBUS
  * @param  None
  * @retval None
  */
void USBH_USR_OverCurrentDetected (void)
{
}

/**
  * @brief  USBH_USR_MSC_Application
  *         Demo application for IAP thru USB mass storage
  * @param  None
  * @retval Staus
  */
int USBH_USR_MSC_Application(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;
  
  switch (USBH_USR_ApplicationState)
  {
  case USH_USR_FS_INIT:
    
    /* Initialises the File System*/
    if (f_mount( 0, &fatfs ) != FR_OK ) 
    {
      /* Fatfs initialisation fails */
      /* Toggle Red LED in infinite loop */
      Fail_Handler();
      return(-1); 
    }
    
    /* Flash Disk is write protected: Set ON Blue LED and Toggle Red LED in infinite loop */
    if (USBH_MSC_Param.MSWriteProtect == DISK_WRITE_PROTECTED)
    {
      /* Set ON Blue LED */
      STM_EVAL_LEDOn(LED6);
      /* Toggle Red LED in infinite loop */
      Fail_Handler();
    }
    
    /* Go to IAP menu */
    USBH_USR_ApplicationState = USH_USR_IAP;
    break;
    
  case USH_USR_IAP:
    
    TimingDelay = 300;
    UploadCondition = 0x01;
    
    /* Initialize User_Button on STM32F4-Discovery in the EXTI Mode ----------*/
    STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);
    
    /* Configure Button EXTI line */
    EXTI_InitStructure.EXTI_Line = USER_BUTTON_EXTI_LINE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    /* Writes Flash memory */
    COMMAND_DOWNLOAD();
    
    /* Initialize User_Button on STM32F4-Discovery in the GPIO Mode ----------*/
    STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);
    
    /* Check if User Button is already pressed */
    if ((TimingDelay == 0x00) && (UploadCondition == 0x01))
    {
      /* Reads all flash memory */
      COMMAND_UPLOAD();
      
    }
    else
    {
      /* Set Off Orange LED : Download Done */
      STM_EVAL_LEDOff(LED3); 
      /* Set ON Green LED: Waiting User button pressed */
      STM_EVAL_LEDOn(LED4); 
    }
    
    UploadCondition = 0x00;
    
    /* Waiting User Button Released */
    while ((STM_EVAL_PBGetState(BUTTON_USER) == Bit_SET) && (HCD_IsDeviceConnected(&USB_OTG_Core) == 1))
    {}
    
    /* Waiting User Button Pressed */
    while ((STM_EVAL_PBGetState(BUTTON_USER) == Bit_RESET) && (HCD_IsDeviceConnected(&USB_OTG_Core) == 1))
    {}
    
    /* Waiting User Button Released */
    while ((STM_EVAL_PBGetState(BUTTON_USER) == Bit_SET) && (HCD_IsDeviceConnected(&USB_OTG_Core) == 1))
    {}
    
    /* Jumps to user application code located in the internal Flash memory */
    COMMAND_JUMP();
    break;
    
  default:
    break;
  }
  return(0);
}

/**
  * @brief  USBH_USR_DeInit
  *         Deint User state and associated variables
  * @param  None
  * @retval None
  */
void USBH_USR_DeInit(void)
{
  USBH_USR_ApplicationState = USH_USR_FS_INIT;
}

/**
  * @brief  This function handles the program fail.
  * @param  None
  * @retval None
  */
void Fail_Handler(void)
{
  while(1)
  {
    /* Toggle Red LED */
    STM_EVAL_LEDToggle(LED5);
    Delay(50);
  }
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
