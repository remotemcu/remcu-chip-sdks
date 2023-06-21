/**
 * \file
 *
 * \brief SAM Direct Memory Access Controller driver example.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

/**
 * \mainpage SAM Extensible Direct Memory Access Controller Example - memory to memory transfer
 *
 * \section Purpose
 * This example demonstrates how to configure and use XDMA controller
 * for memory to memory data buffer transfers.
 *
 * \section Requirements
 * This example can be used with SAM evaluation kits that have a XDMA
 * Controller.
 *
 * \section Description
 * This example transfers data in one RAM buffer to another RAM buffer.
 * It uses single block with multiple microblock transfer with interrupt mode.
 * After transfer is done, the transferred data will be verified.
 *
 * \section Main Files
 * - xdmac.c: Direct Memory Access Controller driver
 * - xdmac.h: Direct Memory Access Controller driver header file
 * - xdmac_example.c: Direct Memory Access Controller example application
 *
 * \section Compilation Information
 * This software is written for GNU GCC and IAR Embedded Workbench&reg;
 * for Atmel&reg;. Other compilers may or may not work.
 *
 * \section Usage
 * -# Build the program and download it into the evaluation board.
 * -# On the computer, open and configure a terminal application
 *    (e.g., HyperTerminal on Microsoft&reg; Windows&reg;) with these settings:
 *   - 115200 baud
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear.
 *    (values depend on the board and the chip used):
 *    \code
 *     -- XDMAC Example --
 *     -- xxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *
 *     > Test OK. \endcode
 */

#include <asf.h>
#include <conf_board.h>
#include <conf_clock.h>

/** Micro-block length for single transfer  */
#define MICROBLOCK_LEN       16

/** Block length for single transfer  */
#define BLOCK_LEN                 16

/** The buffer size for transfer  */
#define BUFFER_SIZE               512

/** XDMA channel used in this example. */
#define XDMA_CH 0

/** XDMA channel configuration. */
static xdmac_channel_config_t xdmac_channel_cfg;

/* DMA transfer done flag. */
volatile uint32_t g_xfer_done = 0;

COMPILER_ALIGNED(8)
static uint8_t src_buf[BUFFER_SIZE];

COMPILER_ALIGNED(8)
static uint8_t dst_buf[BUFFER_SIZE];

/** Linked list descriptor */
COMPILER_WORD_ALIGNED
static lld_view0 lld[2];

/**
 * \brief Configure the console UART.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.charlength = CONF_UART_CHAR_LENGTH,
		.paritytype = CONF_UART_PARITY,
		.stopbits = CONF_UART_STOP_BITS,
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief XDMAC interrupt handler.
 */
void XDMAC_Handler(void)
{
	uint32_t dma_status;

	dma_status = xdmac_channel_get_interrupt_status(XDMAC, XDMA_CH);

	if (dma_status & XDMAC_CIS_BIS) {
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
	uint32_t i;

	/* Initialize the system */
	sysclk_init();
	board_init();

	/* Configure console UART */
	configure_console();

	/* Output example information */
	printf("-- XDMAC Example --\n\r");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	/* Initialize and enable DMA controller */
	pmc_enable_periph_clk(ID_XDMAC);

	/*Enable XDMA interrupt */
	NVIC_ClearPendingIRQ(XDMAC_IRQn);
	NVIC_SetPriority( XDMAC_IRQn ,1);
	NVIC_EnableIRQ(XDMAC_IRQn);

	/* Initialize source and destination buffer */
	for (i = 0; i < BUFFER_SIZE; i++) {
		src_buf[i] = 0x55;
		dst_buf[i] = 0;
	}

	/* Initialize channel config */
	xdmac_channel_cfg.mbr_ubc = MICROBLOCK_LEN;
	xdmac_channel_cfg.mbr_sa = (uint32_t)src_buf;
	xdmac_channel_cfg.mbr_da = (uint32_t)dst_buf;
	xdmac_channel_cfg.mbr_cfg = XDMAC_CC_TYPE_MEM_TRAN |
		XDMAC_CC_MEMSET_NORMAL_MODE |
		XDMAC_CC_MBSIZE_SINGLE |
		XDMAC_CC_DWIDTH_BYTE |
		XDMAC_CC_SIF_AHB_IF0 |
		XDMAC_CC_DIF_AHB_IF0 |
		XDMAC_CC_SAM_INCREMENTED_AM |
		XDMAC_CC_DAM_INCREMENTED_AM;
	xdmac_channel_cfg.mbr_bc = BLOCK_LEN - 1;
	xdmac_channel_cfg.mbr_ds =  0;
	xdmac_channel_cfg.mbr_sus = 0;
	xdmac_channel_cfg.mbr_dus = 0;

	xdmac_configure_transfer(XDMAC, XDMA_CH, &xdmac_channel_cfg);

	/* Initialize linked list descriptor */
	lld[0].mbr_nda = (uint32_t)(&lld[1]);
	lld[0].mbr_ubc = XDMAC_UBC_NVIEW_NDV0 |
			XDMAC_UBC_NDE_FETCH_EN |
			XDMAC_UBC_NSEN_UPDATED |
			XDMAC_UBC_NDEN_UPDATED |
			XDMAC_UBC_UBLEN(MICROBLOCK_LEN);
	lld[0].mbr_da = (uint32_t)dst_buf;

	lld[1].mbr_nda = 0;
	lld[1].mbr_ubc = (BUFFER_SIZE - MICROBLOCK_LEN * BLOCK_LEN);
	lld[1].mbr_da = (uint32_t)dst_buf + MICROBLOCK_LEN * BLOCK_LEN;

	xdmac_channel_set_descriptor_control(XDMAC, XDMA_CH, XDMAC_CNDC_NDVIEW_NDV0 |
			XDMAC_CNDC_NDE_DSCR_FETCH_EN |
			XDMAC_CNDC_NDSUP_SRC_PARAMS_UPDATED |
			XDMAC_CNDC_NDDUP_DST_PARAMS_UPDATED);
	xdmac_channel_set_descriptor_addr(XDMAC, XDMA_CH, (uint32_t)(&lld[0]), 0);

	xdmac_enable_interrupt(XDMAC, XDMA_CH);
	xdmac_channel_enable_interrupt(XDMAC, XDMA_CH, XDMAC_CIE_BIE);
#ifdef CONF_BOARD_ENABLE_CACHE
	SCB_CleanDCache();
#endif
	xdmac_channel_enable(XDMAC, XDMA_CH);

	/* Wait transfer finish */
	while (!g_xfer_done) {
	}
#ifdef CONF_BOARD_ENABLE_CACHE
	SCB_InvalidateDCache();
#endif

	/* Verify the transferred data */
	for (i = 0; i < BUFFER_SIZE; i++) {
		if (src_buf[i] != dst_buf[i]) {
			printf("> Test Fail.\n\r");
			while (1) {
			}
		}
	}
	printf("> Test OK.\n\r");

	while (1) {
	}
}
