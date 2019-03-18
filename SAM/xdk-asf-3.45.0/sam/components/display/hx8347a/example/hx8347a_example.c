/**
 * \file
 *
 * \brief lcd controller HX8347A example.
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
 * \mainpage lcd controller HX8347A example
 *
 * \section Purpose
 *
 * This example demonstrates how to configure lcd controller HX8347A
 * to control the LCD on the board.
 *
 * \section Requirements
 *
 * This example can be used with SAM3U and SAM3X evaluation kits now.
 *
 * \section Description
 *
 * This example first configures HX8347A for access the LCD controller,
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

struct hx8347a_opt_t g_hx8347a_display_opt;

/* Convert 24-bits color to 16-bits color */
static hx8347a_color_t rgb24_to_rgb16(uint32_t ul_color)
{
	hx8347a_color_t result_color;
	result_color = (((ul_color >> 8) & 0xF800) |
			((ul_color >> 5) & 0x7E0) | ((ul_color >> 3) & 0x1F));
	return result_color;
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
	smc_set_setup_timing(SMC, CONF_BOARD_HX8347A_LCD_CS, SMC_SETUP_NWE_SETUP(1)
			| SMC_SETUP_NCS_WR_SETUP(1)
			| SMC_SETUP_NRD_SETUP(9)
			| SMC_SETUP_NCS_RD_SETUP(9));
	smc_set_pulse_timing(SMC, CONF_BOARD_HX8347A_LCD_CS, SMC_PULSE_NWE_PULSE(4)
			| SMC_PULSE_NCS_WR_PULSE(4)
			| SMC_PULSE_NRD_PULSE(36)
			| SMC_PULSE_NCS_RD_PULSE(36));
	smc_set_cycle_timing(SMC, CONF_BOARD_HX8347A_LCD_CS, SMC_CYCLE_NWE_CYCLE(10)
			| SMC_CYCLE_NRD_CYCLE(45));
	smc_set_mode(SMC, CONF_BOARD_HX8347A_LCD_CS, SMC_MODE_READ_MODE
			| SMC_MODE_WRITE_MODE | SMC_MODE_DBW_BIT_16);

	/* Initialize display parameter */
	g_hx8347a_display_opt.ul_width = HX8347A_LCD_WIDTH;
	g_hx8347a_display_opt.ul_height = HX8347A_LCD_HEIGHT;
	g_hx8347a_display_opt.foreground_color = rgb24_to_rgb16(COLOR_BLACK);
	g_hx8347a_display_opt.background_color = rgb24_to_rgb16(COLOR_WHITE);

	/* Switch off backlight */
	aat31xx_disable_backlight();

	/* Initialize LCD */
	if(hx8347a_init(&g_hx8347a_display_opt)){
		puts("Read HX8347A chip ID error, please check the configuration.\r");
	}

	/* Set backlight level */
	aat31xx_set_backlight(AAT31XX_AVG_BACKLIGHT_LEVEL);

	hx8347a_set_foreground_color(rgb24_to_rgb16(COLOR_WHITE));
	hx8347a_draw_filled_rectangle(0, 0, HX8347A_LCD_WIDTH - 1, HX8347A_LCD_HEIGHT - 1);

	/* Turn on LCD */
	hx8347a_display_on();

	/* Draw text, image and basic shapes on the LCD */
	hx8347a_set_foreground_color(rgb24_to_rgb16(COLOR_BLACK));
	hx8347a_draw_string(10, 20, (uint8_t *)"HX8347A LCD Example");

	hx8347a_set_foreground_color(rgb24_to_rgb16(COLOR_RED));
	hx8347a_draw_circle(60, 120, 40);
	hx8347a_set_foreground_color(rgb24_to_rgb16(COLOR_GREEN));
	hx8347a_draw_circle(120, 120, 40);
	hx8347a_set_foreground_color(rgb24_to_rgb16(COLOR_BLUE));
	hx8347a_draw_circle(180, 120, 40);

	hx8347a_set_foreground_color(rgb24_to_rgb16(COLOR_VIOLET));
	hx8347a_draw_rectangle(40, 200, 200, 260);
	hx8347a_draw_line(40, 200, 200, 260);
	hx8347a_draw_line(40, 260, 200, 200);
	hx8347a_draw_line(40, 230, 200, 230);
	hx8347a_draw_line(120, 200, 120, 260);

	while (1) {
		/* Busy-wait forever. */
	}
}

