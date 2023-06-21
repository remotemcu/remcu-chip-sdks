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
#ifndef _BMP_COMMON_H_
#define _BMP_COMMON_H_

#include <asf.h>

#ifdef __cplusplus
extern "C" {
#endif

/* TWI/I2C address (write @ 0xee on bus, read @ 0xef on bus) */
#define BMP_TWI_ADDR               (0x77)

/** \brief BMP Register Addresses */
/** @{ */
#define BMP_CHIP_ID                (0xd0)   /* chip ID - always 0x55 */
#define BMP_CHIP_VERSION           (0xd1)   /* chip revision */
#define BMP_SOFT_RESET             (0xe0)   /* reset device */
#define BMP_CONTROL                (0xf4)   /* device control register */
#define BMP_DATA_MSB               (0xf6)   /* temp. or press. data MSB */
#define BMP_DATA_LSB               (0xf7)   /* temp. or press. data LSB */
#define BMP_DATA_XLSB              (0xf8)   /* press. data XLSB (19 bit data) */
/** @} */

/* EEPROM Calibration Coefficient Addresses (MSB | LSB) */

#define BMP_EEPROM_ADDR            (0xaa)   /* BMP085/BMP180 EEPROM base address */
#define BMP_EEPROM_SIZE_BYTES      (22)     /* BMP085/BMP180 EEPROM size (bytes) */

/** \brief BMP Register Bit Definitions */
/** @{ */

/* BMP_CHIP_ID (0xd0) */

#define BMP085_ID_VAL              (0x55)   /* BMP085 chip id value */
#define BMP085_VER_VAL             (0x01)   /* BMP085 chip version value */

#define BMP180_ID_VAL              (0x55)   /* BMP180 chip id value */
#define BMP180_VER_VAL             (0x02)   /* BMP180 chip version value */

/* BMP_SOFT_RESET (0xe0) */

#define BMP_RESET_CMD              (0xb6)   /* soft reset command */

/* BMP_CONTROL (0xf4) */

#define BMP_TEMP_READ              (0x2e)   /* read temperature */
#define BMP_PRESS_READ             (0x34)   /* read pressure (@ osrs = 0) */

/* Operating Ranges */

#define BMP_MIN_hPa                (300)    /* +9 000 (m) above sea level */
#define BMP_MAX_hPa                (1100)   /* -500 (m) above sea level */

#define BMP_MIN_COUNTS             (0)
#define BMP_MAX_COUNTS             (0xfffful)

/** @} */

extern bool bmp085_init(sensor_t *, int);
extern bool bmp180_init(sensor_t *, int);

#ifdef __cplusplus
}
#endif

#endif
