/**
 * \file
 *
 * \brief Serial Peripheral Interface (SPI) XDMAC example for SAMV71/SAME70.
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

/**
 * \mainpage SPI Example
 *
 * \par Purpose
 *
 * This example uses Serial Peripheral Interface (SPI) of samv71_xplained_ultra/same70_xplained_pro board in
 * slave mode to communicate with another samv71_xplained_ultra board's SPI in master mode.
 * The memory move operations through the unidirectional communication are controlled by XDMAC
 * for SPI transmitter and receiver,one XDMAC channel for transmitter and one channel for receiver.
 *
 * \par Requirements
 *
 * This package can be used with two SAM evaluation kits boards.
 * Please connect the SPI pins from one board to another.
 * \copydoc spi_example_pin_defs
 *
 * \par Descriptions
 *
 * This example shows control of the SPI, and how to configure and
 * transfer data with SPI through XDMAC. By default, example runs in SPI slave mode,
 * waiting SPI slave & COM port inputs.
 *
 * The code can be roughly broken down as follows:
 *
 * \par Usage
 *
 * -# Compile the application.
 * -# Connect the COM port of the evaluation board to the computer and open
 * it in a terminal.
 *    - Settings: 115200 bauds, 8 bits, 1 stop bit, no parity, no flow control.
 * -# Download the program into the evaluation board and run it.
 * -# Upon startup, the application will output the following line on the
 *    terminal:
 *    \code
 *	-- Spi Example  --
 *	-- xxxxxx-xx
 *	-- Compiled: xxx xx xxxx xx:xx:xx --
 *  -I- Initialize SPI as slave
 *
 *Menu
 *------
 *      0: Set SPCK =  500000 Hz
 *      1: Set SPCK = 1000000 Hz
 *      2: Set SPCK = 2000000 Hz
 *      2: Set SPCK = 5000000 Hz
 *      t: Perform SPI master
 *      h: Display menu
\endcode
 * -# The following traces detail operations on the SPI example, displaying
 *    success or error messages depending on the results of the commands.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "stdio_serial.h"
#include "conf_board.h"
#include "conf_clock.h"
#include "conf_spi_example.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/* Chip select. */
#define SPI_CHIP_SEL 0
#define SPI_CHIP_PCS spi_get_pcs(SPI_CHIP_SEL)

/* Clock polarity. */
#define SPI_CLK_POLARITY 0

/* Clock phase. */
#define SPI_CLK_PHASE 0

/* Delay before SPCK. */
#define SPI_DLYBS 0x40

/* Delay between consecutive transfers. */
#define SPI_DLYBCT 0x10

/* Number of SPI clock configurations. */
#define NUM_SPCK_CONFIGURATIONS 4

/* SPI module working role. */
uint32_t g_uc_role;

/** spi mode definition*/
#define	MASTER_MODE   0
#define SLAVE_MODE	  1

/** XDMAC channel used in this example. */
#define XDMAC_TX_CH 0
#define XDMAC_RX_CH 1

/** XDMAC channel HW Interface number for SPI0,refer to datasheet. */
#define SPI0_XDMAC_TX_CH_NUM  1
#define SPI0_XDMAC_RX_CH_NUM  2

/** XDMAC channel configuration. */
static xdmac_channel_config_t xdmac_tx_cfg,xdmac_rx_cfg;

/** The buffer size for transfer  */
#define BUFFER_SIZE          100


/* SPI clock default setting (Hz). */
static uint32_t gs_ul_spi_clock = 500000;

#define STRING_EOL    "\r"
#define STRING_HEADER "--Spi XDMAC Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL


/* SPI clock configuration. */
static const uint32_t gs_ul_clock_configurations[] =
		{ 500000, 1000000, 2000000, 5000000 };

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

uint8_t tx_buffer[] = "This is message from SPI master transferred by XDMAC test";

uint8_t rx_buffer[BUFFER_SIZE] = "0";

uint32_t g_size = sizeof(tx_buffer);


/**
 * \brief Display the user menu on the terminal.
 */
static void display_menu(void)
{
	uint32_t i;

	puts("\n\rMenu :\n\r"
			"------\r");

	for (i = 0; i < NUM_SPCK_CONFIGURATIONS; i++) {
		printf("  %u: Set SPCK = %7lu Hz\n\r", (unsigned)i,
			(unsigned long)gs_ul_clock_configurations[i]);
	}
	puts("  t: Perform SPI master\n\r"
			"  h: Display this menu again\n\r\r");
}

/**
 * \brief Initialize SPI as slave.
 */
static void spi_slave_initialize(void)
{
	g_uc_role = SLAVE_MODE;

	puts("-I- Initialize SPI as slave \r");

	/* Configure an SPI peripheral. */
	spi_enable_clock(SPI_SLAVE_BASE);
	spi_disable(SPI_SLAVE_BASE);
	spi_reset(SPI_SLAVE_BASE);
	spi_set_slave_mode(SPI_SLAVE_BASE);
	spi_disable_mode_fault_detect(SPI_SLAVE_BASE);
	spi_set_peripheral_chip_select_value(SPI_SLAVE_BASE, SPI_CHIP_PCS);
	spi_set_clock_polarity(SPI_SLAVE_BASE, SPI_CHIP_SEL, SPI_CLK_POLARITY);
	spi_set_clock_phase(SPI_SLAVE_BASE, SPI_CHIP_SEL, SPI_CLK_PHASE);
	spi_set_bits_per_transfer(SPI_SLAVE_BASE, SPI_CHIP_SEL, SPI_CSR_BITS_8_BIT);
	spi_enable(SPI_SLAVE_BASE);
}

/**
 * \brief Initialize SPI as master.
 */
static void spi_master_initialize(void)
{
	g_uc_role = MASTER_MODE;
	puts("-I- Initialize SPI as master\r");

	/* Configure an SPI peripheral. */
	spi_enable_clock(SPI_MASTER_BASE);
	spi_disable(SPI_MASTER_BASE);
	spi_reset(SPI_MASTER_BASE);
	spi_set_lastxfer(SPI_MASTER_BASE);
	spi_set_master_mode(SPI_MASTER_BASE);
	spi_disable_mode_fault_detect(SPI_MASTER_BASE);
	spi_set_peripheral_chip_select_value(SPI_MASTER_BASE, SPI_CHIP_PCS);
	spi_set_clock_polarity(SPI_MASTER_BASE, SPI_CHIP_SEL, SPI_CLK_POLARITY);
	spi_set_clock_phase(SPI_MASTER_BASE, SPI_CHIP_SEL, SPI_CLK_PHASE);
	spi_set_bits_per_transfer(SPI_MASTER_BASE, SPI_CHIP_SEL,
			SPI_CSR_BITS_8_BIT);
	spi_set_baudrate_div(SPI_MASTER_BASE, SPI_CHIP_SEL,
			(sysclk_get_peripheral_hz() / gs_ul_spi_clock));
	spi_set_transfer_delay(SPI_MASTER_BASE, SPI_CHIP_SEL, SPI_DLYBS,
			SPI_DLYBCT);
	spi_enable(SPI_MASTER_BASE);
}

/**
 *  \brief Configure the Console UART.
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
 * \brief disable XDMAC for spi and forbidden transmit and receive by XDMAC.
 *
 */
 static void spi_disable_xdmac(void)
 {
	 uint32_t xdmaint;

	xdmaint = (XDMAC_CIE_BIE |
		XDMAC_CIE_DIE   |
		XDMAC_CIE_FIE   |
		XDMAC_CIE_RBIE  |
		XDMAC_CIE_WBIE  |
		XDMAC_CIE_ROIE);

 	xdmac_channel_disable_interrupt(XDMAC, XDMAC_RX_CH, xdmaint);
 	xdmac_channel_disable(XDMAC, XDMAC_RX_CH);
 	xdmac_disable_interrupt(XDMAC, XDMAC_RX_CH);

	xdmac_channel_disable_interrupt(XDMAC, XDMAC_TX_CH, xdmaint);
	xdmac_channel_disable(XDMAC, XDMAC_TX_CH);
	xdmac_disable_interrupt(XDMAC, XDMAC_TX_CH);

	NVIC_ClearPendingIRQ(XDMAC_IRQn);
	NVIC_DisableIRQ(XDMAC_IRQn);
 }

/**
 * \brief configure xdmac for spi and ready to transfer/receive.
 *
 * \param pspi  Base address of the SPI
 */
static void spi_xdmac_configure(Spi *const pspi)
{
	uint32_t xdmaint;

	/* Initialize and enable DMA controller */
	pmc_enable_periph_clk(ID_XDMAC);

	xdmaint = (XDMAC_CIE_BIE |
		XDMAC_CIE_DIE   |
		XDMAC_CIE_FIE   |
		XDMAC_CIE_RBIE  |
		XDMAC_CIE_WBIE  |
		XDMAC_CIE_ROIE);

		/* Initialize channel config for transmitter */
	xdmac_tx_cfg.mbr_ubc = g_size;

	xdmac_tx_cfg.mbr_sa = (uint32_t)tx_buffer;
	xdmac_tx_cfg.mbr_da = (uint32_t)&(pspi->SPI_TDR);
	xdmac_tx_cfg.mbr_cfg = XDMAC_CC_TYPE_PER_TRAN |
		XDMAC_CC_MBSIZE_SINGLE |
		XDMAC_CC_DSYNC_MEM2PER |
		XDMAC_CC_CSIZE_CHK_1 |
		XDMAC_CC_DWIDTH_BYTE |
		XDMAC_CC_SIF_AHB_IF0 |
		XDMAC_CC_DIF_AHB_IF1 |
		XDMAC_CC_SAM_INCREMENTED_AM |
		XDMAC_CC_DAM_FIXED_AM |
		XDMAC_CC_PERID(SPI0_XDMAC_TX_CH_NUM);

	xdmac_tx_cfg.mbr_bc = 0;
	xdmac_tx_cfg.mbr_ds =  0;
	xdmac_tx_cfg.mbr_sus = 0;
	xdmac_tx_cfg.mbr_dus = 0;

	xdmac_configure_transfer(XDMAC, XDMAC_TX_CH, &xdmac_tx_cfg);

	xdmac_channel_set_descriptor_control(XDMAC, XDMAC_TX_CH, 0);
	xdmac_channel_enable_interrupt(XDMAC, XDMAC_TX_CH, xdmaint);
	xdmac_channel_enable(XDMAC, XDMAC_TX_CH);
	xdmac_enable_interrupt(XDMAC, XDMAC_TX_CH);

		/* Initialize channel config for receiver */
	xdmac_rx_cfg.mbr_ubc = g_size;

	xdmac_rx_cfg.mbr_da = (uint32_t)rx_buffer;

	xdmac_rx_cfg.mbr_sa = (uint32_t)&pspi->SPI_RDR;
	xdmac_rx_cfg.mbr_cfg = XDMAC_CC_TYPE_PER_TRAN |
		XDMAC_CC_MBSIZE_SINGLE |
		XDMAC_CC_DSYNC_PER2MEM |
		XDMAC_CC_CSIZE_CHK_1 |
		XDMAC_CC_DWIDTH_BYTE|
		XDMAC_CC_SIF_AHB_IF1 |
		XDMAC_CC_DIF_AHB_IF0 |
		XDMAC_CC_SAM_FIXED_AM |
		XDMAC_CC_DAM_INCREMENTED_AM |
		XDMAC_CC_PERID(SPI0_XDMAC_RX_CH_NUM);

	xdmac_rx_cfg.mbr_bc = 0;
	xdmac_tx_cfg.mbr_ds =  0;
	xdmac_rx_cfg.mbr_sus = 0;
	xdmac_rx_cfg.mbr_dus =0;

	xdmac_configure_transfer(XDMAC, XDMAC_RX_CH, &xdmac_rx_cfg);

	xdmac_channel_set_descriptor_control(XDMAC, XDMAC_RX_CH, 0);

	xdmac_channel_enable_interrupt(XDMAC, XDMAC_RX_CH, xdmaint);
	xdmac_channel_enable(XDMAC, XDMAC_RX_CH);
	xdmac_enable_interrupt(XDMAC, XDMAC_RX_CH);

	/*Enable XDMAC interrupt */
	NVIC_ClearPendingIRQ(XDMAC_IRQn);
	NVIC_SetPriority( XDMAC_IRQn ,1);
	NVIC_EnableIRQ(XDMAC_IRQn);
}

/**
 * \brief Set the specified SPI clock configuration.
 *
 * \param configuration  Index of the configuration to set.
 */
static void spi_set_clock_configuration(uint8_t configuration)
{
	spi_disable_xdmac();
	NVIC_ClearPendingIRQ(SPI_IRQn);
	NVIC_DisableIRQ(SPI_IRQn);
	NVIC_SetPriority(SPI_IRQn, 0);
	NVIC_EnableIRQ(SPI_IRQn);

	gs_ul_spi_clock = gs_ul_clock_configurations[configuration];
	printf("Setting SPI clock #%lu ... \n\r", (unsigned long)gs_ul_spi_clock);
	spi_master_initialize();
	spi_xdmac_configure(SPI0);
}

/**
 * \brief Start SPI transfer test.
 */
static void spi_master_go(void)
{
	/* Configure SPI as master, set up SPI clock. */
	spi_master_initialize();
	/** Configure xdamc for spi0 and ready to transfer*/
	spi_xdmac_configure(SPI0);
}

/**
 * \brief XDMAC interrupt handler.
 */
void XDMAC_Handler(void)
{
	uint32_t dma_status;

	dma_status = xdmac_channel_get_interrupt_status(XDMAC, XDMAC_RX_CH);
	if(	g_uc_role == SLAVE_MODE) {
		if (dma_status & XDMAC_CIS_BIS) {
			printf(" %s\n\r", rx_buffer);
			NVIC_ClearPendingIRQ(XDMAC_IRQn);
			NVIC_DisableIRQ(XDMAC_IRQn);
			/** re-configure receiver for next reception*/
			spi_xdmac_configure(SPI0);
		}
	}
	else {
		spi_disable(SPI0);
		NVIC_ClearPendingIRQ(XDMAC_IRQn);
		NVIC_DisableIRQ(XDMAC_IRQn);
		printf("master transfers completed\n\r");
	}
}
/**
 * \brief Application entry point for SPI example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t uc_key;

	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	/* Initialize the console UART. */
	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);

	/* Configure SPI interrupts for slave only. */
	NVIC_ClearPendingIRQ(SPI_IRQn);
	NVIC_DisableIRQ(SPI_IRQn);
	NVIC_SetPriority(SPI_IRQn, 0);
	NVIC_EnableIRQ(SPI_IRQn);

	spi_slave_initialize();
	spi_xdmac_configure(SPI0);

	/* Display menu. */
	display_menu();

	while (1) {
		scanf("%c", (char *)&uc_key);

		switch (uc_key) {
		case 'h':
			display_menu();
			break;

		case 't':
			spi_disable_xdmac();
			NVIC_ClearPendingIRQ(SPI_IRQn);
			NVIC_DisableIRQ(SPI_IRQn);
			NVIC_SetPriority(SPI_IRQn, 0);
			NVIC_EnableIRQ(SPI_IRQn);
			spi_master_go();
			break;

		default:
			/* Set configuration #n. */
			if ((uc_key >= '0')
					&& (uc_key <= ('0' + NUM_SPCK_CONFIGURATIONS - 1))) {
				spi_set_clock_configuration(uc_key - '0');
			}
			break;
		}
	}
}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
