/**
 * \file
 *
 * \brief USB host configuration file
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

#ifndef _CONF_USB_HOST_H_
#define _CONF_USB_HOST_H_

#include "compiler.h"

/**
 * USB Host Configuration
 * @{
 */

//! Array of UHI APIs Define the list of UHI supported by USB host.
#define USB_HOST_UHI        // UHI_MSC, UHI_HID_MOUSE, UHI_CDC, UHI_VENDOR

//! Maximum current allowed on Vbus (mA)
#define USB_HOST_POWER_MAX  500

//! Authorize the USB HUB support
// #define USB_HOST_HUB_SUPPORT

//! Authorize the USB host to run in High Speed
#if (UC3A3 || UC3A4)
#  define USB_HOST_HS_SUPPORT
#endif

/**
 * USB Host callbacks
 * @{
 */

//! To notify that the USB mode are switched automatically.
//! This is possible only when ID pin is available.
//#define UHC_MODE_CHANGE(b_host_mode)        usb_host_mode_change(b_host_mode)

//! To notify that the Vbus level has changed
//! Available only in USB hardware with Vbus monitoring.
//#define UHC_VBUS_CHANGE(b_present)          usb_host_vbus_change(b_present)

//! To notify that a Vbus error has occurred
//! Available only in USB hardware with Vbus monitoring.
//#define UHC_VBUS_ERROR()                    usb_host_vbus_error()

//! To notify that a device has been connected or disconnected.
//#define UHC_CONNECTION_EVENT(dev,b_present) usb_host_connection_event(dev,b_present)

//! Called when a USB device or the host have wake up the USB line.
//#define UHC_WAKEUP_EVENT()                  usb_host_wakeup_event()

//! Called for each received SOF each 1 ms
//! Note: Available in High and Full speed mode
//#define UHC_SOF_EVENT()                     usb_host_sof_event()

//! Called when a USB device configuration must be chosen.
//! Thus, the application can choose either a configuration number for this device
//! or a configuration number 0 to reject it.
//! If callback not defined the configuration 1 is chosen.
//#define UHC_DEVICE_CONF(dev)                uint8_t usb_host_device_conf(dev)

//! Called when a USB device enumeration is completed.
//#define UHC_ENUM_EVENT(dev,b_status)        usb_host_enum_event(dev,b_status)


//@}



/**
 * USB Interface Configuration
 * @{
 */

/**
 * Configuration of HID Mouse interface
 * @{
 */
#define UHI_HID_MOUSE_CHANGE(dev,b_plug)
#define UHI_HID_MOUSE_EVENT_BTN_LEFT(b_state)
#define UHI_HID_MOUSE_EVENT_BTN_RIGHT(b_state)
#define UHI_HID_MOUSE_EVENT_BTN_MIDDLE(b_state)
#define UHI_HID_MOUSE_EVENT_MOUVE(x,y,scroll)
//@}

/**
 * Configuration of MSC interface
 * @{
 */
#define UHI_MSC_CHANGE(dev,b_plug)
//@}

/**
 * Configuration of CDC interface
 * @{
 */
#define UHI_CDC_CHANGE(dev,b_plug)
#define UHI_CDC_RX_NOTIFY()
//@}
/**
 * Configuration of Vendor interface
 * @{
 */
#define UHI_VENDOR_CHANGE(dev, b_plug)
#define UHI_VENDOR_VID_PID_LIST {USB_VID_ATMEL, USB_PID_ATMEL_ASF_VENDOR_CLASS}
//@}
//@}


//@}

//#include "uhi_msc.h"
//#include "uhi_hid_mouse.h"

#endif // _CONF_USB_HOST_H_
