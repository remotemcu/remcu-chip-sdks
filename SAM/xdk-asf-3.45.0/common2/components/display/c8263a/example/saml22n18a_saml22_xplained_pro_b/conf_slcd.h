/**
 * \file
 *
 * \brief SAM SLCD Driver Configuration Header
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#ifndef CONF_SLCD_H_INCLUDED
#define CONF_SLCD_H_INCLUDED

/** Select SLCD clock. Use 32.768KHz OSCULP32K or XOSC32K for SLCD clock.
 *  0 : From OSCULP32K
 *  1 : From XOSC32K
 */
#define CONF_SLCD_CLOCK_SOURCE    0

/** SLCD Duty Setting
 *  0:Static duty
 *  1:1/2 duty
 *  2:1/3 duty
 *  3:1/4 duty
*/
#define CONF_SLCD_DUTY         5

/**
 * SLCD Bias Setting.
 *  0:Static bias
 *  1:1/2 bias
 *  2:1/3 bias
 *  3:1/4 bias
 */
#define CONF_SLCD_BIAS         3

/**
 * SLCD Frame Frequency.
 * The optimal frame frequency should be in range from 30Hz up to 100Hz
 * to avoid flickering and ghosting effect.
 * To get the frame frequency, CLK_SLCD_OSC is first divided by a prescaler
 * from 16 to 128 then divided by 1 up to 8 as following.
 * 
 * FrameRate = CLK_SLCD_OSC / (PVAL*(CKDIV+1)(DUTY+1))
 *
 * SLCD Prescaler Value (PVAL).
 * 0 : 16 prescaler
 * 1 : 32 prescaler
 * 2 : 64 prescaler
 * 3 : 128 prescaler
 *
 * SLCD Clock divider (CKDIV)
 * 0 : CKDIV is 0
 * 1 : CKDIV is 1
 * 2 : CKDIV is 2
 * 3 : CKDIV is 3
 * 4 : CKDIV is 4
 * 5 : CKDIV is 5
 * 6 : CKDIV is 6
 * 7 : CKDIV is 7
 */
#define CONF_SLCD_PVAL         0
#define CONF_SLCD_CKDIV        2

/** Internal/External VLCD selection.
* 0 : Internal VLCD generation
* 1 : External VLCD generation
*/
#define CONF_SLCD_VLCD_SEL        0

/** Reference refresh frequency. 
*  0: Bias Reference refresh frequency is 2KHz
*  1: Bias Reference refresh frequency is 1KHz
*  2: Bias Reference refresh frequency is 500Hz
*  3: Bias Reference refresh frequency is 250Hz
*  4: Bias Reference refresh frequency is 125Hz
*  5: Bias Reference refresh frequency is 62.5Hz
*/
#define CONF_SLCD_REF_REFRESH_FREQ        0

/** Power fefresh frequency.
*  0: Charge pump refresh frequency is 2KHz
*  1: Charge pump refresh frequency is 1KHz
*  2: Charge pump refresh frequency is 500Hz
*  3: Charge pump refresh frequency is 250Hz
 */
#define CONF_SLCD_POWER_REFRESH_FREQ       0
 
/** LCD Working Power Mode.
 * 0:LCD power automatically select regualation mode or pump mode.
 * 1:LCD power use step-up pump loop only.
 * 2:LCD power use step-down drop-out regulation loop only.
 */ 
#define CONF_SLCD_POWER_MODE       0

/** COM/SEG PIN Selection.
 * There are 52 LCD pins, but SLCD can drive up to 48 LCD pins which can be
 * individually enabled or disabled according to the LCD glass. The number of LCD pins
 * enabled should not be higher than the maximum of COM and SEG lines supported.
 * COM and SEG lines are always assigned in ascending order.
 * CONF_SLCD_PIN_L_MASK is pin mask [31,0]
 * CONF_SLCD_PIN_H_MASK is pin mask [51,32]
 */ 
#define CONF_SLCD_PIN_L_MASK       0xCFFFFFC0
#define CONF_SLCD_PIN_H_MASK       0x00000FF0
#endif
