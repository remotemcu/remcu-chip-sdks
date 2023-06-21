/**
 * \file
 *
 * \brief Example application for GFX Monochrome System Font (sysfont)
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
#include <asf.h>
/**
 * \page asfdoc_common2_gfx_mono_sysfont_example GFX Mono Font Example
 *
 * \section asfdoc_common2_sysfont_example_intro Introduction
 * This is an example application for the \ref asfdoc_common2_gfx_mono_font. It will print a
 * string, with line break, on the screen and scroll it.
 *
 * \section files Main Files
 * - \ref example_sysfont.c
 * - \ref conf_board.h
 * - \ref conf_clocks.h
 * - \ref conf_ssd1306.h
 * - \ref conf_sysfont.h
 *
 * \section asfdoc_common2_sysfont_example_device_info Device Info
 * This example has been tested with the following setup:
 * - SAM D20 Xplained Pro
 * - SAM D21 Xplained Pro
 * - SAM R21 Xplained Pro
 * - SAM D11 Xplained Pro
 * - SAM L21 Xplained Pro
 * - SAM L22 Xplained Pro
 *
 * \section asfdoc_common2_sysfont_example_description Description of the example application
 * The example application will upon power up display several text strings on the
 * display; "PASSION...".
 *
 * \section asfdoc_common2_sysfont_example_dependencies Dependencies
 * Relevant module dependencies for this application are:
 * - \ref asfdoc_common2_gfx_mono_font
 *
 * \section asfdoc_common2_sysfont_example_compinfo Compilation info
 * This software was written for the GNU GCC and IAR. Other compilers
 * may or may not work.
 *
 * \section asfdoc_common2_sysfont_example_contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 */

#define LINES 8

char string[LINES][24] = {
	{"          PASSION   \r\n"},
	{"    INTEGRITY       \r\n"},
	{"        TEAMWORK    \r\n"},
	{"   ACHIEVEMENT      \r\n"},
	{" ACCOUNTABILITY     \r\n"},
	{"                    \r\n"},
	{"                    \r\n"},
	{"                    \r\n"},
};

/**
 * \brief Main entry of example application
 */
int main(void)
{
	/**
	 * Starts off by initializing the system clock before configuring the
	 * board and the monochrome graphical system.
	 */
	system_init();
	gfx_mono_init();

	uint8_t start_line_address = 0;
	uint8_t scroll = 0;
	uint32_t line = 0;

	/**
	 * After initialization the example will write the Star Wars opening scrolling text.
	 * Use the system font sysfont. Afterwards the text will be scrolled forever.
	 */

	while (true) {
		if (++start_line_address%8 == 0) {
			scroll = 1;
			gfx_mono_draw_string(string[line%LINES],0, ((line)%8)*8, &sysfont);
			line++;
		} else if (start_line_address % 7 != 0) {
			delay_ms(100);
		}

		if ( scroll != 0 ) {
			ssd1306_set_display_start_line_address(start_line_address-8);
		} else {
			gfx_mono_draw_string(string[line%LINES],0, ((line)%8)*8, &sysfont);
			line++;
		}
	}
}
