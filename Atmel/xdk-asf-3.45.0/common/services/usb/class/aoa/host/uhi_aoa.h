/**
 * \file
 *
 * \brief Android Open Accessory Header File
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
#ifndef _UHI_AOA_H_
#define _UHI_AOA_H_

#include <string.h>
#include "conf_usb_host.h"
#include "conf_aoa.h"
#include "usb_protocol_aoa.h"
#include "uhc.h"
#include "uhi.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup uhi_group
 * \defgroup uhi_aoa_group UHI for Android Open Accessory
 * @{
 */

/** Global structure which contains standard UHI API for UHC */
#define UHI_AOA { \
		.install = uhi_aoa_install, \
		.enable = uhi_aoa_enable, \
		.uninstall = uhi_aoa_uninstall, \
		.sof_notify = NULL, \
}

/**
 * Functions required by UHC
 *
 */
extern uhc_enum_status_t uhi_aoa_install(uhc_device_t *dev);
extern void uhi_aoa_enable(uhc_device_t *dev);
extern void uhi_aoa_uninstall(uhc_device_t *dev);

/**
 * \name Routines to initialize the Android device
 * @{
 */

/*! \brief Function to send Identifying Information to the Android Device
 *
 */
void uhi_aoa_send_info_string(uint8_t, char *, uhd_callback_setup_end_t);

/**
 * \brief Tries to configure bulk Endpoints for the Android Accessory
 *
 * \return true, if Configuration was successful
 */
bool uhi_aoa_configure(uhc_device_t *);

/**
 * \brief Takes care of Devices being attached/detached
 *
 */
void main_event_aoa(uhc_device_t *, bool);

/** @} */

/**
 * \name Routines to communicate with the Android device
 * @{
 */

/**
 * \brief Main Function to receive a message from an Android device
 *
 * \param payload        Pointer on the data to transfer
 * \param payload_size   Size of the data to transfer
 * \param callback_end   Callback to call at the end of transfer
 */
bool uhi_aoa_read(uint8_t *payload, uint16_t payload_size,
		uhd_callback_trans_t callback_end);

/**
 * \brief Main Function to send a message to an Android device
 *
 * \param payload        Pointer on the data to transfer
 * \param payload_size   Size of the data to transfer
 * \param callback_end   Callback to call at the end of transfer
 */
bool uhi_aoa_write(uint8_t *payload, uint16_t payload_size,
		uhd_callback_trans_t callback_end);

/**
 * \brief Register a HID device
 *
 * \param[in]  id                ID for the HID device
 * \param[in]  hid_rpt_desc      Pointer to the HID report descriptor
 * \param[in]  hid_rpt_desc_len  Total length of the HID report descriptor
 */
bool uhi_aoa_register_hid(uint16_t id,
		uint8_t *hid_rpt_desc, uint16_t hid_rpt_desc_len);

/**
 * \brief Unregister a HID device
 *
 * \param[in]  id ID for HID device
 */
bool uhi_aoa_unregister_hid(uint16_t id);

/**
 * \brief Send HID events
 *
 * \param[in]  id       ID for the HID device
 * \param[in]  hid_rpt  Pointer to the HID report for the event,
 *                      the report format and data length should follow what
 *                      is defined in HID report descriptor.
 * \param[in]  rpt_size The HID report size
 */
bool uhi_aoa_send_hid_event(uint16_t id, void *hid_rpt, uint16_t rpt_size);


/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif /** _UHI_AOA_H_ */
