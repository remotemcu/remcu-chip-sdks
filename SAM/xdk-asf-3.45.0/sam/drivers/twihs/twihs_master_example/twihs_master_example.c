/**
 * \file
 *
 * \brief TWIHS MASTER Example for SAM.
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

/**
 * \mainpage TWI MASTER Example
 *
 * \section intro Introduction
 *
 * The application demonstrates how to use the SAM TWIHS driver to access an
 * external serial EEPROM chip.
 *
 * \section Requirements
 *
 * This package can be used with the following setup:
 *  - SAMV71 Xplained Ultra kit
 *  - SAME70 Xplained kit
 *
 * \section files Main files:
 *  - twihs.c SAM Two-Wire Interface driver implementation.
 *  - twihs.h SAM Two-Wire Interface driver definitions.
 *  - TWIHS_master_example.c Example application.
 *
 * \section exampledescription Description of the Example
 * Upon startup, the program configures PIOs for console UART, LEDs and TWIHS
 * connected to EEPROM on board. Then it configures the TWIHS driver and data
 * package. The clock of I2C bus is set as 400kHz.
 * After initializing the master mode, the example sends test pattern to the
 * EEPROM. When sending is complete, TWIHS driver reads the memory and saves the
 * content in the reception buffer. Then the program compares the content
 * received with the test pattern sent before and prints the comparison result.
 * The corresponding LED is turned on.
 *
 * On SAM Xplained Pro, the EEPROM is simulated though the TWIHS_slave_example,
 * which means 2 SAM Xplained Pro boards are required to run this example.
 * One board executes this example as the twi master and another runs
 * TWIHS_salve_example as the simulated EEPROM.
 * The TWI PINs and GND PIN should be connected between these 2 boards.
 * More information of the simulated EEPROM implementation can be referred in
 * the description of TWIHS_slave_example.
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
#include "stdio_serial.h"
#include "conf_board.h"
#include "led.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/** EEPROM Wait Time */
#define WAIT_TIME   10
/** TWI Bus Clock 400kHz */
#define TWIHS_CLK     400000
/** Address of AT24C chips */
#define AT24C_ADDRESS           0x50
#define EEPROM_MEM_ADDR         0
#define EEPROM_MEM_ADDR_LENGTH  2

#define STRING_EOL    "\r"
#define STRING_HEADER "--TWIHS MASTER Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
/** TWI ID for simulated EEPROM application to use */
#define BOARD_ID_TWIHS_EEPROM         ID_TWIHS0
/** TWI Base for simulated TWI EEPROM application to use */
#define BOARD_BASE_TWIHS_EEPROM       TWIHS0
/** The address for simulated TWI EEPROM application */
#undef  AT24C_ADDRESS
#define AT24C_ADDRESS        0x40
#endif

static const uint8_t test_data_tx[] = {
	/** SAM TWI EEPROM EXAMPLE */
	'S', 'A', 'M', ' ', 'T', 'W', 'I', ' ',
	'E', 'E', 'P', 'R', 'O', 'M', ' ',
	'E', 'X', 'A', 'M', 'P', 'L', 'E'
};

/** Data to be sent */
#define TEST_DATA_LENGTH  (sizeof(test_data_tx) / sizeof(uint8_t))

/** Reception buffer */
static uint8_t gs_uc_test_data_rx[TEST_DATA_LENGTH] = { 0 };

/** Global timestamp in milliseconds since start of application */
volatile uint32_t g_ul_ms_ticks = 0;

/**
 *  \brief Handler for System Tick interrupt.
 *
 *  Process System Tick Event
 *  increments the timestamp counter.
 */
void SysTick_Handler(void)
{
	g_ul_ms_ticks++;
}

/**
 *  \brief Configure the Console UART.
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
 *  \brief Wait for the given number of milliseconds (using the dwTimeStamp
 *         generated by the SAM microcontrollers' system tick).
 *  \param ul_dly_ticks  Delay to wait for, in milliseconds.
 */
static void mdelay(uint32_t ul_dly_ticks)
{
	uint32_t ul_cur_ticks;

	ul_cur_ticks = g_ul_ms_ticks;
	while ((g_ul_ms_ticks - ul_cur_ticks) < ul_dly_ticks);
}

/**
 * \brief Application entry point for TWI EEPROM example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint32_t i;
	twihs_options_t opt;
	twihs_packet_t packet_tx, packet_rx;

	/* Initialize the SAM system */
	sysclk_init();

	/* Initialize the board */
	board_init();

	/* Turn off LEDs */
	LED_Off(LED0);

    /* Initialize the console UART */
	configure_console();

	/* Output example information */
	puts(STRING_HEADER);

	/* Configure systick for 1 ms */
	puts("Configure system tick to get 1ms tick period.\r");
	if (SysTick_Config(sysclk_get_cpu_hz() / 1000)) {
		puts("-E- Systick configuration error\r");
		while (1) {
			/* Capture error */
		}
	}

	/* Enable the peripheral clock for TWI */
	pmc_enable_periph_clk(BOARD_ID_TWIHS_EEPROM);

	/* Configure the options of TWI driver */
	opt.master_clk = sysclk_get_peripheral_hz();
	opt.speed      = TWIHS_CLK;

	/* Configure the data packet to be transmitted */
	packet_tx.chip        = AT24C_ADDRESS;
	packet_tx.addr[0]     = EEPROM_MEM_ADDR >> 8;
	packet_tx.addr[1]     = EEPROM_MEM_ADDR;
	packet_tx.addr_length = EEPROM_MEM_ADDR_LENGTH;
	packet_tx.buffer      = (uint8_t *) test_data_tx;
	packet_tx.length      = TEST_DATA_LENGTH;

	/* Configure the data packet to be received */
	packet_rx.chip        = packet_tx.chip;
	packet_rx.addr[0]     = packet_tx.addr[0];
	packet_rx.addr[1]     = packet_tx.addr[1];
	packet_rx.addr_length = packet_tx.addr_length;
	packet_rx.buffer      = gs_uc_test_data_rx;
	packet_rx.length      = packet_tx.length;

	if (twihs_master_init(BOARD_BASE_TWIHS_EEPROM, &opt) != TWIHS_SUCCESS) {
		puts("-E-\tTWI master initialization failed.\r");
		while (1) {
			/* Capture error */
		}
	}

	/* Send test pattern to EEPROM */
	if (twihs_master_write(BOARD_BASE_TWIHS_EEPROM, &packet_tx) != TWIHS_SUCCESS) {
		puts("-E-\tTWI master write packet failed.\r");
		while (1) {
			/* Capture error */
		}
	}
	puts("Write:\tOK!\n\r");

	/* Wait at least 10 ms */
	mdelay(WAIT_TIME);

	/* Get memory from EEPROM*/
	if (twihs_master_read(BOARD_BASE_TWIHS_EEPROM, &packet_rx) != TWIHS_SUCCESS) {
		puts("-E-\tTWI master read packet failed.\r");
		while (1) {
			/* Capture error */
		}
	}
	puts("Read:\tOK!\r");

	/* Compare the sent and the received */
	for (i = 0; i < TEST_DATA_LENGTH; i++) {
		if (test_data_tx[i] != gs_uc_test_data_rx[i]) {
			/* No match */
			puts("Data comparison:\tUnmatched!\r");
			while (1) {
				/* Capture error */
			}
		}
	}
	/* Match */
	puts("Data comparison:\tMatched!\r");
	LED_On(LED0);
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
