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

//! [buffer]
static uint8_t buffer_rx[BUF_LENGTH] = {0x00,};
static uint8_t buffer_expect[BUF_LENGTH] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
		 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13
};
//! [buffer]
//! [var]
volatile bool transfer_complete_spi_slave = false;
//! [var]

//! [dev_inst]
struct spi_module spi_slave_instance;
//! [dev_inst]
//! [setup]

void configure_spi_slave_callbacks(void);
void configure_spi_slave(void);

//! [callback]
static void spi_slave_callback(struct spi_module *const module)
{
//! [callback_var]
	transfer_complete_spi_slave = true;
//! [callback_var]
}
//! [callback]

//! [conf_callback]
void configure_spi_slave_callbacks(void)
{
//! [reg_callback]
	spi_register_callback(&spi_slave_instance, spi_slave_callback,
			SPI_CALLBACK_BUFFER_RECEIVED);
//! [reg_callback]
//! [en_callback]
	spi_enable_callback(&spi_slave_instance, SPI_CALLBACK_BUFFER_RECEIVED);
//! [en_callback]
}
//! [conf_callback]

//! [configure_spi]
void configure_spi_slave(void)
{
//! [config]
	struct spi_config config_spi_slave;
//! [config]
	/* Configure, initialize and enable SERCOM SPI module */
//! [conf_defaults]
	spi_get_config_defaults(&config_spi_slave);
//! [conf_defaults]
//! [conf_spi_slave_instance]
	config_spi_slave.mode = SPI_MODE_SLAVE;
//! [conf_spi_slave_instance]
//! [conf_preload]
	config_spi_slave.mode_specific.slave.preload_enable = true;
//! [conf_preload]
//! [conf_format]
	config_spi_slave.mode_specific.slave.frame_format = SPI_FRAME_FORMAT_SPI_FRAME;
//! [conf_format]
//! [mux_setting]
	config_spi_slave.mux_setting = CONF_SLAVE_MUX_SETTING;
//! [mux_setting]

	config_spi_slave.pinmux_pad0 = CONF_SLAVE_PINMUX_PAD0;
	config_spi_slave.pinmux_pad1 = CONF_SLAVE_PINMUX_PAD1;
	config_spi_slave.pinmux_pad2 = CONF_SLAVE_PINMUX_PAD2;
	config_spi_slave.pinmux_pad3 = CONF_SLAVE_PINMUX_PAD3;

//! [init]
	spi_init(&spi_slave_instance, CONF_SLAVE_SPI_MODULE, &config_spi_slave);
//! [init]

//! [enable]
	spi_enable(&spi_slave_instance);
//! [enable]

}
//! [configure_spi]

int main(void)
{
//! [main_start]
	uint8_t result = 0;
	
	/* Initialize system */
//! [system_init]
	system_init();
//! [system_init]

//! [run_config]
	configure_spi_slave();
//! [run_config]
//! [run_callback_config]
	configure_spi_slave_callbacks();
//! [run_callback_config]
//! [main_start]

//! [main_use_case]
//! [read]
	spi_read_buffer_job(&spi_slave_instance, buffer_rx, BUF_LENGTH, 0x00);
//! [read]
//! [transf_complete]
	while(!transfer_complete_spi_slave) {
		/* Wait for transfer from master */
	}
//! [transf_complete]
//! [compare]
	for (uint8_t i = 0; i < BUF_LENGTH; i++) {
		if(buffer_rx[i] != buffer_expect[i]) {
			result++;
		}
	}
//! [compare]

//! [inf_loop]
	while (true) {
		/* Infinite loop */
		if (result) {
			port_pin_toggle_output_level(LED_0_PIN);
			/* Add a short delay to see LED toggle */
			volatile uint32_t delay = 30000;
			while(delay--) {
			}
		} else {
			port_pin_toggle_output_level(LED_0_PIN);
			/* Add a short delay to see LED toggle */
			volatile uint32_t delay = 600000;
			while(delay--) {
			}
		}
	}
//! [inf_loop]
//! [main_use_case]
}
