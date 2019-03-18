/**
 * \file
 *
 * \brief Kionix KXTF9 3-axis accelerometer.
 *
 * This file contains functions for initializing and reading data
 * from a Kionix KXTF9 3-axis accelerometer.
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
#ifndef _KXTF9_H_
#define _KXTF9_H_

#include <asf.h>

#ifdef __cplusplus
extern "C" {
#endif

/* TWI/I2C address */

#define KXTF9_TWI_ADDR          (0x0f)

#define KXTF9_ID_VAL            (0x01)  /* KXTF9 device ID */
#define KXTI9_ID_VAL            (0x04)  /* KXTI9 device ID */
#define KXTF9_DATA_RESOLUTION   (12)    /* full-scale data resolution */

/* "Kionix recommended values" from example driver (kxtf9_driver.c) */

#define TILT_TIMER_INIT         (6)     /* tilt timer value */
#define WUF_TIMER_INIT          (4)     /* wake-up timer value */

/* Miscellaneous time values */

#define RESET_DELAY_MSEC                (5)     /* ram reset polling interval */
#define START_DELAY_MSEC                (20)    /* startup time (@200Hz sample) */
#define TAP_TIMER_HZ                    (400)   /* default tap timer frequency */
#define TAP_THRESH_MAX_DEFAULT          (0xB6 << 1)     /* 182 (shifted) */
#define TAP_THRESH_MIN_DEFAULT          (0x1A)          /* 26 */
#define TAP_TDT_TIMER_DEFAULT           (0x78)  /* 0.3   seconds */
#define TAP_TDT_TOTAL_TIMER_DEFAULT     (0x24)  /* 0.09  seconds */
#define TAP_TDT_LATENCY_TIMER_DEFAULT   (0x28)  /* 0.1   seconds */
#define TAP_TDT_TAP_TIMER_MIN_DEFAULT   (0x02)  /* 0.005 seconds */
#define TAP_TDT_TAP_TIMER_MAX_DEFAULT   (0x14)  /* 0.05  seconds */
#define TAP_TDT_WINDOW_TIMER_DEFAULT    (0xA0)  /* 0.4   seconds */

/** \brief KXTF9 Register Addresses */
/** @{ */

#define KXTF9_XOUT_HPF_L        (0x00)  /* accel high pass data - X lsb */
#define KXTF9_XOUT_HPF_H        (0x01)  /* accel high pass data - X msb */
#define KXTF9_YOUT_HPF_L        (0x02)  /* accel high pass data - Y lsb */
#define KXTF9_YOUT_HPF_H        (0x03)  /* accel high pass data - Y msb */
#define KXTF9_ZOUT_HPF_L        (0x04)  /* accel high pass data - Z lsb */
#define KXTF9_ZOUT_HPF_H        (0x05)  /* accel high pass data - Z msb */
#define KXTF9_XOUT_L            (0x06)  /* accel normal data - X lsb */
#define KXTF9_XOUT_H            (0x07)  /* accel normal data - X msb */
#define KXTF9_YOUT_L            (0x08)  /* accel normal data - Y lsb */
#define KXTF9_YOUT_H            (0x09)  /* accel normal data - Y msb */
#define KXTF9_ZOUT_L            (0x0A)  /* accel normal data - Z lsb */
#define KXTF9_ZOUT_H            (0x0B)  /* accel normal data - Z msb */
#define KXTF9_ST_RESP           (0x0C)  /* self test response */
#define KXTF9_WHO_AM_I          (0x0F)  /* device ID */
#define KXTF9_TILT_POS_CUR      (0x10)  /* current tilt position */
#define KXTF9_TILT_POS_PRE      (0x11)  /* previous tilt position */
#define KXTF9_INT_SRC_REG1      (0x15)  /* interrupt source reg 1 */
#define KXTF9_INT_SRC_REG2      (0x16)  /* interrupt source reg 2 */
#define KXTF9_STATUS_REG        (0x18)  /* status register */
#define KXTF9_INT_REL           (0x1A)  /* interrupt release - read to clear */
#define KXTF9_CTRL_REG1         (0x1B)  /* control reg 1 */
#define KXTF9_CTRL_REG2         (0x1C)  /* control reg 2 */
#define KXTF9_CTRL_REG3         (0x1D)  /* control reg 3 */
#define KXTF9_INT_CTRL_REG1     (0x1E)  /* interrupt control reg 1 */
#define KXTF9_INT_CTRL_REG2     (0x1F)  /* interrupt control reg 2 */
#define KXTF9_INT_CTRL_REG3     (0x20)  /* interrupt control reg 3 */
#define KXTF9_DATA_CTRL_REG     (0x21)  /* data control reg (b/w, data rate) */
#define KXTF9_TILT_TIMER        (0x28)  /* tilt timer initial value */
#define KXTF9_WUF_TIMER         (0x29)  /* motion detect timer initial value */
#define KXTF9_TDT_TIMER         (0x2B)  /* dbl tap detect - min intertap time */
#define KXTF9_TDT_H_THRESH      (0x2C)  /* tap detect high threshold */
#define KXTF9_TDT_L_THRESH      (0x2D)  /* tap detect low threshold */
#define KXTF9_TDT_TAP_TIMER     (0x2E)  /* tap detect timer, single tap */
#define KXTF9_TDT_TOTAL_TIMER   (0x2F)  /* dbl tap detect total time limit */
#define KXTF9_TDT_LATENCY_TIMER (0x30)  /* tap detect latency time limit */
#define KXTF9_TDT_WINDOW_TIMER  (0x31)  /* tap detect time window for entire tap */
#define KXTF9_SELF_TEST         (0x3A)  /* MEMS self test enable (write 0xCA) */
#define KXTF9_WUF_THRESH        (0x5A)  /* general motion threshold */
#define KXTF9_TILT_ANGLE        (0x5C)  /* tilt angle threshold */
#define KXTF9_HYST_SET          (0x5F)  /* tilt hysteresis value */

/** @} */

/** \brief KXTF9 Register Bit Definitions */
/** @{ */

/* KXTF9_TILT_POS_CUR (0x10) and KXTF9_TILT_POS_PRE (0x11)
 * (registers use same bit patterns)
 */

#define TILT_POS_FU             (0x01)   /* face up (pos. Z) */
#define TILT_POS_FD             (0x02)   /* face down (neg. Z) */
#define TILT_POS_UP             (0x04)   /* up (pos. Y) */
#define TILT_POS_DO             (0x08)   /* down (neg. Y) */
#define TILT_POS_RI             (0x10)   /* right (pos. X) */
#define TILT_POS_LE             (0x20)   /* left (neg. X) */

/* KXTF9_INT_SRC_REG1 (0x15) */

#define INT_SRC_REG1_TFU        (0x01)  /* face up (pos. Z) tap detected */
#define INT_SRC_REG1_TFD        (0x02)  /* face down (neg. Z) tap detected */
#define INT_SRC_REG1_TUP        (0x04)  /* up (pos. Y) tap detected */
#define INT_SRC_REG1_TDO        (0x08)  /* down (neg. Y) tap detected */
#define INT_SRC_REG1_TRI        (0x10)  /* right (pos. X) tap detected */
#define INT_SRC_REG1_TLE        (0x20)  /* left (neg. X) tap detected */

/* KXTF9_INT_SRC_REG2 (0x16) */

#define INT_SRC_REG2_TPS        (0x01)  /* tilt position change reported */
#define INT_SRC_REG2_WUFS       (0x02)  /* motion wake up reported */
#define INT_SRC_REG2_TD         (0x0C)  /* directional tap detected (2 bits) */
#define INT_SRC_REG2_TD_SINGLE  (0x04) /*   single tap */
#define INT_SRC_REG2_TD_DOUBLE  (0x08) /*   double tap */
#define INT_SRC_REG2_DRDY       (0x10)  /* new data ready */

/* KXTF9_STATUS_REG (0x18 ) */

#define STATUS_INT              (0x10)  /* interrupt has occurred */

/* KXTF9_CTRL_REG1 (0x1B) */

#define CTRL_REG1_TPE           (0x01)  /* enables tilt position function */
#define CTRL_REG1_WUFE          (0x02)  /* enables wake up function */
#define CTRL_REG1_TDTE          (0x04)  /* enables directional tap function */
#define CTRL_REG1_GSEL          (0x18)  /* g range select mask (2 bits */
#define CTRL_REG1_GSEL_2G       (0x00)  /* range = +/- 2g */
#define CTRL_REG1_GSEL_4G       (0x08)  /* range = +/- 4g */
#define CTRL_REG1_GSEL_8G       (0x10)  /* range = +/- 8g */
#define CTRL_REG1_DRDYE         (0x20)  /* data ready data output on int pin */
#define CTRL_REG1_RES           (0x40)  /* resolution: 0 = 8-bit, 1 = 12-bit */
#define CTRL_REG1_PC1           (0x80)  /* mode: 0 = standby, 1 = full power */

/* KXTF9_CTRL_REG2 (0x1C) */

#define CTRL_REG2_FUM           (0x01)  /* face up state mask */
#define CTRL_REG2_FDM           (0x02)  /* face down state mask */
#define CTRL_REG2_UPM           (0x04)  /* up state mask */
#define CTRL_REG2_DOM           (0x08)  /* down state mask */
#define CTRL_REG2_RIM           (0x10)  /* right state mask */
#define CTRL_REG2_LEM           (0x20)  /* left state mask */

/* KXTF9_CTRL_REG3 (0x1D) */

#define CTRL_REG3_OWUF          (0x03)  /* active mode output data rate mask */
#define CTRL_REG3_OWUF_25HZ     (0x00)  /* ODR = 25 Hz */
#define CTRL_REG3_OWUF_50HZ     (0x01)  /* ODR = 50 Hz */
#define CTRL_REG3_OWUF_100HZ    (0x02)  /* ODR = 100 Hz */
#define CTRL_REG3_OWUF_200HZ    (0x03)  /* ODR = 200 Hz */
#define CTRL_REG3_OTDT          (0x0C)  /* directional tap output data rate mask */
#define CTRL_REG3_OTDT_50HZ     (0x00)  /* ODR = 50 Hz */
#define CTRL_REG3_OTDT_100HZ    (0x04)  /* ODR = 100 Hz */
#define CTRL_REG3_OTDT_200HZ    (0x08)  /* ODR = 200 Hz */
#define CTRL_REG3_OTDT_400HZ    (0x0C)  /* ODR = 400 Hz */
#define CTRL_REG3_DCST          (0x10)  /* initiates self-test function */
#define CTRL_REG3_OTP           (0x60)  /* tilt position output data rate mask */
#define CTRL_REG3_OTP_1_6HZ     (0x00)  /* ODR = 1.6 Hz */
#define CTRL_REG3_OTP_6_3HZ     (0x20)  /* ODR = 6.3 Hz */
#define CTRL_REG3_OTP_12_5HZ    (0x40)  /* ODR = 12.5 Hz */
#define CTRL_REG3_OTP_50HZ      (0x60)  /* ODR = 50 Hz */
#define CTRL_REG3_SRST          (0x80)  /* software reset */

/* KXTF9_INT_CTRL_REG1 (0x1E) */

#define INT_CTRL_REG1_IEU       (0x04)  /* alternate unlatched response (WUF) */
#define INT_CTRL_REG1_IEL       (0x08)  /* int output latch disable */
#define INT_CTRL_REG1_IEA       (0x10)  /* int output 0=active low, 1=active hi */
#define INT_CTRL_REG1_IEN       (0x20)  /* enable pin output */

/* KXTF9_INT_CTRL_REG2 (0x1F) */

#define INT_CTRL_REG2_XBW       (0x80)   /* X-axis motion interrupt enable */
#define INT_CTRL_REG2_YBW       (0x40)   /* Y-axis motion interrupt enable */
#define INT_CTRL_REG2_ZBW       (0x20)   /* Z-axis motion interrupt enable */

/* KXTF9_INT_CTRL_REG3 (0x20) */

#define INT_CTRL_REG3_TFUM      (0x01)   /* face up (pos. Z) tap int enable */
#define INT_CTRL_REG3_TFDM      (0x02)   /* face down (neg. Z) tap int enable */
#define INT_CTRL_REG3_TUPM      (0x04)   /* up (pos. Y) tap int enable */
#define INT_CTRL_REG3_TDOM      (0x08)   /* down (neg. Y) tap int enable */
#define INT_CTRL_REG3_TRIM      (0x10)   /* right (pos. X) tap int enable */
#define INT_CTRL_REG3_TLEM      (0x20)   /* left (neg. X) tap int enable */

/* KXTF9_DATA_CTRL_REG (0x21) */

#define DATA_CTRL_ODR           (0x07)  /* low-pass output data rate mask */
#define DATA_CTRL_ODR_12_5HZ    (0x00)  /*   ODR = 12.5 Hz */
#define DATA_CTRL_ODR_25HZ      (0x01)  /*   ODR = 25 Hz */
#define DATA_CTRL_ODR_50HZ      (0x02)  /*   ODR = 50 Hz */
#define DATA_CTRL_ODR_100HZ     (0x03)  /*   ODR = 100 Hz */
#define DATA_CTRL_ODR_200HZ     (0x04)  /*   ODR = 200 Hz */
#define DATA_CTRL_ODR_400HZ     (0x05)  /*   ODR = 400 Hz */
#define DATA_CTRL_ODR_800HZ     (0x06)  /*   ODR = 800 Hz */
#define DATA_CTRL_HPFRO         (0x30)  /* high-pass filter roll-off freq */
#define DATA_CTRL_HPFRO_50HZ    (0x00)  /*   roll-off = 50 Hz */
#define DATA_CTRL_HPFRO_100HZ   (0x10)  /*   roll-off = 100 Hz */
#define DATA_CTRL_HPFRO_200HZ   (0x20)  /*   roll-off = 200 Hz */
#define DATA_CTRL_HPFRO_400HZ   (0x30)  /*   roll-off = 400 Hz */

/* KXTF9_TDT_H_THRESH (0x2C) */

#define TDT_H_THRESH_MSB        (0xFF)  /* tap high threshold bits 1 to 8 */

/* KXTF9_TDT_L_THRESH (0x2D) */

#define TDT_H_THRESH_LSB        (0x01)  /* tap high threshold bit 0 */
#define TDT_L_THRESH            (0x7F)  /* tap high threshold bits 1 to 8 */

/* KXTF9_SELF_TEST (0x3A) */

#define SELF_TEST_DISABLE       (0x00)  /* end self test, return to normal mode */
#define SELF_TEST_ENABLE        (0xCA)  /* start self test */

/** @} */

extern bool kxtf9_init(sensor_t *, int);

#ifdef __cplusplus
}
#endif

#endif
