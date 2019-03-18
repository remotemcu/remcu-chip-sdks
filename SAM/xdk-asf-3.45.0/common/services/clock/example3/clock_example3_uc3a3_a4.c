/**
 * \file
 *
 * \brief Clock system example 3
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

/**
 * \mainpage
 *
 * \section intro Introduction
 * This example shows how to switch between various system clock sources
 * and prescalers at run time.
 *
 * \section files Main files:
 * - clock_example3_uc3a3_a4.c: clock system example application
 * - conf_board.h: board initialization configuration
 * - conf_clock.h: system clock configuration
 * - conf_example3.h: chip- or board-specific example configuration
 *
 * \section deviceinfo Device Info
 * All AVR UC3A3 and UC3A4 devices can be used.
 *
 * \section exampledescription Description of the example
 * The clock system is reconfigured every time the user presses a button
 * (\ref NEXT_BUTTON) to use the next clock source and prescaler settings
 * shown in the state diagram below.
 *
 * \par Sequence of clock source and prescaler settings
 * \dot
	digraph clock_example {
		node [shape = doublecircle];
		OSC0 [label = "OSC0"];
		node [shape = ellipse];
		OSC0_DIV [label = "OSC0 / 2"];
		RCOSC [label = "RCOSC"];
		PLL0 [label = "PLL0 / 4"];

		OSC0 -> OSC0_DIV [label="Push button"];
		OSC0_DIV -> RCOSC [label="Push button"];
		RCOSC -> PLL0 [label="Push button"];
		PLL0 -> OSC0 [label="Push button"];
	}
 * \enddot
 *
 * A Timer/Counter (TC) is used to generate periodic interrupts based on
 * its peripheral bus clock. With each interrupt, a LED (\ref LED_EXAMPLE_OUTPUT) is
 * toggled, thus giving a visual indication of the system clock frequency.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for AVR.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/">Microchip</A>.\n
 */

//! \name Example configuration
//@{
/**
 * \def NEXT_BUTTON
 * \brief Pin to use for button input
 *
 * This is the active low pin to use for user input.
 *
 * \note The pin is assumed to be configured by the board initialization.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
//@}

#include <compiler.h>
#include <gpio.h>
#include <pll.h>
#include <sysclk.h>
#include <delay.h>
#include <conf_example3.h>

ISR( timer_irq_handler, AVR32_TC0_IRQ_GROUP, 3)
{
	static bool toggle;

	/* Slow down the LED a little bit */
	if (toggle)
		gpio_toggle_pin(LED_EXAMPLE_OUTPUT);
	toggle = !toggle;
	AVR32_TC0.channel[0].sr;
}

static void wait_for_switches(void)
{
	do { } while (gpio_pin_is_high(NEXT_BUTTON));
	delay_ms(1);
	do { } while (gpio_pin_is_low(NEXT_BUTTON));
	delay_ms(1);
}

int main(void)
{
	sysclk_init();
	board_init();

	// Initialize the intc sw module.
	irq_initialize_vectors();

	// Register the TC interrupt handler
	irq_register_handler(timer_irq_handler, AVR32_TC0_IRQ0, 3);

	sysclk_enable_pba_module(SYSCLK_TC0);
	AVR32_TC0.channel[0].cmr = AVR32_TC_TCCLKS_TIMER_CLOCK3
		| AVR32_TC_WAVE_MASK;
	AVR32_TC0.channel[0].ier = AVR32_TC_COVFS_MASK;
	AVR32_TC0.channel[0].ccr = AVR32_TC_CLKEN_MASK | AVR32_TC_SWTRG_MASK;

	Enable_global_interrupt();

	while (1) {
		struct pll_config pllcfg;

		/*
		 * Initial state: Running from OSC0 with all prescalers
		 * disabled.
		 */
		wait_for_switches();

		/*
		 * Divide PBA frequency by 2. This will make the LED
		 * blink half as fast.
		 */
		sysclk_set_prescalers(0, 1, 0);
		wait_for_switches();

		/*
		 * Switch to the slow clock with all prescalers
		 * disabled.
		 */
		sysclk_set_source(SYSCLK_SRC_RCSYS);
		sysclk_set_prescalers(0, 0, 0);
		wait_for_switches();

		/*
		 * Enable the PLL at 132 MHz and use it as system clock
		 * with CPU clock at half the system clock frequency and
		 * PBA clock at 1/4 the system clock frequency.
		 */
		pll_config_init(&pllcfg, PLL_SRC_OSC0, 1,
				132000000 / BOARD_OSC0_HZ);
		pll_enable(&pllcfg, 0);
		pll_wait_for_lock(0);
		sysclk_set_prescalers(1, 2, 1);
		sysclk_set_source(SYSCLK_SRC_PLL0);
		wait_for_switches();

		/*
		 * Go back to the initial state and start over.
		 */
		sysclk_set_source(SYSCLK_SRC_OSC0);
		pll_disable(0);
		sysclk_set_prescalers(0, 0, 0);
	}
}
