/**
 * \file
 *
 * \brief Flash read Unique Identifier example for SAM.
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
 * \mainpage Flash Read Unique Identifier Example
 *
 * \section Purpose
 *
 * This basic example shows how to use the Flash service available on the Atmel 
 * SAM flash microcontrollers. It reads and displays the Unique Identifier 
 * stored in the Flash.
 *
 * \section Requirements
 *
 * This package can be used with SAM evaluation kits.
 *
 * \section Description
 * To read the Unique Identifier, the sequence is:
 * <ul>
 *  <li>Send the Start Read Unique Identifier command (STUI) by writing the 
 * Flash Command Register with the STUI command.</li>
 *  <li>When the Unique Identifier is ready to be read, the FRDY bit in the 
 * Flash Programming Status Register (EEFC_FSR) falls.</li>
 *  <li>The Unique Identifier is located in the first 128 bits of the Flash 
 * memory mapping. So, at the address 0x80000-0x80003.</li>
 *  <li>To stop the Unique Identifier mode, the user needs to send the Stop 
 * Read Unique Identifier command (SPUI) by writing the Flash Command Register 
 * with the SPUI command.</li>
 *  <li>When the Stop Read Unique Identifier command (SPUI) has been performed, 
 * the FRDY bit in the Flash Programming Status Register (EEFC_FSR) rises.</li>
 * </ul>
 *
 * \section Usage
 *
 * -# Build the program and download it into the evaluation board.
 * -# On the computer, open and configure a terminal application
 *    (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *    \code
	-- Flash Read Unique Identifier Example --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
	-I- Reading 128 bits unique identifier
	-I- ID: 0xxxxxxxxx, 0xxxxxxxxx, 0xxxxxxxxx, 0xxxxxxxxx
\endcode
 * 
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "stdio_serial.h"
#include "conf_board.h"
#include "conf_clock.h"

#define STRING_EOL    "\r"
#define STRING_HEADER "-- Flash Read Unique Identifier Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/**
 *  Configure console using UART.
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
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

typedef unsigned long UL;
/**
 *  \brief efc_unique_id_example Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint32_t ul_rc;
	uint32_t unique_id[4];

	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	/* Initialize the console uart */
	configure_console();

	/* Output example information */
	puts(STRING_HEADER);

	/* Initialize Flash service */
	ul_rc = flash_init(FLASH_ACCESS_MODE_128, 4);
	if (ul_rc != FLASH_RC_OK) {
		printf("-F- Initialization error %lu\n\r", (UL)ul_rc);
		return 0;
	}

	/* Read the unique ID */
	puts("-I- Reading 128 bits Unique Identifier\r");
	ul_rc = flash_read_unique_id(unique_id, 4);
	if (ul_rc != FLASH_RC_OK) {
		printf("-F- Read the Unique Identifier error %lu\n\r", (UL)ul_rc);
		return 0;
	}

	printf("-I- ID: 0x%08lu, 0x%08lu, 0x%08lu, 0x%08lu\n\r",
			(UL)unique_id[0], (UL)unique_id[1],
			(UL)unique_id[2], (UL)unique_id[3]);

	while (1) {
		/* Do nothing */
	}
}
