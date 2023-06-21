/**
 * \file
 *
 * \brief Bosch Digital pressure sensor common definitions
 *
 * This module defines registers, constants, data structures, and
 * global function prototypes that are common to multiple Bosch sensor
 * drivers, in particular those for BMP085 and BMP180 devices.
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
#include "bmp.h"

static bool bmp_device_id(sensor_hal_t *, sensor_data_t *);
static bool bmp_get_cal_param(sensor_hal_t *);
static bool bmp_get_pressure(sensor_hal_t *, sensor_data_t *);
static bool bmp_get_temperature(sensor_hal_t *, sensor_data_t *);
static bool bmp_set_state(sensor_hal_t *, sensor_state_t);
static bool bmp_read(sensor_t *, sensor_read_t, sensor_data_t *);
static bool bmp_ioctl(sensor_t *, sensor_command_t, void *);

/** \brief  BMP "oversampling_setting" mode values */
typedef enum {
	OSS_LOW_POWER  = 0, /**< Ultra low power       (1 internal samples) */
	OSS_STANDARD   = 1, /**< Standard              (2 internal samples) */
	OSS_HIGH       = 2, /**< High resolution       (4 internal samples) */
	OSS_ULTRA_HIGH = 3  /**< Ultra high resolution (8 internal samples) */
} osrs_t;

/**
 * @brief BMP085 & BMP180 calibration coeffs
 *
 * Every sensor module has unique individual coefficients stored in the device
 * EEPROM.  Before pressure and temperature can be calculated these values must
 * be read and stored for use in the compensated (i.e. "real") temperature and
 * pressure calculations.
 *
 * This data structure and macros below define a type that stores calibration
 * coefficients for Bosch BMP085, BMP180, or SMD500 pressure sensors.  The
 * fields are named per the Bosch documentation defining the compensated
 * temperature and pressure equations that require these coefficients.
 *
 * The driver currently statically allocates storage for only one copy of
 * the calibration coefficients.  In the event that a system is built with
 * multiple BMP085 (for example) pressure sensors this scheme will not work,
 * as each physical device will require a device-specific copy of the coeffs
 * for use in compensated temperature and pressure calculations for the device.
 */
typedef struct {
	int16_t ac1;
	int16_t ac2;
	int16_t ac3;
	uint16_t ac4;
	uint16_t ac5;
	uint16_t ac6;

	int16_t b1;
	int16_t b2;

	int16_t mb;
	int16_t mc;
	int16_t md;
} bmp_caldata_t;

static osrs_t sensor_oss;
static bmp_caldata_t caldata;

#define BMP_RESOLUTION  (24 - (8 - sensor_oss))

#define AC1     (caldata.ac1)
#define AC2     (caldata.ac2)
#define AC3     (caldata.ac3)
#define AC4     (caldata.ac4)
#define AC5     (caldata.ac5)
#define AC6     (caldata.ac6)
#define B1      (caldata.b1)
#define B2      (caldata.b2)
#define Mb      (caldata.mb)
#define Mc      (caldata.mc)
#define Md      (caldata.md)

/**
 * @brief Bosch BMP085 barometric sensor driver initialization.
 *
 * This is the main initialization function for the BMP085 device.
 *
 * @param   sensor  Address of a sensor device descriptor.
 * @param   resvd   Reserved value.
 * @return  bool    true if the sensor is ready for use, else false.
 */
bool bmp085_init(sensor_t *sensor, int resvd)
{
	bool status = false;

	sensor_hal_t *const hal = sensor->hal;

	if ((BMP085_ID_VAL == sensor_bus_get(hal, BMP_CHIP_ID)) &&
			(BMP085_VER_VAL ==
			sensor_bus_get(hal, BMP_CHIP_VERSION))) {
		status = bmp_get_cal_param(hal);

		/* Set the driver function table and capabilities pointer. */
		static const sensor_device_t bmp085_device = {
			.func.read    = bmp_read,
			.func.ioctl   = bmp_ioctl,
			.caps.feature = SENSOR_CAPS_AUX_TEMP,
			.caps.vendor  = SENSOR_VENDOR_BOSCH,
			.caps.units   = SENSOR_UNITS_pascal,
			.caps.name    = "BMP085 Digital pressure sensor"
		};

		sensor->drv = &bmp085_device;

		/* The initial "normal" execution state corresponds to the
		 * BMP085 standard mode (2 internal samples) with 17-bit data
		 * resolution and an average current @ 1 sample/s of typically
		 * 5 microamps.
		 */
		sensor_oss = OSS_STANDARD;

		hal->resolution = BMP_RESOLUTION;
	}

	return status;
}

/**
 * @brief Bosch BMP180 barometric sensor driver initialization.
 *
 * This is the main initialization function for the BMP180 device.
 *
 * @param sensor    Address of a sensor device descriptor.
 * @param resvd     Reserved value.
 * @return bool     true if the sensor is ready for use, else false.
 */
bool bmp180_init(sensor_t *sensor, int resvd)
{
	bool status = false;

	sensor_hal_t *const hal = sensor->hal;

	if ((BMP180_ID_VAL == sensor_bus_get(hal, BMP_CHIP_ID)) &&
			(BMP180_VER_VAL ==
			sensor_bus_get(hal, BMP_CHIP_VERSION))) {
		status = bmp_get_cal_param(hal);

		/* Set the driver function table and capabilities pointer. */
		static const sensor_device_t bmp180_device = {
			.func.read    = bmp_read,
			.func.ioctl   = bmp_ioctl,
			.caps.feature = SENSOR_CAPS_AUX_TEMP,
			.caps.vendor  = SENSOR_VENDOR_BOSCH,
			.caps.units   = SENSOR_UNITS_pascal,
			.caps.name    = "BMP180 Digital pressure sensor"
		};

		sensor->drv = &bmp180_device;

		/* The initial "normal" execution state corresponds to the
		 * BMP180 standard mode (2 internal samples) with 17-bit data
		 * resolution and an average current @ 1 sample/s of typically
		 * 5 microamps.
		 */
		sensor_oss = OSS_STANDARD;

		hal->resolution = BMP_RESOLUTION;
	}

	return status;
}

/**
 * @brief Read BMP085 / BMP180 calibration coefficients.
 *
 * Calculating temperature in degrees C or pressure in Pa requires the use of
 * calibration data coefficients stored in the BMP EEPROM.  Every sensor
 * module has individual coefficients.  Before the first calculation of
 * temperature and pressure, the master reads this data from device EEPROM.
 *
 * @param hal   Address of an initialized sensor HAL descriptor.
 * @retval  bool    "true" if valid coefficients have been fetched
 * @retval  bool    "false" for errors reading the device coefficients
 */
static bool bmp_get_cal_param(sensor_hal_t *hal)
{
	/* Set an intermediate buffer to known invalid values (0 or ffff). */
	uint8_t *const coeffs = (uint8_t [BMP_EEPROM_SIZE_BYTES]) {0};

	/* Attempt to fetch calibration coefficients from the slave EEPROM. */
	const size_t bytes_read = sensor_bus_read
				(hal, BMP_EEPROM_ADDR, coeffs,
				BMP_EEPROM_SIZE_BYTES);

	AC1 = ((uint16_t)coeffs[ 0] << 8) | coeffs[ 1];
	AC2 = ((uint16_t)coeffs[ 2] << 8) | coeffs[ 3];
	AC3 = ((uint16_t)coeffs[ 4] << 8) | coeffs[ 5];
	AC4 = ((uint16_t)coeffs[ 6] << 8) | coeffs[ 7];
	AC5 = ((uint16_t)coeffs[ 8] << 8) | coeffs[ 9];
	AC6 = ((uint16_t)coeffs[10] << 8) | coeffs[11];

	B1  = ((uint16_t)coeffs[12] << 8) | coeffs[13];
	B2  = ((uint16_t)coeffs[14] << 8) | coeffs[15];

	Mb  = ((uint16_t)coeffs[16] << 8) | coeffs[17];
	Mc  = ((uint16_t)coeffs[18] << 8) | coeffs[19];
	Md  = ((uint16_t)coeffs[20] << 8) | coeffs[21];

	return (BMP_EEPROM_SIZE_BYTES == bytes_read);
}

/**
 * @brief Wait for completion of sensor analog-to-digital conversion.
 *
 * Per the Bosch BMP085 & BMP180 data sheets there will be a delay between
 * the time when a data measurement is requested and the sensor internal
 * A/D conversion is complete.  The maximum conversion varies according
 * to the oversampling mode.
 *
 * Instead of waiting for the maximum conversion time, the end of
 * conversion (EOC) digital sensor output, which is connected to a
 * port on the "Atmel Sensor Board", can be tested for a completed
 * conversion.
 *
 * @param hal   Address of an initialized sensor HAL descriptor.
 * @return  Nothing.
 */
static inline void bmp_eoc_wait(sensor_hal_t *hal)
{
	/**
	 * \brief Poll the End Of Conversion (EOC) input pin.
	 *
	 * This works on the BMP085 but not on the BMP180.
	 *
	 * while (gpio_pin_is_low (hal->mcu_sigint));
	 */
	delay_ms(2 + (3 << sensor_oss));
}

/**
 * @brief Get an uncompensated pressure (UP) reading.
 *
 * This routine gets a raw pressure sample reading from a Bosch BMP085 or
 * BMP180 device.  In the event of a sensor or bus error, a 32-bit value
 * of -1 (all bits set) may be returned from this routine.
 *
 * @param hal   Address of an initialized sensor HAL descriptor.
 * @return  An uncompensated pressure reading.
 */
static int32_t bmp_get_up(sensor_hal_t *hal)
{
	int32_t UP = -1;

	uint8_t buff[3];

	sensor_bus_put(hal, BMP_CONTROL, BMP_PRESS_READ + (sensor_oss << 6));

	bmp_eoc_wait(hal);

	if (sensor_bus_read(hal, BMP_DATA_MSB, buff, sizeof(buff))) {
		UP = ((uint32_t)buff[0] << 16) | ((uint32_t)buff[1] << 8) | buff[2];
	}

	return (UP >> (8 - sensor_oss));
}

/**
 * @brief Get an uncompensated temperature (UT) reading.
 *
 * This routine gets a raw temperature sample reading from the a BMP085 or
 * BMP180 device.  In the event of a sensor or bus error, a 32-bit value
 * of -1 (all bits set) may be returned from this routine.
 *
 * @param hal   Address of an initialized sensor HAL descriptor.
 * @return  An uncompensated temperature reading.
 */
static int32_t bmp_get_ut(sensor_hal_t *hal)
{
	int32_t UT = -1;

	uint8_t buff[2];

	sensor_bus_put(hal, BMP_CONTROL, BMP_TEMP_READ);

	/* The conversion time for temperature is 4.5ms at most. */
	delay_ms(5);

	if (sensor_bus_read(hal, BMP_DATA_MSB, buff, sizeof(buff))) {
		UT = ((uint32_t)buff[0] << 8) | buff[1];
	}

	return UT;
}

/**
 * @brief Get a pressure sensor sample.
 *
 * If scaled data format is selected for the device, this routine gets a
 * compensated "true pressure" sample using the sampling mode specified
 * when the device was initialized.  Otherwise a raw uncompensated pressure
 * reading is returned in "data".
 *
 * @param sensor    Address of an initialized sensor device descriptor.
 * @param data      The address where pressure samples are returned.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bmp_get_pressure(sensor_hal_t *hal, sensor_data_t *data)
{
	int32_t const UP = bmp_get_up(hal);

	if (data->scaled == false) {
		data->pressure.value = UP;
	} else {
		/* The compensated pressure in pascal (Pa) units. */
		int32_t const UT = bmp_get_ut(hal);

		int32_t const x1 = ((UT - AC6) * AC5) >> 15;
		int32_t const x2 = ((int32_t)Mc << 11) / (x1 + Md);

		int32_t const B5 = (x1 + x2);
		int32_t const B6 = B5 - 4000L;

		int32_t X1 = (B2 * ((B6 * B6) >> 12)) >> 11;
		int32_t X2 = (AC2 * B6) >> 11;
		int32_t X3 = X1 + X2;

		int32_t const B3 = ((((int32_t)AC1 * 4 + X3) << sensor_oss) + 2) >> 2;

		X1 = (AC3 * B6) >> 13;
		X2 = (B1 * ((B6 * B6) >> 12)) >> 16;
		X3 = ((X1 + X2) + 2) >> 2;

		uint32_t const B4 = (AC4 * (uint32_t)(X3 + 32768L)) >> 15;
		uint32_t const B7 = (UP - B3) * (50000L >> sensor_oss);

		int32_t P = (B7 < 0x80000000UL) ? ((B7 << 1) / B4) : ((B7 / B4) << 1);

		X1 = (P >> 8);
		X1 = (X1 * X1 * 3038L) >> 16;
		X2 = (-7357L * P) >> 16;

		P += ((X1 + X2 + 3791L) >> 4);

		data->pressure.value = P;
	}

	return true;
}

/**
 * @brief Get a temperature sensor sample.
 *
 * If scaled data format is selected for the device, this routine gets a
 * compensated "true temperature" sample.  Otherwise, a raw uncompensated
 * temperature reading is returned in "data".
 *
 * @param sensor    Address of an initialized sensor device descriptor.
 * @param data      The address where temperature samples are returned.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bmp_get_temperature(sensor_hal_t *hal, sensor_data_t *data)
{
	int32_t const UT = bmp_get_ut(hal);

	if (false == data->scaled) {
		data->temperature.value = UT;
	} else {
		/* The compensated temperature in 0.1 degrees C units. */
		int32_t const x1 = ((UT - AC6) * AC5) >> 15;
		int32_t const x2 = ((int32_t)Mc << 11) / (x1 + Md);

		data->temperature.value = ((x1 + x2) + 8) >> 4;
	}

	return true;
}

/**
 * @brief Read sensor device ID and revision numbers.
 *
 * This function reads the sensor hardware identification registers
 * and returns these values to the addresses specified in the function
 * parameters.
 *
 * @param sensor    Address of an initialized sensor device descriptor.
 * @param data      Address of sensor_data_t structure to return values.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bmp_device_id(sensor_hal_t *hal, sensor_data_t *data)
{
	data->device.id = (uint32_t)sensor_bus_get(hal, BMP_CHIP_ID);
	data->device.version = (uint8_t)sensor_bus_get(hal, BMP_CHIP_VERSION);

	return true;
}

/**
 * @brief Set the BMP085 / BMP180 execution mode.
 *
 * This routine sets a specified BMP085 or BMP180 execution state to one
 * of the following:
 *
 *  SENSOR_STATE_LOWEST_POWER or SENSOR_STATE_LOW_POWER
 *      Ultra low power mode (1 internal sample).  In this mode the average
 *      current @ 1 sample/s is typically 3 microamps.
 *
 *  SENSOR_STATE_NORMAL
 *      Standard mode (2 internal samples).  In this mode the average current @
 *      1 sample/s is typically 5 microamps.
 *
 *  SENSOR_STATE_HIGH_POWER
 *      High resolution mode (4 internal samples).  In this mode the average
 *      current @ 1 sample/s is typically 7 microamps.
 *
 *  SENSOR_STATE_HIGHEST_POWER
 *      Ultra high resolution mode (8 internal samples).  In this mode the
 *      average current @ 1 sample/s is 12 microamps.
 *
 *  SENSOR_STATE_RESET
 *      This function resets the device and internal registers to the power-up
 *      default settings.
 *
 * @param sensor    Address of an initialized sensor device descriptor.
 * @param state     A specified sensor operational state.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bmp_set_state(sensor_hal_t *hal, sensor_state_t state)
{
	/* \todo  Handle Sleep & Suspend states. */

	switch (state) {
	default:
		return false;

	case SENSOR_STATE_LOWEST_POWER:
	case SENSOR_STATE_LOW_POWER:

		sensor_oss = OSS_LOW_POWER;
		break;

	case SENSOR_STATE_NORMAL:

		sensor_oss = OSS_STANDARD;
		break;

	case SENSOR_STATE_HIGH_POWER:

		sensor_oss = OSS_HIGH;
		break;

	case SENSOR_STATE_HIGHEST_POWER:

		sensor_oss = OSS_ULTRA_HIGH;
		break;

	case SENSOR_STATE_RESET:

		/**
		 * \brief Activate, then deactivate, the master reset pin (XCLR).
		 *
		 * This works on the BMP085 but not on the BMP180.
		 *
		 * gpio_set_pin_low  (hal->mcu_sigout);
		 * gpio_set_pin_high (hal->mcu_sigout);
		 */
		sensor_bus_put(hal, BMP_SOFT_RESET, BMP_RESET_CMD);
		break;
	}

	hal->resolution = BMP_RESOLUTION;

	return true;
}

/**
 * @brief Read sensor data
 *
 * If scaled data format is selected for the device, this routine gets a
 * compensated "true pressure" sample using the sampling mode specified
 * when the device was initialized.  Otherwise a raw uncompensated pressure
 * reading is returned in "data".
 *
 * @param sensor    Address of an initialized sensor device descriptor.
 * @param type      Type of sensor data to read.
 * @param data      The address where pressure samples are returned.
 * @return bool     true if the call succeeds, else false is returned.
 */
static bool bmp_read(sensor_t *sensor, sensor_read_t type, sensor_data_t *data)
{
	switch (type) {
	case SENSOR_READ_PRESSURE:
		return bmp_get_pressure(sensor->hal, data);

	case SENSOR_READ_TEMPERATURE:
		return bmp_get_temperature(sensor->hal, data);

	case SENSOR_READ_ID:
		return bmp_device_id(sensor->hal, data);

	default:
		sensor->err = SENSOR_ERR_FUNCTION;
		return false;
	}
}

/**
 * @brief BMP085 / BMP180 ioctl control entry point
 *
 * @param   hal     Address of an initialized sensor device descriptor.
 * @param   cmd     Command to execute
 * @param   arg     Argument for command (varies)
 * @return  bool    true if the call succeeds, else false is returned.
 */
static bool bmp_ioctl(sensor_t *sensor, sensor_command_t cmd, void *arg)
{
	sensor_hal_t *const hal = sensor->hal;
	bool status = false;

	switch (cmd) {
	case SENSOR_SET_STATE:
		status = bmp_set_state(hal, *((sensor_state_t *)arg));
		break;

	default:
		sensor->err = SENSOR_ERR_UNSUPPORTED;
		break;
	}

	return status;
}
