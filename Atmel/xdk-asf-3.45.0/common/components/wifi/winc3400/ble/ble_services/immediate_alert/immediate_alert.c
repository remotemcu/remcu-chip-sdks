/**
 * \file
 *
 * \brief Immediate Alert service
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
*							        Includes                                     		*
****************************************************************************************/
#include "immediate_alert.h"

#if defined IAS_GATT_SERVER
/****************************************************************************************
*							        Globals                                     		*
****************************************************************************************/

uint8_t immediate_alert_initial_value = 0;

/****************************************************************************************
*							        Implementation                                     	*
****************************************************************************************/

/** @brief Immediate alert service initialization
  * 
  */
void init_immediate_alert_service(gatt_service_handler_t *immediate_alert_serv ) 
{
		immediate_alert_serv->serv_handle = 0;
		immediate_alert_serv->serv_uuid.type = AT_BLE_UUID_16;
		
		immediate_alert_serv->serv_uuid.uuid[0]= (uint8_t)IMMEDIATE_ALERT_SERVICE_UUID;
		immediate_alert_serv->serv_uuid.uuid[1] = (uint8_t)(IMMEDIATE_ALERT_SERVICE_UUID >> 8);
		
		//Characteristic Info for Alert Value
		
		/* handle stored here */
		immediate_alert_serv->serv_chars->char_val_handle = 0;       
		
		/* UUID : Alert Level */ 
		immediate_alert_serv->serv_chars->uuid.type = AT_BLE_UUID_16;
		immediate_alert_serv->serv_chars->uuid.uuid[0] = (uint8_t) ALERT_LEVEL_CHAR_UUID;         
		immediate_alert_serv->serv_chars->uuid.uuid[1] = (uint8_t) (ALERT_LEVEL_CHAR_UUID >> 8);          
		
		 /* Properties */
		immediate_alert_serv->serv_chars->properties = AT_BLE_CHAR_WRITE_WITHOUT_RESPONSE;
		
		/* value */
		immediate_alert_serv->serv_chars->init_value = &immediate_alert_initial_value; 
		immediate_alert_serv->serv_chars->value_init_len = sizeof(int8_t);
		immediate_alert_serv->serv_chars->value_max_len = sizeof(int8_t);
		immediate_alert_serv->serv_chars->value_permissions = (AT_BLE_ATTR_READABLE_NO_AUTHN_NO_AUTHR | AT_BLE_ATTR_WRITABLE_NO_AUTHN_NO_AUTHR);   /* permissions */
		
		/* user defined name */
		immediate_alert_serv->serv_chars->user_desc = NULL;           
		immediate_alert_serv->serv_chars->user_desc_len = 0;
		immediate_alert_serv->serv_chars->user_desc_max_len = 0;
		
		/*user description permissions*/
		immediate_alert_serv->serv_chars->user_desc_permissions = AT_BLE_ATTR_NO_PERMISSIONS;             
		
		/*client config permissions*/
		immediate_alert_serv->serv_chars->client_config_permissions = AT_BLE_ATTR_NO_PERMISSIONS;         
		
		/*server config permissions*/
		immediate_alert_serv->serv_chars->server_config_permissions = AT_BLE_ATTR_NO_PERMISSIONS;         
		
		/*user desc handles*/
		immediate_alert_serv->serv_chars->user_desc_handle = 0;             
		
		/*client config handles*/
		immediate_alert_serv->serv_chars->client_config_handle = 0;         
		
		 /*server config handles*/
		immediate_alert_serv->serv_chars->server_config_handle = 0;        
		
		/* presentation format */
		immediate_alert_serv->serv_chars->presentation_format = NULL;       
		
}


/** @brief Immediate alert service definition
  * 
  */
at_ble_status_t ias_primary_service_define(gatt_service_handler_t *ias_primary_service)
{
	
	return(at_ble_primary_service_define(&ias_primary_service->serv_uuid,
											&ias_primary_service->serv_handle,
											NULL, IAS_INCLUDED_SERVICE_COUNT,
											ias_primary_service->serv_chars, IAS_CHARACTERISTIC_COUNT));
}

/** @brief Setting Alert Level Value of immediate alert service
  * 
  */
uint8_t ias_set_alert_value(at_ble_characteristic_changed_t *change_params, gatt_service_handler_t *ias_handler)
{
	if (change_params->char_handle == ias_handler->serv_chars->char_val_handle)
	{
				return change_params->char_new_value[0];
	}
	return INVALID_IAS_PARAM;
}

#endif //IAS_GATT_SERVER

#if defined IAS_GATT_CLIENT
/**@brief write a characteristic  to Immediate Alert Characteristics
 *
 * if with_response is True, write completion will be reported via @ref
 *AT_BLE_CHARACTERISTIC_WRITE_RESPONSE event
 *
 * @param[in] conn_handle handle of the connection
 * @param[in] char_handle handle of the characteristic
 * @param[in] alert_level alert level need to write
 *
 * @return @ref AT_BLE_SUCCESS operation completed successfully
 * @return @ref AT_BLE_FAILURE Generic error.
 */
at_ble_status_t ias_alert_level_write(at_ble_handle_t conn_handle,
		at_ble_handle_t char_handle,
		immediate_alert_level_t alert_level)
{
	/* for immediate alert write without response */
	return (at_ble_characteristic_write(conn_handle,
	       char_handle,
	       IAS_WRITE_OFFSET,
	       IAS_WRITE_LENGTH,
	       &alert_level,
	       IAS_NO_SIGNED_WRITE,
	       IAS_WRITE_WITH_RESPONSE));
}

#endif //IAS_GATT_CLIENT
