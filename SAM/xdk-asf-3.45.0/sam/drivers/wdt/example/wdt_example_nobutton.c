/**
 * \file
 *
 * \brief Watchdog Timer (WDT) example for SAM.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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
 * \mainpage Watchdog Timer Example
 *
 * \section Purpose
 *
 * This example uses a seconds counter event to simulate a deadlock in program so
 * as to demonstrate how watchdog timer works.
 *
 * \section Requirements
 *
 * This example can be used on any SAM3/4 boards without user buttons.
 *
 * \section Descriptions
 *
 * At first, the example configures the pins of LED and Console UART, enables
 * the watchdog timer, and then prints some information via UART.
 * Before seconds counter is reset, the LED keeps blinking and
 * the counter of the watchdog timer is restarted before any fault of the
 * watchdog timer occurs (the interrupt in this case). The example enters a
 * deadlock status after seconds counter become 0 and it causes that the counter
 * will not be restarted until a fault occurs (the interrupt). In the interrupt
 * handler, the counter is restarted.
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
	-- Watchdog with IRQ Interrupt Example --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 * -# After XX seconds the system enters in a deadlock loop.
\endcode
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "conf_board.h"
#include "led.h"
#include <stdio.h>

/** Reset counter 10 seconds */
#define RST_MS_COUNTER                    10000
/** Watchdog period 3000ms */
#define WDT_PERIOD                        3000
/** LED blink time 300ms */
#define BLINK_PERIOD                      300
/** Watchdog restart 2000ms */
#define WDT_RESTART_PERIOD                2000

#define STRING_EOL    "\r"
#define STRING_HEADER "--Watchdog with IRQ Interrupt Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/** System Tick event flag */
volatile bool g_b_systick_event = false;
/** System tick increased by 1 every millisecond */
volatile uint32_t g_ul_ms_ticks = 0;
/** Reset counter decreased by 1 every millisecond */
volatile uint32_t ul_rst_counter;

/**
 *  \brief Handler for System Tick interrupt.
 */
void SysTick_Handler(void)
{
	/* Set systick event flag (g_b_systick_event) and add 1 to systick. */
	g_b_systick_event = true;
	g_ul_ms_ticks++;
	/* Update reset counter */
	ul_rst_counter--;
}

/**
 *  \brief Handler for watchdog interrupt.
 */
void WDT_Handler(void)
{
	puts("Enter watchdog interrupt.\r");

	/* Clear status bit to acknowledge interrupt by dummy read. */
	wdt_get_status(WDT);
	/* Restart the WDT counter. */
	wdt_restart(WDT);
	puts("The watchdog timer was restarted.\r");
}

/**
 *  \brief Configure the Console UART.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
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
 * \brief Application entry point for wdt_irq example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint32_t wdt_mode, timeout_value;

	/* Initialize the system */
	sysclk_init();
	board_init();

	/* Configure pins of console UART, LED and push button on board. */
	configure_console();
	configure_led();

	/* Output example information. */
	puts(STRING_HEADER);

	/* Initialize reset counter */
	ul_rst_counter = RST_MS_COUNTER;

	/* Systick configuration. */
	puts("Configure systick to get 1ms tick period.\r");
	if (SysTick_Config(sysclk_get_cpu_hz() / 1000)) {
		puts("-F- Systick configuration error\r");
	}

	/* Get timeout value. */
	timeout_value = wdt_get_timeout_value(WDT_PERIOD * 1000,
			BOARD_FREQ_SLCK_XTAL);
	if (timeout_value == WDT_INVALID_ARGUMENT) {
		while (1) {
			/* Invalid timeout value, error. */
		}
	}
	/* Configure WDT to trigger an interrupt (or reset). */
	wdt_mode = WDT_MR_WDFIEN |  /* Enable WDT fault interrupt. */
			WDT_MR_WDRPROC   |  /* WDT fault resets processor only. */
			WDT_MR_WDDBGHLT  |  /* WDT stops in debug state. */
			WDT_MR_WDIDLEHLT;   /* WDT stops in idle state. */
	/* Initialize WDT with the given parameters. */
	wdt_init(WDT, wdt_mode, timeout_value, timeout_value);
	printf("Enable watchdog with %d microseconds period\n\r",
			(int)wdt_get_us_timeout_period(WDT, BOARD_FREQ_SLCK_XTAL));

	/* Configure and enable WDT interrupt. */
	NVIC_DisableIRQ(WDT_IRQn);
	NVIC_ClearPendingIRQ(WDT_IRQn);
	NVIC_SetPriority(WDT_IRQn, 0);
	NVIC_EnableIRQ(WDT_IRQn);

	printf("After %u seconds the system enters in a deadlock loop.\n\r", (int)ul_rst_counter/1000);

	while (1) {

		if (g_b_systick_event == true) {
			g_b_systick_event = false;

			/* Toggle LED at the given period. */
			if ((g_ul_ms_ticks % BLINK_PERIOD) == 0) {
#if (SAM4CM)
				LED_Toggle(LED4);
#else
				LED_Toggle(LED0);
#endif
			}

			/* Restart watchdog at the given period. */
			if ((g_ul_ms_ticks % WDT_RESTART_PERIOD) == 0) {
				wdt_restart(WDT);
			}
		}

		/* Simulate deadlock when reset counter is reset. */
		if (!ul_rst_counter) {
			puts("Program enters infinite loop for triggering watchdog interrupt.\r");
			while (1) {
			}
		}
	}
}