/**
 * \file
 *
 * \brief USART RS485 example for SAM.
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
 *  \mainpage USART RS485 Example with PDC
 *
 *  \par Purpose
 *
 *  The USART RS485 Example demonstrates how to use USART in RS485
 *  mode.
 *
 *  \par Requirements
 *
 *  This package can be used with same70_xplained_pro/samv71_xplained_ulta boards. Before running, make sure
 *  to connect two boards with RS485 lines. Match each paired pins of two
 *  boards respectively with A to A, B to B and FGND to FGND.
 *
 *  Please refer to the board user guide for the details of RS485 jumper
 *  settings.
 *
 *  \par Description
 *
 *  This example connects two boards through RS485 interface. One board acts
 *  as the transmitter and the other one as the receiver. It is determined by
 *  the sequence that the two applications started.
 *
 *  In any case, the application sends a sync character at running to seek a
 *  receiver. If the acknowledgement is received in a short time, it will act
 *  as the transmitter and then send a full frame text to the receiver.
 *
 *  The earlier started board will act automatically as the receiver due to no
 *  acknowledgement received. The receiver will wait until sync character is
 *  received. Then it sends the acknowledgement and waits for the full frame
 *  sent by the transmitter. At the end of reception, it prints out message
 *  through UART interface to assert that the whole process succeeds.
 *
 *  \par Usage
 *
 *  -# Build the program and download it into the two evaluation boards.
 *  -# Connect a serial cable to the UART port for each evaluation kit.
 *  -# On the computer, open and configure a terminal application for each board
 *     (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *    - 115200 bauds
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# Start application from two boards in sequence. Make sure the second board
 *     should NOT be started unless the first board has run to wait for the
 *     synchronizing character. The output message in later section would
 *     describe this.
 *
 *  -# In the terminal window, the following text should appear:
 *     \code
	-- USART RS485 Example --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 *  -# The consequent messages will indicate the boards' behavior.
 *
 *     -  The earlier started board will output the message below to indicate it
 *     is waiting for a synchronization character:
 *     \code
	-I- Receiving sync character.
\endcode
 *     -  If it receives a sync character and prepare to receive a frame, it
 *     will print out the message below:
 *     \code
	-I- Start receiving!
\endcode
 *     -  After successfully receives a frame, the board will output the
 *     following message to indicate that the whole process succeeds.
 *     \code
	-I- Received successfully!
\endcode
 *     -  The later started one will act as transmitter, and if it receives an
 *     acknowledgement character successfully, it will output the following
 *     message and start transmitting:
 *     \code
	-I- Start transmitting!
\endcode
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <string.h>
#include "asf.h"
#include "stdio_serial.h"
#include "conf_board.h"
#include "conf_clock.h"
#include "conf_example.h"

/** Size of the receive buffer and transmit buffer. */
#define BUFFER_SIZE         2000

/** Size of the buffer. */
#define PDC_BUF_SIZE        BUFFER_SIZE

/** Acknowledge time out. */
#define TIMEOUT             (1000)

/** Character to synchronize with the other end. */
#define SYNC_CHAR            0x11

/** Character to acknowledge receipt of the sync char. */
#define ACK_CHAR             0x13

/** All interrupt mask. */
#define ALL_INTERRUPT_MASK   0xffffffff

/** System tick frequency in Hz. */
#define SYS_TICK_FREQ        1000

#define STRING_EOL    "\r"
#define STRING_HEADER "-- USART RS485 Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/** State of the USART. */
typedef enum st_usart_state {
	INITIALIZED,
	TRANSMITTING,
	RECEIVING,
	RECEIVED,
	TRANSMITTED
} usart_state_t;

/** Global usart state. */
volatile usart_state_t g_state = INITIALIZED;

/** Tick Counter in unit of ms. */
volatile uint32_t g_ul_tick_count;

/** Transmit buffer. Pure ASCII text. */
uint8_t g_uc_transmit_buffer[BUFFER_SIZE] = "DESCRIPTION of this example: \r\n \
 **************************************************************************\r\n\
 *  This application gives an example of how to use USART in RS485 mode.\r\n\
 *  RS-485 is a standard defining the electrical characteristics of drivers \r\n\
 *  and receivers for use in balanced digital multipoint systems. The standard \r\n\
 *  is published by the ANSI TIA/EIA. \r\n\
 *  \r\n\
 *  This example connects two boards through RS485 interface. One board acts \r\n\
 *  as the transmitter and the other one as the receiver. It is determined by \r\n\
 *  the sequence the two applications started. The earlier started board will \r\n\
 *  act automatically as the receiver due to no acknowledgement received. The \r\n\
 *  receiver will wait until sync character is received. Then it sends the \r\n\
 *  acknowledgement and waits for the full frame sent by the transmitter. \r\n\
 *  At the end of reception, it prints out message through UART interface to \r\n\
 *  assert that the whole process succeeds.\r\n\
 **************************************************************************\r\n\
 END of DESCRIPTION \r\n\
 ";

/** Receive buffer. */
uint8_t g_uc_receive_buffer[BUFFER_SIZE];

/** Pointer to receive buffer base. */
uint8_t *p_revdata = &g_uc_receive_buffer[0];
/** count number for received data. */
uint32_t g_ulcount = 0;

/**
 *  \brief Handler for System Tick interrupt.
 *
 *  Process System Tick Event.
 *  Increment the ul_ms_ticks counter.
 */
void SysTick_Handler(void)
{
	g_ul_tick_count++;
}

/**
 *  \brief Get the tick count value.
 *
 */
static uint32_t get_tick_count(void)
{
	return g_ul_tick_count;
}

/**
 *  \brief Wait for some time in ms.
 *
 */
static void wait(volatile uint32_t ul_ms)
{
	uint32_t ul_start;
	uint32_t ul_current;

	ul_start = g_ul_tick_count;
	do {
		ul_current = g_ul_tick_count;
	} while (ul_current - ul_start < ul_ms);
}

/**
 *  \brief Handler for USART interrupt.
 *
 */
void USART_Handler(void)
{
	uint32_t ul_status;
	uint8_t uc_char;

	/* Read USART status. */
	ul_status = usart_get_status(BOARD_USART);

	/*transmit interrupt rises*/
	if(ul_status & (US_IER_TXRDY | US_IER_TXEMPTY)) {
		usart_disable_interrupt(BOARD_USART, (US_IER_TXRDY | US_IER_TXEMPTY));
	}

	/*receive interrupt rise, store character to receiver buffer*/
	if((g_state == RECEIVING) && (usart_read(BOARD_USART, (uint32_t *)&uc_char) == 0)) {
		*p_revdata++ = uc_char;
		g_ulcount++;
		if(g_ulcount >= BUFFER_SIZE) {
			g_state = RECEIVED;
			usart_disable_interrupt(BOARD_USART, US_IER_RXRDY);
		}
	}
}

/**
 *  \brief USART RS485 mode configuration.
 *
 *  Configure USART in RS485 mode, asynchronous, 8 bits, 1 stop bit,
 *  no parity, 256000 bauds and enable its transmitter and receiver.
 */
static void configure_usart(void)
{
	const sam_usart_opt_t usart_console_settings = {
		BOARD_USART_BAUDRATE,
		US_MR_CHRL_8_BIT,
		US_MR_PAR_NO,
		US_MR_NBSTOP_1_BIT,
		US_MR_CHMODE_NORMAL,
		/* This field is only used in IrDA mode. */
		0
	};

	/* Enable the peripheral clock in the PMC. */
	sysclk_enable_peripheral_clock(BOARD_ID_USART);

	/* Configure USART in RS485 mode. */
	usart_init_rs485(BOARD_USART, &usart_console_settings,
			sysclk_get_peripheral_hz());

	/* enable transmitter timeguard, 4 bit period delay. */
	usart_set_tx_timeguard(BOARD_USART, 4);

	/* Disable all the interrupts. */
	usart_disable_interrupt(BOARD_USART, ALL_INTERRUPT_MASK);

	/* Enable TX & RX function. */
	usart_enable_tx(BOARD_USART);
	usart_enable_rx(BOARD_USART);

	/* Configure and enable interrupt of USART. */
	NVIC_EnableIRQ(USART_IRQn);
}

/**
 *  Configure system tick to generate an interrupt every 1ms.
 */
static void configure_systick(void)
{
	uint32_t ul_flag;

	ul_flag = SysTick_Config(sysclk_get_cpu_hz() / SYS_TICK_FREQ);
	if (ul_flag) {
		puts("-F- Systick configuration error\r");
		while (1) {
		}
	}
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
* \brief transmit data.
*
* \param *p_buff  data to be transmitted
* \param ulsize size of all data.
*
*/
static uint8_t func_transmit(const uint8_t *p_buff, uint32_t ulsize)
{
	Assert(p_buff);

	while(ulsize > 0) {
		if(0 == usart_write(BOARD_USART, *p_buff)){
			usart_enable_interrupt(BOARD_USART, US_IER_TXRDY | US_IER_TXEMPTY);
			ulsize--;
			p_buff++;
		}
	}

	while(!usart_is_tx_empty(BOARD_USART)) {
		;  /*waiting for transmit over*/
	}

	return 0;
}

/**
 * \brief Dump buffer to uart.
 *
 */
static void dump_info(char *p_buf, uint32_t ul_size)
{
	uint32_t ul_i = 0;

	while ((ul_i < ul_size) && (p_buf[ul_i] != 0)) {
		printf("%c", p_buf[ul_i++]);
	}
}

/**
 *  \brief usart_rs485 Application entry point.
 *
 *  Configure USART in RS485 mode. If the application starts earlier, it acts
 *  as a receiver. Otherwise, it should be a transmitter.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	static uint8_t uc_sync = SYNC_CHAR;
	uint32_t time_elapsed = 0;
	uint32_t ul_i;

	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	/* Configure UART for debug message output. */
	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);

	/* Configure USART. */
	configure_usart();


	/* 1ms tick. */
	configure_systick();

	/* Initialize receiving buffer to distinguish with the sent frame. */
	memset(g_uc_receive_buffer, 0x0, BUFFER_SIZE);

	/*
	 * Enable transmitter here, and disable receiver first, to avoid receiving
	 * characters sent by itself. It's necessary for half duplex RS485.
	 */
	usart_enable_tx(BOARD_USART);
	usart_disable_rx(BOARD_USART);

	/* Send a sync character XON (0x11). */
	func_transmit(&uc_sync, 1);
	/* Delay until the line is cleared, an estimated time used. */
	wait(50);

	/* Then enable receiver. */
	usart_enable_rx(BOARD_USART);

	/* Wait until time out or acknowledgement is received. */
	time_elapsed = get_tick_count();
	while (!usart_is_rx_ready(BOARD_USART)) {
		if (get_tick_count() - time_elapsed > TIMEOUT) {
			break;
		}
	}

	/* If acknowledgement received in a short time. */
	if (usart_is_rx_ready(BOARD_USART)) {
		wait(50);
		usart_read(BOARD_USART, (uint32_t *)&uc_sync);
		/* Acknowledgement. */
		if (uc_sync == ACK_CHAR) {
			/* Act as transmitter, start transmitting. */
			g_state = TRANSMITTING;
			puts("-I- Start transmitting!\r");

			func_transmit(&g_uc_transmit_buffer[0], BUFFER_SIZE);
		}
	} else {
		/* Start receiving, act as receiver. */
		puts("-I- Receiving sync character.\r");
		while (!usart_is_rx_ready(BOARD_USART)) {
		}
		wait(50);
		/* Sync character is received. */
		usart_read(BOARD_USART, (uint32_t *)&uc_sync);
		if (uc_sync == SYNC_CHAR) {
			/* SEND XOff as acknowledgement. */
			uc_sync = ACK_CHAR;

			/*
			 * Delay to prevent the character from being discarded by
			 * transmitter due to responding too soon.
			 */
			wait(50);

			/* Send a ack character XOff . */
			func_transmit(&uc_sync, 1);

			g_state = RECEIVING;
			puts("-I- Start receiving!\r");

			/* Enable receiving interrupt. */
			usart_enable_interrupt(BOARD_USART, US_IER_RXRDY);
		}
	}
	while (g_state != RECEIVED) {
	}

	ul_i = 0;
	/* Print received frame out. */
	while ((ul_i < BUFFER_SIZE) && (g_uc_receive_buffer[ul_i] != '\0')) {
		if (g_uc_transmit_buffer[ul_i] != g_uc_receive_buffer[ul_i]) {
			puts("-E- Error occurred while receiving!\r");
			/* Infinite loop here. */
			while (1) {
			}
		}
		ul_i++;
	}
	puts("-I- Received successfully!\r");
	dump_info((char *)g_uc_receive_buffer, BUFFER_SIZE);
	while (1) {
	}
}
