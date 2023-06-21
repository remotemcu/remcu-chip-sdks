/**
 * \file
 *
 * \brief USB Device Atmel Firmware Upgrade (Atmel DFU) interface definitions.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef _UDI_DFU_ATMEL_H_
#define _UDI_DFU_ATMEL_H_

#include "conf_usb.h"
#include "usb_protocol.h"
#include "usb_protocol_dfu.h"
#include "udd.h"
#include "udc_desc.h"
#include "udi.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup udi_dfu_atmel_group_udc
 * @{
 */
//! Global structure which contains standard UDI API for UDC
extern UDC_DESC_STORAGE udi_api_t udi_api_dfu_atmel;
//@}

/**
 * \ingroup udi_dfu_atmel_group
 * \defgroup udi_dfu_atmel_group_desc USB interface descriptors
 *
 * The following structures provide predefined USB interface descriptors.
 * It must be used to define the final USB descriptors.
 */
//@{

//! Interface descriptor structure for Atmel DFU
typedef struct {
	usb_iface_desc_t iface;
} udi_dfu_atmel_desc_t;

//! By default no string associated to this interface
#ifndef UDI_DFU_ATMEL_STRING_ID
#define UDI_DFU_ATMEL_STRING_ID     0
#endif

//! Content of DFU interface descriptor for Full Speed
#define UDI_DFU_ATMEL_DESC      {\
	.iface.bLength             = sizeof(usb_iface_desc_t),\
	.iface.bDescriptorType     = USB_DT_INTERFACE,\
	.iface.bInterfaceNumber    = UDI_DFU_ATMEL_IFACE_NUMBER,\
	.iface.bAlternateSetting   = 0,\
	.iface.bNumEndpoints       = 0,\
	.iface.bInterfaceClass     = CLASS_VENDOR_SPECIFIC,\
	.iface.bInterfaceSubClass  = 0,\
	.iface.bInterfaceProtocol  = 0,\
	.iface.iInterface          = UDI_DFU_ATMEL_STRING_ID,\
	}
//@}


/**
 * \ingroup udi_group
 * \defgroup udi_dfu_atmel_group USB Device Interface (UDI) for Device Firmware Upgrade Atmel specific
 *
 * The DFU from Atmel is based on DFU specification,
 * but does not implement same protocol.
 *
 * The USB Device Atmel DFU class implement both version:
 * - The <A href="http://ww1.microchip.com/downloads/en/DeviceDoc/doc7618.pdf">
 * doc7618: USB DFU Bootloader Datasheet</A> describes the
 * FLIP USB DFU Protocol version 1 used by Mega devices.
 * - The <A href="http://ww1.microchip.com/downloads/en/AppNotes/doc32131.pdf">
 * AVR32760: AVR32 UC3 USB DFU Bootloader Protocol</A>  and the
 * <A href="http://ww1.microchip.com/downloads/en/AppNotes/doc8457.pdf">
 * AVR4023: FLIP USB DFU Protocol</A> describes the
 * FLIP USB DFU Protocol version 2 used by UC3 and Xmega devices.
 *
 * The interface between the DFU Atmel Class and device is done through the 
 * \ref isp service.
 * @{
 */
//@}

#ifdef __cplusplus
}
#endif
#endif // _UDI_DFU_ATMEL_H_
