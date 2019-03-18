/**
 * \file
 *
 * \brief USART RS485 example with PDCA for SAM.
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
 *  \mainpage USART RS485 Example with PDCA
 *
 *  \par Purpose
 *
 *  The USART RS485 Example  with PDCA demonstrates how to use USART in RS485
 *  mode.
 *
 *  \par Requirements
 *
 *  This package can be used with SAM4L EK boards. Before running, make sure
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
#include <asf.h>
#include "conf_board.h"
#include "conf_clock.h"
#include "conf_example.h"

/** Size of the receive buffer and transmit buffer. */
#define BUFFER_SIZE         1280

/** PDCA receive channel setting. */
#define PDCA_RX_CHANNEL  0
/** PDCA transfer channel setting. */
#define PDCA_TX_CHANNEL  1
/** PDCA channel peripheral setting. */
#define PDCA_PID_USART0_RX    0
#define PDCA_PID_USART0_TX    18

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

/** PDC channel options. */
pdca_channel_config_t PDCA_RX_OPTIONS = {
	.addr = (void *)g_uc_receive_buffer, /* memory address */
	.pid = PDCA_PID_USART0_RX, /* select peripheral - USART0 RX line.*/
	.size = BUFFER_SIZE, /* transfer counter */
	.r_addr = NULL, /* next memory address */
	.r_size = 0, /* next transfer counter */
	.transfer_size = PDCA_MR_SIZE_BYTE /* select size of the transfer */
};
pdca_channel_config_t PDCA_TX_OPTIONS = {
	.addr = (void *)g_uc_transmit_buffer, /* memory address */
	.pid = PDCA_PID_USART0_TX, /* select peripheral - USART0 TX line.*/
	.size = BUFFER_SIZE, /* transfer counter */
	.r_addr = NULL, /* next memory address */
	.r_size = 0, /* next transfer counter */
	.transfer_size = PDCA_MR_SIZE_BYTE /* select size of the transfer */
};

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
 * \brief Interrupt handler for PDCA interrupt.
 */
static void PDCA_RX_Handler(enum pdca_channel_status status)
{
	/* Check if PDCA transfer complete */
	if (status == PDCA_CH_TRANSFER_COMPLETED) {
		/* Indicate receiving finished. */
		g_state = RECEIVED;
		pdca_channel_disable_interrupt(PDCA_RX_CHANNEL, PDCA_IER_TRC);
	}
}

/**
 * \brief Interrupt handler for PDCA interrupt.
 */
static void PDCA_TX_Handler(enum pdca_channel_status status)
{
	/* Check if PDCA transfer complete */
	if (status == PDCA_CH_TRANSFER_COMPLETED) {
		/* Transmit continuously. */
		g_state = TRANSMITTED;
		pdca_channel_disable_interrupt(PDCA_TX_CHANNEL, PDCA_IER_TRC);
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
			sysclk_get_peripheral_bus_hz(BOARD_USART));

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
	stdio_serial_init(CONF_UART, &uart_serial_options);
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
	uint8_t uc_receive, uc_send = SYNC_CHAR;
	uint32_t time_elapsed = 0;
	uint32_t i;

	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	/* Configure UART for debug message output. */
	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);

	/* 1ms tick. */
	configure_systick();

	/* Configure USART. */
	configure_usart();

	/* Initialize receiving buffer to distinguish with the sent frame. */
	memset(g_uc_receive_buffer, 0x0, BUFFER_SIZE);

	/*
	 * Enable transmitter here, and disable receiver first, to avoid receiving
	 * characters sent by itself. It's necessary for half duplex RS485.
	 */
	usart_enable_tx(BOARD_USART);
	usart_disable_rx(BOARD_USART);

	/* Enable PDCA module clock */
	pdca_enable(PDCA);

	/* Init PDCA channel with the pdca_options.*/
	pdca_channel_set_config(PDCA_RX_CHANNEL, &PDCA_RX_OPTIONS);
	pdca_channel_set_config(PDCA_TX_CHANNEL, &PDCA_TX_OPTIONS);

	/* Send a sync character XON (0x11). */
	pdca_channel_write_load(PDCA_TX_CHANNEL, &uc_send, 1);
	/* Enable transfer PDCA channel */
	pdca_channel_enable(PDCA_TX_CHANNEL);

	/* Delay until the line is cleared, an estimated time used. */
	wait(50);

	/* Then enable receiver. */
	usart_enable_rx(BOARD_USART);

	/* Read the acknowledgement. */
	pdca_channel_write_load(PDCA_RX_CHANNEL, &uc_receive, 1);
	/* Enable PDCA channel */
	pdca_channel_enable(PDCA_RX_CHANNEL);


	/* Wait until time out or acknowledgement is received. */
	time_elapsed = get_tick_count();
	while (pdca_get_channel_status(PDCA_RX_CHANNEL) !=
			PDCA_CH_TRANSFER_COMPLETED) {
		if (get_tick_count() - time_elapsed > TIMEOUT) {
			break;
		}
	}

	/* If acknowledgement received in a short time. */
	if (pdca_get_channel_status(PDCA_RX_CHANNEL) ==
			PDCA_CH_TRANSFER_COMPLETED) {
		/* Acknowledgement. */
		if (uc_receive == ACK_CHAR) {
			/* Act as transmitter, start transmitting. */
			puts("-I- Act as transmitter.\r");

			g_state = TRANSMITTING;
			puts("-I- Start transmitting!\r");
			pdca_channel_write_load(PDCA_TX_CHANNEL, g_uc_transmit_buffer,
					BUFFER_SIZE);

			/* Enable PDCA interrupt */
			pdca_channel_set_callback(PDCA_TX_CHANNEL, PDCA_TX_Handler,
					PDCA_1_IRQn, 1, PDCA_IER_TRC);

			while (g_state != TRANSMITTED) {
			}
			puts("-I- Transmit done!\r");

			while (1) {
			}
		}
	} else {
		/* Start receiving, act as receiver. */
		puts("-I- Act as receiver.\r");
		puts("-I- Receiving sync character.\r");

		while (pdca_get_channel_status(PDCA_RX_CHANNEL) !=
			PDCA_CH_TRANSFER_COMPLETED) {
		}

		/* Sync character is received. */
		if (uc_receive == SYNC_CHAR) {
			puts("-I- Received sync character.\r");
			/* SEND XOff as acknowledgement. */
			uc_send = ACK_CHAR;

			/*
			 * Delay to prevent the character from being discarded by
			 * transmitter due to responding too soon.
			 */
			wait(100);
			ioport_set_pin_level(RS485_USART_CTS_PIN, 1);
			pdca_channel_write_load(PDCA_TX_CHANNEL, &uc_send, 1);

			g_state = RECEIVING;
			puts("-I- Start receiving buffer!\r");

			pdca_channel_write_load(PDCA_RX_CHANNEL, g_uc_receive_buffer,
					BUFFER_SIZE);

			/* Enable PDCA interrupt */
			pdca_channel_set_callback(PDCA_RX_CHANNEL, PDCA_RX_Handler,
					PDCA_0_IRQn, 1, PDCA_IER_TRC);

			ioport_set_pin_level(RS485_USART_CTS_PIN, 0);

			while (g_state != RECEIVED) {
			}
		}
	}

	i = 0;
	/* Check received frame. */
	while (i < BUFFER_SIZE) {
		if (g_uc_transmit_buffer[i] != g_uc_receive_buffer[i]) {
			puts("-E- Error occurred while receiving!\r");
			/* Infinite loop here. */
			while (1) {
			}
		}

		i++;
	}
	puts("-I- Received buffer successfully!\r");

	while (1) {
	}
}
