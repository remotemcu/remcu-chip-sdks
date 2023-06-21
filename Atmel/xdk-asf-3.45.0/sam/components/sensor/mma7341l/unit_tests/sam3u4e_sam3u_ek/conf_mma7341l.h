/**
 * \file
 *
 * \brief MMA7341L configuration.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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

/* Configuration of the mma7341 accelerometer driver */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef CONF_MMA7341L_H_INCLUDED
#define CONF_MMA7341L_H_INCLUDED

// Definition of MMA7341L x,y,z axis channel number
#define MMA7341L_ADC_CHANNEL_X    2
#define MMA7341L_ADC_CHANNEL_Y    6
#define MMA7341L_ADC_CHANNEL_Z    7

// MMA7341L mode set pin definitions
#define PIN_MMA7341L_MODE         PIO_PC13_IDX
#define PIN_MMA7341L_MODE_FLAG    (PIO_OUTPUT_1 | PIO_DEFAULT)

// MMA7341L X,Y,Z axis pin definitions
#define PIN_MMA7341L_X_AXIS       PIO_PB3_IDX
#define PIN_MMA7341L_X_AXIS_FLAG  (PIO_INPUT | PIO_DEFAULT)
#define PIN_MMA7341L_Y_AXIS       PIO_PC17_IDX
#define PIN_MMA7341L_Y_AXIS_FLAG  (PIO_INPUT | PIO_DEFAULT)
#define PIN_MMA7341L_Z_AXIS       PIO_PC18_IDX
#define PIN_MMA7341L_Z_AXIS_FLAG  (PIO_INPUT | PIO_DEFAULT)

#define MMA7341L_ADC_CLK   100000

#define MMA7341L_USE_ADC12
//#define MMA7341L_USE_ADC10

#endif /* CONF_MMA7341L_H_INCLUDED */
