/**
 * \file
 *
 * \brief AVR MEGARF USART in SPI mode driver functions.
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
#include "usart_spi.h"
#include "sysclk.h"

/**
 * \brief Initializes the USART in SPI master mode.
 *
 * \param usart Base address of the USART instance.
 *
 */
void usart_spi_init(USART_t *usart)
{
#ifdef USARTA0
	if ((uintptr_t)usart == (uintptr_t)&UCSR0A) {
		sysclk_enable_module(POWER_RED_REG0, PRUSART0_bm);
	}

#endif
#ifdef USARTA1
	if ((uintptr_t)usart == (uintptr_t)&UCSR1A) {
		sysclk_enable_module(POWER_RED_REG1, PRUSART1_bm);
	}

#endif
}

/**
 * \brief Setup a USART in SPI mode device.
 *
 * The returned device descriptor structure must be passed to the driver
 * whenever that device should be used as current slave device.
 *
 * \param usart     Base address of the USART instance.
 * \param device    Pointer to usart device struct that should be initialized.
 * \param flags     USART configuration flags. Common flags for all
 *                  implementations are the usart modes SPI_MODE_0 ...
 *                  SPI_MODE_3.
 * \param baud_rate Baud rate for communication with slave device in Hz.
 * \param sel_id    Board specific select id
 */
void usart_spi_setup_device(USART_t *usart, struct usart_spi_device *device,
		spi_flags_t flags, unsigned long baud_rate,
		board_spi_select_id_t sel_id)
{
	usart_spi_options_t opt;
	opt.baudrate = baud_rate;
	opt.spimode = flags;
	opt.data_order = false;
	usart_init_spi(usart, &opt);
}

/**
 * \brief Enables the USART for the specified USART in SPI mode.
 *
 * \param usart Base address of the USART instance.
 */
void usart_spi_enable(USART_t *usart)
{
	usart_tx_enable(usart);
	usart_rx_enable(usart);
}

/**
 * \brief Disables the USART.
 *
 * Ensures that nothing is transferred while setting up buffers.
 *
 * \param usart Base address of the USART instance.
 *
 */
void usart_spi_disable(USART_t *usart)
{
	usart_tx_disable(usart);
	usart_rx_disable(usart);
}

/**
 * \brief Send a sequence of bytes to a SPI device using USART in SPI mode
 *
 * Received bytes on the USART in SPI mode are discarded.
 *
 * \param usart Base address of the USART instance.
 * \param data  Data buffer to write
 * \param len   Length of data
 *
 * \pre usart device must be selected with usart_spi_select_device() first
 */
status_code_t usart_spi_write_packet(USART_t *usart, const uint8_t *data,
		size_t len)
{
	size_t i = 0;
	while (len) {
		usart_spi_transmit(usart, *(data + i));
		len--;
		i++;
	}
	return STATUS_OK;
}

/**
 * \brief Receive a sequence of bytes from a USART in SPI mode device
 *
 * All bytes sent out on usart bus are sent as value 0.
 *
 * \param usart Base address of the usart instance.
 * \param data   data buffer to read
 * \param len    Length of data
 *
 * \pre usart device must be selected with usart_spi_select_device() first
 */
status_code_t usart_spi_read_packet(USART_t *usart, uint8_t *data, size_t len)
{
	while (len) {
		*data = usart_spi_transmit(usart, CONFIG_USART_SPI_DUMMY);
		len--;
		data++;
	}
	return STATUS_OK;
}

/**
 * \brief Select given device on the SPI bus
 *
 * Set device specific setting and calls board chip select.
 *
 * \param usart Base address of the USART instance.
 * \param device SPI device
 *
 */
void usart_spi_select_device(USART_t *usart, struct usart_spi_device *device)
{
	ioport_set_pin_low(device->id);
}

/**
 * \brief Deselect given device on the SPI bus
 *
 * Calls board chip deselect.
 *
 * \param usart Base address of the USART instance.
 * \param device SPI device
 *
 */
void usart_spi_deselect_device(USART_t *usart, struct usart_spi_device *device)
{
	ioport_set_pin_high(device->id);
}
