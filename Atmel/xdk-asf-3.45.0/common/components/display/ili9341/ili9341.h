/**
 * \file
 *
 * \brief ILI9341 Display Controller Component Driver
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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
#ifndef ILI9341_H_INCLUDED
#define ILI9341_H_INCLUDED

#include <ioport.h>
#include <compiler.h>

/* Controller and interface configuration file */
#include "conf_ili9341.h"

#if defined(CONF_ILI9341_USART_SPI)
#  include <usart_spi.h>
#elif defined(CONF_ILI9341_SPI)
#  include <spi_master.h>
#else
#  error "Interface not supported by the component driver"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup ili9341_group ILI9341 Display Controller Component Driver
 *
 * See \ref common_ili9341_qs
 *
 * This is the low level component driver for the ILI9341 display controller.
 * It provides basic functions for initializing, writing and reading the
 * controller. In addition to hardware control and use of the LCD controller
 * internal functions.
 *
 * \warning This component driver is not reentrant and can not be used in
 * interrupt service routines without extra care.
 *
 * Before writing data to the display call \ref ili9341_init() which will set up
 * the physical interface and the display. A configuration file conf_ili9341.h
 * is needed to define which interface to use, pin connections and communication
 * speed.
 *
 * An example conf_ili9341.h file for the XMEGA could look like:
 * \code
	 #define CONF_ILI9341_USART_SPI     &USARTC0
	 #define CONF_ILI9341_CLOCK_SPEED   8000000UL

	 #define CONF_ILI9341_CS_PIN        IOPORT_CREATE_PIN(PORTC, 5)
	 #define CONF_ILI9341_DC_PIN        IOPORT_CREATE_PIN(PORTC, 4)
	 #define CONF_ILI9341_BACKLIGHT_PIN IOPORT_CREATE_PIN(PORTA, 5)
	 #define CONF_ILI9341_RESET_PIN     IOPORT_CREATE_PIN(PORTA, 7)
\endcode
 *
 * \section dependencies Dependencies
 * This component driver depends on the following modules:
 * - \ref gpio_group for IO port control.
 * - \ref sysclk_group for clock speed and functions.
 * - \ref usart_spi_group or \ref spi_group for communication with the
 * controller.
 * @{
 */

/** This macro generates a 16-bit native color for the display from a
 *  24-bit RGB value.
 */
#define ILI9341_COLOR(r, g, b)\
	Swap16((((uint16_t)b) >> 3) |\
	       ((((uint16_t)g) << 3) & 0x07E0) |\
	       ((((uint16_t)r) << 8) & 0xf800))

/** Type define for an integer type large enough to store a pixel color. */
typedef uint16_t ili9341_color_t;

/** Type define for an integer type large enough to store a pixel coordinate.
 */
typedef int16_t ili9341_coord_t;

/**
 * \name Display orientation flags
 * @{
 */

/** Bit mask for flipping X for ili9341_set_orientation() */
#define ILI9341_FLIP_X 1
/** Bit mask for flipping Y for ili9341_set_orientation() */
#define ILI9341_FLIP_Y 2
/** Bit mask for swapping X and Y for ili9341_set_orientation() */
#define ILI9341_SWITCH_XY 4

/** @} */

/** Height of display using default orientation */
#define ILI9341_DEFAULT_HEIGHT   240

/** Width of display using default orientation */
#define ILI9341_DEFAULT_WIDTH    320

/** Height of display using swapped X/Y orientation */
#define ILI9341_SWITCH_XY_HEIGHT 320

/** Width of display using swapped X/Y orientation */
#define ILI9341_SWITCH_XY_WIDTH  240

/**
 * \name Controller primitive graphical functions
 * @{
 */
ili9341_color_t ili9341_read_gram(void);

void ili9341_write_gram(ili9341_color_t color);

void ili9341_set_top_left_limit(ili9341_coord_t x, ili9341_coord_t y);

void ili9341_set_bottom_right_limit(ili9341_coord_t x, ili9341_coord_t y);

void ili9341_set_limits(ili9341_coord_t start_x, ili9341_coord_t start_y,
		ili9341_coord_t end_x, ili9341_coord_t end_y);

void ili9341_set_orientation(uint8_t flags);

void ili9341_copy_pixels_to_screen(const ili9341_color_t *pixels,
		uint32_t count);

#if XMEGA
void ili9341_copy_progmem_pixels_to_screen(
		ili9341_color_t PROGMEM_PTR_T pixels, uint32_t count);
#endif

void ili9341_copy_pixels_from_screen(ili9341_color_t *pixels, uint32_t count);

void ili9341_duplicate_pixel(const ili9341_color_t color, uint32_t count);

/** @} */

/**
 * \name Controller and display initialization and management
 * @{
 */

void ili9341_init(void);

/**
 * \brief Function to turn on the display back light
 *
 * Use this function to simply set the pin controlling the back light high to
 * turn on the back light.
 *
 * \note It is up to the user application if other means of controlling this pin
 * should be used, e.g. a PWM signal to be able to dim the display.
 */
static inline void ili9341_backlight_on(void)
{
	ioport_set_pin_level(CONF_ILI9341_BACKLIGHT_PIN, true);
}

/**
 * \brief Function to turn off the display back light
 *
 * Use this function to simply set the pin controlling the back light low to
 * turn off the back light.
 */
static inline void ili9341_backlight_off(void)
{
	ioport_set_pin_level(CONF_ILI9341_BACKLIGHT_PIN, false);
}

/** @} */

/** @} */

/**
 * \page common_ili9341_qs Quick Start Guide for the ILI9341 Display Controller Component Driver
 *
 * This is the quick start guide for the \ref ili9341_group, with step-by-step
 * instructions on how to configure and use the component driver for specific
 * use cases.
 *
 * The section described below can be compiled into e.g. the main application
 * loop or any other function that will need to interface non-volatile memory.
 *
 * \section common_ili9341_qs_basic Basic usage of the ILI9341 component driver
 * This section will present one use cases of the ILI9341 component driver. It
 * will first turn on the backlight and then fill the screen with a solid
 * color.
 *
 * \section common_ili9341_qs_basic_case Use case 1: Fill Screen Color
 *
 * The ILI9341 component driver contains a basic backlight control as well as
 * functions to draw pixels of various colors within a given pixel boundary.
 * This use case will turn on the backlight and fill the entire display with a
 * single color.
 *
 * \section common_ili9341_qs_basic_case_prereq Prerequisites
 * The conf_ili9341.h configuration file must be present in your application,
 * and should be set to use the correct SPI interface of your chosen
 * microcontroller.
 *
 * Your application should configure the display SPI, reset, command/data and
 * backlight pins as appropriate. If you are using the mXT143E Xplained kit,
 * this can be achieved by defining:
 * \code
	#define CONF_BOARD_MXT143E_XPLAINED
\endcode
 * in your conf_board.h header file.
 *
 * \section common_ili9341_qs_basic_case_setup Setup
 *
 * \subsection common_ili9341_qs_basic_case_setup_steps Code
 * \code
	ili9341_init();
	ili9341_backlight_on();
\endcode
 *
 * \subsection common_ili9341_qs_basic_case_setup_workflow Workflow
 * -# First, we must initialize the display so that it is correctly configured
 *    and ready to receive commands:
 *    \code
	ili9341_init();
\endcode
 * -# Next, the display backlight is enabled, turning it on:
 *    \code
	ili9341_backlight_on();
\endcode
 *
 * \section common_ili9341_qs_basic_case_example_code Example code
 *
 * \code
	 ili9341_set_top_left_limit(0, 0);
	 ili9341_set_bottom_right_limit(240, 320);

	 ili9341_duplicate_pixel(ILI9341_COLOR(255, 0, 0), 240UL * 320UL);
\endcode
 *
 * \subsection common_ili9341_qs_basic_case_workflow Workflow
 *
 * -# First the screen drawing limits are set to start from the upper-left
 *    pixel coordinate, and end at the lower right screen boundary:
 *     - \code
	ili9341_set_top_left_limit(0, 0);
	ili9341_set_bottom_right_limit(240, 320);
\endcode
 *    \note If both the top-left and bottom-right limits are to be set at the
 *          same time, it is faster to call \ref  ili9341_set_limits() instead.
 * -# Next, the display is filled with 240*320 (the screen's pixel dimensions)
 *    pixels of the same RGB color of (255, 0, 0), a bright red.
 *     - \code
	ili9341_duplicate_pixel(ILI9341_COLOR(255, 0, 0), 240UL * 320UL);
\endcode
 *    \note You must encode the RGB color value to use in the display's native
 *          pixel color format using the \ref ILI9341_COLOR() macro.
 */

#ifdef __cplusplus
}
#endif

#endif /* ILI9341_H_INCLUDED */
