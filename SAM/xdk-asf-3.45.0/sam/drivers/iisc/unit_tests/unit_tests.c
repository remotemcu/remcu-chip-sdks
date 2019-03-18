/**
 * \file
 *
 * \brief Unit tests for IIS driver.
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

#include <asf.h>
#include <conf_test.h>
#include <string.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the IISC driver.
 * It contains one test case for the IISC module:
 * - Test audio data by set loop back mode.
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_uart_serial.h
 *
 * \section device_info Device Info
 * Only SAM4L devices can be used.
 * This example has been tested with the following setup:
 * - sam4lc4c_sam4l_ek
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for ARM. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */

#define PDCA_IISC_CHANNEL0  0
#define PDCA_IISC_CHANNEL1  1

#define SOUND_SAMPLES 0x100
int16_t output_samples[SOUND_SAMPLES] = {
	0x7F, 0x7F, 0x7D, 0x7E, 0x7D, 0x7E, 0x7D, 0x7E,
	0x7D, 0x7D, 0x7D, 0x7F, 0x7E, 0x7D, 0x7E, 0x7D,
	0x7D, 0x7D, 0x7C, 0x7A, 0x7B, 0x7C, 0x7A, 0x7A,
	0x7C, 0x7B, 0x7E, 0x7F, 0x7F, 0x7F, 0x80, 0x80,
	0x81, 0x82, 0x82, 0x83, 0x83, 0x83, 0x84, 0x84,
	0x86, 0x83, 0x81, 0x81, 0x83, 0x83, 0x83, 0x84,
	0x82, 0x84, 0x84, 0x83, 0x85, 0x85, 0x82, 0x83,
	0x82, 0x82, 0x82, 0x82, 0x7F, 0x80, 0x81, 0x7E,
	0x7E, 0x7E, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7E,
	0x7C, 0x7E, 0x7E, 0x7F, 0x7F, 0x7D, 0x7D, 0x7C,
	0x7D, 0x7D, 0x7D, 0x7B, 0x7C, 0x7B, 0x7C, 0x7D,
	0x7E, 0x7E, 0x7F, 0x7E, 0x7D, 0x7F, 0x7E, 0x7D,
	0x7D, 0x7B, 0x7D, 0x7D, 0x7E, 0x7D, 0x7D, 0x7E,
	0x7D, 0x7D, 0x7D, 0x7E, 0x7E, 0x7C, 0x7E, 0x7E,
	0x7F, 0x7F, 0x7E, 0x7E, 0x7F, 0x7F, 0x80, 0x81,
	0x7F, 0x80, 0x81, 0x80, 0x81, 0x81, 0x81, 0x81,
	0x82, 0x81, 0x82, 0x82, 0x81, 0x80, 0x7F, 0x80,
	0x7F, 0x7F, 0x7E, 0x80, 0x81, 0x82, 0x83, 0x82,
	0x83, 0x84, 0x81, 0x82, 0x82, 0x81, 0x82, 0x81,
	0x80, 0x80, 0x82, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x81, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x81, 0x80, 0x80, 0x7E,
	0x7E, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F,
	0x80, 0x80, 0x81, 0x7E, 0x7F, 0x80, 0x7E, 0x7E,
	0x7E, 0x7F, 0x7E, 0x7E, 0x7E, 0x7C, 0x7D, 0x7C,
	0x81, 0x7D, 0x7C, 0x7C, 0x7B, 0x7D, 0x7C, 0x7D,
	0x7D, 0x7D, 0x7B, 0x7D, 0x80, 0x80, 0x82, 0x80,
	0x7F, 0x80, 0x83, 0x82, 0x80, 0x82, 0x84, 0x86,
	0x86, 0x84, 0x84, 0x86, 0x87, 0x84, 0x85, 0x85,
	0x85, 0x85, 0x86, 0x85, 0x85, 0x84, 0x83, 0x80,
	0x81, 0x82, 0x83, 0x7F, 0x7E, 0x7F, 0x7F, 0x80,
	0x7E, 0x7E, 0x7E, 0x7C, 0x7C, 0x7D, 0x7D, 0x7C
};
int16_t input_samples[SOUND_SAMPLES];

/* PDCA channel options */
static const pdca_channel_config_t pdca_iisc_config_tx = {
	.addr = 0,               /* memory address */
	.pid = IISC_PDCA_ID_TX,  /* select peripheral */
	.size = 0,               /* transfer counter */
	.r_addr = 0,             /* next memory address */
	.r_size = 0,             /* next transfer counter */
	.ring = false,           /* disable ring buffer mode */
	.transfer_size = PDCA_MR_SIZE_WORD /* select size of the transfer */
};
static const pdca_channel_config_t pdca_iisc_config_rx = {
	.addr = 0,               /* memory address */
	.pid = IISC_PDCA_ID_RX,  /* select peripheral */
	.size = 0,               /* transfer counter */
	.r_addr = 0,             /* next memory address */
	.r_size = 0,             /* next transfer counter */
	.ring = false,           /* disable ring buffer mode */
	.transfer_size = PDCA_MR_SIZE_WORD /* select size of the transfer */
};

/* Flag indicate */
volatile uint32_t flag = true;

/**
 * \brief Test audio data transfer and receive.
 *
 * \param test Current test case.
 */
static void run_iis_test(const struct test_case *test)
{
	uint32_t i;
	struct iis_config config;
	struct iis_dev_inst dev_inst;
	struct genclk_config gencfg;
	struct pll_config pcfg;

	/* Set the GCLK according to the sample rate */
	genclk_config_defaults(&gencfg, IISC_GCLK_NUM);
	/* CPUCLK 48M */
	pll_config_init(&pcfg, PLL_SRC_OSC0, 2, 96000000 /
			BOARD_OSC0_HZ);
	pll_enable(&pcfg, 0);
	sysclk_set_prescalers(0, 0, 0, 0, 0);
	pll_wait_for_lock(0);
	sysclk_set_source(SYSCLK_SRC_PLL0);
	/* GCLK according fs ratio */
	genclk_enable_source(GENCLK_SRC_CLK_CPU);
	genclk_config_set_source(&gencfg, GENCLK_SRC_CLK_CPU);
	genclk_config_set_divider(&gencfg, 4);
	genclk_enable(&gencfg, IISC_GCLK_NUM);

	/* Set the configuration */
	iis_get_config_defaults(&config);
	config.data_format = IIS_DATE_16BIT_COMPACT;
	config.slot_length = IIS_SLOT_LENGTH_16BIT;
	config.fs_ratio = IIS_FS_RATE_256;
	config.tx_channels = IIS_CHANNEL_STEREO;
	config.rx_channels = IIS_CHANNEL_STEREO;
	config.tx_dma = IIS_ONE_DMA_CHANNEL_FOR_BOTH_CHANNELS;
	config.rx_dma = IIS_ONE_DMA_CHANNEL_FOR_BOTH_CHANNELS;
	config.loopback = true;
	iis_init(&dev_inst, IISC, &config);

	/* Enable the IIS module. */
	iis_enable(&dev_inst);

	/* Config PDCA module */
	pdca_enable(PDCA);
	pdca_channel_set_config(PDCA_IISC_CHANNEL0, &pdca_iisc_config_tx);
	pdca_channel_set_config(PDCA_IISC_CHANNEL1, &pdca_iisc_config_rx);
	pdca_channel_write_load(PDCA_IISC_CHANNEL0,
			(void *)output_samples, SOUND_SAMPLES / 2);
	pdca_channel_write_load(PDCA_IISC_CHANNEL1,
			(void *)input_samples, SOUND_SAMPLES / 2);
	pdca_channel_enable(PDCA_IISC_CHANNEL0);
	pdca_channel_enable(PDCA_IISC_CHANNEL1);

	/* Enable the functions */
	iis_enable_transmission(&dev_inst);
	iis_enable_clocks(&dev_inst);
	/**
	 * Since the transfer and receive timing is not under control, we
	 * need adjust here the enable sequence and add some delay
	 * functions if it's needed.
	 */
	delay_us(20);
	iis_enable_reception(&dev_inst);

	while (!(pdca_get_channel_status(PDCA_IISC_CHANNEL1)
			== PDCA_CH_TRANSFER_COMPLETED)) {
	}

	/* Disable the PDCA module. */
	pdca_channel_disable(PDCA_IISC_CHANNEL0);
	pdca_channel_disable(PDCA_IISC_CHANNEL1);
	pdca_disable(PDCA);

	/* Disable the IISC module. */
	iis_disable(&dev_inst);

	for (i = 0; i < SOUND_SAMPLES; i++) {
		if (input_samples[i] != output_samples[i]) {
			flag = false;
		}
	}

	test_assert_true(test, flag == true, "Audio data did not match!");
}

/**
 * \brief Run IISC driver unit tests.
 */
int main(void)
{
	sysclk_init();
	board_init();

	const usart_serial_options_t usart_serial_options = {
		.baudrate = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits = CONF_TEST_STOPBITS
	};

	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Define all the test cases. */
	DEFINE_TEST_CASE(iis_test, NULL, run_iis_test, NULL,
			"SAM IIS transfer test");

	/* Put test case addresses in an array. */
	DEFINE_TEST_ARRAY(iis_tests) = {
		&iis_test,
	};

	/* Define the test suite. */
	DEFINE_TEST_SUITE(iis_suite, iis_tests, "SAM IIS driver test suite");

	/* Run all tests in the test suite. */
	test_suite_run(&iis_suite);

	while (1) {
		/* Busy-wait forever. */
	}
}
