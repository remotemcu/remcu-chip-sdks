/**
 * \file
 *
 * \brief Resistive Touch driver.
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

#include "asf.h"
#include "rtouch.h"
#include "rtouch_calibrate.h"
#include "resistive_touch_board.h"

/** Size in pixels of calibration points. */
#define POINTS_SIZE         4

/** Calibration points. */
static rtouch_calibration_point_t gs_calibration_points[] = {
	/* Top-left corner calibration point */
	{
		{LCD_WIDTH / 10,LCD_HEIGHT / 10},
		{0, 0}
	},
	/* Top-right corner calibration point */
	{
		{LCD_WIDTH - LCD_WIDTH / 10, LCD_HEIGHT / 10},
		{0, 0}
	},
	/* Bottom-right corner calibration point */
	{
		{LCD_WIDTH - LCD_WIDTH / 10, LCD_HEIGHT - LCD_HEIGHT / 10},
		{0, 0}
	},
	/* Bottom-left corner calibration point */
	{
		{LCD_WIDTH / 10, LCD_HEIGHT - LCD_HEIGHT / 10},
		{0, 0}
	},
	/* Test calibration point */
	{
		{LCD_WIDTH / 2, LCD_HEIGHT / 2},
		{0, 0}
	}	
};

/**
 * \brief Display a calibration point on the given buffer.
 *
 * \param p_point  Calibration point to display.
 */
static void draw_calibration_point(const rtouch_point_t *p_point)
{
	lcd_set_foreground_color(UNI_COLOR_RED);
	lcd_draw_filled_rectangle(p_point->x - POINTS_SIZE / 2,
			p_point->y - POINTS_SIZE / 2,
			p_point->x - POINTS_SIZE / 2 + POINTS_SIZE,
			p_point->y - POINTS_SIZE / 2 + POINTS_SIZE
	);
}

/**
 * \brief Clears a calibration point from the given buffer.
 *
 * \param p_point  Calibration point to clear.
 */
static void clear_calibration_point(const rtouch_point_t *p_point)
{
	lcd_set_foreground_color(UNI_COLOR_WHITE);
	lcd_draw_filled_rectangle(p_point->x - POINTS_SIZE / 2,
			p_point->y - POINTS_SIZE / 2,
			p_point->x - POINTS_SIZE / 2 + POINTS_SIZE,
			p_point->y - POINTS_SIZE / 2 + POINTS_SIZE
	);
}

/**
 * \brief Starts the calibration routines and displays user instructions on screen.
 *
 * \return 0 if calibration is successful, else 1.
 */
uint32_t rtouch_calibrate(void)
{
	uint32_t i;
	uint32_t x, y;

	/* Print user instructions */
	lcd_fill(UNI_COLOR_WHITE);
	lcd_set_foreground_color(UNI_COLOR_BLACK);
	lcd_draw_string(30, 60, (uint8_t *)"LCD calibration");
	lcd_draw_string(1, 190, (uint8_t *)"Touch the dots to\ncalibrate the screen");

	/* Calibration points */
	for (i = 0; i < 5; i++) {
		draw_calibration_point(&gs_calibration_points[i].panel);

		/* Wait for touch & end of conversion */
		rtouch_wait_pressed();
		
		rtouch_get_raw_point(&x, &y);
		gs_calibration_points[i].raw.x = x;
		gs_calibration_points[i].raw.y = y;
		clear_calibration_point(&gs_calibration_points[i].panel);

		/* Wait for contact loss */
		rtouch_wait_released();
	}
	
	if (rtouch_compute_calibration((rtouch_calibration_point_t *) &gs_calibration_points) == 0) {
		lcd_fill(UNI_COLOR_WHITE);
		lcd_set_foreground_color(UNI_COLOR_BLACK);
		lcd_draw_string(20, 130, (uint8_t *)"Calibration done.");
		return 0;
	} else {
		lcd_fill(UNI_COLOR_WHITE);
		lcd_set_foreground_color(UNI_COLOR_BLACK);
		lcd_draw_string(10, 100, (uint8_t *)"Calibration failed!");
		lcd_draw_string(10, 190, (uint8_t *)"Please try again...");
		
		/* Wait for contact loss */
		rtouch_wait_released();
		return 1;
	}
}
