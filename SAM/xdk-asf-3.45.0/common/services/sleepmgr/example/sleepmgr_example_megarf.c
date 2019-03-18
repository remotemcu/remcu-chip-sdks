/**
 * \file
 *
 * \brief Sleep manager example for MegaRF
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
 * This simple example shows how to use the \ref sleepmgr_group.
 *
 * \section files Main files:
 * - sleepmgr_example_megarf.c: Sleep manager example application
 *
 * \section apiinfo Sleep manager API
 * The sleep manager API can be found \ref sleepmgr_group "here".
 *
 * \section deviceinfo Device Info
 * The example has been tested on the STK600 kit.
 *
 * \section exampledescription Description of the example
 * This example puts the device to sleep in sleep modes with increasing "depth"
 * and utilizes the external interrupt to wake it up again.
 *
 * For measuring the current consumption in various sleep mode, an ammeter can
 * be connected on JS2 of ATmega128RFA1-EK1 kit.
 *
 * The device will remain in ACTIVE mode for approximately 3 seconds after wake-
 * up, before it goes to sleep in the next mode.
 *
 * The Yellow Led in ATmega128RFA1-EK1 is On when the device is in active mode
 * and is in off state during sleep. Pressing the pushbutton on the kit will
 * wake the device up and goes to next sleep mode in the following order.
 *		Idle mode.
 *		Power Down mode.
 *	    Power Save mode.
 *		Standby mode.
 *      Extended Standby mode.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for AVR.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/">Microchip</A>.\n
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include "conf_example.h"

/** \brief Main function.
 */
int main(void)
{
	/* Set the sleep mode to initially lock. */
	volatile enum sleepmgr_mode mode = SLEEPMGR_ACTIVE;
    /* Initialize the pins for input and output. */
	board_init();
    /* Initialize the clock and disable clock unused modules */
	sysclk_init();
    /* Initialize the IOPORT */
	ioport_init();
	delay_init(sysclk_get_cpu_hz());

	/* Set the pin sense mode */
	ioport_set_pin_sense_mode(BUTTON_PIN, IOPORT_SENSE_LEVEL);
    
    /* Enable external interrupt */
	external_interrupt_enable(BUTTON_NUMBER);

	/* Turn off the LED		*/
	LED_On(LED_PIN);

	/* Initialize the sleep manager, lock initial mode. */
	sleepmgr_init();
	sleepmgr_lock_mode(mode);

	Enable_global_interrupt();

	do {
		/* Delay for 3 seconds to show the device is awake. */
		delay_ms(3000);

		/* Turn off the LED and go to sleep. */
		LED_Off(LED_PIN);
		sleepmgr_enter_sleep();

		/* Turn on the LED on wake up */
		LED_On(LED_PIN);

		/* Unlock current mode, then lock the next one. */
		sleepmgr_unlock_mode(mode);
		if (++mode < SLEEPMGR_NR_OF_MODES) {
			sleepmgr_lock_mode(mode);
		} else {
			mode = SLEEPMGR_ACTIVE;
			sleepmgr_lock_mode(mode);
		}
	} while (1);
}

ISR(BUTTON_vect)
{
	/* Wait for button release before continuing. */
	delay_ms(10);
	do {
	} while (!ioport_get_pin_level(BUTTON_PIN));
}


