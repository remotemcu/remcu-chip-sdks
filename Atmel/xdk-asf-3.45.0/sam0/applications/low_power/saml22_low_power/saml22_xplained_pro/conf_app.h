/**
 * \file
 *
 * \brief SAM L21 Xplained Pro Application Configuration.
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
 /**
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#ifndef CONF_APP_H_INCLUDED
#define CONF_APP_H_INCLUDED

#define CONF_EXT_WAKEUP_PIN   PIN_PC01A_EIC_EXTINT9
#define CONF_EXT_WAKEUP_PINMUX MUX_PC01A_EIC_EXTINT9

#define CONF_STDIO_USART          EDBG_CDC_MODULE
#define CONF_STDIO_MUX_SETTING    EDBG_CDC_SERCOM_MUX_SETTING
#define CONF_STDIO_PINMUX_PAD0    EDBG_CDC_SERCOM_PINMUX_PAD0
#define CONF_STDIO_PINMUX_PAD1    EDBG_CDC_SERCOM_PINMUX_PAD1
#define CONF_STDIO_PINMUX_PAD2    EDBG_CDC_SERCOM_PINMUX_PAD2
#define CONF_STDIO_PINMUX_PAD3    EDBG_CDC_SERCOM_PINMUX_PAD3
#define CONF_STDIO_BAUDRATE       38400

#define CONF_STDIO_PAD0_PIN PIN_PC24D_SERCOM4_PAD2
#define CONF_STDIO_PAD1_PIN PIN_PC25D_SERCOM4_PAD3

#define ACTIVE_MODE_PL0		'a'
#define ACTIVE_MODE_PL2		'b'
#define IDLE_MODE			'c'
#define STANDBY_MODE		'd'
#define BACKUP_MODE			'e'
#define OFF_MODE			'f'

#define UNUSED_GPIO_POWER_SAVE

//milli seconds
#define CONF_RTC_WAKEUP 5000

//comment the following DEBUG_ENABLE constant if we want to test the sleep mode individually without user menu on EDBG virtual COM port
#define DEBUG_ENABLE

//The 'TEST_X_MODE' constant is used only when DEBUG_ENABLE is not used (i.e when 'DEBUG_ENABLE' constant is commented)

//uncomment (only) one of the below sleep mode which we want to test 

//#define TEST_ACTIVE_PL0_MODE	'a'
//#define TEST_ACTIVE_PL2_MODE	'b'
//#define TEST_IDLE_MODE		'c'
//#define TEST_STANDBY_MODE		'd'
//#define TEST_BACKUP_MODE		'e'
//#define TEST_OFF_MODE			'f'
   
#endif
