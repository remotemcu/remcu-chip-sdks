/**
 * \file
 *
 * \brief ISP configuration file.
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

#ifndef _CONF_ISP_H_
#define _CONF_ISP_H_

#include "parts.h"

#if !defined(__ASSEMBLER__) && !defined(__IAR_SYSTEMS_ASM__)
// This define may only be included from C files

#include "compiler.h"
#include "nvm.h"


// Bootloader Versions
// Example: Version 0x00 give 1.0.0 on batchisp log
// Example: Version 0x03 give 1.0.3 on batchisp log
// Example: Version 0x25 give 1.2.5 on batchisp log
#  define BOOTLOADER_VERSION   0x05

#  if (FLASH_SIZE<=0x10000) // FLASH <= 64KB
// If all memories (flash,eeprom,...) do not exceed 64KB.
// then the ISP interface can be optimized to save CODE.
#    define ISP_SMALL_MEMORY_SIZE
#  endif

#endif

// Definition of hardware condition to enter in ISP mode
#if XMEGA_A1U
# define ISP_PORT_DIR      PORTF_DIR
# define ISP_PORT_PINCTRL  PORTF_PIN5CTRL
# define ISP_PORT_IN       PORTF_IN
# define ISP_PORT_PIN      0
#elif (XMEGA_A3U || XMEGA_A3BU)
# define ISP_PORT_DIR      PORTE_DIR
# define ISP_PORT_PINCTRL  PORTE_PIN5CTRL
# define ISP_PORT_IN       PORTE_IN
# define ISP_PORT_PIN      5
#elif (XMEGA_A4U || XMEGA_C4)
# define ISP_PORT_DIR      PORTC_DIR
# define ISP_PORT_PINCTRL  PORTC_PIN3CTRL
# define ISP_PORT_IN       PORTC_IN
# define ISP_PORT_PIN      3
#elif XMEGA_B
# define ISP_PORT_DIR      PORTC_DIR
# define ISP_PORT_PINCTRL  PORTC_PIN6CTRL
# define ISP_PORT_IN       PORTC_IN
# define ISP_PORT_PIN      6
#elif XMEGA_C3
# define ISP_PORT_DIR      PORTF_DIR
# define ISP_PORT_PINCTRL  PORTF_PIN1CTRL
# define ISP_PORT_IN       PORTF_IN
# define ISP_PORT_PIN      1
#else
# error Unknow AVR Xmega part
#endif

#endif // _CONF_ISP_H_
