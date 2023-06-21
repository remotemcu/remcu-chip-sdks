/**
 * \file
 *
 * \brief Matrix example for SAM.
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
 * \mainpage MATRIX Example
 *
 * \section Purpose
 *
 * This example demonstrates the Bus Matrix (MATRIX) provided on
 * SAM microcontrollers.
 *
 * \section Requirements
 *
 * This example can be used on any SAM boards.
 *
 * \section Description
 *
 * This example shows running speed between two matrix configuration.
 * LED toggle times in one second is measured.
 * The first test is done with Round-Robin arbitration without default master.
 * The second test is done with Round-Robin arbitration with last access master.
 * As expected, the LED toggle times of test1 is lower than that of test2.
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
	-- MATRIX Example --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
	Configure system tick to get 1ms tick period.
	-- Test1: configure Round-Robin arbitration without default master. --
	    Led toggled xxx times in one second
	-- Test2: configure Round-Robin arbitration with last access master. --
	    Led toggled xxx times in one second
\endcode
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "stdio_serial.h"
#include "conf_board.h"
#include "conf_clock.h"

/* Matrix slave number */
#if (SAM3S || SAM4S)
#define MATRIX_SLAVE_NUM    5
#elif (SAM3N || SAM4N || SAMG)
#define MATRIX_SLAVE_NUM    4
#elif (SAM3XA)
#define MATRIX_SLAVE_NUM    9
#elif (SAM3U)
#define MATRIX_SLAVE_NUM    10
#elif (SAM4E)
#define MATRIX_SLAVE_NUM    6
#elif (SAM4C || SAM4CP || SAM4CM)
#define MATRIX_SLAVE_NUM    8
#elif (SAMV71 || SAMV70 || SAMS70 || SAME70)
#define MATRIX_SLAVE_NUM    9
#else
#warning "Not define matrix slave number, set 1 for default."
#define MATRIX_SLAVE_NUM    1
#endif

#define STRING_EOL    "\r"
#define STRING_HEADER "-- MATRIX Example --\r\n" \
	"-- "BOARD_NAME " --\r\n" \
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

/* Global g_ul_ms_ticks in milliseconds since start of application */
volatile uint32_t g_ul_ms_ticks = 0;

/**
 * \brief Configure the console UART.
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
 * \brief Toggle led at the given time.
 *
 * \param ul_dly_ticks  Delay to wait for, in milliseconds.
 *
 * \return Led toggle times.
 */
static uint32_t toggle_led_test(uint32_t ul_dly_ticks)
{
	int32_t ul_cnt = 0;
	uint32_t ul_cur_ticks;

	ul_cur_ticks = g_ul_ms_ticks;
	do {
		ul_cnt++;
	#if SAM4CM
		ioport_toggle_pin_level(LED4_GPIO);
	#else
		ioport_toggle_pin_level(LED0_GPIO);
	#endif
	} while ((g_ul_ms_ticks - ul_cur_ticks) < ul_dly_ticks);

	return ul_cnt;
}

/**
 * \brief Handler for System Tick interrupt.
 *
 * Process System Tick Event.
 * Increment the g_ul_ms_ticks counter.
 */
void SysTick_Handler(void)
{
	g_ul_ms_ticks++;
}

/**
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint32_t ul_slave_id, ul_cnt;

	/* Initialize the system */
	sysclk_init();
	board_init();

	/* Configure console UART */
	configure_console();

	/* Output example information */
	puts(STRING_HEADER);

	/* Configure systick for 1 ms */
	puts("Configure system tick to get 1ms tick period.\r");
	if (SysTick_Config(sysclk_get_cpu_hz() / 1000)) {
		puts("-F- Systick configuration error\r");
		while (1) {
		}
	}

	/* First, test with Round-Robin arbitration without default master */
	puts("-- Test1: configure Round-Robin arbitration without default master. --\r");
	for (ul_slave_id = 0; ul_slave_id < MATRIX_SLAVE_NUM; ul_slave_id++) {
#if (!SAM4E) && (!SAM4C) && (!SAM4CP) && (!SAM4CM) && \
	(!SAMV71) && (!SAMV70) && (!SAMS70) && (!SAME70)
		matrix_set_slave_arbitration_type(ul_slave_id,
				MATRIX_ARBT_ROUND_ROBIN);
#endif
		matrix_set_slave_default_master_type(ul_slave_id,
				MATRIX_DEFMSTR_NO_DEFAULT_MASTER);
	}
	ul_cnt = toggle_led_test(1000);
	printf("Led toggled %ld times in one second\n\r", (long)ul_cnt);

	/* Second, test with Round-Robin arbitration with last access master */
	puts("-- Test2: configure Round-Robin arbitration with last access master. --\r");
	for (ul_slave_id = 0; ul_slave_id < MATRIX_SLAVE_NUM; ul_slave_id++) {
#if (!SAM4E) && (!SAM4C) && (!SAM4CP) && (!SAM4CM) && \
	(!SAMV71) && (!SAMV70) && (!SAMS70) && (!SAME70)
		matrix_set_slave_arbitration_type(ul_slave_id,
				MATRIX_ARBT_ROUND_ROBIN);
#endif
		matrix_set_slave_default_master_type(ul_slave_id,
				MATRIX_DEFMSTR_LAST_DEFAULT_MASTER);
	}
	ul_cnt = toggle_led_test(1000);
	printf("Led toggled %ld times in one second\n\r", (long)ul_cnt);

	/* Endless loop */
	while (1) {
	}
}
