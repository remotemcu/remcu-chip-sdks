/**
 * \file
 *
 * \brief Bitmap path for SAM toolkit demo application.
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

#ifndef BITMAPS_H_INCLUDED
#define BITMAPS_H_INCLUDED

#define DEMO_BMP_PATH                            "/demo/skins/default_24bpp/"
#define DEMO_BMP_EXT                             ".bmp"
#define DEMO_BMP_BACKGROUND                      (void*)DEMO_BMP_PATH"bmp_background"DEMO_BMP_EXT
#define DEMO_BMP_LOGO_ATMEL                      (void*)DEMO_BMP_PATH"bmp_logo_atmel"DEMO_BMP_EXT
#define DEMO_BMP_BTN_BACK                        (void*)DEMO_BMP_PATH"btn_back"DEMO_BMP_EXT
#define DEMO_BMP_CLOCK                           (void*)DEMO_BMP_PATH"bmp_clock"DEMO_BMP_EXT
#define DEMO_BMP_INTRO_SAM4S                     (void*)DEMO_BMP_PATH"Chip_SAM4S"DEMO_BMP_EXT
#define DEMO_BMP_BTN_AUDIO                       (void*)DEMO_BMP_PATH"btn_audio"DEMO_BMP_EXT
#define DEMO_BMP_BTN_VIDEO                       (void*)DEMO_BMP_PATH"btn_video"DEMO_BMP_EXT
#define DEMO_BMP_BTN_GFX_DEMO                    (void*)DEMO_BMP_PATH"btn_gfx_demo"DEMO_BMP_EXT
#define DEMO_BMP_BTN_SLIDESHOW                   (void*)DEMO_BMP_PATH"btn_slideshow"DEMO_BMP_EXT
#define DEMO_BMP_BTN_SETTINGS                    (void*)DEMO_BMP_PATH"btn_settings"DEMO_BMP_EXT
#define DEMO_BMP_BTN_QTOUCH                      (void*)DEMO_BMP_PATH"btn_qtouch"DEMO_BMP_EXT
#define DEMO_BMP_BTN_LOW_POWER_MODES             (void*)DEMO_BMP_PATH"btn_low_power_modes"DEMO_BMP_EXT
#define DEMO_BMP_BTN_INFOS                       (void*)DEMO_BMP_PATH"btn_infos"DEMO_BMP_EXT
#define DEMO_BMP_BTN_BACKUP_MODE                 (void*)DEMO_BMP_PATH"btn_backup_mode"DEMO_BMP_EXT
#define DEMO_BMP_BTN_WAIT_MODE                   (void*)DEMO_BMP_PATH"btn_wait_mode"DEMO_BMP_EXT
#define DEMO_BMP_BTN_SLEEP_MODE                  (void*)DEMO_BMP_PATH"btn_sleep_mode"DEMO_BMP_EXT
#define DEMO_BMP_BACKUP_MODE                     (void*)DEMO_BMP_PATH"btn_backup_mode"DEMO_BMP_EXT
#define DEMO_BMP_WAIT_MODE                       (void*)DEMO_BMP_PATH"btn_wait_mode"DEMO_BMP_EXT
#define DEMO_BMP_SLEEP_MODE                      (void*)DEMO_BMP_PATH"btn_sleep_mode"DEMO_BMP_EXT
#define DEMO_BMP_BTN_PLAY_PAUSE                  (void*)DEMO_BMP_PATH"btn_play_pause"DEMO_BMP_EXT
#define DEMO_BMP_BTN_PLAY_PAUSE_DISABLED         (void*)DEMO_BMP_PATH"btn_play_pause_disabled"DEMO_BMP_EXT
#define DEMO_BMP_BTN_PLAY_PAUSE_PRESSED          (void*)DEMO_BMP_PATH"btn_play_pause_pressed"DEMO_BMP_EXT
#define DEMO_BMP_BTN_STOP                        (void*)DEMO_BMP_PATH"btn_stop"DEMO_BMP_EXT
#define DEMO_BMP_BTN_STOP_DISABLED               (void*)DEMO_BMP_PATH"btn_stop_disabled"DEMO_BMP_EXT
#define DEMO_BMP_BTN_STOP_PRESSED                (void*)DEMO_BMP_PATH"btn_stop_pressed"DEMO_BMP_EXT
#define DEMO_BMP_BTN_VOLUME                      (void*)DEMO_BMP_PATH"btn_volume"DEMO_BMP_EXT
#define DEMO_BMP_BTN_VOLUME_DISABLED             (void*)DEMO_BMP_PATH"btn_volume_disabled"DEMO_BMP_EXT
#define DEMO_BMP_BTN_VOLUME_PRESSED              (void*)DEMO_BMP_PATH"btn_volume_pressed"DEMO_BMP_EXT
#define DEMO_BMP_BTN_RECORD                      (void*)DEMO_BMP_PATH"btn_record"DEMO_BMP_EXT
#define DEMO_BMP_BTN_RECORD_DISABLED             (void*)DEMO_BMP_PATH"btn_record_disabled"DEMO_BMP_EXT
#define DEMO_BMP_BTN_RECORD_PRESSED              (void*)DEMO_BMP_PATH"btn_record_pressed"DEMO_BMP_EXT
#define DEMO_BMP_BTN_MICROPHONE                  (void*)DEMO_BMP_PATH"btn_microphone"DEMO_BMP_EXT
#define DEMO_BMP_BTN_MICROPHONE_DISABLED         (void*)DEMO_BMP_PATH"btn_microphone_disabled"DEMO_BMP_EXT
#define DEMO_BMP_BTN_MICROPHONE_PRESSED          (void*)DEMO_BMP_PATH"btn_microphone_pressed"DEMO_BMP_EXT
#define DEMO_BMP_BTN_TIME_SETUP                  (void*)DEMO_BMP_PATH"btn_time_setup"DEMO_BMP_EXT
#define DEMO_BMP_BTN_DATE_SETUP                  (void*)DEMO_BMP_PATH"btn_date_setup"DEMO_BMP_EXT
#define DEMO_BMP_BTN_BACKLIGHT_SETUP             (void*)DEMO_BMP_PATH"btn_backlight_setup"DEMO_BMP_EXT
#define DEMO_BMP_BTN_TSD_SETUP                   (void*)DEMO_BMP_PATH"btn_settings_tsd"DEMO_BMP_EXT
#define DEMO_BMP_BTN_UP                          (void*)DEMO_BMP_PATH"btn_up"DEMO_BMP_EXT
#define DEMO_BMP_BTN_DOWN                        (void*)DEMO_BMP_PATH"btn_down"DEMO_BMP_EXT
#define DEMO_BMP_CONFIG_BACKLIGHT                (void*)DEMO_BMP_PATH"bmp_config_backlight"DEMO_BMP_EXT
#define DEMO_BMP_BTN_AUDIO                       (void*)DEMO_BMP_PATH"btn_audio"DEMO_BMP_EXT
#define DEMO_BMP_INFO                            (void*)DEMO_BMP_PATH"bmp_info"DEMO_BMP_EXT
#define DEMO_BMP_BTN_QT_UP                       (void*)DEMO_BMP_PATH"btn_up_disabled"DEMO_BMP_EXT
#define DEMO_BMP_BTN_QT_PREV                     (void*)DEMO_BMP_PATH"btn_left_disabled"DEMO_BMP_EXT
#define DEMO_BMP_BTN_QT_ENTER                    (void*)DEMO_BMP_PATH"btn_play_pause_disabled"DEMO_BMP_EXT
#define DEMO_BMP_BTN_QT_NEXT                     (void*)DEMO_BMP_PATH"btn_right_disabled"DEMO_BMP_EXT
#define DEMO_BMP_BTN_QT_DOWN                     (void*)DEMO_BMP_PATH"btn_down_disabled"DEMO_BMP_EXT
#define DEMO_BMP_BTN_QT_UP_PRESSED               (void*)DEMO_BMP_PATH"btn_up"DEMO_BMP_EXT
#define DEMO_BMP_BTN_QT_PREV_PRESSED             (void*)DEMO_BMP_PATH"btn_left"DEMO_BMP_EXT
#define DEMO_BMP_BTN_QT_ENTER_PRESSED            (void*)DEMO_BMP_PATH"btn_play_pause"DEMO_BMP_EXT
#define DEMO_BMP_BTN_QT_NEXT_PRESSED             (void*)DEMO_BMP_PATH"btn_right"DEMO_BMP_EXT
#define DEMO_BMP_BTN_QT_DOWN_PRESSED             (void*)DEMO_BMP_PATH"btn_down"DEMO_BMP_EXT

#endif /* BITMAPS_H_INCLUDED */
