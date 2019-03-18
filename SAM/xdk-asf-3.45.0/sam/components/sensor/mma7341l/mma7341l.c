/**
 * \file
 *
 * \brief API driver for MMA7341L accelerometer component.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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

/**
 * \defgroup mma7341l_sensor_group MEMS Sensors - Accelerometer MMA7341L
 *
 * Low-level driver for the Accelerometer MMA7341L. This driver provides access to the main
 * features of the Accelerometer MMA7341L.
 *
 * \{
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "sysclk.h"
#include "gpio.h"
#include "mma7341l.h"
#include "adc.h"
#include "pmc.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
 extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/* Fixed point for tangent tan(15)*0x40 */
#define TAN15 17
/* Sample number in calibration */
#define MMA7341L_SAMPLES  16

#if SAM3S || SAM4S || SAM3XA || SAM3N
/* Tracking Time*/
#define  TRACKING_TIME            1
/* Transfer Period */
#define  TRANSFER_PERIOD       1 
#endif

#if SAM3U
#ifdef MMA7341L_USE_ADC12
/* Start Up Time */
#define   STARTUP_TIME                           7
/* Off Mode Startup Time */
#define   OFF_MODE_STARTUP_TIME      7
#else
#define   STARTUP_TIME                           3
#endif
/* Sample & Hold Time */
#define   SAMPLE_HOLD_TIME   6
#endif

#if SAM3S || SAM4S || SAM3XA || SAM3N
#define mma7341l_adc_get_x_channel_value()    adc_get_channel_value(ADC, (enum adc_channel_num_t)uc_adc_channel_x)
#define mma7341l_adc_get_y_channel_value()    adc_get_channel_value(ADC, (enum adc_channel_num_t)uc_adc_channel_y)
#define mma7341l_adc_get_z_channel_value()    adc_get_channel_value(ADC, (enum adc_channel_num_t)uc_adc_channel_z)
#define mma7341l_adc_x_conversion_end()       while ((adc_get_status(ADC) & MMA7341L_EOC_X) != MMA7341L_EOC_X)
#define mma7341l_adc_y_conversion_end()       while ((adc_get_status(ADC) & MMA7341L_EOC_Y) != MMA7341L_EOC_Y)
#define mma7341l_adc_z_conversion_end()       while ((adc_get_status(ADC) & MMA7341L_EOC_Z) != MMA7341L_EOC_Z)
#define mma7341l_adc_start()                  adc_start(ADC)
#define mma7341l_adc_enable_clock()           pmc_enable_periph_clk(ID_ADC)
#define mma7341l_adc_init()                   adc_init(ADC, sysclk_get_cpu_hz(), MMA7341L_ADC_CLK, ADC_STARTUP_TIME_4)
#if SAM3S || SAM4S || SAM3XA
#define mma7341l_adc_configure_timing()       adc_configure_timing(ADC, TRACKING_TIME, ADC_SETTLING_TIME_3, TRANSFER_PERIOD)
#elif SAM3N
#define mma7341l_adc_configure_timing()       adc_configure_timing(ADC, TRACKING_TIME)
#endif
#if SAM3S8 || SAM4S || SAM3N || SAM3SD8
#define mma7341l_adc_configure_power_save()   adc_configure_power_save(ADC, 0, 0)
#endif
#define mma7341l_adc_configure_trigger()      adc_configure_trigger(ADC, ADC_TRIG_SW, 0)
#define mma7341l_adc_set_resolution()         adc_set_resolution(ADC, (enum adc_resolution_t)ADC_MR_LOWRES_BITS_10)
#define mma7341l_adc_enable_channel();        adc_enable_channel(ADC,(enum adc_channel_num_t) uc_adc_channel_x);  \
                                              adc_enable_channel(ADC, (enum adc_channel_num_t)uc_adc_channel_y);   \
                                              adc_enable_channel(ADC, (enum adc_channel_num_t)uc_adc_channel_z);
#define mma7341l_adc_disable_channel();       adc_disable_channel(ADC, (enum adc_channel_num_t)uc_adc_channel_x);   \
                                              adc_disable_channel(ADC, (enum adc_channel_num_t)uc_adc_channel_y);   \
                                              adc_disable_channel(ADC, (enum adc_channel_num_t)uc_adc_channel_z);
#elif SAM3U
#if defined MMA7341L_USE_ADC12
#define mma7341l_adc_get_x_channel_value() \
		adc12b_get_channel_value(ADC12B,   \
		(enum adc_channel_num_t)uc_adc_channel_x)
#define mma7341l_adc_get_y_channel_value() \
		adc12b_get_channel_value(ADC12B,   \
		(enum adc_channel_num_t)uc_adc_channel_y)
#define mma7341l_adc_get_z_channel_value() \
		adc12b_get_channel_value(ADC12B,   \
		(enum adc_channel_num_t)uc_adc_channel_z)
#define mma7341l_adc_x_conversion_end() \
		while ((adc12b_get_status(ADC12B) & MMA7341L_EOC_X) \
		!= MMA7341L_EOC_X)
#define mma7341l_adc_y_conversion_end() \
		while ((adc12b_get_status(ADC12B) & MMA7341L_EOC_Y) \
		!= MMA7341L_EOC_Y)
#define mma7341l_adc_z_conversion_end() \
		while ((adc12b_get_status(ADC12B) & MMA7341L_EOC_Z) \
		!= MMA7341L_EOC_Z)
#define mma7341l_adc_start()                  adc12b_start(ADC12B)
#define mma7341l_adc_enable_clock()           pmc_enable_periph_clk(ID_ADC12B)
#define mma7341l_adc_init() \
		adc12b_init(ADC12B, sysclk_get_cpu_hz(), MMA7341L_ADC_CLK, STARTUP_TIME, OFF_MODE_STARTUP_TIME)
#define mma7341l_adc_configure_timing() \
		adc12b_configure_timing(ADC12B, SAMPLE_HOLD_TIME)
#define mma7341l_adc_configure_power_save() \
		adc12b_configure_power_save(ADC12B, 0, 0)
#define mma7341l_adc_configure_trigger() \
		adc12b_configure_trigger(ADC12B, ADC12B_TRIG_SW)
#define mma7341l_adc_set_resolution() \
		adc12b_set_resolution(ADC12B, \
		(enum adc_resolution_t)ADC12B_MR_LOWRES_BITS_10)
#define mma7341l_adc_enable_channel(); \
		adc12b_enable_channel(ADC12B, \
		(enum adc_channel_num_t)uc_adc_channel_x); \
		adc12b_enable_channel(ADC12B, \
		(enum adc_channel_num_t)uc_adc_channel_y); \
		adc12b_enable_channel(ADC12B, \
		(enum adc_channel_num_t)uc_adc_channel_z);
#define mma7341l_adc_disable_channel(); \
		adc12b_disable_channel(ADC12B,  \
		(enum adc_channel_num_t)uc_adc_channel_x); \
		adc12b_disable_channel(ADC12B, \
		(enum adc_channel_num_t)uc_adc_channel_y); \
		adc12b_disable_channel(ADC12B, \
		(enum adc_channel_num_t)uc_adc_channel_z);

#elif defined MMA7341L_USE_ADC10
#define mma7341l_adc_get_x_channel_value() \
		adc_get_channel_value(ADC, (enum adc_channel_num_t)uc_adc_channel_x)
#define mma7341l_adc_get_y_channel_value() \
		adc_get_channel_value(ADC, (enum adc_channel_num_t)uc_adc_channel_y)
#define mma7341l_adc_get_z_channel_value() \
		adc_get_channel_value(ADC, (enum adc_channel_num_t)uc_adc_channel_z)
#define mma7341l_adc_x_conversion_end() \
		while ((adc_get_status(ADC) & MMA7341L_EOC_X) != MMA7341L_EOC_X)
#define mma7341l_adc_y_conversion_end() \
		while ((adc_get_status(ADC) & MMA7341L_EOC_Y) != MMA7341L_EOC_Y)
#define mma7341l_adc_z_conversion_end() \
		while ((adc_get_status(ADC) & MMA7341L_EOC_Z) != MMA7341L_EOC_Z)
#define mma7341l_adc_start()                  adc_start(ADC)
#define mma7341l_adc_enable_clock()           pmc_enable_periph_clk(ID_ADC)
#define mma7341l_adc_init() \
		adc_init(ADC, sysclk_get_cpu_hz(), MMA7341L_ADC_CLK, STARTUP_TIME)
#define mma7341l_adc_configure_timing()       adc_configure_timing(ADC, SAMPLE_HOLD_TIME)
#define mma7341l_adc_configure_power_save()   adc_configure_power_save(ADC, 0)
#define mma7341l_adc_configure_trigger() \
		adc_configure_trigger(ADC, ADC_TRIG_SW)
#define mma7341l_adc_set_resolution() \
		adc_set_resolution(ADC, (enum adc_resolution_t)ADC_MR_LOWRES_BITS_10)
#define mma7341l_adc_enable_channel(); \
		adc_enable_channel(ADC,(enum adc_channel_num_t) uc_adc_channel_x); \
		adc_enable_channel(ADC, (enum adc_channel_num_t)uc_adc_channel_y); \
		adc_enable_channel(ADC, (enum adc_channel_num_t)uc_adc_channel_z);
#define mma7341l_adc_disable_channel(); \
		adc_disable_channel(ADC, (enum adc_channel_num_t)uc_adc_channel_x); \
		adc_disable_channel(ADC, (enum adc_channel_num_t)uc_adc_channel_y); \
		adc_disable_channel(ADC, (enum adc_channel_num_t)uc_adc_channel_z);
#else
#error No ADC peripheral defined
#endif
#endif

/* Accelerometer Instance */
acc_t acc = {
	.m = {.x = 0,.y = 0,.z = 0},
	.k = {.x = MMA7341L_ZERO_X,.y = MMA7341L_ZERO_Y,.z = MMA7341L_ZERO_Z},
	.ak = {.x = 0,.y = 0,.z = 0},
};

/* Channel For Accelerometer X, Y and Z */
static uint8_t uc_adc_channel_x, uc_adc_channel_y, uc_adc_channel_z;

/* The voltage value when the gravity value is 1g or 0g */
static float f_volt_1g, f_volt_0g;

/**
 * \brief Addition of two Position axis values.
 *
 * \return The addition value.
 */
static xyz_t mma7341l_xyz_add(xyz_t p, xyz_t q)
{
	xyz_t r;
	r.x = p.x + q.x;
	r.y = p.y + q.y;
	r.z = p.z + q.z;
	return r;
}

/**
 * \brief Subtraction of two Position axis values.
 *
 * \return The subtraction value.
 */
static xyz_t mma7341l_xyz_diff(xyz_t p, xyz_t q)
{
	xyz_t r;
	r.x = p.x - q.x;
	r.y = p.y - q.y;
	r.z = p.z - q.z;
	return r;
}

/**
 * \brief Get converted data from x,y,z axis.
 *
 * \return Converted data for three channels.
 */
static xyz_t mma7341l_get_value(void)
{
	xyz_t val;

	mma7341l_adc_x_conversion_end();
	val.x = (int32_t)mma7341l_adc_get_x_channel_value();
	mma7341l_adc_y_conversion_end();
	val.y = (int32_t)mma7341l_adc_get_y_channel_value();
	mma7341l_adc_z_conversion_end();
	val.z = (int32_t)mma7341l_adc_get_z_channel_value();

	val.x = val.x >> MMA7341L_SHIFT;
	val.y = val.y >> MMA7341L_SHIFT;
	val.z = val.z >> MMA7341L_SHIFT;

	return val;
}

/**
 * \brief Update ADC channel conversion value.
 */
static void mma7341l_update(void)
{
	acc.m = mma7341l_get_value();
	/* Start new measurement */
	mma7341l_adc_start();
}

/**
 * \brief Calibrate MMA7341L component and set the present axis value.
 */
void mma7341l_calibration(void)
{
	volatile uint32_t i;

	acc.m.x = 0;
	acc.m.y = 0;
	acc.m.z = 0;
	for (i = 0; i < MMA7341L_SAMPLES; i++) {
		xyz_t temp = mma7341l_get_value();
		acc.m = mma7341l_xyz_add(acc.m, temp);
		mma7341l_adc_start();
	}
	acc.m.x = acc.m.x / MMA7341L_SAMPLES;
	acc.m.y = acc.m.y / MMA7341L_SAMPLES;
	acc.m.z = acc.m.z / MMA7341L_SAMPLES;

	f_volt_0g = (acc.m.x + acc.m.y) * 3.3 / (2 * 1024);
	f_volt_1g = acc.m.z * 3.3 / 1024;

	acc.k = acc.m;
}

/**
 * \brief Initialize MMA7341L.
 *
 */
void mma7341l_init(void)
{
	uc_adc_channel_x = MMA7341L_ADC_CHANNEL_X;
	uc_adc_channel_y = MMA7341L_ADC_CHANNEL_Y;
	uc_adc_channel_z = MMA7341L_ADC_CHANNEL_Z;

	/* ADC configuration */
	mma7341l_adc_enable_clock();
	mma7341l_adc_init();
	mma7341l_adc_configure_timing();
#if SAM3S8 || SAM4S || SAM3N || SAM3SD8 || SAM3U	
	mma7341l_adc_configure_power_save();
#endif
	mma7341l_adc_configure_trigger();
	mma7341l_adc_set_resolution();

	/* Enable 3 channels for x, y and z */
	mma7341l_adc_enable_channel();

	/* Start measurement */
	mma7341l_adc_start();
}

/**
 * \brief Set MMA7341L working mode.
 *
 * \param uc_mode Working mode value (1 is normal and 0 is sleep).
 */
void mma7341l_set_mode(uint8_t uc_mode)
{
	if (uc_mode) {
		gpio_set_pin_high(PIN_MMA7341L_MODE);
		/* Enable 3 channels for x, y and z */
		mma7341l_adc_enable_channel();
	} else {
		gpio_set_pin_low(PIN_MMA7341L_MODE);
		/* Disable 3 channels for x, y and z */
		mma7341l_adc_disable_channel();
	}
}

/**
 * \brief Get the gravity value of x,y,z axis.
 *
 * \return Gravity value of x,y,z axis.
 */
xyz_g_t mma7341l_get_gravity_value(void)
{
	xyz_g_t xyz_g;

	mma7341l_update();

	xyz_g.x_g = (((float)(acc.m.x) / 1024) * 3.3 - f_volt_0g) / (f_volt_1g - f_volt_0g);
	xyz_g.y_g = (((float)(acc.m.y) / 1024) * 3.3 - f_volt_0g) / (f_volt_1g - f_volt_0g);
	xyz_g.z_g = (((float)(acc.m.z) / 1024) * 3.3 - f_volt_0g) / (f_volt_1g - f_volt_0g);

	return xyz_g;
}

/**
 * \brief Check if the tilt angle is big enough. If yes, get rotation direction
 * according to the sign of two axes.
 *
 * \return Rotation direction.
 */
uint32_t mma7341l_get_rotation_dir(void)
{
	uint32_t dir = MMA7341L_UNCHANGED;
	int32_t x = 0, y = 0, z = 0;

	mma7341l_update();

	acc.ak = mma7341l_xyz_diff(acc.m, acc.k);

	x = acc.ak.x;
	y = acc.ak.y;
	z = (acc.ak.z + MMA7341L_1G);

	if ((uint32_t) (x * x) << 12 > (TAN15 * TAN15) * (y * y + z * z)
			|| (uint32_t) (y * y) << 12 > (TAN15 * TAN15) * (x * x + z * z)) {
		if ((uint32_t) (x * x) << 12 > (TAN15 * TAN15) * (y * y + z * z)) {
			if ((uint32_t) (y * y) << 12 > (TAN15 * TAN15) * (x * x + z * z)) {
				if (x < 0) {
					if (y < 0) {
						dir = MMA7341L_UP_RIGHT;
					} else {
						dir = MMA7341L_DOWM_RIGHT;
					}
				} else {
					if (y < 0) {
						dir = MMA7341L_UP_LEFT;
					} else {
						dir = MMA7341L_DOWN_LEFT;
					}
				}
			} else {
				if (x < 0) {
					dir = MMA7341L_RIGHT;
				} else {
					dir = MMA7341L_LEFT;
				}
			}
		} else {
			if (y < 0) {
				dir = MMA7341L_UP;
			} else {
				dir = MMA7341L_DOWN;
			}
		}
	}
	return dir;
}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \}
 */
