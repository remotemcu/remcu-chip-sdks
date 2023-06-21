/**
 * \file
 *
 * \mainpage
 *
 * \section title Led Chaser example
 *
 * \section file File(s)
 * - \ref led_example.c
 *
 * Copyright (c) 2010-2018 Microchip Technology Inc. and its subsidiaries.
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


#include <compiler.h>
#include <sysclk.h>
#include <board.h>
#include <gpio.h>
#include "conf_example.h"
#include "conf_board.h"

#define INTERVAL_MS 80

void light_single_led(uint8_t led_pin);

#if (UC3A || UC3B || UC3C || UC3D ||UC3L)
static void mdelay(unsigned int ms)
{
	int32_t count, count_end;

	count = Get_system_register(AVR32_COUNT);
	count_end = count + ((sysclk_get_cpu_hz() + 999) / 1000) * ms;

	while ((count_end - count) > 0)
		count = Get_system_register(AVR32_COUNT);
}
#elif XMEGA
static void mdelay(uint16_t ms)
{
	uint32_t count;

	// Approximate the number of loop iterations needed.
	count = sysclk_get_cpu_hz() / 6;
	count *= ms;
	count /= 1000;

	do {
		asm("");
	} while (--count);
}
#endif


void light_single_led(uint8_t led_pin){
	//clear all LEDs
	#if XMEGA
	  gpio_set_pin_group_high(LED_CHASER_PORT_ID, LED_CHASER_PORT_MASK);
	#else
	  gpio_set_group_high(LED_CHASER_PORT_ID, LED_CHASER_PORT_MASK);
	#endif
	//set single LED
	gpio_set_pin_low(led_pin);
}

int main(void)
{
	sysclk_init();
	board_init();

	while (1) {
		#if LED_COUNT > 0
		light_single_led(LED0_GPIO);
		mdelay(INTERVAL_MS);
		#endif

		#if LED_COUNT > 1
		light_single_led(LED1_GPIO);
		mdelay(INTERVAL_MS);
		#endif

		#if LED_COUNT > 2
		light_single_led(LED2_GPIO);
		mdelay(INTERVAL_MS);
		#endif

		#if LED_COUNT > 3
		light_single_led(LED3_GPIO);
		mdelay(INTERVAL_MS);
		#endif

		#if LED_COUNT > 4
		light_single_led(LED4_GPIO);
		mdelay(INTERVAL_MS);
		#endif

		#if LED_COUNT > 5
		light_single_led(LED5_GPIO);
		mdelay(INTERVAL_MS);
		#endif

		#if LED_COUNT > 6
		light_single_led(LED6_GPIO);
		mdelay(INTERVAL_MS);
		#endif

		#if LED_COUNT > 7
		light_single_led(LED7_GPIO);
		mdelay(INTERVAL_MS);
		#endif
	}
}
