/**
 * \file
 *
 * \brief USART Sleepwalking Example for SAM.
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
 * \mainpage USART Sleepwalking Example
 *
 * \section Purpose
 *
 * The example demonstrates how to use sleepwalking function of the USART.
 *
 * \section Requirements
 *
 * This example can be used on SAMG55 device.
 *
 * \note The example use a loose match condition to wake up the system
 * from wait mode.
 *
 * \section Description
 *
 * The example first tests the sleepwalking function in active mode. If
 * the 's' character is received, the match interrupt is triggered.
 * Then it tests the sleepwalking function in wait mode. As soon as a data
 * is received, the system wake up from wait mode.
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
 * -# In the terminal window, the following text should appear (values depend
 *    on the board and chip used):
 *    \code
	-- Usart Sleepwalking Example xxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 * -# the sent text should appear.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include "conf_example.h"

#define STRING_EOL    "\r"
#define STRING_HEADER "-- USART Sleepwalking Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/* CMP interrupt flag*/
volatile uint32_t cmp_flag = 0;

/**
 * \brief Interrupt handler for USART interrupt.
 */
void console_uart_irq_handler(void)
{
	/* Get USART status and check if CMP is set */
	if (usart_get_status(CONSOLE_UART) & US_CSR_CMP) {
		cmp_flag = 1;
		/* Disable USART IRQ */
		usart_disable_interrupt(CONSOLE_UART, US_IDR_CMP);
	}
}

/**
 * \brief Test the usart sleepwalking in active mode.
 */
static void usart_sleepwalking_test_active(void)
{
	uint32_t temp;

	puts("Test in active mode, press 's' to continue.\r");

	/* Wait for the puts operation to finish. */
	delay_ms(50);

	/* Enable UART IRQ */
	usart_enable_interrupt(CONSOLE_UART, US_IER_CMP);

	/* Enable UART interrupt */
	NVIC_EnableIRQ(CONSOLE_UART_IRQn);

	/* Set the match condition */
	usart_set_sleepwalking(CONSOLE_UART, 's', true, true, 's');

	/* Enable the sleepwalking in PMC */
	pmc_enable_sleepwalking(CONSOLE_UART_ID);

	/* Wait for the match interrupt */
	while (!cmp_flag) {
	}

	usart_read(CONSOLE_UART, &temp);
	puts("'s' character is received.\r\n\r");

}

/**
 * \brief Test the usart sleepwalking in wait mode.
 */
static void usart_sleepwalking_test_wait(void)
{
	enum sleepmgr_mode current_sleep_mode = SLEEPMGR_WAIT;

	puts("Test in wait mode, press number '0' to '9' to wake up.\r");

	/* Wait for the puts operation to finish. */
	delay_ms(50);

	/* The sleep manage will set the clock to 24MRC in wait mode,
	 * reconfig the divisor */
	usart_set_async_baudrate(CONSOLE_UART, CONF_UART_BAUDRATE, OSC_MAINCK_24M_RC_HZ);

	/* Wait for the clock stable. */
	delay_ms(5);

	/* Set the wakeup condition */
	usart_set_sleepwalking(CONSOLE_UART, '0', true, true, '9');

	/* Enable the sleepwalking in PMC */
	pmc_enable_sleepwalking(CONSOLE_UART_ID);

	/* Enter wait mode. */
	sleepmgr_init();
	sleepmgr_lock_mode(current_sleep_mode);
	sleepmgr_enter_sleep();

	/* Config the divisor to the original setting */
	usart_set_async_baudrate(CONSOLE_UART, CONF_UART_BAUDRATE, sysclk_get_peripheral_hz());

	/* Wait for the clock stable. */
	delay_ms(5);

	puts("A character is received, system wake up.\r\n\r");

}

/**
 * \brief Configure UART console.
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
 * \brief Application entry point for the example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Initialize the SAM system */
	sysclk_init();
	board_init();    

	/* Initialize the UART console */
	configure_console();

	/* Output example information */
	puts(STRING_HEADER);

	/* First test sleepwalking in active mode */
	usart_sleepwalking_test_active();

	delay_s(1);

	/* Then test sleepwalking in wait mode */
	usart_sleepwalking_test_wait();

	puts("All test are done.\r\n\r");

	while (1) {
	}
}
