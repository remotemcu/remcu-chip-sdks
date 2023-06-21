/**
 * \file
 *
 * \brief TX Service declarations
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


#ifndef __TX_POWER_H__
#define __TX_POWER_H__

#include "ble_manager.h"

/**
@defgroup sdk Atmel BLE SDK

@{
*/

 #if defined TXPS_GATT_SERVER

/****************************************************************************************
*							        Macros	                                     		*
****************************************************************************************/

/** @brief  DEFAULT_TX_PWR_VALUE the tx power value*/
#define DEFAULT_TX_PWR_VALUE			(6)


/** @brief count of included service in tx power service
  * 
  */
#define TXPS_INCLUDED_SERVICE_COUNT		(0)

/** @brief count of characteristics in tx power service
  * 
  */
#define TXPS_CHARACTERISTIC_COUNT		(1)

typedef struct gatt_txps_char_handler
{
	at_ble_handle_t start_handle;
	at_ble_handle_t end_handle;
	at_ble_handle_t char_handle;
	at_ble_status_t char_discovery;
	uint8_t *char_data;
}gatt_txps_char_handler_t;


/****************************************************************************************
*							        Function Declarations	                            *
****************************************************************************************/

/** @brief Initialize the tx power service with default values
  * 
  *
  * @param[in] gatt_service_handler_t  the service info which has handle range,uuid and characteristic array fields
  *
  * @pre Must be called before @ref txps_primary_service_define
  *
  * @return void
  */

void init_tx_power_service(gatt_service_handler_t *tx_power_serv);



/** @brief Defining the tx power service to the attribute data base
  * 
  *
  * @param[in] gatt_service_handler_t  the service info which has handle range,uuid and characteristic array fields
  *
  * @pre Must be called after @ref init_tx_power_service
  *
  * @return @ref AT_BLE_SUCCESS operation completed successfully
  * @return @ref AT_BLE_FAILURE Generic error.
  */
at_ble_status_t txps_primary_service_define(gatt_service_handler_t *txps_primary_service);
#endif//TXPS_GATT_SERVER

#if defined TXPS_GATT_CLIENT
/* Tx Power Maximum Character byte support */
#define MAX_TX_POWER_CHAR_SIZE                  (1)

/* Tx Power offset at where to start reading */
#define TXPS_POWER_READ_OFFSET                  (0)

/* Tx Power length of data to read */
#define TXPS_POWER_READ_LENGTH                  (1)

/* Tx Power invalid Characteristics handler */
#define TXPS_INVALID_CHAR_HANDLE                (0)

/* Tx Power invalid read Power value */
#define TXPS_INVALID_POWER_VALUE                (0xFF)

typedef struct gatt_txps_char_handler
{
	at_ble_handle_t start_handle;
	at_ble_handle_t end_handle;
	at_ble_handle_t char_handle;
	at_ble_status_t char_discovery;
	uint8_t *char_data;
}gatt_txps_char_handler_t;

/**@brief Send the Read Request to Tx Power service
 *
 * Read value will be reported via @ref AT_BLE_CHARACTERISTIC_READ_RESPONSE
 *event
 *
 * @param[in] conn_handle handle of the connection
 * @param[in] char_handle handle of the characteristic
 * @return @ref AT_BLE_SUCCESS operation completed successfully
 * @return @ref AT_BLE_INVALID_PARAM Invalid arguments.
 * @return @ref AT_BLE_FAILURE Generic error.
 */
at_ble_status_t txps_power_read(at_ble_handle_t conn_handle,
    at_ble_handle_t char_handle);

/**@brief Read a Tx Power
 *
 * @param[in] read_value read response data available form
 *at_ble_characteristic_read_response_t
 * @return TX power in dBm .
 * @return @ref TXPS_INVALID_POWER_VALUE if is not valid result
 */
int8_t txps_power_read_response(
    at_ble_characteristic_read_response_t *char_read_resp,
    gatt_txps_char_handler_t *txps_handler);
#endif //TXPS_GATT_CLIENT

/** @}*/

#endif /* __TX_POWER_H__ */