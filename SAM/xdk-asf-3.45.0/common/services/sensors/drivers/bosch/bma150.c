/**
 * \file
 *
 * \brief Bosch BMA150 3-axis accelerometer driver.
 *
 * This file contains functions for initializing and reading data
 * from a Bosch BMA150 3-axis accelerometer.
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
#include "bma150.h"
#include "bma_axis.inc.c"

static bool bma150_read(sensor_t *, sensor_read_t, sensor_data_t *);
static bool bma150_ioctl(sensor_t *, sensor_command_t, void *);
static bool bma150_selftest(sensor_t *, int *, void *);
static bool bma150_event(sensor_t *, sensor_event_t, sensor_event_callback_t *,
		bool);
static void bma150_isr(volatile void *);

/** \brief Bosch BMA150 Range Table (milli-g, register value) */
static const sensor_map_t range_table [] = {
	{{2000}, RANGE_2G},
	{{4000}, RANGE_4G},
	{{8000}, RANGE_8G}
};

/** \brief Bosch BMA150 Bandwidth Table (hertz, register value) */
static const sensor_map_t band_table [] = {
	{{  25}, BANDWIDTH_25HZ  },
	{{  50}, BANDWIDTH_50HZ  },
	{{ 100}, BANDWIDTH_100HZ },
	{{ 190}, BANDWIDTH_190HZ },
	{{ 375}, BANDWIDTH_375HZ },
	{{ 750}, BANDWIDTH_750HZ },
	{{1500}, BANDWIDTH_1500HZ}
};

/** Sensor Event Callback Descriptors (data=0, motion=1, low-g=2, high-g=3) */
static sensor_event_callback_t event_cb[4] = {
	{.handler = default_event_handler},
	{.handler = default_event_handler},
	{.handler = default_event_handler},
	{.handler = default_event_handler}
};

/** \brief Sensor Event Registers */
static struct {
	bma_axis_t acc[3];               /**< Acceleration data */
	int8_t temp;                     /**< Temperature data */

	union {
		uint8_t status_byte;         /**< Status registers Byte */

		struct {                     /**< Status registers fields */
			uint8_t st_result   : 1; /**< Self-test 0 result */
			uint8_t unused      : 2;
			uint8_t alert_phase : 1; /**< Device in alert mode */
			uint8_t LG_latched  : 1; /**< Low-g criteria issued (latch) */
			uint8_t HG_latched  : 1; /**< High-g criteria issued (latch) */
			uint8_t LG_issued   : 1; /**< Low-g criteria issued */
			uint8_t HG_issued   : 1; /**< High-g criteria issued */
		} status_field;
	};
} event_regs;

/**
 * @brief Bosch BMA150 accelerometer driver initialization.
 *
 * This is the main initialization function for the BMA150 device.
 *
 * @param sensor    Address of a sensor device descriptor.
 * @param resvd     Reserved value.
 * @return bool     true if the call succeeds, else false is returned.
 */
bool bma150_init(sensor_t *sensor, int resvd)
{
	bool status = false;
	sensor_hal_t *const hal = sensor->hal;

	if (BMA150_ID_VAL == sensor_bus_get(hal, BMA150_CHIP_ID)) {
		/* Set the driver function table and capabilities pointer. */
		static const sensor_device_t bma150_device = {
			.func.read        = bma150_read,
			.func.ioctl       = bma150_ioctl,
			.func.selftest    = bma150_selftest,
			.func.event       = bma150_event,

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
			.caps.name
				= "BMA150 Digital, triaxial acceleration sensor"
		};

		sensor->drv = &bma150_device;

		/* Set the driver (device) default range, bandwidth, &
		 * resolution.
		 *
		 * Per the BMA150 Datasheet the default range and bandwidth
		 * after device reset are +/- 4g and 1500 Hz. respectively.  So,
		 * if that's the desired initialization state for this device,
		 *then
		 * don't use software to set these values in the driver _init()
		 * routine.
		 */
		hal->range      = 4000;
		hal->bandwidth  = 1500;
		hal->resolution = BMA150_DATA_RESOLUTION;

		/* Set the device burst read base address. */
		hal->burst_addr = BMA150_ACC_X_LSB;

		/* Initialize the control registers. */
		sensor_bus_put(hal, BMA150_CTRL1, 0);
		sensor_bus_put(hal, BMA150_CTRL2, 0);
		sensor_bus_put(hal, BMA150_CTRL5, 0);

		/* Set the interrupt handler. */
		if ((STATUS_OK == hal->bus.status) &&
				sensor_irq_connect(hal->mcu_sigint, bma150_isr, hal)) {
			status = true;
		}
	}

	return status;
}

/**
 * @brief Bosch BMA150 driver interrupt service routine.
 *
 * This is the common interrupt service routine for all enabled BMA150 interrupt
 * events.  Five different types of interrupts can be programmed.  All interrupt
 * criteria are combined and drive the interrupt pad with a Boolean \c OR
 * condition.
 *
 * Interrupt events may be set to an inconsistent state by device EEPROM
 * changes.  BMA150 interrupts should be disabled at the host microcontroller
 * when device EEPROM writes are performed.
 *
 * Interrupt criteria are tested against values from the BMA150 digital filter
 * output.  All thresholds are scaled using the current device range.  Timings
 * for high and low acceleration are absolute values (1 LSB of HG_dur and LG_dur
 * registers corresponds to 1 millisecond, +/- 10%).  Timing for the any-motion
 * interrupt and alert detection are proportional to the bandwidth setting.
 *
 * This routine handles interrupts generated when low-g, high-g, any-motion,
 * alert, and new data criteria are satisfied and the corresponding event
 * notification is enabled in the device.
 *
 * The BMA150 device does not provide any way to definitively identify an
 * any-motion interrupt once it has occurred.  So, if a handler has been
 * installed for that event, it will always be called by this routine,
 * and the SENSOR_EVENT_MOTION indicator will be set in the event type field.
 *
 * @param  arg      The address of the driver sensor_hal_t descriptor.
 * @return Nothing.
 */
static void bma150_isr(volatile void *arg)
{
	sensor_hal_t *const hal = (sensor_hal_t *)arg;

	hal->bus.no_wait = true;
	sensor_bus_read(hal, hal->burst_addr, &event_regs, sizeof(event_regs));
	hal->bus.no_wait = false;

	if (STATUS_OK == hal->bus.status) {
		static sensor_event_data_t event_data = {.data.scaled = true};

		event_data.data.timestamp = sensor_timestamp();
		event_data.event = SENSOR_EVENT_MOTION;

		/*
		 * Test the "new data" bit in the sample outputs prior to
		 * converting axis data to sign extended 10-bit values and
		 * buffering the result.
		 */
		bool const new_data = event_regs.acc[2].field.new_data;

		format_axis_data(hal, event_regs.acc, &(event_data.data));

		if (event_regs.status_field.LG_issued) {
			event_data.event = SENSOR_EVENT_LOW_G;
			(event_cb[2].handler)(&event_data, event_cb[2].arg);
		} else if (event_regs.status_field.HG_issued) {
			event_data.event = SENSOR_EVENT_HIGH_G;
			(event_cb[3].handler)(&event_data, event_cb[3].arg);
		} else if (new_data) {
			event_data.event = SENSOR_EVENT_NEW_DATA;
			(event_cb[0].handler)(&event_data, event_cb[0].arg);
		} else {
			/* Assume the any-motion event triggered the interrupt. */
			(event_cb[1].handler)(&event_data, event_cb[1].arg);
		}
	}
}

/**
 * @brief Read BMA150 device ID and revision numbers.
 *
 * This function reads the accelerometer hardware identification registers
 * and returns these values in the specified data structure.
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param data      Address of sensor_data_t structure to return values.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma150_device_id(sensor_hal_t *hal, sensor_data_t *data)
{
	data->device.id = sensor_bus_get(hal, BMA150_CHIP_ID);
	data->device.version = sensor_bus_get(hal, BMA150_CHIP_VERSION);

	return true;
}

/**
 * @brief Read BMA150 acceleration data.
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
 * @param sensor    Address of an initialized sensor device descriptor.
 * @param data      The address of a vector storing sensor axis data.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma150_get_accel(sensor_hal_t *hal, sensor_data_t *data)
{
	size_t const count = sensor_bus_read(hal, hal->burst_addr,
			event_regs.acc, sizeof(event_regs.acc));

	format_axis_data(hal, event_regs.acc, data);

	return (count == sizeof(event_regs.acc));
}

/**
 * @brief Read BMA150 integrated temperature sensor data.
 *
 * @param sensor    Address of an initialized sensor device descriptor.
 * @param data      The address where temperature samples are returned.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma150_get_temperature(sensor_hal_t *hal, sensor_data_t *data)
{
	int8_t temp_data = (int8_t)sensor_bus_get(hal, BMA150_TEMP);

	if (data->scaled) {
		/*
		 * Per the Bosch BMA150 datasheet, temperature data resolution
		 * is about 0.5 C/LSB.
		 */
		data->temperature.value = BMA150_TEMP_OFFSET + (temp_data / 2);
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
static bool bma150_read(sensor_t *sensor, sensor_read_t type,
		sensor_data_t *data)
{
	sensor_hal_t *const hal = sensor->hal;

	switch (type) {
	case SENSOR_READ_ACCELERATION:
		return bma150_get_accel(hal, data);

	case SENSOR_READ_TEMPERATURE:
		return bma150_get_temperature(hal, data);

	case SENSOR_READ_ID:
		return bma150_device_id(hal, data);

	default:
		sensor->err = SENSOR_ERR_FUNCTION;
		return false;
	}
}

/**
 * @brief Set the BMA150 execution mode.
 *
 * This routine sets a specified BMA150 execution state to one of the
 * following:
 *
 * SENSOR_STATE_SLEEP or SENSOR_STATE_LOWEST_POWER
 *      Setting the sleep mode puts the BMA150 into a very low power state in
 *      which no communication with the sensor IC is possible.  The current
 *      consumption in sleep mode is about 1 microamp.
 *
 *      In case of a soft-reset, it is recommended to do the reset after
 *      switching from sleep to operational mode.  In case a soft-reset is
 *      activated during sleep mode, it can take up to 30ms until normal
 *      operation has resumed.
 *
 *  SENSOR_STATE_LOW_POWER
 *      This option sets the BMA150 to a low power "wake-up" mode that triggers
 *      a system wake-up (interrupt output to master) when motion is detected.
 *      In this mode, the device periodically evaluates acceleration data with
 *      respect to interrupt criteria defined by the user.
 *
 *      Typical current consumption in wake-up mode is estimated as follows:
 * @code
 *                        i_DD * t_active + i_DDsm * wake_up_pause
 *      i_self_wake_up = ------------------------------------------
 *                                 t_active + wake_up_pause
 * @endcode
 *      with approximation:
 * @code
 *      t_active = 1ms + 0.333ms * [(4 * 750/bandwidth) + (1500/bandwidth) * n]
 * @endcode
 *      with parameters:
 * @code
 *      i_DD            Normal mode current (200 microamp)
 *      i_DDsm          Sleep mode current  (1 microamp)
 *      wake_up_pause   Wake-up pause setting
 *      n               Number of data points in any-motion logic (n=0 for
 *                      high-g and low-g threshold, n=3 for any-motion)
 *      bandwidth       bandwidth @ settings 1500 through 25 Hz.
 * @endcode
 *  SENSOR_STATE_NORMAL or SENSOR_STATE_HIGHEST_POWER
 *      In normal mode the sensor IC data and status registers can be accessed
 *      without restriction.  The device current consumption is 200 microamps
 *      in this state.
 *
 *  SENSOR_STATE_RESET
 *      This function resets the device and internal registers to the power-up
 *      default settings.
 *
 * In the wake-up mode, the BMA150 automatically switches from sleep mode to
 * normal mode after a delay defined by a programmable \c wake_up_pause value.
 * After transitioning from sleep to normal mode, acceleration data acquisition
 * and interrupt verification are performed.  The sensor automatically returns
 * to sleep mode again if no interrupt criteria are satisfied.
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param state     A specified sensor operational state.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma150_set_state(sensor_hal_t *hal, sensor_state_t state)
{
	switch (state) {
	case SENSOR_STATE_SLEEP:
	case SENSOR_STATE_LOWEST_POWER:

		sensor_reg_bitclear(hal, BMA150_CTRL5, CTRL5_WAKE_UP);
		sensor_reg_bitset(hal, BMA150_CTRL1, CTRL1_SLEEP);
		break;

	case SENSOR_STATE_LOW_POWER:

		sensor_reg_bitclear(hal, BMA150_CTRL1, CTRL1_SLEEP);
		sensor_reg_bitset(hal, BMA150_CTRL5, CTRL5_WAKE_UP);
		break;

	case SENSOR_STATE_NORMAL:
	case SENSOR_STATE_HIGHEST_POWER:

		sensor_reg_bitclear(hal, BMA150_CTRL1, CTRL1_SLEEP);
		sensor_reg_bitclear(hal, BMA150_CTRL5, CTRL5_WAKE_UP);
		break;

	case SENSOR_STATE_RESET:

		/*
		 * \todo
		 *
		 * Update sensor device descriptor operational settings.
		 */
		sensor_reg_bitclear(hal, BMA150_CTRL1, CTRL1_SLEEP);
		sensor_bus_put(hal, BMA150_CTRL1, CTRL1_SOFT_RESET);
		break;

	default:
		return false;
	}

	return true;
}

/**
 * @brief Set the BMA150 full scale acceleration range.
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param range     The index o a driver-specific range table entry.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma150_set_range(sensor_hal_t *hal, int16_t range)
{
	/*
	 * After changing the full scale range it takes (1/(2 * bandwidth))
	 * to overwrite the data registers with filtered data according to
	 * the selected bandwidth.
	 */
	uint8_t const ctrl4 = ~(CTRL4_RANGE)&sensor_bus_get(hal, BMA150_CTRL4);
	sensor_bus_put(hal, BMA150_CTRL4,
			ctrl4 | range_table[range].reserved_val);

	return true;
}

/**
 * @brief Set the BMA150 ADC output data bandwidth
 *
 * @param hal      Address of an initialized sensor hardware descriptor.
 * @param band     The index of a driver-specific bandwidth table entry.
 * @return bool    true if the call succeeds, else false is returned.
 */
static bool bma150_set_bandwidth(sensor_hal_t *hal, int16_t band)
{
	/* Set the device sample frequency. */
	uint8_t const ctrl4 = ~(CTRL4_BANDWIDTH)&
			sensor_bus_get(hal, BMA150_CTRL4);

	sensor_bus_put(hal, BMA150_CTRL4, ctrl4 |
			band_table[band].reserved_val);

	return true;
}

/**
 * @brief Set event threshold value
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param threshold Address of threshold descriptor.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma150_set_threshold
	(sensor_hal_t *hal, sensor_threshold_desc_t *threshold)
{
	uint32_t const value = threshold->value;
	uint32_t regval;

	switch (threshold->type) {
	default:            /* Invalid/unsupported threshold */
		return false;

	case SENSOR_THRESHOLD_MOTION:           /* any-motion threshold */

		regval = (value * 2000) / ((uint32_t)hal->range * 16);
		sensor_bus_put(hal, BMA150_ANY_MOTION_THRES, (uint8_t)regval);
		break;

	case SENSOR_THRESHOLD_LOW_G:            /* low-G threshold */

		regval = (value * 256) / hal->range;
		sensor_bus_put(hal, BMA150_LG_THRES, (uint8_t)regval);
		break;

	case SENSOR_THRESHOLD_HIGH_G:           /* high-G threshold */

		regval = (value * 256) / hal->range;
		sensor_bus_put(hal, BMA150_HG_THRES, (uint8_t)regval);
		break;
	}

	return (STATUS_OK == hal->bus.status);
}

/**
 * @brief Get event threshold value
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param threshold Address of threshold descriptor.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma150_get_threshold
	(sensor_hal_t *hal, sensor_threshold_desc_t *threshold)
{
	uint32_t regval;
	bool result = false;

	switch (threshold->type) {
	case SENSOR_THRESHOLD_MOTION:           /* any-motion threshold */
		regval = (uint32_t)sensor_bus_get(hal, BMA150_ANY_MOTION_THRES);
		threshold->value = (int16_t)((regval * hal->range * 16) / 2000);
		result = true;
		break;

	case SENSOR_THRESHOLD_LOW_G:            /* low-G threshold */
		regval = (uint32_t)sensor_bus_get(hal, BMA150_LG_THRES);
		threshold->value = (int16_t)((regval * hal->range) / 256);
		result = true;
		break;

	case SENSOR_THRESHOLD_HIGH_G:           /* high-G threshold */
		regval = (uint32_t)sensor_bus_get(hal, BMA150_HG_THRES);
		threshold->value = (int16_t)((regval * hal->range) / 256);
		result = true;
		break;

	default:
		/* Invalid/unsupported threshold type - do nothing, return false. */
		break;
	}

	return result;
}

/**
 * @brief Run BMA150 self-tests.
 *
 * @param sensor    Address of an initialized sensor device descriptor.
 * @param test_code Address of a device-specific numeric test code.
 * @param arg       Device-specific self-test argument options.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma150_selftest(sensor_t *sensor, int *test_code, void *arg)
{
	sensor_hal_t *const hal = sensor->hal;
	bool result = false;

	if (SENSOR_TEST_DEFLECTION == *test_code) {
		/* Execute BMA150 self-test 0; electrostatic deflection test. */
		sensor_reg_bitset(hal, BMA150_CTRL1, CTRL1_SELF_TEST_0);

		result = (STATUS1_ST_RESULT &
				sensor_bus_get(hal, BMA150_STATUS1))
				? true : false;

		sensor_reg_bitclear(hal, BMA150_CTRL1, CTRL1_SELF_TEST_0);
	} else if (SENSOR_TEST_INTERRUPT == *test_code) {
		/* Execute BMA150 self-test 1; interrupt to MCU test. */
		sensor_reg_bitset(hal, BMA150_CTRL1, CTRL1_SELF_TEST_1);
	}

	return result;
}

/**
 * @brief Enable or disable BMA150 sensor events.
 *
 * @param  sensor       Address of an initialized sensor device descriptor
 * @param  sensor_event Specifies the sensor event type
 * @param  callback     Application-defined event callback handler descriptor
 * @param  enable       Enable flag: true = enable event, false = disable event
 * @return bool         true if the call succeeds, else false is returned
 */
static bool bma150_event(sensor_t *sensor, sensor_event_t sensor_event,
		sensor_event_callback_t *callback, bool enable)
{
	sensor_hal_t *const hal = sensor->hal;

	bool status = false;

	uint8_t ctrl2_value = sensor_bus_get(hal, BMA150_CTRL2);
	uint8_t ctrl5_value = sensor_bus_get(hal, BMA150_CTRL5);

	if (sensor_event & SENSOR_EVENT_NEW_DATA) {
		if (callback) {
			event_cb[0] = *callback;
		}

		if (enable) {
			ctrl5_value |= CTRL5_NEW_DATA_INT;
		} else {
			ctrl5_value &= ~CTRL5_NEW_DATA_INT;
		}

		status = true;
	}

	if (sensor_event & SENSOR_EVENT_MOTION) {
		if (callback) {
			event_cb[1] = *callback;
		}

		if (enable) {
			/* Do not enable both alert & motion. */
			ctrl2_value &= ~CTRL2_ALERT;
			ctrl2_value |= CTRL2_ANY_MOTION;
			ctrl5_value |= CTRL5_ENABLE_ADV_INT;
		} else {
			ctrl2_value &= ~CTRL2_ANY_MOTION;
			ctrl5_value &= ~CTRL5_ENABLE_ADV_INT;
		}

		status = true;
	}

	if (sensor_event & SENSOR_EVENT_LOW_G) {
		if (callback) {
			event_cb[2] = *callback;
		}

		if (enable) {
			ctrl2_value |= CTRL2_ENABLE_LG;
		} else {
			ctrl2_value &= ~CTRL2_ENABLE_LG;
		}

		status = true;
	}

	if (sensor_event & SENSOR_EVENT_HIGH_G) {
		if (callback) {
			event_cb[3] = *callback;
		}

		if (enable) {
			ctrl2_value |= CTRL2_ENABLE_HG;
		} else {
			ctrl2_value &= ~CTRL2_ENABLE_HG;
		}

		status = true;
	}

	sensor_bus_put(hal, BMA150_CTRL2, ctrl2_value);
	sensor_bus_put(hal, BMA150_CTRL5, ctrl5_value);

	return status;
}

/**
 * @brief BMA150 ioctl control entry point
 *
 * @param   hal     Address of an initialized sensor hardware descriptor.
 * @param   cmd     Command to execute
 * @param   arg     Argument for command (varies)
 * @return  bool    true if the call succeeds, else false is returned.
 */
static bool bma150_ioctl(sensor_t *sensor, sensor_command_t cmd, void *arg)
{
	sensor_hal_t *const hal = sensor->hal;
	sensor_data_t sample = {.scaled = true};

	switch (cmd) {
	case SENSOR_SET_STATE:
		return bma150_set_state(hal, *((sensor_state_t *)arg));

	case SENSOR_SET_RANGE:
		return bma150_set_range(hal, (uint16_t)*((int *)arg));

	case SENSOR_SET_BANDWIDTH:
		return bma150_set_bandwidth(hal, (uint16_t)*((int *)arg));

	case SENSOR_ENABLE_EVENT:
		return bma150_event(sensor, *((sensor_event_t *)arg), 0, true);

	case SENSOR_DISABLE_EVENT:
		return bma150_event(sensor, *((sensor_event_t *)arg), 0, false);

	case SENSOR_SET_THRESHOLD:
		return bma150_set_threshold(hal,
				(sensor_threshold_desc_t *)arg);

	case SENSOR_GET_THRESHOLD:
		return bma150_get_threshold(hal,
				(sensor_threshold_desc_t *)arg);

	case SENSOR_READ_VECTOR:
		if (bma150_get_accel(hal, &sample)) {
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
