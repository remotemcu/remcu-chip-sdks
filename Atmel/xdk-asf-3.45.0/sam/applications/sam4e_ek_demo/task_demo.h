/**
 * \file
 *
 * \brief FreeRTOS Web/DSP Demo.
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

#ifndef DEMO_TASKS_H
#define DEMO_TASKS_H

#include <FreeRTOS.h>
#include <StackMacros.h>
#include <croutine.h>
#include <list.h>
#include <mpu_wrappers.h>
#include <portable.h>
#include <projdefs.h>
#include <queue.h>
#include <semphr.h>
#include <task.h>
#include <timers.h>

#include <pmc.h>
#include <sysclk.h>

#define SLIDER_SELECTOR_NB     (9UL)
#define SLIDER_SELECTOR_RANGE  (255UL / SLIDER_SELECTOR_NB)

/** Small delay to hold tasks, during instruction screen. */
extern const portTickType instructions_delay;

/** Used to block the application on instruction screen. */
extern uint32_t app_hold;

/** Wait for user to touch screen. */
#define WAIT_FOR_TOUCH_EVENT {while (app_hold) vTaskDelay(instructions_delay);}

void create_dsp_task(uint16_t stack_depth_words,
		unsigned portBASE_TYPE task_priority);

void create_gfx_task(uint16_t stack_depth_words,
		unsigned portBASE_TYPE task_priority);

void create_qtouch_task(uint16_t stack_depth_words,
		unsigned portBASE_TYPE task_priority);

void create_webserver_task(uint16_t stack_depth_words,
		unsigned portBASE_TYPE task_priority);

#endif /* DEMO_TASKS_H */
