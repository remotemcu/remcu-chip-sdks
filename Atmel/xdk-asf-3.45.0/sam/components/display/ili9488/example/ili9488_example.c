/**
 * \file
 *
 * \brief lcd controller ili9488 example.
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
 * \mainpage lcd controller ili9488 Example
 *
 * \section Purpose
 *
 * This example demonstrates how to configure lcd controller ili9488
 * to control the LCD on the board.
 *
 * \section Requirements
 *
 * This package can be used with samv71_xplained_ultra evaluation kits.
 *
 * \section Description
 *
 * This example first configure ili9488 for access the LCD controller,
 * then initialize the LCD, finally draw some text, image, basic shapes (line,
 * rectangle, circle) on LCD.
 *
 * \section Usage
 *
 * -# Connect mXT143E Xplained(ILI9488 LCD Controller) to EXT2 on SAME70 Xplained Pro Kit using 20 pin connector.
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


struct ili9488_opt_t g_ili9488_display_opt;

/** Tick Counter in unit of ms. */
volatile uint32_t g_ul_tick_count;

/** System tick frequency in Hz. */
#define SYS_TICK_FREQ        1000

/**
 *  \brief Handler for System Tick interrupt.
 *
 *  Process System Tick Event.
 *  Increment the ul_ms_ticks counter.
 */
void SysTick_Handler(void)
{
	g_ul_tick_count++;
}


/**
 *  \brief Wait for some time in ms.
 *
 */
 void wait(volatile uint32_t ul_ms)
{
	uint32_t ul_start;
	uint32_t ul_current;

	ul_start = g_ul_tick_count;
	do {
		ul_current = g_ul_tick_count;
	} while (ul_current - ul_start < ul_ms);
}

/**
 *  Configure system tick to generate an interrupt every 1ms.
 */
static void configure_systick(void)
{
	uint32_t ul_flag;

	ul_flag = SysTick_Config(sysclk_get_cpu_hz() / SYS_TICK_FREQ);
	if (ul_flag) {
		puts("-F- Systick configuration error\r");
		while (1) {
		}
	}
}

/**
 *  Configure UART console.
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
	puts("ILI9488 example\n\r");
	
	configure_systick();

	/* Initialize display parameter */
	g_ili9488_display_opt.ul_width = ILI9488_LCD_WIDTH;
	g_ili9488_display_opt.ul_height = ILI9488_LCD_HEIGHT;
	g_ili9488_display_opt.foreground_color = COLOR_CONVERT(COLOR_WHITE);
	g_ili9488_display_opt.background_color = COLOR_CONVERT(COLOR_WHITE);

	/* Initialize LCD */
	ili9488_init(&g_ili9488_display_opt);
	
	/* Draw text, image and basic shapes on the LCD */
	ili9488_set_foreground_color(COLOR_CONVERT(COLOR_WHITE));
	ili9488_draw_filled_rectangle(0, 0, ILI9488_LCD_WIDTH,ILI9488_LCD_HEIGHT);
	
	
	ili9488_set_foreground_color(COLOR_CONVERT(COLOR_BLACK));
	ili9488_draw_string(10, 20, (uint8_t *)"ili9488_lcd example");
	wait(1000);
	
	ili9488_set_foreground_color(COLOR_CONVERT(COLOR_RED));
	ili9488_draw_circle(60, 160, 40);
	ili9488_set_foreground_color(COLOR_CONVERT(COLOR_GREEN));
	ili9488_draw_circle(120, 160, 40);
	ili9488_set_foreground_color(COLOR_CONVERT(COLOR_BLUE));
	ili9488_draw_circle(180, 160, 40);
	
	ili9488_set_foreground_color(COLOR_CONVERT(COLOR_VIOLET));
	ili9488_draw_line(0, 0, ILI9488_LCD_WIDTH, ILI9488_LCD_HEIGHT);
	
	while(1) {

	}
}

