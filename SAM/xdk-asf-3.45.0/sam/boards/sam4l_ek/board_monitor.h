/**
 * \file
 *
 * \brief SAM4L-EK Board Monitor Control.
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

#ifndef BOARD_MONITOR_H_INCLUDED
#define BOARD_MONITOR_H_INCLUDED

#include "compiler.h"
#include "usart.h"
#include "board.h"
#include "sysclk.h"

//! Power scaling definitions
typedef enum {
	POWER_SCALING_NA                = 0, //!< Default Power Scaling Configuration
	POWER_SCALING_PS0               = 1, //!< PS0 Power Scaling Configuration
	POWER_SCALING_PS1               = 2, //!< PS1 Power Scaling Configuration
	POWER_SCALING_PS2               = 3, //!< PS2 Power Scaling Configuration
} power_scaling_t;

//! Sleep Mode definitions
typedef enum {
	SLEEP_MODE_NA                     = 0, //!< Default configuration for sleep Mode
	SLEEP_MODE_RUN                    = 1, //!< Run Mode
	SLEEP_MODE_0                      = 2, //!< Sleep Mode 0
	SLEEP_MODE_1                      = 3, //!< Sleep Mode 1
	SLEEP_MODE_2                      = 4, //!< Sleep Mode 2
	SLEEP_MODE_3                      = 5, //!< Sleep Mode 3
	SLEEP_MODE_WAIT                   = 6, //!< Wait Mode
	SLEEP_MODE_RETENTION              = 7, //!< Retention Mode
	SLEEP_MODE_BACKUP                 = 8, //!< Backup Mode
} sleep_mode_t;

//! CPU Source
typedef enum {
	CPU_SRC_NA                        = 0, //!< Default configuration for CPU source
	CPU_SRC_RCSYS                     = 1, //!< RCSYS
	CPU_SRC_OSC0                      = 2, //!< OSC0
	CPU_SRC_PLL                       = 3, //!< PLL
	CPU_SRC_DFLL                      = 4, //!< DFLL
	CPU_SRC_RC1M                      = 5, //!< RC1M
	CPU_SRC_RC4M                      = 6, //!< RC4M
	CPU_SRC_RC80M                     = 7, //!< RC80M
	CPU_SRC_CRIPOSC                   = 8, //!< CRIPOSC
} cpu_src_t;

typedef struct
{
   //! power scaling variable
   power_scaling_t power_scaling;
   //! sleep mode variable
   sleep_mode_t sleep_mode;
   //! CPU freq variable
   uint32_t cpu_freq;
   //! CPU clock source variable
   cpu_src_t cpu_src;
} sam4l_status_t;

typedef  struct {
	uint8_t start;
	uint8_t id;
	uint8_t dlc;
	sam4l_status_t* sam4l_status;
	uint32_t crc;
} sam4l_status_msg_t;

/**
 * \brief Configure the board monitor.
 *
 */
void bm_init(void);

/**
 * \brief Enable/disable the board monitor.
 *
 * \param state true to enable, false to disable.
 */
void bm_ctrl(bool state);

/**
 * \brief Enable/disable the board monitor mouse-like pointer.
 *
 * \param state true to enable, false to disable.
 */
void bm_mouse_pointer_ctrl(bool state);

/**
 * \brief Send new mouse pointer position.
 *
 * \param x x position. Range is [0; 127].
 * \param y y position range is [0; 63].
 */
void bm_mouse_pointer_move(uint32_t x, uint32_t y);

/**
 * \brief Turn-on a LED of the board monitor.
 *
 * \param led led number. Range is [0; 3].
 */
void bm_led_set(uint32_t led);

/**
 * \brief Turn-off a LED of the board monitor.
 *
 * \param led led number. Range is [0; 3].
 */
void bm_led_clr(uint32_t led);

/**
 * \brief Toggle a LED of the board monitor.
 *
 * \param led led number. Range is [0; 3].
 */
void bm_led_tgl(uint32_t led);

/**
 * \brief Send MCU power saving information to the board monitor,
 *        in order to get them displayed on the OLED screen.
 *
 * \param power_scaling Power scaling.
 * \param sleep_mode Sleep mode.
 * \param cpu_freq CPU frequency.
 * \param cpu_src CPU source clock.
 */
void bm_send_mcu_status(uint32_t power_scaling, uint32_t sleep_mode,
		uint32_t cpu_freq, uint32_t cpu_src);

/**
 * \brief Return Current Consumption Measured.
 *
 * \param sleep_mode Sleep Mode Desired.
 * \param current Current Value Measured.
 */
bool bm_get_mcu_current(uint32_t* sleep_mode, float* current);

/**
 * \brief Return the free size (in byte) of the board monitor command fifo.
 *
 * \param free_size free size in byte.
 */
bool bm_get_fifo_free_size(uint16_t* free_size);

/**
 * \brief Send PicoUart Frame. Note that the timeout countdown starts after a
 *        500ms delay in order to keep a stable current measurement.
 * \param frame Frame to be sent.
 * \param timeout_ms Timeout value in ms.
 */
void bm_send_picouart_frame(uint8_t frame, uint32_t timeout_ms);

/**
 * \brief Force Toggle of Button Line.
 * \param timeout_ms Timeout value in ms.
 */
void bm_tgl_button(uint32_t timeout_ms);

/**
 * \brief Enable/disable the pull-up on TWI lines.
 *
 * \param state true to enable, false to disable.
 */
void bm_pullup_twi(bool state);

/**
 * \brief Clear Print Text Area.
 *
 */
void bm_print_clear(void);

/**
 * \brief Print Text On Board Monitor.
 *
 * \param str String pattern.
 * \param str_length String length pattern.
 */
void bm_print_txt(uint8_t* str, uint8_t str_length);

/**
 * \brief Get Firmware Version.
 *
 * \param fw_minor_version Firmware Version (in ascii format).
 * \param fw_major_version Firmware Version (in ascii format).
 */
bool bm_get_firmware_version(uint8_t* fw_minor_version, uint8_t* fw_major_version);

#endif  // BOARD_MONITOR_H_INCLUDED
