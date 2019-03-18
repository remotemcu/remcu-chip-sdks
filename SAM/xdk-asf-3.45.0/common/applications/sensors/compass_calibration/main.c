/**
 * \file
 *
 * \brief Common Sensor Service Compass Calibration Example
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
 *
 * This application performs a multi-step manual calibration on a compass
 * (magnetometer) sensor device.  The device must be physically manipulated
 * during the calibration process, between individual steps.  The user
 * presses the button on the processor board to move to the next calibration
 * step.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com/design-centers/8-bit">Atmel AVR</a>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <stdio.h>
#include <asf.h>
#include <led.h>

/* Switch and LED definitions */
#define SWITCH_PRESSED   gpio_pin_is_low(GPIO_PUSH_BUTTON_0)

#if (BOARD == UC3_L0_XPLAINED)
#  define NUM_BLINK_LEDS   (4)
#  define ALL_LEDS         (LED1 | LED2 | LED3 | LED4)
#  define PROMPT_LED       LED4 /* Blink while waiting for user input */
static const uint32_t led_array[NUM_BLINK_LEDS] = {LED1, LED2, LED3, LED4};
#else
#  define NUM_BLINK_LEDS   (4)
#  define ALL_LEDS         (LED0 | LED1 | LED2 | LED3)
#  define PROMPT_LED       LED0 /* Blink while waiting for user input */
static const uint32_t led_array[NUM_BLINK_LEDS] = {LED0, LED1, LED2, LED3};
#endif


/** \brief User prompt routine
 *
 * This routine prompts the user to press the button and then waits
 * for him to do so.
 */
static void prompt_user(char *prompt_string)
{
	/* Output prompt string */
	printf("%s\r\n", prompt_string);

	/* Wait for user to push button before continuing */
	LED_Off(ALL_LEDS);

	/* Just blink LED until button is pushed */
	while (!SWITCH_PRESSED) {
		LED_Toggle(PROMPT_LED);
		delay_ms(100);
	}

	LED_Off(PROMPT_LED);

	/* Wait until button is released */
	while (SWITCH_PRESSED) {
	}
}

/** \brief Compass / magnetometer calibration application
 *
 * This application illustrates the use of the sensor_calibrate() function
 * for compass/magnetometer calibration.  It prompts the user (via serial
 * output) to manipulate the sensor board and press a button to continue.
 *
 * The calibration process is used to correct for fixed magnetic forces
 * present on the board where the compass is mounted.  If uncorrected, these
 * fixed forces will prevent accurate measurement of the actual external
 * magnetic forces (e.g. magnetic North).
 *
 * The calibration sequence requires three steps.  During each step, the
 * board is placed in a specific orientation, and the user presses the button
 * on the board to trigger a compass sensor reading.
 *
 * The three orientations are:
 *   -#  Board lying flat (on a table, for example).
 *   -#  Board rotated 180 degrees (end-for-end), still lying flat.
 *   -#  Board flipped (inverted) so that the opposite side is facing up.
 *
 * After Step 3 is completed, the calibration values for the sensor are
 * calculated and are written to non-volatile (flash) memory on the
 * microcontroller.  These values will continue to be used for future
 * compass heading readings.
 */
int main(void)
{
	sensor_t compass_dev;           /* Compass/magnetometer device */
	sensor_data_t compass_data;     /* Compass data */

	/* Initialize hardware & sensor interfaces */
	sensor_platform_init();

	LED_On(ALL_LEDS);              

	/* Wait for user to press button to start */
	prompt_user("Press button to start");
	
	/* Attach descriptor and initialize the compass device */
	sensor_attach(&compass_dev, SENSOR_TYPE_COMPASS, 0, 0);

	/* Set sensor data output formats (for display after calibration
	 * is complete)
	 */
	compass_data.scaled = true;

	/* Perform calibration sequence */

	/* Step 1 */
	prompt_user("Lay board flat & press button");
	(void)sensor_calibrate(&compass_dev, MANUAL_CALIBRATE, 1, NULL);

	/* Step 2 */
	prompt_user("Rotate 180 degrees & press button");
	(void)sensor_calibrate(&compass_dev, MANUAL_CALIBRATE, 2, NULL);

	/* Step 3 */
	prompt_user("Flip board & press button");
	if (sensor_calibrate(&compass_dev, MANUAL_CALIBRATE, 3, NULL) == false) {
		if (compass_dev.err == SENSOR_ERR_IO) {
			printf("Calibration failure: write error\n\r");
		} else {
			printf("Unknown error while calibrating device\n\r");
		}

		while (true) {
			/* Error occurred, loop forever */
		}
	}

	/* Once the calibration is complete, the magnetic heading is
	 * continuously
	 * calculated and displayed.
	 */

	while (true) {
		static uint8_t led_num = 0;

		/* Change LED display */
		LED_Toggle(led_array[led_num++]);
		if (led_num >= NUM_BLINK_LEDS) {
			led_num = 0;
		}

		/* Sample compass and display heading values */
		sensor_get_heading(&compass_dev, &compass_data);

		printf("Direction = %d, Inclination = %d, Strength = %d uT\r\n",
				(int)compass_data.heading.direction,
				(int)compass_data.heading.inclination,
				(int)compass_data.heading.strength);

		delay_ms(100);
	}

	return 0;
}
