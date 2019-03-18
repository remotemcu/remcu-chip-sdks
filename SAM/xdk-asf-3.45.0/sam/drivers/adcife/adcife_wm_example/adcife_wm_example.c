/**
 * \file
 *
 * \brief ADCIFE Window Monitor example for SAM4L.
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
 * \mainpage ADCIFE Window Monitor Example
 *
 * \section Purpose
 *
 * The adcife_window_monitor example demonstrates how to use window monitor mode.
 *
 * \section Requirements
 *
 * This example can be used on SAM4L boards.
 *
 * \section Description
 *
 * This example uses continuous mode for ADCIFE conversion. It would trigger the ADCIFE
 * to start a conversion on the given channel which is DAC internal selection.
 * This example shows a menu as below upon running:
 *
 * \code
	-- Menu Choices for this example--
	 -- 0: Modify DAC output voltage.--
	 -- 1: Modify low threshold.--
	 -- 2: Modify high threshold.--
	 -- 3: Choose comparison mode.--
	 -- i: Display ADCIFE information.--
	 -- m: Display this main menu.--
\endcode
 *
 * With the user interface, DAC output voltage, window threshold and mode could be set.
 * After setting, it will start a conversion and enable window monitor interrupt.
 * If conversion result fall into comparison window, then it will generate relative
 * interrupt and display information in terminal.
 *
 * \section Usage
 *
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
	-- ADCIFE Window Monitor Example xxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
	-- Menu Choices for this example--
	-- 0: Modify DAC output voltage.--
	-- 1: Modify low threshold.--
	-- 2: Modify high threshold.--
	-- 3: Choose comparison mode.--
	-- i: Display ADCIFE information.--
	-- m: Display this main menu.--
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

#define VDDANA             3300

/* Reference voltage in mv */
#define VOLT_REF   1000

/** The maximal digital value*/
#define MAX_DIGITAL     (4095)

#define STRING_EOL    "\r"
#define STRING_HEADER "-- ADCIFE Window Monitor Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL
#define MENU_HEADER "\n\r-- Menu Choices for this example--\n\r" \
		"-- 0: Modify DAC output value--\n\r" \
		"-- 1: Modify low threshold.--\n\r" \
		"-- 2: Modify high threshold.--\n\r" \
		"-- 3: Choose comparison mode.--\n\r" \
		"-- i: Display ADCIFE information.--\n\r" \
		"-- m: Display this main menu.--\n\r"

/** Low threshold */
static uint16_t gs_us_low_threshold = 0;
/** High threshold */
static uint16_t gs_us_high_threshold = 0;

/** ADC instance */
struct adc_dev_inst g_adc_inst;

/**
 * \brief Callback function for ADCIFE interrupt.
 */
static void adcife_wm_handler(void)
{
	uint32_t ul_mode;
	uint16_t us_adc;

	/* Disable Window Monitor Interrupt. */
	adc_disable_interrupt(&g_adc_inst, ADC_WINDOW_MONITOR);

	if ((adc_get_status(&g_adc_inst) & ADCIFE_SR_WM) == ADCIFE_SR_WM) {

		ul_mode = adc_get_wm_mode(&g_adc_inst);
		us_adc = adc_get_last_conv_value(&g_adc_inst);

		switch (ul_mode) {
		case 1:
			printf("-ISR-:DAC output voltage %d mv is above the low threshold:%d mv!\n\r",
					(int)(us_adc * VOLT_REF / MAX_DIGITAL),
					(int)(gs_us_low_threshold * VOLT_REF / MAX_DIGITAL));
			break;

		case 2:
			printf("-ISR-:DAC output voltage %d mv is below the high threshold:%d mv!\n\r",
					(int)(us_adc * VOLT_REF / MAX_DIGITAL),
					(int)(gs_us_high_threshold * VOLT_REF / MAX_DIGITAL));
			break;

		case 3:
			printf("-ISR-:DAC output voltage %d mv is in the comparison window:%d-%d mv!\n\r",
					(int)(us_adc * VOLT_REF / MAX_DIGITAL),
					(int)(gs_us_low_threshold * VOLT_REF / MAX_DIGITAL),
					(int)(gs_us_high_threshold * VOLT_REF / MAX_DIGITAL));
			break;

		case 4:
			printf("-ISR-:DAC output voltage %d mv is out of the comparison window:%d-%d mv!\n\r",
					(int)(us_adc * VOLT_REF / MAX_DIGITAL),
					(int)(gs_us_low_threshold * VOLT_REF / MAX_DIGITAL),
					(int)(gs_us_high_threshold * VOLT_REF / MAX_DIGITAL));
			break;
		}
		adc_clear_status(&g_adc_inst, ADCIFE_SCR_WM);
	}
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
static uint32_t f_to_int(float x)
{
	uint32_t j = (uint32_t) x;
	float k = (float)j;
	if (k == x) {
		return j;
	} else {
		return j + 1;
	}
}

/** Display current information,including
 * voltage on division resistor, thresholds and window monitor mode.
 */
static void display_info(void)
{
	uint32_t ul_adc_value = adc_get_last_conv_value(&g_adc_inst);
	float f_low_threshold =
			(float)gs_us_low_threshold * VOLT_REF / MAX_DIGITAL;
	float f_high_threshold =
			(float)gs_us_high_threshold * VOLT_REF / MAX_DIGITAL;
	uint32_t ul_low_threshold = f_to_int(f_low_threshold);
	uint32_t ul_high_threshold = f_to_int(f_high_threshold);

	printf("-I- Thresholds: %u mv - %u mv.\n\r", ul_low_threshold,
			ul_high_threshold);
	printf("-I- Voltage on tested channel: %u mv.\n\r",
			(unsigned int)(ul_adc_value * VOLT_REF / MAX_DIGITAL));
	printf("-I- Comparison mode is %u\n\r.",
			(unsigned int)(adc_get_wm_mode(&g_adc_inst)));
}

/**
 * Get window monitor mode.
 */
static uint8_t get_wm_mode(void)
{
	uint8_t uc_mode = adc_get_wm_mode(&g_adc_inst);
	uint8_t uc_char;

	while (1) {
		scanf("%c", (char *)&uc_char);
		switch (uc_char) {
		case 'a':
		case 'A':
			uc_mode = 0x1;
			break;
		case 'b':
		case 'B':
			uc_mode = 0x2;
			break;
		case 'c':
		case 'C':
			uc_mode = 0x3;
			break;
		case 'd':
		case 'D':
			uc_mode = 0x4;
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
		scanf("%c", (char *)&c_char);
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

	if (s_value > (int16_t)VOLT_REF) {
		puts("\n\r-F- Too big threshold!\r");
		return -1;
	}

	return s_value;
}

/**
 * \brief Start DAC ouput.
 * Initialize DAC, set clock and timing, and set DAC to given mode.
 */
static void start_dac(void)
{
	sysclk_enable_peripheral_clock(DACC);

	/* Reset DACC registers */
	dacc_reset(DACC);

	/* Half word transfer mode */
	dacc_set_transfer_mode(DACC, 0);

	/* Timing:
	 * startup                - 0x10 (17 clocks)
	 * internal trigger clock - 0x60 (96 clocks)
	 */
	dacc_set_timing(DACC, 0x10, 0x60);

	/* Enable DAC */
	dacc_enable(DACC);

	/* The DAC is 10-bit resolution, so output voltage should be
	 * (3300 * 255) / ((1 << 10) - 1) = 823mv */
	dacc_write_conversion_data(DACC, 255);
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
 * \brief Example entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t c_choice;
	int16_t s_adc_value;
	int16_t s_dac_value;
	int16_t s_threshold = 0;
	float f_dac_data;
	uint32_t ul_dac_data;

	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);

	/* Initialize threshold. */
	gs_us_low_threshold = 1023;
	gs_us_high_threshold = 4095;

	struct adc_config adc_cfg = {
		/* System clock division factor is 16 */
		.prescal = ADC_PRESCAL_DIV16,
		/* The APB clock is used */
		.clksel = ADC_CLKSEL_APBCLK,
		/* Max speed is 150K */
		.speed = ADC_SPEED_150K,
		/* ADC Reference voltage is internal 1.0V */
		.refsel = ADC_REFSEL_0,
		/* Enables the Startup time */
		.start_up = CONFIG_ADC_STARTUP
	};
	struct adc_seq_config adc_seq_cfg = {
		/* Select Vref for shift cycle */
		.zoomrange = ADC_ZOOMRANGE_0,
		/* Pad Ground */
		.muxneg = ADC_MUXNEG_1,
		/* DAC Internal */
		.muxpos = ADC_MUXPOS_3,
		/* Enables the internal voltage sources */
		.internal = ADC_INTERNAL_3,
		/* Disables the ADC gain error reduction */
		.gcomp = ADC_GCOMP_DIS,
		/* Disables the HWLA mode */
		.hwla = ADC_HWLA_DIS,
		/* 12-bits resolution */
		.res = ADC_RES_12_BIT,
		/* Enables the single-ended mode */
		.bipolar = ADC_BIPOLAR_SINGLEENDED
	};
	struct adc_ch_config adc_ch_cfg = {
		.seq_cfg = &adc_seq_cfg,
		/* Internal Timer Max Counter */
		.internal_timer_max_count = 60,
		/* Window monitor mode is off */
		.window_mode = ADC_WM_MODE_3,
		/* The equivalent voltage value is 1023 * VOLT_REF / 4095 = 250mv. */
		.low_threshold = gs_us_low_threshold,
		/* The equivalent voltage value is 4095 * VOLT_REF / 4095 = 1000mv. */
		.high_threshold = gs_us_high_threshold,
	};

	start_dac();

	if(adc_init(&g_adc_inst, ADCIFE, &adc_cfg) != STATUS_OK) {
		puts("-F- ADC Init Fail!\n\r");
		while(1);
	}
	if(adc_enable(&g_adc_inst) != STATUS_OK) {
		puts("-F- ADC Enable Fail!\n\r");
		while(1);
	}
	adc_ch_set_config(&g_adc_inst, &adc_ch_cfg);
	adc_configure_trigger(&g_adc_inst, ADC_TRIG_CON);
	adc_configure_gain(&g_adc_inst, ADC_GAIN_1X);
	adc_set_callback(&g_adc_inst, ADC_WINDOW_MONITOR, adcife_wm_handler,
			ADCIFE_IRQn, 1);

	/* Display main menu. */
	display_menu();

	while (1) {

		scanf("%c", (char *)&c_choice);
		printf("%c\r\n", c_choice);
		switch (c_choice) {
		case '0':
			adc_disable_interrupt(&g_adc_inst, ADC_WINDOW_MONITOR);
			printf("DAC output is set to(mv) from 0mv to %dmv: ",
					(int32_t)VOLT_REF);
			s_dac_value = get_voltage();
			puts("\r");
			f_dac_data = (float)s_dac_value * DACC_MAX_DATA / VDDANA;
			ul_dac_data = f_to_int(f_dac_data);
			if (s_dac_value >= 0) {
				dacc_write_conversion_data(DACC, ul_dac_data);
			}
			delay_ms(100);
			adc_clear_status(&g_adc_inst, ADCIFE_SCR_WM);
			adc_enable_interrupt(&g_adc_inst, ADC_WINDOW_MONITOR);
			break;

		case '1':
			adc_disable_interrupt(&g_adc_inst, ADC_WINDOW_MONITOR);
			printf("Low threshold is set to(mv) from 0mv to %dmv: ",
					(int32_t)VOLT_REF);
			s_threshold = get_voltage();
			puts("\r");
			if (s_threshold >= 0) {
				s_adc_value = s_threshold * MAX_DIGITAL /
						VOLT_REF;
				adc_configure_wm_threshold(&g_adc_inst,
						s_adc_value,
						gs_us_high_threshold);
				/* Renew low threshold. */
				gs_us_low_threshold = s_adc_value;
				float f_low_threshold =
						(float)gs_us_low_threshold *
						VOLT_REF / MAX_DIGITAL;
				uint32_t ul_low_threshold =
						f_to_int(f_low_threshold);
				printf("Setting low threshold to %u mv (reg value to 0x%x ~%d%%)\n\r",
						ul_low_threshold, gs_us_low_threshold,
						gs_us_low_threshold * 100 / MAX_DIGITAL);
			}
			adc_clear_status(&g_adc_inst, ADCIFE_SCR_WM);
			adc_enable_interrupt(&g_adc_inst, ADC_WINDOW_MONITOR);
			break;

		case '2':
			adc_disable_interrupt(&g_adc_inst, ADC_WINDOW_MONITOR);
			printf("High threshold is set to(mv)from 0mv to %dmv:",
					(int32_t)VOLT_REF);
			s_threshold = get_voltage();
			puts("\r");
			if (s_threshold >= 0) {
				s_adc_value = s_threshold * MAX_DIGITAL /
						VOLT_REF;
				adc_configure_wm_threshold(&g_adc_inst,
						gs_us_low_threshold,
						s_adc_value);
				/* Renew high threshold. */
				gs_us_high_threshold = s_adc_value;
				float f_high_threshold =
						(float)gs_us_high_threshold *
						VOLT_REF / MAX_DIGITAL;
				uint32_t ul_high_threshold =
						f_to_int(f_high_threshold);
				printf("Setting high threshold to %u mv (reg value to 0x%x ~%d%%)\n\r",
						ul_high_threshold, gs_us_high_threshold,
						gs_us_high_threshold * 100 / MAX_DIGITAL);
			}
			adc_clear_status(&g_adc_inst, ADCIFE_SCR_WM);
			adc_enable_interrupt(&g_adc_inst, ADC_WINDOW_MONITOR);
			break;

		case '3':
			adc_disable_interrupt(&g_adc_inst, ADC_WINDOW_MONITOR);
			puts("-a. Above low threshold.\n\r"
					"-b. Below high threshold.\n\r"
					"-c. In the comparison window.\n\r"
					"-d. Out of the comparison window.\n\r"
					"-q. Quit the setting.\r");
			c_choice = get_wm_mode();
			adc_configure_wm_mode(&g_adc_inst, c_choice);
			printf("Comparison mode is %c.\n\r", 'a' + c_choice - 1);
			adc_clear_status(&g_adc_inst, ADCIFE_SCR_WM);
			adc_enable_interrupt(&g_adc_inst, ADC_WINDOW_MONITOR);
			break;

		case 'm':
			display_menu();
			break;

		case 'i':
			display_info();
			adc_clear_status(&g_adc_inst, ADCIFE_SCR_WM);
			adc_enable_interrupt(&g_adc_inst, ADC_WINDOW_MONITOR);
			break;
		}
		puts("Press \'m\' or \'M\' to display the main menu again!\r");
	}
}
