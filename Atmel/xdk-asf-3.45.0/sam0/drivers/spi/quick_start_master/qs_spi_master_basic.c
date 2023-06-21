/**
 * \file
 *
 * \brief SAM SPI Quick Start for SAMB
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

//! [setup]
//! [buf_length]
#define BUF_LENGTH 20
//! [buf_length]
//! [slave_select_pin]
#define SLAVE_SELECT_PIN  CONF_PIN_SPI_SSN
//! [slave_select_pin]
//! [buffer]
static uint8_t buffer[BUF_LENGTH];
//! [buffer]

//! [dev_inst]
struct spi_module spi_master_instance;
//! [dev_inst]
//! [slave_dev_inst]
struct spi_slave_inst slave;
//! [slave_dev_inst]
//! [setup]

//! [configure_gpio]
static void configure_gpio(void)
{
	struct gpio_config config_gpio;

	gpio_get_config_defaults(&config_gpio);
	/* Set buttons as inputs */
	config_gpio.direction = GPIO_PIN_DIR_INPUT;
	config_gpio.input_pull = GPIO_PIN_PULL_UP;
	gpio_pin_set_config(BUTTON_0_PIN, &config_gpio);

	/* Configure LEDs as outputs, turn them off */
	config_gpio.direction = GPIO_PIN_DIR_OUTPUT;
	gpio_pin_set_config(LED_0_PIN, &config_gpio);
	gpio_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);
}
//! [configure_gpio]

//! [configure_spi]
static void configure_spi_master(void)
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
	/* Configure, initialize and enable SPI module */
//! [conf_defaults]
	spi_get_config_defaults(&config_spi_master);
//! [conf_defaults]
//! [transfer_mode]
	config_spi_master.transfer_mode = CONF_SPI_TRANSFER_MODE;
//! [transfer_mode]
//! [clock_divider]
	config_spi_master.clock_divider = 154;
//! [clock_divider]
	/* Configure pad 0 */
//! [sck]
	config_spi_master.pin_number_pad[0] = CONF_SPI_PIN_SCK;
	config_spi_master.pinmux_sel_pad[0] = CONF_SPI_MUX_SCK;
//! [sck]
	/* Configure pad 1 */
//! [mosi]
	config_spi_master.pin_number_pad[1] = CONF_SPI_PIN_MOSI;
	config_spi_master.pinmux_sel_pad[1] = CONF_SPI_MUX_MOSI;
//! [mosi]
	/* Configure pad 2 */
//! [ssn]
	config_spi_master.pin_number_pad[2] = PINMUX_UNUSED;
	config_spi_master.pinmux_sel_pad[2] = PINMUX_UNUSED;
//! [ssn]
	/* Configure pad 3 */
//! [miso]
	config_spi_master.pin_number_pad[3] = CONF_SPI_PIN_MISO;
	config_spi_master.pinmux_sel_pad[3] = CONF_SPI_MUX_MISO;
//! [miso]
//! [init]
	spi_init(&spi_master_instance, CONF_SPI, &config_spi_master);
//! [init]

//! [enable]
	spi_enable(&spi_master_instance);
//! [enable]

}
//! [configure_spi]

int main(void)
{
//! [main_setup]
//! [system_init]
	system_clock_config(CLOCK_RESOURCE_XO_26_MHZ, CLOCK_FREQ_26_MHZ);
	for (uint16_t i = 0; i < BUF_LENGTH; i++) {
		buffer[i] = i;
	}
//! [system_init]
//! [run_config_gpio]
	configure_gpio();
//! [run_config_gpio]
//! [run_config_spi]
	configure_spi_master();
//! [run_config_spi]
//! [main_setup]

//! [main_use_case]
//! [inf_loop]
	while (true) {
		/* Infinite loop */
		if(!gpio_pin_get_input_level(BUTTON_0_PIN)) {
			//! [select_slave]
			spi_select_slave(&spi_master_instance, &slave, true);
			//! [select_slave]
			//! [write]
			spi_write_buffer_wait(&spi_master_instance, buffer, BUF_LENGTH);
			//! [write]
			//! [delay]
			for(uint16_t i = 0; i < 0xFF; i++) {
				/* Wait for the last data shift out */
			}
			//! [delay]
			//! [deselect_slave]
			spi_select_slave(&spi_master_instance, &slave, false);
			//! [deselect_slave]
			//! [light_up]
			gpio_pin_set_output_level(LED_0_PIN, LED0_ACTIVE);
			//! [light_up]
		}
	}
//! [inf_loop]
//! [main_use_case]
}
