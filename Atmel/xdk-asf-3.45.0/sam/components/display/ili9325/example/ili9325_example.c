/**
 * \file
 *
 * \brief lcd controller ili9325 example.
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
 * \mainpage lcd controller ili9325 Example
 *
 * \section Purpose
 *
 * This example demonstrates how to configure lcd controller ili9325
 * to control the LCD on the board.
 *
 * \section Requirements
 *
 * This package can be used with SAM3S, SAM3S-EK2 and SAM4S evaluation kits.
 *
 * \section Description
 *
 * This example first configure ili9325 for access the LCD controller,
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

/* Chip select number to be set */
#define ILI9325_LCD_CS      1

struct ili9325_opt_t g_ili9325_display_opt;

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
 * \brief Application entry point for smc_lcd example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	sysclk_init();
	board_init();
	
	/* Initialize debug console */
	configure_console();

	/* Enable peripheral clock */
	pmc_enable_periph_clk(ID_SMC);

	/* Configure SMC interface for Lcd */
	smc_set_setup_timing(SMC,ILI9325_LCD_CS,SMC_SETUP_NWE_SETUP(2)
			| SMC_SETUP_NCS_WR_SETUP(2)
			| SMC_SETUP_NRD_SETUP(2)
			| SMC_SETUP_NCS_RD_SETUP(2));
	smc_set_pulse_timing(SMC, ILI9325_LCD_CS , SMC_PULSE_NWE_PULSE(4)
			| SMC_PULSE_NCS_WR_PULSE(4)
			| SMC_PULSE_NRD_PULSE(10)
			| SMC_PULSE_NCS_RD_PULSE(10));
	smc_set_cycle_timing(SMC, ILI9325_LCD_CS, SMC_CYCLE_NWE_CYCLE(10)
			| SMC_CYCLE_NRD_CYCLE(22));
#if !defined(SAM4S)
	smc_set_mode(SMC, ILI9325_LCD_CS, SMC_MODE_READ_MODE
			| SMC_MODE_WRITE_MODE
			| SMC_MODE_DBW_8_BIT);
#else
	smc_set_mode(SMC, ILI9325_LCD_CS, SMC_MODE_READ_MODE
			| SMC_MODE_WRITE_MODE);
#endif
	/* Initialize display parameter */
	g_ili9325_display_opt.ul_width = ILI9325_LCD_WIDTH;
	g_ili9325_display_opt.ul_height = ILI9325_LCD_HEIGHT;
	g_ili9325_display_opt.foreground_color = COLOR_BLACK;
	g_ili9325_display_opt.background_color = COLOR_WHITE;

	/* Switch off backlight */
	aat31xx_disable_backlight();

	/* Initialize LCD */
	ili9325_init(&g_ili9325_display_opt);

	/* Set backlight level */
	aat31xx_set_backlight(AAT31XX_AVG_BACKLIGHT_LEVEL);

	ili9325_set_foreground_color(COLOR_WHITE);
	ili9325_draw_filled_rectangle(0, 0, ILI9325_LCD_WIDTH, ILI9325_LCD_HEIGHT);

	/* Turn on LCD */
	ili9325_display_on();

	/* Draw text, image and basic shapes on the LCD */
	ili9325_set_foreground_color(COLOR_BLACK);
	ili9325_draw_string(10, 20, (uint8_t *)"ili9325_lcd example");

	ili9325_set_foreground_color(COLOR_RED);
	ili9325_draw_circle(60, 160, 40);
	ili9325_set_foreground_color(COLOR_GREEN);
	ili9325_draw_circle(120, 160, 40);
	ili9325_set_foreground_color(COLOR_BLUE);
	ili9325_draw_circle(180, 160, 40);

	ili9325_set_foreground_color(COLOR_VIOLET);
	ili9325_draw_line(0, 0, 240, 320);

	while (1) {
	}
}

