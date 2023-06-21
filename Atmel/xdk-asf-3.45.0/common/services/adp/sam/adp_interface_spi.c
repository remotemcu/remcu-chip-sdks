/**
 * \file
 *
 * \brief ADP SPI interface implementation
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

#include <compiler.h>
#include <asf.h>
#include "adp_interface.h"

//! \name Embedded debugger SPI interface definitions
//@{
#define EDBG_SPI_MODULE           SPI
//@}

#define SPI_CHIP_SEL  SPI_NPCS3_PA5_GPIO

#define SPI_DEVICE_ID         3
#define SPI_BAUDRATE          1500000

struct spi_device SPI_DEVICE = {
	/** Board specific select id */
	.id = SPI_DEVICE_ID
};

/**
* \brief Send SPI start condition
*
*/
static void adp_interface_send_start(void)
{
	spi_select_device(EDBG_SPI_MODULE, &SPI_DEVICE);
}

/**
* \brief Send SPI stop condition
*
*/
static void adp_interface_send_stop(void)
{
	spi_deselect_device(EDBG_SPI_MODULE, &SPI_DEVICE);
}

/**
* \brief Sends and reads data byte on SPI
*
* \param[in]  data     Data byte to send
* \param[in]  tx_data  SPI character to transmit
* \param[out] rx_data  Pointer to store the received SPI character
*/
static void adp_interface_transceive(uint8_t *tx_data, uint8_t *rx_data, uint16_t length)
{
	spi_transceive_packet(EDBG_SPI_MODULE, tx_data, rx_data, length);
}

/**
* \brief Initialize EDBG SPI communication for SAM
*
*/
enum status_code adp_interface_init(void)
{
	sysclk_init();

	/* Configure the SPI interface */
	spi_master_init(EDBG_SPI_MODULE);
	spi_master_setup_device(EDBG_SPI_MODULE, &SPI_DEVICE, SPI_MODE_0,
			SPI_BAUDRATE, 0);
	spi_enable(EDBG_SPI_MODULE);

	return STATUS_OK;
}

/**
* \brief Sends and reads protocol packet data byte on SPI
*
* \param[in]  tx_buf  Pointer to send the protocol packet data
* \param[in]  length  The length of the send protocol packet data
* \param[out] rx_buf  Pointer to store the received SPI character
*/
void adp_interface_transceive_procotol(uint8_t* tx_buf, uint16_t length, uint8_t* rx_buf)
{
	/* Send SPI start condition */
	adp_interface_send_start();

	adp_interface_transceive(tx_buf, rx_buf, length);
	
	/* Send SPI end condition */
	adp_interface_send_stop();
}

/**
* \brief Read response on SPI from PC
*
* return Status
* \param[in]  rx_buf  Pointer to receive the data
* \param[in]  length  The length of the read data
* \param[out] rx_buf  Pointer to store the received SPI character
*/
enum status_code adp_interface_read_response(uint8_t* rx_buf, uint16_t length)
{
	enum status_code status;

	/* Send SPI start condition */
	adp_interface_send_start();	
	status = spi_read_packet(EDBG_SPI_MODULE, rx_buf, length);
	/* Send SPI end condition */
	adp_interface_send_stop();

	return status;
}
