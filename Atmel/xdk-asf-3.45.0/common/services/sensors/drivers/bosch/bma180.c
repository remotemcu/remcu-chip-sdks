/**
 * \file
 *
 * \brief Bosch BMA180 3-axis accelerometer driver.
 *
 * This file contains functions for initializing and reading data
 * from a Bosch BMA180 3-axis accelerometer.
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
#include "bma180.h"
#include "bma_axis.inc.c"

static bool bma180_ioctl(sensor_t *, sensor_command_t, void *);
static bool bma180_read(sensor_t *, sensor_read_t, sensor_data_t *);
static bool bma180_set_bandwidth(sensor_hal_t *, int16_t bandwidth);
static bool bma180_set_range(sensor_hal_t *, int16_t);

/** \brief Bosch BMA180 Range Table (milli-g, register value) */
static const sensor_map_t range_table [] = {
	{{ 1000}, BMA180_RANGE_1G}, {{1500}, BMA180_RANGE_1_5G},
	{{ 2000}, BMA180_RANGE_2G}, {{3000}, BMA180_RANGE_3G},
	{{ 4000}, BMA180_RANGE_4G}, {{8000}, BMA180_RANGE_8G},
	{{16000}, BMA180_RANGE_16G}
};

/** \brief Bosch BMA180 Bandwidth Table (hertz, register value) */
static const sensor_map_t band_table [] = {
	{{ 10}, BW_10HZ }, {{  20}, BW_20HZ  },
	{{ 40}, BW_40HZ }, {{  75}, BW_75HZ  },
	{{150}, BW_150HZ}, {{ 300}, BW_300HZ },
	{{600}, BW_600HZ}, {{1200}, BW_1200HZ}
};

/**
 * @brief Bosch BMA180 accelerometer driver initialization.
 *
 * This is the main initialization function for the BMA180 device.
 * The accelerometer range and bandwidth are set based on user-specified
 * values from the system configuration.
 *
 * @param sensor    Address of a sensor device descriptor.
 * @param resvd     Reserved value.
 * @return bool     true if the call succeeds, else false is returned.
 */
bool bma180_init(sensor_t *sensor, int resvd)
{
	bool status = false;

	sensor_hal_t *const hal = sensor->hal;

	if (BMA180_ID_VAL == sensor_bus_get(hal, BMA180_CHIP_ID)) {
		/* Set the driver function table and capabilities pointer. */
		static const sensor_device_t bma180_device = {
			.func.read        = bma180_read,
			.func.ioctl       = bma180_ioctl,

			.caps.feature     = SENSOR_CAPS_3_AXIS     |
					SENSOR_CAPS_SELFTEST   |
					SENSOR_CAPS_HI_G_EVENT |
					SENSOR_CAPS_LO_G_EVENT |
					SENSOR_CAPS_AUX_TEMP,

			.caps.vendor      = SENSOR_VENDOR_BOSCH,
			.caps.range_table = range_table,
			.caps.band_table  = band_table,
			.caps.range_count = ARRAYSIZE(range_table),
			.caps.band_count  = ARRAYSIZE(band_table),
			.caps.units       = SENSOR_UNITS_g0,
			.caps.scale       = SENSOR_SCALE_milli,
			.caps.name = "BMA180 Digital, triaxial acceleration sensor"
		};

		sensor->drv = &bma180_device;

		if (STATUS_OK == hal->bus.status) {
			/* Set the driver (device) default range, bandwidth, &
			 * resolution.
			 */
			hal->range      = 1000; /* milli-g */
			hal->bandwidth  = 10;   /* Hertz */
			hal->resolution = BMA180_DATA_RESOLUTION;

			bma180_set_range(hal, 0);
			bma180_set_bandwidth(hal, 0);

			/* Set the device burst read base address. */
			hal->burst_addr = BMA180_ACC_X_LSB;

			status = (STATUS_OK == hal->bus.status);
		}
	}

	return status;
}

/**
 * @brief Read BMA180 device ID and revision numbers.
 *
 * This function reads the accelerometer hardware identification registers
 * and returns these values in the specified data structure.
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param data      Address of sensor_data_t structure to return values.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma180_device_id(sensor_hal_t *hal, sensor_data_t *data)
{
	data->device.id = sensor_bus_get(hal, BMA180_CHIP_ID);
	data->device.version = sensor_bus_get(hal, BMA180_CHIP_VERSION);

	return true;
}

/**
 * @brief Read accelerometer data.
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
 * @param data     The address of a vector storing sensor axis data.
 * @return bool    true if the call succeeds, else false is returned.
 */
static bool bma180_get_accel(sensor_hal_t *hal, sensor_data_t *data)
{
	bma_axis_t axis[3];

	size_t const count = sensor_bus_read(hal, hal->burst_addr,
			axis, sizeof(axis));

	format_axis_data(hal, axis, data);

	return (count == sizeof(axis));
}

/**
 * @brief Read BMA180 integrated temperature sensor data.
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param data      The address where temperature samples are returned.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma180_get_temperature(sensor_hal_t *hal, sensor_data_t *data)
{
	int8_t temp_data = (int8_t)sensor_bus_get(hal, BMA180_TEMP);

	if (data->scaled) {
		/* \todo
		 *
		 * Review and verify this temperature compensation w.r.t. the
		 * setting for the OFFSET_T register in particular.
		 *
		 * Also verify the scaled resolution per the Bosch datasheet;
		 * is the temperature data resolution is 0.5 C/LSB or 0.5 K/LSB?
		 */
		data->temperature.value = BMA180_TEMP_OFFSET + (temp_data / 2);
	} else {
		data->temperature.value = temp_data;
	}

	return (STATUS_OK == hal->bus.status);
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
static bool bma180_read(sensor_t *sensor, sensor_read_t type,
		sensor_data_t *data)
{
	sensor_hal_t *const hal = sensor->hal;

	switch (type) {
	case SENSOR_READ_ACCELERATION:
		return bma180_get_accel(hal, data);

	case SENSOR_READ_TEMPERATURE:
		return bma180_get_temperature(hal, data);

	case SENSOR_READ_ID:
		return bma180_device_id(hal, data);

	default:
		sensor->err = SENSOR_ERR_FUNCTION;
		return false;
	}
}

/**
 * @brief Set the BMA180 execution mode
 *
 * @param hal      Address of an initialized sensor hardware descriptor.
 * @param state     A specified sensor operational state.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma180_set_state(sensor_hal_t *hal, sensor_state_t state)
{
	bool result = false;

	return result;
}

/**
 * @brief Set the BMA180 full scale acceleration range
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param range     The index o a driver-specific range table entry.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma180_set_range(sensor_hal_t *hal, int16_t range)
{
	/* After changing the full scale range it takes (1/(2 * bandwidth))
	 * to overwrite the data registers with filtered data according to
	 * the selected bandwidth.
	 */
	uint8_t const ctrl_range = ~(RANGE)&
			sensor_bus_get(hal, BMA180_OFFSET_LSB1);

	sensor_bus_put(hal, BMA180_OFFSET_LSB1,
			ctrl_range | range_table[range].reserved_val);

	return true;
}

/**
 * @brief Set the BMA180 ADC output data bandwidth
 *
 * @param hal      Address of an initialized sensor hardware descriptor.
 * @param band     The index of a driver-specific bandwidth table entry.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma180_set_bandwidth(sensor_hal_t *hal, int16_t band)
{
	/* Set the device sample frequency. */
	uint8_t const ctrl_bw = ~(BW)&sensor_bus_get(hal, BMA180_BW_TCS);

	sensor_bus_put
		(hal, BMA180_BW_TCS, ctrl_bw | band_table[band].reserved_val);

	return true;
}

/**
 * @brief BMA180 ioctl control entry point
 *
 * @param   hal     Address of an initialized sensor hardware descriptor.
 * @param   cmd     Command to execute
 * @param   arg     Argument for command (varies)
 * @return  bool    true if the call succeeds, else false is returned.
 */
static bool bma180_ioctl(sensor_t *sensor, sensor_command_t cmd, void *arg)
{
	sensor_hal_t *const hal = sensor->hal;
	sensor_data_t sample = {.scaled = true};

	switch (cmd) {
	case SENSOR_SET_STATE:
		return bma180_set_state(hal, *((sensor_state_t *)arg));

	case SENSOR_SET_RANGE:
		return bma180_set_range(hal, (uint16_t)*((int *)arg));

	case SENSOR_SET_BANDWIDTH:
		return bma180_set_bandwidth(hal, (uint16_t)*((int *)arg));

	case SENSOR_READ_VECTOR:
		if (bma180_get_accel(hal, &sample)) {
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
