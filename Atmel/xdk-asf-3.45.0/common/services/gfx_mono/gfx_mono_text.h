/**
 * \file
 *
 * \brief Monochrome graphic library API header file
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
#ifndef GFX_MONO_TEXT_H_INCLUDED
#define GFX_MONO_TEXT_H_INCLUDED

#include <stdint.h>

#include "compiler.h"
#include "progmem.h"
#ifdef CONFIG_HAVE_HUGEMEM
# include "hugemem.h"
#endif

/**
 * \ingroup gfx_mono
 * \defgroup gfx_mono_font Font support
 * This modules provides functionality for outputting a monochrome font
 * to a display.
 *
 * @{
 */

/**
 * \brief Valid storage locations for font data
 *
 * \todo Add support for fonts in regular ram
 */
enum font_data_type {
	/** Font data stored in program/flash memory. */
	FONT_LOC_PROGMEM,
#ifdef CONFIG_HAVE_HUGEMEM
	/** Font data stored in HUGEMEM. */
	FONT_LOC_HUGEMEM,
#endif
};

/** Storage structure for font meta data. */
struct font {
	/** Type of storage used for binary font data. See \ref font_data_type. */
	enum font_data_type type;
	union {
		/**
		 * Pointer to where the binary font data is stored. This
		 * variable is accessed either through hugemem or progmem
		 * depending on the value of \a type.
		 */
#ifdef CONFIG_HAVE_HUGEMEM
		hugemem_ptr_t hugemem;
#endif
		uint8_t PROGMEM_PTR_T progmem;
	} data;
	/** Width of one font character, in pixels. */
	uint8_t width;
	/** Height of one font character, in pixels. */
	uint8_t height;
	/** ASCII value of first character in font set. */
	uint8_t first_char;
	/** ASCII value of last character in the set. */
	uint8_t last_char;
};

/** \name Strings and characters located in RAM */
/** @{ */
void gfx_mono_draw_char(const char c, const gfx_coord_t x, const gfx_coord_t y,
		const struct font *font);

void gfx_mono_draw_string(const char *str, const gfx_coord_t x,
		const gfx_coord_t y, const struct font *font);

void gfx_mono_get_string_bounding_box(char const *str, const struct font *font,
		gfx_coord_t *width, gfx_coord_t *height);

/** @} */

/** \name Strings located in flash */
/** @{ */
void gfx_mono_draw_progmem_string(char PROGMEM_PTR_T str, gfx_coord_t x,
		gfx_coord_t y, const struct font *font);

void gfx_mono_get_progmem_string_bounding_box(char PROGMEM_PTR_T str,
		const struct font *font, gfx_coord_t *width,
		gfx_coord_t *height);

/** @} */

/** @} */

#endif /* GFX_MONO_TEXT_H_INCLUDED */
