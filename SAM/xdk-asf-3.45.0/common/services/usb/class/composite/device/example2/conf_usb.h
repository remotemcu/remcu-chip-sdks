/**
 * \file
 *
 * \brief USB configuration file
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

#ifndef _CONF_USB_H_
#define _CONF_USB_H_

#include "compiler.h"

/**
 * USB Device Configuration
 * @{
 */

//! Device definition (mandatory)
#define  USB_DEVICE_VENDOR_ID             USB_VID_ATMEL
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_ASF_MSC_HIDS_CDC
#define  USB_DEVICE_MAJOR_VERSION         1
#define  USB_DEVICE_MINOR_VERSION         0
#define  USB_DEVICE_POWER                 100 // Consumption on Vbus line (mA)
#define  USB_DEVICE_ATTR                  \
	(USB_CONFIG_ATTR_REMOTE_WAKEUP|USB_CONFIG_ATTR_SELF_POWERED)
// (USB_CONFIG_ATTR_REMOTE_WAKEUP|USB_CONFIG_ATTR_BUS_POWERED)
// (USB_CONFIG_ATTR_SELF_POWERED)
// (USB_CONFIG_ATTR_BUS_POWERED)

//! USB Device string definitions (Optional)
#define  USB_DEVICE_MANUFACTURE_NAME      "ATMEL ASF"
#define  USB_DEVICE_PRODUCT_NAME          "HID Mouse, keyboard, CDC and MSC"
#define  USB_DEVICE_SERIAL_NAME           "123123123123" // Disk SN for MSC

/**
 * Device speeds support
 * @{
 */

//! To define a Low speed device
//#define  USB_DEVICE_LOW_SPEED

//! To authorize the High speed
#if (UC3A3||UC3A4)
#  define  USB_DEVICE_HS_SUPPORT
#elif (SAM3XA||SAM3U)
#  define  USB_DEVICE_HS_SUPPORT
#endif
//@}

/**
 * USB Device Callbacks definitions (Optional)
 * @{
 */
#define  UDC_VBUS_EVENT(b_vbus_high)
#define  UDC_SOF_EVENT()                  main_sof_action()
#define  UDC_SUSPEND_EVENT()              main_suspend_action()
#define  UDC_RESUME_EVENT()               main_resume_action()
//! Mandatory when USB_DEVICE_ATTR authorizes remote wakeup feature
#define  UDC_REMOTEWAKEUP_ENABLE()        main_remotewakeup_enable()
#define  UDC_REMOTEWAKEUP_DISABLE()       main_remotewakeup_disable()
//! When a extra string descriptor must be supported
//! other than manufacturer, product and serial string
#define  UDC_GET_EXTRA_STRING()           main_extra_string()
//@}

/**
 * USB Device low level configuration
 * When only one interface is used, these configurations are defined by the class module.
 * For composite device, these configuration must be defined here
 * @{
 */
//! Control endpoint size
#define  USB_DEVICE_EP_CTRL_SIZE       64

//! Two interfaces for this device (CDC + MSC + HID mouse + HID keyboard)
#define  USB_DEVICE_NB_INTERFACE       5

//! 7 endpoints used by HID mouse, HID keyboard, CDC and MSC interfaces
//! but an IN and OUT endpoints can be defined with the same number on XMEGA, thus 5
// (7 | USB_EP_DIR_IN)  // CDC Notify endpoint
// (6 | USB_EP_DIR_IN)  // CDC TX
// (5 | USB_EP_DIR_OUT) // CDC RX
// (1 | USB_EP_DIR_IN)  // MSC IN
// (2 | USB_EP_DIR_OUT) // MSC OUT
// (3 | USB_EP_DIR_IN)  // HID mouse report
// (4 | USB_EP_DIR_IN)  // HID keyboard report
#define  USB_DEVICE_MAX_EP             7
#  if SAM3XA && defined(USB_DEVICE_HS_SUPPORT)
// In HS mode, size of bulk endpoints are 512
// If CDC and MSC endpoints all uses 2 banks, DPRAM is not enough: 4 bulk
// endpoints requires 4K bytes. So reduce the number of banks of CDC bulk
// endpoints to use less DPRAM. Keep MSC setting to keep MSC performance.
#     define  UDD_BULK_NB_BANK(ep) ((ep == 5 || ep== 6) ? 1 : 2)
#  endif
//@}

//@}


/**
 * USB Interface Configuration
 * @{
 */

/**
 * Configuration of CDC interface
 * @{
 */

//! Define two USB communication ports
#define  UDI_CDC_PORT_NB 1

//! Interface callback definition
#define  UDI_CDC_ENABLE_EXT(port)         main_cdc_enable(port)
#define  UDI_CDC_DISABLE_EXT(port)        main_cdc_disable(port)
#define  UDI_CDC_RX_NOTIFY(port)          uart_rx_notify(port)
#define  UDI_CDC_TX_EMPTY_NOTIFY(port)
#define  UDI_CDC_SET_CODING_EXT(port,cfg) uart_config(port,cfg)
#define  UDI_CDC_SET_DTR_EXT(port,set)    main_cdc_set_dtr(port,set)
#define  UDI_CDC_SET_RTS_EXT(port,set)

//! Define it when the transfer CDC Device to Host is a low rate (<512000 bauds)
//! to reduce CDC buffers size
//#define  UDI_CDC_LOW_RATE

//! Default configuration of communication port
#define  UDI_CDC_DEFAULT_RATE             115200
#define  UDI_CDC_DEFAULT_STOPBITS         CDC_STOP_BITS_1
#define  UDI_CDC_DEFAULT_PARITY           CDC_PAR_NONE
#define  UDI_CDC_DEFAULT_DATABITS         8

//! Enable id string of interface to add an extra USB string
#define  UDI_CDC_IAD_STRING_ID            4

/**
 * USB CDC low level configuration
 * In standalone these configurations are defined by the CDC module.
 * For composite device, these configuration must be defined here
 * @{
 */
//! Endpoint numbers definition
#define  UDI_CDC_COMM_EP_0             (7 | USB_EP_DIR_IN)  // Notify endpoint
#define  UDI_CDC_DATA_EP_IN_0          (6 | USB_EP_DIR_IN)  // TX
#define  UDI_CDC_DATA_EP_OUT_0         (5 | USB_EP_DIR_OUT) // RX

//! Interface numbers
#define  UDI_CDC_COMM_IFACE_NUMBER_0   0
#define  UDI_CDC_DATA_IFACE_NUMBER_0   1
//@}
//@}


/**
 * Configuration of MSC interface
 * @{
 */
//! Vendor name and Product version of MSC interface
#define UDI_MSC_GLOBAL_VENDOR_ID            \
   'A', 'T', 'M', 'E', 'L', ' ', ' ', ' '
#define UDI_MSC_GLOBAL_PRODUCT_VERSION            \
   '1', '.', '0', '0'

//! Interface callback definition
#define  UDI_MSC_ENABLE_EXT()          main_msc_enable()
#define  UDI_MSC_DISABLE_EXT()         main_msc_disable()

//! Enable id string of interface to add an extra USB string
#define  UDI_MSC_STRING_ID                5

/**
 * USB MSC low level configuration
 * In standalone these configurations are defined by the MSC module.
 * For composite device, these configuration must be defined here
 * @{
 */
//! Endpoint numbers definition
#define  UDI_MSC_EP_IN                 (1 | USB_EP_DIR_IN)
#define  UDI_MSC_EP_OUT                (2 | USB_EP_DIR_OUT)

//! Interface number
#define  UDI_MSC_IFACE_NUMBER          2
//@}
//@}


/**
 * Configuration of HID Mouse interface
 * @{
 */
//! Interface callback definition
#define  UDI_HID_MOUSE_ENABLE_EXT()       main_mouse_enable()
#define  UDI_HID_MOUSE_DISABLE_EXT()      main_mouse_disable()

//! Enable id string of interface to add an extra USB string
#define  UDI_HID_MOUSE_STRING_ID          6

/**
 * USB HID Mouse low level configuration
 * In standalone these configurations are defined by the HID Mouse module.
 * For composite device, these configuration must be defined here
 * @{
 */
//! Endpoint numbers definition
#define  UDI_HID_MOUSE_EP_IN           (3 | USB_EP_DIR_IN)

//! Interface number
#define  UDI_HID_MOUSE_IFACE_NUMBER    3
//@}
//@}

/**
 * Configuration of HID Keyboard interface
 * @{
 */
//! Interface callback definition
#define  UDI_HID_KBD_ENABLE_EXT()       main_keyboard_enable()
#define  UDI_HID_KBD_DISABLE_EXT()      main_keyboard_disable()
#define  UDI_HID_KBD_CHANGE_LED(value)  ui_kbd_led(value)

//! Enable id string of interface to add an extra USB string
#define  UDI_HID_KBD_STRING_ID            7

/**
 * USB HID Keyboard low level configuration
 * In standalone these configurations are defined by the HID Keyboard module.
 * For composite device, these configuration must be defined here
 * @{
 */
//! Endpoint numbers definition
#define  UDI_HID_KBD_EP_IN           (4 | USB_EP_DIR_IN)

//! Interface number
#define  UDI_HID_KBD_IFACE_NUMBER    4
//@}
//@}

//@}


/**
 * Description of Composite Device
 * @{
 */
//! USB Interfaces descriptor structure
#define	UDI_COMPOSITE_DESC_T \
	usb_iad_desc_t       udi_cdc_iad; \
	udi_cdc_comm_desc_t  udi_cdc_comm; \
	udi_cdc_data_desc_t  udi_cdc_data; \
	udi_msc_desc_t       udi_msc; \
	udi_hid_mouse_desc_t udi_hid_mouse; \
	udi_hid_kbd_desc_t   udi_hid_kbd

//! USB Interfaces descriptor value for Full Speed
#define UDI_COMPOSITE_DESC_FS \
	.udi_cdc_iad   = UDI_CDC_IAD_DESC_0, \
	.udi_cdc_comm  = UDI_CDC_COMM_DESC_0, \
	.udi_cdc_data  = UDI_CDC_DATA_DESC_0_FS, \
	.udi_msc       = UDI_MSC_DESC_FS, \
	.udi_hid_mouse = UDI_HID_MOUSE_DESC, \
	.udi_hid_kbd   = UDI_HID_KBD_DESC

//! USB Interfaces descriptor value for High Speed
#define UDI_COMPOSITE_DESC_HS \
	.udi_cdc_iad   = UDI_CDC_IAD_DESC_0, \
	.udi_cdc_comm  = UDI_CDC_COMM_DESC_0, \
	.udi_cdc_data  = UDI_CDC_DATA_DESC_0_HS, \
	.udi_msc       = UDI_MSC_DESC_HS, \
	.udi_hid_mouse = UDI_HID_MOUSE_DESC, \
	.udi_hid_kbd   = UDI_HID_KBD_DESC

//! USB Interface APIs
#define	UDI_COMPOSITE_API \
	&udi_api_cdc_comm, \
	&udi_api_cdc_data, \
	&udi_api_msc, \
	&udi_api_hid_mouse, \
	&udi_api_hid_kbd
//@}


/**
 * USB Device Driver Configuration
 * @{
 */
//@}

//! The includes of classes and other headers must be done at the end of this file to avoid compile error
#include "udi_cdc.h"
#include "udi_msc.h"
#include "udi_hid_mouse.h"
#include "udi_hid_kbd.h"
#include "uart.h"
#include "main.h"
#include "ui.h"

#endif // _CONF_USB_H_
