/**
 * \file
 *
 * \brief lcd controller ili9225 example.
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
 * \mainpage lcd controller ili9225 Example
 *
 * \section Purpose
 *
 * This example demonstrates how to configure lcd controller ili9225
 * to control the LCD on the board.
 *
 * \section Requirements
 *
 * This package can be used with SAM3N evaluation kits.
 *
 * \section Description
 *
 * This example first configure ili9225 for access the LCD controller,
 * then initialize the LCD, finally draw some text, image, basic shapes (line,
 * rectangle, circle) on LCD.
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board.
 * -# Some text, image and basic shapes should be displayed on the LCD.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "stdio_serial.h"
#include "conf_board.h"
#include "conf_clock.h"

struct ili9225_opt_t g_ili9225_display_opt;

/**
 * \brief Override SPI handler.
 */
void SPI_Handler(void)
{
	ili9225_spi_handler();
}

/**
 *  Configure UART console.
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
 * \brief Application entry point for ili9225_spi_lcd example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	sysclk_init();
	board_init();

	/* Initialize debug console */
	configure_console();

	/* Initialize display parameter */
	g_ili9225_display_opt.ul_width = ILI9225_LCD_WIDTH;
	g_ili9225_display_opt.ul_height = ILI9225_LCD_HEIGHT;
	g_ili9225_display_opt.foreground_color = COLOR_BLACK;
	g_ili9225_display_opt.background_color = COLOR_WHITE;

	/* Switch off backlight */
	aat31xx_disable_backlight();

	/* Initialize LCD */
	ili9225_init(&g_ili9225_display_opt);

	/* Set backlight level */
	aat31xx_set_backlight(AAT31XX_AVG_BACKLIGHT_LEVEL);

	/* Turn on LCD */
	ili9225_display_on();

	/* Draw filled rectangle with white color */
	ili9225_set_foreground_color(COLOR_WHITE);
	ili9225_draw_filled_rectangle(0, 0, ILI9225_LCD_WIDTH, ILI9225_LCD_HEIGHT);

	/* Draw text and basic shapes on the LCD */
	ili9225_set_foreground_color(COLOR_BLACK);
	ili9225_draw_string(10, 20, (uint8_t *)"ili9225_lcd");

	/* Draw three circle with red, green and blue color */
	ili9225_set_foreground_color(COLOR_RED);
	ili9225_draw_circle(60, 80, 30);
	ili9225_set_foreground_color(COLOR_GREEN);
	ili9225_draw_circle(60, 120, 30);
	ili9225_set_foreground_color(COLOR_BLUE);
	ili9225_draw_circle(60, 160, 30);

	/* Draw one line */
	ili9225_draw_line(0, 0, 176, 220);

	while (1) {
	}
}
