/**
 * \file
 *
 * \brief SD/MMC card example
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
 * \mainpage SD/MMC/SDIO Card Example
 *
 * \section Purpose
 *
 * This example demonstrates basic functions of SD/MMC/SDIO stack.
 * It will read and write an SD, MMC or SDIO card over MCI or SPI interface.
 * It is a development base for a SDIO application or a specific SD/MMC
 * application which does not require a file system.
 *
 * \section Description
 *
 * The example executes the following sequences:
 * - For each card slot available on board:
 *   - Wait for a card insertion
 *   - Initialize an SD, MMC or SDIO card.
 *   - If the inserted card is an SD or MMC card, test read/write access.
 *       - Write data into the card
 *       - Read data from the card
 *       - Verify the written data.
 *   - If the inserted card is a SDIO card:
 *     - Iniltialize a SDIO card.
 *     - Read and write test on CIA.
 *
 * The example outputs the information through the standard output (stdio).
 * To know the output used on the board, look in the conf_example.h file
 * and connect a terminal to the correct stdio port.
 * 
 * While using SAM4L Xplained Pro or SAM4L8 Xplained Pro, please attach IO1
 * Xplained Pro extension board to EXT1.
 *
 * While using Xplained Pro evaluation kits, please attach I/O1 Xplained Pro
 * extension board to EXT1.
 *
 * \section Usage
 *
 * -# Build the program and download it into the  board.
 * -# On the computer, open and configure a terminal application.
 * Refer to conf_example.h file.
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *    \code
	-- SD/MMC/SDIO Card Example --
	-- Compiled: xxx xx xxxx xx:xx:xx --
	Please plug an SD, MMC or SDIO card in slot 1.
	!!Warning, the data contained will be lost!!
\endcode
 * -# If the inserted card is a SD or MMC card, the following text should appear:
 *    \code
 	A card has been connected.
 	Card information:
 	    xxxx
 	    xxxx MB
 	    Write pattern... XXXXKBps [OK]
 	    Read... XXXXKBps [OK]
 	    Read and check pattern... [OK]
 	Test finished, please unplugged card.
\endcode
 * -# If inserted card is a SDIO card, similar following text should appear:
 *    \code
	A card has been connected.
	Card information:
	    SDIO
	    0MB
	--- Test with direct read and write command of CIA:
	Dump buffer (length=22):
	  0: 11 00 00 00 00 00 00 00 17 00 10 00 00 00 00 00
	 10: 00 00 01 00 00 00
	Write 0x02 to IEN(CIA.4).
	Check IEN after write:0x02
	Test OK

	--- Test with extended read and write command of CIA:
	Dump buffer (length=22):
	  0: 11 00 00 00 00 00 00 00 17 00 10 00 00 00 00 00
	 10: 00 00 01 00 00 00
	Modify Some R/W bytes (2,4) for FN0 and write:
	Check CIA after write:
	Dump buffer (length=22):
	  0: 11 00 00 00 03 00 00 00 17 00 10 00 00 00 00 00
	 10: 00 00 01 00 00 00
	test OK
	All test done.
\endcode
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <stdio_serial.h>
#include "conf_board.h"
#include "conf_clock.h"
#include "conf_example.h"
#include "sd_mmc_protocol.h"
#include <string.h>
#include "time_tick.h"

//! \name Read/write access configurations
//! @{

//! Offset before the end of memory card to start the test
#define TEST_MEM_START_OFFSET  (1024lu * 1024lu * 4lu) // 4MB

//! Memory area size dedicated for the read/write test
#define TEST_MEM_AREA_SIZE (1024lu * 1024lu * 1lu) // 1MB
/**
 * Size of each read or write access.
 * Increasing this number can get higher R/W performance.
 */
#define TEST_MEM_ACCESS_SIZE  (8lu * SD_MMC_BLOCK_SIZE)

#if TEST_MEM_START_OFFSET < TEST_MEM_AREA_SIZE
#  error TEST_MEM_START_OFFSET must be higher than TEST_MEM_AREA_SIZE
#endif
#if TEST_MEM_ACCESS_SIZE > TEST_MEM_AREA_SIZE
#  error TEST_MEM_AREA_SIZE must be higher than TEST_MEM_ACCESS_SIZE
#endif

//! The value used to generate test data
#define TEST_FILL_VALUE_U32     (0x5500AAFFU)

//! Buffer used by read/write tests
COMPILER_WORD_ALIGNED
static uint8_t buf_test[TEST_MEM_ACCESS_SIZE];

//! Read and write test length of CIA in bytes
#define TEST_CIA_SIZE           (0x16)

//! Buffer for test SDIO data
static uint8_t buf_cia[TEST_CIA_SIZE];
//! @}

static void main_display_info_card(uint8_t slot);
static void main_test_memory(uint8_t slot);
static void main_test_sdio(uint8_t slot);
static void main_dump_buffer(uint8_t *data_buffer, uint32_t length);

/**
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t slot = 0;
	sd_mmc_err_t err;
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits   = CONF_TEST_STOPBITS,
	};

	irq_initialize_vectors();
	cpu_irq_enable();

	sysclk_init();
	board_init();
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	time_tick_init();

	// Initialize SD MMC stack
	sd_mmc_init();

	printf("\x0C\n\r-- SD/MMC/SDIO Card Example --\n\r");
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);
	while (1) {
		if (slot == sd_mmc_nb_slot()) {
			slot = 0;
		}
		printf("Please plug an SD, MMC or SDIO card in slot %d.\n\r", slot+1);

		// Wait for a card and ready
		do {
			err = sd_mmc_check(slot);
			if ((SD_MMC_ERR_NO_CARD != err)
					&& (SD_MMC_INIT_ONGOING != err)
					&& (SD_MMC_OK != err)) {
				printf("Card install FAILED\n\r");
				printf("Please unplug and re-plug the card.\n\r");
				while (SD_MMC_ERR_NO_CARD != sd_mmc_check(slot)) {
				}
			}
		} while (SD_MMC_OK != err);
	
		// Display basic card information
		main_display_info_card(slot);
	
		/* Test the card */
		if (sd_mmc_get_type(slot) & CARD_TYPE_SDIO) {
			// Test CIA of SDIO card
			main_test_sdio(slot);
		}
		if (sd_mmc_get_type(slot) & (CARD_TYPE_SD | CARD_TYPE_MMC)) {
			// SD/MMC Card R/W
			main_test_memory(slot);
		}	

		printf("Test finished, please unplugged the card.\n\r");
		while (SD_MMC_OK == sd_mmc_check(slot)) {
		}
		slot++;
	}
}

/**
 * \brief Display basic information of the card.
 * \note This function should be called only after the card has been
 *       initialized successfully.
 *
 * \param slot   SD/MMC slot to test
 */
static void main_display_info_card(uint8_t slot)
{
	printf("Card information:\n\r");

	printf("    ");
	switch (sd_mmc_get_type(slot)) {
	case CARD_TYPE_SD | CARD_TYPE_HC:
		printf("SDHC");
		break;
	case CARD_TYPE_SD:
		printf("SD");
		break;
	case CARD_TYPE_MMC | CARD_TYPE_HC:
		printf("MMC High Density");
		break;
	case CARD_TYPE_MMC:
		printf("MMC");
		break;
	case CARD_TYPE_SDIO:
		printf("SDIO\n\r");
		return;
	case CARD_TYPE_SD_COMBO:
		printf("SD COMBO");
		break;
	case CARD_TYPE_UNKNOWN:
	default:
		printf("Unknow\n\r");
		return;
	}
	printf("\n\r    %d MB\n\r", (uint16_t)(sd_mmc_get_capacity(slot)/1024));
}

/**
 * \brief Card R/W tests
 *
 * \param slot   SD/MMC slot to test
 */
static void main_test_memory(uint8_t slot)
{
	uint32_t last_blocks_addr, i, nb_trans;
	uint32_t tick_start, time_ms;

	// Compute the last address
	last_blocks_addr = sd_mmc_get_capacity(slot) *
			(1024 / SD_MMC_BLOCK_SIZE);
	if (last_blocks_addr < (TEST_MEM_START_OFFSET / 512lu)) {
		printf("[Memory is too small.]\n\r");
		return;
	}
	last_blocks_addr -= (TEST_MEM_START_OFFSET / SD_MMC_BLOCK_SIZE);

	printf("Card R/W test:\n\r");

	// Read the last block
	printf("    Read... ");
	tick_start = time_tick_get();
	if (SD_MMC_OK != sd_mmc_init_read_blocks(slot,
			last_blocks_addr,
			TEST_MEM_AREA_SIZE / SD_MMC_BLOCK_SIZE)) {
		printf("[FAIL]\n\r");
		return;
	}
	for (nb_trans = 0; nb_trans < (TEST_MEM_AREA_SIZE / TEST_MEM_ACCESS_SIZE);
			nb_trans++) {
		if (SD_MMC_OK != sd_mmc_start_read_blocks(buf_test,
					TEST_MEM_ACCESS_SIZE / SD_MMC_BLOCK_SIZE)) {
			printf("[FAIL]\n\r");
			return;
		}
		if (SD_MMC_OK != sd_mmc_wait_end_of_read_blocks(false)) {
			printf("[FAIL]\n\r");
			return;
		}		
	}
	time_ms = time_tick_calc_delay(tick_start, time_tick_get());
	if (time_ms) { // Valid time_ms
		printf(" %d KBps ", (int)(((TEST_MEM_AREA_SIZE
				* 1000lu) / 1024lu) / time_ms));
	}
	printf("[OK]\n\r");

	if (sd_mmc_is_write_protected(slot)) {
		printf("Card is write protected [WRITE TEST SKIPPED]\n\r");
		return;
	}
	
	// Fill buffer with a pattern
	for (i = 0; i < (TEST_MEM_ACCESS_SIZE / sizeof(uint32_t)); i++) {
		((uint32_t*)buf_test)[i] = TEST_FILL_VALUE_U32;
	}

	printf("    Write pattern... ");
	if (SD_MMC_OK != sd_mmc_init_write_blocks(slot,
			last_blocks_addr,
			TEST_MEM_AREA_SIZE / SD_MMC_BLOCK_SIZE)) {
		printf("[FAIL]\n\r");
		return;
	}
	tick_start = time_tick_get();
	for (nb_trans = 0; nb_trans < (TEST_MEM_AREA_SIZE / TEST_MEM_ACCESS_SIZE);
			nb_trans++) {
		((uint32_t*)buf_test)[0] = nb_trans; // Unique value for each area
		if (SD_MMC_OK != sd_mmc_start_write_blocks(buf_test,
				TEST_MEM_ACCESS_SIZE / SD_MMC_BLOCK_SIZE)) {
			printf("[FAIL]\n\r");
			return;
		}
		if (SD_MMC_OK != sd_mmc_wait_end_of_write_blocks(false)) {
			printf("[FAIL]\n\r");
			return;
		}
	}
	time_ms = time_tick_calc_delay(tick_start, time_tick_get());
	if (time_ms) { // Valid time_ms
		printf(" %d KBps ", (int)(((TEST_MEM_AREA_SIZE
				* 1000lu) / 1024lu) / time_ms));
	}
	printf("[OK]\n\r");

	printf("    Read and check pattern... ");
	if (SD_MMC_OK != sd_mmc_init_read_blocks(slot,
			last_blocks_addr,
			TEST_MEM_AREA_SIZE / SD_MMC_BLOCK_SIZE)) {
		printf("Read [FAIL]\n\r");
		return;
	}
	for (nb_trans = 0; nb_trans < (TEST_MEM_AREA_SIZE / TEST_MEM_ACCESS_SIZE);
			nb_trans++) {
		// Clear buffer
		for (i = 0; i < (TEST_MEM_ACCESS_SIZE / sizeof(uint32_t)); i++) {
			((uint32_t*)buf_test)[i] = 0xFFFFFFFF;
		}
		// Fill buffer
		if (SD_MMC_OK != sd_mmc_start_read_blocks(buf_test,
					TEST_MEM_ACCESS_SIZE / SD_MMC_BLOCK_SIZE)) {
			printf("Read [FAIL]\n\r");
			return;
		}
		if (SD_MMC_OK != sd_mmc_wait_end_of_read_blocks(false)) {
			printf("Read [FAIL]\n\r");
			return;
		}
		// Check the unique value of the area
		if (((uint32_t*)buf_test)[0] != nb_trans) {
			printf("Check [FAIL]\n\r");
			return;
		}
		// Check buffer
		for (i = 1; i < (TEST_MEM_ACCESS_SIZE / sizeof(uint32_t)); i++) {
			if (((uint32_t*)buf_test)[i] != TEST_FILL_VALUE_U32) {
				printf("Check [FAIL]\n\r");
				return;
			}
		}
	}
	printf("[OK]\n\r");
}

/**
 * \brief Perform test on CIA (Common I/O Area) of SDIO card.
 *
 * \note The Common I/O Area (CIA) shall be implemented on all SDIO cards.
 *
 * \param slot   SD/MMC slot to test
 */
static void main_test_sdio(uint8_t slot)
{
	uint32_t i;
	uint32_t err;

	/*
	 * Test with direct read and write command.
	 */
	printf("\n\r--- Test with direct read and write command of CIA:\n\r");
	/* Read */
	for (i = 0; i < TEST_CIA_SIZE; i++) {
		err = sdio_read_direct(slot, SDIO_CIA, i, &buf_cia[i]);
		if (err) {
			printf("Error: SDIO direct read failed.\n\r");
			return;
		}
	}
	main_dump_buffer(buf_cia, TEST_CIA_SIZE);

	/* Write */
	printf("Write 0x02 to IEN(CIA.4).\n\r");
	err = sdio_write_direct(slot, SDIO_CIA, SDIO_CCCR_IEN, 0x02);
	if (err) {
		printf("Error: SDIO direct write failed.\n\r");
		return;
	}

	/* Check */
	printf("Check IEN after write:");
	err = sdio_read_direct(slot, SDIO_CIA, SDIO_CCCR_IEN,
			&buf_cia[SDIO_CCCR_IEN]);
	if (err) {
		printf("Error: SDIO direct read failed.\n\r");
		return;
	}

	printf("0x%02x\n\r", buf_cia[SDIO_CCCR_IEN]);
	if (0x02 == buf_cia[SDIO_CCCR_IEN]) {
		printf("Test OK.\n\r");
	} else {
		printf("Test failed.\n\r");
	}

	/* Restore data to 0 */
	sdio_write_direct(slot, SDIO_CIA, SDIO_CCCR_IEN, 0);

	/* Clear the buffer. */
	memset(buf_cia, 0x0, sizeof(buf_cia));

	/*
	 *  Test with extended read and write command.
	 */
	printf("\n\r--- Test with extended read and write command of CIA:\n\r");
	/* Read */
	err = sdio_read_extended(slot, SDIO_CIA, 0, 1, &buf_cia[0],
			TEST_CIA_SIZE);
	if (err) {
		printf("Error: SDIO extended read failed.\n\r");
		return;
	}

	main_dump_buffer(buf_cia, TEST_CIA_SIZE);

	/* Write */
	printf("Modify Some R/W bytes for FN0 and write:\n\r");
	buf_cia[SDIO_CCCR_IEN] = 0x3;
	err = sdio_write_extended(slot, SDIO_CIA, SDIO_CCCR_IEN, 1,
			&buf_cia[SDIO_CCCR_IEN], 1);
	if (err) {
		printf("Error: SDIO extended write failed.\n\r");
		return;
	}

	/* Read and check */
	printf("Check CIA after write:\n\r");
	err = sdio_read_extended(slot, SDIO_CIA, 0, 1, &buf_cia[0],
			TEST_CIA_SIZE);
	if (err) {
		printf("Error: SDIO extended read failed.\n\r");
		return;
	}

	main_dump_buffer(buf_cia, TEST_CIA_SIZE);

	if (buf_cia[SDIO_CCCR_IEN] != 0x3) {
		printf("CIA.4 Fail\n\r");
	} else {
		printf("Test OK\n\r");
	}

	/* Restore data to 0 */
	sdio_write_direct(slot, SDIO_CIA, SDIO_CCCR_IEN, 0);

	return;
}

/**
 * \brief Dump and print buffer.
 *
 * \param data_buffer Pointer to data buffer.
 * \param length      Buffer length.
 */
static void main_dump_buffer(uint8_t *data_buffer, uint32_t length)
{
	uint32_t i;

	printf("Dump buffer (length=%d):", (int)length);
	for (i = 0; i < length; i++) {
		if ((i % 16) == 0) { /* Display 16 data per line */
			printf("\n\r%3x:", (int)i);
		}

		printf(" %02x", data_buffer[i]);
	}
	printf("\n\r");
}
