/**
 * \file
 *
 * \brief ST7565R display controller driver.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include "st7565r.h"

/**
 * \internal
 * \brief Initialize the hardware interface
 *
 * Depending on what interface used for interfacing the LCD controller this
 * function will initialize the necessary hardware.
 */
static void st7565r_interface_init(void)
{
#ifdef ST7565R_SERIAL_INTERFACE
	spi_flags_t spi_flags = SPI_MODE_3;
	board_spi_select_id_t spi_select_id = 0;
#endif

#if defined(ST7565R_USART_SPI_INTERFACE)
	struct usart_spi_device device = {
		.id = ST7565R_CS_PIN,
	};
	usart_spi_init(ST7565R_USART_SPI);
	usart_spi_setup_device(ST7565R_USART_SPI, &device, spi_flags,
			ST7565R_CLOCK_SPEED, spi_select_id);
#elif defined(ST7565R_SPI_INTERFACE)
	struct spi_device device = {
		.id = ST7565R_CS_PIN,
	};
	spi_master_init(ST7565R_SPI);
	spi_master_setup_device(ST7565R_SPI, &device, spi_flags,
			ST7565R_CLOCK_SPEED, spi_select_id);
#endif
}

/**
 * \brief Initialize the LCD controller
 *
 * Call this function to initialize the hardware interface and the LCD
 * controller. When initialization is done the display is turned on and ready
 * to receive data.
 */
void st7565r_init(void)
{
	// Do a hard reset of the LCD display controller
	st7565r_hard_reset();

	// Initialize the interface
	st7565r_interface_init();

	// Set the A0 pin to the default state (command)
	ioport_set_pin_low(ST7565R_A0_PIN);

	// The column address is set to increasing
	st7565r_write_command(ST7565R_CMD_ADC_NORMAL);

	// Non-inverted display
	st7565r_display_invert_disable();

	// The common mode scan direction is reversed COM31->COM0
	st7565r_write_command(ST7565R_CMD_REVERSE_SCAN_DIRECTION);

	// Set the voltage bias ratio to 1/6
	st7565r_write_command(ST7565R_CMD_LCD_BIAS_1_DIV_6_DUTY33);

	// Set booster circuit, voltage regulator and voltage follower all to on
	st7565r_write_command(ST7565R_CMD_POWER_CTRL_ALL_ON);

	// Set the booster ratio to 2X,3X,4X
	st7565r_write_command(ST7565R_CMD_BOOSTER_RATIO_SET);
	st7565r_write_command(ST7565R_CMD_BOOSTER_RATIO_2X_3X_4X);

	// Set voltage resistor ratio to 1
	st7565r_write_command(ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_1);

	/* Set contrast to min value, no need to check return value as the contrast
	is set to the defined min*/
	st7565r_set_contrast(ST7565R_DISPLAY_CONTRAST_MIN);

	// Turn on the display
	st7565r_display_on();
}
