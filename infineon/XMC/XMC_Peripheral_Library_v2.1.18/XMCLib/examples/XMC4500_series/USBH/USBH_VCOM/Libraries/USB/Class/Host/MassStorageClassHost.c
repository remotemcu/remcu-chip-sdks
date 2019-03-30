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
#include "../../Core/USBMode.h"

#if defined(USB_CAN_BE_HOST)

#define  __INCLUDE_FROM_MS_DRIVER
#define  __INCLUDE_FROM_MASSSTORAGE_HOST_C
#include "MassStorageClassHost.h"
#include "USB_Glue.h"

XMC_USBH_PIPE_HANDLE MS_BULK_OUT_pipe_handle, MS_BULK_IN_pipe_handle;

/*Made global to use it from DSRAM1 since local object would be stored in PSRAM and hence not accessible to DMA*/
#if defined __ICCARM__/*IAR*/
#pragma data_alignment=8
MS_CommandBlockWrapper_t SCSICommandBlock =
#else
MS_CommandBlockWrapper_t SCSICommandBlock __attribute__ ((aligned (64)))=
#endif
  {
    .DataTransferLength = CPU_TO_LE32(0),
    .Flags              = MS_COMMAND_DIR_DATA_IN,
    .LUN                = 0,
    .SCSICommandLength  = 6,
    .SCSICommandData    =
      {
        SCSI_CMD_TEST_UNIT_READY,
        0x00,                   // Reserved
        0x00,                   // Reserved
        0x00,                   // Reserved
        0x00,                   // Reserved
        0x00                    // Unused (control)
      }
  };

uint8_t MS_Host_ConfigurePipes(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo,
                               uint16_t ConfigDescriptorSize,
							   void* ConfigDescriptorData)
{
	USB_Descriptor_Endpoint_t*  DataINEndpoint       = NULL;
	USB_Descriptor_Endpoint_t*  DataOUTEndpoint      = NULL;
	USB_Descriptor_Interface_t* MassStorageInterface = NULL;

	uint32_t IN_pipe_index, OUT_pipe_index;

	memset(&MSInterfaceInfo->State, 0x00, sizeof(MSInterfaceInfo->State));

	if (DESCRIPTOR_TYPE(ConfigDescriptorData) != DTYPE_Configuration)
	  return MS_ENUMERROR_InvalidConfigDescriptor;

	while (!(DataINEndpoint) || !(DataOUTEndpoint))
	{
		if (!(MassStorageInterface) ||
		    USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
		                              DCOMP_MS_Host_NextMSInterfaceEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
			                              DCOMP_MS_Host_NextMSInterface) != DESCRIPTOR_SEARCH_COMP_Found)
			{
				return MS_ENUMERROR_NoCompatibleInterfaceFound;
			}

			MassStorageInterface = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Interface_t);

			DataINEndpoint  = NULL;
			DataOUTEndpoint = NULL;

			continue;
		}

		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Endpoint_t);

		if ((EndpointData->EndpointAddress & ENDPOINT_DIR_MASK) == ENDPOINT_DIR_IN)
		  DataINEndpoint  = EndpointData;
		else
		  DataOUTEndpoint = EndpointData;
	}

	MSInterfaceInfo->Config.DataINPipe.Size  = le16_to_cpu(DataINEndpoint->EndpointSize);
	MSInterfaceInfo->Config.DataINPipe.EndpointAddress = DataINEndpoint->EndpointAddress;
	MSInterfaceInfo->Config.DataINPipe.Type  = EP_TYPE_BULK;

	MSInterfaceInfo->Config.DataOUTPipe.Size = le16_to_cpu(DataOUTEndpoint->EndpointSize);
	MSInterfaceInfo->Config.DataOUTPipe.EndpointAddress = DataOUTEndpoint->EndpointAddress;
	MSInterfaceInfo->Config.DataOUTPipe.Type = EP_TYPE_BULK;

	/*Create pipe for IN endpoint*/
	MS_BULK_IN_pipe_handle = Driver_USBH0.PipeCreate(1U, XMC_USBH_SPEED_FULL, 0U, 0U,
	    (DataINEndpoint->EndpointAddress & 0x7f), EP_TYPE_BULK, DataINEndpoint->EndpointSize, 0U);
	IN_pipe_index = USBH_PIPE_GET_INDEX(MS_BULK_IN_pipe_handle);
	USBHost_Pipe_State[IN_pipe_index].pipe_handle = MS_BULK_IN_pipe_handle;
	if(USBHost_Pipe_State[IN_pipe_index].pipe_handle == (XMC_USBH_PIPE_HANDLE)NULL)
	{
	  return false;
	}
  USBHost_Pipe_State[IN_pipe_index].Endpoint_Address = DataINEndpoint->EndpointAddress;
  USBHost_Pipe_State[IN_pipe_index].Data_toggle = (0x01 << 4);
  USBHost_Pipe_State[IN_pipe_index].MaxPacketSize = DataINEndpoint->EndpointSize;


  /*Create pipe for OUT endpoint*/
	MS_BULK_OUT_pipe_handle = Driver_USBH0.PipeCreate(1U, XMC_USBH_SPEED_FULL, 0U, 0U,
	    DataOUTEndpoint->EndpointAddress, EP_TYPE_BULK, DataOUTEndpoint->EndpointSize, 0U);
	OUT_pipe_index = USBH_PIPE_GET_INDEX(MS_BULK_OUT_pipe_handle);
	USBHost_Pipe_State[OUT_pipe_index].pipe_handle = MS_BULK_OUT_pipe_handle;
  if(USBHost_Pipe_State[OUT_pipe_index].pipe_handle == (XMC_USBH_PIPE_HANDLE)NULL)
  {
    return false;
  }
  USBHost_Pipe_State[OUT_pipe_index].Endpoint_Address = DataOUTEndpoint->EndpointAddress;
  USBHost_Pipe_State[OUT_pipe_index].Data_toggle = (0x01 << 4);
  USBHost_Pipe_State[OUT_pipe_index].MaxPacketSize = DataOUTEndpoint->EndpointSize;

	MSInterfaceInfo->State.InterfaceNumber = MassStorageInterface->InterfaceNumber;
	MSInterfaceInfo->State.IsActive = true;
	return MS_ENUMERROR_NoError;
}

static uint8_t DCOMP_MS_Host_NextMSInterface(void* const CurrentDescriptor)
{
	USB_Descriptor_Header_t* Header = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Header_t);

	if (Header->Type == DTYPE_Interface)
	{
		USB_Descriptor_Interface_t* Interface = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Interface_t);

		if ((Interface->Class    == MS_CSCP_MassStorageClass)        &&
		    (Interface->SubClass == MS_CSCP_SCSITransparentSubclass) &&
		    (Interface->Protocol == MS_CSCP_BulkOnlyTransportProtocol))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}

	return DESCRIPTOR_SEARCH_NotFound;
}

static uint8_t DCOMP_MS_Host_NextMSInterfaceEndpoint(void* const CurrentDescriptor)
{
	USB_Descriptor_Header_t* Header = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Header_t);

	if (Header->Type == DTYPE_Endpoint)
	{
		USB_Descriptor_Endpoint_t* Endpoint = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Endpoint_t);

		uint8_t EndpointType = (Endpoint->Attributes & EP_TYPE_MASK);

		if (EndpointType == EP_TYPE_BULK)
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}
	else if (Header->Type == DTYPE_Interface)
	{
		return DESCRIPTOR_SEARCH_Fail;
	}
	return DESCRIPTOR_SEARCH_NotFound;
}

#if defined __ICCARM__/*IAR*/
#pragma data_alignment=8
MS_CommandStatusWrapper_t SCSIStatusBlock;
#else
MS_CommandStatusWrapper_t __attribute__ ((aligned (64))) SCSIStatusBlock;
#endif
static uint8_t MS_Host_SendCommand(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo,
                                   MS_CommandBlockWrapper_t* const SCSICommandBlock,
                                   const void* const BufferPtr)
{
	uint8_t ErrorCode = PIPE_RWSTREAM_NoError;
	uint32_t Data_toggle;

	if (++MSInterfaceInfo->State.TransactionTag == 0xFFFFFFFF)
	  MSInterfaceInfo->State.TransactionTag = 1;

	SCSICommandBlock->Signature = CPU_TO_LE32(MS_CBW_SIGNATURE);
	SCSICommandBlock->Tag       = cpu_to_le32(MSInterfaceInfo->State.TransactionTag);

	Pipe_SelectPipe(MS_BULK_OUT_pipe_handle);
	Pipe_Unfreeze();

	Data_toggle = USBH_PipeGetToggle(MS_BULK_OUT_pipe_handle);
	Data_toggle |= XMC_USBH_PACKET_OUT;
	if(Driver_USBH0.PipeTransfer(MS_BULK_OUT_pipe_handle, Data_toggle, (uint8_t *)SCSICommandBlock,
	    sizeof(MS_CommandBlockWrapper_t)) != XMC_USBH_DRIVER_OK)
	{
		return ErrorCode;
	}
	USBH_WaitForTransfer(MS_BULK_OUT_pipe_handle);
	USBH_PipeSetNextToggle(MS_BULK_OUT_pipe_handle, sizeof(MS_CommandBlockWrapper_t));


	Pipe_ClearOUT();
	Pipe_WaitUntilReady();

	Pipe_Freeze();

	if (BufferPtr != NULL)
	{
		ErrorCode = MS_Host_SendReceiveData(MSInterfaceInfo, SCSICommandBlock, (void*)BufferPtr);

		if ((ErrorCode != PIPE_RWSTREAM_NoError) && (ErrorCode != PIPE_RWSTREAM_PipeStalled))
		{
			Pipe_Freeze();
			return ErrorCode;
		}
	}


	return MS_Host_GetReturnedStatus(MSInterfaceInfo, &SCSIStatusBlock);
}


static uint8_t MS_Host_SendReceiveData(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo,
                                       MS_CommandBlockWrapper_t* const SCSICommandBlock,
                                       void* BufferPtr)
{

	uint8_t  ErrorCode = PIPE_RWSTREAM_NoError;
	int32_t status;
	uint32_t Data_toggle;

	uint32_t BytesRem  = le32_to_cpu(SCSICommandBlock->DataTransferLength);

	if (SCSICommandBlock->Flags & MS_COMMAND_DIR_DATA_IN)
	{

		Pipe_SelectPipe(MS_BULK_IN_pipe_handle);
		Pipe_Unfreeze();

		Data_toggle = USBH_PipeGetToggle(MS_BULK_IN_pipe_handle);
		Data_toggle |= XMC_USBH_PACKET_IN;

		Driver_USBH0.PipeTransfer(MS_BULK_IN_pipe_handle, Data_toggle, (uint8_t *)BufferPtr,
		BytesRem);
		USBH_WaitForTransfer(MS_BULK_IN_pipe_handle);
		USBH_PipeSetNextToggle(MS_BULK_IN_pipe_handle, BytesRem);
		status = USBH_PipeEventGet(MS_BULK_IN_pipe_handle);
		if(status & XMC_USBH_EVENT_HANDSHAKE_STALL)
		{
		  ErrorCode = PIPE_RWSTREAM_PipeStalled;
		  Pipe_ResetToggle(MS_BULK_IN_pipe_handle);
		  USB_Host_ClearEndpointStall(Pipe_GetBoundEndpointAddress());
		  return ErrorCode;
		}

		Pipe_ClearIN();
	}
	else
	{
		Pipe_SelectPipe(MS_BULK_OUT_pipe_handle);
		Pipe_Unfreeze();

		Data_toggle = USBH_PipeGetToggle(MS_BULK_OUT_pipe_handle);
		Data_toggle |= XMC_USBH_PACKET_OUT;

		Driver_USBH0.PipeTransfer(MS_BULK_OUT_pipe_handle, Data_toggle, (uint8_t *)BufferPtr,
				BytesRem);
		USBH_WaitForTransfer(MS_BULK_OUT_pipe_handle);
		USBH_PipeSetNextToggle(MS_BULK_OUT_pipe_handle, BytesRem);
		status = USBH_PipeEventGet(MS_BULK_OUT_pipe_handle);
		if(status & XMC_USBH_EVENT_HANDSHAKE_STALL)
		{
		  ErrorCode = PIPE_RWSTREAM_PipeStalled;
		  Pipe_ResetToggle(MS_BULK_OUT_pipe_handle);
		  USB_Host_ClearEndpointStall(Pipe_GetBoundEndpointAddress());
		  return ErrorCode;
		}

		Pipe_ClearOUT();

	}

	Pipe_Freeze();

	return ErrorCode;

}


static uint8_t MS_Host_GetReturnedStatus(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo,
                                         MS_CommandStatusWrapper_t* const SCSICommandStatus)
{
	uint8_t ErrorCode = PIPE_RWSTREAM_NoError;
	uint32_t Data_toggle;

	Pipe_SelectPipe(MS_BULK_IN_pipe_handle);
	Pipe_Unfreeze();

	Data_toggle = USBH_PipeGetToggle(MS_BULK_IN_pipe_handle);
	Data_toggle |= XMC_USBH_PACKET_IN;

	if(Driver_USBH0.PipeTransfer(MS_BULK_IN_pipe_handle, Data_toggle, (uint8_t *)SCSICommandStatus,
	    sizeof(MS_CommandStatusWrapper_t)) != XMC_USBH_DRIVER_OK)
	{
		return ErrorCode;
	}
	USBH_WaitForTransfer(MS_BULK_IN_pipe_handle);
	USBH_PipeSetNextToggle(MS_BULK_IN_pipe_handle, sizeof(MS_CommandStatusWrapper_t));

	Pipe_ClearIN();
	Pipe_Freeze();

	if (SCSICommandStatus->Status != MS_SCSI_COMMAND_Pass)
		ErrorCode = MS_ERROR_LOGICAL_CMD_FAILED;
	return ErrorCode;
}

uint8_t MS_Host_ResetMSInterface(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo)
{
	uint8_t ErrorCode;

	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = MS_REQ_MassStorageReset,
			.wValue        = 0,
			.wIndex        = MSInterfaceInfo->State.InterfaceNumber,
			.wLength       = 0,
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	if ((ErrorCode = USB_Host_SendControlRequest(NULL)) != HOST_SENDCONTROL_Successful)
	  return ErrorCode;

	Pipe_SelectPipe(MS_BULK_IN_pipe_handle);

	Pipe_ResetToggle(MS_BULK_IN_pipe_handle);
	if ((ErrorCode = USB_Host_ClearEndpointStall(Pipe_GetBoundEndpointAddress())) != HOST_SENDCONTROL_Successful)
	  return ErrorCode;

	Pipe_SelectPipe(MS_BULK_OUT_pipe_handle);

	Pipe_ResetToggle(MS_BULK_OUT_pipe_handle);
	if ((ErrorCode = USB_Host_ClearEndpointStall(Pipe_GetBoundEndpointAddress())) != HOST_SENDCONTROL_Successful)
	  return ErrorCode;

	return HOST_SENDCONTROL_Successful;
}

uint8_t MS_Host_GetMaxLUN(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo,
                          uint8_t* const MaxLUNIndex)
{
	uint8_t ErrorCode;

	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = MS_REQ_GetMaxLUN,
			.wValue        = 0,
			.wIndex        = MSInterfaceInfo->State.InterfaceNumber,
			.wLength       = 1,
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	if ((ErrorCode = USB_Host_SendControlRequest(MaxLUNIndex)) == HOST_SENDCONTROL_SetupStalled)
	{
		*MaxLUNIndex = 0;
		ErrorCode    = HOST_SENDCONTROL_Successful;
	}

	return ErrorCode;
}

uint8_t MS_Host_GetInquiryData(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo,
                               const uint8_t LUNIndex,
                               SCSI_Inquiry_Response_t* const InquiryData)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(MSInterfaceInfo->State.IsActive))
	  return HOST_SENDCONTROL_DeviceDisconnected;

	SCSICommandBlock.DataTransferLength = CPU_TO_LE32(sizeof(SCSI_Inquiry_Response_t));
  SCSICommandBlock.Flags              = MS_COMMAND_DIR_DATA_IN;
  SCSICommandBlock.LUN                = LUNIndex;
  SCSICommandBlock.SCSICommandLength  = 6;
  SCSICommandBlock.SCSICommandData[0] = SCSI_CMD_INQUIRY;
  SCSICommandBlock.SCSICommandData[1] = 0x00;                            // Reserve
  SCSICommandBlock.SCSICommandData[2] = 0x00;                            // Reserved
  SCSICommandBlock.SCSICommandData[3] = 0x00;                            // Reserved
  SCSICommandBlock.SCSICommandData[4] = sizeof(SCSI_Inquiry_Response_t); // Allocation Length
  SCSICommandBlock.SCSICommandData[5] = 0x00;                             // Unused (control)

	return MS_Host_SendCommand(MSInterfaceInfo, &SCSICommandBlock, InquiryData);
}


uint8_t MS_Host_TestUnitReady(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo,
                              const uint8_t LUNIndex)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(MSInterfaceInfo->State.IsActive))
	  return HOST_SENDCONTROL_DeviceDisconnected;
  SCSICommandBlock.DataTransferLength = CPU_TO_LE32(0);
  SCSICommandBlock.Flags              = MS_COMMAND_DIR_DATA_IN;
  SCSICommandBlock.LUN                = LUNIndex;
  SCSICommandBlock.SCSICommandLength  = 6;
  SCSICommandBlock.SCSICommandData[0] = SCSI_CMD_TEST_UNIT_READY;
  SCSICommandBlock.SCSICommandData[1] = 0x00;                            // Reserve
  SCSICommandBlock.SCSICommandData[2] = 0x00;                            // Reserved
  SCSICommandBlock.SCSICommandData[3] = 0x00;                            // Reserved
  SCSICommandBlock.SCSICommandData[4] = 0x00;                            // Allocation Length
  SCSICommandBlock.SCSICommandData[5] = 0x00;                            // Unused (control)

	return MS_Host_SendCommand(MSInterfaceInfo, &SCSICommandBlock, NULL);
}

uint8_t MS_Host_ReadDeviceCapacity(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo,
                                   const uint8_t LUNIndex,
                                   SCSI_Capacity_t* const DeviceCapacity)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(MSInterfaceInfo->State.IsActive))
	  return HOST_SENDCONTROL_DeviceDisconnected;

	uint8_t ErrorCode;

	  SCSICommandBlock.DataTransferLength = CPU_TO_LE32(sizeof(SCSI_Capacity_t));
	      SCSICommandBlock.Flags              = MS_COMMAND_DIR_DATA_IN;
	      SCSICommandBlock.LUN                = LUNIndex;
	      SCSICommandBlock.SCSICommandLength  = 10;
	      SCSICommandBlock.SCSICommandData[0] = SCSI_CMD_READ_CAPACITY_10;
	      SCSICommandBlock.SCSICommandData[1] =0x00;                   // Reserved
	      SCSICommandBlock.SCSICommandData[2] =0x00;                   // MSB of Logical block address
	      SCSICommandBlock.SCSICommandData[3] =0x00;
	      SCSICommandBlock.SCSICommandData[4] =0x00;
	      SCSICommandBlock.SCSICommandData[5] =0x00;                   // LSB of Logical block address
	      SCSICommandBlock.SCSICommandData[6] =0x00;                   // Reserved
	      SCSICommandBlock.SCSICommandData[7] =0x00;                   // Reserved
	      SCSICommandBlock.SCSICommandData[8] =0x00;                   // Partial Medium Indicator
	      SCSICommandBlock.SCSICommandData[9] =0x00;                   // Unused (control)

	if ((ErrorCode = MS_Host_SendCommand(MSInterfaceInfo, &SCSICommandBlock, DeviceCapacity)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	DeviceCapacity->Blocks    = BE32_TO_CPU(DeviceCapacity->Blocks);
	DeviceCapacity->BlockSize = BE32_TO_CPU(DeviceCapacity->BlockSize);

	return PIPE_RWSTREAM_NoError;
}

uint8_t MS_Host_RequestSense(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo,
                             const uint8_t LUNIndex,
                             SCSI_Request_Sense_Response_t* const SenseData)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(MSInterfaceInfo->State.IsActive))
	  return HOST_SENDCONTROL_DeviceDisconnected;

	  SCSICommandBlock.DataTransferLength = CPU_TO_LE32(sizeof(SCSI_Request_Sense_Response_t));
	  SCSICommandBlock.Flags              = MS_COMMAND_DIR_DATA_IN;
	  SCSICommandBlock.LUN                = LUNIndex;
	  SCSICommandBlock.SCSICommandLength  = 6;
	  SCSICommandBlock.SCSICommandData[0] =	SCSI_CMD_REQUEST_SENSE;
	  SCSICommandBlock.SCSICommandData[1] =0x00;                                  // Reserved
	  SCSICommandBlock.SCSICommandData[2] =0x00;                                  // Reserved
	  SCSICommandBlock.SCSICommandData[3] =0x00;                                  // Reserved
	  SCSICommandBlock.SCSICommandData[4] =sizeof(SCSI_Request_Sense_Response_t); // Allocation Length
	  SCSICommandBlock.SCSICommandData[5] =0x00;                                   // Unused (control)

	return MS_Host_SendCommand(MSInterfaceInfo, &SCSICommandBlock, SenseData);
}

uint8_t MS_Host_PreventAllowMediumRemoval(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo,
                                          const uint8_t LUNIndex,
                                          const bool PreventRemoval)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(MSInterfaceInfo->State.IsActive))
	  return HOST_SENDCONTROL_DeviceDisconnected;

	SCSICommandBlock.DataTransferLength = CPU_TO_LE32(0);
	SCSICommandBlock.Flags              = MS_COMMAND_DIR_DATA_OUT;
	SCSICommandBlock.LUN                = LUNIndex;
	SCSICommandBlock.SCSICommandLength  = 6;
	SCSICommandBlock.SCSICommandData[0] =	SCSI_CMD_PREVENT_ALLOW_MEDIUM_REMOVAL;
	SCSICommandBlock.SCSICommandData[1] =0x00;                   // Reserved
	SCSICommandBlock.SCSICommandData[2] =0x00;                   // Reserved
	SCSICommandBlock.SCSICommandData[3] =PreventRemoval;         // Prevent flag
	SCSICommandBlock.SCSICommandData[4] =0x00;                   // Reserved
	SCSICommandBlock.SCSICommandData[5] =0x00;                    // Unused (control)

	return MS_Host_SendCommand(MSInterfaceInfo, &SCSICommandBlock, NULL);
}

uint8_t MS_Host_ReadDeviceBlocks(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo,
                                 const uint8_t LUNIndex,
                                 const uint32_t BlockAddress,
                                 const uint8_t Blocks,
                                 const uint16_t BlockSize,
                                 void* BlockBuffer)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(MSInterfaceInfo->State.IsActive))
	  return HOST_SENDCONTROL_DeviceDisconnected;

	SCSICommandBlock.DataTransferLength = cpu_to_le32((uint32_t)Blocks * BlockSize);
	SCSICommandBlock.Flags              = MS_COMMAND_DIR_DATA_IN;
	SCSICommandBlock.LUN                = LUNIndex;
	SCSICommandBlock.SCSICommandLength  = 10;
	SCSICommandBlock.SCSICommandData[0] = SCSI_CMD_READ_10;
	SCSICommandBlock.SCSICommandData[1] =0x00;                   // Unused (control bits, all off)
	SCSICommandBlock.SCSICommandData[2] =(BlockAddress >> 24);   // MSB of Block Address
	SCSICommandBlock.SCSICommandData[3] =(BlockAddress >> 16);
	SCSICommandBlock.SCSICommandData[4] =(BlockAddress >> 8);
	SCSICommandBlock.SCSICommandData[5] =(BlockAddress & 0xFF);  // LSB of Block Address
	SCSICommandBlock.SCSICommandData[6] =0x00;                   // Reserved
	SCSICommandBlock.SCSICommandData[7] =0x00;                   // MSB of Total Blocks to Read
	SCSICommandBlock.SCSICommandData[8] =Blocks;                 // LSB of Total Blocks to Read
	SCSICommandBlock.SCSICommandData[9] =0x00;                    // Unused (control)

	return MS_Host_SendCommand(MSInterfaceInfo, &SCSICommandBlock, BlockBuffer);
}

uint8_t MS_Host_WriteDeviceBlocks(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo,
                                  const uint8_t LUNIndex,
                                  const uint32_t BlockAddress,
                                  const uint8_t Blocks,
                                  const uint16_t BlockSize,
                                  const void* BlockBuffer)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(MSInterfaceInfo->State.IsActive))
	  return HOST_SENDCONTROL_DeviceDisconnected;

	SCSICommandBlock.DataTransferLength = cpu_to_le32((uint32_t)Blocks * BlockSize);
	SCSICommandBlock.Flags              = MS_COMMAND_DIR_DATA_OUT;
	SCSICommandBlock.LUN                = LUNIndex;
	SCSICommandBlock.SCSICommandLength  = 10;
	SCSICommandBlock.SCSICommandData[0] = SCSI_CMD_WRITE_10;
	SCSICommandBlock.SCSICommandData[1] =0x00;                   // Unused (control bits, all off)
	SCSICommandBlock.SCSICommandData[2] =(BlockAddress >> 24);   // MSB of Block Address
	SCSICommandBlock.SCSICommandData[3] =(BlockAddress >> 16);
	SCSICommandBlock.SCSICommandData[4] =(BlockAddress >> 8);
	SCSICommandBlock.SCSICommandData[5] =(BlockAddress & 0xFF);  // LSB of Block Address
	SCSICommandBlock.SCSICommandData[6] =0x00;                   // Reserved
	SCSICommandBlock.SCSICommandData[7] =0x00;                   // MSB of Total Blocks to Write
	SCSICommandBlock.SCSICommandData[8] =Blocks;                 // LSB of Total Blocks to Write
	SCSICommandBlock.SCSICommandData[9] =0x00;                    // Unused (control)

	return MS_Host_SendCommand(MSInterfaceInfo, &SCSICommandBlock, BlockBuffer);
}

#endif

