/**
 * \file
 *
 * \brief AKM AK8975 3-axis magnetometer.
 *
 * This file contains functions for initializing and reading data
 * from a AKM AK8975 3-axis magnetometer.
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
#ifndef _AK8975_H_
#define _AK8975_H_

#include <asf.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AK8975_TWI_ADDR             (0x0c)  /* TWI/I2C slave address */

/** Signed axis data sample resolution (bits) */
#define AK8975_DATA_RESOLUTION      (13)

/** Device sensitivity (scaling) */
#define MICRO_TESLA_PER_COUNT       (0.3)   /* from AK8975 data sheet */

/** \brief Self-test Definitions */
/** @{ */
#define AK8975_TEST_X_MIN           (-100)  /* min X */
#define AK8975_TEST_X_MAX           (100)   /* max X */
#define AK8975_TEST_Y_MIN           (-100)  /* min Y */
#define AK8975_TEST_Y_MAX           (100)   /* max Y */
#define AK8975_TEST_Z_MIN           (-1000) /* min Z */
#define AK8975_TEST_Z_MAX           (-300)  /* max Z */
/** @} */

/** \brief AK8975 Register Addresses */
/** @{ */
#define AK8975_REG_WIA              (0x00)  /* device ID */
#define AK8975_REG_INFO             (0x01)  /* information */
#define AK8975_REG_ST1              (0x02)  /* data status 1 */
#define AK8975_REG_HXL              (0x03)  /* x-axis data (low) */
#define AK8975_REG_HXH              (0x04)  /* x-axis data (high) */
#define AK8975_REG_HYL              (0x05)  /* y-axis data (low) */
#define AK8975_REG_HYH              (0x06)  /* y-axis data (high) */
#define AK8975_REG_HZL              (0x07)  /* z-axis data (low) */
#define AK8975_REG_HZH              (0x08)  /* z-axis data (high) */
#define AK8975_REG_ST2              (0x09)  /* data status 2 */
#define AK8975_REG_CNTL1            (0x0a)  /* control 1 */
#define AK8975_REG_CNTL2            (0x0b)  /* reserved (do not access) */
#define AK8975_REG_ASTC             (0x0c)  /* self-test */
#define AK8975_REG_TS1              (0x0d)  /* test 1 (do not access) */
#define AK8975_REG_TS2              (0x0e)  /* test 2 (do not access) */
#define AK8975_REG_I2CDIS           (0x0f)  /* I2C disable */
/** @} */

/*
 * Values from 10h to 12h can be read only in Fuse access mode.
 * In other modes, read data is not correct.
 */
#define AK8975_REG_ASAX             (0x10)  /* x-axis sensitivity adjust */
#define AK8975_REG_ASAY             (0x11)  /* y-axis sensitivity adjust */
#define AK8975_REG_ASAZ             (0x12)  /* z-axis sensitivity adjust */

/** \brief AK8975 Register Bit Definitions */
/** @{ */

/* AK8975_REG_WIA (0x00) */

#define AK8975_WIA_VALUE            (0x48)  /* AK8975 device ID value */

/* AK8975_REG_ST1 (0x02) */

#define AK8975_DATA_READY           (0x01)  /* data ready in single mode */

/* AK8975_REG_ST2 (0x09) */

#define AK8975_DERR                 (0x04)  /* data read error event */
#define AK8975_HOFL                 (0x08)  /* magnetic sensor overflow event */

/* AK8975_REG_CNTL1 (0x0a) */

#define AK8975_POWER_DOWN_MODE      (0x00)  /* set power down mode */
#define AK8975_SINGLE_MODE          (0x01)  /* set single measurement mode */
#define AK8975_SELF_TEST_MODE       (0x08)  /* set self-test mode */
#define AK8975_FUSE_READ_MODE       (0x0f)  /* set fuse ROM access mode */

/* AK8975_REG_ASTC (0x0c) */

#define AK8975_ASTC_SELF            (0x40)  /* enable self-test mode */

/** @} */

/** Sensor Layout Type Constants */
typedef enum {
	OBVERSE_0DEG,   /**< Obverse / standard position */
	OBVERSE_90DEG,  /**< Obverse / rotates counterclockwise by 90  deg. */
	OBVERSE_180DEG, /**< Obverse / rotates counterclockwise by 180 deg. */
	OBVERSE_270DEG, /**< Obverse / rotates counterclockwise by 270 deg. */
	REVERSE_0DEG,   /**< Reverse / standard position */
	REVERSE_90DEG,  /**< Reverse / rotates counterclockwise by 90  deg. */
	REVERSE_180DEG, /**< Reverse / rotates counterclockwise by 180 deg. */
	REVERSE_270DEG  /**< Reverse / rotates counterclockwise by 270 deg. */
} LAYOUT;

extern bool ak8975_init(sensor_t *, int);

#ifdef __cplusplus
}
#endif

#endif
