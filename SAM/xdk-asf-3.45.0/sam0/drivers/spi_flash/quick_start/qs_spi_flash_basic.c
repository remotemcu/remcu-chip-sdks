/**
 * \file
 *
 * \brief SAM SPI Flash Driver Quick Start for SAMB11
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

//! [buffer]
#define len_buf    FLASH_PAGE_SIZE

volatile uint8_t read_buf[len_buf];
volatile uint8_t write_buf[len_buf];
//! [buffer]

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

int main(void)
{
	uint32_t delay = 0;
	uint32_t i;
	
//! [system_init]
	system_clock_config(CLOCK_RESOURCE_XO_26_MHZ, CLOCK_FREQ_26_MHZ);
//! [system_init]
//! [run_config_gpio]
	configure_gpio();
//! [run_config_gpio]

//! [setup_init]
//!   [setup_1]
	for (i = 0; i < len_buf; i++) {
		write_buf[i] = i;
	}
//!   [setup_1]
//!   [setup_2]
	spi_flash_init();
//!   [setup_2]
//! [setup_init]

//! [main_use_case]
//!   [main_1]
	while(spi_flash_erase((unsigned long)FLASH_NVDS_START_ADDRESS, len_buf)) {
		gpio_pin_toggle_output_level(LED_0_PIN);
		/* Add a short delay to see LED toggle */
		delay = 300000;
		while(delay--) {
		}
	}
//!  [main_1]

//!  [main_2]
	spi_flash_read((unsigned char *)read_buf, \
				(unsigned long)FLASH_NVDS_START_ADDRESS, \
				len_buf);
//!  [main_2]

//!  [main_3]
	for (i = 0; i < len_buf; i++) {
		if(read_buf[i] != 0xFF) {
			while(1) {
				gpio_pin_toggle_output_level(LED_0_PIN);
				/* Add a short delay to see LED toggle */
				delay = 300000;
				while(delay--) {
				}
			}
		}
	}
//!  [main_3]

//!  [main_4]
	spi_flash_write((unsigned char *)write_buf, \
				(unsigned long)FLASH_NVDS_START_ADDRESS, \
				len_buf);
//!  [main_4]

//!  [main_5]
	spi_flash_read((unsigned char *)read_buf, \
				(unsigned long)FLASH_NVDS_START_ADDRESS, \
				len_buf);
//!  [main_5]

//!  [main_6]
	for (i = 0; i < len_buf; i++) {
		if(read_buf[i] != write_buf[i]) {
			while(1) {
				gpio_pin_toggle_output_level(LED_0_PIN);
				/* Add a short delay to see LED toggle */
				delay = 300000;
				while(delay--) {
				}
			}
		}
	}
//!  [main_6]

//!  [inf_loop]
	while (true) {
		gpio_pin_toggle_output_level(LED_0_PIN);
		/* Add a short delay to see LED toggle */
		delay = 5000000;
		while(delay--) {
		}
	}
//!  [inf_loop]
//! [main_use_case]
}
