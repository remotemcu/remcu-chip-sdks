/**
 * \file
 *
 * \brief I2C Master Quick Start Guide with Callbacks for SAMB
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

static uint8_t wr_buffer[DATA_LENGTH] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09
};

static uint8_t wr_buffer_reversed[DATA_LENGTH] = {
	0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00
};

static uint8_t rd_buffer[DATA_LENGTH];
//! [packet_data]

//! [address]
#define SLAVE_ADDRESS 0x12
//! [address]

//! [packet_glob]
struct i2c_master_packet wr_packet;
struct i2c_master_packet rd_packet;
//! [packet_glob]

/* Init software module instance. */
//! [dev_inst]
struct i2c_master_module i2c_master_instance;
//! [dev_inst]

//! [callback_func]
static void i2c_write_complete_callback(
		struct i2c_master_module *const module)
{
	/* Initiate new packet read */
	//! [read_next]
	i2c_master_read_packet_job(&i2c_master_instance,&rd_packet);
	//! [read_next]
}
//! [callback_func]

//! [initialize_gpio]
static void configure_gpio(void)
{
	//! [setup_1]
	struct gpio_config config_gpio_pin;
	gpio_get_config_defaults(&config_gpio_pin);
	//! [setup_1]
	//! [setup_2]
	config_gpio_pin.direction  = GPIO_PIN_DIR_INPUT;
	config_gpio_pin.input_pull = GPIO_PIN_PULL_UP;
	//! [setup_2]
	//! [setup_3]
	gpio_pin_set_config(BUTTON_0_PIN, &config_gpio_pin);
	//! [setup_3]
}
//! [initialize_gpio]

//! [initialize_i2c]
static void configure_i2c(void)
{
	/* Initialize config structure and software module */
	//! [setup_4]
	struct i2c_master_config config_i2c_master;
	i2c_master_get_config_defaults(&config_i2c_master);
	//! [init_conf]

	/* Initialize and enable device with config */
	//! [init_module]
	while(i2c_master_init(&i2c_master_instance, CONF_I2C_MASTER_MODULE, &config_i2c_master)
			!= STATUS_OK);
	//! [init_module]

	//! [enable_module]
	i2c_enable(i2c_master_instance.hw);
	//! [enable_module]
}
//! [initialize_i2c]

//! [setup_callback]
static void configure_i2c_callbacks(void)
{
	/* Register callback function. */
	//! [callback_reg]
	i2c_master_register_callback(&i2c_master_instance, i2c_write_complete_callback,
			I2C_MASTER_CALLBACK_WRITE_COMPLETE);
	//! [callback_reg]
	//! [callback_en]
	i2c_master_enable_callback(&i2c_master_instance,
			I2C_MASTER_CALLBACK_WRITE_COMPLETE);
	//! [callback_en]
}
//! [setup_callback]

int main(void)
{

	//! [run_initialize_i2c]
	system_clock_config(CLOCK_RESOURCE_XO_26_MHZ, CLOCK_FREQ_26_MHZ);
	//! [config_gpio]
	configure_gpio();
	//! [config_gpio]
	//! [config_i2c]
	configure_i2c();
	//! [config_i2c]
	//! [config_callback]
	configure_i2c_callbacks();
	//! [config_callback]
	//! [run_initialize_i2c]

	/* Init i2c packet. */

	//! [write_packet]
	wr_packet.address     = SLAVE_ADDRESS;
	wr_packet.data_length = DATA_LENGTH;
	wr_packet.data        = wr_buffer;
	//! [write_packet]
	//! [read_packet]
	rd_packet.address     = SLAVE_ADDRESS;
	rd_packet.data_length = DATA_LENGTH;
	rd_packet.data        = rd_buffer;
	//! [read_packet]
	
	while (true) {
		if (!gpio_pin_get_input_level(BUTTON_0_PIN)) {
			while (!gpio_pin_get_input_level(BUTTON_0_PIN)) {
				/* Waiting for button steady */
			}
		
			/* Send every other packet with reversed data */
			//! [revert_order]
			if (wr_packet.data[0] == 0x00) {
				wr_packet.data = &wr_buffer_reversed[0];
			} else {
				wr_packet.data = &wr_buffer[0];
			}
			//! [write_packet_job]
			i2c_master_write_packet_job(&i2c_master_instance, &wr_packet);
			//! [write_packet_job]
		}
	}
}
