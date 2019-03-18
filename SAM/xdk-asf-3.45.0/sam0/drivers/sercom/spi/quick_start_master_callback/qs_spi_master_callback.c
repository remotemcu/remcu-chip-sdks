/**
 * \file
 *
 * \brief SAM SPI Quick Start
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

//! [setup]
//! [buf_length]
#define BUF_LENGTH 20
//! [buf_length]
//! [slave_select_pin]
#define SLAVE_SELECT_PIN CONF_MASTER_SS_PIN
//! [slave_select_pin]
//! [buffer]
static uint8_t wr_buffer[BUF_LENGTH] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
		 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13
};
static uint8_t rd_buffer[BUF_LENGTH];
//! [buffer]

//! [dev_inst]
struct spi_module spi_master_instance;
//! [dev_inst]
//! [slave_dev_inst]
struct spi_slave_inst slave;
//! [slave_dev_inst]
//! [var]
volatile bool transrev_complete_spi_master = false;
//! [var]
//! [setup]

void configure_spi_master_callbacks(void);
void configure_spi_master(void);
//! [callback]
static void callback_spi_master( struct spi_module *const module)
{
//! [callback_var]
	transrev_complete_spi_master = true;
//! [callback_var]
}
//! [callback]

//! [conf_callback]
void configure_spi_master_callbacks(void)
{
//! [reg_callback]
	spi_register_callback(&spi_master_instance, callback_spi_master,
			SPI_CALLBACK_BUFFER_TRANSCEIVED);
//! [reg_callback]
//! [en_callback]
	spi_enable_callback(&spi_master_instance, SPI_CALLBACK_BUFFER_TRANSCEIVED);
//! [en_callback]
}
//! [conf_callback]

//! [configure_spi]
void configure_spi_master(void)
{
//! [config]
	struct spi_config config_spi_master;
//! [config]
//! [slave_config]
	struct spi_slave_inst_config slave_dev_config;
//! [slave_config]
	/* Configure and initialize software device instance of peripheral slave */
//! [slave_conf_defaults]
	spi_slave_inst_get_config_defaults(&slave_dev_config);
//! [slave_conf_defaults]
//! [ss_pin]
	slave_dev_config.ss_pin = SLAVE_SELECT_PIN;
//! [ss_pin]
//! [slave_init]
	spi_attach_slave(&slave, &slave_dev_config);
//! [slave_init]
	/* Configure, initialize and enable SERCOM SPI module */
//! [conf_defaults]
	spi_get_config_defaults(&config_spi_master);
//! [conf_defaults]
//! [mux_setting]
	config_spi_master.mux_setting = CONF_MASTER_MUX_SETTING;
//! [mux_setting]
	config_spi_master.pinmux_pad0 = CONF_MASTER_PINMUX_PAD0;
	config_spi_master.pinmux_pad1 = CONF_MASTER_PINMUX_PAD1;
	config_spi_master.pinmux_pad2 = CONF_MASTER_PINMUX_PAD2;
	config_spi_master.pinmux_pad3 = CONF_MASTER_PINMUX_PAD3;

//! [init]
	spi_init(&spi_master_instance, CONF_MASTER_SPI_MODULE, &config_spi_master);
//! [init]

//! [enable]
	spi_enable(&spi_master_instance);
//! [enable]

}
//! [configure_spi]

int main(void)
{
//! [main_start]
	/* Initialize system */
//! [system_init]
	system_init();
//! [system_init]

//! [run_config]
	configure_spi_master();
//! [run_config]
//! [run_callback_config]
	configure_spi_master_callbacks();
//! [run_callback_config]
//! [main_start]

//! [main_use_case]
//! [inf_loop]
	while (true) {
		/* Infinite loop */
		if (!port_pin_get_input_level(BUTTON_0_PIN)) {
			//! [select_slave]
			spi_select_slave(&spi_master_instance, &slave, true);
			//! [select_slave]
			//! [write and read]
			spi_transceive_buffer_job(&spi_master_instance, wr_buffer,rd_buffer,BUF_LENGTH);
			//! [write and read]
			//! [wait]
			while (!transrev_complete_spi_master) {
				/////* Wait for write and read complete */
			}
			transrev_complete_spi_master = false;
			//! [wait]
			//! [deselect_slave]
			spi_select_slave(&spi_master_instance, &slave, false);
			//! [deselect_slave]
		}
	}
//! [inf_loop]
//! [main_use_case]
}
