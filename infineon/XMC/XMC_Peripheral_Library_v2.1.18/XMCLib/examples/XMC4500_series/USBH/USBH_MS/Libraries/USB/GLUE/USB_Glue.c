/*
 * USB_Glue.c
 *
 *  Created on: 20-Apr-2016
 *      Author:
 *  Description: File acts as interface between LUFA USB stack and the
 *  USB low level driver. It implements some of the LUFA API functions
 *  and callback functions.
 */

#include "xmc_common.h"
#include "xmc_scu.h"
#include "core_cm4.h"
#include "USB_Glue.h"
#include "Core/Endpoint.h"
#include "Core/PipeStream.h"


static int32_t USB_Host_ResetDevice(void);


/*Variable to hold control pipe packet size*/
uint8_t USB_Host_ControlPipeSize = PIPE_CONTROLPIPE_DEFAULT_SIZE;

/*Pipe event and data toggle tracker*/
USBH_GLUE_PIPE_STATE_t USBHost_Pipe_State[USBH0_MAX_PIPE_NUM];

/*Pipe identifiers*/
uint32_t XMC_USB_SelectedPipe;
uint8_t XMC_USB_PipeSetup;

/*Function pointer to be called from pipe event callback function*/
USBH_GLUE_APP_IF_t * USBH_EventCB;

/*Static variable to track if bus is suspended
 * Added to check before calling resume API*/
static bool USB_Is_Suspend = false;

/*Callback function fpor USB port event handling*/
void USBH_SignalPortEventHandler (uint8_t port, uint32_t event)
{
  if (event & XMC_USBH_EVENT_CONNECT)
  {
    USB_HostState = HOST_STATE_Powered;
  }
  else if (event & XMC_USBH_EVENT_DISCONNECT)
  {
    USB_HostState = HOST_STATE_WaitForDevice;
  }
  else
  {

  }
  /*Execute callback function*/
  if ((USBH_EventCB != NULL) && (USBH_EventCB->PortEventHandler != NULL))
  {
    USBH_EventCB->PortEventHandler(port, event);
  }
}

/*Function clears the event in the global event log specific to pipe*/
void USBH_PipeEventReset(XMC_USBH_PIPE_HANDLE handle, uint32_t event)
{
    USBHost_Pipe_State[USBH_PIPE_GET_INDEX(handle)].Event &= ~(event);
}

/*Function gets events from the global event log specific to pipe*/
uint32_t USBH_PipeEventGet(XMC_USBH_PIPE_HANDLE handle)
{
  return USBHost_Pipe_State[USBH_PIPE_GET_INDEX(handle)].Event;
}

/*Function gets the data toggle information from the global event log specific to pipe*/
uint32_t USBH_PipeGetToggle(XMC_USBH_PIPE_HANDLE handle)
{
  return USBHost_Pipe_State[USBH_PIPE_GET_INDEX(handle)].Data_toggle;
}

/*Function sets the next data toggle information from the global event log specific to pipe*/
void USBH_PipeSetNextToggle(XMC_USBH_PIPE_HANDLE handle, uint32_t transfer_length)
{
  uint32_t toggle_temp;
  if (((transfer_length == 0) || (transfer_length < USBHost_Pipe_State[USBH_PIPE_GET_INDEX(handle)].MaxPacketSize)) ||
      USBH_TOGGLE_CHECK(USBHost_Pipe_State[USBH_PIPE_GET_INDEX(handle)].MaxPacketSize, transfer_length))
  {
    toggle_temp = (USBHost_Pipe_State[USBH_PIPE_GET_INDEX(handle)].Data_toggle >> 4);
    toggle_temp ^= 0x03;
    USBHost_Pipe_State[USBH_PIPE_GET_INDEX(handle)].Data_toggle = (toggle_temp << 4);
  }
}

/*Function blocks the execution till transfer of the data is complete
 * Checks if device got disconnected or checks if wait timed out*/
uint8_t USBH_WaitForTransfer(XMC_USBH_PIPE_HANDLE handle)
{
  uint32_t delay_counter = XMC_USB_TRANSFER_WAIT_DELAY;
  uint8_t ret_val = HOST_SENDCONTROL_Successful;
  while(!(USBH_PipeEventGet(handle) & XMC_USBH_EVENT_TRANSFER_COMPLETE))
  {
    /*Check if device disconnected*/
    if (USB_HostState ==  HOST_STATE_WaitForDevice)
    {
      Driver_USBH0.PipeTransferAbort(handle);
      ret_val = HOST_SENDCONTROL_DeviceDisconnected;
      break;
    }
    /*Check if wait time elpased*/
    if (!delay_counter)
    {
      Driver_USBH0.PipeTransferAbort(handle);
      ret_val = HOST_SENDCONTROL_SoftwareTimeOut;
      break;
    }
    XMC_USBH_osDelay(1);
    delay_counter--;
  }
  USBH_PipeEventReset(handle, XMC_USBH_EVENT_TRANSFER_COMPLETE);
  return ret_val;
}

/*Callback function for USB host pipe event handling*/
void USBH_SignalPipeEventHandler(XMC_USBH_PIPE_HANDLE pipe_hndl, uint32_t event)
{
  USBHost_Pipe_State[USBH_PIPE_GET_INDEX(pipe_hndl)].Event = event;

  if ((USBH_EventCB != NULL)&&(USBH_EventCB->PipeEventHandler != NULL))
  {
    USBH_EventCB->PipeEventHandler(pipe_hndl, event);
  }
}

void USB_Disable(void)
{
  Driver_USBH0.Uninitialize();
  USB_IsInitialized = false;
}

void USB_Init_Host(USBH_GLUE_APP_IF_t * event_cbk)
{
  USBH_EventCB = event_cbk;
  /*Initialize USB host*/
  XMC_SCU_CLOCK_EnableClock(XMC_SCU_CLOCK_USB);

  USB_HostState                = HOST_STATE_Unattached;
  USB_Host_ConfigurationNumber = 0;
  USB_Host_ControlPipeSize     = PIPE_CONTROLPIPE_DEFAULT_SIZE;

  Driver_USBH0.Uninitialize();
  Driver_USBH0.Initialize(USBH_SignalPortEventHandler, USBH_SignalPipeEventHandler);
  Driver_USBH0.PowerControl(XMC_USBH_POWER_FULL);
  Driver_USBH0.PortVbusOnOff(0,true);
  USB_IsInitialized = true;
}

/*Implementation from Pipe functions for LUFA*/
void Pipe_SelectPipe(const uint32_t Address)
{
  XMC_USB_SelectedPipe = Address;
}
void Pipe_SetPipeToken(const uint8_t Token)
{

}

uint8_t Pipe_GetCurrentPipe(void)
{
  return (uint8_t)XMC_USB_SelectedPipe;
}

/*Dummy stubs for LUFA*/
void Pipe_ClearError(void)
{
  return;
}
void Pipe_Unfreeze(void)
{
  return;
}
uint8_t Pipe_WaitUntilReady(void)
{
  return PIPE_RWSTREAM_NoError;
}
void Pipe_Write_8(const uint8_t Data)
{

}
void Pipe_ClearSETUP(void)
{

}
void Pipe_Freeze(void)
{

}
void Pipe_ClearIN(void)
{

}
void Pipe_ClearOUT(void)
{

}
bool Pipe_IsSETUPSent(void)
{
  return true;
}
bool Pipe_IsOUTReady(void)
{
  return false;
}
uint16_t Pipe_BytesInPipe(void)
{
  if ((USBH_EventCB != NULL) && (USBH_EventCB->GetBytesInPipe != NULL))
  {
    return USBH_EventCB->GetBytesInPipe(XMC_USB_SelectedPipe);
  }
  else
  {
    return 0U;
  }
}
uint8_t Pipe_Read_8(void)
{
  if ((USBH_EventCB != NULL) && (USBH_EventCB->GetReadByte != NULL))
  {
    return USBH_EventCB->GetReadByte(XMC_USB_SelectedPipe);
  }
  else
  {
    return 0U;
  }
}
bool Pipe_IsINReceived(void)
{
  if ((USBH_EventCB != NULL) && (USBH_EventCB->IsINReceived != NULL))
  {
    return USBH_EventCB->IsINReceived(XMC_USB_SelectedPipe);
  }
  else
  {
    return false;
  }
}

/*Host state machine*/
void USB_Host_ProcessNextHostState(void)
{
  uint8_t ErrorCode    = HOST_ENUMERROR_NoError;
  uint8_t SubErrorCode = HOST_ENUMERROR_NoError;

  static uint16_t WaitMSRemaining;
  static uint8_t  PostWaitState;

  switch (USB_HostState)
  {
    case HOST_STATE_WaitForDevice:
      if (WaitMSRemaining)
      {
        if ((SubErrorCode = USB_Host_WaitMS(1)) != HOST_WAITERROR_Successful)
        {
          USB_HostState = PostWaitState;
          ErrorCode     = HOST_ENUMERROR_WaitStage;
          break;
        }

        if (!(--WaitMSRemaining))
          USB_HostState = PostWaitState;
      }

      break;
    case HOST_STATE_Powered:
      USB_HostState = HOST_STATE_Powered_WaitForDeviceSettle;
      break;

    case HOST_STATE_Powered_WaitForDeviceSettle:
      XMC_USBH_osDelay(1000U);
      USB_HostState = HOST_STATE_Powered_WaitForConnect;
      break;

    case HOST_STATE_Powered_WaitForConnect:

      HOST_TASK_NONBLOCK_WAIT(100, HOST_STATE_Powered_DoReset);

      break;
    case HOST_STATE_Powered_DoReset:
      if (USB_Host_ResetDevice() != XMC_USBH_DRIVER_OK)
      {
        ErrorCode = HOST_ENUMERROR_ControlError;
        break;
      }
      HOST_TASK_NONBLOCK_WAIT(200, HOST_STATE_Powered_ConfigPipe);

      break;
    case HOST_STATE_Powered_ConfigPipe:
      USBHost_Pipe_State[0].pipe_handle = Driver_USBH0.PipeCreate(0U, XMC_USBH_SPEED_FULL, 0U, 0U, 0U, EP_TYPE_CONTROL, PIPE_CONTROLPIPE_DEFAULT_SIZE, 0U);
      if (!(USBHost_Pipe_State[0].pipe_handle))
      {
        ErrorCode    = HOST_ENUMERROR_PipeConfigError;
        SubErrorCode = 0;
        break;
      }

      USB_HostState = HOST_STATE_Default;
      break;
    case HOST_STATE_Default:
      USB_ControlRequest = (USB_Request_Header_t)
        {
          .bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_DEVICE),
          .bRequest      = REQ_GetDescriptor,
          .wValue        = (DTYPE_Device << 8),
          .wIndex        = 0,
          .wLength       = 8,
        };

      uint8_t DataBuffer[8];

      Pipe_SelectPipe(PIPE_CONTROLPIPE);
      if ((SubErrorCode = USB_Host_SendControlRequest(DataBuffer)) != HOST_SENDCONTROL_Successful)
      {
        ErrorCode = HOST_ENUMERROR_ControlError;
        break;
      }

      USB_Host_ControlPipeSize = DataBuffer[offsetof(USB_Descriptor_Device_t, Endpoint0Size)];

      if (USB_Host_ResetDevice() != XMC_USBH_DRIVER_OK)
      {
        ErrorCode = HOST_ENUMERROR_ControlError;
        break;
      }

      HOST_TASK_NONBLOCK_WAIT(200, HOST_STATE_Default_PostReset);
      break;
    case HOST_STATE_Default_PostReset:

      /*Set address*/
      USB_ControlRequest = (USB_Request_Header_t)
        {
          .bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_DEVICE),
          .bRequest      = REQ_SetAddress,
          .wValue        = USB_HOST_DEVICEADDRESS,
          .wIndex        = 0,
          .wLength       = 0,
        };

      if ((SubErrorCode = USB_Host_SendControlRequest(NULL)) != HOST_SENDCONTROL_Successful)
      {
        ErrorCode = HOST_ENUMERROR_ControlError;
        break;
      }

      HOST_TASK_NONBLOCK_WAIT(100, HOST_STATE_Default_PostAddressSet);
      break;
    case HOST_STATE_Default_PostAddressSet:

      Driver_USBH0.PipeModify(USBHost_Pipe_State[0].pipe_handle, USB_HOST_DEVICEADDRESS, XMC_USBH_SPEED_FULL, 0, 0, PIPE_CONTROLPIPE_DEFAULT_SIZE);
      USB_HostState = HOST_STATE_Addressed;
      EVENT_USB_Host_DeviceEnumerationComplete();
      break;
    default:
      break;
  }

  if ((ErrorCode != HOST_ENUMERROR_NoError) && (USB_HostState != HOST_STATE_Unattached))
  {
    if ((USBH_EventCB != NULL) && (USBH_EventCB->EnumerationCompleteCb != NULL))
    {
      USBH_EventCB->EnumerationCompleteCb(ErrorCode, SubErrorCode);
    }

    EVENT_USB_Host_DeviceUnattached();

    USB_ResetInterface();
  }
}

void USB_SetHostState(uint8_t state)
{
  USB_HostState = state;
}

void USB_GetHostState(uint8_t * state)
{
  *state = USB_HostState;
}

uint16_t USB_Host_GetFrameNumber(void)
{
  return Driver_USBH0.GetFrameNumber();
}

void USB_ResetInterface(void)
{
  USB_Host_ResetDevice();
}


bool USB_Host_IsBusSuspended(void)
{
  return false;
}

bool USB_Host_IsBusResetComplete(void)
{
  return true;
}

void USB_Host_SuspendBus(void)
{
  USB_Is_Suspend = true;
  Driver_USBH0.PortSuspend(0);
}
void Pipe_ResetPipe(const uint8_t Address)
{
  XMC_USB_SelectedPipe = 0;
}

/*Definition for resume USB bus*/
void USB_Host_ResumeBus(void)
{
  if (USB_Is_Suspend)
  {
    Driver_USBH0.PortResume(0U);
    USB_Is_Suspend = false;
  }
}

static int32_t USB_Host_ResetDevice(void)
{
  return Driver_USBH0.PortReset(0U);
}

/*Function moved from HostStandardReq.c due to hardware dependency*/
extern USB_Request_Header_t USB_ControlRequest;
uint8_t USB_Host_SendControlRequest_PRV(void* const BufferPtr)
{
  uint8_t* DataStream   = (uint8_t*)BufferPtr;
  uint8_t  ReturnStatus = HOST_SENDCONTROL_Successful;
  uint16_t DataLen      = USB_ControlRequest.wLength;

  USB_Host_ResumeBus();

  if ((ReturnStatus = USB_Host_WaitMS(1)) != HOST_WAITERROR_Successful)
    return ReturnStatus;

  Pipe_ClearError();

  Pipe_Unfreeze();

#if defined(ARCH_BIG_ENDIAN)
  Pipe_Write_8(USB_ControlRequest.bmRequestType);
  Pipe_Write_8(USB_ControlRequest.bRequest);
  Pipe_Write_16_LE(USB_ControlRequest.wValue);
  Pipe_Write_16_LE(USB_ControlRequest.wIndex);
  Pipe_Write_16_LE(USB_ControlRequest.wLength);
#else
  uint8_t* HeaderStream = (uint8_t*)&USB_ControlRequest;

  XMC_USB_PipeSetup = XMC_USBH_PACKET_SETUP;
  Driver_USBH0.PipeTransfer((XMC_USBH_PIPE_HANDLE)USBHost_Pipe_State[0].pipe_handle, XMC_USB_PipeSetup, (uint8_t*)HeaderStream, 8U);
  ReturnStatus = USBH_WaitForTransfer(USBHost_Pipe_State[0].pipe_handle);
  if (ReturnStatus != HOST_SENDCONTROL_Successful)
  {
    return ReturnStatus;
  }
#endif

  Pipe_ClearSETUP();

  Pipe_Freeze();

  if ((ReturnStatus = USB_Host_WaitMS(1)) != HOST_WAITERROR_Successful)
    return ReturnStatus;

  if ((USB_ControlRequest.bmRequestType & CONTROL_REQTYPE_DIRECTION) == REQDIR_DEVICETOHOST)
  {

    if (DataStream != NULL)
    {
      XMC_USB_PipeSetup = ((XMC_USBH_PACKET_IN | (0x02UL << 4)));
      while (DataLen)
      {
        Pipe_Unfreeze();

        if (!(Pipe_BytesInPipe()))
          DataLen = 0;

        Driver_USBH0.PipeTransfer((XMC_USBH_PIPE_HANDLE)USBHost_Pipe_State[0].pipe_handle, XMC_USB_PipeSetup, (uint8_t*)DataStream, 8U);
        ReturnStatus = USBH_WaitForTransfer(USBHost_Pipe_State[0].pipe_handle);
        if (ReturnStatus != HOST_SENDCONTROL_Successful)
        {
          return ReturnStatus;
        }

        Pipe_Freeze();
        Pipe_ClearIN();
      }
    }

    XMC_USB_PipeSetup = ((XMC_USBH_PACKET_OUT | (0x02UL << 4)));
    Pipe_Unfreeze();

    /*Setting status phase with empty packet transfer*/
    Driver_USBH0.PipeTransfer((XMC_USBH_PIPE_HANDLE)USBHost_Pipe_State[0].pipe_handle, XMC_USB_PipeSetup, NULL, 0U);
    ReturnStatus = USBH_WaitForTransfer(USBHost_Pipe_State[0].pipe_handle);
    if (ReturnStatus != HOST_SENDCONTROL_Successful)
    {
      return ReturnStatus;
    }
    Pipe_ClearOUT();
  }
  else
  {
    if (DataStream != NULL)
    {
      Pipe_Unfreeze();

      while (DataLen)
      {
        XMC_USB_PipeSetup = ((XMC_USBH_PACKET_OUT | (0x02UL << 4)));
        Driver_USBH0.PipeTransfer((XMC_USBH_PIPE_HANDLE)USBHost_Pipe_State[0].pipe_handle, XMC_USB_PipeSetup, (uint8_t*)DataStream, DataLen);
        ReturnStatus = USBH_WaitForTransfer(USBHost_Pipe_State[0].pipe_handle);
        if (ReturnStatus != HOST_SENDCONTROL_Successful)
        {
          return ReturnStatus;
        }
        DataLen = 0;

        Pipe_ClearOUT();
      }

      Pipe_Freeze();
    }

    XMC_USB_PipeSetup = ((XMC_USBH_PACKET_IN | (0x02UL << 4)));
    Pipe_Unfreeze();

    Driver_USBH0.PipeTransfer((XMC_USBH_PIPE_HANDLE)USBHost_Pipe_State[0].pipe_handle, XMC_USB_PipeSetup, NULL, 0U);
    ReturnStatus = USBH_WaitForTransfer(USBHost_Pipe_State[0].pipe_handle);
    if (ReturnStatus != HOST_SENDCONTROL_Successful)
    {
      return ReturnStatus;
    }
    Pipe_ClearIN();
  }
  return ReturnStatus;
}

bool Pipe_ConfigurePipeTable(const USB_Pipe_Table_t* const Table,
                             const uint8_t Entries)
{
  for (uint8_t i = 0; i < Entries; i++)
  {
    if (!(Table[i].Address))
      continue;
  }

  return true;
}

bool Pipe_IsStalled(void)
{
  return ((USBH_PipeEventGet(XMC_USB_SelectedPipe) & XMC_USBH_EVENT_HANDSHAKE_STALL) == XMC_USBH_EVENT_HANDSHAKE_STALL);
}

uint8_t Pipe_GetBoundEndpointAddress(void)
{
  return USBHost_Pipe_State[USBH_PIPE_GET_INDEX(XMC_USB_SelectedPipe)].Endpoint_Address;
}

void Pipe_ResetToggle(XMC_USBH_PIPE_HANDLE pipe_hndl)
{
  USBHost_Pipe_State[USBH_PIPE_GET_INDEX(XMC_USB_SelectedPipe)].Data_toggle = (0x01 << 4);
}

bool Pipe_IsReadWriteAllowed(void)
{
  return true;
}


/**************************************************************************************************************/

/*----------------------Implementation of delay function using systick----------------------------------------*/

#define USBH_GLUE_CLOCK_FREQUENCY (120000000U)
#define USBH_GLUE_SYSTICK_PERIOD_IN_SEC (0.001F)

volatile uint32_t usbh_glue_systick_flag;

void USBH_GLUE_StartTimer(uint32_t milliseconds)
{
  usbh_glue_systick_flag = milliseconds;

  SysTick_Config((uint32_t)(USBH_GLUE_CLOCK_FREQUENCY * USBH_GLUE_SYSTICK_PERIOD_IN_SEC));

}

/*
*  SysTick Event Handler.
*/
void SysTick_Handler(void)
{
  usbh_glue_systick_flag--;
  if (usbh_glue_systick_flag == 0U)
  {
    SysTick->CTRL  = 0U;
  }

}

bool USBH_GLUE_IsTimerRunning(void)
{
  bool status = false;
  if (usbh_glue_systick_flag)
  {
    status = true;
  }
    return status;
}

uint8_t XMC_USBH_osDelay(uint32_t MS)
{
  USBH_GLUE_StartTimer(MS);
  while(USBH_GLUE_IsTimerRunning());

  return 0;
}

/**
 * \par<b>Description:</b><BR>
 * Entry point for exception vector table.\n
 *
 * This function gets called, if an usb exception (interrupt) was thrown and
 * dispatches it to \ref XMC_USBH_HandleIrq.
 */
void USB0_0_IRQHandler()
{
  uint32_t status = XMC_USBH_GetInterruptStatus();
  XMC_USBH_HandleIrq(status);
}
