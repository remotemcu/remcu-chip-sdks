/**
 * \file
 *
 * \brief Smart Card Driver Quick Start
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

/**
 * \mainpage Smart Card Example
 * See \ref appdoc_sam0_smart_card_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 * \page appdoc_preface Overview
 * In this use case we will communicate with smart card (AT88SC1616C) via ISO7816, reset the
 * smart card, send the couple of commands to the smart card through user choice 
 * via EDBG VCP and receive the appropriate response from the smart card.
 *
 * The iso7816 software provide in this examples is use to transform APDU
 * commands to TPDU commands for the smart card. The iso7816 provided here
 * is for the protocol T=0 only. The sending and reception of a character
 * is made under polling. User must change these pins according to his
 * environment.
 */

 /**
 * \page appdoc_sam0_smart_card_main Smart Card Example
 * Overview:
 * - \ref appdoc_sam0_smart_card_intro
 * - \ref appdoc_sam0_smart_card_setup
 * - \ref appdoc_sam0_smart_card_compinfo
 * - \ref appdoc_sam0_smart_card_contactinfo
 *
 * \section  appdoc_sam0_smart_card_intro Introduction
 * In this use case we will communicate with smart card (AT88SC1616C) via ISO7816, reset the
 * smart card, send the couple of commands to the smart card through user choice 
 * via EDBG VCP and receive the appropriate response from the smart card.
 *
 * The iso7816 software provide in this examples is use to transform APDU
 * commands to TPDU commands for the smart card. The iso7816 provided here
 * is for the protocol T=0 only. The sending and reception of a character
 * is made under polling. User must change these pins according to his
 * environment.
 *
 *
 * This application has been tested on following boards:
 * - SAM L22 Xplained Pro
 * - Smart Card Xplained Pro Extension
 * - Smart card used is, Atmel CryptoMemory (AT88SC1616C -in ISO Module form) 
 *
 * \section appdoc_sam0_smart_card_setup Hardware Setup
 * The Smart Card Xplained Pro extension board must be connected to extension
 * header 3 (EXT3) on the SAM L22 Xplained Pro.
 *
 * To run the test:
 *  - Connect the Debug USB port of Xplained Pro board to the computer using a
 *    micro USB cable.
 *  - Open the virtual COM port in a terminal application.
 *  - Terminal session settings are: 
 *    Baud rate: 115200 
 *    Data bits: 8 
 *	  Parity: None 
 *    Stop bits: 1 
 *    Flow Control: None 
 *    
 *    \note The USB composite firmware running on the Embedded Debugger (EDBG)
 *          will enumerate as debugger, virtual COM port and EDBG data
 *          gateway.
 *  - Build the project, program the target board and run the application.
 *    The terminal shows the Information about Demo and User input options.
 *
 * \section appdoc_sam0_smart_card_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_smart_card_contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com">http://www.microchip.com</a>.
 */
 
#include <asf.h>
#include <string.h>
#include "conf_iso7816.h"

static struct usart_module cdc_uart_module, usart_instance;

#define STRING_EOL      "\r"
#define STRING_HEADER   "--Smart Card(ISO7816) Quick Start Example --\r\n" \
"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/* Maximum uc_size in bytes of the smart card answer to a uc_command. */
#define MAX_ANSWER_SIZE         10

/* Maximum ATR uc_size in bytes. */
#define MAX_ATR_SIZE            55

#define CMD1_LEN                7
#define CMD2_LEN                5

/* Test command #1 - Write to memory Test Zone {CLA, INS, Add, Add, No of bytes, Data}*/
const uint8_t test_cmd1[CMD1_LEN] = {0x00, 0xB4, 0x00, 0x0A, 0x02, 0x25, 0x22};

/* Test command #2 - Read from Memory Test Zone {CLA, INS, Add, Add, No of bytes}*/
const uint8_t test_cmd2[CMD2_LEN] = {0x00, 0xB6, 0x00, 0x0A, 0x02};


/**
 * \brief Initialize the USART for EDBG Virtual COM Port
 */
static void console_init(void)
{
	struct usart_config usart_conf;

	/* Configure USART for output */
	usart_get_config_defaults(&usart_conf);
	usart_conf.mux_setting = CONF_STDIO_MUX_SETTING;
	usart_conf.pinmux_pad0 = CONF_STDIO_PINMUX_PAD0;
	usart_conf.pinmux_pad1 = CONF_STDIO_PINMUX_PAD1;
	usart_conf.pinmux_pad2 = CONF_STDIO_PINMUX_PAD2;
	usart_conf.pinmux_pad3 = CONF_STDIO_PINMUX_PAD3;
	usart_conf.baudrate    = CONF_STDIO_BAUDRATE;

	stdio_serial_init(&cdc_uart_module, CONF_STDIO_USART, &usart_conf);
	usart_enable(&cdc_uart_module);
}

/**
 * \brief Detect smart card.
 */
static void smart_card_detect(void)
{
	struct port_config pin_conf;

	port_get_config_defaults(&pin_conf);

	/* Config smart card detect */
	pin_conf.direction = PORT_PIN_DIR_INPUT;
	port_pin_set_config(CONF_ISO7816_PIN_DET, &pin_conf);

	if(port_pin_get_input_level(CONF_ISO7816_PIN_DET) == false) {
		printf("-Message:- Please insert Smart card. \r\n");
	}
	while (port_pin_get_input_level(CONF_ISO7816_PIN_DET) == false) {
		/* Wait insert smart card */
	}

	printf("Smart card is detected.\r\n");
}

/**
 * \brief Initialize the SERCOM USART (ISO7816 mode) for smart card.
 */
static void smart_card_init(void)
{
	struct port_config pin_conf;

	port_get_config_defaults(&pin_conf);
	pin_conf.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(CONF_ISO7816_PIN_RST, &pin_conf);
	port_pin_set_output_level(CONF_ISO7816_PIN_RST, false);

	/* Config smart card vcc enable */
	port_pin_set_config(CONF_ISO7816_PIN_VCC, &pin_conf);
	port_pin_set_output_level(CONF_ISO7816_PIN_VCC, true);

	struct usart_config usart_conf;

	/* Configure USART for output */
	usart_get_config_defaults(&usart_conf);
	usart_conf.mux_setting            = CONF_ISO7816_MUX_SETTING;
	usart_conf.pinmux_pad0            = CONF_ISO7816_PINMUX_PAD0;
	usart_conf.pinmux_pad1            = CONF_ISO7816_PINMUX_PAD1;
	usart_conf.pinmux_pad2            = CONF_ISO7816_PINMUX_PAD2;
	usart_conf.pinmux_pad3            = CONF_ISO7816_PINMUX_PAD3;
	usart_conf.baudrate               = CONF_ISO7816_BAUDRATE;
	usart_conf.iso7816_config.enabled    = true;
	usart_conf.iso7816_config.guard_time = ISO7816_GUARD_TIME_2_BIT;

	usart_init(&usart_instance, CONF_ISO7816_USART, &usart_conf);

	iso7816_init(&usart_instance, CONF_ISO7816_PIN_RST, \
				system_gclk_chan_get_hz(usart_conf.generator_source));

	/* Config pinmux as smart card clock */
	struct system_pinmux_config pin_clk_conf;
	system_pinmux_get_config_defaults(&pin_clk_conf);
	pin_clk_conf.direction = PORT_PIN_DIR_OUTPUT;
	pin_clk_conf.input_pull = SYSTEM_PINMUX_PIN_PULL_NONE;
	pin_clk_conf.mux_position = PINMUX_PA15H_GCLK_IO1 & 0xFFFF;
	system_pinmux_pin_set_config(PINMUX_PA15H_GCLK_IO1 >> 16, &pin_clk_conf);

	usart_enable(&usart_instance);
}

/**
 * \brief Displays a menu which enables the user to send several commands to the
 * smart card and check its answers.
 */
static void send_receive_cmd(void)
{
	uint8_t uc_message[MAX_ANSWER_SIZE];
	uint8_t  uc_size;
	uint16_t uc_key;
	uint8_t  uc_command;
	uint8_t  i;

	/* Clear message buffer. */
	for (i = 0; i < MAX_ANSWER_SIZE; i++) {
		uc_message[i] = 0;
	}

	/* Display menu. */
	puts("The following three User Inputs can be sent:\r\n");
	puts("  1 - To Execute Write command");
	for (i=0; i < CMD1_LEN; i++) {
		printf("0x%02X ", test_cmd1[i]);
	}
	puts("\r\n  2- To Execute Read Command");

	for (i=0; i < CMD2_LEN; i++) {
		printf("0x%02X ", test_cmd2[i]);
	}
    puts("\r\n  q - To Quit the Application. "); 
	/* Get user input. */
	uc_key = 0;
	while (uc_key != 'q') {
		puts("\r\nChoice ? ('1' or '2' or 'q'): ");
		while (usart_read_wait(&cdc_uart_module, &uc_key)) {
		}
		printf("%c\r\n", uc_key);
		uc_command = (uint8_t)uc_key - '0';

		/* Check user input. */
		uc_size = 0;
		if (uc_command == 1) {
			puts("Sending test command #1 (Writing 2 bytes in Memory Test Zone) :\r\n ");
			for (i = 0; i < CMD1_LEN; i++) {
				printf("0x%02X ", test_cmd1[i]);
			}
			puts("...");
			uc_size = iso7816_xfr_block_tpdu_t0(test_cmd1, uc_message, CMD1_LEN);
		} else {
			if (uc_command == 2) {
				puts("Sending test command #2 (Reading 2 bytes from Memory Test Zone):\r\n ");
				for (i = 0; i < CMD2_LEN; i++) {
					printf("0x%02X ", test_cmd2[i]);
				}
				puts("...");
				uc_size = iso7816_xfr_block_tpdu_t0(test_cmd2, uc_message, CMD2_LEN);
			} 
	   }

		/* Output smart card answer. */
		if (uc_size > 0) {
			puts("Answer: ");
			for (i=0; i < uc_size; i++) {
				printf("0x%02X ", uc_message[i]);
			}
		}
	}
	puts("Please wait.... \r\n");
	port_pin_set_output_level(CONF_ISO7816_PIN_VCC, false);
	puts("The smart card can now be safely removed. \r\n");
}
int main (void)
{
	
	uint8_t p_atr[MAX_ATR_SIZE];
	uint8_t  uc_size;
	uint16_t i;
	
	/* Init system. */
	system_init();
	
	/* EDBG UART Console Initilaization. */
	console_init();
	
	/* Display example information. */
	printf("%s \r\n", STRING_HEADER);
	
	/* Smart card detect and display the status. */
	smart_card_detect();
	
	/* Smart card Initialization. */
	smart_card_init();

	/* Smart card warm reset. */
	iso7816_warm_reset();
	
	memset(p_atr, 0, sizeof(p_atr));
	iso7816_data_block_atr(p_atr, &uc_size);

	if (uc_size != 0) {
		puts("Reset response from Smart Card: ");
		for(i = 0; i < uc_size; i++) {
			printf("0x%02X ", p_atr[i]);
		}
		puts("\r\n");
	}

	/* User inputs commands to send / receive / quit. */
	send_receive_cmd();
	
	while (1) {

	}
}
