/**
 * \file
 *
 * \brief API driver for MMA7341L accelerometer component.
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

#ifndef MMA7341L_H_INCLUDED
#define MMA7341L_H_INCLUDED

#include "compiler.h"
#include "board.h"
#include "conf_mma7341l.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
 extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/** Accelerometer filtering value */
#define MMA7341L_SHIFT  0
/** Accelerometer 0g output voltage value is 1.65v, converted digital value 0x400/2 (10-bit ADC) */
#define MMA7341L_ZERO  (0x1FF >> MMA7341L_SHIFT)
/** Accelerometer delta 1g digital value is 0.44/3.3 * 0x400 (10-bit ADC) */
#define MMA7341L_1G    (0x88 >> MMA7341L_SHIFT)

#define MMA7341L_ZERO_X  MMA7341L_ZERO
#define MMA7341L_ZERO_Y  MMA7341L_ZERO
#define MMA7341L_ZERO_Z  MMA7341L_ZERO

/* The rotation direction definition */
#define  MMA7341L_UNCHANGED  0
#define  MMA7341L_UP         1
#define  MMA7341L_DOWN       2
#define  MMA7341L_LEFT       3
#define  MMA7341L_RIGHT      4
#define  MMA7341L_UP_RIGHT   5
#define  MMA7341L_UP_LEFT    6
#define  MMA7341L_DOWN_LEFT  7
#define  MMA7341L_DOWM_RIGHT 8

/** Definition of MMA7341L working mode */
#define MMA7341L_NORMAL_MODE   1
#define MMA7341L_SLEEP_MODE    0

#ifndef MMA7341L_ADC_CHANNEL_X
#warning an ADC channel is not defined as X axis channel. Using default settings.
#define MMA7341L_ADC_CHANNEL_X   2
#endif
#ifndef MMA7341L_ADC_CHANNEL_Y
#warning an ADC channel is not defined as Y axis channel. Using default settings.
#define MMA7341L_ADC_CHANNEL_Y   6
#endif
#ifndef MMA7341L_ADC_CHANNEL_Z
#warning an ADC channel is not defined as Z axis channel. Using default settings.
#define MMA7341L_ADC_CHANNEL_Z   7
#endif

#define MMA7341L_EOC_X    (0x1u << MMA7341L_ADC_CHANNEL_X)
#define MMA7341L_EOC_Y    (0x1u << MMA7341L_ADC_CHANNEL_Y)
#define MMA7341L_EOC_Z    (0x1u << MMA7341L_ADC_CHANNEL_Z)

typedef struct {
	int32_t x;
	int32_t y;
	int32_t z;
} xyz_t;

typedef struct {
	float x_g;
	float y_g;
	float z_g;
} xyz_g_t;

typedef struct {
	xyz_t m;  /* Immediate acceleration */
	xyz_t k;   /* Calibration basis */
	xyz_t ak; /* Acceleration difference */
} acc_t;

void mma7341l_calibration(void);
void mma7341l_init(void);
void mma7341l_set_mode(uint8_t uc_mode);
xyz_g_t mma7341l_get_gravity_value(void);
uint32_t mma7341l_get_rotation_dir(void);

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

#endif /* MMA7341L_H_INCLUDED */
