/**
 * \file
 *
 * \brief AT45dbx DataFlash Component Example.
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


/*! \mainpage
 * \section intro Introduction
 * This example demonstrates how to use the Atmel DataFlash AT45DBx component.
 * The DataFlash requires an SPI bus as a low level communication interface. This
 * interface can be implemented using SPI or USART in SPI mode for AVR devices.
 *
 * \section files Main Files
 * - at45dbx_example.c: AT45DBx memory example application.
 * - at45dbx.c: The DataFlash driver
 * - at45dbx.h: The DataFlash driver header
 * - conf_board.h: board initialization process configuration
 * - conf_clock.h: clock specific initialization
 * - conf_at45dbx.h: DataFlash driver configuration (including SPI service selection)
 *
 * \section spiapiinfo services/basic/spi API
 * The SPI API can be found \ref spi_master.h "here" for SPI module connection
 * or \ref usart_spi.h "here" for USART in SPI mode.
 *
 * \section deviceinfo Device Info
 * All AVR devices can be used. This example has been tested
 * with the following setup:
 *   - Evaluation kits with a DataFlash connected to an SPI interface.
 *
 * \section exampledescription Description of the example
 *   - Send "Read Status" command to the dataflash.
 *   - Read back the status of the dataflash.
 *   - Write two sectors to the dataflash
 *   - Read Back these sectors and check correct content
 *   - If all operations are correct, \ref DATA_FLASH_LED_EXAMPLE_0 is 'on' and \ref DATA_FLASH_LED_EXAMPLE_1 is 'on'
 *     other leds state means the DataFlash access fails somewhere.
 *
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


#include "compiler.h"
#include "preprocessor.h"
#include "board.h"
#include "gpio.h"
#include "sysclk.h"
#include "at45dbx.h"
#include "conf_data_flash_example.h"

// Dataflash target sector used in this example
#define	TARGET_SECTOR 0x00002
// RAM buffer used in this example
uint8_t ram_buf[AT45DBX_SECTOR_SIZE];

void test_ko(void);

/*! \brief Main function.
 */
int main(void)
{
	uint16_t i;
	sysclk_init();

	// Initialize the board.
	// The board-specific conf_board.h file contains the configuration of the board
	// initialization.
	board_init();
	at45dbx_init();
	if(at45dbx_mem_check()==true)	{
		gpio_set_pin_low(DATA_FLASH_LED_EXAMPLE_0);
	} else
	{
		test_ko();
	}

	// Prepare half a data flash sector to 0xAA
	for(i=0;i<AT45DBX_SECTOR_SIZE/2;i++) {
		ram_buf[i]=0xAA;
	}
	// And the remaining half to 0x55
	for(;i<AT45DBX_SECTOR_SIZE;i++) {
		ram_buf[i]=0x55;
	}

	at45dbx_write_sector_open(TARGET_SECTOR);
	at45dbx_write_sector_from_ram(ram_buf);
	at45dbx_write_close();

	// Read back this sector and compare to expected values
	at45dbx_read_sector_open(TARGET_SECTOR);
	at45dbx_read_sector_to_ram(ram_buf);
	at45dbx_read_close();
	for(i=0;i<AT45DBX_SECTOR_SIZE/2;i++) {
		if (ram_buf[i]!=0xAA) {
			test_ko();
		}
	}
	for(;i<AT45DBX_SECTOR_SIZE;i++) {
		if (ram_buf[i]!=0x55) {
			test_ko();
		}
	}

	// Write one data flash sector to 0x00, 0x01 ....
	for(i=0;i<AT45DBX_SECTOR_SIZE;i++) {
		ram_buf[i]=i;
	}
	at45dbx_write_sector_open(TARGET_SECTOR);
	at45dbx_write_sector_from_ram(ram_buf);
	at45dbx_write_close();

	// Read one data flash sector to ram
	at45dbx_read_sector_open(TARGET_SECTOR);
	at45dbx_read_sector_to_ram(ram_buf);
	at45dbx_read_close();
	for(i=0;i<AT45DBX_SECTOR_SIZE;i++) {
		if ( ram_buf[i]!=(i%0x100) ) {
			test_ko();
		}
	}

	gpio_set_pin_low(DATA_FLASH_LED_EXAMPLE_1);
	while (1);
}

void test_ko(void)
{
	gpio_set_pin_high(DATA_FLASH_LED_EXAMPLE_1);
	while(1);
}
