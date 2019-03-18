/**
 * \file
 *
 * \brief AFEC automatic comparison example for SAM.
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
 * \mainpage AFEC Automatic Comparison Example
 *
 * \section Purpose
 *
 * The example demonstrates how to use the automatic comparison feature
 * inside the microcontroller to compare analog voltage.
 *
 * \section Requirements
 *
 * This example can be used on SAM4E-EK boards,SAMV71-Xplained-Ultra,
 * SAME70-Xplained-Pro.
 *
 * \section Description
 *
 * The example is aimed to demonstrate the automatic comparison feature
 * inside the microcontroller. To use this feature, the channel 5 which is
 * connected to the potentiometer should be enabled. Users can change the
 * potentiometer voltage to compare with threshold value.The terminal will
 * output current potentiometer voltage and configured window value.
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
 * -# In the terminal window, the
 *    following text should appear (values depend on the board and the chip used):
 *    \code
	-- AFEC Automatic Comparison Examplexxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 * -# The application will output comparison result on the terminal.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "asf.h"

/** Reference voltage for AFEC in mv. */
#define VOLT_REF        (3300)

/** The maximal digital value */
#define MAX_DIGITAL     (4095UL)

#define STRING_EOL    "\r"
#define STRING_HEADER "-- AFEC Automatic Comparison Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/** Low threshold */
static uint16_t gs_us_low_threshold = 0;
/** High threshold */
static uint16_t gs_us_high_threshold = 0;

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
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief Callback function for AFEC enter compasion window interrupt.
 */
static void afec_print_comp_result(void)
{
	uint16_t us_adc;

	/* Disable Compare Interrupt. */
	afec_disable_interrupt(AFEC0, AFEC_INTERRUPT_COMP_ERROR);

	us_adc = afec_channel_get_value(AFEC0, AFEC_CHANNEL_POTENTIOMETER);

	printf("-ISR-:Potentiometer voltage %d mv is in the comparison "
			"window:%d -%d mv!\n\r",
			(int)(us_adc * VOLT_REF / MAX_DIGITAL),
			(int)(gs_us_low_threshold * VOLT_REF / MAX_DIGITAL),
			(int)(gs_us_high_threshold * VOLT_REF / MAX_DIGITAL));
}

/**
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);

	gs_us_low_threshold = 0x0;
	gs_us_high_threshold = 0x7FF;

	afec_enable(AFEC0);

	struct afec_config afec_cfg;

	afec_get_config_defaults(&afec_cfg);
	afec_init(AFEC0, &afec_cfg);

	struct afec_ch_config afec_ch_cfg;
	afec_ch_get_config_defaults(&afec_ch_cfg);

#if (SAMV71 || SAMV70 || SAME70 || SAMS70)
	/*
	 * Because the internal AFEC offset is 0x200, it should cancel it and shift
	 * down to 0.
	 */
	afec_channel_set_analog_offset(AFEC0, AFEC_CHANNEL_POTENTIOMETER, 0x200);

	afec_ch_cfg.gain = AFEC_GAINVALUE_0;

#else
	/*
	 * Because the internal AFEC offset is 0x800, it should cancel it and shift
	 * down to 0.
	 */
	afec_channel_set_analog_offset(AFEC0, AFEC_CHANNEL_POTENTIOMETER, 0x800);
#endif

	afec_ch_set_config(AFEC0, AFEC_CHANNEL_POTENTIOMETER, &afec_ch_cfg);
	afec_set_trigger(AFEC0, AFEC_TRIG_SW);

	afec_set_comparison_mode(AFEC0, AFEC_CMP_MODE_2, AFEC_CHANNEL_POTENTIOMETER, 0);
	afec_set_comparison_window(AFEC0, gs_us_low_threshold, gs_us_high_threshold);

	/* Enable channel for potentiometer. */
	afec_channel_enable(AFEC0, AFEC_CHANNEL_POTENTIOMETER);

	afec_set_callback(AFEC0, AFEC_INTERRUPT_COMP_ERROR, afec_print_comp_result, 1);

	while (1) {
		afec_start_software_conversion(AFEC0);
		delay_ms(1000);
	}
}
