/**
 * \file
 *
 * \brief Clock system example 3.
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
 * This example shows how to switch between various system clock sources
 * and prescalers at run time.
 *
  * \section files Main files:
 * - clock_example3_uc3d.c: clock system example application
 * - conf_board.h: board initialization configuration
 * - conf_clock.h: system clock configuration
 * - conf_example3.h: chip- or board-specific example configuration
 *
 * \section deviceinfo Device Info
 * All AVR UC3D devices can be used.
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
		RC120M [label = "RC120M"];
		node [shape = ellipse];
		RC120M_DIV [label = "RC120 / 4"];
		RCSYS;
		OSC0;
		PLL0 [label = "PLL0 / 2"];

		RC120M -> RC120M_DIV [label="Push button"];
		RC120M_DIV -> RCOSC [label="Push button"];
		RCOSC -> OSC0 [label="Push button"];
		RCSYS -> PLL0 [label="Push button"];
		OSC0 -> RC120M [label="Push button"];

	}
 * \enddot
 *
 * The Asynchronous Timer (AST) is used to generate periodic interrupts based on
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
 * Support and FAQ: https://www.microchip.com/support/
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
#include <conf_example3.h>

static void mdelay(unsigned int ms)
{
	int32_t count, count_end;

	count = Get_system_register(AVR32_COUNT);
	count_end = count + ((sysclk_get_cpu_hz() + 999) / 1000) * ms;

	while ((count_end - count) > 0)
		count = Get_system_register(AVR32_COUNT);
}

ISR( timer_irq_handler, AVR32_AST_IRQ_GROUP1, 3)
{
	AVR32_AST.scr = AVR32_AST_PER0_MASK;
	gpio_toggle_pin(LED_EXAMPLE_OUTPUT);
	while (AVR32_AST.sr & AVR32_AST_BUSY_MASK);
}

static void wait_for_switches(void)
{
	do { } while (gpio_pin_is_high(NEXT_BUTTON));
	mdelay(1);
	do { } while (gpio_pin_is_low(NEXT_BUTTON));
	mdelay(1);
}

static void ast_init(void)
{
	uint32_t clock;

	sysclk_enable_pba_module(SYSCLK_AST);
	clock = 2 << AVR32_AST_CSSEL;
	AVR32_AST.clock = clock;
	clock |= AVR32_AST_CEN_MASK;
	while (AVR32_AST.sr & AVR32_AST_CLKBUSY_MASK) {
		/* Do nothing */
	}
	AVR32_AST.clock = clock;
	while (AVR32_AST.sr & AVR32_AST_CLKBUSY_MASK) {
		/* Do nothing */
	}

	AVR32_AST.cr = AVR32_AST_EN_MASK;
	while (AVR32_AST.sr & AVR32_AST_BUSY_MASK);
	AVR32_AST.pir0 = 18;
	while (AVR32_AST.sr & AVR32_AST_BUSY_MASK);
	AVR32_AST.scr = AVR32_AST_PER0_MASK;
	while (AVR32_AST.sr & AVR32_AST_BUSY_MASK);
	AVR32_AST.ier = AVR32_AST_PER0_MASK;
}

int main(void)
{
	/* Enable one wait state for flash access */
	AVR32_FLASHCDW.fcr = AVR32_FLASHCDW_FWS_MASK;

	sysclk_init();
	board_init();

	// Initialize the intc sw module.
	irq_initialize_vectors();

	// Register the TC interrupt handler
	irq_register_handler(timer_irq_handler, AVR32_AST_PER_IRQ, 3);

	ast_init();
	Enable_global_interrupt();

	while (1) {
		struct pll_config pcfg;

		/*
		 * Initial state: Running from RC120M with all
		 * prescalers set to 2**3.
		 */
		wait_for_switches();

		/*
		 * Divide PBA frequency by 2. This will make the LED
		 * blink half as fast.
		 */
		sysclk_set_prescalers(3, 4, 3);
		wait_for_switches();

		/*
		 * Switch to the slow clock with all prescalers
		 * disabled.
		 */
		sysclk_set_source(SYSCLK_SRC_RCSYS);
		sysclk_set_prescalers(0, 0, 0);
		osc_disable(OSC_ID_RC120M);
		wait_for_switches();

		/*
		 * Switch to OSC0, if available on the board
		 */
		osc_enable(OSC_ID_OSC0);
		osc_wait_ready(OSC_ID_OSC0);
		sysclk_set_source(SYSCLK_SRC_OSC0);
		wait_for_switches();

		/*
		 * Switch to PLL0 running at 80 MHz. Use OSC0 as the
		 * source
		 */
		pll_config_init(&pcfg, PLL_SRC_OSC0, 1, 80000000 / BOARD_OSC0_HZ);
		pll_enable(&pcfg, 0);
		sysclk_set_prescalers(1, 1, 1);
		pll_wait_for_lock(0);
		sysclk_set_source(SYSCLK_SRC_PLL0);
		wait_for_switches();

		/*
		 * Go back to the initial state and start over.
		 */
		osc_enable(OSC_ID_RC120M);
		osc_wait_ready(OSC_ID_RC120M);
		sysclk_set_prescalers(3, 3, 3);
		sysclk_set_source(SYSCLK_SRC_RC120M);
		pll_disable(0);
		osc_disable(OSC_ID_OSC0);
	}
}
