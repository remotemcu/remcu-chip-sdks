/**
 * \file
 *
 * \brief Osram SFH5712 light sensor driver.
 *
 * This file contains functions for initializing and reading data
 * from a Osram SFH5712 light sensor.
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
#ifndef _SFH5712_H_
#define _SFH5712_H_

#include <asf.h>

#ifdef __cplusplus
extern "C" {
#endif

/* TWI/I2C address (write @ 0x52 on bus, read @ 0x53 on bus) */

#define SFH5712_TWI_ADDR            (0x29)

/* Signed 16-bit axis data sample resolution and alignment */

#define SFH5712_DATA_RESOLUTION     (16)

/** \brief SFH5712 Register Addresses */
/** @{ */

#define SFH5712_ALS_CONTROL         (0x80)   /* ambient light sensor control */
#define SFH5712_PART_ID             (0x8A)   /* part id & revision */
#define SFH5712_MAN_ID              (0x8B)   /* manufacturer id */
#define SFH5712_ALS_DATA_LSB        (0x8C)   /* light meas data (low 8 bits) */
#define SFH5712_ALS_DATA_MSB        (0x8D)   /* light meas data (high 8 bits) */

/** @} */

/** \brief SFH5712 Register Bit Definitions */
/** @{ */

/* SFH5712_ALS_CONTROL (0x80) ambient light sensor control */

#define ALS_MODE_MASK               (0x03)  /* light sensor mode mask */
#define ALS_MODE_STANDBY            (0x00)  /* standby mode (default) */
#define ALS_MODE_ACTIVE             (0x03)  /* active mode */

/* SFH5712_PART_ID (0x8A) part ID and revision */

#define PART_REV_MASK               (0x0F)   /* SFH5712 chip revision bit mask */
#define PART_ID_MASK                (0xF0)   /* SFH5712 chip id bit mask */
#define PART_ID_SHIFT               (0x04)   /* bit shift for part ID (upper 4
	                                      * bits) */

#define SFH5712_PART_ID_VAL         (0x80)   /* expected chip id field value */
#define SFH5712_PART_REV_VAL        (0x04)   /* expected chip revision field
	                                      * value */

/* SFH5712_MAN_ID (0x8B) */

#define SFH5712_MAN_ID_VAL          (0x03)   /* expected manufacturer id value */

/** @} */

extern bool sfh5712_init(sensor_t *, int);

#ifdef __cplusplus
}
#endif

#endif
