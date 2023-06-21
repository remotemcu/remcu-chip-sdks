/**
 * \file
 *
 * \brief Monochrome graphic library example application
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
 * This is an example application for the \ref gfx_mono.
 * It will output some random graphic primitives to a connected LCD screen or
 * framebuffer.
 *
 * \section files Main Files
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_st7565r.h or conf_ssd1306.h
 * - \ref conf_usart_spi.h
 *
 * \section device_info Device Info
 * All AVR devices can be used.
 * This example has been tested with the following setup:
 * - XMEGA-A3BU Xplained
 * - XMEGA-C3 Xplained
 *
 * \section dependencies Dependencies
 * Relevant module dependencies for this application are:
 * - \ref gfx_mono
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
#include <gfx_mono.h>

// Bitmap of two 8x8 pixel smileyfaces on top of each other stored in RAM
uint8_t smiley_data[16] = {
		0x3C, 0x42, 0x95, 0xA1, 0xA1, 0x95, 0x42, 0x3C,
		0x3C, 0x42, 0x95, 0xA1, 0xA1, 0x95, 0x42, 0x3C
};

// Bitmap of two 8x8 pixel smileyfaces on top of each other stored in FLASH
PROGMEM_DECLARE(gfx_mono_color_t, flash_bitmap[16]) =  {
		0x3C, 0x42, 0x95, 0xA1, 0xA1, 0x95, 0x42, 0x3C,
		0x3C, 0x42, 0x95, 0xA1, 0xA1, 0x95, 0x42, 0x3C
};

int main(void){

	struct gfx_mono_bitmap smiley;
	struct gfx_mono_bitmap smiley_flash;

	board_init();
	sysclk_init();

	/* Initialize GFX lib. Will configure the display controller and
	 * create a framebuffer in RAM if the controller lack two-way communication
	 */
	gfx_mono_init();

	// Setup bitmap struct for bitmap stored in RAM
	smiley.type = GFX_MONO_BITMAP_RAM;
	smiley.width = 8;
	smiley.height = 16;
	smiley.data.pixmap = smiley_data;

	// Setup bitmap for bitmap stored in FLASH
	smiley_flash.type = GFX_MONO_BITMAP_PROGMEM;
	smiley_flash.width = 8;
	smiley_flash.height = 16;
	smiley_flash.data.progmem = flash_bitmap;

	// Output bitmaps to display
	gfx_mono_put_bitmap(&smiley, 50, 0);
	gfx_mono_put_bitmap(&smiley_flash, 0, 0);

	//Draw  horizontal an vertical lines with length 128 and 32 pixels
	gfx_mono_draw_vertical_line(1, 0, 32, GFX_PIXEL_SET);
	gfx_mono_draw_horizontal_line(0, 2, 128, GFX_PIXEL_SET);

	// Draw a line from the top-left corner to the bottom right corner
	gfx_mono_draw_line(0, 0, 127, 31, GFX_PIXEL_SET);

	// Draw a rectangle with upper left corner at x=20,y=10 - width=height=10px
	gfx_mono_draw_rect(20, 10, 10, 10,GFX_PIXEL_SET);

	// Draw a 10x10 filled rectangle at x=10,y=10
	gfx_mono_draw_filled_rect(10, 10, 10, 10, GFX_PIXEL_SET);

	// Draw a whole circle at x=50,y=16 with radios=8 and all octants drawn
	gfx_mono_draw_circle(50, 16, 8, GFX_PIXEL_SET,GFX_WHOLE);

	// Draw a filled circle with all quadrant drawn
	gfx_mono_draw_filled_circle(80, 16, 10, GFX_PIXEL_SET, GFX_WHOLE);

	while(true) {
	// This while left intentionally blank to halt execution.
	}
}
