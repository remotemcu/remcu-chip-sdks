/**
 * \file
 *
 * \brief Example application 1 for calendar functionality
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <stdint.h>
#include <calendar.h>
#include <asf.h>
#include <led.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is an example application for the \ref calendar_group "calendar"
 * functionality.
 *
 * \section device_info Device Info
 * All AVR devices can be used.
 * This example has been tested with the following setup:
 * - XMEGA-A1 Xplain
 * - UC3-L0 Xplained
 * - STK600+RCUC3L4
 * - STK600 with RCUC3D extension board (Connect STK600.PORTA.PA4 -> STK600.LEDS.LED0)
 *
 * \section description Description of the example application
 * This application will convert a date to a known timestamp, and turn on a
 * LED if the timestamp is correct.
 *
 * \section dependencies Dependencies
 * Relevant module dependencies for this application are:
 * - \ref calendar_group
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for AVR. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */

/**
 * \brief Main entry of example application
 */
int main(void)
{
	board_init();
	sysclk_init();

	// Initialize the platform LED's.
	LED_Off(LED0_GPIO);

	// Randomly selected date to convert to timestamp
	struct calendar_date date = {
		.second = 12,
		.minute = 1,
		.hour = 22,
		.date = 8,
		.month = 2,
		.year = 1985
	};
	uint32_t timestamp = 479253672;

	// Convert date to timestamp
	uint32_t timestamp2 = calendar_date_to_timestamp(&date);

	/*
	* Check that generated timestamp matches provided timestamp and turn on LED
	*/
	if (timestamp == timestamp2) {
		LED_On(LED0_GPIO);
	}

	// Infinite loop
	while(1) {
		// Intentionally left empty.
	};
}
