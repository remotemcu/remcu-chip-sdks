/**
 * \file
 *
 * \brief SAM AON Sleep Timer Driver Quick Start for SAMB11
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
#include "conf_aon_sleep_timer.h"

//! [setup]

//! [callback_funcs]
static void aon_sleep_timer_callback(void)
{
	gpio_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
}
//! [callback_funcs]

static void configure_gpio_pins(void)
{
//! [setup_1]
	struct gpio_config config_gpio_pin;
//! [setup_1]
//! [setup_2]
	gpio_get_config_defaults(&config_gpio_pin);
//! [setup_2]
//! [setup_3]
	config_gpio_pin.direction = GPIO_PIN_DIR_OUTPUT;
//! [setup_3]
//! [setup_4]
	gpio_pin_set_config(LED_0_PIN, &config_gpio_pin);
//! [setup_4]
//! [setup_5]
	gpio_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);
//! [setup_5]
}

static void configure_aon_sleep_timer(void)
{
//! [setup_6]
	struct aon_sleep_timer_config config_aon_sleep_timer;
//! [setup_6]
//! [setup_7]
	aon_sleep_timer_get_config_defaults(&config_aon_sleep_timer);
//! [setup_7]
//! [setup_8]
	config_aon_sleep_timer.counter = CONF_AON_SLEEP_COUNTER;
	config_aon_sleep_timer.mode = AON_SLEEP_TIMER_SINGLE_MODE;
	config_aon_sleep_timer.wakeup = AON_SLEEP_TIMER_WAKEUP_ARM_BLE;
//! [setup_8]
//! [setup_9]
	aon_sleep_timer_init(&config_aon_sleep_timer);
//! [setup_9]

}

static void configure_aon_sleep_timer_callback(void)
{
	//! [setup_register_callback]
	aon_sleep_timer_register_callback(aon_sleep_timer_callback);
	//! [setup_register_callback]
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
	configure_aon_sleep_timer();
	//! [config_timer]

	configure_aon_sleep_timer_callback();
	//! [setup_init]

	//! [timer_active]
	while(!aon_sleep_timer_sleep_timer_active());
	//! [timer_active]
	//! [wait_wfi]
	/* wait for interrupt is just for demo application purpose. 
	It is not mandatory to add this instruction in actual application*/
	asm volatile ("wfi");
	asm volatile ("nop");
	//! [wait_wfi]

	//! [timer_disable]
	aon_sleep_timer_unregister_callback();
	aon_sleep_timer_disable();
	//! [timer_disable]

	//! [main_imp]
	//! [main_loop]
	while (true) {
	}
	//! [main_loop]
	//! [main_imp]
}
