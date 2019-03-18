/*****************************************************************************
 *
 * \file
 *
 * \brief Example of usage of the USART_SPI Master Mode Basic Services.
 *
 ****************************************************************************/

/**
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
/*! \mainpage
 * \section intro Introduction
 * This example demonstrates how to use the USART_SPI Master Mode Basic
 * Services.
 *
 * \section files Main Files
 * - usart_spi_master_example.c: port drivers example application.
 * - conf_board.h: board initialization process configuration
 * - conf_usart_spi_master_example.h: board-specific mapping of resources used
 *    by this example
 * - usart_spi.c: Part Specific USART_SPI Master Mode Implementation
 *
 * \section usart_spi API
 * The usart_spi API can be found \ref usart_spi.h "here".
 *
 * \section deviceinfo Device Info
 * This example can be used on all SAM EK boards with external AT45DBX data
 * flash component. Connect the board and external component with the
 * following paired pins.
 * \copydoc usart_spi_master_example_pin_defs
 *
 * \section exampledescription Description of the example
 *   - Send "Manufacturer ID Read" command to the dataflash.
 *   - Read back the Manufacturer ID of the dataflash.
 *   - If Manufacturer ID match Atmel ID "0x1F" and there are at least 2 LEDs
 *     on the board, both
 *      \ref USART_SPI_EXAMPLE_LED_PIN_EXAMPLE_1 and
 *      \ref USART_SPI_EXAMPLE_LED_PIN_EXAMPLE_2 are 'on'. Otherwise
 *      \ref USART_SPI_EXAMPLE_LED_PIN_EXAMPLE_1 is 'on' and
 *      \ref USART_SPI_EXAMPLE_LED_PIN_EXAMPLE_2 is 'off'.
 *     If there is only one LED on the board, 
 *      \ref USART_SPI_EXAMPLE_LED_PIN_EXAMPLE_1 is 'on'. Otherwise
 *      \ref USART_SPI_EXAMPLE_LED_PIN_EXAMPLE_1 is 'off'.
 *     
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR.
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
#include "conf_usart_spi_master_example.h"

/* Manufacturer ID for dataflash. */
uint8_t manufacturer_id;

/* Manufacturer ID for Atmel dataflash. */
#define ATMEL_MANUFACTURER_ID         0x1F

/* AT45DBX Command: Manufacturer ID Read. */
#define AT45DF_CMDC_RD_MID_REG        0x9F

/* Buffer size. */
#define DATA_BUFFER_SIZE         0x04

/* Data buffer. */
uint8_t data[DATA_BUFFER_SIZE] = {AT45DF_CMDC_RD_MID_REG};

struct usart_spi_device USART_SPI_DEVICE_EXAMPLE = {
	/* Board specific select ID. */
	.id = USART_SPI_DEVICE_EXAMPLE_ID
};

static bool usart_spi_at45dbx_mem_check(void)
{
	/* Select the DF memory to check. */
	usart_spi_select_device(USART_SPI_EXAMPLE, &USART_SPI_DEVICE_EXAMPLE);

	/* Send the Manufacturer ID Read command. */
	usart_spi_write_packet(USART_SPI_EXAMPLE, data, 1);

	/* Receive Manufacturer ID. */
	usart_spi_read_packet(USART_SPI_EXAMPLE, data, DATA_BUFFER_SIZE);

	/* Extract the Manufacturer ID. */
	manufacturer_id = data[0];

	/* Deselect the checked DF memory. */
	usart_spi_deselect_device(USART_SPI_EXAMPLE, &USART_SPI_DEVICE_EXAMPLE);

	/* Check the Manufacturer id. */
	if (manufacturer_id == ATMEL_MANUFACTURER_ID) {
		return true;
	} else {
		return false;
	}
}


/*! \brief Main function.
 */
int main(void)
{
	sysclk_init();

	/*
	 * Initialize the board.
	 * The board-specific conf_board.h file contains the configuration of
	 * the board initialization.
	 */
	board_init();

	/* Config the USART_SPI. */
	usart_spi_init(USART_SPI_EXAMPLE);
	usart_spi_setup_device(USART_SPI_EXAMPLE, &USART_SPI_DEVICE_EXAMPLE,
			SPI_MODE_0, USART_SPI_EXAMPLE_BAUDRATE, 0);
	usart_spi_enable(USART_SPI_EXAMPLE);

	/* Show the test result by LED. */
	if (usart_spi_at45dbx_mem_check() == false) {
#ifndef USART_SPI_EXAMPLE_LED_PIN_EXAMPLE_2
		ioport_set_pin_level(USART_SPI_EXAMPLE_LED_PIN_EXAMPLE_1,
				IOPORT_PIN_LEVEL_HIGH);
#else
		ioport_set_pin_level(USART_SPI_EXAMPLE_LED_PIN_EXAMPLE_1,
				IOPORT_PIN_LEVEL_LOW);
		ioport_set_pin_level(USART_SPI_EXAMPLE_LED_PIN_EXAMPLE_2,
				IOPORT_PIN_LEVEL_HIGH);
#endif
	} else {
		ioport_set_pin_level(USART_SPI_EXAMPLE_LED_PIN_EXAMPLE_1,
				IOPORT_PIN_LEVEL_LOW);
#ifdef USART_SPI_EXAMPLE_LED_PIN_EXAMPLE_2
		ioport_set_pin_level(USART_SPI_EXAMPLE_LED_PIN_EXAMPLE_2,
				IOPORT_PIN_LEVEL_LOW);
#endif
	}

	while (1) {
		/* Do nothing */
	}
}

