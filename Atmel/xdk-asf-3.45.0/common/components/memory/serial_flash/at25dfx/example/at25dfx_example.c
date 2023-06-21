/**
 * \file
 *
 * \brief AT25DFx SerialFlash Component Example.
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
 * \mainpage AT25 SerialFlash example
 *
 * \section Purpose
 *
 * This example demonstrates how to use the Atmel SerialFlash AT25DFx component.
 * The SerialFlash requires an SPI bus as a low level communication interface. This
 * interface can be implemented using SPI or USART in SPI mode for SAM devices.
 *
 * \section Requirements
 *
 * This package can be used with SAM3N, SAM4L, SAM4E and SAM4C evaluation kits.
 *
 * \section Description
 *
 * This example will do the following operations.
 *   - Send "Read Status" command to the SerialFlash.
 *   - Read back the status of the SerialFlash.
 *   - Write two sectors to the SerialFlash.
 *   - Read back these sectors and check correct content.
 *   - If all operations are correct, \ref DATA_FLASH_LED_EXAMPLE_0 is 'on' and
 *     \ref DATA_FLASH_LED_EXAMPLE_1 is 'on'(If have).
 *     The other states of  LEDs mean that the SerialFlash access fails somewhere.
 *
 * \section Usage
 *
 * -# Build the program and download it into the evaluation board. Please
 *    refer to the
 *    <a href="http://www.microchip.com/dyn/resources/prod_documents/doc6224.pdf">
 *    SAM-BA User Guide</a>, the
 *    <a href="http://ww1.microchip.com/downloads/en/appnotes/doc6310.pdf">
 *    GNU-Based Software Development</a> application note or the
 *    <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *    IAR EWARM User Guide</a>, depending on the solutions that users choose.
 * -# Some texts, images and basic shapes should be displayed on the LCD.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include "conf_board.h"

/** Test size */
#define AT25DFX_TEST_DATA_SIZE   (1024)

/** Test block start address */
#define AT25DFX_TEST_BLOCK_ADDR  (0)

/** RAM buffer used in this example */
static uint8_t ram_buff[AT25DFX_TEST_DATA_SIZE];

/**
 * \brief Entry point when test is failed.
 */
void test_ko(void);

/**
 * \brief Application entry point for AT25DFx example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint16_t i;

	sysclk_init();
	board_init();

	/* Initialize the SerialFlash */
	at25dfx_initialize();

	/* Set the SerialFlash active */
	at25dfx_set_mem_active(AT25DFX_MEM_ID);

	/* Unprotect the chip */
	if (at25dfx_protect_chip(AT25_TYPE_UNPROTECT) == AT25_SUCCESS) {
		LED_On(DATA_FLASH_LED_EXAMPLE_0);
	} else {
		test_ko();
	}

	/* Check if the SerialFlash is valid */
	if (at25dfx_mem_check() == AT25_SUCCESS) {
		LED_On(DATA_FLASH_LED_EXAMPLE_0);
	} else {
		test_ko();
	}

	/* Prepare half of the SerialFlash sector as 0xAA */
	for (i = 0; i < AT25DFX_TEST_DATA_SIZE / 2; i++) {
		ram_buff[i] = 0xAA;
	}

	/* And the remaining half as 0x55 */
	for (; i < AT25DFX_TEST_DATA_SIZE; i++) {
		ram_buff[i] = 0x55;
	}

	/* Erase the block before write */
	at25dfx_erase_block(AT25DFX_TEST_BLOCK_ADDR);

	/* Write the data to the SerialFlash */
	at25dfx_write(ram_buff, AT25DFX_TEST_DATA_SIZE, AT25DFX_TEST_BLOCK_ADDR);

	/* Read back this sector and compare them with the expected values */
	at25dfx_read(ram_buff, AT25DFX_TEST_DATA_SIZE, AT25DFX_TEST_BLOCK_ADDR);

	for (i = 0; i < AT25DFX_TEST_DATA_SIZE / 2; i++) {
		if (ram_buff[i] != 0xAA) {
			test_ko();
		}
	}
	for (; i < AT25DFX_TEST_DATA_SIZE; i++) {
		if (ram_buff[i] != 0x55) {
			test_ko();
		}
	}

	/* Write one SerialFlash sector as 0x00, 0x01 .... */
	for (i = 0; i < AT25DFX_TEST_DATA_SIZE; i++) {
		ram_buff[i] = i;
	}

	/* Erase the block before write */
	at25dfx_erase_block(AT25DFX_TEST_BLOCK_ADDR);

	/* Write the data to the SerialFlash */
	at25dfx_write(ram_buff, AT25DFX_TEST_DATA_SIZE, AT25DFX_TEST_BLOCK_ADDR);

	/* Read back this sector and compare them with the expected values */
	at25dfx_read(ram_buff, AT25DFX_TEST_DATA_SIZE, AT25DFX_TEST_BLOCK_ADDR);

	for (i = 0; i < AT25DFX_TEST_DATA_SIZE; i++) {
		if (ram_buff[i] != (i % 0x100)) {
			test_ko();
		}
	}

	LED_On(DATA_FLASH_LED_EXAMPLE_1);
	while (1);
}

void test_ko(void)
{
	LED_Off(DATA_FLASH_LED_EXAMPLE_1);
	while (1);
}
