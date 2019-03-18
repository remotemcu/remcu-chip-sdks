/*****************************************************************************
 *
 * \file
 *
 * \brief SAM4S toolkit demo configurations.
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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
 ******************************************************************************/
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */


#ifndef CONF_DEMO_H
#define CONF_DEMO_H

#include "board.h"
#include "ili93xx.h"

/** Demo board */
#define DEMO_BOARD_NAME   "SAM4S-EK"

/** Demo version */
#define DEMO_VERSION "2.1"

/** Switch to enable/disable QTouch library use */
#define DEMO_USE_QTOUCH

/** Switch to enable/disable USB library use */
#define DEMO_USE_USB

#define LCD_WIDTH ILI93XX_LCD_WIDTH
#define LCD_HEIGHT ILI93XX_LCD_HEIGHT

/** Wakeup pin for low power mode: Touchscreen controller IRQ pin */
#define LPM_WAKEUP_INPUT_ID  (1u << 15)

/** QTouch key number */
#define BOARD_KEY_NUM_5

/** QTouch valid key ID */
#define BOARD_VALID_KEY_ID    0

/** QTouch up key ID */
#define BOARD_UP_KEY_ID    1

/** QTouch down key ID */
#define BOARD_DOWN_KEY_ID    2

/** QTouch left key ID */
#define BOARD_LEFT_KEY_ID    3

/** QTouch right key ID */
#define BOARD_RIGHT_KEY_ID    4

/** QTouch valid key channel */
#define BOARD_VALID_KEY_CHANNEL    CHANNEL_11

/** QTouch up key channel */
#define BOARD_UP_KEY_CHANNEL    CHANNEL_12

/** QTouch down key channel */
#define BOARD_DOWN_KEY_CHANNEL    CHANNEL_13

/** QTouch left key channel */
#define BOARD_LEFT_KEY_CHANNEL    CHANNEL_14

/** QTouch right key channel */
#define BOARD_RIGHT_KEY_CHANNEL    CHANNEL_15

/** QTouch slider start channel */
#define BOARD_SLIDER_START_CHANNEL    CHANNEL_16

/** QTouch slider end channel */
#define BOARD_SLIDER_END_CHANNEL    CHANNEL_18

#endif /* CONF_DEMO_H */
