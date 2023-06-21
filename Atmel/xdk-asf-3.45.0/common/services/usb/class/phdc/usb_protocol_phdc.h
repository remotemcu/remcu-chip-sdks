/**
 * \file
 *
 * \brief USB Personal Healthcare Device Class (PHDC) protocol definitions.
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

#ifndef _USB_PROTOCOL_PHDC_H_
#define _USB_PROTOCOL_PHDC_H_


/**
 * \ingroup usb_protocol_group
 * \defgroup usb_phdc_protocol USB Personal Healthcare Device Class (PHDC)
 * protocol definitions
 *
 * @{
 */

/**
 * \name Possible Class value
 */
//@{
#define  PHDC_CLASS         0x0F
//@}

/**
 * \name Possible SubClass value
 */
//@{
#define  PHDC_SUB_CLASS     0x00
//@}

/**
 * \name Possible protocol value
 * \note Only the BULK protocol should be used in new designs.
 */
//@{
#define  PHDC_PROTOCOL      0x00
//@}


/**
 * \brief Standard USB PHDC interface feature flags
 *
 * \note valid for SetFeature and ClearFeature requests.
 */
enum usb_phdc_feature {
	USB_PHDC_FEATURE_METADATA = 0x01,
};

/**
 * \brief PHDC USB descriptor types
 */
enum usb_descriptor_type_phdc {
	USB_DT_PHDC_CLASSFUNCTION = 0x20,
	USB_DT_PHDC_QOS = 0x21,
	USB_DT_PHDC_METADATA = 0x22,
	USB_DT_PHDC_11073PHD_FUNCTION = 0x30,
};

/**
 * \brief PHDC Data/Messaging format code
 */
enum usb_phdc_data_msg_format_code {
	USB_PHDC_DATAMSG_FORMAT_VENDOR = 0x01,
	//! refer to the section ISO/IEEE AA073-20601 protocol for further information
	USB_PHDC_DATAMSG_FORMAT_11073_20601 = 0x02,
};

/**
 * \brief PHDC interface capability
 */
enum usb_phdc_capability {
	//! If Meta_Data Message Preamble is implemented
	USB_PHDC_CAPABILITY_METADATAMSG_PREAMBLE = (1 << 0),
};

/**
 * \brief QoS Encoding Version
 */
enum usb_phdc_qos_encoding_version {
	USB_PHDC_QOS_ENCODING_VERSION_1 = 0x01,
};

//! \name latency/reliability bin for the QoS data
//! @{
#define  USB_PHDC_QOS_VERYHIGH_BEST  (1<<5)
#define  USB_PHDC_QOS_HIGH_BEST      (1<<4)
#define  USB_PHDC_QOS_MEDIUM_BEST    (1<<3)
#define  USB_PHDC_QOS_MEDIUM_BETTER  (1<<2)
#define  USB_PHDC_QOS_MEDIUM_GOOD    (1<<1)
#define  USB_PHDC_QOS_LOW_GOOD       (1<<0)
//! @}

//! String use by meta-data message to verify it
#define METADATA_MESSAGE_SIG 	\
			{'P','h','d','c','Q','o','S','S','i','g','n','a','t','u','r','e'}

COMPILER_PACK_SET(1)

//! PHDC Class Function Descriptor
typedef struct {
	uint8_t bLength;	//!< Size of this descriptor in bytes
	uint8_t bDescriptorType;	//!< PHDC descriptor type
	uint8_t bPHDCDataCode;	//!< Data/Messaging format code
	uint8_t bmCapability;	//!< Features available in the interface
} usb_phdc_classfnct_desc_t;

//! PHDC Function Extension Descriptor
//! Note: The wDevSpecializations fields must follow this struct
typedef struct {
	uint8_t bLength;	//!< Size of this descriptor in bytes
	uint8_t bDescriptorType;	//!< PHDC descriptor type
	uint8_t bReserved;	//!< Reserved for future use, must be zero
	uint8_t bNumDevSpecs;	//!< Number of wDevSpecializations below
} usb_phdc_fnctext_desc_t;

//! PHDC Function Extension Descriptor with single specification
typedef struct {
	uint8_t bLength;	//!< Size of this descriptor in bytes
	uint8_t bDescriptorType;	//!< PHDC descriptor type
	uint8_t bReserved;	//!< Reserved for future use, must be zero
	uint8_t bNumDevSpecs;	//!< Number of wDevSpecializations below
	le16_t wDevSpecializations;	//!< list that defines the device specialization
} usb_phdc_fnctext_singlespec_desc_t;

//! PHDC QoS Descriptor
typedef struct {
	uint8_t bLength;	//!< Size of this descriptor in bytes
	uint8_t bDescriptorType;	//!< PHDC descriptor type
	uint8_t bQoSEncodingVersion;	//!< 01h = version 1 QoS information encoding
	uint8_t bmLatencyReliability;	//!< If bQoSEncodingVersion = 01h,
	//!< then this bitmap refers to the latency/reliability bin for the QoS data
} usb_phdc_qos_desc_t;

//! PHDC Meta-Data Descriptor
//! Note: The optional meta-data field (0 to 253B) can follow this struct
typedef struct {
	uint8_t bLength;	//!< Size of this descriptor in bytes
	uint8_t bDescriptorType;	//!< PHDC descriptor type
} usb_phdc_meta_data_desc_t;

typedef struct {
	usb_phdc_meta_data_desc_t header;
	uint8_t bOpaqueData[1];	//!< Opaque meta-data (size=1)
} usb_phdc_meta_data_1_desc_t;

//! PHDC Meta-Data Message
//! Note: The optional meta-data field (0 to EPx_size-21) can follow this struct
typedef struct {
	uint8_t aSignature[16];	//!< Constant used to give preamble verifiability.
	uint8_t bNumTransfers;	//!< Count of following transfers
	uint8_t bQoSEncodingVersion;	//!< 01h = version 1 QoS information encoding
	uint8_t bmLatencyReliability;	//!< If bQoSEncodingVersion = 01h,
	//!< then this bitmap refers to the latency/reliability bin for the QoS data
	uint8_t bOpaqueDataSize;	//!< Size, in bytes, of opaque QoS data or meta-data
	//!< if bQoSEncodingVersion = 01h
} usb_phdc_metadata_msg_t;

typedef struct {
	usb_phdc_metadata_msg_t header;
	uint8_t bOpaqueData[1];	//!< Opaque meta-data (size=1)
} usb_phdc_metadata_msg_1_t;

COMPILER_PACK_RESET()

//@}

#endif // _USB_PROTOCOL_PHDC_H_
