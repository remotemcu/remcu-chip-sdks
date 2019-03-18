/**
 * \file
 *
 * \brief Monochrome graphic library framebuffer device
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
#ifndef GFX_MONO_FRAMEBUFFER
#define GFX_MONO_FRAMEBUFFER

#include "gfx_mono.h"

/**
 * \ingroup gfx_mono
 * \defgroup gfx_mono_framebuffer_group Framebuffer
 *
 * This module provides read/write from and to a framebuffer in RAM. This is
 * needed when using a controller that does not provide a way to read back data
 * from the LCD controller memory. In this case we need to buffer the data in
 * a local framebuffer to allow manipulation on pixel level. It is generally
 * not recommended to access the framebuffer directly; this is handled by the
 * graphic driver when needed.
 *
 * @{
 */

void gfx_mono_set_framebuffer(uint8_t *framebuffer);

void gfx_mono_framebuffer_put_page(gfx_mono_color_t *data, gfx_coord_t page,
		gfx_coord_t page_offset, gfx_coord_t width);

void gfx_mono_framebuffer_get_page(gfx_mono_color_t *data, gfx_coord_t page,
		gfx_coord_t page_offset, gfx_coord_t width);

void gfx_mono_framebuffer_draw_pixel(gfx_coord_t x, gfx_coord_t y,
		gfx_mono_color_t color);

uint8_t gfx_mono_framebuffer_get_pixel(gfx_coord_t x, gfx_coord_t y);

void gfx_mono_framebuffer_put_byte(gfx_coord_t page, gfx_coord_t column,
		uint8_t data);

uint8_t gfx_mono_framebuffer_get_byte(gfx_coord_t page, gfx_coord_t column);

void gfx_mono_framebuffer_mask_byte(gfx_coord_t page, gfx_coord_t column,
		gfx_mono_color_t pixel_mask, gfx_mono_color_t color);

/** @} */
#endif /* GFX_MONO_FRAMEBUFFER */
