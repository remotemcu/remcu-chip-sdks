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
 * @brief Implements an example of USB host CDC ACM class <br>
 *
 * <b>Detailed description of file</b> <br>
 * The file implements the main function where it initializes USB peripheral, UART peripheral,
 * LUFA stack and executes the device enumeration and character echo application.
 *
 * History
 *
 * 01 Jul 2014 Version 1.0.0 <br>
 * Initial version
 */




#include <xmc_common.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "xmc_usbh.h"
#include "USB/GLUE/USB_Glue.h"
#include "USBH_VCOM/USBVCH.h"
#include "uart.h"

void ClockSetup(void);
/*Port interrupt callback function*/
void CDC_USB_PortCb(uint8_t port, uint32_t event);
/*BULK OUT and NOTIFICATION pipe transfer completion handler*/
void CDC_TransferCompletion_Handle(void);
extern bool BULK_OUT_TransferCompleted;
extern bool NOTIFICATION_TransferCompleted;
extern uint8_t SerialState[SERIAL_STATE_SIZE];
extern uint8_t UART_RX_Buffer[UART_RX_BUFF_SIZE];
/*USB receive buffer*/
#define USB_RX_BUFFER_SIZE  80
uint8_t RxBuffer[USB_RX_BUFFER_SIZE];

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

/*Callback functions to be called from USB glue layer*/
USBH_GLUE_APP_IF_t USBVCH_CB =
{
    .GetBytesInPipe = USBVCH_Pipe_BytesInPipe,
    .GetReadByte = USBVCH_Pipe_Read_8,
    .IsINReceived = USBVCH_Pipe_IsINReceived,
    .PipeEventHandler = USBH_VCOM_Rx_Data_Handler,
    .PortEventHandler = CDC_USB_PortCb
};
/*Flag to identify remote wakeup event*/
volatile uint32_t USBH_RemoteWkUp_Detected = 0U;
/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */
int main(void)
{
  uint8_t USBHostState;
  int8_t ReceivedByte;
  uint8_t *RxPtr;
  uint32_t Rxlen;
  uint32_t uart_data_count;


  /*Configure USB and CPU clocks*/
  ClockSetup();
  /*Initialize UART channel*/
  UART_init();
  /*Select VBUS pin as P3.2*/
  XMC_USBH_Select_VBUS(XMC_GPIO_PORT3, 2U);
  /* Initializes the USB host driver. */
  USB_Init_Host(&USBVCH_CB);

  /*LED pin to indicate USB status*/
  XMC_GPIO_SetMode(XMC_GPIO_PORT3, 9, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT3, 9);

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {
    /*Check if remote wakeup is detected and clear the resume
     * bit after 20ms delay*/
    if (USBH_RemoteWkUp_Detected)
    {
      (void)XMC_USBH_osDelay(20U);
      XMC_USBH_TurnOffResumeBit();
      USBH_RemoteWkUp_Detected = 0;
    }

    USB_GetHostState(&USBHostState);

    /* Check whether device is in configured status */
    if(USBHostState == HOST_STATE_Configured)
    {
      XMC_GPIO_SetOutputLow(XMC_GPIO_PORT3, 9);

      /*Check if any data received on UART channel and forward
       * the same to USB device*/
      uart_data_count = UART_CheckRxData();
      /*Send received data to USB device*/
      if(uart_data_count > 0)
      {
        USBVCH_SendData(UART_RX_Buffer, uart_data_count, NULL);
      }

      /*Check if anything received on USB channel and forward the smae
       * to UART channel*/
      Rxlen = 0;
      RxPtr = RxBuffer;
      do{
        ReceivedByte = -1;
        USBVCH_ReceiveByte(&ReceivedByte);
        if(ReceivedByte != -1)
        {
          *RxPtr = ReceivedByte;
          Rxlen++;
          RxPtr++;
          if(Rxlen == USB_RX_BUFFER_SIZE)
          {
            break;
          }
        }
      }while(ReceivedByte != -1);
      /*Transmit the received data to UART channel*/
      UART_Transmit(RxBuffer, Rxlen);
    }
    USBVCH_Process();
    /* Keep calling this function for USB management */
    USB_USBTask();
    /*Handle transfer completion on BULK OUT and NOTIFICATION*/
    CDC_TransferCompletion_Handle();
  }
}

/*Callback function executed on port interrupt*/
void CDC_USB_PortCb(uint8_t port, uint32_t event)
{
  if(event & XMC_USBH_EVENT_DISCONNECT)
  {
    XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT3, 9);
    Driver_USBH0.PipeDelete(USBHost_Pipe_State[0].pipe_handle);
    Driver_USBH0.PipeDelete(USBHost_Pipe_State[1].pipe_handle);
    Driver_USBH0.PipeDelete(USBHost_Pipe_State[2].pipe_handle);
    Driver_USBH0.PipeDelete(USBHost_Pipe_State[3].pipe_handle);
	  /*Reset the data handling indices*/
    USBH_VCOM_RX_cur_index = 0;
    USBH_VCOM_RX_prev_index = 0;
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

/*Function handles BULK OUT and NOTIFICATION pipe transfer completion*/
void CDC_TransferCompletion_Handle(void)
{
  if(NOTIFICATION_TransferCompleted)
  {
    /*Notification received from device.
     * Data is available in the buffer SerialState[]*/
  }

  if(BULK_OUT_TransferCompleted)
  {
    /*Application code to be executed when BULK OUT transfer completes*/
  }
}


/*Clock configuration*/
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
