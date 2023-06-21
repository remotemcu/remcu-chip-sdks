/**
 * \file
 *
 * \brief SAM Peripheral Event Controller (PEVC) example 1.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <conf_example.h>
#include <events_example1.h>

uint8_t event_string[] = "AST event triggered PDCA!";

/**
 * \brief PDCA transfer interrupt callback.
 */
static void pdca_tranfer_done(
		enum pdca_channel_status status)
{
	/* Get PDCA channel status and check if PDCA transfer is completed */
	if (status == PDCA_CH_TRANSFER_COMPLETED) {
		/* Reload PDCA data transfer */
		pdca_channel_write_reload(PEVC_ID_USER_PDCA_0, (void *)event_string,
				sizeof( event_string));
		printf("\r\n");
	}
}

/**
 * \brief Initialize the AST as event generator.
 */
static void init_ast(void)
{
	struct ast_config ast_conf;

	/* Enable osc32 oscillator */
	if (!osc_is_ready(OSC_ID_OSC32)) {
		osc_enable(OSC_ID_OSC32);
		osc_wait_ready(OSC_ID_OSC32);
	}

	/* Enable the AST */
	ast_enable(AST);

	/* Configure the AST with counter mode and set counter to 0 */
	ast_conf.mode = AST_COUNTER_MODE;
	ast_conf.osc_type = AST_OSC_32KHZ;
	ast_conf.psel = AST_PSEL_32KHZ_1HZ;
	ast_conf.counter = 0;

	if (!ast_set_config(AST, &ast_conf)) {
		printf("Error initializing the AST\r\n");
		while (1) {
		}
	}

	/* Enable period event of AST */
	ast_write_periodic0_value(AST, AST_PSEL_32KHZ_1HZ);
	ast_enable_event(AST, AST_EVENT_PER);
}

/**
 * \brief Initialize the PEVC for the example.
 */
//! [quick_start_init_events_function]
static void init_events(void)
{
	struct events_conf    events_config;
	struct events_ch_conf ch_config;

	/* Initialize event module */
	events_get_config_defaults(&events_config);
	events_init(&events_config);
	events_enable();

	/*
	 * Configure an event channel
	 * - AST periodic event 0 --- Generator
	 * - PDCA channel 0       --- User
	 */
	events_ch_get_config_defaults(&ch_config);
	ch_config.channel_id = PEVC_ID_USER_PDCA_0;
	ch_config.generator_id = PEVC_ID_GEN_AST_2;
	ch_config.shaper_enable = true;
	ch_config.igf_edge = EVENT_IGF_EDGE_NONE;
	events_ch_configure(&ch_config);

	/* Enable the channel */
	events_ch_enable(PEVC_ID_USER_PDCA_0);
}
//! [quick_start_init_events_function]

/**
 * \brief Initialize the PDCA transfer for the example.
 */
static void init_pdca(void)
{
	/* PDCA channel options */
	static const pdca_channel_config_t pdca_tx_configs = {
		.addr = (void *)event_string,
		.pid = CONF_PDCA_PID_USART_TX,
		.size = sizeof(event_string),
		.r_addr = 0,
		.r_size = 0,
		.ring = false,
		.etrig = true,
		.transfer_size = PDCA_MR_SIZE_BYTE
	};

	/* Enable PDCA module */
	pdca_enable(PDCA);

	/* Init PDCA channel with the pdca_options.*/
	pdca_channel_set_config(PEVC_ID_USER_PDCA_0, &pdca_tx_configs);

	/* Set callback for PDCA channel */
	pdca_channel_set_callback(PEVC_ID_USER_PDCA_0, pdca_tranfer_done,
			PDCA_0_IRQn, 1, PDCA_IER_TRC | PDCA_IER_TERR);

	/* Enable PDCA channel */
	pdca_channel_enable(PEVC_ID_USER_PDCA_0);
}

/**
 *  \brief Configure serial console.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
#ifdef CONF_UART_CHAR_LENGTH
		.charlength = CONF_UART_CHAR_LENGTH,
#endif /* CONF_UART_CHAR_LENGTH */
		.paritytype = CONF_UART_PARITY,
#ifdef CONF_UART_STOP_BITS
		.stopbits = CONF_UART_STOP_BITS,
#endif /* CONF_UART_STOP_BITS */
	};

	/* Configure console. */
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief Main entry point for event example.
 */
int main(void)
{
	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	/* Initialize the console uart */
	configure_console();

	/* Output example information */
	printf("\r\n\r\n-- Events example 1 --\r\n");
	printf("-- %s\r\n", BOARD_NAME);
	printf("-- Compiled: %s %s --\r\n", __DATE__, __TIME__);

	//! [quick_start_init_all_basic_use]
	/* Initialize AST as event generator. */
	//! [quick_start_init_ast_basic_use]
	init_ast();
	//! [quick_start_init_ast_basic_use]

	/* Initialise events for this example. */
	//! [quick_start_init_events_basic_use]
	init_events();
	//! [quick_start_init_events_basic_use]

	/* Initialize the PDCA as event user */
	//! [quick_start_init_pdca_basic_use]
	init_pdca();
	//! [quick_start_init_pdca_basic_use]
	//! [quick_start_init_all_basic_use]

	while (1) {
		/* Toggle LED0 every 500 ms */
		LED_Toggle(LED0);
		delay_ms(500);
	}
}
