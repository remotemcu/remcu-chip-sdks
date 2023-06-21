/**
 * \file
 *
 * \brief ADC temperature sensor example for SAM.
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
 * \mainpage ADC Temperature Sensor Example
 *
 * \section Purpose
 *
 * The adc_temp_sensor example demonstrates how to use the temperature sensor
 * feature inside the microcontroller.
 *
 * \section Requirements
 *
 * This example can be used on any SAM3/4 boards.
 *
 * Temperature sensor output range is from 0 to 3300 mv, hence ADVREF must be
 * set to 3300 mv in order to provide reliable temperature information. Please
 * refer to the board schematics for ADVREF jumper configuration.
 *
 * \note For SAM4CMP-DB and SAM4CMS-DB (Rev B), the ADVREF is not connected to
 * 3300mv by default, so need to solder DNP component to get this example
 * work correctly.
 *
 * \section Description
 *
 * The adc_temp_sensor is aimed to demonstrate the temperature sensor feature
 * inside the device. To use this feature, the temperature sensor should be
 * turned on by setting TSON bit in ADC_ACR. The channel 15 is connected to the
 * sensor by default. With PDC support, the Interrupt Handler of ADC is designed
 * to handle RXBUFF interrupt.
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
	-- ADC Temperature Sensor xxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 * -# The application will output current Celsius temperature on the terminal, and
 *    users can set temperature offset by a menu.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "asf.h"
#include "conf_board.h"

/** Size of the receive buffer and transmit buffer. */
#define BUFFER_SIZE     (100)

/** Reference voltage for ADC,in mv. */
#define VOLT_REF        (3300)

#if SAM3S || SAM4S || SAM3XA || SAM3N || SAM4C || SAM4CM
/* Tracking Time*/
#define TRACKING_TIME    1
/* Transfer Period */
#define TRANSFER_PERIOD  1
/* Startup Time*/
#if SAM4C || SAM4CM
#define STARTUP_TIME ADC_STARTUP_TIME_10
#else
#define STARTUP_TIME ADC_STARTUP_TIME_4
#endif
#endif

#if SAM3U
#ifdef ADC_12B
/* Start Up Time */
#define STARTUP_TIME               7
/* Off Mode Startup Time */
#define OFF_MODE_STARTUP_TIME      7
#else
#define STARTUP_TIME               3
#endif
/* Sample & Hold Time */
#define SAMPLE_HOLD_TIME           6
#endif

/** The maximal digital value */
#if SAM3S || SAM3XA || SAM4S
/** The maximal digital value */
#define MAX_DIGITAL     (4095)
#elif SAM3N || SAM4C || SAM4CM
#define MAX_DIGITAL     (1023)
#elif SAM3U
#ifdef ADC_12B
#define MAX_DIGITAL     (4095)
#else
#define MAX_DIGITAL     (1023)
#endif
#endif

#define STRING_EOL    "\r"
#define STRING_HEADER "-- ADC Temperature Sensor Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/** adc buffer */
static int16_t gs_s_adc_values[BUFFER_SIZE] = { 0 };

/**
 * \brief Simple function to replace printf with float formatting.
 * One decimal with rounding support.
 */
static void print_temp(float temp)
{
	int16_t s_integer1 = 0;
	int32_t l_integer2 = 0;

	Assert(INT16_MAX > (temp * 100.0) && INT16_MIN < (temp * 100.0));

	/* Cast to integer */
	s_integer1 = (int16_t) (temp * 100.0);

	/* Rounding */
	l_integer2 = s_integer1 / 10;
	if ((s_integer1 - l_integer2 * 10) > 4) {
		s_integer1 = l_integer2 + 1;
	} else {
		if ((s_integer1 - l_integer2 * 10) < -4) {
			s_integer1 = l_integer2 - 1;
		} else {
			s_integer1 = l_integer2;
		}
	}

	/* Quotient */
	l_integer2 = s_integer1 / 10;
	/* Remainder */
	s_integer1 = s_integer1 - l_integer2 * 10;

	if (s_integer1 < 0) {
		printf("Temp:-%d.%d \n\r", (int16_t) ((l_integer2) * (-1)),
				(int16_t) ((s_integer1) * (-1)));
	} else {
		printf("Temp:%d.%d \n\r", (int16_t) l_integer2,
				(int16_t) s_integer1);
	}
}

/**
 * \brief Read converted data through PDC channel.
 *
 * \param pADC The pointer of adc peripheral.
 * \param pwBuffer The destination buffer.
 * \param dwSize The size of the buffer.
 */
static uint32_t adc_read_buffer(Adc * pADC, int16_t * pwBuffer, uint32_t dwSize)
{
	/* Check if the first PDC bank is free. */
	if ((pADC->ADC_RCR == 0) && (pADC->ADC_RNCR == 0)) {
		pADC->ADC_RPR = (uint32_t) pwBuffer;
		pADC->ADC_RCR = dwSize;
		pADC->ADC_PTCR = ADC_PTCR_RXTEN;

		return 1;
	} else {	/* Check if the second PDC bank is free. */
		if (pADC->ADC_RNCR == 0) {
			pADC->ADC_RNPR = (uint32_t) pwBuffer;
			pADC->ADC_RNCR = dwSize;

			return 1;
		} else {
			return 0;
		}
	}
}

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
 * \brief Systick handler, start new conversion.
 */
void SysTick_Handler(void)
{
	if (adc_get_status(ADC) & (1 << ADC_TEMPERATURE_SENSOR)) {
		adc_start(ADC);
	}
}

/**
 * \brief ADC interrupt handler.
 */
void ADC_Handler(void)
{
	uint32_t ul_counter;
	int32_t l_vol;
	float f_temp;
	uint32_t ul_value = 0;
	uint32_t ul_temp_value = 0;

	if ((adc_get_status(ADC) & ADC_ISR_RXBUFF) == ADC_ISR_RXBUFF) {

		/* Multisample */
		for (ul_counter = 0; ul_counter < BUFFER_SIZE; ul_counter++) {
			ul_value += gs_s_adc_values[ul_counter];
		}
		/* Averaging */
		ul_temp_value = ul_value / 10;
		ul_value = ul_value / 100;
		ul_temp_value -= (ul_value * 10);
		/* Round for last decimal */
		if (ul_temp_value > 4) {
			ul_value++;
		}

		l_vol = ul_value * VOLT_REF / MAX_DIGITAL;
#if SAM3S || SAM3XA
		/* Using multiplication (*0.37736) instead of division (/2.65). */
		f_temp = (float)(l_vol - 800) * 0.37736 + 27.0;
#elif SAM4N
		/* Using multiplication (*0.21186) instead of division (/4.72). */
		f_temp = (float)(l_vol - 1440) * 0.21186 + 27.0;
#else
		/* Using multiplication (*0.21276) instead of division (/4.7). */
		f_temp = (float)(l_vol - 1440) * 0.21276 + 27.0;
#endif
		print_temp(f_temp);
		/* Clear the buffer. */
		memset(gs_s_adc_values, 0x0, sizeof(gs_s_adc_values));
		/* Start new pdc transfer. */
		adc_read_buffer(ADC, gs_s_adc_values, BUFFER_SIZE);

	}
}

/**
 * \brief adc_temp_sensor Application entry point.
 *
 * Initialize adc to 12-bit, enable channel 15,turn on
 * temp sensor, pdc channel interrupt for temp sensor
 * and start conversion.
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

	/* 10 ms timer */
	if (SysTick_Config(sysclk_get_cpu_hz() / 100)) {
		puts("-F- Systick configuration error\r");
		while (1) {
		}
	}
	/* Enable peripheral clock. */
	pmc_enable_periph_clk(ID_ADC);
	/* Initialize ADC. */
	/*
	 * Formula: ADCClock = MCK / ( (PRESCAL+1) * 2 )
	 * For example, MCK = 64MHZ, PRESCAL = 4, then:
	 * ADCClock = 64 / ((4+1) * 2) = 6.4MHz;
	 */
	/* Formula:
	 *     Startup  Time = startup value / ADCClock
	 *     Startup time = 64 / 6.4MHz = 10 us
	 */
	adc_init(ADC, sysclk_get_cpu_hz(), 6400000, STARTUP_TIME);
	/* Formula:
	 *     Transfer Time = (TRANSFER * 2 + 3) / ADCClock
	 *     Tracking Time = (TRACKTIM + 1) / ADCClock
	 *     Settling Time = settling value / ADCClock
	 *
	 *     Transfer Time = (1 * 2 + 3) / 6.4MHz = 781 ns
	 *     Tracking Time = (1 + 1) / 6.4MHz = 312 ns
	 *     Settling Time = 3 / 6.4MHz = 469 ns
	 */
	adc_configure_timing(ADC, TRACKING_TIME
#if !SAM4C && !SAM4CM
			, ADC_SETTLING_TIME_3, TRANSFER_PERIOD
#endif
	);

	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);

	adc_check(ADC, sysclk_get_cpu_hz());

	/* Enable channel for potentiometer. */
	adc_enable_channel(ADC, ADC_TEMPERATURE_SENSOR);

	/* Enable the temperature sensor. */
	adc_enable_ts(ADC);

	/* Enable ADC interrupt. */
	NVIC_EnableIRQ(ADC_IRQn);

	/* Start conversion. */
	adc_start(ADC);

	adc_read_buffer(ADC, gs_s_adc_values, BUFFER_SIZE);

	/* Enable PDC channel interrupt. */
	adc_enable_interrupt(ADC, ADC_ISR_RXBUFF);

	while (1) {
	}
}
