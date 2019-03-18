/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * This is a bare minimum user application template.
 *
 * For documentation of the board, go \ref group_common_boards "here" for a link
 * to the board-specific documentation.
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# Basic usage of on-board LED and button
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>

int main (void)
{
	system_init();

	/* Insert application code here, after the board has been initialized. */

	/* This skeleton code simply sets the LED to the state of the button. */
	while (1) {
		/* Is button pressed? */
		if (port_pin_get_input_level(BUTTON_0_PIN) == BUTTON_0_ACTIVE) {
			/* Yes, so turn LED on. */
			port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
		} else {
			/* No, so turn LED off. */
			port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
		}
	}
}
