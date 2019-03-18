/**
 * \file
 *
 * \brief USB configuration file
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

#ifndef _CONF_USB_H_
#define _CONF_USB_H_

#include "compiler.h"

#warning You must refill the following definitions with a correct values

/**
 * USB Device Configuration
 * @{
 */

//! Device definition (mandatory)
#define  USB_DEVICE_VENDOR_ID             USB_VID_ATMEL
#define  USB_DEVICE_PRODUCT_ID            0xFFFF
#define  USB_DEVICE_MAJOR_VERSION         1
#define  USB_DEVICE_MINOR_VERSION         0
#define  USB_DEVICE_POWER                 100 // Consumption on Vbus line (mA)
#define  USB_DEVICE_ATTR                  \
	(USB_CONFIG_ATTR_SELF_POWERED)
// (USB_CONFIG_ATTR_BUS_POWERED)
//	(USB_CONFIG_ATTR_REMOTE_WAKEUP|USB_CONFIG_ATTR_SELF_POWERED)
//	(USB_CONFIG_ATTR_REMOTE_WAKEUP|USB_CONFIG_ATTR_BUS_POWERED)

//! USB Device string definitions (Optional)
// #define  USB_DEVICE_MANUFACTURE_NAME      "Manufacture name"
// #define  USB_DEVICE_PRODUCT_NAME          "Product name"
// #define  USB_DEVICE_SERIAL_NAME           "12...EF"

/**
 * Device speeds support
 * Only Full speed is authorized on DFU ATMEL
 * Because FLIP supports only full speed
 * Also:
 * - low speed is too slow (endpoint 8 Bytes)
 * - high speed does not increase flash program speed
 * - high speed is not supported on custom board with bad USB layout
 * @{
 */
// No speed change possible
//@}

/**
 * USB Device Callbacks definitions (Optional)
 * @{
 */
// #define  UDC_VBUS_EVENT(b_vbus_high)      user_callback_vbus_action(b_vbus_high)
// extern void user_callback_vbus_action(bool b_vbus_high);
// #define  UDC_SOF_EVENT()                  user_callback_sof_action()
// extern void user_callback_sof_action(void);
// #define  UDC_SUSPEND_EVENT()              user_callback_suspend_action()
// extern void user_callback_suspend_action(void);
// #define  UDC_RESUME_EVENT()               user_callback_resume_action()
// extern void user_callback_resume_action(void);
//! Mandatory when USB_DEVICE_ATTR authorizes remote wakeup feature
// #define  UDC_REMOTEWAKEUP_ENABLE()        user_callback_remotewakeup_enable()
// extern void user_callback_remotewakeup_enable(void);
// #define  UDC_REMOTEWAKEUP_DISABLE()       user_callback_remotewakeup_disable()
// extern void user_callback_remotewakeup_disable(void);
//! When a extra string descriptor must be supported
//! other than manufacturer, product and serial string
// #define  UDC_GET_EXTRA_STRING()
//@}

//@}


/**
 * USB Interface Configuration
 * @{
 */
/**
 * Configuration of DFU interface
 * @{
 */
//! Interface callback definition
#define  UDI_DFU_ENABLE_EXT()             true
#define  UDI_DFU_DISABLE_EXT()

//! FLIP protocol version to use
#define  FLIP_PROTOCOL_VERSION   FLIP_PROTOCOL_VERSION_2
// Split erase is available since batchisp 1.2.5 to avoid USB protocol 2 error
#define  UDI_DFU_ATMEL_PROTOCOL_2_SPLIT_ERASE_CHIP
// Reduce the RAM used (1KB instead of 2KB), but the CODE increase of 80B
#define  UDI_DFU_SMALL_RAM
//@}
//@}


/**
 * USB Device Driver Configuration
 * @{
 */
//#define UDD_NO_SLEEP_MGR
//@}

//! The includes of classes and other headers must be done at the end of this file to avoid compile error
#include "udi_dfu_atmel_conf.h"

#endif // _CONF_USB_H_
