/**
 * \file
 *
 * \brief Clock system example 2.
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
 * This example shows how to initialize the clock system and output the
 * CPU clock on pin PCK0 (please refer to datasheet for PIN number).
 * \note For SAM4C_EK, PCK2 is used.
 *
 * \section files Main files:
 * - clock_example2_sam.c: clock system example application
 * - conf_board.h: board initialization configuration
 * - conf_clock.h: system clock configuration
 * - conf_example2.h: chip- or board-specific example configuration
 *
 * \section deviceinfo Device Info
 * All SAM devices can be used.
 *
 * \section exampledescription Description of the example
 * This example makes use of the output GPIO function for a generic clock to
 * output the CPU clock on pin PCK0 (please refer to datasheet for PIN number).
 *
 * The generic clock and its corresponding GPIO pin and function are defined in
 * conf_example2.h.
 * The main system clock source and prescalers, along with any PLL
 * and/or DFLL configuration, if supported, are defined in conf_clock.h.
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
#include "genclk.h"
#include "conf_board.h"
#include "conf_example2.h"

/** Programmable Clock ID for the example by default */
#ifndef GCLK_ID
#define GCLK_ID         GENCLK_PCK_0
#endif

/**
 * \brief Initialize the clock system and output the CPU clock on pin
 * PCK0 (please refer to datasheet for PIN number).
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	struct genclk_config gcfg;

	sysclk_init();
	board_init();

	/* Configure specific CLKOUT pin */
	ioport_set_pin_mode(GCLK_PIN, GCLK_PIN_MUX);
	ioport_disable_pin(GCLK_PIN);

	/* Configure the output clock */
	genclk_config_defaults(&gcfg, GCLK_ID);
	genclk_config_set_source(&gcfg, GCLK_SOURCE);
	genclk_config_set_divider(&gcfg, GCLK_DIV);
	genclk_enable(&gcfg, GCLK_ID);

	while (1) {
		/* Do nothing */
	}
}

