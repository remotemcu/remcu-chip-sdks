/**
 * \file
 *
 * \brief ADC Enhanced Mode example for SAM.
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
 * \mainpage ADC Enhanced Resolution Example
 *
 * \section Purpose
 *
 * The example demonstrates how to use the enhanced resolution mode
 * inside the microcontroller to sample analog voltage.
 *
 * \section Requirements
 *
 * This example can be used on SAM4C-EK boards.
 *
 * \section Description
 *
 * The example is aimed to demonstrate the enhanced resolution mode
 * inside the microcontroller. To use this feature, the ADC channel connected to
 * the potentiometer should be enabled. Users can select different resolution
 * modes by configuration menu in the terminal.
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
	-- ADC Enhanced Resolution Examplexxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
	=========================================================
	Menu: press a key to change the resolution mode.
	---------------------------------------------------------
	-- n: Normal Resolution Mode--
	-- e: Enhanced Resolution Mode--
	-- q: Quit Configuration--
\endcode
 * -# The application will output the raw ADC result and the current voltage of
 * potentiometer on the terminal.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "asf.h"

/* Tracking Time*/
#define TRACKING_TIME         1
/* Transfer Period */
#define TRANSFER_PERIOD       1
/* ADC channel for potentiometer */
#define ADC_CHANNEL_POTENTIOMETER  ADC_CHANNEL_1

/** Reference voltage for ADC in mv. */
#define VOLT_REF        (3300)

/** The maximal digital value */
#define MAX_DIGITAL_10_BIT     (1024UL)

#define STRING_EOL    "\r"
#define STRING_HEADER "-- ADC Enhanced Mode Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

#define MENU_HEADER "\n\r-- press a key to change the resolution mode--\n\r" \
		"-- n: Normal Resolution Mode--\n\r" \
		"-- e: Enhanced Resolution Mode--\n\r" \
		"-- q: Quit Configuration--\n\r"

/** ADC sample data */
struct {
	uint32_t value;
	bool is_done;
} g_adc_sample_data;

/** The maximal digital value */
static uint32_t g_max_digital;

/**
 * \brief Configure UART console.
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
 * \brief Set ADC resolution mode.
 */
static void set_adc_resolution(void)
{
	uint8_t uc_key;
	uint8_t uc_done = 0;

	puts(MENU_HEADER);

	while (!uc_done) {
		while (uart_read(CONF_UART, &uc_key));

		switch (uc_key) {
		case 'n':
		case 'N':
			g_max_digital = MAX_DIGITAL_10_BIT;
			adc_set_resolution(ADC, ADC_10_BITS);
			puts(" Set Resolution to Normal \n\r");
			break;
		case 'e':
		case 'E':
			g_max_digital = MAX_DIGITAL_10_BIT * 4;
			adc_set_resolution(ADC, ADC_12_BITS);
			puts(" Set Resolution to Enhanced \n\r");
			break;
		case 'q':
		case 'Q':
			uc_done = 1;
			puts(" Quit Configuration \n\r");
			break;
		default:
			break;
		}
	}
}

/**
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t uc_key;

	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);

	g_adc_sample_data.value = 0;
	g_adc_sample_data.is_done = false;
	g_max_digital = MAX_DIGITAL_10_BIT;

	/* Enable peripheral clock. */
	sysclk_enable_peripheral_clock(ID_ADC);

	/* Initialize ADC. */
	adc_init(ADC, sysclk_get_cpu_hz(), 6400000, ADC_STARTUP_TIME_8);
	adc_configure_timing(ADC, TRACKING_TIME);
	adc_check(ADC, sysclk_get_cpu_hz());

	/* Software Trigger. */
	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);
	/* Enable channel for potentiometer. */
	adc_enable_channel(ADC, ADC_CHANNEL_POTENTIOMETER);
	adc_set_averaging_trigger(ADC, false);

	/* Enable ADC interrupt. */
    adc_enable_interrupt(ADC, ADC_IER_DRDY);
	NVIC_EnableIRQ(ADC_IRQn);

	while (1) {
		adc_start(ADC);
		delay_ms(1000);

		/* Check if ADC sample is done. */
		if (g_adc_sample_data.is_done == true) {
			printf("Potentiometer Voltage: %4d mv.\r\n",
					(int)(g_adc_sample_data.value * VOLT_REF
					/ g_max_digital));
			printf("Raw ADC result: 0x%04x\r\n\r\n", (unsigned int)g_adc_sample_data.value);
			g_adc_sample_data.is_done = false;
		}

		/* Check if the user enters a key. */
		if (!uart_read(CONF_UART, &uc_key)) {
			/* Disable all ADC interrupt. */
			adc_disable_interrupt(ADC, ADC_IER_DRDY);
			set_adc_resolution();
			adc_enable_interrupt(ADC, ADC_IER_DRDY);
		}
	}
}

void ADC_Handler(void)
{
	if (adc_get_status(ADC) & ADC_ISR_DRDY) {
		g_adc_sample_data.value = adc_get_latest_value(ADC);
		g_adc_sample_data.is_done = true;
	}
}
