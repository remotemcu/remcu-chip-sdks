/**
 * \file
 *
 * \brief USB configuration file
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

#ifndef _CONF_USB_H_
#define _CONF_USB_H_

#include "compiler.h"

//! To reduce the code size, the interrupt register management from IAR is not used
#if defined(__ICCAVR32__)
#  include "intc.h"
#  undef  irq_register_handler
#  define irq_register_handler(func, int_num, int_lvl)                    \
	INTC_register_interrupt(&func, int_num,                                \
			TPASTE2(AVR32_INTC_INT, int_lvl))
#  undef  ISR
#  define ISR(func, int_grp, int_lvl)    \
	   __interrupt static void func (void)
#endif

//! To link service clock routines used by usb driver to specific clock management
#include "sysclk_auto.h"
#define  sysclk_enable_usb  sysclk_auto_enable_usb
#define  sysclk_disable_usb  sysclk_auto_disable_usb

/**
 * USB Device Configuration
 * @{
 */

//! Device definition (mandatory)
#define  USB_DEVICE_VENDOR_ID             USB_VID_ATMEL
#if UC3A0 || UC3A1
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_AT32UC3A
#define  USB_DEVICE_PRODUCT_NAME          "DFU AT32UC3A"
#elif UC3B
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_AT32UC3B
#define  USB_DEVICE_PRODUCT_NAME          "DFU AT32UC3B"
#elif UC3A3
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_AT32UC3A3
#define  USB_DEVICE_PRODUCT_NAME          "DFU AT32UC3A3"
#elif UC3C
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_AT32UC3C
#define  USB_DEVICE_PRODUCT_NAME          "DFU AT32UC3C"
#elif UC3D
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATUC3D
#define  USB_DEVICE_PRODUCT_NAME          "DFU AT32UC3D"
#elif UC3L3_L4
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATUCL3_L4
#define  USB_DEVICE_PRODUCT_NAME          "DFU UC3 L3U/L4U"
#else
#error Unknow DFU PID for this AVR part
#endif

#define  USB_DEVICE_MAJOR_VERSION         (BOOTLOADER_VERSION>>4)
#define  USB_DEVICE_MINOR_VERSION         (BOOTLOADER_VERSION&0x0F)
#define  USB_DEVICE_POWER                 100 // Consumption on Vbus line (mA)
#define  USB_DEVICE_MANUFACTURE_NAME      "ATMEL"
#define  USB_DEVICE_ATTR                  USB_CONFIG_ATTR_SELF_POWERED

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
#define  UDC_VBUS_EVENT(b_vbus_high)
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
//@}
//@}


/**
 * USB Device Driver Configuration
 * @{
 */
#define UDD_NO_SLEEP_MGR
//@}

//! The includes of classes and other headers must be done at the end of this file to avoid compile error
#include "udi_dfu_atmel_conf.h"
#include "main.h"
#include "conf_isp.h"   // Need to put bootloader version at USB device version

#endif // _CONF_USB_H_
