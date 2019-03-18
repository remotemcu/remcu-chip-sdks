/**
 * \file
 *
 * \brief Android Open Accessory
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
#include "conf_usb_host.h"
#include "usb_protocol_aoa.h"
#include "uhd.h"
#include "uhc.h"
#include "uhi_aoa.h"
#include <string.h>

#ifdef USB_HOST_HUB_SUPPORT
#   error USB HUB support is not implemented on UHI Android Open Accessory
#endif

#ifndef AOA_V2_SUPPORT
#   define AOA_V2_SUPPORT 0
#endif

/**
 * \addtogroup uhi_aoa_group
 * @{
 */

/** \name Stages of enabling the Android Device
 * @{
 */
#define AOA_ENABLE_STAGE_PROCESSING 0
#define AOA_ENABLE_STAGE_SUCCESSFUL 1
#define AOA_ENABLE_STAGE_FAILED     2
/** @} */

/**
 * \name Internal Defines and Variables to store information about the Accessory
 * @{
 */

/*! \brief Function to enable the Accessory Mode on Android Devices
 *  - Implements step one of starting the Device in Accessory Mode
 *  - Checks the Protocol Version on the Android Device
 *  - Calls step two of starting the Device in Accessory Mode
 */
void uhi_aoa_mode_enable_step1(uhc_device_t *);

/*! \brief Function to enable the Accessory Mode on Android Devices
 *  - Implements steps two and three of starting the Device in Accessory Mode
 *  - Sends the Identifying Information as Strings
 *  - Calls step three of starting the Device in Accessory Mode
 */
void uhi_aoa_mode_enable_step2(usb_add_t, uhd_trans_status_t, uint16_t);

/*! \brief Function to enable the Accessory Mode on Android Devices
 *  - Implements step three of starting the Device in Accessory Mode
 *  - Sends the Request to Startup in Accessory Mode
 *  - Calls last step of starting the Device in Accessory Mode
 */
void uhi_aoa_mode_enable_step3(usb_add_t, uhd_trans_status_t, uint16_t);

/*! \brief Function to enable the Accessory Mode on Android Devices
 *  - Called when the process of trying to start the device in Accessory Mode
 *    is finished.
 *  - Determines whether the process of starting in Accessory Mode was successful
 *  - Does NOT check if the device is in Accessory Mode. That happens later
 */
void uhi_aoa_mode_enable_complete(usb_add_t, uhd_trans_status_t, uint16_t);

/** Stores relevant information about the USB connection */
struct uhi_aoa_dev_t {
	uhc_device_t *dev;
#if AOA_V2_SUPPORT
	uint16_t protocol;
#endif
	usb_ep_t ep_in;
	usb_ep_t ep_out;
};

/** \brief Function to end AoA enabling success
 *  - Called when the process of trying to enable the device in Accessory Mode
 *    with success.
 */
static void uhi_aoa_enable_success(void);

/** Current USB device AOA selected by the UHI AOA */
#ifdef USB_HOST_HUB_SUPPORT
static struct uhi_aoa_dev_t *uhi_aoa_dev_sel;
#else
#   define uhi_aoa_dev_sel (&uhi_aoa_dev)
#endif

static struct uhi_aoa_dev_t uhi_aoa_dev = {
	.dev = NULL,
};

#ifndef AOA_STRING_MANUFACTURER
#   define AOA_STRING_MANUFACTURER "Atmel"
#   warning Using the default Manufacturer value meant for the EVK1105
#endif
#ifndef AOA_STRING_MODEL
#   define AOA_STRING_MODEL        "EVK1105"
#   warning Using the default Model value meant for the EVK1105
#endif
#ifndef AOA_STRING_DESCRIPTION
#   define AOA_STRING_DESCRIPTION  "EVK1105 Application Board"
#   warning Using the default Application Board value meant for the EVK1105
#endif
#ifndef AOA_STRING_VERSION
#   define AOA_STRING_VERSION      "1.0"
#   warning Using the default Version value meant for the EVK1105
#endif
#ifndef AOA_STRING_URL
#   define AOA_STRING_URL          "http://www.microchip.com/design-centers/smartphone-accessory"
#   warning Using the default URL value meant for the EVK1105
#endif
#ifndef AOA_STRING_SERIAL
#   define AOA_STRING_SERIAL       "0000000012345678"
#   warning Using the default Serial value meant for the EVK1105
#endif

/** @} */

/** Stores the "Android Open Accessory Protocol" version */
volatile uint16_t uhi_aoa_protocol;

/** Stores the status of the process enabling the Accessory device */
volatile uint8_t uhi_aoa_enable_stage;

/**
 * \name Functions required by UHC
 * @{
 */

uhc_enum_status_t uhi_aoa_install(uhc_device_t *dev)
{
	bool b_iface_supported;
	uint16_t conf_desc_lgt;
	usb_iface_desc_t *ptr_iface;

	if (uhi_aoa_dev.dev != NULL) {
		return UHC_ENUM_SOFTWARE_LIMIT; /* Device already allocated */
	}

	if ((dev->dev_desc.idVendor == le16_to_cpu(GOOGLE_VID)) &&
			((dev->dev_desc.idProduct == le16_to_cpu(AOA_ACCESSORY_PID)) ||
			 (dev->dev_desc.idProduct == le16_to_cpu(AOA_ACCESSORY_ADB_PID))
#if AOA_V2_SUPPORT
			 || (dev->dev_desc.idProduct == le16_to_cpu(AOA_ACCESSORY_AUDIO_PID))
			 || (dev->dev_desc.idProduct == le16_to_cpu(AOA_ACCESSORY_AUDIO_ADB_PID))
#endif
			 )) {
		/* Device is in AOA mode */
		uhi_aoa_dev.dev = dev;
		uhi_aoa_enable_stage = AOA_ENABLE_STAGE_SUCCESSFUL;
	} else {
		/* Not determined if the device supports AOA */
		uhi_aoa_enable_stage = AOA_ENABLE_STAGE_PROCESSING;
	}

	conf_desc_lgt = le16_to_cpu(dev->conf_desc->wTotalLength);
	ptr_iface = (usb_iface_desc_t*)dev->conf_desc;
	b_iface_supported = false;
	uhi_aoa_dev.ep_in = 0;
	uhi_aoa_dev.ep_out = 0;

	while(conf_desc_lgt) {
		switch (ptr_iface->bDescriptorType) {
		case USB_DT_INTERFACE:
			if (ptr_iface->bInterfaceClass ==
					CLASS_VENDOR_SPECIFIC) {
				/* Possibly an AOA interface */
				/* Start allocation endpoint(s) */
				b_iface_supported = true;
			} else {
				/* Stop allocation endpoint(s) */
				b_iface_supported = false;
			}

			break;

		case USB_DT_ENDPOINT:
			/* Allocation of the endpoint */
			if (!b_iface_supported) {
				break;
			}

			usb_ep_desc_t *ptr_ep = (usb_ep_desc_t *) ptr_iface;
			if (!uhd_ep_alloc(dev->address, (usb_ep_desc_t*)ptr_iface, dev->speed)) {
				/* Endpoint allocation fail */
				return UHC_ENUM_HARDWARE_LIMIT;
			}

			if (ptr_ep->bEndpointAddress & USB_EP_DIR_IN) {
				uhi_aoa_dev.ep_in = ptr_ep->bEndpointAddress;
			} else {
				uhi_aoa_dev.ep_out = ptr_ep->bEndpointAddress;
			}

			if (uhi_aoa_dev.ep_out && uhi_aoa_dev.ep_in) {
				/* All Endpoints allocated */
				uhi_aoa_dev.dev = dev;
				return UHC_ENUM_SUCCESS;
			}

			break;

		default:
			/* Ignore descriptor */
			break;
		}
		Assert(conf_desc_lgt>=ptr_iface->bLength);
		conf_desc_lgt = ptr_iface->bLength;
		ptr_iface =
				(usb_iface_desc_t*)((uint8_t*)ptr_iface +
				ptr_iface->bLength);
	}

	if (uhi_aoa_dev.ep_in) {
		uhd_ep_free(0,uhi_aoa_dev.ep_in);
	}

	if (uhi_aoa_dev.ep_out) {
		uhd_ep_free(0,uhi_aoa_dev.ep_out);
	}

	return UHC_ENUM_UNSUPPORTED; /* No interface supported */
}

void uhi_aoa_enable(uhc_device_t *dev)
{
	if (uhi_aoa_dev.dev != dev) {
		return; /* No interface to enable */
	}

	if (uhi_aoa_enable_stage == AOA_ENABLE_STAGE_SUCCESSFUL) {
		uhi_aoa_enable_success();
	} else if (uhi_aoa_enable_stage == AOA_ENABLE_STAGE_PROCESSING) {
		uhi_aoa_mode_enable_step1(dev);
	}
}

void uhi_aoa_uninstall(uhc_device_t *dev)
{
	if (uhi_aoa_dev.dev != dev) {
		return; /* Device not enabled in this interface */
	}

	uhi_aoa_dev.dev = NULL;
	uhi_aoa_dev.ep_in = 0x00;
	uhi_aoa_dev.ep_out = 0x00;
#if AOA_V2_SUPPORT
	uhi_aoa_dev.protocol = 0;
#endif
	UHI_AOA_CHANGE(dev, false);
}

/** @} */

void uhi_aoa_mode_enable_step1(uhc_device_t *dev)
{
	uhi_aoa_dev.dev = dev;

	usb_setup_req_t req;
	req.bmRequestType = USB_REQ_RECIP_DEVICE | USB_REQ_TYPE_VENDOR |
			USB_REQ_DIR_IN;
	req.bRequest = (uint8_t)USB_REQ_AOA_GET_PROTOCOL;
	req.wValue = 0;
	req.wIndex = 0;
	req.wLength = 0x02;
	uhd_setup_request(dev->address, &req, (uint8_t *)&uhi_aoa_protocol, 2,
			NULL, uhi_aoa_mode_enable_step2);
}

void uhi_aoa_mode_enable_step2(
		usb_add_t add,
		uhd_trans_status_t status,
		uint16_t payload_trans)
{
	(void)add;
	(void)payload_trans;
	if (status == UHD_TRANS_NOERROR) {
		uhi_aoa_protocol = le16_to_cpu(uhi_aoa_protocol);
		if (uhi_aoa_protocol != 0) {
			uhi_aoa_send_info_string(
					(uint8_t)AOA_STRING_INDEX_MANUFACTURER,
					(char *)AOA_STRING_MANUFACTURER, NULL);
			uhi_aoa_send_info_string(
					(uint8_t)AOA_STRING_INDEX_MODEL,
					(char *)AOA_STRING_MODEL, NULL);
			uhi_aoa_send_info_string(
					(uint8_t)AOA_STRING_INDEX_DESCRIPTION,
					(char *)AOA_STRING_DESCRIPTION, NULL);
			uhi_aoa_send_info_string(
					(uint8_t)AOA_STRING_INDEX_VERSION,
					(char *)AOA_STRING_VERSION, NULL);
			uhi_aoa_send_info_string(
					(uint8_t)AOA_STRING_INDEX_URL,
					(char *)AOA_STRING_URL, NULL);
			uhi_aoa_send_info_string(
					(uint8_t)AOA_STRING_INDEX_SERIAL,
					(char *)AOA_STRING_SERIAL,
					uhi_aoa_mode_enable_step3);
		} else { /* Device does not support Accessory Mode */
			uhi_aoa_enable_stage = AOA_ENABLE_STAGE_FAILED;
		}
	} else {
		uhi_aoa_enable_stage = AOA_ENABLE_STAGE_FAILED;
	}
}

void uhi_aoa_mode_enable_step3(
		usb_add_t add,
		uhd_trans_status_t status,
		uint16_t payload_trans)
{
	(void)add;
	(void)payload_trans;
	if (status == UHD_TRANS_NOERROR) {
		usb_setup_req_t req;

		req.bmRequestType = USB_REQ_RECIP_DEVICE | USB_REQ_TYPE_VENDOR |
				USB_REQ_DIR_OUT;
		req.bRequest = (uint8_t)USB_REQ_AOA_STARTUP;
		req.wValue = 0;
		req.wIndex = 0;
		req.wLength = 0;

		uhd_setup_request(uhi_aoa_dev_sel->dev->address, &req, NULL, 0,
				NULL, uhi_aoa_mode_enable_complete);
	} else {
		uhi_aoa_enable_stage = AOA_ENABLE_STAGE_FAILED;
	}
}

void uhi_aoa_mode_enable_complete(
		usb_add_t add,
		uhd_trans_status_t status,
		uint16_t payload_trans)
{
	(void)add;
	(void)payload_trans;
	if (status == UHD_TRANS_NOERROR) {
		uhi_aoa_enable_stage = AOA_ENABLE_STAGE_SUCCESSFUL;
		uhi_aoa_enable_success();
	} else {
		uhi_aoa_enable_stage = AOA_ENABLE_STAGE_FAILED;
	}
}

static void uhi_aoa_enable_success(void)
{
#if AOA_V2_SUPPORT
	uhi_aoa_dev_sel->protocol = uhi_aoa_protocol;
#endif

	/* Notify AoA change */
	UHI_AOA_CHANGE(uhi_aoa_dev_sel->dev, true);
}

void uhi_aoa_send_info_string(uint8_t pindex, char *pinfo,
		uhd_callback_setup_end_t callback_end)
{
	usb_setup_req_t req;

	req.bmRequestType = USB_REQ_RECIP_DEVICE | USB_REQ_TYPE_VENDOR |
			USB_REQ_DIR_OUT;
	req.bRequest = (uint8_t)USB_REQ_AOA_SEND_IDENT_STRING;
	req.wValue = 0;
	req.wIndex = ((uint16_t)pindex);
	req.wLength = ((uint16_t)(strlen(pinfo) + 1));
	uhd_setup_request(uhi_aoa_dev_sel->dev->address, &req, (uint8_t *)pinfo,
			req.wLength, NULL, callback_end);
}

bool uhi_aoa_read(uint8_t *payload, uint16_t payload_size,
		uhd_callback_trans_t callback_end)
{
	return uhd_ep_run(uhi_aoa_dev_sel->dev->address, uhi_aoa_dev.ep_in,
			false, payload, payload_size, 100, callback_end);
}

bool uhi_aoa_write(uint8_t *payload, uint16_t payload_size,
		uhd_callback_trans_t callback_end)
{
	return uhd_ep_run(uhi_aoa_dev_sel->dev->address, uhi_aoa_dev.ep_out,
			!payload_size, payload, payload_size, 100, callback_end);
}


bool uhi_aoa_register_hid(uint16_t id, uint8_t *rpt_desc, uint16_t desc_len)
{
#if AOA_V2_SUPPORT
	usb_setup_req_t req;
	uint16_t off, pkt_siz;
	if (uhi_aoa_enable_stage != AOA_ENABLE_STAGE_SUCCESSFUL) {
		return false;
	}
	if (uhi_aoa_dev_sel->protocol < 2) {
		return false;
	}
	req.bmRequestType = USB_REQ_RECIP_DEVICE | USB_REQ_TYPE_VENDOR |
			USB_REQ_DIR_OUT;
	req.bRequest = (uint8_t)USB_REQ_AOA_REGISTER_HID;
	req.wValue = cpu_to_le16(id);
	req.wIndex = cpu_to_le16(desc_len);
	req.wLength = 0;
	if (!uhd_setup_request(uhi_aoa_dev_sel->dev->address, &req, NULL, 0,
			NULL, NULL)) {
		return false;
	}
	req.bRequest = (uint8_t)USB_REQ_AOA_SET_HID_RPT_DESC;
	for (off = 0; off < desc_len; ) {
		pkt_siz = desc_len - off;
		if (pkt_siz > uhi_aoa_dev_sel->dev->dev_desc.bMaxPacketSize0) {
			pkt_siz = uhi_aoa_dev_sel->dev->dev_desc.bMaxPacketSize0;
		}
		req.wIndex = cpu_to_le16(off);
		req.wLength = cpu_to_le16(pkt_siz);
		if (!uhd_setup_request(uhi_aoa_dev_sel->dev->address, &req,
				&rpt_desc[off], pkt_siz, NULL, NULL)) {
			return false;
		}
		off += pkt_siz;
	}
	return true;
#else
	return false;
#endif
}

bool uhi_aoa_unregister_hid(uint16_t id)
{
#if AOA_V2_SUPPORT
	usb_setup_req_t req;
	if (uhi_aoa_dev_sel->protocol < 2) {
		return false;
	}
	req.bmRequestType = USB_REQ_RECIP_DEVICE | USB_REQ_TYPE_VENDOR |
			USB_REQ_DIR_OUT;
	req.bRequest = (uint8_t)USB_REQ_AOA_UNREGISTER_HID;
	req.wValue = cpu_to_le16(id);
	req.wIndex = 0;
	req.wLength = 0;
	return uhd_setup_request(uhi_aoa_dev_sel->dev->address, &req, NULL, 0,
			NULL, NULL);
#else
	return false;
#endif
}

bool uhi_aoa_send_hid_event(uint16_t id, void *hid_rpt, uint16_t rpt_size)
{
#if AOA_V2_SUPPORT
	usb_setup_req_t req;
	if (uhi_aoa_dev_sel->protocol < 2) {
		return false;
	}
	req.bmRequestType = USB_REQ_RECIP_DEVICE | USB_REQ_TYPE_VENDOR |
			USB_REQ_DIR_OUT;
	req.bRequest = (uint8_t)USB_REQ_AOA_SEND_HID_EVENT;
	req.wValue = cpu_to_le16(id);
	req.wIndex = 0;
	req.wLength = cpu_to_le16(rpt_size);
	return uhd_setup_request(uhi_aoa_dev_sel->dev->address, &req,
			(uint8_t *)hid_rpt, rpt_size,
			NULL, NULL);
#else
	return false;
#endif
}

/** @} */
/** @} */
