/******************************************************************************
 * Software License Agreement
 *
 * Copyright (c) 2015-2016, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of the copyright holders nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share
 * modifications, enhancements or bug fixes with Infineon Technologies AG
 * (dave@infineon.com).
 *
 *****************************************************************************/
/**
 * @file main.c
 * @date 30 July, 2016
 * @version 1.0.0
 *
 * @brief Implements an example of USB host mass storage <br>
 *
 * <b>Detailed description of file</b> <br>
 * The file implements the main function where it initializes USB peripheral, FatFS file system,
 * LUFA stack and executes the device enumeration and file, folder creation application.
 *
 * History
 *
 * 01 Jul 2014 Version 1.0.0 <br>
 * Initial version
 */

#include <xmc_common.h>

#include "xmc_rtc.h"
#include "FatFs/ff.h"
#include "USB/GLUE/USB_Glue.h"
#include "USBH_BLOCK/USBBL.h"

void ClockSetup(void);
/*FAT file access demonstration function*/
void FATFS_TestDemo(void);
/*USB port event callback function*/
void MS_USB_PortCb(uint8_t port, uint32_t event);

/*FAT related buffer for file IO*/
char read_buff[1000];
uint32_t read_index, loc_index;


/*RTC configuration*/
const XMC_RTC_CONFIG_t rtc_config =
{
    .prescaler = 0x7FFFU,
    .time = {
       .year = 2016,
       .month = 6,
       .days = 6,
       .hours = 0,
       .minutes = 0,
       .seconds = 0,
    },
};

#if (defined (XMC4500_E144x1024) || defined (XMC4500_F144x1024) || defined (XMC4500_F100x1024) || \
    defined (XMC4500_F144x768) || defined (XMC4500_F100x768) || defined (XMC4502_F100x768) || \
    defined (XMC4504_F100x512) || defined (XMC4504_F144x512))
/* Data structure for initializing the clock functional block */
const XMC_SCU_CLOCK_CONFIG_t CLOCK_XMC4_0_CONFIG =
{
  .syspll_config.n_div = 80U,
  .syspll_config.p_div = 2U,

  .syspll_config.k_div = 4U,

  .syspll_config.mode = XMC_SCU_CLOCK_SYSPLL_MODE_NORMAL,
  .syspll_config.clksrc = XMC_SCU_CLOCK_SYSPLLCLKSRC_OSCHP,
  .enable_oschp = true,

  .enable_osculp = false,

  .calibration_mode = XMC_SCU_CLOCK_FOFI_CALIBRATION_MODE_FACTORY,
  .fstdby_clksrc = XMC_SCU_HIB_STDBYCLKSRC_OSI,
  .fsys_clksrc = XMC_SCU_CLOCK_SYSCLKSRC_PLL,
  .fsys_clkdiv = 1U,
  .fcpu_clkdiv = 1U,
  .fperipheral_clkdiv = 1U
};
#else
#error "Clock configuration has to be updated for the device selected. You may use CLOCK_XMC4 APP to derive the required configuration."
#endif

/* File pointer */
FIL fp ;
/* File System Object Structure variable */
FATFS myfsObject ;

/*Callback functions to be called from USB glue layer*/
USBH_GLUE_APP_IF_t MS_CB =
{
    .PortEventHandler = MS_USB_PortCb
};
/* Variable to access the current USB host state */
uint8_t USBHostState;
/*Flag to identify remote wakeup event*/
volatile uint32_t USBH_RemoteWkUp_Detected = 0U;

/**
 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code.
 * The application enumerates a USB device and executes a demonstration of FAT file access example function.
 */
int main(void)
{
  /*Configure USB and CPU clocks*/
  ClockSetup();
  /*Select VBUS pin as P3.2*/
  XMC_USBH_Select_VBUS(XMC_GPIO_PORT3, 2U);
  /* Initializes the USB host driver. */
  USB_Init_Host(&MS_CB);

  /*LED pin to indicate USB status*/
  XMC_GPIO_SetMode(XMC_GPIO_PORT3, 9, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT3, 9);

  /*Initialize RTC used for FAT get time API*/
  XMC_RTC_Enable();
  XMC_RTC_Init(&rtc_config);
  XMC_RTC_Start();

  /* Infinite loop */
  while (1)
  {
    /*Check if remote wakeup is detected and clear the resume
     * bit after 20ms delay*/
    if (USBH_RemoteWkUp_Detected)
    {
      (void)XMC_USBH_osDelay(20U);
      XMC_USBH_TurnOffResumeBit();
      USBH_RemoteWkUp_Detected = 0;
    }
    /* Get the USB Host status. */
    USB_GetHostState(&USBHostState);

    /* To Enumerate the attached mass storage device
     * after it is addressed. */
    USBBL_Process();

    if(USBHostState == HOST_STATE_Configured)
    {
      /* Call MassStorageHost demo function */
      XMC_GPIO_SetOutputLow(XMC_GPIO_PORT3, 9);
      FATFS_TestDemo();
      XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT3, 9);
      (void)XMC_USBH_osDelay(200U);
    }
    else
    {
      /*Keep the LED switched Off as long as it is not
       * enumerated*/
      XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT3, 9);
    }

    /* Keep calling this function for USB management.
     * This function handles the USB host states till it gets
     * addressed */
    USB_USBTask();
  }
}

/*Function to demonstrate FAT file access.
 * Creates a folder with the name ABSTEP, writes 3 files each with 1KB, 2KB and 3KB
 * of data, reads the content of the same files and compares with written data.
 * A LED connected on P3.9 glows when the enumeration is complete and contiunues to glow
 * when the file access is ongoing. When the file access is done, the LED starts blinking.*/
void FATFS_TestDemo(void)
{
  volatile FRESULT DResult;
  uint32_t data_index;

  /* Mount USB device */
  DResult =  f_mount(&myfsObject, "0:", 0);


  /* Make directory  */
  DResult =  f_mkdir("ABSTEP");

  if ((DResult == FR_OK) || (DResult == FR_EXIST))
  {
    /*Directory already exists!!*/
  }

  /* Create File */
  DResult = f_open( &fp, "ABSTEP/readme1.txt", (FA_CREATE_NEW | FA_WRITE | FA_READ));
  if (DResult == FR_OK)
  {
    for(data_index = 0; data_index < 1000; data_index++)
    {
      f_printf( &fp,"%d", 1);
    }
  }
  else if (DResult == FR_EXIST )
  {
  /* File already exists!! */
  }

  /* Close File */
  DResult = f_close(&fp);

  DResult = f_open( &fp, "ABSTEP/readme1.txt", (FA_READ));
  read_index = 0;
  while(read_index < 1000)
  {
    f_read(&fp, read_buff, 1000, (UINT*)&loc_index);
    read_index += loc_index;
    for(data_index = 0; data_index < loc_index; data_index++)
    {
      if(read_buff[data_index] != '1')
      {
        /*TODO: Error management */
        while(1);
      }
    }
    if(read_index < 1000)
    {
      f_lseek(&fp, read_index);
    }
    USB_GetHostState(&USBHostState);
    if(USBHostState == HOST_STATE_WaitForDevice)
    {
      break;
    }
  }
  /* Close File */
  DResult = f_close(&fp);

  /* Create File */
  DResult = f_open( &fp, "ABSTEP/readme2.txt", (FA_CREATE_NEW | FA_WRITE | FA_READ));
  if (DResult == FR_OK)
  {
    for(data_index = 0; data_index < 2000; data_index++)
    {
      f_printf( &fp,"%d", 2);
    }
  }
  else if (DResult == FR_EXIST )
  {
  /* File already exists!! */
  }
  /* Close File */
  DResult = f_close(&fp);

  DResult = f_open( &fp, "ABSTEP/readme2.txt", (FA_READ));

  read_index = 0;
  while(read_index < 2000)
  {
    f_read(&fp, read_buff, 1000, (UINT*)&loc_index);
    read_index += loc_index;
    for(data_index = 0; data_index < loc_index; data_index++)
    {
      if(read_buff[data_index] != '2')
      {
        /*TODO: Error management */
        while(1);
      }
    }
    if(read_index < 2000)
    {
      f_lseek(&fp, read_index);
    }
    USB_GetHostState(&USBHostState);
    if(USBHostState == HOST_STATE_WaitForDevice)
    {
      break;
    }
  }

  /* Close File */
  DResult = f_close(&fp);

  /* Create File */
  DResult = f_open( &fp, "ABSTEP/readme3.txt", (FA_CREATE_NEW | FA_WRITE | FA_READ));
  if (DResult == FR_OK)
  {
    for(data_index = 0; data_index < 3000; data_index++)
    {
      f_printf( &fp,"%d", 3);
    }
  }
  else if (DResult == FR_EXIST )
  {
  /* File already exists!! */
  }
  /* Close File */
  DResult = f_close(&fp);

  DResult = f_open( &fp, "ABSTEP/readme3.txt", (FA_READ));

  read_index = 0;
  while(read_index < 3000)
  {
    f_read(&fp, read_buff, 1000, (UINT*)&loc_index);
    read_index += loc_index;
    for(data_index = 0; data_index < loc_index; data_index++)
    {
      if(read_buff[data_index] != '3')
      {
        /*TODO: Error management */
        while(1);
      }
    }
    if(read_index < 3000)
    {
      f_lseek(&fp, read_index);
    }
    USB_GetHostState(&USBHostState);
    if(USBHostState == HOST_STATE_WaitForDevice)
    {
      break;
    }
  }

  /* Close File */
  DResult = f_close(&fp);
}

/*USB port event callback function*/
void MS_USB_PortCb(uint8_t port, uint32_t event)
{
  if(event & XMC_USBH_EVENT_DISCONNECT)
  {
    /*Switch off the LED when device is disconnected*/
    XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT3, 9);
    Driver_USBH0.PipeDelete(USBHost_Pipe_State[0].pipe_handle);
    Driver_USBH0.PipeDelete(USBHost_Pipe_State[1].pipe_handle);
    Driver_USBH0.PipeDelete(USBHost_Pipe_State[2].pipe_handle);
  }
  if(event & XMC_USBH_EVENT_REMOTE_WAKEUP)
  {
    /*This flag is set to remember the occurrence of remote wakeup event and
     * to return from ISR immediately. This helps to time a 20ms delay in
     * the context of the application main loop rather than inside the ISR context.
     * The reason for this is that the example uses a timer interrupt whose priority is
     * lower than the USB interrupt and therefore would result in a deadlock.*/
    USBH_RemoteWkUp_Detected = 1;
  }
}

/*Implementation of FAT get time API for completeness.
 * This implementation can be modified to use any other interface or DAVE APP.*/
DWORD get_fattime(void)
{
  XMC_RTC_TIME_t cur_time;
  XMC_RTC_GetTime(&cur_time);

  /* Pack date and time into a DWORD variable */
  return (((DWORD)(cur_time.year - 1980UL) << 25UL) | (((DWORD)cur_time.month+1U) << 21UL) | (((DWORD)cur_time.days+1U) << 16UL)
          | ((DWORD)cur_time.hours << 11UL)
          | ((DWORD)cur_time.minutes << 5UL)
          | ((DWORD)cur_time.seconds >> 1UL));
}

/*Function to initialize CPU clock and USB clock*/
void ClockSetup(void)
{
  /* Initialize the SCU clock */
  XMC_SCU_CLOCK_Init(&CLOCK_XMC4_0_CONFIG);
  /* RTC source clock */
  XMC_SCU_HIB_SetRtcClockSource(XMC_SCU_HIB_RTCCLKSRC_OSI);

  /*CLOCK_XMC4_USBCLK_ENABLED*/
  /* USB/SDMMC source clock */
  XMC_SCU_CLOCK_SetUsbClockSource(XMC_SCU_CLOCK_USBCLKSRC_USBPLL);
  /* USB/SDMMC divider setting */
  XMC_SCU_CLOCK_SetUsbClockDivider(4U);
  /* Start USB PLL */
  XMC_SCU_CLOCK_StartUsbPll(1U, 32U);
}
