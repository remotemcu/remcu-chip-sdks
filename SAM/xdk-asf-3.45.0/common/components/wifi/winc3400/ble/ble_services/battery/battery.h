/**
 * \file
 *
 * \brief Battery Service declarations
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


#ifndef __BATTERY_H__
#define __BATTERY_H__

#include "at_ble_api.h"
#include "ble_manager.h"

/**
@defgroup sdk Atmel BLE SDK

@{
*/

/** characteristic presentation format value */
#define BAT_CHAR_PRESENTATION_FORMAT_VALUE 0x04

/** @brief Characteristic presentation format exponent */
#define BAT_CHAR_PRESENTATION_FORMAT_EXPONENT 0x00

/** @brief Characteristic presentation format unit */
#define BAT_CHAR_PRESENTATION_FORMAT_UNIT BAT_SERVICE_UUID

/** @brief Characteristic presentation format namespace */
#define BAT_CHAR_PRESENTATION_FORMAT_NAMESPACE 0x01

/**  @brief Characteristic presentation format descriptor */
#define BAT_CHAR_PRESENTATION_FORMAT_DESCRIPTOR 0x0000


/**@brief Update the battery characteristic value after defining the services using bat_primary_service_define
 *
 * @param[in] battery_serv battery service instance
 * @param[in] char_data New battery level
 * @return @ref AT_BLE_SUCCESS operation completed successfully
 * @return @ref AT_BLE_FAILURE Generic error.
 */
at_ble_status_t bat_update_char_value (gatt_service_handler_t *battery_serv , uint8_t char_data);

/**@brief Battery service and characteristic initialization(Called only once by user).
 *
 * @param[in] battery_serv battery service instance
 *
 * @return none
 */
void bat_init_service(gatt_service_handler_t *battery_serv, uint8_t *battery_value);

/**@brief Register a battery service instance inside stack. 
 *
 * @param[in] battery_service battery service instance
 *
 * @return @ref AT_BLE_SUCCESS operation completed successfully
 * @return @ref AT_BLE_FAILURE Generic error.
 */
at_ble_status_t bat_primary_service_define(gatt_service_handler_t *battery_service);

 /** @}*/

#endif /* __BATTERY_H__ */