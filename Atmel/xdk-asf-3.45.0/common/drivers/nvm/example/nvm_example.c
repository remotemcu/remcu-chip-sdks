/**
 * \file
 *
 * \brief Common NVM service example
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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
 * \mainpage
 *
 * \section intro Introduction
 * This example demonstrates how to use the basic Non volatile memories
 * access functions
 *
 * \section files Main files
 * - nvm_example.c: example application
 * - conf_board.h: board configuration
 * - conf_nvm.h: Non volatile memory configuration used in this example
 * - conf_nvm_example.h: board-specific mapping of resources
 * used by this example
 *
 * \section nvmapiinfo drivers/basic/nvm API
 * The NVM API can be found \ref common_nvm.h "here".
 *
 * \section deviceinfo Device Info
 * All AVR and SAM devices with internal Flash can be used.
 *
 * \section exampledescription Description of the example
 *   - Write data to the internal flash and/or external dataflash AT45DBX
 *   - Read back the data and compare with the original data
 *
 * NVM_EXAMPLE_LED0 gives the result for internal flash:\n
 * NVM_EXAMPLE_LED0 OFF: Test failed
 * NVM_EXAMPLE_LED0 ON : Test passed
 *
 * On boards with external dataflash,
 * NVM_EXAMPLE_LED1 gives the result for external dataflash AT45DBX:\n
 * NVM_EXAMPLE_LED1 OFF: Test failed
 * NVM_EXAMPLE_LED1 ON : Test passed
 *
 * NVM_EXAMPLE_LED2 ON: Indicates that all tests are complete
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for AVR.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/">Microchip</A>.\n
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "conf_nvm_example.h"

/*! \brief Test routine that writes to the non volatile memory, reads back
 * and compares the values
 */
static status_code_t test_mem(mem_type_t mem, uint32_t test_address)
{
	static uint8_t write_buf[8]
		= {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
	static uint8_t read_buf[8], i = 0;

	/* Initialize the non volatile memory */
	if (nvm_init(mem) != STATUS_OK) {
		return ERR_INVALID_ARG;
	}

#if SAM4S
	nvm_page_erase(mem, test_address / IFLASH_PAGE_SIZE);
#endif

	/* Write test pattern to the specified address */
	nvm_write(mem, test_address, (void *)write_buf, sizeof(write_buf));

	/* Read back data from the same address */
	nvm_read(mem, test_address, (void *)read_buf, sizeof(read_buf));

	/* Validate the read data */
	for (i = 0; i < sizeof(write_buf); i++) {
		if (read_buf[i] != write_buf[i]) {
			return ERR_BAD_DATA;
		}
	}

	return STATUS_OK;
}

/*! \brief NVM Example Main
 *
 * The NVM example begins by initializing required board resources.  The
 * system clock and basic GPIO pin mapping are established.
 *
 * A memory location on the Non volatile memory is written with a fixed test
 * pattern which is then read back into a separate buffer. As a basic sanity
 * check, the original write-buffer values are compared with values read to
 * a separate buffer.  An LED on the development board is illuminated when there
 * is a match between the written and read data.
 *
 * \return Nothing.
 */
int main(void)
{
	mem_type_t mem;

	sysclk_init();
	board_init();

	/* Test internal flash */
	mem = INT_FLASH;
	if (test_mem(mem, (uint32_t)TEST_ADDRESS_INT) == STATUS_OK) {
		/* Turn on LED to indicate success */
		ioport_set_pin_level(NVM_EXAMPLE_LED0, false);
	}

#if defined(USE_EXTMEM) && defined(CONF_BOARD_AT45DBX)
	/* Test external dataflash */
	mem = AT45DBX;
	if (test_mem(mem, (uint32_t)TEST_ADDRESS_EXT) == STATUS_OK) {
		/* Turn on LED to indicate success */
		ioport_set_pin_level(NVM_EXAMPLE_LED1, false);
	}
#endif

	/* Turn on LED to indicate tests are complete */
	ioport_set_pin_level(NVM_EXAMPLE_LED2, false);

	while (1) {
	}
}
