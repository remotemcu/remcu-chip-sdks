/**
 * \file
 *
 * \brief AT24CXX Component Example for SAM.
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
 * \mainpage AT24CXX Component Example
 *
 * \section Purpose
 *
 * The application demonstrates how to access AT24CXX EEPROM component.
 *
 * \section Requirements
 *
 * This package can be used with SAM evaluation kits.
 *
 * \section Description
 *
 * Upon startup, the program configures PIOs for console UART, LEDs and TWI
 * connected to AT24CXX on board. Then it initializes the AT24CXX component.
 * After initializing it, the example sends test pattern to the AT24CXX component.
 * When the sending is complete, AT24CXX API reads the memory and saves the
 * content in the reception buffer. Then the program compares the content
 * received with the test pattern sent before and prints the comparison result.
 * The corresponding LED is turned on.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR EWARM.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/">Microchip</A>.\n
 * Support and FAQ: https://www.microchip.com/support/
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/** Memory Start Address of AT24CXX chips */
#define AT24C_MEM_ADDR  0x0
/** TWI Bus Clock 400kHz */
#define AT24C_TWI_CLK   400000

/** Data to be sent */
#define  TEST_DATA_LENGTH  (sizeof(test_data_tx)/sizeof(uint8_t))

#define STRING_EOL    "\r"
#define STRING_HEADER "--AT24CXX Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

static const uint8_t test_data_tx[] = {
	'S', 'A', 'M', ' ', 'A', 'T', '2', '4', 'C', 'X', 'X', ' ', 'E',
	'X', 'A', 'M', 'P', 'L', 'E'
};

/* Memory Pattern */
#define MEMORY_PATTERN  0xFF

/* EEPROM Page Size */
#define PAGE_SIZE  128
/* EEPROM Page Address */
#define PAGE_ADDR  3
uint8_t page_read_buf[PAGE_SIZE];
uint8_t page_write_buf[PAGE_SIZE];

/** Reception buffer */
static uint8_t test_data_rx[TEST_DATA_LENGTH] = { 0 };

/** Global timestamp in milliseconds since the start of application */
volatile uint32_t dw_ms_ticks = 0;

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
 * \brief Application entry point for AT24CXX Component Example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint32_t i;
	twi_options_t opt;

	/* Initialize the SAM system */
	sysclk_init();

	/* Initialize the board */
	board_init();

	/* Turn off LEDs */
	ioport_set_pin_level(LED0_GPIO, LED0_INACTIVE_LEVEL);
	ioport_set_pin_level(LED1_GPIO, LED1_INACTIVE_LEVEL);

	/* Initialize the console UART */
	configure_console();

	/* Output example information */
	puts(STRING_HEADER);

	/* Configure the options of TWI driver */
	opt.master_clk = sysclk_get_cpu_hz();
	opt.speed = AT24C_TWI_CLK;

	if (twi_master_setup(BOARD_AT24C_TWI_INSTANCE, &opt) != TWI_SUCCESS) {
		puts("AT24CXX initialization is failed.\r");
		ioport_set_pin_level(LED0_GPIO, LED0_ACTIVE_LEVEL);
		ioport_set_pin_level(LED1_GPIO, LED1_ACTIVE_LEVEL);
		while (1) {
			/* Capture error */
		}
	}

	/* Fill EEPROM with memory pattern */
	if (at24cxx_fill_pattern(AT24C_MEM_ADDR,
			AT24C_MEM_ADDR + TEST_DATA_LENGTH - 1,
			MEMORY_PATTERN) != AT24C_WRITE_SUCCESS) {
		puts("AT24CXX pattern fill is failed.\r");
		ioport_set_pin_level(LED0_GPIO, LED0_ACTIVE_LEVEL);
		ioport_set_pin_level(LED1_GPIO, LED1_ACTIVE_LEVEL);
		while (1) {
			/* Capture error */
		}
	}

	if (at24cxx_read_continuous(AT24C_MEM_ADDR, TEST_DATA_LENGTH,
			test_data_rx) != AT24C_READ_SUCCESS) {
		puts("AT24CXX read packet is failed.\r");
		ioport_set_pin_level(LED0_GPIO, LED0_ACTIVE_LEVEL);
		ioport_set_pin_level(LED1_GPIO, LED1_ACTIVE_LEVEL);
		while (1) {
			/* Capture error */
		}
	}

	/* Compare the sent and the received */
	for (i = 0; i < TEST_DATA_LENGTH; i++) {
		if (MEMORY_PATTERN != test_data_rx[i]) {
			/* No match */
			puts("Pattern comparison: Unmatched!\r");
			ioport_set_pin_level(LED0_GPIO, LED0_ACTIVE_LEVEL);
			ioport_set_pin_level(LED1_GPIO, LED1_ACTIVE_LEVEL);
			while (1) {
				/* Capture error */
			}
		}
	}
	puts("Pattern comparison: Matched!\r");

	/* Send test pattern to EEPROM */
	if (at24cxx_write_continuous(AT24C_MEM_ADDR, TEST_DATA_LENGTH,
			test_data_tx) != AT24C_WRITE_SUCCESS) {
		puts("AT24CXX write packet is failed.\r");
		ioport_set_pin_level(LED0_GPIO, LED0_ACTIVE_LEVEL);
		ioport_set_pin_level(LED1_GPIO, LED1_ACTIVE_LEVEL);
		while (1) {
			/* Capture error */
		}
	}

	/* Get memory from EEPROM */
	if (at24cxx_read_continuous(AT24C_MEM_ADDR, TEST_DATA_LENGTH,
			test_data_rx) != AT24C_READ_SUCCESS) {
		puts("AT24CXX read packet is failed.\r");
		ioport_set_pin_level(LED0_GPIO, LED0_ACTIVE_LEVEL);
		ioport_set_pin_level(LED1_GPIO, LED1_ACTIVE_LEVEL);
		while (1) {
			/* Capture error */
		}
	}

	/* Compare the sent and the received */
	for (i = 0; i < TEST_DATA_LENGTH; i++) {
		if (test_data_tx[i] != test_data_rx[i]) {
			/* No match */
			puts("Data comparison: Unmatched!\r");
			ioport_set_pin_level(LED0_GPIO, LED0_ACTIVE_LEVEL);
			ioport_set_pin_level(LED1_GPIO, LED1_ACTIVE_LEVEL);
			while (1) {
				/* Capture error */
			}
		}
	}
	/* Match */
	puts("Data comparison: Matched!\r");

	/* Page Operation */
	for (i = 0; i < PAGE_SIZE; i++) {
		page_read_buf[i] = 0;
		page_write_buf[i] = i;
	}

	if (at24cxx_write_page(PAGE_ADDR, PAGE_SIZE, page_write_buf) !=
			AT24C_WRITE_SUCCESS) {
		puts("AT24CXX page write is failed.\r");
		ioport_set_pin_level(LED0_GPIO, LED0_ACTIVE_LEVEL);
		ioport_set_pin_level(LED1_GPIO, LED1_ACTIVE_LEVEL);
		while (1) {
			/* Capture error */
		}
	}

	if (at24cxx_read_page(PAGE_ADDR, PAGE_SIZE, page_read_buf) !=
			AT24C_READ_SUCCESS) {
		puts("AT24CXX page read is failed.\r");
		ioport_set_pin_level(LED0_GPIO, LED0_ACTIVE_LEVEL);
		ioport_set_pin_level(LED1_GPIO, LED1_ACTIVE_LEVEL);
		while (1) {
			/* Capture error */
		}
	}

	for (i = 0; i < PAGE_SIZE; i++) {
		if (page_read_buf[i] != page_write_buf[i]) {
			/* No match */
			puts("Page comparison: Unmatched!\r");
			ioport_set_pin_level(LED0_GPIO, LED0_ACTIVE_LEVEL);
			ioport_set_pin_level(LED1_GPIO, LED1_ACTIVE_LEVEL);
			while (1) {
				/* Capture error */
			}
		}
	}
	/* Match */
	puts("Page comparison: Matched!\r");
	while (1) {
	}
}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
