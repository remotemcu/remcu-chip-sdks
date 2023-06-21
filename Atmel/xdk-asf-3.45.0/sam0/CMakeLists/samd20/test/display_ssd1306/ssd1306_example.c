/**
 * \file
 *
 * \brief SSD1306 display controller driver example.
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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
 * This simple example shows how to use the \ref ssd1306_oled_controller_group
 * for interfacing the SSD1306 controller
 *
 * \section files Main files:
 * - ssd1306_example.c: the SSD1306 low level driver example
 * - conf_ssd1306.h: configuration of the SSD1306 controller and interface
 * - conf_board.h: configuration for the board
 * - conf_clocks.h: configuration for the clocks used in the device
 * - interface configuration files.
 *
 * \section apiinfo SSD1306 low level driver API
 * The SSD1306 low level driver API can be found
 * \ref ssd1306_lcd_controller_group "here".
 *
 * \section deviceinfo Device Info
 * All devices with a SPI can be used.
 * \note Parallel interface is also possible, but not currently supported by the
 * driver.
 *
 * \section exampledescription Description of the example
 * The display is initialized and a pattern with alternating lines are drawn to
 * the entire screen. After this the screen is scrolled line by line using the
 * hardware scrolling function available in the LCD controller.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/">Microchip</A>.\n
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include "ssd1306.h"

#include <assert.h>

#include "remcu.h"

int main(int argc, char** argv)
{
  printf("argc : %d\n", argc);

  if(argc < 3){
        printf("test requare 2 arguments: host and verbose level\n");
        printf("optional 3-d arg: testOpenocd(bool)\n");
        return -1;
    }
    const char * host = argv[1];
    printf("argv[1] : %s\n", argv[1]);
    printf("argv[2] : %s\n", argv[2]);
    const uint16_t port = (atoi(argv[2]) & 0xFFFF);
    printf("port : %d\n", port);

  if (port == 6666){
    remcu_connect2OpenOCD(host, 6666, 3);
  } else {
    remcu_connect2GDB(host, port, 3);
  }

  remcu_resetRemoteUnit(__HALT);
    //remcu_resetRemoteUnit(__RUN);
  //remcu_setVerboseLevel(__INFO);
  //remcu_setVerboseLevel(__ALL_LOG);

  assert(remcu_is_connected());
	//! the page address to write to
	uint8_t page_address;
	//! the column address, or the X pixel.
	uint8_t column_address;
	//! store the LCD controller start draw line
	uint8_t start_line_address = 0;

	system_init();

	// Initialize SPI and SSD1306 controller
	ssd1306_init();

	// set addresses at beginning of display
	ssd1306_set_page_address(0);
	ssd1306_set_column_address(0);

	printf("fill display...\n");

#if 0
	// fill display with lines
	for (page_address = 0; page_address < 4; page_address++) {
		ssd1306_set_page_address(page_address);
		for (column_address = 0; column_address < 128; column_address++) {
			ssd1306_set_column_address(column_address);
			/* fill every other pixel in the display. This will produce
			horizontal lines on the display. */
			ssd1306_write_data(0x00);
			printf("page_address %d | column_address %d\n", page_address, column_address);
		}
	}
#endif
	printf("wait command\n");

	ssd1306_set_display_start_line_address(0);

	ssd1306_write_text("Hello! It is REMCU library");

	while(1){

	}

}

void system_board_init(void)
{
	struct port_config pin_conf;
	port_get_config_defaults(&pin_conf);

	/* Configure LEDs as outputs, turn them off */
	pin_conf.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(LED_0_PIN, &pin_conf);
	port_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);

	/* Set buttons as inputs */
	pin_conf.direction  = PORT_PIN_DIR_INPUT;
	pin_conf.input_pull = PORT_PIN_PULL_UP;
	port_pin_set_config(BUTTON_0_PIN, &pin_conf);
}