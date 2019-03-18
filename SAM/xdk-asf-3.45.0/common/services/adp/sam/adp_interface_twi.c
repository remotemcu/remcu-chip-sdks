/**
 * \file
 *
 * \brief ADP service implementation
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

#include <compiler.h>
#include <asf.h>
#include "adp_interface.h"

//! \name Embedded debugger TWI interface definitions
//@{
#define EDBG_TWI_MODULE           TWI0
//@}

#define TWI_EDBG_SLAVE_ADDR 0x28
#define TIMEOUT 1000

/**
* \brief Initialize EDBG TWI interface for SAM4S
*
*/
enum status_code adp_interface_init(void)
{
	sysclk_init();

	/* Configure the TWI interface */
	twi_master_options_t opt = {
		.speed = 100000,
		.chip  = TWI_EDBG_SLAVE_ADDR
	};
	return twi_master_setup(EDBG_TWI_MODULE, &opt);
}

/**
* \brief Send data on TWI
*
* \param[in] data   Pointer to data to send
* \param[in] length Number of bytes to send
*/
static enum status_code adp_interface_send(uint8_t* tx_buf, uint16_t length)
{
	twi_package_t packet_write = {
		.chip         = TWI_EDBG_SLAVE_ADDR, /* TWI slave bus address */
		.buffer       = tx_buf,        /* transfer data source buffer */
		.length       = length               /* transfer data size (bytes) */
	};
	return twi_master_write(EDBG_TWI_MODULE, &packet_write);
}

/**
* \brief Read data on TWI
*
* \param[out] data   Pointer to place received data
* \param[in]  length Number of bytes to receive
*/
enum status_code adp_interface_read_response(uint8_t *data,	uint16_t length)
{
	enum status_code status = ERR_IO_ERROR;
	uint8_t data_len = 0;
	
	twi_package_t packet_read = {
		.chip         = TWI_EDBG_SLAVE_ADDR, // TWI slave bus address
		.buffer       = &data_len,                // transfer data destination buffer
		.length       = 1               // transfer data size (bytes)
	};
	twi_master_read(EDBG_TWI_MODULE, &packet_read);
	
	if(data_len != 0){
		packet_read.length = data_len;
		packet_read.buffer = data;
		status = twi_master_read(EDBG_TWI_MODULE, &packet_read);	
	}

	return status;
}

/**
* \brief Sends and reads protocol packet data byte on I2C
*
* \param[in]  tx_buf  Pointer to send the protocol packet data
* \param[in]  length  The length of the send protocol packet data
* \param[out] rx_buf  Pointer to store the received I2C character
*/
void adp_interface_transceive_procotol(uint8_t* tx_buf, uint16_t length, uint8_t* rx_buf)
{
	adp_interface_send(tx_buf, length);
	adp_interface_read_response(rx_buf, length);
}

