/**
 * \file
 *
 * \brief Example of usage of the SPI Master Mode Basic Services.
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
 * \mainpage spi_master_example_sam
 *
 * \par intro Introduction
 * This example demonstrates how to use the SPI Master Mode Basic Services.
 *
 * \par files Main Files
 * - spi_master_example_sam.c: port drivers example application.
 * - conf_board.h: board initialization process configuration.
 * - conf_spi_master_example.h: board-specific mapping of resources used by this example.
 * - spi_master.c: Part Specific SPI Master Mode Implementation.
 *
 * \par spiapiinfo services/basic/spi API
 * The spi API can be found \ref spi_master.h "here".
 *
 * \par deviceinfo Device Info
 * This example has been tested with the following setup:
 *   - Evaluation kits with a serialflash (AT25 series) connected through an SPI interface.
 *
 * \par exampledescription Description of the example
 *   - Send "Read Status" command to the dataflash.
 *   - Read back the status of the dataflash.
 *   - If status is "ok", both \ref SPI_EXAMPLE_LED_PIN_EXAMPLE_1 and \ref SPI_EXAMPLE_LED_PIN_EXAMPLE_2 are 'on',
 *     else \ref SPI_EXAMPLE_LED_PIN_EXAMPLE_1 is 'on' and \ref SPI_EXAMPLE_LED_PIN_EXAMPLE_2 is 'off'.
 *
 * \par compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for AVR and SAM.
 * Other compilers may or may not work.
 *
 * \par contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/">Microchip</A>.\n
 * Support and FAQ: https://www.microchip.com/support/
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "conf_spi_master_example.h"

/*! \name AT25DF321 Commands
 */
//! @{
//! Status Register Read (Serial/8-bit Mode).
#define AT25DF_CMDC_RD_MID_REG    0x9F
//! @}

#define DATA_BUFFER_SIZE          0x04

/** First Status Command Register - Second Dummy Data */
uint8_t data[DATA_BUFFER_SIZE] = { AT25DF_CMDC_RD_MID_REG };

struct spi_device SPI_DEVICE_EXAMPLE = {
	/** Board specific select id */
	.id = SPI_DEVICE_EXAMPLE_ID
};

/*! \brief Read AT25DF321 manufacturer and device ID, check the density.
 */
static bool spi_at25df_mem_check(void)
{
	// Select the AT25DF memory to check.
	spi_select_device(SPI_EXAMPLE, &SPI_DEVICE_EXAMPLE);

	// Send the Status Register Read command followed by a dummy data.
	spi_write_packet(SPI_EXAMPLE, data, 1);

	// Receive the manufacturer and device id.
	spi_read_packet(SPI_EXAMPLE, data, DATA_BUFFER_SIZE);

	// Deselect the checked AT25DF memory.
	spi_deselect_device(SPI_EXAMPLE, &SPI_DEVICE_EXAMPLE);

	// Unexpected device density.
	if ((data[1] & AT25DF_MSK_DENSITY) < AT25DF_DENSITY) {
		return false;
	} else {
		return true;
	}
}


/*! \brief Main function.
 */
int main(void)
{
	sysclk_init();

	/* Initialize the board.
	 * The board-specific conf_board.h file contains the configuration of
	 * the board initialization.
	 */
	board_init();

	spi_master_init(SPI_EXAMPLE);
	spi_master_setup_device(SPI_EXAMPLE, &SPI_DEVICE_EXAMPLE, SPI_MODE_0,
			SPI_EXAMPLE_BAUDRATE, 0);
	spi_enable(SPI_EXAMPLE);

	if (spi_at25df_mem_check() == false) {
	#if !SAM4CM
		ioport_set_pin_level(SPI_EXAMPLE_LED_PIN_EXAMPLE_1, IOPORT_PIN_LEVEL_LOW);
	#endif
		ioport_set_pin_level(SPI_EXAMPLE_LED_PIN_EXAMPLE_2, IOPORT_PIN_LEVEL_HIGH);
	} else {
	#if !SAM4CM
		ioport_set_pin_level(SPI_EXAMPLE_LED_PIN_EXAMPLE_1, IOPORT_PIN_LEVEL_LOW);
	#endif
		ioport_set_pin_level(SPI_EXAMPLE_LED_PIN_EXAMPLE_2, IOPORT_PIN_LEVEL_LOW);
	}
	while (1) {
	}
}
