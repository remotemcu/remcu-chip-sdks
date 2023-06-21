/**
 * \file
 *
 * \brief SAM4C-EK board configuration.
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

#ifndef CONF_BOARD_H_INCLUDED
#define CONF_BOARD_H_INCLUDED

/* Keep watchdog at board initialization (not disable it) */
//#define CONF_BOARD_KEEP_WATCHDOG_AT_INIT

/* Configure UART0 pins */
#define CONF_BOARD_UART_CONSOLE
#define CONF_BOARD_UART0

/* Configure LCD backlight */
//#define CONF_BOARD_UART_CONSOLE

/* Configure PWM LED0 pin */
//#define CONF_BOARD_PWM_LED0

/* Configure PWM LED1 pin */
//#define CONF_BOARD_PWM_LED1

/* Configure PWM LED2 pin */
//#define CONF_BOARD_PWM_LED2

/* Configure SPI0 pins */
#define CONF_BOARD_SPI0
#define CONF_BOARD_SPI0_NPCS0

/* Configure SPI1 pins */
//#define CONF_BOARD_SPI1
//#define CONF_BOARD_SPI0_NPCS1

/* Configure TWI0 pins */
//#define CONF_BOARD_TWI0

/* Configure TWI0 pins for AT30TSE */
//#define CONF_BOARD_AT30TSE

/* Configure TWI1 pins */
//#define CONF_BOARD_TWI1

/* Configure USART pins */
//#define CONF_BOARD_USART_RXD
//#define CONF_BOARD_USART_TXD
//#define CONF_BOARD_USART_CTS
//#define CONF_BOARD_USART_RTS
//#define CONF_BOARD_USART_SCK

/* Configure IrDA transceiver shutdown pin */
//#define CONF_BOARD_TFDU4300_SD

/* Configure RS485 transceiver RE pin */
//#define CONF_BOARD_ADM3485_RE

/* Configure ISO7816 card reset pin */
//#define CONF_BOARD_ISO7816_RST

/* Configure ISO7816 interface TXD & SCK pin */
//#define CONF_BOARD_ISO7816

/* Configure ADC pins */
//#define CONF_BOARD_ADC

/* Configure PPLC pins */
#define CONF_BOARD_PPLC

#endif /* CONF_BOARD_H_INCLUDED */
