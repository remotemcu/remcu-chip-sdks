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
#include "conf_timer.h"

//! [setup]
//! [callback_funcs]
static void timer_callback(void)
{
	gpio_pin_toggle_output_level(LED_0_PIN);
}
//! [callback_funcs]

static void configure_gpio_pins(void)
{
//! [setup_gpio_1]
	struct gpio_config config_gpio_pin;
//! [setup_gpio_1]
//! [setup_gpio_2]
	gpio_get_config_defaults(&config_gpio_pin);
//! [setup_gpio_2]

//! [setup_gpio_3]
	config_gpio_pin.direction = GPIO_PIN_DIR_OUTPUT;
//! [setup_gpio_3]
//! [setup_gpio_4]
	gpio_pin_set_config(LED_0_PIN, &config_gpio_pin);
//! [setup_gpio_4]
}

static void configure_timer(void)
{
//! [setup_timer_1]
	struct timer_config config_timer;
//! [setup_timer_1]
//! [setup_timer_2]
	timer_get_config_defaults(&config_timer);
//! [setup_timer_2]
//! [setup_timer_3]
	config_timer.reload_value = CONF_TIMER_RELOAD_VALUE;
//! [setup_timer_3]
//! [setup_timer_4]
	timer_init(&config_timer);
//! [setup_timer_4]
//! [setup_timer_5]
	timer_enable();
//! [setup_timer_5]
}

static void configure_timer_callback(void)
{
	//! [setup_register_callback]
	timer_register_callback(timer_callback);
	//! [setup_register_callback]
	
	//! [enable_IRQ]
	NVIC_EnableIRQ(TIMER0_IRQn);
	//! [enable_IRQ]
}
//! [setup]

int main(void)
{
	/**
	 * For make this QS work, disable the systick to stop task switch.
	 * Should not do it if you want the BLE functions.
	 */
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

//! [setup_init]
	system_clock_config(CLOCK_RESOURCE_XO_26_MHZ, CLOCK_FREQ_26_MHZ);

//! [config_gpio]
	configure_gpio_pins();
//! [config_gpio]

//! [config_timer]
	configure_timer();
//! [config_timer]

//! [config_timer_callback]
	configure_timer_callback();
//! [config_timer_callback]
//! [setup_init]
	
//! [main_loop]
	while (true) {
	}
//! [main_loop]
}
