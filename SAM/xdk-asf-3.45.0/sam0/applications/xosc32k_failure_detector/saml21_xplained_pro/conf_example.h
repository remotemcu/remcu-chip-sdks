/**
 * \file
 *
 * \brief SAM L21 Xplained Pro example configuration.
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

#ifndef CONF_TEST_H_INCLUDED
#define CONF_TEST_H_INCLUDED

/** Timer configured to source from the XOSC32K crystal generator */
#define CONF_TC_XOSC32K               TC3
/** Timer configured to source from the OSC32K oscillator generator */
#define CONF_TC_OSC32K                TC4
#define CONF_CLOCK_PIN_OUT            PIN_PA27H_GCLK_IO0
#define CONF_CLOCK_PIN_MUX            MUX_PA27H_GCLK_IO0
#define CONF_EVENT_GENERATOR_ID       EVSYS_ID_GEN_TC3_OVF
#define CONF_EVENT_USED_ID            EVSYS_ID_USER_TC4_EVU
/** The value should be 0 or 1 */
#define CONF_FRANGE_CAL               0
#define CONF_TEMP_CAL                 1
/** The suggested value is 13 to 15 */
#define CONF_CALIBRATION_RESOLUTION   13

#endif /* CONF_TEST_H_INCLUDED */
