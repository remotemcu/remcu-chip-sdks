/**
 * \file
 *
 * \brief Common Sensor Service Data Visualizer
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
 * This application obtains sensor data from the MEMS accelerometer, gyroscope,
 * and electronic compass devices installed on an Atmel development board.
 * The data is then formatted and transferred to a remote host for display
 * using the Atmel Data Visualizer tool.
 *
 * The Atmel Data Visualizer (ADV) tool is a standalone Windows application
 * that provides a graphical display of data sent from a remote target.  It
 * is available as a separate download.  For more information on downloading
 * and installing the ADV tool, visit
 * <a href="http://www.microchip.com/mplab/avr-support/data-visualizer">Atmel
 * Data Visualizer</a>
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com/design-centers/8-bit">Atmel AVR</a>.\n
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <led.h>
#include "data_visualizer.h"

/* Sensor interval settings - how often each sensor is measured */
#define ACCEL_INTERVAL      1       /* Loops per accel meas/xmit */
#define GYRO_INTERVAL       3       /* Loops per gyro meas/xmit */
#define COMPASS_INTERVAL    5       /* Loops per compass meas/xmit */
#define TEMP_INTERVAL       10      /* Loops per temperature meas/xmit */

#define ACCEL_STREAM_NUM    1       /* Accelerometer data stream number */
#define GYRO_STREAM_NUM     2       /* Gyroscope data stream number */
#define COMPASS_STREAM_NUM  3       /* Compass/magnetometer data stream number */
#define TEMP_STREAM_NUM     4       /* Temperature data stream number */

#define NUM_ACCEL_FIELDS    3       /* Accelerometer data fields in data packet */
#define NUM_GYRO_FIELDS     3       /* Gyroscope data fields in data packet */
#define NUM_COMPASS_FIELDS  3       /* Compass data fields in data packet */
#define NUM_TEMP_FIELDS     1       /* Temperature data fields in data packet */

#define TIMESTAMP_RES       1000000 /* Timestamp resolution (1 per usec) */

/* Switch and LED definitions */

#if (BOARD == UC3_L0_XPLAINED)
#  define SWITCH_PRESSED  gpio_pin_is_low(GPIO_PUSH_BUTTON_0)
#  define NUM_BLINK_LEDS  (LED_COUNT - 1) /* Don't blink LED0 (shared gpio) */
#  define ALL_LEDS        (LED1 | LED2 | LED3 | LED4)
#  define PROMPT_LED      LED4      /* Blink while waiting for user input */
static const uint32_t led_array[LED_COUNT - 1] = {LED1, LED2, LED3, LED4};
#elif (BOARD == UC3_A3_XPLAINED)
#  define SWITCH_PRESSED  gpio_pin_is_low(GPIO_PUSH_BUTTON_0)
#  define NUM_BLINK_LEDS  (LED_COUNT)     /* Blink all LEDs */
#  define ALL_LEDS        (LED0 | LED1 | LED2 | LED3)
#  define PROMPT_LED      LED0      /* Blink while waiting for user input */
static const uint32_t led_array[LED_COUNT] = {LED0, LED1, LED2, LED3};
#elif (BOARD == XMEGA_A1_XPLAINED) || (BOARD == XMEGA_B1_XPLAINED)
#  define SWITCH_PRESSED  gpio_pin_is_low(GPIO_PUSH_BUTTON_0)
#  define NUM_BLINK_LEDS  (4)       /* Blink 4 LEDs */
#  define ALL_LEDS        (LED0 | LED1 | LED2 | LED3)
#  define PROMPT_LED      LED0      /* Blink while waiting for user input */
static const uint32_t led_array[LED_COUNT] = {LED0, LED1, LED2, LED3};
#elif (BOARD == XMEGA_A3BU_XPLAINED)
#  define SWITCH_PRESSED  gpio_pin_is_low(GPIO_PUSH_BUTTON_1)
#  define NUM_BLINK_LEDS  (LED_COUNT - 2) /* Blink 2 LEDs */
#  define ALL_LEDS        (LED0 | LED1)
#  define PROMPT_LED      LED0      /* Blink while waiting for user input */
static const uint32_t led_array[LED_COUNT - 2] = {LED0, LED1};
#endif


/** \brief  Initialize sensor data output streams for Atmel Data Visualizer
 *
 * This routine initializes the data streams used in this application for the
 * Atmel Data Visualizer (ADV) tool.  First, a start-of-configuration packet
 * is constructed and sent.  Next, each data stream is described with a
 * stream descriptor packet and either one or three field descriptor packets
 * (depending on how many data fields are used to report a single set of
 * data from that device).  After all streams and data fields have been
 * described, an end-of-configuration packet is sent.
 */
void visual_stream_init(void)
{
	adv_config_start_t start;       /* Config start packet */
	adv_config_stream_t stream;     /* Stream config packet */
	adv_config_field_t field;       /* Data field info packet */
	adv_config_end_t end;           /* Config end packet */

	/* Configuration start packet */
	start.header1     = ADV_PKT_HEADER_1;
	start.header2     = ADV_PKT_HEADER_2;
	start.length      = cpu_to_le16(sizeof(adv_config_start_t));
	start.type        = ADV_PKT_CONFIG_START;
	start.num_streams = 4;
	start.crc         = 0x00; /* Not used */
	start.mark        = ADV_PKT_END;

	adv_write_buf((uint8_t *)&start, sizeof(start));

	/* Common field values for all stream config packets */
	stream.header1  = ADV_PKT_HEADER_1;
	stream.header2  = ADV_PKT_HEADER_2;
	stream.type     = ADV_PKT_CONFIG_STREAM;
	stream.tick_res = cpu_to_le32(TIMESTAMP_RES);
	stream.length   = cpu_to_le16(sizeof(adv_config_stream_t));
	stream.mark     = ADV_PKT_END;
	stream.crc      = 0x00; /* Not used */

	/* Common field values for all data field descriptor config packets */
	field.header1      = ADV_PKT_HEADER_1;
	field.header2      = ADV_PKT_HEADER_2;
	field.type         = ADV_PKT_CONFIG_FIELD;
	field.length       = cpu_to_le16(sizeof(adv_config_field_t));
	field.field_length = 4; /* All fields are signed 4-byte integers */
	field.format       = FIELD_FORMAT_SIGNED;
	field.mark         = ADV_PKT_END;
	field.crc          = 0x00; /* Not used */

	/* Accelerometer stream */
	stream.stream_num = ACCEL_STREAM_NUM;
	stream.num_fields = NUM_ACCEL_FIELDS;
	strcpy((void *)&(stream.stream_name), "Acceleration");

	adv_write_buf((uint8_t *)&stream, sizeof(stream));

	/* X axis data field */
	field.stream_num = ACCEL_STREAM_NUM;
	field.field_num  = 1;
	field.min        = cpu_to_le32(-2000);
	field.max        = cpu_to_le32(2000);
	strcpy((void *)&(field.units), "Milli-g");
	strcpy((void *)&(field.name), "Accel X");

	adv_write_buf((uint8_t *)&field, sizeof(field));

	/* Y axis data field (re-use previous values except name & field number) */
	field.field_num = 2;
	strcpy((void *)&(field.name), "Accel Y");

	adv_write_buf((uint8_t *)&field, sizeof(field));

	/* Z axis data field (re-use previous values except name & field number) */
	field.field_num = 3;
	strcpy((void *)&(field.name), "Accel Z");

	adv_write_buf((uint8_t *)&field, sizeof(field));

	/* Gyroscope stream */
	stream.stream_num = GYRO_STREAM_NUM;
	stream.num_fields = NUM_GYRO_FIELDS;
	strcpy((void *)&(stream.stream_name), "Rotation");

	adv_write_buf((uint8_t *)&stream, sizeof(stream));

	/* X axis data field */
	field.stream_num = GYRO_STREAM_NUM;
	field.field_num  = 1;
	field.min        = cpu_to_le32(-2000);
	field.max        = cpu_to_le32(2000);
	strcpy((void *)&(field.units), "Deg per sec");
	strcpy((void *)&(field.name), "Rot X");

	adv_write_buf((uint8_t *)&field, sizeof(field));

	/* Y axis data field (re-use previous values except name & field number) */
	field.field_num = 2;
	strcpy((void *)&(field.name), "Rot Y");

	adv_write_buf((uint8_t *)&field, sizeof(field));

	/* Z axis data field (re-use previous values except name & field number) */
	field.field_num = 3;
	strcpy((void *)&(field.name), "Rot Z");

	adv_write_buf((uint8_t *)&field, sizeof(field));

	/* Compass/Magnetometer stream */
	stream.stream_num = COMPASS_STREAM_NUM;
	stream.num_fields = NUM_COMPASS_FIELDS;
	strcpy((void *)&(stream.stream_name), "Magnetic Heading");

	adv_write_buf((uint8_t *)&stream, sizeof(stream));

	/* Heading data field */
	field.stream_num = COMPASS_STREAM_NUM;
	field.field_num  = 1;
	field.min        = cpu_to_le32(0);
	field.max        = cpu_to_le32(360);
	strcpy((void *)&(field.units), "Degrees");
	strcpy((void *)&(field.name), "Direction");

	adv_write_buf((uint8_t *)&field, sizeof(field));

	/* Inclination field */
	field.stream_num = COMPASS_STREAM_NUM;
	field.field_num  = 2;
	field.min        = cpu_to_le32(-90);
	field.max        = cpu_to_le32(90);
	strcpy((void *)&(field.units), "Degrees");
	strcpy((void *)&(field.name), "Incl");

	adv_write_buf((uint8_t *)&field, sizeof(field));

	/* Field strength field */
	field.stream_num = COMPASS_STREAM_NUM;
	field.field_num  = 3;
	field.min        = cpu_to_le32(0);
	field.max        = cpu_to_le32(200);
	strcpy((void *)&(field.units), "uTesla");
	strcpy((void *)&(field.name), "Field");

	adv_write_buf((uint8_t *)&field, sizeof(field));

	/* Temperature stream */
	stream.stream_num = TEMP_STREAM_NUM;
	stream.num_fields = NUM_TEMP_FIELDS;
	strcpy((void *)&(stream.stream_name), "Temperature");

	adv_write_buf((uint8_t *)&stream, sizeof(stream));

	/* Temperature field */
	field.stream_num = TEMP_STREAM_NUM;
	field.field_num  = 1;
	field.min        = cpu_to_le32(-10);
	field.max        = cpu_to_le32(50);
	strcpy((void *)&(field.units), "Deg C");
	strcpy((void *)&(field.name), "Temp");

	adv_write_buf((uint8_t *)&field, sizeof(field));

	/* Configuration end packet */
	end.header1 = ADV_PKT_HEADER_1;
	end.header2 = ADV_PKT_HEADER_2;
	end.length  = cpu_to_le16(sizeof(adv_config_end_t));
	end.type    = ADV_PKT_CONFIG_END;
	end.num_streams = 4;
	end.crc     = 0x00;             /* not used */
	end.mark    = ADV_PKT_END;

	adv_write_buf((uint8_t *)&end, sizeof(end));
}

/** \brief Inertial sensor data visualizer demo application entry
 *
 * This application uses a serial connection to transmit sensor data.  The
 * data is formatted for use by the Atmel Data Visualizer application
 * running on a remote host.
 *
 * Upon entry, the hardware (including processor and sensor board) are
 * initialized, and the sensor interfaces are established.  The application
 * then transmits a series of special data stream configuration packets,
 * which tell the remote application the number, type, and labels for
 * data streams that will subsequently be used.
 *
 * After this initialization, the application enters a continuous loop
 * in which it periodically samples the sensors that are defined and
 * sends the obtained data values to the remote host in stream data packets.
 * Each type of sensor measurement uses an interval counter to determine
 * how often the measurement should be performed and transmitted.
 */
int main(void)
{
	int led_index = 0;
	int loop_count = 0;

	sensor_t accel_dev;             /* Accelerometer device */
	sensor_t compass_dev;           /* Compass/magnetometer device */
	sensor_t gyro_dev;              /* Gyroscope device */

	sensor_data_t accel_data;       /* Accelerometer data */
	sensor_data_t compass_data;     /* Compass data */
	sensor_data_t gyro_data;        /* Gyroscope data */
	sensor_data_t temp_data;        /* Temperature data */

	/* Initialize the board (Xplained UC3 or XMEGA & Xplained Sensor boards)
	 * I/O pin mappings and any other configurable resources selected in
	 * the build configuration.
	 */
	sensor_platform_init();

	LED_On(ALL_LEDS);

	/* Attach descriptors to the defined sensor devices. */
	sensor_attach(&accel_dev, SENSOR_TYPE_ACCELEROMETER, 0, 0);
	sensor_attach(&gyro_dev, SENSOR_TYPE_GYROSCOPE, 0, 0);
	sensor_attach(&compass_dev, SENSOR_TYPE_COMPASS, 0, 0);

	if (accel_dev.err || gyro_dev.err || compass_dev.err) {
		while (true) {
			/* Error occurred, loop forever */
		}
	}

	/* Set sensor data output formats */
	accel_data.scaled   = true;
	gyro_data.scaled    = true;
	compass_data.scaled = true;
	temp_data.scaled    = true;

	/* Wait for user to push button before continuing */
	LED_Off(ALL_LEDS);
	
	do {
		/* Just blink LED until button is pushed */
		LED_Toggle(PROMPT_LED);

		delay_ms(500);
	} while (!SWITCH_PRESSED);

	LED_Off(PROMPT_LED);

	/* Enable output streams for Atmel Data Visualizer (ADV) */
	visual_stream_init();

	while (true) {
		/* Change LED display */
		LED_Toggle(led_array [led_index++]);
		if (led_index >= NUM_BLINK_LEDS) {
			led_index = 0;
		}

		/* Accelerometer data */
		if ((loop_count % ACCEL_INTERVAL) == 0) {
			sensor_get_acceleration(&accel_dev, &accel_data);

			adv_data_send_3(ACCEL_STREAM_NUM, accel_data.timestamp,
					accel_data.axis.x, accel_data.axis.y,
					accel_data.axis.z);
		}

		/* Gyroscope data */
		if ((loop_count % GYRO_INTERVAL) == 0) {
			sensor_get_rotation(&gyro_dev, &gyro_data);

			adv_data_send_3(GYRO_STREAM_NUM, gyro_data.timestamp,
					gyro_data.axis.x, gyro_data.axis.y,
					gyro_data.axis.z);
		}

		/* Compass/magnetometer data */
		if ((loop_count % COMPASS_INTERVAL) == 0) {
			sensor_get_heading(&compass_dev, &compass_data);

			adv_data_send_3(COMPASS_STREAM_NUM,
					compass_data.timestamp,
					compass_data.heading.direction,
					compass_data.heading.inclination,
					compass_data.heading.strength);
		}

		/* Temperature data */
		if ((loop_count % TEMP_INTERVAL) == 0) {
			sensor_get_temperature(&gyro_dev, &temp_data);

			adv_data_send_1(TEMP_STREAM_NUM, temp_data.timestamp,
					temp_data.temperature.value);
		}

		/* Re-send stream initialization if switch pressed */
		if (SWITCH_PRESSED) {
			LED_Off(ALL_LEDS);
			LED_On(PROMPT_LED);
			
			/* Re-send init info */
			visual_stream_init();

			while (SWITCH_PRESSED) {
				/* wait until button is released */
			}

			LED_Off(PROMPT_LED);
			led_index = 0;
		}

		loop_count++;
	}

	return 0;
}
