/**
 * \file
 *
 * \brief Example application 2 for calendar functionality.
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
 * This application will calculate the time difference in years, months, days,
 * hours, minutes and seconds between two dates and turn on a LED if it is
 * correct.
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

	struct calendar_date duration;
	struct calendar_date result;
	struct calendar_date end_date;
	struct calendar_date start_date;

	// Randomly selected timestamps
	uint32_t end_timestamp = 1309174659;
	uint32_t start_timestamp = 123456789;

	// The actual duration between the timestamps
	duration.year = 37;
	duration.month = 6;
	duration.date = 28;
	duration.hour = 14;
	duration.minute = 4;
	duration.second = 30;

	// Convert the timestamps to dates
	calendar_timestamp_to_date(end_timestamp, &end_date);
	calendar_timestamp_to_date(start_timestamp, &start_date);

	// Calculate the time difference between the timestamps
	calendar_time_between_dates(&end_date, &start_date, &result);

	/*
	* Check that all parameters of the computed result equals all parameters
	* of duration, and turn on LED.
	*/
	if ((duration.year == result.year) && (duration.month == result.month) &&
			(duration.date == result.date) && (duration.hour == result.hour) &&
			(duration.minute == result.minute) &&
			(duration.second == result.second)) {

		LED_On(LED0_GPIO);
	}

	// Infinite loop
	while(1) {
		// Intentionally left empty.
	};
}
