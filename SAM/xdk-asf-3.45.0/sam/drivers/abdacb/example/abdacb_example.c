/**
 * \file
 *
 * \brief Audio Bitstream DAC Example for SAM4L.
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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
 * \mainpage Audio Bitstream DAC Example
 *
 * \section Purpose
 *
 * The example demonstrates how to use ABDAC driver to
 * transfers an input buffer of audio samples to an output .
 *
 * \section Requirements
 *
 * This example can be used on SAM4L-EK boards with hardware rework. Please
 * see detail in document: ATSAM4L-EK User Guide.
 *
 * \section Description
 *
 * The example read the audio samples and output it.
 *
 * \section Usage
 *
 * - Build the program and download it to the evaluation board. Please
 *  refer to the SAM4L main page documentation 
 *  http://www.microchip.com/developmenttools/productdetails/partno/atsam4l-ek
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
	-- ABDAC Example xxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 * -# the sent text should appear.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include "sound.h"

#define PDCA_ABDAC_CHANNEL0  0
#define PDCA_ABDAC_CHANNEL1  1

#define SOUND_SAMPLES 0x100
int16_t samples_left[SOUND_SAMPLES];
int16_t samples_right[SOUND_SAMPLES];

volatile bool exit_flag = false;

/* PDCA channel options */
static const pdca_channel_config_t pdca_abdac_config0 = {
	.addr = 0,   /* memory address */
	.pid = ABDACB_PDCA_ID_TX_CH0,     /* select peripheral */
	.size = 0,   /* transfer counter */
	.r_addr = 0,                   /* next memory address */
	.r_size = 0,                   /* next transfer counter */
	.ring = false,                 /* disable ring buffer mode */
	.transfer_size = PDCA_MR_SIZE_HALF_WORD /* select size of the transfer */
};
static const pdca_channel_config_t pdca_abdac_config1 = {
	.addr = 0,   /* memory address */
	.pid = ABDACB_PDCA_ID_TX_CH1,     /* select peripheral */
	.size = 0,   /* transfer counter */
	.r_addr = 0,                   /* next memory address */
	.r_size = 0,                   /* next transfer counter */
	.ring = false,                 /* disable ring buffer mode */
	.transfer_size = PDCA_MR_SIZE_HALF_WORD /* select size of the transfer */
};

/** ABDAC instance */
struct abdac_dev_inst g_abdac_inst;

/** ABDAC configuration */
struct abdac_config   g_abdac_cfg;

/**
 * \brief EIC interrupt handler for push button interrupt
 */
static void eic_5_callback(void)
{
	if (eic_line_interrupt_is_pending(EIC, GPIO_PUSH_BUTTON_EIC_LINE)) {
		exit_flag = true;
		eic_line_clear_interrupt(EIC, GPIO_PUSH_BUTTON_EIC_LINE);
	}
}

static void config_buttons(void)
{
	/* Initialize EIC for button wakeup. */
	struct eic_line_config eic_line_conf = {
		EIC_MODE_EDGE_TRIGGERED,
		EIC_EDGE_FALLING_EDGE,
		EIC_LEVEL_LOW_LEVEL,
		EIC_FILTER_DISABLED,
		EIC_ASYNCH_MODE
	};
	eic_enable(EIC);
	eic_line_set_config(EIC, GPIO_PUSH_BUTTON_EIC_LINE, 
		&eic_line_conf);
	eic_line_set_callback(EIC, GPIO_PUSH_BUTTON_EIC_LINE, eic_5_callback,
		EIC_5_IRQn, 1);
	eic_line_enable(EIC, GPIO_PUSH_BUTTON_EIC_LINE);
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
 * \brief Display the user menu on the terminal.
 */
static void display_menu(void)
{
	printf("Menu :\r\n"
			"  -- Select the action:\r\n"
			"  s: Start output the audio with PDCA. \r\n"
			"  h: Display menu \r\n\r\n");
}

/**
 * \brief Application entry point for ABDAC example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t key;
	uint32_t i, count;
	status_code_t status;

	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	/* Initialize the UART console. */
	configure_console();

	/* Output example information */
	printf("-- ABDAC Example --\r\n");
	printf("-- %s\r\n", BOARD_NAME);
	printf("-- Compiled: %s %s --\r\n", __DATE__, __TIME__);

	/* Config the push button. */
	config_buttons();

	/* Config the ABDAC. */
	abdac_get_config_defaults(&g_abdac_cfg);
	g_abdac_cfg.sample_rate_hz = ABDAC_SAMPLE_RATE_11025;
	g_abdac_cfg.data_word_format = ABDAC_DATE_16BIT;
	g_abdac_cfg.mono = false;
	g_abdac_cfg.cmoc = false;
	status = abdac_init(&g_abdac_inst, ABDACB, &g_abdac_cfg);
	if (status != STATUS_OK) {
		printf("-- Initialization fails! --\r\n");
		while (1) {
		}
	}
	abdac_enable(&g_abdac_inst);
	abdac_clear_interrupt_flag(&g_abdac_inst, ABDAC_INTERRUPT_TXRDY);
	abdac_clear_interrupt_flag(&g_abdac_inst, ABDAC_INTERRUPT_TXUR);

	/* Config PDCA module */
	pdca_enable(PDCA);
	pdca_channel_set_config(PDCA_ABDAC_CHANNEL0, &pdca_abdac_config0);
	pdca_channel_enable(PDCA_ABDAC_CHANNEL0);
	pdca_channel_set_config(PDCA_ABDAC_CHANNEL1, &pdca_abdac_config1);
	pdca_channel_enable(PDCA_ABDAC_CHANNEL1);

	/* Display menu. */
	display_menu();

	while (1) {
		scanf("%c", (char *)&key);

		switch (key) {
		case 'h':
			display_menu();
			break;

		case 's':
			printf("--Looped output audio, use push button to exit--\r\n");
			abdac_set_volume0(&g_abdac_inst, false, 0x7FFF);
			abdac_set_volume1(&g_abdac_inst, false, 0x7FFF);
			i = 0;
			/* output sample from the sound_table array */
			while(!exit_flag) {
				count = 0;
				// Store sample from the sound_table array
				while(count < (SOUND_SAMPLES)){
					samples_left[count] = ((uint8_t)sound_table[i]) << 8;
					samples_right[count] = ((uint8_t)sound_table[i]) << 8;
					i++;
					count++;
					if (i >= sizeof(sound_table)) i = 0;
				}

				pdca_channel_write_reload(PDCA_ABDAC_CHANNEL0,
						(void *)samples_left, SOUND_SAMPLES);
				pdca_channel_write_reload(PDCA_ABDAC_CHANNEL1,
						(void *)samples_right, SOUND_SAMPLES);
				/**
				 * Wait until the reload register is empty. This means that
				 * one transmission is still ongoing but we are already able
				 * to set up the next transmission.
				 */
				while(!(pdca_get_channel_status(PDCA_ABDAC_CHANNEL1)
					== PDCA_CH_COUNTER_RELOAD_IS_ZERO));
			}
			exit_flag = false;
			printf("--Exit the audio output--\r\n\r\n");
			/* Mute the volume */
			abdac_set_volume0(&g_abdac_inst, true, 0x7FFF);
			abdac_set_volume1(&g_abdac_inst, true, 0x7FFF);
			break;

		default:
			break;
		}
	}
}
