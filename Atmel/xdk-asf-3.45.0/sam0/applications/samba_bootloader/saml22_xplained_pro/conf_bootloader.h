/**
 * \file
 *
 * \brief Bootloader specific configuration.
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

#ifndef CONF_BOOTLOADER_H_INCLUDED
#define CONF_BOOTLOADER_H_INCLUDED

#include "conf_board.h"

#define APP_START_ADDRESS          0x00006000
#define BOOT_LED                   LED0_PIN
#define BOOT_LOAD_PIN              SW0_PIN
#define GPIO_BOOT_PIN_MASK         (1U << (BOOT_LOAD_PIN & 0x1F))

#define BOOT_USART_MODULE          EDBG_CDC_MODULE
#define BOOT_USART_BAUDRATE        115200
#define BOOT_USART_MUX_SETTINGS    EDBG_CDC_SERCOM_MUX_SETTING
#define BOOT_USART_PAD2            EDBG_CDC_SERCOM_PINMUX_PAD2
#define BOOT_USART_PAD3            EDBG_CDC_SERCOM_PINMUX_PAD3
#define BOOT_USART_GCLK_SOURCE     GCLK_GENERATOR_0

#define APP_START_PAGE             (APP_START_ADDRESS / FLASH_PAGE_SIZE)

/* DEBUG LED output enable/disable */
#define DEBUG_ENABLE               false

#endif /* CONF_BOOTLOADER_H_INCLUDED */
