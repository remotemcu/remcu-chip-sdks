/**
 * \file
 *
 * \brief Debug print basic quick start guide code
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

//! [main_task_data]
uint32_t main_counter;
char main_string[] = "Main task iteration: 0x00000000\r\n";
//! [main_task_data]

//! [main_task]
//! [main_task_open]
static void main_task(void *params)
{
	do {
//! [main_task_open]
//! [main_task_1]
		dbg_print_str("Main task loop executing\r\n");
//! [main_task_1]

//! [main_task_2]
		// Update hexadecimal 32-bit integer in string, and print it
		dbg_sprint_hexint(&main_string[23], main_counter++);
		dbg_print_str(main_string);
//! [main_task_2]

//! [main_task_close]
		vTaskDelay(1000 / portTICK_RATE_MS);
	} while(1);
}
//! [main_task_close]
//! [main_task]


int main (void)
{
//! [init_calls]
	system_init();
	dbg_init();
//! [init_calls]

//! [main_task_create]
	xTaskCreate(&main_task,
		(const char *)"Main task",
		configMINIMAL_STACK_SIZE + 100,
		NULL,
		tskIDLE_PRIORITY + 2,
		NULL);
//! [main_task_create]

//! [freertos_start]
	vTaskStartScheduler();
//! [freertos_start]
}
