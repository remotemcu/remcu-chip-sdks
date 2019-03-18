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
 * - clock_example3_uc3a_uc3b.c: clock system example application
 * - conf_board.h: board initialization configuration
 * - conf_clock.h: system clock configuration
 * - conf_example3.h: chip- or board-specific example configuration
 *
 * \section deviceinfo Device Info
 * All AVR UC3A, UC3A1 and UC3B devices can be used.
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
/**
 * \def STEP4_PLL_OUTPUT_FREQ
 * \brief PLL output frequency for step 4
 *
 * This is the frequency to set the PLL to output once the example application
 * reaches step 4 in the clock setting sequence.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
//@}

#include <compiler.h>
#include <flashc.h>
#include <gpio.h>
#include <pll.h>
#include <sysclk.h>
#include <delay.h>
#include <conf_example3.h>

ISR( timer_irq_handler, AVR32_TC_IRQ_GROUP, 3)
{
	static bool toggle;

	// Slow down the LED a little bit.
	if (toggle)
		gpio_toggle_pin(LED_EXAMPLE_OUTPUT);
	toggle = !toggle;

	// Clear the TC interrupt.
	AVR32_TC.channel[0].sr;
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
	/* Initialize the synchronous clock system to the default configuration
	 * set in conf_clock.h.
	 * Note: all non-essential peripheral clocks are initially disabled.
	 */
	sysclk_init();

	/* Initialize the resources used by this example to the default
	 * configuration set in conf_board.h.
	 */
	board_init();

	Disable_global_interrupt();

	// Initialize the intc sw module.
	irq_initialize_vectors();

	// Register the TC interrupt handler
	irq_register_handler(timer_irq_handler, AVR32_TC_IRQ0, 3);

	/* Enable the clock used by the TC module (because sysclk_init()
	 * disabled it).
	 */
	sysclk_enable_pba_module(SYSCLK_TC);

	/* TC configuration:
	 * - input clock selection: TIMER_CLOCK3
	 * - operating mode: Waveform mode
	 * - Counter overflow interrupt enabled
	 */
	AVR32_TC.channel[0].cmr = AVR32_TC_TCCLKS_TIMER_CLOCK3
			| AVR32_TC_WAVE_MASK;
	AVR32_TC.channel[0].ier = AVR32_TC_COVFS_MASK;
	/* Enable the clock, and perform a software trigger: the counter is
	 * reset and the clock is started.
	 */
	AVR32_TC.channel[0].ccr = AVR32_TC_CLKEN_MASK | AVR32_TC_SWTRG_MASK;

	Enable_global_interrupt();

	while (1) {
		struct pll_config pllcfg;

		/*
		 * Step 1: Running from OSC0 with all prescalers disabled.
		 */
		wait_for_switches();

		/*
		 * Step 2: Divide PBA frequency by 2. This will make the LED
		 * blink half as fast.
		 */
		sysclk_set_prescalers(0, 1, 0);
		wait_for_switches();

		/*
		 * Step 3: Switch the main clock to the slow clock with all
		 * prescalers disabled.
		 */
		sysclk_set_source(SYSCLK_SRC_RCSYS);
		sysclk_set_prescalers(0, 0, 0);
		wait_for_switches();

		/*
		 * Step 4: Enable the PLL at STEP4_PLL_OUTPUT_FREQ MHz and use
		 * it as source of the main clock with CPU clock at half the
		 * main clock frequency and PBA clock at 1/4 of the main clock
		 * frequency.
		 */
		/* Initialize the PLL configuration:
		 * - PLL reference clock: OSC0
		 * - div = 1,
		 * - mul = STEP4_PLL_OUTPUT_FREQ / BOARD_OSC0_HZ
		 * => the PLL output frequency will be running at:
		 * (mul / div) times the frequency of OSC0
		 */
		pll_config_init(&pllcfg, PLL_SRC_OSC0, 1,
				STEP4_PLL_OUTPUT_FREQ / BOARD_OSC0_HZ);
		// Configure and enable the PLL.
		pll_enable(&pllcfg, 0);
		/* Wait for the PLL to become locked (and thus ready to be used
		 * as clock source).
		 */
		pll_wait_for_lock(0);
		/* Set the prescalers applied to the main clock so that:
		 * - CPU & HSB clock == PLL clock/2
		 * - PBA clock == PLL clock/4
		 * - PBB clock == PLL clock/2
		 */
		sysclk_set_prescalers(1, 2, 1);

		/* Before changing the main clock source, set the appropriate
		 * FLASH wait state depending on the new HSB bus frequency.
		 */
		flash_set_bus_freq(STEP4_PLL_OUTPUT_FREQ / 2);

		// Switch the main clock to PLL0.
		sysclk_set_source(SYSCLK_SRC_PLL0);
		wait_for_switches();

		/*
		 * Restore the step 1 configuration and start over.
		 */
		// Switch the main clock to OSC0.
		sysclk_set_source(SYSCLK_SRC_OSC0);
		/* Set the appropriate FLASH wait state depending on the new HSB
		 * bus frequency.
		 */
		flash_set_bus_freq(BOARD_OSC0_HZ);
		// Disable all prescalers.
		sysclk_set_prescalers(0, 0, 0);
		// Disable the PLL0.
		pll_disable(PLL_SRC_OSC0);
	}
}
