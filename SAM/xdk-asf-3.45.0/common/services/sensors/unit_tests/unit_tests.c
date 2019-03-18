/**
 * \file
 *
 * \brief Sensor platform unit test
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \page License
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
 * \mainpage Sensor platform unit test
 *
 * \par Purpose
 *
 * Perform a range of unit tests on the Sensor Platform library to ensure
 * correct operation, using the INERTIAL ONE sensor board.
 *
 * \par Behavior: executing each unit test in turn
 *
 * -# Check that the Sensor Platform is initialized correctly with the Inertial
 *  One board.
 * -# Check that the gyroscope works correctly on the Inertial One board using
 *  the Sensor Platform library.
 * -# Check that the accelerometer works correctly on the Inertial One board
 *  using the Sensor Platform library.
 * -# Check that the compass works correctly on the Inertial One board using
 *  the Sensor Platform library.
 * -# Check that the gyroscope internal temperature sensor works correctly on
 *  the Inertial One board using the Sensor Platform library.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include "conf_test.h"

static const usart_serial_options_t usart_serial_options = {
	.baudrate     = CONF_TEST_BAUDRATE,
	.charlength   = CONF_TEST_CHARLENGTH,
	.paritytype   = CONF_TEST_PARITY,
	.stopbits     = CONF_TEST_STOPBITS,
};

/** Initializes the sensor platform - as this calls the board and sysclock
 *  init functions internally, it will also wait for any pending serial
 *  transfer(s) to complete before calling sensor_platform_init() and will
 *  re-initialize the USART afterwards to ensure no corrupt or lost data.
 */
static void configure_sensor_platform(void)
{
#if XMEGA
	usart_clear_tx_complete(CONF_TEST_USART);
	while (!usart_tx_is_complete(CONF_TEST_USART));
#elif UC3
	while (!(usart_tx_empty(CONF_TEST_USART)));
#endif

	sensor_platform_init();

	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);	
}

/** Unit test to check that the Sensor Platform is initialized correctly with
 *  the Intertial One board.
 *
 *  \param test  Pointer to the unit test case instance
 */
static void run_sensor_init_test(const struct test_case *test)
{
	sensor_t gyro;
	sensor_t accel;
	sensor_t compass;
	
	configure_sensor_platform();
	
	sensor_attach(&gyro, SENSOR_TYPE_GYROSCOPE, 0, 0);	
	test_assert_false(test, gyro.err, "Error attaching to gyroscope");
	
	sensor_attach(&accel, SENSOR_TYPE_ACCELEROMETER, 0, 0);
	test_assert_false(test, accel.err, "Error attaching to accelerometer");

	sensor_attach(&compass, SENSOR_TYPE_COMPASS, 0, 0);
	test_assert_false(test, compass.err, "Error attaching to compass");
}

/** Unit test to check that the gyroscope works correctly on the Inertial
 *  One board using the Sensor Platform library.
 *
 *  \param test  Pointer to the unit test case instance
 */
static void run_sensor_gyro_test(const struct test_case *test)
{
	sensor_t gyro;
	sensor_data_t gyro_data = { .scaled = true };
	
	configure_sensor_platform();
	
	sensor_attach(&gyro, SENSOR_TYPE_GYROSCOPE, 0, 0);	
	test_assert_false(test, gyro.err, "Error attaching to gyroscope");
	
	delay_ms(50);
	
	for (uint8_t i = 0; i < 10; i++) {	
		test_assert_true(test, sensor_get_rotation(&gyro, &gyro_data),
				"Gyroscope read failed");
		test_assert_false(test, gyro.err,
				"Gyroscope internal error");
				
		delay_ms(2);
	}	
}

/** Unit test to check that the accelerometer works correctly on the Inertial
 *  One board using the Sensor Platform library.
 *
 *  \param test  Pointer to the unit test case instance
 */
static void run_sensor_accel_test(const struct test_case *test)
{
	sensor_t accel;
	sensor_data_t accel_data = { .scaled = true };
	
	configure_sensor_platform();
	
	sensor_attach(&accel, SENSOR_TYPE_ACCELEROMETER, 0, 0);
	test_assert_false(test, accel.err, "Error attaching to accelerometer");
	
	delay_ms(50);
	
	for (uint8_t i = 0; i < 10; i++) {
		vector3_t accel_data_vect;
		
		test_assert_true(test, sensor_get_acceleration(&accel, &accel_data),
				"Accelerometer read failed");
		test_assert_false(test, accel.err,
				"Accelerometer internal error");
		
		accel_data_vect.x = accel_data.axis.x;
		accel_data_vect.y = accel_data.axis.y;
		accel_data_vect.z = accel_data.axis.z;
		
		scalar_t accel_mag = vector3_magnitude(&accel_data_vect);
		
		test_assert_true(test,
				(accel_mag > (1000 - 300)) && (accel_mag < (1000 + 300)),
				"Accelerometer returned value not close to 1000 milli-g: %i",
				(uint16_t)accel_mag);
				
		delay_ms(2);
	}	
}

/** Unit test to check that the compass works correctly on the Inertial
 *  One board using the Sensor Platform library.
 *
 *  \param test  Pointer to the unit test case instance
 */
static void run_sensor_compass_test(const struct test_case *test)
{
	sensor_t compass;
	sensor_data_t compass_data = { .scaled = true };
	
	configure_sensor_platform();
	
	sensor_attach(&compass, SENSOR_TYPE_COMPASS, 0, 0);
	test_assert_false(test, compass.err, "Error attaching to magnetometer");
	
	delay_ms(50);
	
	for (uint8_t i = 0; i < 10; i++) {
		vector3_t compass_data_vect;
		
		test_assert_true(test, sensor_get_heading(&compass, &compass_data),
				"Compass read failed");
		test_assert_false(test, compass.err,
				"Compass internal error");
		
		compass_data_vect.x = compass_data.heading.direction;
		compass_data_vect.y = compass_data.heading.inclination;
		compass_data_vect.z = compass_data.heading.strength;
		
		scalar_t compass_mag = vector3_magnitude(&compass_data_vect);
		
		test_assert_false(test, (compass_mag == 0),
				"Compass returned zero data");		
		
		delay_ms(2);
	}	
}

/** Unit test to check that the gyroscope internal temperature sensor works 
 *  correctly on the Inertial One board using the Sensor Platform library.
 *
 *  \param test  Pointer to the unit test case instance
 */
static void run_sensor_temp_test(const struct test_case *test)
{
	sensor_t gyro;
	sensor_data_t temp_data = { .scaled = true };
	
	configure_sensor_platform();
	
	sensor_attach(&gyro, SENSOR_TYPE_GYROSCOPE, 0, 0);
	test_assert_false(test, gyro.err, "Error attaching to gyroscope");
	
	delay_ms(50);
	
	for (uint8_t i = 0; i < 10; i++) {	
		test_assert_true(test, sensor_get_temperature(&gyro, &temp_data),
				"Gyroscope temperature read failed");
		test_assert_false(test, gyro.err,
				"Gyroscope internal error");
		
		test_assert_false(test, ((int16_t)temp_data.temperature.value == 0),
				"Gyroscope returned zero temperature data");

		test_assert_false(test, ((int16_t)temp_data.temperature.value > 40),
				"Gyroscope returned too high temperature data: %d",
				(int16_t)temp_data.temperature.value);

		delay_ms(2);
	}
}

int main(void)
{
	// Initialize the board and all the peripheral required
	sysclk_init();
	board_init();
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

#if XMEGA
	pmic_init();
	sleepmgr_init();
#endif

	DEFINE_TEST_CASE(sensor_init_test, NULL, run_sensor_init_test,
			NULL, "Test sensor initialization");

	DEFINE_TEST_CASE(sensor_gyro_test, NULL, run_sensor_gyro_test,
			NULL, "Test gyroscope read");

	DEFINE_TEST_CASE(sensor_accel_test, NULL, run_sensor_accel_test,
			NULL, "Test accelerometer read");
	
	DEFINE_TEST_CASE(sensor_compass_test, NULL, run_sensor_compass_test,
			NULL, "Test compass read");

	DEFINE_TEST_CASE(sensor_temp_test, NULL, run_sensor_temp_test,
			NULL, "Test temperature read");
				
	DEFINE_TEST_ARRAY(sensor_tests) = {
		&sensor_init_test,
		&sensor_gyro_test,
		&sensor_accel_test,
		&sensor_compass_test,
		&sensor_temp_test
	};

	DEFINE_TEST_SUITE(sensor_suite,
			sensor_tests, "Common sensor plarform test suite");

	test_suite_run(&sensor_suite);

	while (1) {
		/* Intentionally left blank */
	}
}
