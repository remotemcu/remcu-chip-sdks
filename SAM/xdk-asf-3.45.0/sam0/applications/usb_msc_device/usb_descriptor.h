/**
 * \file
 *
 * \brief SAM USB MSC descriptor 
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef USB_DESCRIPTOR_H_
#define USB_DESCRIPTOR_H_

/* USB Device Descriptor */
COMPILER_WORD_ALIGNED
uint8_t devDescriptor[] = {
	/* Device descriptor */
	0x12,   // bLength
	0x01,   // bDescriptorType
	0x00,   // bcdUSBL
	0x02,   //
	0x00,   // bDeviceClass:
	0x00,   // bDeviceSubclass:
	0x00,   // bDeviceProtocol:
	0x40,   // bMaxPacketSize0
	0xEB,   // idVendorL
	0x03,   //
	0x03,   // idProductL // USB_PID_ATMEL_MSC
	0x24,   //
	0x00,   // bcdDeviceL
	0x01,   //
	0x00,   // iManufacturer    
	0x02,   // iProduct
	0x03,   // SerialNumber
	0x01    // bNumConfigs
};
/* USB Configuration Descriptor */
COMPILER_WORD_ALIGNED
uint8_t cfgDescriptor[] = {
	/* ============== CONFIGURATION 1 =========== */
	/* Configuration 1 descriptor */
	0x09,   // CbLength
	0x02,   // CbDescriptorType
	0x20,   //
	0x00,
	0x01,   // CbNumInterfaces
	0x01,   // CbConfigurationValue
	0x00,   // CiConfiguration
	0xC0,   // CbmAttributes self powered
	0x32,   // CMaxPower

	/* MSC Class Interface Descriptor Requirement */
	0x09, // bLength
	0x04, // bDescriptorType
	0x00, // bInterfaceNumber
	0x00, // bAlternateSetting
	TOTAL_EP-1, // bNumEndpoints number of endpoints for MSC is 2
	0x08, // bInterfaceClass: Mass storage
	0x06, // bInterfaceSubclass
	0x50, // bInterfaceProtocol :bulk only
	0x00, // iInterface

	/* USB MSC BULK IN Endpoint Descriptor */
	0x07, // in.bLength
	0x05, // in.bDescriptor type:
	MSC_BULK_IN_EP | 0x80, // in.bEndpointAddress
	0x02, // in.bmAttributes : Bulk
	MSC_BULK_IN_EP_SIZE, // in.wMaxPacketSize for full speed	// 64 bytes
	0x00,
	0x00, // in.bInterval  doesn't apply to bulk endpoints
	
	/* USB MSC BULK OUT Endpoint Descriptor */	
	0x07, // out.bLength
	0x05, // out.bRDescriptor type
	MSC_BULK_OUT_EP, // out.bEndpointAddress
	0x02, // out.bmAttributes : Type: bulk
	MSC_BULK_OUT_EP_SIZE, // out.wMaxPacketSize for full speed  // 64 bytes
	0x00,
	0x00, // out.bInterval doesn't apply to bulk endpoints
};

/* USB String Descriptor */
COMPILER_WORD_ALIGNED
uint8_t string_descriptor_lang_id[] = {
	/*Language ID*/
	0x04,	// length of the string descriptor
	0x03,	// descriptor type
	0x09,	// Language id code for U.S.English is 0x0409
	0x04,	// Language id
};

/* USB String Descriptor */
COMPILER_WORD_ALIGNED
uint8_t string_descriptor_manufacture[] = {
	
	/*Manufacturer string*/
	0x08,	// length of the string descriptor 
	0x03,	// descriptor type 
	0x4D,	// 0x4D - M (Ascii value)
	0x00,	// NULL
	0x53,	// 0x53 - S
	0x00,	// NULL
	0x43,	// 0x43 - C
	0x00,	// NULL
};

/*The USB serial number is mandatory when a MSC interface is used.*/

/*Serial number descriptor*/
COMPILER_WORD_ALIGNED
uint8_t string_descriptor_serial_number[] = {
	0x1A,	// length of the string descriptor 0x1A = 26
	0x03,	// descriptor type = 0x03 indicates string descriptor
	0x31,	// 0x31 - 1
	0x00,	// NULL
	0x32,	// 0x32 - 2
	0x00,	// NULL
	0x33,	// 0x33	- 3
	0x00,	// NULL
	0x31,	// 0x31 - 1
	0x00,	// NULL
	0x32,	// 0x32 - 2
	0x00,	// NULL
	0x33,	// 0x33 - 3
	0x00,	// NULL
	0x31,	// 0x31 - 1
	0x00,	// NULL
	0x32,	// 0x32 - 2
	0x00,	// NULL
	0x33,	// 0x33 - 3 
	0x00,	// NULL
	0x31,	// 0x31 - 1
	0x00,	// NULL
	0x32,	// 0x32 - 2
	0x00,	// NULL
	0x33,	// 0x33 - 3
	0x00,	// NULL
};

COMPILER_WORD_ALIGNED
uint8_t getmaxlun[] = {
	0x00,	 // 0 (since one LUN (SD card) is connected )
};

COMPILER_WORD_ALIGNED
uint8_t msc_inquiry_data[] = {	
	0x00,	//Peripheral Device Type
	0x80,	//Medium is Removable
	0x03,
	0x02,
	0x1F,	// additional length
	0x00,
	0x00,
	0x00,
	0x41,	// Vendor id ascii value is mentioned 0x41 - 'A'
	0x54,	//'T'
	0x4D,	//'M'
	0x45,	//'E'
	0x4C,	//'L'
	0x20,	//'space'
	0x20,	//'space'
	0x20,	//'space'
	0x53,	//'S'
	0x44,	//'D'
	0x20,	//'space'
	0x43,	//'C'
	0x41,	//'A'
	0x52,	//'R'
	0x44,	//'D'
	0x20,	//'space'
	0x20,	//'space'
	0x20,	//'space'
	0x20,	//'space'
	0x20,	//'space'
	0x20,	//'space'
	0x20,	//'space'
	0x20,	//'space'
	0x20,	//'space'
	0x31,	// version '1'
	0x2E,	//'.'
	0x30,	//'0'
	0x30,	//'0'
	
};

/*request sense for illegal request*/
/*Additional Sense length =0x0A */
/*Additional Sense Code   = 0x24 (for illegal request)*/
/*Additional Sense Code Qualifier = 0x00 */

uint8_t request_sense[]={
	0xF0,   //11110000 -> 1 -Valid bit, 111 indicates this field shall contain a value of 70h to indicate current errors.
	0x00,	//refer usb_developer_scsi commands pdf
	0x05,	//sense key (05 - sense key, 24- additional sense data, 00, additional sense qualifier. invalid field in command packet)
	0x00,	//reserved
	0x00,	//reserved
	0x00,	//reserved
	0x00,	//reserved
	0x0A,	//additional sense length 10
	0x00,	//reserved
	0x00,	//reserved
	0x00,	//reserved
	0x00,	//reserved
	0x24,	// Additional Sense Code (ASC)
	0x00,	// Additional Sense Code Qualifier (ASCQ)
	0x00,	//reserved
	0x00,	//reserved
	0x00,	//reserved
	0x00,	//reserved
};

/*request sense for Medium not present*/
/*Additional Sense Length = 0x0A */
/*Additional Sense Code  = 0x3A (Medium not present)*/
/*Additional Sense Code Qualifier = 0x00 */

uint8_t request_sense_medium_not_present[]={
	0xF0,   //11110000 -> 1 -Valid bit, 111 indicates this field shall contain a value of 70h to indicate current errors.
	0x00,	//refer usb_developer_scsi commands pdf
	0x02,	//sense key (02 - sense key, 3A- additional sense data, 00, additional sense qualifier. invalid field in command packet)
	0x00,	//reserved
	0x00,	//reserved
	0x00,	//reserved
	0x00,	//reserved
	0x0A,	//additional sense length 10
	0x00,	//reserved
	0x00,	//reserved
	0x00,	//reserved
	0x00,	//reserved
	0x3A,	// Additional Sense Code (ASC) for Medium not present
	0x00,	// Additional Sense Code Qualifier (ASCQ)
	0x00,	//reserved
	0x00,	//reserved
	0x00,	//reserved
	0x00,	//reserved
};


#endif /* USB_DESCRIPTOR_H_ */