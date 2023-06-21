/**
 * \file
 *
 * \brief PIO Capture Example.
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
 *  \mainpage PIO Parallel Capture Example
 *
 *  \par Purpose
 *
 *  This example demonstrates how to use PIO Parallel Capture function of
 *  the PIO Controller.
 *
 *  \par Requirements
 *
 *  This package can only be used with SAM3/4 MCU featuring PIO Parallel 
 *  Capture function.
 *
 *  \par Description
 *
 *  The PIO Controller integrates an interface that is able to read data from
 *  a CMOS digital image sensor, a high-speed parallel ADC, a DSP synchronous
 *  port in synchronous mode, etc.
 *
 *  The application is composed of 2 softwares:
 *  - one for using the PIO to simulate a sensor in send mode.
 *  - one for using the PIO Parallel Capture in receive mode.
 *
 *  Two boards are required to use. Connect one to the other, and at first put
 *  one board in send mode(to avoid unexpected signal to slave) and then
 *  the second in receive mode.
 *  Different choices can be selected to use the data enable pins or not, and
 *  to sample all the data or only one out of two.
 *  Pins to be connected between the 2 boards:<br />
 *    PA15 - PA15<br />
 *    PA16 - PA16<br />
 *    PA23 - PA23<br />
 *    PA24 - PC0<br />
 *    PA25 - PC1 <br />
 *    PA26 - PC2<br />
 *    PA27 - PC3<br />
 *    PA28 - PC4<br />
 *    PA29 - PC5<br />
 *    PA30 - PC6<br />
 *    PA31 - PC7<br />
 *    And, of course: GND<br />
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
 *  -# Connect the first board to the second board.
 *  -# Start the application of the first board.
 *  -# Put the software in send mode.
 *  -# In the terminal window, the
 *     following text should appear (values depend on the board and the chip used):
 *     \code
	      -- PIO Parallel Capture example --
	      -- xxxx-xx --
	      -- Compiled: xxx xx xxxx xx:xx:xx --
	      Frequency: xxx MHz.
	      Press r to Receive data on PPIO Parallel Capture.
	      Press s to Send data on PIO Parallel Capture.
	      ** SEND mode **
	      This is for debug purpose only !
	      Frequency of PIO controller clock must be strictly superior to 2 times
	      the frequency of the clock of the device which generates the parallel data.

	      Please, connect the second board, and put it in receive mode.
	      Press y to indicate that receiver samples all data.
	      Press n to indicate that receiver samples data with an even index.
	      Receiver samples all data, or Receiver samples data with an even index.
	      Press y to send data without enabling the data enable pins.
	      Press n to send data with data enable pins enabled.
	      Send data without enabling the data enable pins, or Send data with both data enable pins enabled.
	      Send data without enabling the data enable pins.
	      Press a key
	      or
	      Send data with both data enable pins enabled.
	      Press a key
\endcode
 *  -# Start the application of the second board.
 *  -# Put the software in receive mode.
 *  -# In the terminal window, the
 *     following text should appear (values depend on the board and the chip used):
 *     \code
	-- PIO Parallel Capture example --
	-- xxxxxx-xx --
	-- Compiled: xxx xx xxxx xx:xx:xx --
	Frequency: xxx MHz
	Press r to Receive data on PIO Parallel Capture.
	Press s to Send data on PIO Parallel Capture.
	** RECEIVE mode **
	Press y to sample the data when both data enable pins are enabled.
	Press n to sample the data, don't care the status of the data enable pins.
	Receive data, don't care the status of the data enable pins, or Receive data when both data enable pins are enabled.
	Press y to sample all the data.
	Press n to sample the data only one out of two.
	Only one out of two data is sampled, with an even index, or All data are sampled.
	Waiting...
\endcode
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include "pio_handler.h"

/** Buffer size. */
#define SIZE_BUFF_RECEPT               (64)

/** Configure the PIO capture pins that send out data simulating as a sensor. */
#define PIO_CAPTURE_CCLK_IDX           PIO_PA23_IDX
#define PIO_CAPTURE_EN1_IDX            PIO_PA15_IDX
#define PIO_CAPTURE_EN2_IDX            PIO_PA16_IDX
#define PIO_CAPTURE_OUTPUT_PIN_FLAGS   (PIO_OUTPUT_0 | PIO_DEFAULT)
#define PIO_CAPTURE_DATA_PINS_MASK     (0x000000FF)
#define PIO_CAPTURE_CONTROL_PIN_MSK    ((1 << 15) | (1 << 16) | (1 << 23))

/** Data offset position. */
#define PIO_CAPTURE_DATA_POS           (0)

/** PIOA interrupt priority. */
#define PIO_IRQ_PRI                    (4)

#define STRING_EOL    "\r"
#define STRING_HEADER "-- PIO Parallel Capture example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/** PIO receive buffer. */
uint8_t pio_rx_buffer[SIZE_BUFF_RECEPT];

/** Test if a callback is received. */
volatile uint8_t g_uc_cbk_received = 0;

/** PDC data packet. */
pdc_packet_t packet_t;

/** Pointer to PDC register base. */
Pdc *p_pdc;

/**
 *  \brief Handler for capture function interrupt.
 *
 */
static void capture_handler(Pio *p_pio)
{
	uint8_t uc_i;
	uint32_t dummy_data;

	pio_capture_disable_interrupt(p_pio, (PIO_PCIDR_ENDRX | PIO_PCIDR_RXBUFF));
	/* Disable PDC transfer. */
	pdc_disable_transfer(p_pdc, PERIPH_PTCR_RXTEN);
	/* Clear any unwanted data */
	pio_capture_read(PIOA, &dummy_data);

	printf("End of receive.\r\n");
	for (uc_i = 0; uc_i < SIZE_BUFF_RECEPT; uc_i++) {
		printf("0x%X ", pio_rx_buffer[uc_i]);
	}
	printf("\r\n");
	g_uc_cbk_received = 1;
}

/**
 *  Configure UART for debug message output.
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
 * \brief pio_capture Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 *
 */
int main(void)
{
	uint8_t uc_i;
	uint32_t ul_length;
	uint32_t ul_mode;
	uint8_t uc_key;
	static uint8_t uc_rx_even_only;
	static uint8_t uc_tx_without_en;

	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	/* Configure UART for debug message output. */
	configure_console();

	/* Configure PIOA clock. */
	pmc_enable_periph_clk(ID_PIOA);
	pmc_enable_periph_clk(ID_PIOC);

	/* Configure PIO Capture handler */
	pio_capture_handler_set(capture_handler);

	/* Output example information. */
	puts(STRING_HEADER);

	printf("Frequency: %d MHz.\r\n",
			(uint8_t) (sysclk_get_cpu_hz() / 1000000));

	printf("Press r to Receive data on PIO Parallel Capture.\r\n");
	printf("Press s to Send data on PIO Parallel Capture.\r\n");
	uc_key = 0;
	while ((uc_key != 'r') && (uc_key != 's')) {
		uart_read(CONSOLE_UART, &uc_key);
	}
	if (uc_key == 'r') {
		printf("** RECEIVE mode **\r\n");

		/* Initialize PIO capture mode value. */
		ul_mode = 0;
		/* Set up the parallel capture mode data size as 8 bits. */
		ul_mode |= 0 << PIO_PCMR_DSIZE_Pos;

		printf("Press y to sample the data when both data enable pins are enabled.\r\n");
		printf("Press n to sample the data, don't care the status of the data enable pins.\r\n");
		uc_key = 0;
		while ((uc_key != 'y') && (uc_key != 'n')) {
			uart_read(CONSOLE_UART, &uc_key);
		}
		if (uc_key == 'y') {
			/* Sample the data when both data enable pins are enabled. */
			ul_mode &= ~PIO_PCMR_ALWYS;
			printf("Receive data when both data enable pins are enabled.\r\n");
		} else {
			/* Sample the data, don't care the status of the data enable pins. */
			ul_mode |= PIO_PCMR_ALWYS;
			printf("Receive data, don't care the status of the data enable pins.\r\n");
		}
		printf("Press y to sample all the data\r\n");
		printf("Press n to sample the data only one out of two.\r\n");
		uc_key = 0;
		while ((uc_key != 'y') && (uc_key != 'n')) {
			uart_read(CONSOLE_UART, &uc_key);
		}
		if (uc_key == 'y') {
			/* Sample all the data. */
			ul_mode &= ~PIO_PCMR_HALFS;
			printf("All data are sampled.\r\n");
		} else {
			/* Sample the data only one out of two. */
			ul_mode |= PIO_PCMR_HALFS;
			/* Only if half-Sampling is set, data with an even index are sampled. */
			ul_mode &= ~PIO_PCMR_FRSTS;
			printf("Only one out of two data is sampled, with an even index.\r\n");
		}

		/* Initialize PIO Parallel Capture function. */
		pio_capture_set_mode(PIOA, ul_mode);
		pio_capture_enable(PIOA);

		/* Disable all PIOA I/O line interrupt. */
		pio_disable_interrupt(PIOA, 0xFFFFFFFF);

		/* Configure and enable interrupt of PIO. */
		NVIC_DisableIRQ(PIOA_IRQn);
		NVIC_ClearPendingIRQ(PIOA_IRQn);
		NVIC_SetPriority(PIOA_IRQn, PIO_IRQ_PRI);
		NVIC_EnableIRQ(PIOA_IRQn);

		while (1) {
			g_uc_cbk_received = 0;

			/* Clear Receive buffer. */
			for (uc_i = 0; uc_i < SIZE_BUFF_RECEPT; uc_i++) {
				pio_rx_buffer[uc_i] = 0;
			}

			/* Set up PDC receive buffer, waiting for 64 bytes. */
			packet_t.ul_addr = (uint32_t) pio_rx_buffer;
			packet_t.ul_size = SIZE_BUFF_RECEPT;
			p_pdc = pio_capture_get_pdc_base(PIOA);
			pdc_rx_init(p_pdc, &packet_t, NULL);

			/* Enable PDC transfer. */
			pdc_enable_transfer(p_pdc, PERIPH_PTCR_RXTEN);

			/* Configure the PIO capture interrupt mask. */
			pio_capture_enable_interrupt(PIOA,
					(PIO_PCIER_ENDRX | PIO_PCIER_RXBUFF));

			printf("Waiting...\r\n");
			while (g_uc_cbk_received == 0) {
			}
		}
	} else if (uc_key == 's') {
		printf("** SEND mode **\r\n");
		printf("This is for debug purpose only !\r\n");
		printf("Frequency of PIO controller clock must be strictly superior");
		printf("to 2 times the frequency of the clock of the device which");
		printf(" generates the parallel data.\r\n");
		printf("\r\nPlease connect the second board, ");
		printf("and put it in receive mode.\r\n");

		/* Configure PIO pins which simulate as a sensor. */
		pio_configure_pin_group(PIOA, PIO_CAPTURE_CONTROL_PIN_MSK,
			PIO_CAPTURE_OUTPUT_PIN_FLAGS);
		pio_configure_pin_group(PIOC, PIO_CAPTURE_DATA_PINS_MASK,
			PIO_CAPTURE_OUTPUT_PIN_FLAGS);
		pio_set_pin_low(PIO_CAPTURE_EN1_IDX);
		pio_set_pin_low(PIO_CAPTURE_EN2_IDX);
		pio_set_pin_low(PIO_CAPTURE_CCLK_IDX);

		/* Enable sync. output data. */
		pio_enable_output_write(PIOC, PIO_CAPTURE_DATA_PINS_MASK);

		/* Initialize the capture data line. */
		pio_sync_output_write(PIOC, 0);

		printf("Press y to send data with data enable pins.\r\n");
		printf("Press n to send data without data enable pins.\r\n");

		uc_key = 0;
		while ((uc_key != 'y') && (uc_key != 'n')) {
			uart_read(CONSOLE_UART, &uc_key);
		}
		if (uc_key == 'y') {
			uc_tx_without_en = 0;
			printf("Send data with both data enable pins enabled.\r\n");
		} else {
			uc_tx_without_en = 1;
			printf("Send data without enabling the data enable pins.\r\n");
		}

		printf("Press y to indicate that receiver samples all data.\r\n");
		printf("Press n to indicate that receiver samples data with an even index.\r\n");
		uc_key = 0;
		while ((uc_key != 'y') && (uc_key != 'n')) {
			uart_read(CONSOLE_UART, &uc_key);
		}
		if (uc_key == 'y') {
			uc_rx_even_only = 0;
			printf("Receiver samples all data.\r\n");
		} else {
			uc_rx_even_only = 1;
			printf("Receiver samples data with an even index.\r\n");
		}

		ul_length = SIZE_BUFF_RECEPT * (1 + uc_rx_even_only);
		while (1) {
			if (uc_tx_without_en) {
				printf("\r\nSend data without enabling the data enable pins.\r\n");
			} else {
				printf("\r\nSend data with both data enable pins enabled.\r\n");
			}
			if (!uc_tx_without_en) {
				/* Set enable pins. */
				pio_set_pin_high(PIO_CAPTURE_EN1_IDX);
				pio_set_pin_high(PIO_CAPTURE_EN2_IDX);
			}
			for (uc_i = 0; uc_i < ul_length;) {
				/* Send data. */
				pio_sync_output_write(PIOC,
						(uc_i << PIO_CAPTURE_DATA_POS));
				/* Set clock. */
				pio_set_pin_high(PIO_CAPTURE_CCLK_IDX);
				delay_us(20);
				/* Clear clock. */
				pio_set_pin_low(PIO_CAPTURE_CCLK_IDX);
				delay_us(20);
				uc_i++;
			}
			if (!uc_tx_without_en) {
				/* Clear enable pins. */
				pio_set_pin_low(PIO_CAPTURE_EN1_IDX);
				pio_set_pin_low(PIO_CAPTURE_EN2_IDX);
			}
			printf("Press a key.\r\n");
			while (uart_read(CONSOLE_UART, &uc_key)) {
			}
		}
	}

	return 0;
}
