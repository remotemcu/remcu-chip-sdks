/**
 * \file
 *
 * \brief Clock system example 2
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
 * This example shows how to initialize the clock system and output the
 * CPU clock on a dedicated pin.
 *
 * \section files Main files:
 * - clock_example2_uc3.c: clock system example application
 * - conf_board.h: board initialization configuration
 * - conf_clock.h: system clock configuration
 * - conf_example2.h: chip- or board-specific example configuration
 *
 * \section deviceinfo Device Info
 * All AVR UC3 devices can be used.
 *
 * \section exampledescription Description of the example
 * This example makes use of the output GPIO function for a generic clock to
 * output the CPU clock on a pin.
 *
 * The generic clock and its corresponding GPIO pin and function are defined in
 * conf_example2.h.
 * The main system clock source and prescalers, along with any PLL
 * and/or DFLL configuration, if supported, are defined in conf_clock.h.
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
 * \def GCLK_ID
 * \brief Generic clock ID
 *
 * This is the ID of the generic clock to use.
 */
/**
 * \def GCLK_PIN
 * \brief Generic clock output GPIO pin
 *
 * This is the GPIO pin on which the generic clock signal will be output.
 *
 * \note Not all GPIO pins can be used for this purpose. Refer to the device's
 * datasheet or device header file for details on which GPIO pins can be used
 * for output of the individual generic clocks.
 */
/**
 * \def GCLK_FUNCTION
 * \brief Generic clock function for GPIO pin
 *
 * This is the GPIO function for output of the generic clock with the configured
 * ID on the GPIO pin.
 */
/**
 * \def GCLK_SOURCE
 * \brief Generic clock source
 *
 * This is the clock source to use for the generic clock.
 */
/**
 * \def GCLK_DIV
 * \brief Generic clock divider
 *
 * This is how much the generic clock should divide the frequency of the
 * configured clock source by.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
//@}

#include <compiler.h>
#include <genclk.h>
#include <gpio.h>
#include <sysclk.h>
#include <conf_example2.h>

int main(void)
{

	sysclk_init();
	board_init();

	genclk_enable_config(GCLK_ID, GCLK_SOURCE, GCLK_DIV);

	/* Enable GPIO Alternate to output GCLK*/
	gpio_enable_module_pin(GCLK_PIN,GCLK_FUNCTION);

	while (1) {
		/* Do nothing */
	}
}

