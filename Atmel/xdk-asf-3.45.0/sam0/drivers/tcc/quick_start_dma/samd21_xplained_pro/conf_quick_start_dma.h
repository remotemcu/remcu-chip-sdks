/**
 * \file
 *
 * \brief TCC Quick Start configuration for SAM D21 Xplained Pro
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

#ifndef CONF_QUICK_START_H_INCLUDED
#define CONF_QUICK_START_H_INCLUDED

//[definition_pwm]
/** PWM module to use */
#define CONF_PWM_MODULE      LED_0_PWM4CTRL_MODULE
/** PWM channel */
#define CONF_PWM_CHANNEL     LED_0_PWM4CTRL_CHANNEL
/** PWM output */
#define CONF_PWM_OUTPUT      LED_0_PWM4CTRL_OUTPUT
/** PWM output pin */
#define CONF_PWM_OUT_PIN     LED_0_PWM4CTRL_PIN
/** PWM output pin mux */
#define CONF_PWM_OUT_MUX     LED_0_PWM4CTRL_MUX
//[definition_pwm]

//[definition_feedback]
/** TCC channel to capture */
#define CONF_TCC_CAPTURE_CHANNEL      1

/** Generator of TCC event */
#define CONF_TCC_EVENT_GENERATOR      EVSYS_ID_GEN_TCC0_MCX_0
/** User of TCC event */
#define CONF_TCC_EVENT_USER           EVSYS_ID_USER_TCC0_MC_1
//[definition_feedback]

//[definition_dma_compare_trigger]
/** DMA Peripheral to Memory beat trigger: TCC0 OVF */
#define CONF_COMPARE_TRIGGER TCC0_DMAC_ID_OVF
//[definition_dma_compare_trigger]

//[definition_dma_capture_trigger]
/** DMA Memory to Peripheral beat trigger: TCC0 MC1 */
#define CONF_CAPTURE_TRIGGER TCC0_DMAC_ID_MC_1
//[definition_dma_capture_trigger]

#endif /* CONF_QUICK_START_H_INCLUDED */
