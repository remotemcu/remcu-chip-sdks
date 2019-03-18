/**
 * \file
 *
 * \brief ST7565R display controller driver example.
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
 * \mainpage
 *
 * \section intro Introduction
 * This simple example shows how to use the \ref st7565r_lcd_controller_group
 * for interfacing the ST7565R controller
 *
 * \section files Main files:
 * - st7565r_example.c: the ST7565R low level driver example
 * - conf_st7565r.h: configuration of the ST7565R controller and interface
 * - conf_board.h: configuration for the board
 * - conf_clock.h: configuration for the clocks used in the device
 * - interface configuration files.
 *
 * \section apiinfo ST7565R low level driver API
 * The ST7565R low level driver API can be found
 * \ref st7565r_lcd_controller_group "here".
 *
 * \section deviceinfo Device Info
 * All devices with a SPI (USART SPI) can be used.
 * \note Parallel interface is also possible, but not currently supported by the
 * driver.
 *
 * \section exampledescription Description of the example
 * The display is initialized and a pattern with alternating lines are drawn to
 * the entire screen. After this the screen is scrolled line by line using the
 * hardware scrolling function available in the LCD controller.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for AVR.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/">Microchip</A>.\n
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <board.h>
#include <sysclk.h>
#include <st7565r.h>

int main(void)
{
	//! the page address to write to
	uint8_t page_address;
	//! the column address, or the X pixel.
	uint8_t column_address;
	//! store the LCD controller start draw line
	uint8_t start_line_address = 0;

	board_init();
	sysclk_init();

	// initialize the interface (SPI), ST7565R LCD controller and LCD
	st7565r_init();

	// set addresses at beginning of display
	st7565r_set_page_address(0);
	st7565r_set_column_address(0);

	// fill display with lines
	for (page_address = 0; page_address <= 4; page_address++) {
		st7565r_set_page_address(page_address);
		for (column_address = 0; column_address < 128; column_address++) {
			st7565r_set_column_address(column_address);
			/* fill every other pixel in the display. This will produce
			horizontal lines on the display. */
			st7565r_write_data(0xAA);
		}
	}

	// scroll the display using hardware support in the LCD controller
	while (true) {
		st7565r_set_display_start_line_address(start_line_address++);
		delay_ms(250);
	}
}
