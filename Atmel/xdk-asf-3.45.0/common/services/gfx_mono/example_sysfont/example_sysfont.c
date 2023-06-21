/**
 * \file
 *
 * \brief Example application for GFX Monochrome System Font (sysfont)
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
#include <asf.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is an example application for the \ref gfx_mono_font. It will print a
 * string, with line break, on the display; Hello World!\\r\\nI'm bored...".
 *
 * \section files Main Files
 * - \ref example_sysfont.c
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_st7565r.h or conf_ssd1306.h
 * - \ref conf_sysfont.h
 * - \ref conf_usart_spi.h
 *
 * \section device_info Device Info
 * All AVR devices can be used.
 * This example has been tested with the following setup:
 * - XMEGA-A3BU Xplained
 * - XMEGA-C3 Xplained
 *
 * \section description Description of the example application
 * The example application will upon power up display two text strings on the
 * display; "My name is XXXXXXXX!" "And I'm board...".
 *
 * \section dependencies Dependencies
 * Relevant module dependencies for this application are:
 * - \ref gfx_mono
 * - \ref gfx_mono_font
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for AVR. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 */

/**
 * \brief Main entry of example application
 */
int main(void)
{
	/**
	 * Starts off by initializing the system clock before configuring the
	 * board and the monochrome graphical system.
	 */
	board_init();
	sysclk_init();
	gfx_mono_init();

	/**
	 * After initialization the example will write the "Hello
	 * world!\\r\\nI'm board..." string to position 0, 0 on the display.
	 * Use the system font sysfont. Afterwards the system busy waits
	 * forever in a while true loop.
	 */
#if BOARD == XMEGA_A3BU_XPLAINED
	gfx_mono_draw_string("My name is\r\nXMEGA-A3BU Xplained!\r\nAnd I'm board...",
			0, 0, &sysfont);
#elif BOARD == XMEGA_C3_XPLAINED
	gfx_mono_draw_string("My name is\r\nXMEGA-C3 Xplained!\r\nAnd I'm board...",
			0, 0, &sysfont);
#else
#  error Unknow board.
#endif

	while (true) {
		/* Intentionally left empty. */
	}
}
