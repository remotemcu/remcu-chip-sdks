/**
 * \file
 *
 * \brief Bosch BMA220 3-axis accelerometer driver.
 *
 * This file contains functions for initializing and reading data
 * from a Bosch BMA220 3-axis accelerometer.
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
#include "bma220.h"
#include "bma_axis.inc.c"

static bool bma220_read(sensor_t *, sensor_read_t, sensor_data_t *);
static bool bma220_ioctl(sensor_t *, sensor_command_t, void *);
static bool bma220_selftest(sensor_t *, int *, void *);
static bool bma220_event(sensor_t *, sensor_event_t, sensor_event_callback_t *,
		bool);
static void bma220_isr(volatile void *);
static bool bma220_set_state(sensor_t *, sensor_state_t);

/** \brief Bosch BMA220 Range Table (milli-g, register value) */
static const sensor_map_t range_table [] = {
	{{ 2000}, RANGE_2G},
	{{ 4000}, RANGE_4G},
	{{ 8000}, RANGE_8G},
	{{16000}, RANGE_16G}
};

/** \brief Bosch BMA220 Bandwidth Table (hertz, register value) */
static const sensor_map_t band_table [] = {
	{{  32}, BANDWIDTH_32HZ},
	{{  64}, BANDWIDTH_64HZ},
	{{ 125}, BANDWIDTH_125HZ},
	{{ 250}, BANDWIDTH_250HZ},
	{{ 500}, BANDWIDTH_500HZ},
	{{1000}, BANDWIDTH_1000HZ}
};

/** Sensor Event Callback Descriptors (data=0, motion=1, low-g=2, high-g=3,
 *  tap=4) */
static sensor_event_callback_t event_cb[5] = {
	{.handler = default_event_handler},
	{.handler = default_event_handler},
	{.handler = default_event_handler},
	{.handler = default_event_handler},
	{.handler = default_event_handler}
};

/** \brief Sensor Event Registers */
static struct {
	bma_axis_t acc[3];               /**< Acceleration data */
	uint8_t unused[6];               /**< Unused register space */

	union {
		uint8_t status_byte[2];      /**< Status bytes */

		struct {                     /**< Status fields */
			uint8_t orient_int  : 1; /**< Orientation interrupt triggered */
			uint8_t orient      : 3; /**< Orientation with respect to gravity */
			uint8_t int_first_x : 1; /**< x-axis triggered any-motion interrupt */
			uint8_t int_first_y : 1; /**< y-axis triggered any-motion interrupt */
			uint8_t int_first_z : 1; /**< z-axis triggered any-motion interrupt */
			uint8_t int_sign    : 1; /**< Axis motion direction */

			uint8_t unused      : 3;
			uint8_t tt_int      : 1; /**< Tap criteria triggered */
			uint8_t low_int     : 1; /**< Low-g criteria triggered */
			uint8_t high_int    : 1; /**< High-g criteria triggered */
			uint8_t data_int    : 1; /**< New data interrupt triggered */
			uint8_t slope_int   : 1; /**< Slope criteria triggered */
		} status_field;
	};
} event_regs;

/**
 * @brief Burst Address Adjustment
 *
 * From SPI -> TWI use burst address increment in 2h steps.
 */
static uint8_t burst_increment;

#define REG_ADDR(reg) ((reg) * burst_increment)

/**
 * @brief Bosch BMA220 accelerometer driver initialization.
 *
 * This is the main initialization function for the BMA220 device.
 *
 * @param sensor    Address of a sensor device descriptor.
 * @param resvd     Reserved value.
 * @return bool     true if the call succeeds, else false is returned.
 */
bool bma220_init(sensor_t *sensor, int resvd)
{
	bool status = false;
	sensor_hal_t *const hal = sensor->hal;

	if (BMA220_ID_VAL == sensor_bus_get(hal, BMA220_CHIP_ID)) {
		/* Set the driver function table and capabilities pointer. */
		static const sensor_device_t bma220_device = {
			.func.read        = bma220_read,
			.func.ioctl       = bma220_ioctl,
			.func.selftest    = bma220_selftest,
			.func.event       = bma220_event,

			.caps.feature =     SENSOR_CAPS_3_AXIS     |
					SENSOR_CAPS_SELFTEST   |
					SENSOR_CAPS_HI_G_EVENT |
					SENSOR_CAPS_LO_G_EVENT |
					SENSOR_CAPS_TAP_EVENT  |
					SENSOR_CAPS_TILT_EVENT,

			.caps.vendor      = SENSOR_VENDOR_BOSCH,
			.caps.range_table = range_table,
			.caps.band_table  = band_table,
			.caps.range_count = ARRAYSIZE(range_table),
			.caps.band_count  = ARRAYSIZE(band_table),
			.caps.units       = SENSOR_UNITS_g0,
			.caps.scale       = SENSOR_SCALE_milli,
			.caps.name
				= "BMA220 Digital, triaxial acceleration sensor"
		};

		sensor->drv = &bma220_device;

		/* The local REG_ADDR() macro uses this to convert
		 * SPI to TWI bus addresses.
		 */
		burst_increment = (hal->bus.type == BUS_TYPE_TWI) ? 2 : 1;

		/* Set the driver (device) default range, bandwidth, &
		 * resolution.
		 *
		 * Per the BMA220 Datasheet the default range and bandwidth
		 * after device reset are +/- 2g and 1kHz respectively.
		 */
		bma220_set_state(sensor, SENSOR_STATE_RESET);

		hal->range      = 2000;
		hal->bandwidth  = 1000;
		hal->resolution = BMA220_DATA_RESOLUTION;
		hal->burst_addr = REG_ADDR(BMA220_X_AXIS_DATA);

		/* Install an interrupt handler. */
		if ((STATUS_OK == hal->bus.status) &&
				sensor_irq_connect(hal->mcu_sigint, bma220_isr,
				hal)) {
			status = true;
		}
	}

	return status;
}

/**
 * @brief Bosch BMA220 driver interrupt service routine.
 *
 * This is the common interrupt service routine for all enabled BMA220 interrupt
 * events.  Five different types of interrupts can be programmed.  All interrupt
 * criteria are combined and drive the interrupt pad with a Boolean \c OR
 * condition.
 *
 * Interrupt criteria are tested against values from the BMA220 digital filter
 * output.  All thresholds are scaled using the current device range.  Timings
 * for high and low acceleration are absolute values (1 LSB of HG_dur and LG_dur
 * registers corresponds to 1 millisecond, +/- 10%).  Timing for the any-motion
 * interrupt and alert detection are proportional to the bandwidth setting.
 *
 * This routine handles interrupts generated when low-g, high-g, any-motion,
 * alert, and new data criteria are satisfied and the corresponding event
 * notification is enabled in the device.
 *
 * The BMA220 device does not provide any way to definitively identify an
 * any-motion interrupt once it has occurred.  So, if a handler has been
 * installed for that event, it will always be called by this routine,
 * and the SENSOR_EVENT_MOTION indicator will be set in the event type field.
 *
 * @param arg       The address of the driver sensor_hal_t descriptor.
 * @return Nothing.
 */
static void bma220_isr(volatile void *arg)
{
	sensor_hal_t *const hal = (sensor_hal_t *)arg;

	hal->bus.no_wait = true;
	sensor_bus_read(hal, hal->burst_addr, &event_regs, sizeof(event_regs));
	hal->bus.no_wait = false;

	if (STATUS_OK == hal->bus.status) {
		static sensor_event_data_t event_data = {.data.scaled = true};

		event_data.data.timestamp = sensor_timestamp();
		event_data.event = SENSOR_EVENT_UNKNOWN;

		format_axis_data(hal, event_regs.acc, &(event_data.data));

		if (event_regs.status_field.data_int) {
			/* Service a data-ready interrupt. */
			event_data.event |= SENSOR_EVENT_NEW_DATA;
			(event_cb[0].handler)(&event_data, event_cb[0].arg);
		}

		if (event_regs.status_field.slope_int) {
			/* Service an "any-motion" (slope) interrupt. */
			event_data.event |= SENSOR_EVENT_MOTION;
			(event_cb[1].handler)(&event_data, event_cb[1].arg);
		}

		if (event_regs.status_field.low_int) {
			/* Service an interrupt on low-g criteria. */
			event_data.event |= SENSOR_EVENT_LOW_G;
			(event_cb[2].handler)(&event_data, event_cb[2].arg);
		}

		if (event_regs.status_field.high_int) {
			/* Service an interrupt on high-g criteria. */
			event_data.event |= SENSOR_EVENT_HIGH_G;
			(event_cb[3].handler)(&event_data, event_cb[3].arg);
		}

		if (event_regs.status_field.tt_int) {
			/* Service an interrupt on tap criteria. */
			event_data.event |= SENSOR_EVENT_TAP;
			(event_cb[4].handler)(&event_data, event_cb[4].arg);
		}
	}
}

/**
 * @brief Read BMA220 device ID and revision numbers.
 *
 * This function reads the accelerometer hardware identification registers
 * and returns these values in the specified data structure.
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param data      Address of sensor_data_t structure to return values.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma220_device_id(sensor_hal_t *hal, sensor_data_t *data)
{
	data->device.id = sensor_bus_get(hal, REG_ADDR(BMA220_CHIP_ID));
	data->device.version
		= sensor_bus_get(hal, REG_ADDR(BMA220_CHIP_VERSION));

	return true;
}

/**
 * @brief Read BMA220 acceleration data.
 *
 * This function obtains accelerometer data for all three axes of the Bosch
 * device.  The data is read from three device registers using a multi-byte
 * bus transfer.
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
static bool bma220_get_accel(sensor_hal_t *hal, sensor_data_t *data)
{
	size_t const count = sensor_bus_read(hal, hal->burst_addr,
			event_regs.acc, sizeof(event_regs.acc));

	format_axis_data(hal, event_regs.acc, data);

	return (count == sizeof(event_regs.acc));
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
static bool bma220_read(sensor_t *sensor, sensor_read_t type,
		sensor_data_t *data)
{
	sensor_hal_t *const hal = sensor->hal;

	switch (type) {
	case SENSOR_READ_ACCELERATION:
		return bma220_get_accel(hal, data);

	case SENSOR_READ_ID:
		return bma220_device_id(hal, data);

	default:
		sensor->err = SENSOR_ERR_FUNCTION;
		return false;
	}
}

/**
 * @brief Enable or disable the BMA220 sleep mode.
 *
 * This routine enables or disables the BMA220 sleep mode depending upon
 * the value of the \sleep parameter; a \true value enables sleep mode and
 * a \false value disables sleep mode by setting or clearing the 'sleep_en'
 * bit, respectively.
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param sleep     Set flag \true to enable sleep mode.
 * @return Nothing
 */
static inline void bma220_sleep_en(sensor_hal_t *hal, bool sleep)
{
	if (sleep) {
		sensor_reg_bitset(hal, BMA220_SLEEP_CONFIG, SLEEP_ENABLE);
	} else {
		sensor_reg_bitclear(hal, BMA220_SLEEP_CONFIG, SLEEP_ENABLE);
	}
}

/**
 * @brief Set the BMA220 execution mode.
 *
 * This routine sets a specified BMA220 execution state to one of the
 * following:
 *
 * SENSOR_STATE_SUSPEND or SENSOR_STATE_LOWEST_POWER
 *      The BMA220 can be put into a suspend mode to easily achieve a power
 *      consumption below 1uA.  In this mode all analog modules except for
 *      power-on reset will be disabled.  Only reads through the serial
 *      interface are supported during suspend.
 *
 *  SENSOR_STATE_SLEEP or SENSOR_STATE_LOW_POWER
 *      This option sets the BMA220 to a low-power mode.  In this mode, the
 *      device periodically wakes up, evaluates acceleration data with respect
 *      to interrupt criteria defined by the user and goes back to sleep if no
 *      interrupt has occurred using the following procedure:
 *
 *      1. Wake-up
 *
 *      2. Enable analog front-end and convert acceleration data until the
 *         low-pass filters have settled.
 *
 *      3. Enable interrupt controller and evaluate interrupt conditions.
 *         Once interrupt conditions are evaluated and no interrupt has
 *         occurred, the chip goes back to sleep.  If no interrupts are enabled,
 *         acceleration for all three axes are converted once before the chip
 *         goes back to sleep.
 *
 *      4. Sleep for the programmed duration.  Available sleep durations are
 *         2ms, 10ms, 25ms, 50ms, 100ms, 500ms, 1s, and 2s.
 *
 *  SENSOR_STATE_NORMAL or SENSOR_STATE_HIGHEST_POWER
 *      In normal mode the sensor IC data and status registers can be accessed
 *      without restriction.  The device current consumption is typically
 *      250 microamps in this state.
 *
 *  SENSOR_STATE_X_AXIS_STANDBY
 *  SENSOR_STATE_Y_AXIS_STANDBY
 *  SENSOR_STATE_Z_AXIS_STANDBY
 *      In order to optimize further power consumption of the BMA220, data
 *      evaluation of individual axes can be deactivated.
 *
 *  SENSOR_STATE_RESET
 *      This function resets the device and internal registers to the power-up
 *      default settings.
 *
 * @param sensor    Address of a sensor device descriptor.
 * @param mode      A specified sensor operational mode.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma220_set_state(sensor_t *sensor, sensor_state_t mode)
{
	sensor_hal_t *const hal = sensor->hal;

	/* Perform a state transition out of the previous mode into the new
	 * mode.
	 */
	switch (sensor->mod) {
	default:
		return false;

	case SENSOR_STATE_NORMAL:
	case SENSOR_STATE_HIGHEST_POWER:

		if ((SENSOR_STATE_SLEEP == mode) ||
				(SENSOR_STATE_LOW_POWER == mode)) {
			/* Enter sleep from normal mode. */
			bma220_sleep_en(hal, true);
		} else if ((SENSOR_STATE_SUSPEND == mode) ||
				(SENSOR_STATE_LOWEST_POWER == mode)) {
			/* Enter suspend mode from normal mode. */
			(void)sensor_bus_get(hal,
					REG_ADDR(BMA220_SUSPEND_MODE));
		}

		break;

	case SENSOR_STATE_SLEEP:
	case SENSOR_STATE_LOW_POWER:

		bma220_sleep_en(hal, false);

		if ((SENSOR_STATE_SUSPEND == mode) ||
				(SENSOR_STATE_LOWEST_POWER == mode)) {
			/* Enter suspend mode from sleep mode. */
			(void)sensor_bus_get(hal,
					REG_ADDR(BMA220_SUSPEND_MODE));
		}

		break;

	case SENSOR_STATE_SUSPEND:
	case SENSOR_STATE_LOWEST_POWER:

		/*
		 * If the BMA220 is in suspend mode, a subsequent read from
		 * the suspend register switches back to the previous state.
		 */
		(void)sensor_bus_get(hal, REG_ADDR(BMA220_SUSPEND_MODE));

		if ((SENSOR_STATE_SLEEP == mode) ||
				(SENSOR_STATE_LOW_POWER == mode)) {
			/* Enter sleep from suspend mode. */

			bma220_sleep_en(hal, true);
		}

		break;

	case SENSOR_STATE_RESET:

		/*
		 * Read the "softreset" register twice to activate then release
		 * the reset.
		 *
		 * \todo
		 * Update sensor device descriptor operational settings.
		 */
		(void)sensor_bus_get(hal, REG_ADDR(BMA220_SOFTRESET));
		(void)sensor_bus_get(hal, REG_ADDR(BMA220_SOFTRESET));
		break;
	}

	return true;
}

/**
 * @brief Set the BMA220 full scale acceleration range.
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param range     The index of a driver-specific range table entry.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma220_set_range(sensor_hal_t *hal, int16_t range)
{
	uint8_t const reg = REG_ADDR(BMA220_RANGE_SELFTEST);
	sensor_reg_fieldset(hal, reg, RANGE_FIELD,
			range_table[range].reserved_val);

	return true;
}

/**
 * @brief Set the BMA220 digital filter cut-off frequency
 *
 * @param hal      Address of an initialized sensor hardware descriptor.
 * @param band     The index of a driver-specific bandwidth table entry.
 * @return bool    true if the call succeeds, else false is returned.
 */
static bool bma220_set_bandwidth(sensor_hal_t *hal, int16_t band)
{
	uint8_t const reg = REG_ADDR(BMA220_BANDWIDTH_CONFIG);
	sensor_reg_fieldset(hal, reg, FILTER_CONFIG_FIELD,
			band_table[band].reserved_val);

	return true;
}

/**
 * @brief Set a BMA220 event threshold value
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param threshold Address of threshold descriptor.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma220_set_threshold
	(sensor_hal_t *hal, sensor_threshold_desc_t *threshold)
{
	int8_t const value = THRESHOLD_IN_G(threshold->value, hal->range);

	switch (threshold->type) {
	/* Invalid/unsupported threshold type. */
	default:
		return false;

	/* any-motion (slope) threshold */
	case SENSOR_THRESHOLD_MOTION:
	case SENSOR_THRESHOLD_TILT:
	{
		uint8_t const reg = REG_ADDR(BMA220_SLOPE_CONFIG);
		sensor_reg_fieldset(hal, reg, SLOPE_TH_FIELD, value);
	}
	break;

	/* tap/double-tap threshold */
	case SENSOR_THRESHOLD_TAP:
	{
		uint8_t const reg = REG_ADDR(BMA220_TAP_CONFIG);
		sensor_reg_fieldset(hal, reg, TT_TH_FIELD, value);
	}
	break;

	/* low-G threshold */
	case SENSOR_THRESHOLD_LOW_G:
	{
		uint8_t const reg = REG_ADDR(BMA220_HG_LG_THRESHOLD);
		sensor_reg_fieldset(hal, reg, LOW_TH_FIELD, value);
	}
	break;

	/* high-G threshold */
	case SENSOR_THRESHOLD_HIGH_G:
	{
		uint8_t const reg = REG_ADDR(BMA220_HG_LG_THRESHOLD);
		sensor_reg_fieldset(hal, reg, HIGH_TH_FIELD, value);
	}
	break;
	}

	return true;
}

/**
 * @brief Get a BMA220 event threshold value
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param threshold Address of threshold descriptor.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma220_get_threshold
	(sensor_hal_t *hal, sensor_threshold_desc_t *threshold)
{
	uint32_t val;

	switch (threshold->type) {
	/* Invalid/unsupported threshold type */
	default:
		return false;

	/* any-motion threshold */
	case SENSOR_THRESHOLD_MOTION:
	case SENSOR_THRESHOLD_TILT:
		val = sensor_bus_get(hal, REG_ADDR(BMA220_SLOPE_CONFIG));
		threshold->value = (int16_t)((val * hal->range * 16) / 2000);
		break;

	/* tap/double-tap threshold */
	case SENSOR_THRESHOLD_TAP:
		val = sensor_bus_get(hal, REG_ADDR(SENSOR_THRESHOLD_TAP));
		threshold->value = (int16_t)((val * hal->range) / 256);
		break;

	/* low-G threshold */
	case SENSOR_THRESHOLD_LOW_G:
		val = sensor_bus_get(hal, REG_ADDR(BMA220_HG_LG_THRESHOLD));
		threshold->value = (int16_t)((val * hal->range) / 256);
		break;

	/* high-G threshold */
	case SENSOR_THRESHOLD_HIGH_G:
		val = sensor_bus_get(hal, REG_ADDR(BMA220_HG_LG_THRESHOLD));
		threshold->value = (int16_t)((val * hal->range) / 256);
		break;
	}

	return true;
}

/**
 * @brief Run BMA220 self-tests.
 *
 * @param sensor    Address of an initialized sensor device descriptor.
 * @param test_code Address of a device-specific numeric test code.
 * @param arg       Device-specific self-test argument options.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma220_selftest(sensor_t *sensor, int *test_code, void *arg)
{
	bool result = false;

	if (SENSOR_TEST_DEFLECTION == *test_code) {
		/* \todo Execute BMA220 electrostatic deflection self-test. */
	}

	return result;
}

/**
 * @brief Enable or disable BMA220 sensor events.
 *
 * @param  sensor       Address of an initialized sensor device descriptor
 * @param  sensor_event Specifies the sensor event type
 * @param  callback     Application-defined event callback handler descriptor
 * @param  enable       Enable flag: true = enable event, false = disable event
 * @return bool         true if the call succeeds, else false is returned
 */
static bool bma220_event(sensor_t *sensor, sensor_event_t sensor_event,
		sensor_event_callback_t *callback, bool enable)
{
	sensor_hal_t *const hal = sensor->hal;

	bool status = false;

	uint8_t int_enable1 = sensor_bus_get(hal, REG_ADDR(BMA220_INT_ENABLE1));
	uint8_t int_enable2 = sensor_bus_get(hal, REG_ADDR(BMA220_INT_ENABLE2));

	if (sensor_event & SENSOR_EVENT_NEW_DATA) {
		if (callback) {
			event_cb[0] = *callback;
		}

		if (enable) {
			int_enable1 |= EN_DATA_FIELD;
		} else {
			int_enable1 &= ~EN_DATA_FIELD;
		}

		status = true;
	}

	if (sensor_event & SENSOR_EVENT_MOTION) {
		if (callback) {
			event_cb[1] = *callback;
		}

		if (enable) {
			/* Enable slope detection on x, y, and z axes using the
			 * default settings for the slope threshold & duration.
			 */
			int_enable1 |=  (EN_SLOPE_Z_FIELD | EN_SLOPE_Y_FIELD |
					EN_SLOPE_X_FIELD);
		} else {
			int_enable1 &= ~(EN_SLOPE_Z_FIELD | EN_SLOPE_Y_FIELD |
					EN_SLOPE_X_FIELD);
		}

		status = true;
	}

	if (sensor_event & SENSOR_EVENT_LOW_G) {
		if (callback) {
			event_cb[2] = *callback;
		}

		if (enable) {
			int_enable2 |=  EN_LOW_FIELD;
		} else {
			int_enable2 &= ~EN_LOW_FIELD;
		}

		status = true;
	}

	if (sensor_event & SENSOR_EVENT_HIGH_G) {
		if (callback) {
			event_cb[3] = *callback;
		}

		if (enable) {
			/* Enable high-g detection on x, y, and z axes using the
			 * default settings for the high-g duration & hysteresis.
			 */
			int_enable2 |=  (EN_HIGH_Z_FIELD | EN_HIGH_Y_FIELD |
					EN_HIGH_X_FIELD);
		} else {
			int_enable2 &= ~(EN_HIGH_Z_FIELD | EN_HIGH_Y_FIELD |
					EN_HIGH_X_FIELD);
		}

		status = true;
	}

	if (sensor_event & SENSOR_EVENT_TAP) {
		if (callback) {
			event_cb[4] = *callback;
		}

		if (enable) {
			int_enable1
				|=  (EN_TT_Z_FIELD | EN_TT_Y_FIELD |
					EN_TT_X_FIELD);
		} else {
			int_enable1
				&= ~(EN_TT_Z_FIELD | EN_TT_Y_FIELD |
					EN_TT_X_FIELD);
		}

		status = true;
	}

	/* It is recommended to reset the interrupt controller when interrupt
	 * settings are changed. Set the latched interrupt mode.
	 */
	int_enable2 |= (RESET_INT | LATCH_INT_FIELD);

	sensor_bus_put(hal, REG_ADDR(BMA220_INT_ENABLE1), int_enable1);
	sensor_bus_put(hal, REG_ADDR(BMA220_INT_ENABLE2), int_enable2);

	return status;
}

/**
 * @brief Set up tap detection parameters
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param params    Address of an initialized tap parameter structure.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma220_set_tap(sensor_hal_t *hal, sensor_tap_params_t *params)
{
	/* \todo Implement the device tap functions. */

	return false;
}

/**
 * @brief BMA220 ioctl control entry point
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param cmd       Command to execute
 * @param arg       Argument for command (varies)
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bma220_ioctl(sensor_t *sensor, sensor_command_t cmd, void *arg)
{
	sensor_hal_t *const hal = sensor->hal;
	sensor_data_t sample = {.scaled = true};

	switch (cmd) {
	default:
		sensor->err = SENSOR_ERR_UNSUPPORTED;
		return false;

	case SENSOR_SET_STATE:
	{
		sensor_state_t const mode = *((sensor_state_t *)arg);

		if ((mode != sensor->mod) && bma220_set_state(sensor, mode)) {
			sensor->mod = (mode == SENSOR_STATE_RESET)
					? SENSOR_STATE_NORMAL : mode;
			return true;
		} else {
			return false;
		}
	}

	case SENSOR_SET_RANGE:
		return bma220_set_range(hal, (uint16_t)*((int *)arg));

	case SENSOR_SET_BANDWIDTH:
		return bma220_set_bandwidth(hal, (uint16_t)*((int *)arg));

	case SENSOR_ENABLE_EVENT:
		return bma220_event(sensor, *((sensor_event_t *)arg), 0, true);

	case SENSOR_DISABLE_EVENT:
		return bma220_event(sensor, *((sensor_event_t *)arg), 0, false);

	case SENSOR_SET_THRESHOLD:
		return bma220_set_threshold(hal,
				(sensor_threshold_desc_t *)arg);

	case SENSOR_GET_THRESHOLD:
		return bma220_get_threshold(hal,
				(sensor_threshold_desc_t *)arg);

	case SENSOR_SET_TAP:
		return bma220_set_tap(hal, (sensor_tap_params_t *)arg);

	case SENSOR_READ_VECTOR:
		if (bma220_get_accel(hal, &sample)) {
			vector3_t *const pvec = (vector3_t *)arg;
			pvec->x = sample.axis.x;
			pvec->y = sample.axis.y;
			pvec->z = sample.axis.z;
			return true;
		} else {
			return false;
		}
	}
}
