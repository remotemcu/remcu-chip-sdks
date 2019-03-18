/**
 * \file
 *
 * \brief HX8347A display controller driver Example
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
 * This simple example shows how to use the \ref hx8347a_group for interfacing
 * the HX8347A display controller.
 *
 * \section files Main files:
 * - hx8347a_example.c: The main example file
 * - conf_hx8347a.h: configuration file for the driver
 * - conf_board.h: configuration for the board
 * - conf_clock.h: configuration for the device clocks
 * - conf_usart_spi.h or conf_spi_master.h depending on which hardware module is
 * used for communicating with the controller
 *
 * \section apiinfo HX8347A low level driver API
 * The HX8347A low level driver API can be found \ref hx8347a_group "here".
 *
 * \section deviceinfo Device Info
 * All devices with some sort of SPI interface, e.g. SPI or USART in SPI mode.
 * \note a Parallel interface is also possible, but is currently not supported
 * by any standard Atmel hardware, hence the driver does not support this.
 *
 * \section exampledescription Description of the example
 * This example show how to use the functions provided by the low level driver
 * to draw very simple graphics to the screen.
 *
 * First it uses the function \ref hx8347a_duplicate_pixel to draw a color to
 * the screen 20 times. Then it uses \ref hx8347a_copy_pixels_to_screen to copy
 * a 40 x 40 single color pixmap to the screen at different locations.
 *
 * For any advanced drawing of graphics please use the higher level GFX drivers.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for AVR.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/">Microchip</A>.\n
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>

/** Table of primary and secondary display pixel colors */
const hx8347a_color_t color_table[] = {
	HX8347A_COLOR(0, 0, 255), HX8347A_COLOR(0, 255, 0),
	HX8347A_COLOR(255, 0, 0), HX8347A_COLOR(255, 255, 0),
	HX8347A_COLOR(255, 0, 255), HX8347A_COLOR(0, 255, 255)};

/** Number of colors stored in the \ref color_table array */
#define COLOR_TABLE_SIZE           (sizeof(color_table) / sizeof(color_table[0]))

/** Number of pixels for full screen */
#define TOTAL_PIXELS ((uint32_t)HX8347A_DEFAULT_WIDTH * HX8347A_DEFAULT_HEIGHT)

/* Create an array to hold a 40 x 40 bitmap */
hx8347a_color_t bitmap[1600];

/* Pointer to the location in the array */
uint16_t bitmap_ptr = 0;

/**
 * \brief Main application
 */
int main(void)
{
	uint16_t x, y;
	uint8_t color_index;
	
	board_init();
	sysclk_init();

	/* Make sure to initialize the display controller */
	hx8347a_init();

	/* Turn on the back light */
	hx8347a_backlight_on();

	hx8347a_set_top_left_limit(0, 0);
	hx8347a_set_bottom_right_limit(HX8347A_DEFAULT_WIDTH, HX8347A_DEFAULT_HEIGHT);

	/* Draw colors to the screen, filling it */
	for (color_index = 0; color_index < COLOR_TABLE_SIZE; color_index++)
	{
		hx8347a_set_top_left_limit(0, 0);
		hx8347a_set_bottom_right_limit(HX8347A_DEFAULT_WIDTH, HX8347A_DEFAULT_HEIGHT);

		hx8347a_duplicate_pixel(color_table[color_index], TOTAL_PIXELS);
	}

	/* Draw bands of colors to the screen, showing all colors at once */
	for (uint8_t step = 1; step < 10; step++)
	{
		for (y = 0; y < 320 / step; y++)
		{
			hx8347a_set_top_left_limit(0, y * step);
			hx8347a_duplicate_pixel(color_table[y % COLOR_TABLE_SIZE],
					(uint32_t)HX8347A_DEFAULT_WIDTH * step);
		}
	}
	
	/* Clear display to black */
	hx8347a_set_top_left_limit(0, 0);
	hx8347a_set_bottom_right_limit(HX8347A_DEFAULT_WIDTH, HX8347A_DEFAULT_HEIGHT);	
	hx8347a_duplicate_pixel(HX8347A_COLOR(0, 0, 0), TOTAL_PIXELS);

	while (true) {
		/* Load the bitmap with a new color */
		for (bitmap_ptr = 0; bitmap_ptr < 1600; bitmap_ptr++) {
			bitmap[bitmap_ptr] = color_table[color_index % COLOR_TABLE_SIZE];
		}
		
		color_index++;
		
		for (x = 0; x < 240; x = x + 40) {
			for (y = 0; y < 320; y = y + 5) {
				/* Clear the last drawn area */
				hx8347a_set_top_left_limit(x, y - 5);
				hx8347a_set_bottom_right_limit(x + 40, y + 5);
				hx8347a_duplicate_pixel(HX8347A_COLOR(0, 0, 0), 205);

				/* Draw the moved pixmap */
				hx8347a_set_top_left_limit(x, y);
				hx8347a_set_bottom_right_limit(x + 40, y + 40);
				hx8347a_copy_pixels_to_screen(bitmap, 1600);
			}	
		}	
	}
}
