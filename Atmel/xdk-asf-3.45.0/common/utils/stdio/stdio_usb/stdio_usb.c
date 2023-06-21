/**
 * \file
 *
 * \brief USB CDC Standard I/O Serial Management.
 *
 * This module defines support routines for a stdio serial interface to the
 * Atmel Software Framework (ASF) common USB CDC service.
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


#include "stdio_usb.h"

static bool stdio_usb_interface_enable = false;

int stdio_usb_putchar (volatile void * unused, char data)
{
	/* A negative return value should be used to indicate that data
	 * was not written, but this doesn't seem to work with GCC libc.
	 */
	if (!stdio_usb_interface_enable) {
		return 0;  // -1
	}

	return udi_cdc_putc(data) ? 0 : -1;
}

void stdio_usb_getchar (void volatile * unused, char *data)
{
	/* A negative return value should be used to indicate that data
	 * was not read, but this doesn't seem to work with GCC libc.
	 */
	if (!stdio_usb_interface_enable) {
		*data = 0;  // -1
		return;
	}

	*data = (char)udi_cdc_getc();
}

bool stdio_usb_enable(void)
{
	stdio_usb_interface_enable = true;
	return true;
}

void stdio_usb_disable(void)
{
	stdio_usb_interface_enable = false;
}

void stdio_usb_init(void)
{
	stdio_base = NULL;
	ptr_put = stdio_usb_putchar;
	ptr_get = stdio_usb_getchar;

	/*
	 * Start and attach USB CDC device interface for devices with
	 * integrated USB interfaces.  Assume the VBUS is present if
	 * VBUS monitoring is not available.
	 */
	udc_start ();

#if defined(__GNUC__)
# if XMEGA
	// For AVR GCC libc print redirection uses fdevopen.
	fdevopen((int (*)(char, FILE*))(_write),(int (*)(FILE*))(_read));
# endif
# if UC3 || SAM
	// For AVR32 and SAM GCC
	// Specify that stdout and stdin should not be buffered.
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	// Note: Already the case in IAR's Normal DLIB default configuration
	// and AVR GCC library:
	// - printf() emits one character at a time.
	// - getchar() requests only 1 byte to exit.
# endif
#endif
}

