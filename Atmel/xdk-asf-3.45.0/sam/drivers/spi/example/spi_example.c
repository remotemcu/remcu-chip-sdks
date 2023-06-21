/**
 * \file
 *
 * \brief Serial Peripheral Interface (SPI) example for SAM.
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
 * This example uses Serial Peripheral Interface (SPI) of one EK board in
 * slave mode to communicate with another EK board's SPI in master mode.
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
 * transfer data with SPI. By default, example runs in SPI slave mode,
 * waiting SPI slave & UART inputs.
 *
 * The code can be roughly broken down as follows:
 * <ul>
 * <li> 't' will start SPI transfer test.
 * <ol>
 * <li>Configure SPI as master, and set up SPI clock.
 * <li>Send 4-byte CMD_TEST to indicate the start of test.
 * <li>Send several 64-byte blocks, and after transmitting the next block, the
 * content of the last block is returned and checked.
 * <li>Send CMD_STATUS command and wait for the status reports from slave.
 * <li>Send CMD_END command to indicate the end of test.
 * </ol>
 * <li>Setup SPI clock for master.
 * </ul>
 *
 * \par Usage
 *
 * -# Compile the application.
 * -# Connect the UART port of the evaluation board to the computer and open
 * it in a terminal.
 *    - Settings: 115200 bauds, 8 bits, 1 stop bit, no parity, no flow control.
 * -# Download the program into the evaluation board and run it.
 * -# Upon startup, the application will output the following line on the
 *    terminal:
 *    \code
	-- Spi Example  --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
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
#if (SAMG55)
#include "flexcom.h"
#endif

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

/* SPI slave states for this example. */
#define SLAVE_STATE_IDLE           0
#define SLAVE_STATE_TEST           1
#define SLAVE_STATE_DATA           2
#define SLAVE_STATE_STATUS_ENTRY   3
#define SLAVE_STATE_STATUS         4
#define SLAVE_STATE_END            5

/* SPI example commands for this example. */
/* slave test state, begin to return RC_RDY. */
#define CMD_TEST     0x10101010

/* Slave data state, begin to return last data block. */
#define CMD_DATA     0x29380000

/* Slave status state, begin to return RC_RDY + RC_STATUS. */
#define CMD_STATUS   0x68390384

/* Slave idle state, begin to return RC_SYN. */
#define CMD_END      0x68390484

/* General return value. */
#define RC_SYN       0x55AA55AA

/* Ready status. */
#define RC_RDY       0x12345678

/* Slave data mask. */
#define CMD_DATA_MSK 0xFFFF0000

/* Slave data block mask. */
#define DATA_BLOCK_MSK 0x0000FFFF

/* Number of commands logged in status. */
#define NB_STATUS_CMD   20

/* Number of SPI clock configurations. */
#define NUM_SPCK_CONFIGURATIONS 4

/* SPI Communicate buffer size. */
#define COMM_BUFFER_SIZE   64

/* UART baudrate. */
#define UART_BAUDRATE      115200

/* Data block number. */
#define MAX_DATA_BLOCK_NUMBER  4

/* Max retry times. */
#define MAX_RETRY    4

#define STRING_EOL    "\r"
#define STRING_HEADER "--Spi Example --\r\n" \
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
static uint32_t gs_ul_spi_clock = 500000;

/* Current SPI return code. */
static uint32_t gs_ul_spi_cmd = RC_SYN;

/* Current SPI state. */
static uint32_t gs_ul_spi_state = 0;

/* 64 bytes data buffer for SPI transfer and receive. */
static uint8_t gs_uc_spi_buffer[COMM_BUFFER_SIZE];

/* Pointer to transfer buffer. */
static uint8_t *gs_puc_transfer_buffer;

/* Transfer buffer index. */
static uint32_t gs_ul_transfer_index;

/* Transfer buffer length. */
static uint32_t gs_ul_transfer_length;

/* SPI Status. */
static struct status_block_t gs_spi_status;

static uint32_t gs_ul_test_block_number;

/* SPI clock configuration. */
static const uint32_t gs_ul_clock_configurations[] =
		{ 500000, 1000000, 2000000, 5000000 };


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
 * \brief Set SPI slave transfer.
 *
 * \param p_buf Pointer to buffer to transfer.
 * \param size Size of the buffer.
 */
static void spi_slave_transfer(void *p_buf, uint32_t size)
{
	gs_puc_transfer_buffer = p_buf;
	gs_ul_transfer_length = size;
	gs_ul_transfer_index = 0;
	spi_write(SPI_SLAVE_BASE, gs_puc_transfer_buffer[gs_ul_transfer_index], 0,
			0);
}

/**
 * \brief  SPI command block process.
 */
static void spi_slave_command_process(void)
{
	if (gs_ul_spi_cmd == CMD_END) {
		gs_ul_spi_state = SLAVE_STATE_IDLE;
		gs_spi_status.ul_total_block_number = 0;
		gs_spi_status.ul_total_command_number = 0;
	} else {
		switch (gs_ul_spi_state) {
		case SLAVE_STATE_IDLE:
			/* Only CMD_TEST accepted. */
			if (gs_ul_spi_cmd == CMD_TEST) {
				gs_ul_spi_state = SLAVE_STATE_TEST;
			}
			break;

		case SLAVE_STATE_TEST:
			/* Only CMD_DATA accepted. */
			if ((gs_ul_spi_cmd & CMD_DATA_MSK) == CMD_DATA) {
				gs_ul_spi_state = SLAVE_STATE_DATA;
			}
			gs_ul_test_block_number = gs_ul_spi_cmd & DATA_BLOCK_MSK;
			break;

		case SLAVE_STATE_DATA:
			gs_spi_status.ul_total_block_number++;

			if (gs_spi_status.ul_total_block_number == 
					gs_ul_test_block_number) {
				gs_ul_spi_state = SLAVE_STATE_STATUS_ENTRY;
			}
			break;

		case SLAVE_STATE_STATUS_ENTRY:
			gs_ul_spi_state = SLAVE_STATE_STATUS;
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
	switch (gs_ul_spi_state) {
	case SLAVE_STATE_IDLE:
	case SLAVE_STATE_END:
		gs_ul_spi_cmd = RC_SYN;
		spi_slave_transfer(&gs_ul_spi_cmd, sizeof(gs_ul_spi_cmd));
		break;

	case SLAVE_STATE_TEST:
		gs_ul_spi_cmd = RC_RDY;
		spi_slave_transfer(&gs_ul_spi_cmd, sizeof(gs_ul_spi_cmd));
		break;

	case SLAVE_STATE_DATA:
		if (gs_spi_status.ul_total_block_number < gs_ul_test_block_number) {
			spi_slave_transfer(gs_uc_spi_buffer, COMM_BUFFER_SIZE);
		}
		break;

	case SLAVE_STATE_STATUS_ENTRY:
		gs_ul_spi_cmd = RC_RDY;
		spi_slave_transfer(&gs_ul_spi_cmd, sizeof(gs_ul_spi_cmd));
		gs_ul_spi_state = SLAVE_STATE_STATUS;
		break;

	case SLAVE_STATE_STATUS:
		gs_ul_spi_cmd = RC_SYN;
		spi_slave_transfer(&gs_spi_status, sizeof(struct status_block_t));
		gs_ul_spi_state = SLAVE_STATE_END;
		break;
	}
}

/**
 * \brief Interrupt handler for the SPI slave.
 */
void SPI_Handler(void)
{
	uint32_t new_cmd = 0;
	static uint16_t data;
	uint8_t uc_pcs;

	if (spi_read_status(SPI_SLAVE_BASE) & SPI_SR_RDRF) {
		spi_read(SPI_SLAVE_BASE, &data, &uc_pcs);
		gs_puc_transfer_buffer[gs_ul_transfer_index] = data;
		gs_ul_transfer_index++;
		gs_ul_transfer_length--;
		if (gs_ul_transfer_length) {
			spi_write(SPI_SLAVE_BASE,
					gs_puc_transfer_buffer[gs_ul_transfer_index], 0, 0);
		}

		if (!gs_ul_transfer_length) {
			spi_slave_command_process();
			new_cmd = 1;
		}

		if (new_cmd) {
			if (gs_ul_spi_cmd != CMD_END) {
				gs_spi_status.ul_cmd_list[gs_spi_status.ul_total_command_number]
						= gs_ul_spi_cmd;
				gs_spi_status.ul_total_command_number++;
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
	uint32_t i;

	/* Reset status */
	gs_spi_status.ul_total_block_number = 0;
	gs_spi_status.ul_total_command_number = 0;
	for (i = 0; i < NB_STATUS_CMD; i++) {
		gs_spi_status.ul_cmd_list[i] = 0;
	}
	gs_ul_spi_state = SLAVE_STATE_IDLE;
	gs_ul_spi_cmd = RC_SYN;

	puts("-I- Initialize SPI as slave \r");
#if (SAMG55)
	/* Enable the peripheral and set SPI mode. */
	flexcom_enable(BOARD_FLEXCOM_SPI);
	flexcom_set_opmode(BOARD_FLEXCOM_SPI, FLEXCOM_SPI);
#else
	/* Configure an SPI peripheral. */
	spi_enable_clock(SPI_SLAVE_BASE);
#endif
	spi_disable(SPI_SLAVE_BASE);
	spi_reset(SPI_SLAVE_BASE);
	spi_set_slave_mode(SPI_SLAVE_BASE);
	spi_disable_mode_fault_detect(SPI_SLAVE_BASE);
	spi_set_peripheral_chip_select_value(SPI_SLAVE_BASE, SPI_CHIP_PCS);
	spi_set_clock_polarity(SPI_SLAVE_BASE, SPI_CHIP_SEL, SPI_CLK_POLARITY);
	spi_set_clock_phase(SPI_SLAVE_BASE, SPI_CHIP_SEL, SPI_CLK_PHASE);
	spi_set_bits_per_transfer(SPI_SLAVE_BASE, SPI_CHIP_SEL, SPI_CSR_BITS_8_BIT);
	spi_enable_interrupt(SPI_SLAVE_BASE, SPI_IER_RDRF);
	spi_enable(SPI_SLAVE_BASE);

	/* Start waiting command. */
	spi_slave_transfer(&gs_ul_spi_cmd, sizeof(gs_ul_spi_cmd));
}

/**
 * \brief Initialize SPI as master.
 */
static void spi_master_initialize(void)
{
	puts("-I- Initialize SPI as master\r");

#if (SAMG55)
	/* Enable the peripheral and set SPI mode. */
	flexcom_enable(BOARD_FLEXCOM_SPI);
	flexcom_set_opmode(BOARD_FLEXCOM_SPI, FLEXCOM_SPI);
#else
	/* Configure an SPI peripheral. */
	spi_enable_clock(SPI_MASTER_BASE);
#endif
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
			(
#if (SAM4L)
			sysclk_get_pba_hz()
#else
			sysclk_get_peripheral_hz()
#endif
			/ gs_ul_spi_clock));
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
	gs_ul_spi_clock = gs_ul_clock_configurations[configuration];
	printf("Setting SPI clock #%lu ... \n\r", (unsigned long)gs_ul_spi_clock);
	spi_master_initialize();
}

/**
 * \brief Perform SPI master transfer.
 *
 * \param pbuf Pointer to buffer to transfer.
 * \param size Size of the buffer.
 */
static void spi_master_transfer(void *p_buf, uint32_t size)
{
	uint32_t i;
	uint8_t uc_pcs;
	static uint16_t data;

	uint8_t *p_buffer;

	p_buffer = p_buf;

	for (i = 0; i < size; i++) {
		spi_write(SPI_MASTER_BASE, p_buffer[i], 0, 0);
		/* Wait transfer done. */
		while ((spi_read_status(SPI_MASTER_BASE) & SPI_SR_RDRF) == 0);
		spi_read(SPI_MASTER_BASE, &data, &uc_pcs);
		p_buffer[i] = data;
	}
}

/**
 * \brief Start SPI transfer test.
 */
static void spi_master_go(void)
{
	uint32_t cmd;
	uint32_t block;
	uint32_t i;

	/* Configure SPI as master, set up SPI clock. */
	spi_master_initialize();

	/*
	 * Send CMD_TEST to indicate the start of test, and device shall return
	 * RC_RDY.
	 */
	while (1) {
		cmd = CMD_TEST;
		puts("-> Master sending CMD_TEST... \r");
		spi_master_transfer(&cmd, sizeof(cmd));
		if (cmd == RC_RDY) {
			puts("   <- Slave response RC_SYN, RC_RDY \r");
			break;
		}
		if (cmd != RC_SYN) {
			printf("-E- Response unexpected: 0x%x \n\r", (unsigned)cmd);
			return;
		}
	}
	/* Send CMD_DATA with 4 blocks (64 bytes per page). */
	puts("-> Master sending CMD_DATA... \r");
	cmd = CMD_DATA | MAX_DATA_BLOCK_NUMBER;
	spi_master_transfer(&cmd, sizeof(cmd));
	puts("                                <---- Slave response RC_RDY \r");
	for (block = 0; block < MAX_DATA_BLOCK_NUMBER; block++) {
		for (i = 0; i < COMM_BUFFER_SIZE; i++) {
			gs_uc_spi_buffer[i] = block;
		}
		printf("-> Master sending block %u ... \n\r", (unsigned)block);
		spi_master_transfer(gs_uc_spi_buffer, COMM_BUFFER_SIZE);
		if (block) {
			for (i = 0; i < COMM_BUFFER_SIZE; i++) {
				if (gs_uc_spi_buffer[i] != (block - 1)) {
					break;
				}
			}
			if (i < COMM_BUFFER_SIZE) {
				printf("-E- block %u contains unexpected data \n\r",
					(unsigned)block);
			} else {
				printf("   <- Slave response last block %x \n\r",
					(unsigned)(block - 1));
			}
		}
	}

	for (i = 0; i < MAX_RETRY; i++) {
		cmd = CMD_STATUS;
		puts("-> Master sending CMD_STATUS... \r");
		spi_master_transfer(&cmd, sizeof(cmd));
		if (cmd == RC_RDY) {
			puts("   <- Slave response RC_RDY \r");
			break;
		}
	}
	if (i >= MAX_RETRY) {
		puts("   <- Slave no response \r");
		return;
	}

	puts("-> Master request slave status... \r");
	spi_master_transfer(&gs_spi_status, sizeof(struct status_block_t));

	puts("   <- Slave reports status...\r");
	printf("-I- Received  %u commands:",
		(unsigned)gs_spi_status.ul_total_command_number);

	for (i = 0; i < gs_spi_status.ul_total_command_number; i++) {
		printf(" 0x%08x", (unsigned)gs_spi_status.ul_cmd_list[i]);
	}
	printf(" \n\r-I- Received  %lu data blocks \n\r",
			(unsigned long)gs_spi_status.ul_total_block_number);

	for (i = 0; i < MAX_RETRY; i++) {
		puts("-> Master sending CMD_END... \r");
		cmd = CMD_END;
		spi_master_transfer(&cmd, sizeof(cmd));

		if (cmd == RC_SYN) {
			puts("   <- Slave response RC_SYN \r");
			break;
		}
	}

	if (i >= MAX_RETRY) {
		puts("   <- Slave no response \r");
	}

	puts("\r");
	puts("SPI transfer test finished! \r");
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
	NVIC_DisableIRQ(SPI_IRQn);
	NVIC_ClearPendingIRQ(SPI_IRQn);
	NVIC_SetPriority(SPI_IRQn, 0);
	NVIC_EnableIRQ(SPI_IRQn);

	spi_slave_initialize();

	/* Display menu. */
	display_menu();

	while (1) {
		scanf("%c", (char *)&uc_key);

		switch (uc_key) {
		case 'h':
			display_menu();
			break;

		case 't':
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
