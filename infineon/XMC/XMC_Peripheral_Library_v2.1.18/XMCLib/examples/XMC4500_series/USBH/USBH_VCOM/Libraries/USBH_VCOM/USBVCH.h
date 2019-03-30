/* CODE_BLOCK_BEGIN[USBVCH.h]*/

/* THIS FILE IS PROVIDED BY DAVE.
 * THIS FILE IS GENERATED.
 */

/*******************************************************************************
 *
 * Copyright (C) 2011 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
********************************************************************************
**                                                                            **
**                                                                            **
** PLATFORM : Infineon XMC4000 Series                                         **
**                                                                            **
** COMPILER : Compiler Independent                                            **
**                                                                            **
** AUTHOR : App Developer                                                     **
**                                                                            **
** MAY BE CHANGED BY USER [yes/no]: Yes                                       **
**                                                                            **
** MODIFICATION DATE : Nov 29, 2012                                            **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                       Author(s) Identity                                   **
********************************************************************************
**                                                                            **
** Initials    Name                                                           **
** ---------------------------------------------------------------------------**
** CM          App Developer                                                  **
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
 * @file   USBVCH.h
 *
 * @brief  This file contains the function prototypes and type declarations of
 *         USB VCOM HOST Application.
 *
 */

#ifndef _USBVCH_H_
#define _USBVCH_H_

#ifdef __cplusplus
extern "C"{
#endif

/******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "xmc_usbh.h"


/**
 * @ingroup USBVCH_publicparam
 * @{
 */
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*******************************************************************************
 *                                ENUMERATIONS                                **
******************************************************************************/
/**
 * This enumerates USBVCH App Errors.
 */

typedef enum USBVCH_ErrorCodesType
{
  /*
  ERRCODESTRING = USBVCH_ERROR
  STRCODESTRING = error in USBVCH App.
  */
	USBVCH_ERROR =1,

  /**
   * Device is attached (2)
   */
  /*
  ERRCODESTRING = USBVCH_DEVICE_ATTACHED
  STRCODESTRING = Device is attached
  */
	USBVCH_DEVICE_ATTACHED,
  /**
   * Device is enumerated by the Host (3)
   */
  /*
  ERRCODESTRING = USBVCH_DEVICE_ENUM_COMPLETE
  STRCODESTRING = Device is enumerated by the Host
  */
	USBVCH_DEVICE_ENUM_COMPLETE,
  /**
   * Device is un-attached (4)
   */
  /*
  ERRCODESTRING = USBVCH_DEVICE_UNATTACHED
  STRCODESTRING = Device is unattached
  */
	USBVCH_DEVICE_UNATTACHED,
  /**
   * Sub-Error of an Error. (5)
   */
  /*
  ERRCODESTRING = USBVCH_SUB_ERROR
  STRCODESTRING = The Error is in USBCDCH001 App,The Error Code is %hd and Sub-error code is %hd
  */
	USBVCH_SUB_ERROR,

} USBVCH_ErrorCodesType;

/**
 * @}
 */

#define SERIAL_STATE_SIZE 10

/**
 * @ingroup USBVCH_apidoc
 * @{
 */
/*******************************************************************************
** FUNCTION PROTOTYPES                                                        **
*******************************************************************************/

/**
 * @brief The function enumerates the attached USB device.\n\n
 * 		  This function :\n
 * 		  1) Gets USB Device Configuration descriptor.\n
 * 		  2) Sets the PIPE configuration for further USB communication.\n
 * 		  3) Sets device configuration to one.\n
 * 		  4) Sets the USB device in "Configured Mode".\n\n
 *        In order to call USBVCH_Process()  following procedure should be
 *        followed:\n
 *        1) Call USB_SetHostState(HOST_STATE_WaitForDevice) to put the USB
 *        host in "Wait for Device " status.\n
 *        2) Call USBVCH_Init() initialize the USB core in Host mode.\n
 *        3) Call USBVCH_Process() continuously  to put the attached device
 *        in "Configured Mode" status.\n
 *        4) Call USBVCH_CDCHost_USBTask() to change control line states and
 *         synchronize.\n
 *        5) Call USB_USBTask() continuously to put the attached device in
 *        "Addressed Mode" status.
 *
 * @return status_t
 * DAVEApp_SUCCESS:  If the initialization is successful\n
 * @code
 * #include <XMC4500.h>
 * #include <DAVE3.h>
 * #include "Dave\Generated\inc\USBVCH\VirtualSerialHost.h"

 *
 * int main(void)
 * {
 *	uint8_t USBHostState;
 *
 *	DAVE_Init();
 *
 *  // Put the USB host "Wait for device" state
 *	USB_SetHostState(HOST_STATE_WaitForDevice);
 *
 *	//Initialize the USB core in Host mode
 *	USBVCH_Init();
 *
 *	while (1)
 *	{
 *
 *		// Enumerate the attached device and put it to the "Configured Mode"
 *		// status.
 *		USBVCH_Process();
 *
 *		// Get the host status
 *		USB_GetHostState(&USBHostState);
 *
 *		if(USBHostState == HOST_STATE_Configured)
 *		{
 *		}
 *		 // Calls USB Management function for setting
 *		 // control line states
 *		USBVCH_CDCHost_USBTask();
 *
 *		// Enumerate the attached device and put it to the "Addressed Mode"
 *		// status.
 *		USB_USBTask();
 *	}
 * }
 * @endcode
 */
uint32_t USBVCH_Process(void);

/**
 * @brief The function initializes the USB core layer and register
 *        call backs.\n\n
 * 		  This function :\n
 * 		  1) Initializes the USB core driver.\n
 * 		  2) Registers the USB Host Event.\n
 * 		  3) Registers the USB Connect-Disconnect Event.\n
 * 		  4) Registers the USB HID report parser call back.\n
 * 		  5) Starts the USB Host controller.\n\n
 *        In order to call USBVCH_Init()  following procedure should be
 *        followed:\n
 *        1) Call USB_SetHostState(HOST_STATE_WaitForDevice) to put the USB
 *        host in "Wait for Device " status.\n
 *        2) Call USBVCH_Init() initialize the USB core in Host mode.
 * @return status_t
 * DAVEApp_SUCCESS:  If the initialization is successful.
 * @code
 * #include <XMC4500.h>
 * #include <DAVE3.h>
 * #include "Dave\Generated\inc\USBVCH\VirtualSerialHost.h"

 *
 * int main(void)
 * {
 *	uint8_t USBHostState;
 *
 *	DAVE_Init();
 *
 *  // Put the USB host "Wait for device" state
 *	USB_SetHostState(HOST_STATE_WaitForDevice);
 *
 *	//Initialize the USB core in Host mode
 *	USBVCH_Init();
 *
 *	while (1)
 *	{
 *
 *		// Enumerate the attached device and put it to the
 *		// "Configured Mode" status.
 *		USBVCH_Process();
 *
 *		// Get the host status
 *		USB_GetHostState(&USBHostState);
 *
 *		if(USBHostState == HOST_STATE_Configured)
 *		{
 *		}
 *		 // Calls USB Management function for setting
 *		 // control line states
 *		USBVCH_CDCHost_USBTask();
 *
 *		// Enumerate the attached device and put it to the
 *		// "Addressed Mode" status.
 *		USB_USBTask();
 *	}
 * }
 * @endcode
 */
//status_t USBVCH_Init(void);

/**
 * @brief The function de-initializes App.
 * @return status_t
 * DAVEApp_SUCCESS: If the de-initialization is successful\n
 * USBVCH_ERROR:  If de-initialization fails.
 */
//status_t USBVCH_DInit(void);

/**
 * @brief The function sends a byte of data to the USB VCOM Device.
 *        In order to call USBVCH_SendByte()  following procedure should
 *        be followed:\n
 *        1) Call DAVE_Init().\n
 *        2) Call USB_SetHostState(HOST_STATE_WaitForDevice) to put the USB
 *        host in "Wait for Device " status.\n
 *        3) Call USBVCH_Init() initialize the USB core in Host mode.\n
 *        4) Call USBVCH_Process() continuously  to put the attached device
 *        in "Configured Mode" status.\n
 *        5) Call USB_GetHostState(&USBHostState) Gets USB Host State.\n
 *        6) Call USBVCH_SendByte() in loop if Host state is Configured Sends
 *        a byte to USB VCOM Device.
 * @param[in] DataByte Data to send to the USB host.
 * @return status_t
 * DAVEApp_SUCCESS:  If the initialization is successful\n
 * @code
 * #include <XMC4500.h>
 * #include <DAVE3.h>
 * #include "Dave\Generated\inc\USBVCH\VirtualSerialHost.h"
 *
 * int main(void)
 * {
 *   uint16_t DataByte = 0;
 *   DAVE_Init();      // Initialization of DAVE Apps
 *
 *  // Put the USB host "Wait for device" state
 *	USB_SetHostState(HOST_STATE_WaitForDevice);
 *
 *  //Initialize the USB core in Device mode
 *  USBVCH_Init();
 *
 *	while (1)
 *	{
 *
 *		// Enumerate the attached device and put it to the
 *		// "Configured Mode" status.
 *		USBVCH_Process();
 *
 *		// Get the host status
 *		USB_GetHostState(&USBHostState);
 *
 *		if(USBHostState == HOST_STATE_Configured)
 *		{
 *			USBVCH_SendByte(DataByte);
 *		}
 *
 *		 // Calls USB Management function for setting
 *		 // control line states
 *		USBVCH_CDCHost_USBTask();
 *
 *		// Enumerate the attached device and put it to the
 *		// "Addressed Mode" status.
 *		USB_USBTask();
 *	}
 * }
 *  @endcode
 */
uint32_t USBVCH_SendByte(const uint8_t DataByte);

/**
 * @brief The function sends multiple bytes of data to the USB VCOM Device.
 *        In order to call USBVCH_SendData()  following procedure should
 *        be followed:\n
 *        1) Call DAVE_Init().\n
 *        2) Call USB_SetHostState(HOST_STATE_WaitForDevice) to put the USB
 *        host in "Wait for Device " status.\n
 *        3) Call USBVCH_Init() initialize the USB core in Host mode.\n
 *        4) Call USBVCH_Process() continuously  to put the attached device
 *        in "Configured Mode" status.\n
 *        5) Call USB_GetHostState(&USBHostState) Gets USB Host State.\n
 *        6) Call USBVCH_SendData() Sends data to device.\n
 *           This API transfers data as per the endpoint size of the
 *           attached device.\n Actual transferred data can be known from the
 *           parameter ActulaXferLengthPtr.\n User has to use this parameter
 *           to transfer the remaining data as shown in the below code snippet.\n
 *           In the loop back mode user has to call  USBVCH_ReceiveByte()
 *           API, after calling USBVCH_SendData().\n
 * @param[in] DataBuffer Contains the data to send.
 * @param[in] Length Number of bytes to send to the USB host.
 * @param[out] ActulaXferLengthPtr Pointer to the actual transferred data
 * @return status_t
 * DAVEApp_SUCCESS:  If the initialization is successful\n
 * @code
 * #include <XMC4500.h>
 * #include <DAVE3.h>
 * #include "Dave\Generated\inc\USBVCH\VirtualSerialHost.h"
 *
 * int main(void)
 * {
 *   int8_t ReceivedByte;
 *   uint16_t ActualXfer = 0;
 *   uint8_t TxBuffer[80] = {"Hello World1Hello World2Hello World3Hello World4Hello World5Hello World6"};
 *   uint8_t *TxPtr = TxBuffer;
 *   uint32_t Txlen = strlen(TxBuffer);
 *   DAVE_Init();      // Initialization of DAVE Apps
 *
 *  //Initialize the USB core in Device mode
 *  USBVCH_Init();
 *
 *  while (1)
 *  {
 *    // Enumerate the attached device and put it to the
 *    // "Configured Mode" status.
 *    USBVCH_Process();
 *
 *    // Get the host status
 *    USB_GetHostState(&USBHostState);
 *
 *    if(USBHostState == HOST_STATE_Configured)
 *    {
 *        //Send Data
 *      USBVCH_SendData(TxPtr , Txlen, &ActualXfer);
 *      Txlen -= ActualXfer;
 *      TxPtr += ActualXfer;
 *
 *      if(Txlen == 0)
 *      {
 *        Txlen = strlen(TxBuffer);
 *        TxPtr = TxBuffer;
 *      }
 *
 *      // In the Loop back mode user has to call USBVCH_ReceiveByte() after sending data.
 *      // Display received byte from the device on OLED
 *      ReceivedByte = -1;
 *      // Receive data
 *      USBVCH_ReceiveByte(&ReceivedByte);
 *
 *      if (!(ReceivedByte < 0))
 *      {
 *        while(!(ReceivedByte <= 0))
 *        {
 *          ReceivedByte = -1;
 *          USBVCH_ReceiveByte(&ReceivedByte);
 *        }
 *      }
 *    }
 *     // Calls USB Management function for setting
 *     // control line states
 *    USBVCH_CDCHost_USBTask();
 *
 *    // Enumerate the attached device and put it to the
 *    // "Addressed Mode" status.
 *    USB_USBTask();
 *  }
 * }
 *  @endcode
 */
 uint32_t USBVCH_SendData(const uint8_t* const DataBuffer,
        const uint16_t Length, uint16_t *ActulaXferLengthPtr);


/**
 * @brief The function receives a byte from the USB VCOM Device.
 *        In order to call USBVCH_ReceiveByte()  following procedure should
 *        be followed:\n
 *        1) Call DAVE_Init().\n
 *        2) Call USB_SetHostState(HOST_STATE_WaitForDevice) to put the USB
 *        host in "Wait for Device " status.\n
 *        3) Call USBVCH_Init() initialize the USB core in Host mode.\n
 *        4) Call USBVCH_Process() continuously  to put the attached device
 *        in "Configured Mode" status.\n
 *        5) Call USB_GetHostState(&USBHostState) Gets USB Host State.\n
 *        6) Call USBVCH_ReceiveByte() receives a byte from USB VCOM
 *        Device.
 * @param[in] DataByte Pointer to the buffer to store the received data.
 * @return status_t
 * DAVEApp_SUCCESS:  If the initialization is successful\n
 * @code
 * #include <XMC4500.h>
 * #include <DAVE3.h>
 * #include "Dave\Generated\inc\USBVCH\VirtualSerialHost.h"
 *
 * int main(void)
 * {
 *   int8_t RxBytes = 0;
 *   DAVE_Init();      // Initialization of DAVE Apps
 *
 *  //Initialize the USB core in Device mode
 *  USBVCH_Init();
 *
 *	while (1)
 *	{
 *
 *		// Enumerate the attached device and put it to the
 *		// "Configured Mode" status.
 *		USBVCH_Process();
 *
 *		// Get the host status
 *		USB_GetHostState(&USBHostState); *
 *
 *		if(USBHostState == HOST_STATE_Configured)
 *		{
 *	    	//Receive byte
 *  	  	USBVCH_ReceiveByte(&RxBytes);
 *		}
 *
 *		 // Calls USB Management function for setting
 *		 // control line states
 *		USBVCH_CDCHost_USBTask();
 *
 *		// Enumerate the attached device and put it to the
 *		// "Addressed Mode" status.
 *		USB_USBTask();
 *	}
 * }
 *  @endcode
 */
uint32_t USBVCH_ReceiveByte(int8_t* DataByte);

 /**
  * @brief The function calls low level function to change control line state
  * and synchronize.Call USBVCH_CDCHost_USBTask() before USB_USBTask()
  * function in application code.
  *
  * @return void
  * @code
  * #include <XMC4500.h>
  * #include <DAVE3.h>
  * #include "Dave\Generated\inc\USBVCH\VirtualSerialHost.h"
  *
  * int main(void)
  * {
  *   int8_t RxBytes = 0;
  *   DAVE_Init();      // Initialization of DAVE Apps
  *
  *
  *  //Initialize the USB core in Device mode
  *  USBVCH_Init();
  *
  *	while (1)
  *	{
  *
  *		// Enumerate the attached device and put it to the
  *		// "Configured Mode" status.
  *		USBVCH_Process();
  *
  *		// Get the host status
  *		USB_GetHostState(&USBHostState);
  *
  *		if(USBHostState == HOST_STATE_Configured)
  *		{
  *	    	//Receive byte
  *  	  	USBVCH_ReceiveByte(&RxBytes);
  *		}
  *		 // Calls USB Management function for setting
  *		 // control line states.
  *		USBVCH_CDCHost_USBTask();
  *
  *
  *		// Enumerate the attached device and put it to the
  *		// "Addressed Mode" status.
  *		USB_USBTask();
  *	}
  * }
  *  @endcode
  */
void USBVCH_CDCHost_USBTask(void);

/**
 * @brief Event handler for the USB_DeviceAttached event. This indicates that a
 * device has been attached to the host, and starts the library USB task to
 * begin the enumeration and USB management process.
 */
//void  EVENT_USB_Host_DeviceAttached(void);

/**
 * @brief Event handler for the USB_DeviceEnumerationComplete event. This
 * indicates that a device has been successfully enumerated by the host and is
 * now ready to be used by the application.
 */
void EVENT_USB_Host_DeviceEnumerationComplete(void);

/**
 * @brief Event handler for the USB_DeviceEnumerationFailed event. This
 * indicates that a problem occurred while  enumerating an attached USB device.
 * @param[in]  ErrorCode  Error code indicating the failure reason, a value in
 * USB_Host_EnumerationErrorCodes_t enum.
 * @param[in]  SubErrorCode Sub error code indicating the reason for failure
 * @return void
 */
void  EVENT_USB_Host_DeviceEnumerationFailed(const uint8_t ErrorCode,     \
                                             const uint8_t SubErrorCode);
/**
 * @brief Event handler for the USB_DeviceUnattached event. This indicates
 * that a device has been removed from the host, and  stops the library USB
 * task management process.
 */
//void  EVENT_USB_Host_DeviceUnattached(void);

/**
 * @brief Event handler for the USB_HostError event. This indicates that a
 * hardware error occurred while in host mode.
 * @param[in]  ErrorCode  Error code indicating the failure reason, a value in
 * USB_Host_ErrorCodes_t enum.
 * @return void
 */
//void EVENT_USB_Host_HostError(const uint8_t ErrorCode);
/*
 * Function to handle received data
 * */
void USBH_VCOM_Rx_Data_Handler(XMC_USBH_PIPE_HANDLE pipe_handl, uint32_t event);
uint16_t USBVCH_Pipe_BytesInPipe(XMC_USBH_PIPE_HANDLE ptr_pipe);
uint8_t USBVCH_Pipe_Read_8(XMC_USBH_PIPE_HANDLE ptr_pipe);
bool USBVCH_Pipe_IsINReceived(XMC_USBH_PIPE_HANDLE ptr_pipe);

#define USBH_VCOM_RXBUF_SIZE  2048U
extern uint8_t USBH_VCOM_RX_Buffer[USBH_VCOM_RXBUF_SIZE];
extern uint32_t USBH_VCOM_RX_cur_index;
extern uint32_t USBH_VCOM_RX_prev_index;
extern XMC_USBH_PIPE_HANDLE CDC_BULK_OUT_pipe_handle, CDC_BULK_IN_pipe_handle, CDC_INTERRUPT_pipe_handle;
extern uint8_t USBH_VCOM_Packet_Buffer[64];
/**
 * @}
 */
#ifdef __cplusplus
}
#endif
#endif	/*_USBVCH_H_*/
