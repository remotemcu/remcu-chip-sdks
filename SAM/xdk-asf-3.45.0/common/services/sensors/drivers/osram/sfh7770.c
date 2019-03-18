/**
 * \file
 *
 * \brief Osram SFH7770 light & proximity sensor driver.
 *
 * This file contains functions for initializing and reading data
 * from a Osram SFH7770 light & proximity sensor.
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
#include "sfh7770.h"

#define SFH7770_NVRAM_OFFSET    (0x18)

static bool sfh7770_read(sensor_t *, sensor_read_t, sensor_data_t *);
static bool sfh7770_ioctl(sensor_t *, sensor_command_t, void *);
static bool sfh7770_calibrate(sensor_t *, sensor_calibration_t, int, void *);
static bool sfh7770_event(sensor_t *, sensor_event_t, sensor_event_callback_t *,
		bool);
static void sfh7770_isr(volatile void *);

/** \brief Proximity sensor LED current table (mA, register field value) */
typedef struct {
	uint16_t level;     /**< Current in mA */
	uint8_t field_val;  /**< Register field value */
} current_level_t;

static const current_level_t current_table[] = {
	{  5, I_LED_5MA  }, { 10, I_LED_10MA },
	{ 20, I_LED_20MA }, { 50, I_LED_50MA },
	{100, I_LED_100MA}, {150, I_LED_150MA},
	{200, I_LED_200MA}
};

#define NUM_CURRENT_LEVELS (sizeof(current_table) / sizeof(current_level_t))

/** Sample rate table entry. */
typedef struct {
	uint16_t rate;      /**< Rate in Hz */
	uint8_t reg_val;    /**< Register value */
} sample_rate_t;

/** Light sensor sample rate table (Hz, reg field value) */
static const sample_rate_t light_rate_table[] = {
	{ 0, ALS_INTERVAL_2000MS},  /* "0" Hz = 2000ms interval */
	{ 1, ALS_INTERVAL_1000MS},  /* 1 Hz = 1000ms interval */
	{ 2, ALS_INTERVAL_500MS },  /* 2 Hz = 500ms interval */
	{ 5, ALS_INTERVAL_200MS },  /* 5 Hz = 200ms interval */
	{10, ALS_INTERVAL_100MS }   /* 10 Hz = 100ms interval */
};

#define NUM_LIGHT_RATES (sizeof(light_rate_table) / sizeof(sample_rate_t))

/** Proximity sensor sample rate table (Hz, reg field value) */
static const sample_rate_t prox_rate_table[] = {
	{  0, PS_INTERVAL_2000MS},  /* "0" Hz = 2000ms interval */
	{  1, PS_INTERVAL_1000MS},  /* 1 Hz = 1000ms interval */
	{  2, PS_INTERVAL_500MS },  /* 2 Hz = 500ms interval */
	{  5, PS_INTERVAL_200MS },  /* 5 Hz = 200ms interval */
	{ 10, PS_INTERVAL_100MS },  /* 10 Hz = 100ms interval */
	{ 14, PS_INTERVAL_70MS  },  /* 14 Hz = 70ms interval */
	{ 20, PS_INTERVAL_50MS  },  /* 20 Hz = 50ms interval */
	{ 33, PS_INTERVAL_30MS  },  /* 33 Hz = 30ms interval */
	{ 50, PS_INTERVAL_20MS  },  /* 50 Hz = 20ms interval */
	{100, PS_INTERVAL_10MS  }   /* 100 Hz = 10ms interval */
};

#define NUM_PROX_RATES (sizeof(prox_rate_table) / sizeof(sample_rate_t))

/** Sensor Event Callback table (proximity=0, low light=1, high light=2) */
static sensor_event_callback_t event_cb[3] = {
	{.handler = default_event_handler},
	{.handler = default_event_handler},
	{.handler = default_event_handler}
};

/** Event threshold value for hight light */
static uint16_t high_light_threshold;
/** Event threshold value for low light */
static uint16_t low_light_threshold;

/** Driver initialization flag */
static bool sfh7770_initialized = false;


/**
 * @brief Osram SFH7770 light & proximity sensor driver initialization.
 *
 * This is the main initialization function for the SFH7770 device.
 *
 * @param sensor    Address of a sensor device descriptor.
 * @param resvd     Reserved value.
 * @return bool     true if the call succeeds, else false is returned.
 */
bool sfh7770_init(sensor_t *sensor, int resvd)
{
	bool status = false;
	sensor_hal_t *const hal = sensor->hal;

	/* Proximity threshold values from NVRAM */
	struct {
		uint8_t ps_thr_led1;
		uint8_t ps_thr_led2;
		uint8_t ps_thr_led3;
	} prox_thresholds;

	/* Read and check part ID register */
	uint8_t part_id = sensor_bus_get(hal, SFH7770_PART_ID);

	if (part_id == (SFH7770_PART_ID_VAL | SFH7770_PART_REV_VAL)) {
		/* Set the driver function table and capabilities pointer. */
		static const sensor_device_t sfh7770_device = {
			.func.read           = sfh7770_read,
			.func.ioctl          = sfh7770_ioctl,
			.func.calibrate      = sfh7770_calibrate,
			.func.event          = sfh7770_event,
#if 0
			.caps.feature        = XXX
#endif
			.caps.vendor         = SENSOR_VENDOR_OSRAM,
			.caps.units          = SENSOR_UNITS_lux,
			.caps.scale          = SENSOR_SCALE_one,
			.caps.name = "SFH7770 Ambient Light & Proximity Sensor"
		};

		sensor->drv = &sfh7770_device;

		hal->resolution = SFH7770_DATA_RESOLUTION;

		/* Set the device burst read starting register address. */
		hal->burst_addr = SFH7770_ALS_DATA_LSB;

		/* Reset device during first init call */
		if (!sfh7770_initialized) {
			sensor_bus_put(hal, SFH7770_ALS_CONTROL,
					ALS_CONTROL_SW_RESET);
		}

		/* Init light sensor functions if specified */

		if (sensor->type & SENSOR_TYPE_LIGHT) {
			/* Set light sensor mode & interval */

			sensor_bus_put(hal, SFH7770_ALS_CONTROL,
					ALS_MODE_FREE_RUNNING);
			sensor_bus_put(hal, SFH7770_ALS_INTERVAL,
					ALS_INTERVAL_500MS);
		}

		/* Init proximity sensor functions if specified */
		if (sensor->type & SENSOR_TYPE_PROXIMITY) {
			/* Set proximity sensor mode & interval */
			sensor_bus_put(hal, SFH7770_PS_CONTROL,
					PS_MODE_FREE_RUNNING);
			sensor_bus_put(hal, SFH7770_PS_INTERVAL,
					PS_INTERVAL_100MS);

			/* Specify which LEDs are active */
			uint8_t const active_leds = LED_ACTIVE_ALL;
			/* XXX one of: */
			/* XXX  LED_ACTIVE_1    - LED1 only (default) */
			/* XXX  LED_ACTIVE_1_2  - LED1 & LED2 */
			/* XXX  LED_ACTIVE_1_3  - LED1 & LED3 */
			/* XXX  LED_ACTIVE_ALL  - all LEDs */

			/* Set LED current levels */
			uint8_t const led1_curr = I_LED_50MA; /* LED1 current */
			uint8_t const led2_curr = I_LED_50MA; /* LED2 current */
			uint8_t const led3_curr = I_LED_50MA; /* LED3 current */

			sensor_bus_put(hal, SFH7770_I_LED_1_2,
					(active_leds |
					(led2_curr <<
					I_LED2_SHIFT) | led1_curr));

			sensor_bus_put(hal, SFH7770_I_LED_3, led3_curr);

			/* Apply stored proximity thresholds from nvram */
			nvram_read(SFH7770_NVRAM_OFFSET, &prox_thresholds,
					sizeof(prox_thresholds));

			sensor_bus_write(hal, (SFH7770_PS_THR_LED1),
					&prox_thresholds,
					sizeof(prox_thresholds));
		}

		if (!sfh7770_initialized) {
			/* Set interrupt output polarity & mode(active-low,
			 * latched).
			 */
			sensor_bus_put(hal, SFH7770_INT_SET, 0);

			/* Set up interrupt handler */
			if (STATUS_OK == hal->bus.status) {
				sensor_irq_connect(hal->mcu_sigint, sfh7770_isr, hal);
			}
		}

		sfh7770_initialized = true;
		status = true;
	}

	return status;
}

/**
 * @brief Osram SFH7770 driver interrupt service routine.
 *
 * This is the common interrupt service routine for all enabled SFH7770
 * interrupt events.  Three different types of interrupts can be programmed:
 * high light level, low light level, and near proximity.  All share the
 * same interrupt pin and therefore the same ISR entry.
 *
 * @param arg       The address of the driver sensor_hal_t descriptor.
 * @return Nothing.
 */
static void sfh7770_isr(volatile void *arg)
{
	sensor_hal_t *const hal = (sensor_hal_t *)arg;

	struct {                    /* Interrupt register data */
		uint8_t als_data_lsb;   /* light meas data - least signif byte */
		uint8_t als_data_msb;   /* light meas data - most signif byte */
		uint8_t als_ps_status;  /* light & prox sensor status */
		uint8_t ps_data_led1;   /* proximity meas data - LED 1 */
		uint8_t ps_data_led2;   /* proximity meas data - LED 2 */
		uint8_t ps_data_led3;   /* proximity meas data - LED 3 */
		uint8_t int_set;        /* interrupt status */
	}
	regs;

	/* Do not wait for a busy bus when reading data. */
	hal->bus.no_wait = true;
	sensor_bus_read(hal, hal->burst_addr, (uint8_t *)&regs, sizeof(regs));
	hal->bus.no_wait = false;

	if (STATUS_OK == hal->bus.status) {
		static sensor_event_data_t event_data = {.data.scaled = true};

		event_data.data.timestamp = sensor_timestamp();
		event_data.event = SENSOR_EVENT_UNKNOWN;

		/*
		 * Determine the interrupt source then combine measurement
		 * register values into a single 16-bit measurement value.
		 */
		uint8_t const int_source = (regs.int_set & INT_SOURCE_MASK);

		uint16_t const light_level
			= ((regs.als_data_msb << 8) | regs.als_data_lsb);

		switch (int_source) {
		case INT_SOURCE_ALS:

			/* Determine if low or high light interrupt */
			if (light_level >= high_light_threshold) {
				event_data.event = SENSOR_EVENT_HIGH_LIGHT;
				event_data.data.light.value = light_level;

				(event_cb[2].handler)(&event_data,
						event_cb[2].arg);
			} else if (light_level <= low_light_threshold) {
				event_data.event = SENSOR_EVENT_LOW_LIGHT;
				event_data.data.light.value = light_level;

				(event_cb[1].handler)(&event_data,
						event_cb[1].arg);
			}

			return;

		case INT_SOURCE_LED1:
		case INT_SOURCE_LED2:
		case INT_SOURCE_LED3:

			event_data.event = SENSOR_EVENT_NEAR_PROXIMITY;

			if (int_source == INT_SOURCE_LED1) {
				event_data.channel = 1;
			} else if (int_source == INT_SOURCE_LED2) {
				event_data.channel = 2;
			} else { /* INT_SOURCE_LED3 */
				event_data.channel = 3;
			}

			/* Use internal device threshold status to
			 * determine scaled values.
			 */
			event_data.data.proximity.value[0]
				= (regs.als_ps_status & PS_LED1_THRESH) ?
					PROXIMITY_NEAR : PROXIMITY_NONE;

			event_data.data.proximity.value[1]
				= (regs.als_ps_status & PS_LED2_THRESH) ?
					PROXIMITY_NEAR : PROXIMITY_NONE;

			event_data.data.proximity.value[2]
				= (regs.als_ps_status & PS_LED3_THRESH) ?
					PROXIMITY_NEAR : PROXIMITY_NONE;

			(event_cb[0].handler)(&event_data, event_cb[0].arg);
		}
	}
}

/**
 * @brief Read SFH7770 device ID and revision numbers.
 *
 * This function reads the sensor hardware identification registers
 * and returns these values in the specified data structure.
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param data      Address of sensor_data_t structure to return values.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool sfh7770_device_id(sensor_hal_t *hal, sensor_data_t *data)
{
	uint8_t const part_id = sensor_bus_get(hal, SFH7770_PART_ID);

	data->device.id = (uint32_t)(part_id & PART_ID_MASK) >> PART_ID_SHIFT;
	data->device.version = (uint32_t)(part_id & PART_REV_MASK);

	return true;
}

/**
 * @brief Read SFH7770 light level data.
 *
 * This function reads the ambient light level data from the sensor
 * and places it in the user-provided sensor_data_t structure.
 *
 * @param sensor    Address of an initialized sensor device descriptor.
 * @param data      The address of a vector storing sensor measurement data.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool sfh7770_get_light(sensor_hal_t *hal, sensor_data_t *data)
{
	struct {
		uint8_t lsb;
		uint8_t msb;
	}
	light_data;

	/* Read and combine two light level data registers
	 *   NOTE:  LSB register must be read first!
	 */
	size_t const count = sensor_bus_read(hal, SFH7770_ALS_DATA_LSB,
			(uint8_t *)&light_data, sizeof(light_data));

	/* Device uses lux for internal values, so raw is the same as scaled */
	data->light.value = (uint32_t)((light_data.msb << 8) | light_data.lsb);

	return (count == sizeof(light_data));
}

/**
 * @brief Read SFH7770 proximity data.
 *
 * This function reads the proximity data from the three channels of the sensor
 * and places it in the user-provided sensor_data_t structure.  The
 * proximity value is not in standard units, so for "scaled" output
 * the values are encoded based on whether or not the proximity
 * reading exceeds the programmed threshold level for each channel (LED).
 *
 * The sensor has only a single threshold level, so only two possible
 * values are reported:  PROXIMITY_NEAR (if threshold is exceeded) or
 * PROXIMITY_NONE.
 *
 * @param sensor    Address of an initialized sensor device descriptor.
 * @param data      The address of a vector storing sensor measurement data.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool sfh7770_get_proximity(sensor_hal_t *hal, sensor_data_t *data)
{
	struct {
		uint8_t als_ps_status;
		uint8_t ps_data_led1;
		uint8_t ps_data_led2;
		uint8_t ps_data_led3;
	}
	regs;

	/* Read three LED proximity measurements + status */
	size_t const count = sensor_bus_read(hal, SFH7770_ALS_PS_STATUS,
			(uint8_t *)&regs, sizeof(regs));

	/* Fill in return values based on "scaled" or raw selection */
	if (data->scaled) {
		/* Use internal device threshold status to determine values */
		data->proximity.value[0]
			= (regs.als_ps_status & PS_LED1_THRESH) ?
				PROXIMITY_NEAR : PROXIMITY_NONE;

		data->proximity.value[1]
			= (regs.als_ps_status & PS_LED2_THRESH) ?
				PROXIMITY_NEAR : PROXIMITY_NONE;

		data->proximity.value[2]
			= (regs.als_ps_status & PS_LED3_THRESH) ?
				PROXIMITY_NEAR : PROXIMITY_NONE;
	} else {
		/* Use internal raw values */
		data->proximity.value[0] = (int32_t)regs.ps_data_led1;
		data->proximity.value[1] = (int32_t)regs.ps_data_led2;
		data->proximity.value[2] = (int32_t)regs.ps_data_led3;
	}

	return (count == sizeof(regs));
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
static bool sfh7770_read(sensor_t *sensor, sensor_read_t type,
		sensor_data_t *data)
{
	sensor_hal_t *const hal = sensor->hal;

	switch (type) {
	case SENSOR_READ_LIGHT:
		return sfh7770_get_light(hal, data);

	case SENSOR_READ_PROXIMITY:
		return sfh7770_get_proximity(hal, data);

	case SENSOR_READ_ID:
		return sfh7770_device_id(hal, data);

	default:
		sensor->err = SENSOR_ERR_FUNCTION;
		return false;
	}
}

/**
 * @brief Set the SFH7770 execution mode.
 *
 * This routine sets a specified SFH7770 execution state to one of the
 * following:
 *
 * SENSOR_STATE_SLEEP:
 *      Setting the sleep mode puts the specific sensor unit (light or
 *      proximity) in standby mode, in which no measurements are made.
 *
 *  SENSOR_STATE_NORMAL:
 *      Setting the sleep mode puts the specific sensor unit (light or
 *      proximity) in continuous measurement mode.
 *
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param type      The operational type of the sensor (light or proximity)
 * @param state     A specified sensor operational state.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool sfh7770_set_state(sensor_hal_t *hal, sensor_type_t type,
		sensor_state_t state)
{
	switch (state) {
	case SENSOR_STATE_SLEEP:
		if (type == SENSOR_TYPE_LIGHT) { /* if light */
			sensor_bus_put(hal, SFH7770_ALS_CONTROL,
					ALS_MODE_STANDBY);
		} else {                        /* if proximity */
			sensor_bus_put(hal, SFH7770_PS_CONTROL,
					PS_MODE_STANDBY);
		}

		break;

	case SENSOR_STATE_NORMAL:
		if (type == SENSOR_TYPE_LIGHT) { /* if light */
			sensor_bus_put(hal, SFH7770_ALS_CONTROL,
					ALS_MODE_FREE_RUNNING);
		} else {                        /* if proximity */
			sensor_bus_put(hal, SFH7770_PS_CONTROL,
					PS_MODE_FREE_RUNNING);
		}

		break;

	default:
		return false;
	}

	return true;
}

/**
 * @brief Set event threshold value
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param channel   Channel (LED) number to set threshold
 * @param threshold Address of threshold descriptor.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool sfh7770_set_threshold(sensor_hal_t *hal, int16_t channel,
		sensor_threshold_desc_t *threshold)
{
	struct {
		uint8_t lsb;
		uint8_t msb;
	}
	reg_thresh;

	uint8_t led_count = 0;
	uint8_t index;
	uint8_t value = threshold->value;

	bool result = false;

	switch (threshold->type) {  /* check threshold type */
	case SENSOR_THRESHOLD_NEAR_PROXIMITY:   /* high (near) prox. threshold
		                                 **/

		/* Write to sensor register based on current channel (LED
		 * selection)
		 */
		switch (channel) {
		case SENSOR_CHANNEL_ALL:    /* "channel -1" = all 3 LEDs */
			led_count = 3;
			index = 0;
			break;

		case 1:
		case 2:
		case 3:
			led_count = 1;
			index = channel - 1;
			break;

		default:
			return false;   /* invalid channel selection */
		}

		while (led_count--) {
			sensor_bus_put(hal, (SFH7770_PS_THR_LED1 + index),
					(uint8_t)threshold->value);

			/* Write to nvram */
			nvram_write((SFH7770_NVRAM_OFFSET + index), &value, 1);
			++index;
		}

		result = true;
		break;

	case SENSOR_THRESHOLD_LOW_LIGHT:         /* lower light level threshold
		                                  **/
		reg_thresh.lsb = (uint8_t)(threshold->value & 0xFF);
		reg_thresh.msb = (uint8_t)((threshold->value >> 8) & 0xFF);
		low_light_threshold = (uint16_t)threshold->value;
		if (sensor_bus_write(hal, SFH7770_ALS_LO_THR_LSB, &reg_thresh,
				sizeof(reg_thresh)) == sizeof(reg_thresh)) {
			result = true;
		}

		break;

	case SENSOR_THRESHOLD_HIGH_LIGHT:        /* upper light level threshold
		                                  **/
		reg_thresh.lsb = (uint8_t)(threshold->value & 0xFF);
		reg_thresh.msb = (uint8_t)((threshold->value >> 8) & 0xFF);
		high_light_threshold = (uint16_t)threshold->value;
		if (sensor_bus_write(hal, SFH7770_ALS_UP_THR_LSB, &reg_thresh,
				sizeof(reg_thresh)) == sizeof(reg_thresh)) {
			result = true;
		}

		break;

	default:
		/* Invalid/unsupported threshold type - do nothing, return false */
		break;
	}

	return result;
}

/**
 * @brief Get event threshold value
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param channel   Channel (LED) number to set threshold
 * @param threshold Address of threshold descriptor.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool sfh7770_get_threshold(sensor_hal_t *hal, int16_t channel,
		sensor_threshold_desc_t *threshold)
{
	bool result = false;

	switch (threshold->type) {  /* check threshold type */
	case SENSOR_THRESHOLD_NEAR_PROXIMITY: /* proximity threshold */
		if (channel == SENSOR_CHANNEL_ALL) {
			/* if "all channels", just use chan #1 value */
			channel = 1;
		}

		if ((channel >= 1) && (channel <= 3)) {
			/* Read corresponding register for LED channel */
			threshold->value = (uint16_t)sensor_bus_get(hal,
					(SFH7770_PS_THR_LED1 + channel - 1));
			result = true;
		}

		break;

	case SENSOR_THRESHOLD_LOW_LIGHT:  /* low light level threshold */
		threshold->value = low_light_threshold;
		result = true;
		break;

	case SENSOR_THRESHOLD_HIGH_LIGHT: /* high light level threshold */
		threshold->value = high_light_threshold;
		result = true;
		break;

	default:
		/* Invalid/unsupported threshold type - do nothing, return false */
		break;
	}

	return result;
}

/**
 * @brief Set sensor sample rate
 *
 * @param hal         Address of an initialized sensor hardware descriptor.
 * @param type        Active mode of the sensor (i.e. light or proximity)
 * @param rate_hz     Sample rate in Hz
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool sfh7770_set_rate(sensor_hal_t *hal, sensor_type_t type,
		uint16_t rate_hz)
{
	bool status = false;

	if (type & SENSOR_TYPE_LIGHT) {
		for (int i = 0; i < NUM_LIGHT_RATES; ++i) {
			if (light_rate_table[i].rate == rate_hz) {
				sensor_bus_put(hal, SFH7770_ALS_INTERVAL,
						light_rate_table[i].reg_val);
				status = true;
				break;
			}
		}
	}

	if (type & SENSOR_TYPE_PROXIMITY) {
		for (int i = 0; i < NUM_PROX_RATES; ++i) {
			if (prox_rate_table[i].rate == rate_hz) {
				sensor_bus_put(hal, SFH7770_PS_INTERVAL,
						prox_rate_table[i].reg_val);
				status = true;
				break;
			}
		}
	}

	return status;
}

/**
 * @brief Set proximity LED current level
 *
 * @param hal         Address of an initialized sensor hardware descriptor.
 * @param channel     Channel (LED) number to set current
 * @param curr_levels Address of an array of current levels (1 per LED)
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool sfh7770_set_current(sensor_hal_t *hal, int16_t channel,
		uint16_t *level_mA)
{
	uint8_t curr_setting;

	bool status = false;

	/* Find current level in table */
	for (int i = 0; i < NUM_CURRENT_LEVELS; ++i) {
		if (current_table[i].level == *level_mA) {
			curr_setting = current_table[i].field_val;
			status = true;
			break;
		}
	}

	if (status == true) {   /* if entry was found in table */
		uint8_t reg_val;

		if (channel == SENSOR_CHANNEL_ALL) {
			reg_val = sensor_bus_get(hal, SFH7770_I_LED_1_2);
			reg_val &= ~(I_LED1_MASK | I_LED2_MASK);
			reg_val
				|= (curr_setting |
					(curr_setting << I_LED2_SHIFT));
			sensor_bus_put(hal, SFH7770_I_LED_1_2, reg_val);
			sensor_bus_put(hal, SFH7770_I_LED_3, curr_setting);
		} else if ((channel == 1) || (channel == 2)) {
			reg_val = sensor_bus_get(hal, SFH7770_I_LED_1_2);
			if (channel == 1) {
				reg_val &= ~I_LED1_MASK;
				reg_val |= curr_setting;
			} else {
				reg_val &= ~I_LED2_MASK;
				reg_val |= (curr_setting << I_LED2_SHIFT);
			}

			sensor_bus_put(hal, SFH7770_I_LED_1_2, reg_val);
		} else if (channel == 3) {
			sensor_bus_put(hal, SFH7770_I_LED_3, curr_setting);
		} else {        /* invalid channel selected */
			status = false;
		}
	}

	return status;
}

/**
 * @brief Enable or disable SFH7770 sensor events.
 *
 * @param  sensor    Address of an initialized sensor device descriptor
 * @param  callback  Application-defined event callback handler descriptor
 * @param  enable    Enable flag: true = enable event, false = disable event
 * @return bool      true if the call succeeds, else false is returned
 */
static bool sfh7770_event(sensor_t *sensor, sensor_event_t sensor_event,
		sensor_event_callback_t *callback, bool enable)
{
	sensor_hal_t *const hal = sensor->hal;

	bool status = false;

	uint8_t int_set = sensor_bus_get(hal, SFH7770_INT_SET);

	if (sensor_event & SENSOR_EVENT_NEAR_PROXIMITY) {
		if (callback) {
			event_cb[0] = *callback;
		}

		if (enable) {
			int_set |= INT_MODE_PS;
		} else {
			int_set &= ~INT_MODE_PS;
		}

		status = true;
	}

	if (sensor_event & SENSOR_EVENT_LOW_LIGHT) {
		if (callback) {
			event_cb[1] = *callback;
		}

		if (enable) {
			int_set |= INT_MODE_ALS;
		} else {
			int_set &= ~INT_MODE_ALS;
		}

		status = true;
	}

	if (sensor_event & SENSOR_EVENT_HIGH_LIGHT) {
		if (callback) {
			event_cb[2] = *callback;
		}

		if (enable) {
			int_set |= INT_MODE_ALS;
		} else {
			int_set &= ~INT_MODE_ALS;
		}

		status = true;
	}

	/* Write the new setting then read to clear. */
	sensor_bus_put(hal, SFH7770_INT_SET, int_set);

	int_set = sensor_bus_get(hal, SFH7770_INT_SET);

	return status;
}

/**
 * @brief SFH7770 ioctl control entry point
 *
 * @param  hal   Address of an initialized sensor hardware descriptor.
 * @param  cmd   Command to execute
 * @param  arg   Argument for command (varies)
 * @return bool  true if the call succeeds, else false is returned.
 */
static bool sfh7770_ioctl(sensor_t *sensor, sensor_command_t cmd, void *arg)
{
	sensor_hal_t *const hal = sensor->hal;

	bool status = false;

	switch (cmd) {
	case SENSOR_SET_STATE:
		status
			= sfh7770_set_state(hal, sensor->type,
				*((sensor_state_t *)arg));
		break;

	case SENSOR_ENABLE_EVENT:
		status
			= sfh7770_event(sensor, *((sensor_event_t *)arg), 0,
				true);
		break;

	case SENSOR_DISABLE_EVENT:
		status = sfh7770_event(sensor, *((sensor_event_t *)arg), 0,
				false);
		break;

	case SENSOR_SET_THRESHOLD:
		status = sfh7770_set_threshold(hal, sensor->channel,
				(sensor_threshold_desc_t *)arg);
		break;

	case SENSOR_GET_THRESHOLD:
		status = sfh7770_get_threshold(hal, sensor->channel,
				(sensor_threshold_desc_t *)arg);
		break;

	case SENSOR_SET_SAMPLE_RATE:
		status
			= sfh7770_set_rate(hal, sensor->type,
				*((uint16_t *)arg));
		break;

	case SENSOR_SET_CURRENT:
		status = sfh7770_set_current(hal, sensor->channel,
				(uint16_t *)arg);
		break;

	default:
		sensor->err = SENSOR_ERR_UNSUPPORTED;
		break;
	}

	return status;
}

/**
 * @brief Calibrate proximity sensor detection thresholds
 *
 * This function measures the proximity sensor output in 3 different steps,
 * one for each channel in the device.  This function should be called when
 * a sample object has been placed at the desired distance from the device
 * to define the threshold for near-proximity detection.  The measured
 * proximity sensor value for each channel is stored in non-volatile memory.
 * These thresholds will later be used to set the threshold during the
 * device initialization sequence.
 *
 * This routine must be called 3 times total, with the "step" parameter
 * indicating what stage of the calibration is being performed (i.e. which
 * channel of the proximity sensor).  This multi-step mechanism allows
 * the application to prompt for physical placement of the object to be
 * detected before this routine is called.
 *
 * @param sensor     Address of an initialized sensor device descriptor.
 * @param calib_type The address of a vector storing sensor axis data.
 * @param step       The calibration stage number [1,3].
 * @param info       Unimplemented (ignored) parameter.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool sfh7770_calibrate(sensor_t *sensor,
		sensor_calibration_t calib_type, int step, void *info)
{
	sensor_hal_t *const hal = sensor->hal;

	static uint8_t prox_data[3];
	uint8_t read_data[3];

	/* Validate the specified calibration type */
	if (calib_type != MANUAL_CALIBRATE) {
		sensor->err = SENSOR_ERR_PARAMS;
		return false;
	}

	/* Read proximity sensor for individual channel based on step number. */
	switch (step) {
	case 1:
		prox_data[0] = sensor_bus_get(hal, SFH7770_PS_DATA_LED1);
		break;

	case 2:
		prox_data[1] = sensor_bus_get(hal, SFH7770_PS_DATA_LED2);
		break;

	case 3:
		prox_data[2] = sensor_bus_get(hal, SFH7770_PS_DATA_LED3);

		/* Write data */
		nvram_write((SFH7770_NVRAM_OFFSET), prox_data,
				sizeof(prox_data));

		/* Read back data and confirm it was written correctly */
		nvram_read(SFH7770_NVRAM_OFFSET, read_data, sizeof(read_data));

		if (memcmp(prox_data, read_data, sizeof(prox_data))) {
			sensor->err = SENSOR_ERR_IO;
			return false;
		}

		/* Apply stored proximity thresholds from nvram */
		sensor_bus_write(hal, (SFH7770_PS_THR_LED1), read_data,
				sizeof(read_data));

		break;

	/* Any other step number is invalid */
	default:
		sensor->err = SENSOR_ERR_PARAMS;
		return false;
	}

	return true;
}
