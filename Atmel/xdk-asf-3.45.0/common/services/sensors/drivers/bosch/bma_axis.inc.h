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
#ifndef _BMA_AXIS_H_
#define _BMA_AXIS_H_

#include <asf.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name Bosch Accelerometer Driver Axis Types
 * @{
 */

/**
 * @brief Bosch 8-bit Axis Data Format
 *
 * The BMA222 stores 2's-complement 8-bit axis data samples split across
 * two contiguous 8-bit device locations where the lower address in the
 * device register space stores a 1-bit "new data" flag and the next
 * higher address stores the 8 most significant bits of the axis data.
 */
typedef union {
	int16_t word;

	struct {
		uint16_t unused   : 7;
		uint16_t new_data : 1;
		int16_t acc_msb   : 8;
	} field;
} bma_axis8_t;

/**
 * @brief Bosch 10-bit Axis Data Format
 *
 * The BMA020, BMA150, and BMA250 store 2's-complement 10-bit axis data
 * samples split across two contiguous 8-bit device locations where the
 * lower address in the device register space stores a 1-bit "new data"
 * flag and the next higher locations store the 10 most significant bits
 * of the axis data.
 */
typedef union {
	int16_t word;

	struct {
		uint16_t acc_lsb  : 2;
		uint16_t unused   : 5;
		uint16_t new_data : 1;
		int16_t acc_msb   : 8;
	} field;
} bma_axis10_t;

/**
 * @brief Bosch 14-bit Axis Data Format
 *
 * The BMA180 stores 2's-complement 14-bit axis data samples split across
 * two contiguous 8-bit device locations where the lower address in the
 * device register space stores the 6 least significant bits and the next
 * higher address stores the 8 most significant bits of the axis data.
 */
typedef union {
	int16_t word;

	struct {
		uint16_t acc_lsb  : 6;
		uint16_t unused   : 1;
		uint16_t new_data : 1;
		int16_t acc_msb   : 8;
	} field;
} bma_axis14_t;

/** @} */

/**
 * @name Bosch Accelerometer Driver Axis Value (type conversion)
 * @{
 */

/**
 * @brief Construct a signed value from a raw axis sample.
 *
 * The BMA222 returns little-endian 2's-complement 8-bit axis values
 * stored within a 16-bit word.
 *
 * @param   axis    An bma_axis8_t type storing a raw sensor axis sample.
 * @return          The aligned and sign-extended axis data value.
 */
static inline int16_t bma_axis8_val(const bma_axis8_t axis)
{
#if UC3
	return axis.field.acc_msb;
#elif XMEGA
	return (axis.word >> 8);
#endif
}

/**
 * @brief Construct a signed value from a raw axis sample.
 *
 * The BMA020, BMA150, and BMA250 return little-endian 2's-complement
 * 10-bit axis values stored within a 16-bit word.
 *
 * @param   axis    An bma_axis10_t type storing a raw sensor axis sample.
 * @return          The aligned and sign-extended axis data value.
 */
static inline int16_t bma_axis10_val(const bma_axis10_t axis)
{
#if UC3
	return (axis.field.acc_msb << 2) | (axis.field.acc_lsb);
#elif XMEGA
	return (axis.word >> 6);
#endif
}

/**
 * @brief Construct a signed value from a raw axis sample.
 *
 * The BMA180 returns little-endian 2's-complement 14-bit axis values
 * stored within a 16-bit word.
 *
 * @param   axis    An bma_axis14_t type storing a raw sensor axis sample.
 * @return          The aligned and sign-extended axis data value.
 */
static inline int16_t bma_axis14_val(const bma_axis14_t axis)
{
#if UC3
	return (axis.field.acc_msb << 6) | (axis.field.acc_lsb);
#elif XMEGA
	return (axis.word >> 2);
#endif
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif
