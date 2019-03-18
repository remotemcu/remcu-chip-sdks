/**
 * \file
 *
 * \brief Atmel Software Framework Common Sensor API.
 *
 * The sensor device service provides high-level interfaces and binary driver
 * libraries for sensor devices on systems built around UC3, XMEGA, and SAM
 * microcontrollers.
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

#include "sensor.h"

/** Driver Call Wrapper */
#define SENSOR_DRV_CALL(sns, fn, ...)   (((sns)->drv->func.fn) \
	? (((sns)->drv->func.fn)(sns, __VA_ARGS__)) : sensor_driver_unimpl(sns))

/**
 * @brief Get a range table index associated with a range value
 *
 * @internal
 *
 * This utility routine, provided for internal API and driver functions,
 * fetches the driver range table index associated with a device-specific
 * range value.  The table index returned in \c index is undefined in the event
 * of a \c false return value.
 *
 * @param  caps     Specifies an initialized driver capabilities descriptor.
 * @param  range    A device-specific operational range value.
 * @param  index    The driver range table index is returned to this location.
 * @return bool     true if the call succeeds, else false is returned.
 */
static inline bool sensor_range_index
	(const sensor_caps_t *caps, int16_t range, int *index)
{
	if (caps && caps->range_table) {
		for (int i = 0; i < caps->range_count; ++i) {
			if (caps->range_table[i].range_units == range) {
				*index = i;
				return true;
			}
		}
	}

	return false;
}

/**
 * @brief Get a bandwidth table index associated with a bandwidth value
 *
 * @internal
 *
 * This utility routine, provided for internal API and driver functions,
 * fetches the driver bandwidth table index associated with a specified
 * bandwidth value.  The table index returned in \c index is undefined in
 * the event of a \c false return value.
 *
 * @param  caps     Specifies an initialized driver capabilities descriptor.
 * @param  band     A bandwidth value (Hz).
 * @param  index    The driver range table index is returned to this location.
 * @return bool     true if the call succeeds, else false is returned.
 */
static inline bool sensor_band_index
	(const sensor_caps_t *caps, int16_t band, int *index)
{
	if (caps && caps->band_table) {
		for (int i = 0; i < caps->band_count; ++i) {
			if (caps->band_table[i].bandwidth_Hz == band) {
				*index = i;
				return true;
			}
		}
	}

	return false;
}

/**
 * @brief Default sensor event callback handler
 *
 * The default event callback handler returns immediately.
 *
 * @param data Sensor event data descriptor
 * @param arg  Optional user-specified callback argument
 * @return nothing
 */
void default_event_handler(volatile sensor_event_data_t *data,
		volatile void *arg)
{
#if 0
	static uint32_t spurious_event;
	++spurious_event;
#endif
}

/**
 * @ingroup mems_sensor_api
 * @{
 */

/**
 * @brief Unimplemented driver function handler
 *
 * This routine is called in the API to set the sensor error status and return
 * a status indicating a function call failure when a driver has been invoked to
 * run an interface that's not implemented in the driver.
 *
 * @param  sensor   The address of an initialized sensor descriptor.
 * @return bool     Always returns \c false.
 */
static bool inline sensor_driver_unimpl(sensor_t *sensor)
{
	sensor->err = SENSOR_ERR_FUNCTION;
	return false;
}

/**
 * @brief Attach a specified sensor descriptor to a sensor device.
 *
 * Applications invoke this routine to attach a \c sensor_t instance to an
 * existing sensor device of a specified \c type.  Assuming the attach call
 * is successful, the \c sensor_t instance can then be used with other sensor
 * API functions to perform operations on the device.
 *
 * @param   sensor  Specifies a descriptor to attach to the sensor device.
 * @param   type    Specifies the sensor type to attach.
 * @param   num     Driver instance number; currently ignored.
 * @param   aux     API Reserved value; should always be set to zero.
 * @return  bool    true if the call succeeds, else false is returned.
 */
bool sensor_attach(sensor_t *sensor, sensor_type_t type, int num, void *aux)
{
	bool attached = false;

	sensor_hal_t *hal = sensor_find(type);

	sensor->hal  = hal;   /* Set unconditionally for use in driver init. */
	sensor->type = type;  /* user-selected type (for multi-function device)
	                       **/
	sensor->aux  = aux;

	if ((hal != NULL) && /* sensor_bus_probe (hal, 0) && */
			((hal->sensor_init)(sensor, num))) {
		sensor->mod = SENSOR_STATE_NORMAL;
		sensor->err = SENSOR_ERR_NONE;
		attached = true;
	} else {
		sensor->err = SENSOR_ERR_DRIVER;
	}

	return attached;
}

/**
 * @brief Enumerate sensor devices.
 *
 * This routine is a sensor device enumeration function that will call a
 * user-defined callback \c func for each sensor of a specified \c type
 * configured into the system.  The user-callback function will be passed the
 * address of a \a sensor_hal_t \c HAL descriptor corresponding to the sensor
 * type along with a user-specified address \c arg storing any additional
 * function arguments.
 *
 * If the specified sensor \c type is \c SENSOR_TYPE_UNKNOWN, then the user
 * \c func will be called for every sensor device in the system.
 *
 * Once called, the user-callback function must return a boolean \a true
 * value to continue iterating the list, else \a false to cease device list
 * iteration.  This routine returns when there are not more sensors of the
 * requested \c type in the device list, or when the user function returns
 * zero (false).
 *
 * Note that this function will not be included in the API by default.  Build
 * a sensor system with \c INCLUDE_SENSOR_ENUM defined to include this routine.
 *
 * @param   type    Specifies the sensor type to enumerate.
 * @param   func    Specifies the address of a user callback function.
 * @param   arg     Specifies the address of a callback function argument.
 * @return  bool    true if the call succeeds, else false is returned.
 */
bool sensor_device_enum
	(sensor_type_t type, sensor_enum_callback func, void *arg)
{
#ifdef INCLUDE_SENSOR_ENUM
	size_t count;
	const sensor_hal_t *hal = sensor_list(&count);

	if (func != 0) {
		for (int n = 0; n < count; ++n, ++hal) {
			if (((type == SENSOR_TYPE_UNKNOWN) ||
					(type == hal->dev_type)) &&
					(false == (func)(hal, arg))) {
				return true;
			}
		}
	}
#endif /* INCLUDE_SENSOR_ENUM */

	return false;
}

/**
 * @brief Get sensor hardware device ID.
 *
 * This routine returns device-specific sensor hardware identification
 * and, optionally, version values.  Unimplemented values will be set
 * to zero.  For example, devices supporting a dedicated ID register, but
 * not a version register, will set "id" to the ID value and "ver" to zero.
 *
 * @param   sensor  The address of an initialized sensor descriptor.
 * @param   id      An address where the device ID is returned.
 * @param   ver     An address where the device version is returned.
 * @return  bool    true if the call succeeds, else false is returned.
 */
bool sensor_device_id(sensor_t *sensor, uint32_t *id, uint8_t *ver)
{
	sensor_data_t dev_data;
	bool status = false;

	status = sensor_read(sensor, SENSOR_READ_ID, &dev_data);

	if (status) {
		*id = dev_data.device.id;
		*ver = (uint8_t)dev_data.device.version;
	}

	return status;
}

/**
 * @brief Read sensor data
 *
 * This is a generic routine that will call a specified sensor function
 * returning sensor data.  It is used primarily by API routines
 * but may be called by special-case application or library code where
 * needed to extend the API semantics.
 *
 * As an example, consider a multiple-axis gyroscope driver implementing
 * the sensor_funcs_t.get_rotation() interface.  An application will usually
 * call the sensor_get_rotation() routine in this case, but the angular
 * rate might be obtained from the device as follows:
 *
 * @code
 *
 * sensor_t      gyroscope;
 * sensor_data_t omega;
 * ...
 *
 * sensor_read (&gyroscope, SENSOR_READ_ROTATION, &omega);
 * ...
 *
 * @endcode
 *
 * In the event of a false return from this routine, the contents stored
 * at the location specified by "data" are undefined.
 *
 * @param   sensor  The address of an initialized sensor descriptor.
 * @param   type    Type of sample to read from sensor
 * @param   data    Specifies an address where sensor data is stored.
 * @return  bool    true if the call succeeds, else false is returned.
 */
bool sensor_read(sensor_t *sensor, sensor_read_t type,
		sensor_data_t *data)
{
	bool result;

	result = SENSOR_DRV_CALL(sensor, read, type, data);

	if (result) {
		data->timestamp = sensor_timestamp();
	}

	return result;
}

/**
 * @brief Enumerate sensor bandwidth settings.
 *
 * This routine returns the address of a table, if any, holding device-specific
 * sensor bandwidth settings.  The use and context of the settings are specific
 * to the device and typically documented in the manufacturer's data sheets for
 * the device.
 *
 * @param   sensor  The address of a sensor descriptor.
 * @param   table   Location where the table address is returned.
 * @param   count   Location where the number of table elements is returned.
 * @return  bool    true if the call succeeds, else false is returned.
 */
bool sensor_enum_bandwidth
	(sensor_t *sensor, const sensor_band_t **table, size_t *count)
{
	*table = sensor->drv->caps.band_table;
	*count = sensor->drv->caps.band_count;

	return (*count) ? true : false;
}

/**
 * @brief Enumerate sensor range settings
 *
 * This routine returns the address of a table, if any, holding device-specific
 * sensor range settings.  The units of the settings are specific to the
 * device and typically documented in the manufacturer's data sheets for
 * the device.
 *
 * @param   sensor  The address of a sensor descriptor.
 * @param   table   Location where the table address is returned.
 * @param   count   Location where the number of table elements is returned.
 * @return  bool    true if the call succeeds, else false is returned.
 */
bool sensor_enum_range
	(sensor_t *sensor, const sensor_range_t **table, size_t *count)
{
	*table = sensor->drv->caps.range_table;
	*count = sensor->drv->caps.range_count;

	return (*count) ? true : false;
}

/**
 * @brief Install a sensor event handler.
 *
 * This routine installs a sensor event handler that will be called when
 * the specified sensor events occur. Function parameters specify the
 * specific sensor event to be reported, the address of the handler
 * function to be called, an optional parameter that will be passed to the
 * handler, and whether the event handler should initially be enabled or
 * disabled.
 *
 * The event handler can subsequently be enabled and disabled using the
 * sensor_event_enable() and sensor_event_disable() routines.
 *
 * @param  sensor        Specifies an initialized sensor descriptor
 * @param  sensor_event  Specifies the sensor event type
 * @param  handler       Specifies an application-defined callback
 * @param  arg           Specifies an optional callback argument
 * @param  enable        Specifies whether or not the event should be enabled
 * @return bool          true if the call succeeds, else false is returned.
 */
bool sensor_add_event(sensor_t *sensor, sensor_event_t sensor_event,
		sensor_event_callback handler, volatile void *arg, bool enable)
{
	sensor_event_callback_t callback;

	callback.handler = (handler != NULL) ? handler : default_event_handler;
	callback.arg     = arg;

	return SENSOR_DRV_CALL(sensor, event, sensor_event, &callback, enable);
}

/**
 * @brief Calibrate a sensor device.
 *
 * @param   sensor  The address of an initialized sensor descriptor.
 * @param   caltype The type of calibration to perform.
 * @return  bool    true if the call succeeds, else false is returned.
 */
bool sensor_calibrate(sensor_t *sensor, sensor_calibration_t caltype,
		int code, void *caldata)
{
	return SENSOR_DRV_CALL(sensor, calibrate, caltype, code, caldata);
}

/**
 * @brief Set a sensor device to low-power or standby mode.
 *
 * @param   sensor  The address of an initialized sensor descriptor.
 * @return  bool    true if the call succeeds, else false is returned.
 */
bool sensor_sleep(sensor_t *sensor, int arg)
{
	return sensor_set_state(sensor, SENSOR_STATE_SLEEP);
}

/**
 * @brief Initiate a sensor device software reset.
 *
 * @param   sensor  The address of an initialized sensor descriptor.
 * @return  bool    true if the call succeeds, else false is returned.
 */
bool sensor_reset(sensor_t *sensor, int arg)
{
	return sensor_set_state(sensor, SENSOR_STATE_RESET);
}

/**
 * @brief Set a sensor mode.
 *
 * This routine sets a specified sensor execution state to one of the
 * following values:
 *
 *  - SENSOR_STATE_NORMAL
 *  - SENSOR_STATE_SLEEP
 *  - SENSOR_STATE_SUSPEND
 *  - SENSOR_STATE_LOWEST_POWER
 *  - SENSOR_STATE_LOW_POWER
 *  - SENSOR_STATE_HIGH_POWER
 *  - SENSOR_STATE_HIGHEST_POWER
 *  - SENSOR_STATE_RESET
 *
 * These execution states are not supported in all devices.  The function
 * return value will indicate whether or not the request could be processed.
 * The result of the request, when supported, is device dependent.
 *
 * @param   sensor  The address of an initialized sensor descriptor.
 * @param   mode    A specified sensor operational mode.
 * @return  bool    true if the call succeeds, else false is returned.
 */
bool sensor_set_state(sensor_t *sensor, sensor_state_t mode)
{
	bool result = false;

	if (mode != sensor->mod) {
		result
			= SENSOR_DRV_CALL(sensor, ioctl, SENSOR_SET_STATE,
				&mode);
	}

	if (result) {
		sensor->mod
			= (mode ==
				SENSOR_STATE_RESET) ? SENSOR_STATE_NORMAL : mode;
	}

	return result;
}

/**
 * @brief Get a sensor mode.
 *
 * This routine gets the current sensor execution state which may be one
 * of the following values:
 *
 *  - SENSOR_STATE_NORMAL
 *  - SENSOR_STATE_SLEEP
 *  - SENSOR_STATE_SUSPEND
 *  - SENSOR_STATE_LOWEST_POWER
 *  - SENSOR_STATE_LOW_POWER
 *  - SENSOR_STATE_HIGH_POWER
 *  - SENSOR_STATE_HIGHEST_POWER
 *  - SENSOR_STATE_RESET
 *
 * These execution states are not supported in all devices.  The function
 * return value will indicate whether or not the request could be processed.
 * The result of the request, when supported, is device dependent.
 *
 * @param   sensor  The address of an initialized sensor descriptor.
 * @param   mode    The current sensor mode is returned to this location.
 * @return  bool    true if the call succeeds, else false is returned.
 */
bool sensor_get_state(sensor_t *sensor, sensor_state_t *mode)
{
	*mode = sensor->mod;
	return true;
}

/**
 * @brief Set a sensor operational threshold.
 *
 * @param   sensor  The address of an initialized sensor descriptor.
 * @param   type    A specified sensor operational threshold type.
 * @param   value   The value of the specified threshold.
 * @return  bool    true if the call succeeds, else false is returned.
 */
bool sensor_set_threshold
	(sensor_t *sensor, sensor_threshold_t type, int16_t value)
{
	sensor_threshold_desc_t threshold;

	threshold.type = type;
	threshold.value = value;

	return SENSOR_DRV_CALL(sensor, ioctl, SENSOR_SET_THRESHOLD, &threshold);
}

/**
 * @brief Get a sensor operational threshold.
 *
 * @param   sensor     The address of an initialized sensor descriptor.
 * @param   type       A specified sensor operational threshold type.
 * @param   value      Address of location to return threshold value
 * @return  bool       true if the call succeeds, else false is returned.
 */
bool sensor_get_threshold
	(sensor_t *sensor, sensor_threshold_t type, int16_t *value)
{
	sensor_threshold_desc_t threshold;
	bool status = false;

	threshold.type = type;

	if (SENSOR_DRV_CALL(sensor, ioctl, SENSOR_GET_THRESHOLD, &threshold)) {
		*value = threshold.value;
		status = true;
	}

	return status;
}

/**
 * @brief Execute a sensor device control function.
 *
 * @param   sensor  The address of an initialized sensor descriptor.
 * @param   cmd     Specifies the IOCTL command.
 * @param   arg     Specifies command parameters (varies by command).
 * @return  bool    true if the call succeeds, else false is returned.
 */
bool sensor_ioctl(sensor_t *sensor, sensor_command_t cmd, void *arg)
{
	bool result = false;

	switch (cmd) {
	case SENSOR_GET_RANGE:
		*((int16_t *)arg) = sensor->hal->range;
		result = true;
		break;

	case SENSOR_SET_RANGE:
	{
		int16_t const range = *(int16_t *)arg;

		int index;
		result
			= sensor_range_index(&(sensor->drv->caps), range,
				&index);

		if (result &&
				(result
					= SENSOR_DRV_CALL(sensor, ioctl, cmd,
						&index))) {
			sensor->hal->range = range;
		} else {
			sensor->err = SENSOR_ERR_PARAMS;
		}

		break;
	}

	case SENSOR_GET_BANDWIDTH:
		*((int16_t *)arg) = sensor->hal->bandwidth;
		result = true;
		break;

	case SENSOR_SET_BANDWIDTH:
	{
		int16_t const bandwidth_Hz = *(int16_t *)arg;

		int index;
		result = sensor_band_index(&(sensor->drv->caps), bandwidth_Hz,
				&index);

		if (result &&
				(result
					= SENSOR_DRV_CALL(sensor, ioctl, cmd,
						&index))) {
			sensor->hal->bandwidth = bandwidth_Hz;
		} else {
			sensor->err = SENSOR_ERR_PARAMS;
		}

		break;
	}

	case SENSOR_GET_SAMPLE_RATE:
		*((int16_t *)arg) = sensor->hal->sample_rate;
		result = true;
		break;

	case SENSOR_SET_SAMPLE_RATE:
	{
		int16_t const sample_Hz = *(int16_t *)arg;

		if (SENSOR_DRV_CALL(sensor, ioctl, cmd, arg)) {
			sensor->hal->sample_rate = sample_Hz;
			result = true;
		} else if (SENSOR_ERR_FUNCTION != sensor->err) {
			sensor->err = SENSOR_ERR_PARAMS;
		}

		break;
	}

	default:
		result = SENSOR_DRV_CALL(sensor, ioctl, cmd, arg);
		break;
	}

	return result;
}

/**
 * @brief Set tap event parameters
 *
 * @param   sensor  Address of an initialized sensor device descriptor.
 * @param   params  Address of a tap parameter structure.
 * @return  bool    true if the call succeeds, else false is returned.
 */
bool sensor_set_tap(sensor_t *sensor, sensor_tap_params_t *params)
{
	if (params) {
		return SENSOR_DRV_CALL(sensor, ioctl, SENSOR_SET_TAP, params);
	}

	return false;
}

/**
 * @brief Activate a sensor self-test function.
 *
 * @param   sensor    Address of an initialized sensor device descriptor.
 * @param   test_code Address of a device-specific numeric test code.
 * @param   arg       Device-specific self-test argument options.
 * @return  bool      true if the test succeeds, else false is returned.
 */
bool sensor_selftest(sensor_t *sensor, int *test_code, void *arg)
{
	bool result = SENSOR_DRV_CALL(sensor, selftest, test_code, arg);

	if ((false == result) && (SENSOR_ERR_FUNCTION != sensor->err)) {
		sensor->err = SENSOR_ERR_SELFTEST;
	}

	return result;
}

/**
 * @brief Atmel Software Framework Common Sensor API version
 *
 * This routine Gets the Sensor API version number and release date.
 *
 * @return The address of a null-terminated read-only version string.
 */
const char *sensor_api_version(void)
{
	static const char sensors_xplained_version []
		= "$Id: ATML ASF Sensor Service 1.7 $ $Revision: 29685 $ "
			"$Date: 2012-03-09 15:53:00 -0800 (Fri, 09 Mar 2012) $";

	return sensors_xplained_version;
}

/** @} */
