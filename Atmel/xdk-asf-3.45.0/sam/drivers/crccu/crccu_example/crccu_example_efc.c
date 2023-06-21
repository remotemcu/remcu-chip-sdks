/**
 * \file
 *
 * \brief Cyclic Redundancy Check Calculation Unit (CRCCU) example for SAM.
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
 *
 * \mainpage CRCCU Example
 *
 * \par Purpose
 *
 * This example demonstrates the Cyclic Redundancy Check Calculation Unit (CRCCU)
 * provided on SAM serials' microcontrollers. It shows how to use CRCCU
 * to compute CRC on a memory area.
 *
 * \par Requirements
 *
 * This package can be used with the following setup:
 * - SAM3S evaluation kits
 * - SAM4S evaluation kits
 * - SAMG55 Xplained Pro
 *
 * \par Description
 *
 * The example work as:
 * a. Initialize a buffer in SRAM with random data;
 *    Initialize a buffer in Flash with the same data as in SRAM.
 * b. Initialize the CRCCU to compute the CRC of the buffer in SRAM
 *    with one of the 3 CRC algorithms.
 * c. Start the computation.
 * d. Read the result and display it.
 * e. Calculate and display the CRC result in Flash and compare it with
 *    the result in SRAM .
 * f. Redo b, c, d, e with 2 other CRC modes.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR EWARM.
 * Other compilers may or may not work.
 *
 * \par Usage
 *
 * -# Build the program and download it inside the evaluation board.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear
 *    (values depend on the board and chip used):
 *    \code
	-- CRCCU Example --
	-- SAMXX-EK
	-- Compiled: Oct 27 2011 13:33:38 --
	...
\endcode
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <string.h>
#include "conf_crccu_example.h"

/** Flash buffer address */
#if SAMG55
#define FLASH_BUFFER_ADDRESS   (IFLASH_ADDR + IFLASH_SIZE / 2 - FLASH_BUFFER_SIZE * 16)
#else
#define FLASH_BUFFER_ADDRESS   (IFLASH_ADDR + IFLASH_SIZE / 2 - FLASH_BUFFER_SIZE * 8)
#endif

/** CRC data buffer size (in byte) */
#define BUFFER_LENGTH   64
#if (BUFFER_LENGTH > FLASH_BUFFER_SIZE)
#error "Flash buffer size is too small."
#endif

/** CRCCU operation time out value */
#define CRCCU_TIMEOUT   0xFFFFFFFF

#define STRING_EOL    "\r"
#define STRING_HEADER "-- CRCCU Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/** CRC descriptor */
COMPILER_ALIGNED(512)
crccu_dscr_type_t crc_dscr;

/** CRC data buffer */
uint8_t g_uc_data_buf[BUFFER_LENGTH];

/** Flash wait state number. */
#define FLASH_WAIT_STATE_NBR   6

/**
 * \brief Compute CRC of a buffer.
 *
 * \param p_buffer         The buffer holding the data.
 * \param ul_length          The buffer length.
 * \param ul_polynomial_type The polynomial type(CRCCU_MR_PTYPE_XXX).
 *
 * \return CRC of the buffer.
 */
static uint32_t compute_crc(uint8_t *p_buffer, uint32_t ul_length,
		uint32_t ul_polynomial_type)
{
	uint32_t ul_crc;
	uint32_t ul_timeout = 0;

	/* Reset the CRCCU */
	crccu_reset(CRCCU);

	memset((void *)&crc_dscr, 0, sizeof(crccu_dscr_type_t));

	crc_dscr.ul_tr_addr = (uint32_t) p_buffer;

	/* Transfer width: byte, interrupt enable */
	crc_dscr.ul_tr_ctrl =
			CRCCU_TR_CTRL_TRWIDTH_BYTE | ul_length |
			CRCCU_TR_CTRL_IEN_ENABLE;

	/* Configure the CRCCU descriptor */
	crccu_configure_descriptor(CRCCU, (uint32_t) &crc_dscr);

	/* Configure CRCCU mode */
	crccu_configure_mode(CRCCU, CRCCU_MR_ENABLE | ul_polynomial_type);

	/* Start the CRC calculation */
	crccu_enable_dma(CRCCU);

	/* Wait for calculation ready */
	while ((crccu_get_dma_status(CRCCU) == CRCCU_DMA_SR_DMASR) &&
			(ul_timeout++ < CRCCU_TIMEOUT)) {
	}

	/* Get CRC value */
	ul_crc = crccu_read_crc_value(CRCCU);

	/* Display CRC */
	if (ul_polynomial_type == CRCCU_MR_PTYPE_CCITT16) {
		/* 16-bits CRC */
		ul_crc &= 0xFFFF;
		printf("  CRC of the buffer is 0x%04x\n\r", ul_crc);
	} else {
		/* 32-bits CRC */
		printf("  CRC of the buffer is 0x%08x\n\r", ul_crc);
	}

	return ul_crc;
}

/**
 * \brief Compute CRC of a buffer and compare it with the reference CRC.
 *
 * \param p_Buffer         The buffer holding the data.
 * \param ul_length          The buffer length.
 * \param ul_type  The polynomial type(CRCCU_MR_PTYPE_XXX).
 * \param ul_ref_crc          Reference CRC for the buffer.
 *
 * \return CRC of the buffer.
 */
static uint32_t compute_crc_and_compare(uint8_t *p_buffer, uint32_t ul_length,
		uint32_t ul_type, uint32_t ul_ref_crc)
{
	uint32_t ul_crc;

	/* Compute CRC */
	ul_crc = compute_crc(p_buffer, ul_length, ul_type);

	/* Compare CRC */
	if (ul_crc == ul_ref_crc) {
		puts("  CRC matches the reference value.\r");
	} else {
		puts("  CRC does NOT match the reference value.\r");
	}

	return ul_crc;
}

/**
 *  \brief Configure the Console Uart
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
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief Application entry point for CRCCU example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint32_t ul_counter;
	uint32_t ul_crc;

	/* Initialize the system */
	sysclk_init();
	board_init();

	/* Configure the console uart */
	configure_console();
	/* Output example information */
	puts(STRING_HEADER);

	/* Enable CRCCU peripheral clock */
	pmc_enable_periph_clk(ID_CRCCU);

	/* Initialize flash: 6 wait states for flash writing. */
	flash_init(FLASH_ACCESS_MODE_128, FLASH_WAIT_STATE_NBR);

	/* Unlock flash page. */
	flash_unlock(FLASH_BUFFER_ADDRESS,
			FLASH_BUFFER_ADDRESS + IFLASH_PAGE_SIZE - 1, NULL, NULL);

	/* Fill data buffer in SRAM (The data may be random data) */
	for (ul_counter = 0; ul_counter < BUFFER_LENGTH; ul_counter++) {
		g_uc_data_buf[ul_counter] = ul_counter;
	}

#if SAM4S || SAMG55
	/* Fill data buffer in Flash, the data is same as in SRAM */
#if SAM4S
	flash_erase_page(FLASH_BUFFER_ADDRESS,
			IFLASH_ERASE_PAGES_8);
#else 
	flash_erase_page(FLASH_BUFFER_ADDRESS,
				IFLASH_ERASE_PAGES_16);
#endif
	flash_write(FLASH_BUFFER_ADDRESS,
			(void *)g_uc_data_buf,
			BUFFER_LENGTH, 0);
#else
	flash_write(FLASH_BUFFER_ADDRESS,
			(void *)g_uc_data_buf,
			BUFFER_LENGTH, 1);
#endif

	/* Test CRC with CCITT-16 polynomial */
	puts("\n\r====Test CRC with CCITT 16 (0x1021) ====\r");

	/* Compute CRC in SRAM */
	puts("Test CRC in SRAM buffer\r");
	ul_crc = compute_crc(g_uc_data_buf, BUFFER_LENGTH,
			CRCCU_MR_PTYPE_CCITT16);

	/* Compute CRC in Flash and compare it with the result in SRAM */
	puts("Test CRC in Flash buffer\r");
	compute_crc_and_compare((uint8_t *) FLASH_BUFFER_ADDRESS, BUFFER_LENGTH,
			CRCCU_MR_PTYPE_CCITT16, ul_crc);

	/* Test CRC with CASTAGNOLI polynomial */
	puts("\n\r====Test CRC with CASTAGNOLI (0x1EDC6F41) ====\r");

	/* Compute CRC in SRAM */
	puts("Test CRC in SRAM buffer\r");
	ul_crc = compute_crc(g_uc_data_buf, BUFFER_LENGTH,
			CRCCU_MR_PTYPE_CASTAGNOLI);
	/* Compute CRC in Flash and compare it with the result in SRAM */
	puts("Test CRC in Flash buffer\r");
	compute_crc_and_compare((uint8_t *) FLASH_BUFFER_ADDRESS, BUFFER_LENGTH,
			CRCCU_MR_PTYPE_CASTAGNOLI, ul_crc);

	/* Test CRC with CCITT 802.3 polynomial */
	puts("\n\r====Test CRC with CCITT 802.3 (0x04C11DB7) ====\r");

	/* Compute CRC in SRAM */
	puts("Test CRC in SRAM buffer\r");
	ul_crc = compute_crc(g_uc_data_buf, BUFFER_LENGTH,
			CRCCU_MR_PTYPE_CCITT8023);
	/* Compute CRC in Flash and compare it with the result in SRAM */
	puts("Test CRC in Flash buffer\r");
	compute_crc_and_compare((uint8_t *) FLASH_BUFFER_ADDRESS, BUFFER_LENGTH,
			CRCCU_MR_PTYPE_CCITT8023, ul_crc);

	while (1) {
	}
}

