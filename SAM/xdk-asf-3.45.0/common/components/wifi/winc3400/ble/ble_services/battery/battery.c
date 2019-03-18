/**
 * \file
 *
 * \brief Battery service
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

#include "battery.h"

/** Initial value of the battery level characteristic value */
uint8_t battery_init_value = 10;

/** Presentation format of the batery level */
at_ble_char_presentation_t presentation_format;

extern at_ble_connected_t ble_connected_dev_info[MAX_DEVICE_CONNECTED];

/**@brief Initialize the service with its included service, characteristics, and descriptors
 *
 * @param[in] battery_serv gatt service information
 *
 * @return none
 */
void bat_init_service(gatt_service_handler_t *battery_serv, uint8_t *battery_value)
{
	battery_serv->serv_handle = 0;
	battery_serv->serv_uuid.type = AT_BLE_UUID_16;
	battery_serv->serv_uuid.uuid[0] = (uint8_t) BAT_SERVICE_UUID;
	battery_serv->serv_uuid.uuid[1] = (uint8_t) (BAT_SERVICE_UUID >> 8);
	
	//Battery service characteristic
	battery_serv->serv_chars[0].char_val_handle = 0;          /* handle stored here */
	battery_serv->serv_chars[0].uuid.type = AT_BLE_UUID_16;
	battery_serv->serv_chars[0].uuid.uuid[0] = (uint8_t) BAT_CHAR_BAT_LEVEL_UUID;          /* UUID : Manufacturer Name String */
	battery_serv->serv_chars[0].uuid.uuid[1] = (uint8_t) (BAT_CHAR_BAT_LEVEL_UUID >> 8);          /* UUID : Manufacturer Name String */
	battery_serv->serv_chars[0].properties = (AT_BLE_CHAR_READ | AT_BLE_CHAR_NOTIFY); /* Properties */
	battery_serv->serv_chars[0].init_value = &battery_init_value;             /* value */
	battery_serv->serv_chars[0].value_init_len = sizeof(uint8_t);
	battery_serv->serv_chars[0].value_max_len = sizeof(uint8_t);
	battery_serv->serv_chars[0].value_permissions = (AT_BLE_ATTR_READABLE_NO_AUTHN_NO_AUTHR | AT_BLE_ATTR_WRITABLE_NO_AUTHN_NO_AUTHR);   /* permissions */
	battery_serv->serv_chars[0].user_desc = NULL;           /* user defined name */
	battery_serv->serv_chars[0].user_desc_len = 0;
	battery_serv->serv_chars[0].user_desc_max_len = 0;
	battery_serv->serv_chars[0].user_desc_permissions = AT_BLE_ATTR_NO_PERMISSIONS;             /*user description permissions*/
	battery_serv->serv_chars[0].client_config_permissions = AT_BLE_ATTR_NO_PERMISSIONS;         /*client config permissions*/
	battery_serv->serv_chars[0].server_config_permissions = AT_BLE_ATTR_NO_PERMISSIONS;         /*server config permissions*/
	battery_serv->serv_chars[0].user_desc_handle = 0;             /*user desc handles*/
	battery_serv->serv_chars[0].client_config_handle = 0;         /*client config handles*/
	battery_serv->serv_chars[0].server_config_handle = 0;         /*server config handles*/
	
	presentation_format.format = BAT_CHAR_PRESENTATION_FORMAT_VALUE;
	presentation_format.exponent = BAT_CHAR_PRESENTATION_FORMAT_EXPONENT;
	presentation_format.unit =  BAT_CHAR_PRESENTATION_FORMAT_UNIT;
	presentation_format.name_space = BAT_CHAR_PRESENTATION_FORMAT_NAMESPACE;
	presentation_format.description = BAT_CHAR_PRESENTATION_FORMAT_DESCRIPTOR;
	
	battery_serv->serv_chars[0].presentation_format = &presentation_format;       /* presentation format */
}

/**@brief defining a initialized service 
 *
 * @param[in] battery_service gatt service information
 *
 * @return @ref AT_BLE_SUCCESS operation completed successfully
 * @return @ref AT_BLE_FAILURE Generic error.
 */
at_ble_status_t bat_primary_service_define(gatt_service_handler_t *battery_service)
{
	return(at_ble_primary_service_define(&battery_service->serv_uuid,
	&battery_service->serv_handle,
	NULL, 0,
	battery_service->serv_chars, 1));
}

/**@brief Function used to update characteristic value
 *
 * @param[in] battery_serv gatt service information
 * @param[in] char_len length of the new characteristic value
 * @param[in] char_data new characteristic value information
 * @return @ref AT_BLE_SUCCESS operation completed successfully
 * @return @ref AT_BLE_FAILURE Generic error.
 */
at_ble_status_t bat_update_char_value (gatt_service_handler_t *battery_serv , uint8_t char_data)
{
	/* Updating the att data base */
	if ((at_ble_characteristic_value_set(battery_serv->serv_chars[0].char_val_handle, &char_data, 0 , sizeof(uint8_t))) == AT_BLE_FAILURE){
		DBG_LOG("updating the characteristic failed");
		return AT_BLE_FAILURE;
	} else {
		DBG_LOG_DEV("updating the characteristic value is successful");
	}

	/* sending notification to the peer about change in the battery level */ 
	if((at_ble_notification_send(ble_connected_dev_info[0].handle, battery_serv->serv_chars[0].char_val_handle)) == AT_BLE_FAILURE) {
		DBG_LOG("sending notification to the peer failed");
		return AT_BLE_FAILURE;
	}
	else {
		DBG_LOG_DEV("sending notification to the peer successful");
		return AT_BLE_SUCCESS;
	}
}
