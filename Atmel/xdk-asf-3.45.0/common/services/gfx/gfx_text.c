/**
 * \file
 *
 * \brief Font and text drawing routines
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
#include "compiler.h"
#include "stddef.h"
#include "assert.h"
#ifdef CONFIG_HUGEMEM
# include "hugemem.h"
#endif
#if XMEGA
# include "progmem.h"
#endif

#include "gfx.h"
#include "gfx_text.h"

#ifndef CONFIG_FONT_PIXELS_PER_BYTE
# define CONFIG_FONT_PIXELS_PER_BYTE    8
#endif

#define EXTMEM_BUF_SIZE                 20

#if defined(CONFIG_HUGEMEM) || defined(__DOXYGEN__)

/**
 * \internal
 * \brief Helper function that draws a character from a font in hugemem
 *        to the display.
 *
 * This function will first calculate the start offset in the font character
 * data before iterating over the specific character data.
 *
 * Only pixels in the character that should be enabled are done so, the caller
 * is required to prepare the drawing area before printing a character to it.
 * This is done by the gfx_draw_string() and gfx_draw_progmem_string()
 * functions.
 *
 * \param ch       Character to be drawn
 * \param x        X coordinate on screen.
 * \param y        Y coordinate on screen.
 * \param font     Font to draw character in
 * \param color    Foreground color to draw the character in
 */
static void gfx_draw_char_hugemem(const char ch, const gfx_coord_t x,
		const gfx_coord_t y, const struct font *font,
		const gfx_color_t color)
{
	uint8_t i;
	uint8_t char_row_size;
	uint8_t glyph_size;
	uint16_t glyph_data_offset;
	uint8_t char_buff[EXTMEM_BUF_SIZE];
	uint8_t buffer_pos;
	uint8_t rows_left;

	/* Sanity check on parameters, assert if font is NULL. */
	Assert(font != NULL);

	gfx_coord_t inc_x = x;
	gfx_coord_t inc_y = y;

	char_row_size = font->width / CONFIG_FONT_PIXELS_PER_BYTE;
	if (font->width % CONFIG_FONT_PIXELS_PER_BYTE) {
		char_row_size++;
	}

	glyph_size = char_row_size * font->height;
	glyph_data_offset = glyph_size * ((uint8_t)ch - font->first_char);
	buffer_pos = EXTMEM_BUF_SIZE;
	rows_left = font->height;

	do {
		static uint8_t glyph_byte = 0;
		uint8_t pixelsToDraw = font->width;

		for (i = 0; i < pixelsToDraw; i++) {
			if (i % CONFIG_FONT_PIXELS_PER_BYTE == 0) {
				/* Read another byte from hugemem */
				if (buffer_pos >= EXTMEM_BUF_SIZE) {
					hugemem_ptr_t source
						= font->data.hugemem;
					source = (hugemem_ptr_t)
							((uint32_t)source +
							glyph_data_offset);

					hugemem_read_block(char_buff, source,
							EXTMEM_BUF_SIZE);

					glyph_data_offset += EXTMEM_BUF_SIZE;
					buffer_pos = 0;
				}

				glyph_byte = char_buff[buffer_pos];
				buffer_pos++;
			}

			/* Draw bit of glyph to screen */
			if ((glyph_byte & 0x80)) {
				gfx_draw_pixel(inc_x, inc_y, color);
			}

			inc_x += 1;
			glyph_byte <<= 1;
		}

		inc_y += 1;
		inc_x = x;
	} while (--rows_left > 0);
}

#endif

/**
 * \internal
 * \brief Helper function that draws a character from a font in progmem
 *        to the display
 *
 * This function will first calculate the start offset in the font character
 * data before iterating over the specific character data.
 *
 * Only pixels in the character that should be enabled are done so, the caller
 * is required to prepare the drawing area before printing a character to it.
 * This is done by the gfx_draw_string() and gfx_draw_progmem_string()
 * functions.
 *
 * \param ch       Character to be drawn
 * \param x        X coordinate on screen.
 * \param y        Y coordinate on screen.
 * \param font     Font to draw character in
 * \param color    Foreground color to draw the character in
 */
static void gfx_draw_char_progmem(const char ch, const gfx_coord_t x,
		const gfx_coord_t y, const struct font *font,
		const gfx_color_t color)
{
	uint8_t PROGMEM_PTR_T glyph_data;
	uint16_t glyph_data_offset;
	uint8_t char_row_size;
	uint8_t rows_left;
	uint8_t i;

	/* Sanity check on parameters, assert if font is NULL. */
	Assert(font != NULL);

	gfx_coord_t inc_x = x;
	gfx_coord_t inc_y = y;

	char_row_size = font->width / CONFIG_FONT_PIXELS_PER_BYTE;
	if (font->width % CONFIG_FONT_PIXELS_PER_BYTE) {
		char_row_size++;
	}

	glyph_data_offset = char_row_size * font->height *
			((uint8_t)ch - font->first_char);
	glyph_data = font->data.progmem + glyph_data_offset;
	rows_left = font->height;

	do {
		uint8_t glyph_byte = 0;
		uint8_t pixelsToDraw = font->width;

		for (i = 0; i < pixelsToDraw; i++) {
			if (i % CONFIG_FONT_PIXELS_PER_BYTE == 0) {
				glyph_byte = PROGMEM_READ_BYTE(glyph_data);
				glyph_data++;
			}

			if ((glyph_byte & 0x80)) {
				gfx_draw_pixel(inc_x, inc_y, color);
			}

			inc_x += 1;
			glyph_byte <<= 1;
		}

		inc_y += 1;
		inc_x = x;
		rows_left--;
	} while (rows_left > 0);
}

/**
 * \brief Draws a character to the display
 *
 * \param c           Character to be drawn
 * \param x           X coordinate on screen.
 * \param y           Y coordinate on screen.
 * \param font        Font to draw character in
 * \param bg_color    Background color to draw behind the text string
 * \param text_color  Foreground color to draw the text string in
 */
void gfx_draw_char(const char c, const gfx_coord_t x, const gfx_coord_t y,
		const struct font *font, const gfx_color_t bg_color,
		const gfx_color_t text_color)
{
	if (bg_color != GFX_COLOR_TRANSPARENT) {
		gfx_draw_filled_rect(x, y, font->width, font->height, bg_color);
	}

	switch (font->type) {
	case FONT_LOC_PROGMEM:
		gfx_draw_char_progmem(c, x, y, font, text_color);
		break;

#ifdef CONFIG_HUGEMEM
	case FONT_LOC_HUGEMEM:
		gfx_draw_char_hugemem(c, x, y, font, text_color);
		break;

#endif
	default:
		/* Unsupported mode, call assert */
		Assert(false);
		break;
	}
}

/**
 * \brief Draws a string to the display
 *
 * This function will draw a string located in memory to the display.
 *
 * \param str         Pointer to string
 * \param x           X coordinate on screen.
 * \param y           Y coordinate on screen.
 * \param font        Font to draw string in
 * \param bg_color    Background color to draw behind the text string
 * \param text_color  Foreground color to draw the text string in
 */
void gfx_draw_string(const char *str, gfx_coord_t x, gfx_coord_t y,
		const struct font *font, const gfx_color_t bg_color,
		const gfx_color_t text_color)
{
	gfx_draw_string_aligned(str, x, y, font, bg_color, text_color,
			TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
}

/**
 * \brief Draws an aligned string to the display
 *
 * This function will draw a string located in memory to the display
 * with the specified alignment.
 *
 * \param str         Pointer to string
 * \param x           X coordinate on screen.
 * \param y           Y coordinate on screen.
 * \param font        Font to draw string in
 * \param bg_color    Background color to draw behind the text string
 * \param text_color  Foreground color to draw the text string in
 * \param text_pos    Position of the coordinate relative to the text paragraph
 * \param text_align  Alignment of text lines within the paragraph bounding box
 */
void gfx_draw_string_aligned(const char *str, gfx_coord_t x, gfx_coord_t y,
		const struct font *font, const gfx_color_t bg_color,
		const gfx_color_t text_color, enum gfx_text_position text_pos,
		enum gfx_text_alignment text_align)
{
	gfx_coord_t bounding_x, bounding_y;

	/* Sanity check on parameters, assert if str or font is NULL. */
	Assert(str != NULL);
	Assert(font != NULL);

	/* Retrieve the bounding box of the overall text paragraph */
	gfx_get_string_bounding_box(str, font, &bounding_x, &bounding_y);

	/* Move the Y coordinate according to the Y positional setting given */
	if (text_pos & TEXT_POS_CENTER_Y) {
		y -= bounding_y / 2;
	} else if (text_pos & TEXT_POS_BOTTOM) {
		y -= bounding_y;
	}

	/* Move the X coordinate according to the X positional setting given */
	if (text_pos & TEXT_POS_CENTER_X) {
		x -= bounding_x / 2;
	} else if (text_pos & TEXT_POS_RIGHT) {
		x -= bounding_x;
	}

	/* Need to draw each line of the text paragraph individually */
	while (*str != '\0') {
		const char *curr_line_text = str;
		gfx_coord_t curr_line_x = x;
		gfx_coord_t curr_line_width = 0;

		/* Determine width of current line in the the paragraph */
		do {
			if (*str == '\n') {
				str++;
				break;
			} else if (*str != '\r') {
				curr_line_width += font->width;
			}
		} while (*(++str) != '\0');

		/* Move the line starting X coordinate on the display according
		 * to the line width and the specified text alignment parameter
		 */
		if (text_align == TEXT_ALIGN_CENTER) {
			curr_line_x += (bounding_x / 2) - (curr_line_width / 2);
		} else if (text_align == TEXT_ALIGN_RIGHT) {
			curr_line_x += bounding_x - curr_line_width;
		}

		/* Draw current line to the display with the calculated
		 * coordinates
		 */
		do {
			if (*curr_line_text == '\n') {
				break;
			} else if (*curr_line_text != '\r') {
				gfx_draw_char(*curr_line_text, curr_line_x, y,
						font, bg_color, text_color);

				/* Step to the next character display X
				 * coordinate
				 */
				curr_line_x += font->width;
			}
		} while (*(++curr_line_text) != '\0');

		/* Step to the next Y line coordinate for the next line in
		 * paragraph
		 */
		y += font->height + 1;
	}
}

/**
 * \brief Draws a string located in program memory to the display
 *
 * This function will draw a string located in program memory to the display,
 * this differs from gfx_draw_string() by using constant string data from the
 * program memory instead of string data in RAM.
 *
 * Using program memory for constant strings will reduce the applications need
 * for RAM, and thus lower the overall size footprint.
 *
 * \param str         Pointer to string located in program memory
 * \param x           X coordinate on screen.
 * \param y           Y coordinate on screen.
 * \param font        Font to draw string in
 * \param bg_color    Background color to draw behind the text string
 * \param text_color  Foreground color to draw the text string in
 */
void gfx_draw_progmem_string(char PROGMEM_PTR_T str, gfx_coord_t x,
		gfx_coord_t y, const struct font *font,
		const gfx_color_t bg_color, const gfx_color_t text_color)
{
	gfx_draw_progmem_string_aligned(str, x, y, font, bg_color, text_color,
			TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
}

/**
 * \brief Draws an aligned string located in program memory to the display
 *
 * This function will draw a string located in program memory to the display
 * with the specified alignment. This differs from gfx_draw_aligned_string() by
 * using constant string data from the program memory instead of string data in
 * RAM.
 *
 * \param str         Pointer to string located in program memory
 * \param x           X coordinate on screen.
 * \param y           Y coordinate on screen.
 * \param font        Font to draw string in
 * \param bg_color    Background color to draw behind the text string
 * \param text_color  Foreground color to draw the text string in
 * \param text_pos    Position of the coordinate relative to the text paragraph
 * \param text_align  Alignment of text lines within the paragraph bounding box
 */
void gfx_draw_progmem_string_aligned(char PROGMEM_PTR_T str,
		gfx_coord_t x, gfx_coord_t y, const struct font *font,
		const gfx_color_t bg_color, const gfx_color_t text_color,
		enum gfx_text_position text_pos,
		enum gfx_text_alignment text_align)
{
	gfx_coord_t bounding_x, bounding_y;
	char curr_str_char;

	/* Sanity check on parameters, assert if str or font is NULL. */
	Assert(str != NULL);
	Assert(font != NULL);

	/* Retrieve the bounding box of the overall text paragraph */
	gfx_get_progmem_string_bounding_box(str, font,
			&bounding_x, &bounding_y);

	/* Move the Y coordinate according to the Y positional setting given */
	if (text_pos & TEXT_POS_CENTER_Y) {
		y -= bounding_y / 2;
	} else if (text_pos & TEXT_POS_BOTTOM) {
		y -= bounding_y;
	}

	/* Move the X coordinate according to the X positional setting given */
	if (text_pos & TEXT_POS_CENTER_X) {
		x -= bounding_x / 2;
	} else if (text_pos & TEXT_POS_RIGHT) {
		x -= bounding_x;
	}

	curr_str_char = PROGMEM_READ_BYTE((uint8_t PROGMEM_PTR_T)str);

	/* Need to draw each line of the text paragraph individually */
	while (curr_str_char != '\0') {
		char PROGMEM_PTR_T curr_line_text = str;
		char curr_line_char;
		gfx_coord_t curr_line_x = x;
		gfx_coord_t curr_line_width = 0;

		/* Determine width of current line in the the paragraph */
		do {
			if (curr_str_char == '\n') {
				curr_str_char
					= PROGMEM_READ_BYTE(
						(uint8_t PROGMEM_PTR_T)(++str));
				break;
			} else if (curr_str_char != '\r') {
				curr_line_width += font->width;
			}

			curr_str_char = PROGMEM_READ_BYTE(
					(uint8_t PROGMEM_PTR_T)(++str));
		} while (curr_str_char != '\0');

		/* Move the line starting X coordinate on the display according
		 * to the line width and the specified text alignment parameter
		 */
		if (text_align == TEXT_ALIGN_CENTER) {
			curr_line_x += (bounding_x / 2) - (curr_line_width / 2);
		} else if (text_align == TEXT_ALIGN_RIGHT) {
			curr_line_x += bounding_x - curr_line_width;
		}

		curr_line_char = PROGMEM_READ_BYTE(
				(uint8_t PROGMEM_PTR_T)curr_line_text);

		/* Draw current line to the display with the calculated
		 * coordinates
		 */
		do {
			if (*curr_line_text == '\n') {
				break;
			} else if (*curr_line_text != '\r') {
				gfx_draw_char(*curr_line_text, curr_line_x, y,
						font, bg_color, text_color);

				/* Step to the next character display X
				 *coordinate
				 */
				curr_line_x += font->width;
			}

			curr_line_char = PROGMEM_READ_BYTE(
					(uint8_t PROGMEM_PTR_T)(++curr_line_text));
		} while (curr_line_char != '\0');

		/* Step to the next Y line coordinate for the next line in
		 * paragraph
		 */
		y += font->height + 1;
	}
}

/**
 * \brief Computes the bounding box of a string
 *
 * \note If string is empty the returned width will be 1 pixel and the height
 * equal to the font height.
 *
 * \param str      String to calculate bounding box for
 * \param font     Font used
 * \param width    Pointer to width result
 * \param height   Pointer to height result
 */
void gfx_get_string_bounding_box(const char *str, const struct font *font,
		gfx_coord_t *width, gfx_coord_t *height)
{
	gfx_coord_t font_width = font->width;
	gfx_coord_t font_height = font->height;

	gfx_coord_t max_width = 1;
	gfx_coord_t max_height = font_height;
	gfx_coord_t x = 0;

	/* Sanity check on parameters, assert if str or font is NULL. */
	Assert(str != NULL);
	Assert(font != NULL);

	/* Handle each character until trailing null byte */
	do {
		/* Handle '\n' as newline, draw normal characters. */
		if (*str == '\n') {
			x = 0;
			max_height += font_height;
		} else if (*str == '\r') {
			/* Skip '\r' characters. */
		} else {
			x += font_width;
			if (x > max_width) {
				max_width = x;
			}
		}
	} while (*(++str));

	/* Return values through references */
	*width = max_width;
	*height = max_height;
}

/**
 * \brief Computes the bounding box of a string located in program memory
 *
 * \note If string is empty the returned width will be 1 pixel and the height
 * equal to the font height.
 *
 * \param str      String in program memory to calculate bounding box for
 * \param font     Font used
 * \param width    Pointer to width result
 * \param height   Pointer to height result
 */
void gfx_get_progmem_string_bounding_box(char PROGMEM_PTR_T str,
		const struct font *font, gfx_coord_t *width,
		gfx_coord_t *height)
{
	gfx_coord_t font_width = font->width;
	gfx_coord_t font_height = font->height;

	char temp_char;
	gfx_coord_t max_width = 1;
	gfx_coord_t max_height = font_height;
	gfx_coord_t x = 0;

	/* Sanity check on parameters, assert if str or font is NULL. */
	Assert(str != NULL);
	Assert(font != NULL);

	/* Handle each character until trailing null byte */
	temp_char = PROGMEM_READ_BYTE((uint8_t PROGMEM_PTR_T)str);

	while (temp_char) {
		/* Handle '\n' as newline, draw normal characters. */
		if (temp_char == '\n') {
			x = 0;
			max_height += font_height;
		} else if (*str == '\r') {
			/* Skip '\r' characters. */
		} else {
			x += font_width;
			if (x > max_width) {
				max_width = x;
			}
		}

		temp_char = PROGMEM_READ_BYTE((uint8_t PROGMEM_PTR_T)(++str));
	}

	/* Return values through references */
	*width = max_width;
	*height = max_height;
}
