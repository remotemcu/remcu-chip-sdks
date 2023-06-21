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
 * This example shows how to switch between various system clock sources and
 * prescalers at run time.
 *
 * \section files Main files:
 * - clock_example3_xmega.c: clock system example application
 * - conf_board.h: board initialization configuration
 * - conf_clock.h: system clock configuration
 * - conf_example3.h: chip- or board-specific example configuration
 *
 * \section deviceinfo Device Info
 * All AVR XMEGA devices can be used.
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
		RC32M [label = "RC32M / (16 * 2 * 2)"];
		node [shape = ellipse];
		RC32M_div [label = "RC32M / (128 * 1 * 1)"];
		RC2M [label = "RC2M / (4 * 4 * 1)"];
		PLL [label = "PLL : (RC2M * 4) / (128 * 1 * 1)"];

		RC32M -> RC32M_div;
		RC32M_div -> RC2M;
		RC2M -> PLL;
		PLL -> RC32M;
	}
 * \enddot
 *
 * Note that the state diagram indicates the prescaling from the clock source to
 * each of the available clock signals: clk_PER4, clk_PER2 and clk_PER +
 * clk_CPU.
 *
 * The clock frequency decreases with each step in the sequence, until it resets
 * to the initial clock setting. A timer/counter (\ref LED_TC,
 * \ref TC_SYSCLK_PORT and \ref TC_SYSCLK_MODULE) is used in PWM mode to blink a
 * LED, thus giving a visual indication of the peripheral clock frequency.
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
 * \def LED_TC
 * \brief Timer/counter to use for LED output
 *
 * This is the timer/counter module to use for outputting a signal indicating
 * the peripheral clock frequency of the device. Compare/capture channel A of
 * the timer/counter is used in this example, corresponding to pin 0 on its
 * associated port.
 */
/**
 * \def TC_SYSCLK_PORT
 * \brief Timer/counter port
 *
 * This specifies to the \ref sysclk_group which port the timer/counter is on.
 */
/**
 * \def TC_SYSCLK_MODULE
 * \brief Timer/counter module
 *
 * This specifies to the \ref sysclk_group which timer/counter on the port to
 * enable the peripheral clock for.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
//@}

#include <compiler.h>
#include <ioport.h>
#include <sysclk.h>
#include <delay.h>
#include <conf_example3.h>

static void wait_for_switches(void)
{
	do { } while (ioport_pin_is_high(NEXT_BUTTON));
	delay_ms(5);
	do { } while (ioport_pin_is_low(NEXT_BUTTON));
	delay_ms(5);
}

static void tc_init(void)
{
	// Configure PWM output on the TC's CCA, with 50% duty cycle.
	sysclk_enable_module(TC_SYSCLK_PORT, SYSCLK_TC0);
	sysclk_enable_module(TC_SYSCLK_PORT, SYSCLK_HIRES);

	LED_TC.CTRLB = TC_WGMODE_SS_gc | TC0_CCAEN_bm;
	LED_TC.PER = 0xffff;
	LED_TC.CCA = 0x8000;
	LED_TC.CTRLA = TC_CLKSEL_DIV1_gc;
}

int main(void)
{
	sysclk_init();
	board_init();

	// Start TC and configure pin to get PWM output to LED.
	tc_init();

	while (1) {
		struct pll_config pcfg;

		/*
		 * Initial state: Running from RC32M prescalers with 16x
		 * prescaling of CLKsys, 2x prescaling for CLKper2 and 2x
		 * prescaling for CLKper.
		 */
		wait_for_switches();

		/*
		 * Prescale CLKsys by 128x, prescale all peripheral clocks by 1.
		 */
		sysclk_set_prescalers(SYSCLK_PSADIV_128, SYSCLK_PSBCDIV_1_1);
		wait_for_switches();

		/*
		 * Switch to RC2M with 4x prescaling of CLKsys, 4x prescaling
		 * for CLKper2 and 1x prescaling for CLKper.
		 */
		osc_enable(OSC_ID_RC2MHZ);
		do {} while (!osc_is_ready(OSC_ID_RC2MHZ));
		sysclk_set_source(SYSCLK_SRC_RC2MHZ);
		sysclk_set_prescalers(SYSCLK_PSADIV_4, SYSCLK_PSBCDIV_4_1);
		osc_disable(OSC_ID_RC32MHZ);
		wait_for_switches();

		/*
		 * Switch to PLL with RC2M as reference and 4x multiplier.
		 * Prescale CLKsys by 128x, and all peripheral clocks by 1x.
		 */
		pll_config_init(&pcfg, PLL_SRC_RC2MHZ, 1, 4);
		pll_enable(&pcfg, 0);
		do {} while (!pll_is_locked(0));
		sysclk_set_prescalers(SYSCLK_PSADIV_128, SYSCLK_PSBCDIV_1_1);
		sysclk_set_source(SYSCLK_SRC_PLL);
		wait_for_switches();

		/*
		 * Go back to the initial state and start over.
		 */
		osc_enable(OSC_ID_RC32MHZ);
		do {} while(!osc_is_ready(OSC_ID_RC32MHZ));
		sysclk_set_source(SYSCLK_SRC_RC32MHZ);
		sysclk_set_prescalers(SYSCLK_PSADIV_16, SYSCLK_PSBCDIV_2_2);
		pll_disable(0);
		osc_disable(OSC_ID_RC2MHZ);
	}
}
