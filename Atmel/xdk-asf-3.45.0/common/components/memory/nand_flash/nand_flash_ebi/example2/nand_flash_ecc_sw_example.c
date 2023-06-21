/**
 * \file
 *
 * \brief NAND Flash Operation With Software ECC Example
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

/**
 * \mainpage NAND Flash With Software ECC Example
 *
 * \section Purpose
 *
 * This NAND Flash software ECC example show how to read and write data with
 * software ECC from/to a NAND Flash connected to the chip.
 *
 * \section Description
 *
 * The required steps are:
 * <ul>
 * <li> Initialize NAND Flash. </li>
 * <li> Find a good block by erase function.</li>
 * <li> Prepare a buffer.</li>
 * <li> Write the buffer into a NAND Flash page by software ECC function.</li>
 * <li> Read the page by software ECC function and check data is correct.</li>
 * </ul>
 * \section Usage
 *
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *     \code
	-- NAND Flash With Software ECC Example --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
	-I- NAND Flash driver initialized
	-I- Size of the whole device in bytes : 0xxxxxxxx
	-I- Size in bytes of one single block of a device : 0xxxxxx
	-I- Number of blocks in the entire device : 0xxxx
	-I- Size of the data area of a page in bytes : 0xxxx
	-I- Number of pages in the entire device : 0xxx
\endcode
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <string.h>

/* NAND Flash memory size. */
static uint32_t mem_size;
/* Number of blocks in NAND Flash. */
static uint32_t num_block;
/* Size of one block in the NAND Flash, in bytes. */
static uint32_t block_size;
/* Size of one page in the NAND Flash, in bytes. */
static uint32_t page_size;
/* Number of page per block. */
static uint32_t pages_per_block;

/* NAND Flash raw structure. */
static struct nand_flash_raw nf_raw;
/* Address for transferring command to the NAND Flash. */
static uint32_t cmd_address = BOARD_NF_COMMAND_ADDR;
/* Address for transferring address to the NAND Flash. */
static uint32_t addr_address = BOARD_NF_ADDRESS_ADDR;
/* Address for transferring data to the NAND Flash. */
static uint32_t data_address = BOARD_NF_DATA_ADDR;

/* NAND Flash ecc structure. */
static struct nand_flash_ecc nf_ecc;

/* Temporary buffer */
uint8_t write_buffer[2048];
uint8_t read_buffer[2048];
uint8_t spare_buffer[NAND_COMMON_MAX_PAGE_SPARE_SIZE];

/**
 *  Configure UART console.
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

int main(void)
{
	uint16_t block, page;
	uint32_t i;

	uint32_t error = 0;

	/* Initialize the SAM3 system */
	sysclk_init();
	board_init();

	/* Initialize the console uart */
	configure_console();

	/* Output example information */
	printf("-- NAND Flash With Software ECC Example --\n\r");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	memset(&nf_raw, 0, sizeof(nf_raw));

	if (nand_flash_raw_initialize(&nf_raw, 0, cmd_address,
			addr_address, data_address)) {
		printf("-E- Device Unknown\n\r");
		return 0;
	}

	printf("-I- NAND Flash driver initialized\n\r");

	/* Get device parameters */
	mem_size = nand_flash_model_get_device_size_in_bytes(&nf_raw.model);
	block_size = nand_flash_model_get_block_size_in_bytes(&nf_raw.model);
	num_block = nand_flash_model_get_device_size_in_blocks(&nf_raw.model);
	page_size = nand_flash_model_get_page_data_size(&nf_raw.model);
	pages_per_block
		= nand_flash_model_get_block_size_in_pages(&nf_raw.model);

	printf("-I- Size of the whole device in bytes : 0x%x \n\r", mem_size);
	printf("-I- Size in bytes of one single block of a device : 0x%x \n\r",
			block_size);
	printf("-I- Number of blocks in the entire device : 0x%x \n\r",
			num_block);
	printf("-I- Size of the data area of a page in bytes : 0x%x \n\r",
			page_size);
	printf("-I- Number of pages in the entire device : 0x%x \n\r",
			pages_per_block);

	/* Erase all block and use the last good block for read/write test */
	for (i = 0; i < num_block; i++) {
		error = nand_flash_raw_erase_block(&nf_raw, i);

		if (error == NAND_COMMON_ERROR_BADBLOCK) {
			printf("-E- Block %u is BAD block. \n\r", i);
		} else {
			block = i;
		}
	}
	/* Prepare a page size buffer in SRAM. */
	printf("-I- Preparing a buffer in SRAM ...\n\r");
	for (i = 0; i < page_size; i++) {
		write_buffer[i] = (i & 0xFF);
	}

	/* Reset read buffer. */
	memset(read_buffer, 0, sizeof(read_buffer));

	nf_ecc.raw = nf_raw;

	/* Test all pages in the good block. */
	printf("-I- Test the read/write of all pages in block %d.\n\r", block);
	for (page = 0; page < pages_per_block; page++) {
		/* Write a page to the NAND Flash. */
		error = nand_flash_ecc_write_page(&nf_ecc, block, page,
				write_buffer, spare_buffer);
		if (error) {
			printf("-E- Cannot write page %d of block %d.\n\r",
					page, block);
		}

		/* Read the page from the NAND Flash. */
		nand_flash_ecc_read_page(&nf_ecc, block, page, read_buffer,
				spare_buffer);

		/* Test if the read buffer is the same as SRAM buffer */
		error = memcmp(read_buffer, write_buffer, sizeof(write_buffer));
		if (error) {
			printf("-I- Read data is different from write data in page %d of block %d.\n\r",
					page, block);
			printf("-I- Software ECC does not work correctly.\n\r");
		} else {
			printf("-I- Read data matches write data in page %d of block %d.\n\r",
					page, block);
		}
	}

	printf("-I- Test Completed.\n\r");

	while (1) {
		/* Do nothing */
	}
}
