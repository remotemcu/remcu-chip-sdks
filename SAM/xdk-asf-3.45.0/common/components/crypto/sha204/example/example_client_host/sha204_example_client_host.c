/**
 * \file
 *
 * \brief ATSHA204 example module
 *
 * This file contains the main function and some helper functions.
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

/**
 * \mainpage ATSHA204 Example 2 for Security Xplained
 *
 * \par Purpose
 *
 * Client-host communication example with two ATSHA204 devices.
 *
 * \par Description
 *
 * In an infinite loop, sends a Mac command to an ATSHA204 device serving as
 * a client, and sends a CheckMac command with the Mac challenge / response
 * data to a second ATSHA204 device that serves as a host. Helper functions log
 * the commands and responses through the USB-CDC board controller in hex-ascii.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <string.h>
#include <stdio.h>
#include "asf.h"
#include "compiler.h"
#include "preprocessor.h"
#include "board.h"
#include "sysclk.h"
#include "sha204_example_led.h"
#include "sha204_example_log.h"
#include "sha204_timer.h"
#include "sha204_command_marshaling.h"
#include "sha204_lib_return_codes.h"
#include "security_xplained.h"


void sha204_sleep_all(void);


/** \brief This function puts all devices to sleep.
*/
void sha204_sleep_all(void)
{
	uint8_t i;
	for (i = 1; i < SHA204_DEVICE_COUNT; i++) {
		sha204p_set_device_id(sha204_i2c_address(i));

		// Send Sleep command.
		sha204p_sleep();
	}
}


/** \brief This function is the entry function for an example application that
           uses the SHA204 ASF component.
 * \return result (0: success, otherwise failure)
 */
int main(void)
{
	static uint8_t tx_buffer_command[CHECKMAC_COUNT]; // biggest command in this example
	static uint8_t rx_buffer[SHA204_RSP_SIZE_MAX];
	static uint8_t challenge[MAC_CHALLENGE_SIZE];
	static uint8_t other_data[CHECKMAC_OTHER_DATA_SIZE];
	uint8_t sha204_lib_return = SHA204_SUCCESS;
	uint32_t loop_count = 0;
	uint8_t i2c_address_index = 0;
	uint8_t twi_address_client;
	uint8_t twi_address_host;

    // Initialize system clock.
	sysclk_init();

	// Initialize board.
	board_init();

	// Initialize logging (USART).
	log_init();

	// Initialize interrupt vectors.
	irq_initialize_vectors();

	// Send example info.
	log_sha204_title("ATSHA204 Mac / CheckMac Example\r\n");

	// Indicate entering main loop.
	led_display_number(0xFF);
	sha204h_delay_ms(1000);

	// The main loop wakes up all four devices, sends a Mac command to one serving
	// as a client, and subsequently a CheckMac command with the Mac challenge and response data
	// to another SHA204 serving as a host. At the end of the loop, all four devices
	// are put back to sleep by sending a Sleep command to every one of them.
	while (true) {
		// Indicate success or error for some time.
		led_display_number(sha204_lib_return);
		sha204h_delay_ms(1000);

		log_sha204_title("----------------------");
		sprintf((char *) tx_buffer_command, "loop count = %lu", loop_count++);
		log_sha204_title((char *) tx_buffer_command);

		// Indicate that Mac / CheckMac command sequence is running.
		led_display_number(0xFF);

		// Generate Wakeup pulse. All SHA204 devices that share SDA will wake up.
		log_sha204_title("generating 60 us Wakeup low pulse on TWI SDA");
		sha204_lib_return = sha204p_wakeup();
	    if (sha204_lib_return != SHA204_SUCCESS) {
			// todo Indicate Wakeup failure.
			continue;		 
	    }
		// Exercise all four devices.
		twi_address_client = sha204_i2c_address(i2c_address_index % 4);
		i2c_address_index++;
		twi_address_host = sha204_i2c_address(i2c_address_index % 4);
		i2c_address_index++;

		// ---------------------------------------------------------------------------------
		// Now let's send a Mac to one SHA204, and verify the generated Mac with a second
		// SHA204 serving as a host device. In this example, we are not using the Nonce
		// command but the least secure and simplest mode.

		// Let host generate a random number to use as Mac challenge. An unlocked SHA204
		// will always generate "FFFF0000FFFF0000...".
		struct sha204_random_parameters random;
		random.mode = 0;
		random.tx_buffer = tx_buffer_command;
		random.rx_buffer = rx_buffer;
		sha204p_set_device_id(twi_address_host);
		log_sha204_title("sending Random command to host");
		sha204_lib_return = sha204m_random(&random);
		log_sha204(random.tx_buffer[SHA204_COUNT_IDX], random.tx_buffer, false);
	    if (sha204_lib_return != SHA204_SUCCESS) {
			sha204_sleep_all();
			continue;
	    }
		log_sha204(random.rx_buffer[SHA204_COUNT_IDX], random.rx_buffer, true);

		// Save challenge for subsequent CheckMac command.
		memcpy(challenge, &random.rx_buffer[SHA204_BUFFER_POS_DATA], sizeof(challenge));

		// Send Mac command to client.
		struct sha204_mac_parameters mac;
		mac.mode = 0;
		mac.key_id = 0;
		mac.challenge = challenge;
		mac.tx_buffer = tx_buffer_command;
		mac.rx_buffer = rx_buffer;
		sha204p_set_device_id(twi_address_client);
		log_sha204_title("sending Mac command to client");
		sha204_lib_return = sha204m_mac(&mac);
		log_sha204(mac.tx_buffer[SHA204_COUNT_IDX], mac.tx_buffer, false);
	    if (sha204_lib_return != SHA204_SUCCESS) {
			sha204_sleep_all();
			continue;
	    }
		log_sha204(mac.rx_buffer[SHA204_COUNT_IDX], mac.rx_buffer, true);

		// Save first four bytes of Mac command for subsequent CheckMac command.
		memset(other_data, 0, CHECKMAC_OTHER_DATA_SIZE);
		memcpy(other_data, &tx_buffer_command[SHA204_OPCODE_IDX], CHECKMAC_CLIENT_COMMAND_SIZE);

		// Send CheckMac command to host.
		struct sha204_check_mac_parameters check_mac;
		check_mac.mode = 0;
		check_mac.key_id = 0;
		check_mac.client_challenge = challenge;
		check_mac.client_response = &rx_buffer[SHA204_BUFFER_POS_DATA];
		check_mac.other_data = other_data;
		check_mac.tx_buffer = tx_buffer_command;
		check_mac.rx_buffer = rx_buffer;
		sha204p_set_device_id(twi_address_host);
		log_sha204_title("sending CheckMac command to host");
		sha204_lib_return = sha204m_check_mac(&check_mac);
		log_sha204(check_mac.tx_buffer[SHA204_COUNT_IDX], check_mac.tx_buffer, false);
	    if (sha204_lib_return != SHA204_SUCCESS) {
			sha204_sleep_all();
			continue;
	    }
		log_sha204(check_mac.rx_buffer[SHA204_COUNT_IDX], check_mac.rx_buffer, true);

		log_sha204_title("sending a Sleep command to all devices");
		sha204_sleep_all();
		
		// Display response status byte.
		sha204_lib_return = check_mac.rx_buffer[SHA204_BUFFER_POS_STATUS];
	}	

	return sha204_lib_return;
}
