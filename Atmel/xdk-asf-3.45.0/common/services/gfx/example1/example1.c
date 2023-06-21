/**
 * \file
 *
 * \brief Graphic library example application
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

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is an example application for the \ref gfx_group.
 * It will output all graphic primitives to a connected LCD screen.
 * It will also draw a color palette as well as the Atmel logo.
 *
 * \section files Main Files
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_spi.h
 * - \ref example1.c
 * - \ref atmel_logo.h
 * - \ref smiley.h
 *
 * \section device_info Device Info
 * This example has been tested with the following setup:
 * - UC3-A3 Xplained with the mXT143E Xplained
 * - UC3-L0 Xplained with the mXT143E Xplained
 * - XMEGA-A1 Xplained with the mXT143E Xplained
 * - XMEGA-B1 Xplained with the mXT143E Xplained
 * - XMEGA-A3BU Xplained with the mXT143E Xplained
 * - SAM4S Xplained with the mXT143E Xplained
 * - SAMV71 Xplained Ultra with the mXT143E Xplained
 * - SAME70 Xplained with the mXT143E Xplained
 *
 * \section exampledescription Description of the example
 * This example will demonstrate all the graphic primitives available in the
 * graphics service on a connected LCD panel. It steps down the y-axis while
 * drawing the different primitives from left to right on the x-axis.
 * Finally it will display an Atmel logo centered at the bottom of the screen.
 *
 * \section dependencies Dependencies
 * Relevant module dependencies for this application are:
 * - \ref gfx_group
 *
 * \section Usage
 *
 * -# Connect mXT143E Xplained to EXT2 on SAME70 Xplained Pro Kit using 20 pin connector.
 * -# Build the program and download it into the evaluation board.
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for AVR. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <board.h>
#include <sysclk.h>
#include "asf.h"

/* Include bitmaps */
#include "smiley.h"
#include "atmel_logo.h"

#define STEP 20
#define SPACING 10
#define GAP (STEP + SPACING)

/* Comment this out for portrait mode */
#define LANDSCAPE_MODE

const gfx_color_t color_table[] =      {GFX_COLOR_BLUE, GFX_COLOR_GREEN,
					GFX_COLOR_RED, GFX_COLOR_CYAN,
					GFX_COLOR_MAGENTA, GFX_COLOR_YELLOW};

const char example_string[] = "Atmel Graphical Library GFX Service Test";

/**
 * \brief main example code
 *
 * The main function will draw all the graphic primitives from the graphic
 * library on a line from left to right (incrementing x) and repeat this
 * from bottom to top with varying colors (incrementing y). Below the figures
 * it draws the Atmel logo centered on the screen.
 *
 */
int main(void)
{
	uint8_t color_table_index = 0;
	uint16_t y, color;
	uint8_t xoff = 0;

	board_init();
	sysclk_init();

	gfx_init();

#ifdef LANDSCAPE_MODE
	gfx_set_orientation(GFX_SWITCH_XY | GFX_FLIP_Y);
#endif

	/* Fill the whole screen with the background color */
	gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(),
			GFX_COLOR_WHITE);

	/* Write center-aligned text string to the top of the display */
	gfx_draw_string_aligned(example_string,
			gfx_get_width() / 2, 2, &sysfont,
			GFX_COLOR_TRANSPARENT, GFX_COLOR_RED,
			TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);

	/* We move down the screen with STEP size increments */
	for (y = STEP; y < (gfx_get_height() - atmel_logo.height - STEP);
			y += STEP) {

		/* Generate a color that increments along with the Y coordinate */
		color = color_table[color_table_index++];
		color_table_index %= sizeof(color_table) / sizeof(color_table[0]);

		/* set X offset so that the pattern is centered */
		xoff = (gfx_get_width() - (7 * GAP)) / 2;

		/* Draw a filled circle with radius of 10 */
		gfx_draw_filled_circle(xoff, y + 10, 10, color, GFX_WHOLE);

		xoff += GAP;

		/* Draw box with cross to the right of the filled circles */
		gfx_draw_horizontal_line(xoff, y, STEP, color);
		gfx_draw_horizontal_line(xoff, y + STEP, STEP, color);
		gfx_draw_vertical_line(xoff, y, STEP, color);
		gfx_draw_vertical_line(xoff + STEP, y, STEP, color);
		gfx_draw_line(xoff, y, xoff + STEP, y + STEP, color);
		gfx_draw_line(xoff, y + STEP, xoff + STEP, y, color);

		xoff += GAP;

		/* even better, use a rectangle to make box instead */
		gfx_draw_rect(xoff, y, STEP, STEP, color);

		xoff += GAP;

		/* filled rectangles */
		gfx_draw_filled_rect(xoff, y, STEP, STEP, color);

		xoff += GAP + SPACING;

		/* circles that are not filled */
		gfx_draw_circle(xoff, y + 10, 10, color, GFX_WHOLE);

		xoff += GAP;

		/* Draw a smiley bitmap */
		gfx_draw_bitmap(&smiley, xoff, y);
	}

	xoff += GAP;

	/* Draw a color palette at the right of the screen */
	uint16_t start_pos = xoff;
	uint8_t r, g, b;

	/* reset y to the top of the screen */
	y = STEP;
	for (r = 0; r < 32; r += 4) {
		for (g = 0; g < 64; g += 4) {
			for (b = 0; b < 32; b += 4) {
				/* The gfx_color function expect 8-bit color
				 * values, so we make the color values 8-bit
				 * before passing them.
				 */
				gfx_draw_pixel(xoff++, y,
						gfx_color((r << 3), (g << 2), (b << 3)));
				if (xoff >= start_pos + 8) {
					xoff = start_pos;
					y++;
				}
			}
		}
	}

	/* Draw the Atmel logo (186x85 pixels) at the bottom of the screen */
	gfx_draw_bitmap(&atmel_logo, (gfx_get_width() - atmel_logo.width) / 2,
			gfx_get_height() - atmel_logo.height);

	while (true) {
		/* Intentionally blank to halt execution */
	}
}
