/**
 * \file
 *
 * \file
 *
 * \brief Honeywell HMC5883L 3-axis magnetometer.
 *
 * This file contains functions for initializing and reading data
 * from a Honeywell HMC5883L 3-axis magnetometer.
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
#include "hmc5883l.h"

static bool hmc5883l_calibrate(sensor_t *, sensor_calibration_t, int, void *);
static bool hmc5883l_device_id(sensor_hal_t *, sensor_data_t *);
static bool hmc5883l_get_field(sensor_hal_t *, sensor_data_t *);
static bool hmc5883l_get_heading(sensor_hal_t *, sensor_data_t *);
static bool hmc5883l_ioctl(sensor_t *, sensor_command_t, void *);
static bool hmc5883l_read(sensor_t *, sensor_read_t type, sensor_data_t *);
static bool hmc5883l_selftest(sensor_t *, int *, void *);
static bool hmc5883l_set_bandwidth(sensor_hal_t *, int16_t);
static bool hmc5883l_set_range(sensor_hal_t *, int16_t);

#define DATA_OUTPUT_OVERFLOW    ((int16_t)0xf000)

#define SELF_TEST_DELAY_MSEC    (250)   /* delay in msec during self test */

#define READ_DELAY_MSEC         (100)   /* delay in msec between consecutive */

/*  readings (e.g. in calibration) */

/** \todo Flash memory addresses should be configurable. */

/* offset data */
#define CAL_OFFSETS_ADDR       (0)

/* sensitivity scaling data */
#define CAL_SENSITIVITY_ADDR   (0 + sizeof(vector3_t))

/** \brief Honeywell HMC5883L Range Table (microtesla, register value) */
static const sensor_map_t range_table [] = {
	{{90}, GAIN_0_9GA},  /**< 0.9 Gauss =  90 uTesla */
	{{130}, GAIN_1_3GA}, /**< 1.3 Gauss = 130 uTesla */
	{{190}, GAIN_1_9GA}, /**< 1.9 Gauss = 190 uTesla */
	{{250}, GAIN_2_5GA}, /**< 2.5 Gauss = 250 uTesla */
	{{400}, GAIN_4_0GA}, /**< 4.0 Gauss = 400 uTesla */
	{{470}, GAIN_4_7GA}, /**< 4.7 Gauss = 470 uTesla */
	{{560}, GAIN_5_6GA}, /**< 5.6 Gauss = 560 uTesla */
	{{810}, GAIN_8_1GA}, /**< 8.1 Gauss = 810 uTesla */
};

enum {index_90uT, index_130uT, index_190uT, index_250uT,
      index_400uT, index_470uT, index_560uT, index_810uT};

/** \brief Honeywell HMC5883L Data Scaling Table (counts per milligauss) */
static const int scale_table [] = {
	SCALE_0_9GA,        /**< 0.9 Gauss range */
	SCALE_1_3GA,        /**< 1.3 Gauss range */
	SCALE_1_9GA,        /**< 1.9 Gauss range */
	SCALE_2_5GA,        /**< 2.5 Gauss range */
	SCALE_4_0GA,        /**< 4.0 Gauss range */
	SCALE_4_7GA,        /**< 4.7 Gauss range */
	SCALE_5_6GA,        /**< 5.6 Gauss range */
	SCALE_8_1GA         /**< 8.1 Gauss range */
};

/** \brief Honeywell HMC5883L Bandwidth Table (hertz, register value) */
static const sensor_map_t band_table [] = {
	{{1}, DATA_RATE_0_75HZ},  /* 0.75 Hz  XXX called "1" for now XXX */
	{{2}, DATA_RATE_1_5HZ},   /* 1.5 Hz  XXX called "2" for now XXX */
	{{3}, DATA_RATE_3HZ},
	{{8}, DATA_RATE_7_5HZ},   /* 7.5 Hz  XXX called "8" for now XXX */
	{{15}, DATA_RATE_15HZ},
	{{30}, DATA_RATE_30HZ},
	{{75}, DATA_RATE_75HZ},
};

enum { index_1hz, index_2hz, index_3hz, index_8hz,
       index_15hz, index_30hz, index_75hz };

typedef struct {
	scalar_t cos_pitch; /**< Cosine of pitch angle */
	scalar_t sin_pitch; /**< Sine of pitch angle */
	scalar_t cos_roll;  /**< Cosine of roll angle */
	scalar_t sin_roll;  /**< Sine of roll angle */
} angle_t;

/** \brief HMC 5883l axis data format */
typedef struct {
	uint8_t msb;        /**< Most significant 8 bits */
	uint8_t lsb;        /**< Least significant 8 bits */
} hmc588l_axis_t;

/**
 * @brief Sensor calibration data
 *
 * This variable stores copies of axis calibration offsets stored in NVRAM.
 *
 * \internal
 * The current implementation will either use software floating-point routines
 * from the toolchain or fixed-point math routines in the ASF.  All fractional
 * sensor data should use types defined in precision.h where the type
 * \c scalar_t is an alias for a C/C++ floating-point type or an integer type
 * used by fixed-point arithmetic functions defined in the API.
 */
typedef struct {
	vector3_t offsets;
	vector3_t sensitivity;
} cal_data_t;

static cal_data_t cal_data;

/** Current range index for device */
static int dev_range;

/**
 * @brief Honeywell HMC5883L magnetometer driver initialization.
 *
 * This is the main initialization function for the HMC5883L device.
 *
 * @param sensor    Address of a sensor device descriptor.
 * @param resvd     Reserved value.
 * @return bool     true if the call succeeds, else false is returned.
 */
bool hmc5883l_init(sensor_t *sensor, int resvd)
{
	bool status = false;

	sensor_hal_t *const hal = sensor->hal;

	sensor_data_t data;

	if (hmc5883l_device_id(hal,
			&data) && (HMC5883L_DEV_ID == data.device.id)) {
		/* Set the driver function table and capabilities pointer. */
		static const sensor_device_t hmc5883l_device = {
			.func.read      = hmc5883l_read,
			.func.ioctl     = hmc5883l_ioctl,
			.func.selftest  = hmc5883l_selftest,
			.func.calibrate = hmc5883l_calibrate,

			.caps.feature   = SENSOR_CAPS_3_AXIS |
					SENSOR_CAPS_SELFTEST,

			.caps.vendor    = SENSOR_VENDOR_HONEYWELL,
			.caps.units     = SENSOR_UNITS_tesla,
			.caps.scale     = SENSOR_SCALE_micro,
			.caps.name
				= "HMC5883L triaxial compass/magnetometer"
		};

		sensor->drv = &hmc5883l_device;

		/* Enable sensor in continuous measurement mode */
		sensor_bus_put(hal, HMC5883L_MODE_REG, MODE_CONTIN);

		/* Set the driver (device) default range, bandwidth, and
		 * resolution.
		 */
		sensor_bus_put(hal, HMC5883L_CONFIG_REG_A,
				(DATA_RATE_15HZ | MEAS_MODE_NORM));

		hal->range      = range_table[index_130uT].range_units;
		hal->bandwidth  = band_table[index_15hz].bandwidth_Hz;
		hal->resolution = HMC5883L_DATA_RESOLUTION;

		hmc5883l_set_range(hal, index_130uT);
		hmc5883l_set_bandwidth(hal, index_15hz);

		/* Initialize calibration data (offsets & sensitivity) from
		 * NVRAM.
		 */
		nvram_read(0, &cal_data, sizeof(cal_data));

		/* Clear all calibration values if any are invalid. */
		#if defined(MATH_FIXED_POINT)
		if ((cal_data.x == -1) || (cal_data.y == -1) || (cal_data.z == -1)) {
		#else
		if (isnan(cal_data.offsets.x) || isnan(cal_data.offsets.y) ||
				isnan(cal_data.offsets.z)) {
		#endif
			memset(&cal_data, 0x00, sizeof(cal_data));
		}
		
		status = (STATUS_OK == hal->bus.status);
	}

	return status;
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
static bool hmc5883l_device_id(sensor_hal_t *hal, sensor_data_t *data)
{
	uint32_t id_reg = 0;
	size_t const id_len = 3;

	size_t const count = sensor_bus_read
				(hal, HMC5883L_ID_REG_A, &id_reg, id_len);

	data->device.id  = cpu_to_be32(id_reg) >> 8;
	data->device.version = 0;

	return (count == id_len);
}

/**
 * @brief Read magnetometer vector data.
 *
 * This function obtains magnetometer data for all three axes of the Honeywell
 * device.  The data is read from six device registers using a multi-byte
 * bus transfer.  The 13-bit raw results are then assembled from the two
 * register values for each axis, including extending the sign bit, to
 * form a signed 16-bit value.
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param data      The address of a vector storing sensor axis data.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool hmc5883l_get_data(sensor_hal_t *hal, vector3_t *data)
{
	int16_t axis_data[3];    /* input data values:  X,Y,Z */

	/* Ensure that single-measurement mode is set and that bit MR7 is
	 * cleared. Bit MR7 is set internally after each single-measurement
	 * operation.
	 */
	sensor_bus_put(hal, HMC5883L_MODE_REG, MODE_SINGLE);

	do {
		/* Wait for the data ready signal.
		 *
		 * Instead of polling DRDY, as is done below, the device can be
		 * placed in continuous measurement mode and this signal can be
		 * configured to trigger an asynchronous interrupt.
		 */
	} while (gpio_pin_is_low(hal->mcu_sigint /* DRDY input */));

	/* Get measurement data (consecutive big endian byte pairs: x, y, z). */
	hmc588l_axis_t input[3];

	size_t const count = sensor_bus_read
				(hal, HMC5883L_MAG_X_HI, (uint8_t *)input,
				sizeof(input));

	if (count != sizeof(input)) {
		return false;
	}

	/* Note: Device data register order = x, z, y !! */
	axis_data[0] = ((int16_t)((input[0].msb << 8) + input[0].lsb));
	axis_data[2] = ((int16_t)((input[1].msb << 8) + input[1].lsb));
	axis_data[1] = ((int16_t)((input[2].msb << 8) + input[2].lsb));

	if ((axis_data[0] == DATA_OUTPUT_OVERFLOW) ||
			(axis_data[1] == DATA_OUTPUT_OVERFLOW) ||
			(axis_data[2] == DATA_OUTPUT_OVERFLOW)) {
		return false;
	}

	/*
	 * Convert signed integer values to a real data type for calculations.
	 * Use device orientation configuration to assign axes.
	 */
	const sensor_orient_t *const orient = &(hal->orientation);

	data->x = orient->x.sign * axis_data[orient->x.axis];
	data->y = orient->y.sign * axis_data[orient->y.axis];
	data->z = orient->z.sign * axis_data[orient->z.axis];

	return true;
}

/**
 * @brief Apply stored sensitivity scaling factors to sensor reading
 *
 * This function applies stored sensitivity scaling to the "input" vector of
 * magnetometer values (the magnetic field vector) and returns the modified
 * values.
 *
 * @param   input       Contains the measured magnetic field values.  The
 *                      sensitivty-adjusted values will replace the contents.
 * @retval  true        successfully adjusted sensor readings
 * @retval  false       Failed to adjust sensor readings
 */
static void hmc5883l_apply_sensitivity(vector3_t *input)
{
	/* Apply sensitivity scaling to the uncalibrated input field vector. */
	input->x *= cal_data.sensitivity.x;
	input->y *= cal_data.sensitivity.y;
	input->z *= cal_data.sensitivity.z;
}

/**
 * @brief Apply stored offset values to sensor reading
 *
 * This function applies stored calibration offsets to the "input" vector of
 * magnetometer values (the magnetic field vector) and returns the modified
 * values.  The offsets are calculated based on sensitivity-adjusted readings,
 * so this function should be used after the values that have been adjusted
 * using hmc5883l_apply_sensitivity().
 *
 * @param   input       Contains the measured magnetic field values, adjusted
 *                      for sensitivity.  The offset-adjusted values will
 *                      replace the contents.
 * @retval  true        successfully adjusted sensor readings
 * @retval  false       Failed to adjust sensor readings
 */
static void hmc5883l_apply_offset(vector3_t *input)
{
	/* Apply calibrated offsets to the uncalibrated input field vector. */
	input->x -= cal_data.offsets.x;
	input->y -= cal_data.offsets.y;
	input->z -= cal_data.offsets.z;
}

/**
 * @brief Read magnetometer vector (3-axis) data
 *
 * This function obtains magnetometer data for all three axes of the Honeywell
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
 * @param   hal     Address of an initialized sensor device descriptor.
 * @param   data    The address of a vector storing sensor axis data.
 * @return  bool    true if the call succeeds, else false is returned.
 */
static bool hmc5883l_get_field(sensor_hal_t *hal, sensor_data_t *data)
{
	/* Get magnetic field measurements & test for data overflow. */
	vector3_t mag_data;

	bool result = hmc5883l_get_data(hal, &mag_data);

	if (result) {
		if (data->scaled) {
			/* Apply sensitivity adjustment to data */
			hmc5883l_apply_sensitivity(&mag_data);

			/* Apply measurement offsets to data */
			hmc5883l_apply_offset(&mag_data);

			/* Scale output values to SI units (uTesla) */
			scalar_t const scale = (scalar_t)GAUSS_TO_MICRO_TESLA /
					scale_table[dev_range];

			vector3_scale(scale, &mag_data);
		}

		data->axis.x = (int32_t)mag_data.x;
		data->axis.y = (int32_t)mag_data.y;
		data->axis.z = (int32_t)mag_data.z;
	}

	return result;
}

/**
 * @brief Read magnetometer heading/direction data.
 *
 * This function obtains magnetometer data for all three axes of the Honeywell
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
 * @param   hal     Address of an initialized sensor device descriptor.
 * @param   data    The address of a vector storing sensor axis data.
 * @return  bool    true if the call succeeds, else false is returned.
 */
static bool hmc5883l_get_heading(sensor_hal_t *hal, sensor_data_t *data)
{
	/* Get magnetic field measurements & test for data overflow. */
	vector3_t mag_data;

	bool result = hmc5883l_get_data(hal, &mag_data);

	if (result) {
		/* Apply sensitivity adjustment to data */
		hmc5883l_apply_sensitivity(&mag_data);

		/* Apply measurement offsets to data */
		hmc5883l_apply_offset(&mag_data);

		/* Calculate direction, inclination, and field strength. */
		scalar_t theta;    /* direction angle (degrees) */
		scalar_t delta;    /* inclination angle (degrees) */
		scalar_t strength; /* magnetic field intensity */

		result = field_direction(&mag_data, &theta, &delta, &strength);

		if (result) {
			strength *= ((scalar_t)GAUSS_TO_MICRO_TESLA /
					scale_table[dev_range]);

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
static bool hmc5883l_read(sensor_t *sensor, sensor_read_t type,
		sensor_data_t *data)
{
	sensor_hal_t *const hal = sensor->hal;

	switch (type) {
	case SENSOR_READ_FIELD:
		return hmc5883l_get_field(hal, data);

	case SENSOR_READ_HEADING:
		return hmc5883l_get_heading(hal, data);

	case SENSOR_READ_ID:
		return hmc5883l_device_id(hal, data);

	default:
		sensor->err = SENSOR_ERR_FUNCTION;
		return false;
	}
}

/**
 * @brief  Set the range for the magnetometer
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param range     The index of a driver-specific range table entry.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool hmc5883l_set_range(sensor_hal_t *hal, int16_t range)
{
	sensor_bus_put(hal, HMC5883L_CONFIG_REG_B,
			range_table[range].reserved_val);

	/* Store the index for use with data scaling. */
	dev_range = range;

	return true;
}

/**
 * @brief  Set the sample bandwidth for the magnetometer
 *
 * @param hal      Address of an initialized sensor hardware descriptor.
 * @param band     The index of a driver-specific bandwidth table entry.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool hmc5883l_set_bandwidth(sensor_hal_t *hal, int16_t bw)
{
	uint8_t reg_val = sensor_bus_get(hal, HMC5883L_CONFIG_REG_A);

	reg_val &= ~(DATA_RATE); /* clear data rate select bits */

	sensor_bus_put(hal, HMC5883L_CONFIG_REG_A,
			reg_val | band_table[bw].reserved_val);

	return true;
}

/**
 * @brief HMC5883L ioctl control entry point
 *
 * @param sensor        Address of an initialized sensor descriptor.
 * @param cmd           Command to execute
 * @param arg           Argument for command (varies)
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool hmc5883l_ioctl(sensor_t *sensor, sensor_command_t cmd,
		void *arg)
{
	sensor_hal_t *const hal = sensor->hal;
	bool status = false;

	switch (cmd) {
	case SENSOR_SET_RANGE:
		status = hmc5883l_set_range(hal, (uint16_t)*((int *)arg));
		break;

	case SENSOR_SET_BANDWIDTH:
		status = hmc5883l_set_bandwidth(hal, (uint16_t)*((int *)arg));
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
 * @param sensor    Address of an initialized sensor descriptor.
 * @param data      The address of a vector storing sensor axis data.
 * @param step      The calibration stage number (1 to 3).
 * @param info      Unimplemented (ignored) parameter.
 * @return bool     true if the call succeeds, else false is returned.
 */
bool hmc5883l_calibrate(sensor_t *sensor, sensor_calibration_t calib_type,
		int step, void *info)
{
	static vector3_t step_data[3]; /* sensor readings during calibration */
	vector3_t dummy_data;          /* data from first sensor read (ignored) */
	vector3_t read_back;           /* data read back from nvram to validate */
	sensor_data_t test_data;       /* readings during self test */
	int test_code;                 /* self-test code & result */
	sensor_hal_t *const hal = sensor->hal;

	/* Validate the supported calibration types and step number. */
	if ((calib_type != MANUAL_CALIBRATE) || ((step < 1) || (step > 3))) {
		return false;
	}

	/* During first pass, use self-test to determine sensitivity scaling */
	if (step == 1) {
		/* Run internal self test with known bias field */
		test_code = SENSOR_TEST_BIAS_POS;

		if ((hmc5883l_selftest(sensor, &test_code,
				&test_data) == false) ||
				(test_code != SENSOR_TEST_ERR_NONE)) {
			return false;
		}

		/* Calculate & store sensitivity adjustment values */
		cal_data.sensitivity.x
			= ((scalar_t)HMC5883L_TEST_X_NORM / test_data.axis.x);
		cal_data.sensitivity.z
			= ((scalar_t)HMC5883L_TEST_Z_NORM / test_data.axis.z);
		cal_data.sensitivity.y
			= ((scalar_t)HMC5883L_TEST_Y_NORM / test_data.axis.y);

		nvram_write(CAL_SENSITIVITY_ADDR, &cal_data.sensitivity,
				sizeof(cal_data.sensitivity));

		/* Read back data and confirm it was written correctly */
		nvram_read(CAL_SENSITIVITY_ADDR, &read_back, sizeof(vector3_t));

		if (memcmp(&cal_data.sensitivity, &read_back,
				sizeof(vector3_t))) {
			sensor->err = SENSOR_ERR_IO;
			return false;
		}
	}

	/* Read sensor data and test for data overflow.
	 *   Note: Sensor must be read twice - the first reading may
	 *         contain stale data from previous orientation.
	 */
	if (hmc5883l_get_data(hal, &dummy_data) != true) {
		return false;
	}

	delay_ms(READ_DELAY_MSEC);

	if (hmc5883l_get_data(hal, &(step_data [step - 1])) != true) {
		return false;
	}

	/* Apply sensitivity scaling factors */
	hmc5883l_apply_sensitivity(&(step_data [step - 1]));

	switch (step) {
	/* There's nothing more to do on the first two passes. */
	case 1:
	case 2:
		break;

	/* Calculate & store the offsets on the final pass. */
	case 3:
		cal_data.offsets.x = (step_data[0].x + step_data[1].x) / 2;
		cal_data.offsets.y = (step_data[0].y + step_data[1].y) / 2;
		cal_data.offsets.z = (step_data[1].z + step_data[2].z) / 2;

		nvram_write(CAL_OFFSETS_ADDR, &cal_data.offsets,
				sizeof(cal_data.offsets));

		/* Read back data and confirm it was written correctly */
		nvram_read(0, &read_back, sizeof(vector3_t));

		if (memcmp(&cal_data.offsets, &read_back, sizeof(vector3_t))) {
			sensor->err = SENSOR_ERR_IO;
			return false;
		}

		break;

	default:
		return false;   /* bad step value */
	}

	return true;
}

/**
 * @brief Perform self-test function
 *
 * This function sets up and executes an built-in self test function
 * within the HMC5883L device.
 *
 * @param sensor    Address of an initialized sensor descriptor.
 * @param test_code Address of a numeric code of which test to perform
 *                  This location will contain the specific test result code
 *                  when the function returns.
 * @return bool     true if the call succeeds, else false is returned.
 */
bool hmc5883l_selftest(sensor_t *sensor, int *test_code, void *arg)
{
	int count;
	uint8_t meas_mode;          /* test measurement mode */
	vector3_t data;
	bool status = true;
	sensor_hal_t *const hal = sensor->hal;

	struct {
		uint8_t config_reg_a;
		uint8_t config_reg_b;
		uint8_t mode_reg;
	}
	reg_set;

	/* Initialize result code */
	*test_code = SENSOR_TEST_ERR_NONE;

	/* Save register values */
	count = sensor_bus_read(hal, HMC5883L_CONFIG_REG_A, (uint8_t *)&reg_set,
			sizeof(reg_set));

	if (count != sizeof(reg_set)) {
		*test_code = SENSOR_TEST_ERR_READ;
		return false;
	}

	/* Set range (sensitivity) */
	sensor_bus_put(hal, HMC5883L_CONFIG_REG_B, HMC5883L_TEST_GAIN);

	/* Set test mode */
	switch (*test_code) {          /* which test was specified */
	case SENSOR_TEST_DEFAULT:
	case SENSOR_TEST_BIAS_POS:
		meas_mode = MEAS_MODE_POS;  /* positive bias measurement mode */
		break;

	case SENSOR_TEST_BIAS_NEG:
		meas_mode = MEAS_MODE_NEG;  /* negative bias measurement mode */
		break;

	default:
		/* bad test code specified */
		sensor_bus_put(hal, HMC5883L_CONFIG_REG_B,
				reg_set.config_reg_b);
		/* restore reg */
		*test_code = SENSOR_TEST_ERR_FUNCTION;
		return false;
	}

	sensor_bus_put(hal, HMC5883L_CONFIG_REG_A,
			(DATA_RATE_15HZ | MEAS_AVG_1 | meas_mode));

	delay_ms(SELF_TEST_DELAY_MSEC);

	/* Perform test measurement & check results */
	sensor_bus_put(hal, HMC5883L_MODE_REG, MODE_SINGLE); /* single meas mode
	                                                      **/

	if (hmc5883l_get_data(hal, &data) != true) {
		*test_code = SENSOR_TEST_ERR_READ;
		status = false;    /* failed to read data registers */
	} else {
		if (arg != NULL) {
			((sensor_data_t *)arg)->scaled = false; /* only raw values */
			((sensor_data_t *)arg)->timestamp = 0;  /* no timestamp */

			((sensor_data_t *)arg)->axis.x = (int32_t)data.x; /* copy values */
			((sensor_data_t *)arg)->axis.y = (int32_t)data.y;
			((sensor_data_t *)arg)->axis.z = (int32_t)data.z;
		}

		/* Check range of readings */
		if ((HMC5883L_TEST_X_MIN > data.x) ||
				(data.x > HMC5883L_TEST_X_MAX) ||
				(HMC5883L_TEST_Y_MIN > data.y) ||
				(data.y > HMC5883L_TEST_Y_MAX) ||
				(HMC5883L_TEST_Z_MIN > data.z) ||
				(data.z > HMC5883L_TEST_Z_MAX)) {
			*test_code = SENSOR_TEST_ERR_RANGE;
			status = false; /* value out of range */
		}
	}

	/* Restore registers */
	count = sensor_bus_write(hal, HMC5883L_CONFIG_REG_A,
			(uint8_t *)&reg_set, sizeof(reg_set));

	if (count != sizeof(reg_set)) {
		*test_code = SENSOR_TEST_ERR_WRITE;
		status = false;
	}

	return status;
}
