/**
 * \file
 *
 * \brief ILI9341 display controller component driver
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
#include "conf_ili9341.h"
#include "ili9341.h"
#include "ili9341_regs.h"
#include <sysclk.h>
#include <ioport.h>
#include <delay.h>

#if (SAM3S || SAM3N || SAM4S)
#  include <pdc.h>
#elif UC3
#  include <pdca.h>
#endif

#if (SAM3S || SAM3N || SAM4S) && defined(CONF_ILI9341_SPI)
#  define ILI9341_DMA_ENABLED
#  define ILI9341_DMA_CHUNK_SIZE   16
#elif UC3 && defined(CONF_ILI9341_PDCA_CHANNEL)
#  define ILI9341_DMA_ENABLED
#  define ILI9341_DMA_CHUNK_SIZE   16
#endif

/**
 * \internal
 * \brief Helper function to select the CS of the controller on the bus
 */
__always_inline static void ili9341_select_chip(void)
{
	ioport_set_pin_level(CONF_ILI9341_CS_PIN, false);
}

/**
 * \internal
 * \brief Helper function to de-select the CS of the controller on the bus
 */
__always_inline static void ili9341_deselect_chip(void)
{
	ioport_set_pin_level(CONF_ILI9341_CS_PIN, true);
}

/**
 * \internal
 * \brief Helper function to select command byte transmission mode
 */
__always_inline static void ili9341_select_command_mode(void)
{
	ioport_set_pin_level(CONF_ILI9341_DC_PIN, false);
}

/**
 * \internal
 * \brief Helper function to select data byte transmission mode
 */
__always_inline static void ili9341_select_data_mode(void)
{
	ioport_set_pin_level(CONF_ILI9341_DC_PIN, true);
}

/**
 * \internal
 * \brief Helper function to wait for the last send operation to complete
 */
__always_inline static void ili9341_wait_for_send_done(void)
{
#if defined(CONF_ILI9341_USART_SPI)
#  if XMEGA
	while (!usart_tx_is_complete(CONF_ILI9341_USART_SPI)) {
		/* Do nothing */
	}
	usart_clear_tx_complete(CONF_ILI9341_USART_SPI);
#  else
	/* Wait for TX to complete */
	while (!usart_spi_is_tx_empty(CONF_ILI9341_USART_SPI)) {
		/* Do nothing */
	}
#  endif
#elif defined(CONF_ILI9341_SPI)
	/* Wait for TX to complete */
	while (!spi_is_tx_empty(CONF_ILI9341_SPI)) {
		/* Do nothing */
	}
#endif
}

/**
 * \internal
 * \brief Helper function to send a byte over an arbitrary interface
 *
 * This function is used to hide what interface is used by the component
 * driver, e.g.  the component driver does not need to know if USART in SPI
 * mode is used or the native SPI module.
 *
 * \param data The byte to be transfered
 */
__always_inline static void ili9341_send_byte(uint8_t data)
{
#if defined(CONF_ILI9341_USART_SPI)
#  if XMEGA
	while (!usart_data_register_is_empty(CONF_ILI9341_USART_SPI)) {
		/* Do nothing */
	}

	irqflags_t flags = cpu_irq_save();
	usart_clear_tx_complete(CONF_ILI9341_USART_SPI);
	usart_put(CONF_ILI9341_USART_SPI, data);
	cpu_irq_restore(flags);
#  else
	usart_spi_write_single(CONF_ILI9341_USART_SPI, data);
#  endif
#elif defined(CONF_ILI9341_SPI)
	/* Wait for any previously running send data */
	ili9341_wait_for_send_done();

	spi_write_single(CONF_ILI9341_SPI, data);
#endif
}

/**
 * \internal
 * \brief Helper function to read a byte from an arbitrary interface
 *
 * This function is used to hide what interface is used by the component
 * driver, e.g.  the component driver does not need to know if USART in SPI
 * mode is used or the native SPI module.
 *
 * \retval uint8_t Byte of data read from the display controller
 */
__always_inline static uint8_t ili9341_read_byte(void)
{
	uint8_t data;

#if defined(CONF_ILI9341_USART_SPI)
#  if XMEGA
	/* Workaround for clearing the RXCIF for XMEGA */
	usart_rx_enable(CONF_ILI9341_USART_SPI);

	usart_put(CONF_ILI9341_USART_SPI, 0xFF);
	while (!usart_rx_is_complete(CONF_ILI9341_USART_SPI)) {
		/* Do nothing */
	}
	data = usart_get(CONF_ILI9341_USART_SPI);

	/* Workaround for clearing the RXCIF for XMEGA */
	usart_rx_disable(CONF_ILI9341_USART_SPI);
#  else
	usart_spi_read_single(CONF_ILI9341_USART_SPI, &data);
#  endif
#elif defined(CONF_ILI9341_SPI)
	spi_write_single(CONF_ILI9341_SPI, 0xFF);

	ili9341_wait_for_send_done();

	/* Wait for RX to complete */
	while (!spi_is_rx_full(CONF_ILI9341_SPI)) {
		/* Do nothing */
	}

	spi_read_single(CONF_ILI9341_SPI, &data);
#endif

	return data;
}

/**
 * \internal
 * \brief Sends a command to the controller, and prepares for parameter transfer
 *
 * Helper function to use for sending a command to the controller.
 *
 * \note After the command is sent, the display remains selected.
 *
 * \param command The command to send
 */
static void ili9341_send_command(uint8_t command)
{
	ili9341_select_command_mode();
	ili9341_select_chip();
	ili9341_send_byte(command);
	ili9341_wait_for_send_done();
	ili9341_select_data_mode();
}

static ili9341_coord_t limit_start_x, limit_start_y;
static ili9341_coord_t limit_end_x, limit_end_y;

/**
 * \internal
 * \brief Helper function to send the drawing limits (boundaries) to the display
 *
 * This function is used to send the currently set upper-left and lower-right
 * drawing limits to the display, as set through the various limit functions.
 *
 * \param send_end_limits  True to also send the lower-right drawing limits
 */
static void ili9341_send_draw_limits(const bool send_end_limits)
{
	ili9341_send_command(ILI9341_CMD_COLUMN_ADDRESS_SET);
	ili9341_send_byte(limit_start_x >> 8);
	ili9341_send_byte(limit_start_x & 0xFF);
	if (send_end_limits) {
		ili9341_send_byte(limit_end_x >> 8);
		ili9341_send_byte(limit_end_x & 0xFF);
	}
	ili9341_wait_for_send_done();
	ili9341_deselect_chip();

	ili9341_send_command(ILI9341_CMD_PAGE_ADDRESS_SET);
	ili9341_send_byte(limit_start_y >> 8);
	ili9341_send_byte(limit_start_y & 0xFF);
	if (send_end_limits) {
		ili9341_send_byte(limit_end_y >> 8);
		ili9341_send_byte(limit_end_y & 0xFF);
	}
	ili9341_wait_for_send_done();
	ili9341_deselect_chip();
}

/**
 * \brief Set the display top left drawing limit
 *
 * Use this function to set the top left limit of the drawing limit box.
 *
 * \param x The x coordinate of the top left corner
 * \param y The y coordinate of the top left corner
 */
void ili9341_set_top_left_limit(ili9341_coord_t x, ili9341_coord_t y)
{
	limit_start_x = x;
	limit_start_y = y;

	ili9341_send_draw_limits(false);
}

/**
 * \brief Set the display bottom right drawing limit
 *
 * Use this function to set the bottom right corner of the drawing limit box.
 *
 * \param x The x coordinate of the bottom right corner
 * \param y The y coordinate of the bottom right corner
 */
void ili9341_set_bottom_right_limit(ili9341_coord_t x, ili9341_coord_t y)
{
	limit_end_x = x;
	limit_end_y = y;

	ili9341_send_draw_limits(true);
}

/**
 * \brief Set the full display drawing limits
 *
 * Use this function to set the full drawing limit box.
 *
 * \param start_x The x coordinate of the top left corner
 * \param start_y The y coordinate of the top left corner
 * \param end_x The x coordinate of the bottom right corner
 * \param end_y The y coordinate of the bottom right corner
 */
void ili9341_set_limits(ili9341_coord_t start_x, ili9341_coord_t start_y,
		ili9341_coord_t end_x, ili9341_coord_t end_y)
{
	limit_start_x = start_x;
	limit_start_y = start_y;
	limit_end_x = end_x;
	limit_end_y = end_y;

	ili9341_send_draw_limits(true);
}

/**
 * \brief Read a single color from the graphical memory
 *
 * Use this function to read a color from the graphical memory of the
 * controller.
 *
 * Limits have to be set prior to calling this function, e.g.:
 * \code
	ili9341_set_top_left_limit(0, 0);
	ili9341_set_bottom_right_limit(320, 240);
	...
\endcode
 *
 * \retval ili9341_color_t The read color pixel
 */
ili9341_color_t ili9341_read_gram(void)
{
	uint8_t red, green, blue;

	ili9341_send_command(ILI9341_CMD_MEMORY_READ);

	/* No interesting data in the first byte, hence read and discard */
	red = ili9341_read_byte();

	red = ili9341_read_byte();
	green = ili9341_read_byte();
	blue = ili9341_read_byte();

	ili9341_deselect_chip();

	return ILI9341_COLOR(red, green, blue);
}

/**
 * \brief Write the graphical memory with a single color pixel
 *
 * Use this function to write a single color pixel to the controller memory.
 *
 * Limits have to be set prior to calling this function, e.g.:
 * \code
	ili9341_set_top_left_limit(0, 0);
	ili9341_set_bottom_right_limit(320, 240);
	...
\endcode
 *
 * \param color The color pixel to write to the screen
 */
void ili9341_write_gram(ili9341_color_t color)
{
	/* Only 16-bit color supported */
	Assert(sizeof(color) == 2);

	ili9341_send_command(ILI9341_CMD_MEMORY_WRITE);
	ili9341_send_byte(color);
	ili9341_send_byte(color >> 8);
	ili9341_wait_for_send_done();
	ili9341_deselect_chip();
}

/**
 * \brief Copy pixels from SRAM to the screen
 *
 * Used to copy a large quantitative of data to the screen in one go.
 *
 * Limits have to be set prior to calling this function, e.g.:
 * \code
	ili9341_set_top_left_limit(0, 0);
	ili9341_set_bottom_right_limit(320, 240);
	...
\endcode
 *
 * \param pixels Pointer to the pixel data
 * \param count Number of pixels to copy to the screen
 */
void ili9341_copy_pixels_to_screen(const ili9341_color_t *pixels, uint32_t count)
{
	const ili9341_color_t *pixel = pixels;

	/* Sanity check to make sure that the pixel count is not zero */
	Assert(count > 0);

	ili9341_send_command(ILI9341_CMD_MEMORY_WRITE);

#if defined(ILI9341_DMA_ENABLED)
	ili9341_color_t chunk_buf[ILI9341_DMA_CHUNK_SIZE];
	uint32_t chunk_len;

#  if SAM
	Pdc *SPI_DMA = spi_get_pdc_base(CONF_ILI9341_SPI);
	pdc_packet_t spi_pdc_data;

	pdc_enable_transfer(SPI_DMA, PERIPH_PTCR_TXTEN);
	spi_pdc_data.ul_addr = (uint32_t)chunk_buf;
#  elif UC3
	pdca_set_transfer_size(CONF_ILI9341_PDCA_CHANNEL,
			PDCA_TRANSFER_SIZE_BYTE);
	pdca_set_peripheral_select(CONF_ILI9341_PDCA_CHANNEL,
			CONF_ILI9341_PDCA_PID);
#  endif

	while (count)
	{
		/* We need to copy out the data to send in chunks into RAM, as the PDC
		 * does not allow FLASH->Peripheral transfers */
		chunk_len = min(ILI9341_DMA_CHUNK_SIZE, count);

		/* Wait for pending transfer to complete */
		ili9341_wait_for_send_done();

		for (uint32_t i = 0; i < chunk_len; i++) {
			chunk_buf[i] = le16_to_cpu(pixel[i]);
		}

#  if SAM
		spi_pdc_data.ul_size = (uint32_t)sizeof(ili9341_color_t) * chunk_len;
		pdc_tx_init(SPI_DMA, NULL, &spi_pdc_data);
#  elif UC3
		pdca_reload_channel(CONF_ILI9341_PDCA_CHANNEL, chunk_buf,
				(uint32_t)sizeof(ili9341_color_t) * chunk_len);
		pdca_enable(CONF_ILI9341_PDCA_CHANNEL);
#  endif

		pixel += chunk_len;
		count -= chunk_len;
	}

	ili9341_wait_for_send_done();
	ili9341_deselect_chip();

#  if SAM
	pdc_disable_transfer(SPI_DMA, PERIPH_PTCR_TXTEN);
#  elif UC3
	pdca_disable(CONF_ILI9341_PDCA_CHANNEL);
#  endif
#else
	while (count--) {
		ili9341_send_byte(*pixel);
		ili9341_send_byte(*pixel >> 8);

		pixel++;
	}

	ili9341_wait_for_send_done();
	ili9341_deselect_chip();
#endif
}

#if XMEGA
/**
 * \brief Copy pixels from progmem to the screen
 *
 * This function can be used to copy data from program memory (flash) to the
 * display.
 *
 * Limits have to be set prior to calling this function, e.g.:
 * \code
	ili9341_set_top_left_limit(0, 0);
	ili9341_set_bottom_right_limit(320, 240);
	...
\endcode
 *
 * \param pixels Pointer to the progmem data
 * \param count Number of pixels to write
 */
void ili9341_copy_progmem_pixels_to_screen(
		ili9341_color_t PROGMEM_PTR_T pixels, uint32_t count)
{
	ili9341_color_t color;

	/* Sanity check to make sure that the pixel count is not zero */
	Assert(count > 0);

	ili9341_send_command(ILI9341_CMD_MEMORY_WRITE);

	while (count--) {
		color = PROGMEM_READ_WORD(pixels);

		ili9341_send_byte(color);
		ili9341_send_byte(color >> 8);

		pixels++;
	}

	ili9341_wait_for_send_done();
	ili9341_deselect_chip();
}
#endif

/**
 * \brief Set a given number of pixels to the same color
 *
 * Use this function to write a certain number of pixels to the same color
 * within a set limit.
 *
 * Limits have to be set prior to calling this function, e.g.:
 * \code
	ili9341_set_top_left_limit(0, 0);
	ili9341_set_bottom_right_limit(320, 240);
	...
\endcode
 *
 * \param color The color to write to the display
 * \param count The number of pixels to write with this color
 */
void ili9341_duplicate_pixel(const ili9341_color_t color, uint32_t count)
{
	/* Sanity check to make sure that the pixel count is not zero */
	Assert(count > 0);

	ili9341_send_command(ILI9341_CMD_MEMORY_WRITE);

#if defined(ILI9341_DMA_ENABLED)
	ili9341_color_t chunk_buf[ILI9341_DMA_CHUNK_SIZE];
	uint32_t chunk_len;

#  if SAM
	Pdc *SPI_DMA = spi_get_pdc_base(CONF_ILI9341_SPI);
	pdc_packet_t spi_pdc_data;

	pdc_enable_transfer(SPI_DMA, PERIPH_PTCR_TXTEN);
	spi_pdc_data.ul_addr = (uint32_t)chunk_buf;
#  elif UC3
	pdca_set_transfer_size(CONF_ILI9341_PDCA_CHANNEL,
			PDCA_TRANSFER_SIZE_BYTE);
	pdca_set_peripheral_select(CONF_ILI9341_PDCA_CHANNEL,
			CONF_ILI9341_PDCA_PID);
#  endif

	for (uint32_t i = 0; i < ILI9341_DMA_CHUNK_SIZE; i++) {
		chunk_buf[i] = le16_to_cpu(color);
	}

	while (count)
	{
		chunk_len = min(ILI9341_DMA_CHUNK_SIZE, count);

		ili9341_wait_for_send_done();

#  if SAM
		spi_pdc_data.ul_size = (uint32_t)sizeof(ili9341_color_t) * chunk_len;
		pdc_tx_init(SPI_DMA, NULL, &spi_pdc_data);
#  elif UC3
		pdca_reload_channel(CONF_ILI9341_PDCA_CHANNEL, chunk_buf,
				(uint32_t)sizeof(ili9341_color_t) * chunk_len);
		pdca_enable(CONF_ILI9341_PDCA_CHANNEL);
#  endif

		count -= chunk_len;
	}

	ili9341_wait_for_send_done();
	ili9341_deselect_chip();

#  if SAM
	pdc_disable_transfer(SPI_DMA, PERIPH_PTCR_TXTEN);
#  elif UC3
	pdca_disable(CONF_ILI9341_PDCA_CHANNEL);
#  endif
#else
	while (count--) {
		ili9341_send_byte(color);
		ili9341_send_byte(color >> 8);
	}

	ili9341_wait_for_send_done();
	ili9341_deselect_chip();
#endif
}

/**
 * \brief Copy pixels from the screen to a pixel buffer
 *
 * Use this function to copy pixels from the display to an internal SRAM buffer.
 *
 * Limits have to be set prior to calling this function, e.g.:
 * \code
	ili9341_set_top_left_limit(0, 0);
	ili9341_set_bottom_right_limit(320, 240);
	...
\endcode
 *
 * \param pixels Pointer to the pixel buffer to read to
 * \param count Number of pixels to read
 */
void ili9341_copy_pixels_from_screen(ili9341_color_t *pixels, uint32_t count)
{
	uint8_t red, green, blue;

	/* Sanity check to make sure that the pixel count is not zero */
	Assert(count > 0);

	ili9341_send_command(ILI9341_CMD_MEMORY_READ);

	/* No interesting data in the first byte, hence read and discard */
	red = ili9341_read_byte();

	while (count--) {
		red = ili9341_read_byte();
		green = ili9341_read_byte();
		blue = ili9341_read_byte();

		*pixels = ILI9341_COLOR(red, green, blue);
		pixels++;
	}

	ili9341_deselect_chip();
}

/**
 * \internal
 * \brief Initialize the hardware interface to the controller
 *
 * This will initialize the module used for communication with the controller.
 * Currently supported interfaces by this component driver are the SPI
 * interface through either the SPI module in master mode or the USART in
 * Master SPI mode.  Configuration must be done in the associated
 * conf_ili9341.h file.
 */
static void ili9341_interface_init(void)
{
#if defined(CONF_ILI9341_USART_SPI) || defined(CONF_ILI9341_SPI)
	spi_flags_t spi_flags = SPI_MODE_0;
	board_spi_select_id_t spi_select_id = 0;
#else
	#error Interface for ILI9341 has not been selected or interface not\
	supported, please configure component driver using the conf_ili9341.h\
	file!
#endif

#if defined(CONF_ILI9341_USART_SPI)
	struct usart_spi_device device = {
		.id = 0,
	};

	usart_spi_init(CONF_ILI9341_USART_SPI);
	usart_spi_setup_device(CONF_ILI9341_USART_SPI, &device, spi_flags,
			CONF_ILI9341_CLOCK_SPEED, spi_select_id);

#elif defined(CONF_ILI9341_SPI)
	struct spi_device device = {
		.id = 0,
	};

	spi_master_init(CONF_ILI9341_SPI);
	spi_master_setup_device(CONF_ILI9341_SPI, &device, spi_flags,
			CONF_ILI9341_CLOCK_SPEED, spi_select_id);
	spi_enable(CONF_ILI9341_SPI);

#  if UC3
	spi_set_chipselect(CONF_ILI9341_SPI, ~(1 << 0));

#    if defined(ILI9341_DMA_ENABLED)
	sysclk_enable_peripheral_clock(&AVR32_PDCA);
#    endif
#  endif

	/* Send one dummy byte for the spi_is_tx_ok() to work as expected */
	spi_write_single(CONF_ILI9341_SPI, 0);
#endif
}

/**
 * \internal
 * \brief Initialize all the display registers
 *
 * This function will set up all the internal registers according the the
 * manufacturer's description.
 */
static void ili9341_controller_init_registers(void)
{
	ili9341_send_command(ILI9341_CMD_POWER_CONTROL_A);
	ili9341_send_byte(0x39);
	ili9341_send_byte(0x2C);
	ili9341_send_byte(0x00);
	ili9341_send_byte(0x34);
	ili9341_send_byte(0x02);
	ili9341_wait_for_send_done();
	ili9341_deselect_chip();

	ili9341_send_command(ILI9341_CMD_POWER_CONTROL_B);
	ili9341_send_byte(0x00);
	ili9341_send_byte(0xAA);
	ili9341_send_byte(0XB0);
	ili9341_wait_for_send_done();
	ili9341_deselect_chip();

	ili9341_send_command(ILI9341_CMD_PUMP_RATIO_CONTROL);
	ili9341_send_byte(0x30);
	ili9341_wait_for_send_done();
	ili9341_deselect_chip();

	ili9341_send_command(ILI9341_CMD_POWER_CONTROL_1);
	ili9341_send_byte(0x25);
	ili9341_wait_for_send_done();
	ili9341_deselect_chip();

	ili9341_send_command(ILI9341_CMD_POWER_CONTROL_2);
	ili9341_send_byte(0x11);
	ili9341_wait_for_send_done();
	ili9341_deselect_chip();

	ili9341_send_command(ILI9341_CMD_VCOM_CONTROL_1);
	ili9341_send_byte(0x5C);
	ili9341_send_byte(0x4C);
	ili9341_wait_for_send_done();
	ili9341_deselect_chip();

	ili9341_send_command(ILI9341_CMD_VCOM_CONTROL_2);
	ili9341_send_byte(0x94);
	ili9341_wait_for_send_done();
	ili9341_deselect_chip();

	ili9341_send_command(ILI9341_CMD_DRIVER_TIMING_CONTROL_A);
	ili9341_send_byte(0x85);
	ili9341_send_byte(0x01);
	ili9341_send_byte(0x78);
	ili9341_wait_for_send_done();
	ili9341_deselect_chip();

	ili9341_send_command(ILI9341_CMD_DRIVER_TIMING_CONTROL_B);
	ili9341_send_byte(0x00);
	ili9341_send_byte(0x00);
	ili9341_wait_for_send_done();
	ili9341_deselect_chip();

	ili9341_send_command(ILI9341_CMD_COLMOD_PIXEL_FORMAT_SET);
	ili9341_send_byte(0x05);
	ili9341_wait_for_send_done();
	ili9341_deselect_chip();

	ili9341_set_orientation(0);
	ili9341_set_limits(0, 0, ILI9341_DEFAULT_WIDTH,
			ILI9341_DEFAULT_HEIGHT);
}

/**
 * \internal
 * \brief Send display commands to exit standby mode
 *
 * This function is used to exit the display standby mode, which is the default
 * mode after a reset signal to the display.
 */
static void ili9341_exit_standby(void)
{
	ili9341_send_command(ILI9341_CMD_SLEEP_OUT);
	ili9341_deselect_chip();
	delay_ms(150);
	ili9341_send_command(ILI9341_CMD_DISPLAY_ON);
	ili9341_deselect_chip();
}

/**
 * \internal
 * \brief Reset the display using the digital control interface
 *
 * Controls the reset pin of the display controller to reset the display.
 */
static void ili9341_reset_display(void)
{
	ioport_set_pin_level(CONF_ILI9341_RESET_PIN, true);
	delay_ms(10);
	ioport_set_pin_level(CONF_ILI9341_RESET_PIN, false);
	delay_ms(10);
	ioport_set_pin_level(CONF_ILI9341_RESET_PIN, true);
	delay_ms(150);
}

/**
 * \brief Initialize the controller
 *
 * Used to initialize the ILI9341 display controller by setting up the hardware
 * interface, and setting up the controller according to the manufacturer's
 * description. It also set up the screen orientation to the default state
 * (portrait).
 */
void ili9341_init(void)
{
	/* Initialize the communication interface */
	ili9341_interface_init();

	/* Reset the display */
	ili9341_reset_display();

	/* Send commands to exit standby mode */
	ili9341_exit_standby();

	/* Write all the controller registers with correct values */
	ili9341_controller_init_registers();
}

/**
 * \brief Sets the orientation of the display data
 *
 * Configures the display for a given orientation, including mirroring and/or
 * screen rotation.
 *
 * \param flags Orientation flags to use, see \ref ILI9341_FLIP_X, \ref ILI9341_FLIP_Y
 *        and \ref ILI9341_SWITCH_XY.
 */
void ili9341_set_orientation(uint8_t flags)
{
	uint8_t madctl = 0x48;

	/* Pretend the display is in landscape mode by default to match other display drivers */
	flags ^= ILI9341_SWITCH_XY | ILI9341_FLIP_X;

	if (flags & ILI9341_FLIP_X) {
		madctl &= ~(1 << 6);
	}

	if (flags & ILI9341_FLIP_Y) {
		madctl |= 1 << 7;
	}

	if (flags & ILI9341_SWITCH_XY) {
		madctl |= 1 << 5;
	}

	ili9341_send_command(ILI9341_CMD_MEMORY_ACCESS_CONTROL);
	ili9341_send_byte(madctl);
	ili9341_wait_for_send_done();
	ili9341_deselect_chip();
}
