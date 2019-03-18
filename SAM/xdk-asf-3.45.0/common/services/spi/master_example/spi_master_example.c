/*****************************************************************************
 *
 * \file
 *
 * \brief Example of usage of the SPI Master Mode Basic Services.
 *
 ******************************************************************************/

/**
 * Copyright (c) 2010-2018 Microchip Technology Inc. and its subsidiaries.
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
 * This example demonstrates how to use the SPI Master Mode Basic Services.
 *
 * \section files Main Files
 * - spi_master_example.c: port drivers example application.
 * - conf_board.h: board initialization process configuration
 * - conf_spi_master_example.h: board-specific mapping of resources used by this example
 * - spi_master.c: Part Specific SPI Master Mode Implementation
 *
 * \section spiapiinfo services/basic/spi API
 * The spi API can be found \ref spi_master.h "here".
 *
 * \section deviceinfo Device Info
 * All AVR devices can be used. This example has been tested
 * with the following setup:
 *   - Evaluation kits with a dataflash connecting through a SPI interface.
 * To make this example work on STK600 define AT45DB041 in config file.
 *
 * \section exampledescription Description of the example
 *   - Send "Read Status" command to the dataflash.
 *   - Read back the status of the dataflash.
 *   - If status "ok", both \ref SPI_EXAMPLE_LED_PIN_EXAMPLE_1 and \ref SPI_EXAMPLE_LED_PIN_EXAMPLE_2 are 'on'
 *     else \ref SPI_EXAMPLE_LED_PIN_EXAMPLE_1 is 'on' and \ref SPI_EXAMPLE_LED_PIN_EXAMPLE_2 is 'off'.
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
#include "spi_master.h"
#include "conf_spi_master_example.h"


uint16_t status; // Status value for dataflash.

/*! \name AT45DBX Group C Commands
 */
//! @{
//! Status Register Read (Serial/8-bit Mode).
#define AT45DBX_CMDC_RD_STATUS_REG        0xD7
//! @}

/*! \name Bit-Masks and Values for the Status Register
 */
//! @{
#define AT45DBX_MSK_DENSITY               0x3C      //!< Device density bit-mask
#ifdef AT45DB041
#define AT45DBX_DENSITY                   0x1C      //!< Device density value.
#else
#define AT45DBX_DENSITY                   0x3C      //!< Device density value.
#endif
//! @}

//! First Status Command Register - Second Dummy Data
uint8_t data[1] = {AT45DBX_CMDC_RD_STATUS_REG};

struct spi_device SPI_DEVICE_EXAMPLE = {
	//! Board specific select id
	.id = SPI_DEVICE_EXAMPLE_ID
};

static bool spi_at45dbx_mem_check(void)
{
	// Select the DF memory to check.
	spi_select_device(SPI_EXAMPLE,&SPI_DEVICE_EXAMPLE);

	// Send the Status Register Read command following by a dummy data.
	spi_write_packet(SPI_EXAMPLE, data, 1);

	// Receive status.
	spi_read_packet(SPI_EXAMPLE, data,1);

	// Extract the status.
	status = data[0];

	// Deselect the checked DF memory.
	spi_deselect_device(SPI_EXAMPLE,&SPI_DEVICE_EXAMPLE);

	// Unexpected device density value.
	if ((status & AT45DBX_MSK_DENSITY) < AT45DBX_DENSITY) return false;
	else return true;
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
	status = spi_at45dbx_mem_check();
	while (true)
	{
		if (status==false)
		{
			gpio_set_pin_low(SPI_EXAMPLE_LED_PIN_EXAMPLE_1);
			gpio_set_pin_high(SPI_EXAMPLE_LED_PIN_EXAMPLE_2);
		}
		else
		{
			gpio_set_pin_low(SPI_EXAMPLE_LED_PIN_EXAMPLE_1);
			gpio_set_pin_low(SPI_EXAMPLE_LED_PIN_EXAMPLE_2);
		}
	}
}

