/**
 * \file
 *
 * \brief Heart Rate Service declarations
 *
 * Copyright (c) 2017-2018 Microchip Technology Inc. and its subsidiaries.
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


#ifndef __HEART_RATE_H__
#define __HEART_RATE_H__

#include "at_ble_api.h"
#include "ble_manager.h"

/**
@defgroup sdk Atmel BLE SDK

@{
*/
/************************************************************************/
/*								enum					
 *               */
/************************************************************************/
typedef enum {
	OTHERS = 0,
	CHEST,
	WRIST,
	FINGER,
	HAND,
	EAR_LOBE,
	FOOT,
} body_sensor_location_val;


/** @brief number for Enabling the notification */
#define HR_NOTIFICATION_DISABLE														(0)

/**@brief number for disabling the notification */
#define HR_NOTIFICATION_ENABLE														(1)

/**@brief number for resetting energy expended */
#define HR_CONTROL_POINT_RESET														(2)

/**@brief maximum size of flags field of hr mm characteristic in bytes */
#define HR_MM_FLAGS_SIZE                                                            (1)

/**@brief maximum size of heart rate  field of hr mm characteristic in bytes */
#define HR_MM_VAL_SIZE                                                              (2)

/**@brief maximum size of heart rate  field of hr mm characteristic in bytes */
#define HR_MM_EX_SIZE                                                               (2)

/**@brief maximum size of rr value field of hr mm characteristic in bytes */
#define HR_MM_RR_SIZE                                                               (2 * 2)

/** characteristic presentation format value */
#define HEART_RATE_CHAR_PRESENTATION_FORMAT_VALUE 0x04

/** @brief Characteristic presentation format exponent */
#define HEART_RATE_CHAR_PRESENTATION_FORMAT_EXPONENT 0x00

/** @brief Characteristic presentation format unit */
#define HEART_RATE_CHAR_PRESENTATION_FORMAT_UNIT HEART_RATE_SERVICE_UUID

/** @brief Characteristic presentation format namespace */
#define HEART_RATE_CHAR_PRESENTATION_FORMAT_NAMESPACE 0x01

/**  @brief Characteristic presentation format descriptor */
#define HEART_RATE_CHAR_PRESENTATION_FORMAT_DESCRIPTOR 0x0000


/**@brief Update the heart rate characteristic value after defining the services using bat_primary_service_define
 *
 * @param[in] heart_rate_serv heart rate service instance
 * @param[in] char_data New heart rate value
 * @return @ref AT_BLE_SUCCESS operation completed successfully
 * @return @ref AT_BLE_FAILURE Generic error.
 */
at_ble_status_t heart_rate_update_char_value (gatt_service_handler_t *heart_rate_serv , uint8_t *char_data, uint8_t length);

/**@brief Heart rate service and characteristic initialization(Called only once by user).
 *
 * @param[in] heart_rate_serv heart rate service instance
 *
 * @return none
 */
void heart_rate_init_service(gatt_service_handler_t *heart_rate_serv);

/**@brief Register a heart rate service instance inside stack. 
 *
 * @param[in] heart_rate_service heart rate service instance
 *
 * @return @ref AT_BLE_SUCCESS operation completed successfully
 * @return @ref AT_BLE_FAILURE Generic error.
 */
at_ble_status_t heart_rate_primary_service_define(gatt_service_handler_t *heart_rate_service);

 /** @}*/

#endif /* __HEART_RATE_H__ */
