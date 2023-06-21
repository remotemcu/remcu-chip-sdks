/**
 * \file
 *
 * \brief Example specific configurations
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

#ifndef CONF_EXAMPLE_H_INCLUDED
#define CONF_EXAMPLE_H_INCLUDED

/**
 * \section intro Introduction
 * This example application is created for AT30TSE758 on 
 * the ATAVRTempSensorX board. When checking this code on other devices,
 * define the preprocessor symbol corresponding to the selected Sensor 
 * device, in the project properties
 * eg:
 * _AT30TSE002B_ _AT30TSE758_
 * Connect pull up for TWI, on A3BU Xplained Kit or TempSensor Xplained
 */
 
/*! \name GPIO Connections and device addresses.
 */
/* ! @{ */

#define LED_LOW         J1_PIN5
#define LED_HIGH        J1_PIN7
#define LED_CRIT        J1_PIN3
#define LED_NORM        J1_PIN2
#define EVENT_PIN       J2_PIN6

/* ! @} */

/* PATTERN_TEST_LENGTH value should be less 
 * than the size of 'ibuf' in main() 
 */
#define PATTERN_TEST_LENGTH            7
#define TWI_SPEED                      50000

#ifdef _AT30TSE758_
#define EXAMPLE_TS_DEVICE              AT30TSE758
#define EXAMPLE_TS_DEVICE_ADDR         AT30TSE758_ADDR_LOCAL
#elif defined _AT30TSE002B_
#define EXAMPLE_TS_DEVICE              AT30TSE002B
#define EXAMPLE_TS_DEVICE_ADDR         AT30TSE002B_ADDR_LOCAL
#endif

/* EE_TEST_ADDR max value for AT30TSE758 is (1024 -  PATTERN_TEST_LENGTH) */
/* EE_TEST_ADDR max value for AT30TSE002B is (256 -  PATTERN_TEST_LENGTH) */
#define EE_TEST_ADDR                   130

/* Development kits */
#ifdef _AT30TK175_

/* Temperature register address on AT30TK175 board */
#define AT30TSE002B_ADDR               0x1B
#define AT30TS75_ADDR                  0x48
#define AT30TS750_ADDR                 0x49
#define AT30TSE758_ADDR                0x4A
/* EEPROM Address */
#define AT30TSE002B_EEPROM_ADDR        0x53
#define AT30TSE758_EEPROM_ADDR         0x52

#elif defined _ATAVRTEMPSENSORX_

/* Local (main board): temperature register address */
#define AT30TSE002B_ADDR_LOCAL         0x18
#define AT30TSE758_ADDR_LOCAL          0x48

/* Local (main board): EEPROM Address */
#define AT30TSE002B_EEPROM_ADDR_LOCAL  0x50
#define AT30TSE758_EEPROM_ADDR_LOCAL   0x50

#endif

#endif // CONF_EXAMPLE_H_INCLUDED
