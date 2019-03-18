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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <compiler.h>
#include <system.h>

#include <asf.h>
#include <adp_interface.h>

#define EDBG_TWI EDBG_I2C_MODULE
#define TWI_EDBG_SLAVE_ADDR 0x28
#define TIMEOUT 1000

struct i2c_master_module i2c_master_instance;

/**
* \brief Initialize EDBG I2C communication for SAM0
*
*/
enum status_code adp_interface_init(void)
{
	enum status_code return_value;

	system_init();

	struct i2c_master_config config_i2c_master;
	i2c_master_get_config_defaults(&config_i2c_master);
	config_i2c_master.buffer_timeout = 10000;
	return_value = i2c_master_init(&i2c_master_instance, EDBG_TWI, &config_i2c_master);
	i2c_master_enable(&i2c_master_instance);
	return return_value;
}

static enum status_code adp_interface_send(uint8_t* tx_buf, uint16_t length)
{
	enum status_code status;
	
	struct i2c_master_packet packet = {
		.address = TWI_EDBG_SLAVE_ADDR,
		.data_length = length,
		.data = tx_buf,
	};
	/* Send data to PC */
	status = i2c_master_write_packet_wait(&i2c_master_instance, &packet);
	
	return status;
}

/**
* \brief Read response on I2C from PC
*
* return Status
* \param[in]  rx_buf  Pointer to receive the data
* \param[in]  length  The length of the read data
* \param[out] rx_buf  Pointer to store the received SPI character
*/
enum status_code adp_interface_read_response(uint8_t* rx_buf, uint16_t length)
{
	enum status_code status = STATUS_ERR_IO;
	uint8_t data_len = 0;

	struct i2c_master_packet packet = {
		.address = TWI_EDBG_SLAVE_ADDR,
		.data_length = 1,
		.data = &data_len,
	};
	i2c_master_read_packet_wait(&i2c_master_instance, &packet);
	
	if (data_len != 0)
	{
		packet.data_length = data_len;
		packet.data = rx_buf;
		status = i2c_master_read_packet_wait(&i2c_master_instance, &packet);
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
