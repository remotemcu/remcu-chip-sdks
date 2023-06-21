/**
 * \file
 *
 * \brief TWIM Master Example for SAM.
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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
 *  \mainpage TWIM Master Example
 *
 *  \par Purpose
 *
 *  This application gives an example of how to use TWIM driver of SAM to
 *  access an TWI-compatible EEPROM.
 *
 *  \par Requirements
 *
 *  The program needs a TWI-compatible EEPROM connected with the TWIM module.
 *  See the connection below:
 *  \copydoc twim_master_example_pin_defs
 *
 *  \par Description
 *
 *  At first, the specified TWIM write some data pattern to the EEPROM, then
 *  read it back and check if the written and the read match.
 *
 * \par Usage
 *
 *  -# Build the program and download it into the evaluation board.
 *  -# Connect a serial cable to the UART port for each evaluation kit.
 *  -# On the computer, open and configure a terminal application (e.g.,
 *     HyperTerminal on Microsoft Windows) with these settings:
 *        - 115200 bauds
 *        - 8 data bits
 *        - No parity
 *        - 1 stop bit
 *        - No flow control
 *  -# Start the application. The following traces shall appear on the terminal:
 *     \code
	     -- TWIM Master Example --
	     -- xxxxxx-xx
	     -- Compiled: xxx xx xxxx xx:xx:xx --

\endcode
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */


#include <asf.h>
#include "conf_example.h"
#include "sleepmgr.h"

#define PATTERN_TEST_LENGTH (sizeof(write_data)/sizeof(uint8_t))
//! Array to store the test data for sending
const uint8_t write_data[] = {
	'S', 'A', 'M', '4', 'L', ' ', 'T', 'W', 'I', 'M', ' ', 'M',
	'a', 's', 't', 'e', 'r', ' ', 'E', 'x', 'a', 'm', 'p', 'l', 'e'
};
//! Array to store the received test data
uint8_t read_data[PATTERN_TEST_LENGTH];
//! TWI data package
twi_package_t packet_tx, packet_rx;
uint32_t cpu_speed = 0;


/**
 *  Configure serial console.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
#ifdef CONF_UART_CHAR_LENGTH
		.charlength = CONF_UART_CHAR_LENGTH,
#endif
		.paritytype = CONF_UART_PARITY,
#ifdef CONF_UART_STOP_BITS
		.stopbits = CONF_UART_STOP_BITS,
#endif
	};

	/* Configure console UART. */
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief Initialize the TWIM module.
 *
 * \return STATUS_OK   if the initialization succeeds, error code otherwise.
 */
static status_code_t init_test(void)
{
	/* Set TWIM options */
	cpu_speed = sysclk_get_peripheral_bus_hz(EXAMPLE_TWIM);
	struct twim_config opts = {
		.twim_clk = cpu_speed,
		.speed = TWIM_MASTER_SPEED,
		.hsmode_speed = 0,
		.data_setup_cycles = 0,
		.hsmode_data_setup_cycles = 0,
		.smbus = false,
		.clock_slew_limit = 0,
		.clock_drive_strength_low = 0,
		.data_slew_limit = 0,
		.data_drive_strength_low = 0,
		.hs_clock_slew_limit = 0,
		.hs_clock_drive_strength_high = 0,
		.hs_clock_drive_strength_low = 0,
		.hs_data_slew_limit = 0,
		.hs_data_drive_strength_low = 0,
	};
	/* Initialize the TWIM Module */
	twim_set_callback(EXAMPLE_TWIM, 0, twim_default_callback, 1);

	return twim_set_config(EXAMPLE_TWIM, &opts);
}

/**
 * \brief Write the data pattern to the target.
 *
 * \return STATUS_OK   if all bytes were written, error code otherwise.
 */
static status_code_t write_test(void)
{
	/* TWI chip address to communicate with */
	packet_tx.chip = TARGET_ADDRESS;
	/* TWI address/commands to issue to the other chip (node) */
	packet_tx.addr[0] = (VIRTUALMEM_ADDR >> 16) & 0xFF;
	packet_tx.addr[1] = (VIRTUALMEM_ADDR >> 8) & 0xFF;
	/* Length of the TWI data address segment (1-3 bytes) */
	packet_tx.addr_length = TARGET_ADDR_LGT;
	/* Where to find the data to be written */
	packet_tx.buffer = (void *) write_data;
	/* How many bytes do we want to write */
	packet_tx.length = PATTERN_TEST_LENGTH;
	printf("Writing data to TARGET\r\n");
	/* Write data to TARGET */
	return twi_master_write(EXAMPLE_TWIM, &packet_tx);
}

/**
 * \brief Read the data pattern from the target.
 *
 * \return STATUS_OK   If all bytes were read, error code otherwise
 */
static status_code_t read_test(void)
{
	/* TWI chip address to communicate with */
	packet_rx.chip = TARGET_ADDRESS;
	/* Length of the TWI data address segment (1-3 bytes) */
	packet_rx.addr_length = TARGET_ADDR_LGT;
	/* How many bytes do we want to write */
	packet_rx.length = PATTERN_TEST_LENGTH;
	/* TWI address/commands to issue to the other chip (node) */
	packet_rx.addr[0] = (VIRTUALMEM_ADDR >> 16) & 0xFF;
	packet_rx.addr[1] = (VIRTUALMEM_ADDR >> 8) & 0xFF;
	/* Where to find the data to be written */
	packet_rx.buffer = read_data;
	printf("Reading data from TARGET\r\n");
	/* Read data from TARGET */
	return twi_master_read(EXAMPLE_TWIM, &packet_rx);
}

/**
 * \remarks Main function.
 * @{
 */
int main (void)
{
	uint8_t i;
	status_code_t status;

	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	/* Initialize the console USART */
	configure_console();

	/* Output example information */
	printf("-- TWIM Master Example --\r\n");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	/* Perform Initialization Test */
	status = init_test();
	/* Check whether the TWIM module is initialized */
	if (status == STATUS_OK) {
		printf("TWIM module has be initialized successfully.\r\n");
	} else {
		printf("TWIM module failed to be initialized.r\n");
		while (1) {
			sleepmgr_enter_sleep();
		}
	}

	/* Perform Write Test */
	status = write_test();
	/* Check status of transfer */
	if (status == STATUS_OK) {
		printf("WRITE TEST:\tPASS\r\n");
	} else {
		printf("WRITE TEST:\tFAILED\r\n");
		while (1) {
			sleepmgr_enter_sleep();
		}
	}

	/* Perform Read Test */
	status = read_test();
	/* Check Status */
	if (status == STATUS_OK) {
		printf("READ TEST:\tPASS\r\n");
	} else {
		printf("READ TEST:\tFAILED\r\n");
		while (1) {
			sleepmgr_enter_sleep();
		}
	}

	/* Check received data against sent data */
	printf("Checking data...\r\n");
	for (i = 0; i < PATTERN_TEST_LENGTH; i++) {
		if (read_data[i] != write_data[i]) {
			/* Error */
			printf("Check Data:\tFAIL\r\n");
			while (1) {
				sleepmgr_enter_sleep();
			}
		}
	}

	/* No errors in communication */
	printf("No errors in communication\r\nDone\r\n");
	while (1) {
		sleepmgr_enter_sleep();
	}
}
//! @}

/* END OF FILE */
