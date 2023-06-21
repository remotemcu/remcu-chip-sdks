/**
 * \file
 *
 * \brief Board configuration.
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

#ifndef CONF_BOARD_H_INCLUDED
#define CONF_BOARD_H_INCLUDED

/* Configure UART pins */
#define CONF_BOARD_UART_CONSOLE

/* Configure ADC example pins */
#define CONF_BOARD_ADC

/*
 * LED pins are not configured for PWM function here.
 * Because those LED pins are enabled for PIO function by default.
 * You can enable them according to application.
 */
/* Configure PWM LED0 pin */
//#define CONF_BOARD_PWM_LED0

/* Configure PWM LED1 pin */
//#define CONF_BOARD_PWM_LED1

/* Configure PWM LED2 pin */
//#define CONF_BOARD_PWM_LED2

/* Configure SPI pins */
#define CONF_BOARD_SPI
#define CONF_BOARD_SPI_NPCS0
//#define CONF_BOARD_SPI_NPCS1
//#define CONF_BOARD_SPI_NPCS2
//#define CONF_BOARD_SPI_NPCS3

/*
 * USART pins are configured as basic serial port by default.
 * You can enable other pins according application.
 */
/* Configure USART RXD pin */
#define CONF_BOARD_USART_RXD

/* Configure USART TXD pin */
#define CONF_BOARD_USART_TXD

/* Configure USART CTS pin */
//#define CONF_BOARD_USART_CTS

/* Configure USART RTS pin */
//#define CONF_BOARD_USART_RTS

/* Configure USART synchronous communication SCK pin */
//#define CONF_BOARD_USART_SCK

/* Configure ADM33312 enable pin */
#define CONF_BOARD_ADM3312_EN

/* Configure IrDA transceiver shutdown pin */
//#define CONF_BOARD_TFDU4300_SD

/* Configure RS485 transceiver RE pin */
//#define CONF_BOARD_ADM3485_RE

/* Configure LCD EBI pins */
#define CONF_BOARD_ILI9325

/* Configure Backlight control pin */
#define CONF_BOARD_AAT3155

/* Configure Touchscreen SPI pins */
#define CONF_BOARD_ADS7843

#endif /* CONF_BOARD_H_INCLUDED */
