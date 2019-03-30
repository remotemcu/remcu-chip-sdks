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

/** \file
 *
 *  Header file for WinUSB.c.
 */


#ifndef _USBD_WINUSB_H_
#define _USBD_WINUSB_H_

/******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
	/* Includes: */
  #include <USB/USB.h>
  #include "Descriptors.h"
  #include "xmc_gpio.h"
  #include "xmc_vadc.h"
  #include "xmc_i2c.h"
/*******************************************************************************
 *                                CONSTANTS                                   **
******************************************************************************/

/*USBD_WINUSB RX buffer size*/
#define RX_BUF_SIZE 384

/*USBD_WINUSB TX buffer size*/
#define TX_BUF_SIZE 384


/*******************************************************************************
 *                                DATA STRUCTURES                             **
******************************************************************************/
/* WinUSB Interface Information */
typedef struct {
	struct {
		USB_Endpoint_Table_t InEndpoint; /**< IN Endpoint Configuration */
		USB_Endpoint_Table_t OutEndpoint; /**< OUT Endpoint Configuration */
	} Config;
} USBD_WINUSB_Info_t;




/*
 *WinUSB error codes
 */
typedef enum {
	USBD_WINUSB_STATUS_SUCCESS, /**< Operation was successful */
	USBD_WINUSB_STATUS_FAILURE, /**< Operation has raised an error */
	USBD_WINUSB_STATUS_NOT_READY /**< Device/Endpoint is not ready for operation */
} USBD_WINUSB_Status_t;





extern USBD_WINUSB_Info_t WinUSBInfo;


/*******************************************************************************
** FUNCTION PROTOTYPES                                                        **
*******************************************************************************/
/* The function initializes the USB core layer and register call backs. */
void USB_Init(void);


/* Send \a Length number of bytes of data to the USB host on selected end-point */
USBD_WINUSB_Status_t USBD_WINUSB_WriteData(uint8_t ep,
		const void *Buffer,uint16_t Length);

/* Reads \a Length number of bytes of data from the USB host through endpoint  */
USBD_WINUSB_Status_t USBD_WINUSB_ReadData(uint8_t ep,void *Buffer,
		uint16_t Length);

/* Checks the number of bytes received from host and returns the same. */
uint16_t USBD_WINUSB_BytesReceived(uint8_t ep);


/* Configures the IN and OUT end-points of WinUSB device based on ::USBD_WINUSB_Info_t Information. */
void USBD_WINUSB_ConfigureEndpoints(USBD_WINUSB_Info_t* const WinUSBInfo);

/*
* USB configuration changed event handler
*/
void USBD_WINUSB_Event_ConfigurationChanged(void);

/*
* USB control request event handler
*/
void USBD_WINUSB_Event_ControlRequest(void);

/*
* USB Get descriptor event handler
*/
uint16_t USBD_WINUSB_Event_GetDescriptor(const uint16_t wValue,
									const uint16_t wIndex,
									const void** const DescriptorAddress);

#endif


