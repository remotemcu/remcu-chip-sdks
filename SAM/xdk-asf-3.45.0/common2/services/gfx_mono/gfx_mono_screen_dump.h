/**
 * \file
 *
 * \brief Service for performing a screen dump to XPM image file
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
#ifndef GFX_MONO_SCREEN_DUMP_H_INCLUDED
#define GFX_MONO_SCREEN_DUMP_H_INCLUDED

#include <serial.h>
#include <gfx_mono.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup asfdoc_common2_gfx_mono
 * \defgroup asfdoc_common2_gfx_mono_screen_dump XPM USART Screendump functions
 *
 * This service will add the possibility to dump the LCD screen to the USART
 * using the XPM file format.
 *
 * Before using the screen dump function one should make sure that one has
 * performed initialization of this service by calling
 * \ref gfx_mono_screen_dump_init() to set up which USART to use. One should
 * also make sure that one has initialized the gfx mono driver
 * \ref gfx_mono_init() which will produce the screen buffer that is dumped
 * trough the USART.
 *
 * \section asfdoc_common2_screen_dump_dependencies Dependencies
 * This driver depends on the following modules:
 * - asfdoc_samd20_sercom_spi_group
 * @{
 */

/** TODO: This define should be fetched from the GFX display header file. */
#define LCD_PAGE_HEIGHT 8
#define GFX_MONO_LCD_PAGE_COUNT GFX_MONO_LCD_HEIGHT / LCD_PAGE_HEIGHT

/* Define used for stringifying number defines */
#define str(s) # s

#define _XPM_HEADER(w, h) "/* XPM */\r\n" \
	"static char * asf_screen_dump[] = {\r\n" \
	"\"" str(w) " " str(h) " 2 1\",\r\n" \
	"\"   c #FFFFFF\",\r\n"	\
	"\".  c #000000\",\r\n"

#define XPM_HEADER _XPM_HEADER(GFX_MONO_LCD_WIDTH, GFX_MONO_LCD_HEIGHT)

#if UC3
typedef avr32_usart_t dump_usart_t;
#elif XMEGA
typedef USART_t dump_usart_t;
#endif

/** storage for the usart to use when dumping data */
dump_usart_t *dump_usart;

static const uint8_t xpm_header[] = XPM_HEADER;

/**
 * \brief Init the framebuffer dump function
 *
 * \param[in] usart   pointer to the USART to use for dumping the image
 * \param[in] options pointer to the USART options, see documentation
 *
 */
static inline void gfx_mono_screen_dump_init(dump_usart_t *usart,
		const usart_serial_options_t *options)
{
	dump_usart = usart;
	usart_serial_init(usart, options);
}

/**
 * \brief Function for dumping a LCD framebuffer
 *
 * This function will dump a framebuffer to a UART in XPM file format.
 */
static inline void gfx_mono_screen_dump(void)
{
	uint8_t page_buffer[GFX_MONO_LCD_WIDTH];
	/* wait to receive a character on UART before sending */
	uint8_t dummy;
	usart_serial_getchar(dump_usart, &dummy);

	/* write the XPM header */
	usart_serial_write_packet(dump_usart, xpm_header,
			(sizeof(xpm_header) - 1));

	for (uint8_t page = 0; page < GFX_MONO_LCD_PAGE_COUNT; ++page) {
		gfx_mono_get_page(page_buffer, page, 0, GFX_MONO_LCD_WIDTH);
		for (uint8_t row = 0; row < LCD_PAGE_HEIGHT; ++row) {
			usart_putchar(dump_usart, '"');
			for (uint16_t column = 0; column < GFX_MONO_LCD_WIDTH;
					++column) {
				if ((page_buffer[column] & (0x01 << row)) !=
						0x00) {
					usart_putchar(dump_usart, '.');
				} else {
					usart_putchar(dump_usart, ' ');
				}
			}
			usart_serial_write_packet(dump_usart,
					(uint8_t *)"\",\r\n", 4);
		}
	}
	usart_serial_write_packet(dump_usart, (uint8_t *)"};\r\n", 4);
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* GFX_MONO_SCREEN_DUMP_H_INCLUDED */
