/**
 * \file
 *
 * \brief I2C Slave Quick Start Guide for SAMB
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

#include <asf.h>

//! [packet_data]
#define DATA_LENGTH 10
static uint8_t write_buffer[DATA_LENGTH] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09
};

static uint8_t read_buffer[DATA_LENGTH];
//! [packet_data]

//! [address]
#define SLAVE_ADDRESS 0x12
//! [address]

/* Init software module. */
//! [dev_inst]
struct i2c_slave_module i2c_slave_instance;
//! [dev_inst]

//! [initialize_i2c]
static void configure_i2c_slave(void)
{
	/* Initialize config structure and software module. */
	//! [init_conf]
	struct i2c_slave_config config_i2c_slave;
	i2c_slave_get_config_defaults(&config_i2c_slave);
	//! [init_conf]
	/* Change address and address_mode. */
	//! [conf_changes]
	config_i2c_slave.address = SLAVE_ADDRESS;
	
	config_i2c_slave.pin_number_pad0 = PIN_LP_GPIO_14;
	config_i2c_slave.pin_number_pad1 = PIN_LP_GPIO_15;
	config_i2c_slave.pinmux_sel_pad0 = MUX_LP_GPIO_14_I2C1_SDA;
	config_i2c_slave.pinmux_sel_pad1 = MUX_LP_GPIO_15_I2C1_SCL;
	
	//! [conf_changes]
	/* Initialize and enable device with config, and enable i2c. */
	//! [init_module]
	while(i2c_slave_init(&i2c_slave_instance, I2C1, &config_i2c_slave)     \
			!= STATUS_OK);
	//! [init_module]
	//! [enable_module]
	i2c_enable(i2c_slave_instance.hw);
	//! [enable_module]
	//! [enable_interurpt]
	i2c_slave_rx_interrupt(i2c_slave_instance.hw, true);
	i2c_slave_tx_interrupt(i2c_slave_instance.hw, true);
	//! [enable_interurpt]
}
//! [initialize_i2c]

int main(void)
{
	
	//! [init]
	system_clock_config(CLOCK_RESOURCE_XO_26_MHZ, CLOCK_FREQ_26_MHZ);
	
	configure_i2c_slave();

	//! [packet]
	struct i2c_slave_packet packet = {
		.data_length = DATA_LENGTH,
		.data        = write_buffer,
	};
	//! [packet]

	//! [init]
	//! [while]
	while (true) {
		packet.data = read_buffer;
		i2c_slave_read_packet_wait(&i2c_slave_instance, &packet);
		packet.data = write_buffer;
		i2c_slave_write_packet_wait(&i2c_slave_instance, &packet);
	}
	//! [while]
}
