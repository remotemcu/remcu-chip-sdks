/**
 * \file
 *
 * \brief Common Sensor Service Pressure Sensor Example
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
 * This application obtains sensor data from the MEMS pressure sensor device
 * installed on an Atmel development board.
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

/* Application configuration constants */
#define PRINT_BANNER    (true)

/* Hardware environment constants */
#define ACTIVITY_LED    (LED1)


/** \brief Pressure sensor demonstration application entry
 *
 * After initializing the development platform and sensors, this application
 * attaches a descriptor to the sensor on an Xplained pressure sensor board.
 * The sensor pressure and temperature data, which is formatted and printed
 * via printf() after being read, can be viewed with a terminal application on
 * a machine attached to the serial interface on the development board.
 */
int main(void)
{
	sensor_t barometer;             /* Pressure sensor device descriptor */
	sensor_data_t press_data;       /* Pressure data */
	sensor_data_t temp_data;        /* Temperature data */

	/* Initialize the board (Xplained UC3 or XMEGA & Xplained Sensor boards)
	 * I/O pin mappings and any other configurable resources selected in
	 * the build configuration.
	 */
	sensor_platform_init();

	/* Attach a descriptor to the existing sensor device. */
	sensor_attach(&barometer, SENSOR_TYPE_BAROMETER, 0, 0);

	if (barometer.err) {
		puts("\rSensor initialization error.");

		while (true) {
			/* Error occurred, loop forever */
		}
	}

	sensor_set_state(&barometer, SENSOR_STATE_HIGHEST_POWER);

	/* Initialize sensor data structure flags for scaled vs. raw data */
	press_data.scaled = true;
	temp_data.scaled = true;

	/* Print sensor config info */
	if (PRINT_BANNER) {
		uint32_t id;
		uint8_t ver;

		static const char *const banner_format
			= "%s\r\nID = 0x%02x ver. 0x%02x\r\n  %d-bit Resolution\r\n";

		sensor_device_id(&barometer, &id, &ver);

		printf(banner_format, barometer.drv->caps.name, (unsigned)id,
				(unsigned)ver, barometer.hal->resolution);
	}

	while (true) {
		LED_Toggle(ACTIVITY_LED);

		sensor_get_pressure(&barometer, &press_data);
		sensor_get_temperature(&barometer, &temp_data);

		printf("P = %.2f hPa,  T = %.1f C\r\n",
				(press_data.pressure.value / 100.0),
				(temp_data.temperature.value / 10.0));

		delay_ms(500);
	}

	return 0;
}
