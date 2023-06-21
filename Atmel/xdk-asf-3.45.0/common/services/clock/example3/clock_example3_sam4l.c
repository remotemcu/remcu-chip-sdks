/**
 * \file
 *
 * \brief Clock system example 3
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

/**
 * \mainpage
 *
 * \section intro Introduction
 * This example shows how to switch between various system clock sources
 * and prescalers at run time.
 *
 * \section files Main files:
 * - clock_example3_sam4l.c: clock system example application
 * - conf_board.h: board initialization configuration
 * - conf_clock.h: system clock configuration
 * - conf_example3.h: chip- or board-specific example configuration
 *
 * \section deviceinfo Device Info
 * All SAM4L devices can be used.
 *
 * \section exampledescription Description of the example
 * The clock system is reconfigured every time the user presses a button
 * (\ref NEXT_BUTTON) to use the next clock source and prescaler settings
 * shown in the state diagram below.
 *
 * \par Sequence of clock source and prescaler settings
 * \dot
 *      digraph clock_example {
 *              node [shape = doublecircle];
 *              RC80M [label = "RC80M / 4"];
 *              node [shape = ellipse];
 *              RC80M_DIV [label = "RC80M / 8"];
 *              DFLL_OPEN [label = "DFLL Open Loop / 1"];
 *              RCSYS [label = "RCSYS"];
 *              RCFAST [label = "RCFAST"];
 *              RC1M [label = "RC1M"];
 *              OSC0 [label = "OSC0"];
 *              PLL0 [label = "PLL0 / 4"];
 *              DFLL_CLOSED [label = "DFLL Closed Loop / 1"];
 *
 *              RC80M -> RC80M_DIV;
 *              RC80M_DIV -> DFLL_OPEN;
 *              DFLL_OPEN -> RCSYS;
 *              RCSYS -> RCFAST;
 *              RCFAST -> RC1M;
 *              RC1M -> OSC0 [label = "OSC0 on board"];
 *              OSC0 -> PLL0 [label = "PLL0 with OSC0 on board"];
 *              PLL0 -> DFLL_CLOSED;
 *              RC1M -> DFLL_CLOSED [label = "OSC0 not on board"];
 *              DFLL_CLOSED -> RC80M;
 *      }
 * \enddot
 *
 * The Systick is used to generate periodic interrupts based on its CPU clock.
 * With each interrupt, a LED (\ref LED_EXAMPLE_OUTPUT) is toggled,
 * thus giving a visual indication of the system clock frequency.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for SAM.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/">Microchip</A>.\n
 */

/** \name Example configuration */
/* @{ */

/**
 * \def NEXT_BUTTON
 * \brief Pin to use for button input
 *
 * This is the active low pin to use for user input.
 *
 * \note The pin is assumed to be configured by the board initialization.
 */
/* @} */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <conf_example3.h>

void SysTick_Handler(void)
{
	ioport_toggle_pin_level(LED_EXAMPLE_OUTPUT);
}

static void wait_for_switches(void)
{
	do { } while (ioport_get_pin_level(NEXT_BUTTON));
	delay_ms(1);
	do { } while (!ioport_get_pin_level(NEXT_BUTTON));
	delay_ms(1);
}

int main(void)
{
	sysclk_init();
	board_init();

	/* Enable one wait state for flash access */
	flashcalw_set_wait_state(1);

	/*
	 * Configure systick for 200ms (CPU frequency / 5) at startup time.
	 *
	 * Note: CPU frequency will be changed with below clock switching.
	 */
	if (SysTick_Config(sysclk_get_cpu_hz() / 5)) {
		while (1) { /* Capture error */
		}
	}

	while (1) {
		struct dfll_config dcfg;
		struct pll_config pcfg;
		/* avoid Cppcheck Warning */
		UNUSED(pcfg);

		/*
		 * Initial state: Running from RC80M with all
		 * prescalers set to 2 (Divide frequency by 4).
		 */
		wait_for_switches();

		/*
		 * Divide CPU frequency by 8. This will make the LED
		 * blink half as fast.
		 */
		sysclk_set_prescalers(3, 3, 3, 3, 3);
		wait_for_switches();

		/*
		 * Switch to the DFLL running at ~48 MHz in Open Loop
		 * mode, with the CPU running at ~48 MHz.
		 */
		dfll_config_init_open_loop_mode(&dcfg);
		dfll_config_tune_for_target_hz(&dcfg, 48000000);
		dfll_enable_open_loop(&dcfg, 0);
		sysclk_set_prescalers(1, 1, 1, 1, 1);
		sysclk_set_source(SYSCLK_SRC_DFLL);
		osc_disable(OSC_ID_RC80M);
		wait_for_switches();

		/*
		 * Switch to the slow clock with all prescalers
		 * disabled.
		 */
		sysclk_set_source(SYSCLK_SRC_RCSYS);
		sysclk_set_prescalers(0, 0, 0, 0, 0);
		dfll_disable_open_loop(0);
		wait_for_switches();

		/*
		 * Switch to the RCFAST clock with all prescalers
		 * disabled.
		 */
		osc_enable(OSC_ID_RCFAST);
		sysclk_set_prescalers(0, 0, 0, 0, 0);
		osc_wait_ready(OSC_ID_RCFAST);
		sysclk_set_source(SYSCLK_SRC_RCFAST);
		wait_for_switches();

		/*
		 * Switch to the RC1M clock with all prescalers
		 * disabled.
		 */
		osc_enable(OSC_ID_RC1M);
		sysclk_set_prescalers(0, 0, 0, 0, 0);
		osc_wait_ready(OSC_ID_RC1M);
		sysclk_set_source(SYSCLK_SRC_RC1M);
		osc_disable(OSC_ID_RCFAST);
		wait_for_switches();

		/*
		 * Switch to external OSC0, if available.
		 */
#ifdef BOARD_OSC0_HZ
		osc_enable(OSC_ID_OSC0);
		osc_wait_ready(OSC_ID_OSC0);
		sysclk_set_source(SYSCLK_SRC_OSC0);
		osc_disable(OSC_ID_RC1M);
		wait_for_switches();

		/*
		 * Switch to PLL0 running at 96 MHz. Use OSC0 as the
		 * source
		 */
		pll_config_init(&pcfg, PLL_SRC_OSC0, 1, 96000000 /
				BOARD_OSC0_HZ);
		pll_enable(&pcfg, 0);
		sysclk_set_prescalers(2, 2, 2, 2, 2);
		pll_wait_for_lock(0);
		sysclk_set_source(SYSCLK_SRC_PLL0);
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
				CONFIG_DFLL0_FREQ / BOARD_OSC32_HZ);
		osc_wait_ready(OSC_ID_OSC32);
#else
		dfll_config_init_closed_loop_mode(&dcfg,
				GENCLK_SRC_RCSYS, 1,
				CONFIG_DFLL0_FREQ / OSC_RCSYS_NOMINAL_HZ);
#endif
		dfll_enable_closed_loop(&dcfg, 0);
		sysclk_set_prescalers(1, 1, 1, 1, 1);
		dfll_wait_for_fine_lock(0);
		sysclk_set_source(SYSCLK_SRC_DFLL);
#ifdef BOARD_OSC0_HZ
		osc_disable(OSC_ID_OSC0);
#endif
		wait_for_switches();

		/*
		 * Go back to the initial state and start over.
		 */
		osc_enable(OSC_ID_RC80M);
		sysclk_set_prescalers(2, 2, 2, 2, 2);
		osc_wait_ready(OSC_ID_RC80M);
		sysclk_set_source(SYSCLK_SRC_RC80M);
		dfll_disable_closed_loop(0);
#ifdef BOARD_OSC32_HZ
		osc_disable(OSC_ID_OSC32);
#endif
	}
}
