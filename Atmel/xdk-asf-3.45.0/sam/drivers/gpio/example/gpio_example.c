/**
 * \file
 *
 * \brief GPIO interrupt example.
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
 * \mainpage
 * \section intro Introduction
 * This example shows how to configure GPIO module to trigger an interrupt
 * and an event.
 *
 * The push button 0 is configured to trigger a GPIO interrupt when it is
 * pressed. In the interrupt handler, the LED0 will be toggled every time.
 *
 * The \ref EXAMPLE_PIN_EVENT is configured to trigger a GPIO event when
 * detecting a falling edge. Each time a new event is coming, it will trigger
 * the PDCA to send a character to the USART without CPU usage.
 *
 * \section files Main Files
 * - gpio.c: GPIO driver implementation
 * - gpio.h: GPIO driver header file
 * - gpio_example.c: GPIO example application
 *
 * \section compilinfo Compilation Information
 * This software is written for GNU GCC and IAR Embedded Workbench&reg;
 * for Atmel&reg;. Other compilers may or may not work.
 *
 * \section deviceinfo Device Information
 * SAM4L device can be used.
 *
 * \section configinfo Configuration Information
 * This example has been tested with the following configuration:
 * - SAM4L evaluation kit
 * - SAM4L Xplained Pro
 * - SAM4L8 Xplained Pro
 * - PC terminal settings:
 *   - 115200 bps
 *   - 8 data bits
 *   - no parity bit
 *   - 1 stop bit
 *   - no flow control
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com">Microchip</A>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include "asf.h"
#include "conf_example.h"

/**
 * Configure serial console.
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

	/* Configure console. */
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * Initialize the PEVC for the example.
 */
static void init_pevc(void)
{
	/* Set input glitch filter divider to 0x0A (2^10) */
	struct events_conf config;
	events_get_config_defaults(&config);
	events_init(&config);

	/*
	 * Setup and enable PEVC channel:
	 * - Generator: PAD_EVT 1
	 * - User: PDCA - channel 0 transfer one word
	 * - Enable falling edge detection for EVS
	 */
	struct events_ch_conf ch_config;
	events_ch_get_config_defaults(&ch_config);
	ch_config.channel_id = PEVC_ID_USER_PDCA_0;
	ch_config.generator_id = PEVC_ID_GEN_PAD_1;
	ch_config.shaper_enable = true;
	ch_config.igf_edge = EVENT_IGF_EDGE_FALLING;
	events_ch_configure(&ch_config);
	events_ch_enable(PEVC_ID_USER_PDCA_0);
}

uint8_t event_string[] = "gpio event triggered!";

/**
 * PDCA transfer interrupt callback.
 */
static void pdca_tranfer_done(enum pdca_channel_status status)
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
 * Initialize the PDCA transfer for the example.
 */
static void init_pdca(void)
{
	/* PDCA channel options */
	static const pdca_channel_config_t pdca_tx_configs = {
		.addr = (void *)event_string,
		.pid = PDCA_PID_USART_TX,
		.size = sizeof(event_string),
		.r_addr = 0,
		.r_size = 0,
		.ring = false,
		.etrig = true,
		.transfer_size = PDCA_MR_SIZE_BYTE
	};

	/* Enable PDCA module clock */
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
 * Push button 0 interrupt callback.
 */
//!	[example_pb0_callback]
static void pb0_callback(void)
{
	/* Handle pin interrupt here e.g. toggle an LED */
	LED_Toggle(LED0);
}
//!	[example_pb0_callback]

/**
 * \brief Main entry point for GPIO example.
 */
int main(void)
{
	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	/* Initialize the console uart */
	configure_console();

	/* Output example information */
	printf("\r\n\r\n-- GPIO interrupt and event example --\r\n");
	printf("-- %s\r\n", BOARD_NAME);
	printf("-- Compiled: %s %s --\r\n", __DATE__, __TIME__);

//!	[config_button_0_trig_fall]
	/* Configure push button 0 to trigger an interrupt on falling edge */
//!	[config_button_0_trig_fall_1]
	ioport_set_pin_dir(EXAMPLE_BUTTON_INT, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(EXAMPLE_BUTTON_INT, IOPORT_MODE_PULLUP |
			IOPORT_MODE_GLITCH_FILTER);
	ioport_set_pin_sense_mode(EXAMPLE_BUTTON_INT, IOPORT_SENSE_FALLING);
//!	[config_button_0_trig_fall_1]
//!	[config_button_0_trig_fall_2]
	if (!gpio_set_pin_callback(EXAMPLE_BUTTON_INT, pb0_callback, 1)) {
		printf("Set pin callback failure!\r\n");
		while (1) {
		}
	}
//!	[config_button_0_trig_fall_2]
//!	[enable_pin_interrupt]
	gpio_enable_pin_interrupt(EXAMPLE_BUTTON_INT);
//!	[enable_pin_interrupt]
//! [config_button_0_trig_fall]
	printf("Press %s to trigger LED.\r\n", BUTTON_0_NAME);

	/* Configure pin to trigger an event on falling edge */
	ioport_set_pin_mode(EXAMPLE_PIN_EVENT, IOPORT_MODE_PULLUP |
			IOPORT_MODE_MUX_C);
	ioport_disable_pin(EXAMPLE_PIN_EVENT);
	ioport_set_pin_sense_mode(EXAMPLE_PIN_EVENT, IOPORT_SENSE_FALLING);
	gpio_enable_pin_periph_event(EXAMPLE_PIN_EVENT);
	printf("Connect %s to %s to trigger an event.\r\n", EXAMPLE_PIN_NAME,
			EXAMPLE_GND_NAME);

	init_pevc();
	init_pdca();

	while (1) {
	}
}
