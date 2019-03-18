/**
 * \file
 *
 * \brief Reinforced Safety Watchdog Timer (RSWDT) example for SAM.
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
 * \mainpage Reinforced Safety Watchdog Timer Example
 *
 * \section Purpose
 *
 * This example uses a push button event to simulate a deadlock in program so
 * as to demonstrate how reinforced safety watchdog timer works.
 *
 * \section Requirements
 *
 * This package can be used with SAM evaluation kits.
 *
 * \section Descriptions
 *
 * At first, the example configures the pins of LED and Console UART, enables
 * the reinforced safety watchdog timer, and then prints some information via 
 * UART. Before user presses the push button that the information mentions, 
 * the LED keeps blinking and the counter of the watchdog timer is restarted 
 * before any fault of the watchdog timer occurs (the interrupt in this case).
 * The example enters a deadlock status after user presses the push button
 * and it causes that the counter will not be restarted until a fault
 * occurs (the interrupt). In the interrupt handler, the counter is restarted.
 *
 *
 * \section Usage
 *
 * -# Compile the application.
 * -# Connect the UART port of the evaluation board to the computer and open
 * it in a terminal.
 *    - Settings: 115200 bauds, 8 bits, 1 stop bit, no parity, no flow control.
 * -# Download the program into the evaluation board and run it.
 * -# Upon startup, the application will output the following lines on the UART:
 *    \code
	-- Reinforced Safety Watchdog with IRQ Interrupt Example --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 * -# Press the push button on board.
 *    \code
	Press xxx to simulate a deadlock loop.
\endcode
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "conf_board.h"
#include "led.h"
#include <stdio.h>

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/** Reinforced Safety Watchdog period 3000ms */
#define RSWDT_PERIOD                        3000
/** LED blink time 300ms */
#define BLINK_PERIOD                      300
/** Reinforced Safety Watchdog restart 2000ms */
#define RSWDT_RESTART_PERIOD                2000
/** PIO debounce filter parameters 10 Hz*/
#define PUSHBUTTON_FILTER_GLITCH_VAULE    10

#define STRING_EOL    "\r"
#define STRING_HEADER "--Reinforced Safety Watchdog with IRQ Interrupt Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/** Pushbutton event flag */
volatile bool g_b_button_event = false;
/** System Tick event flag */
volatile bool g_b_systick_event = false;
/** System tick increased by 1 every millisecond */
volatile uint32_t g_ul_ms_ticks = 0;


/**
 *  \brief Handler for System Tick interrupt.
 */
void SysTick_Handler(void)
{
	/* Set systick event flag (g_b_systick_event) and add 1 to systick. */
	g_b_systick_event = true;
	g_ul_ms_ticks++;
}

/**
 *  \brief Handler for reinforced safety watchdog interrupt.RSWDT and WDT are the same as the interrupt number.
 */
void WDT_Handler(void)
{
	puts("Enter reinforced safety watchdog interrupt.\r");

	/* Clear status bit to acknowledge interrupt by dummy read. */
	rswdt_get_status(RSWDT);
	/* Restart the RSWDT counter. */
	rswdt_restart(RSWDT);
	puts("The reinforced safety watchdog timer was restarted.\r");
}

/**
 *  \brief Handler for Button 1 rising edge interrupt.
 */
static void button_handler(uint32_t id, uint32_t mask)
{
	/* Set button event flag (g_b_button_event). */
	if ((PUSHBUTTON_ID == id) && (PUSHBUTTON_MASK == mask)) {
		g_b_button_event = true;
	}
}

/**
 *  \brief Configure the Console UART.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
#ifdef CONF_UART_CHAR_LENGTH
		.charlength = CONF_UART_CHAR_LENGTH,
#endif
		.paritytype = CONF_UART_PARITY,
#ifdef CONF_UART_STOP_BITS
		.stopbits = CONF_UART_STOP_BITS,
#endif
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 *  \brief Configure the Pushbutton.
 */
static void configure_button(void)
{
	/* Enable the peripheral clock for the push button on board. */
	pmc_enable_periph_clk(PUSHBUTTON_ID);

	/* Configure PIOs as input pins. */
	pio_configure(PUSHBUTTON_PIO, PUSHBUTTON_TYPE, PUSHBUTTON_MASK,
			PUSHBUTTON_ATTR);

	/* Adjust PIO debounce filter parameters. */
	pio_set_debounce_filter(PUSHBUTTON_PIO, PUSHBUTTON_MASK,
			PUSHBUTTON_FILTER_GLITCH_VAULE);

	/* Initialize PIO interrupt handler, interrupt on rising edge. */
	pio_handler_set(PUSHBUTTON_PIO, PUSHBUTTON_ID, PUSHBUTTON_MASK,
			PUSHBUTTON_ATTR, button_handler);
}

/**
 *  \brief Configure LED.
 */
static void configure_led(void)
{
	/* Configure PIOs for LED. */
	pio_configure(LED_PIO, LED_TYPE, LED_MASK, LED_ATTR);
}

/**
 * \brief Application entry point for RSWDT example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint32_t rswdt_mode, timeout_value;

	/* Initialize the system */
	sysclk_init();
	board_init();

	/* Configure pins of console UART, LED and push button on board. */
	configure_console();
	configure_led();
	configure_button();

	/* Output example information. */
	puts(STRING_HEADER);

	/* Systick configuration. */
	puts("Configure systick to get 1ms tick period.\r");
	if (SysTick_Config(sysclk_get_cpu_hz() / 1000)) {
		puts("-F- Systick configuration error\r");
	}
	
	/* Get timeout value. */
	timeout_value = rswdt_get_timeout_value(RSWDT_PERIOD * 1000,
			BOARD_FREQ_SLCK_XTAL);
	if (timeout_value == RSWDT_INVALID_ARGUMENT) {
		while (1) {
			/* Invalid timeout value, error. */
		}
	}
	/* Configure RSWDT to trigger an interrupt (or reset). */
	rswdt_mode = RSWDT_MR_WDFIEN |  /* Enable RSWDT fault interrupt. */
			RSWDT_MR_WDRPROC   |  /* RSWDT fault resets processor only. */
			RSWDT_MR_WDDBGHLT  |  /* RSWDT stops in debug state. */
			RSWDT_MR_WDIDLEHLT;   /* RSWDT stops in idle state. */
	/* Initialize RSWDT with the given parameters. */
	rswdt_init(RSWDT, rswdt_mode, timeout_value, timeout_value);
	printf("Enable reinforced safety watchdog with %d microseconds period\n\r",
			(int)rswdt_get_us_timeout_period(RSWDT, BOARD_FREQ_SLCK_XTAL));

	/* Configure and enable RSWDT interrupt. */
	NVIC_DisableIRQ(RSWDT_IRQn);
	NVIC_ClearPendingIRQ(RSWDT_IRQn);
	NVIC_SetPriority(RSWDT_IRQn, 0);
	NVIC_EnableIRQ(RSWDT_IRQn);

	/* Initialize and enable push button (PIO) interrupt. */
	pio_handler_set_priority(PUSHBUTTON_PIO, PUSHBUTTON_IRQn, 0);
	pio_enable_interrupt(PUSHBUTTON_PIO, PUSHBUTTON_MASK);

	printf("Press %s to simulate a deadlock loop.\n\r", PUSHBUTTON_STRING);

	while (1) {

		if (g_b_systick_event == true) {
			g_b_systick_event = false;

			/* Toggle LED at the given period. */
			if ((g_ul_ms_ticks % BLINK_PERIOD) == 0) {
				LED_Toggle(LED0);
			}

			/* Restart reinforced safety watchdog at the given period. */
			if ((g_ul_ms_ticks % RSWDT_RESTART_PERIOD) == 0) {
				rswdt_restart(RSWDT);
			}
		}

		/* Simulate deadlock when button is pressed. */
		if (g_b_button_event == true) {
			puts("Program enters infinite loop for triggering reinforced safety watchdog interrupt.\r");
			while (1) {
			}
		}
	}
}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
