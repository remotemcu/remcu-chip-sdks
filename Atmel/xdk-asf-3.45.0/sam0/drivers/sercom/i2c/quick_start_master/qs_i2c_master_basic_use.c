/**
 * \file
 *
 * \brief SAM SERCOM I2C Master Quick Start Guide
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

#include <asf.h>

//! [packet_data]
#define DATA_LENGTH 10
static uint8_t write_buffer[DATA_LENGTH] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
};

static uint8_t read_buffer[DATA_LENGTH];
//! [packet_data]

//! [address]
#define SLAVE_ADDRESS 0x12
//! [address]

/* Number of times to try to send packet if failed. */
//! [timeout]
#define TIMEOUT 1000
//! [timeout]

/* Init software module. */
//! [dev_inst]
struct i2c_master_module i2c_master_instance;
//! [dev_inst]

void configure_i2c_master(void);

//! [initialize_i2c]
void configure_i2c_master(void)
{
	/* Initialize config structure and software module. */
	//! [init_conf]
	struct i2c_master_config config_i2c_master;
	i2c_master_get_config_defaults(&config_i2c_master);
	//! [init_conf]

	/* Change buffer timeout to something longer. */
	//! [conf_change]
	config_i2c_master.buffer_timeout = 10000;
#if SAMR30
	config_i2c_master.pinmux_pad0    = CONF_MASTER_SDA_PINMUX;
	config_i2c_master.pinmux_pad1    = CONF_MASTER_SCK_PINMUX;
#endif
	//! [conf_change]
	/* Initialize and enable device with config. */
	//! [init_module]
	i2c_master_init(&i2c_master_instance, CONF_I2C_MASTER_MODULE, &config_i2c_master);
	//! [init_module]

	//! [enable_module]
	i2c_master_enable(&i2c_master_instance);
	//! [enable_module]
}
//! [initialize_i2c]

int main(void)
{
	system_init();

	//! [init]
	/* Configure device and enable. */
	//! [config]
	configure_i2c_master();
	//! [config]

	/* Timeout counter. */
	//! [timeout_counter]
	uint16_t timeout = 0;
	//! [timeout_counter]

	/* Init i2c packet. */
	//! [packet]
	struct i2c_master_packet packet = {
		.address     = SLAVE_ADDRESS,
		.data_length = DATA_LENGTH,
		.data        = write_buffer,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	//! [packet]
	//! [init]

	//! [main]
	/* Write buffer to slave until success. */
	//! [write_packet]
	while (i2c_master_write_packet_wait(&i2c_master_instance, &packet) !=
			STATUS_OK) {
		/* Increment timeout counter and check if timed out. */
		if (timeout++ == TIMEOUT) {
			break;
		}
	}
	//! [write_packet]

	/* Read from slave until success. */
	//! [read_packet]
	packet.data = read_buffer;
	while (i2c_master_read_packet_wait(&i2c_master_instance, &packet) !=
			STATUS_OK) {
		/* Increment timeout counter and check if timed out. */
		if (timeout++ == TIMEOUT) {
			break;
		}
	}
	//! [read_packet]

	//! [main]

	while (true) {
		/* Infinite loop */
	}

}
