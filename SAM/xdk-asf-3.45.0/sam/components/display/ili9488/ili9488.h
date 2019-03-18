/**
 * \file
 *
 * \brief API driver for ILI9488 TFT display component.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef ILI9488_H_INCLUDED
#define ILI9488_H_INCLUDED

#include "compiler.h"
#include "board.h"
#include "conf_ili9488.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
 extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/** Type define for an integer type large enough to store a pixel color. */
#ifdef ILI9488_EBIMODE
   typedef uint16_t ili9488_color_t;
#  define LCD_DATA_COLOR_UNIT 1
#  define COLOR_CONVERT       RGB_24_TO_RGB565
#endif
#ifdef ILI9488_SPIMODE
   typedef uint8_t ili9488_color_t;
#  define LCD_DATA_COLOR_UNIT 3
#  define COLOR_CONVERT       RGB_24_TO_18BIT
#endif

typedef int16_t ili9488_coord_t;

typedef union _union_type
{
	uint32_t value;
	struct{
		uint8_t byte_8;
		uint8_t byte_l6;
		uint8_t byte_24;
		uint8_t byte_32;
	}byte;
	struct{
		uint16_t half_word_l;
		uint16_t half_word_h;
	}half_word;
}union_type;

/** Bit mask for flipping X for ili9488_set_orientation() */
#define ILI9488_FLIP_X 1
/** Bit mask for flipping Y for ili9488_set_orientation() */
#define ILI9488_FLIP_Y 2
/** Bit mask for swapping X and Y for ili9488_set_orientation() */
#define ILI9488_SWITCH_XY 4


/* ILI9488 screen size */
#define ILI9488_LCD_WIDTH  320
#define ILI9488_LCD_HEIGHT 480

/** Height of display using swapped X/Y orientation */
#define ILI9488_SWITCH_XY_HEIGHT 480

/** Width of display using swapped X/Y orientation */
#define ILI9488_SWITCH_XY_WIDTH  320

/* ILI9488 ID code */
#define ILI9488_DEVICE_CODE (0x9488u)

/* Level 1 Commands (from the display Datasheet) */
#define ILI9488_CMD_NOP                             0x00
#define ILI9488_CMD_SOFTWARE_RESET                  0x01
#define ILI9488_CMD_READ_DISP_ID                    0x04
#define ILI9488_CMD_READ_ERROR_DSI                  0x05
#define ILI9488_CMD_READ_DISP_STATUS                0x09
#define ILI9488_CMD_READ_DISP_POWER_MODE            0x0A
#define ILI9488_CMD_READ_DISP_MADCTRL               0x0B
#define ILI9488_CMD_READ_DISP_PIXEL_FORMAT          0x0C
#define ILI9488_CMD_READ_DISP_IMAGE_MODE            0x0D
#define ILI9488_CMD_READ_DISP_SIGNAL_MODE           0x0E
#define ILI9488_CMD_READ_DISP_SELF_DIAGNOSTIC       0x0F
#define ILI9488_CMD_ENTER_SLEEP_MODE                0x10
#define ILI9488_CMD_SLEEP_OUT                       0x11
#define ILI9488_CMD_PARTIAL_MODE_ON                 0x12
#define ILI9488_CMD_NORMAL_DISP_MODE_ON             0x13
#define ILI9488_CMD_DISP_INVERSION_OFF              0x20
#define ILI9488_CMD_DISP_INVERSION_ON               0x21
#define ILI9488_CMD_PIXEL_OFF                       0x22
#define ILI9488_CMD_PIXEL_ON                        0x23
#define ILI9488_CMD_DISPLAY_OFF                     0x28
#define ILI9488_CMD_DISPLAY_ON                      0x29
#define ILI9488_CMD_COLUMN_ADDRESS_SET              0x2A
#define ILI9488_CMD_PAGE_ADDRESS_SET                0x2B
#define ILI9488_CMD_MEMORY_WRITE                    0x2C
#define ILI9488_CMD_MEMORY_READ                     0x2E
#define ILI9488_CMD_PARTIAL_AREA                    0x30
#define ILI9488_CMD_VERT_SCROLL_DEFINITION          0x33
#define ILI9488_CMD_TEARING_EFFECT_LINE_OFF         0x34
#define ILI9488_CMD_TEARING_EFFECT_LINE_ON          0x35
#define ILI9488_CMD_MEMORY_ACCESS_CONTROL           0x36
#define ILI9488_CMD_VERT_SCROLL_START_ADDRESS       0x37
#define ILI9488_CMD_IDLE_MODE_OFF                   0x38
#define ILI9488_CMD_IDLE_MODE_ON                    0x39
#define ILI9488_CMD_COLMOD_PIXEL_FORMAT_SET         0x3A
#define ILI9488_CMD_WRITE_MEMORY_CONTINUE           0x3C
#define ILI9488_CMD_READ_MEMORY_CONTINUE            0x3E
#define ILI9488_CMD_SET_TEAR_SCANLINE               0x44
#define ILI9488_CMD_GET_SCANLINE                    0x45
#define ILI9488_CMD_WRITE_DISPLAY_BRIGHTNESS        0x51
#define ILI9488_CMD_READ_DISPLAY_BRIGHTNESS         0x52
#define ILI9488_CMD_WRITE_CTRL_DISPLAY              0x53
#define ILI9488_CMD_READ_CTRL_DISPLAY               0x54
#define ILI9488_CMD_WRITE_CONTENT_ADAPT_BRIGHTNESS  0x55
#define ILI9488_CMD_READ_CONTENT_ADAPT_BRIGHTNESS   0x56
#define ILI9488_CMD_WRITE_MIN_CAB_LEVEL             0x5E
#define ILI9488_CMD_READ_MIN_CAB_LEVEL              0x5F
#define ILI9488_CMD_READ_ABC_SELF_DIAG_RES          0x68
#define ILI9488_CMD_READ_ID1                        0xDA
#define ILI9488_CMD_READ_ID2                        0xDB
#define ILI9488_CMD_READ_ID3                        0xDC

/* Level 2 Commands (from the display Datasheet) */
#define ILI9488_CMD_INTERFACE_MODE_CONTROL          0xB0
#define ILI9488_CMD_FRAME_RATE_CONTROL_NORMAL       0xB1
#define ILI9488_CMD_FRAME_RATE_CONTROL_IDLE_8COLOR  0xB2
#define ILI9488_CMD_FRAME_RATE_CONTROL_PARTIAL      0xB3
#define ILI9488_CMD_DISPLAY_INVERSION_CONTROL       0xB4
#define ILI9488_CMD_BLANKING_PORCH_CONTROL          0xB5
#define ILI9488_CMD_DISPLAY_FUNCTION_CONTROL        0xB6
#define ILI9488_CMD_ENTRY_MODE_SET                  0xB7
#define ILI9488_CMD_BACKLIGHT_CONTROL_1             0xB9
#define ILI9488_CMD_BACKLIGHT_CONTROL_2             0xBA
#define ILI9488_CMD_HS_LANES_CONTROL                0xBE
#define ILI9488_CMD_POWER_CONTROL_1                 0xC0
#define ILI9488_CMD_POWER_CONTROL_2                 0xC1
#define ILI9488_CMD_POWER_CONTROL_NORMAL_3          0xC2
#define ILI9488_CMD_POWER_CONTROL_IDEL_4            0xC3
#define ILI9488_CMD_POWER_CONTROL_PARTIAL_5         0xC4
#define ILI9488_CMD_VCOM_CONTROL_1                  0xC5
#define ILI9488_CMD_CABC_CONTROL_1                  0xC6
#define ILI9488_CMD_CABC_CONTROL_2                  0xC8
#define ILI9488_CMD_CABC_CONTROL_3                  0xC9
#define ILI9488_CMD_CABC_CONTROL_4                  0xCA
#define ILI9488_CMD_CABC_CONTROL_5                  0xCB
#define ILI9488_CMD_CABC_CONTROL_6                  0xCC
#define ILI9488_CMD_CABC_CONTROL_7                  0xCD
#define ILI9488_CMD_CABC_CONTROL_8                  0xCE
#define ILI9488_CMD_CABC_CONTROL_9                  0xCF
#define ILI9488_CMD_NVMEM_WRITE                     0xD0
#define ILI9488_CMD_NVMEM_PROTECTION_KEY            0xD1
#define ILI9488_CMD_NVMEM_STATUS_READ               0xD2
#define ILI9488_CMD_READ_ID4                        0xD3
#define ILI9488_CMD_ADJUST_CONTROL_1                0xD7
#define ILI9488_CMD_READ_ID_VERSION                 0xD8
#define ILI9488_CMD_POSITIVE_GAMMA_CORRECTION       0xE0
#define ILI9488_CMD_NEGATIVE_GAMMA_CORRECTION       0xE1
#define ILI9488_CMD_DIGITAL_GAMMA_CONTROL_1         0xE2
#define ILI9488_CMD_DIGITAL_GAMMA_CONTROL_2         0xE3
#define ILI9488_CMD_SET_IMAGE_FUNCTION              0xE9
#define ILI9488_CMD_ADJUST_CONTROL_2                0xF2
#define ILI9488_CMD_ADJUST_CONTROL_3                0xF7
#define ILI9488_CMD_ADJUST_CONTROL_4                0xF8
#define ILI9488_CMD_ADJUST_CONTROL_5                0xF9
#define ILI9488_CMD_SPI_READ_SETTINGS               0xFB
#define ILI9488_CMD_ADJUST_CONTROL_6                0xFC
#define ILI9488_CMD_ADJUST_CONTROL_7                0xFF


/*----------------------------------------------------------------------------
 *        Function Marcos
 *----------------------------------------------------------------------------*/
#define get_0b_to_8b(x)             (((union_type*)&(x))->byte.byte_8)
#define get_8b_to_16b(x)            (((union_type*)&(x))->byte.byte_l6)
#define get_16b_to_24b(x)           (((union_type*)&(x))->byte.byte_24)
#define get_24b_to_32b(x)           (((union_type*)&(x))->byte.byte_32)

/* Define EBI access for ILI9488 16-bit System Interface.*/
#ifdef ILI9488_EBIMODE
	static inline void LCD_IR(uint8_t lcd_index)
	{
		*((volatile uint16_t *)(BOARD_ILI9488_ADDR)) = lcd_index; /* ILI9488 index register address */
	}
	static inline void LCD_WD(uint16_t lcd_data)
	{
		*(volatile uint16_t *)(BOARD_ILI9488_ADDR) = lcd_data;
	}
	static inline void LCD_MULTI_WD(const uint16_t *lcd_data, uint32_t size)
	{
		while(size--) {
			*((volatile uint16_t *)(BOARD_ILI9488_ADDR)) = *lcd_data++;
		}
	}
	static inline uint16_t LCD_RD(void)
	{
		return *(volatile uint16_t *)(BOARD_ILI9488_ADDR);
	}
	static inline void LCD_MULTI_RD(uint16_t *pbuffer, uint32_t size)
	{
		while(size--) {
			*pbuffer++ = *((volatile uint16_t *)(BOARD_ILI9488_ADDR));
		}
	}
#endif

/* RGB 24-bits color table definition (RGB888). */
#define COLOR_BLACK          (0x000000u)
#define COLOR_WHITE          (0xFFFFFFu)
#define COLOR_BLUE           (0x0000FFu)
#define COLOR_GREEN          (0x00FF00u)
#define COLOR_RED            (0xFF0000u)
#define COLOR_NAVY           (0x000080u)
#define COLOR_DARKBLUE       (0x00008Bu)
#define COLOR_DARKGREEN      (0x006400u)
#define COLOR_DARKCYAN       (0x008B8Bu)
#define COLOR_CYAN           (0x00FFFFu)
#define COLOR_TURQUOISE      (0x40E0D0u)
#define COLOR_INDIGO         (0x4B0082u)
#define COLOR_DARKRED        (0x800000u)
#define COLOR_OLIVE          (0x808000u)
#define COLOR_GRAY           (0x808080u)
#define COLOR_SKYBLUE        (0x87CEEBu)
#define COLOR_BLUEVIOLET     (0x8A2BE2u)
#define COLOR_LIGHTGREEN     (0x90EE90u)
#define COLOR_DARKVIOLET     (0x9400D3u)
#define COLOR_YELLOWGREEN    (0x9ACD32u)
#define COLOR_BROWN          (0xA52A2Au)
#define COLOR_DARKGRAY       (0xA9A9A9u)
#define COLOR_SIENNA         (0xA0522Du)
#define COLOR_LIGHTBLUE      (0xADD8E6u)
#define COLOR_GREENYELLOW    (0xADFF2Fu)
#define COLOR_SILVER         (0xC0C0C0u)
#define COLOR_LIGHTGREY      (0xD3D3D3u)
#define COLOR_LIGHTCYAN      (0xE0FFFFu)
#define COLOR_VIOLET         (0xEE82EEu)
#define COLOR_AZUR           (0xF0FFFFu)
#define COLOR_BEIGE          (0xF5F5DCu)
#define COLOR_MAGENTA        (0xFF00FFu)
#define COLOR_TOMATO         (0xFF6347u)
#define COLOR_GOLD           (0xFFD700u)
#define COLOR_ORANGE         (0xFFA500u)
#define COLOR_SNOW           (0xFFFAFAu)
#define COLOR_YELLOW         (0xFFFF00u)


/* level is in [0; 31]*/
#define BLUE_LEV( level)  (   (level)&BLUE )
#define GREEN_LEV(level)  ( (((level)*2)<<5)&GREEN )
#define RED_LEV(  level)  (  ((level)<<(5+6))&RED )
#define GRAY_LEV( level)  ( BLUE_LEV(level) | GREEN_LEV(level) | RED_LEV(level))

#define RGB_24_TO_RGB565(RGB) \
		(((RGB >>19)<<11) | (((RGB & 0x00FC00) >>5)) | (RGB & 0x00001F))
#define RGB_24_TO_18BIT(RGB) \
		((RGB & 0xFC0000) | (RGB & 0x00FC00) | (RGB & 0x0000FC))
#define RGB_16_TO_18BIT(RGB) \
		(((((RGB >>11)*63)/31) << 18) | (((RGB >> 5) & 0x00003F) << 10) | (((RGB & 0x00001F)*63)/31) << 2)
#define BGR_TO_RGB_18BIT(RGB) \
		(RGB & 0xFF0000) | ((RGB & 0x00FF00) >> 8 ) | ( (RGB & 0x0000FC) >> 16 ))
#define BGR_16_TO_18BITRGB(RGB)   BGR_TO_RGB_18BIT(RGB_16_TO_18BIT(RGB))

#define ILI9488_COLOR(r, g, b)\
			((((uint16_t)b) >> 3) |\
			((((uint16_t)g) << 3) & 0x07E0) |\
			((((uint16_t)r) << 8) & 0xf800))

/**
 * Input parameters when initializing ili9488 driver.
 */
struct ili9488_opt_t{
	uint32_t ul_width;          //!< lcd width in pixel
	uint32_t ul_height;         //!< lcd height in pixel
	uint32_t foreground_color;  //!< lcd foreground color
	uint32_t background_color;  //!< lcd background color
};

/**
 * Font structure
 */
struct ili9488_font{
	/* Font width in pixels. */
	uint8_t width;
	/* Font height in pixels. */
	uint8_t height;
};

/**
 * Display direction option
 */
enum ili9488_display_direction{
	LANDSCAPE  = 0,
	PORTRAIT   = 1
};


uint32_t ili9488_init(struct ili9488_opt_t *p_opt);
void ili9488_set_display_direction(enum ili9488_display_direction direction);
void ili9488_set_window( uint16_t dwX, uint16_t dwY, uint16_t dwWidth, uint16_t dwHeight );
void ili9488_display_on(void);
void ili9488_display_off(void);
void ili9488_set_foreground_color(uint32_t ul_color);
void ili9488_fill(ili9488_color_t ul_color);
void ili9488_set_cursor_position(uint16_t us_x, uint16_t us_y);
void ili9488_scroll(uint16_t ul_tfa, uint16_t ul_lines, uint16_t ul_bfa);
void ili9488_set_scroll_address(uint16_t ul_vsp);
uint32_t ili9488_draw_pixel(uint32_t ul_x, uint32_t ul_y);
ili9488_color_t ili9488_get_pixel(uint32_t ul_x, uint32_t ul_y);
void ili9488_draw_line(uint32_t ul_x1, uint32_t ul_y1,
		uint32_t ul_x2, uint32_t ul_y2);
void ili9488_draw_rectangle(uint32_t ul_x1, uint32_t ul_y1,
		uint32_t ul_x2, uint32_t ul_y2);
void ili9488_draw_filled_rectangle(uint32_t ul_x1, uint32_t ul_y1,
		uint32_t ul_x2, uint32_t ul_y2);
uint32_t ili9488_draw_circle(uint32_t ul_x, uint32_t ul_y, uint32_t ul_r);
uint32_t ili9488_draw_filled_circle(uint32_t ul_x, uint32_t ul_y, uint32_t ul_r);
void ili9488_draw_prepare(uint32_t ul_x, uint32_t ul_y, uint32_t ul_width,
		    uint32_t ul_height);
void ili9488_draw_string(uint32_t ul_x, uint32_t ul_y, const uint8_t *p_str);
void ili9488_draw_pixmap(uint32_t ul_x, uint32_t ul_y, uint32_t ul_width,
		uint32_t ul_height, const ili9488_color_t *p_ul_pixmap);
void ili9488_delay(uint32_t ul_ms);
void ili9488_write_brightness(uint16_t us_value);
uint16_t ili9488_read_gram(void);
void ili9488_write_gram(uint16_t color);
void ili9488_set_top_left_limit(ili9488_coord_t x, ili9488_coord_t y);
void ili9488_set_bottom_right_limit(ili9488_coord_t x, ili9488_coord_t y);
void ili9488_set_limits(ili9488_coord_t start_x, ili9488_coord_t start_y,
		ili9488_coord_t end_x, ili9488_coord_t end_y);
void ili9488_set_orientation(uint8_t flags);
void ili9488_copy_pixels_to_screen(const uint16_t *pixels,
		uint32_t count);
void ili9488_copy_pixels_from_screen(uint16_t *pixels, uint32_t count);
void ili9488_duplicate_pixel(const uint16_t color, uint32_t count);
/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

#endif /* ILI9488_H_INCLUDED */
