/**
 * \file
 *
 * \brief USB Device Human Interface Device (HID) multi-touch interface.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

#include "conf_usb.h"
#include "usb_protocol.h"
#include "udd.h"
#include "udc.h"
#include "udi_hid.h"
#include "udi_hid_multitouch.h"
#include <string.h>

/**
 * \ingroup udi_hid_multi_touch_group
 * \defgroup udi_hid_multi_touch_group_udc Interface with USB Device Core (UDC)
 *
 * Structures and functions required by UDC.
 *
 * @{
 */
bool udi_hid_multi_touch_enable(void);
void udi_hid_multi_touch_disable(void);
bool udi_hid_multi_touch_setup(void);
uint8_t udi_hid_multi_touch_getsetting(void);

//! Global structure which contains standard UDI interface for UDC
UDC_DESC_STORAGE udi_api_t udi_api_hid_multi_touch = {
	.enable = (bool(*)(void))udi_hid_multi_touch_enable,
	.disable = (void (*)(void))udi_hid_multi_touch_disable,
	.setup = (bool(*)(void))udi_hid_multi_touch_setup,
	.getsetting = (uint8_t(*)(void))udi_hid_multi_touch_getsetting,
	.sof_notify = NULL,
};
//@}


/**
 * \ingroup udi_hid_multi_touch_group
 * \defgroup udi_hid_multi_touch_group_internal Implementation of UDI HID multi-touch
 *
 * Class internal implementation
 * @{
 */

/**
 * \name Internal defines and variables to manage HID multi-touch
 */
//@{

//! To store current rate of HID multi-touch
COMPILER_WORD_ALIGNED
		static uint8_t udi_hid_multi_touch_rate;
//! To store current protocol of HID multi-touch
COMPILER_WORD_ALIGNED
		static uint8_t udi_hid_multi_touch_protocol;
//! To signal if the report IN buffer is free (no transfer on going)
static bool udi_hid_multi_touch_b_report_in_free;
//! Report to send
COMPILER_WORD_ALIGNED
		static uint8_t udi_hid_multi_touch_report_in[UDI_HID_REPORT_IN_SIZE];
//! Report to receive via SetFeature
COMPILER_WORD_ALIGNED
		static uint8_t udi_hid_multi_touch_report_feature[UDI_HID_REPORT_FEATURE_SIZE];

//@}

//! HID report descriptor for standard HID multi-touch
UDC_DESC_STORAGE udi_hid_multi_touch_report_desc_t udi_hid_multi_touch_report_desc = {
		{
			0x05, 0x0d,                         // USAGE_PAGE (Digitizers)
			0x09, 0x04,                         // USAGE (Touch Screen)
			0xa1, 0x01,                         // COLLECTION (Application)
			0x85, UDI_HID_REPORT_ID_MTOUCH,     //   REPORT_ID (Touch)
			0x09, 0x22,                         //   USAGE (Finger)
			0xa1, 0x02,                         //     COLLECTION (Logical)
			0x09, 0x42,                         //       USAGE (Tip Switch)
			0x15, 0x00,                         //       LOGICAL_MINIMUM (0)
			0x25, 0x01,                         //       LOGICAL_MAXIMUM (1)
			0x75, 0x01,                         //       REPORT_SIZE (1)
			0x95, 0x01,                         //       REPORT_COUNT (1)
			0x81, 0x02,                         //       INPUT (Data,Var,Abs)
			0x09, 0x32,                         //       USAGE (In Range)
			0x81, 0x02,                         //       INPUT (Data,Var,Abs)
			0x95, 0x06,                         //       REPORT_COUNT (6)
			0x81, 0x03,                         //       INPUT (Cnst,Ary,Abs)
			0x75, 0x08,                         //       REPORT_SIZE (8)
			0x09, 0x51,                         //       USAGE (Contact Identifier)
			0x95, 0x01,                         //       REPORT_COUNT (1)
			0x81, 0x02,                         //       INPUT (Data,Var,Abs)
			0x05, 0x01,                         //       USAGE_PAGE (Generic Desk..
			0x26, 0xff, 0x0f,                   //       LOGICAL_MAXIMUM (4095)
			0x75, 0x10,                         //       REPORT_SIZE (16)
			0x55, 0x00,                         //       UNIT_EXPONENT (0)
			0x65, 0x00,                         //       UNIT (None)
			0x09, 0x30,                         //       USAGE (X)
			0x35, 0x00,                         //       PHYSICAL_MINIMUM (0)
			0x46, 0x00, 0x00,                   //       PHYSICAL_MAXIMUM (0)
			0x81, 0x02,                         //       INPUT (Data,Var,Abs)
			0x09, 0x31,                         //       USAGE (Y)
			0x46, 0x00, 0x00,                   //       PHYSICAL_MAXIMUM (0)
			0x81, 0x02,                         //       INPUT (Data,Var,Abs)
			0xc0,                               //    END_COLLECTION
			0xa1, 0x02,                         //    COLLECTION (Logical)
			0x05, 0x0d,                         //     USAGE_PAGE (Digitizers)
			0x09, 0x42,                         //       USAGE (Tip Switch)
			0x15, 0x00,                         //       LOGICAL_MINIMUM (0)
			0x25, 0x01,                         //       LOGICAL_MAXIMUM (1)
			0x75, 0x01,                         //       REPORT_SIZE (1)
			0x95, 0x01,                         //       REPORT_COUNT (1)
			0x81, 0x02,                         //       INPUT (Data,Var,Abs)
			0x09, 0x32,                         //       USAGE (In Range)
			0x81, 0x02,                         //       INPUT (Data,Var,Abs)
			0x95, 0x06,                         //       REPORT_COUNT (6)
			0x81, 0x03,                         //       INPUT (Cnst,Ary,Abs)
			0x75, 0x08,                         //       REPORT_SIZE (8)
			0x09, 0x51,                         //       USAGE (Contact Identifier)
			0x95, 0x01,                         //       REPORT_COUNT (1)
			0x81, 0x02,                         //       INPUT (Data,Var,Abs)
			0x05, 0x01,                         //       USAGE_PAGE (Generic Desk..
			0x26, 0xff, 0x0f,                   //       LOGICAL_MAXIMUM (4095)
			0x75, 0x10,                         //       REPORT_SIZE (16)
			0x55, 0x00,                         //       UNIT_EXPONENT (0)
			0x65, 0x00,                         //       UNIT (None)
			0x09, 0x30,                         //       USAGE (X)
			0x35, 0x00,                         //       PHYSICAL_MINIMUM (0)
			0x46, 0x00, 0x00,                   //       PHYSICAL_MAXIMUM (0)
			0x81, 0x02,                         //       INPUT (Data,Var,Abs)
			0x09, 0x31,                         //       USAGE (Y)
			0x46, 0x00, 0x00,                   //       PHYSICAL_MAXIMUM (0)
			0x81, 0x02,                         //       INPUT (Data,Var,Abs)
			0xc0,                               //    END_COLLECTION
			0x05, 0x0d,                         //    USAGE_PAGE (Digitizers)
			0x09, 0x54,                         //    USAGE (Contact Count)
			0x95, 0x01,                         //    REPORT_COUNT (1)
			0x75, 0x08,                         //    REPORT_SIZE (8)
			0x15, 0x00,                         //    LOGICAL_MINIMUM (0)
			0x25, 0x08,                         //    LOGICAL_MAXIMUM (8)
			0x81, 0x02,                         //    INPUT (Data,Var,Abs)
			0x85, UDI_HID_REPORT_ID_MAX_COUNT,  // REPORT_ID (Contact Count Max)
			0x09, 0x55,                         //    USAGE(Contact Count Maximum)
			0x25, 0x02,                         //    LOGICAL_MAXIMUM (2)
			0xb1, 0x02,                         //    FEATURE (Data,Var,Abs)
			0xc0,                               // END_COLLECTION
		}
};

/**
 * \name Internal routines
 */
//@{

/**
 * \brief Recieve or send a report to HID interface
 *
 */
static bool udi_hid_multi_touch_setupreport(void);

/**
 * \brief Callback called when the report is sent
 *
 * \param status     UDD_EP_TRANSFER_OK, if transfer is completed
 * \param status     UDD_EP_TRANSFER_ABORT, if transfer is aborted
 * \param nb_sent    number of data transfered
 */
static void udi_hid_multi_touch_report_in_sent(udd_ep_status_t status,
		iram_size_t nb_sent, udd_ep_id_t ep);

//@}


//--------------------------------------------
//------ Interface for UDI HID level

bool udi_hid_multi_touch_enable(void)
{
	// Initialize internal values
	udi_hid_multi_touch_rate = 0;
	udi_hid_multi_touch_protocol = 0;
	udi_hid_multi_touch_b_report_in_free = true;
	memset(udi_hid_multi_touch_report_in, 0, UDI_HID_REPORT_IN_SIZE);
	return UDI_HID_MTOUCH_ENABLE_EXT();
}


void udi_hid_multi_touch_disable(void)
{
	UDI_HID_MTOUCH_DISABLE_EXT();
}


bool udi_hid_multi_touch_setup(void)
{
	return udi_hid_setup(&udi_hid_multi_touch_rate,
								&udi_hid_multi_touch_protocol,
								(uint8_t *) &udi_hid_multi_touch_report_desc,
								udi_hid_multi_touch_setupreport);
}


uint8_t udi_hid_multi_touch_getsetting(void)
{
	return 0;
}

static bool udi_hid_multi_touch_setupreport(void)
{
	if ((USB_HID_REPORT_TYPE_FEATURE == (udd_g_ctrlreq.req.wValue >> 8))
          && (UDI_HID_REPORT_ID_MAX_COUNT == (0xFF & udd_g_ctrlreq.req.wValue))
          && (sizeof(udi_hid_multi_touch_report_feature) == udd_g_ctrlreq.req.wLength)) {
		// Feature type on report ID maximum contact count equals two
		udi_hid_multi_touch_report_feature[0] = UDI_HID_REPORT_ID_MAX_COUNT;
		udi_hid_multi_touch_report_feature[1] = 2;

		udd_g_ctrlreq.payload = udi_hid_multi_touch_report_feature;
		udd_g_ctrlreq.payload_size = 2;
		return true;
	}

	return false;
}

//--------------------------------------------
//------ Interface for application

bool udi_hid_multi_touch_send_report_in(uint8_t *data)
{
	if (!udi_hid_multi_touch_b_report_in_free)
		return false;

	// Fill report
	memset(&udi_hid_multi_touch_report_in, 0,
			sizeof(udi_hid_multi_touch_report_in));
	memcpy(&udi_hid_multi_touch_report_in, data,
			sizeof(udi_hid_multi_touch_report_in));

	udi_hid_multi_touch_b_report_in_free =
			!udd_ep_run(UDI_HID_MULTI_TOUCH_EP_IN,
							false,
							(uint8_t *) & udi_hid_multi_touch_report_in,
							sizeof(udi_hid_multi_touch_report_in),
							udi_hid_multi_touch_report_in_sent);

	return !udi_hid_multi_touch_b_report_in_free;

}

static void udi_hid_multi_touch_report_in_sent(udd_ep_status_t status,
		iram_size_t nb_sent, udd_ep_id_t ep)
{
	UNUSED(status);
	UNUSED(nb_sent);
	UNUSED(ep);
	udi_hid_multi_touch_b_report_in_free = true;
}

//@}
