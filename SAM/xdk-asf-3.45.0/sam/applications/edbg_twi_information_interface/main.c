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
 * This package can be used with SAM4E Xplained Pro.
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
 *   - 115200 bauds
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
#include "conf_board.h"

#define STRING_EOL    "\r"
#define STRING_HEADER "-- EDBG TWI Information Interface Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/** TWI Bus Clock 400kHz */
#define TWI_CLK     400000

/** EDBG TWI interface address */
#define EDBG_ADDRESS 0x28;

/** Request token of EDBG TWI information interface */
#define EDBG_EXTEN_BOARDS_TOKEN 0xE1;
#define EDBG_KIT_DATA_TOKEN     0xD2;

/** I2C related structure */
twi_options_t opt;
twi_packet_t packet_rx;

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

	/** Get the extension boards info */
	packet_rx.chip        = EDBG_ADDRESS;
	packet_rx.addr_length = 1;
	packet_rx.addr[0] = request_token;
	packet_rx.buffer      = read_buffer;
	packet_rx.length      = 1024;
	while (twi_master_read(EDBG_I2C_MODULE, &packet_rx) != TWI_SUCCESS) {
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

	/** Get the extension boards info */
	packet_rx.chip        = EDBG_ADDRESS;
	packet_rx.addr_length = 1;
	packet_rx.addr[0] = request_token;
	packet_rx.buffer      = kit_data;
	packet_rx.length      = 256;
	while (twi_master_read(EDBG_I2C_MODULE, &packet_rx) != TWI_SUCCESS) {
		/* Increment timeout counter and check if timed out. */
		if (timeout++ == TIMEOUT) {
			return;
		}
	}

	/** show kit data */
	printf("\r\n The kit data: \r\n 0x");
	for (i = 0; i < CONF_KIT_DATA_NUM; i++) {
		printf("%02x", kit_data[i]);
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
	/* Enable the peripheral clock for TWI */
	pmc_enable_periph_clk(EDBG_I2C_MODULE_ID);

	/* Configure the options of TWI driver */
	opt.master_clk = sysclk_get_cpu_hz();
	opt.speed      = TWI_CLK;

	if (twi_master_init(EDBG_I2C_MODULE, &opt) != TWI_SUCCESS) {
		puts("-E-\tTWI master initialization failed.\r");
		while (1) {
			/* Capture error */
		}
	}
}

/**
 *  \brief Configure the Console UART.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief Main application
 */
int main(void)
{
	/* Initialize the SAM system */
	sysclk_init();

	/* Initialize the board */
	board_init();

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
