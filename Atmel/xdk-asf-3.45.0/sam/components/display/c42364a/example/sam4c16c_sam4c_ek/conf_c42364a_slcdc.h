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

#ifndef CONF_C42364A_SLCDC_H_INCLUDED
#define CONF_C42364A_SLCDC_H_INCLUDED

/** LCD buffer on-time */
#define CONF_C42364A_BUF_TIME         SLCDC_BUFTIME_X64_SCLK

/** LCD frame rate value */
#define CONF_C42364A_FRAME_RATE       64

/** LCD display mode */
#define CONF_C42364A_DISP_MODE        SLCDC_DISPMODE_NORMAL

/** LCD power mode */
#define CONF_C42364A_POWER_MODE       SLCDC_POWER_MODE_LCDON_INVR

/** LCD blinking frequency */
#define CONF_C42364A_BLINK_FREQ       2

/** LCD Contrast value */
#define CONF_C4236A_CONTRAST          8

#endif /* CONF_C42364A_SLCDC_H_INCLUDED */
