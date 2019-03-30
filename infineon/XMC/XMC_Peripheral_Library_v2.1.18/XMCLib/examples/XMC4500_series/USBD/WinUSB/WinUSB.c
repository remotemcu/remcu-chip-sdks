/*******************************************************************************
 Copyright (c) 2014, Infineon Technologies AG                                 **
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
 *******************************************************************************/


/**
 * @file WinUSB.c
 *
 * @brief winusb device framework
 */

#include "WinUSB.h"

/**
 * Buffer to hold transmit and receive data
 **/
uint8_t tx_buf[TX_BUF_SIZE];
uint8_t rx_buf[RX_BUF_SIZE];


/* USB runtime structure*/
XMC_USBD_t USB_runtime =
{
  .usbd = USB0,
  .usbd_max_num_eps = XMC_USBD_MAX_NUM_EPS_6,
  .usbd_transfer_mode = XMC_USBD_USE_DMA,
  .cb_xmc_device_event = USBD_SignalDeviceEventHandler,
  .cb_endpoint_event = USBD_SignalEndpointEvent_Handler

};


/*WinUSB endpoint info data structure*/
USBD_WINUSB_Info_t WinUSBInfo = {
  .Config = {
    .InEndpoint = {
		.Address = ENDPOINT_DIR_IN | WINUSB_TX_EPNUM,
		.Size = WINUSB_TXRX_EPSIZE,
		.Type = EP_TYPE_BULK
},
.OutEndpoint = {
		.Address = ENDPOINT_DIR_OUT | WINUSB_RX_EPNUM,
		.Size = WINUSB_TXRX_EPSIZE,
		.Type = EP_TYPE_BULK
}
}
};




/*******************************************************************************
**                     Public Function Definitions                            **
*******************************************************************************/

void USB0_0_IRQHandler(void)
{
  XMC_USBD_IRQHandler(&USB_runtime);
}

/*The function initializes the USB core layer and register call backs. */
void USB_Init(void)
{
  USBD_Initialize(&USB_runtime);

  /* Interrupts configuration*/
  NVIC_SetPriority(USB0_0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 63, 0));
  NVIC_ClearPendingIRQ(USB0_0_IRQn);
  NVIC_EnableIRQ(USB0_0_IRQn);

  /* USB Connection*/
  USB_Attach();

}



/*The WinUSB API to write data to USB host*/
USBD_WINUSB_Status_t USBD_WINUSB_WriteData(uint8_t ep, const void *Buffer, uint16_t Length)
{
USBD_WINUSB_Status_t Status = USBD_WINUSB_STATUS_SUCCESS;
uint8_t sts;

/*make sure it is IN endpoint*/
ep |= ENDPOINT_DIR_MASK;

if (Length > 0)
{
	do
	{
		/* leave if device is not configured */
		if (USB_DeviceState != DEVICE_STATE_Configured)
		{
			Status =  USBD_WINUSB_STATUS_NOT_READY;
			break;
		}

		/* Selecet winusb in endpoint */
		Endpoint_SelectEndpoint(ep);

		/* Leave if endpoint is not ready */
		if (!Endpoint_IsINReady())
		{
			Status = USBD_WINUSB_STATUS_NOT_READY;
			break;
		}

		/* write data to endpoint and then flush the data */
		sts = Endpoint_Write_Stream_LE(Buffer,Length,NULL);
		if (sts != ENDPOINT_RWSTREAM_NoError )
		{
			Status = USBD_WINUSB_STATUS_FAILURE;
			break;
		}
		Endpoint_ClearIN();
	}while(0);
}
else
{
	Status = USBD_WINUSB_STATUS_FAILURE;
}
return Status;
}

/*The WinUSB API to read data from USB host*/
USBD_WINUSB_Status_t USBD_WINUSB_ReadData(uint8_t ep,void *Buffer,uint16_t Length)
{
	USBD_WINUSB_Status_t Status = USBD_WINUSB_STATUS_SUCCESS;
	uint8_t sts;

	if (Length > 0)
	{
		do
		{
			/* Leave if device is not configured */
			if (USB_DeviceState != DEVICE_STATE_Configured)
			{
				Status = (USBD_WINUSB_Status_t)ENDPOINT_RWSTREAM_DeviceDisconnected;
				break;
			}

			/* Select the winusb out endpoint */
			Endpoint_SelectEndpoint(ep);

			/* leave if no out is received */
			if (true != Endpoint_IsOUTReceived())
			{
				Status = USBD_WINUSB_STATUS_NOT_READY;
				break;
			}

			/* read data from endpoint and start new read operation */
			sts = Endpoint_Read_Stream_LE(Buffer,Length,NULL);
			if (sts != ENDPOINT_RWSTREAM_NoError) 
			{
				Status = USBD_WINUSB_STATUS_FAILURE;
				break;
			}
			Endpoint_ClearOUT();
		}while(0);
	}
	else
	{
		Status = USBD_WINUSB_STATUS_FAILURE;
	}
	return Status;
}

/*The WinUSB API to check the data reception from USB host*/
uint16_t USBD_WINUSB_BytesReceived(uint8_t ep)
{
	uint16_t bytes = 0;
	/* Leave if device is not configured */
	if (USB_DeviceState == DEVICE_STATE_Configured)
	{
		/* Select the winusb out endpoint */
		Endpoint_SelectEndpoint(ep);

		/* check if we have out received and if we have data. if is empty out
		 * packet, flush */
		if (true == Endpoint_IsOUTReceived())
		{
			if (0 == Endpoint_BytesInEndpoint())
			{
				Endpoint_ClearOUT();
				bytes = 0;
			}
			else
			{
				bytes = Endpoint_BytesInEndpoint();
			}
		}

	}

	return bytes;
}

/*The API to configure the USB end points*/
void USBD_WINUSB_ConfigureEndpoints(USBD_WINUSB_Info_t* const WinUSBInfo)
{
	/* configure in endpoint */
	Endpoint_ConfigureEndpointTable(&WinUSBInfo->Config.InEndpoint,1);
	/* configure out endpoint */
	Endpoint_ConfigureEndpointTable(&WinUSBInfo->Config.OutEndpoint,1);
}

/*The USB device control request call back.
 * This can be used by the customers to handle the class/vendor specific
 * USB requests
 * */
void EVENT_USB_Device_ControlRequest()
{
	uint16_t Length = 0;
	uint16_t index = USB_ControlRequest.wIndex;

	/* Serve Microsoft vendor control request */
	if (MS_GET_DESCRIPTOR == (USB_ControlRequest.bmRequestType & REQTYPE_VENDOR && USB_ControlRequest.bRequest))
	{
		/* Send comapt_ID descriptor for automatic winusb detection */
		if (Extended_Compat_ID == index)
		{
			Endpoint_ClearSETUP();

			if (USB_ControlRequest.wLength < Compat_ID.dwLength)
			{
				Length = USB_ControlRequest.wLength;
			}
			else
			{
				Length = Compat_ID.dwLength;
			}

			Endpoint_Write_Control_Stream_LE(&Compat_ID,Length);
		}
		/* Send Extended Properties to get allways the same device GUID */
		if ((USB_ControlRequest.bmRequestType & REQREC_INTERFACE) && (Extended_Properties == index))
		{
			Endpoint_ClearSETUP();

			if (USB_ControlRequest.wLength < Properties.dwLength)
			{
				Length = USB_ControlRequest.wLength;
			}
			else
			{
				Length = Properties.dwLength;
			}
			Endpoint_Write_Control_Stream_LE(&Properties,Length);
		}
	}
}

/*
 * USB device configuration changed event call back.
 * Here we reconfigure the USB end points.
 * */
void EVENT_USB_Device_ConfigurationChanged()
{
	uint8_t i;
	/* Clear configured flag */
	for (i = 1;i < USB_runtime.usbd_max_num_eps;i++)
	{
		device.Endpoints[i].IsConfigured = 0;
	}
	USBD_SetEndpointBuffer(WinUSBInfo.Config.InEndpoint.Address,tx_buf,TX_BUF_SIZE);
	USBD_SetEndpointBuffer(WinUSBInfo.Config.OutEndpoint.Address,rx_buf,RX_BUF_SIZE);
	USBD_WINUSB_ConfigureEndpoints(&WinUSBInfo);

	/* Unconfigure all enabled but not used endpoints */
	for (i = 1;i < USB_runtime.usbd_max_num_eps;i++)
	{
		USBD_Endpoint_t *ep = &device.Endpoints[i];
		if ((0U == ep->IsConfigured) && (1U == ep->IsEnabled))
		{
			device.Driver->EndpointUnconfigure(ep->Number);
		}
	}
	device.IsConfigured = 1;
	USB_DeviceState = DEVICE_STATE_Configured;
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Reset(void)
{
  if(device.IsConfigured)
  {
    USB_Init();
    device.IsConfigured=0;
  }
}
