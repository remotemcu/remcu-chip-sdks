/**
 * \file
 *
 * \brief HX8347A display controller driver
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include "conf_hx8347a.h"
#include "hx8347a.h"
#include "hx8347a_regs.h"
#include <sysclk.h>
#include <gpio.h>
#include <delay.h>

/**
 * \internal
 * \brief Helper function to select the CS of the controller on the bus
 */
__always_inline static void hx8347a_select_chip(void)
{
	gpio_set_pin_low(CONF_HX8347A_CS_PIN);
}

/**
 * \internal
 * \brief Helper function to de-select the CS of the controller on the bus
 */
__always_inline static void hx8347a_deselect_chip(void)
{
	gpio_set_pin_high(CONF_HX8347A_CS_PIN);
}

/**
 * \internal
 * \brief Helper function to write a number of bytes
 *
 * This function is used to write several bytes to the interface in one go.
 *
 * \param data   pointer to the location of the data to write
 * \param length the number of bytes to write
 */
__always_inline static void hx8347a_write_packet(const uint8_t *data,
		const uint32_t length)
{
#if defined(CONF_HX8347A_USART_SPI)
	usart_spi_write_packet(CONF_HX8347A_USART_SPI, data, length);
#elif defined(CONF_HX8347A_SPI)
	spi_write_packet(CONF_HX8347A_SPI, data, length);
#endif
}

/**
 * \internal
 * \brief Helper function to send a byte over an arbitrary interface
 *
 * This function is used to hide what interface is used by the driver, e.g.
 * the driver does not need to know if USART in SPI mode is used or the native
 * SPI module.
 *
 * \param data the byte to be transfered
 */
__always_inline static void hx8347a_send_byte(uint8_t data)
{
#if defined(CONF_HX8347A_USART_SPI)

	/* A workaround for optimizing data transfer had to be done for the
	 * XMEGA in order for the display to work correctly at all SPI clock
	 * clock speeds */

#  if UC3
	usart_spi_write_packet(CONF_HX8347A_USART_SPI, &data, 1);

#  elif XMEGA
	usart_spi_write_single(CONF_HX8347A_USART_SPI, data);

#  endif

#elif defined(CONF_HX8347A_SPI)
	spi_write_single(CONF_HX8347A_SPI, data);

	/* Wait for TX to complete */
	while (!spi_is_tx_ok(CONF_HX8347A_SPI)) {
		/* Do nothing */
	}
#endif
}

/**
 * \internal
 * \brief Helper function to read a byte from an arbitrary interface
 *
 * This function is used to hide what interface is used by the driver, e.g.
 * the driver does not need to know if USART in SPI mode is used or the native
 * SPI module.
 */
__always_inline static uint8_t hx8347a_read_byte(void)
{
	uint8_t data;
#if defined(CONF_HX8347A_USART_SPI)
#  if UC3

	/* A workaround for optimizing data transfer had to be done for the
	 * XMEGA in order for the display to work correctly at all SPI clock
	 * clock speeds */

	/* This function could also be used for XMEGA but results in a very slow
	 * framerate, hence a workaround has been implemented for the XMEGA */
	usart_spi_read_packet(CONF_HX8347A_USART_SPI, &data, 1);

#  elif XMEGA
	usart_spi_read_single(CONF_HX8347A_USART_SPI, &data);

#  endif
#elif defined(CONF_HX8347A_SPI)
	spi_write_single(CONF_HX8347A_SPI, 0xFF);

	/* Wait for RX to complete */
	while (!spi_is_rx_full(CONF_HX8347A_SPI)) {
		/* Do nothing */
	}

	spi_read_single(CONF_HX8347A_SPI, &data);
#endif
	return data;
}

/**
 * \internal
 * \brief Used to select a register within the controller
 *
 * Helper function to use for selecting a register to write to.
 *
 * \param address the address of the register to select
 */
static void hx8347a_select_register(uint8_t address)
{
	hx8347a_select_chip();
	hx8347a_send_byte(HX8347A_START_WRITEIDX);
	hx8347a_send_byte(address);
	hx8347a_deselect_chip();
}

/**
 * \brief Write a specific register in the controller with a single byte
 *
 * Use this function to write a value to a specific register in the display
 * controller.
 *
 * \param address the address of the register to write
 * \param value   the value to be written
 */
void hx8347a_write_register(uint8_t address, uint8_t value)
{
	hx8347a_select_register(address);
	hx8347a_select_chip();
	hx8347a_send_byte(HX8347A_START_WRITEREG);
	hx8347a_send_byte(value);
	hx8347a_deselect_chip();
}

/**
 * \brief Read the value of a specific register in the controller
 *
 * Use this function to get the value of a specific register in the display
 * controller.
 *
 * \param address the address of the register to read
 */
uint8_t hx8347a_read_register(uint8_t address)
{
	uint8_t value;

	hx8347a_select_register(address);
	hx8347a_select_chip();
	hx8347a_send_byte(HX8347A_START_READREG);
	value = hx8347a_read_byte();
	hx8347a_deselect_chip();

	return value;
}

/**
 * \brief Helper function for easier register access
 *
 * Use this function to clear specific bits in the controller registers.
 *
 * \param address the address of the register to clear
 * \param bitmask the bitmask of the specific bits to clear
 */
void hx8347a_clear_register(uint8_t address, uint8_t bitmask)
{
	uint8_t value;

	value = hx8347a_read_register(address);
	value &= ~bitmask;
	hx8347a_write_register(address, value);
}

/**
 * \brief Helper function for easier register access
 *
 * Use this function to set specific bits in the controller registers.
 *
 * \param address the address of the controller register to set
 * \param bitmask the bitmask describing which bit to set
 */
void hx8347a_set_register(uint8_t address, uint8_t bitmask)
{
	uint8_t value;

	value = hx8347a_read_register(address);
	value |= bitmask;
	hx8347a_write_register(address, value);
}

/**
 * \brief Read a single color from the graphical memory
 *
 * Use this function to read a color from the graphical memory of the
 * controller.
 * Limits have to be set prior to calling this function, e.g.:
 * \code
	hx8347a_set_top_left_limit(0, 0);
	hx8347a_set_bottom_right_limit(320, 240);
	...
\endcode
 *
 * \retval hx8347a_color_t the read color pixel
 */
hx8347a_color_t hx8347a_read_gram(void)
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;

	hx8347a_select_register(HX8347A_SRAMWRITE);
	hx8347a_select_chip();
	hx8347a_send_byte(HX8347A_START_READREG);

	/* First byte is useless */
	red = hx8347a_read_byte();

	/* Read each individual color */
	red = hx8347a_read_byte();
	green = hx8347a_read_byte();
	blue = hx8347a_read_byte();

	hx8347a_deselect_chip();

	/* Convert to the correct GFX color type e.g. 16-bit or 18-bit */
	return HX8347A_COLOR(red, green, blue);
}

/**
 * \brief Write the graphical memory with a single color pixel
 *
 * Use this function to write a single color pixel to the controller memory.
 * Limits have to be set prior to calling this function, e.g.:
 * \code
	hx8347a_set_top_left_limit(0, 0);
	hx8347a_set_bottom_right_limit(320, 240);
	...
\endcode
 *
 * \param color the color pixel to write to the screen
 */
void hx8347a_write_gram(hx8347a_color_t color)
{
	/* Only 16-bit color supported */
	Assert(sizeof(color) == 2);

	hx8347a_select_register(HX8347A_SRAMWRITE);
	hx8347a_select_chip();
	hx8347a_send_byte(HX8347A_START_WRITEREG);

	hx8347a_send_byte(color & 0xFF);
	hx8347a_send_byte(color >> 8);
	hx8347a_deselect_chip();
}

/**
 * \brief Set the display top left drawing limit
 *
 * Use this function to set the top left limit of the drawing limit box.
 *
 * \param x the x coordinate of the top left corner
 * \param y the y coordinate of the top left corner
 */
void hx8347a_set_top_left_limit(hx8347a_coord_t x, hx8347a_coord_t y)
{
	hx8347a_write_register(HX8347A_COLSTARTHIGH, (x >> 8));
	hx8347a_write_register(HX8347A_COLSTARTLOW, (x & 0xff));
	hx8347a_write_register(HX8347A_ROWSTARTHIGH, (y >> 8));
	hx8347a_write_register(HX8347A_ROWSTARTLOW, (y & 0xff));
}

/**
 * \brief Set the display bottom right drawing limit
 *
 * Use this function to set the bottom right corner of the drawing limit box.
 *
 * \param x the x coordinate of the bottom right corner
 * \param y the y coordinate of the bottom right corner
 */
void hx8347a_set_bottom_right_limit(hx8347a_coord_t x, hx8347a_coord_t y)
{
	hx8347a_write_register(HX8347A_COLENDHIGH, (x >> 8));
	hx8347a_write_register(HX8347A_COLENDLOW, (x & 0xff));
	hx8347a_write_register(HX8347A_ROWENDHIGH, (y >> 8));
	hx8347a_write_register(HX8347A_ROWENDLOW, (y & 0xff));
}

/**
 * \brief Set the fully display drawing limits
 *
 * Use this function to set the full drawing limit box.
 *
 * \param start_x the x coordinate of the top left corner
 * \param start_y the y coordinate of the top left corner
 * \param end_x the x coordinate of the bottom right corner
 * \param end_y the y coordinate of the bottom right corner
 */
void hx8347a_set_limits(hx8347a_coord_t start_x, hx8347a_coord_t start_y,
		hx8347a_coord_t end_x, hx8347a_coord_t end_y)
{
	hx8347a_set_top_left_limit(start_x, start_y);
	hx8347a_set_bottom_right_limit(end_x, end_y);
}

/**
 * \brief Set the display orientation
 *
 * This is used for orienting the display in different directions, the most
 * obvious once are landscape or portrait mode.
 *
 * Example of usage (for setting landscape mode):
 * \code
	hx8347a_set_orientation(HX8347A_FLIP_Y | HX8347A_SWITCH_XY);
\endcode
 * Or use the GFX defines:
 * \code
	hx8347a_set_orientation(GFX_FLIP_Y | GFX_SWITCH_XY);
\endcode
 *
 * \param flags different flags used to define what orientation to use.
 */
void hx8347a_set_orientation(uint8_t flags)
{
	uint8_t setting = 0;
	uint8_t regval;

	setting |= (flags & HX8347A_FLIP_X ? HX8347A_FLIP_X_MASK : 0);
	setting |= (flags & HX8347A_FLIP_Y ? HX8347A_FLIP_Y_MASK : 0);
	setting |= (flags & HX8347A_SWITCH_XY ? HX8347A_SWITCH_XY_MASK : 0);

	/* Read-modify-write HIMAX control register */
	regval = hx8347a_read_register(HX8347A_MEMACCESSCTRL);
	regval &= ~(HX8347A_FLIP_X_MASK | HX8347A_FLIP_Y_MASK | HX8347A_SWITCH_XY_MASK);
	regval |= setting;
	hx8347a_write_register(HX8347A_MEMACCESSCTRL, regval);
}

/**
 * \brief Copy pixels from SRAM to the screen
 *
 * Used to copy a large quantitative of data to the screen in one go.
 * Limits have to be set prior to calling this function, e.g.:
 * \code
	hx8347a_set_top_left_limit(0, 0);
	hx8347a_set_bottom_right_limit(320, 240);
	...
\endcode
 *
 * \param pixels pointer to the pixel data
 * \param count number of pixels to copy to the screen
 */
void hx8347a_copy_pixels_to_screen(const hx8347a_color_t *pixels, uint32_t count)
{
	uint32_t byte_count;

	/* Sanity check to make sure that the pixel count is not zero */
	Assert(count > 0);

	hx8347a_select_register(HX8347A_SRAMWRITE);
	hx8347a_select_chip();
	hx8347a_send_byte(HX8347A_START_WRITEREG);

	/* Find number of bytes to transfer */
	byte_count = count * sizeof(hx8347a_color_t);

	hx8347a_write_packet((uint8_t *)pixels, byte_count);

	hx8347a_deselect_chip();
}

/**
 * \brief Copy pixels from progmem to the screen
 *
 * This function can be used to copy data from program memory (flash) to the
 * display.
 * Limits have to be set prior to calling this function, e.g.:
 * \code
	hx8347a_set_top_left_limit(0, 0);
	hx8347a_set_bottom_right_limit(320, 240);
	...
\endcode
 *
 * \param pixels pointer to the progmem data
 * \param count number of pixels to write
 */
void hx8347a_copy_progmem_pixels_to_screen(
		hx8347a_color_t PROGMEM_PTR_T pixels, uint32_t count)
{
	uint32_t byte_count;
	uint8_t PROGMEM_PTR_T byte_ptr = (uint8_t PROGMEM_PTR_T)pixels;

	/* Sanity check to make sure that the pixel count is not zero */
	Assert(count > 0);

	hx8347a_select_register(HX8347A_SRAMWRITE);
	hx8347a_select_chip();
	hx8347a_send_byte(HX8347A_START_WRITEREG);

	/* Find number of bytes to transfer */
	byte_count = count * sizeof(hx8347a_color_t);

	while (byte_count > 0) {
		hx8347a_send_byte(PROGMEM_READ_BYTE(byte_ptr));
		byte_count--;
		byte_ptr++;
	}

	hx8347a_deselect_chip();
}

/**
 * \brief Write a set color to the screen
 *
 * Use this function to write a certain number of pixels to the same color
 * within a set limit.
 * Limits have to be set prior to calling this function, e.g.:
 * \code
	hx8347a_set_top_left_limit(0, 0);
	hx8347a_set_bottom_right_limit(320, 240);
	...
\endcode
 *
 * \param color the color to write to the display
 * \param count the number of pixels to write with this color
 */
void hx8347a_duplicate_pixel(const hx8347a_color_t color, uint32_t count)
{
	uint32_t transmit_count;

	/* Sanity check to make sure that the pixel count is not zero */
	Assert(count > 0);

	hx8347a_select_register(HX8347A_SRAMWRITE);
	hx8347a_select_chip();
	hx8347a_send_byte(HX8347A_START_WRITEREG);

	transmit_count = count;

	while (transmit_count--) {
		hx8347a_write_packet((uint8_t *)(&color), 2);
	}

	hx8347a_deselect_chip();
}

/**
 * \brief Copy pixels from the screen to a pixel buffer
 *
 * Use this function to copy pixels from the display to an internal SRAM buffer.
 * Limits have to be set prior to calling this function, e.g.:
 * \code
	hx8347a_set_top_left_limit(0, 0);
	hx8347a_set_bottom_right_limit(320, 240);
	...
\endcode
 *
 * \param pixels pointer to the pixel buffer to read to
 * \param count number of pixels to read
 */
void hx8347a_copy_pixels_from_screen(hx8347a_color_t *pixels, uint32_t count)
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;

	/* Sanity check to make sure that the pixel count is not zero */
	Assert(count > 0);

	hx8347a_select_register(HX8347A_SRAMWRITE);
	hx8347a_select_chip();
	hx8347a_send_byte(HX8347A_START_READREG);

	/* No interesting data in the first byte, hence read and discard */
	red = hx8347a_read_byte();

	while (count > 0) {
		red = hx8347a_read_byte();
		green = hx8347a_read_byte();
		blue = hx8347a_read_byte();

		*pixels = HX8347A_COLOR(red, green, blue);

		pixels++;
		count--;
	}

	hx8347a_deselect_chip();
}

/**
 * \internal
 * \brief Initialize the hardware interface to the controller
 *
 * This will initialize the module used for communication with the controller.
 * Currently supported interface by this driver is the SPI interface trough
 * either the SPI module in master mode or the USART in Master SPI mode.
 * Configurations has to be done in the \ref conf_hx8347a.h file.
 */
static void hx8347a_interface_init(void)
{
#if defined(CONF_HX8347A_USART_SPI) | defined(CONF_HX8347A_SPI)
	spi_flags_t spi_flags = SPI_MODE_3;
	board_spi_select_id_t spi_select_id = 0;
#else
	#error Interface for HX8347A has not been selected or interface not\
	supported, please configure driver using the conf_hx8347a.h file!
#endif

#if defined(CONF_HX8347A_USART_SPI)
	struct usart_spi_device device = {
		.id = CONF_HX8347A_CS_PIN,
	};
	usart_spi_init(CONF_HX8347A_USART_SPI);
	usart_spi_setup_device(CONF_HX8347A_USART_SPI, &device, spi_flags,
			CONF_HX8347A_CLOCK_SPEED, spi_select_id);
#elif defined(CONF_HX8347A_SPI)
	struct spi_device device = {
		.id = CONF_HX8347A_CS_PIN,
	};
	spi_master_init(CONF_HX8347A_SPI);
	spi_master_setup_device(CONF_HX8347A_SPI, &device, spi_flags,
			CONF_HX8347A_CLOCK_SPEED, spi_select_id);
#endif
}

/**
 * \internal
 * \brief Initialize all the display registers
 *
 * This function will set up all the internal registers according the the
 * manufacturer's description. What this values do are unfortunately
 * undocumented  from the manufacturer side.
 */
static void hx8347a_controller_init_registers(void)
{
	/* Undocumented values from the display manufacturer. */
	hx8347a_write_register(HX8347A_GAMMACTRL1, 0x94);
	hx8347a_write_register(HX8347A_GAMMACTRL2, 0x41);
	hx8347a_write_register(HX8347A_GAMMACTRL3, 0x00);
	hx8347a_write_register(HX8347A_GAMMACTRL4, 0x33);
	hx8347a_write_register(HX8347A_GAMMACTRL5, 0x23);
	hx8347a_write_register(HX8347A_GAMMACTRL6, 0x45);
	hx8347a_write_register(HX8347A_GAMMACTRL7, 0x44);
	hx8347a_write_register(HX8347A_GAMMACTRL8, 0x77);
	hx8347a_write_register(HX8347A_GAMMACTRL9, 0x12);
	hx8347a_write_register(HX8347A_GAMMACTRL10, 0xCC);
	hx8347a_write_register(HX8347A_GAMMACTRL11, 0x46);
	hx8347a_write_register(HX8347A_GAMMACTRL12, 0x82);

	hx8347a_write_register(HX8347A_DISPMODECTRL, 0x06);

	/* Not actually gamma, but driving timing,
	 *  required for noise removal for our LCD. */
	hx8347a_write_register(HX8347A_CYCLECTRL1, 0x01);
	hx8347a_write_register(HX8347A_CYCLECTRL2, 0x01);
	hx8347a_write_register(HX8347A_CYCLECTRL3, 0xF0);
	hx8347a_write_register(HX8347A_CYCLECTRL4, 0x00);
	hx8347a_write_register(HX8347A_CYCLECTRL5, 0x38);
	hx8347a_write_register(HX8347A_CYCLECTRL6, 0x0F);
	hx8347a_write_register(HX8347A_CYCLECTRL7, 0xF0);

	hx8347a_write_register(HX8347A_DISPCTRL2, 0x02);
	hx8347a_write_register(HX8347A_DISPCTRL3, 0x02);
	hx8347a_write_register(HX8347A_DISPCTRL4, 0x02);
	hx8347a_write_register(HX8347A_DISPCTRL5, 0x02);
	hx8347a_write_register(HX8347A_DISPCTRL6, 0x02);
	hx8347a_write_register(HX8347A_DISPCTRL7, 0x02);

	hx8347a_write_register(HX8347A_INTERNAL28, 0x0E);
	hx8347a_write_register(HX8347A_OSCCTRL1, 0x49);

	hx8347a_write_register(HX8347A_COLSTARTHIGH, 0x00);
	hx8347a_write_register(HX8347A_COLSTARTLOW, 0x00);
	hx8347a_write_register(HX8347A_COLENDHIGH, 0x00);
	hx8347a_write_register(HX8347A_COLENDLOW, 0xEF);
	hx8347a_write_register(HX8347A_ROWSTARTHIGH, 0x00);
	hx8347a_write_register(HX8347A_ROWSTARTLOW, 0x00);
	hx8347a_write_register(HX8347A_ROWENDHIGH, 0x01);
	hx8347a_write_register(HX8347A_ROWENDLOW, 0x3F);

	hx8347a_write_register(HX8347A_MEMACCESSCTRL, 0x08);

	hx8347a_write_register(HX8347A_CYCLECTRL1_X, 0x95);
	hx8347a_write_register(HX8347A_CYCLECTRL2_X, 0x95);
	hx8347a_write_register(HX8347A_CYCLECTRL3_X, 0xFF);
	hx8347a_write_register(HX8347A_DISPCTRL8, 0x7F);
	hx8347a_write_register(HX8347A_DISPCTRL9, 0x38);
	hx8347a_write_register(HX8347A_DISPCTRL10, 0x78);

	hx8347a_write_register(HX8347A_POWERCTRL3, 0x07);
	hx8347a_write_register(HX8347A_POWERCTRL4, 0x00);
	hx8347a_write_register(HX8347A_POWERCTRL5, 0x04);
	hx8347a_write_register(HX8347A_POWERCTRL6, 0x40);
	hx8347a_write_register(HX8347A_VCOMCTRL2, 0x38);
	hx8347a_write_register(HX8347A_VCOMCTRL3, 0x12);
	delay_ms(10);
	hx8347a_write_register(HX8347A_POWERCTRL2, 0x04);
	delay_ms(20);
	hx8347a_write_register(HX8347A_VCOMCTRL1, 0x80);
	delay_ms(5);
	hx8347a_write_register(HX8347A_POWERCTRL1, 0x08);
	delay_ms(50);
	hx8347a_write_register(HX8347A_POWERCTRL1, 0x10);
	delay_ms(50);
	hx8347a_write_register(HX8347A_DISPCTRL1, 0x04);
	delay_ms(50);
	hx8347a_write_register(HX8347A_DISPCTRL1, 0x24);
	hx8347a_write_register(HX8347A_DISPCTRL1, 0x2C);
	delay_ms(50);
	hx8347a_write_register(HX8347A_DISPCTRL1, 0x3C);
}

/**
 * \brief Initialize the controller
 *
 * Used to initialize the HX8347A display controller by setting up the hardware
 * interface, and setting up the controller according to the manufacturer's
 * description. It also set up the screen orientation to the default state
 * (portrait).
 */
void hx8347a_init(void)
{
	/* Initialize the communication interface */
	hx8347a_interface_init();

	/* Reset the display */
	hx8347a_reset_display();

	/* Send commands to exit standby mode */
	hx8347a_exit_standby();

	/* Write all the controller registers with correct values */
	hx8347a_controller_init_registers();
}

/**
 * \internal
 * \brief Send display commands to exit standby mode
 *
 * This function is used to exit the display standby mode, which is the default
 * mode after a reset signal to the display.
 */
void hx8347a_exit_standby(void)
{
	hx8347a_set_register(HX8347A_OSCCTRL1, 0x3A | (1 << HX8347A_OSC_EN));
	delay_ms(5);
	hx8347a_clear_register(HX8347A_POWERCTRL1, (1 << HX8347A_STB));
}

/**
 * \internal
 * \brief Reset the display using the digital control interface
 *
 * Controls the reset pin of the display controller to reset the display.
 */
void hx8347a_reset_display(void)
{
	delay_ms(1);
	gpio_set_pin_low(CONF_HX8347A_RESET_PIN);
	delay_ms(1);
	gpio_set_pin_high(CONF_HX8347A_RESET_PIN);
	delay_ms(5);
}
