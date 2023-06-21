/**
 * \file
 *
 * \brief InvenSense IMU-3000 digital triaxial gyroscope.
 *
 * This module implements a driver for the InvenSense IMU-3000 digital 3-axis
 * MEMS gyroscope and digital motion processor (IMU).  The IMU-3000 provides
 * digital-output x-, y-, and z-axis angular rate sensor readings with a
 * sensitivity of 16 LSBs per deg/sec and programmable full-scale ranges of
 * +/-250, +/-500, +/-1000, and +/-2000 deg/sec.  The device includes a
 * dedicated I2C master accelerometer sensor bus facilitating direct data
 * acquisition from an off-chip third party accelerometer without intervention
 * from an external processor.  A configurable 512 Byte FIFO allows system
 * microcontrollers to burst read the sensor data and then sleep while the IMU
 * collects more data.
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
#include "imu3000.h"

static bool imu3000_read(sensor_t *, sensor_read_t, sensor_data_t *);
static bool imu3000_ioctl(sensor_t *, sensor_command_t, void *);
static void imu3000_isr(volatile void *);
static bool imu3000_event(sensor_t *, sensor_event_t, sensor_event_callback_t *,
		bool);

typedef struct {
	uint8_t int_status;         /**< Interrupt status (read to clear int) */
	int8_t temp_hi;             /**< Temperature (MSB) */
	int8_t temp_lo;             /**< Temperature (LSB) */
	int8_t x_hi;                /**< X axis rotation (MSB) */
	int8_t x_lo;                /**< X axis rotation (LSB) */
	int8_t y_hi;                /**< Y axis rotation (MSB) */
	int8_t y_lo;                /**< Y axis rotation (LSB) */
	int8_t z_hi;                /**< Z axis rotation (MSB) */
	int8_t z_lo;                /**< Z axis rotation (LSB) */
} imu3000_event_t;

/** Axis data sample resolution (bits) */
#define IMU3000_RESOLUTION      (16)

/** \brief InvenSense IMU-3000 Range Table (deg/sec, register value) */
static const sensor_map_t range_table [] = {
	{{ 250}, FS_SEL_250 }, {{ 500}, FS_SEL_500 },
	{{1000}, FS_SEL_1000}, {{2000}, FS_SEL_2000}
};

/** The range table index defaults to 2000 deg/sec full-scale. */
static int sensor_fs_sel = 3;

/** \brief InvenSense IMU-3000 low-pass Bandwidth Table (hertz, register value) */
static const sensor_map_t band_table [] = {
	{{  5}, DLPF_CFG_5HZ  }, {{ 10}, DLPF_CFG_10HZ },
	{{ 20}, DLPF_CFG_20HZ }, {{ 42}, DLPF_CFG_42HZ },
	{{ 98}, DLPF_CFG_98HZ }, {{188}, DLPF_CFG_188HZ},
	{{256}, DLPF_CFG_256HZ} /* , { {2100}, DLPF_CFG_2100HZ } */
};

/** The digital low-pass filter table index defaults to 42 Hz. */
static int sensor_dlpf_cfg = 3;

/** \brief Sensitivity Scale Factors */
int16_t const scale_lsb_per_dps [] = {
	(131 /  1),      /* 131  LSB/deg/sec, fs_sel = 0 */
	(655 / 10),      /* 65.5 LSB/deg/sec, fs_sel = 1 */
	(328 / 10),      /* 32.8 LSB/deg/sec, fs_sel = 2 */
	(164 / 10)       /* 16.4 LSB/deg/sec, fs_sel = 3 */
};

/** \brief Sensor Event Callback Descriptor */
static sensor_event_callback_t event_cb = {.handler = default_event_handler};

/**
 * @brief InvenSense IMU-3000 gyroscope driver defaults.
 *
 * This is a convenience routine for setting the default device configuration
 * during initialization or after reset.
 *
 * @return bool     true if the sensor is ready for use, else false.
 */
static bool imu3000_default_init(sensor_hal_t *hal, sensor_hal_t *aux)
{
	bool status = false;

	/* Assuming the device is on an I2C bus, the device address and ID
	 * are one and the same.  Per the vendor data sheet, AD0 in the
	 * WHO_AM_I (device ID) register is software configurable s.t. two
	 * devices can be installed on the sensor bus.  The undefined AD0
	 * bit is set to zero to select the 110 1000 (AD0=0) address.
	 *
	 * Set the bus address here then verify the setting.
	 */
	sensor_bus_put(hal, IMU3000_WHO_AM_I, IMU3000_ID_VAL);

	if (IMU3000_ID_VAL == sensor_bus_get(hal, IMU3000_WHO_AM_I)) {
		/* Reset the motion processing unit to a known state then enable
		 * the gyroscope using the Z-axis for clock.
		 */
		sensor_bus_put(hal, IMU3000_PWR_MGM, PWR_MGM_H_RESET);
		sensor_bus_put(hal, IMU3000_WHO_AM_I, IMU3000_ID_VAL);
		sensor_bus_put(hal, IMU3000_PWR_MGM, PWR_MGM_CLK_SEL_Z);

		/* \todo Define a method to support I2C master mode.
		 *
		 * Determine whether it is reasonable to use the
		 * "sensor_desc.aux" field to support an external 3-axis accelerometer
		 * configured as an auxiliary device. For example, assume a user
		 * selects this as a build-time configuration option and the "aux"
		 * field points to a sensor_hal_t type describing the accelerometer.
		 */
		if (aux) {
			/* Configure and enable the IMU-3000 auxiliary device
			 * interface, including bus and burst read addresses.
			 */
			sensor_bus_put(hal, IMU3000_AUX_SLV_ADDR,
					AUX_ADDR_CLKOUTEN | aux->bus.addr);

			sensor_bus_put(hal, IMU3000_AUX_BURST_ADDR,
					aux->burst_addr);

			/* Enable the IMU as master to accelerometer (aux)
			 * interface via secondary I2C bus. For an external
			 * processor to communicate directly to an external accelerometer
			 * the AUX_IF_EN bit should be cleared and AUX_IF_RST bit
			 * should be set. The configuration below turns the accelerometer
			 * into a slave device that's not addressed by a separate
			 * sensor_t descriptor and API routines.
			 */
			sensor_bus_put(hal, IMU3000_USER_CTRL,
					USER_CTRL_AUX_IF_RST |
					USER_CTRL_AUX_IF_EN);
		} else {
			/* Reset the auxiliary interface in pass-through mode
			 * s.t. the external processor can communicate directly with
			 * an external accelerometer.
			 */
			sensor_bus_put(hal, IMU3000_USER_CTRL,
					USER_CTRL_AUX_IF_RST);
		}

		/* \todo Define a method to dynamically compute DC bias.
		 *
		 * The gyro signed offset registers remove DC bias from the
		 * sensor outputs by subtracting the offset values from gyro sensor
		 * values prior to moving sensor data to output registers. The
		 * device is initialized s.t. DC bias offsets are not applied to
		 * sensor data.
		 */
		const uint16_t *const gyro_offsets = (uint16_t [3]) {0};

		sensor_bus_write(hal, IMU3000_X_OFFS_USRH,
				gyro_offsets, 3 * sizeof(uint16_t));

		/* Set the sample rate divider, digital low-pass filter, and
		 * full-scale range.
		 *
		 * The digital low-pass filter also determines the internal
		 * sample rate used by the device.  The 256 Hz. and 2.1 kHz
		 * filter bandwidths result in an 8 kHz. internal sample rate, while
		 * all other settings result in a 1 kHz. internal sample rate.
		 *
		 * This internal sample rate is then further scaled by the
		 * sample rate divider (SMPLRT_DIV) value to produce the gyro
		 * sample rate according to the formula:
		 *
		 *          F_sample = F_internal / (divider + 1)
		 */
		uint8_t const dlpf_fs
			= range_table[sensor_fs_sel].reserved_val |
				band_table[sensor_dlpf_cfg].reserved_val;

		sensor_bus_put(hal, IMU3000_SMPLRT_DIV, 9);
		sensor_bus_put(hal, IMU3000_DLPF_FS, dlpf_fs);
	}

	if (STATUS_OK == hal->bus.status) {
		status = true;
	}

	return status;
}

/**
 * @brief InvenSense IMU-3000 motion processor driver initialization.
 *
 * This is the main initialization function for the IMU-3000 device.
 *
 * @param sensor    Address of a sensor device descriptor.
 * @param resvd     Reserved value.
 * @return bool     true if the sensor is ready for use, else false.
 */
bool imu3000_init(sensor_t *sensor, int resvd)
{
	sensor_hal_t *const hal = sensor->hal;
	sensor_hal_t *const aux = (sensor_hal_t *)sensor->aux;
	bool status = false;

	/* Set the driver function table and capabilities pointer. */
	static const sensor_device_t imu3000_device = {
		.func.read            = imu3000_read,
		.func.ioctl           = imu3000_ioctl,
		.func.event           = imu3000_event,

		.caps.feature         = SENSOR_CAPS_3_AXIS   |
				SENSOR_CAPS_AUX_TEMP |
				SENSOR_CAPS_AUX_ACCEL,
		.caps.vendor          = SENSOR_VENDOR_INVENSENSE,
		.caps.range_table     = range_table,
		.caps.band_table      = band_table,
		.caps.range_count     = ARRAYSIZE(range_table),
		.caps.band_count      = ARRAYSIZE(band_table),
		.caps.units           = SENSOR_UNITS_deg_per_sec,
		.caps.name = "InvenSense IMU-3000 Motion Processing Unit"
	};

	sensor->drv = &imu3000_device;

	/* Set the driver default, range, bandwidth, resolution, etc. */
	hal->range      = range_table [sensor_fs_sel].range_units;
	hal->bandwidth  = band_table [sensor_dlpf_cfg].bandwidth_Hz;
	hal->sample_rate = 100;
	hal->resolution = IMU3000_RESOLUTION;

	/* Apply default device settings */
	if (imu3000_default_init(hal, aux) != true) {
		return status; /* return error */
	}

	/* Set start addr for burst read (used during interrupt). */
	hal->burst_addr = IMU3000_INT_STATUS;

	/* Connect interrupt event handler. */
	if (sensor_irq_connect(hal->mcu_sigint, imu3000_isr, hal)) {
		status = true;
	}

	return status;
}

/**
 * @brief Invensense IMU3000 driver interrupt service routine.
 *
 * This is the interrupt service routine for enabled IMU3000 interrupt events.
 * Only the new data ("raw data ready") interrupt is supported.
 *
 * @param arg       The address of the driver sensor_hal_t descriptor.
 * @return Nothing.
 */
static void imu3000_isr(volatile void *arg)
{
	sensor_hal_t *const hal = (sensor_hal_t *)arg;
	int16_t input[3];

	hal->bus.no_wait = true;

	imu3000_event_t regs;
	sensor_bus_read(hal, hal->burst_addr, &regs, sizeof(regs));

	hal->bus.no_wait = false;

	if (STATUS_OK == hal->bus.status) {
		/* Assume new data to avoid an apparent race condition. The
		 * interupt status register sometimes has the new data flag
		 * cleared before it is read above.  If this happens, the sensor will
		 * not generate any further new data interrupts until the device is
		 * independently accessed.
		 */
		static sensor_event_data_t event_data = {.data.scaled = true};

		event_data.data.timestamp = sensor_timestamp();
		event_data.event = SENSOR_EVENT_NEW_DATA;

		input[0] = (regs.x_hi << 8) | regs.x_lo;
		input[1] = (regs.y_hi << 8) | regs.y_lo;
		input[2] = (regs.z_hi << 8) | regs.z_lo;

		event_data.data.axis.x
			= hal->orientation.x.sign *
				input[hal->orientation.x.axis];
		event_data.data.axis.y
			= hal->orientation.y.sign *
				input[hal->orientation.y.axis];
		event_data.data.axis.z
			= hal->orientation.z.sign *
				input[hal->orientation.z.axis];

		const int32_t scaling
			= (int32_t)scale_lsb_per_dps[sensor_fs_sel];
		event_data.data.axis.x /= scaling;
		event_data.data.axis.y /= scaling;
		event_data.data.axis.z /= scaling;

		/* Call application-supplied handler routine */
		(event_cb.handler)(&event_data, event_cb.arg);
	}
}

/**
 * @brief Enable/disable IMU3000 sensor event
 *
 * @param  sensor    Address of an initialized sensor device descriptor
 * @param  callback  Application-defined event callback handler descriptor
 * @param  enable    Enable flag: true = enable event, false = disable event
 * @return bool      true if the call succeeds, else false is returned
 */
static bool imu3000_event(sensor_t *sensor, sensor_event_t sensor_event,
		sensor_event_callback_t *callback, bool enable)
{
	sensor_hal_t *const hal = sensor->hal;

	bool status = false;

	if (sensor_event & SENSOR_EVENT_NEW_DATA) {
		if (callback) {
			event_cb = *callback;
		}

		if (enable) {
			/* Enable new data int, latch until any reg is read,
			 * active high */
			sensor_bus_put(hal, IMU3000_INT_CFG,
					INT_CFG_RAW_RDY_EN |
					INT_CFG_ANYRD_2CLEAR);
		} else {
			/* Disable new data int */
			sensor_reg_bitclear(hal, IMU3000_INT_CFG,
					INT_CFG_LATCH_INT_EN);
		}

		status = true;
	}

	return status;
}

/**
 * @brief Read gyroscope angular rate axis data.
 *
 * This function reads angular rate data for all 3 axes of an IMU-3000
 * gyroscope.
 *
 * @param sensor    Address of an initialized sensor device descriptor.
 * @param data      The address of a vector storing sensor axis data.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool imu3000_get_rotation(sensor_hal_t *hal, sensor_data_t *data)
{
	struct
	{
		uint8_t msb;
		uint8_t lsb;
	} input[3];

	size_t const count = sensor_bus_read(hal, IMU3000_GYRO_XOUT_H,
			input, sizeof(input));

	/* Copy data values based on device orientation and signs. */
	data->axis.x = hal->orientation.x.sign *
			((int16_t)((input[hal->orientation.x.axis].msb << 8) |
			input[hal->orientation.x.axis].lsb));

	data->axis.y = hal->orientation.y.sign *
			((int16_t)((input[hal->orientation.y.axis].msb << 8) |
			input[hal->orientation.y.axis].lsb));

	data->axis.z = hal->orientation.z.sign *
			((int16_t)((input[hal->orientation.z.axis].msb << 8) |
			input[hal->orientation.z.axis].lsb));

	/* Convert raw sensor samples to engineering units if requested. */
	if (data->scaled) {
		data->axis.x /= (int32_t)scale_lsb_per_dps [sensor_fs_sel];
		data->axis.y /= (int32_t)scale_lsb_per_dps [sensor_fs_sel];
		data->axis.z /= (int32_t)scale_lsb_per_dps [sensor_fs_sel];
	}

	return (count == sizeof(input));
}

/**
 * @brief Read gyroscope integrated temperature sensor data
 *
 * This function reads IMU-3000 integrated temperature sensor data.
 * The temperature is always returned in scaled engineering units
 * (degrees Celsius).
 *
 * @param sensor    Address of an initialized sensor device descriptor.
 * @param data      The address where temperature samples are returned.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool imu3000_get_temperature(sensor_hal_t *hal, sensor_data_t *data)
{
	int16_t temp_data;

	size_t const count = sensor_bus_read(hal, IMU3000_TEMP_OUT_H,
			&temp_data, sizeof(temp_data));

	data->temperature.value = (int16_t)be16_to_cpu(temp_data);

	if (data->scaled) {
		data->temperature.value -= TEMP_OFFSET;
		data->temperature.value /= TEMP_COUNTS_PER_DEG_C;
		data->temperature.value += TEMP_REF_DEG;
	}

	return (count == sizeof(temp_data));
}

/**
 * @brief Read gyroscope device ID
 *
 * This function reads the gyroscope hardware identification registers
 * and returns these values to the addresses specified in the function
 * parameters.
 *
 * @param sensor    Address of an initialized sensor device descriptor.
 * @param data      Address of sensor_data_t structure to return values.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool imu3000_device_id(sensor_hal_t *hal, sensor_data_t *data)
{
	data->device.id = sensor_bus_get(hal, IMU3000_WHO_AM_I);
	data->device.version = 0;

	return true;
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
static bool imu3000_read(sensor_t *sensor, sensor_read_t type,
		sensor_data_t *data)
{
	sensor_hal_t *const hal = sensor->hal;

	switch (type) {
	case SENSOR_READ_ROTATION:
		return imu3000_get_rotation(hal, data);

	case SENSOR_READ_TEMPERATURE:
		return imu3000_get_temperature(hal, data);

	case SENSOR_READ_ID:
		return imu3000_device_id(hal, data);

	default:
		sensor->err = SENSOR_ERR_FUNCTION;
		return false;
	}
}

/**
 * @brief Set the IMU-3000 execution mode.
 *
 * This routine sets a specified IMU-3000 execution state to one of the
 * following:
 *
 * SENSOR_STATE_SLEEP or SENSOR_STATE_LOWEST_POWER
 *      Setting the sleep mode puts the device into very low power sleep
 *      mode.  In this mode, only the serial interface and internal registers
 *      remain active.
 *
 *  SENSOR_STATE_NORMAL or SENSOR_STATE_HIGHEST_POWER
 *      Sets the device to a normal operational state.
 *
 *  SENSOR_STATE_RESET
 *      Sets the device and internal registers to the power-up default
 *      settings.
 *
 * @param sensor    Address of an initialized sensor device descriptor.
 * @param state     A specified sensor operational state.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool imu3000_set_state(sensor_hal_t *hal, sensor_state_t state)
{
	switch (state) {
	case SENSOR_STATE_SLEEP:
	case SENSOR_STATE_LOWEST_POWER:

		sensor_reg_bitset(hal, IMU3000_PWR_MGM, PWR_MGM_SLEEP);
		break;

	case SENSOR_STATE_NORMAL:
	case SENSOR_STATE_HIGHEST_POWER:

		sensor_reg_bitclear(hal, IMU3000_PWR_MGM, PWR_MGM_SLEEP);
		delay_ms(5);
		break;

	case SENSOR_STATE_RESET:

		/**
		 * \todo
		 *
		 * Update sensor device descriptor operational settings.
		 */
		return imu3000_default_init(hal,
				(sensor_hal_t *)(((sensor_t *)hal)->aux));

	default:
		return false;
	}

	return true;
}

/**
 * @brief Set the IMU-3000 full scale range.
 *
 * This routine sets the IMU-3000 full scale range using an index to
 * a table of valid ranges:  +/-250, +/-500, +/-1000, and +/-2000 deg/sec.
 *
 * @param hal       Address of an initialized sensor device descriptor.
 * @param range     The index o a driver-specific range table entry.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool imu3000_set_range(sensor_hal_t *hal, int16_t range)
{
	sensor_fs_sel = range;

	/* Set the device full scale range. */
	uint8_t const dlpf_fs = (~FS_SEL_FIELD) &
			sensor_bus_get(hal, IMU3000_DLPF_FS);

	sensor_bus_put(hal, IMU3000_DLPF_FS,
			dlpf_fs | range_table [sensor_fs_sel].reserved_val);

	return true;
}

/**
 * @brief Set the IMU-3000 low-pass filter bandwidth.
 *
 * This routine sets the IMU-3000 low-pass filter bandwidth and the
 * internal sample rate used by the device.  This internal sample rate is
 * then further scaled by the sample rate divider (SMPLRT_DIV) value to
 * produce the gyro sample rate according to the formula:
 *
 *          F_sample = F_internal / (divider + 1)
 *
 * Valid filter bandwidths and the associated internal sample rate are
 * as follows:
 *
 * @code
 *          Low Pass Filter Bandwidth       Internal Sample Rate
 *          ____________________________________________________
 *              256Hz                           8kHz
 *              188Hz                           1kHz
 *              98Hz                            1kHz
 *              42Hz                            1kHz
 *              20Hz                            1kHz
 *              10Hz                            1kHz
 *              5Hz                             1kHz
 * @endcode
 *
 * @param hal       Address of an initialized sensor device descriptor.
 * @param band      The index of a driver-specific bandwidth table entry.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool imu3000_set_bandwidth(sensor_hal_t *hal, int16_t band)
{
	sensor_dlpf_cfg = band;

	/* Set the device low-pass filter frequency. */
	uint8_t const dlpf_fs = (~DLPF_CFG_FIELD) &
			sensor_bus_get(hal, IMU3000_DLPF_FS);

	sensor_bus_put(hal, IMU3000_DLPF_FS,
			dlpf_fs | band_table [sensor_dlpf_cfg].reserved_val);

	return true;
}

/**
 * @brief Set the IMU3000 sample rate
 *
 * This routine sets the externally visible IMU3000 sample rate
 * for the device.  This sets a divider that scaled down the internal
 * 1Khz or 8 KHz sample rate to the specified frequency, according to
 * the formula:
 *
 * @code
 *
 *          F_sample = F_internal / (divider + 1)
 *
 * @endcode
 *
 * The internal sampling rate is 1KHz for all filter bandwidths except
 * 256Hz, which uses an 8KHz internal rate.
 *
 * @param hal       Address of an initialized sensor device descriptor.
 * @param rate      The externally visible sampling rate to be set
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool imu3000_set_sample_rate(sensor_hal_t *hal, int16_t rate)
{
	/* Determine internal sample rate based on bandwidth. */
	uint16_t const internal_rate = (hal->bandwidth == 256) ? 8000 : 1000;

	/* Calculate divider. */
	uint8_t const divider = (internal_rate / rate) - 1;

	/* Set the sample rate divider. */
	sensor_bus_put(hal, IMU3000_SMPLRT_DIV, divider);

	return true;
}

/**
 * @brief IMU3000 ioctl control entry point
 *
 * This function provides a general-purpose interface for performing various
 * control operations on the sensor device.
 *
 * @param sensor        Address of an initialized sensor device descriptor.
 * @param cmd           Command to execute
 * @param arg           Argument for command (varies)
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool imu3000_ioctl(sensor_t *sensor, sensor_command_t cmd, void *arg)
{
	sensor_hal_t *const hal = sensor->hal;
	sensor_data_t sample = {.scaled = true};

	switch (cmd) {
	case SENSOR_SET_STATE:
		return imu3000_set_state(hal, *((sensor_state_t *)arg));

	case SENSOR_SET_RANGE:
		return imu3000_set_range(hal, (uint16_t)*((int *)arg));

	case SENSOR_SET_BANDWIDTH:
		return imu3000_set_bandwidth(hal, (uint16_t)*((int *)arg));

	case SENSOR_SET_SAMPLE_RATE:
		return imu3000_set_sample_rate(hal, *((uint16_t *)arg));

	case SENSOR_ENABLE_EVENT:
		return imu3000_event(sensor, *((sensor_event_t *)arg), 0, true);

	case SENSOR_DISABLE_EVENT:
		return imu3000_event(sensor, *((sensor_event_t *)arg), 0,
				false);

	case SENSOR_READ_VECTOR:
		if (imu3000_get_rotation(hal, &sample)) {
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
