/**
 * \file
 *
 * \brief ads7843 touchscreen controller Example.
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
 * \mainpage ads7843 Touchscreen controller Example
 *
 * \section Purpose
 *
 * This example shows how to use SPI to control touchscreen controller (ADS7843).
 * It can also help you to get familiar with the touchscreen configurations
 * and usage, which can be used for fast implementation of your own touchscreen
 * driver and other applications related.
 *
 * \section Requirements
 *
 * This package can be used with SAM evaluation kits.
 *
 * \section Description
 *
 * This example first initialize LCD and touchscreen controller, then let
 * user do calibration for the touchscreen. After calibration is done, user may
 * touch the LCD and the pen position will be output on terminal.
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
 * -# Start the application
 * -# In HyperTerminal, it will show something like
 *     \code
	-- SPI_Touchscreen Example xxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 * -# Touch the dots on the LCD to calibrate the touchscreen, the calibration
 *    results will output on the terminal and LCD.
 * -# Touch the LCD, the pen position will output on the terminal
 *    if touchscreen is calibrated ok.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "stdio_serial.h"
#include "conf_board.h"
#include "resistive_touch_board.h"
#include "rtouch_calibrate.h"

/** IRQ priority for PIO (The lower the value, the greater the priority) */
#define IRQ_PRIOR_PIO    0

#define STRING_EOL    "\r"
#define STRING_HEADER "-- SPI_Touchscreen Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/** Tick Counter united by ms */
static volatile uint32_t g_ul_tick_count = 0;

/**
 * \brief Handler for SysTick interrupt. Increments the timestamp counter.
 */
void SysTick_Handler(void)
{
	g_ul_tick_count++;

	/* Call TSD_TimerHandler per 10ms */
	if ((g_ul_tick_count % 10) == 0) {
		rtouch_process();
	}
}

/**
 * \brief Callback called when the pen is pressed on the touchscreen.
 *
 * \param x horizontal position (in pixel if ts calibrated).
 * \param y vertical position (in pixel if ts calibrated).
 */
static void event_handler(rtouch_event_t const *event)
{
	switch(event->type) {
	case RTOUCH_MOVE:
		printf("Pen moved at     (%03u, %03u)\n\r", (unsigned int) event->panel.x, (unsigned int) event->panel.y);
		break;
	case RTOUCH_PRESS:
		printf("Pen pressed at   (%03u, %03u)\n\r", (unsigned int) event->panel.x, (unsigned int) event->panel.y);
		break;
	case RTOUCH_RELEASE:
		printf("Pen released at  (%03u, %03u)\n\r", (unsigned int) event->panel.x, (unsigned int) event->panel.y);
		break;
	default:
		break;
	}
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
 * \brief Application entry point for spi_touchscreen example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t uc_result;

	sysclk_init();
	board_init();

	configure_console();

	/* Enable clocks for push buttons management */
	pmc_enable_periph_clk(ID_PIOA);
	pmc_enable_periph_clk(ID_PIOB);
	pmc_enable_periph_clk(ID_PIOC);

	/* Output example information */
	puts(STRING_HEADER);

	/* Configure systick for 1 ms. */
	puts("Configure system tick to get 1ms tick period.\r");
	if (SysTick_Config(sysclk_get_cpu_hz() / 1000)) {
		puts("Systick configuration error\r");
		while (1);
	}

	/* Switch off backlight */
	aat31xx_disable_backlight();

	lcd_init();

	lcd_set_foreground_color(UNI_COLOR_WHITE);
	lcd_draw_filled_rectangle(0, 0, LCD_WIDTH, LCD_HEIGHT);

	/* Turn on LCD */
	lcd_display_on();

	/* Switch on backlight */
	aat31xx_set_backlight(AAT31XX_MAX_BACKLIGHT_LEVEL);

	/* Initializes the PIO interrupt management for touchscreen driver */
	pio_handler_set_priority(PIOA, PIOA_IRQn, IRQ_PRIOR_PIO);
	pio_handler_set_priority(PIOB, PIOB_IRQn, IRQ_PRIOR_PIO);
	pio_handler_set_priority(PIOC, PIOC_IRQn, IRQ_PRIOR_PIO);

	/* Initialize touchscreen without calibration */
	rtouch_init(LCD_WIDTH, LCD_HEIGHT);
	rtouch_enable();
	rtouch_set_event_handler(event_handler);

	while (1) {
		uc_result = rtouch_calibrate();
		if (uc_result == 0) {
			puts("Calibration successful !\r");
			break;
		} else {
			puts("Calibration failed; error delta is too big ! Please retry calibration procedure...\r");
		}
	}

	while (1) {
	}
}
