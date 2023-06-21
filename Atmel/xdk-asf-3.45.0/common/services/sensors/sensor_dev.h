/**
 * \file
 *
 * \brief Sensor API device definitions
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef _SENSOR_DEV_h_
#define _SENSOR_DEV_h_

/* Sensor API Definitions */
#include "sensor.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \name Sensor Driver Initialization Entry Points */
/** @{ */
extern bool ak8975_init(sensor_t *, int);
extern bool bma020_init(sensor_t *, int);
extern bool bma150_init(sensor_t *, int);
extern bool bma180_init(sensor_t *, int);
extern bool bma220_init(sensor_t *, int);
extern bool bma222_init(sensor_t *, int);
extern bool bma250_init(sensor_t *, int);
extern bool bmp085_init(sensor_t *, int);
extern bool bmp180_init(sensor_t *, int);
extern bool hmc5883l_init(sensor_t *, int);
extern bool imu3000_init(sensor_t *, int);
extern bool itg3200_init(sensor_t *, int);
extern bool kxtf9_init(sensor_t *, int);
extern bool sfh5712_init(sensor_t *, int);
extern bool sfh7770_init(sensor_t *, int);
/** @} */

/** \name Sensor Device Bus Addresses
 *
 * Each driver must have a bus address $(name)_bus_addr defined here, where
 * $(name) is the same prefix used for the driver $(name)_init function.
 *
 * The bus address definitions are keyed off build constants and will vary
 * by application.  If the bus does not assign particular addresses, then
 * define the address as (0).  If, as is the case with TWI/I2C, the device
 * responds to a specific address, then define the constant bus address value.
 *
 * The default values provided here may be modified or redefined by specific
 * board and bus implementations.
 *
 * @{
 */
#if defined(CONF_SENSOR_BUS_TWI)
#   define ak8975_bus_addr      (0x0c)
#   define kxtf9_bus_addr       (0x0f)
#   define hmc5883l_bus_addr    (0x1e)
#   define bma020_bus_addr      (0x38)
#   define bma150_bus_addr      (0x38)
#   define bma180_bus_addr      (0x40)
#   define bma220_bus_addr      (0x0b)
#   define bma222_bus_addr      (0x08)
#   define bma250_bus_addr      (0x18)
#   define bmp085_bus_addr      (0x77)
#   define bmp180_bus_addr      (0x77)
#   define imu3000_bus_addr     (0x68)
#   define itg3200_bus_addr     (0x68)
#   define sfh5712_bus_addr     (0x29)
#   define sfh7770_bus_addr     (0x38)
#else
#   define ak8975_bus_addr      (0)
#   define kxtf9_bus_addr       (0)
#   define hmc5883l_bus_addr    (0)
#   define bma020_bus_addr      (0)
#   define bma150_bus_addr      (0)
#   define bma180_bus_addr      (0)
#   define bma220_bus_addr      (0)
#   define bma222_bus_addr      (0)
#   define bma250_bus_addr      (0)
#   define bmp085_bus_addr      (0)
#   define bmp180_bus_addr      (0)
#   define imu3000_bus_addr     (0)
#   define itg3200_bus_addr     (0)
#   define sfh5712_bus_addr     (0)
#   define sfh7770_bus_addr     (0)
#endif
/** @} */

#ifdef __cplusplus
}
#endif

#endif
