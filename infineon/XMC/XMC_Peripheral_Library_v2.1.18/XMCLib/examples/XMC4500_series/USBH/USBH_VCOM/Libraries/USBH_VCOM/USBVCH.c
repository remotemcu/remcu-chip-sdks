
/* CODE_BLOCK_BEGIN[USBVCH.c] */

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
** PLATFORM : Infineon XMC4000 Series                                         **
**                                                                            **
** COMPILER : Compiler Independent                                            **
**                                                                            **
** AUTHOR : Infineon Developer                                                **
**                                                                            **
** MAY BE CHANGED BY USER [yes/no]: Yes                                       **
**                                                                            **
** MODIFICATION DATE : May 23, 2016                                           **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                       Author(s) Identity                                   **
********************************************************************************
**                                                                            **
** Initials    Name                                                           **
** ---------------------------------------------------------------------------**
**                                                                            **
*******************************************************************************/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/**
 * @file   USBVCH.c
 *
 *
 * @brief  This file contains the private and public function definitions
 * of USB VCOM host Application.
 *
 */

/*******************************************************************************
 *                            INCLUDE FILES                                   **
 ******************************************************************************/
#include "USBVCH.h"
#include "USB/Class/CDCClass.h"
#include "USB/GLUE/USB_Glue.h"

extern XMC_USBH_PIPE_HANDLE CDC_BULK_OUT_pipe_handle, CDC_BULK_IN_pipe_handle, CDC_INTERRUPT_pipe_handle;
/*******************************************************************************
 *                          GLOBAL VARIABLES                                  **
 ******************************************************************************/

/** LUFA CDC Class driver interface configuration and state information. This structure is
 *  passed to all CDC Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_CDC_Host_t USBVCH_CDCInterface;

/* Store the received size of Configuration Descriptor */
uint16_t USBVCH_ConfigDescriptorSize;

/* Store the received Configuration Descriptor */
uint8_t  USBVCH_ConfigDescriptorData[512];

/*Global interrupt pipe data buffer defined in CDCClassHost.c*/
extern uint8_t SerialState[SERIAL_STATE_SIZE];

/*Global buffers to store received data*/
uint8_t USBH_VCOM_RX_Buffer[USBH_VCOM_RXBUF_SIZE];
/*Global variables to handle VCOM receive data buffer*/
uint32_t USBH_VCOM_RX_cur_index;
uint32_t USBH_VCOM_RX_prev_index;

/*Flags to indicate BULK OUT and NOTIFICATION pipe transfer completion*/
bool BULK_OUT_TransferCompleted = false;


/*******************************************************************************
**                      Public Function Definitions                           **
*******************************************************************************/

/*
 * The function enumerates the attached USB device.
 */
uint32_t USBVCH_Process(void)
{
  uint32_t Status = 0;
  uint8_t USBHostStat;
  uint32_t BaudRate_BPS;
  uint8_t Char_Format;
  uint8_t Data_Bits;
  int8_t Parity_Type;
  uint32_t Data_toggle, max_packet_size;
  uint8_t enum_status = HOST_ENUMERROR_ControlError;
 
  BaudRate_BPS = 9600;   
  Char_Format = CDC_LINEENCODING_OneStopBit;
  Data_Bits = 8; 
  Parity_Type = CDC_PARITY_None;

  /* Get the USB Host status */
  USB_GetHostState(&USBHostStat);

  if(USBHostStat == HOST_STATE_Addressed)
  {
    /* Get USB Configuration descriptor */
    memset(USBVCH_ConfigDescriptorData, 0x00,
                      sizeof(USBVCH_ConfigDescriptorData));

    Status = USB_Host_GetDeviceConfigDescriptor(1, &USBVCH_ConfigDescriptorSize,
              USBVCH_ConfigDescriptorData, sizeof(USBVCH_ConfigDescriptorData));
    if(Status == HOST_GETCONFIG_Successful)
    {
      /* Set the PIPE configuration for further USB communication */
      Status = CDC_Host_ConfigurePipes(&USBVCH_CDCInterface, USBVCH_ConfigDescriptorSize, USBVCH_ConfigDescriptorData);
      if(Status == CDC_ENUMERROR_NoError)
      {
        /* Set device configuration to one */
        Status = USB_Host_SetDeviceConfiguration(1);
        if(Status == HOST_SENDCONTROL_Successful)
        {
          /*Start initial transfer for interrupt end point*/
          Data_toggle = USBH_PipeGetToggle(CDC_INTERRUPT_pipe_handle);
          Data_toggle |= XMC_USBH_PACKET_IN;
          max_packet_size = USBHost_Pipe_State[USBH_PIPE_GET_INDEX(CDC_INTERRUPT_pipe_handle)].MaxPacketSize;
          Driver_USBH0.PipeTransfer(CDC_INTERRUPT_pipe_handle, Data_toggle, SerialState, max_packet_size);

          /*Start first transfer trigger for bulk in end point*/
          Data_toggle = USBH_PipeGetToggle(CDC_BULK_IN_pipe_handle);
          Data_toggle |= XMC_USBH_PACKET_IN;
          max_packet_size = USBHost_Pipe_State[USBH_PIPE_GET_INDEX(CDC_BULK_IN_pipe_handle)].MaxPacketSize;
          Driver_USBH0.PipeTransfer((XMC_USBH_PIPE_HANDLE)CDC_BULK_IN_pipe_handle, Data_toggle, USBH_VCOM_Packet_Buffer,
              max_packet_size);
          enum_status = HOST_ENUMERROR_NoError;
        }
      }
    }

    if(Status != HOST_SENDCONTROL_Successful)
    {
      USB_SetHostState(HOST_STATE_WaitForDevice);
    }

    if((USBH_EventCB != NULL) && (USBH_EventCB->EnumerationCompleteCb != NULL))
    {
      USBH_EventCB->EnumerationCompleteCb(enum_status, Status);
    }
  }
  else
  {
    Status = (uint32_t)USBVCH_ERROR;
  }
  /* Get the USB Host status */
  USB_GetHostState(&USBHostStat);

  if((USBHostStat == (uint8_t)HOST_STATE_Configured) &&
      (Status == 0))
  {
    XMC_USBH_osDelay(1000);

      /* Sends a Serial Control Line State Change notification to the device. */
      USBVCH_CDCInterface.State.ControlLineStates.HostToDevice = 1;
      USBVCH_CDCInterface.State.ControlInterfaceNumber = 0;
      USBVCH_CDCInterface.State.LineEncoding.BaudRateBPS = BaudRate_BPS;
      USBVCH_CDCInterface.State.LineEncoding.CharFormat = Char_Format;
      USBVCH_CDCInterface.State.LineEncoding.DataBits  =  Data_Bits;
      USBVCH_CDCInterface.State.LineEncoding.ParityType = Parity_Type;

      if(CDC_Host_SendControlLineStateChange(&USBVCH_CDCInterface) != HOST_SENDCONTROL_Successful)
      {
        USB_SetHostState(HOST_STATE_WaitForDevice);
      }
      /* Sets the line encoding for the attached device's virtual serial port.*/
      else if(CDC_Host_SetLineEncoding(&USBVCH_CDCInterface) != HOST_SENDCONTROL_Successful)
      {
        USB_SetHostState(HOST_STATE_WaitForDevice);
      }

    }
  else
  {
      Status = (uint32_t)USBVCH_ERROR;
  }

  CDC_Host_USBTask(&USBVCH_CDCInterface);
  return Status;
}

/* This function sends a byte to the USB device. */
uint32_t USBVCH_SendByte(const uint8_t DataByte)
{
  uint32_t Status = 0;

  uint8_t CurrentState;

  /* Get the Current Host State */
  USB_GetHostState(&CurrentState);

  if(CurrentState != HOST_STATE_Configured)
  {
    Status = USBVCH_ERROR;
  }
  /* Send a byte to the host. */
  else if(CDC_Host_SendByte(&USBVCH_CDCInterface, DataByte)
                    != PIPE_RWSTREAM_NoError)
  {
    Status = USBVCH_ERROR;
  }

  return Status;
}

/* This function sends multiple bytes to the USB device. */
uint32_t USBVCH_SendData(const uint8_t* const DataBuffer,
        const uint16_t Length, uint16_t *ActulaXferLengthPtr)
{
  uint32_t Status = 0;
  uint32_t max_packet_size;
  uint8_t CurrentState;
  uint8_t TxLen = 0;

  /* Get the Current Host State */
  USB_GetHostState(&CurrentState);

  if(CurrentState != HOST_STATE_Configured)
  {
    Status = USBVCH_ERROR;
  }
  else if(Length == 0)
  {
    Status = USBVCH_ERROR;
  }

  if(Status == 0)
  {
    max_packet_size = USBHost_Pipe_State[USBH_PIPE_GET_INDEX(CDC_BULK_OUT_pipe_handle)].MaxPacketSize;
    if(Length <= max_packet_size)
      TxLen = Length;
    else
      TxLen = max_packet_size;

    if(CDC_Host_SendData(&USBVCH_CDCInterface, (const uint8_t *)DataBuffer,
        TxLen) != PIPE_RWSTREAM_NoError)
    {
        Status = USBVCH_ERROR;
    }
    else
    {
      if(ActulaXferLengthPtr != NULL)
      {
        *ActulaXferLengthPtr = TxLen;
      }
    }
  }
  return Status;
}


/* This function receives a byte from the USB device.*/
uint32_t USBVCH_ReceiveByte(int8_t* DataByte)
{
  uint32_t Status = 0;
  int16_t RxByte;
  uint8_t CurrentState;

  /* Get the Current Host State */
  USB_GetHostState(&CurrentState);
  if(CurrentState != HOST_STATE_Configured)
  {
    return (uint32_t)USBVCH_ERROR;
  }

  /* Receive one byte of data */
  RxByte = CDC_Host_ReceiveByte(&USBVCH_CDCInterface);

  if(RxByte != -1)
  {
    *DataByte = (int8_t)RxByte;
  }
  else
  {
    Status = USBVCH_ERROR;
  }

  return Status;
}

/* This function calls CDC host USB management function with synchronizing
 *  delay
 */
void USBVCH_CDCHost_USBTask (void)
{
	CDC_Host_USBTask(&USBVCH_CDCInterface);
}


/*
 * Event handler for the USB_DeviceEnumerationComplete event.
 *
 */
void EVENT_USB_Host_DeviceEnumerationComplete()
{

}

/*
 * Event handler for the USB_DeviceEnumerationFailed event
 *
 */
void  EVENT_USB_Host_DeviceEnumerationFailed(const uint8_t ErrorCode,
                                             const uint8_t SubErrorCode)
{

}

/*
 * Event handler for the USB_DeviceUnattached event.
 *
 */
void  EVENT_USB_Host_DeviceUnattached()
{
  /* Set the USB host status to Wait for Device. */
  USB_SetHostState(HOST_STATE_WaitForDevice);
}

void USBH_VCOM_Rx_Data_Handler(XMC_USBH_PIPE_HANDLE ptr_ch, uint32_t event)
{
  uint32_t data_index, Data_toggle, max_packet_size;
  /*Get logical data structure for the pipe handle*/
  XMC_USBH0_pipe_t * pipe_handl = (XMC_USBH0_pipe_t *)&pipe[USBH_PIPE_GET_INDEX(ptr_ch)];

  if((XMC_USBH_PIPE_HANDLE)ptr_ch == CDC_BULK_IN_pipe_handle)
  {
    if(event & XMC_USBH_EVENT_TRANSFER_COMPLETE)
    {
      for(data_index = 0; data_index < pipe_handl->num_transferred_total; data_index++)
      {
        USBH_VCOM_RX_Buffer[(USBH_VCOM_RX_cur_index + data_index)%USBH_VCOM_RXBUF_SIZE] = pipe_handl->data[data_index];
      }
      USBH_VCOM_RX_cur_index = (USBH_VCOM_RX_cur_index + data_index) % USBH_VCOM_RXBUF_SIZE;
      /*Next toggle is calculated based on received data count*/
      USBH_PipeSetNextToggle(CDC_BULK_IN_pipe_handle, pipe_handl->num_transferred_total);
      Data_toggle = USBH_PipeGetToggle(CDC_BULK_IN_pipe_handle);
      Data_toggle |= XMC_USBH_PACKET_IN;
      max_packet_size = USBHost_Pipe_State[USBH_PIPE_GET_INDEX(CDC_BULK_IN_pipe_handle)].MaxPacketSize;
      Driver_USBH0.PipeTransfer((XMC_USBH_PIPE_HANDLE)CDC_BULK_IN_pipe_handle, Data_toggle, USBH_VCOM_Packet_Buffer, max_packet_size);

    }
  }
  else if((XMC_USBH_PIPE_HANDLE)ptr_ch == CDC_BULK_OUT_pipe_handle)
  {
    if(event & XMC_USBH_EVENT_TRANSFER_COMPLETE)
    {
      BULK_OUT_TransferCompleted = true;
    }
  }
  else
  {
  }
}

uint16_t USBVCH_Pipe_BytesInPipe(XMC_USBH_PIPE_HANDLE ptr_pipe)
{
  /*VCOM specific implementation*/
  if(USBH_VCOM_RX_cur_index >= USBH_VCOM_RX_prev_index)
  {
    return (USBH_VCOM_RX_cur_index - USBH_VCOM_RX_prev_index);
  }
  else
  {
    return ((USBH_VCOM_RXBUF_SIZE - USBH_VCOM_RX_prev_index) + USBH_VCOM_RX_cur_index);
  }
}

uint8_t USBVCH_Pipe_Read_8(XMC_USBH_PIPE_HANDLE ptr_pipe)
{
  /*VCOM specific implementation*/
  uint32_t loc_index = USBH_VCOM_RX_prev_index;
  USBH_VCOM_RX_prev_index = (USBH_VCOM_RX_prev_index + 1)%USBH_VCOM_RXBUF_SIZE;
  return USBH_VCOM_RX_Buffer[loc_index];
}

bool USBVCH_Pipe_IsINReceived(XMC_USBH_PIPE_HANDLE ptr_pipe)
{
  /*VCOM specific implementation*/
  if(ptr_pipe == CDC_BULK_IN_pipe_handle)
  {
    if(USBH_VCOM_RX_cur_index != USBH_VCOM_RX_prev_index)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  if(ptr_pipe == CDC_INTERRUPT_pipe_handle)
  {
    if(USBH_PipeEventGet(ptr_pipe) & XMC_USBH_EVENT_TRANSFER_COMPLETE /*XMC_USBH_EVENT_BUS_ERROR*/)
    {
      USBH_PipeEventReset(ptr_pipe, XMC_USBH_EVENT_TRANSFER_COMPLETE /*XMC_USBH_EVENT_BUS_ERROR*/);
      return true;
    }
  }
  return false;
}



