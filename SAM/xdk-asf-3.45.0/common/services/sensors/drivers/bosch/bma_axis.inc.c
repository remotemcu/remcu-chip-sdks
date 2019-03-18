/**
 * \file
 *
 * \brief Bosch Digital, triaxial acceleration sensor axis format
 *
 * This module defines accelerometer axis data types and utility routines
 * used in multiple Bosch sensor drivers, including BMA020, BMA150, BMA180,
 * BMA220, BMA222, and BMA250 devices.
 *
 * The module relies upon conditionally compiled types and functions to
 * generate functions specialized for a particular driver module. Driver
 * source modules include this module directly via the C-preprocessor
 * with a #include directive.
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
#ifndef _BMA_AXIS_C_
#define _BMA_AXIS_C_

#include "bma_axis.inc.h"

#if defined(_BMA020_H_)
#   define bma_axis_t       bma_axis10_t
#   define bma_axis_val     bma_axis10_val
#elif defined(_BMA150_H_)
#   define bma_axis_t       bma_axis10_t
#   define bma_axis_val     bma_axis10_val
#elif defined(_BMA180_H_)
#   define bma_axis_t       bma_axis14_t
#   define bma_axis_val     bma_axis14_val
#elif defined(_BMA220_H_)
#   define bma_axis_t       int8_t
#   define bma_axis_val(x)  ((int8_t)((x) >> 2))
#elif defined(_BMA222_H_)
#   define bma_axis_t       bma_axis8_t
#   define bma_axis_val     bma_axis8_val
#elif defined(_BMA250_H_)
#   define bma_axis_t       bma_axis10_t
#   define bma_axis_val     bma_axis10_val
#endif

#if defined(bma_axis_t)

/**
 * @brief Format Bosch 3-axis accelerometer data samples
 *
 * This routine formats Bosch 3-axis accelerometer data using tunable
 * configuration parameters controlling device orientation and flags that
 * indicate whether or not axis data should be scaled in engineering units.
 *
 * @param   hal     Address of an initialized sensor hardware descriptor.
 * @param   acc     Bosch accelerometer axis data samples.
 * @param   data    Address of sensor_data_t structure to return values.
 * @return          Nothing
 */
static void format_axis_data(const sensor_hal_t *hal, const bma_axis_t acc[],
		sensor_data_t *data)
{
	/* Get axis values based based on device orientation configuration. */
	int32_t const acc_x = hal->orientation.x.sign *
			bma_axis_val(acc[hal->orientation.x.axis]);

	int32_t const acc_y = hal->orientation.y.sign *
			bma_axis_val(acc[hal->orientation.y.axis]);

	int32_t const acc_z = hal->orientation.z.sign *
			bma_axis_val(acc[hal->orientation.z.axis]);

	/* Convert raw sensor sample to engineering units if requested. */
	if (data->scaled) {
		data->axis.x = raw_to_scaled(hal, acc_x);
		data->axis.y = raw_to_scaled(hal, acc_y);
		data->axis.z = raw_to_scaled(hal, acc_z);
	} else {
		data->axis.x = acc_x;
		data->axis.y = acc_y;
		data->axis.z = acc_z;
	}
}

#endif

#endif
