/**
 * \file
 *
 * \brief Clock system example 1.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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

/**
 * \mainpage
 *
 * \section intro Introduction
 * This example shows how to initialize the clock system and blink a LED
 * at a constant 1 Hz frequency.
 *
 * \section files Main files:
 * - clock_example1_sam.c: clock system example application
 * - conf_board.h: board initialization configuration
 * - conf_clock.h: system clock configuration
 *
 * \section deviceinfo Device Info
 * All SAM devices supported by ASF can be used.
 *
 * \section exampledescription Description of the example
 * A delay routine is used to time the interval between each toggling of a LED.
 * The duration of the delay routine is computed from the frequency of the
 * configured system clock source.
 *
 * The main system clock source and prescalers, along with any PLL
 * and/or DFLL configuration, if supported, are defined in conf_clock.h.
 * Changing any of the defines -- #CONFIG_SYSCLK_SOURCE,
 * #CONFIG_SYSCLK_CPU_DIV, etc. -- should not change the frequency of the
 * blinking LED.
 *
 * Refer to the \ref clk_group API documentation for further information on the
 * configuration.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for SAM.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/">Microchip</A>.\n
 * Support and FAQ: https://www.microchip.com/support/
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"

#if ((BOARD == SAM4CMP_DB) || (BOARD == SAM4CMS_DB))
#  define EXAMPLE_LED_GPIO    LED4_GPIO
#else
#  define EXAMPLE_LED_GPIO    LED0_GPIO
#endif

/* Global ul_ms_ticks in milliseconds since start of application */
volatile uint32_t ul_ms_ticks = 0;

/**
 * \brief Wait for the given number of milliseconds (using the ul_ms_ticks generated
 * by the SAM microcontroller system tick).
 *
 * \param ul_dly_ticks  Delay to wait for, in milliseconds.
 */
static void mdelay(uint32_t ul_dly_ticks)
{
	uint32_t ul_cur_ticks;

	ul_cur_ticks = ul_ms_ticks;
	while ((ul_ms_ticks - ul_cur_ticks) < ul_dly_ticks) {
	}
}

/**
 * \brief Handler for System Tick interrupt.
 *
 * Process System Tick Event and increments the ul_ms_ticks counter.
 */
void SysTick_Handler(void)
{
	ul_ms_ticks++;
}

/**
 * \brief Initialize the clock system and blink a LED at a constant 1 Hz frequency.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	sysclk_init();
	board_init();

	/* Setup SysTick Timer for 1 msec interrupts */
	if (SysTick_Config(sysclk_get_cpu_hz() / 1000)) {
		while (1) {  /* Capture error */
		}
	}

	while (1) {
		ioport_toggle_pin_level(EXAMPLE_LED_GPIO);
		mdelay(500);
	}
}

