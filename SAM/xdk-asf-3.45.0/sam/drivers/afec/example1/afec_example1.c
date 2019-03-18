/**
 * \file
 *
 * \brief AFEC temperature sensor example for SAM.
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
 * \mainpage AFEC Temperature Sensor Example
 *
 * \section Purpose
 *
 * The example demonstrates how to use the temperature sensor
 * feature inside the microcontroller.
 *
 * \section Requirements
 *
 * This example can be used on SAM4E-EK boards , SAMV71-Xplained-Ultra ,
 * SAME70-Xplained.
 *
 * \section Description
 *
 * The example is aimed to demonstrate the temperature sensor feature
 * inside the device. To use this feature, the temperature sensor should be automatically
 * turned on by RTC event. The channel 15 is connected to the sensor by default.
 * If set RTCT = 1, TRGEN is disabled and all channels are disabled (AFE_CHSR = 0),
 * then only channel 15 is converted at a rate of 1 conversion per second.
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
	-- AFEC Temperature Sensor xxx --
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
#include <string.h>
#include <assert.h>
#include "asf.h"

/** Reference voltage for AFEC,in mv. */
#define VOLT_REF        (3300)

/** The maximal digital value */
#define MAX_DIGITAL     (4095UL)

#define STRING_EOL    "\r"
#define STRING_HEADER "-- AFEC Temperature Sensor Example --\r\n" \
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
 * \brief AFEC interrupt callback function.
 */
static void afec_temp_sensor_end_conversion(void)
{
	g_ul_value = afec_channel_get_value(AFEC0, AFEC_TEMPERATURE_SENSOR);
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

	afec_enable(AFEC0);

	struct afec_config afec_cfg;

	afec_get_config_defaults(&afec_cfg);

	afec_init(AFEC0, &afec_cfg);

	afec_set_trigger(AFEC0, AFEC_TRIG_SW);

	struct afec_ch_config afec_ch_cfg;
	afec_ch_get_config_defaults(&afec_ch_cfg);
#if (SAMV71 || SAMV70 || SAME70 || SAMS70)
	afec_ch_cfg.gain = AFEC_GAINVALUE_0;
#endif
	afec_ch_set_config(AFEC0, AFEC_TEMPERATURE_SENSOR, &afec_ch_cfg);

#if (SAMV71 || SAMV70 || SAME70 || SAMS70)
	/*
	 * Because the internal ADC offset is 0x200, it should cancel it and shift
	 * down to 0.
	 */
	afec_channel_set_analog_offset(AFEC0, AFEC_TEMPERATURE_SENSOR, 0x200);
#else
	/*
	 * Because the internal ADC offset is 0x800, it should cancel it and shift
	 * down to 0.
	 */
	afec_channel_set_analog_offset(AFEC0, AFEC_TEMPERATURE_SENSOR, 0x800);
#endif

	struct afec_temp_sensor_config afec_temp_sensor_cfg;

	afec_temp_sensor_get_config_defaults(&afec_temp_sensor_cfg);
	afec_temp_sensor_cfg.rctc = true;
	afec_temp_sensor_set_config(AFEC0, &afec_temp_sensor_cfg);

#if (SAMV71 || SAMV70 || SAME70 || SAMS70)
	afec_set_callback(AFEC0, AFEC_INTERRUPT_EOC_11,
			afec_temp_sensor_end_conversion, 1);

#else
	afec_set_callback(AFEC0, AFEC_INTERRUPT_EOC_15,
			afec_temp_sensor_end_conversion, 1);
#endif

	while (1) {

		if(is_conversion_done == true) {

			ul_vol = g_ul_value * VOLT_REF / MAX_DIGITAL;

#if (SAMV71 || SAMV70 || SAME70 || SAMS70)
			/*
			 * According to datasheet, The output voltage VT = 0.72V at 27C
			 * and the temperature slope dVT/dT = 2.33 mV/C
			 */
			ul_temp = (ul_vol - 720)  * 100 / 233 + 27;
#else
			/*
			 * According to datasheet, The output voltage VT = 1.44V at 27C
			 * and the temperature slope dVT/dT = 4.7 mV/C
			 */
			ul_temp = (ul_vol - 1440)  * 100 / 470 + 27;
#endif

			printf("Temperature is: %4d\r", (int)ul_temp);
			is_conversion_done = false;
		}
	}
}
