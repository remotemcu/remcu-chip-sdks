/**
 * \file
 *
 * \brief Osram SFH7770 light & proximity sensor driver.
 *
 * This file contains functions for initializing and reading data
 * from a Osram SFH7770 light & proximity sensor.
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
#ifndef _SFH7770_H_
#define _SFH7770_H_

#include <asf.h>

#ifdef __cplusplus
extern "C" {
#endif

/* TWI/I2C address (write @ 0x70 on bus, read @ 0x71 on bus) */

#define SFH7770_TWI_ADDR            (0x38)

/* Signed 16-bit axis data sample resolution and alignment (light data) */

#define SFH7770_DATA_RESOLUTION     (16)

/** \brief SFH7770 Register Addresses */
/** @{ */

#define SFH7770_ALS_CONTROL         (0x80)  /* ambient light sensor control */
#define SFH7770_PS_CONTROL          (0x81)  /* proximity sensor control */
#define SFH7770_I_LED_1_2           (0x82)  /* emitter current - LED1 & 2 */
#define SFH7770_I_LED_3             (0x83)  /* emitter control reg 2 */
#define SFH7770_ALS_PS_TRIG         (0x84)  /* measurement start (trigger mode) */
#define SFH7770_PS_INTERVAL         (0x85)  /* proximity measurement interval */
#define SFH7770_ALS_INTERVAL        (0x86)  /* light measurement interval */
#define SFH7770_PART_ID             (0x8A)  /* part id & revision */
#define SFH7770_MAN_ID              (0x8B)  /* manufacturer id */
#define SFH7770_ALS_DATA_LSB        (0x8C)  /* light meas data (low 8 bits) */
#define SFH7770_ALS_DATA_MSB        (0x8D)  /* light meas data (high 8 bits) */
#define SFH7770_ALS_PS_STATUS       (0x8E)  /* light/prox measurement status */
#define SFH7770_PS_DATA_LED1        (0x8F)  /* proximity meas data (LED1) */
#define SFH7770_PS_DATA_LED2        (0x90)  /* proximity meas data (LED2) */
#define SFH7770_PS_DATA_LED3        (0x91)  /* proximity meas data (LED3) */
#define SFH7770_INT_SET             (0x92)  /* interrupt status/control */
#define SFH7770_PS_THR_LED1         (0x93)  /* proximity threshold (LED1) */
#define SFH7770_PS_THR_LED2         (0x94)  /* proximity threshold (LED2) */
#define SFH7770_PS_THR_LED3         (0x95)  /* proximity threshold (LED3) */
#define SFH7770_ALS_UP_THR_LSB      (0x96)  /* upper light threshold (lsb) */
#define SFH7770_ALS_UP_THR_MSB      (0x97)  /* upper light threshold (msb) */
#define SFH7770_ALS_LO_THR_LSB      (0x98)  /* lower light threshold (lsb) */
#define SFH7770_ALS_LO_THR_MSB      (0x99)  /* lower light threshold (msb) */

/** @} */

/** \brief SFH7770 Register Bit Definitions */
/** @{ */

/* SFH7770_ALS_CONTROL (0x80) - ambient light sensor control */

#define ALS_MODE_MASK               (0x03)  /* light sensor mode mask */
#define   ALS_MODE_STANDBY          (0x00)  /* standby mode (default) */
#define   ALS_MODE_TRIGGERED        (0x02)  /* triggered mode */
#define   ALS_MODE_FREE_RUNNING     (0x03)  /* free-running mode */
#define ALS_CONTROL_SW_RESET        (0x04)  /* software reset */

/* SFH7770_PS_CONTROL (0x81) - proximity sensor control */

#define PS_MODE_MASK                (0x03)  /* proximity sensor mode mask */
#define   PS_MODE_STANDBY           (0x00)  /* standby mode (default) */
#define   PS_MODE_TRIGGERED         (0x02)  /* triggered mode */
#define   PS_MODE_FREE_RUNNING      (0x03)  /* free-running mode */

/* SFH7770_I_LED_1_2 (0x82) - emitter current - LED1 & LED2 */

#define I_LED_5MA                   (0x00)  /* LED current = 5mA */
#define I_LED_10MA                  (0x01)  /* LED current = 10mA */
#define I_LED_20MA                  (0x02)  /* LED current = 20mA */
#define I_LED_50MA                  (0x03)  /* LED current = 50mA (default) */
#define I_LED_100MA                 (0x04)  /* LED current = 100mA */
#define I_LED_150MA                 (0x05)  /* LED current = 150mA */
#define I_LED_200MA                 (0x06)  /* LED current = 200mA */
#define I_LED2_SHIFT                (3)      /* bit shift for LED2 field */

#define I_LED1_MASK                 (0x07)        /* LED1 pulse current mask */
#define   I_LED1_5MA                (I_LED_5MA)
#define   I_LED1_10MA               (I_LED_10MA)
#define   I_LED1_20MA               (I_LED_20MA)
#define   I_LED1_50MA               (I_LED_50MA)
#define   I_LED1_100MA              (I_LED_100MA)
#define   I_LED1_150MA              (I_LED_150MA)
#define   I_LED1_200MA              (I_LED_200MA)
#define I_LED2_MASK                 (0x38)  /* LED2 pulse current mask */
#define   I_LED2_5MA                (I_LED_5MA   << I_LED2_SHIFT)
#define   I_LED2_10MA               (I_LED_10MA  << I_LED2_SHIFT)
#define   I_LED2_20MA               (I_LED_20MA  << I_LED2_SHIFT)
#define   I_LED2_50MA               (I_LED_50MA  << I_LED2_SHIFT)
#define   I_LED2_100MA              (I_LED_100MA << I_LED2_SHIFT)
#define   I_LED2_150MA              (I_LED_150MA << I_LED2_SHIFT)
#define   I_LED2_200MA              (I_LED_200MA << I_LED2_SHIFT)
#define LED_ACTIVE_MASK             (0xC0)  /* active LED mask */
#define   LED_ACTIVE_1              (0x00)  /* LED1 active */
#define   LED_ACTIVE_1_2            (0x40)  /* LED1 & LED2 active */
#define   LED_ACTIVE_1_3            (0x80)  /* LED1 & LED3 active */
#define   LED_ACTIVE_ALL            (0xC0)  /* all LEDs active */

/* SFH7770_I_LED_3 (0x83) - emitter current - LED3 */

#define I_LED3_MASK                 (0x07)  /* LED3 pulse current mask */
#define   I_LED3_5MA                (I_LED_5MA)
#define   I_LED3_10MA               (I_LED_10MA)
#define   I_LED3_20MA               (I_LED_20MA)
#define   I_LED3_50MA               (I_LED_50MA)
#define   I_LED3_100MA              (I_LED_100MA)
#define   I_LED3_150MA              (I_LED_150MA)
#define   I_LED3_200MA              (I_LED_200MA)

/* SFH7770_PS_INTERVAL (0x85) - proximity measurement interval */

#define PS_INTERVAL_10MS            (0x00)  /* 10 msec */
#define PS_INTERVAL_20MS            (0x01)  /* 20 msec */
#define PS_INTERVAL_30MS            (0x02)  /* 30 msec */
#define PS_INTERVAL_50MS            (0x03)  /* 50 msec */
#define PS_INTERVAL_70MS            (0x04)  /* 70 msec */
#define PS_INTERVAL_100MS           (0x05)  /* 100 msec (default) */
#define PS_INTERVAL_200MS           (0x06)  /* 200 msec */
#define PS_INTERVAL_500MS           (0x07)  /* 500 msec */
#define PS_INTERVAL_1000MS          (0x08)  /* 1000 msec */
#define PS_INTERVAL_2000MS          (0x09)  /* 2000 msec */

/* SFH7770_ALS_INTERVAL (0x86) - light measurement interval */

#define ALS_INTERVAL_100MS          (0x00)  /* 100 msec */
#define ALS_INTERVAL_200MS          (0x01)  /* 200 msec */
#define ALS_INTERVAL_500MS          (0x02)  /* 500 msec (default) */
#define ALS_INTERVAL_1000MS         (0x03)  /* 1000 msec */
#define ALS_INTERVAL_2000MS         (0x04)  /* 2000 msec */

/* SFH7770_PART_ID (0x8A) - part ID and revision */

#define PART_REV_MASK               (0x0F)  /* SFH7770 chip revision bit mask */
#define PART_ID_MASK                (0xF0)  /* SFH7770 chip id bit mask */
#define PART_ID_SHIFT               (0x04)  /* bit shift for part ID (upper 4
	                                     * bits) */

#define SFH7770_PART_ID_VAL         (0x90)  /* expected chip id field value */
#define SFH7770_PART_REV_VAL        (0x04)  /* expected chip revision field
	                                     * value */

/* SFH7770_MAN_ID (0x8B) */

#define SFH7770_MAN_ID_VAL          (0x03)  /* expected manufacturer id value */

/* SFH7770_ALS_PS_STATUS (0x8E) - light/prox measurement status */

#define PS_LED1_DATA                (0x01)  /* PS LED1 sensor data available */
#define PS_LED1_THRESH              (0x02)  /* PS LED1 sensor value above
	                                     * threshold */
#define PS_LED2_DATA                (0x04)  /* PS LED2 sensor data available */
#define PS_LED2_THRESH              (0x08)  /* PS LED2 sensor value above
	                                     * threshold */
#define PS_LED3_DATA                (0x10)  /* PS LED3 sensor data available */
#define PS_LED3_THRESH              (0x20)  /* PS LED3 sensor value above
	                                     * threshold */
#define ALS_DATA                    (0x40)  /* ALS sensor data available */
#define ALS_THRESH                  (0x80)  /* ALS sensor value above threshold */

/* SFH7770_INT_SET (0x92) - interrupt status/control */

#define INT_MODE_MASK               (0x03)  /* interrupt mode enable (2 bits) */
#define INT_MODE_PS                 (0x01)  /* enable interrupt from prox sensor */
#define INT_MODE_ALS                (0x02)  /*   enable interrupt from ALS */
#define INT_OUT_POL                 (0x04)  /* int output polarity (0=active lo,
	                                     * 1=high) */
#define INT_OUT_MODE                (0x08)  /* int output mode (0=latched, 1=not
	                                     * latchd) */
#define INT_SOURCE_MASK             (0x60)  /* interrupt source (2 bits) */
#define INT_SOURCE_ALS              (0x00)  /* source = ALS */
#define INT_SOURCE_LED1             (0x20)  /* source = PS, LED 1 */
#define INT_SOURCE_LED2             (0x40)  /* source = PS, LED 2 */
#define INT_SOURCE_LED3             (0x60)  /* source = PS, LED 3 */

/** @} */

extern bool sfh7770_init(sensor_t *, int);

#ifdef __cplusplus
}
#endif

#endif /* _sfh7770_h_ */
