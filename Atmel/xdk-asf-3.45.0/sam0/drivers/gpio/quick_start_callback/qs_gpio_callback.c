/**
 * \file
 *
 * \brief GPIO Quick Start Guide with Callbacks for SAMB
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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
#include "conf_uart_serial.h"

//! [module_inst]
struct uart_module uart_instance;
//! [module_inst]

//! [callback_func]
static void gpio_callback(void)
{
	puts("GPIO callback\r\n"); 
}

//! [callback_func]

//! [setup]
static void configure_uart(void)
{
	//! [setup_uart_1]
	struct uart_config config_uart;
	//! [setup_uart_1]
	//! [setup_uart_2]
	uart_get_config_defaults(&config_uart);
	//! [setup_uart_2]
	//! [setup_uart_3]
	config_uart.baud_rate	      = CONF_STDIO_BAUDRATE;
	config_uart.pin_number_pad[0] = CONF_STDIO_PIN_PAD0;
	config_uart.pin_number_pad[1] = CONF_STDIO_PIN_PAD1;
	config_uart.pin_number_pad[2] = CONF_STDIO_PIN_PAD2;
	config_uart.pin_number_pad[3] = CONF_STDIO_PIN_PAD3;
	
	config_uart.pinmux_sel_pad[0] = CONF_STDIO_MUX_PAD0;
	config_uart.pinmux_sel_pad[1] = CONF_STDIO_MUX_PAD1;
	config_uart.pinmux_sel_pad[2] = CONF_STDIO_MUX_PAD2;
	config_uart.pinmux_sel_pad[3] = CONF_STDIO_MUX_PAD3;
	//! [setup_uart_3]
	//! [setup_uart_4]
	stdio_serial_init(&uart_instance, CONF_STDIO_USART_MODULE, &config_uart);
	//! [setup_uart_4]
}

static void configure_gpio(void)
{
	//! [setup_gpio_1]
	struct gpio_config config_gpio_pin;
	gpio_get_config_defaults(&config_gpio_pin);
	//! [setup_gpio_1]
	
	//! [setup_gpio_2]
	config_gpio_pin.direction  = GPIO_PIN_DIR_INPUT;
	config_gpio_pin.input_pull = GPIO_PIN_PULL_NONE;
	config_gpio_pin.aon_wakeup = false;	
	//! [setup_gpio_2]
	//! [setup_gpio_3]
	gpio_pin_set_config(BUTTON_0_PIN, &config_gpio_pin);
	//! [setup_gpio_3]
}

static void configure_gpio_callbacks(void)
{
	/* Register callback function. */
//! [callback_init]
	gpio_init();
//! [callback_init]
	//! [callback_reg]
	gpio_register_callback(BUTTON_0_PIN, gpio_callback,
			GPIO_CALLBACK_RISING);
	//! [callback_reg]
	//! [callback_en]
	gpio_enable_callback(BUTTON_0_PIN);
	//! [callback_en]
}
//! [setup]

int main(void)
{
	//! [run_initialize_i2c]
	system_clock_config(CLOCK_RESOURCE_XO_26_MHZ, CLOCK_FREQ_26_MHZ);

	//! [setup_init]
	configure_uart();

	configure_gpio();

	configure_gpio_callbacks();
	//! [setup_init]

	//! [main]
	while (true){
		
	}
	//! [main]
}