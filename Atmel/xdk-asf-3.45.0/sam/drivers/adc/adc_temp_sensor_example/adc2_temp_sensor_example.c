/**
 * \file
 *
 * \brief ADC temperature sensor example for SAM4N.
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
 * \mainpage ADC Temperature Sensor Example
 *
 * \section Purpose
 *
 * The example demonstrates how to use the temperature sensor
 * feature inside the microcontroller.
 *
 * \section Requirements
 *
 * This example can be used on SAM4N-Xplained-Pro boards.
 *
 * \section Description
 *
 * The example is aimed to demonstrate the temperature sensor feature
 * inside the device. 
 *
 * The temperature sensor provides an output voltage (VT) that is proportional
 * to absolute temperature (PTAT). The relationship between measured voltage and
 * actual temperature could be found in Electrical Characteristics part of the
 * datasheet.
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
	-- ADC Temperature Sensor Example xxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 * -# The application will output current Celsius temperature on the terminal.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <stdio.h>
#include <assert.h>
#include "asf.h"

/** Reference voltage for ADC,in mv. */
#define VOLT_REF        (3300)

/** The maximal digital value */
#define MAX_DIGITAL     (1023UL)

#define STRING_EOL    "\r"
#define STRING_HEADER "\n-- ADC Temperature Sensor Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/** The conversion data is done flag */
volatile bool is_conversion_done = false;

/** The conversion data value */
volatile uint32_t g_ul_value = 0;

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
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief ADC interrupt callback function.
 */
static void adc_temp_sensor_end_conversion(void)
{
	g_ul_value = adc_channel_get_value(ADC, ADC_TEMPERATURE_SENSOR);
	is_conversion_done = true;
}

/**
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	int32_t ul_vol;
	int32_t ul_temp;

	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);

	adc_enable();

	struct adc_config adc_cfg;

	adc_get_config_defaults(&adc_cfg);

	adc_init(ADC, &adc_cfg);
	adc_channel_enable(ADC,ADC_TEMPERATURE_SENSOR);

	adc_set_trigger(ADC, ADC_TRIG_SW);

	struct adc_temp_sensor_config adc_temp_sensor_cfg;

	adc_temp_sensor_get_config_defaults(&adc_temp_sensor_cfg);
	
	adc_temp_sensor_set_config(ADC, &adc_temp_sensor_cfg);

	adc_set_callback(ADC, ADC_INTERRUPT_EOC_16,
			adc_temp_sensor_end_conversion, 1);

	adc_start_software_conversion(ADC);

	while (1) {
		if (is_conversion_done == true) {
			is_conversion_done = false;
			ul_vol = g_ul_value * VOLT_REF / MAX_DIGITAL;
			/*
			* According to datasheet, The output voltage VT = 1.44V at 27C
			* and the temperature slope dVT/dT = 4.7 mV/C
			*/
			ul_temp = (ul_vol - 1440)  * 100 / 470 + 27;

			printf("-- Temperature is: %4d\r\n", (int)ul_temp);
			delay_ms(1000);
			adc_start_software_conversion(ADC);
		}
	}
}
