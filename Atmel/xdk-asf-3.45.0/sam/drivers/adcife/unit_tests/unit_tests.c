/**
 * \file
 *
 * \brief Unit tests for ADCIFE driver.
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

#include <board.h>
#include <sysclk.h>
#include <delay.h>
#include "adcife.h"
#include "dacc.h"
#include "pdca.h"
#include <string.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <conf_test.h>
#include <conf_board.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the ADCIFE driver.
 * It consists of test cases for the following functionality:
 * - Initialize test
 * - Differential test
 * - Internal Timer trigger test
 * - Multichannel test
 * - Window mode test
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 *
 * \section device_info Device Info
 * The SAM4L devices can be used.
 * This example has been tested with the following setup:
 * - sam4lc4c_sam4l_ek
 * - sam4lc4c_sam4l_xplained_pro
 * - sam4lc8c_sam4l8_xplained_pro
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for ARM. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */

//! \name Unit test configuration
//@{
/**
 * \def CONF_TEST_ADCIFE
 * \brief Test the functions provided by the ADCIFE driver.
 */
//@}

/** Conversion done flag */
volatile uint8_t g_uc_condone_flag = 0;

/** Enter comparison window flag */
volatile uint8_t g_uc_enter_win_flag = 0;

/** Conversion value */
uint16_t g_adc_sample_data[2];

/** ADC CDMA config value */
struct adc_cdma_first_config g_adc_cdma_first_cfg[2] = {
	{
		/* Select Vref for shift cycle */
		.zoomrange = ADC_ZOOMRANGE_0,
		/* Pad Ground */
		.muxneg = ADC_MUXNEG_1,
		/* Scaled Vcc, Vcc/10 */
		.muxpos = ADC_MUXPOS_2,
		/* Enables the internal voltage sources */
		.internal = ADC_INTERNAL_3,
		/* Disables the ADC gain error reduction */
		.gcomp = ADC_GCOMP_DIS,
		/* Disables the HWLA mode */
		.hwla = ADC_HWLA_DIS,
		/* 12-bits resolution */
		.res = ADC_RES_12_BIT,
		/* Enables the single-ended mode */
		.bipolar = ADC_BIPOLAR_SINGLEENDED,
		/* Gain factor is 1x */
		.gain = ADC_GAIN_1X,
		.strig = 1,
		.tss = 1,
		.enstup = 1,
		.dw = 0
	},
	{
		.zoomrange = ADC_ZOOMRANGE_0,
		.muxneg = ADC_MUXNEG_1,
		/* DAC internal */
		.muxpos = ADC_MUXPOS_3,
		.internal = ADC_INTERNAL_3,
		.gcomp = ADC_GCOMP_DIS,
		.hwla = ADC_HWLA_DIS,
		.res = ADC_RES_12_BIT,
		.bipolar = ADC_BIPOLAR_SINGLEENDED,
		.gain = ADC_GAIN_1X,
		.strig = 1,
		.tss = 1,
		.enstup = 1,
		.dw = 0
	}
};

struct adc_pdca_config g_adc_pdca_cfg = {
	/* ADC Window Mode */
	.wm = false,
	/* ADC Nb channel */
	.nb_channels = 2,
	/* ADC Buffer */
	.buffer = g_adc_sample_data,
	/* ADC PDC Rx Channel */
	.pdc_rx_channel = CONFIG_ADC_PDCA_RX_CHANNEL,
	/* ADC PDC Tx Channel */
	.pdc_tx_channel = CONFIG_ADC_PDCA_TX_CHANNEL,
	/* ADC CDMA Configuration Structure */
	.cdma_cfg = (void *)&g_adc_cdma_first_cfg[0]
};

/** ADCIFE startup time value */
#define  ADCIFE_STARTUP   24

/** The maximal digital value*/
#define MAX_DIGITAL     (4095)

/** ADC instance */
struct adc_dev_inst g_adc_inst;

/**
 * \brief Callback function for ADCIFE interrupt.
 */
static void adcife_set_conv_flag(void)
{
	if ((adc_get_status(&g_adc_inst) & ADCIFE_SR_SEOC) == ADCIFE_SR_SEOC) {
		g_uc_condone_flag = 1;
		adc_clear_status(&g_adc_inst, ADCIFE_SCR_SEOC);
		adc_disable_interrupt(&g_adc_inst, ADC_SEQ_SEOC);
	}
}

/**
 * \brief Callback function for PDCA interrupt.
 */
static void pdca_transfer_done(enum pdca_channel_status status)
{
	if (status == PDCA_CH_TRANSFER_COMPLETED) {
		pdca_channel_write_load(CONFIG_ADC_PDCA_RX_CHANNEL,
				g_adc_sample_data, 2);
		pdca_channel_write_load(CONFIG_ADC_PDCA_TX_CHANNEL,
				g_adc_cdma_first_cfg, 2);
		pdca_channel_disable_interrupt(CONFIG_ADC_PDCA_RX_CHANNEL,
				PDCA_IER_TRC);
		pdca_channel_disable_interrupt(CONFIG_ADC_PDCA_TX_CHANNEL,
				PDCA_IER_TRC);
	}
}

/**
 * \brief Callback function for ADCIFE enter compasion window interrupt.
 */
static void adcife_set_wm_flag(void)
{
	/* Disable Window Monitor Interrupt. */
	adc_disable_interrupt(&g_adc_inst, ADC_WINDOW_MONITOR);
	g_uc_enter_win_flag = 1;
	adc_clear_status(&g_adc_inst, ADCIFE_SCR_WM);
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
	dacc_write_conversion_data(DACC, 0xFF);
}

/**
 * \brief Test ADCIFE Initialize is OK or not.
 *
 * \param test Current test case.
 */
static void run_adcife_init_test(const struct test_case *test)
{
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

	test_assert_true(test,
			(adc_init(&g_adc_inst, ADCIFE, &adc_cfg) == STATUS_OK) &&
			(adc_enable(&g_adc_inst) == STATUS_OK),
			"ADCIFE initialize test failed");
}

/**
 * \brief Test ADCIFE in Differential mode.
 *
 * \param test Current test case.
 */
static void run_adcife_diff_test(const struct test_case *test)
{
	uint32_t timeout = ADC_NUM_OF_ATTEMPTS;
	bool conversion_timeout = false;

	struct adc_seq_config adc_seq_cfg = {
		/* Select Vref for shift cycle */
		.zoomrange = ADC_ZOOMRANGE_0,
		/* Pad Ground */
		.muxneg = ADC_MUXNEG_1,
		/* Scaled Vcc, Vcc/10 */
		.muxpos = ADC_MUXPOS_2,
		/* Enables the internal voltage sources */
		.internal = ADC_INTERNAL_3,
		/* Disables the ADC gain error reduction */
		.gcomp = ADC_GCOMP_DIS,
		/* Disables the HWLA mode */
		.hwla = ADC_HWLA_DIS,
		/* 12-bits resolution */
		.res = ADC_RES_12_BIT,
		/* Enables the differential mode */
		.bipolar = ADC_BIPOLAR_DIFFERENTIAL
	};
	struct adc_ch_config adc_ch_cfg = {
		.seq_cfg = &adc_seq_cfg,
		/* Internal Timer Max Counter */
		.internal_timer_max_count = 60,
		/* Window monitor mode is off */
		.window_mode = 0,
		.low_threshold = 0,
		.high_threshold = 0,
	};

	adc_ch_set_config(&g_adc_inst, &adc_ch_cfg);
	adc_configure_trigger(&g_adc_inst, ADC_TRIG_CON);
	adc_configure_gain(&g_adc_inst, ADC_GAIN_1X);
	while (!((adc_get_status(&g_adc_inst) & ADCIFE_SR_SEOC) ==
			ADCIFE_SR_SEOC)) {
		if (!timeout--) {
			conversion_timeout = true;
		}
	}

	test_assert_true(test, conversion_timeout == false, "ADCIFE Differential conversion timeout");

	/* Because selected channel is positive input, then in differential mode
	 * the output conversion result will = 2047 + (Vin/Vref)*2047.
	 */
	test_assert_true(test, adc_get_last_conv_value(&g_adc_inst) > 2047,
			"ADCIFE Differential test failed");
}

/**
 * \brief Test ADCIFE in internal timer trigger mode,
 *        which also tests interrupt driven conversions.
 *
 * \param test Current test case.
 */
static void run_adcife_itimer_trig_test(const struct test_case *test)
{
	struct adc_seq_config adc_seq_cfg = {
		/* Select Vref for shift cycle */
		.zoomrange = ADC_ZOOMRANGE_0,
		/* Pad Ground */
		.muxneg = ADC_MUXNEG_1,
		/* Scaled Vcc, Vcc/10 */
		.muxpos = ADC_MUXPOS_2,
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
		.window_mode = 0,
		.low_threshold = 0,
		.high_threshold = 0,
	};

	adc_ch_set_config(&g_adc_inst, &adc_ch_cfg);
	adc_set_callback(&g_adc_inst, ADC_SEQ_SEOC, adcife_set_conv_flag,
			ADCIFE_IRQn, 1);
	adc_configure_trigger(&g_adc_inst, ADC_TRIG_INTL_TIMER);
	adc_configure_gain(&g_adc_inst, ADC_GAIN_1X);
	adc_configure_itimer_period(&g_adc_inst,
			adc_ch_cfg.internal_timer_max_count);
	adc_start_itimer(&g_adc_inst);
	delay_ms(100);

	test_assert_true(test, g_uc_condone_flag == 1,
			"ADCIFE Internal Timer trigger test failed");
}

/* When VDDANA is in MIN value = 2.4V, the equivalent voltage value is
 * (2400 * 255) / ((1 << 10) - 1) = 598mv. The relative digital value is
 * 598 * 4095 / 1000 = 2449. */
#define DAC_INTERNAL_MIN_VALUE          2449
/* When VDDANA is in MAX value = 3.6V the equivalent voltage value is
 * (3600 * 255) / ((1 << 10) - 1) = 897mv. The relative digital value is
 * 897 * 4095 / 1000 = 3673. */
#define DAC_INTERNAL_MAX_VALUE          3673
/* When VCC is in MIN value = 1.6V, the equivalent voltage value is
 * 1600 / 10 = 160mv. The relative digital value is
 * 160 * 4095 / 1000 = 434. */
#define VCC_SCALED_MIN_VALUE            434
/* When VCC is in MAX value = 3.6V, the equivalent voltage value is
 * 3600 / 10 = 360mv. The relative digital value is
 * 360 * 4095 / 1000 = 1474. */
#define VCC_SCALED_MAX_VALUE            1474

/**
 * \brief Test ADCIFE in multiple channel mode.
 *
 * \param test Current test case.
 */
static void run_adcife_multichannel_test(const struct test_case *test)
{
	start_dac();

	adc_pdca_set_config(&g_adc_pdca_cfg);
	pdca_channel_set_callback(CONFIG_ADC_PDCA_RX_CHANNEL, pdca_transfer_done,
			PDCA_0_IRQn, 1, PDCA_IER_TRC);
	adc_configure_trigger(&g_adc_inst, ADC_TRIG_CON);
	adc_configure_gain(&g_adc_inst, ADC_GAIN_1X);

	delay_ms(100);

	/* The DAC output voltage value is 823mv, so the equivalent ADC value should be
	 * 4095 * 823 / 1000 = 3370. The scaled VCC output voltage is 330mv, so the
	 * equivalent ADC value should be 4095 * 330 / 1000 =  1351. */
	test_assert_true(test,
			((DAC_INTERNAL_MIN_VALUE < g_adc_sample_data[0] < DAC_INTERNAL_MAX_VALUE)
			&& (VCC_SCALED_MIN_VALUE < g_adc_sample_data[1] < VCC_SCALED_MAX_VALUE)),
			"ADCIFE Multichannel test failed");
}

/**
 * \brief Test ADCIFE in window monitor mode.
 *
 * \param test Current test case.
 */
static void run_adcife_wm_test(const struct test_case *test)
{
	struct adc_seq_config adc_seq_cfg = {
		/* Select Vref for shift cycle */
		.zoomrange = ADC_ZOOMRANGE_0,
		/* Pad Ground */
		.muxneg = ADC_MUXNEG_1,
		/* Scaled Vcc, Vcc/10 */
		.muxpos = ADC_MUXPOS_2,
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
		/*  The equivalent voltage value is 205 * 1000 / 4095 = 50mv. */
		.low_threshold = 205,
		/*  The equivalent voltage value is 2050 * 1000 / 4095 = 500mv. */
		.high_threshold = 2050,
	};

	adc_ch_set_config(&g_adc_inst, &adc_ch_cfg);
	adc_configure_trigger(&g_adc_inst, ADC_TRIG_CON);
	adc_configure_gain(&g_adc_inst, ADC_GAIN_1X);

	adc_set_callback(&g_adc_inst, ADC_WINDOW_MONITOR, adcife_set_wm_flag,
			ADCIFE_IRQn, 1);
	delay_ms(100);
	test_assert_true(test, g_uc_enter_win_flag == 1,
			"ADCIFE Inside Window Mode test failed");

	/* The teseted channel voltage is outside window */
	adc_disable(&g_adc_inst);
	g_uc_enter_win_flag = 0;
	adc_seq_cfg.muxpos = ADC_MUXPOS_3;
	adc_ch_set_config(&g_adc_inst, &adc_ch_cfg);
	adc_configure_trigger(&g_adc_inst, ADC_TRIG_CON);
	adc_configure_gain(&g_adc_inst, ADC_GAIN_1X);
	adc_enable_interrupt(&g_adc_inst, ADC_WINDOW_MONITOR);

	delay_ms(100);
	test_assert_true(test, g_uc_enter_win_flag == 0,
			"ADCIFE Outside Window Mode test failed");
}

/**
 * \brief Run ADCIFE driver unit tests.
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits = CONF_TEST_STOPBITS
	};

	/* Initialize the system clock and board */
	sysclk_init();
	board_init();

	/* Enable the debug uart */
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

#if defined(__GNUC__)
	setbuf(stdout, NULL);
#endif

	/* Define all the test cases */
	DEFINE_TEST_CASE(adcife_init_test, NULL, run_adcife_init_test, NULL,
			"ADCIFE Initialize test");
	DEFINE_TEST_CASE(adcife_diff_test, NULL, run_adcife_diff_test, NULL,
			"ADCIFE Differential test");
	DEFINE_TEST_CASE(adcife_itmer_trig_test, NULL, run_adcife_itimer_trig_test,
			NULL, "ADCIFE Internal Timer trigger test");
	DEFINE_TEST_CASE(adcife_multichannel_test, NULL, run_adcife_multichannel_test, NULL,
			"ADCIFE Multichannel test");
	DEFINE_TEST_CASE(adcife_wm_test, NULL, run_adcife_wm_test,
			NULL, "ADCIFE Window Monitor Mode test");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(adcife_tests) = {
	&adcife_init_test,
	&adcife_diff_test,
	&adcife_itmer_trig_test,
	&adcife_multichannel_test,
	&adcife_wm_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(adcife_suite, adcife_tests,
			"SAM ADCIFE driver test suite");

	/* Run all tests in the test suite */
	test_suite_run(&adcife_suite);

	while (1) {
		/* Busy-wait forever. */
	}
}
