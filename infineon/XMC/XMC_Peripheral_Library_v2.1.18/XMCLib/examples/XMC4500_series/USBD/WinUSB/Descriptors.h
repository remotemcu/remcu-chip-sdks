/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
                                                                              **
*******************************************************************************/

/**
 * @file  descriptors.h
 *
 * @brief This file contains the WinUSB device frame work descriptors.
 *
 */


#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_


/******************************************************************************
* INCLUDE FILES
******************************************************************************/
#include <USB/USB.h>
/*******************************************************************************
*                                CONSTANTS                                **
******************************************************************************/

/**
 * @ingroup USBD_WINUSB_constans
 * @{
 */
/** Endpoint number of the WinUSB device-to-host data IN endpoint. */
#define WINUSB_TX_EPNUM                   1

/** Endpoint number of the WinUSB host-to-device data OUT endpoint. */
#define WINUSB_RX_EPNUM                   2

/** Size in bytes of the WinUSB data IN and OUT endpoints. */
#define WINUSB_TXRX_EPSIZE                64

/*Microsoft OS get descriptor -code*/
#define MS_GET_DESCRIPTOR 0x01

/**
 * @}
 */

/**
 * @ingroup USBD_WINUSB_enumerations
 * @{
 */

/**
 * \brief  Microsoft OS descriptor index */
enum MS_Descriptor_Index_t {
	Genre = 0x0001,
	Extended_Compat_ID = 0x0004,/**<Compatible ID descriptor index*/
	Extended_Properties = 0x0005/**<OS properties descriptor index*/
};

/**
 * @}
 */


/**
 * @ingroup USBD_WINUSB_datastructures
 * @{
 */
/**
\brief  USB configuration descriptor
*/
typedef struct
{
	USB_Descriptor_Configuration_Header_t    Config;
										/**<Configuration descriptor header*/
	USB_Descriptor_Interface_t               WinUSB_Interface;
										/**<WinUSB interface data structure*/
	USB_Descriptor_Endpoint_t                WinUSB_DataInEndpoint;
										/**<WinUSB IN endpoint data structure*/
	USB_Descriptor_Endpoint_t                WinUSB_DataOutEndpoint;
										/**<WinUSB OUT endpoint data structure*/
} USB_Descriptor_Configuration_t;
/**
 * @}
 */

/**
 * @ingroup USBD_WINUSB_datastructures
 * @{
 */
/**
\brief  Microsoft string descriptor
*/
typedef struct {
	uint8_t bLength;/**< MS string descriptor length*/
	uint8_t bDescriptorType;/**<Descriptor type-string*/
	uint8_t qwSignature[14];/**<Signature-MSFT100*/
	uint8_t bMS_VendorCode;/**<Vendor code to retrieve OS feature descriptor*/
	uint8_t bPad;/**<pad byte*/
} MS_String_Descriptor_t;
/**
 * @}
 */


/**
 * @ingroup USBD_WINUSB_datastructures
 * @{
 */
/**
\brief  Microsoft OS descriptor function
*/
typedef struct {
	uint8_t bFirstInterfaceNumber;/**<First interface number*/
	uint8_t RESERVED0;/**<Reserved byte*/
	uint8_t compatibleID[8];/**<Compatible ID-WINUSB*/
	uint8_t subCompatibleID[8];/**<Sub compatible ID*/
	uint8_t RESERVED1[6];/**<Reserved 6 bytes*/
}MS_OS_Descriptor_Function_t;
/**
 * @}
 */


/**
 * @ingroup USBD_WINUSB_datastructures
 * @{
 */
/**
\brief  Microsoft OS descriptor header
*/
typedef struct {
	uint32_t dwLength;/**<size of extended compatible ID descriptor*/
	uint16_t bcdVersion;/**< BCD version-1.00*/
	uint16_t wIndex;/**<Index of OS feature descriptor*/
	uint8_t bCount;/**< Number of functions*/
} MS_OS_Descriptor_Header_t;
/**
 * @}
 */

/**
 * @ingroup USBD_WINUSB_datastructures
 * @{
 */
/**
\brief  Microsoft OS extended properties descriptor
*/
typedef struct {
	uint32_t dwLength;/**<Size of extended properties descriptor*/
	uint16_t bcdVersion;/**<BCD version-1.00*/
	uint16_t wIndex;/**<Index of the extended properties descriptor*/
	uint16_t wCount;/**< Number of functions*/
	uint8_t Properties[0x84];/**<Properties data*/
} MS_Extended_Properties_Descriptor_t;
/**
 * @}
 */


/**
 * @ingroup USBD_WINUSB_datastructures
 * @{
 */
/**
\brief  Microsoft OS extended compatible ID descriptor
*/
typedef struct {
	uint32_t dwLength;/**<Size of extended compatible id descriptor*/
	uint16_t bcdVersion;/**<BCD version-1.00*/
	uint16_t wIndex;/**<string descriptor index of compatible id descriptor*/
	uint8_t bCount;/**< Number of functions*/
	uint8_t RESERVED[7];/**< reserved 7 bytes*/
	MS_OS_Descriptor_Function_t Functions[1];/**<MS OS descriptor functions*/
} MS_Extended_Compat_ID_Descriptor_t;
/**
 * @}
 */

extern const MS_Extended_Properties_Descriptor_t Properties;
extern const MS_Extended_Compat_ID_Descriptor_t Compat_ID;

#endif

