/**
 * \file
 *
 * \brief Webserver component task for the FreeRTOS Web/DSP Demo.
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

#include "task_demo.h"
#include "stdio_serial.h"
#include "ethernet_sam.h"
#include "sysclk.h"

static void webserver_task(void *pvParameters);

/**
 * \brief Create the Webserver task.
 *
 * \param stack_depth_words Task stack size in 32 bits word.
 * \param task_priority Task priority.
 */
void create_webserver_task(uint16_t stack_depth_words,
		unsigned portBASE_TYPE task_priority)
{
	/** Create the task as described above. */
	xTaskCreate(webserver_task, (const signed char *const) "Webserver",
			stack_depth_words, NULL, task_priority,
			NULL);
}

/**
 * \brief Webserver task core function.
 *
 * \param pvParameters Junk parameter.
 */
static void webserver_task(void *pvParameters)
{
	/* Just to avoid compiler warnings. */
	UNUSED(pvParameters);

	/** Wait for user to read instructions. */
	WAIT_FOR_TOUCH_EVENT;

	/** Webserver task Loop. */
	while (1)
	{
		/**
		 * Check if any packets are available and process if they are
		 * ready. That function also manages the LwIP timers.
		 */
		ethernet_task();
	}
}
