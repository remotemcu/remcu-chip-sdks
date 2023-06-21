/**
 * \file
 *
 * \brief TX Service
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

 /**
 * \mainpage
 * \section preface Preface
 * This is the reference manual for the Atmel BLE SDK
 */
/****************************************************************************************
*							        Includes                                     		*
****************************************************************************************/
#include "tx_power.h"

#if defined TXPS_GATT_SERVER
/****************************************************************************************
*							        Global	                                     		*
****************************************************************************************/
uint8_t tx_power_initial_value = DEFAULT_TX_PWR_VALUE;



/** @brief Tx power service initialization
  * 
  */

void init_tx_power_service(gatt_service_handler_t *tx_power_serv )
{
	
	tx_power_serv->serv_handle = 0;
	tx_power_serv->serv_uuid.type = AT_BLE_UUID_16;
	
	tx_power_serv->serv_uuid.uuid[0] = (uint8_t) TX_POWER_SERVICE_UUID ;
	tx_power_serv->serv_uuid.uuid[1] = (uint8_t) (TX_POWER_SERVICE_UUID >> 8); 
	
	/*Characteristic Info for Alert Value*/
	
	 /* handle stored here */
	tx_power_serv->serv_chars->char_val_handle = 0;         
	
	/* UUID : Alert Level */
	tx_power_serv->serv_chars->uuid.type = AT_BLE_UUID_16;
	tx_power_serv->serv_chars->uuid.uuid[0] = (uint8_t) TX_POWER_LEVEL_CHAR_UUID  ;           
	tx_power_serv->serv_chars->uuid.uuid[1] = (uint8_t) (TX_POWER_LEVEL_CHAR_UUID >> 8);         
	
	 /* Properties */
	tx_power_serv->serv_chars->properties = AT_BLE_CHAR_READ ; 
	
	/* value */
	tx_power_serv->serv_chars->init_value = &tx_power_initial_value ; 
	tx_power_serv->serv_chars->value_init_len = sizeof(int8_t);
	tx_power_serv->serv_chars->value_max_len = sizeof(int8_t);
	
	/* permissions */
	tx_power_serv->serv_chars->value_permissions = (AT_BLE_ATTR_READABLE_NO_AUTHN_NO_AUTHR | AT_BLE_ATTR_WRITABLE_NO_AUTHN_NO_AUTHR);   
	
	/* user defined name */
	tx_power_serv->serv_chars->user_desc = NULL;           
	tx_power_serv->serv_chars->user_desc_len = 0;
	tx_power_serv->serv_chars->user_desc_max_len = 0;
	
	/*user description permissions*/
	tx_power_serv->serv_chars->user_desc_permissions = AT_BLE_ATTR_NO_PERMISSIONS;             
	
	/*client config permissions*/
	tx_power_serv->serv_chars->client_config_permissions = AT_BLE_ATTR_NO_PERMISSIONS;         
	
	/*server config permissions*/
	tx_power_serv->serv_chars->server_config_permissions = AT_BLE_ATTR_NO_PERMISSIONS;         
	
	 /*user desc handles*/
	tx_power_serv->serv_chars->user_desc_handle = 0;            
	
	/*client config handles*/
	tx_power_serv->serv_chars->client_config_handle = 0;         
	
	/*server config handles*/
	tx_power_serv->serv_chars->server_config_handle = 0;         
	
	/* presentation format */
	tx_power_serv->serv_chars->presentation_format = NULL;       
	
}



/** @brief Tx power service definition
  * 
  */

at_ble_status_t txps_primary_service_define(gatt_service_handler_t *txps_primary_service)
{
	
	return(at_ble_primary_service_define(&txps_primary_service->serv_uuid,
											&txps_primary_service->serv_handle,
											NULL, TXPS_INCLUDED_SERVICE_COUNT,
											txps_primary_service->serv_chars, TXPS_CHARACTERISTIC_COUNT));
}	

#endif //TXPS_GATT_SERVER

#if defined TXPS_GATT_CLIENT
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
		at_ble_handle_t char_handle)
{
	if (char_handle == TXPS_INVALID_CHAR_HANDLE) {
		return (AT_BLE_INVALID_HANDLE);
	} else {
		return (at_ble_characteristic_read(conn_handle, char_handle,
		       TXPS_POWER_READ_OFFSET,
		       TXPS_POWER_READ_LENGTH));
	}
}

/**@brief Read a Tx Power
 *
 * @param[in] read_value read response data available form
 *at_ble_characteristic_read_response_t
 * @return TX power in dBm .
 * @return @ref TXPS_INVALID_POWER_VALUE if is not valid result
 */
int8_t txps_power_read_response(
		at_ble_characteristic_read_response_t *char_read_resp,
		gatt_txps_char_handler_t *txps_handler)
{
	int8_t tx_power = TXPS_INVALID_POWER_VALUE;
	if (char_read_resp->char_handle == txps_handler->char_handle) {
		tx_power = char_read_resp->char_value[TXPS_POWER_READ_OFFSET];
		 DBG_LOG("Tx Power of device is %02d dBm", tx_power); 
		memcpy(txps_handler->char_data,
				&char_read_resp->char_value[
					TXPS_POWER_READ_OFFSET],
				TXPS_POWER_READ_LENGTH);
	}

	return tx_power;
}
#endif //TXPS_GATT_CLIENT