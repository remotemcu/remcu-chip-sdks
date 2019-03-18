/**
 * \file
 *
 * \brief Bosch BMA180 3-axis accelerometer driver.
 *
 * This file contains functions for initializing and reading data
 * from a Bosch BMA180 3-axis accelerometer.
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
#ifndef _BMA180_H_
#define _BMA180_H_

#include <asf.h>

#ifdef __cplusplus
extern "C" {
#endif

/* TWI/I2C address (write @ 0x80 on bus, read @ 0x81 on bus) */
#define BMA180_TWI_ADDR             (0x40)
#define BMA180_SPI_MODE             (3)

/* Signed 16-bit axis data sample resolution and alignment */
#define BMA180_DATA_RESOLUTION      (14)
#define BMA180_TEMP_OFFSET          (-40)   /* temperature sensor offset */

/** \brief BMA180 Register Addresses */
/** @{ */
#define BMA180_CHIP_ID              (0x00)  /* chip ID - always 0x03 */
#define BMA180_CHIP_VERSION         (0x01)  /* chip revision */
#define BMA180_ACC_X_LSB            (0x02)  /* X accel - LSB + new data */
#define BMA180_ACC_X_MSB            (0x03)  /* X accel - MSB */
#define BMA180_ACC_Y_LSB            (0x04)  /* Y accel - LSB + new data */
#define BMA180_ACC_Y_MSB            (0x05)  /* Y accel - MSB */
#define BMA180_ACC_Z_LSB            (0x06)  /* Z accel - LSB + new data */
#define BMA180_ACC_Z_MSB            (0x07)  /* Z accel - MSB */
#define BMA180_TEMP                 (0x08)  /* temperature */
#define BMA180_STATUS1              (0x09)  /* device status register 1 */
#define BMA180_STATUS2              (0x0a)  /* device status register 2 */
#define BMA180_STATUS3              (0x0b)  /* device status register 3 */
#define BMA180_STATUS4              (0x0c)  /* device status register 4 */
#define BMA180_CTRL0                (0x0d)  /* device control register 0 */
#define BMA180_CTRL1                (0x0e)  /* device control register 1 */
#define BMA180_CTRL2                (0x0f)  /* device control register 2 */
#define BMA180_RESET                (0x10)  /* soft reset */
/** @} */

/** \brief BMA180 Default Setting Register Addresses */
/** @{ */
#define BMA180_BW_TCS               (0x20)  /* bandwidth & temp compensation */
#define BMA180_CTRL3                (0x21)  /* device control register 3 */
#define BMA180_CTRL4                (0x22)  /* device control register 4 */
#define BMA180_HY                   (0x23)  /* hysteresis */
#define BMA180_SLOPE_TAPSENS_INFO   (0x24)  /* slope & tap sense info */
#define BMA180_HIGH_LOW_INFO        (0x25)  /* high & low info */
#define BMA180_LOW_DUR              (0x26)  /* low g duration */
#define BMA180_HIGH_DUR             (0x27)  /* high g duration */
#define BMA180_TAPSENS_TH           (0x28)  /* tap sense threshold */
#define BMA180_LOW_TH               (0x29)  /* low g threshold */
#define BMA180_HIGH_TH              (0x2a)  /* high g threshold */
#define BMA180_SLOPE_TH             (0x2b)  /* slope threshold */
#define BMA180_CD1                  (0x2c)  /* customer data 1 */
#define BMA180_CD2                  (0x2d)  /* customer data 2 */
#define BMA180_TCO_X                (0x2e)  /* temp compensation - X */
#define BMA180_TCO_Y                (0x2f)  /* temp compensation - Y */
#define BMA180_TCO_Z                (0x30)  /* temp compensation - Z */
#define BMA180_GAIN_T               (0x31)  /* gain - temperature */
#define BMA180_GAIN_X               (0x32)  /* gain - X */
#define BMA180_GAIN_Y               (0x33)  /* gain - Y */
#define BMA180_GAIN_Z               (0x34)  /* gain - Z */
#define BMA180_OFFSET_LSB1          (0x35)  /* offset LSB (X) & range */
#define BMA180_OFFSET_LSB2          (0x36)  /* offset LSB (Y & Z) */
#define BMA180_OFFSET_T             (0x37)  /* offset - temperature */
#define BMA180_OFFSET_X             (0x37)  /* offset MSB - X */
#define BMA180_OFFSET_Y             (0x38)  /* offset MSB - Y */
#define BMA180_OFFSET_Z             (0x39)  /* offset MSB - Z */
/** @} */

/** \brief BMA180 Default Setting Register Addresses (EEPROM) */
/** @{ */
#define BMA180_EE_BW_TCS            (0x20)  /* bandwidth & temp compensation */
#define BMA180_EE_CTRL_REG3         (0x21)  /* device control register 3 */
#define BMA180_EE_CTRL_REG4         (0x22)  /* device control register 4 */
#define BMA180_EE_HY                (0x23)  /* hysteresis */
#define BMA180_EE_SLOPE_TAPSENS     (0x24)  /* slope & tap sense info */
#define BMA180_EE_HIGH_LOW          (0x25)  /* high & low info */
#define BMA180_EE_LOW_DUR           (0x26)  /* low g duration */
#define BMA180_EE_HIGH_DUR          (0x27)  /* high g duration */
#define BMA180_EE_TAPSENS_TH        (0x28)  /* tap sense threshold */
#define BMA180_EE_LOW_TH            (0x29)  /* low g threshold */
#define BMA180_EE_HIGH_TH           (0x2a)  /* high g threshold */
#define BMA180_EE_SLOPE_TH          (0x2b)  /* slope threshold */
#define BMA180_EE_CD1               (0x2c)  /* customer data 1 */
#define BMA180_EE_CD2               (0x2d)  /* customer data 2 */
#define BMA180_EE_TCO_X             (0x2e)  /* temp compensation - X */
#define BMA180_EE_TCO_Y             (0x2f)  /* temp compensation - Y */
#define BMA180_EE_TCO_Z             (0x30)  /* temp compensation - Z */
#define BMA180_EE_GAIN_T            (0x31)  /* gain - temperature */
#define BMA180_EE_GAIN_X            (0x32)  /* gain - X */
#define BMA180_EE_GAIN_Y            (0x33)  /* gain - Y */
#define BMA180_EE_GAIN_Z            (0x34)  /* gain - Z */
#define BMA180_EE_OFFSET_LSB1       (0x35)  /* offset LSB (X) & range */
#define BMA180_EE_OFFSET_LSB2       (0x36)  /* offset LSB (Y & Z) */
#define BMA180_EE_OFFSET_T          (0x37)  /* offset - temperature */
#define BMA180_EE_OFFSET_X          (0x37)  /* offset MSB - X */
#define BMA180_EE_OFFSET_Y          (0x38)  /* offset MSB - Y */
#define BMA180_EE_OFFSET_Z          (0x39)  /* offset MSB - Z */
/** @} */

/** \brief BMA180 Register Bit Definitions */
/** @{ */

/* BMA180_CHIP_ID (0x00) */

#define BMA180_ID_VAL               (0x03)  /* BMA180 chip id value */

/* BMA180_ACC_X_LSB (0x02), BMA180_ACC_Y_LSB (0x04), BMA180_ACC_Z_LSB (0x06) */

#define ACC_NEW_DATA                (0x01)  /* new data available */
#define ACC_LSB_0_5                 (0xfc)  /* bits 0 to 5 of accel reading */

/* BMA180_STATUS1 (0x09) */

#define STATUS1_EE_WRITE            (0x01)  /* eeprom write in progress */
#define STATUS1_OFFSET_ST_S         (0x02)  /* offset or self-test complete */
#define STATUS1_SLOPE_SIGN_Z_INT    (0x04)  /* Z slope sign (0=pos 1=neg) */
#define STATUS1_SLOPE_SIGN_Y_INT    (0x08)  /* Y slope sign (0=pos 1=neg) */
#define STATUS1_SLOPE_SIGN_X_INT    (0x10)  /* X slope sign (0=pos 1=neg) */
#define STATUS1_ALERT               (0x20)  /* slope alert */
#define STATUS1_SELF_TEST_RESULT    (0x40)  /* test result (0=fail 1=pass) */
#define STATUS1_FIRST_TAPSENS_S     (0x80)  /* first tap detected */

/* BMA180_STATUS2 (0x0a) */

#define STATUS2_LOW_SIGN_Z_INT      (0x01)  /* Z low-g sign (0=pos 1=neg) */
#define STATUS2_LOW_SIGN_Y_INT      (0x02)  /* Y low-g sign (0=pos 1=neg) */
#define STATUS2_LOW_SIGN_X_INT      (0x04)  /* X low-g sign (0=pos 1=neg) */
#define STATUS2_TAPSENS_S           (0x10)  /* tap event */
#define STATUS2_SLOPE_S             (0x20)  /* slope event */
#define STATUS2_LOW_TH_S            (0x40)  /* low-g threshold event */
#define STATUS2_HIGH_TH_S           (0x80)  /* high-g threshold event */

/* BMA180_STATUS3 (0x0b) */

#define STATUS3_Z_FIRST_INT         (0x01)  /* first Z axis interrupt */
#define STATUS3_Y_FIRST_INT         (0x02)  /* first Y axis interrupt */
#define STATUS3_X_FIRST_INT         (0x04)  /* first X axis interrupt */
#define STATUS3_TAPSENS_INT         (0x10)  /* tap detected interrupt */
#define STATUS3_SLOPE_INT_S         (0x20)  /* slope event interrupt */
#define STATUS3_LOW_TH_INT          (0x40)  /* low-g event interrupt */
#define STATUS3_HIGH_TH_INT         (0x80)  /* high-g event interrupt */

/* BMA180_STATUS4 (0x0c) */

#define STATUS4_TAPSENS_SIGN_Z_INT  (0x04)  /* Z tap sign (0=pos, 1=neg) */
#define STATUS4_TAPSENS_SIGN_Y_INT  (0x08)  /* Y tap sign (0=pos, 1=neg) */
#define STATUS4_TAPSENS_SIGN_X_INT  (0x10)  /* X tap sign (0=pos, 1=neg) */
#define STATUS4_HIGH_SIGN_Z_INT     (0x20)  /* Z high-g sign (0=pos 1=neg) */
#define STATUS4_HIGH_SIGN_Y_INT     (0x40)  /* Y high-g sign (0=pos 1=neg) */
#define STATUS4_HIGH_SIGN_X_INT     (0x80)  /* X high-g sign (0=pos 1=neg) */

/* BMA180_CTRL0 (0x0d) */

#define CTRL0_DIS_WAKE_UP           (0x01)  /* disable wake-up mode */
#define CTRL0_SLEEP_MODE            (0x02)  /* enter sleep mode */
#define CTRL0_ST0                   (0x04)  /* self-test 0 (electrostatic) */
#define CTRL0_ST1                   (0x08)  /* self-test 1 (digital only) */
#define CTRL0_EE_W                  (0x10)  /* enable image/eeprom reg write */
#define CTRL0_UPDATE_IMAGE          (0x20)  /* copy eeprom to image regs */
#define CTRL0_RESET_INT             (0x40)  /* reset latched interrupt */
#define CTRL0_ST_DAMP               (0x80)  /* use damping in self test */

/* BMA180_CTRL1 (0x0e) */

#define CTRL1_SEL_Z                 (0x01)  /* internal only - do not use */
#define CTRL1_SEL_Y                 (0x02)  /* internal only - do not use */
#define CTRL1_SEL_X                 (0x04)  /* internal only - do not use */
#define CTRL1_SEL_T                 (0x08)  /* internal only - do not use */
#define CTRL1_EN_OFFSET_Z           (0x20)  /* enable offset regulation - Z */
#define CTRL1_EN_OFFSET_Y           (0x40)  /* enable offset regulation - Y */
#define CTRL1_EN_OFFSET_X           (0x80)  /* enable offset regulation - X */

/* BMA180_CTRL2 (0x0f) */

#define CTRL2_ST_AMP                (0x0e)  /* self-test amplitude (3 bits) */
#define CTRL2_UNLOCK_EE             (0xf0)  /* internal only - do not use */

/* BMA180_RESET (0x10) */

#define SOFT_RESET_VAL              (0xb6)  /* write value for soft reset */

/* BMA180_BW_TCS (0x20) */

#define TCS                         (0x0f)  /* temp compensation (4 bits) */
#define TCS_NEG_4_0_PCT             (0x00)  /*    -4.0% */
#define TCS_NEG_3_5_PCT             (0x01)  /*    -3.5% */
#define TCS_NEG_3_0_PCT             (0x02)  /*    -3.0% */
#define TCS_NEG_2_5_PCT             (0x03)  /*    -2.5% */
#define TCS_NEG_2_0_PCT             (0x04)  /*    -2.0% */
#define TCS_NEG_1_5_PCT             (0x05)  /*    -1.5% */
#define TCS_NEG_1_0_PCT             (0x06)  /*    -1.0% */
#define TCS_NEG_0_5_PCT             (0x07)  /*    -0.5% */
#define TCS_0_0_PCT                 (0x08)  /*     0.0% (default) */
#define TCS_0_5_PCT                 (0x09)  /*    +0.5% */
#define TCS_1_0_PCT                 (0x0a)  /*    +1.0% */
#define TCS_1_5_PCT                 (0x0b)  /*    +1.5% */
#define TCS_2_0_PCT                 (0x0c)  /*    +2.0% */
#define TCS_2_5_PCT                 (0x0d)  /*    +2.5% */
#define TCS_3_0_PCT                 (0x0e)  /*    +3.0% */
#define TCS_3_5_PCT                 (0x0f)  /*    +3.5% */
#define BW                          (0xf0)  /* bandwidth (4 bits) */
#define BW_10HZ                     (0x00)  /*    10 Hz */
#define BW_20HZ                     (0x10)  /*    20 Hz */
#define BW_40HZ                     (0x20)  /*    40 Hz */
#define BW_75HZ                     (0x30)  /*    75 Hz */
#define BW_150HZ                    (0x40)  /*   150 Hz (default) */
#define BW_300HZ                    (0x50)  /*   300 Hz */
#define BW_600HZ                    (0x60)  /*   600 Hz */
#define BW_1200HZ                   (0x70)  /*  1200 Hz */
#define BW_HIGH_PASS                (0x80)  /*  1 Hz high pass filter */
#define BW_BAND_PASS                (0x90)  /*  0.2 to 300 Hz band pass fltr */

/* BMA180_CTRL3 (0x21) */

#define CTRL3_LAT_INT               (0x01)  /* latch ints until reset_int */
#define CTRL3_NEW_DATA_INT          (0x02)  /* generate int when new data */
#define CTRL3_ADV_INT               (0x04)  /* enable advanced int controls */
#define CTRL3_TAPSENS_INT_EN        (0x08)  /* enable tap sense interrupt */
#define CTRL3_LOW_INT               (0x10)  /* enable low-g interrupt */
#define CTRL3_HIGH_INT              (0x20)  /* enable high-g interrupt */
#define CTRL3_SLOPE_INT             (0x40)  /* enable slope interrupt */
#define CTRL3_SLOPE_ALERT           (0x80)  /* enable slope alert mode */

/* BMA180_CTRL4 (0x22) */

#define CTRL4_OFFSET_FINETUNING     (0x03)  /* offset fine tuning (2 bits) */
#define CTRL4_FF_CD_R               (0x0c)  /* free fall countdown (2 bits) */
#define CTRL4_MOT_CD_R              (0x30)  /* motion countdown (2 bits) */
#define CTRL4_LOW_HY_LSB            (0xc0)  /* low-g hysteresis (low 2 bits) */

/* BMA180_HY (0x23) */

#define LOW_HY_MSB                  (0x07)  /* low-g hysteresis (high 3bits) */
#define HIGH_HY                     (0xf8)  /* high-g hysteresis (5 bits) */

/* BMA180_SLOPE_TAPSENS_INFO (0x24) */

#define TAPSENS_FILT                (0x01)  /* filter tap sensing */
#define TAPSENS_INT_Z               (0x02)  /* generate int on Z tap */
#define TAPSENS_INT_Y               (0x04)  /* generate int on Y tap */
#define TAPSENS_INT_X               (0x08)  /* generate int on X tap */
#define SLOPE_FILT                  (0x10)  /* filter slope sensing */
#define SLOPE_INT_Z                 (0x20)  /* generate int on Z slope */
#define SLOPE_INT_Y                 (0x40)  /* generate int on Y slope */
#define SLOPE_INT_X                 (0x80)  /* generate int on X slope */

/*  BMA180_HIGH_LOW_INFO (0x25) */

#define LOW_FILT                    (0x01)  /* filter low-g sensing */
#define LOW_INT_Z                   (0x02)  /* generate int on Z low-g */
#define LOW_INT_Y                   (0x04)  /* generate int on Y low-g */
#define LOW_INT_X                   (0x08)  /* generate int on X low-g */
#define HIGH_FILT                   (0x10)  /* filter high-g sensing */
#define HIGH_INT_Z                  (0x20)  /* generate int on Z high-g */
#define HIGH_INT_Y                  (0x40)  /* generate int on Y high-g */
#define HIGH_INT_X                  (0x80)  /* generate int on X high-g */

/* BMA180_LOW_DUR (0x26) */

#define TCO_RANGE                   (0x01)  /* increase temp comp range */
#define LOW_DUR                     (0xfe)  /* low-g detect duration (7bits) */

/* BMA180_LOW_DUR (0x27) */

#define DIS_I2C                     (0x01)  /* disable I2C interface */
#define HIGH_DUR                    (0xfe)  /* high-g detect duration (7bits) */

/* BMA180_TCO_X (0x2e) */

#define SLOPE_DUR                   (0x03)  /* slope detect duration (2bits) */
#define TCO_X                       (0xfc)  /* temp comp value - X (6 bits) */

/* BMA180_TCO_Y (0x2f) */

#define WAKE_UP_DUR                 (0x03)  /* wake up duration (2 bits) */
#define TCO_Y                       (0xfc)  /* temp comp value - Y (6 bits) */

/* BMA180_TCO_Z (0x30) */

#define MODE_CONFIG                 (0x03)  /* std. mode "sub mode" (2 bits) */
#define MODE_LOW_NOISE              (0x00)  /* low noise mode */
#define MODE_SUPER_LOW_NOISE        (0x01)  /* super low noise mode */
#define MODE_ULTRA_LOW_NOISE        (0x02)  /* ultra low noise mode */
#define MODE_LOW_POWER              (0x03)  /* low power mode */
#define TCO_Z                       (0xfc)  /* temp comp value - Z (6 bits) */

/* BMA180_GAIN_T (0x31) */

#define TAPSENS_DUR                 (0x07)  /* tap sense duration (3 bits) */
#define GAIN_T                      (0xf8)  /* temperature gain (5 bits) */

/* BMA180_GAIN_X (0x32) */

#define DIS_REG                     (0x01)  /* disable voltage regulators */
#define GAIN_X                      (0xfe)  /* X gain (7 bits) */

/* BMA180_GAIN_Y (0x33) */

#define SHADOW_DIS                  (0x01)  /* disable MSB/LSB shadowing */
#define GAIN_Y                      (0xfe)  /* Y gain (7 bits) */

/* BMA180_GAIN_Z (0x34) */

#define WAKE_UP                     (0x01)  /* enter normal (wake) mode */
#define GAIN_Z                      (0xfe)  /* Z gain (7 bits) */

/* BMA180_OFFSET_LSB1 (0x35) */

#define SMP_SKIP                    (0x01)  /* enable sample skipping */
#define RANGE                       (0x0e)  /* accel range +/- g (3 bits) */
#define BMA180_RANGE_1G             (0x00)  /*   +/- 1   g */
#define BMA180_RANGE_1_5G           (0x02)  /*   +/- 1.5 g */
#define BMA180_RANGE_2G             (0x04)  /*   +/- 2   g */
#define BMA180_RANGE_3G             (0x06)  /*   +/- 3   g */
#define BMA180_RANGE_4G             (0x08)  /*   +/- 4   g */
#define BMA180_RANGE_8G             (0x0a)  /*   +/- 8   g */
#define BMA180_RANGE_16G            (0x0c)  /*   +/- 16  g */
#define OFFSET_X_LSB                (0xf0)  /* X offset (low 4 bits) */

/* BMA180_OFFSET_LSB2 (0x36) */

#define OFFSET_Y_LSB                (0x0f)  /* Y offset (low 4 bits) */
#define OFFSET_Z_LSB                (0xf0)  /* Z offset (low 4 bits) */

/* BMA180_OFFSET_T (0x37) */

#define READOUT_12BIT               (0x01)  /* enable 12-bit output mode */
#define OFFSET_T                    (0xfe)  /* temperature offset (7 bits) */

/** @} */

extern bool bma180_init(sensor_t *, int);

#ifdef __cplusplus
}
#endif

#endif
