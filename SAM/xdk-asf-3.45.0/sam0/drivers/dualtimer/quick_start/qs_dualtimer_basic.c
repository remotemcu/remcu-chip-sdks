/**
 * \file
 *
 * \brief SAM TIMER Driver Quick Start for SAMB11
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
#include <stdio_serial.h>
#include <string.h>
#include "conf_dualtimer.h"
#include "conf_uart_serial.h"

//! [module_inst]
struct uart_module uart_instance;
//! [module_inst]

//! [callback_funcs]
//! [print_timer1]
static void dualtimer_callback1(void)
{
	puts("Timer1 trigger\r\n");
}
//! [print_timer1]

//! [print_timer2]
static void dualtimer_callback2(void)
{
	puts("Timer2 trigger\r\n");
}
//! [print_timer2]
//! [callback_funcs]

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
	config_uart.baud_rate     = CONF_STDIO_BAUDRATE;
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

static void configure_dualtimer(void)
{
//! [setup_dualtimer_1]
	struct dualtimer_config config_dualtimer;
//! [setup_dualtimer_1]

//! [setup_dualtimer_2]
	dualtimer_get_config_defaults(&config_dualtimer);
//! [setup_dualtimer_2]
//! [setup_dualtimer_3]
	config_dualtimer.timer1.load_value = CONF_DUALTIMER_TIMER1_LOAD;
//! [setup_dualtimer_3]
//! [setup_dualtimer_4]
	config_dualtimer.timer2.load_value = CONF_DUALTIMER_TIMER2_LOAD;
//! [setup_dualtimer_4]

//! [setup_dualtimer_5]
	dualtimer_init(&config_dualtimer);
//! [setup_dualtimer_5]
}

static void configure_dualtimer_callback(void)
{
	//! [setup_register_callback]
	dualtimer_register_callback(DUALTIMER_TIMER1, dualtimer_callback1);
	dualtimer_register_callback(DUALTIMER_TIMER2, dualtimer_callback2);
	//! [setup_register_callback]

	//! [enable_IRQ]
	NVIC_EnableIRQ(DUALTIMER0_IRQn);
	//! [enable_IRQ]
}
//! [setup]

int main(void)
{
//! [setup_init]
	system_clock_config(CLOCK_RESOURCE_XO_26_MHZ, CLOCK_FREQ_26_MHZ);
//! [config_uart]
	configure_uart();
//! [config_uart]
//! [config_dualtimer]
	configure_dualtimer();
//! [config_dualtimer]
//! [config_callback]
	configure_dualtimer_callback();
//! [config_callback]
//! [setup_init]

//! [main_imp]
//! [main_loop]
	while (true) {

	}
//! [main_loop]
//! [main_imp]
}
