/*
 * \file
 *
 * \brief utility module for ATSHA204 examples
 *
 * This file contains the main function and some helper functions.
 *
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

#include <string.h>
#include <stdio.h>
#include "asf.h"
#include "compiler.h"
#include "preprocessor.h"
#include "sha204_example_log.h"
#include "serial.h"
#include "conf_usart_serial.h"


void usart_write_crlf(void);
uint8_t convert_nibble_to_hexascii(uint8_t nibble);


/** 
 * \brief This function initializes the logging hardware.
 * 
 */
void log_init(void)
{
	usart_rs232_options_t USART_SERIAL_OPTIONS = {
		.baudrate = USART_SHA204_BAUDRATE,
		.charlength = USART_SHA204_CHAR_LENGTH,
		.paritytype = USART_SHA204_PARITY,
		.stopbits = USART_SHA204_STOP_BIT
	};
	// Initialize the serial port for CDC communication.
	usart_serial_init(USART_SHA204, &USART_SERIAL_OPTIONS);
}


/** \brief This function sends a carriage return and linefeed over USART.
 */
void usart_write_crlf(void)
{
	usart_serial_write_packet(USART_SHA204, (uint8_t *) "\r\n", 2);
}


/** \brief This function converts a nibble to Hex-ASCII.
 * \param[in] nibble nibble value to be converted
 * \return ASCII value
**/
uint8_t convert_nibble_to_hexascii(uint8_t nibble)
{
    nibble &= 0x0F;
    if (nibble <= 0x09 )
        nibble += '0';
    else
        nibble += ('A' - 10);
    return nibble;
}


/** 
 * \brief This function logs the title of a SHA204 transaction.
 * \param[in] title pointer to title string
 */
void log_sha204_title(char *title)
{
	usart_write_crlf();
	usart_serial_write_packet(USART_SHA204, (uint8_t *) title, strlen(title));
	usart_write_crlf();
}


/** 
 * \brief This function logs rx or tx data as hex-ascii.
 * \param[in] length number of characters
 * \param[in] buffer pointer to data
 * \param[in] is_rx true if rx buffer, false if tx_buffer is logged
 */
void log_sha204(uint8_t length, uint8_t *buffer, bool is_rx)
{
	uint8_t i;
	uint8_t nibble;
	
	usart_serial_write_packet(USART_SHA204, (uint8_t *) (is_rx ? "r" : "t"), 1);
	usart_serial_write_packet(USART_SHA204, (uint8_t *) "x: ", 3);
	for (i = 0; i < length; i++) {
		nibble = convert_nibble_to_hexascii(buffer[i] >> 4);
		usart_putchar(USART_SHA204, nibble);
		nibble = convert_nibble_to_hexascii(buffer[i] & 0x0F);
		usart_putchar(USART_SHA204, nibble);
		usart_putchar(USART_SHA204, ' ');
	}
	usart_write_crlf();
}
