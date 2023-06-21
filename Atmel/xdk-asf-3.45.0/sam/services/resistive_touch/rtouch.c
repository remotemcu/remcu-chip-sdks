/**
 * \file
 *
 * \brief Resistive Touch Service.
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

#include "board.h"
#include "ioport.h"
#include "rtouch.h"

/** @cond 0*/
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/** @endcond*/

/** Delay for pushbutton debouncing (the time-base is 10 ms). */
#define DEBOUNCE_TIME      6  /* 10 * 6 = 60 ms */

/** Maximum difference in pixels between the test point and the measured point. */
#define POINTS_MAX_ERROR   5

/** The multiplicator value used by the calibration algorithm to avoid working on float values. */
#define  MULTI_FACTOR      1024

/** Pen state definitions. */
typedef enum rtouch_pen_state_enum {
	STATE_PEN_RELEASED = 0,
	STATE_PEN_PRESSED = 1,
	STATE_PEN_DEBOUNCE = 2
} rtouch_pen_state_t;

/** Global g_ul_timestamp in milliseconds since start of application. */
static volatile uint32_t g_ul_timestamp = 0;

/** last time when the pen is pressed on the touchscreen. */
static volatile uint32_t g_ul_timepress = 0;

/** last time when the pen is released. */
static volatile uint32_t g_ul_timerelease = 0;

/** Pen current state */
static volatile rtouch_pen_state_t pen_state = STATE_PEN_RELEASED;

/** Touch screen enable flag. */
static volatile uint32_t g_ul_is_rtouch_enabled = 0;

/** indicates if the touch screen has been calibrated. */
/** If not, Callback functions are not called. */
static volatile uint32_t g_ul_is_calibrated = 0;

/** Slope for interpoling touchscreen measurements along the X-axis. */
static int32_t g_l_xslope;

/** Slope for interpoling touchscreen measurements along the Y-axis. */
static int32_t g_l_yslope;

/** First calibration point (required for processing point). */
static rtouch_calibration_point_t calibration_point_0;

/** User event handler function pointer. */
static rtouch_event_handler_t event_handler;

/** Current touch screen event. */
static rtouch_event_t event;

/** Panel size. */
static uint32_t g_ul_width;
static uint32_t g_ul_height;

/**
 * \brief Indicates if the calibration of the touch screen is Ok.
 *
 * \return 1 calibration Ok, 0 if not.
 */
static uint8_t rtouch_is_calibrated(void)
{
	return g_ul_is_calibrated;
}

/**
 * \brief Interpolate the provided raw measurements using the previously calculated
 * slope. The resulting x and y coordinates are stored in an array.
 *
 * \param p_data  Raw measurement data.
 * \param p_point  Array in which x and y will be stored.
 */
static void rtouch_get_calibrated_point(const rtouch_point_t *p_raw,
		rtouch_point_t *p_point)
{
	int32_t point_x,point_y;
	point_x = calibration_point_0.panel.x
			- (((int32_t) calibration_point_0.raw.x - (int32_t) p_raw->x)
			* MULTI_FACTOR) / g_l_xslope;

	point_y = calibration_point_0.panel.y
			- (((int32_t) calibration_point_0.raw.y - (int32_t) p_raw->y)
			* MULTI_FACTOR) / g_l_yslope;

	p_point->x = (point_x > 0) ? point_x : 0;
	p_point->x = (p_point->x > g_ul_width) ? g_ul_width : p_point->x;
	p_point->y = (point_y > 0) ? point_y : 0;
	p_point->y = (p_point->y > g_ul_height) ? g_ul_height : p_point->y;
}

/**
 * \brief Handler for PEN interrupts.
 */
static void rtouch_pen_handler(void)
{
	/** Check if the touch screen has been pressed */
	if (rtouch_is_pressed()) {
		if (pen_state == STATE_PEN_RELEASED) {
			g_ul_timepress = g_ul_timestamp;
			pen_state = STATE_PEN_DEBOUNCE;
		}
	} else {
		if (pen_state == STATE_PEN_PRESSED) {
			g_ul_timerelease = g_ul_timestamp;
			pen_state = STATE_PEN_DEBOUNCE;
		}
	}
}

/**
 * \brief Enable PEN interrupts.
 */
static void rtouch_enable_pen_interrupt(void)
{
	/** Initialize interrupts */
	rtouch_set_handler(
			(void (*)(uint32_t, uint32_t)) rtouch_pen_handler
			);

	/** Enable the interrupt */
	rtouch_enable_interrupt();
}

/**
 * \brief Disable PEN interrupts.
 */
static void rtouch_disable_pen_interrupt(void)
{
	/** Disable the interrupt */
	rtouch_disable_interrupt();
}

uint32_t rtouch_init(const uint32_t ul_width, const uint32_t ul_height)
{
	g_ul_width = ul_width;
	g_ul_height = ul_height;

	return rtouch_init_device();
}

void rtouch_wait_pressed(void)
{
	/** Wait for touch & end of conversion */
	while (pen_state != STATE_PEN_RELEASED);
	while (pen_state != STATE_PEN_PRESSED);
}

void rtouch_wait_released(void)
{
	/** Wait for contact loss */
	while (pen_state != STATE_PEN_PRESSED);
	while (pen_state != STATE_PEN_RELEASED);
}

void rtouch_enable(void)
{
	rtouch_enable_pen_interrupt();
	g_ul_is_rtouch_enabled = 1;
}

void rtouch_disable(void)
{
	rtouch_disable_pen_interrupt();
	g_ul_is_rtouch_enabled = 0;
}

void rtouch_set_calibration_parameter(int32_t xslope, int32_t yslope,
								int32_t rawx, int32_t rawy)
{
	/* Set calibration parameters when manual calibration procedure
	 * is not performed.
	 */
	g_l_xslope = xslope;
	g_l_yslope = yslope;
	calibration_point_0.raw.x = rawx;
	calibration_point_0.raw.y = rawy;
	g_ul_is_calibrated = 1;
}

uint32_t rtouch_compute_calibration(rtouch_calibration_point_t *points)
{
	int32_t slope1, slope2;
	bool xOk, yOk;
	static int32_t xDiff, yDiff;
	rtouch_point_t calibrated_point;

	/**
	 * Calculate slopes using the calibration data
	 * Theory behind those calculations:
	 *   - We suppose the touchscreen measurements are linear, so the following
	 * equations are true (simple linear regression) for any two 'a' and 'b'
	 * points of the screen:
	 *       dx = (a.data[0] - b.data[0]) / (a.x - b.x)
	 *       dy = (a.data[1] - b.data[1]) / (a.y - b.y)
	 *
	 *   - We calculate dx and dy (called xslope and yslope here) using
	 *     the calibration points.
	 *
	 *   - We can then use dx and dy to infer the position of a point 'p'
	 *     given the measurements performed by the touchscreen
	 *     ('c' is any of the calibration points):
	 *       dx = (p.data[0] - c.data[0]) / (p.x - c.x)
	 *       dy = (p.data[1] - c.data[1]) / (p.y - c.y)
	 *     Thus:
	 *       p.x = c.x - (p.data[0] - c.data[0]) / dx
	 *       p.y = c.y - (p.data[1] - c.data[1]) / dy
	 *
	 *   - Since there are four calibration points, dx and dy can be
	 *     calculated twice, so we average
	 *     the two values.
	 */
	slope1 = (points[0].raw.x) - (points[1].raw.x);
	slope1 *= MULTI_FACTOR;
	slope1 /= (points[0].panel.x) - (points[1].panel.x);
	slope2 = (points[2].raw.x) - (points[3].raw.x);
	slope2 *= MULTI_FACTOR;
	slope2 /= (points[2].panel.x) - (points[3].panel.x);
	g_l_xslope = (slope1 + slope2) / 2;

	slope1 = (points[0].raw.y) - (points[2].raw.y);
	slope1 *= MULTI_FACTOR;
	slope1 /= (points[0].panel.y) - (points[2].panel.y);
	slope2 = (points[1].raw.y) - (points[3].raw.y);
	slope2 *= MULTI_FACTOR;
	slope2 /= (points[1].panel.y) - (points[3].panel.y);
	g_l_yslope = (slope1 + slope2) / 2;

	/** Backup calibration point 0, used for point processing */
	calibration_point_0.panel.x = points[0].panel.x;
	calibration_point_0.raw.x = points[0].raw.x;
	calibration_point_0.panel.y = points[0].panel.y;
	calibration_point_0.raw.y = points[0].raw.y;

	rtouch_get_calibrated_point(&points[4].raw, &calibrated_point);

	/** Check resulting x and y */
	xDiff = calibrated_point.x - points[4].panel.x;
	yDiff = calibrated_point.y - points[4].panel.y;
	xOk = (xDiff >= -POINTS_MAX_ERROR) && (xDiff <= POINTS_MAX_ERROR);
	yOk = (yDiff >= -POINTS_MAX_ERROR) && (yDiff <= POINTS_MAX_ERROR);

	/** Check calibration result */
	if (xOk && yOk) {
		g_ul_is_calibrated = 1;
		return 0;

	} else {
		g_ul_is_calibrated = 0;
		return 1;
	}
}

void rtouch_set_event_handler(rtouch_event_handler_t handler)
{
	/**
	 * This needs to be an atomic operation, in case an interrupt
	 * fires while we change the handler.
	 * ENTER_CRITICAL_SECTION( SET_HANDLER );
	 */
	event_handler = handler;

	/** LEAVE_CRITICAL_SECTION( SET_HANDLER );*/
}

rtouch_event_handler_t rtouch_get_event_handler(void)
{
	return event_handler;
}

void rtouch_process(void)
{
	static rtouch_point_t old_position;
	uint32_t timeKeep;
	int32_t xDiff, yDiff;
	uint32_t x, y;

	if (g_ul_is_rtouch_enabled == 0) {
		return;
	}

	g_ul_timestamp++;

	/**
	 * Get the current position of the pen if penIRQ has
	 * low value (pen pressed)
	 */
	if (rtouch_is_pressed()) {
		/** Get the current position of the pressed pen */
		if (rtouch_is_calibrated()) {
			rtouch_get_raw_point(&x, &y);
			event.raw.x = x;
			event.raw.y = y;
			old_position.x = event.panel.x;
			old_position.y = event.panel.y;
			rtouch_get_calibrated_point(&event.raw, &event.panel);
		}

		/** call the callback function */
		if (pen_state == STATE_PEN_PRESSED) {
			if (rtouch_is_calibrated()) {
				/** Filter move event if the move is too low */
				xDiff = old_position.x - event.panel.x;
				yDiff = old_position.y - event.panel.y;
				if (!((xDiff >= -POINTS_MAX_ERROR) &&
						(xDiff <= POINTS_MAX_ERROR) &&
						(yDiff >= -POINTS_MAX_ERROR) &&
						(yDiff <= POINTS_MAX_ERROR))) {
					event.type = RTOUCH_MOVE;
					if (event_handler) {
						event_handler(&event);
					}
				}
			}
		}
	}

	/** Determine the pen state */
	if (rtouch_is_pressed()) {
		/** Touch pressed: reinit the last time when release */
		g_ul_timerelease = g_ul_timestamp;

		if (pen_state == STATE_PEN_DEBOUNCE) {
			timeKeep = g_ul_timestamp;
			timeKeep -= g_ul_timepress;
			if (timeKeep > DEBOUNCE_TIME) {
				/** pen is pressed during an enough time : the state change */
				pen_state = STATE_PEN_PRESSED;
				event.type = RTOUCH_PRESS;
				/** call the callback function */
				if (rtouch_is_calibrated() && event_handler) {
					event_handler(&event);
				}
			}
		}
	} else {
		/** Touch released: reinit the last time when release */
		g_ul_timepress = g_ul_timestamp;

		if (pen_state == STATE_PEN_DEBOUNCE) {
			timeKeep = g_ul_timestamp;
			timeKeep -= g_ul_timerelease;
			if (timeKeep > DEBOUNCE_TIME) {
				/** pen is pressed during an enough time : the state change */
				pen_state = STATE_PEN_RELEASED;
				event.type = RTOUCH_RELEASE;
				/** call the callback function */
				if (rtouch_is_calibrated() && event_handler) {
					event_handler(&event);
				}
			}
		}
	}
}

/** @cond 0*/
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/** @endcond*/
