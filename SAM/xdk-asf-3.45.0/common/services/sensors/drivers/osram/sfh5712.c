/**
 * \file
 *
 * \brief Osram SFH5712 light sensor driver.
 *
 * This file contains functions for initializing and reading data
 * from a Osram SFH5712 light sensor.
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
#include "sfh5712.h"

static bool sfh5712_ioctl(sensor_t *, sensor_command_t, void *);
static bool sfh5712_device_id(sensor_hal_t *, sensor_data_t *);
static bool sfh5712_get_light(sensor_hal_t *, sensor_data_t *);
static bool sfh5712_read(sensor_t *, sensor_read_t, sensor_data_t *);
static bool sfh5712_set_state(sensor_hal_t *, sensor_state_t);

/**
 * @brief Osram SFH5712 light sensor driver initialization.
 *
 * This is the main initialization function for the SFH5712 device.
 *
 * @param sensor    Address of a sensor device descriptor.
 * @param resvd     Reserved value.
 * @return bool     true if the call succeeds, else false is returned.
 */
bool sfh5712_init(sensor_t *sensor, int resvd)
{
	bool status = false;
	sensor_hal_t *const hal = sensor->hal;

	/* Read and check part ID register */
	uint8_t part_id = sensor_bus_get(hal, SFH5712_PART_ID);

	if (part_id == (SFH5712_PART_ID_VAL | SFH5712_PART_REV_VAL)) {
		/* Set the driver function table and capabilities pointer. */
		static const sensor_device_t sfh5712_device = {
			.func.read            = sfh5712_read,
			.func.ioctl           = sfh5712_ioctl,
#if 0
			.caps.feature         = XXX
#endif
			.caps.vendor          = SENSOR_VENDOR_OSRAM,
			.caps.units           = SENSOR_UNITS_lux,
			.caps.scale           = SENSOR_SCALE_one,
			.caps.name            = "SFH5712 Ambient Light Sensor"
		};

		sensor->drv = &sfh5712_device;

		hal->resolution = SFH5712_DATA_RESOLUTION;

		/* Put sensor in active mode */
		sensor_bus_put(hal, SFH5712_ALS_CONTROL, ALS_MODE_ACTIVE);

		status = true;
	}

	return status;
}

/**
 * @brief Read SFH5712 device ID and revision numbers.
 *
 * This function reads the sensor hardware identification registers
 * and returns these values in the specified data structure.
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param data      Address of sensor_data_t structure to return values.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool sfh5712_device_id(sensor_hal_t *hal, sensor_data_t *data)
{
	uint32_t const part_id = sensor_bus_get(hal, SFH5712_PART_ID);

	data->device.id = (part_id & PART_ID_MASK) >> PART_ID_SHIFT;
	data->device.version = (part_id & PART_REV_MASK);

	return true;
}

/**
 * @brief Read SFH5712 light level data.
 *
 * This function reads the ambient light level data from the sensor
 * and places it in the user-provided sensor_data_t structure.
 *
 * @param sensor    Address of an initialized sensor device descriptor.
 * @param data      The address of a vector storing sensor measurement data.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool sfh5712_get_light(sensor_hal_t *hal, sensor_data_t *data)
{
	struct {
		uint8_t lsb;
		uint8_t msb;
	} light_data;

	/* Read and combine two light level data registers
	 *   NOTE:  LSB register must be read first!
	 */
	size_t const count = sensor_bus_read(hal, SFH5712_ALS_DATA_LSB,
			(uint8_t *)&light_data, sizeof(light_data));

	/* Device uses lux for internal values, so raw is the same as scaled */
	data->light.value = (uint32_t)((light_data.msb << 8) | light_data.lsb);

	return (count == sizeof(light_data));
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
static bool sfh5712_read(sensor_t *sensor, sensor_read_t type,
		sensor_data_t *data)
{
	sensor_hal_t *const hal = sensor->hal;

	switch (type) {
	case SENSOR_READ_LIGHT:
		return sfh5712_get_light(hal, data);

	case SENSOR_READ_ID:
		return sfh5712_device_id(hal, data);

	default:
		sensor->err = SENSOR_ERR_FUNCTION;
		return false;
	}
}

/**
 * @brief Set the SFH5712 execution mode.
 *
 * This routine sets a specified SFH5712 execution state to one of the
 * following:
 *
 * SENSOR_STATE_SLEEP:
 *      Setting the sleep mode puts the sensor in standby mode, in which
 *      no measurements are made.
 *
 *  SENSOR_STATE_NORMAL:
 *      Setting the sleep mode puts sensor in continuous measurement mode.
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param state     A specified sensor operational state.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool sfh5712_set_state(sensor_hal_t *hal, sensor_state_t state)
{
	switch (state) {
	case SENSOR_STATE_SLEEP:
		sensor_bus_put(hal, SFH5712_ALS_CONTROL, ALS_MODE_STANDBY);
		break;

	case SENSOR_STATE_NORMAL:
		sensor_bus_put(hal, SFH5712_ALS_CONTROL, ALS_MODE_ACTIVE);
		break;

	default:
		return false;
	}

	return true;
}

/**
 * @brief SFH5712 ioctl control entry point
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param cmd       Command to execute
 * @param arg       Argument for command (varies)
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool sfh5712_ioctl(sensor_t *sensor, sensor_command_t cmd, void *arg)
{
	sensor_hal_t *const hal = sensor->hal;
	bool status = false;

	switch (cmd) {
	case SENSOR_SET_STATE:
		status = sfh5712_set_state(hal, *((sensor_state_t *)arg));
		break;

	default:
		sensor->err = SENSOR_ERR_UNSUPPORTED;
		break;
	}

	return status;
}
