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
 * - clock_example3_uc3l.c: clock system example application
 * - conf_board.h: board initialization configuration
 * - conf_clock.h: system clock configuration
 * - conf_example3.h: chip- or board-specific example configuration
 *
 * \section deviceinfo Device Info
 * All AVR UC3L devices can be used.
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
		RC120M [label = "RC120M / 8"];
		node [shape = ellipse];
		RC120M_DIV [label = "RC120M / 16"];
		DFLL_OPEN [label = "DFLL Open Loop / 8"];
		RCSYS [label = "RCSYS"];
		OSC0 [label = "OSC0"];
		DFLL_CLOSED [label = "DFLL Closed Loop / 4"];

		RC120M -> RC120M_DIV;
		RC120M_DIV -> DFLL_OPEN;
		DFLL_OPEN -> RCSYS;
		RCSYS -> OSC0 [label = "OSC0 on board"];
		RCSYS -> DFLL_CLOSED [label = "OSC0 not on board"];
		OSC0 -> DFLL_CLOSED;
		DFLL_CLOSED -> RC120M;
	}
 * \enddot
 *
 * The Asynchronous Timer (AST) is used to generate periodic interrupts based on
 * its peripheral bus clock. With each interrupt,
 * a LED (\ref LED_EXAMPLE_OUTPUT) is toggled,
 * thus giving a visual indication of the system clock frequency.
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
#include <dfll.h>
#include <sysclk.h>
#include <delay.h>
#include <conf_example3.h>

ISR( timer_irq_handler, AVR32_AST_IRQ_GROUP1, 3)
{
	AVR32_AST.scr = AVR32_AST_PER0_MASK;
	gpio_toggle_pin(LED_EXAMPLE_OUTPUT);
	while (AVR32_AST.sr & AVR32_AST_BUSY_MASK);
}

static void wait_for_switches(void)
{
	do { } while (gpio_pin_is_high(NEXT_BUTTON));
	delay_ms(1);
	do { } while (gpio_pin_is_low(NEXT_BUTTON));
	delay_ms(1);
}

static void ast_init(void)
{
	uint32_t clock;

	sysclk_enable_pba_module(SYSCLK_AST);
	clock = AVR32_AST_CLOCK_CSSEL_PBCLOCK << AVR32_AST_CSSEL;
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
		struct dfll_config dcfg;

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
		 * Switch to the DFLL running at ~50 MHz in Open Loop
		 * mode, with the CPU running at 25 MHz and PBA at 12.5
		 * MHz.
		 */
		dfll_config_init_open_loop_mode(&dcfg);
		dfll_config_tune_for_target_hz(&dcfg, 50000000);
		dfll_enable_open_loop(&dcfg, 0);
		sysclk_set_prescalers(2, 3, 2);
		sysclk_set_source(SYSCLK_SRC_DFLL);
		osc_disable(OSC_ID_RC120M);
		wait_for_switches();

		/*
		 * Switch to the slow clock with all prescalers
		 * disabled.
		 */
		sysclk_set_source(SYSCLK_SRC_RCSYS);
		sysclk_set_prescalers(0, 0, 0);
		dfll_disable_open_loop(0);
		wait_for_switches();

		/*
		 * Switch to external OSC0, if available.
		 */
#ifdef BOARD_OSC0_HZ
		osc_enable(OSC_ID_OSC0);
		osc_wait_ready(OSC_ID_OSC0);
		sysclk_set_source(SYSCLK_SRC_OSC0);
		wait_for_switches();
#endif

		/*
		 * Switch to the DFLL, using the 32 kHz oscillator as a
		 * reference if available, or failing that, the 115 kHz
		 * RCSYS oscillator.
		 */
#ifdef BOARD_OSC32_HZ
		osc_enable(OSC_ID_OSC32);
		dfll_config_init_closed_loop_mode(&dcfg,
				GENCLK_SRC_OSC32K, 1,
				50000000 / BOARD_OSC32_HZ);
		osc_wait_ready(OSC_ID_OSC32);
#else
		dfll_config_init_closed_loop_mode(&dcfg,
				GENCLK_SRC_RCSYS, 1,
				50000000 / OSC_RCSYS_NOMINAL_HZ);
#endif
		dfll_enable_closed_loop(&dcfg, 0);
		sysclk_set_prescalers(1, 2, 1);
		dfll_wait_for_fine_lock(0);
		sysclk_set_source(SYSCLK_SRC_DFLL);
#ifdef BOARD_OSC0_HZ
		osc_disable(OSC_ID_OSC0);
#endif
		wait_for_switches();

		/*
		 * Go back to the initial state and start over.
		 */
		osc_enable(OSC_ID_RC120M);
		sysclk_set_prescalers(3, 3, 3);
		osc_wait_ready(OSC_ID_RC120M);
		sysclk_set_source(SYSCLK_SRC_RC120M);
		dfll_disable_closed_loop(0);
#ifdef BOARD_OSC32_HZ
		osc_disable(OSC_ID_OSC32);
#endif
	}
}
