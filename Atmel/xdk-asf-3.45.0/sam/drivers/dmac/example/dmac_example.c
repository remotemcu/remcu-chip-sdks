/**
 * \file
 *
 * \brief SAM4E Direct Memory Access Controller driver example.
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

#include <asf.h>
#include <conf_board.h>
#include <conf_clock.h>

//! [dmac_define_channel]
/** DMA channel used in this example. */
#define DMA_CH 0
//! [dmac_define_channel]

//! [dmac_define_buffer]
/** DMA buffer size. */
#define DMA_BUF_SIZE    32

/** DMA buffer. */
uint32_t g_dma_buf[6][DMA_BUF_SIZE];
//! [dmac_define_buffer]

/* DMA transfer done flag. */
volatile uint32_t g_xfer_done = 0;

/**
 * \brief Configure the console UART.
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
 * \brief Test DMA single buffer transfer with polling mode.
 */
static void test_single_buf_xfer(void)
{
	//! [dmac_define_vars]
	uint32_t i;
	uint32_t cfg;
	dma_transfer_descriptor_t desc;
	//! [dmac_define_vars]
	
	printf("\n\rTest single buffer transfer...\n\r");

	//! [dmac_define_prepare_buffer]
	/** Initialize DMA buffer */
	for (i = 0; i < DMA_BUF_SIZE; i++) {
		g_dma_buf[0][i] = i;
		g_dma_buf[1][i] = 0;
	}
	//! [dmac_define_prepare_buffer]

	/* Initialize and enable DMA controller */
	//! [dmac_init_clock]
	pmc_enable_periph_clk(ID_DMAC);
	//! [dmac_init_clock]
	
	//! [dmac_init_module]
	dmac_init(DMAC);
	//! [dmac_init_module]
	
	//! [dmac_set_priority]
	dmac_set_priority_mode(DMAC, DMAC_PRIORITY_ROUND_ROBIN);
	//! [dmac_set_priority]
	
	//! [dmac_enable_module]	
	dmac_enable(DMAC);
	//! [dmac_enable_module]	

	//! [dmac_configure_channel]	
	/** Set for channel configuration register */
	cfg = DMAC_CFG_SOD_ENABLE |        /** Enable stop on done */
			DMAC_CFG_AHB_PROT(1) |     /** Set AHB Protection */
			DMAC_CFG_FIFOCFG_ALAP_CFG; /** FIFO Configuration */
	dmac_channel_set_configuration(DMAC, DMA_CH, cfg);
	//! [dmac_configure_channel]	

	//! [dmac_configure_for_single_transfer_1]	
	/** Initialize single buffer transfer: buffer 0 -> buffer 1 */
	desc.ul_source_addr = (uint32_t) g_dma_buf[0];
	desc.ul_destination_addr = (uint32_t) g_dma_buf[1];
	//! [dmac_configure_for_single_transfer_1]	
	
	/*
	 * Set DMA CTRLA:
	 * - Set Buffer Transfer Size
	 * - Source transfer size is set to 32-bit width
	 * - Destination transfer size is set to 32-bit width
	 */
	//! [dmac_configure_for_single_transfer_2]	
	desc.ul_ctrlA = DMAC_CTRLA_BTSIZE(DMA_BUF_SIZE) |
			DMAC_CTRLA_SRC_WIDTH_WORD |
			DMAC_CTRLA_DST_WIDTH_WORD;
	//! [dmac_configure_for_single_transfer_2]	
	
	/*
	 * Set DMA CTRLB:
	 * - Buffer Descriptor Fetch operation is disabled for the source
	 * - Buffer Descriptor Fetch operation is disabled for the destination
	 * - Memory-to-Memory Transfer
	 * - The source address is incremented
	 * - The destination address is incremented
	 */
	//! [dmac_configure_for_single_transfer_3]	
	desc.ul_ctrlB = DMAC_CTRLB_SRC_DSCR_FETCH_DISABLE |
			DMAC_CTRLB_DST_DSCR_FETCH_DISABLE |
			DMAC_CTRLB_FC_MEM2MEM_DMA_FC |
			DMAC_CTRLB_SRC_INCR_INCREMENTING |
			DMAC_CTRLB_DST_INCR_INCREMENTING;
	//! [dmac_configure_for_single_transfer_3]	
	
	/* No descriptor for single transfer */
	//! [dmac_configure_for_single_transfer_4]	
	desc.ul_descriptor_addr = 0;
	dmac_channel_single_buf_transfer_init(DMAC, DMA_CH, &desc);
	//! [dmac_configure_for_single_transfer_4]	

	/* Start DMA transfer and wait for finish */
	//! [dmac_start_transfer]	
	dmac_channel_enable(DMAC, DMA_CH);
	//! [dmac_start_transfer]	
	//! [dmac_wait_for_done]		
	while (!dmac_channel_is_transfer_done(DMAC, DMA_CH)) {
	}
	//! [dmac_wait_for_done]		

	/* Verify the transferred data */
	for (i = 0; i < DMA_BUF_SIZE; i++) {
		if (g_dma_buf[0][i] != g_dma_buf[1][i]) {
			printf("> Test NG.\n\r");
			while (1) {
			}
		}
	}
	printf("> Test OK\n\r");
}

/**
 * \brief Test DMA multiple buffer transfer with interrupt mode.
 */
static void test_multi_buf_xfer(void)
{
	uint32_t i;
	uint32_t cfg;
	dma_transfer_descriptor_t desc[3];

	printf("\n\rTest multiple buffer transfer...\n\r");

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
	/*
	 * Set DMA CTRLA:
	 * - Set Buffer Transfer Size
	 * - Source transfer size is set to 32-bit width
	 * - Destination transfer size is set to 32-bit width
	 */
	desc[0].ul_ctrlA = DMAC_CTRLA_BTSIZE(DMA_BUF_SIZE) |
			DMAC_CTRLA_SRC_WIDTH_WORD |
			DMAC_CTRLA_DST_WIDTH_WORD;
	/*
	 * Set DMA CTRLB:
	 * - Descriptor is fetched from the memory
	 * - Descriptor is fetched from the memory
	 * - Memory-to-Memory Transfer
	 * - The source address is incremented
	 * - The destination address is incremented
	 */
	desc[0].ul_ctrlB = DMAC_CTRLB_SRC_DSCR_FETCH_FROM_MEM |
			DMAC_CTRLB_DST_DSCR_FETCH_FROM_MEM |
			DMAC_CTRLB_FC_MEM2MEM_DMA_FC |
			DMAC_CTRLB_SRC_INCR_INCREMENTING |
			DMAC_CTRLB_DST_INCR_INCREMENTING;
	/* Pointer to next descriptor */
	desc[0].ul_descriptor_addr = (uint32_t) &desc[1];

	desc[1].ul_source_addr = (uint32_t) g_dma_buf[1];
	desc[1].ul_destination_addr = (uint32_t) g_dma_buf[4];
	/*
	 * Set DMA CTRLA:
	 * - Set Buffer Transfer Size
	 * - Source transfer size is set to 32-bit width
	 * - Destination transfer size is set to 32-bit width
	 */
	desc[1].ul_ctrlA = DMAC_CTRLA_BTSIZE(DMA_BUF_SIZE) |
			DMAC_CTRLA_SRC_WIDTH_WORD |
			DMAC_CTRLA_DST_WIDTH_WORD;
	/*
	 * Set DMA CTRLB:
	 * - Source descriptor is fetched from the memory
	 * - Destination descriptor is fetched from the memory
	 * - Memory-to-Memory Transfer
	 * - The source address is incremented
	 * - The destination address is incremented
	 */
	desc[1].ul_ctrlB = DMAC_CTRLB_SRC_DSCR_FETCH_FROM_MEM |
			DMAC_CTRLB_DST_DSCR_FETCH_FROM_MEM |
			DMAC_CTRLB_FC_MEM2MEM_DMA_FC |
			DMAC_CTRLB_SRC_INCR_INCREMENTING |
			DMAC_CTRLB_DST_INCR_INCREMENTING;
	/* Pointer to next descriptor */
	desc[1].ul_descriptor_addr = (uint32_t) &desc[2];

	desc[2].ul_source_addr = (uint32_t) g_dma_buf[2];
	desc[2].ul_destination_addr = (uint32_t) g_dma_buf[5];
	/*
	 * Set Buffer Transfer Size
	 * Source transfer size is set to 32-bit width
	 * Destination transfer size is set to 32-bit width
	 */
	desc[2].ul_ctrlA = DMAC_CTRLA_BTSIZE(DMA_BUF_SIZE) |
			DMAC_CTRLA_SRC_WIDTH_WORD |
			DMAC_CTRLA_DST_WIDTH_WORD;
	/*
	 * Set DMA CTRLB:
	 * - Source descriptor is fetched from the memory
	 * - Destination descriptor is fetched from the memory
	 * - Memory-to-Memory Transfer
	 * - The source address is incremented
	 * - The destination address is incremented
	 */
	desc[2].ul_ctrlB = DMAC_CTRLB_SRC_DSCR_FETCH_FROM_MEM |
			DMAC_CTRLB_DST_DSCR_FETCH_FROM_MEM |
			DMAC_CTRLB_FC_MEM2MEM_DMA_FC |
			DMAC_CTRLB_SRC_INCR_INCREMENTING |
			DMAC_CTRLB_DST_INCR_INCREMENTING;
	/* The end of LLI */
	desc[2].ul_descriptor_addr = 0;

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
		if ((g_dma_buf[0][i] != g_dma_buf[3][i]) ||
				(g_dma_buf[1][i] != g_dma_buf[4][i]) ||
				(g_dma_buf[2][i] != g_dma_buf[5][i])) {
			printf("> Test NG.\n\r");
			while (1) {
			}
		}
	}
	printf("> Test OK.\n\r");
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
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Initialize the system */
	sysclk_init();
	board_init();

	/* Configure console UART */
	configure_console();

	/* Output example information */
	printf("-- DMAC Example --\n\r");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	/* Test DMA single buffer transfer */
	test_single_buf_xfer();

	/* Test DMA multiple buffer transfer */
	test_multi_buf_xfer();

	while (1) {
	}
}
