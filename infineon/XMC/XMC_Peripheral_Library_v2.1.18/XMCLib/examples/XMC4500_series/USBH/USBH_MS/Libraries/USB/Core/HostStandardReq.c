/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#define  __INCLUDE_FROM_USB_DRIVER
#include "USBMode.h"

#if defined(USB_CAN_BE_HOST)

#define  __INCLUDE_FROM_HOSTSTDREQ_C
#include "HostStandardReq.h"
#include "USB_Glue.h"

uint8_t USB_Host_ConfigurationNumber;

uint8_t USB_Host_SendControlRequest(void* const BufferPtr)
{
	bool BusSuspended    = USB_Host_IsBusSuspended();
	uint8_t ReturnStatus = USB_Host_SendControlRequest_PRV(BufferPtr);

	Pipe_Freeze();

	if (BusSuspended)
	  USB_Host_SuspendBus();

	Pipe_ResetPipe(PIPE_CONTROLPIPE);

	return ReturnStatus;
}

uint8_t USB_Host_SetDeviceConfiguration(const uint8_t ConfigNumber)
{
	uint8_t ErrorCode;

	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_DEVICE),
			.bRequest      = REQ_SetConfiguration,
			.wValue        = ConfigNumber,
			.wIndex        = 0,
			.wLength       = 0,
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	if ((ErrorCode = USB_Host_SendControlRequest(NULL)) == HOST_SENDCONTROL_Successful)
	{
		USB_Host_ConfigurationNumber = ConfigNumber;
		USB_HostState                = (ConfigNumber) ? HOST_STATE_Configured : HOST_STATE_Addressed;
	}

	return ErrorCode;
}

uint8_t USB_Host_GetDeviceConfiguration(uint8_t* const ConfigNumber)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_DEVICE),
			.bRequest      = REQ_GetConfiguration,
			.wValue        = 0,
			.wIndex        = 0,
			.wLength       = sizeof(uint8_t),
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(ConfigNumber);
}

uint8_t USB_Host_GetDescriptor(const uint8_t Type,
                               const uint8_t Index,
                               void* const Buffer,
                               const uint8_t BufferLength)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_DEVICE),
			.bRequest      = REQ_GetDescriptor,
			.wValue        = (((uint16_t)Type << 8) | Index),
			.wIndex        = 0,
			.wLength       = BufferLength,
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(Buffer);
}

uint8_t USB_Host_GetDeviceStatus(uint8_t* const FeatureStatus)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_DEVICE),
			.bRequest      = REQ_GetStatus,
			.wValue        = 0,
			.wIndex        = 0,
			.wLength       = 0,
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(FeatureStatus);
}

uint8_t USB_Host_ClearEndpointStall(const uint8_t EndpointAddress)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_ENDPOINT),
			.bRequest      = REQ_ClearFeature,
			.wValue        = FEATURE_SEL_EndpointHalt,
			.wIndex        = EndpointAddress,
			.wLength       = 0,
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(NULL);
}

uint8_t USB_Host_SetInterfaceAltSetting(const uint8_t InterfaceIndex,
                                        const uint8_t AltSetting)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_INTERFACE),
			.bRequest      = REQ_SetInterface,
			.wValue        = AltSetting,
			.wIndex        = InterfaceIndex,
			.wLength       = 0,
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(NULL);
}

uint8_t USB_Host_GetInterfaceAltSetting(const uint8_t InterfaceIndex,
                                        uint8_t* const AltSetting)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_INTERFACE),
			.bRequest      = REQ_GetInterface,
			.wValue        = 0,
			.wIndex        = InterfaceIndex,
			.wLength       = sizeof(uint8_t),
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(AltSetting);
}

#endif

