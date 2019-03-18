/**
 * \file
 *
 * \brief Bosch BMA250 3-axis accelerometer driver.
 *
 * This file contains functions for initializing and reading data
 * from a Bosch BMA250 3-axis accelerometer.
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
#ifndef _BMA250_H_
#define _BMA250_H_

#include <asf.h>

#ifdef __cplusplus
extern "C" {
#endif

/* TWI/I2C address (write @ 0x30 on bus, read @ 0x31 on bus) */
#define BMA250_TWI_ADDR         (0x18)
#define BMA250_SPI_MODE         (3)

/* Sensor Data Resolution and Offsets */
#define BMA250_DATA_RESOLUTION  (10)    /* signed axis data size (bits) */
#define BMA250_TEMP_OFFSET      (24)    /* temperature center (Celsius) */

/**
 * @brief Standard Register Addresses (TWI & SPI)
 *
 * w/r=write/read, wo=write only, ro=read only
 */
typedef enum {
	BMA250_CHIP_ID = 0,     /* 0x00 (ro) chip ID (always 0x03) */
	BMA250_01_RSVD,         /* 0x01 reserved */
	BMA250_NEW_DATA_X,      /* 0x02 (ro) X-axis new data flag */
	BMA250_ACC_X,           /* 0x03 (ro) X-axis acceleration */
	BMA250_NEW_DATA_Y,      /* 0x04 (ro) Y-axis new data flag */
	BMA250_ACC_Y,           /* 0x05 (ro) Y-axis acceleration */
	BMA250_NEW_DATA_Z,      /* 0x06 (ro) Z-axis new data flag */
	BMA250_ACC_Z,           /* 0x07 (ro) Z-axis acceleration */
	BMA250_TEMP,            /* 0x08 (ro) temperature */
	BMA250_INTR_STATUS,     /* 0x09 (ro) misc. interrupt status */
	BMA250_NEW_DATA_STATUS, /* 0x0a (ro) new data interrupt status */
	BMA250_TAP_SLOPE_STATUS, /* 0x0b (ro) tap and slope interrupt status */
	BMA250_ORIENTATION_STATUS, /* 0x0c (ro) flat and orientation status */
	BMA250_0D_RSVD,         /* 0x0d reserved */
	BMA250_0E_RSVD,         /* 0x0e reserved */
	BMA250_G_RANGE,         /* 0x0f (w/r) G-range selection */
	BMA250_BANDWIDTH,       /* 0x10 (w/r) bandwidth selection */
	BMA250_POWER_MODES,     /* 0x11 (w/r) power mode configuration */
	BMA250_12_RSVD,         /* 0x12 reserved */
	BMA250_DATA_HIGH_BW,    /* 0x13 (w/r) acceleration data filter */
	BMA250_SOFTRESET,       /* 0x14 (wo) user-triggered software reset */
	BMA250_15_RSVD,         /* 0x15 reserved */
	BMA250_16_INTR_EN,      /* 0x16 (w/r) interrupt enable bits */
	BMA250_17_INTR_EN,      /* 0x17 (w/r) interrupt enable bits */
	BMA250_18_RSVD,         /* 0x18 reserved */
	BMA250_19_INTR_MAP,     /* 0x19 (w/r) interrupt pin mapping */
	BMA250_1A_INTR_MAP,     /* 0x1a (w/r) interrupt pin mapping */
	BMA250_1B_INTR_MAP,     /* 0x1b (w/r) interrupt pin mapping */
	BMA250_1C_RSVD,         /* 0x1c reserved */
	BMA250_1D_RSVD,         /* 0x1d reserved */
	BMA250_INTR_DATA_SRC,   /* 0x1e (w/r) filtered/unfiltered data */
	BMA250_1F_RSVD,         /* 0x1f reserved */
	BMA250_INTR_PIN_CONFIG, /* 0x20 (w/r) interrupt pin configuration */
	BMA250_INTR_PIN_MODE,   /* 0x21 (w/r) interrupt pin mode & reset */
	BMA250_LOW_G_DURATION,  /* 0x22 (w/r) low-g interrupt delay time */
	BMA250_LOW_G_THRESHOLD, /* 0x23 (w/r) low-g interrupt threshold */
	BMA250_EVENT_HYSTERESIS, /* 0x24 (w/r) low-/high-g event hysteresis */
	BMA250_HIGH_G_DURATION, /* 0x25 (w/r) high-g interrupt delay time */
	BMA250_HIGH_G_THRESHOLD, /* 0x26 (w/r) high-g interrupt threshold */
	BMA250_SLOPE_DURATION,  /* 0x27 (w/r) no. samples for slope event */
	BMA250_SLOPE_THRESHOLD, /* 0x28 (w/r) slope event threshold */
	BMA250_29_RSVD,         /* 0x29 reserved */
	BMA250_TAP_TIMING,      /* 0x2a (w/r) single/double tap event timing */
	BMA250_TAP_CONFIG,      /* 0x2b (w/r) wake samples & thresholds */
	BMA250_ORIENTATION_CONFIG, /* 0x2c (w/r) hysteresis, blocking, & mode */
	BMA250_ORIENTATION_THETA, /* 0x2d (w/r) theta blocking angle */
	BMA250_FLAT_THETA,      /* 0x2e (w/r) flat threshold angle */
	BMA250_FLAT_HOLD_TIME,  /* 0x2f (w/r) flat hold time */
	BMA250_30_RSVD,         /* 0x30 reserved */
	BMA250_31_RSVD,         /* 0x31 reserved */
	BMA250_SENSOR_SELF_TEST, /* 0x32 (w/r) self-test settings/activation */
	BMA250_EEPROM_CONTROL,  /* 0x33 (w/r) non-volatile memory control */
	BMA250_DIGITAL_IO_CONTROL, /* 0x34 (w/r) I2C & SPI interface settings */
	BMA250_35_RSVD,         /* 0x35 reserved */
	BMA250_FAST_OFFSET_COMP, /* 0x36 (w/r) fast offset compensation settings */
	BMA250_SLOW_OFFSET_COMP, /* 0x37 (w/r) slow offset compensation settings */
	BMA250_OFFSET_FILT_X,   /* 0x38 (w/r) filtered data compensation x-axis */
	BMA250_OFFSET_FILT_Y,   /* 0x39 (w/r) filtered data compensation y-axis */
	BMA250_OFFSET_FILT_Z,   /* 0x3a (w/r) filtered data compensation z-axis */
	BMA250_OFFSET_UNFILT_X, /* 0x3b (w/r) unfiltered data compensation
	                         * x-axis */
	BMA250_OFFSET_UNFILT_Y, /* 0x3c (w/r) unfiltered data compensation
	                         * y-axis */
	BMA250_OFFSET_UNFILT_Z  /* 0x3d (w/r) unfiltered data compensation
	                         * z-axis */
} bma250_register_t;

/** \brief BMA250 Register Bit Definitions */
/** @{ */

/* BMA250_CHIP_ID (0x00) */

#define BMA250_ID_VAL           (0x03)

/* BMA250_INTR_STATUS (0x09) */

#define BMA250_FLAT_INT         (1 << 7)    /* flat interrupt status */
#define BMA250_ORIENT_INT       (1 << 6)    /* orientation interrupt status */
#define BMA250_S_TAP_INT        (1 << 5)    /* single tap interrupt status */
#define BMA250_D_TAP_INT        (1 << 4)    /* double tap interrupt status */
#define BMA250_SLOPE_INT        (1 << 2)    /* slope interrupt status */
#define BMA250_HIGH_INT         (1 << 1)    /* high-g interrupt status */
#define BMA250_LOW_INT          (1 << 0)    /* low-g interrupt status */

/* BMA250_NEW_DATA_STATUS (0x0a) */

#define BMA250_DATA_INT         (1 << 7)    /* new data interrupt status */

/* BMA250_TAP_SLOPE_STATUS (0x0b) */

#define BMA250_TAP_SIGN_POS     (1 << 7)    /* tap interrupt sign (0=negative) */
#define BMA250_TAP_FIRST_Z      (1 << 6)    /* z-axis triggered tap interrupt */
#define BMA250_TAP_FIRST_Y      (1 << 5)    /* y-axis triggered tap interrupt */
#define BMA250_TAP_FIRST_X      (1 << 4)    /* x-axis triggered tap interrupt */
#define BMA250_SLOPE_SIGN_POS   (1 << 3)    /* slope interrupt sign (0=negative) */
#define BMA250_SLOPE_FIRST_Z    (1 << 2)    /* z-axis triggered slope interrupt */
#define BMA250_SLOPE_FIRST_Y    (1 << 1)    /* y-axis triggered slope interrupt */
#define BMA250_SLOPE_FIRST_X    (1 << 0)    /* x-axis triggered slope interrupt */

/* BMA250_ORIENTATION_STATUS (0x0c) */

#define BMA250_FLAT             (1 << 7)    /* flat condition is fulfilled */
#define BMA250_Z_DOWN           (1 << 6)    /* z-axis orientation (0=upward) */
#define BMA250_XY_PORTRAIT_UP   (0 << 4)    /* x-y plane portrait upright */
#define BMA250_XY_PORTRAIT_DOWN (1 << 4)    /* x-y plane portrait upside-down */
#define BMA250_XY_LANDSCAPE_L   (2 << 4)    /* x-y plane landscape left */
#define BMA250_XY_LANDSCAPE_R   (3 << 4)    /* x-y plane landscape right */
#define BMA250_HIGH_SIGN_NEG    (1 << 3)    /* high-g interrupt sign
	                                     * (0=positive) */
#define BMA250_HIGH_FIRST_Z     (1 << 2)    /* z-axis triggered high-g interrupt */
#define BMA250_HIGH_FIRST_Y     (1 << 1)    /* y-axis triggered high-g interrupt */
#define BMA250_HIGH_FIRST_X     (1 << 0)    /* x-axis triggered high-g interrupt */

/* BMA250_G_RANGE (0x0f) */

#define BMA250_RANGE_2G         (0x03)      /* +/- 2g range (default) */
#define BMA250_RANGE_4G         (0x05)      /* +/- 4g range */
#define BMA250_RANGE_8G         (0x08)      /* +/- 8g range */
#define BMA250_RANGE_16G        (0x0c)      /* +/- 16g range */

/* BMA250_BANDWIDTH (0x10) */

#define BMA250_BANDWIDTH_8Hz    (0x08)      /*   7.81 Hz filtered data bandwidth */
#define BMA250_BANDWIDTH_16Hz   (0x09)      /*  15.63 Hz filtered data bandwidth */
#define BMA250_BANDWIDTH_31Hz   (0x0a)      /*  31.25 Hz filtered data bandwidth */
#define BMA250_BANDWIDTH_63Hz   (0x0b)      /*  62.5 Hz filtered data bandwidth */
#define BMA250_BANDWIDTH_125Hz  (0x0c)      /* 125 Hz filtered data bandwidth */
#define BMA250_BANDWIDTH_250Hz  (0x0d)      /* 250 Hz filtered data bandwidth */
#define BMA250_BANDWIDTH_500Hz  (0x0e)      /* 500 Hz filtered data bandwidth */
#define BMA250_BANDWIDTH_1000Hz (0x0f)      /* 1000 Hz filtered data bandwidth */

/* BMA250_POWER_MODES (0x11) */

#define BMA250_SUSPEND          (1  << 7)   /* set suspend mode (0=reset mode) */
#define BMA250_LOWPOWER_EN      (1  << 6)   /* set low-power mode (0=reset mode) */
#define BMA250_SLEEP_DUR_0_5ms  (5  << 1)   /* 0.5 ms sleep phase duration */
#define BMA250_SLEEP_DUR_1ms    (6  << 1)   /*   1 ms sleep phase duration */
#define BMA250_SLEEP_DUR_2ms    (7  << 1)   /*   2 ms sleep phase duration */
#define BMA250_SLEEP_DUR_4ms    (8  << 1)   /*   4 ms sleep phase duration */
#define BMA250_SLEEP_DUR_6ms    (9  << 1)   /*   6 ms sleep phase duration */
#define BMA250_SLEEP_DUR_10ms   (10 << 1)   /*   6 ms sleep phase duration */
#define BMA250_SLEEP_DUR_25ms   (11 << 1)   /*  25 ms sleep phase duration */
#define BMA250_SLEEP_DUR_50ms   (12 << 1)   /*  50 ms sleep phase duration */
#define BMA250_SLEEP_DUR_100ms  (13 << 1)   /* 100 ms sleep phase duration */
#define BMA250_SLEEP_DUR_500ms  (14 << 1)   /* 500 ms sleep phase duration */
#define BMA250_SLEEP_DUR_1000ms (15 << 1)   /*   1 s sleep phase duration */

/* BMA250_DATA_HIGH_BW (0x13) */

#define BMA250_DATA_UNFILTERED  (1 << 7)    /* unfiltered accel data (0=filtered) */

/* BMA250_SOFTRESET (0x14) */

#define BMA250_RESET            (0xb6)      /* user-triggered reset write value */

/* BMA250_16_INTR_EN (0x16) */

#define BMA250_FLAT_EN          (1 << 7)    /* flat interrupt enable */
#define BMA250_ORIENT_EN        (1 << 6)    /* orientation interrupt enable */
#define BMA250_S_TAP_EN         (1 << 5)    /* single tap interrupt enable */
#define BMA250_D_TAP_EN         (1 << 4)    /* double tap interrupt enable */
#define BMA250_SLOPE_EN_Z       (1 << 2)    /* z-axis slope interrupt enable */
#define BMA250_SLOPE_EN_Y       (1 << 1)    /* y-axis slope interrupt enable */
#define BMA250_SLOPE_EN_X       (1 << 0)    /* x-axis slope interrupt enable */

/* BMA250_17_INTR_EN (0x17) */

#define BMA250_DATA_EN          (1 << 4)    /* new data interrupt enable */
#define BMA250_LOW_EN           (1 << 3)    /* low-g interrupt enable */
#define BMA250_HIGH_EN_Z        (1 << 2)    /* z-axis high-g interrupt enable */
#define BMA250_HIGH_EN_Y        (1 << 1)    /* y-axis high-g interrupt enable */
#define BMA250_HIGH_EN_X        (1 << 0)    /* x-axis high-g interrupt enable */

/* BMA250_19_INTR_MAP (0x19) */

#define BMA250_INT1_FLAT        (1 << 7)    /* map flat interrupt to INT1 */
#define BMA250_INT1_ORIENT      (1 << 6)    /* map orientation interrupt to INT1 */
#define BMA250_INT1_S_TAP       (1 << 5)    /* map single tap interrupt to INT1 */
#define BMA250_INT1_D_TAP       (1 << 4)    /* map double tap interrupt to INT1 */
#define BMA250_INT1_SLOPE       (1 << 2)    /* map slope interrupt to INT1 */
#define BMA250_INT1_HIGH        (1 << 1)    /* map high-g interrupt to INT1 */
#define BMA250_INT1_LOW         (1 << 0)    /* map low-g interrupt to INT1 */

/* BMA250_1A_INTR_MAP (0x1a) */

#define BMA250_INT2_DATA        (1 << 7)    /* map new data interrupt to INT2 */
#define BMA250_INT1_DATA        (1 << 0)    /* map new data interrupt to INT1 */

/*  BMA250_1B_INTR_MAP (0x1b) */

#define BMA250_INT2_FLAT        (1 << 7)    /* map flat interrupt to INT2 */
#define BMA250_INT2_ORIENT      (1 << 6)    /* map orientation interrupt to INT2 */
#define BMA250_INT2_S_TAP       (1 << 5)    /* map single tap interrupt to INT2 */
#define BMA250_INT2_D_TAP       (1 << 4)    /* map double tap interrupt to INT2 */
#define BMA250_INT2_SLOPE       (1 << 2)    /* map slope interrupt to INT2 */
#define BMA250_INT2_HIGH        (1 << 1)    /* map high-g interrupt to INT2 */
#define BMA250_INT2_LOW         (1 << 0)    /* map low-g interrupt to INT2 */

/* BMA250_INTR_DATA_SRC (0x1e) */

#define BMA250_INT_SRC_DATA     (1 << 5)    /* unfiltered new data interrupt
	                                     * data */
#define BMA250_INT_SRC_TAP      (1 << 4)    /* unfiltered s/d tap interrupt data */
#define BMA250_INT_SRC_SLOPE    (1 << 2)    /* unfiltered slope interrupt data */
#define BMA250_INT_SRC_HIGH     (1 << 1)    /* unfiltered high-g interrupt data */
#define BMA250_INT_SRC_LOW      (1 << 0)    /* unfiltered low-g interrupt data */

/* BMA250_INTR_PIN_CONFIG (0x20) */

#define BMA250_INT2_OD          (1 << 3)    /* open drive for INT2 pin */
#define BMA250_INT2_LVL_1       (1 << 2)    /* active level 1 for INT2 (default) */
#define BMA250_INT1_OD          (1 << 1)    /* open drive for INT1 pin */
#define BMA250_INT1_LVL_1       (1 << 0)    /* active level 1 for INT1 (default) */

/* BMA250_INTR_PIN_MODE (0x21) */

#define BMA250_RESET_INT        (0x80)      /* reset any latched interrupt */
#define BMA250_INT_NON_LATCHED  (0x00)      /* non-latched interrupt (default) */
#define BMA250_INT_TMP_250ms    (0x01)      /* 250ms temporary latched interrupt */
#define BMA250_INT_TMP_500ms    (0x02)      /* 500ms temporary latched interrupt */
#define BMA250_INT_TMP_1sec     (0x03)      /* 1000ms temporary latched
	                                     * interrupt */
#define BMA250_INT_TMP_2sec     (0x04)      /* 2000ms temporary latched
	                                     * interrupt */
#define BMA250_INT_TMP_4sec     (0x05)      /* 4000ms temporary latched
	                                     * interrupt */
#define BMA250_INT_TMP_8sec     (0x06)      /* 8000ms temporary latched
	                                     * interrupt */
#define BMA250_INT_TMP_500us    (0x0a)      /* 500us temporary latched interrupt */
#define BMA250_INT_TMP_1ms      (0x0b)      /* 1ms temporary latched interrupt */
#define BMA250_INT_TMP_12_5ms   (0x0c)      /* 12.5ms temporary latched
	                                     * interrupt */
#define BMA250_INT_TMP_25ms     (0x0d)      /* 25ms temporary latched interrupt */
#define BMA250_INT_TMP_50ms     (0x0e)      /* 50ms temporary latched interrupt */
#define BMA250_INT_LATCHED      (0x0f)      /* latched interrupt mode */

/**
 * BMA250_LOW_G_DURATION (0x22)
 *
 * Low-G interrupt delay time constants where the physical delay time is
 * computed as: delay[ms] = [low_dur + 1] * 2ms. The default value is 0x09
 * corresponding to a delay of 20ms.
 */

/**
 * BMA250_LOW_G_THRESHOLD (0x23)
 *
 * The log-g interrupt threshold value LSB corresponds to an acceleration
 * of 7.81mg with range 0 to 1.992g. The default value is 0x30 corresponding
 * to 375mg.
 */

/* BMA222_TAP_CONFIG (0x2b) */

#define BMA250_TAP_TH_FIELD     (0x1f)      /* tap interrupt threshold field */
#define BMA250_TAP_SAMP_FIELD   (0xc0)      /* tap wake-up samples count field */

/* BMA250_SENSOR_SELF_TEST (0x32) */

#define BMA250_SELF_TEST_NONE   (0x00)      /* no self-test (default) */
#define BMA250_SELF_TEST_AXIS_X (0x01)      /* self-test positive x-axis */
#define BMA250_SELF_TEST_AXIS_Y (0x02)      /* self-test positive y-axis */
#define BMA250_SELF_TEST_AXIS_Z (0x03)      /* self-test positive z-axis */

/** @} */

extern bool bma250_init(sensor_t *, int);

#ifdef __cplusplus
}
#endif

#endif
