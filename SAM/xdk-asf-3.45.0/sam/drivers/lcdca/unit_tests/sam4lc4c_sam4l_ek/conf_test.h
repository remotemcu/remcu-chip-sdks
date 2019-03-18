/**
 * \file
 *
 * \brief Unit test configuration
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

#ifndef CONF_TEST_INCLUDED
#define CONF_TEST_INCLUDED

#include "compiler.h"

/** USART Interface */
#define CONF_TEST_USART      USART2
/** Baudrate setting */
#define CONF_TEST_BAUDRATE   115200
/** Character length setting */
#define CONF_TEST_CHARLENGTH US_MR_CHRL_8_BIT
/** Parity setting */
#define CONF_TEST_PARITY     US_MR_PAR_NO
/** Stop bits setting */
#define CONF_TEST_STOPBITS   US_MR_NBSTOP_1_BIT

/** LCD contrast level */
#define LCD_CONTRAST_LEVEL 30

/**
 * Here are definitions of C42364A glass LCD for this example
 * @{
 */

/** \name LCD Common
 * @{
 */
#define NB_OF_COM 4
#define NB_OF_SEG 40
/** @} */

/** \name LCD Connection Initialization
 * @{
 */
#define PORT_MASK  NB_OF_SEG
#define LCD_DUTY   (NB_OF_COM % 4)
/** @} */

/** \name Digit Decoder
 * @{
 */
/** 7-segment with 3 commons terminals */
#define FIRST_7SEG_3C  255 /* 255 = unavailable */
#define WIDTH_7SEG_3C  255 /* 255 = unavailable */
#define DIR_7SEG_3C    0   /* 0 = from left to right */

/** 7-segment with 4 commons terminals */
#define FIRST_7SEG_4C 10
#define WIDTH_7SEG_4C 4
#define DIR_7SEG_4C   1    /* 1 = from right to left */

/** 14-segment with 4 commons terminals */
#define FIRST_14SEG_4C 36
#define WIDTH_14SEG_4C 7
#define DIR_14SEG_4C   1  /* 1 = from right to left */

/** 16-segment with 3 commons terminals */
#define FIRST_16SEG_3C 255 /* 255 = unavailable */
#define WIDTH_16SEG_3C 255 /* 255 = unavailable */
#define DIR_16SEG_3C   0
/** @} */

/** \name Pixel With Blinking feature
 * @{
 */
#define ICON_USB      1, 0
#define ICON_COLON    0, 0
#define ICON_WLESS    2, 0
#define ICON_AUDIO    3, 0
#define ICON_BAT      0, 1
#define ICON_ERROR    1, 1
#define ICON_CHINESE  2, 1
#define ICON_ARM      3, 1
/** @} */

/** \name Pixel With No-Blinking feature
 * @{
 */
#define ICON_MINUS          0, 37
#define ICON_MINUS_SEG1     3, 30
#define ICON_MINUS_SEG2     0, 33
#define ICON_DOT_1          0, 29
#define ICON_DOT_2          3, 10
#define ICON_DOT_3          3, 8
#define ICON_DOT_4          3, 6
#define ICON_BAT_LEVEL_1    0, 21
#define ICON_BAT_LEVEL_2    0, 17
#define ICON_BAT_LEVEL_3    0, 25
#define ICON_AUDIO_PAUSE    3, 38
#define ICON_AUDIO_PLAY     3, 34
#define ICON_AM             3, 4
#define ICON_PM             3, 26
#define ICON_DEGREE_C       3, 22
#define ICON_DEGREE_F       3, 18
#define ICON_VOLT           3, 14
#define ICON_MILLI_VOLT     0, 13
/** @} */
/** @} */

#endif /* CONF_TEST_INCLUDED */
