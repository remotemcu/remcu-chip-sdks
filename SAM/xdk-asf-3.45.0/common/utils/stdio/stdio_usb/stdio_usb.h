/**
 * \file
 *
 * \brief USB Standard I/O Serial Management.
 *
 * This file defines a useful set of functions for the Stdio Serial
 * interface on AVR devices.
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

#ifndef _stdio_usb_h_
#define _stdio_usb_h_

/**
 * \defgroup group_common_utils_stdio_stdio_usb USB/CDC Standard I/O (stdio)
 * \ingroup group_common_utils_stdio
 *
 * Standard I/O (stdio) management component that implements a stdio
 * USB CDC interface on AVR devices.
 *
 * \{
 */

#include <compiler.h>

#include <stdio.h>

#include <udc.h>
#include <udi_cdc.h>

extern int _write (char c, int *f);
extern int _read (int *f);


//! Pointer to the base of the USART module instance to use for stdio.
extern volatile void *volatile stdio_base;
//! Pointer to the external low level write function.
extern int (*ptr_put)(void volatile*, char);
//! Pointer to the external low level read function.
extern void (*ptr_get)(void volatile*, char*);

/*! \brief Sends a character with the USART.
 *
 * \param usart   Base address of the USART instance.
 * \param data    Character to write.
 *
 * \return Status.
 *   \retval  0  The character was written.
 *   \retval -1  The function timed out before the transmitter became ready.
 */
int stdio_usb_putchar (volatile void * usart, char data);

/*! \brief Waits until a character is received, and returns it.
 *
 * \param usart   Base address of the USART instance.
 * \param data    Data to read
 *
 * \return Nothing.
 */
void stdio_usb_getchar (void volatile * usart, char * data);

/*! \brief Enables the stdio in USB Serial Mode.
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
bool stdio_usb_enable(void);

/*! \brief Disables the stdio in USB Serial Mode.
 *
 * \return Nothing.
 */
void stdio_usb_disable(void);

/*! \brief Initializes the stdio in USB Serial Mode.
 *
 * \return Nothing.
 */
void stdio_usb_init(void);

/**
 * \}
 */

#endif  // _stdio_usb_h_
