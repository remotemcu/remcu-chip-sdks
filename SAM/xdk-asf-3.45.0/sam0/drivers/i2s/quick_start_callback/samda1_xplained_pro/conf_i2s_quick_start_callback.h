/**
 * \file
 *
 * \brief I2S Quick Start configuration for SAM DA1 Xplained Pro
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

#ifndef CONF_QUICK_START_CALLBACK_H_INCLUDED
#define CONF_QUICK_START_CALLBACK_H_INCLUDED

//! [definition_i2s]
/** I2S module to use */
#define CONF_I2S_MODULE      I2S

/** I2S MCK pin */
#define CONF_I2S_MCK_PIN     PIN_PA09G_I2S_MCK0
/** I2S MCK pin mux */
#define CONF_I2S_MCK_MUX     MUX_PA09G_I2S_MCK0
/** I2S SCK pin */
#define CONF_I2S_SCK_PIN     PIN_PA10G_I2S_SCK0
/** I2S SCK pin mux */
#define CONF_I2S_SCK_MUX     MUX_PA10G_I2S_SCK0
/** I2S FS pin */
#define CONF_I2S_FS_PIN      PIN_PA11G_I2S_FS0
/** I2S FS pin mux */
#define CONF_I2S_FS_MUX      MUX_PA11G_I2S_FS0

/** I2S SD pin */
#define CONF_I2S_SD_PIN      PIN_PA07G_I2S_SD0
/** I2S SD pin mux */
#define CONF_I2S_SD_MUX      MUX_PA07G_I2S_SD0
//! [definition_i2s]

#endif /* CONF_QUICK_START_CALLBACK_H_INCLUDED */
