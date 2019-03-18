/**
 * \file
 *
 * \brief SAM EDBG TWI Information Interface Example
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
 * \mainpage SAM EDBG TWI Information Interface Example
 *
 * \section Purpose
 *
 * The example show the feature of the EDBG TWI information interface.
 *
 * \section Requirements
 *
 * This package can be used with SAM xplained pro.
 *
 * This package has been tested on following boards:
 * - SAM D21/R21 Xplained Pro
 *
 * \section Description
 *
 * The program demo how to read the extension boards information and kit data
 * by the EDBG TWI information interface.
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 38400 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear (values
 *    depend on the board and chip used):
 *    \code
 *     -- EDBG TWI Information Interface Example --
 *     -- xxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *    \endcode
 * -# Extension boards information and kit data will be show in the terminal.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <string.h>
#include "conf_uart_serial.h"

#define STRING_EOL    "\r"
#define STRING_HEADER "-- EDBG TWI Information Interface Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

static struct usart_module cdc_uart_module;

/** EDBG TWI interface address */
#define EDBG_ADDRESS 0x28;

/** Request token of EDBG TWI information interface */
#define EDBG_EXTEN_BOARDS_TOKEN 0xE1;
#define EDBG_KIT_DATA_TOKEN     0xD2;

/** I2C related structure */
struct i2c_master_module i2c_master_instance;
struct i2c_master_packet master_packet;

/* Number of times to try to send packet if failed. */
#define TIMEOUT 1000

/** Read buffer */
uint8_t read_buffer[1024];

/** Extension board info structure*/
uint8_t extension_map[2];
uint8_t extension_info[64];
uint16_t minimum_voltage;
uint16_t maximum_voltage;
uint16_t minimum_current;

#ifdef CONF_KIT_DATA_EXIST
/** Kit data structure*/
uint8_t kit_data[256];
/** Kit data MAC offset */
#define EDBG_KIT_DATA_MAC_OFFSET     0x00
#endif

/**
 * \brief Function for show the extension boards information
 *
 */
static void decode_board_info(uint8_t *buffer)
{
	uint8_t i = 0;

	memcpy(extension_info, buffer, 64);

	/** show extension boards information */
	printf("Manufacturer name: ");
	while (extension_info[i] != 0x00) {
		printf("%c", extension_info[i]);
		i++;
	}
	printf("\r\n");
	i++;

	printf("Product name: ");
	while (extension_info[i] != 0x00) {
		printf("%c", extension_info[i]);
		i++;
	}
	printf("\r\n");
	i++;

	printf("Product revision: ");
	while (extension_info[i] != 0x00) {
		printf("%c", extension_info[i]);
		i++;
	}
	printf("\r\n");
	i++;

	printf("Product serial number: ");
	while (extension_info[i] != 0x00) {
		printf("%c", extension_info[i]);
		i++;
	}
	printf("\r\n");

	minimum_voltage = extension_info[59] | (extension_info[58] << 8);
	printf("Minimum supported voltage: %d mV \r\n", minimum_voltage);

	maximum_voltage = extension_info[61] | (extension_info[60] << 8);
	printf("Maximum supported voltage: %d mV \r\n", maximum_voltage);

	minimum_current = extension_info[63] | (extension_info[62] << 8);
	printf("Minimum required current: %d mA \r\n", minimum_current);
}

/**
 * \brief Function for show the extension boards information
 *
 */
static void show_extension_boards_information(void)
{
	uint8_t request_token = EDBG_EXTEN_BOARDS_TOKEN;
	uint32_t timeout = 0;
	uint8_t board_num = 0;
	uint8_t i,j;

	/** Send the request token */
	master_packet.address         = EDBG_ADDRESS;
	master_packet.data_length     = 1;
	master_packet.data            = &request_token;
	master_packet.ten_bit_address = false;
	master_packet.high_speed      = false;
	master_packet.hs_master_code  = 0x0;
	while (i2c_master_write_packet_wait_no_stop(&i2c_master_instance, &master_packet) !=
			STATUS_OK) {
		/* Increment timeout counter and check if timed out. */
		if (timeout++ == TIMEOUT) {
			return;
		}
	}

	/** Get the extension boards info */
	master_packet.data_length     = 1024;
	master_packet.data            = read_buffer;
	while (i2c_master_read_packet_wait(&i2c_master_instance, &master_packet) !=
			STATUS_OK) {
		/* Increment timeout counter and check if timed out. */
		if (timeout++ == TIMEOUT) {
			return;
		}
	}

	/** Check and show info */
	extension_map[0] = read_buffer[0];
	extension_map[1] = read_buffer[1];

	for (i = 0; i < 2; i++) {
		for (j = 1; j <= 8; j++) {
			if (extension_map[1 - i] & 0x01) {
				/** show extension board info */
 				printf("\r\n Extension board %d detected \r\n", (i * 8) + j);
				decode_board_info(&read_buffer[2 + 64 * board_num]);
				board_num++;
			}
			extension_map[1 - i] = extension_map[1 - i] >> 1;
		}
	}
}

#ifdef CONF_KIT_DATA_EXIST
/**
 * \brief Function for show the kit data
 *
 */
static void show_kit_data(void)
{
	uint8_t request_token = EDBG_KIT_DATA_TOKEN;
	uint32_t timeout = 0;
	uint8_t i;

	/** Send the request token */
	master_packet.address         = EDBG_ADDRESS;
	master_packet.data_length     = 1;
	master_packet.data            = &request_token;
	master_packet.ten_bit_address = false;
	master_packet.high_speed      = false;
	master_packet.hs_master_code  = 0x0;
	while (i2c_master_write_packet_wait_no_stop(&i2c_master_instance, &master_packet) !=
			STATUS_OK) {
		/* Increment timeout counter and check if timed out. */
		if (timeout++ == TIMEOUT) {
			return;
		}
	}

	/** Get the extension boards info */
	master_packet.data_length     = 256;
	master_packet.data            = kit_data;
	while (i2c_master_read_packet_wait(&i2c_master_instance, &master_packet) !=
			STATUS_OK) {
		/* Increment timeout counter and check if timed out. */
		if (timeout++ == TIMEOUT) {
			return;
		}
	}

	/** show kit data */
	printf("\r\n The kit data(MAC value): \r\n 0x");
	for (i = 0; i < CONF_KIT_DATA_NUM; i++) {
		printf("%02x", kit_data[i + EDBG_KIT_DATA_MAC_OFFSET]);
	}
	printf("\r\n");
}
#endif

/**
 * \brief Function for configuring I2C master module
 *
 * This function will configure the I2C master module with
 * the SERCOM module to be used and pinmux settings
 */
static void configure_i2c_master(void)
{
	/* Create and initialize config structure */
	struct i2c_master_config config_i2c;
	i2c_master_get_config_defaults(&config_i2c);

	/* Change pins */
	config_i2c.pinmux_pad0  = EDBG_I2C_SERCOM_PINMUX_PAD0;
	config_i2c.pinmux_pad1  = EDBG_I2C_SERCOM_PINMUX_PAD1;

	/* Initialize and enable device with config */
	i2c_master_init(&i2c_master_instance, EDBG_I2C_MODULE, &config_i2c);

	i2c_master_enable(&i2c_master_instance);
}

/**
 *  Configure UART console.
 */
static void configure_console(void)
{
	struct usart_config usart_conf;

	usart_get_config_defaults(&usart_conf);
	usart_conf.mux_setting = CONF_STDIO_MUX_SETTING;
	usart_conf.pinmux_pad0 = CONF_STDIO_PINMUX_PAD0;
	usart_conf.pinmux_pad1 = CONF_STDIO_PINMUX_PAD1;
	usart_conf.pinmux_pad2 = CONF_STDIO_PINMUX_PAD2;
	usart_conf.pinmux_pad3 = CONF_STDIO_PINMUX_PAD3;
	usart_conf.baudrate    = CONF_STDIO_BAUDRATE;

	stdio_serial_init(&cdc_uart_module, CONF_STDIO_USART_MODULE, &usart_conf);
	usart_enable(&cdc_uart_module);
}

/**
 * \brief Main application
 */
int main(void)
{

	/* Initialize system */
	system_init();

	/*Configure UART console.*/
	configure_console();

	/* Configure the I2C master module */
	configure_i2c_master();

	/* Output example information */
	puts(STRING_HEADER);

	/* Show the extension boards information */
	show_extension_boards_information();

#ifdef CONF_KIT_DATA_EXIST
	/* Show the kit data */
	show_kit_data();
#endif

	while (1) {
		/* Infinite loop */
	}

}
