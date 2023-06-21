/**
 * \file
 *
 * \brief SAM toolkit demo parameter initialization and storage.
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

#include <string.h>
#include <stdio.h>
#include "demo_parameters.h"
#include "flash_efc.h"
#include "conf_demo.h"
#include "FreeRTOS.h"
#include "task.h"

/** Parameter offset */
const int __offset_parameters__
	= (IFLASH0_ADDR + IFLASH0_SIZE - IFLASH0_PAGE_SIZE*8);

/** Parameters used in the demo */
demo_param_t g_demo_parameters = {
	.magic = DEMO_PARAMETERS_MAGIC,
	.ppt_delay = 5000,
	.hour = 12,
	.minute = 0,
	.second = 0,
	.day = 20,
	.month = 12,
	.year = 2012,
	.backlight = 10,
	.calib_points[0].panel.x = LCD_WIDTH / 10,
	.calib_points[0].panel.y = LCD_HEIGHT / 10,
	.calib_points[0].raw.x = 0,
	.calib_points[0].raw.y = 0,
	.calib_points[1].panel.x = LCD_WIDTH - LCD_WIDTH / 10,
	.calib_points[1].panel.y = LCD_HEIGHT / 10,
	.calib_points[1].raw.x = 0,
	.calib_points[1].raw.y = 0,
	.calib_points[2].panel.x = LCD_WIDTH - LCD_WIDTH / 10,
	.calib_points[2].panel.y = LCD_HEIGHT - LCD_HEIGHT / 10,
	.calib_points[2].raw.x = 0,
	.calib_points[2].raw.y = 0,
	.calib_points[3].panel.x = LCD_WIDTH / 10,
	.calib_points[3].panel.y = LCD_HEIGHT - LCD_HEIGHT / 10,
	.calib_points[3].raw.x = 0,
	.calib_points[3].raw.y = 0,
	.calib_points[4].panel.x = LCD_WIDTH / 2,
	.calib_points[4].panel.y = LCD_HEIGHT / 2,
	.calib_points[4].raw.x = 0,
	.calib_points[4].raw.y = 0,
};

/*
 * \brief Initialize demo parameters.
 */
uint32_t demo_parameters_initialize( void )
{
	volatile demo_param_t *param = (demo_param_t *)__offset_parameters__;

	if (param->magic == DEMO_PARAMETERS_MAGIC) {
		memcpy( &g_demo_parameters, (void const *)param,
				sizeof(demo_param_t));
	} else {
		return demo_parameters_commit_changes();
	}

	return 0;
}

/*
 * \brief Commit demo parameters.
 */
uint32_t demo_parameters_commit_changes( void )
{
	uint32_t ret;
	taskENTER_CRITICAL();
	flash_init(FLASH_ACCESS_MODE_128, 6);
	flash_unlock(IFLASH0_ADDR, __offset_parameters__ + IFLASH0_PAGE_SIZE - 1,
			0, 0);
#if SAM4S
	/* Erase flag page */
	flash_erase_page(__offset_parameters__, IFLASH_ERASE_PAGES_8);
	ret = flash_write((uint32_t)(__offset_parameters__),
			(void *)&g_demo_parameters, sizeof(demo_param_t), 0);
#else
	ret = flash_write((uint32_t)(__offset_parameters__),
			(void *)&g_demo_parameters, sizeof(demo_param_t), 1);
#endif

	taskEXIT_CRITICAL();

	return ret;
}
