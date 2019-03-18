/*****************************************************************************
 *
 * \file
 *
 * \brief SPI Master driver for AVR UC3.
 *
 * This file defines a useful set of functions for the SPI interface on AVR UC3
 * devices.
 *
 * Copyright (c) 2009-2018 Microchip Technology Inc. and its subsidiaries.
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
 ******************************************************************************/
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */


#include "spi_master.h"

#ifdef FREERTOS_USED

#include "FreeRTOS.h"
#include "semphr.h"

#endif

void spi_master_setup_device(volatile avr32_spi_t *spi,
		struct spi_device *device, spi_flags_t flags, uint32_t baud_rate,
		board_spi_select_id_t sel_id)
{
	spi_set_chipselect_delay_bct(spi,device->id,CONFIG_SPI_MASTER_DELAY_BCT);
	spi_set_chipselect_delay_bs(spi,device->id,CONFIG_SPI_MASTER_DELAY_BS);
	spi_set_bits_per_transfer(spi,device->id,
			CONFIG_SPI_MASTER_BITS_PER_TRANSFER);
	spi_set_baudrate_register(spi,device->id,
			getBaudDiv(baud_rate, sysclk_get_peripheral_bus_hz(spi)));
	spi_enable_active_mode(spi,device->id);
	spi_set_mode(spi,device->id,flags);

#ifdef FREERTOS_USED
	if (!xSPIMutex) {
		// Create the SPI mutex.
		vSemaphoreCreateBinary(xSPIMutex);
		if (!xSPIMutex) {
			while(1);
		}
	}
#endif
}

status_code_t spi_read_packet(volatile avr32_spi_t *spi,
		uint8_t *data, size_t len)
{
	unsigned int timeout = SPI_TIMEOUT;
	uint8_t val;
	size_t i=0;
	while(len) {
		timeout = SPI_TIMEOUT;
		while (!spi_is_tx_ready(spi)) {
			if (!timeout--) {
				return ERR_TIMEOUT;
			}
		}
		spi_write_single(spi,CONFIG_SPI_MASTER_DUMMY);
		timeout = SPI_TIMEOUT;
		while (!spi_is_rx_ready(spi)) {
			if (!timeout--) {
				return ERR_TIMEOUT;
			}
		}
		spi_read_single(spi,&val);
		data[i] = val;
		i++;
		len--;
	}
	return STATUS_OK;
}

status_code_t spi_write_packet(volatile avr32_spi_t *spi, const uint8_t *data,
		size_t len)
{
	unsigned int timeout = SPI_TIMEOUT;
	size_t i=0;
	uint8_t val;
	while(len) {
		timeout = SPI_TIMEOUT;
		while (!spi_is_tx_ready(spi)) {
			if (!timeout--) {
				return ERR_TIMEOUT;
			}
		}
		val = data[i];
		spi_write_single(spi,val);
		i++;
		len--;
	}
	return STATUS_OK;
}

//! @}
