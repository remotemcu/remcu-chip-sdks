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
#include "nvm.h"

/* Redefine USB interrupt vectors base address to safe code space */
# if defined(__GNUC__)
#   error GCC no supported when interrupt vectors space is optimized
/*
#   undef USB_BUSEVENT_vect
#   undef USB_TRNCOMPL_vect
#   undef USB_BUSEVENT_vect_num
#   undef USB_TRNCOMPL_vect_num
#   define USB_BUSEVENT_vect_num  1
#   define USB_BUSEVENT_vect      _VECTOR(1)
#   define USB_TRNCOMPL_vect_num  2
#   define USB_TRNCOMPL_vect      _VECTOR(2)
*/
# elif defined(__ICCAVR__)
#   undef USB_BUSEVENT_vect
#   undef USB_TRNCOMPL_vect
#   define USB_BUSEVENT_vect 0x0
#   define USB_TRNCOMPL_vect 0x4
# endif

// A reduce clock implementation is used to fit on bootloader 4KB
#if (FLASH_SIZE<=0x10000)
// Redirection of common services clock interface
# define sysclk_init sysclk_init_opt
# define sysclk_enable_usb sysclk_enable_usb_opt
# define sysclk_disable_usb sysclk_disable_usb_opt
	void sysclk_init_opt(void);
	void sysclk_enable_usb_opt(uint8_t freq);
	void sysclk_disable_usb_opt(void);
#endif

/**
 * USB Device Configuration
 * @{
 */

//! Device definition (mandatory)
#define  USB_DEVICE_VENDOR_ID             USB_VID_ATMEL
#if AVR8_PART_IS_DEFINED(ATxmega16A4U)
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATXMEGA16A4U
//#define  USB_DEVICE_PRODUCT_NAME        "DFU ATXMEGA16A4U" // Removed to save CODE
#elif AVR8_PART_IS_DEFINED(ATxmega32A4U)
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATXMEGA32A4U
//#define  USB_DEVICE_PRODUCT_NAME        "DFU ATXMEGA32A4U" // Removed to save CODE
#elif AVR8_PART_IS_DEFINED(ATxmega64A4U)
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATXMEGA64A4U
#define  USB_DEVICE_PRODUCT_NAME          "DFU ATXMEGA64A4U"
#elif AVR8_PART_IS_DEFINED(ATxmega128A4U)
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATXMEGA128A4U
#define  USB_DEVICE_PRODUCT_NAME          "DFU ATXMEGA128A4U"
#elif AVR8_PART_IS_DEFINED(ATxmega64A3U)
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATXMEGA64A3U
#define  USB_DEVICE_PRODUCT_NAME          "DFU ATXMEGA64A3U"
#elif AVR8_PART_IS_DEFINED(ATxmega128A3U)
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATXMEGA128A3U
#define  USB_DEVICE_PRODUCT_NAME          "DFU ATXMEGA128A3U"
#elif AVR8_PART_IS_DEFINED(ATxmega192A3U)
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATXMEGA192A3U
#define  USB_DEVICE_PRODUCT_NAME          "DFU ATXMEGA128A3U"
#elif AVR8_PART_IS_DEFINED(ATxmega256A3U)
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATXMEGA256A3U
#define  USB_DEVICE_PRODUCT_NAME          "DFU ATXMEGA256A3U"
#elif AVR8_PART_IS_DEFINED(ATxmega256A3BU)
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATXMEGA256A3BU
#define  USB_DEVICE_PRODUCT_NAME          "DFU ATXMEGA256A3BU"
#elif AVR8_PART_IS_DEFINED(ATxmega128A1U)
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATXMEGA128A1U
#define  USB_DEVICE_PRODUCT_NAME          "DFU ATXMEGA128A1U"
#elif AVR8_PART_IS_DEFINED(ATxmega64A1U)
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATXMEGA64A1U
#define  USB_DEVICE_PRODUCT_NAME          "DFU ATXMEGA64A1U"
#elif AVR8_PART_IS_DEFINED(ATxmega128B1)
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATXMEGA128B1
#define  USB_DEVICE_PRODUCT_NAME          "DFU ATXMEGA128B1"
#elif AVR8_PART_IS_DEFINED(ATxmega64B1)
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATXMEGA64B1
#define  USB_DEVICE_PRODUCT_NAME          "DFU ATXMEGA64B1"
#elif AVR8_PART_IS_DEFINED(ATxmega128B3)
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATXMEGA128B3
#define  USB_DEVICE_PRODUCT_NAME          "DFU ATXMEGA128B3"
#elif AVR8_PART_IS_DEFINED(ATxmega64B3)
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATXMEGA64B3
#define  USB_DEVICE_PRODUCT_NAME          "DFU ATXMEGA64B3"
#elif AVR8_PART_IS_DEFINED(ATxmega384C3)
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATXMEGA384C3
#define  USB_DEVICE_PRODUCT_NAME          "DFU ATXMEGA384C3"
#elif AVR8_PART_IS_DEFINED(ATxmega256C3)
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATXMEGA256C3
#define  USB_DEVICE_PRODUCT_NAME          "DFU ATXMEGA256C3"
#elif AVR8_PART_IS_DEFINED(ATxmega128C3)
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATXMEGA128C3
#define  USB_DEVICE_PRODUCT_NAME          "DFU ATXMEGA128C3"
#elif AVR8_PART_IS_DEFINED(ATxmega64C3)
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATXMEGA64C3
#define  USB_DEVICE_PRODUCT_NAME          "DFU ATXMEGA64C3"
#elif AVR8_PART_IS_DEFINED(ATxmega32C4)
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATXMEGA32C4
//#define  USB_DEVICE_PRODUCT_NAME        "DFU ATXMEGA32C4" // Removed to save CODE
#elif AVR8_PART_IS_DEFINED(ATxmega16C4)
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_DFU_ATXMEGA16C4
//#define  USB_DEVICE_PRODUCT_NAME        "DFU ATXMEGA16C4" // Removed to save CODE
#else
#error Unknow DFU PID for this AVR part
#endif

#define  USB_DEVICE_MAJOR_VERSION         (BOOTLOADER_VERSION>>4)
#define  USB_DEVICE_MINOR_VERSION         (BOOTLOADER_VERSION&0x0F)
#define  USB_DEVICE_POWER                 100 // Consumption on Vbus line (mA)
#if (FLASH_SIZE>0x10000) // Optimize CODE space (Boot = 4KB)
#define  USB_DEVICE_MANUFACTURE_NAME      "ATMEL"
#endif
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
#define  UDC_VBUS_EVENT(b_vbus_high)      // NO VBUS EVENT on XMEGA
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
#if (FLASH_SIZE<0x8000) // Optimize RAM space (RAM = 2KB)
#  define  UDI_DFU_SMALL_RAM	// Reduce RAM (1KB) but increase CODE (72B)
#endif
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
#include "conf_isp.h"   // Need to put bootloader version at USB device version

#endif // _CONF_USB_H_
