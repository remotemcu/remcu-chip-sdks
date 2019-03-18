/**
 * \file
 *
 * \brief USB Standard I/O (stdio) Example
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

/**
 * \mainpage
 *
 * \section intro Introduction
 * This example demonstrates how to configure a C-library Standard
 * I/O interface to the ASF common USB Device CDC service. The initialization
 * routines, along with board and clock configuration constants, illustrate how
 * to perform serial I/O via a Communication Device Class (CDC) device protocol
 *
 * \section files Main Files
 * - stdio_usb_example.c: the example application.
 * - conf_board.h: board configuration
 * - conf_clock.h: board configuration
 * - stdio_usb.h: Common USB CDC Standard I/O Implementation
 * - read.c : System implementation function used by standard library
 * - write.c : System implementation function used by standard library
 *
 * \section example_description Description of the example
 *   - Send message on USB CDC device to a Virtual Com Port.
 *   - Performs echo of any received character
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/design-centers/8-bit">Atmel AVR</A>.\n
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>

/**
 * \brief main function
 */
int main (void)
{
#if SAMD21 || SAMR21
	/* Initialize basic board support features.
	 * - Initialize system clock sources according to device-specific
	 *   configuration parameters supplied in a conf_clocks.h file.
	 * - Set up GPIO and board-specific features using additional configuration
	 *   parameters, if any, specified in a conf_board.h file.
	 */
	system_init();
#else
	/* Initialize basic board support features.
	 * - Initialize system clock sources according to device-specific
	 *   configuration parameters supplied in a conf_clock.h file.
	 * - Set up GPIO and board-specific features using additional configuration
	 *   parameters, if any, specified in a conf_board.h file.
	 */
	sysclk_init();
	board_init();
#endif

	// Initialize interrupt vector table support.
	irq_initialize_vectors();

	// Enable interrupts
	cpu_irq_enable();

	/* Call a local utility routine to initialize C-Library Standard I/O over
	 * a USB CDC protocol. Tunable parameters in a conf_usb.h file must be
	 * supplied to configure the USB device correctly.
	 */
	stdio_usb_init();

	// Get and echo characters forever.

	uint8_t ch;

	while (true) {

		scanf("%c",&ch); // get one input character

		if (ch) {
			printf("%c",ch); // echo to output
		}
	}
}
