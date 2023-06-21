/**
 * \file
 *
 * \brief C8263A configuration.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

/** Configuration of the C8263A LCD glass driver */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef CONF_C8263A_H_INCLUDED
#define CONF_C8263A_H_INCLUDED
#include "slcd.h"
/**
 * \name Circular Animation Shift Direction
 * @{
 */
#define C8263A_CSR_DIR      SLCD_CIRCULAR_SHIFT_LEFT
/** @} */


/** Init contrast configuration, it's wthin [0-15]. */
#define CONF_C8263A_CONTRAST  0xf


/** Frame count 0 configuration.
	Prescaler is not bypassed,the overflow value is (CONF_C8263A_FC0+1).
 */
#define CONF_C8263A_FC0     2
/** Frame count 0 configuration.
	Prescaler is not bypassed,the overflow value is (CONF_C8263A_FC0+1).
 */
#define CONF_C8263A_FC1     2
/** Frame count 0 configuration.
	Prescaler is not bypassed,the overflow value is (CONF_C8263A_FC0+1).
 */
#define CONF_C8263A_FC2     1

/** Blink timer configuration. */
#define CONF_C8263A_BLINK_TIMER                 SLCD_FRAME_COUNTER_0

/** Circular animation configuration. */
#define CONF_C8263A_CIRCULAR_ANIMATION_TIMER    SLCD_FRAME_COUNTER_0


#define C8263A_NB_OF_COM 8
#define C8263A_NB_OF_SEG 24

#define C8263A_CHAR_SEG_INDEX_S 8
#define C8263A_CHAR_SEG_INDEX_E 23
#define C8263A_DIGITAL_SEG_INDEX_S 1
#define C8263A_DIGITAL_SEG_INDEX_E 7

#define C8263A_CHAR_MAP_NUM_SEG 2
#define C8263A_CHAR_MASK 0x00ff0003 
#define C8263A_DIGITAL_MAP_NUM_SEG 1
#define C8263A_DIGITAL_MASK 0x00ff8000

#define C8263A_MAX_CHAR 8
#define C8263A_MAX_DIGITAL  5

/**
 * \name LCD component C42364A segment map default definitions
 * @{
 */
/* Icon with selected segments blinking feature */
#define C8263A_ICON_USB            2, 0
#define C8263A_ICON_COLON          0, 0
#define C8263A_ICON_BAT            4, 2
#define C8263A_ICON_ATMEL          1, 0
/* Icon without selected segments blinking feature */
#define C8263A_ICON_MINUS          0, 17
#define C8263A_ICON_MINUS_SEG1     0, 16
#define C8263A_ICON_MINUS_SEG2     0, 18
#define C8263A_ICON_DOT_1          7, 1
#define C8263A_ICON_DOT_2          7, 4
#define C8263A_ICON_DOT_3          7, 5
#define C8263A_ICON_DOT_4          7, 6
#define C8263A_ICON_DOT_5          7, 7
#define C8263A_ICON_BAT_LEVEL_1    4, 3
#define C8263A_ICON_BAT_LEVEL_2    5, 2
#define C8263A_ICON_BAT_LEVEL_3    5, 3
#define C8263A_ICON_WLESS_LEVEL_0  0, 2
#define C8263A_ICON_WLESS_LEVEL_1  0, 3
#define C8263A_ICON_WLESS_LEVEL_2  1, 2
#define C8263A_ICON_WLESS_LEVEL_3  1, 3
#define C8263A_ICON_ARROW_UP       3, 0
#define C8263A_ICON_ARROW_DWON     4, 0
#define C8263A_ICON_ARROW_LEFT     5, 0
#define C8263A_ICON_ARROW_RIGHT    6, 0
#define C8263A_ICON_ARROW_CORNER   7, 0
#define C8263A_ICON_AM             0, 21
#define C8263A_ICON_PM             0, 20
#define C8263A_ICON_DEGREE_C       0, 19
#define C8263A_ICON_DEGREE_F       0, 22
#define C8263A_ICON_VOLT           0, 15
#define C8263A_ICON_CUR            0, 23
#define C8263A_ICON_MILLI_VOLT     0, 14
#define C8263A_ICON_MICRO_VOLT     0, 13

/* @} */

#endif /* CONF_C8263A_H_INCLUDED */
