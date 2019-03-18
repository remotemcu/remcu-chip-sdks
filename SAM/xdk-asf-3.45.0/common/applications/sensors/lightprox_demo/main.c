/**
 * \file
 *
 * \brief Common Sensor Service Light and Proximity Sensor Example
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
 * This application obtains sensor data from a light and proximity sensor
 * device installed on an Atmel development board.
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

/* Configuration constants */
#define LIGHT_SAMPLE_RATE   (10)   /* Light sensor sample rate (Hz) */
#define PROX_SAMPLE_RATE    (10)   /* Proximity sensor sample rate (Hz) */

#define SET_PROX_THRESHOLD  (true) /* If true, manually set proximity
	                            * threshold */
#define PROX_THRESHOLD      (100)  /* Manual prox sensor threshold for "near" */

#define SET_PROX_CURRENT    (true) /* If true, manually set proximity current */
#define PROX_CURRENT_mA     (50)   /* Current for proximity sensor LEDs (mA) */

#define PRINT_BANNER        (true) /* If true, print sensor config
	                            * information */
#define SCALED_DATA         (true) /* If true, convert sensor data to standard
	                            * units. */

/* Hardware environment constants */
#define ACTIVITY_LED        (LED1) /* Which LED to blink to show activity */

/** Strings to display based on proximity values */
static const char *const prox_labels[4] = {
	"none  ",               /* PROXIMITY_NONE */
	"FAR   ",               /* PROXIMITY_FAR */
	"MEDIUM",               /* PROXIMITY_MEDIUM */
	"NEAR  "                /* PROXIMITY_NEAR */
};


/** \brief Light & proximity sensor demo application entry
 *
 * After initializing the Xplained platform and sensor boards, this application
 * attaches descriptors to the ambient light and proximity sensor devices on
 * an Xplained inertial sensor board.  The sensor data, which is formatted and
 * printed via printf() after being read, can be viewed with a serial terminal
 * application on a machine attached to the USB interface on the Xplained
 * board.
 */
int main(void)
{
	sensor_t light_dev;     /* Light sensor device descriptor */
	sensor_t prox_dev;      /* Proximity sensor device descriptor */

	/* Initialize the board (Xplained UC3 or XMEGA & Xplained Sensor boards)
	 * I/O pin mappings and any other configurable resources selected in
	 * the build configuration.
	 */
	sensor_platform_init();

	/* Attach descriptors to the defined sensor devices. */
	sensor_attach(&light_dev, SENSOR_TYPE_LIGHT, 0, 0);
	sensor_attach(&prox_dev, SENSOR_TYPE_PROXIMITY, 0, 0);

	if (light_dev.err || prox_dev.err) {
		puts("\rSensor initialization error.");

		while (true) {
			/* Error occurred, loop forever */
		}
	}

	/* Print sensor information */
	if (PRINT_BANNER) {
		static const char *const banner_format
			= "%s\r\nID = 0x%02x ver. 0x%02x\r\n"
				"Bandwidth = %d Hz  Range = +/- %d\r\n\n";

		uint32_t id;
		uint8_t version;
		int16_t freq, range;

		sensor_device_id(&light_dev, &id, &version);
		sensor_get_bandwidth(&light_dev, &freq);
		sensor_get_range(&light_dev, &range);

		printf(banner_format, light_dev.drv->caps.name,
				(unsigned)id, (unsigned)version, freq, range);

		sensor_device_id(&prox_dev, &id, &version);
		sensor_get_bandwidth(&prox_dev, &freq);
		sensor_get_range(&prox_dev, &range);

		printf(banner_format, prox_dev.drv->caps.name,
				(unsigned)id, (unsigned)version, freq, range);

		delay_ms(500);
	}

	/* Set sample interval for the light sensor */
	if (sensor_set_sample_rate(&light_dev, LIGHT_SAMPLE_RATE) != true) {
		printf("Error setting light sensor sample rate.\r\n");
	}

	/* Set sample interval for the proximity sensor */
	if (sensor_set_sample_rate(&prox_dev, PROX_SAMPLE_RATE) != true) {
		printf("Error setting proximity sensor sample rate.\r\n");
	}

	/* Select all proximity sensor channels */
	sensor_set_channel(&prox_dev, SENSOR_CHANNEL_ALL);

#if (SET_PROX_THRESHOLD == true)
	/* Manually set proximity threshold values for each channel */
	/* Otherwise, sensor will use values previously stored in nvram. */
	sensor_set_threshold(&prox_dev, SENSOR_THRESHOLD_NEAR_PROXIMITY,
			PROX_THRESHOLD);
#endif

#if (SET_PROX_CURRENT == true)
	/* Manually set LED current value for each channel */
	/* Otherwise, sensor will use default values. */
	sensor_set_current(&prox_dev, PROX_CURRENT_mA);
#endif

	/* Initialize sensor data descriptors for scaled vs. raw data. */
	static sensor_data_t light_data = {.scaled = SCALED_DATA};
	static sensor_data_t prox_data  = {.scaled = SCALED_DATA};

	while (true) {
		LED_Toggle(ACTIVITY_LED);

		/* Read sensor values */
		sensor_get_light(&light_dev, &light_data);
		sensor_get_proximity(&prox_dev, &prox_data);

		/* Print sensor values */
		if (SCALED_DATA) {
			printf("light = [%5d]\r\n",
					(int16_t)light_data.light.value);

			printf("prox  = 1:%s 2:%s 3:%s\r\n",
					prox_labels[prox_data.proximity.value[0]],
					prox_labels[prox_data.proximity.value[1]],
					prox_labels[prox_data.proximity.value[2]]);
		} else {
			printf("light = [%5d]\r\n",
					(int16_t)light_data.light.value);

			printf("prox = [%.5x, %.5x, %.5x]\r\n",
					(int16_t)prox_data.proximity.value[0],
					(int16_t)prox_data.proximity.value[1],
					(int16_t)prox_data.proximity.value[2]);
		}

		delay_ms(500);
	}

	return 0;
}
