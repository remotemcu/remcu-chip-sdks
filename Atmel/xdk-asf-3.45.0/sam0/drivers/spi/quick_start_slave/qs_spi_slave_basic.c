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

void configure_spi_slave(void);

//! [setup]
//! [buf_length]
#define BUF_LENGTH 20
//! [buf_length]

//! [buffer]
static uint8_t buffer_expect[BUF_LENGTH];
static uint8_t buffer_rx[BUF_LENGTH] = {0x00};
//! [buffer]

//! [dev_inst]
struct spi_module spi_slave_instance;
//! [dev_inst]
//! [setup]

//! [configure_gpio]
static void configure_gpio(void)
{
	struct gpio_config config_gpio;

	gpio_get_config_defaults(&config_gpio);

	/* Configure LEDs as outputs, turn them off */
	config_gpio.direction = GPIO_PIN_DIR_OUTPUT;
	gpio_pin_set_config(LED_0_PIN, &config_gpio);
	gpio_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);
}
//! [configure_gpio]

//! [configure_spi]
void configure_spi_slave(void)
{
//! [config]
	struct spi_config config_spi_slave;
//! [config]
	/* Configure, initialize and enable SPI module */
//! [conf_defaults]
	spi_get_config_defaults(&config_spi_slave);
//! [conf_defaults]
//! [conf_spi_slave_instance]
	config_spi_slave.mode = SPI_MODE_SLAVE;
//! [conf_spi_slave_instance]
//! [transfer_mode]
	config_spi_slave.transfer_mode = CONF_SPI_TRANSFER_MODE;
//! [transfer_mode]
	/* Configure pad 0 */
//! [sck]
	config_spi_slave.pin_number_pad[0] = CONF_SPI_PIN_SCK;
	config_spi_slave.pinmux_sel_pad[0] = CONF_SPI_MUX_SCK;
//! [sck]
	/* Configure pad 1 */
//! [mosi]
	config_spi_slave.pin_number_pad[1] = CONF_SPI_PIN_MOSI;
	config_spi_slave.pinmux_sel_pad[1] = CONF_SPI_MUX_MOSI;
//! [mosi]
	/* Configure pad 2 */
//! [ssn]
	config_spi_slave.pin_number_pad[2] = CONF_SPI_PIN_SSN;
	config_spi_slave.pinmux_sel_pad[2] = CONF_SPI_MUX_SSN;
//! [ssn]
	/* Configure pad 3 */
//! [miso]
	config_spi_slave.pin_number_pad[3] = CONF_SPI_PIN_MISO;
	config_spi_slave.pinmux_sel_pad[3] = CONF_SPI_MUX_MISO;
//! [miso]
//! [init]
	spi_init(&spi_slave_instance, CONF_SPI, &config_spi_slave);
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
	uint16_t i;
	uint32_t delay;

	/* Initialize system */
//! [system_init]
	system_clock_config(CLOCK_RESOURCE_XO_26_MHZ, CLOCK_FREQ_26_MHZ);
	for (i = 0; i < BUF_LENGTH; i++) {
		buffer_expect[i] = i;
		buffer_rx[i] = 0;
	}
//! [system_init]

//! [run_config_gpio]
	configure_gpio();
//! [run_config_gpio]
//! [run_config_spi]
	configure_spi_slave();
//! [run_config_spi]
//! [main_start]

//! [main_use_case]
//! [read]
	memset(buffer_rx, 0x0, BUF_LENGTH);
	while(spi_read_buffer_wait(&spi_slave_instance, buffer_rx, BUF_LENGTH,
		0x00) != STATUS_OK) {
		/* Wait for transfer from the master */
	}
//! [read]
//! [compare]
	for (i = 0; i < BUF_LENGTH; i++) {
		if(buffer_rx[i] != buffer_expect[i]) {
			result++;
		}
	}
//! [compare]
//! [inf_loop]
	while (true) {
		/* Infinite loop */
		if (result) {
			gpio_pin_toggle_output_level(LED_0_PIN);
			/* Add a short delay to see LED toggle */
			delay = 300000;
			while(delay--) {
			}
		} else {
			gpio_pin_toggle_output_level(LED_0_PIN);
			/* Add a short delay to see LED toggle */
			delay = 3000000;
			while(delay--) {
			}
		}
	}
//! [inf_loop]
//! [main_use_case]
}
