/**
 * \file
 *
 * \brief PIO Alternate Function Example.
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
 *  \mainpage PIO Alternate Function Example
 *
 *  \par Purpose
 *
 *  The PIO Alternate Function demonstrates how to alternate ERASE pin between system
 *  I/O mode and PIO mode.
 *
 *  \par Requirements
 *
 *  This package can be used with SAM EKs.
 *
 *  \par Description
 *
 *  The application shows the alternate function of ERASE pin, which extends PIO
 *  from a dedicated system I/O line. It first programs the internal flash with
 *  a walking pattern and then enables ERASE pin in PIO mode. After the erase
 *  operation, it checks the content of flash, which is unchanged due to ERASE in
 *  PIO mode. In the next step, it puts ERASE pin in system I/O mode, which will
 *  enable the erase function. The content of flash should be erased to 0xFF, which
 *  indicates the ERASE pin functioning.
 *
 *  The pins which are used by USB(DDM,DDP), JTAG(TCK,TMS,TDO,TDI) and Oscillator(XIN,
 *  XOUT,XIN32,XOUT32) could also be alternated between general purpose I/O and system
 *  I/O in the similar way.
 *
 *  \par Usage
 *
 *  -# Build the program and download it into the evaluation board.
 *  -# On the computer, open and configure a terminal application
 *     (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *    - 115200 bauds
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# Start application.
 *  -# In the terminal window, the
 *     following text should appear (values depend on the board and the chip used):
 *     \code
	-- PIO Alternate Function Example --
	-- xxxxxx-xx --
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 *  -# Perform erase operation following the application prompt.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "conf_board.h"
#include "conf_clock.h"
#include "conf_example.h"

/** Flash wait state number. */
#define FLASH_WAIT_STATE_NBR   (6)

/** Buffer size. */
#define BUFFER_SIZE            (IFLASH_PAGE_SIZE / 4)

/** The MAX value of shifting. */
#define MAX_SHIFTING_NUMBER    (32)

#define STRING_EOL    "\r"
#define STRING_HEADER "-- PIO Alternate Function Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/** Pushbutton #1 pin event flag. */
volatile uint32_t g_button_event = 0;

/**
 *  \brief Handler for Button 1 rising edge interrupt.
 *
 *  Set button1 event flag (g_button_event).
 */
static void button_handler(uint32_t id, uint32_t mask)
{
	if ((PUSH_BUTTON_ID == id) && (PUSH_BUTTON_PIN_MSK == mask)) {
		g_button_event = 1;
	}
}

/**
 *  \brief Configure the push button.
 *
 *  Configure the PIOs as inputs and generate corresponding interrupt when
 *  pressed or released.
 */
static void configure_button(void)
{
	/* Configure PIO clock. */
	pmc_enable_periph_clk(PUSH_BUTTON_ID);

	/* Adjust pio debounce filter parameters, uses 10 Hz filter. */
	pio_set_debounce_filter(PUSH_BUTTON_PIO, PUSH_BUTTON_PIN_MSK, 10);

	/* Initialize pios interrupt handlers, see PIO definition in board.h. */
	pio_handler_set(PUSH_BUTTON_PIO, PUSH_BUTTON_ID, PUSH_BUTTON_PIN_MSK,
		PUSH_BUTTON_ATTR, button_handler);

	/* Enable PIO controller IRQs. */
	NVIC_EnableIRQ((IRQn_Type)PUSH_BUTTON_ID);

	/* Enable PIO line interrupts. */
	pio_enable_interrupt(PUSH_BUTTON_PIO, PUSH_BUTTON_PIN_MSK);
}

/**
 *  Configure UART for debug message output.
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

/**
 *  \brief pio_alternate_function Application entry point.
 *
 *  Program the test page of internal flash with pattern
 *  0x00000001,0x00000002,...,0x80000000. If the ERASE is in
 *  PIO mode, putting jumper on ERASE has no effect.
 *  That is, this pin could be used as general purpose I/O
 *  line. Otherwise, the content of flash will be erased to
 *  0xFFFFFFFF.
 *
 *  \return Unused (ANSI-C compatibility).
 *
 */

int main(void)
{
	uint32_t i;
	uint32_t ul_error;
	volatile uint32_t *p_test_page_data;
	uint32_t p_buffer[BUFFER_SIZE];
	
	/* Initialize the system. */
	sysclk_init();
	board_init();

	/* Configure UART for debug message output. */
	configure_console();

	/* Initialize flash: 6 wait states for flash writing. */
	flash_init(FLASH_ACCESS_MODE_128, FLASH_WAIT_STATE_NBR);

	/* Configure Push Button. */
	configure_button();

	/* Output example information. */
	puts(STRING_HEADER);

	puts("-I- Unlocking the whole flash.\r\n");
	/* Unlock the whole flash. */
	ul_error = flash_unlock(IFLASH_ADDR, (IFLASH_ADDR + IFLASH_SIZE - 1), 0, 0);
	if (FLASH_RC_OK != ul_error) {
		puts("Unlock internal flash failed.\r\n");
		return 0;
	}

	/* Perform tests on the test page. */
	p_test_page_data = (volatile uint32_t *)TEST_PAGE_ADDRESS;

	/* Write page with walking bit pattern (0x00000001, 0x00000002, ...). */
	puts("-I- Writing test page with walking bit pattern.\r\n");
	for (i = 0; i < BUFFER_SIZE; i++) {
		p_buffer[i] = 1 << (i % MAX_SHIFTING_NUMBER);
	}
#if (SAM4E || SAM4C || SAME70 || SAMV71)
	/**
	 * The EWP command can only be used in 8 KBytes sector for SAM4E,
	 * so an erase command is requried before write operation.
	 */
	ul_error = flash_erase_sector(TEST_PAGE_ADDRESS);
	if (ul_error != FLASH_RC_OK) {
		printf("-F- Flash erase error %u\n\r", ul_error);
		return 0;
	}

	ul_error = flash_write(TEST_PAGE_ADDRESS, p_buffer,
			IFLASH_PAGE_SIZE, 0);
#else
	ul_error = flash_write(TEST_PAGE_ADDRESS, p_buffer,
			IFLASH_PAGE_SIZE, 1);
#endif
	if (FLASH_RC_OK != ul_error) {
		puts("Write the test page of internal flash failed.\r\n");
		return 0;
	}

	/* Check page contents. */
	puts("-I- Checking page contents.\r\n");
	for (i = 0; i < BUFFER_SIZE; i++) {
		printf(".");
		if (p_test_page_data[i] != (1u << (i % MAX_SHIFTING_NUMBER))) {
			puts("The content in the test page isn't written correctly");
			return 0;
		}
	}
	puts(" OK! \r\n");

	/* Configure Erase pin NOT in Erase mode. */
	puts("-I- Configure Erase pin in PIO mode.\r\n");
	matrix_set_system_io(PIN_PIO_MODE_MSK);

	/**
	 * Ask the user to close the erase jumper and then open it(200ms minimum).
	 */
	printf("-I- Please close the erase jumper and then open it ");
	printf("at least 200ms later.\r\n");

	printf("Then press button %s to go on!\r\n", BUTTON_STRING);
	/* Wait until Push Button is pressed. */
	while (!g_button_event) {
	}
	/**
	 * Disable the PIO line interrupts to eliminate the wrong check of
	 * key press.
	 */
	pio_disable_interrupt(PUSH_BUTTON_PIO, PUSH_BUTTON_PIN_MSK);
	g_button_event = 0;
	/* Read the page again, it should be unchanged. */
	puts("-I- Reading the page\r\n");
	for (i = 0; i < BUFFER_SIZE; i++) {
		printf(".");
		if (p_test_page_data[i] != (1u << (i % MAX_SHIFTING_NUMBER))) {
			puts("-F- Reading Error! \r\n");
			return 0;
		}
	}
	puts("\r\n");
	puts("Read OK! Erase is out of function!\r\n");
	/* Configure Erase pin as Erase function. */
	puts("-I- Configure Erase pin as Erase function\r\n");
	matrix_set_system_io(PIN_ERASE_MODE_MSK);

	/**
	 * Ask the user to close the erase jumper and then open it(200ms minimum).
	 */
	printf("-I- Please close the erase jumper and then open it ");
	printf("at least 200ms later.\r\n");

	/**
	 * Remind the users that after closing the erase jumper and then opening
	 * it, codes are gone.
	 */
	printf("-I- As the internal flash has been erased and the code can't ");
	printf("be executed any more, users can press the reset button on EK ");
	printf("and will see there will be no output message any more.\r\n");

	while (1) {
	}
}
