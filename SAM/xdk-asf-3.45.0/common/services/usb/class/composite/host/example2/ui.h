/**
 * \file
 *
 * \brief Common User Interface for USB host composite application
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _UI_H_
#define _UI_H_

#include "uhc.h"

//! \brief Initializes the user interface
void ui_init(void);

/*! \brief Notify that the USB mode are switched automatically.
 * This is possible only when ID pin is available.
 *
 * \param b_host_mode true, if the host mode has been selected
 */
void ui_usb_mode_change(bool b_host_mode);

/*! \brief Notify that a Vbus are changed
 * Available only in USB hardware with Vbus monitoring.
 *
 * \param b_vbus_present true, if Vbus is high.
 */
void ui_usb_vbus_change(bool b_vbus_present);

/*! \brief Notify that a Vbus error has occurred
 * Available only in USB hardware with Vbus monitoring.
 */
void ui_usb_vbus_error(void);

/*! \brief Notify that a USB device has been connected or disconnected.
 *
 * \param dev         Pointer on USB device information
 * \param b_present   true, if the device has been connected
 */
void ui_usb_connection_event(uhc_device_t *dev, bool b_present);

//! \brief Notify that a USB device or the host has wake up the USB line.
void ui_usb_wakeup_event(void);

//! \brief Notify that a SOF has been sent (each 1 ms)
void ui_usb_sof_event(void);

//! \brief Resets the status flag of the test
void ui_test_flag_reset(void);

/*! \brief Displays the result of the test
 *
 * \param b_success   true, if the test is successful
 */
void ui_test_finish(bool b_success);

/*! \brief Notify the end of a USB device enumeration
 *
 * \param dev         Pointer on USB device information
 * \param status      Status of the USB enumeration
 */
void ui_usb_enum_event(uhc_device_t *dev, uhc_enum_status_t status);

/*! \brief Notify that a USB device HID has been connected or disconnected.
 *
 * \param dev         Pointer on USB device information
 * \param b_plug      true, if the device has been connected
 */
void ui_uhi_hid_mouse_change(uhc_device_t *dev, bool b_plug);

/*! \brief Notify that a USB device MSC has been connected or disconnected.
 *
 * \param dev         Pointer on USB device information
 * \param b_plug      true, if the device has been connected
 */
void ui_uhi_msc_change(uhc_device_t *dev, bool b_plug);

//! \name Callback to manage the HID mouse events
//! @{
void ui_uhi_hid_mouse_btn_left(bool b_state);
void ui_uhi_hid_mouse_btn_right(bool b_state);
void ui_uhi_hid_mouse_btn_middle(bool b_state);
void ui_uhi_hid_mouse_move(int8_t x,int8_t y,int8_t scroll);
//! @}

//! \name Callback to show the MSC read and write access
//! Functions are already declared in conf_access.h.
//! @{
//! @}

#endif // _UI_H_
