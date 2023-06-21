/**
 * \file
 *
 * \brief TCC Quick Start configuration
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef CONF_QUICK_START_H_INCLUDED
#define CONF_QUICK_START_H_INCLUDED

//[definition_pwm]
#if SAMR30G
/** PWM module to use */
#define CONF_PWM_MODULE      LED_0_PWM3CTRL_MODULE
/** PWM channel */
#define CONF_PWM_CHANNEL     LED_0_PWM3CTRL_CHANNEL
/** PWM output */
#define CONF_PWM_OUTPUT      LED_0_PWM3CTRL_OUTPUT
/** PWM output pin */
#define CONF_PWM_OUT_PIN     LED_0_PWM3CTRL_PIN
/** PWM output pinmux */
#define CONF_PWM_OUT_MUX     LED_0_PWM3CTRL_MUX

#elif SAMR30E
/** PWM module to use */
#define CONF_PWM_MODULE      LED_1_PWM2CTRL_MODULE
/** PWM channel */
#define CONF_PWM_CHANNEL     LED_1_PWM2CTRL_CHANNEL
/** PWM output */
#define CONF_PWM_OUTPUT      LED_1_PWM2CTRL_OUTPUT
/** PWM output pin */
#define CONF_PWM_OUT_PIN     LED_1_PWM2CTRL_PIN
/** PWM output pinmux */
#define CONF_PWM_OUT_MUX     LED_1_PWM2CTRL_MUX

#else
/** PWM module to use */
#define CONF_PWM_MODULE      LED_0_PWM4CTRL_MODULE
/** PWM channel */
#define CONF_PWM_CHANNEL     LED_0_PWM4CTRL_CHANNEL
/** PWM output */
#define CONF_PWM_OUTPUT      LED_0_PWM4CTRL_OUTPUT
/** PWM output pin */
#define CONF_PWM_OUT_PIN     LED_0_PWM4CTRL_PIN
/** PWM output pinmux */
#define CONF_PWM_OUT_MUX     LED_0_PWM4CTRL_MUX
#endif
//[definition_pwm]

#endif /* CONF_QUICK_START_H_INCLUDED */
