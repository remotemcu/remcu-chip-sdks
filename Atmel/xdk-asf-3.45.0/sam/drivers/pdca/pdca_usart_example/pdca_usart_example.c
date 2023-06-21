/**
 * \file
 *
 * \brief Peripheral DMA Controller Example for SAM4L.
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
 * \mainpage Peripheral DMA Controller Example
 *
 * \section Purpose
 *
 * The pdca_usart example demonstrates how to use PDCA driver to send 
 * data to the USART.
 *
 * \section Requirements
 *
 * This example can be used on SAM4L series.
 *
 * \section Description
 *
 * The SAM4L controller sends data in ascii_anim1.h and ascii_anim2.h from USART
 * to the terminal.
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
	-- PDCA_USART Example xxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 * -# the sent text should appear.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "stdio_serial.h"
#include "conf_board.h"

#define PDCA_TX_CHANNEL  0

#define STRING_EOL    "\r"
#define STRING_HEADER "-- PDCA_USART Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/* Counter for interrupt test. */
volatile int bool_anim = 1;

/* String for ASCII animation: this is the first part of the ASCII animation. */
const char ascii_anim1[] =
#include "ascii_anim1.h"
;

/*
* String for ASCII animation: this is the second and final part of the ASCII
* animation.
*/
const char ascii_anim2[] =
#include "ascii_anim2.h"
;

/* PDCA channel options */
static const pdca_channel_config_t pdca_tx_configs = {
	.addr   = (void *)ascii_anim1,      /* memory address              */
	.pid    = PDCA_PID_USART_TX,        /* select peripheral           */
	.size   = sizeof(ascii_anim1),      /* transfer counter            */
	.r_addr = 0,                        /* next memory address         */
	.r_size = 0,                        /* next transfer counter       */
	.etrig  = false,                    /* disable the transfer upon event
										 * trigger */
	.ring   = false,                    /* disable ring buffer mode    */
	.transfer_size = PDCA_MR_SIZE_BYTE  /* select size of the transfer */
};

/**
 * \brief Interrupt handler for UART interrupt.
 */
static void pdca_tranfer_done(enum pdca_channel_status status)
{
	/* Get PDCA channel status and check if PDCA transfer complete */
	if (status == PDCA_CH_TRANSFER_COMPLETED) {
		/* Configure PDCA for data transfer */
		if (bool_anim == 1){
			pdca_channel_write_reload(PDCA_TX_CHANNEL, (void *)ascii_anim2,
				sizeof( ascii_anim2 ));
			bool_anim = 2;
		} else {
			pdca_channel_write_reload(PDCA_TX_CHANNEL, (void *)ascii_anim1,
				sizeof( ascii_anim1 ));
			bool_anim = 1;
		}
	}
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
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief Application entry point for pdca_usart example.
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

	/* Enable PDCA module clock */
	pdca_enable(PDCA);

	/* Init PDCA channel with the pdca_options.*/
	pdca_channel_set_config(PDCA_TX_CHANNEL, &pdca_tx_configs);

	/* Enable PDCA channel */
	pdca_channel_enable(PDCA_TX_CHANNEL);

	pdca_channel_set_callback(PDCA_TX_CHANNEL, pdca_tranfer_done, PDCA_0_IRQn,
		1, PDCA_IER_RCZ);

	while (1) {
	}
}
