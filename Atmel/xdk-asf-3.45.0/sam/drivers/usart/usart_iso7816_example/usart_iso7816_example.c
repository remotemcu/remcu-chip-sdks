/**
 * \file
 *
 * \brief USART ISO7816 example for SAM.
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
 *  \mainpage usart_iso7816 USART ISO7816 Example
 *
 *  \par Purpose
 *  This example sends ISO7816 commands to a smartcard connected to the
 *  evaluation kits on SAM.
 *
 *  \par Requirements
 *  This example can be used on SAM evaluation kit. Please connect the
 *  smartcard contacts with following pins which could be easily wired from
 *  the board. 
 *  SAM3N-EK, SAM3U-EK, SAM3X-EK and SAM4N-Xplained-Pro use USART0 TXD0 and SCK0, 
 *  SAM3S-EK, SAM3S-EK2, SAM4S-EK and SAM4E-EK use USART1 TXD1 and SCK1.
 *  SAM4C-EK uses USART2 TXD2 and SCK2.
 *  - <b>SAM-EK -- SMARTCARD</b>
 *   - PA15     --    RST
 *   - TXD*     --    I/O
 *   - SCK*     --    CLK
 *   - VCC      --    VCC
 *   - GND      --    GND
 *
 *  \par Description
 *  The iso7816 software provide in this examples is use to transform APDU
 *  commands to TPDU commands for the smart card.
 *  The iso7816 provide here is for the protocol T=0 only.
 *  The send and the receive of a character is made under polling.
 *  User must change these pins according to his environment.
 * 
 *  The driver is compliant with CASE 1, 2, 3 of the ISO7816-4 specification.
 *
 *  \par Usage
 *  -# Build the program and download it inside the evaluation board.
 *  -# On the computer, open and configure a terminal application (e.g.
 *     HyperTerminal on Microsoft Windows) with these settings:
 *        - 115200 bauds
 *        - 8 data bits
 *        - No parity
 *        - 1 stop bit
 *        - No flow control
 *  -# Connect the card reader to SAM EK board as described before:
 *  -# Start the application. The following traces shall appear on the terminal:
 *     \code
	-- USART ISO7816 Example --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"

/** Maximum uc_size in bytes of the smartcard answer to a uc_command. */
#define MAX_ANSWER_SIZE         10

/** Maximum ATR uc_size in bytes. */
#define MAX_ATR_SIZE            55

/** Define the baudrate of ISO7816 mode. */
#define ISO7816_BAUDRATE        9600

/** Define the FI_DI_RATIO filed value. */
#define ISO7816_FI_DI           372

/** Test command #1. */
const uint8_t test_cmd1[] = {0x00, 0x10, 0x00, 0x00};
/** Test command #2. */
const uint8_t test_cmd2[] = {0x00, 0x20, 0x00, 0x00, 0x02};
/** Test command #3. */
const uint8_t test_cmd3[] = {0x00, 0x30, 0x00, 0x00, 0x02, 0x0A, 0x0B};

#define STRING_EOL    "\r"
#define STRING_HEADER "-- USART ISO7816 Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

const usart_iso7816_opt_t conf_iso7816_t = {
	ISO7816_BAUDRATE * ISO7816_FI_DI, /* ISO7816 clock. */
	ISO7816_FI_DI,                    /* Number of clock per bit period. */
	US_MR_PAR_EVEN,                   /* The parity check mode. */
	0,                                /* Inhibit Non Acknowledge. */
	0,                                /* Disable Successive NCKs. */
	3,                                /* Number of repetitions. */
	0,                                /* Bit order. */
	0                                 /* Protocol type T = 0. */
};

/**
 * \brief Displays a menu which enables the user to send several commands to the
 * smartcard and check its answers.
 */
static void send_receive_cmd(void)
{
	uint8_t uc_message[MAX_ANSWER_SIZE];
	uint8_t uc_size;
	uint8_t uc_key;
	uint8_t uc_command;
	uint8_t i;

	/* Clear message buffer. */
	for (i = 0; i < sizeof(uc_message); i++) {
		uc_message[i] = 0;
	}

	/* Display menu. */
	puts("-I- The following three commands can be sent:\r\n");
	puts("  1. ");
	for (i=0; i < sizeof(test_cmd1); i++) {
		printf("0x%02X ", test_cmd1[i]);
	}
	puts("\r\n  2. ");
	
	for (i=0; i < sizeof(test_cmd2); i++) {
		printf("0x%02X ", test_cmd2[i]);
	}
	puts("\r\n  3. ");

	for (i=0; i < sizeof(test_cmd3); i++) {
		printf("0x%02X ", test_cmd3[i]);
	}
	
	/* Get user input. */
	uc_key = 0;
	while (uc_key != 'q') {
		puts("\r\nChoice ? (q to quit): ");
		while (uart_read(CONSOLE_UART, &uc_key)) {
		}
		printf("%c\r\n", uc_key);
		uc_command = uc_key - '0';

		/* Check user input. */
		uc_size = 0;
		if (uc_command == 1) {
			puts("-I- Sending test command #1 : ");
			for (i = 0; i < sizeof(test_cmd1); i++) {
				printf("0x%02X ", test_cmd1[i]);
			}
			puts("...");
			uc_size = iso7816_xfr_block_tpdu_t0(test_cmd1, uc_message,
						sizeof(test_cmd1));
		} else {
			if (uc_command == 2) {
				puts("-I- Sending test command #2 : ");
				for (i = 0; i < sizeof(test_cmd2); i++) {
					printf("0x%02X ", test_cmd2[i]);
				}
				puts("...");
				uc_size = iso7816_xfr_block_tpdu_t0(test_cmd2, uc_message,
							sizeof(test_cmd2));
			} else {
				if (uc_command == 3) {
					puts("-I- Sending test command #3 : ");
					for (i = 0; i < sizeof(test_cmd3); i++) {
						printf("0x%02X ", test_cmd3[i]);
					}
					puts("...");
					uc_size = iso7816_xfr_block_tpdu_t0(test_cmd3, uc_message,
								sizeof(test_cmd3));
				}
			}
	   }

		/* Output smartcard answer. */
		if (uc_size > 0) {
			puts("Answer: ");
			for (i=0; i < uc_size; i++) {
				printf("0x%02X ", uc_message[i]);
			}
		}
	}

	puts("Quitting ...\r\n");
}

/**
 * \brief Configure UART for debug message output.
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
 * \brief  Initializes the DBGU and ISO7816 driver, and starts some tests.
 *
 * \return Unused (ANSI-C compatibility)
 */
int main(void)
{
	uint8_t p_atr[MAX_ATR_SIZE];
	uint8_t uc_size;
	uint8_t i;

	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	/* Configure UART for debug message output. */
	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);

	/* Initialize Atr buffer. */
	for (i = 0; i < sizeof(p_atr); i++) {
		p_atr[i] = 0;
	}

	/* Configure IT on Smart Card. */
	puts("-I- Smartcard detection not supported.\r\n");

	/* Enable peripheral clock. */
	sysclk_enable_peripheral_clock(ISO7816_USART_ID);

	/* Configure ISO7816 driver. */
	iso7816_init(&conf_iso7816_t, sysclk_get_peripheral_hz(), PIN_ISO7816_RST_IDX);

	/* Read ATR. */
	iso7816_warm_reset();

	iso7816_data_block_atr(p_atr, &uc_size);

	/* Decode ATR. */
	iso7816_decode_atr(p_atr);

	/* Allow user to send some commands. */
	send_receive_cmd();

	while (1) {
	}
}
