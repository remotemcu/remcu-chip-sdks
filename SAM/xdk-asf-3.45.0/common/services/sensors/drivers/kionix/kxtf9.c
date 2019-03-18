/**
 * \file
 *
 * \brief Kionix KXTF9 3-axis accelerometer.
 *
 * This file contains functions for initializing and reading data
 * from a Kionix KXTF9 3-axis accelerometer.
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
#include "kxtf9.h"

static bool kxtf9_read(sensor_t *, sensor_read_t, sensor_data_t *);
static bool kxtf9_event(sensor_t *, sensor_event_t, sensor_event_callback_t *,
		bool);
static bool kxtf9_ioctl(sensor_t *, sensor_command_t, void *);
static void kxtf9_isr(volatile void *);
static bool kxtf9_get_accel(sensor_hal_t *, sensor_data_t *);

/** \brief Kionix KXTF9 Range Table (milli-g, register value) */
static const sensor_map_t range_table [] = {
	{{2000}, CTRL_REG1_GSEL_2G},
	{{4000}, CTRL_REG1_GSEL_4G},
	{{8000}, CTRL_REG1_GSEL_8G}
};

enum {
	INDEX_2G,
	INDEX_4G,
	INDEX_8G,
};

/**
 * @brief Kionix KXTF9 Bandwidth Table (hertz, register value)
 * LPF bandwidth on the KXTF9 is 1/2 ODR
 */
static const sensor_map_t band_table [] = {
	{{6}, DATA_CTRL_ODR_12_5HZ},     /* 6  = (int) 12.5/2 */
	{{12}, DATA_CTRL_ODR_25HZ},      /* 12 = (int) 25/2   */
	{{25}, DATA_CTRL_ODR_50HZ},
	{{50}, DATA_CTRL_ODR_100HZ},
	{{100}, DATA_CTRL_ODR_200HZ},
	{{200}, DATA_CTRL_ODR_400HZ},
	{{400}, DATA_CTRL_ODR_800HZ}
};

enum {
	ODR_INDEX_13HZ,
	ODR_INDEX_25HZ,
	ODR_INDEX_50HZ,
	ODR_INDEX_100HZ,
	ODR_INDEX_200HZ,
	ODR_INDEX_400HZ,
	ODR_INDEX_800HZ,
};

/** \brief Sensor Event Callbacks (data=0, motion=1, tap=2, tilt=3) */

static sensor_event_callback_t event_cb[4] = {
	{.handler = default_event_handler},
	{.handler = default_event_handler},
	{.handler = default_event_handler},
	{.handler = default_event_handler}
};

/** \brief KXTF9 Axis Data Format
 *
 * The 2's-complement 12-bit axis data samples split across two contiguous
 * 8-bit device locations where the lower address in the device register space
 * stores the 4 least significant bits (in bits 4:7) and the next higher address
 * stores the 8 most significant bits of the axis data.
 */
typedef union {
	int16_t word;

	struct {
		uint8_t lsb;
		int8_t msb;
	} byte;

	struct {
		uint16_t acc_lsb  : 4;
		uint16_t unused   : 4;
		int16_t acc_msb  : 8;
	} field;
} kxtf9_axis_t;

/**
 * @brief Construct a signed value from a raw axis sample.
 *
 * The KXTF9 returns 2's-complement 12-bit axis values stored within a
 * 16-bit word.
 *
 * @param   axis    A kxtf9_axis_t type storing a raw sensor axis sample.
 * @return  The sign extended axis sample value.
 */
static inline int16_t kxtf9_axis_val(const kxtf9_axis_t axis)
{
#if UC3     /* big-endian */
	return (axis.field.acc_msb << 4) | (axis.field.acc_lsb);

#elif XMEGA /* little-endian */
	return (axis.word >> 4);

#endif
}

/**
 * @brief Kionix KXTF9 accelerometer driver initialization.
 *
 * This is the main initialization function for the KXTF9 device.
 *
 * @param sensor    Address of a sensor device descriptor.
 * @param resvd     Reserved value.
 * @return bool     true if the call succeeds, else false is returned.
 */
bool kxtf9_init(sensor_t *sensor, int resvd)
{
	bool status = false;

	sensor_hal_t *const hal = sensor->hal;

	/* Set the driver function table and capabilities pointer. */
	static const sensor_device_t kxtf9_device = {
		.func.read            = kxtf9_read,
		.func.event           = kxtf9_event,
		.func.ioctl           = kxtf9_ioctl,

		.caps.feature         = SENSOR_CAPS_3_AXIS     |
				SENSOR_CAPS_SELFTEST   |
				SENSOR_CAPS_HI_G_EVENT |
				SENSOR_CAPS_LO_G_EVENT |
				SENSOR_CAPS_TAP_EVENT  |
				SENSOR_CAPS_TILT_EVENT,

		.caps.vendor          = SENSOR_VENDOR_KIONIX,
		.caps.range_table     = range_table,
		.caps.band_table      = band_table,
		.caps.range_count     = ARRAYSIZE(range_table),
		.caps.band_count      = ARRAYSIZE(band_table),
		.caps.units           = SENSOR_UNITS_g0,
		.caps.scale           = SENSOR_SCALE_milli,
		.caps.name = "Kionix KXTF9 digital 3-axis accelerometer"
	};

	sensor->drv = &kxtf9_device;

	uint8_t const id_val = sensor_bus_get(hal, KXTF9_WHO_AM_I);

	if ((id_val == KXTF9_ID_VAL) || (id_val == KXTI9_ID_VAL)) {
		/* Set the driver (device) default range, bandwidth,
		 * and resolution.
		 */
		hal->range      = range_table[INDEX_2G].range_units;
		hal->bandwidth  = band_table[ODR_INDEX_50HZ].bandwidth_Hz;
		hal->sample_rate = band_table[ODR_INDEX_50HZ].bandwidth_Hz * 2;
		hal->resolution = KXTF9_DATA_RESOLUTION;

		/* Wake up the device in standby mode. */
		sensor_bus_put(hal, KXTF9_CTRL_REG1, 0);

		/* Reset RAM and set the following data rates:
		 *
		 *  400 Hz double tap data rate
		 *  6.3 Hz tilt position data rate
		 *  50  Hz wake-up function data rate
		 */
		sensor_bus_put(hal, KXTF9_CTRL_REG3,
				CTRL_REG3_SRST       | CTRL_REG3_OTP_6_3HZ |
				CTRL_REG3_OTDT_400HZ | CTRL_REG3_OWUF_50HZ);

		/* Wait for the reset bit to clear. */
		do {
			delay_ms(RESET_DELAY_MSEC);
		} while (sensor_bus_get(hal, KXTF9_CTRL_REG3) & CTRL_REG3_SRST);

		/* Enable interrupt pin, active high, latching */
		sensor_bus_put(hal, KXTF9_INT_CTRL_REG1,
				INT_CTRL_REG1_IEN | INT_CTRL_REG1_IEA |
				INT_CTRL_REG1_IEL);

		/* Set the output data rate. */
		sensor_bus_put(hal, KXTF9_DATA_CTRL_REG, DATA_CTRL_ODR_200HZ);

		/* Set the wake-up timer. */
		/* Write "Kionix recommended values" for timer init. */
		sensor_bus_put(hal, KXTF9_TILT_TIMER, TILT_TIMER_INIT);
		sensor_bus_put(hal, KXTF9_WUF_TIMER, WUF_TIMER_INIT);

		/* Clear any outstanding interrupt signal. */
		(void)sensor_bus_get(hal, KXTF9_INT_REL);

		/* Enable the device (power up state) and 12-bit mode. */
		sensor_bus_put(hal, KXTF9_CTRL_REG1,
				CTRL_REG1_PC1 | CTRL_REG1_RES);
		delay_ms(START_DELAY_MSEC);

		status = (STATUS_OK == hal->bus.status);

		/* Set the device burst read base address. */
		hal->burst_addr = KXTF9_XOUT_L;

		/* Set up interrupt handler */
		if ((STATUS_OK == hal->bus.status) &&
				sensor_irq_connect(hal->mcu_sigint, kxtf9_isr,
				hal)) {
			status = true;
		}
	}

	return status;
}

/**
 * @brief Kionix KXTF9 driver interrupt service routine.
 *
 * This is the common interrupt service routine for all enabled KXTF9 interrupt
 * events.  Several different types of interrupts can be programmed.  All
 * interrupt criteria are combined and drive the interrupt pad with a
 * Boolean \c OR condition.
 *
 * This routine handles interrupts generated when motion, tap, double-tap,
 * tilt, and new data criteria are satisfied and the corresponding event
 * notification is enabled in the device.
 *
 * @param arg       The address of the driver sensor_hal_t hardware descriptor.
 * @return Nothing.
 */
static void kxtf9_isr(volatile void *arg)
{
	sensor_hal_t *const hal = (sensor_hal_t *)arg;

	struct {                    /* KXTF9 Interrupt Register Information */
		uint8_t int_src_reg1;   /* interrupt source reg 1 */
		uint8_t int_src_reg2;   /* interrupt source reg 2 */
		uint8_t gap1;           /*  <gap - no register at this address> */
		uint8_t status_reg;     /* status register */
		uint8_t gap2;           /*  <gap - no register at this address> */
		uint8_t int_rel;        /* interrupt release - read to clear */
	}
	regs;

	/* Read interrupt info registers to clear the interrupt status. */
	hal->bus.no_wait = true;
	sensor_bus_read(hal, KXTF9_INT_SRC_REG1, (uint8_t *)&regs,
			sizeof(regs));
	hal->bus.no_wait = false;

	/* Confirm that the interrupt condition occurred. */
	if ((STATUS_OK != hal->bus.status) || !(regs.status_reg & STATUS_INT)) {
		return;
	}

	static sensor_event_data_t event_data = {.data.scaled = true};

	event_data.data.timestamp = sensor_timestamp();
	event_data.event = SENSOR_EVENT_UNKNOWN;

	kxtf9_get_accel(hal, &(event_data.data));

	/* Test for a new data ready interrupt. */
	if (regs.int_src_reg2 & INT_SRC_REG2_DRDY) {
		event_data.event |= SENSOR_EVENT_NEW_DATA;
		(event_cb[0].handler)(&event_data, event_cb[0].arg);
	}

	/* Test for a motion interrupt. */
	if (regs.int_src_reg2 & INT_SRC_REG2_WUFS) {
		event_data.event |= SENSOR_EVENT_MOTION;
		(event_cb[1].handler)(&event_data, event_cb[1].arg);
	}

	/* Test for a tilt position interrupt. */
	if (regs.int_src_reg2 & INT_SRC_REG2_TPS) {
		event_data.event |= SENSOR_EVENT_TILT;
		event_data.data.value[0] = sensor_bus_get(hal,
				KXTF9_TILT_POS_CUR);
		(event_cb[3].handler)(&event_data, event_cb[3].arg);
	}

	/* Test for a tap detection interrupt. */
	uint8_t const tap_bits = (regs.int_src_reg2 & INT_SRC_REG2_TD);

	if (tap_bits != 0) {
		event_data.event |= SENSOR_EVENT_TAP;

		if (tap_bits == INT_SRC_REG2_TD_SINGLE) {
			event_data.data.tap.count = 1;
		} else if (tap_bits == INT_SRC_REG2_TD_DOUBLE) {
			event_data.data.tap.count = 2;
		}

		/* Determine the tap axis & direction. */
		switch (regs.int_src_reg1) {
		case INT_SRC_REG1_TRI:
			event_data.data.tap.axis = SENSOR_TAP_AXIS_X;
			event_data.data.tap.direction
				= SENSOR_TAP_DIRECTION_POS;
			break;

		case INT_SRC_REG1_TLE:
			event_data.data.tap.axis = SENSOR_TAP_AXIS_X;
			event_data.data.tap.direction
				= SENSOR_TAP_DIRECTION_NEG;
			break;

		case INT_SRC_REG1_TUP:
			event_data.data.tap.axis = SENSOR_TAP_AXIS_Y;
			event_data.data.tap.direction
				= SENSOR_TAP_DIRECTION_POS;
			break;

		case INT_SRC_REG1_TDO:
			event_data.data.tap.axis = SENSOR_TAP_AXIS_Y;
			event_data.data.tap.direction
				= SENSOR_TAP_DIRECTION_NEG;
			break;

		case INT_SRC_REG1_TFU:
			event_data.data.tap.axis = SENSOR_TAP_AXIS_Z;
			event_data.data.tap.direction
				= SENSOR_TAP_DIRECTION_POS;
			break;

		case INT_SRC_REG1_TFD:
			event_data.data.tap.axis = SENSOR_TAP_AXIS_Z;
			event_data.data.tap.direction
				= SENSOR_TAP_DIRECTION_NEG;
			break;

		default:
			event_data.data.tap.axis = SENSOR_TAP_AXIS_UNKNOWN;
			event_data.data.tap.direction
				= SENSOR_TAP_DIRECTION_UNKNOWN;
			break;
		}

		(event_cb[2].handler)(&event_data, event_cb[2].arg);
	}
}

/**
 * @brief Put sensor in standby mode
 *
 * This function places the KXTF9 device in standby mode. This can
 * be done to save power, or to allow modification of various control
 * registers. This function will return the value of the CTRL_REG1
 * register prior to entering standby mode, so that it can be restored.
 *
 * @param  hal         Address of an initialized sensor hardware descriptor.
 * @return uint8_t     Previous contents of CTRL_REG1 register
 */
static uint8_t kxtf9_standby(sensor_hal_t *hal)
{
	/* Get th current control register value. */
	uint8_t const ctrl_reg1 = sensor_bus_get(hal, KXTF9_CTRL_REG1);

	/* Put device in standby mode to change settings. */
	sensor_bus_put(hal, KXTF9_CTRL_REG1, (ctrl_reg1 & ~CTRL_REG1_PC1));

	return ctrl_reg1;
}

/**
 * @brief Resume sensor standby/run mode
 *
 * This function restores the KXTF9 device to standby or normal mode, based
 * on the register value parameter.  This can be used to restore the
 * mode to the state previously saved during a kxtf9_standby() call.
 *
 * @param  hal         Address of an initialized sensor hardware descriptor.
 * @return uint8_t     Previous contents of CTRL_REG1 register
 */
static void kxtf9_resume(sensor_hal_t *hal, uint8_t regval)
{
	/* Write input value to control register */
	sensor_bus_put(hal, KXTF9_CTRL_REG1, regval);
}

/**
 * @brief Read accelerometer device ID and revision numbers.
 *
 * This function reads the accelerometer hardware identification registers
 * and returns these values to the addresses specified in the function
 * parameters.
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param id        An address where the device ID is returned.
 * @param ver       An address where the device version is returned.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool kxtf9_device_id(sensor_hal_t *hal, sensor_data_t *data)
{
	data->device.id = (uint32_t)sensor_bus_get(hal, KXTF9_WHO_AM_I);
	data->device.version = 0;

	return true;
}

/**
 * @brief Get accelerometer data.
 *
 * This function obtains accelerometer data for all three axes of the Kionix
 * device.  The data is read from six device registers using a multi-byte
 * bus transfer.  The 10-bit raw results are then assembled from the two
 * register values for each axis, including extending the sign bit, to
 * form a signed 32-bit value.
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param data      The address of a vector storing sensor axis data.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool kxtf9_get_accel(sensor_hal_t *hal, sensor_data_t *data)
{
	kxtf9_axis_t axis[3];

	size_t const count = sensor_bus_read(hal, hal->burst_addr,
			(uint8_t *)axis, sizeof(axis));

	/* Assign axis values based on device orientation. */
	int32_t const x_val = hal->orientation.x.sign *
			kxtf9_axis_val(axis[hal->orientation.x.axis]);

	int32_t const y_val = hal->orientation.y.sign *
			kxtf9_axis_val(axis[hal->orientation.y.axis]);

	int32_t const z_val = hal->orientation.z.sign *
			kxtf9_axis_val(axis[hal->orientation.z.axis]);

	/* Convert raw sensor sample to engineering units if requested. */
	if (data->scaled) {
		data->axis.x = raw_to_scaled(hal, x_val);
		data->axis.y = raw_to_scaled(hal, y_val);
		data->axis.z = raw_to_scaled(hal, z_val);
	} else {
		data->axis.x = x_val;
		data->axis.y = y_val;
		data->axis.z = z_val;
	}

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
static bool kxtf9_read(sensor_t *sensor, sensor_read_t type,
		sensor_data_t *data)
{
	sensor_hal_t *const hal = sensor->hal;

	switch (type) {
	case SENSOR_READ_ACCELERATION:
		return kxtf9_get_accel(hal, data);

	case SENSOR_READ_ID:
		return kxtf9_device_id(hal, data);

	default:
		sensor->err = SENSOR_ERR_FUNCTION;
		return false;
	}
}

/**
 * @brief  Set the accelerometer operation state
 *
 * @param hal      Address of an initialized sensor hardware descriptor.
 * @param
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool kxtf9_set_state(sensor_hal_t *hal, sensor_state_t state)
{
	switch (state) {
	case SENSOR_STATE_SLEEP:
	case SENSOR_STATE_SUSPEND:
	case SENSOR_STATE_LOWEST_POWER:
	case SENSOR_STATE_POWER_DOWN:
		(void)kxtf9_standby(hal);
		break;

	case SENSOR_STATE_NORMAL:
	case SENSOR_STATE_HIGH_POWER:
	case SENSOR_STATE_HIGHEST_POWER:
		sensor_reg_bitset(hal, KXTF9_CTRL_REG1, CTRL_REG1_PC1);
		break;

	case SENSOR_STATE_RESET:
		sensor_reg_bitset(hal, KXTF9_CTRL_REG3, CTRL_REG3_SRST);

		/* wait for reset bit to clear */
		do {
			delay_ms(RESET_DELAY_MSEC);
		} while (sensor_bus_get(hal, KXTF9_CTRL_REG3) & CTRL_REG3_SRST);
		break;

	default:
		return false;
	}

	return true;
}

/**
 * @brief  Set the g range for the accelerometer
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param range     The index of a driver-specific range table entry.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool kxtf9_set_range(sensor_hal_t *hal, int16_t range)
{
	/* Enter standby mode, get the current mode,
	 * and clear the g-range select bits.
	 */
	uint8_t const ctrl_reg1 = ~(CTRL_REG1_GSEL)&kxtf9_standby(hal);

	sensor_bus_put(hal, KXTF9_CTRL_REG1,
			ctrl_reg1 | range_table[range].reserved_val);

	return true;
}

/**
 * @brief  Set the sample bandwidth for the accelerometer
 *
 * @param  hal      Address of an initialized sensor hardware descriptor.
 * @param  index    The index of a driver-specific bandwidth table entry.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool kxtf9_set_bandwidth(sensor_hal_t *hal, int16_t index)
{
	if (hal->bandwidth == band_table[index].bandwidth_Hz) {
		return true;
	}

	hal->bandwidth = band_table[index].bandwidth_Hz;
	hal->sample_rate = hal->bandwidth * 2;

	uint8_t const data_ctrl = ~(DATA_CTRL_ODR)&
			sensor_bus_get(hal, KXTF9_DATA_CTRL_REG);

	sensor_bus_put(hal, KXTF9_DATA_CTRL_REG,
			data_ctrl | band_table[index].reserved_val);

	kxtf9_resume(hal, kxtf9_standby(hal));

	return true;
}

/**
 * @brief  Set the sample rate for the accelerometer
 *
 * @param  hal      Address of an initialized sensor hardware descriptor.
 * @param  sr       the sample rate desired in HZ
 *
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool kxtf9_set_sample_rate(sensor_hal_t *hal, int16_t sr)
{
	int index = -1;

	for (int ii = 0; ii < ARRAYSIZE(band_table); ++ii) {
		if (band_table[ii].bandwidth_Hz == sr) {
			index = ii;
			break;
		}
	}

	if (index == -1) {
		return false;
	} else {
		return kxtf9_set_bandwidth(hal, index);
	}
}

/**
 * @brief Set event threshold value
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @param threshold Type of threshold to be set
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool kxtf9_set_threshold(sensor_hal_t *hal,
		sensor_threshold_desc_t *threshold)
{
	if (threshold->type == SENSOR_THRESHOLD_MOTION) {
		uint8_t const ctrl_reg1 = kxtf9_standby(hal);

		sensor_bus_put(hal, KXTF9_WUF_THRESH,
				(threshold->value * 16) / 1000);

		kxtf9_resume(hal, ctrl_reg1);

		return true;

		/* \todo Set tap threshold? */
	}

	return false;
}

/**
 * @brief Get event threshold value
 *
 * @param  hal       Address of an initialized sensor hardware descriptor.
 * @param  threshold Address of threshold descriptor.
 * @return bool      true if the call succeeds, else false is returned.
 */
static bool kxtf9_get_threshold(sensor_hal_t *hal,
		sensor_threshold_desc_t *threshold)
{
	if (threshold->type == SENSOR_THRESHOLD_MOTION) {
		uint32_t const regval = sensor_bus_get(hal, KXTF9_WUF_THRESH);
		threshold->value = (int16_t)((regval * 1000) / 16);
		return true;
	}

	return false;
}

/**
 * @brief  Set tap detection parameters
 *
 * @param  hal      Address of an initialized sensor hardware descriptor.
 * @param  params   Address of an initialized tap parameter structure
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool kxtf9_set_tap(sensor_hal_t *hal, sensor_tap_params_t *params)
{
	uint16_t threshold_min;
	uint16_t threshold_max;

	struct {
		uint8_t tdt_timer;
		uint8_t tdt_h_thresh;
		uint8_t tdt_l_thresh;
		uint8_t tdt_tap_timer;
		uint8_t tdt_total_timer;
		uint8_t tdt_latency_timer;
		uint8_t tdt_window_timer;
	}
	tap_regs;

	/* Set min/max thresholds for tap level. */
	if (params->threshold_min != 0) {
		threshold_min = scaled_to_raw(hal, params->threshold_min);
	} else {
		threshold_min = TAP_THRESH_MIN_DEFAULT;
	}

	if (params->threshold_max != 0) {
		threshold_max = scaled_to_raw(hal, params->threshold_max);
	} else {
		threshold_max = TAP_THRESH_MAX_DEFAULT;
	}

	tap_regs.tdt_h_thresh = threshold_max >> 1;
	tap_regs.tdt_l_thresh = ((threshold_max & 0x01) << 7) |
			(threshold_min & TDT_L_THRESH);

	/* Set timer values. */
	if (params->total_time != 0) {  /* total time for tap detect */
		tap_regs.tdt_window_timer = params->total_time * TAP_TIMER_HZ /
				1000;
	} else {
		tap_regs.tdt_window_timer = TAP_TDT_WINDOW_TIMER_DEFAULT;
	}

	if (params->between_time != 0) { /* min time between double taps */
		tap_regs.tdt_timer = params->between_time * TAP_TIMER_HZ / 1000;
	} else {
		tap_regs.tdt_timer = TAP_TDT_TIMER_DEFAULT;
	}

	if (params->ignore_time != 0) { /* time to ignore subsequent taps */
		tap_regs.tdt_latency_timer = params->ignore_time *
				TAP_TIMER_HZ / 1000;
	} else {
		tap_regs.tdt_latency_timer = TAP_TDT_LATENCY_TIMER_DEFAULT;
	}

	if (params->tap_time_max != 0) { /* max time duration for a tap */
		tap_regs.tdt_tap_timer |= params->tap_time_max * TAP_TIMER_HZ /
				1000;
	} else {
		tap_regs.tdt_tap_timer |= TAP_TDT_TAP_TIMER_MAX_DEFAULT;
	}

	tap_regs.tdt_tap_timer <<= 3;   /* shift max value into bits 3-7 */

	if (params->tap_time_min != 0) { /* min time duration for a tap */
		tap_regs.tdt_tap_timer |= params->tap_time_min * TAP_TIMER_HZ /
				1000;
	} else {
		tap_regs.tdt_tap_timer |= TAP_TDT_TAP_TIMER_MIN_DEFAULT;
	}

	tap_regs.tdt_total_timer = TAP_TDT_TOTAL_TIMER_DEFAULT;

	/* Put the device in standby mode. */
	uint8_t ctrl_reg1 = kxtf9_standby(hal);

	/* Write tap control register values */
	sensor_bus_write(hal, KXTF9_TDT_TIMER, (uint8_t *)&tap_regs,
			sizeof(tap_regs));

	/* Enable tap interrupts for specified axes. */
	uint8_t int_ctrl_reg3 = 0;

	if (params->axes & SENSOR_TAP_AXIS_X) { /* if X, enable right/left */
		int_ctrl_reg3 |= (INT_CTRL_REG3_TRIM | INT_CTRL_REG3_TLEM);
	}

	if (params->axes & SENSOR_TAP_AXIS_Y) { /* if Y, enable up/down */
		int_ctrl_reg3 |= (INT_CTRL_REG3_TUPM | INT_CTRL_REG3_TDOM);
	}

	if (params->axes & SENSOR_TAP_AXIS_Z) { /* if Z, enable face up/down */
		int_ctrl_reg3 |= (INT_CTRL_REG3_TFUM | INT_CTRL_REG3_TFDM);
	}

	sensor_bus_put(hal, KXTF9_INT_CTRL_REG3, int_ctrl_reg3);

	/* Restore normal/standby mode. */
	kxtf9_resume(hal, ctrl_reg1);

	return true;
}

/**
 * @brief Enable or disable KXTF9 sensor events.
 *
 * @param  sensor    Address of an initialized sensor device descriptor
 * @param  callback  Application-defined event callback handler descriptor
 * @param  enable    Enable flag: true = enable event, false = disable event
 * @return bool      true if the call succeeds, else false is returned
 */
static bool kxtf9_event(sensor_t *sensor, sensor_event_t sensor_event,
		sensor_event_callback_t *callback, bool enable)
{
	sensor_hal_t *const hal = sensor->hal;

	bool status = false;

	/* Put the device in standby mode to change settings. */
	uint8_t ctrl_reg1 = kxtf9_standby(hal);

	if (sensor_event & SENSOR_EVENT_NEW_DATA) {
		if (callback) {
			event_cb[0] = *callback;
		}

		if (enable) {
			ctrl_reg1 |= CTRL_REG1_DRDYE;
		} else {
			ctrl_reg1 &= ~CTRL_REG1_DRDYE;
		}

		status = true;
	}

	if (sensor_event & SENSOR_EVENT_MOTION) {
		if (callback) {
			event_cb[1] = *callback;
		}

		if (enable) {
			ctrl_reg1 |= CTRL_REG1_WUFE;
		} else {
			ctrl_reg1 &= ~CTRL_REG1_WUFE;
		}

		status = true;
	}

	if (sensor_event & SENSOR_EVENT_TAP) {
		if (callback) {
			event_cb[2] = *callback;
		}

		if (enable) {
			ctrl_reg1 |= CTRL_REG1_TDTE;
		} else {
			ctrl_reg1 &= ~CTRL_REG1_TDTE;
		}

		status = true;
	}

	if (sensor_event & SENSOR_EVENT_TILT) {
		if (callback) {
			event_cb[3] = *callback;
		}

		if (enable) {
			ctrl_reg1 |= CTRL_REG1_TPE;
		} else {
			ctrl_reg1 &= ~CTRL_REG1_TPE;
		}

		status = true;
	}

	uint8_t int_ctrl_reg1 = INT_CTRL_REG1_IEA | INT_CTRL_REG1_IEL;

	if (ctrl_reg1 & (CTRL_REG1_DRDYE | CTRL_REG1_WUFE |
			CTRL_REG1_TDTE | CTRL_REG1_TPE)) {
		int_ctrl_reg1 |= INT_CTRL_REG1_IEN;
	}

	/* Write the new control reg values. */
	sensor_bus_put(hal, KXTF9_INT_CTRL_REG1, int_ctrl_reg1);
	sensor_bus_put(hal, KXTF9_CTRL_REG1, ctrl_reg1);

	return status;
}

/**
 * @brief KXTF9 ioctl control entry point
 *
 * @param hal           Address of an initialized sensor device descriptor.
 * @param cmd           Command to execute
 * @param arg           Argument for command (varies)
 *
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool kxtf9_ioctl(sensor_t *sensor, sensor_command_t cmd,
		void *arg)
{
	sensor_hal_t *const hal = sensor->hal;
	sensor_data_t sample = {.scaled = true};

	switch (cmd) {
	case SENSOR_SET_STATE:
		return kxtf9_set_state(hal, *((sensor_state_t *)arg));

	case SENSOR_SET_RANGE:
		return kxtf9_set_range(hal, (uint16_t)*((int *)arg));

	case SENSOR_SET_BANDWIDTH:
		return kxtf9_set_bandwidth(hal, (uint16_t)*((int *)arg));

	case SENSOR_SET_SAMPLE_RATE:
		return kxtf9_set_sample_rate(hal, *((uint16_t *)arg));

	case SENSOR_ENABLE_EVENT:
		return kxtf9_event(sensor, *((sensor_event_t *)arg), 0, true);

	case SENSOR_DISABLE_EVENT:
		return kxtf9_event(sensor, *((sensor_event_t *)arg), 0, false);

	case SENSOR_SET_THRESHOLD:
		return kxtf9_set_threshold(hal, (sensor_threshold_desc_t *)arg);

	case SENSOR_GET_THRESHOLD:
		return kxtf9_get_threshold(hal, (sensor_threshold_desc_t *)arg);

	case SENSOR_SET_TAP:
		return kxtf9_set_tap(hal, (sensor_tap_params_t *)arg);

	case SENSOR_READ_VECTOR:
		if (kxtf9_get_accel(hal, &sample)) {
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
