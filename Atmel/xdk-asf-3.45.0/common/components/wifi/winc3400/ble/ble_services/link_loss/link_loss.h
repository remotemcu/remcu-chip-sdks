/**
 * \file
 *
 * \brief Link Loss Service declarations
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


#ifndef __LINK_LOSS_H__
#define __LINK_LOSS_H__

#include "at_ble_api.h"
#include "ble_utils.h"
#include "ble_manager.h"

/**
@defgroup sdk Atmel BLE SDK

@{
*/

 #if defined LLS_GATT_SERVER

/** @brief count of included service in Linkloss service
  * 
  */

#define LLS_INCLUDED_SERVICE_COUNT  (0)

/** @brief count of characteristics in linkloss service
  * 
  */
#define LLS_CHARACTERISTIC_COUNT	(1)

#define INVALID_LLS_PARAM			(0xff)

typedef enum linkloss_alert_level {
	LLS_NO_ALERT,
	LLS_MILD_ALERT,
	LLS_HIGH_ALERT
} linkloss_alert_level_t;

typedef struct gatt_lls_char_handler
{
	at_ble_handle_t start_handle;
	at_ble_handle_t end_handle;
	at_ble_handle_t char_handle;
	at_ble_status_t char_discovery;
	uint8_t *char_data;
}gatt_lls_char_handler_t;

/****************************************************************************************
*							        Function Prototypes	                                     							*
****************************************************************************************/

/** @brief Initialize the linkloss service with default values
  * 
  *
  * @param[in] gatt_service_handler_t  the service info which has handle range,uuid and characteristic array fields
  *
  * @pre Must be called before @ref lls_primary_service_define
  *
  * @return void
  */
void init_linkloss_service(gatt_service_handler_t *linkloss_serv);

/** @brief Defining linkloss service to the attribute data base
  * 
  *
  * @param[in] gatt_service_handler_t  the service info which has handle range,uuid and characteristic array fields
  *
  * @pre Must be called after @ref init_linkloss_service
  *
  * @return @ref AT_BLE_SUCCESS operation completed successfully
  * @return @ref AT_BLE_FAILURE Generic error.
  */

at_ble_status_t lls_primary_service_define(gatt_service_handler_t *lls_service);


/** @brief sets the alert value of the Linkloss service
  * @param[in] gatt_service_handler_t  the service info which has handle range,uuid and characteristic array fields
  * @param[in] at_ble_characteristic_changed_t  the information of the characteristic changed.
  * @return @ref ias alert value
  */
uint8_t lls_set_alert_value(at_ble_characteristic_changed_t *change_params, gatt_service_handler_t *lls_handler);

#endif //LLS_GATT_SERVER

#if defined LLS_GATT_CLIENT
#define MAX_LLS_CHAR_SIZE                       (1)

/* Link Loss write offset value */
#define LLS_WRITE_OFFSET                        (0)

/* Link loss Data write length */
#define LLS_WRITE_LENGTH                        (1)

/* Link Loss write with response */
#define LLS_WRITE_WITH_RESPONSE         (true)

/* Link Loss no signed write */
#define LLS_NO_SIGNED_WRITE                     (false)

/* Link Loss Alert length of data to read */
#define LLS_READ_LENGTH                         (1)

/* Link Loss read offset length*/
#define LLS_READ_OFFSET                         (0)

/* Link Loss invalid character handler*/
#define LLS_INVALID_CHAR_HANDLE         (0)

/* Link Loss invalid read response value */
#define LLS_READ_RESP_INVALID         (0xFF)

#define LLS_ALERT_LEVEL                         LLS_HIGH_ALERT

typedef enum {
  LLS_NO_ALERT,
  LLS_LOW_ALERT,
  LLS_HIGH_ALERT
} link_loss_alert_level_t;

typedef struct gatt_lls_char_handler
{
	at_ble_handle_t start_handle;
	at_ble_handle_t end_handle;
	at_ble_handle_t char_handle;
	at_ble_status_t char_discovery;
	uint8_t *char_data;
}gatt_lls_char_handler_t;

/**@brief write a characteristic  to Link Loss Characteristics
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
at_ble_status_t lls_alert_level_write(at_ble_handle_t conn_handle,
    at_ble_handle_t char_handle,
    link_loss_alert_level_t alert_level);

/**@brief Send the Read request to link loss handler
 * Read value will be reported via @ref AT_BLE_CHARACTERISTIC_READ_RESPONSE
 *event
 *
 * @param[in] conn_handle handle of the connection
 * @param[in] char_handle handle of the characteristic
 * @return @ref AT_BLE_SUCCESS operation completed successfully
 * @return @ref AT_BLE_INVALID_PARAM Invalid arguments.
 * @return @ref AT_BLE_FAILURE Generic error.
 */
at_ble_status_t lls_alert_level_read(at_ble_handle_t conn_handle,
    at_ble_handle_t char_handle);

/**@brief Read Link Loss Alert Value
 *
 * @param[in] read_value read response data available form
 *at_ble_characteristic_read_response_t
 * @return Link Loss Alert level .
 * @return LLS_READ_RESP_INVALID if value are other than alert levels
 */
int8_t lls_alert_read_response(at_ble_characteristic_read_response_t *read_resp,
    gatt_lls_char_handler_t *lls_handler);
#endif //LLS_GATT_CLIENT

 /** @}*/

#endif /* __LINK_LOSS_H__ */