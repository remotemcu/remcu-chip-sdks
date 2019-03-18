/**
 * \file
 *
 * \brief This file defines a useful set of functions for the Serial interface on 
 * AVR MEGARF devices.
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
#ifndef _USART_SERIAL_H_
#define _USART_SERIAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "compiler.h"
#include "sysclk.h"
#include "status_codes.h"
#include "usart_megarf.h"

/*! \name Serial Management Configuration
 */
/* ! @{ */
#include "conf_usart_serial.h"
/* ! @} */

typedef usart_rs232_options_t usart_serial_options_t;

typedef USART_t *usart_if;

/*! \brief Initializes the Usart in master mode.
 *
 * \param usart       Base address of the USART instance.
 * \param options     Options needed to set up RS232 communication (see \ref
 * usart_serial_options_t).
 *
 * \retval true if the initialization was successful
 * \retval false if initialization failed (error in baud rate calculation)
 */
static inline bool usart_serial_init(usart_if usart, const
		usart_serial_options_t *options)
{
	/* USART options. */
	usart_rs232_options_t usart_rs232_options;
	usart_rs232_options.charlength   = options->charlength;
	usart_rs232_options.paritytype   = options->paritytype;
	usart_rs232_options.stopbits     = options->stopbits;
	usart_rs232_options.baudrate     = options->baudrate;

	if (usart_init_rs232(usart, &usart_rs232_options)) {
		return true;
	} else {
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
static inline status_code_t usart_serial_putchar(usart_if usart, uint8_t c)
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
extern status_code_t usart_serial_write_packet(usart_if usart,
		const uint8_t *data, size_t len);

/**
 * \brief Receive a sequence of bytes from USART device
 *
 * \param usart  Base address of the USART instance.
 * \param data   Data buffer to write
 * \param len    Length of data
 *
 */
extern status_code_t usart_serial_read_packet(usart_if usart, uint8_t *data,
		size_t len);

#ifdef __cplusplus
}
#endif
		
#endif  /* _USART_SERIAL_H_ */
