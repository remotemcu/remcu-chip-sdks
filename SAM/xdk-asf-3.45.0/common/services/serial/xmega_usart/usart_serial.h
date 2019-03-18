/**
 * \file
 *
 * This file defines a useful set of functions for the Serial interface on AVR
 * XMEGA devices.
 *
 * Copyright (c) 2009-2018 Microchip Technology Inc. and its subsidiaries.
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
#ifndef _USART_SERIAL_H_
#define _USART_SERIAL_H_

#include "compiler.h"
#include "sysclk.h"
#include "status_codes.h"
#include "usart.h"

/*! \name Serial Management Configuration
 */
//! @{
#include "conf_usart_serial.h"
//! @}

typedef usart_rs232_options_t usart_serial_options_t;

typedef USART_t *usart_if;

/*! \brief Initializes the Usart in master mode.
 *
 * \param usart       Base address of the USART instance.
 * \param options     Options needed to set up RS232 communication (see \ref usart_serial_options_t).
 *
 * \retval true if the initialization was successful
 * \retval false if initialization failed (error in baud rate calculation)
 */
static inline bool usart_serial_init(usart_if usart, const
		usart_serial_options_t *options)
{
	// USART options.
	usart_rs232_options_t usart_rs232_options;
	usart_rs232_options.charlength   = options->charlength;
	usart_rs232_options.paritytype   = options->paritytype;
	usart_rs232_options.stopbits     = options->stopbits;
	usart_rs232_options.baudrate     = options->baudrate;

#ifdef USARTC0
	if((uint16_t)usart == (uint16_t)&USARTC0) {
		sysclk_enable_module(SYSCLK_PORT_C,PR_USART0_bm);
	}
#endif
#ifdef USARTC1
	if((uint16_t)usart == (uint16_t)&USARTC1) {
		sysclk_enable_module(SYSCLK_PORT_C,PR_USART1_bm);
	}
#endif
#ifdef USARTD0
	if((uint16_t)usart == (uint16_t)&USARTD0) {
		sysclk_enable_module(SYSCLK_PORT_D,PR_USART0_bm);
	}
#endif
#ifdef USARTD1
	if((uint16_t)usart == (uint16_t)&USARTD1) {
		sysclk_enable_module(SYSCLK_PORT_D,PR_USART1_bm);
	}
#endif
#ifdef USARTE0
	if((uint16_t)usart == (uint16_t)&USARTE0) {
		sysclk_enable_module(SYSCLK_PORT_E,PR_USART0_bm);
	}
#endif
#ifdef USARTE1
	if((uint16_t)usart == (uint16_t)&USARTE1) {
		sysclk_enable_module(SYSCLK_PORT_E,PR_USART1_bm);
	}
#endif
#ifdef USARTF0
	if((uint16_t)usart == (uint16_t)&USARTF0) {
		sysclk_enable_module(SYSCLK_PORT_F,PR_USART0_bm);
	}
#endif
#ifdef USARTF1
	if((uint16_t)usart == (uint16_t)&USARTF1) {
		sysclk_enable_module(SYSCLK_PORT_F,PR_USART1_bm);
	}
#endif
	if (usart_init_rs232(usart, &usart_rs232_options)) {
		return true;
	}
	else {
		return false;
	}
}

/*! \brief Sends a character with the USART.
 *
 * \param usart   Base address of the USART instance.
 * \param c       Character to write.
 *
 * \return Status code
 */
static inline enum status_code usart_serial_putchar(usart_if usart, uint8_t c)
{
	return usart_putchar(usart, c);
}
/*! \brief Waits until a character is received, and returns it.
 *
 * \param usart   Base address of the USART instance.
 * \param data   Data to read
 *
 */
static inline void usart_serial_getchar(usart_if usart, uint8_t *data)
{
	*data = usart_getchar(usart);
}

/**
 * \brief Send a sequence of bytes to USART device
 *
 * \param usart  Base address of the USART instance.
 * \param data   Data buffer to read
 * \param len    Length of data
 *
 */
extern status_code_t usart_serial_write_packet(usart_if usart, const uint8_t *data, size_t len);

/**
 * \brief Receive a sequence of bytes from USART device
 *
 * \param usart  Base address of the USART instance.
 * \param data   Data buffer to write
 * \param len    Length of data
 *
 */
extern status_code_t usart_serial_read_packet(usart_if usart, uint8_t *data, size_t len);

#endif  // _USART_SERIAL_H_
