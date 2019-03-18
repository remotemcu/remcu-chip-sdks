/**
 * \file
 *
 * \brief Analog Devices ADXL345Z Digital, triaxial acceleration sensor driver.
 *
 * This module defines registers, constants, data structures, and
 * global function prototypes for an ADI ADXL345Z sensor driver.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#ifndef _ADXL345Z_H_
#define _ADXL345Z_H_

#include <asf.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Standard ADXL345Z Register Addresses (TWI & SPI) */
typedef enum {
	ADXL345Z_DEVID = 0,     /* 0x00 (ro) device ID (fixed value 0xe5) */
	ADXL345Z_01_RSVD,       /* 0x01 reserved */
	ADXL345Z_02_RSVD,       /* 0x02 reserved */
	ADXL345Z_03_RSVD,       /* 0x03 reserved */
	ADXL345Z_04_RSVD,       /* 0x04 reserved */
	ADXL345Z_05_RSVD,       /* 0x05 reserved */
	ADXL345Z_06_RSVD,       /* 0x06 reserved */
	ADXL345Z_07_RSVD,       /* 0x07 reserved */
	ADXL345Z_08_RSVD,       /* 0x08 reserved */
	ADXL345Z_09_RSVD,       /* 0x09 reserved */
	ADXL345Z_0a_RSVD,       /* 0x0a reserved */
	ADXL345Z_0b_RSVD,       /* 0x0b reserved */
	ADXL345Z_0c_RSVD,       /* 0x0c reserved */
	ADXL345Z_0d_RSVD,       /* 0x0d reserved */
	ADXL345Z_0e_RSVD,       /* 0x0e reserved */
	ADXL345Z_0f_RSVD,       /* 0x0f reserved */
	ADXL345Z_10_RSVD,       /* 0x10 reserved */
	ADXL345Z_11_RSVD,       /* 0x11 reserved */
	ADXL345Z_12_RSVD,       /* 0x12 reserved */
	ADXL345Z_13_RSVD,       /* 0x13 reserved */
	ADXL345Z_14_RSVD,       /* 0x14 reserved */
	ADXL345Z_15_RSVD,       /* 0x15 reserved */
	ADXL345Z_16_RSVD,       /* 0x16 reserved */
	ADXL345Z_17_RSVD,       /* 0x17 reserved */
	ADXL345Z_18_RSVD,       /* 0x18 reserved */
	ADXL345Z_19_RSVD,       /* 0x19 reserved */
	ADXL345Z_1a_RSVD,       /* 0x1a reserved */
	ADXL345Z_1b_RSVD,       /* 0x1b reserved */
	ADXL345Z_1c_RSVD,       /* 0x1c reserved */
	ADXL345Z_THRESH_TAP,    /* 0x1d (w/r) tap threshold */
	ADXL345Z_OFSX,          /* 0x1e (w/r) x-axis offset */
	ADXL345Z_OFSY,          /* 0x1f (w/r) y-axis offset */
	ADXL345Z_OFSZ,          /* 0x20 (w/r) z-axis offset */
	ADXL345Z_DUR,           /* 0x21 (w/r) tap duration */
	ADXL345Z_LATENT,        /* 0x22 (w/r) tap latency */
	ADXL345Z_WINDOW,        /* 0x23 (w/r) tap window */
	ADXL345Z_THRESH_ACT,    /* 0x24 (w/r) activity threshold */
	ADXL345Z_THRESH_INACT,  /* 0x25 (w/r) inactivity threshold */
	ADXL345Z_TIME_INACT,    /* 0x26 (w/r) inactivity time */
	ADXL345Z_ACT_INACT_CTL, /* 0x27 (w/r) axis enable (activity/inactivity) */
	ADXL345Z_THRESH_FF,     /* 0x28 (w/r) free-fall threshold */
	ADXL345Z_TIME_FF,       /* 0x29 (w/r) free-fall time */
	ADXL345Z_TAP_AXES,      /* 0x2a (w/r) single/double-tap axis control */
	ADXL345Z_ACT_TAP_STATUS, /* 0x2b (ro) single/double-tap source */
	ADXL345Z_BW_RATE,       /* 0x2c (w/r) data rate and power mode control */
	ADXL345Z_POWER_CTL,     /* 0x2d (w/r) power-saving features control */
	ADXL345Z_INT_ENABLE,    /* 0x2e (w/r) interrupt enable control */
	ADXL345Z_INT_MAP,       /* 0x2f (w/r) interrupt mapping control */
	ADXL345Z_INT_SOURCE,    /* 0x30 (ro) interrupt source */
	ADXL345Z_DATA_FORMAT,   /* 0x31 (w/r) data format control */
	ADXL345Z_DATAX0,        /* 0x32 (ro) x-axis data 0 */
	ADXL345Z_DATAX1,        /* 0x33 (ro) x-axis data 1 */
	ADXL345Z_DATAY0,        /* 0x34 (ro) y-axis data 0 */
	ADXL345Z_DATAY1,        /* 0x35 (ro) y-axis data 1 */
	ADXL345Z_DATAZ0,        /* 0x36 (ro) z-axis data 0 */
	ADXL345Z_DATAZ1,        /* 0x37 (ro) z-axis data 1 */
	ADXL345Z_FIFO_CTL,      /* 0x38 (w/r) FIFO control */
	ADXL345Z_FIFO_STATUS    /* 0x39 (ro) FIFO status */
} adxl345z_register_t;

/** \brief ADXL345Z Register Bit Definitions */
/** @{ */

/* ADXL345Z_POWER_CTL (0x2d) */

#define POWER_CTL_LINK          (1 << 5)
#define POWER_CTL_AUTO_SLEEP    (1 << 4)
#define POWER_CTL_MEASURE       (1 << 3)
#define POWER_CTL_SLEEP         (1 << 2)
#define POWER_CTL_WAKE_8Hz      (0)
#define POWER_CTL_WAKE_4Hz      (1)
#define POWER_CTL_WAKE_2Hz      (2)
#define POWER_CTL_WAKE_1Hz      (3)

/** @} */

extern bool adxl345z_init(sensor_t *, int);

#ifdef __cplusplus
}
#endif

#endif
