/**
 * \file
 *
 * \brief SERCOM SPI master with vectored I/O driver quick start
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

#include <asf.h>

//! [transceive_buffers]
uint8_t tx_buffer_1[3] = {1, 2, 3};
uint8_t tx_buffer_2[2] = {4, 5};
uint8_t tx_buffer_3[1] = {6};

uint8_t rx_buffer_1[1];
uint8_t rx_buffer_2[2];
//! [transceive_buffers]

//! [buffer_descriptors]
struct spi_master_vec_bufdesc tx_buffers[4] = {
			{
				.data = tx_buffer_1,
				.length = 3,
			},
			{
				.data = tx_buffer_2,
				.length = 2,
			},
			{
				.data = tx_buffer_3,
				.length = 1,
			},
			{
				.data = NULL,
				.length = 0,
			},
		};

struct spi_master_vec_bufdesc rx_buffers[4] = {
			{
				.data = rx_buffer_1,
				.length = 1,
			},
			{
				.data = NULL,
				.length = 2,
			},
			{
				.data = rx_buffer_2,
				.length = 2,
			},
			{
				.data = NULL,
				.length = 0,
			},
		};
//! [buffer_descriptors]

//! [driver_instance]
struct spi_master_vec_module spi_master;
//! [driver_instance]

int main (void)
{
//! [config_instance]
	struct spi_master_vec_config spi_config;
//! [config_instance]

//! [init_system]
	system_init();
//! [init_system]

//! [set_up_config_instance]
	spi_master_vec_get_config_defaults(&spi_config);

	spi_config.baudrate = 200000;
	spi_config.transfer_mode = SPI_TRANSFER_MODE_3;
	spi_config.mux_setting = EXT1_SPI_SERCOM_MUX_SETTING;
	spi_config.pinmux_pad0 = EXT1_SPI_SERCOM_PINMUX_PAD0;
	spi_config.pinmux_pad1 = EXT1_SPI_SERCOM_PINMUX_PAD1;
	spi_config.pinmux_pad2 = EXT1_SPI_SERCOM_PINMUX_PAD2;
	spi_config.pinmux_pad3 = EXT1_SPI_SERCOM_PINMUX_PAD3;
//! [set_up_config_instance]

//! [init_instance]
	spi_master_vec_init(&spi_master, EXT1_SPI_MODULE, &spi_config);
//! [init_instance]

//! [enable_instance]
	spi_master_vec_enable(&spi_master);
//! [enable_instance]

//! [start_reception_wait]
	spi_master_vec_transceive_buffer_wait(&spi_master, NULL, rx_buffers);
//! [start_reception_wait]

//! [start_transmission]
	spi_master_vec_transceive_buffer_job(&spi_master, tx_buffers, NULL);
//! [start_transmission]

//! [start_transception]
	while (spi_master_vec_transceive_buffer_job(&spi_master, tx_buffers, rx_buffers) == STATUS_BUSY) {
		/* Try to start transfer until it succeeds. */
	}
//! [start_transception]

//! [wait_transception]
	spi_master_vec_get_job_status_wait(&spi_master);
//! [wait_transception]

	while (1) {
	}
}