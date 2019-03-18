/**
 * \file
 *
 * \brief AFEC feature test example for SAM.
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
 * \mainpage AFEC Feature Test Example
 *
 * \section Purpose
 *
 * The example demonstrates test some features inside the microcontroller.
 *
 * \section Requirements
 *
 * This example can be used on SAM4E-EK boards.
 *
 * \section Description
 *
 * The example is aimed to test some features inside the microcontroller.
 * Users can select testing feature by configuration menu in the terminal.
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
	-- AFEC Feature Test Examplexxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
	=========================================================
	Menu: press a key to test feature.
	---------------------------------------------------------
	-- 0: Gain Test --
	-- 1: Dual AFEC Conversion Test --
	-- 2: Differential Input Test --
	-- 3: User Sequence Test --
	-- 4: Typical Application Test--
\endcode
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
#define MAX_DIGITAL_12_BIT     (4095UL)

#define STRING_EOL    "\r"
#define STRING_HEADER "-- AFEC Feature Test Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

#define MENU_HEADER "\n\r-- press a key to set test feature--\n\r" \
		"-- 0: Gain Test --\n\r" \
		"-- 1: Dual AFEC Conversion Test --\n\r" \
		"-- 2: Differential Input Test --\n\r" \
		"-- 3: User Sequence Test --\n\r" \
		"-- 4: Typical Application Test -- \n\r" \

/** AFEC sample data */
float g_afec0_sample_data, g_afec1_sample_data;

/** The maximal digital value */
static uint32_t g_max_digital;

/** The delay counter value */
static uint32_t g_delay_cnt;

enum afec_channel_num ch_list[] =
{
	AFEC_CHANNEL_1,
	AFEC_CHANNEL_0,
};

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
 * \brief Display main menu.
 */
static void display_menu(void)
{
	puts(MENU_HEADER);
}

/**
 * \brief Simple function to replace printf with float formatting.
 */
static void print_float(float temp)
{
	uint8_t i;
	int32_t j;
	float f;

	f = 100.00 * temp;

	j = (int32_t)f;

	if (temp > 0) {
		i = j - (int32_t)temp * 100;
	} else {
		i = (int32_t)temp * 100 - j;
	}

	j = j / 100;

	printf("%d.%d mv \n\r", (int32_t)j, (int32_t)i);
}

/**
 * \brief AFEC0 DRDY interrupt callback function.
 */
static void afec0_data_ready(void)
{
	g_afec0_sample_data = afec_get_latest_value(AFEC0);
	puts("AFEC0 Channel Voltage:");
	print_float(g_afec0_sample_data * VOLT_REF / g_max_digital);
}

/**
 * \brief AFEC1 DRDY interrupt callback function.
 */
static void afec1_data_ready(void)
{
	g_afec1_sample_data = afec_get_latest_value(AFEC1);
	puts("AFEC1 Channel Voltage:");
	print_float(g_afec1_sample_data * VOLT_REF / g_max_digital);
}

/**
 * \brief AFEC0 EOC0 interrupt callback function.
 */
static void afec_eoc_0(void)
{
	g_afec0_sample_data = afec_channel_get_value(AFEC0, AFEC_CHANNEL_0);
	puts("AFEC0 Channel 0 Voltage:");
	print_float(g_afec0_sample_data * VOLT_REF / g_max_digital);
}

/**
 * \brief AFEC0 EOC1 interrupt callback function.
 */
static void afec_eoc_1(void)
{
	g_afec1_sample_data = afec_channel_get_value(AFEC0, AFEC_CHANNEL_1);
	puts("AFEC0 Channel 1 Voltage:");
	print_float(g_afec1_sample_data * VOLT_REF / g_max_digital);
}

/**
 * \brief AFEC0 DRDY interrupt callback function.
 */
static void afec0_diff_data_ready(void)
{
	g_afec0_sample_data = afec_get_latest_value(AFEC0);
	puts("AFEC0 Channel Differential Voltage:");
	print_float(g_afec0_sample_data * VOLT_REF / g_max_digital - 1650);
}

/**
 * \brief Configure to trigger AFEC by TIOA output of timer.
 */
static void configure_tc_trigger(void)
{
	uint32_t ul_div = 0;
	uint32_t ul_tc_clks = 0;
	uint32_t ul_sysclk = sysclk_get_cpu_hz();

	/* Enable peripheral clock. */
	pmc_enable_periph_clk(ID_TC0);

	/* Configure TC for a 1Hz frequency and trigger on RC compare. */
	tc_find_mck_divisor(1, ul_sysclk, &ul_div, &ul_tc_clks, ul_sysclk);
	tc_init(TC0, 0, ul_tc_clks | TC_CMR_CPCTRG | TC_CMR_WAVE |
			TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_SET);

	TC0->TC_CHANNEL[0].TC_RA = (ul_sysclk / ul_div) / 2;
	TC0->TC_CHANNEL[0].TC_RC = (ul_sysclk / ul_div) / 1;

	/* Start the Timer. */
	tc_start(TC0, 0);

	afec_set_trigger(AFEC1, AFEC_TRIG_TIO_CH_0);
}

/**
 * \brief Set AFEC test mode.
 */
static void set_afec_test(void)
{
	uint8_t uc_key;
	struct afec_config afec_cfg;
	struct afec_ch_config afec_ch_cfg;

	display_menu();

	afec_enable(AFEC0);
	afec_get_config_defaults(&afec_cfg);
	afec_ch_get_config_defaults(&afec_ch_cfg);

	while (uart_read(CONF_UART, &uc_key));

	switch (uc_key) {
	case '0':
		/*
		* This test will use AFEC0 channel4 to connect with external input.
		* Setting gain = 4, if external input voltage is 100mv,
		* the ouput result should be 1650 + 100 * 4 = 2050mv .
		*/
		puts("Gain Test \n\r");
		g_delay_cnt = 1000;
		afec_init(AFEC0, &afec_cfg);
		afec_ch_cfg.gain = AFEC_GAINVALUE_3;
		afec_ch_set_config(AFEC0, AFEC_CHANNEL_4, &afec_ch_cfg);
		afec_set_trigger(AFEC0, AFEC_TRIG_SW);
		afec_channel_enable(AFEC0, AFEC_CHANNEL_4);
		afec_set_callback(AFEC0, AFEC_INTERRUPT_DATA_READY, afec0_data_ready, 1);
		afec_start_calibration(AFEC0);
		while((afec_get_interrupt_status(AFEC0) & AFEC_ISR_EOCAL) != AFEC_ISR_EOCAL);
		break;
	case '1':
		/*
		 *  This test will use AFEC0 channel5 to connect with potentiometer and
		 * AFEC1 channel0 to connect with external input. The AFEC0 conversion
		 * is triggered by software every 3s and AFEC1 conversion is triggered
		 * by TC every 1s.
		 */
		puts("Dual AFEC Conversion Test \n\r");
		g_delay_cnt = 3000;
		afec_enable(AFEC1);
		afec_init(AFEC0, &afec_cfg);
		afec_init(AFEC1, &afec_cfg);
		afec_ch_set_config(AFEC0, AFEC_CHANNEL_POTENTIOMETER, &afec_ch_cfg);
		afec_ch_set_config(AFEC1, AFEC_CHANNEL_0, &afec_ch_cfg);
		/*
		 * Because the internal AFEC offset is 0x800, it should cancel it and shift
		 * down to 0.
		 */
		afec_channel_set_analog_offset(AFEC1, AFEC_CHANNEL_0, 0x800);
		afec_channel_set_analog_offset(AFEC0, AFEC_CHANNEL_POTENTIOMETER, 0x800);
		afec_set_trigger(AFEC0, AFEC_TRIG_SW);
		configure_tc_trigger();
		afec_channel_enable(AFEC1, AFEC_CHANNEL_0);
		afec_channel_enable(AFEC0, AFEC_CHANNEL_POTENTIOMETER);
		afec_set_callback(AFEC0, AFEC_INTERRUPT_DATA_READY, afec0_data_ready, 1);
		afec_set_callback(AFEC1, AFEC_INTERRUPT_DATA_READY, afec1_data_ready, 1);
		afec_start_calibration(AFEC0);
		while((afec_get_interrupt_status(AFEC0) & AFEC_ISR_EOCAL) != AFEC_ISR_EOCAL);
		afec_start_calibration(AFEC1);
		while((afec_get_interrupt_status(AFEC1) & AFEC_ISR_EOCAL) != AFEC_ISR_EOCAL);
		break;
	case '2':
		/*
		 * This test will use AFEC0 channl4 and channel5 as positive and
		 * negative input, so the output result is external input voltage subtracting
		 * potentiometer voltage. The differential voltage range is -1.65v~ +1.65v.
		 */
		puts("Differential Input Test \n\r");
		g_delay_cnt = 1000;
		afec_init(AFEC0, &afec_cfg);
		afec_ch_cfg.diff = true;
		afec_ch_set_config(AFEC0, AFEC_CHANNEL_POTENTIOMETER, &afec_ch_cfg);
		afec_ch_set_config(AFEC0, AFEC_CHANNEL_4, &afec_ch_cfg);
		afec_set_trigger(AFEC0, AFEC_TRIG_SW);
		afec_channel_enable(AFEC0, AFEC_CHANNEL_4);
		afec_channel_enable(AFEC0, AFEC_CHANNEL_POTENTIOMETER);
		afec_set_callback(AFEC0, AFEC_INTERRUPT_DATA_READY, afec0_diff_data_ready, 1);
		afec_start_calibration(AFEC0);
		while((afec_get_interrupt_status(AFEC0) & AFEC_ISR_EOCAL) != AFEC_ISR_EOCAL);
		break;
	case '3':
		/*
		 * This test will configure user sequence channel1, channel0,
		 * so the first conversion is is channel1 and next is channel0.
		 * The output information will show this.
		 */
		puts("User Sequence Test \n\r");
		g_delay_cnt = 1000;
		afec_init(AFEC0, &afec_cfg);
		afec_ch_set_config(AFEC0, AFEC_CHANNEL_0, &afec_ch_cfg);
		afec_ch_set_config(AFEC0, AFEC_CHANNEL_1, &afec_ch_cfg);
		afec_channel_enable(AFEC0, AFEC_CHANNEL_0);
		afec_channel_enable(AFEC0, AFEC_CHANNEL_1);
		afec_configure_sequence(AFEC0, ch_list, 2);
		afec_set_callback(AFEC0, AFEC_INTERRUPT_EOC_0, afec_eoc_0, 1);
		afec_set_callback(AFEC0, AFEC_INTERRUPT_EOC_1, afec_eoc_1, 1);
		afec_start_calibration(AFEC0);
		while((afec_get_interrupt_status(AFEC0) & AFEC_ISR_EOCAL) != AFEC_ISR_EOCAL);
		break;
	case '4':
		/*
		 * This test use AFEC0 channel4 to connect with external input.
		 * It integrate the enhanced resolution test and gain and offset test.
		 */
		puts("Typical Application Test \n\r");
		g_delay_cnt = 1000;
		g_max_digital = MAX_DIGITAL_12_BIT * 16;
		afec_cfg.resolution = AFEC_16_BITS;
		afec_init(AFEC0, &afec_cfg);
		afec_ch_cfg.gain = AFEC_GAINVALUE_3;
		afec_ch_set_config(AFEC0, AFEC_CHANNEL_4, &afec_ch_cfg);
		afec_set_trigger(AFEC0, AFEC_TRIG_SW);
		afec_channel_enable(AFEC0, AFEC_CHANNEL_4);
		afec_set_callback(AFEC0, AFEC_INTERRUPT_DATA_READY, afec0_data_ready, 1);
		afec_start_calibration(AFEC0);
		while((afec_get_interrupt_status(AFEC0) & AFEC_ISR_EOCAL) != AFEC_ISR_EOCAL);
		break;
	default:
		puts("Please select feature test correctly! \n\r");
		break;
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

	g_afec0_sample_data = 0;
	g_afec1_sample_data = 0;
	g_max_digital = MAX_DIGITAL_12_BIT;

	set_afec_test();

	while (1) {
		afec_start_software_conversion(AFEC0);
		delay_ms(g_delay_cnt);

		/* Check if the user enters a key. */
		if (!uart_read(CONF_UART, &uc_key)) {
			/* Disable all afec interrupt. */
			afec_disable_interrupt(AFEC0, AFEC_INTERRUPT_ALL);
			afec_disable_interrupt(AFEC1, AFEC_INTERRUPT_ALL);
			tc_stop(TC0, 0);
			set_afec_test();
		}
	}
}
