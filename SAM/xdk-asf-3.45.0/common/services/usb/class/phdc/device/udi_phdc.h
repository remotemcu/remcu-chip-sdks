/**
 * \file
 *
 * \brief USB Device Personal Healthcare Device Class (PHDC)
 * interface definitions.
 *
 * Copyright (c) 2009-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _UDI_PHDC_H_
#define _UDI_PHDC_H_

#include "conf_usb.h"
#include "usb_protocol.h"
#include "usb_protocol_phdc.h"
#include "udd.h"
#include "udc_desc.h"
#include "udi.h"

/* Check if preample feature is supported (don't change it) */
#define UDI_PHDC_PREAMBLE_FEATURE false /* No preample message by default */
#if (0 != (UDI_PHDC_QOS_OUT & (UDI_PHDC_QOS_OUT - 1)))
/* There are many QOS for OUT then enable preample feature */
#undef  UDI_PHDC_PREAMBLE_FEATURE
#define UDI_PHDC_PREAMBLE_FEATURE true
#endif
#if (0 != (UDI_PHDC_QOS_IN & (UDI_PHDC_QOS_IN - 1)))
/* There are many QOS for IN then enable preample feature */
#undef  UDI_PHDC_PREAMBLE_FEATURE
#define UDI_PHDC_PREAMBLE_FEATURE true
#endif
/* Check QOS value */
#if (0 != (UDI_PHDC_QOS_OUT & USB_PHDC_QOS_LOW_GOOD))
#error The QOS Low Good is not authorized on OUT transfer
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup udi_phdc_group_udc
 * @{
 */
/* ! Global structure which contains standard UDI API for UDC */
extern UDC_DESC_STORAGE udi_api_t udi_api_phdc;
/* @} */

/**
 * \ingroup udi_phdc_group
 * \defgroup udi_phdc_group_desc USB interface descriptors
 *
 * The following structures provide predefined USB interface descriptors.
 * It must be used to define the final USB descriptors.
 * @{
 */

COMPILER_PACK_SET(1)

/*! Array used only to compute the size of wDevSpecializations through sizeof()
 * during compilation. This array is not used and is removed by compiler.
 */
static le16_t tmp_wDevSpecializations[] = UDI_PHDC_SPECIALIZATION;
/* ! Function specialization descriptor for interface descriptors */
typedef struct {
	usb_phdc_fnctext_desc_t header;
	le16_t wDevSpecializations[sizeof(tmp_wDevSpecializations) / 2];
} udi_phdc_fnctext_desc_t;

#ifdef UDI_PHDC_METADATA_DESC_BULK_IN
/*! Array used only to compute the size of wDevSpecializations through sizeof()
 * during compilation. This array is not used and is removed by compiler.
 */
static uint8_t tmp_bulk_in[] = UDI_PHDC_METADATA_DESC_BULK_IN;
/* ! Metadata descriptor of bulk IN for interface descriptors */
typedef struct {
	usb_phdc_meta_data_desc_t header;
	uint8_t bOpaqueData[sizeof(tmp_bulk_in)];
} udi_phdc_metadata_desc_bulkin_t;
#endif

#ifdef UDI_PHDC_METADATA_DESC_BULK_OUT
/*! Array used only to compute the size of wDevSpecializations through sizeof()
 * during compilation. This array is not used and is removed by compiler.
 */
static uint8_t tmp_bulk_out[] = UDI_PHDC_METADATA_DESC_BULK_OUT;
/* ! Metadata descriptor of bulk OUT for interface descriptors */
typedef struct {
	usb_phdc_meta_data_desc_t header;
	uint8_t bOpaqueData[sizeof(tmp_bulk_out)];
} udi_phdc_metadata_desc_bulkout_t;
#endif

#ifdef UDI_PHDC_METADATA_DESC_INT_IN
/*! Array used only to compute the size of wDevSpecializations through sizeof()
 * during compilation. This array is not used and is removed by compiler.
 */
static uint8_t tmp_int_in[] = UDI_PHDC_METADATA_DESC_INT_IN;
/* ! Metadata descriptor of interrupt IN for interface descriptors */
typedef struct {
	usb_phdc_meta_data_desc_t header;
	uint8_t bOpaqueData[sizeof(tmp_int_in)];
} udi_phdc_metadata_desc_intin_t;
#endif

/* ! Interface descriptor structure for PHDC */
typedef struct {
	usb_iface_desc_t iface;
	usb_phdc_classfnct_desc_t classfnct;
#if (UDI_PHDC_DATAMSG_FORMAT == USB_PHDC_DATAMSG_FORMAT_11073_2060)
	udi_phdc_fnctext_desc_t fnctext;
#endif

	usb_ep_desc_t ep_bulk_in;
	usb_phdc_qos_desc_t qos_bulk_in;
#ifdef UDI_PHDC_METADATA_DESC_BULK_IN
	udi_phdc_metadata_desc_bulkin_t metadata_bulk_in;
#endif

	usb_ep_desc_t ep_bulk_out;
	usb_phdc_qos_desc_t qos_bulk_out;
#ifdef UDI_PHDC_METADATA_DESC_BULK_OUT
	udi_phdc_metadata_desc_bulkout_t metadata_bulk_out;
#endif

#if ((UDI_PHDC_QOS_IN & USB_PHDC_QOS_LOW_GOOD) == USB_PHDC_QOS_LOW_GOOD)
	usb_ep_desc_t ep_int_in;
	usb_phdc_qos_desc_t qos_int_in;
#  ifdef UDI_PHDC_METADATA_DESC_INT_IN
	udi_phdc_metadata_desc_intin_t metadata_int_in;
#  endif
#endif
} udi_phdc_desc_t;

COMPILER_PACK_RESET()

/* ! By default no string associated to this interface */
#ifndef UDI_PHDC_STRING_ID
#define UDI_PHDC_STRING_ID 0
#endif

/* ! Compute the number of endpoints used by the interface */
#if ((UDI_PHDC_QOS_IN & USB_PHDC_QOS_LOW_GOOD) == USB_PHDC_QOS_LOW_GOOD)
#define UDI_PHDC_NUM_ENDPOINT 3 /* Bulk IN, bulk OUT, Interrupt IN */
#else
#define UDI_PHDC_NUM_ENDPOINT 2 /* Bulk IN, bulk OUT */
#endif

/* ! Value to enable/disable in descriptor the feature metadata preample */
#if (UDI_PHDC_PREAMBLE_FEATURE == true)
#define UDI_PHDC_BMCAPABILITY USB_PHDC_CAPABILITY_METADATAMSG_PREAMBLE
#else
#define UDI_PHDC_BMCAPABILITY 0
#endif

/* ! Extension descriptor for optional format 11073 2060 */
#if (UDI_PHDC_DATAMSG_FORMAT == USB_PHDC_DATAMSG_FORMAT_11073_2060)
#define UDI_PHDC_FNCTEXT \
	.fnctext.header.bLength            = sizeof(udi_phdc_fnctext_desc_t), \
	.fnctext.header.bDescriptorType    = USB_DT_PHDC_11073PHD_FUNCTION, \
	.fnctext.header.bReserved          = 0, \
	.fnctext.header.bNumDevSpecs       = sizeof(tmp_wDevSpecializations) / 2, \
	.fnctext.wDevSpecializations       = UDI_PHDC_SPECIALIZATION,
#else
#define UDI_PHDC_FNCTEXT
#endif

/* ! Optional metadata descriptor for endpoint bulk IN */
#ifdef UDI_PHDC_METADATA_DESC_BULK_IN
#define UDI_PHDC_METADATA_BULKIN \
	.metadata_bulk_in.header.bLength \
			= sizeof(udi_phdc_metadata_desc_bulkin_t), \
	.metadata_bulk_in.header.bDescriptorType = USB_DT_PHDC_METADATA, \
	.metadata_bulk_in.bOpaqueData = UDI_PHDC_METADATA_DESC_BULK_IN,
#else
#define UDI_PHDC_METADATA_BULKIN
#endif

/* ! Optional metadata descriptor for endpoint bulk OUT */
#ifdef UDI_PHDC_METADATA_DESC_BULK_OUT
#define UDI_PHDC_METADATA_BULKOUT \
	.metadata_bulk_out.header.bLength \
			= sizeof(udi_phdc_metadata_desc_bulkout_t), \
	.metadata_bulk_out.header.bDescriptorType = USB_DT_PHDC_METADATA, \
	.metadata_bulk_in.bOpaqueData = UDI_PHDC_METADATA_DESC_BULK_OUT,
#else
#define UDI_PHDC_METADATA_BULKOUT
#endif

/* ! Optional metadata descriptor for endpoint interrupt IN */
#ifdef UDI_PHDC_METADATA_DESC_INT_IN
#define UDI_PHDC_METADATA_INTIN \
	.metadata_int_in.header.bLength \
			= sizeof(udi_phdc_metadata_desc_intin_t), \
	.metadata_int_in.header.bDescriptorType = USB_DT_PHDC_METADATA, \
	.metadata_int_in.bOpaqueData       = UDI_PHDC_METADATA_DESC_INT_IN,
#else
#define UDI_PHDC_METADATA_INTIN
#endif

/* ! Declaration of endpoint interrupt IN in case of QOS low good */
#if ((UDI_PHDC_QOS_IN & USB_PHDC_QOS_LOW_GOOD) == USB_PHDC_QOS_LOW_GOOD)
#define UDI_PHDC_EP_INTIN \
	.ep_int_in.bLength                 = sizeof(usb_ep_desc_t), \
	.ep_int_in.bDescriptorType         = USB_DT_ENDPOINT, \
	.ep_int_in.bEndpointAddress        = UDI_PHDC_EP_INTERRUPT_IN, \
	.ep_int_in.bmAttributes            = USB_EP_TYPE_INTERRUPT, \
	.ep_int_in.wMaxPacketSize          = LE16(UDI_PHDC_EP_SIZE_INT_IN), \
	.ep_int_in.bInterval               = 20, \
	.qos_int_in.bLength                = sizeof(usb_phdc_qos_desc_t), \
	.qos_int_in.bDescriptorType        = USB_DT_PHDC_QOS, \
	.qos_int_in.bQoSEncodingVersion    = USB_PHDC_QOS_ENCODING_VERSION_1, \
	.qos_int_in.bmLatencyReliability   = USB_PHDC_QOS_LOW_GOOD, \
	UDI_PHDC_METADATA_INTIN
#else
#define UDI_PHDC_EP_INTIN
#endif

/* ! Content of PHDC interface descriptor for all speeds */
#define UDI_PHDC_DESC    { \
		.iface.bLength             = sizeof(usb_iface_desc_t), \
		.iface.bDescriptorType     = USB_DT_INTERFACE, \
		.iface.bInterfaceNumber    = UDI_PHDC_IFACE_NUMBER, \
		.iface.bAlternateSetting   = 0, \
		.iface.bNumEndpoints       = UDI_PHDC_NUM_ENDPOINT, \
		.iface.bInterfaceClass     = PHDC_CLASS, \
		.iface.bInterfaceSubClass  = PHDC_SUB_CLASS, \
		.iface.bInterfaceProtocol  = PHDC_PROTOCOL, \
		.iface.iInterface          = UDI_PHDC_STRING_ID, \
		.classfnct.bLength \
				= sizeof(usb_phdc_classfnct_desc_t), \
		.classfnct.bDescriptorType         = USB_DT_PHDC_CLASSFUNCTION, \
		.classfnct.bPHDCDataCode           = UDI_PHDC_DATAMSG_FORMAT, \
		.classfnct.bmCapability            = UDI_PHDC_BMCAPABILITY, \
		UDI_PHDC_FNCTEXT \
		.ep_bulk_in.bLength                = sizeof(usb_ep_desc_t), \
		.ep_bulk_in.bDescriptorType        = USB_DT_ENDPOINT, \
		.ep_bulk_in.bEndpointAddress       = UDI_PHDC_EP_BULK_IN, \
		.ep_bulk_in.bmAttributes           = USB_EP_TYPE_BULK, \
		.ep_bulk_in.wMaxPacketSize         = LE16(UDI_PHDC_EP_SIZE_BULK_IN), \
		.ep_bulk_in.bInterval              = 0, \
		.qos_bulk_in.bLength \
			= sizeof(usb_phdc_qos_desc_t), \
		.qos_bulk_in.bDescriptorType       = USB_DT_PHDC_QOS, \
		.qos_bulk_in.bQoSEncodingVersion \
				= USB_PHDC_QOS_ENCODING_VERSION_1, \
		.qos_bulk_in.bmLatencyReliability \
				= UDI_PHDC_QOS_IN & (~USB_PHDC_QOS_LOW_GOOD), \
		UDI_PHDC_METADATA_BULKIN \
		.ep_bulk_out.bLength               = sizeof(usb_ep_desc_t), \
		.ep_bulk_out.bDescriptorType       = USB_DT_ENDPOINT, \
		.ep_bulk_out.bEndpointAddress      = UDI_PHDC_EP_BULK_OUT, \
		.ep_bulk_out.bmAttributes          = USB_EP_TYPE_BULK, \
		.ep_bulk_out.wMaxPacketSize        = LE16(UDI_PHDC_EP_SIZE_BULK_OUT), \
		.ep_bulk_out.bInterval             = 0, \
		.qos_bulk_out.bLength \
				= sizeof(usb_phdc_qos_desc_t), \
		.qos_bulk_out.bDescriptorType      = USB_DT_PHDC_QOS, \
		.qos_bulk_out.bQoSEncodingVersion \
				= USB_PHDC_QOS_ENCODING_VERSION_1, \
		.qos_bulk_out.bmLatencyReliability = UDI_PHDC_QOS_OUT, \
		UDI_PHDC_METADATA_BULKOUT \
		UDI_PHDC_EP_INTIN \
}
/* @} */

/**
 * \ingroup udi_group
 * \defgroup udi_phdc_group USB Device Interface (UDI) for Personal Healthcare
 * Device Class (PHDC)
 *
 * Common APIs used by high level application to use this USB class.
 * @{
 */

/* ! Structure used in argument for routines
 * udi_phdc_senddata and udi_phdc_waitdata
 */
typedef struct {
	uint8_t qos;
	uint8_t *opaquedata;
	uint8_t opaque_size;
	uint8_t *metadata;
	uint16_t metadata_size;
} udi_phdc_metadata_t;

/**
 * \brief Send metadata to USB host
 *
 * \param metadata      Information about metadata to send
 * \param callback      Function to call at the end of transfer.
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
bool udi_phdc_senddata(udi_phdc_metadata_t *metadata,
		void (*callback)(uint16_t));

/**
 * \brief Abort of send metadata to USB host
 */
void udi_phdc_senddata_abort(void);

/**
 * \brief Wait metadata from USB host
 *
 * \param metadata      Information about expected metadata
 * \param callback      Function to call at the end of transfer.
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
bool udi_phdc_waitdata(udi_phdc_metadata_t *metadata,
		void (*callback)(bool, uint16_t));

/* ! @} */

#ifdef __cplusplus
}
#endif
#endif /* _UDI_PHDC_H_ */
