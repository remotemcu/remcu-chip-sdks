/*
 * USB_Glue.h
 *
 *  Created on: 20-Apr-2016
 *      Author: jainvish
 */

#ifndef USB_GLUE_USB_GLUE_H_
#define USB_GLUE_USB_GLUE_H_

#include "xmc_usbh.h"

/*Definitions from USBController_AVR8.c*/
#define  __INCLUDE_FROM_USB_DRIVER

/*Inclusion from AVR8 specific headers*/
#include "../Core/USBTask.h"
#include "../Core/Pipe.h"
#include "../Core/Host.h"

/*Macro to indicate that LUFA is ported using XMC specific functions*/
#define XMC_USBH_ENABLED  1

/*Macro to find pipe index using handle*/
#define USBH_PIPE_GET_INDEX(handle) (((uint32_t)handle - (uint32_t)USB0_CH0_BASE)/(0x20U))
/*Extern declaration of pipe logical structure for decoding index of pipe*/
extern volatile XMC_USBH0_pipe_t pipe[USBH0_MAX_PIPE_NUM];
#define USBH_PIPE_GET_LOGICAL_INDEX(handle) ((XMC_USBH0_pipe_t *)handle - (XMC_USBH0_pipe_t *)pipe)
#define USBH_TOGGLE_CHECK(maxpsize, size) (((size/maxpsize)+(size%maxpsize)) % 2)
/*Macro taken from Dave3*/
/**
 * @brief  Dummy macro needed by LUFA
 */
/*Value as used in Pipe_AVR8.h*/
#define PIPE_CONTROLPIPE_DEFAULT_SIZE   64
/*As defined in Host_AVR8.h*/
#define USB_HOST_DEVICEADDRESS          1


/*Enums from Host_AVR8.h*/
enum USB_Host_EnumerationErrorCodes_t
      {
        HOST_ENUMERROR_NoError          = 0, /**< No error occurred. Used internally, this is not a valid
                                              *   ErrorCode parameter value for the \ref EVENT_USB_Host_DeviceEnumerationFailed()
                                              *   event.
                                              */
        HOST_ENUMERROR_WaitStage        = 1, /**< One of the delays between enumeration steps failed
                                              *   to complete successfully, due to a timeout or other
                                              *   error.
                                              */
        HOST_ENUMERROR_NoDeviceDetected = 2, /**< No device was detected, despite the USB data lines
                                              *   indicating the attachment of a device.
                                              */
        HOST_ENUMERROR_ControlError     = 3, /**< One of the enumeration control requests failed to
                                              *   complete successfully.
                                              */
        HOST_ENUMERROR_PipeConfigError  = 4, /**< The default control pipe (address 0) failed to
                                              *   configure correctly.
                                              */
      };
enum USB_Host_WaitMSErrorCodes_t
{
  HOST_WAITERROR_Successful       = 0,
  HOST_WAITERROR_DeviceDisconnect = 1,
  HOST_WAITERROR_PipeError        = 2,
  HOST_WAITERROR_SetupStalled     = 3,
};

/*Pipe event callback function*/
typedef void (*USBH_Pipe_Event_Handler_cb)(XMC_USBH_PIPE_HANDLE pipe_handl, uint32_t event);
/*Port event callback function*/
typedef void (*USBH_Port_Event_Handler_cb)(uint8_t port, uint32_t event);
/*Device enumeration complete callback function*/
typedef void (*USBH_EnumerationComplete_cb)(uint8_t ErrorCode, uint8_t SubErrorCode);

/*Function pointers to provide implementations required for classes*/
/*Function that implements logic to determine the number of bytes of data
 * received on the pipe selected*/
typedef uint16_t (*USBH_BytesInPipe)(XMC_USBH_PIPE_HANDLE pipe_handl);
/*Function that handles pipe receive event by buffering received data*/
typedef uint8_t (*USBH_PipeRead)(XMC_USBH_PIPE_HANDLE pipe_handl);
/*Function that indicates if any new data received on the selected pipe*/
typedef bool (*USBH_PipeIsINReceived)(XMC_USBH_PIPE_HANDLE pipe_handl);



/*Implementation from Pipe_AVR8.h*/
#define PIPE_TOKEN_SETUP    (0 << 0)
#define PIPE_TOKEN_IN       (1 << 0)
#define PIPE_TOKEN_OUT      (2 << 0)

/*Delay count for USB transfer wait*/
#define XMC_USB_TRANSFER_WAIT_DELAY 5000

/*Local structure to keep track of Data toggle and events*/
typedef struct USBH_GLUE_PIPE_STATE
{
  uint32_t Data_toggle;
  uint32_t Event;
  XMC_USBH_PIPE_HANDLE pipe_handle;
  uint32_t MaxPacketSize;
  uint8_t Endpoint_Address;          /*MSB indicates direction of endpoint*/
}USBH_GLUE_PIPE_STATE_t;

/*Structure has members to interface the LUFA stack with
 * class implementation and the application*/
typedef struct USBH_GLUE_APP_IF
{
  USBH_Port_Event_Handler_cb PortEventHandler;        /*Callback function to be executed on
                                                        occurance of a port event*/
  USBH_Pipe_Event_Handler_cb PipeEventHandler;        /*Callback function to be executed on
                                                        occurance of a pipe event*/
  USBH_EnumerationComplete_cb EnumerationCompleteCb;  /*Callback function to be executed after
                                                        device enumeration is complete*/
  /*Following function pointers will be called from the implementation of certain LUFA APIs*/
  USBH_BytesInPipe GetBytesInPipe;                    /*Function will be executed when a call
                                                        to LUFA API Pipe_BytesInPipe is made.*/

  USBH_PipeRead GetReadByte;                          /*Function will be executed when a call
                                                        to LUFA API Pipe_Read_8 is made.*/

  USBH_PipeIsINReceived IsINReceived;                 /*Function will be executed when a call
                                                        to LUFA API Pipe_IsINReceived is made.*/
}USBH_GLUE_APP_IF_t;

void Pipe_SelectPipe(const uint32_t Address);
uint8_t Pipe_GetCurrentPipe(void);
void Pipe_SetPipeToken(const uint8_t Token);
void Pipe_ClearError(void);
void Pipe_Unfreeze(void);
void Pipe_Write_8(const uint8_t Data);
void Pipe_ClearSETUP(void);
void Pipe_Freeze(void);
uint8_t Pipe_WaitUntilReady(void);
uint16_t Pipe_BytesInPipe(void);
uint8_t Pipe_Read_8(void);
void Pipe_ClearIN(void);
void Pipe_ClearOUT(void);
bool Pipe_IsSETUPSent(void);
bool Pipe_IsINReceived(void);
bool Pipe_IsOUTReady(void);
bool Pipe_IsReadWriteAllowed(void);
void USB_Host_ProcessNextHostState(void);
bool USB_Host_IsBusSuspended(void);
bool USB_Host_IsBusResetComplete(void);
void USB_Host_SuspendBus(void);
void Pipe_ResetPipe(const uint8_t Address);
bool Pipe_ConfigurePipeTable(const USB_Pipe_Table_t* const Table, const uint8_t Entries);
extern uint8_t USB_Host_SendControlRequest_PRV(void* const BufferPtr);
uint32_t USBH_PipeGetToggle(XMC_USBH_PIPE_HANDLE handle);
void USBH_PipeEventReset(XMC_USBH_PIPE_HANDLE handle, uint32_t event);
uint32_t USBH_PipeEventGet(XMC_USBH_PIPE_HANDLE handle);
uint8_t USBH_WaitForTransfer(XMC_USBH_PIPE_HANDLE handle);
void USBH_PipeSetNextToggle(XMC_USBH_PIPE_HANDLE handle, uint32_t transfer_length);

extern void USBH_SignalPortEventHandler (uint8_t port, uint32_t event);
extern void USBH_SignalPipeEventHandler(XMC_USBH_PIPE_HANDLE pipe_hndl, uint32_t event);
extern void USB_Init_Host(USBH_GLUE_APP_IF_t * event_cbk);
void USB_SetHostState(uint8_t state);
void USB_GetHostState(uint8_t * state);
uint16_t USB_Host_GetFrameNumber(void);
bool Pipe_IsStalled(void);
uint8_t Pipe_GetBoundEndpointAddress(void);
void Pipe_ResetToggle(XMC_USBH_PIPE_HANDLE pipe_hndl);

/*APIs from USBController_AVR8.h*/
void USB_Init(void);
void USB_Disable(void);
void USB_ResetInterface(void);

/*Definition from Host_AVR8.h*/
void USB_Host_ResumeBus(void);

#define HOST_TASK_NONBLOCK_WAIT(t, state) do{ \
  XMC_USBH_osDelay(t);                         \
  USB_HostState = state;                      \
}while(0);
#define USB_Host_WaitMS(x) XMC_USBH_osDelay(x)


extern uint8_t USB_Host_ControlPipeSize;
extern XMC_USBH_DRIVER_t Driver_USBH0;
extern USBH_GLUE_PIPE_STATE_t USBHost_Pipe_State[USBH0_MAX_PIPE_NUM];
/*Function pointer to be called from pipe event callback function*/
extern USBH_GLUE_APP_IF_t * USBH_EventCB;

#endif /* USB_GLUE_USB_GLUE_H_ */
