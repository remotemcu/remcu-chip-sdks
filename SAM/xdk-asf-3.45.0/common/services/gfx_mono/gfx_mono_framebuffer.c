/**
 * \file
 *
 * \brief Local framebuffer
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

#include "gfx_mono_framebuffer.h"

/* Pointer to the framebuffer; updated by the gfx_mono_set_framebuffer function */
static uint8_t *fbpointer;

/* \brief Set the LCD framebuffer.
 *
 * \param framebuffer A pointer to an allocated area of RAM that can hold the
 * framebuffer.
 *
 * A small example:
 * \code
	uint8_t framebuffer[FRAMEBUFFER_SIZE];
	gfx_mono_set_framebuffer(framebuffer);
\endcode
 */
void gfx_mono_set_framebuffer(uint8_t *framebuffer)
{
	fbpointer = framebuffer;
}

/**
 * \brief Put a page from RAM to the framebuffer
 *
 * \param data Pointer to data to be written
 * \param page Page address
 * \param column Offset into page (x coordinate)
 * \param width Number of bytes to be written.
 *
 * The following example will write 32 bytes from data_buf to the page 0,
 * column 10 (byte 10 to 42 in the framebuffer).
 * \code
	gfx_mono_framebuffer_put_page(data_buf, 0, 10, 32);
\endcode
 */
void gfx_mono_framebuffer_put_page(gfx_mono_color_t *data, gfx_coord_t page,
		gfx_coord_t column, gfx_coord_t width)
{
	gfx_mono_color_t *data_pt = data;
	gfx_coord_t *framebuffer_pt = fbpointer +
			((page * GFX_MONO_LCD_WIDTH) + column);

	do {
		*framebuffer_pt++ = *data_pt++;
	} while (--width > 0);
}

/**
 * \brief Read a page from the framebuffer
 *
 * \param data   Pointer where to store the read data
 * \param page   Page address
 * \param column Offset into page (x coordinate)
 * \param width  Number of bytes to be read
 *
 * The following example will read back the first 128 bytes (first page) from
 * the framebuffer:
 * \code
	gfx_mono_framebuffer_get_page(read_buffer, 0, 0, 128);
\endcode
 */
void gfx_mono_framebuffer_get_page(gfx_mono_color_t *data, gfx_coord_t page, \
		gfx_coord_t column, gfx_coord_t width)
{
	gfx_coord_t *framebuffer_pt = fbpointer +
			((page * GFX_MONO_LCD_WIDTH) + column);
	do {
		*data++ = *framebuffer_pt++;
	} while (--width > 0);
}

/**
 * \brief Draw pixel to framebuffer
 *
 * \param x         X coordinate of the pixel
 * \param y         Y coordinate of the pixel
 * \param color     Pixel operation
 *
 */
void gfx_mono_framebuffer_draw_pixel(gfx_coord_t x, gfx_coord_t y,
		gfx_mono_color_t color)
{
	uint8_t page;
	uint8_t pixel_mask;
	uint8_t pixel_value;

	/* Discard pixels drawn outside the screen */
	if ((x > GFX_MONO_LCD_WIDTH - 1) || (y > GFX_MONO_LCD_HEIGHT - 1)) {
		return;
	}

	page = y / GFX_MONO_LCD_PIXELS_PER_BYTE;
	pixel_mask = (1 << (y - (page * 8)));

	/*
	 * Read the page containing the pixel in interest, then perform the
	 * requested action on this pixel before writing the page back to the
	 * display.
	 */
	pixel_value = gfx_mono_framebuffer_get_byte(page, x);

	switch (color) {
	case GFX_PIXEL_SET:
		pixel_value |= pixel_mask;
		break;

	case GFX_PIXEL_CLR:
		pixel_value &= ~pixel_mask;
		break;

	case GFX_PIXEL_XOR:
		pixel_value ^= pixel_mask;
		break;

	default:
		break;
	}

	gfx_mono_framebuffer_put_byte(page, x, pixel_value);
}

/**
 * \brief Get the pixel value at x,y in framebuffer
 *
 * \param x      X coordinate of pixel
 * \param y      Y coordinate of pixel
 * \return Non zero value if pixel is set.
 *
 */
uint8_t gfx_mono_framebuffer_get_pixel(gfx_coord_t x, gfx_coord_t y)
{
	uint8_t page;
	uint8_t pixel_mask;

	if ((x > GFX_MONO_LCD_WIDTH - 1) || (y > GFX_MONO_LCD_HEIGHT - 1)) {
		return 0;
	}

	page = y / GFX_MONO_LCD_PIXELS_PER_BYTE;
	pixel_mask = (1 << (y - (page * 8)));

	return gfx_mono_framebuffer_get_byte(page, x) & pixel_mask;
}

/**
 * \brief Put a byte to the framebuffer
 *
 * \param page   Page address
 * \param column Page offset (x coordinate)
 * \param data   Data to be written
 *
 * This example will put the value 0xFF to the first byte in the framebuffer
 * \code
	gfx_mono_framebuffer_put_byte(0, 0, 0xFF);
\endcode
 */
void gfx_mono_framebuffer_put_byte(gfx_coord_t page, gfx_coord_t column,
		uint8_t data)
{
	*(fbpointer + (page * GFX_MONO_LCD_WIDTH) + column) = data;
}

/**
 * \brief Get a byte from the framebuffer
 *
 * \param page   Page address
 * \param column Page offset (x coordinate)
 * \return       data from LCD controller or framebuffer.
 *
 * The following code will read the first byte of the framebuffer
 * \code
	data = gfx_mono_framebuffer_get_byte(0, 0);
\endcode
 */
uint8_t gfx_mono_framebuffer_get_byte(gfx_coord_t page, gfx_coord_t column)
{
	return *(fbpointer + (page * GFX_MONO_LCD_WIDTH) + column);
}

/**
 * \brief Read/Modify/Write a byte in the framebuffer
 *
 * This function will read the byte from the framebuffer and
 * do a mask operation on the byte according to the pixel operation selected
 * by the color argument and the pixel mask provided.
 *
 * \param page       Page address
 * \param column     Page offset (x coordinate)
 * \param pixel_mask Mask for pixel operation
 * \param color      Pixel operation
 *
 * A small example that will XOR the first byte of the framebuffer with 0xAA
 * \code
	gfx_mono_framebuffer_mask_byte(0,0,0xAA,GFX_PIXEL_XOR);
\endcode
 */
void gfx_mono_framebuffer_mask_byte(gfx_coord_t page, gfx_coord_t column,
		gfx_mono_color_t pixel_mask, gfx_mono_color_t color)
{
	gfx_mono_color_t temp;

	temp = gfx_mono_get_byte(page, column);

	switch (color) {
	case GFX_PIXEL_SET:
		temp |= pixel_mask;
		break;

	case GFX_PIXEL_CLR:
		temp &= ~pixel_mask;
		break;

	case GFX_PIXEL_XOR:
		temp ^= pixel_mask;
		break;
	}

	gfx_mono_put_byte(page, column, temp);
}
