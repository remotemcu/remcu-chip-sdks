/**
 * \file
 *
 * \brief SAM4L-EK board configuration template
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
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef CONF_BOARD_H_INCLUDED
#define CONF_BOARD_H_INCLUDED

/* Keep watchdog at board initialization */
//#define CONF_BOARD_KEEP_WATCHDOG_AT_INIT

/* Initialize the USART pins for the RS485 interface */
#define CONF_BOARD_RS485

/* Initialize the push button PB0 as an External Interrupt pin */
#define CONF_BOARD_EIC

/* Initialize the LCD Backlight */
#define CONF_BOARD_BL

/* Initialize the SAM4L pins for the USB SAM4L plug */
#define CONF_BOARD_USB_PORT
#define CONF_BOARD_USB_ID_DETECT           /* ID detect enabled,  uncomment it if jumper PB05/USB set */
#define CONF_BOARD_USB_VBUS_CONTROL        /* Host VBUS control enabled,  uncomment it if jumper PC08/USB set */
#define CONF_BOARD_USB_VBUS_ERR_DETECT     /* Host VBUS error detect NOT enabled,  uncomment it if jumper PC07/USB set */

/* Initialize the USART pins for the COM PORT interface with the JLink OB
module that acts as a USB CDC gateway over the USB JLink plug. */
#define CONF_BOARD_COM_PORT

/* Initialize the USART pins that interface with the Board Monitor(BM) */
#define CONF_BOARD_BM_USART

/* Initialize the SPI pins for use with the on-board serial flash or with the
 * WIRELESS connector or with the Sensors Xplained extension board. */
#define CONF_BOARD_SPI

/* Initialize the SPI CS for the WIRELESS connector. */
#define CONF_BOARD_SPI_NPCS0

/* Initialize the SPI CS for the on-board serial flash. */
#define CONF_BOARD_SPI_NPCS2

/* Initialize the SPI CS for the Sensors Xplained extension board. */
#define CONF_BOARD_SPI_NPCS3

/* Initialize the DACC VOUT pin */
#define CONF_BOARD_DACC_VOUT

#endif // CONF_BOARD_H_INCLUDED
