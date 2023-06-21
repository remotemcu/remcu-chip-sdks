/*****************************************************************************
 *
 * \file
 *
 * \brief SPI software driver functions.
 *
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
 *****************************************************************************/
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "spi_master.h"
#include "sysclk.h"

/*! \brief Initializes the SPI in master mode.
 *
 * \param spi       Base address of the SPI instance.
 *
 */
void spi_master_init(SPI_t *spi)
{
#ifdef SPIA
	if ((uint16_t)spi == (uint16_t)&SPIA) {
		sysclk_enable_module(SYSCLK_PORT_A, PR_SPI_bm);
	}
#endif
#ifdef SPIB
	if ((uint16_t)spi == (uint16_t)&SPIB) {
		sysclk_enable_module(SYSCLK_PORT_B, PR_SPI_bm);
	}
#endif
#ifdef SPIC
	if ((uint16_t)spi == (uint16_t)&SPIC) {
		sysclk_enable_module(SYSCLK_PORT_C, PR_SPI_bm);
	}
#endif
#ifdef SPID
	if ((uint16_t)spi == (uint16_t)&SPID) {
		sysclk_enable_module(SYSCLK_PORT_D, PR_SPI_bm);
	}
#endif
#ifdef SPIE
	if ((uint16_t)spi == (uint16_t)&SPIE) {
		sysclk_enable_module(SYSCLK_PORT_E, PR_SPI_bm);
	}
#endif
#ifdef SPIF
	if ((uint16_t)spi == (uint16_t)&SPIF) {
		sysclk_enable_module(SYSCLK_PORT_F, PR_SPI_bm);
	}
#endif
	spi_enable_master_mode(spi);
}

/**
 * \brief Setup a SPI device.
 *
 * The returned device descriptor structure must be passed to the driver
 * whenever that device should be used as current slave device.
 *
 * \param spi Base address of the SPI instance.
 * \param device    Pointer to SPI device struct that should be initialized.
 * \param flags     SPI configuration flags. Common flags for all
 *                  implementations are the SPI modes SPI_MODE_0 ...
 *                  SPI_MODE_3.
 * \param baud_rate Baud rate for communication with slave device in Hz.
 * \param sel_id    Board specific select id
 */
void spi_master_setup_device(SPI_t *spi, struct spi_device *device,
		spi_flags_t flags, uint32_t baud_rate,
		board_spi_select_id_t sel_id)
{
	if (spi_xmega_set_baud_div(spi, baud_rate, sysclk_get_cpu_hz()) < 0) {
		Assert(false);
		return;
	}

	/* Clear any set SPI mode flags and set them to the user-specified mode */
	spi->CTRL = (spi->CTRL & ~SPI_MODE_gm) |
			((flags << SPI_MODE_gp) & SPI_MODE_gm);
}

/**
 * \brief Send a sequence of bytes to a SPI device
 *
 * Received bytes on the SPI bus are discarded.
 *
 * \param spi Base address of the SPI instance.
 * \param data   data buffer to write
 * \param len    Length of data
 *
 * \pre SPI device must be selected with spi_select_device() first
 */
status_code_t spi_write_packet(SPI_t *spi, const uint8_t *data, size_t len)
{
	while (len--) {
		spi_write_single(spi, *data++);
		
		while (!spi_is_rx_full(spi)) {
		}
	}
	
	return STATUS_OK;
}

/**
 * \brief Receive a sequence of bytes from a SPI device
 *
 * All bytes sent out on SPI bus are sent as value 0.
 *
 * \param spi Base address of the SPI instance.
 * \param data   data buffer to read
 * \param len    Length of data
 *
 * \pre SPI device must be selected with spi_select_device() first
 */
status_code_t spi_read_packet(SPI_t *spi, uint8_t *data, size_t len)
{
	while (len--) {
		spi_write_single(spi,CONFIG_SPI_MASTER_DUMMY); //Dummy write

		while (!spi_is_rx_full(spi)) {
		}
		
		spi_read_single(spi, data);
		data++;
	}
	
	return STATUS_OK;
}

/**
 * \brief Select given device on the SPI bus
 *
 * Set device specific setting and calls board chip select.
 *
 * \param spi Base address of the SPI instance.
 * \param device SPI device
 *
 */
void spi_select_device(SPI_t *spi, struct spi_device *device)
{
	ioport_set_pin_low(device->id);
}

/**
 * \brief Deselect given device on the SPI bus
 *
 * Calls board chip deselect.
 *
 * \param spi Base address of the SPI instance.
 * \param device SPI device
 *
 * \pre SPI device must be selected with spi_select_device() first
 */
void spi_deselect_device(SPI_t *spi, struct spi_device *device)
{
	ioport_set_pin_high(device->id);
}
