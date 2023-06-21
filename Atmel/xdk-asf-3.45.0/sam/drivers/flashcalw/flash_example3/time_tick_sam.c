/**
 * \file
 *
 * \brief Time tick for SAM.
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

#include "asf.h"
#include "time_tick.h"

/** Counts for 1ms time ticks. */
volatile uint32_t g_ms_ticks = 0;

#define TICK_US 1000

/**
 * \brief Handler for Sytem Tick interrupt.
 *
 * Process System Tick Event
 * Increments the g_ms_ticks counter.
 */
void SysTick_Handler(void)
{
	g_ms_ticks++;
}

void time_tick_init(uint32_t mck)
{
	g_ms_ticks = 0;

	/* Configure systick */
	if (SysTick_Config(mck / TICK_US)) {
		Assert(false);
	}
}

uint32_t time_tick_get(void)
{
	return g_ms_ticks;
}

uint32_t time_tick_calc_delay(uint32_t tick_start, uint32_t tick_end)
{
	if (tick_end >= tick_start) {
		return (tick_end - tick_start) * (1000 / TICK_US);
	} else {
		/* In the case of 32-bit couter number overflow */
		return (tick_end +
			(0xFFFFFFFF - tick_start)) * (1000 / TICK_US);
	}
}
