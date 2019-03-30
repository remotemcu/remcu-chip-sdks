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
 *  USB Device Descriptors, for library use when in USB device mode. Descriptors are special
 *  computer-readable structures which the host requests upon device enumeration, to determine
 *  the device's capabilities and functions.
 */

#include "Descriptors.h"


/** Device descriptor structure. This descriptor, located in FLASH memory,
 * describes the overall device characteristics, including the supported USB
 * version, control end point size and the number of device configurations.
 * The descriptor is read out by the USB host when the enumeration process
 * begins.
 */
const USB_Descriptor_Device_t DeviceDescriptor =
{
	.Header                 = {.Size = sizeof(USB_Descriptor_Device_t),
											.Type = DTYPE_Device},

	.USBSpecification       = 0x0200,
	.Class                  = USB_CSCP_NoDeviceClass,
	.SubClass               = USB_CSCP_NoDeviceSubclass,
	.Protocol               = USB_CSCP_NoDeviceProtocol,

	.Endpoint0Size          = 64,

	.VendorID               = 0x058b,
	.ProductID              = 0x0050,
	.ReleaseNumber          = 0x0001,

	.ManufacturerStrIndex   = 0x01,
	.ProductStrIndex        = 0x02,
	.SerialNumStrIndex      = NO_DESCRIPTOR,

	.NumberOfConfigurations = 1
};

/** Configuration descriptor structure. This descriptor, located in FLASH
 * memory, describes the usage of the device in one of its supported
 * configurations, including information about any device interfaces and
 * end points. The descriptor is read out by the USB host during the enumeration
 * process when selecting a configuration so that the host may correctly
 * communicate with the USB device.
 */
const USB_Descriptor_Configuration_t ConfigurationDescriptor =
{
	.Config =
		{
			.Header                 =
					{.Size = sizeof(USB_Descriptor_Configuration_Header_t),
							.Type = DTYPE_Configuration},

			.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
			.TotalInterfaces        = 1,

			.ConfigurationNumber    = 1,
			.ConfigurationStrIndex  = NO_DESCRIPTOR,

			.ConfigAttributes       = (USB_CONFIG_ATTR_RESERVED),

			.MaxPowerConsumption    = USB_CONFIG_POWER_MA(100)
		},

	.WinUSB_Interface =
		{
			.Header                 =
					{.Size = sizeof(USB_Descriptor_Interface_t),
							.Type = DTYPE_Interface},

			.InterfaceNumber        = 0,
			.AlternateSetting       = 0,

			.TotalEndpoints         = 2,

			.Class                  = USB_CSCP_VendorSpecificClass,
			.SubClass               = USB_CSCP_NoDeviceSubclass,
			.Protocol               = USB_CSCP_NoDeviceProtocol,

			.InterfaceStrIndex      = NO_DESCRIPTOR
		},
	.WinUSB_DataOutEndpoint =
		{
			.Header                 =
						{.Size = sizeof(USB_Descriptor_Endpoint_t),
								.Type = DTYPE_Endpoint},

			.EndpointAddress        = (ENDPOINT_DIR_OUT | WINUSB_RX_EPNUM),
			.Attributes             = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC |
														ENDPOINT_USAGE_DATA),
			.EndpointSize           = WINUSB_TXRX_EPSIZE,
			.PollingIntervalMS      = 0x00
		},

	.WinUSB_DataInEndpoint =
		{
			.Header                 =
						{.Size = sizeof(USB_Descriptor_Endpoint_t),
								.Type = DTYPE_Endpoint},

			.EndpointAddress        = (ENDPOINT_DIR_IN | WINUSB_TX_EPNUM),
			.Attributes             = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC |
														ENDPOINT_USAGE_DATA),
			.EndpointSize           = WINUSB_TXRX_EPSIZE,
			.PollingIntervalMS      = 0x00
		}
};

/** Language descriptor structure. This descriptor, located in FLASH memory,
 * is returned when the host requests the string descriptor with index
 * 0 (the first index). It is actually an array of 16-bit integers, which
 * indicate via the language ID table available at USB.org what languages the
 * device supports for its string descriptors.
 */
const USB_Descriptor_String_t LanguageString =
{
	.Header                 = {.Size = USB_STRING_LEN(1), .Type = DTYPE_String},

	.UnicodeString          = {LANGUAGE_ID_ENG}
};

/** Manufacturer descriptor string. This is a Unicode string containing the
 * manufacturer's details in human readable form, and is read out upon request
 * by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t ManufacturerString =
{
	.Header                 = {.Size = USB_STRING_LEN(21),
										.Type = DTYPE_String},

	.UnicodeString          = { 'I','n','f','i','n','e','o','n',' ','T','e',
								'c','h','n','o','l','o','g','i','e','s'}
};

/** Product descriptor string. This is a Unicode string containing the product's
 *  details in human readable form, and is read out upon request by the host
 *  when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t ProductString =
{
	.Header                 = {.Size = USB_STRING_LEN(22),
										.Type = DTYPE_String},

	.UnicodeString          = {'I','n','f','i','n','e','o','n',' ','W','i','n',
								'U','S','B',' ','D','e','v','i','c','e'}
};

const MS_String_Descriptor_t MS_String = {
		.bLength = 0x12,
		.bDescriptorType = DTYPE_String,
		.qwSignature = {
				0x4D ,0x00, 0x53, 0x00, 0x46, 0x00, 0x54, 0x00, 0x31, 0x00,
				0x30, 0x00, 0x30, 0x00
		},/*MSFT100*/
		.bMS_VendorCode = 0x1,
		.bPad = 0x1
};

const MS_Extended_Compat_ID_Descriptor_t Compat_ID = {
		.dwLength = 0x0028,
		.bcdVersion = 0x0100,
		.wIndex = Extended_Compat_ID,
		.bCount = 0x1,
		.Functions = {
				{
						.bFirstInterfaceNumber = 0x0,
						.RESERVED0 = 0x1,
						.compatibleID = { 0x57, 0x49, 0x4E, 0x55, 0x53, 0x42,
								0x00, 0x00 },/*WINUSB*/
				}
		}
};

const MS_Extended_Properties_Descriptor_t Properties = {
		.dwLength = 0x8E,
		.bcdVersion = 0x0100,
		.wIndex = Extended_Properties,
		.wCount = 0x1,
		.Properties = {
				132,0x0,0x0,0x0, /* over all length */
				0x1,0x0,0x0,0x0, /* data type: unicode null-terminated string */
				40, 0x0, /* name length */
				'D',0x0,'e',0x0,'v',0x0,'i',0x0,'c',0x0,'e',0x0,'I',0x0,'n',0x0,
				't',0x0,'e',0x0,'r',0x0,'f',0x0,'a',0x0,'c',0x0,'e',0x0,'G',0x0,
				'U',0x0,'I',0x0,'D',0x0,0x0,0x0,
				78,0x0,0x0,0x0, /* data length */
				'{',0x0,'4',0x0,'0',0x0,'E',0x0,'E',0x0,'A',0x0,'1',0x0,'E',0x0,
				'B',0x0,'-',0x0,
				'E',0x0,'F',0x0,'6',0x0,'7',0x0,'-',0x0,
				'4',0x0,'D',0x0,'6',0x0,'A',0x0,'-',0x0,
				'A',0x0,'B',0x0,'0',0x0,'B',0x0,'-',0x0,
				'8',0x0,'B',0x0,'B',0x0,'5',0x0,'8',0x0,'8',0x0,'5',0x0,'9',0x0,
				'8',0x0,'7',0x0,'0',0x0,'4',0x0,'}',0x0,0x0,0x0
		}
};


/** This function is called by the library when in device mode, and must be
 * overridden (see library "USB Descriptors" documentation) by the application
 * code so that the address and size of a requested descriptor can be given
 *  to the USB library. When the device receives a Get Descriptor request on
 *  the control end point, this function is called so that the descriptor
 *  details can be passed back and the appropriate descriptor sent back to the
 *  USB host.
 */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint8_t wIndex,
                                    const void** const DescriptorAddress)
{
	const uint8_t  DescriptorType   = (wValue >> 8);
	const uint8_t  DescriptorNumber = (wValue & 0xFF);

	const void* Address = NULL;
	uint16_t    Size    = NO_DESCRIPTOR;

	switch (DescriptorType)
	{
		case DTYPE_Device:
			Address = &DeviceDescriptor;
			Size    = sizeof(USB_Descriptor_Device_t);
			break;
		case DTYPE_Configuration:
			Address = &ConfigurationDescriptor;
			Size    = sizeof(USB_Descriptor_Configuration_t);
			break;
		case DTYPE_String:
			switch (DescriptorNumber)
			{
				case 0x00:
					Address = &LanguageString;
					Size    = LanguageString.Header.Size;
					break;
				case 0x01:
					Address = &ManufacturerString;
					Size    = ManufacturerString.Header.Size;
					break;
				case 0x02:
					Address = &ProductString;
					Size    = ProductString.Header.Size;
					break;
				case 0xEE:
					Address = &MS_String;
					Size    = MS_String.bLength;
					break;
			}
			break;
	}

	(void)wIndex;
	*DescriptorAddress = Address;
	return Size;
}

