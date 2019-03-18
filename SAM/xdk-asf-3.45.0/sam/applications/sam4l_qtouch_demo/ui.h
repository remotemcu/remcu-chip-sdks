/**
 * \file
 *
 * \brief User Interface.
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

#ifndef _UI_H
#define _UI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"
#include "sleepmgr.h"
#include "sysclk.h"
#include "board.h"
#include "c42364a.h"
#include "board_monitor.h"
#include "touch_api_sam4l.h"
#include "ioport.h"

void ui_set_mcu_status(power_scaling_t power_scaling,
	sleep_mode_t sleep_mode, uint32_t cpu_freq, cpu_src_t cpu_src);
power_scaling_t ui_get_power_scaling_mcu_status(void);
void ui_set_power_scaling_mcu_status(power_scaling_t power_scaling);
sleep_mode_t ui_get_sleep_mode_mcu_status(void);
void ui_set_sleep_mode_mcu_status(sleep_mode_t sleep_mode);
void ui_bm_init(void);
void ui_bm_send_mcu_status(void);
void ui_lcd_init(void);
void ui_lcd_refresh_alphanum(bool ui_lcd_refresh,
	int32_t event_qtouch_slider_position);
void ui_lcd_refresh_txt(void);

#endif  // _UI_H
