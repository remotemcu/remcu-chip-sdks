/**
 * \file
 *
 * \brief Immediate Alert Service declarations
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


#ifndef __IMMEDIATE_ALERT_H__
#define __IMMEDIATE_ALERT_H__

#include "ble_manager.h"

/**
@defgroup sdk Atmel BLE SDK

@{
*/

/** @brief count of included service in immediate alert service
  * 
  */
#define IAS_INCLUDED_SERVICE_COUNT	(0)

/** @brief count of characteristics in immediate alert service
  * 
  */
#define IAS_CHARACTERISTIC_COUNT	(1)

/** @brief Invalid parameter written
  * 
  */
#define INVALID_IAS_PARAM			(0xff)

/* Immediate alert levels */
typedef enum immediate_alert_level {
	IAS_NO_ALERT,
	IAS_MID_ALERT,
	IAS_HIGH_ALERT
} immediate_alert_level_t;


/****************************************************************************************
*							        Function Prototypes	                                *
****************************************************************************************/

#if defined IAS_GATT_CLIENT

/* Maximum character data size to support */
#define MAX_IAS_CHAR_SIZE                       (1)

/* Character pointer to start data write */
#define IAS_WRITE_OFFSET                        (0)

/* Immediate Alert write length */
#define IAS_WRITE_LENGTH                        (1)

/* Immediate alert write without response */
#define IAS_WRITE_WITH_RESPONSE					(false)

/* Perform the signed write  */
#define IAS_NO_SIGNED_WRITE                     (false)

typedef struct gatt_ias_char_handler
{
	at_ble_handle_t start_handle;
	at_ble_handle_t end_handle;
	at_ble_handle_t char_handle;
	at_ble_status_t char_discovery;
	uint8_t *char_data;
}gatt_ias_char_handler_t;


/**@brief write a characteristic  to Immediate Alert Characteristics
 *
 * if with_response is True, write completion will be reported via @ref
 *AT_BLE_CHARACTERISTIC_WRITE_RESPONSE event
 *
 * @param[in] conn_handle handle of the connection
 * @param[in] char_handle handle of the characteristic
 * @param[in] alert level need to write
 *
 * @return @ref AT_BLE_SUCCESS operation completed successfully
 * @return @ref AT_BLE_FAILURE Generic error.
 */
at_ble_status_t ias_alert_level_write(at_ble_handle_t conn_handle,
		at_ble_handle_t char_handle,
		immediate_alert_level_t alert_level);

#endif /*__IAS_GATT_CLIENT__*/


#if defined IAS_GATT_SERVER

/** @brief Initialize the Immediate alert service with default values
  * 
  *
  * @param[in] gatt_service_handler_t  the service info which has handle range,uuid and characteristic array fields
  *
  * @pre Must be called before @ref ias_primary_service_define
  *
  * @return void
  */
void init_immediate_alert_service(gatt_service_handler_t *immediate_alert_serv);

/** @brief Defining Immediate alert service to the attribute data base
  * 
  *
  * @param[in] gatt_service_handler_t  the service info which has handle range,uuid and characteristic array fields
  *
  * @pre Must be called after @ref init_immediate_alert_service
  *
  * @return @ref AT_BLE_SUCCESS operation completed successfully
  * @return @ref AT_BLE_FAILURE Generic error.
  */

at_ble_status_t ias_primary_service_define(gatt_service_handler_t *ias_primary_service);

/** @brief sets the alert value of the immediate alert service
  * @param[in] gatt_service_handler_t  the service info which has handle range,uuid and characteristic array fields
  * @param[in] at_ble_characteristic_changed_t  the information of the characteristic changed.
  * @return @ref ias alert value
  */
uint8_t ias_set_alert_value(at_ble_characteristic_changed_t *change_params, gatt_service_handler_t *ias_handler);
#endif //IAS_GATT_SERVER

/** @}*/

#endif /* __IMMEDIATE_ALERT_H__ */