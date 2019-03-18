/**
 * \file
 *
 * \brief QTouch implementation for SAM toolkit demo.
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
#include <asf.h>
#include "demo.h"
#include "bitmaps.h"

/** QTouch library type: QTouch / QMatrix */
#define QTOUCH_LIB_TPYE_MASK    0x01

/** QTouch library compiler type offset: GCC / IAR */
#define QTOUCH_LIB_COMPILER_OFFSET    2

/** QTouch library compiler type mask */
#define QTOUCH_LIB_COMPILER_MASK    0x01

/** QTouch library maximum channels offset */
#define QTOUCH_LIB_MAX_CHANNEL_OFFSET    3

/** QTouch library maximum channels mask */
#define QTOUCH_LIB_MAX_CHANNEL_MASK   0x7F

/** QTouch library supports keys only offset */
#define QTOUCH_LIB_KEY_ONLY_OFFSET    10

/** QTouch library supports keys only mask */
#define QTOUCH_LIB_KEY_ONLY_MASK   0x01

/** QTouch library maximum rotors/silders offset */
#define QTOUCH_LIB_ROTOR_NUM_OFFSET    11

/** QTouch library maximum rotors/silders mask */
#define QTOUCH_LIB_ROTOR_NUM_MASK   0x1F

/** Total slider number supported */
#define TOTAL_SLIDER_NUM 2

/** Get QTouch state */
#define GET_SENSOR_STATE(SENSOR_NUMBER) \
	(qt_measure_data.qt_touch_status.sensor_states[(SENSOR_NUMBER / 8)] & (1 << (SENSOR_NUMBER % 8)))
#define GET_ROTOR_SLIDER_POSITION(ROTOR_SLIDER_NUMBER) \
	qt_measure_data.qt_touch_status.rotor_slider_values[ROTOR_SLIDER_NUMBER]

/**
 * \brief Main screen IDs. The screen ID is used to selecte the specific icon
 * widget through the QTouch event.
 */
enum main_screen_icon_id {
	/** ID for audio screen */
	MAIN_SCR_AUDIO_ID = 0,
	/** ID for FFT screen */
	MAIN_SCR_FFT_ID,
	/** ID for PPT player screen */
	MAIN_SCR_PPT_ID,
	/** ID for settings screen */
	MAIN_SCR_SETTINGS_ID,
	/** ID for qtouch screen */
	MAIN_SCR_QTOUCH_ID,
	/** ID for low power mode screen */
	MAIN_SCR_LPM_ID,
	/** ID for dummy left screen */
	MAIN_SCR_DUMMY_LEFT_ID,
	/** ID for information screen */
	MAIN_SCR_INFO_ID,
	/** ID for dummy right screen */
	MAIN_SCR_DUMMY_RIGHT_ID,
	/** Max dummy screen ID */
	MAIN_SCR_MAX_ID,
};

/** Flag set by timer ISR when it's time to measure touch */
uint8_t time_to_measure_touch = 0u;

/** Current time, set by timer ISR */
uint16_t current_time_ms_touch = 0u;

/** Timer period in msec */
uint16_t qt_measurement_period_msec = 25u;

/** QTouch enter key pressed */
static uint8_t vld_pressed = 0;

/** QTouch up key pressed */
static uint8_t up_pressed = 0;

/** QTouch down key pressed */
static uint8_t dwn_pressed = 0;

/** QTouch left key pressed */
static uint8_t lft_pressed = 0;

/** QTouch right key pressed */
static uint8_t rgt_pressed = 0;

/** Selected icon ID; default is set to info icon */
static enum main_screen_icon_id demo_selected_icon_id = MAIN_SCR_INFO_ID;
static enum main_screen_icon_id demo_last_selected_icon_id = MAIN_SCR_INFO_ID;

/** Bitmap for QTouch up button */
static struct gfx_bitmap win_qtouch_btn_up_icon = {
	.width = 48, .height = 48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_QT_UP
};

/** Bitmap for QTouch down button */
static struct gfx_bitmap win_qtouch_btn_down_icon = {
	.width = 48, .height = 48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_QT_DOWN
};

/** Bitmap for QTouch left button */
static struct gfx_bitmap win_qtouch_btn_prev_icon = {
	.width = 48, .height = 48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_QT_PREV
};

/** Bitmap for QTouch right button */
static struct gfx_bitmap win_qtouch_btn_next_icon = {
	.width = 48, .height = 48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_QT_NEXT
};

/** Bitmap for QTouch selected button */
static struct gfx_bitmap win_qtouch_btn_enter_icon = {
	.width = 48, .height = 48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_QT_ENTER
};

/** Bitmap for QTouch pressed up button */
static struct gfx_bitmap win_qtouch_btn_up_press_icon = {
	.width = 48, .height = 48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_QT_UP_PRESSED
};

/** Bitmap for QTouch pressed down button */
static struct gfx_bitmap win_qtouch_btn_down_press_icon = {
	.width = 48, .height = 48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_QT_DOWN_PRESSED
};

/** Bitmap for QTouch pressed left button */
static struct gfx_bitmap win_qtouch_btn_prev_press_icon = {
	.width = 48, .height = 48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_QT_PREV_PRESSED
};

/** Bitmap for QTouch pressed right button */
static struct gfx_bitmap win_qtouch_btn_next_press_icon = {
	.width = 48, .height = 48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_QT_NEXT_PRESSED
};

/** Bitmap for QTouch pressed selected button */
static struct gfx_bitmap win_qtouch_btn_enter_press_icon = {
	.width = 48, .height = 48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_QT_ENTER_PRESSED
};

/**
 * \brief This will fill the default threshold values in the configuration
 * data structure.But User can change the values of these parameters.
 */
static void qt_set_parameters(void)
{
	qt_config_data.qt_di = DEF_QT_DI;
	qt_config_data.qt_neg_drift_rate = DEF_QT_NEG_DRIFT_RATE;
	qt_config_data.qt_pos_drift_rate = DEF_QT_POS_DRIFT_RATE;
	qt_config_data.qt_max_on_duration = DEF_QT_MAX_ON_DURATION;
	qt_config_data.qt_drift_hold_time = DEF_QT_DRIFT_HOLD_TIME;
	qt_config_data.qt_recal_threshold = DEF_QT_RECAL_THRESHOLD;
	qt_config_data.qt_pos_recal_delay = DEF_QT_POS_RECAL_DELAY;
}

/**
 * \brief Configure the sensors.
 */
static void config_sensors(void)
{
#ifdef BOARD_SILDER_BEFOR_KEY
	qt_enable_slider(BOARD_SLIDER_START_CHANNEL, BOARD_SLIDER_END_CHANNEL,
			AKS_GROUP_1, 16u, HYST_6_25, RES_8_BIT, 0u);
#endif

#if defined BOARD_KEY_NUM_5
	qt_enable_key(BOARD_VALID_KEY_CHANNEL, AKS_GROUP_1, 18u, HYST_6_25);
	qt_enable_key(BOARD_UP_KEY_CHANNEL, AKS_GROUP_1, 18u, HYST_6_25);
	qt_enable_key(BOARD_DOWN_KEY_CHANNEL, AKS_GROUP_1, 18u, HYST_6_25);
	qt_enable_key(BOARD_LEFT_KEY_CHANNEL, AKS_GROUP_1, 18u, HYST_6_25);
	qt_enable_key(BOARD_RIGHT_KEY_CHANNEL, AKS_GROUP_1, 18u, HYST_6_25);
#elif defined BOARD_KEY_NUM_2
	qt_enable_key(BOARD_LEFT_KEY_CHANNEL, AKS_GROUP_1, 18u, HYST_6_25);
	qt_enable_key(BOARD_RIGHT_KEY_CHANNEL, AKS_GROUP_1, 18u, HYST_6_25);
#endif

#ifndef BOARD_SILDER_BEFOR_KEY
	qt_enable_slider(BOARD_SLIDER_START_CHANNEL, BOARD_SLIDER_END_CHANNEL,
			AKS_GROUP_1, 16u, HYST_6_25, RES_8_BIT, 0u);
#endif
}


/**
 * \brief QTouch event handler. The QTouch event is valid at main
 * window and QTouch application window.
 */
void demo_qtouch_event_handler( void )
{
	uint16_t status_flag = 0u;
	uint16_t burst_flag = 0u;

	static uint8_t old_position = 0;

	/* QTouch window handler */
	if (demo_get_special_mode_status(DEMO_QTOUCH_MODE)) {
		if (time_to_measure_touch) {
			/* Clear flag: it's time to measure touch */
			time_to_measure_touch = 0u;

			do {
				/*  One time measure touch sensors    */
				status_flag = qt_measure_sensors
							(current_time_ms_touch);

				burst_flag = status_flag & QTLIB_BURST_AGAIN;

				/* Time critical host application code goes here */
			} while (burst_flag);
		}

		/*  Time Non-critical host application code goes here */
		if ((GET_SENSOR_STATE(BOARD_VALID_KEY_ID) != 0) &&
				(vld_pressed == 0)) {
			vld_pressed = 1;
			gfx_draw_bitmap(&win_qtouch_btn_enter_press_icon, 96, 136);
			printf("Valid Press \n\r");
		} else {
			if ((GET_SENSOR_STATE(BOARD_VALID_KEY_ID) == 0) &&
					(vld_pressed == 1)) {
				printf("Valid Release \n\r");
				gfx_draw_bitmap(&win_qtouch_btn_enter_icon, 96,	136);
				vld_pressed = 0;
			}
		}

		if ((GET_SENSOR_STATE(BOARD_UP_KEY_ID) != 0) &&
				(up_pressed == 0)) {
			up_pressed = 1;
			gfx_draw_bitmap(&win_qtouch_btn_up_press_icon, 96, 70);
			printf("Up Key Press \n\r");
		} else {
			if ((GET_SENSOR_STATE(BOARD_UP_KEY_ID) == 0) &&
					(up_pressed == 1)) {
				printf("Up Key Release \n\r");
				up_pressed = 0;
				gfx_draw_bitmap(&win_qtouch_btn_up_icon, 96, 70);
			}
		}

		if ((GET_SENSOR_STATE(BOARD_DOWN_KEY_ID) != 0) &&
				(dwn_pressed == 0)) {
			dwn_pressed = 1;
			gfx_draw_bitmap(&win_qtouch_btn_down_press_icon, 96, 200);
			printf("Down Key Press \n\r");
		} else {
			if ((GET_SENSOR_STATE(BOARD_DOWN_KEY_ID) == 0) &&
					(dwn_pressed == 1)) {
				printf("Down Key Release \n\r");
				dwn_pressed = 0;
				gfx_draw_bitmap(&win_qtouch_btn_down_icon, 96,
						200);
			}
		}

		if ((GET_SENSOR_STATE(BOARD_LEFT_KEY_ID) != 0) &&
				(lft_pressed == 0)) {
			lft_pressed = 1;
			gfx_draw_bitmap(&win_qtouch_btn_prev_press_icon, 30,
					136);
			printf("Left Key Press \n\r");
		} else {
			if ((GET_SENSOR_STATE(BOARD_LEFT_KEY_ID) == 0) &&
					(lft_pressed == 1)) {
				printf("Left Key Release \n\r");
				lft_pressed = 0;
				gfx_draw_bitmap(&win_qtouch_btn_prev_icon, 30,
						136);
			}
		}

		if ((GET_SENSOR_STATE(BOARD_RIGHT_KEY_ID) != 0) &&
				(rgt_pressed == 0)) {
			rgt_pressed = 1;
			printf("Right Key Press \n\r");
			gfx_draw_bitmap(&win_qtouch_btn_next_press_icon, 170,
					136);
		} else {
			if ((GET_SENSOR_STATE(BOARD_RIGHT_KEY_ID) == 0) &&
					(rgt_pressed == 1)) {
				printf("Right Key Release \n\r");
				gfx_draw_bitmap(&win_qtouch_btn_next_icon, 170,
						136);
				rgt_pressed = 0;
			}
		}

		if (GET_ROTOR_SLIDER_POSITION(0) != old_position) {
			old_position = GET_ROTOR_SLIDER_POSITION(0);
			printf("%d ", old_position);
			gfx_draw_rect(19, 19, 202, 42, GFX_COLOR(0, 0, 0));
			gfx_draw_filled_rect(20, 20, 200, 40,
					GFX_COLOR(255, 255, 255));
#ifdef QTOUCH_SLIDER_REVERSED
			gfx_draw_filled_rect(20, 20,
					((255 - old_position) * 200) / 255,
					40, GFX_COLOR(255, 0, 0));
#else
			gfx_draw_filled_rect(20, 20,
					(old_position * 200) / 255,
					40, GFX_COLOR(255, 0, 0));
#endif
		}
	}

	/* Main window handler */
	if (demo_get_special_mode_status(DEMO_MAIN_MODE)) {
		if (time_to_measure_touch) {
			/* Clear flag: it's time to measure touch */
			time_to_measure_touch = 0u;

			do {
				/*  One time measure touch sensors    */
				status_flag = qt_measure_sensors
							(current_time_ms_touch);

				burst_flag = status_flag & QTLIB_BURST_AGAIN;

				/*Time critical host application code goes here */
			} while (burst_flag);
		}

		/*  Time Non-critical host application code goes here */
		if ((GET_SENSOR_STATE(BOARD_VALID_KEY_ID) != 0) &&
				(vld_pressed == 0)) {
			vld_pressed = 1;

			printf("Valid Press \n\r");
		} else {
			if ((GET_SENSOR_STATE(BOARD_VALID_KEY_ID) == 0) &&
					(vld_pressed == 1)) {
				printf("Valid Release \n\r");

				vld_pressed = 0;
			}
		}

		if ((GET_SENSOR_STATE(BOARD_UP_KEY_ID) != 0) &&
				(up_pressed == 0)) {
			up_pressed = 1;
			if (demo_selected_icon_id < 3) {
				demo_selected_icon_id += MAIN_SCR_MAX_ID;
			}

			demo_selected_icon_id -= 3;

			if ((demo_selected_icon_id ==
					MAIN_SCR_DUMMY_LEFT_ID) ||
					(demo_selected_icon_id ==
					MAIN_SCR_DUMMY_RIGHT_ID)) {
				demo_selected_icon_id -= 3;
			}

			printf("Up Key Press \n\r");
		} else {
			if ((GET_SENSOR_STATE(BOARD_UP_KEY_ID) == 0) &&
					(up_pressed == 1)) {
				printf("Up Key Release \n\r");
				up_pressed = 0;
			}
		}

		if ((GET_SENSOR_STATE(BOARD_DOWN_KEY_ID) != 0) &&
				(dwn_pressed == 0)) {
			dwn_pressed = 1;

			demo_selected_icon_id += 3;

			if ((demo_selected_icon_id ==
					MAIN_SCR_DUMMY_LEFT_ID) ||
					(demo_selected_icon_id ==
					MAIN_SCR_DUMMY_RIGHT_ID)) {
				demo_selected_icon_id = MAIN_SCR_INFO_ID;
			}

			if (demo_selected_icon_id >= MAIN_SCR_MAX_ID) {
				demo_selected_icon_id = MAIN_SCR_FFT_ID;
			}

			printf("Down Key Press \n\r");
		} else {
			if ((GET_SENSOR_STATE(BOARD_DOWN_KEY_ID) == 0) &&
					(dwn_pressed == 1)) {
				printf("Down Key Release \n\r");
				dwn_pressed = 0;
			}
		}

		if ((GET_SENSOR_STATE(BOARD_LEFT_KEY_ID) != 0) &&
				(lft_pressed == 0)) {
			lft_pressed = 1;

			if (demo_selected_icon_id == MAIN_SCR_AUDIO_ID) {
				demo_selected_icon_id = MAIN_SCR_MAX_ID;
			}

			demo_selected_icon_id--;

			if ((demo_selected_icon_id ==
					MAIN_SCR_DUMMY_LEFT_ID) ||
					(demo_selected_icon_id ==
					MAIN_SCR_DUMMY_RIGHT_ID)) {
				demo_selected_icon_id--;
			}

			printf("Left Key Press \n\r");
		} else {
			if ((GET_SENSOR_STATE(BOARD_LEFT_KEY_ID) == 0) &&
					(lft_pressed == 1)) {
				printf("Left Key Release \n\r");
				lft_pressed = 0;
			}
		}

		if ((GET_SENSOR_STATE(BOARD_RIGHT_KEY_ID) != 0) &&
				(rgt_pressed == 0)) {
			demo_selected_icon_id++;

			if ((demo_selected_icon_id ==
					MAIN_SCR_DUMMY_LEFT_ID)) {
				demo_selected_icon_id++;
			}

			if ((demo_selected_icon_id ==
					MAIN_SCR_DUMMY_RIGHT_ID)) {
				demo_selected_icon_id = MAIN_SCR_AUDIO_ID;
			}

			rgt_pressed = 1;
			printf("Right Key Press \n\r");
		} else {
			if ((GET_SENSOR_STATE(BOARD_RIGHT_KEY_ID) == 0) &&
					(rgt_pressed == 1)) {
				printf("Right Key Release \n\r");
				rgt_pressed = 0;
			}
		}

		if (up_pressed || dwn_pressed || lft_pressed || rgt_pressed) {
			/* Redraw the select icon */
			gfx_generic_draw_rect(14 + MAIN_SCR_INFO_ID % 3 * 76,
					62 + MAIN_SCR_INFO_ID / 3 * 76,
					64, 64, GFX_COLOR(255, 255, 255));
			gfx_generic_draw_rect(
					14 + demo_last_selected_icon_id % 3 * 76,
					62 + demo_last_selected_icon_id / 3 * 76, 64, 64,
					GFX_COLOR(255, 255, 255));
			gfx_generic_draw_rect(
					14 + demo_selected_icon_id % 3 * 76,
					62 + demo_selected_icon_id / 3 * 76, 64,
					64, GFX_COLOR(0, 0, 255));
			demo_last_selected_icon_id = demo_selected_icon_id;
		}

		/* If enter key pressed, send the key event */
		if (vld_pressed) {
			struct win_pointer_event win_touch_event;

			win_touch_event.type = WIN_POINTER_PRESS;

			/* Indicate the touch event is a non-relative movement
			 * with the virtual touch button pressed
			 */
			win_touch_event.is_relative = false;
			win_touch_event.buttons = WIN_TOUCH_BUTTON;

			/* Translate the touch X and Y position into a screen
			 * coordinate */
			win_touch_event.pos.x
				= 14 + 32 + demo_selected_icon_id % 3 * 76;
			win_touch_event.pos.y
				= 62 + 32 + demo_selected_icon_id / 3 * 76;
			win_queue_pointer_event(&win_touch_event);

			win_touch_event.type = WIN_POINTER_RELEASE;
			win_queue_pointer_event(&win_touch_event);
		}
	}
}

/**
  * \brief Initialize QTouch.
 */
void demo_qt_init(void)
{
	/* Reset touch sensing */
	qt_reset_sensing();

	/* Configure the Sensors as keys or Keys With Rotor/Sliders in this
	 * function */
	config_sensors();

	/* Initialise touch sensing */
	qt_init_sensing();

	/* Set the parameters like recalibration threshold, Max_On_Duration etc
	 * in this function by the user */
	qt_set_parameters();

	/* Address to pass address of user functions */
	/* This function is called after the library has made capacitive measurements,
	 * but before it has processed them. The user can use this hook to apply filter
	 * functions to the measured signal values.(Possibly to fix sensor layout faults) */
	qt_filter_callback = 0;
}
