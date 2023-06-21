/**
 * \file
 *
 * \brief AKM AK8975 3-axis magnetometer.
 *
 * This file contains functions for initializing and reading data
 * from a AKM AK8975 3-axis magnetometer.
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
 
#include <string.h>
#include <math.h>
#include "ak8975.h"

static bool ak8975_calibrate(sensor_t *, sensor_calibration_t, int, void *);
static bool ak8975_ioctl(sensor_t *, sensor_command_t, void *);
static bool ak8975_read(sensor_t *, sensor_read_t, sensor_data_t *);
static bool ak8975_selftest(sensor_t *, int *, void *);

/** Delay loop count during self-test */
#define SELF_TEST_DELAY     (0x80000)

/**
 * @brief Sensor Calibration Data
 *
 * This variable stores copies of axis calibration offsets stored in NVRAM.
 *
 * @internal
 * The current implementation will either use software floating-point routines
 * from the toolchain or fixed-point math routines in the ASF.  All fractional
 * sensor data should use types defined in precision.h where the type
 * \c scalar_t is an alias for a C/C++ floating-point type or an integer type
 * used by fixed-point arithmetic functions defined in the API.
 */
static vector3_t calibrated_offsets;

/**
 * @brief AKM AK8975 magnetometer driver initialization.
 *
 * This is the main initialization function for the AK8975 device.
 *
 * @param sensor    Address of a sensor device descriptor.
 * @param resvd     Reserved value.
 * @return bool     true if the call succeeds, else false is returned.
 */
bool ak8975_init(sensor_t *sensor, int resvd)
{
	sensor_hal_t *const hal = sensor->hal;

	/* Set the driver function table and capabilities pointer. */
	static const sensor_device_t ak8975_device = {
		.func.read      = ak8975_read,
		.func.ioctl     = ak8975_ioctl,
		.func.selftest  = ak8975_selftest,
		.func.calibrate = ak8975_calibrate,
		.caps.feature   = SENSOR_CAPS_3_AXIS | SENSOR_CAPS_SELFTEST,
		.caps.vendor    = SENSOR_VENDOR_AKM,
		.caps.units     = SENSOR_UNITS_tesla,
		.caps.scale     = SENSOR_SCALE_micro,
		.caps.name = "AK8975 Digital, triaxial compass/magnetometer"
	};

	sensor->drv = &ak8975_device;

	/* Set the driver default, range, bandwidth, resolution, &c. */
	hal->resolution = AK8975_DATA_RESOLUTION;

	/* Initialize calibration data from NVRAM storage. */
	nvram_read(0 /* + NVRAM_BASE_ADDR */, &calibrated_offsets,
			sizeof(calibrated_offsets));

	/* Clear all calibration values if any are invalid */
	#if defined(MATH_FIXED_POINT)
	if ((calibrated_offsets.x == -1) || (calibrated_offsets.y == -1) ||
			(calibrated_offsets.z == -1)) {
	#else
	if (isnan(calibrated_offsets.x) || isnan(calibrated_offsets.y) ||
			isnan(calibrated_offsets.z)) {
	#endif
		memset(&calibrated_offsets, 0x00, sizeof(calibrated_offsets));
	}
	
	return (AK8975_WIA_VALUE == sensor_bus_get(hal, AK8975_REG_WIA));
}

/**
 * @brief Read magnetometer device ID
 *
 * This function reads the magnetometer hardware identification registers
 * and returns these values to the addresses specified in the function
 * parameters.
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param data      Address of sensor_data_t structure to return values.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool ak8975_device_id(sensor_hal_t *hal, sensor_data_t *data)
{
	data->device.id = (uint32_t)sensor_bus_get(hal, AK8975_REG_WIA);
	data->device.version = 0;

	return true;
}

/**
 * @ brief Test for magnetic sensor overflow
 *
 * AK8975/B has the limitation for measurement range that the sum of the
 * absolute values of each axis should be smaller than 2400 microtesla:
 *
 *          |x| + |y| + |z| < 2400 uT
 *
 * When the magnetic field exceeds this limitation, data stored at measurement
 * data are not correct.  This is called "Magnetic Sensor Overflow".
 *
 * When magnetic sensor overflow occurs, HOFL but turns to "1".  When the next
 * measurement starts, it returns to "0".
 *
 * @return  bool    true if Magnetic Sensor Overflow criteria are satisfied.
 */
static inline bool ak8975_check_overflow(const vector3_t *data)
{
	static scalar_t const MEASURE_MAX = (1 << (AK8975_DATA_RESOLUTION - 1)) /
			MICRO_TESLA_PER_COUNT;

	/* \todo Use register instead of calculating overflow?
	 * return (AK8975_HOFL & sensor_bus_get(hal, AK8975_REG_ST2));
	 */
	return ((abs(data->x) + abs(data->y) + abs(data->z)) >= MEASURE_MAX);
}

/**
 * @brief Read magnetometer vector data.
 *
 * This function obtains magnetometer data for all three axes of the AKM
 * device.  The data is read from six device registers using a multi-byte
 * bus transfer.  The 13-bit raw results are then assembled from the two
 * register values for each axis, including extending the sign bit, to
 * form a signed 16-bit value.
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param data      The address of a vector storing sensor axis data.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool ak8975_get_data(sensor_hal_t *hal, uint8_t mode, vector3_t *data)
{
	/* Put sensor in single measurement or self-test mode */
	sensor_bus_put(hal, AK8975_REG_CNTL1, mode);

	/* Wait for the data ready signal. */
	do {
		/* In single measurement or self-test mode, when measurement
		 * data is stored and ready to be read, DRDY bit in ST1 register
		 * turns to "1". This is called "Data Ready". DRDY pin is in the
		 * same state as DRDY bit.
		 *
		 * Instead of polling DRDY, as is done below, this signal out of
		 * the sensor and into the microcontroller can be used to
		 * trigger
		 * an asynchronous interrupt.
		 */
	} while (gpio_pin_is_low(hal->mcu_sigint /* DRDY input */));

	/* Get measurement data (consecutive little endian byte pairs: x, y, z). */
	struct {
		uint8_t lsb;
		uint8_t msb;
	}
	input[3];

	size_t const count = sensor_bus_read(hal, AK8975_REG_HXL,
			input, sizeof(input));

	if (count != sizeof(input)) {
		return false;
	}

	/* Convert to a real data (non-integer) type for calculations. */
	data->x = hal->orientation.x.sign *
			((int16_t)((input[hal->orientation.x.axis].msb << 8)
			+ input[hal->orientation.x.axis].lsb));

	data->y = hal->orientation.y.sign *
			((int16_t)((input[hal->orientation.y.axis].msb << 8)
			+ input[hal->orientation.y.axis].lsb));

	data->z = hal->orientation.z.sign *
			((int16_t)((input[hal->orientation.z.axis].msb << 8)
			+ input[hal->orientation.z.axis].lsb));

	return true;
}

/**
 * @brief Apply stored offset values to sensor reading
 *
 * This function applies stored calibration offsets to the "input" vector of
 * magnetometer values (the magnetic field vector) and returns the modified
 * values.
 *
 * @param   input       Contains the measured magnetic field values.  The
 *                      offset-adjusted values will replace the contents.
 * @retval  true        successfully adjusted sensor readings
 * @retval  false       Failed to adjust sensor readings
 */
static inline void ak8975_apply_offset(vector3_t *input)
{
	/* Apply calibrated offsets to the uncalibrated input field vector. */
	input->x -= calibrated_offsets.x;
	input->y -= calibrated_offsets.y;
	input->z -= calibrated_offsets.z;
}

/**
 * @brief Read magnetometer vector (3-axis) data
 *
 * This function obtains magnetometer data for all three axes of the AKM
 * device.  The data is read from six device registers using a multi-byte
 * bus transfer.  The 10-bit raw results are then assembled from the two
 * register values for each axis, including extending the sign bit, to
 * form a signed 32-bit value.
 *
 * Along with the actual sensor data, the LSB byte contains a "new" flag
 * indicating if the data for this axis has been updated since the last
 * time the axis data was read.  Reading either LSB or MSB data will
 * clear this flag.
 *
 * @param   hal     Address of an initialized sensor hardware descriptor.
 * @param   data    The address of a vector storing sensor axis data.
 * @return  bool    true if the call succeeds, else false is returned.
 */
static bool ak8975_get_field(sensor_hal_t *hal, sensor_data_t *data)
{
	vector3_t mag_data;
	bool result = false;

	/* Get magnetic field measurements & test for data overflow. */
	if (ak8975_get_data(hal, AK8975_SINGLE_MODE, &mag_data) &&
			(!ak8975_check_overflow(&mag_data))) {
		if (data->scaled) {
			/* Apply stored measurement offsets to data. */
			ak8975_apply_offset(&mag_data);

			/* Scale output values to SI units (uTesla). */
			vector3_scale((scalar_t)MICRO_TESLA_PER_COUNT,
					&mag_data);
		}

		data->axis.x = mag_data.x;
		data->axis.y = mag_data.y;
		data->axis.z = mag_data.z;

		result = true;
	}

	return result;
}

/**
 * @brief Read magnetometer heading/direction data.
 *
 * This function obtains magnetometer data for all three axes of the AKM
 * device.  The data is read from six device registers using a multi-byte
 * bus transfer.  The 10-bit raw results are then assembled from the two
 * register values for each axis, including extending the sign bit, to
 * form a signed 32-bit value.
 *
 * Along with the actual sensor data, the LSB byte contains a "new" flag
 * indicating if the data for this axis has been updated since the last
 * time the axis data was read.  Reading either LSB or MSB data will
 * clear this flag.
 *
 * @param   hal     Address of an initialized sensor hardware descriptor.
 * @param   data    The address of a vector storing sensor axis data.
 * @return  bool    true if the call succeeds, else false is returned.
 */
static bool ak8975_get_heading(sensor_hal_t *hal, sensor_data_t *data)
{
	bool result = false;

	/* Get magnetic field measurements & test for data overflow. */
	vector3_t mag_data;

	if (ak8975_get_data(hal, AK8975_SINGLE_MODE, &mag_data) &&
			(!ak8975_check_overflow(&mag_data))) {
		/* Apply stored measurement offsets to data. */
		ak8975_apply_offset(&mag_data);

		/* Calculate direction, inclination, and field strength. */
		scalar_t theta;    /* direction angle (degrees) */
		scalar_t delta;    /* inclination angle (degrees) */
		scalar_t strength; /* magnetic field intensity */

		result = field_direction(&mag_data, &theta, &delta, &strength);

		if (result) {
			strength *= (scalar_t)MICRO_TESLA_PER_COUNT;

			data->heading.direction   = (int32_t)theta;
			data->heading.inclination = (int32_t)delta;
			data->heading.strength    = (int32_t)strength;
		}
	}

	return result;
}

/**
 * @brief Read sensor data
 *
 * This routine calls the appropriate internal data function to obtain
 * the specified type of data from the sensor device.
 *
 * @param sensor    Address of an initialized sensor device descriptor.
 * @param type      Type of sensor data to read.
 * @param data      The address where data values are returned.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool ak8975_read(sensor_t *sensor, sensor_read_t type,
		sensor_data_t *data)
{
	sensor_hal_t *const hal = sensor->hal;

	switch (type) {
	case SENSOR_READ_FIELD:
		return ak8975_get_field(hal, data);

	case SENSOR_READ_HEADING:
		return ak8975_get_heading(hal, data);

	case SENSOR_READ_ID:
		return ak8975_device_id(hal, data);

	default:
		sensor->err = SENSOR_ERR_FUNCTION;
		return false;
	}
}

/**
 * @brief AKM AK8975 device state set routine
 *
 * This function places the AK8975 device in the specified state.
 *
 * @param sensor    Address of a sensor device descriptor.
 * @param state     State device will be placed into.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool ak8975_set_state(sensor_hal_t *hal, sensor_state_t state)
{
	if ((state == SENSOR_STATE_POWER_DOWN) ||
			(state == SENSOR_STATE_SLEEP)) {
		sensor_bus_put(hal, AK8975_REG_CNTL1, AK8975_POWER_DOWN_MODE);
		return true;
	}

	return false;
}

/**
 * @brief AK8975 ioctl control entry point
 *
 * @param hal           Address of an initialized sensor hardware descriptor.
 * @param cmd           Command to execute
 * @param arg           Argument for command (varies)
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool ak8975_ioctl(sensor_t *sensor, sensor_command_t cmd,
		void *arg)
{
	sensor_hal_t *const hal = sensor->hal;
	bool status = false;

	switch (cmd) {
	case SENSOR_SET_STATE:
		status = ak8975_set_state(hal, *((sensor_state_t *)arg));
		break;

	default:
		sensor->err = SENSOR_ERR_UNSUPPORTED;
		break;
	}

	return status;
}

/**
 * @brief Calibrate magnetometer
 *
 * This function measures the magnetometer output if 3 different device
 * orientations, calculates average offset values, and stores these offsets
 * in non-volatile memory.  The offsets will later be used during normal
 * measurements, to compensate for fixed magnetic effects.
 *
 * This routine must be called 3 times total, with the "step" parameter
 * indicating what stage of the calibration is being performed.  This
 * multi-step mechanism allows the application to prompt for physical
 * placement of the sensor device before this routine is called.
 *
 * @param sensor     Address of an initialized sensor device descriptor.
 * @param calib_type The address of a vector storing sensor axis data.
 * @param step       The calibration stage number [1,3].
 * @param info       Unimplemented (ignored) parameter.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool ak8975_calibrate(sensor_t *sensor,
		sensor_calibration_t calib_type, int step, void *info)
{
	sensor_hal_t *const hal = sensor->hal;
	static vector3_t step_data [3];

	/* Validate the supported calibration types and step number. */
	if ((calib_type != MANUAL_CALIBRATE) || ((step < 1) || (step > 3))) {
		return false;
	}

	/* Read sensor data and test for data overflow. */
	vector3_t *const ptr_step_data = &step_data[ step - 1 ];

	if ((!ak8975_get_data(hal, AK8975_SINGLE_MODE, ptr_step_data)) ||
			ak8975_check_overflow(ptr_step_data)) {
		return false;
	}

	switch (step) {
	/* There's nothing to do on the first two passes. */
	case 1:
	case 2:
		break;

	/* Calculate & update the calibrated offsets on the final pass. */
	case 3:
		calibrated_offsets.x = (step_data[0].x + step_data[1].x) / 2;
		calibrated_offsets.y = (step_data[0].y + step_data[1].y) / 2;
		calibrated_offsets.z = (step_data[1].z + step_data[2].z) / 2;

		/* Write the calibration data then read it back and confirm it
		 * was written correctly
		 */
		nvram_write(0, &calibrated_offsets, sizeof(calibrated_offsets));

		vector3_t read_back;
		nvram_read(0, &read_back, sizeof(vector3_t));

		if (memcmp(&calibrated_offsets, &read_back,
				sizeof(vector3_t))) {
			sensor->err = SENSOR_ERR_IO;
			return false;
		}

		break;

	/* Any other step number is invalid */
	default:
		sensor->err = SENSOR_ERR_PARAMS;
		return false;
	}

	return true;
}

/**
 * @brief Perform self-test function
 *
 * This function sets up and executes the built-in self test function
 * of the AK8975 sensor device.
 *
 * @param test_code Address of a numeric code of which test to perform
 *                  This location will contain the specific test result code
 *                  when the function returns.
 *
 * @return bool     true if the call succeeds, else false is returned.
 */
bool ak8975_selftest(sensor_t *sensor, int *test_code, void *arg)
{
	vector3_t data;
	sensor_hal_t *const hal = sensor->hal;
	bool ret_val = true;

	/* Initialize the test result code. */
	*test_code = SENSOR_TEST_ERR_NONE;

	/* Set the test mode. */
	sensor_bus_put(hal, AK8975_REG_CNTL1, AK8975_POWER_DOWN_MODE);

	/* start in power-down */
	sensor_bus_put(hal, AK8975_REG_ASTC, AK8975_ASTC_SELF);

	/* Apply the test bias. */

	for (int32_t i = 0; i < SELF_TEST_DELAY; ++i) {
		/* Do nothing while the applied bias settles. */
	}

	/* Perform test measurement & check results. */
	if (ak8975_get_data(hal, AK8975_SELF_TEST_MODE, &data) != true) {
		*test_code = SENSOR_TEST_ERR_READ;
		ret_val = false;
	} else {
		if (arg != NULL) {
			((sensor_data_t *)arg)->scaled = false;
			((sensor_data_t *)arg)->timestamp = 0;

			((sensor_data_t *)arg)->axis.x = (int32_t)data.x;
			((sensor_data_t *)arg)->axis.y = (int32_t)data.y;
			((sensor_data_t *)arg)->axis.z = (int32_t)data.z;
		}

		/* Check range of readings */
		if ((AK8975_TEST_X_MIN > data.x) ||
				(data.x > AK8975_TEST_X_MAX) ||
				(AK8975_TEST_Y_MIN > data.y) ||
				(data.y > AK8975_TEST_Y_MAX) ||
				(AK8975_TEST_Z_MIN > data.z) ||
				(data.z > AK8975_TEST_Z_MAX)) {
			*test_code = SENSOR_TEST_ERR_RANGE;
			ret_val = false;  /* value out of range */
		}
	}

	/* Disable test bias */
	sensor_bus_put(hal, AK8975_REG_ASTC, 0);

	return ret_val;
}
