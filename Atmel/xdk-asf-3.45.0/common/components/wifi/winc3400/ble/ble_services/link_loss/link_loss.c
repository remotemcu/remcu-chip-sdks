/**
 * \file
 *
 * \brief Linkloss service
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

/* can only have one mainpage/preface for doxygen see ble_sdk\ble_services\tx_power\tx_power.c */
/****************************************************************************************
*							        Includes	                                     	*
****************************************************************************************/

#include "link_loss.h"

#if defined LLS_GATT_SERVER
/****************************************************************************************
*							        Globals	                                     		*
****************************************************************************************/

uint8_t linkloss_initial_value = 0;


/****************************************************************************************
*							        Implementations	                                    *
****************************************************************************************/



/** @brief Linkloss service initialization
  * 
  */
void init_linkloss_service(gatt_service_handler_t *linkloss_serv)
{
	 
	 linkloss_serv->serv_handle = 0;
	 linkloss_serv->serv_uuid.type = AT_BLE_UUID_16;
	
	 linkloss_serv->serv_uuid.uuid[0] = (uint8_t) LINK_LOSS_SERVICE_UUID	; 
	 linkloss_serv->serv_uuid.uuid[1] = (uint8_t) (LINK_LOSS_SERVICE_UUID >> 8);
	 
	 //Characteristic Info for Alert Value
	 
	 /* handle stored here */
	 linkloss_serv->serv_chars->char_val_handle = 0;
	           
	 /*16bit UUID : Alert Level */
	 linkloss_serv->serv_chars->uuid.type = AT_BLE_UUID_16;
	
	 linkloss_serv->serv_chars->uuid.uuid[0] = (uint8_t)  ALERT_LEVEL_CHAR_UUID;
	 linkloss_serv->serv_chars->uuid.uuid[1] = (uint8_t) (ALERT_LEVEL_CHAR_UUID >> 8);
	
	 /* Properties */
	 linkloss_serv->serv_chars->properties = AT_BLE_CHAR_READ | AT_BLE_CHAR_WRITE; 
	
	 /* value */
	 linkloss_serv->serv_chars->init_value = &linkloss_initial_value ; 
	 linkloss_serv->serv_chars->value_init_len = sizeof(int8_t);
	 linkloss_serv->serv_chars->value_max_len = sizeof(int8_t);
	
	 /* permissions */
	 linkloss_serv->serv_chars->value_permissions = (AT_BLE_ATTR_READABLE_NO_AUTHN_NO_AUTHR | AT_BLE_ATTR_WRITABLE_NO_AUTHN_NO_AUTHR);   
	
	 /* user defined name */
	 linkloss_serv->serv_chars->user_desc = NULL;           
	 linkloss_serv->serv_chars->user_desc_len = 0;
	 linkloss_serv->serv_chars->user_desc_max_len = 0;
	
	 /*user description permissions*/
	 linkloss_serv->serv_chars->user_desc_permissions = AT_BLE_ATTR_NO_PERMISSIONS;             
	
	 /*client config permissions*/
	 linkloss_serv->serv_chars->client_config_permissions = AT_BLE_ATTR_NO_PERMISSIONS;         
	
	  /*server config permissions*/
	 linkloss_serv->serv_chars->server_config_permissions = AT_BLE_ATTR_NO_PERMISSIONS;        
	
	  /*user desc handles*/
	 linkloss_serv->serv_chars->user_desc_handle = 0;            
	
	  /*client config handles*/
	 linkloss_serv->serv_chars->client_config_handle = 0;        
	
	 /*server config handles*/
	 linkloss_serv->serv_chars->server_config_handle = 0;         
	
	 /* presentation format */
	 linkloss_serv->serv_chars->presentation_format = NULL;       
	
}
 

/** @brief linkloss service definition
  * 
  */
at_ble_status_t lls_primary_service_define(gatt_service_handler_t *lls_service)
{
	return(at_ble_primary_service_define(&lls_service->serv_uuid,
											&lls_service->serv_handle,
											NULL, LLS_INCLUDED_SERVICE_COUNT,  
											lls_service->serv_chars, LLS_CHARACTERISTIC_COUNT));
}


/** @brief Setting the alert value of linkloss service
  * 
  */
uint8_t lls_set_alert_value(at_ble_characteristic_changed_t *change_params, gatt_service_handler_t *lls_handler)
{
	if (change_params->char_handle == lls_handler->serv_chars->char_val_handle)
	{
		DBG_LOG("The current alert level for linkloss is %x",change_params->char_new_value[0]);
		return change_params->char_new_value[0];
	}
	return INVALID_LLS_PARAM;
}

#endif //LLS_GATT_SERVER

#if defined LLS_GATT_CLIENT
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
		link_loss_alert_level_t alert_level)
{
	/* for link loss alert write with response */
	return (at_ble_characteristic_write(conn_handle,
	       char_handle,
	       LLS_WRITE_OFFSET,
	       LLS_WRITE_LENGTH,
	       &alert_level,
	       LLS_NO_SIGNED_WRITE,
	       LLS_WRITE_WITH_RESPONSE));
}

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
		at_ble_handle_t char_handle)
{
	if (char_handle == LLS_INVALID_CHAR_HANDLE) {
		return (AT_BLE_INVALID_HANDLE);
	} else {
		return (at_ble_characteristic_read(conn_handle,
		       char_handle,
		       LLS_READ_OFFSET,
		       LLS_READ_LENGTH));
	}
}

/**@brief Read Link Loss Alert Value
 *
 * @param[in] read_value read response data available form
 *at_ble_characteristic_read_response_t
 * @return Link Loss Alert level .
 * @return LLS_READ_RESP_INVALID if value are other than alert levels
 */
int8_t lls_alert_read_response(at_ble_characteristic_read_response_t *read_resp,
		gatt_lls_char_handler_t *lls_handler)
{
	if (read_resp->char_handle == lls_handler->char_handle) {
		memcpy(lls_handler->char_data,
				&read_resp->char_value[LLS_READ_OFFSET],
				LLS_READ_LENGTH);

		DBG_LOG("Link Loss Alert level set to");

		switch (read_resp->char_value[LLS_READ_OFFSET]) {
		case LLS_NO_ALERT:
		{
			DBG_LOG_CONT(" NO ALERT ");
		}
		break;

		case LLS_LOW_ALERT:
		{
			DBG_LOG_CONT(" LOW ALERT ");
		}
		break;

		case LLS_HIGH_ALERT:
		{
			DBG_LOG_CONT(" HIGH ALERT ");
		}
		break;
		}
		return (read_resp->char_value[LLS_READ_OFFSET]);
	}

	return(LLS_READ_RESP_INVALID);
}
#endif //LLS_GATT_CLIENT