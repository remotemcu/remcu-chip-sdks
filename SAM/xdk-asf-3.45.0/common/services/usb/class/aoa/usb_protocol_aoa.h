/**
 * \file
 *
 * \brief USB Android Open Accessory protocol definitions.
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

#ifndef _USB_PROTOCOL_AOA_H_
#define _USB_PROTOCOL_AOA_H_

/**
 * \ingroup usb_protocol_group
 * \defgroup usb_aoa_protocol USB Android Open Accessory
 *
 * @{
 */

/**
 * \brief Android Open Accessory USB requests (bRequest)
 */
/** Get AOA Protocol version */
#define USB_REQ_AOA_GET_PROTOCOL      0x33
/** Sending identifying string info */
#define USB_REQ_AOA_SEND_IDENT_STRING 0x34
/** Start the Android Device in acc mode */
#define USB_REQ_AOA_STARTUP           0x35

/** Register a HID device */
#define USB_REQ_AOA_REGISTER_HID      54
/** Unregister a HID device */
#define USB_REQ_AOA_UNREGISTER_HID    55
/** Sending the HID report descriptor */
#define USB_REQ_AOA_SET_HID_RPT_DESC  56
/** Sending HID events */
#define USB_REQ_AOA_SEND_HID_EVENT    57

/** Google Vendor ID */
#define GOOGLE_VID                  0x18D1
/** Google Product ID which indicates it supports Android Accessory Device */
#define AOA_ACCESSORY_PID           0x2D00
/** Google Product ID which indicates it supports
 * Android Accessory Device which supports ADB */
#define AOA_ACCESSORY_ADB_PID       0x2D01
#define AOA_AUDIO_PID               0x0202
#define AOA_AUDIO_ADB_PID           0x0203
#define AOA_ACCESSORY_AUDIO_PID     0x0204
#define AOA_ACCESSORY_AUDIO_ADB_PID 0x0205

/** Index of manufacturer */
#define AOA_STRING_INDEX_MANUFACTURER  0
/** Index of model */
#define AOA_STRING_INDEX_MODEL         1
/** Index of description */
#define AOA_STRING_INDEX_DESCRIPTION   2
/** Index of version */
#define AOA_STRING_INDEX_VERSION       3
/** Index of URL */
#define AOA_STRING_INDEX_URL           4
/** Index of serialnumber */
#define AOA_STRING_INDEX_SERIAL        5

/** @} */

#endif /* _USB_PROTOCOL_AOA_H_ */
