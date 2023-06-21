/**
 * \file
 *
 * \brief Bosch BMA150 3-axis accelerometer driver.
 *
 * This file contains functions for initializing and reading data
 * from a Bosch BMA150 3-axis accelerometer.
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
#ifndef _BMA150_H_
#define _BMA150_H_

#include <asf.h>

#ifdef __cplusplus
extern "C" {
#endif

/* TWI/I2C address (write @ 0x70 on bus, read @ 0x71 on bus) */
#define BMA150_TWI_ADDR            (0x38)
#define BMA150_SPI_MODE            (3)

/* Sensor Data Resolution and Offsets */
#define BMA150_DATA_RESOLUTION     (10)     /* signed axis data size (bits) */
#define BMA150_TEMP_OFFSET         (-30)    /* temperature center (Celsius) */

/** \brief BMA150 Register Addresses */
/** @{ */
#define BMA150_CHIP_ID             (0x00)   /* chip ID - always 0x02 */
#define BMA150_CHIP_VERSION        (0x01)   /* chip revision */
#define BMA150_ACC_X_LSB           (0x02)   /* X accel - LSB + new data */
#define BMA150_ACC_X_MSB           (0x03)   /* X accel - MSB */
#define BMA150_ACC_Y_LSB           (0x04)   /* Y accel - LSB + new data */
#define BMA150_ACC_Y_MSB           (0x05)   /* Y accel - MSB */
#define BMA150_ACC_Z_LSB           (0x06)   /* Z accel - LSB + new data */
#define BMA150_ACC_Z_MSB           (0x07)   /* Z accel - MSB */
#define BMA150_TEMP                (0x08)   /* temperature */
#define BMA150_STATUS1             (0x09)   /* device status register 1 */
#define BMA150_CTRL1               (0x0a)   /* device control register 1 */
#define BMA150_CTRL2               (0x0b)   /* device control register 2 */
#define BMA150_LG_THRES            (0x0c)   /* low g threshold */
#define BMA150_LG_DUR              (0x0d)   /* low g duration */
#define BMA150_HG_THRES            (0x0e)   /* high g threshold */
#define BMA150_HG_DUR              (0x0f)   /* high g duration */
#define BMA150_ANY_MOTION_THRES    (0x10)   /* any motion threshold */
#define BMA150_CTRL3               (0x11)   /* device control register 3 */
#define BMA150_CUST1               (0x12)   /* customer reserved reg 1 */
#define BMA150_CUST2               (0x13)   /* customer reserved reg 2 */
#define BMA150_CTRL4               (0x14)   /* range and bandwidth */
#define BMA150_CTRL5               (0x15)   /* device control register 5 */
/** @} */

/** \brief BMA150 Default Setting Register Addresses */
/** @{ */
#define BMA150_GAIN_OFF_X          (0x16)   /* gain & offset LSB - X */
#define BMA150_GAIN_OFF_Y          (0x17)   /* gain & offset LSB - Y */
#define BMA150_GAIN_OFF_Z          (0x18)   /* gain & offset LSB - Z */
#define BMA150_GAIN_OFF_T          (0x19)   /* gain & offset LSB - temp */
#define BMA150_OFFSET_X            (0x1a)   /* offset MSB - X */
#define BMA150_OFFSET_Y            (0x1b)   /* offset MSB - Y */
#define BMA150_OFFSET_Z            (0x1c)   /* offset MSB - Z */
#define BMA150_OFFSET_T            (0x1d)   /* offset MSB - temperature */
/** @} */

/** \brief BMA150 Default Setting Register Addresses (EEPROM) */
/** @{ */
#define BMA150_EE_CTRL2            (0x2b)   /* device control register 2 */
#define BMA150_EE_LG_THRES         (0x2c)   /* low g threshold */
#define BMA150_EE_LG_DUR           (0x2d)   /* low g duration */
#define BMA150_EE_HG_THRES         (0x2e)   /* high g threshold */
#define BMA150_EE_HG_DUR           (0x2f)   /* high g duration */
#define BMA150_EE_ANY_MOTION_THRES (0x30)   /* any motion threshold */
#define BMA150_EE_CTRL3            (0x31)   /* device control register 3 */
#define BMA150_EE_CUST1            (0x32)   /* customer reserved reg 1 */
#define BMA150_EE_CUST2            (0x33)   /* customer reserved reg 2 */
#define BMA150_EE_CTRL4            (0x34)   /* range and bandwidth */
#define BMA150_EE_CTRL5            (0x35)   /* device control register 3 */
#define BMA150_EE_GAIN_OFF_X       (0x36)   /* gain & offset LSB - X */
#define BMA150_EE_GAIN_OFF_Y       (0x37)   /* gain & offset LSB - Y */
#define BMA150_EE_GAIN_OFF_Z       (0x38)   /* gain & offset LSB - Z */
#define BMA150_EE_GAIN_OFF_T       (0x39)   /* gain & offset LSB - temp */
#define BMA150_EE_OFFSET_X         (0x3a)   /* offset MSB - X */
#define BMA150_EE_OFFSET_Y         (0x3b)   /* offset MSB - Y */
#define BMA150_EE_OFFSET_Z         (0x3c)   /* offset MSB - Z */
#define BMA150_EE_OFFSET_T         (0x3d)   /* offset MSB - temperature */
/** @} */

/** \brief BMA150 Register Bit Definitions */
/** @{ */

/* BMA150_CHIP_ID (0x00) */

#define BMA150_ID_VAL              (0x02)   /* BMA150 chip id value */

/* BMA150_STATUS1 (0x09) */

#define STATUS1_ALERT_PHASE        (0x10)   /* motion alert phase */
#define STATUS1_ST_RESULT          (0x80)   /* self test result (1=pass) */

/* BMA150_CTRL1 (0x0a) */

#define CTRL1_EE_W                 (0x10)   /* enable default setting access */
#define CTRL1_UDPATE_IMAGE         (0x20)   /* copy eeprom to image reg's */

/* Bosch BMA020 / BMA150 Common Register Definitions */

/* BMA_ACC_X_LSB (0x02), BMA_ACC_Y_LSB (0x04), BMA_ACC_Z_LSB (0x06) */

#define ACC_NEW_DATA                (0x01)  /* new data available */
#define ACC_LSB_0_1                 (0xc0)  /* bits 0 and 1 of accel reading */

/* BMA_STATUS1 (0x09) */

#define STATUS1_HG                  (0x01)  /* high-g currently detected */
#define STATUS1_LG                  (0x02)  /* low-g currently detected */
#define STATUS1_HG_LATCHED          (0x04)  /* high-g event detected */
#define STATUS1_LG_LATCHED          (0x08)  /* low-g event detected */

/* BMA_CTRL1 (0x0a) */

#define CTRL1_SLEEP                 (0x01)   /* enter sleep mode */
#define CTRL1_SOFT_RESET            (0x02)   /* reset device */
#define CTRL1_SELF_TEST_0           (0x04)   /* perform self test 0 */
#define CTRL1_SELF_TEST_1           (0x08)   /* perform self test 1 */
#define CTRL1_RESET_INT             (0x40)   /* reset interrupt */

/* BMA_CTRL2 (0x0b) */

#define CTRL2_ENABLE_LG             (0x01)   /* enable low g interrupt */
#define CTRL2_ENABLE_HG             (0x02)   /* enable high g interrupt */
#define CTRL2_COUNTER_LG            (0x0c)   /* low g int count (2 bits) */
#define CTRL2_COUNTER_HG            (0x30)   /* high g int count (2 bits) */
#define CTRL2_ANY_MOTION            (0x40)   /* enable any-motion interrupt */
#define CTRL2_ALERT                 (0x80)   /* enable any-motion alert mode */

/* BMA_CTRL3 (0x11) */

#define CTRL3_LG_HYST               (0x07)   /* low g hysteresis (3 bits) */
#define CTRL3_HG_HYST               (0x28)   /* high g hysteresis (3 bits) */
#define CTRL3_ANY_MOTION_DUR        (0xc0)   /* any motion duration (2 bits) */

/* BMA_CTRL4 (0x14) */

#define CTRL4_BANDWIDTH             (0x07)  /* bandwidth (3 bits) */
#define BANDWIDTH_25HZ              (0x00)  /*   25 Hz */
#define BANDWIDTH_50HZ              (0x01)  /*   50 Hz */
#define BANDWIDTH_100HZ             (0x02)  /*   100 Hz */
#define BANDWIDTH_190HZ             (0x03)  /*   190 Hz */
#define BANDWIDTH_375HZ             (0x04)  /*   375 Hz */
#define BANDWIDTH_750HZ             (0x05)  /*   750 Hz */
#define BANDWIDTH_1500HZ            (0x06)  /*   1500 Hz */
#define CTRL4_RANGE                 (0x18)  /* range (2 bits) */
#define RANGE_2G                    (0x00)  /*   +/- 2g */
#define RANGE_4G                    (0x08)  /*   +/- 4g */
#define RANGE_8G                    (0x10)  /*   +/- 8g */

/* BMA_CTRL5 (0x15) */

#define CTRL5_WAKE_UP              (0x01)   /* enable automatic wake up */
#define CTRL5_WAKE_UP_PAUSE        (0x06)   /* duration between wakes, 2bits */
#define CTRL5_SHADOW_DIS           (0x08)   /* disable lsb/msb read blocking */
#define CTRL5_LATCH_INT            (0x10)   /* latch interrupts until reset */
#define CTRL5_NEW_DATA_INT         (0x20)   /* enable new data interrupt */
#define CTRL5_ENABLE_ADV_INT       (0x40)   /* enable advanced interrupts */
#define CTRL5_SPI4                 (0x80)   /* SPI uses 4-wire interface */

/** @} */

extern bool bma150_init(sensor_t *, int);

#ifdef __cplusplus
}
#endif

#endif
