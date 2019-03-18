/**
 * \file
 *
 * \brief Connection of the AT25DFx SerialFlash to SPI interface driver.
 *
 * This file manages the connection of the AT25DFx SerialFlash driver to an
 * SPI service (could be spi master service or usart in spi mode). The SPI
 * service selection depends on  AT25DFX_USES_SPI_MASTER_SERVICE or
 * AT25DFX_USES_USART_SPI_SERVICE in conf_at25dfx.h.
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

#include "at25dfx_hal_spi.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \name Functions to connect the SerialFlash driver with the SPI Multiple-Sector Access Functions.
 */
//! @{

/* Sanity check to enable connection with only one SPI service */
#if defined(AT25DFX_USES_SPI_MASTER_SERVICE) &&  defined(AT25DFX_USES_USART_SPI_SERVICE)
#error only one SPI service should be selected
#endif
/* At least one SPI service should be connected. */
#if !defined(AT25DFX_USES_SPI_MASTER_SERVICE) &&  !defined(AT25DFX_USES_USART_SPI_SERVICE)
#error No SPI service is selected
#endif

#if defined( AT25DFX_USES_SPI_MASTER_SERVICE)
#include "spi_master.h"
	/* Create as many spi_device as required. */
#if (AT25DFX_MEM_CNT>0)
	struct spi_device AT25DFX_DEVICE1 = {
		.id = AT25DFX_CS
	};
#endif
#if (AT25DFX_MEM_CNT>1)
	struct spi_device AT25DFX_DEVICE2 = {
		.id = AT25DFX_CS2
	};
#endif
#if (AT25DFX_MEM_CNT>2)
	struct spi_device AT25DFX_DEVICE3 = {
		.id = AT25DFX_CS3
	};
#endif
#if (AT25DFX_MEM_CNT>3)
	struct spi_device AT25DFX_DEVICE4 = {
		.id = AT25DFX_CS4
	};
#endif

#elif defined(AT25DFX_USES_USART_SPI_SERVICE)
#include "usart_spi.h"
	/* Create as many usart_spi_device as required. */
#if (AT25DFX_MEM_CNT>0)
	struct usart_spi_device AT25DFX_DEVICE1 = {
		.id = AT25DFX_CS
	};
#endif
#if (AT25DFX_MEM_CNT>1)
	struct usart_spi_device AT25DFX_DEVICE2 = {
		.id = AT25DFX_CS2
	};
#endif
#if (AT25DFX_MEM_CNT>2)
	struct usart_spi_device AT25DFX_DEVICE3 = {
		.id = AT25DFX_CS3
	};
#endif
#if (AT25DFX_MEM_CNT>3)
	struct usart_spi_device AT25DFX_DEVICE4 = {
		.id = AT25DFX_CS4
	};
#endif
#endif

/** 
 * \brief Initialize SPI external resource for AT25DFx SerialFlash driver.
 *
 *  This function initializes the SerialFlash component as well as the SPI service that
 *  the memory is connected to.
 *  \pre The conf_at25dfx.h file should provide the following information:
 *  - Selection of the SPI service the SerialFlash is connected
 *  (AT25DFX_USES_SPI_MASTER_SERVICE or  AT25DFX_USES_USART_SPI_SERVICE).
 *  - AT25DFX_MEM_SIZE: The SerialFlash type that the driver is connected to.
 *  - AT25DFX_MEM_CNT: The number of SerialFlash components (number of chipselect).
 *  - AT25DFX_SPI_MODULE:  The name of the SPI module used by the SerialFlash driver.
 *  - AT25DFX_SPI_MASTER_SPEED: The SPI bus speed.
 */
void at25dfx_spi_init(void)
{
#if defined( AT25DFX_USES_SPI_MASTER_SERVICE)
	spi_master_init(AT25DFX_SPI_MODULE);
	#if (AT25DFX_MEM_CNT==1)
		spi_master_setup_device(AT25DFX_SPI_MODULE,&AT25DFX_DEVICE1,SPI_MODE_0,AT25DFX_SPI_MASTER_SPEED,0);
	#endif
	#if (AT25DFX_MEM_CNT>1)
		spi_master_setup_device(AT25DFX_SPI_MODULE,&AT25DFX_DEVICE2,SPI_MODE_0,AT25DFX_SPI_MASTER_SPEED,0);
	#endif
	#if (AT25DFX_MEM_CNT>2)
		spi_master_setup_device(AT25DFX_SPI_MODULE,&AT25DFX_DEVICE3,SPI_MODE_0,AT25DFX_SPI_MASTER_SPEED,0);
	#endif
	#if (AT25DFX_MEM_CNT>3)
		spi_master_setup_device(AT25DFX_SPI_MODULE,&AT25DFX_DEVICE4,SPI_MODE_0,AT25DFX_SPI_MASTER_SPEED,0);
	#endif
	spi_enable(AT25DFX_SPI_MODULE);

/* Implementation with USART in SPI mode service */
#elif defined(AT25DFX_USES_USART_SPI_SERVICE)
	usart_spi_init(AT25DFX_SPI_MODULE);
	#if (AT25DFX_MEM_CNT==1)
		usart_spi_setup_device(AT25DFX_SPI_MODULE,&AT25DFX_DEVICE1,SPI_MODE_0,AT25DFX_SPI_MASTER_SPEED,0);
	#endif
	#if (AT25DFX_MEM_CNT>1)
		usart_spi_setup_device(AT25DFX_SPI_MODULE,&AT25DFX_DEVICE2,SPI_MODE_0,AT25DFX_SPI_MASTER_SPEED,0);
	#endif
	#if (AT25DFX_MEM_CNT>2)
		usart_spi_setup_device(AT25DFX_SPI_MODULE,&AT25DFX_DEVICE3,SPI_MODE_0,AT25DFX_SPI_MASTER_SPEED,0);
	#endif
	#if (AT25DFX_MEM_CNT>3)
		usart_spi_setup_device(AT25DFX_SPI_MODULE,&AT25DFX_DEVICE4,SPI_MODE_0,AT25DFX_SPI_MASTER_SPEED,0);
	#endif
#endif
}

/**
 * \brief Select one external SerialFlash component.
 *
 * \param mem_id  The SerialFlash index number.
 */
void at25dfx_spi_select_device(uint8_t mem_id)
{
	UNUSED(mem_id);
#if defined( AT25DFX_USES_SPI_MASTER_SERVICE)
#if (AT25DFX_MEM_CNT==1)
		spi_select_device(AT25DFX_SPI_MODULE, &AT25DFX_DEVICE1);
#else
		switch (mem_id) {
		case 1:
			spi_select_device(AT25DFX_SPI_MODULE, &AT25DFX_DEVICE1);
			break;

		case 2:
			spi_select_device(AT25DFX_SPI_MODULE, &AT25DFX_DEVICE2);
			break;

		case 3:
			spi_select_device(AT25DFX_SPI_MODULE, &AT25DFX_DEVICE3);
			break;

		case 4:
			spi_select_device(AT25DFX_SPI_MODULE, &AT25DFX_DEVICE4);
			break;

		default:
			/* unhandled_case(id); */
			return;
		}
#endif

/* Implementation with USART in SPI mode service */
#elif defined(AT25DFX_USES_USART_SPI_SERVICE)
#if (AT25DFX_MEM_CNT==1)
		usart_spi_select_device(AT25DFX_SPI_MODULE, &AT25DFX_DEVICE1);
#else
		switch (mem_id) {
		case 1:
			usart_spi_select_device(AT25DFX_SPI_MODULE,&AT25DFX_DEVICE1);
			break;

	case 2:
		usart_spi_select_device(AT25DFX_SPI_MODULE, &AT25DFX_DEVICE2);
		break;

	case 3:
		usart_spi_select_device(AT25DFX_SPI_MODULE, &AT25DFX_DEVICE3);
		break;

	case 4:
		usart_spi_select_device(AT25DFX_SPI_MODULE, &AT25DFX_DEVICE4);
		break;

	default:
		/* unhandled_case(id); */
		return;
	}
#endif

#endif
}

/** 
 * \brief Deselect one external SerialFlash component.
 *
 * \param mem_id  The SerialFlash index number.
 */
void at25dfx_spi_deselect_device(uint8_t mem_id)
{
	UNUSED(mem_id);
#if defined( AT25DFX_USES_SPI_MASTER_SERVICE)
	#if (AT25DFX_MEM_CNT==1)
	spi_deselect_device(AT25DFX_SPI_MODULE, &AT25DFX_DEVICE1);
	#else
	switch(mem_id) {
	case 1:
		spi_deselect_device(AT25DFX_SPI_MODULE, &AT25DFX_DEVICE1);
		break;

	case 2:
		spi_deselect_device(AT25DFX_SPI_MODULE, &AT25DFX_DEVICE2);
		break;

	case 3:
		spi_deselect_device(AT25DFX_SPI_MODULE, &AT25DFX_DEVICE3);
		break;

	case 4:
		spi_deselect_device(AT25DFX_SPI_MODULE, &AT25DFX_DEVICE4);
		break;

	default:
		/* unhandled_case(id); */
		return;
	}
	#endif

/* Implementation with USART in SPI mode service */
#elif defined(AT25DFX_USES_USART_SPI_SERVICE)
	#if (AT25DFX_MEM_CNT==1)
	usart_spi_deselect_device(AT25DFX_SPI_MODULE, &AT25DFX_DEVICE1);
	#else
	switch(mem_id) {
	case 1:
		usart_spi_deselect_device(AT25DFX_SPI_MODULE, &AT25DFX_DEVICE1);
		break;

	case 2:
		usart_spi_deselect_device(AT25DFX_SPI_MODULE, &AT25DFX_DEVICE2);
		break;

	case 3:
		usart_spi_deselect_device(AT25DFX_SPI_MODULE, &AT25DFX_DEVICE3);
		break;

	case 4:
		usart_spi_deselect_device(AT25DFX_SPI_MODULE, &AT25DFX_DEVICE4);
		break;

		default:
			/* unhandled_case(id); */
			return;
		}
#endif
#endif
	}

/**
 * \brief Send one byte to the SerialFlash.
 *
 * \param data The data byte to send.
 * \pre The SerialFlash should be selected first using at25dfx_spi_select_device.
 */
status_code_t at25dfx_spi_write_byte(uint8_t data)
{
#if defined( AT25DFX_USES_SPI_MASTER_SERVICE)
		return spi_write_packet(AT25DFX_SPI_MODULE, &data, 1);
/* Implementation with USART in SPI mode service */
#elif defined(AT25DFX_USES_USART_SPI_SERVICE)
		return usart_spi_write_packet(AT25DFX_SPI_MODULE, &data, 1);
#endif
	}

/**
 * \brief Get one byte (read) from the SerialFlash.
 *
 * \param data   Data buffer to read.
 *
 * \return The received byte.
 * \pre The SerialFlash should be selected first using at25dfx_spi_select_device.
 */
status_code_t at25dfx_spi_read_byte(uint8_t *data)
{
#if defined( AT25DFX_USES_SPI_MASTER_SERVICE)
		return spi_read_packet(AT25DFX_SPI_MODULE, data, 1);

/* Implementation with USART in SPI mode service */
#elif defined(AT25DFX_USES_USART_SPI_SERVICE)
		return usart_spi_read_packet(AT25DFX_SPI_MODULE, data, 1);
#endif
	}


/**
 * \brief Receive a sequence of bytes from a SerialFlash.
 *
 * \param data   Data buffer to read
 * \param len    Length of data
 * \pre The SerialFlash should be selected first using at25dfx_spi_select_device
 */
status_code_t at25dfx_spi_read_packet(void const *data, size_t len)
{
#if defined( AT25DFX_USES_SPI_MASTER_SERVICE)
	return spi_read_packet(AT25DFX_SPI_MODULE, (uint8_t*)data, len);

/* Implementation with USART in SPI mode service */
#elif defined(AT25DFX_USES_USART_SPI_SERVICE)
	return usart_spi_read_packet(AT25DFX_SPI_MODULE, (uint8_t*)data, len);
#endif
}

/**
 * \brief Send a sequence of bytes to a SerialFlash.
 *
 *
 * \param data   Data buffer to write
 * \param len    Length of data
 * \pre The SerialFlash should be selected first using at25dfx_spi_select_device
 *
 */
status_code_t at25dfx_spi_write_packet(void const *data, size_t len)
{
#if defined( AT25DFX_USES_SPI_MASTER_SERVICE)
	return spi_write_packet(AT25DFX_SPI_MODULE, (uint8_t*)data, len);

/* Implementation with USART in SPI mode service */
#elif defined(AT25DFX_USES_USART_SPI_SERVICE)
	return usart_spi_write_packet(AT25DFX_SPI_MODULE, (uint8_t*)data, len);
#endif
	}

//! @}

#ifdef __cplusplus
}
#endif
