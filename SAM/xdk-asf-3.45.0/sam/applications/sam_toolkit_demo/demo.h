/**
 * \file
 *
 * \brief Main header file for SAM toolkit demo.
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

#ifndef DEMO_H_INCLUDED
#define DEMO_H_INCLUDED

#include "demo_parameters.h"
#include "conf_board.h"
#include "conf_demo.h"

#define DEMO_QTOUCH

/* For ADC input frame */
#define NB_VAL 256
#define FFT_IN_GAIN  3
#define FFT_OUT_GAIN 30
/* Max display FREQ */
#define MAX_FFT_DISP_FREQ 20000
/* 128K, 128 sample/ms */
#define AUDIO_SAMPLE_RATE 256000
/* 128 samples */
#define AUDIO_FRAME_SIZE (AUDIO_SAMPLE_RATE/1000)
/* Number of frame buffer */
#define AUDIO_NB_BUFFER ((NB_VAL/AUDIO_FRAME_SIZE)+3)
/* Total frame buffer size, in samples */
#define AUDIO_BUFFER_SIZE (AUDIO_NB_BUFFER*AUDIO_FRAME_SIZE)
#define SYSTICK_FREQ 1000

/**
 * \brief Special window mode ID.
 */
typedef enum demo_special_mode_id {
	/** ID for qtouch mode */
	DEMO_QTOUCH_MODE = 0,
	/** ID for lcd calibration mode */
	DEMO_LCD_CALIBRATE_MODE,
	/** ID for PPT mode */
	DEMO_PPT_MODE,
	/** ID for wait mode */
	DEMO_WAIT_MODE,
	/** ID for sleep mode */
	DEMO_SLEEP_MODE,
	/** ID for main mode */
	DEMO_MAIN_MODE,
	/** ID for main mode */
	DEMO_FFT_MODE,
	/** Max special mode */
	DEMO_SPEC_MODE_MAX
}demo_special_mode_id;

/** Demo board name */
extern char demo_board_name[];

void app_widget_main_on(uint8_t on);
void app_widget_settings_on(uint8_t on);
void app_widget_settings_time_on(uint8_t on);
void app_widget_settings_date_on(uint8_t on);
void app_widget_settings_backlight_on(uint8_t on);
void app_widget_settings_tsd_on(uint8_t on);
void app_widget_lpm_on(uint8_t on);
void app_widget_lpm_wait_on(uint8_t on);
void app_widget_lpm_backup_on(uint8_t on);
void app_widget_lpm_sleep_on(uint8_t on);
void app_widget_qtouch_on(uint8_t on);
void app_widget_info_on(uint8_t on);
void set_widget_ppt_mode( void );
void app_widget_audio_on(uint8_t on);
void app_widget_fft_on(void);
void demo_set_special_mode_status( demo_special_mode_id id, uint8_t status );
uint8_t demo_get_special_mode_status( demo_special_mode_id id );
void demo_qt_init(void);
void demo_qtouch_event_handler( void );
uint8_t demo_draw_bmpfile_init(void);

#endif /* DEMO_H_INCLUDED */
