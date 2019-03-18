/**
 * \file
 *
 * \brief Unit tests for WM8731 module.
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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

#include <stdint.h>
#include <stdbool.h>
#include <board.h>
#include <sysclk.h>
#include <string.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <conf_test.h>
#include "conf_board.h"
#include "conf_clock.h"
#include "conf_wm8731.h"
#include "wm8731.h"
#include "ssc.h"
#include "dmac.h"
#include "twi_master.h"
#ifdef BOARD_AT24C_TWI_INSTANCE
#  include "at24cxx.h"
#endif

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the WM8731 module.
 * It consists of test cases for the following functionalities:
 * - WM8731 transfer test.
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 * - \ref conf_twi_master.h
 *
 * \section device_info Device Info
 * All SAM devices with TWI and SSC interface can be used.
 * This example has been tested with the following setup:
 * - sam3u4e_sam3u_ek
 * - sam3x8h_sam3x_ek
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
 * \def CONF_TEST_UART
 * \brief UART to redirect STDIO
 */
/**
 * \def CONF_TEST_BAUDRATE
 * \brief Baudrate of UART
 */
/**
 * \def CONF_TEST_PARITY
 * \brief Parity mode of UART
 */
//@}

/* DMA channel used in this example. */
#define DMA_CH 0

/** Wav feature. */
#define SAMPLE_RATE             (48000)
/** Wav slot per frame */
#define SLOT_BY_FRAME           (2)
/** Bits per slot */
#define BITS_BY_SLOT            (16)

/** Bits per slot */
#define WAV_LENGTH            (0xA0u)
/** wav data from the file "sample.wav" */
const uint8_t wav_data[WAV_LENGTH] = {
	0xd8, 0x01, 0x06, 0x01, 0xd4, 0x01, 0x0e, 0x01,
	0xd2, 0x01, 0x18, 0x01, 0xd3, 0x01, 0x20, 0x01,
	0xcd, 0x01, 0x21, 0x01, 0xca, 0x01, 0x23, 0x01,
	0xc6, 0x01, 0x2a, 0x01, 0xbe, 0x01, 0x2d, 0x01,
	0xb7, 0x01, 0x30, 0x01, 0xb4, 0x01, 0x38, 0x01,
	0xb2, 0x01, 0x39, 0x01, 0xae, 0x01, 0x3c, 0x01,
	0xae, 0x01, 0x45, 0x01, 0xaa, 0x01, 0x43, 0x01,
	0xa4, 0x01, 0x3e, 0x01, 0x9d, 0x01, 0x3b, 0x01,
	0x8c, 0x01, 0x30, 0x01, 0x81, 0x01, 0x29, 0x01,
	0x81, 0x01, 0x27, 0x01, 0x81, 0x01, 0x23, 0x01,
	0x82, 0x01, 0x1d, 0x01, 0x84, 0x01, 0x1c, 0x01,
	0x80, 0x01, 0x19, 0x01, 0x7e, 0x01, 0x17, 0x01,
	0x7d, 0x01, 0x12, 0x01, 0x77, 0x01, 0x0c, 0x01,
	0x78, 0x01, 0x0a, 0x01, 0x7a, 0x01, 0x0b, 0x01,
	0x78, 0x01, 0x04, 0x01, 0x75, 0x01, 0xff, 0x00,
	0x77, 0x01, 0x04, 0x01, 0x73, 0x01, 0x09, 0x01,
	0x6f, 0x01, 0x0b, 0x01, 0x6f, 0x01, 0x0c, 0x01,
	0x71, 0x01, 0x08, 0x01, 0x74, 0x01, 0x10, 0x01
};

/** Transfer done flag. */
volatile uint32_t ul_transfer_done = 0;

/*
 * Init TWI interface for WM8731 .
 */
static void init_twi_wm8731(void)
{
	twi_options_t opt;

	/* Configure the options of TWI driver */
	opt.master_clk = sysclk_get_peripheral_hz();
	opt.speed	   = TWI_WM8731_CLK;
	opt.chip	   = WM8731_SLAVE_ADDRESS;
	twi_master_setup(TWI_WM8731, &opt);
}

/**
 * \brief  Initial the codec for audio play.
 */
static void init_dac(void)
{
	uint32_t ul_value;
	/* First, disable programmable clock */
	pmc_disable_pck(PMC_PCK_0);
	/* Then, configure PMC Programmable Clock */
	pmc_switch_pck_to_mainck(PMC_PCK_0, PMC_MCKR_PRES_CLK_1);
	/* Finally, enable programmable clock */
	pmc_enable_pck(PMC_PCK_0);
	/* init control interface */
	init_twi_wm8731();
	/* reset the WM8731 */
	wm8731_reset();
	/* Select the WM8731 DAC */
	wm8731_dac_select(1);
	/* Set the WM8731 to usb mode and 48K DAC */
	wm8731_set_sampling_control(1,0,0);
	/* Set the WM8731 audio interface to I2S mode */
	ul_value = WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_I2S;
	wm8731_set_digital_audio_data_bit_length(ul_value);
	/* Set the WM8731 audio data bit length to 16bit */
	ul_value = WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_IWL_16_BIT;
	wm8731_set_digital_audio_data_bit_length(ul_value);
	/* Disable the WM8731 DAC soft mute */
	wm8731_set_dac_soft_mute(0);
	/* Power up the WM8731 DAC */
	wm8731_power_mode_dac();
	/* Active the WM8731 */
	wm8731_set_active(1);
}


/**
 * \brief  Initial the ssc interface.
 */
static void init_ssc(void)
{
	clock_opt_t tx_clk_option;
	data_frame_opt_t tx_data_frame_option;

	/* Initialize clock */
	pmc_enable_periph_clk(ID_SSC);

	/* Reset SSC */
	ssc_reset(SSC);
	/* Configure SSC */
	ssc_set_clock_divider(SSC, SAMPLE_RATE * (BITS_BY_SLOT + 1) * 2,
			sysclk_get_peripheral_hz());

	/* Transmitter clock mode configuration. */
	tx_clk_option.ul_cks = SSC_TCMR_CKS_MCK;
	tx_clk_option.ul_cko = SSC_TCMR_CKO_CONTINUOUS;
	tx_clk_option.ul_cki = 0;
	tx_clk_option.ul_ckg = SSC_TCMR_CKG_NONE;
	tx_clk_option.ul_start_sel = SSC_TCMR_START_RF_EDGE;
	tx_clk_option.ul_sttdly = 1;
	tx_clk_option.ul_period = BITS_BY_SLOT - 1;
	/* Transmitter frame mode configuration. */
	tx_data_frame_option.ul_datlen = BITS_BY_SLOT - 1;
	tx_data_frame_option.ul_msbf = SSC_TFMR_MSBF;
	tx_data_frame_option.ul_datnb = 0;
	tx_data_frame_option.ul_fslen = BITS_BY_SLOT - 1;
	tx_data_frame_option.ul_fslen_ext = 0;
	tx_data_frame_option.ul_fsos = SSC_TFMR_FSOS_NEGATIVE;
	tx_data_frame_option.ul_fsedge = SSC_TFMR_FSEDGE_POSITIVE;
	/* Configure the SSC transmitter to I2S mode. */
	ssc_set_transmitter(SSC, &tx_clk_option, &tx_data_frame_option);

	/* Disable transmitter first */
	ssc_disable_tx(SSC);

	/* Disable All Interrupt */
	ssc_disable_interrupt(SSC, 0xFFFFFFFF);
}


/**
 * \brief DMA driver configuration
 */
static void init_dma(void)
{
	uint32_t cfg;

	/* Enable DMA controller */
	dmac_enable(DMAC);

	/* Initialize and enable DMA controller */
	pmc_enable_periph_clk(ID_DMAC);
	dmac_init(DMAC);
	dmac_set_priority_mode(DMAC, DMAC_PRIORITY_ROUND_ROBIN);
	dmac_enable(DMAC);

	/* Disable the DMA channel for SSC */
	dmac_channel_disable(DMAC, DMA_CH);

	/* Set channel configuration register */
	cfg = DMAC_CFG_SOD_ENABLE | 	   /* Enable stop on done */
			DMAC_CFG_DST_H2SEL |	   /* Hardware Selection for the Destination */
			DMAC_CFG_DST_PER(3) | /* Destination with Peripheral identifier */
			DMAC_CFG_AHB_PROT(1) |	   /* Set AHB Protection */
			DMAC_CFG_FIFOCFG_ALAP_CFG; /* FIFO Configuration */

	dmac_channel_set_configuration(DMAC, DMA_CH, cfg);

	/* Set interrupt */
	NVIC_EnableIRQ(DMAC_IRQn);
	dmac_enable_interrupt(DMAC, (DMAC_EBCIER_CBTC0 << DMA_CH));
}

/**
 *  \brief Start DMA sending data.
 *
 * \param p_buffer Pointer to the data to be transmitted.
 * \param us_size Size of the data to be transmitted.
 */
static void ssc_dma(void *p_buffer, uint16_t us_size)
{
	dma_transfer_descriptor_t desc;

	desc.ul_source_addr = (uint32_t)p_buffer;
	desc.ul_destination_addr = (uint32_t)(&SSC->SSC_THR);
	desc.ul_ctrlA = DMAC_CTRLA_BTSIZE(us_size)
			| DMAC_CTRLA_SRC_WIDTH_HALF_WORD
			| DMAC_CTRLA_DST_WIDTH_HALF_WORD;
	desc.ul_ctrlB = DMAC_CTRLB_SRC_DSCR_FETCH_DISABLE
			| DMAC_CTRLB_DST_DSCR_FETCH_DISABLE
			| DMAC_CTRLB_FC_MEM2PER_DMA_FC
			| DMAC_CTRLB_SRC_INCR_INCREMENTING
			| DMAC_CTRLB_DST_INCR_FIXED
			| DMAC_CTRLB_IEN;
	desc.ul_descriptor_addr = NULL;

	dmac_channel_single_buf_transfer_init(DMAC, DMA_CH, &desc);

	/* Start DMA transfer */
	dmac_channel_enable(DMAC, DMA_CH);

	/* Enable SSC transmitter */
	ssc_enable_tx(SSC);
}


/**
 * ISR for DMA interrupt
 */
void DMAC_Handler(void)
{
	uint32_t dma_status;

	dma_status = dmac_get_status(DMAC);

	if (dma_status & (DMAC_EBCISR_CBTC0 << DMA_CH)) {
		dmac_channel_stop_transfer(DMAC, DMA_CH);
		ssc_disable_tx(SSC);
		ul_transfer_done = 1;
	}
}

/**
 * \brief WM8731 transfer test.
 *
 * \param test Current test case.
 */
static void run_wm8731_transfer_test(const struct test_case *test)
{
	uint32_t timeout = 0xFFFF;

	ssc_dma((void *)wav_data, WAV_LENGTH);

	while (!ul_transfer_done && timeout) {
		timeout--;
	}

	test_assert_true(test, ul_transfer_done == 1, "WM8731 Transfer Done.");
}

/**
 * \brief Run WM8731 module unit tests.
 */
int main(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_TEST_BAUDRATE,
		.paritytype = CONF_TEST_PARITY
	};

	/* Initialize the system. */
	sysclk_init();
	board_init();
#ifdef BOARD_AT24C_TWI_INSTANCE
	/* reset EEPROM state to release TWI */
	at24cxx_reset();
#endif

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_TEST_UART, &uart_serial_options);

	/* Initial the WM8731 to DAC */
	init_dac();

	/* Initial the ssc interface */
	init_ssc();

	/* Configure DMA */
	init_dma();

	/* Define all the test cases */
	DEFINE_TEST_CASE(wm8731_transfer_test, NULL, run_wm8731_transfer_test,
			NULL, "WM8731 transfer test.");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(wm8731_tests) = {
		&wm8731_transfer_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(wm8731_suite, wm8731_tests,
			"SAM WM8731 module test suite");

	/* Run all tests in the test suite */
	test_suite_run(&wm8731_suite);

	while (1) {
		/* Busy-wait forever */
	}
}
