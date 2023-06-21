/**
 * \file
 *
 * \brief Clock system example 2
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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
 * - clock_example2_xmega.c: clock system example application
 * - conf_board.h: board initialization configuration
 * - conf_clock.h: system clock configuration
 * - conf_example2.h: chip- or board-specific example configuration
 *
 * \section deviceinfo Device Info
 * All AVR XMEGA devices can be used.
 *
 * \section exampledescription Description of the example
 * Pin 7 (\ref IOPORT_PIN) on a configurable port (\ref CLKOUT_PORT) is used for
 * output of the CPU clock signal.
 *
 * The main system clock source and prescalers are defined in conf_clock.h.
 * The port to output the clock signal on is defined in conf_example2.h.
 *
 * Refer to the \ref clk_group API documentation for further information on the
 * clock configuration, and the \ref port_driver_group API documentation for
 * further information on the pin configuration.
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
 * \def CLKOUT_PORT
 * \brief Port to output clock signal on
 *
 * This is the configuration for the clock output port, and must be defined as
 * one of the \c PORTCFG_CLKOUT_t settings of the device header file.
 *
 * \note It is only possible to select the port, not the pin: the clock signal
 * will be output on pin 7 of the configured port.
 */
/**
 * \def IOPORT_PIN
 * \brief Pin to set as output for clock signal
 *
 * This must be defined as IOPORT pin 7 of the port setting in CLKOUT_PORT.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
//@}

#include <compiler.h>
#include <sysclk.h>
#include <ioport.h>
#include <conf_example2.h>

int main(void)
{
	sysclk_init();
	board_init();

	ioport_configure_pin(IOPORT_PIN, IOPORT_DIR_OUTPUT);
	PORTCFG.CLKEVOUT = CLKOUT_PORT;

	while (1) {
		/* Do nothing */
	}
}
