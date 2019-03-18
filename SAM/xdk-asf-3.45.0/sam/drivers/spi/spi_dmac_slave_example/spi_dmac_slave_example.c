/**
 * \file
 *
 * \brief Serial Peripheral Interface (SPI) DMA slave example for SAM.
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
 * \mainpage SPI Example
 *
 * \par Purpose
 *
 * This example uses Serial Peripheral Interface (SPI) of one EK board in slave mode to
 * communicate with another EK board's SPI in master mode.
 *
 * \par Requirements
 *
 * This package can be used with two SAM evaluation kit boards that support DMAC operation.
 * Please connect the SPI pins from one board to another.
 *        - <b>SAM EK board(MASTER)--SAM EK board(SLAVE)</b>
 *        - NPCS0--NPCS0
 *        - MISO--MISO
 *        - MOSI--MOSI
 *        - SPCK--SPCK
 *
 * \par Descriptions
 *
 * This example shows control of the SPI, and how to configure and transfer data with SPI.
 * The user needs to configure the SPI as slave or master mode according to UART inputs.
 *
 * The code can be roughly broken down as follows:
 * <ul>
 * <li> 't' will start SPI transfer test.
 * <ol>
 * <li>Configure SPI as master, and set up SPI clock.
 * <li>Send 4-byte CMD_TEST to indicate the start of test.
 * <li>Send several 64-byte blocks, and after transmitting the next block, the content of the last block is returned and checked.
 * <li>Send CMD_STATUS command and wait for the status reports from slave.
 * <li>Send CMD_END command to indicate the end of test.
 * </ol>
 * <li>Set up SPI clock for master.
 * </ul>
 *
 * \par Usage
 *
 * -# Compile the application.
 * -# Connect the UART port of the evaluation board to the computer and open
 * it in a terminal.
 *    - Settings: 115200 bauds, 8 bits, 1 stop bit, no parity, no flow control.
 * -# Download the program into the evaluation board and run it.
 * -# Upon startup, the application will output the following line on the terminal:
 *    \code
	-- Spi DMA Slave Example --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 * -# The following traces detail operations on the SPI example, displaying success
 *    or error messages depending on the results of the commands.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */


#include <asf.h>
#include "conf_example.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/* Chip select. */
#define SPI_CHIP_SEL           0
/* Clock polarity. */
#define SPI_CLK_POLARITY       0
/* Clock phase. */
#define SPI_CLK_PHASE          0
/* Delay before SPCK. */
#define SPI_DLYBS              0x08
/* Delay between consecutive transfers. */
#define SPI_DLYBCT             0x10

/* SPI slave states for this example. */
#define SLAVE_STATE_IDLE           0
#define SLAVE_STATE_TEST           1
#define SLAVE_STATE_DATA           2
#define SLAVE_STATE_STATUS_ENTRY   3
#define SLAVE_STATE_STATUS         4
#define SLAVE_STATE_END            5

/* Communication commands for this example. */
#define CMD_TEST               0x10101010
#define CMD_DATA               0x29380000
#define CMD_STATUS             0x68390384
#define CMD_END                0x68390484
#define RC_SYN                 0x55AA55AA
#define RC_RDY                 0x12345678

/* Slave data mask. */
#define CMD_DATA_MSK            0xFFFF0000

/* Slave data block mask. */
#define DATA_BLOCK_MSK          0x0000FFFF

/* Number of commands logged in status. */
#define NB_STATUS_CMD           20

/* Number of SPI clock configurations. */
#define NUM_SPCK_CONFIGURATIONS 4

/* SPI Communicate buffer size. */
#define COMM_BUFFER_SIZE        64

/* UART baudrate. */
#define UART_BAUDRATE           115200

/* Data block number. */
#define MAX_DATA_BLOCK_NUMBER   4

/* Max retry times. */
#define MAX_RETRY               4

/** DMAC receive channel of master. */
#define BOARD_SPI_DMAC_RX_CH    0
/** DMAC transmit channel of master. */
#define BOARD_SPI_DMAC_TX_CH    1

/** DMAC Channel HW Interface Number for SPI. */
#define SPI_TX_IDX              1
#define SPI_RX_IDX              2

/** SPI working role in the example. */
#define SPI_MASTER              0
#define SPI_SLAVE               1

#define STRING_EOL    "\r"
#define STRING_HEADER "-- Spi DMA Slave Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/* Status block. */
struct status_block_t {
	/** Number of data blocks. */
	uint32_t ul_total_block_number;
	/** Number of SPI commands (including data blocks). */
	uint32_t ul_total_command_number;
	/** Command list. */
	uint32_t ul_cmd_list[NB_STATUS_CMD];
};

/* SPI clock setting (Hz). */
uint32_t g_ul_spi_clock;

/* Slave transfer command. */
uint32_t g_ul_slave_cmd = RC_SYN;

/* Master transfer command. */
uint32_t g_ul_master_cmd;

/* Current SPI state. */
uint32_t g_ul_spi_state = 0;

/* 64 bytes data buffer for SPI transfer and receive. */
uint8_t g_uc_spi_buffer[COMM_BUFFER_SIZE];

/* SPI Status. */
struct status_block_t spi_status;

uint32_t g_ul_test_block_number;

/* Master receive status. */
volatile uint32_t g_ul_master_recv_done;

/* SPI module working role. */
uint8_t g_uc_role;

/* SPI clock configuration. */
const uint32_t g_ul_clock_configurations[] =
		{ 500000, 1000000, 2000000, 5000000 };

/**
 * \brief Display the user menu on the terminal.
 */
static void display_menu(void)
{
	uint32_t i;

	puts("\n\rMenu :\n\r" "------\r");

	for (i = 0; i < NUM_SPCK_CONFIGURATIONS; i++) {
		printf("  %u: Set SPCK = %7u Hz\n\r", i,
				g_ul_clock_configurations[i]);
	}
	if (SPI_MASTER == g_uc_role) {
		puts("SPI works in master mode.\n\r");
	} else {
		puts("SPI works in slave mode.\n\r");
	}
		
	puts("  s: Configure SPI as slave\n\r"
			"  m: Configure SPI as master\n\r"
			"  t: Perform communication sequence\n\r"
			"  h: Display this menu again\n\r\r");
}

/**
 * \brief Set SPI slave transfer.
 *
 * \param p_buf   Pointer to buffer to transfer.
 * \param ul_size Size of the buffer.
 */
static void spi_slave_transfer(void *p_buf, uint32_t ul_size)
{
	dma_transfer_descriptor_t dmac_trans;

	dmac_channel_disable(DMAC, BOARD_SPI_DMAC_TX_CH);
	dmac_trans.ul_source_addr = (uint32_t) p_buf;
	dmac_trans.ul_destination_addr = (uint32_t) & SPI_SLAVE_BASE->SPI_TDR;
	dmac_trans.ul_ctrlA = ul_size | DMAC_CTRLA_SRC_WIDTH_BYTE |
			DMAC_CTRLA_DST_WIDTH_BYTE;
	dmac_trans.ul_ctrlB = DMAC_CTRLB_SRC_DSCR | DMAC_CTRLB_DST_DSCR |
			DMAC_CTRLB_FC_MEM2PER_DMA_FC |
			DMAC_CTRLB_SRC_INCR_INCREMENTING |
			DMAC_CTRLB_DST_INCR_FIXED;
	dmac_trans.ul_descriptor_addr = 0;
	dmac_channel_single_buf_transfer_init(DMAC, BOARD_SPI_DMAC_TX_CH,
			&dmac_trans);
	dmac_channel_enable(DMAC, BOARD_SPI_DMAC_TX_CH);

	dmac_channel_disable(DMAC, BOARD_SPI_DMAC_RX_CH);
	dmac_trans.ul_source_addr = (uint32_t) & SPI_SLAVE_BASE->SPI_RDR;
	dmac_trans.ul_destination_addr = (uint32_t) p_buf;
	dmac_trans.ul_ctrlA = ul_size | DMAC_CTRLA_SRC_WIDTH_BYTE |
			DMAC_CTRLA_DST_WIDTH_BYTE;
	dmac_trans.ul_ctrlB = DMAC_CTRLB_SRC_DSCR | DMAC_CTRLB_DST_DSCR |
			DMAC_CTRLB_FC_PER2MEM_DMA_FC |
			DMAC_CTRLB_SRC_INCR_FIXED |
			DMAC_CTRLB_DST_INCR_INCREMENTING;
	dmac_trans.ul_descriptor_addr = 0;
	dmac_channel_single_buf_transfer_init(DMAC, BOARD_SPI_DMAC_RX_CH,
			(dma_transfer_descriptor_t *) & dmac_trans);
	dmac_channel_enable(DMAC, BOARD_SPI_DMAC_RX_CH);
}

/**
 * \brief  SPI command block process.
 */
static void spi_slave_command_process(void)
{
	if (g_ul_slave_cmd == CMD_END) {
		g_ul_spi_state = SLAVE_STATE_IDLE;
		spi_status.ul_total_block_number = 0;
		spi_status.ul_total_command_number = 0;
	} else {
		switch (g_ul_spi_state) {
		case SLAVE_STATE_IDLE:
			/* Only CMD_TEST accepted. */
			if (g_ul_slave_cmd == CMD_TEST) {
				g_ul_spi_state = SLAVE_STATE_TEST;
			}
			break;

		case SLAVE_STATE_TEST:
			/* Only CMD_DATA accepted. */
			if ((g_ul_slave_cmd & CMD_DATA_MSK) == CMD_DATA) {
				g_ul_spi_state = SLAVE_STATE_DATA;
				g_ul_test_block_number =
						g_ul_slave_cmd & DATA_BLOCK_MSK;
			}
			break;

		case SLAVE_STATE_DATA:
			spi_status.ul_total_block_number++;

			if (spi_status.ul_total_block_number ==
					g_ul_test_block_number) {
				g_ul_spi_state = SLAVE_STATE_STATUS_ENTRY;
			}
			break;

		case SLAVE_STATE_STATUS_ENTRY:
			g_ul_spi_state = SLAVE_STATE_STATUS;
			break;

		case SLAVE_STATE_END:
			break;
		}
	}
}

/**
 * \brief  Start waiting new command.
 */
static void spi_slave_new_command(void)
{
	switch (g_ul_spi_state) {
	case SLAVE_STATE_IDLE:
	case SLAVE_STATE_END:
		g_ul_slave_cmd = RC_SYN;
		spi_slave_transfer(&g_ul_slave_cmd, sizeof(g_ul_slave_cmd));
		break;

	case SLAVE_STATE_TEST:
		g_ul_slave_cmd = RC_RDY;
		spi_slave_transfer(&g_ul_slave_cmd, sizeof(g_ul_slave_cmd));
		break;

	case SLAVE_STATE_DATA:
		if (spi_status.ul_total_block_number < g_ul_test_block_number) {
			spi_slave_transfer(g_uc_spi_buffer, COMM_BUFFER_SIZE);
		}
		break;

	case SLAVE_STATE_STATUS_ENTRY:
		g_ul_slave_cmd = RC_RDY;
		spi_slave_transfer(&g_ul_slave_cmd, sizeof(g_ul_slave_cmd));
		g_ul_spi_state = SLAVE_STATE_STATUS;
		break;

	case SLAVE_STATE_STATUS:
		g_ul_slave_cmd = RC_SYN;
		spi_slave_transfer(&spi_status, sizeof(struct status_block_t));
		g_ul_spi_state = SLAVE_STATE_END;
		break;
	}
}

/**
 * \brief Interrupt handler for the DMAC.
 */
void DMAC_Handler(void)
{
	static uint32_t ul_status;

	ul_status = dmac_get_status(DMAC);
	if (ul_status & (1 << BOARD_SPI_DMAC_RX_CH)) {
		if (SPI_MASTER == g_uc_role) {
			g_ul_master_recv_done = 1;
		} else {
			spi_slave_command_process();
			if (g_ul_slave_cmd != CMD_END) {
				spi_status.ul_cmd_list[spi_status.ul_total_command_number] =
						g_ul_slave_cmd;
				spi_status.ul_total_command_number++;
			}
			spi_slave_new_command();
		}
	}
}

/**
 * \brief Initialize SPI as slave.
 */
static void spi_slave_initialize(void)
{
	/* Reset status. */
	spi_status.ul_total_block_number = 0;
	spi_status.ul_total_command_number = 0;
	for (uint32_t i = 0; i < NB_STATUS_CMD; i++) {
		spi_status.ul_cmd_list[i] = 0;
	}
	g_ul_spi_state = SLAVE_STATE_IDLE;
	g_ul_slave_cmd = RC_SYN;
	g_uc_role = SPI_SLAVE;

	dmac_channel_disable(DMAC, BOARD_SPI_DMAC_TX_CH);
	dmac_channel_disable(DMAC, BOARD_SPI_DMAC_RX_CH);
	puts("-I- Initialize SPI as slave \r");
	/* Configure an SPI peripheral. */
	pmc_enable_periph_clk(SPI_ID);
	spi_disable(SPI_SLAVE_BASE);
	spi_reset(SPI_SLAVE_BASE);
	spi_set_slave_mode(SPI_SLAVE_BASE);
	spi_disable_mode_fault_detect(SPI_SLAVE_BASE);
	spi_set_peripheral_chip_select_value(SPI_SLAVE_BASE,
		spi_get_pcs(SPI_CHIP_SEL));
	spi_set_clock_polarity(SPI_SLAVE_BASE, SPI_CHIP_SEL, SPI_CLK_POLARITY);
	spi_set_clock_phase(SPI_SLAVE_BASE, SPI_CHIP_SEL, SPI_CLK_PHASE);
	spi_set_bits_per_transfer(SPI_SLAVE_BASE, SPI_CHIP_SEL,
			SPI_CSR_BITS_8_BIT);
	spi_enable(SPI_SLAVE_BASE);

	/* Start waiting command. */
	spi_slave_transfer(&g_ul_slave_cmd, sizeof(g_ul_slave_cmd));
}

/**
 * \brief Initialize SPI as master.
 */
static void spi_master_initialize(void)
{
	uint32_t ul_sysclk;

	g_ul_spi_clock = g_ul_clock_configurations[0];
	g_uc_role = SPI_MASTER;
	puts("-I- Initialize SPI as master\r");

	dmac_channel_disable(DMAC, BOARD_SPI_DMAC_TX_CH);
	dmac_channel_disable(DMAC, BOARD_SPI_DMAC_RX_CH);
	/* Configure an SPI peripheral. */
	pmc_enable_periph_clk(SPI_ID);
	spi_disable(SPI_MASTER_BASE);
	spi_reset(SPI_MASTER_BASE);
	spi_set_lastxfer(SPI_MASTER_BASE);
	spi_set_master_mode(SPI_MASTER_BASE);
	spi_disable_mode_fault_detect(SPI_MASTER_BASE);
	spi_set_peripheral_chip_select_value(SPI_MASTER_BASE,
		spi_get_pcs(SPI_CHIP_SEL));
	spi_set_clock_polarity(SPI_MASTER_BASE, SPI_CHIP_SEL, SPI_CLK_POLARITY);
	spi_set_clock_phase(SPI_MASTER_BASE, SPI_CHIP_SEL, SPI_CLK_PHASE);
	spi_set_bits_per_transfer(SPI_MASTER_BASE, SPI_CHIP_SEL,
			SPI_CSR_BITS_8_BIT);
	ul_sysclk = sysclk_get_peripheral_hz();
	spi_set_baudrate_div(SPI_MASTER_BASE, SPI_CHIP_SEL,
			(ul_sysclk / g_ul_spi_clock));
	spi_set_transfer_delay(SPI_MASTER_BASE, SPI_CHIP_SEL, SPI_DLYBS,
			SPI_DLYBCT);
	spi_enable(SPI_MASTER_BASE);
}

/**
 * \brief Set the specified SPI clock configuration.
 *
 * \param configuration  Index of the configuration to set.
 */
static void spi_set_clock_configuration(uint8_t configuration)
{
	g_ul_spi_clock = g_ul_clock_configurations[configuration];
	printf("Select SPI clock as #%u ... \n\r", g_ul_spi_clock);
}

/**
 * \brief Perform SPI master transfer.
 *
 * \param pbuf    Pointer to buffer to transfer.
 * \param ul_size Size of the buffer.
 */
static void spi_master_transfer(void *p_buf, uint32_t ul_size)
{
	dma_transfer_descriptor_t dmac_trans;

	dmac_channel_disable(DMAC, BOARD_SPI_DMAC_TX_CH);
	dmac_trans.ul_source_addr = (uint32_t) p_buf;
	dmac_trans.ul_destination_addr = (uint32_t) & SPI_MASTER_BASE->SPI_TDR;
	dmac_trans.ul_ctrlA = ul_size | DMAC_CTRLA_SRC_WIDTH_BYTE |
			DMAC_CTRLA_DST_WIDTH_BYTE;
	dmac_trans.ul_ctrlB = DMAC_CTRLB_SRC_DSCR | DMAC_CTRLB_DST_DSCR |
			DMAC_CTRLB_FC_MEM2PER_DMA_FC |
			DMAC_CTRLB_SRC_INCR_INCREMENTING |
			DMAC_CTRLB_DST_INCR_FIXED;
	dmac_trans.ul_descriptor_addr = 0;
	dmac_channel_single_buf_transfer_init(DMAC, BOARD_SPI_DMAC_TX_CH,
			(dma_transfer_descriptor_t *) & dmac_trans);

	dmac_channel_disable(DMAC, BOARD_SPI_DMAC_RX_CH);
	dmac_trans.ul_source_addr = (uint32_t) & SPI_MASTER_BASE->SPI_RDR;
	dmac_trans.ul_destination_addr = (uint32_t) p_buf;
	dmac_trans.ul_ctrlA = ul_size | DMAC_CTRLA_SRC_WIDTH_BYTE |
			DMAC_CTRLA_DST_WIDTH_BYTE;
	dmac_trans.ul_ctrlB = DMAC_CTRLB_SRC_DSCR | DMAC_CTRLB_DST_DSCR |
			DMAC_CTRLB_FC_PER2MEM_DMA_FC |
			DMAC_CTRLB_SRC_INCR_FIXED |
			DMAC_CTRLB_DST_INCR_INCREMENTING;
	dmac_trans.ul_descriptor_addr = 0;
	dmac_channel_single_buf_transfer_init(DMAC, BOARD_SPI_DMAC_RX_CH,
			&dmac_trans);

	dmac_channel_enable(DMAC, BOARD_SPI_DMAC_TX_CH);
	dmac_channel_enable(DMAC, BOARD_SPI_DMAC_RX_CH);
}

/**
 * \brief Start SPI transfer test.
 */
static void spi_master_go(void)
{
	uint32_t ul_block;
	uint32_t i;

	/* Send CMD_TEST to indicate the start of test, and device shall return RC_RDY. */
	while (1) {
		g_ul_master_cmd = CMD_TEST;
		puts("-> Master sending CMD_TEST... \r");
		g_ul_master_recv_done = 0;
		spi_master_transfer(&g_ul_master_cmd, sizeof(g_ul_master_cmd));
		while (!g_ul_master_recv_done) {
		}
		g_ul_master_recv_done = 0;
		if (g_ul_master_cmd == RC_RDY) {
			puts("   <- Slave response RC_SYN, RC_RDY \r");
			break;
		}
		if (g_ul_master_cmd != RC_SYN) {
			printf("-E- Response unexpected: 0x%x \n\r",
					g_ul_master_cmd);
			return;
		}
	}
	/* Send CMD_DATA with 4 blocks (64 bytes per page). */
	puts("-> Master sending CMD_DATA... \r");
	g_ul_master_cmd = CMD_DATA | MAX_DATA_BLOCK_NUMBER;
	spi_master_transfer(&g_ul_master_cmd, sizeof(g_ul_master_cmd));
	while (!g_ul_master_recv_done) {
	}
	g_ul_master_recv_done = 0;
	puts("                                <---- Slave response RC_RDY \r");
	for (ul_block = 0; ul_block < MAX_DATA_BLOCK_NUMBER; ul_block++) {
		for (i = 0; i < COMM_BUFFER_SIZE; i++) {
			g_uc_spi_buffer[i] = ul_block;
		}
		printf("-> Master sending block %u ... \n\r", ul_block);
		spi_master_transfer(g_uc_spi_buffer, COMM_BUFFER_SIZE);
		while (!g_ul_master_recv_done) {
		}
		g_ul_master_recv_done = 0;
		if (ul_block) {
			for (i = 0; i < COMM_BUFFER_SIZE; i++) {
				if (g_uc_spi_buffer[i] != (ul_block - 1)) {
					break;
				}
			}
			if (i < COMM_BUFFER_SIZE) {
				printf("-E- block %u contains unexpected data \n\r", ul_block);
			} else {
				printf("   <- Slave response last block %x \n\r", (ul_block - 1));
			}
		}
	}

	for (i = 0; i < MAX_RETRY; i++) {
		g_ul_master_cmd = CMD_STATUS;
		puts("-> Master sending CMD_STATUS... \r");
		spi_master_transfer(&g_ul_master_cmd, sizeof(g_ul_master_cmd));
		while (!g_ul_master_recv_done) {
		}
		g_ul_master_recv_done = 0;
		if (g_ul_master_cmd == RC_RDY) {
			puts("   <- Slave response RC_RDY \r");
			break;
		}
	}
	if (i >= MAX_RETRY) {
		puts("   <- Slave no response \r");
		return;
	}

	puts("-> Master request slave status... \r");
	spi_master_transfer(&spi_status, sizeof(struct status_block_t));
	while (!g_ul_master_recv_done) {
	}
	g_ul_master_recv_done = 0;

	puts("   <- Slave reports status...\r");
	printf("-I- Received  %u commands:",
			spi_status.ul_total_command_number);

	for (i = 0; i < spi_status.ul_total_command_number; i++) {
		printf(" 0x%08x", spi_status.ul_cmd_list[i]);
	}
	printf(" \n\r-I- Received  %u data blocks \n\r",
			spi_status.ul_total_block_number);

	for (i = 0; i < MAX_RETRY; i++) {
		puts("-> Master sending CMD_END... \r");
		g_ul_master_cmd = CMD_END;
		spi_master_transfer(&g_ul_master_cmd, sizeof(g_ul_master_cmd));
		while (!g_ul_master_recv_done) {
		}
		g_ul_master_recv_done = 0;
		if (g_ul_master_cmd == RC_SYN) {
			puts("   <- Slave response RC_SYN \r");
			break;
		}
	}

	if (i >= MAX_RETRY) {
		puts("   <- Slave no response \r");
	}

	puts("\r");
	puts("SPI transfer test is finished! \r");
}

/**
 *  \brief Configure the Console UART.
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
 * \brief DMAC driver configuration.
 */
static void configure_dmac(void)
{
	uint32_t ul_cfg;

	/* Initialize and enable DMA controller. */
	pmc_enable_periph_clk(ID_DMAC);
	dmac_init(DMAC);
	dmac_set_priority_mode(DMAC, DMAC_PRIORITY_ROUND_ROBIN);
	dmac_enable(DMAC);

	/* Configure DMA RX channel. */
	ul_cfg = 0;
	ul_cfg |= DMAC_CFG_SRC_PER(SPI_RX_IDX) |
			DMAC_CFG_SRC_H2SEL |
			DMAC_CFG_SOD | DMAC_CFG_FIFOCFG_ALAP_CFG;
	dmac_channel_set_configuration(DMAC, BOARD_SPI_DMAC_RX_CH, ul_cfg);

	/* Configure DMA TX channel. */
	ul_cfg = 0;
	ul_cfg |= DMAC_CFG_DST_PER(SPI_TX_IDX) |
			DMAC_CFG_DST_H2SEL |
			DMAC_CFG_SOD | DMAC_CFG_FIFOCFG_ALAP_CFG;
	dmac_channel_set_configuration(DMAC, BOARD_SPI_DMAC_TX_CH, ul_cfg);

	/* Enable receive channel interrupt for DMAC. */
	NVIC_EnableIRQ(DMAC_IRQn);
	dmac_enable_interrupt(DMAC, (1 << BOARD_SPI_DMAC_RX_CH));
}

/**
 * \brief Application entry point for spi_slave example.
 *
 * \return Unused (ANSI-C compatibility).
 */
uint32_t main(void)
{
	uint8_t uc_key;

	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	/* Initialize the console UART. */
	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);

	/* Configure DMAC. */
	configure_dmac();

	/* Initialize the SPI as slave. */
	spi_slave_initialize();

	/* Display menu. */
	display_menu();

	while (1) {
		while (uart_read(CONSOLE_UART, &uc_key));

		switch (uc_key) {
		case 's':
			spi_slave_initialize();
			break;

		case 'm':
			spi_master_initialize();
			break;

		case 'h':
			display_menu();
			break;

		case 't':
			spi_master_go();
			break;

		default:
			/* Set Clock configuration #n. */
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
