/**
 * \file
 *
 * \brief Screen dump example
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
 * This simple example shows how to use the \ref gfx_mono_screen_dump
 * for dumping the LCD screen in XPM file format trough the USART.
 *
 * \section files Main files:
 * - example_screen_dump.c: the example itself.
 * - conf_st7565r.h: configuration of the ST7565R controller and interface
 * - conf_board.h: configuration for the board
 * - conf_clock.h: configuration for the clocks used in the device
 * - interface configuration files.
 *
 * \section apiinfo XPM Screen dump API
 * The screen dump service API can be found
 * \ref gfx_mono_screen_dump "here".
 *
 * \section deviceinfo Device Info
 * All AVR devices with a USART can be used. There is no need for the physical
 * LCD to be present to use this function. As this function will only rely on a
 * framebuffer. If using the ST7565R LCD in serial mode a local framebuffer will
 * always be created due to that one can not read data back from the LCD.
 *
 * \section exampledescription Description of the example
 * The phantom display is initialized and different gfx functions are used to
 * produce an "image" which is written to the LCD screen (if present) and at the
 * end the entire screen buffer is dumped trough the USART using the XPM image
 * file format.
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
#include <board.h>
#include <sysclk.h>
#include <gfx_mono.h>
#include <gfx_mono_screen_dump.h>

uint8_t smiley_data[16] = { 0x3C, 0x42, 0x95, 0xA1, 0xA1, 0x95, 0x42, 0x3C,
		0x3C, 0x42, 0x95, 0xA1, 0xA1, 0x95, 0x42, 0x3C};

int main(void){

	struct gfx_mono_bitmap smiley;

	board_init();
	sysclk_init();
	gfx_mono_init();

	usart_serial_options_t options;
	options.baudrate = 115200;
	options.charlength = USART_CHSIZE_8BIT_gc;
	options.paritytype = USART_PMODE_DISABLED_gc;
	options.stopbits = 0;

	gfx_mono_screen_dump_init(&USARTD0, &options);

	smiley.type = GFX_MONO_BITMAP_RAM;
	smiley.width = 8;
	smiley.height = 16;
	smiley.data.pixmap = smiley_data;

	gfx_mono_draw_vertical_line(30, 4, 28, GFX_PIXEL_SET);
	gfx_mono_draw_horizontal_line(20,4,20, GFX_PIXEL_SET);

	gfx_mono_draw_pixel(10, 10, GFX_PIXEL_SET);

	gfx_mono_generic_put_bitmap(&smiley, 50, 0);

	//vertical line
	gfx_mono_draw_vertical_line(20, 4, 28, GFX_PIXEL_SET);

	gfx_mono_draw_vertical_line(20, 10, 22, GFX_PIXEL_SET);

	gfx_mono_draw_vertical_line(29, 1, 31, GFX_PIXEL_SET);

	gfx_mono_draw_horizontal_line(10,10,20, GFX_PIXEL_SET);

	gfx_mono_draw_horizontal_line(20,10,20, GFX_PIXEL_CLR);

	gfx_mono_draw_horizontal_line(10,13,20, GFX_PIXEL_XOR);

	gfx_mono_draw_line(10,10,100,0, GFX_PIXEL_SET);

	gfx_mono_draw_rect(20, 20, 60, 5, GFX_PIXEL_SET);

	gfx_mono_draw_filled_rect(82, 20, 20, 5, GFX_PIXEL_SET);

	//whole circle
	gfx_mono_draw_circle(50, 16, 8, GFX_PIXEL_SET,GFX_WHOLE);

	//half circle
	gfx_mono_draw_circle(60, 16, 8, GFX_PIXEL_SET,  GFX_QUADRANT3 | GFX_QUADRANT0);

	gfx_mono_draw_filled_circle(100, 16, 8, GFX_PIXEL_SET, 0xFF);

	gfx_mono_draw_circle(64, 16, 15, GFX_PIXEL_SET, 0xFF);

	gfx_mono_draw_filled_circle(64, 16, 14, GFX_PIXEL_XOR, 0xFF);

	gfx_mono_screen_dump();

	while(1);
}
