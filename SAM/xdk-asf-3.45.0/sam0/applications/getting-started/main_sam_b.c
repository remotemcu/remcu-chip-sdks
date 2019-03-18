/**
 * \file
 *
 * \brief Getting Started Application.
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

/**
 * \mainpage Getting Started Application
 *
 * \section Purpose
 *
 * The Getting Started example will help new users get familiar with Atmel's
 * SAM family of microcontrollers. This basic application shows the startup
 * sequence of a chip and how to use its core peripherals.
 *
 * \section Requirements
 *
 * This application has been tested on following boards:
 * - SAM B11 Xplained Pro
 *
 * \section Description
 *
 * The program demo how LED,button,interrupt and dualtimer work.
 * It makes the LED on the board blink at a fixed rate.
 * The blinking can be stopped/started by using the push button.
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# The LED(s) should start blinking on the board. In the terminal window, the
 *    following text should appear (values depend on the board and chip used):
 *    \code
 *     -- Getting Started Example xxx --
 *     -- xxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *    \endcode
 * -# Pressing and release button SW0 should make LED0 stop and restart blinking.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <conf_uart_serial.h>
#include <conf_example.h>


#define STRING_EOL    "\r"
#define STRING_HEADER "-- Getting Started Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --\r\n" \
		"-- Pressing and release button SW0 should make LED0 on and off --"STRING_EOL


#ifdef __cplusplus
extern "C" {
#endif

static struct uart_module cdc_uart_module;

volatile bool g_b_led0_active;

static void delay(uint32_t count)
{
	for (uint32_t i = 0; i < count; i++) {
		for (uint32_t j = 0; j < 100; j++)
			asm volatile ("nop");
	}
}

/**
 *  Configure UART console.
 */
static void configure_console(void)
{
	struct uart_config config_uart;

	uart_get_config_defaults(&config_uart);

	config_uart.baud_rate = CONF_STDIO_BAUDRATE;
	config_uart.pin_number_pad[0] = CONF_STDIO_PIN_PAD0;
	config_uart.pin_number_pad[1] = CONF_STDIO_PIN_PAD1;
	config_uart.pin_number_pad[2] = CONF_STDIO_PIN_PAD2;
	config_uart.pin_number_pad[3] = CONF_STDIO_PIN_PAD3;
	
	config_uart.pinmux_sel_pad[0] = CONF_STDIO_MUX_PAD0;
	config_uart.pinmux_sel_pad[1] = CONF_STDIO_MUX_PAD1;
	config_uart.pinmux_sel_pad[2] = CONF_STDIO_MUX_PAD2;
	config_uart.pinmux_sel_pad[3] = CONF_STDIO_MUX_PAD3;

	stdio_serial_init(&cdc_uart_module, CONF_STDIO_USART_MODULE, &config_uart);
}

/** Callback function for the GPIO driver, called when a GPIO interrupt
 *  detection occurs.
 */
static void gpio_callback(void)
{
	g_b_led0_active = true;
}

/** Configures and registers the GPIO callback function with the
 *  driver.
 */
static void configure_gpio_callback(void)
{
	gpio_init();
	gpio_register_callback(BUTTON_0_PIN, gpio_callback,
			GPIO_CALLBACK_FALLING);
	gpio_enable_callback(BUTTON_0_PIN);
}

static void configure_gpio_pins(void)
{
	struct gpio_config config_gpio_pin;

	gpio_get_config_defaults(&config_gpio_pin);

	config_gpio_pin.direction  = GPIO_PIN_DIR_INPUT;
	config_gpio_pin.input_pull = GPIO_PIN_PULL_NONE;

	gpio_pin_set_config(BUTTON_0_PIN, &config_gpio_pin);

	config_gpio_pin.direction = GPIO_PIN_DIR_OUTPUT;

	gpio_pin_set_config(LED_0_PIN, &config_gpio_pin);
}


/** Dual Timer 1 Callback function.
 */
static void dualtimer_callback1(void)
{
	puts("Timer1 trigger\r\n");
}

/** Dual Timer 2 Callback function.
 */
static void dualtimer_callback2(void)
{
	puts("Timer2 trigger\r\n");
}

/** Configures Timer function with the  driver.
 */
static void configure_dualtimer(void)
{
	struct dualtimer_config config_dualtimer;

	dualtimer_get_config_defaults(&config_dualtimer);

	config_dualtimer.timer1.load_value = CONF_DUALTIMER_TIMER1_LOAD_VALUE;
	config_dualtimer.timer2.load_value = CONF_DUALTIMER_TIMER2_LOAD_VALUE;

	dualtimer_init(&config_dualtimer);
}

/** Registers Timer callback function with the  driver.
 */
static void configure_dualtimer_callback(void)
{
	dualtimer_register_callback(DUALTIMER_TIMER1, dualtimer_callback1);
	dualtimer_register_callback(DUALTIMER_TIMER2, dualtimer_callback2);

	NVIC_EnableIRQ(DUALTIMER0_IRQn);
}

/**
 *  \brief getting-started Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
*/
int main(void)
{
	system_clock_config(CLOCK_RESOURCE_XO_26_MHZ, CLOCK_FREQ_26_MHZ);

	/*Configure UART console.*/
	configure_console();

	/* Output example information */
	puts(STRING_HEADER);

	/*Configures GPIO pins */
	configure_gpio_pins();

	/*Configures GPIO callback */
	configure_gpio_callback();

	/* Configures Dual Timer driver */
	configure_dualtimer();

	/* Configures Dual Timer callback */
	configure_dualtimer_callback();

	g_b_led0_active = true;

	/*main loop*/
	while (1) {
		/* Wait for LED to be active */
		while (!g_b_led0_active);
		/* Toggle LED state if active */
		gpio_pin_toggle_output_level(LED_0_PIN);
		/* Wait for some time */
		delay(CONF_DELAY_VALUE);
		g_b_led0_active = false;
	}

}

#ifdef __cplusplus
}
#endif
