/**
 * \file
 *
 * \brief Unit tests for DMAC driver.
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

#include "asf.h"
#include "conf_test.h"
#include "conf_board.h"
#include "conf_clock.h"

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the DMAC driver.
 * It consists of test cases for the following functionalities:
 * - Test DMA single buffer transfer with polling mode.
 * - Test DMA multiple buffer transfer with interrupt mode.
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 *
 * \section device_info Device Info
 * All SAM devices with DMAC peripheral can be used.
 * This example has been tested with the following setup:
 * - sam3u4e_sam3u_ek
 * - sam3x8h_sam3x_ek
 * - sam4e16e_sam4e_ek
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for ARM. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */

/** \name Unit test configuration */
/** @{ */

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
/** @} */

/* DMA channel used in this example. */
#define DMA_CH 0

/* DMA buffer size. */
#define DMA_BUF_SIZE    32

/* DMA transfer done flag. */
volatile uint32_t g_xfer_done = 0;

/** DMA buffer. */
uint32_t g_dma_buf[6][DMA_BUF_SIZE];

/**
 * \brief Test DMA single buffer transfer with polling mode.
 *
 * \param test Current test case.
 */
static void run_single_buf_xfer_test(const struct test_case *test)
{
	uint32_t i;
	uint32_t cfg;
	dma_transfer_descriptor_t desc;

	/* Initialize DMA buffer */
	for (i = 0; i < DMA_BUF_SIZE; i++) {
		g_dma_buf[0][i] = i;
		g_dma_buf[1][i] = 0;
	}

	/* Initialize and enable DMA controller */
	pmc_enable_periph_clk(ID_DMAC);
	dmac_init(DMAC);
	dmac_set_priority_mode(DMAC, DMAC_PRIORITY_ROUND_ROBIN);
	dmac_enable(DMAC);

	/* Set for channel configuration register */
	cfg = DMAC_CFG_SOD_ENABLE |        /* Enable stop on done */
			DMAC_CFG_AHB_PROT(1) |     /* Set AHB Protection */
			DMAC_CFG_FIFOCFG_ALAP_CFG; /* FIFO Configuration */
	dmac_channel_set_configuration(DMAC, DMA_CH, cfg);

	/* Initialize single buffer transfer: buffer 0 -> buffer 1 */
	desc.ul_source_addr = (uint32_t) g_dma_buf[0];
	desc.ul_destination_addr = (uint32_t) g_dma_buf[1];
	desc.ul_ctrlA = DMAC_CTRLA_BTSIZE(DMA_BUF_SIZE) |   /* Set Buffer Transfer Size */
			DMAC_CTRLA_SRC_WIDTH_WORD |                 /* Source transfer size is set to 32-bit width */
			DMAC_CTRLA_DST_WIDTH_WORD;                  /* Destination transfer size is set to 32-bit width */
	desc.ul_ctrlB = DMAC_CTRLB_SRC_DSCR_FETCH_DISABLE | /* Buffer Descriptor Fetch operation is disabled for the source */
			DMAC_CTRLB_DST_DSCR_FETCH_DISABLE |         /* Buffer Descriptor Fetch operation is disabled for the destination */
			DMAC_CTRLB_FC_MEM2MEM_DMA_FC |              /* Memory-to-Memory Transfer */
			DMAC_CTRLB_SRC_INCR_INCREMENTING |          /* The source address is incremented */
			DMAC_CTRLB_DST_INCR_INCREMENTING;           /* The destination address is incremented */
	desc.ul_descriptor_addr = 0;                        /* No descriptor for single transfer */
	dmac_channel_single_buf_transfer_init(DMAC, DMA_CH, &desc);

	/* Start DMA transfer and wait for finish */
	dmac_channel_enable(DMAC, DMA_CH);
	while (!dmac_channel_is_transfer_done(DMAC, DMA_CH)) {
	}

	/* Verify the transferred data */
	for (i = 0; i < DMA_BUF_SIZE; i++) {
		test_assert_true(test, g_dma_buf[0][i] == g_dma_buf[1][i],
				"Data comparison failed.");
	}
}

/**
 * \brief Test DMA multiple buffer transfer with interrupt mode.
 *
 * \param test Current test case.
 */
static void run_multi_buf_xfer_test(const struct test_case *test)
{
	uint32_t i;
	uint32_t cfg;
	dma_transfer_descriptor_t desc[3];

	/* Initialize DMA buffer */
	for (i = 0; i < DMA_BUF_SIZE; i++) {
		g_dma_buf[0][i] = i;
		g_dma_buf[1][i] = i + 10;
		g_dma_buf[2][i] = i + 20;
		g_dma_buf[3][i] = 0;
		g_dma_buf[4][i] = 0;
		g_dma_buf[5][i] = 0;
	}

	/* Initialize and enable DMA controller */
	pmc_enable_periph_clk(ID_DMAC);
	dmac_init(DMAC);
	dmac_set_priority_mode(DMAC, DMAC_PRIORITY_ROUND_ROBIN);
	dmac_enable(DMAC);

	/* Set for channel configuration register */
	cfg = DMAC_CFG_SOD_DISABLE |        /* Disable stop on done */
			DMAC_CFG_AHB_PROT(1) |      /* Set AHB Protection */
			DMAC_CFG_FIFOCFG_ALAP_CFG;  /* FIFO Configuration */
	dmac_channel_set_configuration(DMAC, 0, cfg);

	/* Initialize multiple buffer transfer (LLI) :
	 *     buffer 0 -> buffer 3
	 *     buffer 1 -> buffer 4
	 *     buffer 2 -> buffer 5
	 */
	desc[0].ul_source_addr = (uint32_t) g_dma_buf[0];
	desc[0].ul_destination_addr = (uint32_t) g_dma_buf[3];
	desc[0].ul_ctrlA = DMAC_CTRLA_BTSIZE(DMA_BUF_SIZE) |    /* Set Buffer Transfer Size */
			DMAC_CTRLA_SRC_WIDTH_WORD |                     /* Source transfer size is set to 32-bit width */
			DMAC_CTRLA_DST_WIDTH_WORD;                      /* Destination transfer size is set to 32-bit width */
	desc[0].ul_ctrlB = DMAC_CTRLB_SRC_DSCR_FETCH_FROM_MEM | /* Descriptor is fetched from the memory */
			DMAC_CTRLB_DST_DSCR_FETCH_FROM_MEM |            /* Descriptor is fetched from the memory */
			DMAC_CTRLB_FC_MEM2MEM_DMA_FC |                  /* Memory-to-Memory Transfer */
			DMAC_CTRLB_SRC_INCR_INCREMENTING |              /* The source address is incremented */
			DMAC_CTRLB_DST_INCR_INCREMENTING;               /* The destination address is incremented */
	desc[0].ul_descriptor_addr = (uint32_t) &desc[1];       /* Pointer to next descriptor */

	desc[1].ul_source_addr = (uint32_t) g_dma_buf[1];
	desc[1].ul_destination_addr = (uint32_t) g_dma_buf[4];
	desc[1].ul_ctrlA = DMAC_CTRLA_BTSIZE(DMA_BUF_SIZE) |    /* Set Buffer Transfer Size */
			DMAC_CTRLA_SRC_WIDTH_WORD |                     /* Source transfer size is set to 32-bit width */
			DMAC_CTRLA_DST_WIDTH_WORD;                      /* Destination transfer size is set to 32-bit width */
	desc[1].ul_ctrlB = DMAC_CTRLB_SRC_DSCR_FETCH_FROM_MEM | /* Descriptor is fetched from the memory */
			DMAC_CTRLB_DST_DSCR_FETCH_FROM_MEM |            /* Descriptor is fetched from the memory */
			DMAC_CTRLB_FC_MEM2MEM_DMA_FC |                  /* Memory-to-Memory Transfer */
			DMAC_CTRLB_SRC_INCR_INCREMENTING |              /* The source address is incremented */
			DMAC_CTRLB_DST_INCR_INCREMENTING;               /* The destination address is incremented */
	desc[1].ul_descriptor_addr = (uint32_t) &desc[2];       /* Pointer to next descriptor */

	desc[2].ul_source_addr = (uint32_t) g_dma_buf[2];
	desc[2].ul_destination_addr = (uint32_t) g_dma_buf[5];
	desc[2].ul_ctrlA = DMAC_CTRLA_BTSIZE(DMA_BUF_SIZE) |    /* Set Buffer Transfer Size */
			DMAC_CTRLA_SRC_WIDTH_WORD |                     /* Source transfer size is set to 32-bit width */
			DMAC_CTRLA_DST_WIDTH_WORD;                      /* Destination transfer size is set to 32-bit width */
	desc[2].ul_ctrlB = DMAC_CTRLB_SRC_DSCR_FETCH_FROM_MEM | /* Descriptor is fetched from the memory */
			DMAC_CTRLB_DST_DSCR_FETCH_FROM_MEM |            /* Descriptor is fetched from the memory */
			DMAC_CTRLB_FC_MEM2MEM_DMA_FC |                  /* Memory-to-Memory Transfer */
			DMAC_CTRLB_SRC_INCR_INCREMENTING |              /* The source address is incremented */
			DMAC_CTRLB_DST_INCR_INCREMENTING;               /* The destination address is incremented */
	desc[2].ul_descriptor_addr = 0;                         /* The end of LLI */

	dmac_channel_multi_buf_transfer_init(DMAC, DMA_CH, &desc[0]);

	/* Set interrupt */
	NVIC_EnableIRQ(DMAC_IRQn);
	dmac_enable_interrupt(DMAC, (DMAC_EBCIER_CBTC0 << DMA_CH));

	/* Start DMA transfer and wait for finish */
	g_xfer_done = 0;
	dmac_channel_enable(DMAC, DMA_CH);
	while (!g_xfer_done) {
	}

	/* Verify the transferred data */
	for (i = 0; i < DMA_BUF_SIZE; i++) {
		test_assert_true(test,
				(g_dma_buf[0][i] == g_dma_buf[3][i]) &&
				(g_dma_buf[1][i] == g_dma_buf[4][i]) &&
				(g_dma_buf[2][i] == g_dma_buf[5][i]),
				"Data comparison failed.");
	}
}

/**
 * \brief DMAC interrupt handler.
 */
void DMAC_Handler(void)
{
	uint32_t dma_status;

	dma_status = dmac_get_status(DMAC);

	if (dma_status & (DMAC_EBCIER_CBTC0 << DMA_CH)) {
		g_xfer_done = 1;
	}
}

/**
 * \brief Run DMAC driver unit tests.
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

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_TEST_UART, &uart_serial_options);

	/* Define all the test cases */
	DEFINE_TEST_CASE(single_buf_xfer_test, NULL, run_single_buf_xfer_test,
			NULL, "Test DMA single buffer transfer");

	DEFINE_TEST_CASE(multi_buf_xfer_test, NULL, run_multi_buf_xfer_test,
			NULL, "Test DMA multiple buffer transfer");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(dmac_tests) = {
		&single_buf_xfer_test,
		&multi_buf_xfer_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(dmac_suite, dmac_tests, "SAM DMAC driver test suite");

	/* Run all tests in the test suite */
	test_suite_run(&dmac_suite);

	while (1) {
		/* Busy-wait forever */
	}
}
