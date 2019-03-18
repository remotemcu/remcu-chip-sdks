/*
 * \file
 *
 * \brief LED module for ATSHA204 examples
 *
 * This file contains helper functions that use Xplained board LED's to indicate
 * success or failure and byte values (device version for instance).
 *
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

#include <stdio.h>
#include "asf.h"
#include "compiler.h"
#include "preprocessor.h"
#include "led.h"
#include "sha204_example_led.h"
#include "sha204_timer.h"


/** \brief This function displays a byte value using the Xplained LEDs.
    \param[in] value byte to display
*/
void led_display_number(uint8_t value)
{
   int i;
   int shifter;
   int led[] = {LED0_GPIO, LED1_GPIO, LED2_GPIO, LED3_GPIO, LED4_GPIO, LED5_GPIO, LED6_GPIO, LED7_GPIO};
   
   for (i = 0, shifter = 1; i < 8; i++, shifter <<= 1) {
	   if (shifter & value)
	      LED_On(led[i]);
	   else
	      LED_Off(led[i]);
   }
}


/** 
 * \brief This function displays information using LEDs about the SHA204 devices 
 *        on the Security Xplained board.
 * \param[in] device_present_mask The high nibble represents the four SHA204 devices.
 * \param[in] sha204_revision revision of the SHA204 devices
 */
void display_status(uint8_t device_present_mask, uint8_t sha204_revision)
{
	uint8_t i;
	uint8_t shifter = 1;

	// Find out how many devices are present.
	for (i = 0; shifter < 0x10; shifter <<= 1)
		if (shifter & device_present_mask)
			i++;

	if (i < SHA204_DEVICE_COUNT) {
		// Indicate communication failure.
		// Display the devices found using LED4..7 and error using LED0..3.
		uint8_t i;
		for (i = 0; i < 4; i++) {
			led_display_number(~device_present_mask);
			sha204h_delay_ms(125);
			led_display_number(0);
			sha204h_delay_ms(125);
		}
	}
	else {
		// Indicate success.
		// Display the devices found using LED4..7 and revision of last device using LED0..3.
		led_display_number((device_present_mask << 4) | sha204_revision);
		sha204h_delay_ms(1000);
		led_display_number(0);
		sha204h_delay_ms(1000);
	}	  
}
