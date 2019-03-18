/**
 * \file
 *
 * \brief HX8347A display controller driver Example 2
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
 * - hx8347a_example2.c: The main example file
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
 * Five squares of different colors are drawn to the screen to have a test
 * pattern that can be used fto verify correct color operation of the screen.
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

#define HX8347A_BLACK   HX8347A_COLOR(0  ,   0,   0)
#define HX8347A_RED     HX8347A_COLOR(255,   0,   0)
#define HX8347A_BLUE    HX8347A_COLOR(0  ,   0, 255)
#define HX8347A_GREEN   HX8347A_COLOR(0  , 255,   0)
#define HX8347A_WHITE   HX8347A_COLOR(255, 255, 255)
#define HX8347A_GRAY    HX8347A_COLOR(128, 128, 128)

/** Number of pixels for full screen */
#define TOTAL_PIXELS ((uint32_t)HX8347A_DEFAULT_WIDTH * HX8347A_DEFAULT_HEIGHT)

/**
 * \brief The main application routine
 */
int main(void)
{
	board_init();

	sysclk_init();

	/* Make sure to initialize the display controller */
	hx8347a_init();

	/* Turn on the back light */
	hx8347a_backlight_on();

	/* Blank the screen by drawing a black background. Notice how the
	 * drawing boundaries/limits are set to the entire screen */
	hx8347a_set_top_left_limit(0, 0);
	hx8347a_set_bottom_right_limit(HX8347A_DEFAULT_WIDTH, HX8347A_DEFAULT_HEIGHT);

	hx8347a_duplicate_pixel(HX8347A_BLACK, TOTAL_PIXELS);

	/* Draw five squares in different colors to generate a test pattern for
	 * the screen */

	/* First draw a red square */
	hx8347a_set_top_left_limit(60, 204);
	hx8347a_set_bottom_right_limit(180, 294);

	hx8347a_duplicate_pixel(HX8347A_RED, 11040);

	/* Then draw a green square */
	hx8347a_set_top_left_limit(60, 204);
	hx8347a_set_top_left_limit(60, 114);
	hx8347a_set_bottom_right_limit(180, 194);

	hx8347a_duplicate_pixel(HX8347A_GREEN, 11040);

	/* Then draw a blue square */
	hx8347a_set_top_left_limit(60, 204);
	hx8347a_set_top_left_limit(60, 12);
	hx8347a_set_bottom_right_limit(180, 102);

	hx8347a_duplicate_pixel(HX8347A_BLUE, 11040);

	/* Then draw a white square */
	hx8347a_set_top_left_limit(60, 204);
	hx8347a_set_top_left_limit(15, 12);
	hx8347a_set_bottom_right_limit(45, 294);

	hx8347a_duplicate_pixel(HX8347A_WHITE, 11040);

	/* Then draw a gray square */
	hx8347a_set_top_left_limit(60, 204);
	hx8347a_set_top_left_limit(195, 12);
	hx8347a_set_bottom_right_limit(225, 294);

	hx8347a_duplicate_pixel(HX8347A_GRAY, 11040);

	/* Application end */
	while (true) {
		/* Do nothing */
	}
}
