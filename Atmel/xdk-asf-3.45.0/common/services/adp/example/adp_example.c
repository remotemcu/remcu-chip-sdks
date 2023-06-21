/**
 * \file
 *
 * \brief ADP service implementation
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

/**
 * \page asfdoc_common_adp_example ADP Example
 *
 * \section asfdoc_common_adp_example_intro Introduction
 * This simple example shows how to set up communication of the target MCU and 
 * Data Visualizer on PC.
 *
 * \section asfdoc_common_adp_example_files Main files:
 * - \ref adp_example.c : the example itself.
 * - \ref conf_board.h
 * - \ref conf_clocks.h
 * - \ref conf_tc.h
 *
 * \section asfdoc_common_adp_example_deviceinfo Device Info
 * All SAM devices can be used.
 * This example has been tested with the following setup:
 * - SAM D21 Xplained Pro
 * - SAM L21 Xplained Pro
 * - SAM 4S Xplained Pro
 *
 * \section asfdoc_common_adp_example_setup Setup
 * To run the test:
 *  - Connect the IO1 Xplained Pro via EXT1.
 *  - Connect the supported Xplained Pro board to the computer using a
 *    micro USB cable.
 *  - Build the project, program the target and run the application.
 *  - Open Data Visualizer.exe on the computer.
 *  - Select the supported Xplained Pro board, then click "Connect" button 
 *    in Data Visualizer application.
  
 * \section asfdoc_common_adp_example_description Description of the example application
 * This example application will initiate communication with the Data
 * Visualizer on the computer. Set up some elements on the dashboards, 
 * and some data stream between the target mcu and the computer.
 *
 * \section asfdoc_common_adp_example_compinfo Compilation Info
 * This software was written for the GNU GCC and AtmelStudio.
 * Other compilers may or may not work.
 *
 * \section asfdoc_common_adp_example_contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/">Microchip</A>.\n
 */

#include <compiler.h>
#include <asf.h>
#include <string.h>
#include "adp_example_adc.h"
#include "adp_example_tc.h"
#include "adp_window.h"

/* Low hysteresis value */
uint16_t hyst_low = 2300;
/* High hysteresis value */
uint16_t hyst_high = 3000;
bool isLight = false;

/* Length of terminal string */
#define TERMINAL_STRING_LEN 50
/* String holding terminal text */
char terminal_string[TERMINAL_STRING_LEN];
/* Received the packet data buffer */
uint8_t receive_packet_data[MSG_RES_PACKET_DATA_MAX_LEN] = {0,};

/**
* \brief Initiate extension board ioport.
*
*/
static void adp_example_ioport_init(void)
{
	/* Configure LED*/
	ioport_set_pin_dir(USER_LED_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(USER_LED_PIN, USER_LED_INACTIVE);	
}

/**
* \brief Initiate example.
*
*/
static void adp_example_init(void)
{
	adp_init();
	/* Extension board ioport initial */
	adp_example_ioport_init();
	adp_example_adc_init();
	
	while (adp_wait_for_handshake() != ADP_HANDSHAKE_ACCEPTED) {
	}
		
	adp_window_init();
	adp_example_tc_init();
}

/**
* \brief Executive command form PC to the target.
*
*/
static void executive_command(uint8_t* receive_buf)
{
	struct adp_msg_packet_data *receive_buf_s = (struct adp_msg_packet_data *)receive_buf;
	
	switch(receive_buf_s->stream_id) {
		case STREAM_ID_LED_TOGGLE:
			ioport_toggle_pin_level(USER_LED_PIN);
			break;
			
		case STREAM_ID_HYST_LOW:
			if(receive_buf_s->bytes_sent >= 2) {
				hyst_low = (uint16_t)receive_buf_s->data[0] | ((uint16_t)receive_buf_s->data[1] << 8);
			}
			break;
		
		case STREAM_ID_HYST_HIGH:
			if(receive_buf_s->bytes_sent >= 2) {
				hyst_high = (uint16_t)receive_buf_s->data[0] | ((uint16_t)receive_buf_s->data[1] << 8);
			}
			break;
		
		default:
			break;
	}
}

/**
* \brief Send single stream to PC.
*
*/
static void adp_example_transceive_single_stream(uint16_t stream_id, uint8_t* data, \
										uint8_t data_size, uint8_t* receive_buf)
{
	if(adp_transceive_single_stream(stream_id, data, data_size, receive_buf) == true) {
		executive_command(receive_buf);
	}
}

/**
* \brief Send terminal configure to PC.
*
*/
static void adp_example_transceive_terminal(struct adp_msg_conf_terminal *const config, \
										const char* label, uint8_t* receive_buf)
{
	if(adp_configure_terminal(config, label) == true) {
		executive_command(receive_buf);
	}
}

/**
* \brief Read new light sensor value from ADC and handle it.
*
*/
static void transceive_data(void)
{
	uint16_t adc_value;
	float voltage;
	uint8_t status;

	//struct adp_msg_data_stream data_stream;

	/* Get light sensor value */
	adc_value = adp_example_adc_get_value();
	voltage = ((float)adc_value*3.3f)/4096.0f;
	//uint8_t* volt_value = &voltage;
	
	/* Send ADC value to graph and progress bar */
	adp_example_transceive_single_stream(STREAM_ID_LIGHT_SENSOR, (uint8_t*)&voltage, \
										4, receive_packet_data);
	adp_example_transceive_single_stream(STREAM_ID_LIGHT_SENSOR_ADC, \
										(uint8_t *)&adc_value, 2, receive_packet_data);
	
	if((adc_value > hyst_high) & isLight) {		
		status = 0;
		adp_example_transceive_single_stream(STREAM_ID_NIGHT_MODE, &status, 1, \
											receive_packet_data);
		isLight = false;
		
		/* Send string to terminal */
		snprintf(terminal_string, TERMINAL_STRING_LEN,
				"%s", "It got dark... Entered night mode!\r\n");
		adp_example_transceive_single_stream(STREAM_ID_STATUS_MESSAGE, \
											(uint8_t *)&terminal_string, \
											strlen(terminal_string), receive_packet_data);
		/* Set new terminal background color */
		adp_set_color(terminal_config.background_color, ADP_COLOR_BLACK);
		adp_example_transceive_terminal(&terminal_config, TERMINAL_LABEL, receive_packet_data);
	} 
	else if ((adc_value < hyst_low) & (!isLight)) {
		status = 1;
		adp_example_transceive_single_stream(STREAM_ID_NIGHT_MODE, &status, \
											1, receive_packet_data);
		isLight = true;
		
		/* Send string to terminal */
		snprintf(terminal_string, TERMINAL_STRING_LEN,
				"%s", "It's bright again... Entered day mode!\r\n");
		adp_example_transceive_single_stream(STREAM_ID_STATUS_MESSAGE, \
											(uint8_t*)&terminal_string, \
											strlen(terminal_string), receive_packet_data);
		/* Set new terminal background color */
		adp_set_color(terminal_config.background_color, ADP_COLOR_WHITE);
		adp_example_transceive_terminal(&terminal_config, TERMINAL_LABEL, receive_packet_data);
	}	
}

int main (void)
{
	/* Initialize system */
	board_init();
	adp_example_init();

	while (1) {
		if(time_out) {
			/* Receive and send forever */
			transceive_data();
			time_out = false;
		}
		
		/* Add user application here */
	}
}
