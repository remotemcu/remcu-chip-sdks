/**
 * \file
 *
 * \brief InvenSense ITG-3200 digital triaxial gyroscope.
 *
 * This module implements a driver for the InvenSense ITG-3200 digital 3-axis
 * MEMS gyroscope. The ITG-3200 provides digital-output x-, y-, and z-axis
 * angular rate sensor readings with a sensitivity of 16 LSBs per deg/sec and a
 * full-scale range of +/-2000 deg/sec.
 *
 * The ITG-3200 consists of the following key blocks and functions:
 *
 *      - Three-axis MEMS rate gyroscope sensors with individual 16-bit
 *        ADCs and signal conditioning
 *
 *      - I2C serial communications interface
 *
 *      - Clocking
 *
 *      - Sensor Data Registers
 *
 *      - Interrupts
 *
 *      - Digital-Output Temperature Sensor
 *
 *      - Bias and LDO
 *
 *      - Charge Pump
 *
 *      - Three-Axis MEMS Gyroscope with 16-bit ADCs and Signal Conditioning
 *
 * The ITG-3200 consists of three independent vibratory MEMS gyroscopes, which
 * detect rotational rate about the X (roll), Y (pitch), and Z (yaw) axes.
 * When the gyros are rotated about any of the sense axes, the Coriolis Effect
 * causes a deflection that is detected by a capacitive pickoff. The resulting
 * signal is amplified, demodulated, and filtered to produce a voltage that is
 * proportional to the angular rate. This voltage is digitized using individual
 * on-chip 16-bit Analog-to-Digital Converters (ADCs) to sample each axis.
 *
 * The full-scale range of the gyro sensors is preset to +/-2000 degrees per
 * second (deg/sec). The ADC output rate is programmable up to a maximum of
 * 8,000
 * samples per second down to 3.9 samples per second, and user-selectable
 * low-pass filters enable a wide range of cut-off frequencies.
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
#include "itg3200.h"

static bool itg3200_read(sensor_t *, sensor_read_t, sensor_data_t *);
static bool itg3200_ioctl(sensor_t *, sensor_command_t, void *);
static bool itg3200_event(sensor_t *, sensor_event_t, sensor_event_callback_t *,
		bool);
static void itg3200_isr(volatile void *);

static bool itg3200_set_sample_rate(sensor_hal_t *, int16_t);

/** \brief Interrupt Service Routine Data Descriptor */
typedef struct {
	uint8_t int_status;             /* Interrupt status (read to clear int) */
	int8_t temp_hi;                 /* Temperature (MSB) */
	int8_t temp_lo;                 /* Temperature (LSB) */
	int8_t x_hi;                    /* X axis rotation (MSB) */
	int8_t x_lo;                    /* X axis rotation (LSB) */
	int8_t y_hi;                    /* Y axis rotation (MSB) */
	int8_t y_lo;                    /* Y axis rotation (LSB) */
	int8_t z_hi;                    /* Z axis rotation (MSB) */
	int8_t z_lo;                    /* Z axis rotation (LSB) */
} itg3200_event_t;

#define ITG3200_FS_RANGE        (2000)  /* fixed full-scale range (deg/sec) */
#define ITG3200_RESOLUTION      (16)    /* axis data sample resolution (bits) */

/**
 * The ITG-3200 specification originally stated that the sensitivity scale
 * factor was 16.4 LSB/deg/sec.  As of revision 1.4 of the specification, that
 * has been modified to 14.375 LSB/deg/sec.  The vendor may supply a way to
 * interrogate ITG-3200 parts to determine which scale factor to use.
 */
#define SCALE_LSB_PER_DPS       (14375 / 1000)
/* #define SCALE_LSB_PER_DPS    (164 / 10) */

/** \brief InvenSense ITG-3200 low-pass Bandwidth Table (hertz, register value) */
static const sensor_map_t band_table [] = {
	{{  5}, DLPF_CFG_5HZ  }, {{ 10}, DLPF_CFG_10HZ },
	{{ 20}, DLPF_CFG_20HZ }, {{ 42}, DLPF_CFG_42HZ },
	{{ 98}, DLPF_CFG_98HZ }, {{188}, DLPF_CFG_188HZ},
	{{256}, DLPF_CFG_256HZ} /* , { {2100}, DLPF_CFG_2100HZ } */
};

/** \brief Sensor Event Callback Descriptor */
static sensor_event_callback_t event_cb = {.handler = default_event_handler};

/**
 * @brief InvenSense ITG-3200 gyroscope driver defaults.
 *
 * This is a convenience routine for setting the default device configuration
 * during initialization or after reset.
 *
 * @param hal       Address of an initialized sensor hardware descriptor.
 * @return bool     true if the sensor is ready for use, else false.
 */
static inline bool itg3200_default_init(sensor_hal_t *hal)
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
	sensor_bus_put(hal, ITG3200_WHOAMI, ITG3200_ID_VAL);

	if (ITG3200_ID_VAL == sensor_bus_get(hal, ITG3200_WHOAMI)) {
		/* Reset the motion processing unit to a known state then enable
		 * the gyroscope using the X-axis for clock.
		 */
		sensor_bus_put(hal, ITG3200_PWR_MGM, PWR_MGM_H_RESET);
		sensor_bus_put(hal, ITG3200_WHOAMI, ITG3200_ID_VAL);
		sensor_bus_put(hal, ITG3200_PWR_MGM, PWR_MGM_CLK_SEL_Z);

		/* Set the sample rate divider, digital low-pass filter, and
		 * full-scale range (fixed @ +/-2000 deg/sec).
		 *
		 * The digital low-pass filter also determines the internal
		 * sample rate used by the device.  The 256 Hz. and 2.1 kHz
		 * filter bandwidths result in an 8 kHz. internal sample rate, while
		 * all other settings result in a 1 kHz. internal sample rate.
		 *
		 * This internal sample rate is then further scaled by the
		 * sample rate divider (SMPLRT_DIV) value to produce the gyro
		 * sample rate  according to the formula:
		 *
		 *          F_sample = F_internal / (divider + 1)
		 *
		 * On reset the FS_SEL field is 00h and must be set to the
		 * full-scale range setting of 03h (+/-2000 deg/sec) for proper
		 * operation.
		 */
		uint8_t const dlpf_fs = FS_SEL_2000 | DLPF_CFG_42HZ;

		sensor_bus_put(hal, ITG3200_SMPLRT_DIV, 9); /* 100Hz sample rate
		                                             **/
		sensor_bus_put(hal, ITG3200_DLPF_FS, dlpf_fs);

		if (STATUS_OK == hal->bus.status) {
			status = true;
		}
	}

	return status;
}

/**
 * @brief InvenSense ITG-3200 gyroscope driver initialization.
 *
 * This is the main initialization function for the ITG-3200 device.
 *
 * @param sensor    Address of a sensor device descriptor.
 * @param resvd     Reserved value.
 * @return bool     true if the sensor is ready for use, else false.
 */
bool itg3200_init(sensor_t *sensor, int resvd)
{
	sensor_hal_t *const hal = sensor->hal;
	bool status = false;

	/* Set the driver function table and capabilities pointer. */
	static const sensor_device_t itg3200_device = {
		.func.read            = itg3200_read,
		.func.ioctl           = itg3200_ioctl,
		.func.event           = itg3200_event,

		.caps.feature         = SENSOR_CAPS_3_AXIS |
				SENSOR_CAPS_AUX_TEMP,
		.caps.vendor          = SENSOR_VENDOR_INVENSENSE,
		.caps.band_table      = band_table,
		.caps.band_count      = ARRAYSIZE(band_table),
		.caps.units           = SENSOR_UNITS_deg_per_sec,
		.caps.name = "InvenSense ITG-3200 3-axis angular rate sensor"
	};

	sensor->drv = &itg3200_device;

	/* Set the driver default, range, bandwidth, resolution, etc. */
	hal->range      = ITG3200_FS_RANGE;
	hal->bandwidth  = 256; /* Hertz */
	hal->sample_rate = 100; /* Hertz */
	hal->resolution = ITG3200_RESOLUTION;
	hal->burst_addr = ITG3200_INT_STATUS;

	/* Apply default device settings & connect an interrupt handler. */
	if (itg3200_default_init(hal) && sensor_irq_connect
				(hal->mcu_sigint, itg3200_isr, hal)) {
		status = true;
	}

	return status;
}

/**
 * @brief Invensense ITG3200 driver interrupt service routine.
 *
 * This is the interrupt service routine for enabled ITG3200 interrupt events.
 * Only the new data ("raw data ready") interrupt is supported.
 *
 * @param arg       The address of the driver sensor_hal_t descriptor.
 * @return Nothing.
 */
static void itg3200_isr(volatile void *arg)
{
	sensor_hal_t *const hal = (sensor_hal_t *)arg;
	int16_t input[3];

	hal->bus.no_wait = true;

	itg3200_event_t regs;
	sensor_bus_read(hal, hal->burst_addr, &regs, sizeof(regs));

	hal->bus.no_wait = false;

	if (STATUS_OK == hal->bus.status) {
		/* Assume new data to avoid an apparent race condition. The
		 * interrupt status register sometimes has the new data flag
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

		event_data.data.axis.x /= SCALE_LSB_PER_DPS;
		event_data.data.axis.y /= SCALE_LSB_PER_DPS;
		event_data.data.axis.z /= SCALE_LSB_PER_DPS;

		/* Call application-supplied handler routine */
		(event_cb.handler)(&event_data, event_cb.arg);
	}
}

/**
 * @brief Read gyroscope angular rate axis data.
 *
 * This function reads angular rate data for all 3 axes of an ITG-3200
 * gyroscope.
 *
 * @param sensor    Address of an initialized sensor device descriptor.
 * @param data      The address of a vector storing sensor axis data.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool itg3200_get_rotation(sensor_hal_t *hal, sensor_data_t *data)
{
	struct {
		uint8_t msb;
		uint8_t lsb;
	} input[3];

	size_t const count = sensor_bus_read(hal, ITG3200_GYRO_XOUT_H,
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
		data->axis.x /= SCALE_LSB_PER_DPS;
		data->axis.y /= SCALE_LSB_PER_DPS;
		data->axis.z /= SCALE_LSB_PER_DPS;
	}

	return (count == sizeof(input));
}

/**
 * @brief Read gyroscope integrated temperature sensor data
 *
 * This function reads ITG-3200 integrated temperature sensor data.
 * The temperature is always returned in scaled engineering units
 * (degrees Celsius).
 *
 * @param sensor    Address of an initialized sensor device descriptor.
 * @param data      The address where temperature samples are returned.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool itg3200_get_temperature(sensor_hal_t *hal, sensor_data_t *data)
{
	int16_t temp_data;

	size_t const count = sensor_bus_read(hal, ITG3200_TEMP_OUT_H,
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
static bool itg3200_device_id(sensor_hal_t *hal, sensor_data_t *data)
{
	data->device.id = sensor_bus_get(hal, ITG3200_WHOAMI);
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
static bool itg3200_read(sensor_t *sensor, sensor_read_t type,
		sensor_data_t *data)
{
	sensor_hal_t *const hal = sensor->hal;

	switch (type) {
	case SENSOR_READ_ROTATION:
		return itg3200_get_rotation(hal, data);

	case SENSOR_READ_TEMPERATURE:
		return itg3200_get_temperature(hal, data);

	case SENSOR_READ_ID:
		return itg3200_device_id(hal, data);

	default:
		sensor->err = SENSOR_ERR_FUNCTION;
		return false;
	}
}

/**
 * @brief Enable/disable ITG3200 sensor event
 *
 * @param  sensor    Address of an initialized sensor device descriptor
 * @param  callback  Application-defined event callback handler descriptor
 * @param  enable    Enable flag: true = enable event, false = disable event
 * @return bool      true if the call succeeds, else false is returned
 */
static bool itg3200_event(sensor_t *sensor, sensor_event_t sensor_event,
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
			sensor_bus_put(hal, ITG3200_INT_CFG,
					INT_CFG_RAW_RDY_EN |
					INT_CFG_ANYRD_2CLEAR);
		} else {
			/* Disable new data int */
			sensor_reg_bitclear(hal, ITG3200_INT_CFG,
					INT_CFG_LATCH_INT_EN);
		}

		status = true;
	}

	return status;
}

/**
 * @brief Set the ITG-3200 execution mode.
 *
 * This routine sets a specified ITG-3200 execution state to one of the
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
static bool itg3200_set_state(sensor_hal_t *hal, sensor_state_t state)
{
	switch (state) {
	default:
		return false;

	case SENSOR_STATE_SLEEP:
	case SENSOR_STATE_LOWEST_POWER:

		sensor_reg_bitset(hal, ITG3200_PWR_MGM, PWR_MGM_SLEEP);
		break;

	case SENSOR_STATE_NORMAL:
	case SENSOR_STATE_HIGHEST_POWER:

		sensor_reg_bitclear(hal, ITG3200_PWR_MGM, PWR_MGM_SLEEP);
		delay_ms(5);
		break;

	case SENSOR_STATE_RESET:

		/*
		 * \todo
		 *
		 * Update sensor device descriptor operational settings.
		 */
		return itg3200_default_init(hal);
	}

	return true;
}

/**
 * @brief Set the ITG-3200 low-pass filter bandwidth.
 *
 * This routine sets the ITG-3200 low-pass filter bandwidth and the
 * internal sample rate used by the device.  This internal sample rate is
 * then further scaled by the sample rate divider (SMPLRT_DIV) value to
 * produce the gyro sample rate according to the formula:
 *
 * @code
 *          F_sample = F_internal / (divider + 1)
 * @endcode
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
static bool itg3200_set_bandwidth(sensor_hal_t *hal, int16_t band)
{
	/* Set the device low-pass filter frequency. */
	sensor_bus_put(hal, ITG3200_DLPF_FS,
			FS_SEL_2000 | band_table [band].reserved_val);

	/* Reset externally visible sample rate, if internal rate may have
	 * changed
	 * Note: internal rate is different for 256Hz b/w than all other settings
	 */
	if ((hal->bandwidth == 256) ||     /* if old or new is 256Hz */
			(band_table [band].bandwidth_Hz == 256)) {
		hal->bandwidth = band_table [band].bandwidth_Hz;
		itg3200_set_sample_rate(hal, hal->sample_rate);
	}

	return true;
}

/**
 * @brief Set the ITG-3200 sample rate
 *
 * This routine sets the externally visible ITG-3200 sample rate
 * for the device.  This sets a divider that scaled down the internal
 * 1Khz or 8 KHz sample rate to the specified frequency, according to
 * the formula:
 *
 * @code
 *          F_sample = F_internal / (divider + 1)
 * @endcode
 *
 * The internal sampling rate is 1KHz for all filter bandwidths except
 * 256Hz, which uses an 8KHz internal rate.
 *
 * @param hal       Address of an initialized sensor device descriptor.
 * @param rate      The externally visible sampling rate to be set
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool itg3200_set_sample_rate(sensor_hal_t *hal, int16_t rate)
{
	uint16_t internal_rate;
	uint8_t divider;

	/* Determine internal sample rate based on bandwidth. */
	if (hal->bandwidth == 256) {
		internal_rate = 8000;
	} else {
		internal_rate = 1000;
	}

	/* Calculate the divider. */
	divider = (internal_rate / rate) - 1;

	/* Set the sample rate divider. */
	sensor_bus_put(hal, ITG3200_SMPLRT_DIV, divider);

	return true;
}

/**
 * @brief ITG3200 ioctl control entry point
 *
 * This function provides a general-purpose interface for performing various
 * control operations on the sensor device.
 *
 * @param sensor    Address of an initialized sensor device descriptor.
 * @param cmd       Command to execute
 * @param arg       Argument for command (varies)
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool itg3200_ioctl(sensor_t *sensor, sensor_command_t cmd, void *arg)
{
	sensor_hal_t *const hal = sensor->hal;
	sensor_data_t sample = {.scaled = true};

	switch (cmd) {
	case SENSOR_SET_STATE:
		return itg3200_set_state(hal, *((sensor_state_t *)arg));

	case SENSOR_SET_BANDWIDTH:
		return itg3200_set_bandwidth(hal, (uint16_t)*((int *)arg));

	case SENSOR_SET_SAMPLE_RATE:
		return itg3200_set_sample_rate(hal, *((uint16_t *)arg));

	case SENSOR_ENABLE_EVENT:
		return itg3200_event(sensor, *((sensor_event_t *)arg), 0, true);

	case SENSOR_DISABLE_EVENT:
		return itg3200_event(sensor, *((sensor_event_t *)arg), 0,
				false);

	case SENSOR_READ_VECTOR:
		if (itg3200_get_rotation(hal, &sample)) {
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
