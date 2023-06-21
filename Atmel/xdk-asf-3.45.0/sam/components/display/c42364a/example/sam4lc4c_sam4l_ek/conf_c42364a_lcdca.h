/**
 * \file
 *
 * \brief C42364A configuration.
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

/** Configuration of the C42364A LCD glass driver */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef CONF_C42364A_LCDCA_H_INCLUDED
#define CONF_C42364A_LCDCA_H_INCLUDED

/** Bias configuration. */
#define CONF_C42364A_X_BIAS    false

/** Init contrast configuration. */
#define CONF_C42364A_CONTRAST  30

/**
 * \name Init timing definition
 * @{
 */
/** Clock prescaler configuration. */
#define CONF_C42364A_PRES    false
/** Clock divider configuration. */
#define CONF_C42364A_CLKDIV  7
/** Frame count 0 configuration. */
#define CONF_C42364A_FC0     2
/** Frame count 1 configuration. */
#define CONF_C42364A_FC1     2
/** Frame count 1 configuration. */
#define CONF_C42364A_FC2     1
/** @} */

/** Blink timer configuration. */
#define CONF_C42364A_BLINK_TIMER                 LCDCA_TIMER_FC0

/** Circular animation configuration. */
#define CONF_C42364A_CIRCULAR_ANIMATION_TIMER    LCDCA_TIMER_FC0

/** Text scrolling configuration. */
#define CONF_C42364A_TEXT_SCROLLING_TIMER        LCDCA_TIMER_FC0

/**
 * \name C42364A LCD Glass Common and Segment number
 * @{
 */
#define C42364A_NB_OF_COM 4
#define C42364A_NB_OF_SEG 40
/** @} */

/**
 * \name C42364A LCD Glass Connection Initialization
 * @{
 */
#define C42364A_PORT_MASK C42364A_NB_OF_SEG
#define C42364A_LCD_DUTY  (C42364A_NB_OF_COM % 4)
/** @} */

/**
 * \name Digit Decoder
 * @{
 */
/** 7-segment with 4 commons terminals */
#define C42364A_FIRST_7SEG_4C 10
#define C42364A_WIDTH_7SEG_4C 4

/** 14-segment with 4 commons terminals */
#define C42364A_FIRST_14SEG_4C 36
#define C42364A_WIDTH_14SEG_4C 7
/** @} */

#endif /* CONF_C42364A_LCDCA_H_INCLUDED */
