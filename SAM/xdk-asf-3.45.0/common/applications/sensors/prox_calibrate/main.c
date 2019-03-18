/**
 * \file
 *
 * \brief Common Sensor Service Proximity Sensor Calibration Example
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
 *
 * This application performs a multi-step manual calibration on a 3-channel
 * proximity sensor device.  An object (e.g. a hand) is placed in front of
 * the proximity sensor at the desired distance for proximity detection.
 * The user presses the button on the processor board to advance to the
 * next channel.  After each channel's threshold has been set, the program
 * will continuously display an indication of the current proximity
 * status for each channel.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/design-centers/8-bit">Atmel AVR</A>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <stdio.h>
#include <asf.h>
#include <led.h>

/* Proximity sensor settings */
#define SET_PROX_CURRENT    (true) /* If true, manually set proximity current */
#define PROX_CURRENT_mA     (150)  /* Current for proximity sensor LEDs (mA) */

/* Switch and LED definitions */
#define SWITCH_PRESSED   gpio_pin_is_low(GPIO_PUSH_BUTTON_0)

#if (BOARD == UC3_L0_XPLAINED)
#  define NUM_BLINK_LEDS (4)
#  define ALL_LEDS       (LED1 | LED2 | LED3 | LED4)
#  define PROMPT_LED     LED4     /* Blink while waiting for user input */
static const uint32_t led_array[NUM_BLINK_LEDS] = {LED1, LED2, LED3, LED4};

#else
#  define NUM_BLINK_LEDS   (4)
#  define ALL_LEDS         (LED0 | LED1 | LED2 | LED3)
#  define PROMPT_LED       LED0   /* Blink while waiting for user input */
static const uint32_t led_array[NUM_BLINK_LEDS] = {LED0, LED1, LED2, LED3};
#endif

/** Strings to display based on proximity values */
static const char *const prox_labels[4] = {
	"none  ",               /* PROXIMITY_NONE */
	"FAR   ",               /* PROXIMITY_FAR */
	"MEDIUM",               /* PROXIMITY_MEDIUM */
	"NEAR  "                /* PROXIMITY_NEAR */
};


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

/** \brief Proximity sensor threshold calibration application
 *
 * This application illustrates the use of the sensor_calibrate() function
 * to set the proximity detection thresholds in a 3-channel proximity sensor.
 * This threshold is the level at which the sensor will report that an object
 * is near the device.
 *
 * The calibration sequence requires three steps, one for each channel.  During
 * each step, an object is placed at the desired distance in front of the
 * sensor, and the user presses the button on the board to trigger a proximity
 * reading.
 *
 * After Step 3 is completed, the threshold values for the sensor are
 * calculated and are written to non-volatile (flash) memory on the
 * microcontroller.  These values will continue to be used for future
 * proximity readings, unless they are overwritten by an application
 * calling the sensor_set_threshold function for the proximity sensor
 * channel(s).
 */
int main(void)
{
	sensor_t prox_dev;           /* Proximity sensor device */
	sensor_data_t prox_data;     /* Proximity data */
	int led_num = 0;

	/* Initialize the board (Xplained UC3 or XMEGA & Xplained Sensor boards)
	 * I/O pin mappings and any other configurable resources selected in
	 * the build configuration.
	 */
	sensor_platform_init();

	LED_On(ALL_LEDS);

	/* Wait for user to press button to start */
	prompt_user("Press button to start");
	
	/* Attach descriptor and initialize the proximity sensor */
	sensor_attach(&prox_dev, SENSOR_TYPE_PROXIMITY, 0, 0);

#if (SET_PROX_CURRENT == true)
	/* Manually set LED current value for each channel */
	/* Otherwise, sensor will use default values */
	sensor_set_channel(&prox_dev, SENSOR_CHANNEL_ALL);
	sensor_set_current(&prox_dev, PROX_CURRENT_mA);
#endif

	/* Set sensor data output formats (for display after calibration
	 * complete) */
	prox_data.scaled = true;
	
	/* Perform calibration sequence */

	/* Step 1 */
	printf("Setting channel 1: ");
	prompt_user("Place object at desired distance and press button");
	(void)sensor_calibrate(&prox_dev, MANUAL_CALIBRATE, 1, NULL);

	/* Step 2 */
	printf("Setting channel 2: ");
	prompt_user("Place object at desired distance and press button");
	(void)sensor_calibrate(&prox_dev, MANUAL_CALIBRATE, 2, NULL);

	/* Step 3 */
	printf("Setting channel 3: ");
	prompt_user("Place object at desired distance and press button");
	if (sensor_calibrate(&prox_dev, MANUAL_CALIBRATE, 3, NULL) != true) {
		if (prox_dev.err == SENSOR_ERR_IO) {
			printf("Calibration failure: write error\n\r");
		} else {
			printf("Unknown error while calibrating device\n\r");
		}

		while (true) {
			/* Error occurred, loop forever */
		}
	}

	int16_t value;

	/* Display threshold values */
	sensor_set_channel(&prox_dev, 1);
	sensor_get_threshold(&prox_dev, SENSOR_THRESHOLD_NEAR_PROXIMITY,
			&value);
	printf("Channel 1 threshold = %d\r\n", value);

	sensor_set_channel(&prox_dev, 2);
	sensor_get_threshold(&prox_dev, SENSOR_THRESHOLD_NEAR_PROXIMITY,
			&value);
	printf("Channel 2 threshold = %d\r\n", value);

	sensor_set_channel(&prox_dev, 3);
	sensor_get_threshold(&prox_dev, SENSOR_THRESHOLD_NEAR_PROXIMITY,
			&value);
	printf("Channel 3 threshold = %d\r\n", value);

	/* Once the calibration is complete, the proximity status is
	 * continuously captured and displayed.
	 */

	while (true) {
		/* Change LED display */
		LED_Toggle(led_array [led_num++]);
		if (led_num >= NUM_BLINK_LEDS) {
			led_num = 0;
		}

		/* Sample proximity and display results for each channel */
		sensor_get_proximity(&prox_dev, &prox_data);

		printf("prox  = 1:%s 2:%s 3:%s\r\n",
				prox_labels[prox_data.proximity.value[0]],
				prox_labels[prox_data.proximity.value[1]],
				prox_labels[prox_data.proximity.value[2]]);

		delay_ms(500);
	}

	return 0;
}
