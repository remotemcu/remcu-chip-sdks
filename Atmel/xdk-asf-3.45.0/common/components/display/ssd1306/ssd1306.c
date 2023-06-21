/**
 * \file
 *
 * \brief SSD1306 display controller driver.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include "ssd1306.h"
#include "font.h"

/**
 * \internal
 * \brief Initialize the hardware interface
 *
 * Depending on what interface used for interfacing the OLED controller this
 * function will initialize the necessary hardware.
 */
static void ssd1306_interface_init(void)
{
#ifdef SSD1306_SERIAL_INTERFACE
	spi_flags_t spi_flags = SPI_MODE_0;
	board_spi_select_id_t spi_select_id = 0;
#endif

#if defined(SSD1306_USART_SPI_INTERFACE)
	struct usart_spi_device device = {
		.id = SSD1306_CS_PIN,
	};
	usart_spi_init(SSD1306_USART_SPI);
	usart_spi_setup_device(SSD1306_USART_SPI, &device, spi_flags,
			SSD1306_CLOCK_SPEED, spi_select_id);
#elif defined(SSD1306_SPI_INTERFACE)
	struct spi_device device = {
		.id = SSD1306_CS_PIN,
	};
	spi_master_init(SSD1306_SPI);
	spi_master_setup_device(SSD1306_SPI, &device, spi_flags,
			SSD1306_CLOCK_SPEED, spi_select_id);
#ifdef SAM
	spi_enable(SSD1306_SPI);
#endif
#endif
}

/**
 * \brief Initialize the OLED controller
 *
 * Call this function to initialize the hardware interface and the OLED
 * controller. When initialization is done the display is turned on and ready
 * to receive data.
 */
void ssd1306_init(void)
{
	// Do a hard reset of the OLED display controller
	ssd1306_hard_reset();

	// Initialize the interface
	ssd1306_interface_init();

	// 1/32 Duty (0x0F~0x3F)
	ssd1306_write_command(SSD1306_CMD_SET_MULTIPLEX_RATIO);
	ssd1306_write_command(0x1F);

	// Shift Mapping RAM Counter (0x00~0x3F)
	ssd1306_write_command(SSD1306_CMD_SET_DISPLAY_OFFSET);
	ssd1306_write_command(0x00);

	// Set Mapping RAM Display Start Line (0x00~0x3F)
	ssd1306_write_command(SSD1306_CMD_SET_START_LINE(0x00));

	// Set Column Address 0 Mapped to SEG0
	ssd1306_write_command(SSD1306_CMD_SET_SEGMENT_RE_MAP_COL127_SEG0);

	// Set COM/Row Scan Scan from COM63 to 0
	ssd1306_write_command(SSD1306_CMD_SET_COM_OUTPUT_SCAN_DOWN);

	// Set COM Pins hardware configuration
	ssd1306_write_command(SSD1306_CMD_SET_COM_PINS);
	ssd1306_write_command(0x02);

	ssd1306_set_contrast(0x8F);

	// Disable Entire display On
	ssd1306_write_command(SSD1306_CMD_ENTIRE_DISPLAY_AND_GDDRAM_ON);

	ssd1306_display_invert_disable();

	// Set Display Clock Divide Ratio / Oscillator Frequency (Default => 0x80)
	ssd1306_write_command(SSD1306_CMD_SET_DISPLAY_CLOCK_DIVIDE_RATIO);
	ssd1306_write_command(0x80);

	// Enable charge pump regulator
	ssd1306_write_command(SSD1306_CMD_SET_CHARGE_PUMP_SETTING);
	ssd1306_write_command(0x14);

	// Set VCOMH Deselect Level
	ssd1306_write_command(SSD1306_CMD_SET_VCOMH_DESELECT_LEVEL);
	ssd1306_write_command(0x40); // Default => 0x20 (0.77*VCC)

	// Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	ssd1306_write_command(SSD1306_CMD_SET_PRE_CHARGE_PERIOD);
	ssd1306_write_command(0xF1);

	ssd1306_display_on();
}

/**
 * \brief Display text on OLED screen.
 * \param string String to display.
 */
void ssd1306_write_text(const char *string)
{
	uint8_t *char_ptr;
	uint8_t i;

	while (*string != 0) {
		if (*string < 0x7F) {
			char_ptr = font_table[*string - 32];
			for (i = 1; i <= char_ptr[0]; i++) {
				ssd1306_write_data(char_ptr[i]);
			}
			ssd1306_write_data(0x00);
		}
			string++;
	}
}

