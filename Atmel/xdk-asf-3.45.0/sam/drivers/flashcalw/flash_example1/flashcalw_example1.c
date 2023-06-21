/**
 * \file
 *
 * \brief FLASHCALW example1 for SAM.
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
 * \mainpage
 * \section intro Introduction
 * This is the documentation for the data structures, functions, variables,
 * defines, enums, and typedefs for the FLASHCALW software driver.
 *
 * It also comes bundled with an example. This example demonstrates flash read /
 * write data accesses, using a flash block as an NVRAM, located either in the
 * flash array or in the User page. The security bit will be set finally.
 *
 * Once the security bit set, the only way to clear it is doing the
 * Chip Erase command through Atmel Stdio 6 or asserting the erase pin to 1.
 *
 * Operating mode of the example:
 *   -# After reset, the NVRAM variables are displayed on the USART link.
 *   -# The NVRAM is cleared (all bytes are set to 0x00).
 *   -# All NVRAM variables are written with incrementing nibbles, starting from
 *      0x0.
 *   -# The user can reset or power-cycle the board to check the
 *      non-volatileness of the NVRAM.
 *   -# This is performed once in the flash array and then in the user page.
 *   -# The last page of the flash array will be locked.
 *   -# The lock status of the last page will be checked.
 *   -# The last page will be unlocked.
 *   -# Waiting for any key pressed in the debug console.
 *   -# Then security bit will be set. Setting the security bit will lock the chip from
 *     further access through all external programming and debugging interfaces.
 *
 * \section files Main Files
 *   - flashcalw.c: FLASHCALW driver;
 *   - flashcalw.h: FLASHCALW driver header file;
 *   - flashcalw_example.c: flash access example application.
 *
 * \section compilinfo Compilation Information
 * This software is written for GNU GCC and IAR Embedded Workbench
 * for Atmel. Other compilers may or may not work.
 *
 * \section deviceinfo Device Information
 * All SAM devices with a FLASHCALW module can be used.
 *
 * \section configinfo Configuration Information
 * This example has been tested with the following kits:
 * - SAM4L-EK evaluation kit;
 * - SAM4L Xplained Pro
 * - SAM4L8 Xplained Pro
 * This example has been tested with the following configuration:
 * - CPU clock: 12 MHz;
 * - USARTx abstracted with a USB CDC connection to a PC;
 * - PC terminal settings:
 *   - 115200 bps,
 *   - 8 data bits,
 *   - no parity bit,
 *   - 1 stop bit,
 *   - no flow control.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com">Microchip</A>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>

/* NVRAM test page address */
#define NVRAM_PAGE_ADDRESS (FLASH_ADDR + FLASH_SIZE - FLASH_PAGE_SIZE)

/* NVRAM test user page address. The first 8 bytes in the user page is
 * reserved as fuse settings and should not be programmed */
#define USER_PAGE_ADDRESS (FLASH_USER_PAGE_ADDR + 8)

/* Protection test page number */
#define NVRAM_PAGE_NUMBER (NVRAM_PAGE_ADDRESS/FLASH_PAGE_SIZE)

/* Structure type containing variables to store in NVRAM using a specific
memory map. */
typedef const struct {
	uint8_t var8;
	uint16_t var16;
	uint8_t var8_3[3];
	uint32_t var32;
} nvram_data_t;

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

/*! \brief Prints the variables stored in NVRAM.
 *
 * \param nvram_data  Pointer to the NVRAM data structure to print.
 */
static void print_nvram_variables(nvram_data_t *nvram_data)
{
	printf("var8:\t0x%X", nvram_data->var8);

	printf("\r\nvar16:\t0x%X", nvram_data->var16);

	printf("\r\nvar8_3:\t0x%X%X%X", nvram_data->var8_3[0],
		nvram_data->var8_3[1], nvram_data->var8_3[2]);

	printf("\r\nvar32:\t0x%X\r\n", (unsigned int)nvram_data->var32);
}

/*! \brief This is an example demonstrating flash read / write data accesses
 *         using the FLASHCALW driver.
 *
 * \param caption     Caption to print before running the example.
 * \param nvram_data  Pointer to the NVRAM data structure to use in the example.
 */
static void flash_rw_example(const char *caption, nvram_data_t *nvram_data)
{
	static const uint8_t write_data[8]
		= {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};

	printf("%s", caption);

	printf("Initial values of NVRAM variables:\r\n");
	print_nvram_variables(nvram_data);

	printf("\r\nClearing NVRAM variables...");

	/* Clear NVRAM */
	flashcalw_memset((void *)nvram_data, 0x0, 8, sizeof(*nvram_data),
			true);
	printf("\r\nNVRAM variables cleared:\r\n");
	print_nvram_variables(nvram_data);

	printf("\r\nWriting new values to NVRAM variables...");
	flashcalw_memcpy((void *)&nvram_data->var8, &write_data,
			sizeof(nvram_data->var8), true);
	flashcalw_memcpy((void *)&nvram_data->var16, &write_data,
			sizeof(nvram_data->var16), true);
	flashcalw_memcpy((void *)&nvram_data->var8_3, &write_data,
			sizeof(nvram_data->var8_3), true);
	flashcalw_memcpy((void *)&nvram_data->var32, &write_data,
			sizeof(nvram_data->var32), true);
	printf("\r\nNVRAM variables written:\r\n");
	print_nvram_variables(nvram_data);
}

/*! \brief This is an example demonstrating the flash lock bits feature.
 */
static void flash_protect_example( void )
{
	printf("\r\nFlash protection example...\n\r");

	/* Set the lock */
	flashcalw_lock_page_region(NVRAM_PAGE_NUMBER, true);

	/* Try to access the locked area */
	flashcalw_memset((void *)NVRAM_PAGE_ADDRESS, 0x0, 8, FLASH_PAGE_SIZE,
			true);

	/* A lock error will generated if access to the locked page */
	if (flashcalw_is_lock_error()) {
		printf("Flash lock operation succeeded.\n\r");
	}

	/* Unlock the page */
	flashcalw_lock_page_region(NVRAM_PAGE_NUMBER, false);
}

/*!
 * \brief main function : perform several read/write accesses to the flash then
 * lock and unlock a page in the flash.
 */
int main(void)
{
	uint32_t key;

	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	/* Initialize the console uart */
	configure_console();

	/* Output example information */
	printf("-- FLASHCALW Example --\r\n");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	/* Apply the example to the flash array. */
	flash_rw_example(
		"\x0C=== Using a piece of the flash array as NVRAM ===\r\n",
		(nvram_data_t *)NVRAM_PAGE_ADDRESS);

	/* Apply the example to the user page. */
	flash_rw_example(
		"\r\n\r\n=== Using a piece of the user page as NVRAM ===\r\n",
		(nvram_data_t *)USER_PAGE_ADDRESS);

	/* Flash lock example */
	flash_protect_example();

	printf("-I- Good job!\n\r"
		"-I- Now set the security bit \n\r"
		"-I- Press any key to continue to see what happened...\n\r");
	while (0 != usart_read(CONF_UART, &key));

	/* Set security bit */
	printf("-I- Setting security bit \n\r");
	flashcalw_set_security_bit();

	printf("-I- All tests done\n\r");

	while (true) {
	}
}
