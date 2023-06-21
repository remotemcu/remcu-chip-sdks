/**
 *
 * \file
 *
 * \brief
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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
#include "asf.h"
#include <stdio.h>
#include <stdarg.h>
#include "FreeRTOS.h"
#include "osprintf.h"

xSemaphoreHandle trace_lock;

void osprintf_init(void *usart, const void *opt)
{
	trace_lock = xSemaphoreCreateMutex();
	stdio_serial_init(usart, opt);
}

void osprintf(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	xSemaphoreTake(trace_lock, portMAX_DELAY);
	vprintf(fmt, args);
	xSemaphoreGive(trace_lock);
	va_end(args);
}

void osprint(const char *s)
{
	xSemaphoreTake(trace_lock, portMAX_DELAY);
	puts(s);
	xSemaphoreGive(trace_lock);		
}

void osprint_hex_array(uint8_t *p, int sz)
{
	xSemaphoreTake(trace_lock, portMAX_DELAY);
	while (sz) {
		if (sz < 8) {
			while (sz--) {
				printf("%02x ", *p);
				p++;
			}
			break;
		} 
		printf("%02x %02x %02x %02x %02x %02x %02x %02x\n",
				p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
		p += 8;
		sz -= 8;
	}
	printf("\n");
	xSemaphoreGive(trace_lock);
}
 
void osprint_sem_take(void)
{
	xSemaphoreTake(trace_lock, portMAX_DELAY);
}

void osprint_sem_give(void)
{
	xSemaphoreGive(trace_lock);
}
