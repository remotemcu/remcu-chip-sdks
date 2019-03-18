/**
 * \file
 *
 * \brief ADC threshold wakeup example for SAM.
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
 * \mainpage ADC Threshold Wakeup Example
 *
 * \section Purpose
 *
 * The adc_threshold_wakeup example demonstrates how to use ADC with
 * threshold wakeup.
 *
 * \section Requirements
 *
 * This example can be used on any SAM3/4 boards.
 *
 * ADVREF must be set to 3300 mv in order to enable full scale measurement
 * of the potentiometer. Please refer to the board schematics for ADVREF
 * jumper configuration.
 *
 * \section Description
 * This example uses TIOA0 as external trigger instead of software trigger for
 * ADC conversion. The TIOA0 is a 1ms period square wave. The rising edge
 * during each period would trigger the ADC to start a conversion on the given
 * channel which is connected to the potentiometer. This example shows a menu as
 * below upon running:
 * \code
	-- Menu Choices for this example--
	-- 0: Display voltage on potentiometer.--
	 -- 1: Modify low threshold.--
	 -- 2: Modify high threshold.--
	 -- 3: Choose comparison mode.--
	-- i: Display ADC information.--
	-- m: Display this main menu.--
	-- c: Set Auto Calibration Mode. --
	-- s: Enter sleep mode.--
\endcode
 * With the user interface, comparison window and mode could be set. The ADC
 * supports 4 kinds of comparison events as follows:
 *
 * - Lower than the low threshold.
 * - Higher than the high threshold.
 * - In the comparison window.
 * - Out of the comparison window.
 *
 * If the target gets an 'S' or 's' from user's input, the core falls into
 * sleep mode thanks to the __WFI. Turning the potentiometer to enable the ADC input fall into the
 * comparison window will trigger an event. This comparison event
 * will wake the system up.
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
	-- ADC Threshold Wakeup Example xxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
	-- Menu Choices for this example--
	-- 0: Display voltage on potentiometer.--
	 -- 1: Modify low threshold.--
	 -- 2: Modify high threshold.--
	 -- 3: Choose comparison mode.--
	-- i: Display ADC information.--
	-- m: Display this main menu.--
	-- c: Set Auto Calibration Mode. --
	-- s: Enter sleep mode.--
\endcode
 * -# Input the command according to the menu.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "stdio_serial.h"
#include "conf_board.h"

/** ADC channel for potentiometer */
#if SAM3S || SAM3N || SAM4S
#define ADC_CHANNEL_POTENTIOMETER  ADC_CHANNEL_5
#elif SAM3XA || SAM4C
#define ADC_CHANNEL_POTENTIOMETER  ADC_CHANNEL_1
#endif
/** ADC clock */
#define BOARD_ADC_FREQ (6000000)

/** Reference voltage for ADC, in mv.*/
#define VOLT_REF   (3300)

/** The maximal digital value*/
#if SAM3S || SAM3XA || SAM4S
/** The maximal digital value */
#define MAX_DIGITAL     (4095)
#elif SAM3N || SAM4C
#define MAX_DIGITAL     (1023)
#endif

#if SAM3S || SAM4S || SAM3XA || SAM3N || SAM4C
/* Tracking Time*/
#define TRACKING_TIME    1
/* Transfer Period */
#define TRANSFER_PERIOD  1
/* Startup Time*/
#if SAM4C
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
#define SAMPLE_HOLD_TIME   6
#endif

#define STRING_EOL    "\r"
#define STRING_HEADER "-- ADC Threshold Wakeup Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL
#define MENU_HEADER "\n\r-- Menu Choices for this example--\n\r" \
		"-- 0: Display voltage on potentiometer.--\n\r" \
		"-- 1: Modify low threshold.--\n\r" \
		"-- 2: Modify high threshold.--\n\r" \
		"-- 3: Choose comparison mode.--\n\r" \
		"-- i: Display ADC information.--\n\r" \
		"-- m: Display this main menu.--\n\r" \
		"-- s: Enter sleep mode.--\n\r"

/** Low threshold */
static uint16_t gs_us_low_threshold = 0;
/** High threshold */
static uint16_t gs_us_high_threshold = 0;

void ADC_Handler(void)
{
	uint32_t ul_mode;
	uint16_t us_adc;

	/* Disable Compare Interrupt. */
	adc_disable_interrupt(ADC, ADC_IDR_COMPE);

	if ((adc_get_status(ADC) & ADC_ISR_COMPE) == ADC_ISR_COMPE) {
		ul_mode = adc_get_comparison_mode(ADC);
		us_adc = adc_get_channel_value(ADC, ADC_CHANNEL_POTENTIOMETER);

		switch (ul_mode) {
		case 0:
			printf("-ISR-:Potentiometer voltage %d mv is below the low "
				"threshold:%d mv!\n\r", us_adc * VOLT_REF / MAX_DIGITAL,
				gs_us_low_threshold * VOLT_REF / MAX_DIGITAL);
			break;

		case 1:
			printf("-ISR-:Potentiometer voltage %d mv is above the high "
				"threshold:%d mv!\n\r", us_adc * VOLT_REF / MAX_DIGITAL,
				gs_us_high_threshold * VOLT_REF / MAX_DIGITAL);
			break;

		case 2:
			printf("-ISR-:Potentiometer voltage %d mv is in the comparison "
				"window:%d-%d mv!\n\r", us_adc * VOLT_REF / MAX_DIGITAL,
				gs_us_low_threshold * VOLT_REF / MAX_DIGITAL,
				gs_us_high_threshold * VOLT_REF / MAX_DIGITAL);
			break;

		case 3:
			printf("-ISR-:Potentiometer voltage %d mv is out of the comparison"
				" window:%d-%d mv!\n\r", us_adc * VOLT_REF / MAX_DIGITAL,
				gs_us_low_threshold * VOLT_REF / MAX_DIGITAL,
				gs_us_high_threshold * VOLT_REF / MAX_DIGITAL);
			break;
		}
	}
}

/**
 * \brief Configure Timer Counter 0 (TC0) to generate an interrupt every
 * second. This interrupt will be used to display the number of bytes
 * received on the UART.
 */
static void configure_tc0(void)
{
	/* Enable TC0 peripheral clock. */
	pmc_enable_periph_clk(ID_TC0);

	/* Configure TC for a 1s (= 1Hz) tick. */
	tc_init(TC0, 0, 0x4 | TC_CMR_ACPC_SET | TC_CMR_WAVE
			| TC_CMR_ACPA_CLEAR | (0x2 << 13));

	/* 50% duty, 1s frequency */
	TC0->TC_CHANNEL[0].TC_RA = 16384;
	TC0->TC_CHANNEL[0].TC_RC = 32768;
}

/**
 * \brief Display main menu.
 */
static void display_menu(void)
{
	puts(MENU_HEADER);
}

/**
 *  \brief Transform float data type to int.
 */
static uint32_t  f_to_int(float x)
{
	uint32_t j = (uint32_t)x;
	float k = (float)j;
	if(k == x) {
		return j;
	} else {
		return j+1;
	}
}

/** Display current information,including
 * voltage on potentiometer, thresholds and comparison mode.
 */
static void display_info(void)
{
	uint32_t ul_adc_value = adc_get_channel_value(ADC,
			ADC_CHANNEL_POTENTIOMETER);
	float f_low_threshold = (float)gs_us_low_threshold *
			VOLT_REF / MAX_DIGITAL;
	float f_high_threshold = (float)gs_us_high_threshold *
			VOLT_REF / MAX_DIGITAL;
	uint32_t ul_low_threshold = f_to_int(f_low_threshold);
	uint32_t ul_high_threshold = f_to_int(f_high_threshold);

	printf("-I- Thresholds: %u mv - %u mv.\n\r", (unsigned int)ul_low_threshold,
			(unsigned int)ul_high_threshold);
	printf("-I- Voltage on potentiometer: %u mv.\n\r",
			(unsigned int)(ul_adc_value * VOLT_REF / MAX_DIGITAL));
	printf("-I- Comparison mode is %u\n\r.",
			(unsigned int)(ADC->ADC_EMR & ADC_EMR_CMPMODE_Msk));
}

/**
 * \brief Enter sleep mode using WFI instruction.
 * Enable interrupt first and then disable it after wake up.
 */
static void enter_asleep(void)
{
	while (1) {
		puts("Now switching the device into sleep mode...\r");

		/* Clear status register. */
		adc_get_status(ADC);

		/* Enable Compare Interrupt. */
		adc_enable_interrupt(ADC, ADC_IER_COMPE);

		__WFI();

		/* Every time waked up, break out of the loop. */
		break;
	}
}

/**
 * Get comparison mode.
 */
static uint8_t get_comparison_mode(void)
{
	uint8_t uc_mode = adc_get_comparison_mode(ADC);
	uint8_t uc_char;

	while (1) {
		while (uart_read(CONSOLE_UART, &uc_char));
		switch (uc_char) {
		case 'a':
		case 'A':
			uc_mode = 0x0;
			break;
		case 'b':
		case 'B':
			uc_mode = 0x1;
			break;
		case 'c':
		case 'C':
			uc_mode = 0x2;
			break;
		case 'd':
		case 'D':
			uc_mode = 0x3;
			break;
		case 'q':
		case 'Q':
			break;
		default:
			continue;
		}
		return uc_mode;
	}
}

/**
 * \brief Get voltage from user input (range from 0 to 3300 mv).
 */
static int16_t get_voltage(void)
{
	uint8_t c_counter = 0;
	uint8_t c_char = 0;
	int16_t s_value = 0;
	int8_t c_length = 0;
	int8_t c_str_temp[5] = { 0 };

	while (1) {
		while (uart_read(CONSOLE_UART, &c_char));

		if (c_char == '\n' || c_char == '\r') {
			puts("\r");
			break;
		}

		if ('0' <= c_char && '9' >= c_char) {
			printf("%c", c_char);
			c_str_temp[c_counter++] = c_char;
#if defined (  __GNUC__  )
			fflush(stdout);
#endif

			if (c_counter >= 4) {
				break;
			}
		}
	}

	c_str_temp[c_counter] = '\0';
	/* Input string length. */
	c_length = c_counter;
	s_value = 0;

	/* Convert string to integer. */
	for (c_counter = 0; c_counter < 4; c_counter++) {
		if (c_str_temp[c_counter] != '0') {
			switch (c_length - c_counter - 1) {
			case 0:
				s_value += (c_str_temp[c_counter] - '0');
				break;

			case 1:
				s_value += (c_str_temp[c_counter] - '0') * 10;
				break;

			case 2:
				s_value += (c_str_temp[c_counter] - '0') * 100;
				break;

			case 3:
				s_value += (c_str_temp[c_counter] - '0') * 1000;
				break;
			}
		}
	}

	if (s_value > VOLT_REF) {
		puts("\n\r-F- Too big threshold!\r");
		return -1;
	}

	return s_value;
}

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
 * \brief Example entry point.
 *
 * Initialize ADC to 12-bit, enable channel "ADC_CHANNEL_POTENTIOMETER", then
 * enable hardware trigger with TIOA0 every second. Finally, start conversion.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t c_choice;
	int16_t s_adc_value;
	int16_t s_threshold = 0;

	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);

	/* Initialize threshold. */
	gs_us_low_threshold = 0x0;
	gs_us_high_threshold = MAX_DIGITAL;

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
#if SAM3S ||  SAM3XA || SAM4S
	adc_configure_timing(ADC, TRACKING_TIME, ADC_SETTLING_TIME_3,
			TRANSFER_PERIOD);
#elif SAM3N || SAM4C
	adc_configure_timing(ADC, TRACKING_TIME);
#endif
	adc_check(ADC, sysclk_get_cpu_hz());

	/* Hardware trigger TIOA0. */
	adc_configure_trigger(ADC, ADC_TRIG_TIO_CH_0, 0);
	/* Enable channels for x,y and z. */
	adc_enable_channel(ADC, ADC_CHANNEL_POTENTIOMETER);

	/* Configure TC. */
	configure_tc0();

	/* Channel 5 has to be compared. */
	adc_set_comparison_channel(ADC, ADC_CHANNEL_POTENTIOMETER);
	/* Compare mode, in the window. */
	adc_set_comparison_mode(ADC, ADC_EMR_CMPMODE_IN);

	/* Set up Threshold. */
	adc_set_comparison_window(ADC, gs_us_low_threshold, gs_us_high_threshold);

	/* Enable ADC interrupt. */
	NVIC_EnableIRQ(ADC_IRQn);

	/* Start TC0 and hardware trigger. */
	tc_start(TC0, 0);

	/* Display main menu. */
	display_menu();

	while (1) {
		while (uart_read(CONSOLE_UART, &c_choice)) {
		}
		printf("%c\r\n", c_choice);

		switch (c_choice) {
		case '0':
			s_adc_value = adc_get_channel_value(ADC,
					ADC_CHANNEL_POTENTIOMETER);
			printf("-I- Current voltage is %d mv, %d%% of ADVREF\n\r",
					(s_adc_value * VOLT_REF / MAX_DIGITAL),
					(s_adc_value * 100 / MAX_DIGITAL));
			break;

		case '1':
			puts("Low threshold is set to(mv):");
			s_threshold = get_voltage();
			puts("\r");

			if (s_threshold >= 0) {
				s_adc_value = s_threshold * MAX_DIGITAL /
						VOLT_REF;
				adc_set_comparison_window(ADC, s_adc_value,
						gs_us_high_threshold);
				/* Renew low threshold. */
				gs_us_low_threshold = s_adc_value;
				float f_low_threshold = (float)gs_us_low_threshold *
						VOLT_REF / MAX_DIGITAL;
				uint32_t ul_low_threshold = f_to_int(f_low_threshold);
				printf("Setting low threshold to %u mv (reg value to 0x%x ~%d%%)\n\r",
						(unsigned int)ul_low_threshold,
						gs_us_low_threshold,
						gs_us_low_threshold * 100 / MAX_DIGITAL);
			}
			break;

		case '2':
			puts("High threshold is set to(mv):");
			s_threshold = get_voltage();
			puts("\r");

			if (s_threshold >= 0) {
				s_adc_value = s_threshold * MAX_DIGITAL /
						VOLT_REF;
				adc_set_comparison_window(ADC, gs_us_low_threshold,
						s_adc_value);
				/* Renew high threshold. */
				gs_us_high_threshold = s_adc_value;
				float f_high_threshold = (float)gs_us_high_threshold *
						VOLT_REF / MAX_DIGITAL;
				uint32_t ul_high_threshold = f_to_int(f_high_threshold);
				printf("Setting high threshold to %u mv (reg value to 0x%x ~%d%%)\n\r",
						(unsigned int)ul_high_threshold,
						gs_us_high_threshold,
						gs_us_high_threshold * 100 / MAX_DIGITAL);
			}
			break;
		case '3':
			puts("-a. Below low threshold.\n\r"
					"-b. Above high threshold.\n\r"
					"-c. In the comparison window.\n\r"
					"-d. Out of the comparison window.\n\r"
					"-q. Quit the setting.\r");
			c_choice = get_comparison_mode();
			adc_set_comparison_mode(ADC, c_choice);
			printf("Comparison mode is %c.\n\r", 'a' + c_choice);
			break;

		case 'm':
		case 'M':
			display_menu();
			break;

		case 'i':
		case 'I':
			display_info();
			break;

		case 's':
		case 'S':
			enter_asleep();
			break;
		}
		puts("Press \'m\' or \'M\' to display the main menu again!\r");
	}
}
