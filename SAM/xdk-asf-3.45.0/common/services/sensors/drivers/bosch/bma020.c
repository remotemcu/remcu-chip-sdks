/**
 * \file
 *
 * \brief Bosch BMA020 3-axis accelerometer.
 *
 * This file contains functions for initializing and reading data
 * from a Bosch BMA020 3-axis accelerometer.
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
#include "bma020.h"
#include "bma_axis.inc.c"

static bool bma020_ioctl(sensor_t *, sensor_command_t, void *);
static bool bma020_read(sensor_t *, sensor_read_t, sensor_data_t *);
static bool bma020_set_range(sensor_hal_t *, int16_t);
static bool bma020_set_bandwidth(sensor_hal_t *, int16_t);

/** \brief Bosch BMA020 Range Table (milli-g, register value) */
static const sensor_map_t range_table [] = {
	{{2000}, RANGE_2G}, {{4000}, RANGE_4G}, {{8000}, RANGE_8G}
};

/** \brief Bosch BMA020 Bandwidth Table (hertz, register value) */
static const sensor_map_t band_table [] = {
	{{  25}, BANDWIDTH_25HZ  }, {{ 50}, BANDWIDTH_50HZ },
	{{ 100}, BANDWIDTH_100HZ }, {{190}, BANDWIDTH_190HZ},
	{{ 375}, BANDWIDTH_375HZ }, {{750}, BANDWIDTH_750HZ},
	{{1500}, BANDWIDTH_1500HZ}
};

/**
 * @brief Bosch BMA020 accelerometer driver initialization.
 *
 * This is the main initialization function for the BMA020 device.
 * The accelerometer range and bandwidth are set based on user-specified
 * values from the system configuration.
 *
 * @param sensor    Address of a sensor device descriptor.
 * @param resvd     Reserved value.
 * @return bool     true if the call succeeds, else false is returned.
 */
bool bma020_init(sensor_t *sensor, int resvd)
{
	bool status = false;

	sensor_hal_t *const hal = sensor->hal;

	if (BMA020_ID_VAL == sensor_bus_get(hal, BMA020_CHIP_ID)) {
		/* Set the driver function table and capabilities pointer. */
		static const sensor_device_t bma020_device = {
			.func.read        = bma020_read,
			.func.ioctl       = bma020_ioctl,

			.caps.feature     = SENSOR_CAPS_3_AXIS     |
					SENSOR_CAPS_SELFTEST   |
					SENSOR_CAPS_HI_G_EVENT |
					SENSOR_CAPS_LO_G_EVENT,

			.caps.vendor      = SENSOR_VENDOR_BOSCH,
			.caps.range_table = range_table,
			.caps.band_table  = band_table,
			.caps.range_count = ARRAYSIZE(range_table),
			.caps.band_count  = ARRAYSIZE(band_table),
			.caps.units       = SENSOR_UNITS_g0,
			.caps.scale       = SENSOR_SCALE_milli,
			.caps.name = "BMA020 Digital, triaxial acceleration sensor"
		};

		sensor->drv = &bma020_device;

		/* Set the driver (device) default range, bandwidth, and
		 * resolution.
		 */
		hal->range      = 2000; /* milli-g */
		hal->bandwidth  = 25;   /* Hertz */
		hal->resolution = BMA020_DATA_RESOLUTION;

		bma020_set_range(hal, 0);
		bma020_set_bandwidth(hal, 0);

		/* Set the device burst read base address. */
		hal->burst_addr = BMA020_ACC_X_LSB;

		status = (STATUS_OK == hal->bus.status);
	}

	return status;
}

/**
 * @brief Read accelerometer device ID and revision numbers.
 *
 * This function reads the accelerometer hardware identification registers
 * and returns these values in the specified data structure.
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param data      Address of sensor_data_t structure to return values.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma020_device_id(sensor_hal_t *hal, sensor_data_t *data)
{
	data->device.id      = sensor_bus_get(hal, BMA020_CHIP_ID);
	data->device.version = sensor_bus_get(hal, BMA020_CHIP_VERSION);

	return true;
}

/**
 * @brief Read accelerometer vector data.
 *
 * This function obtains accelerometer data for all three axes of the Bosch
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
 * @param hal      Address of an initialized sensor hardware descriptor.
 * @param data      The address of a vector storing sensor axis data.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma020_get_accel(sensor_hal_t *hal, sensor_data_t *data)
{
	bma_axis_t axis [3];

	size_t const count = sensor_bus_read(hal, hal->burst_addr,
			axis, sizeof(axis));

	format_axis_data(hal, axis, data);

	return (count == sizeof(axis));
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
static bool bma020_read(sensor_t *sensor, sensor_read_t type,
		sensor_data_t *data)
{
	sensor_hal_t *const hal = sensor->hal;

	switch (type) {
	case SENSOR_READ_ACCELERATION:
		return bma020_get_accel(hal, data);

	case SENSOR_READ_ID:
		return bma020_device_id(hal, data);

	default:
		sensor->err = SENSOR_ERR_FUNCTION;
		return false;
	}
}

/**
 * @brief Set the BMA020 full scale acceleration range.
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param range     The index of a driver-specific range table entry.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma020_set_range(sensor_hal_t *hal, int16_t range)
{
	/*
	 * After changing the full scale range it takes (1/(2 * bandwidth))
	 * to overwrite the data registers with filtered data according to
	 * the selected bandwidth.
	 */
	uint8_t const ctrl4_range
		= ~(CTRL4_RANGE)&sensor_bus_get(hal, BMA020_CTRL4);

	sensor_bus_put
		(hal, BMA020_CTRL4,
			ctrl4_range | range_table[range].reserved_val);

	return true;
}

/**
 * @brief Set the BMA020 ADC output data bandwidth
 *
 * @param hal      Address of an initialized sensor hardware descriptor.
 * @param band     The index of a driver-specific bandwidth table entry.
 * @return bool    true if the call succeeds, else false is returned.
 */
static bool bma020_set_bandwidth(sensor_hal_t *hal, int16_t band)
{
	/* Set the device sample frequency. */
	uint8_t const ctrl4_bw
		= ~(CTRL4_BANDWIDTH)&sensor_bus_get(hal, BMA020_CTRL4);

	sensor_bus_put
		(hal, BMA020_CTRL4, ctrl4_bw | band_table[band].reserved_val);

	return true;
}

/**
 * @brief BMA020 ioctl control entry point
 *
 *
 * @param hal       Address of an initialized sensor device descriptor.
 * @param cmd       Command to execute
 * @param arg       Argument for command (varies)
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma020_ioctl(sensor_t *sensor, sensor_command_t cmd,
		void *arg)
{
	sensor_hal_t *const hal = sensor->hal;
	sensor_data_t sample = {.scaled = true};

	switch (cmd) {
	case SENSOR_SET_RANGE:
		return bma020_set_range(hal, *((uint16_t *)arg));

	case SENSOR_SET_BANDWIDTH:
		return bma020_set_bandwidth(hal, *((uint16_t *)arg));

	case SENSOR_READ_VECTOR:
		if (bma020_get_accel(hal, &sample)) {
			vector3_t *const pvec = (vector3_t *)arg;
			pvec->x = sample.axis.x;
			pvec->y = sample.axis.y;
			pvec->z = sample.axis.z;
			return true;
		} else {
			return false;
		}

	default:
		sensor->err = SENSOR_ERR_UNSUPPORTED;
		return false;
	}
}
