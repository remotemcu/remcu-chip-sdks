/**
 * \file
 *
 * \brief Transparent service
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

#include "trans_service.h"

/************************************************************************/
/*							Globals	
 *                                   */
/************************************************************************/
uint8_t trans_tx = 0x0;
uint8_t trans_rx = 0x0;
uint8_t trans_ctrl = 0x0;

uint8_t trans_tx_notification_flag = false;
uint8_t trans_ctrl_notification_flag = false;

uint8_t enable_credit_based_fc = false;

at_ble_uuid_t trans_service_uuid = {
	AT_BLE_UUID_128,
	{
		UUID_MCHP_PROPRIETARY_SERVICE_16
	}
};

static at_ble_uuid_t trans_tx_char_uuid = {
	AT_BLE_UUID_128,
	{
		UUID_MCHP_TRANS_TX_16
	}
};

static at_ble_uuid_t trans_rx_char_uuid = {
	AT_BLE_UUID_128,
	{
		UUID_MCHP_TRANS_RX_16
	}
};

static at_ble_uuid_t trans_ctrl_char_uuid = {
	AT_BLE_UUID_128,
	{
		UUID_MCHP_TRANS_CTRL_16
	}
};

extern at_ble_connected_t ble_connected_dev_info[MAX_DEVICE_CONNECTED];

static at_ble_characteristic_t trans_chars[] = {
		{
			0, /* handle stored here */
			{	
				AT_BLE_UUID_128, {UUID_MCHP_TRANS_TX_16}
			}, /* UUID */
			AT_BLE_CHAR_WRITE_WITHOUT_RESPONSE | AT_BLE_CHAR_NOTIFY, /* Properties */
			(uint8_t *)&trans_tx, sizeof(uint8_t), 0x200, /* value */
			AT_BLE_ATTR_WRITABLE_NO_AUTHN_NO_AUTHR, /* permissions */
	
			NULL, 0, 0, /* user defined name */
			AT_BLE_ATTR_NO_PERMISSIONS, AT_BLE_ATTR_NO_PERMISSIONS, AT_BLE_ATTR_NO_PERMISSIONS, 0,0,0, /* Handles */
			NULL /* presentation format */
		},
		{
			0, /* handle stored here */
			{
				AT_BLE_UUID_128, {UUID_MCHP_TRANS_RX_16}
			}, /* UUID */
			AT_BLE_CHAR_WRITE, /* Properties */
			(uint8_t *)&trans_rx, sizeof(uint8_t), 0x200, /* value */
			AT_BLE_ATTR_WRITABLE_NO_AUTHN_NO_AUTHR, /* permissions */
	
			NULL, 0, 0, /* user defined name */
			AT_BLE_ATTR_NO_PERMISSIONS, AT_BLE_ATTR_NO_PERMISSIONS, AT_BLE_ATTR_NO_PERMISSIONS, 0, 0, 0, /* Handles */
			NULL /* presentation format */
		},
		{
			0, /* handle stored here */
			{
				AT_BLE_UUID_128, {UUID_MCHP_TRANS_CTRL_16}
			}, /* UUID */
			AT_BLE_CHAR_WRITE | AT_BLE_CHAR_NOTIFY, /* Properties */
			(uint8_t *)&trans_ctrl, sizeof(uint8_t), 5, /* value */
			AT_BLE_ATTR_NO_PERMISSIONS, /* permissions */
	
			NULL, 0, 0, /* user defined name */
			AT_BLE_ATTR_NO_PERMISSIONS, AT_BLE_ATTR_NO_PERMISSIONS, AT_BLE_ATTR_NO_PERMISSIONS, 0, 0, 0, /* Handles */
			NULL /* presentation format */
		}		
	};

/**@brief Initialize the service with its included service, characteristics, and descriptors
 *
 * @param[in] trans_service gatt service information
 *
 * @return none
 */
void trans_service_init(gatt_service_handler_t *trans_service)
{
        uint8_t i;
	trans_service->serv_handle = 0;
	trans_service->serv_uuid.type = AT_BLE_UUID_128;
    memcpy(&trans_service->serv_uuid.uuid, trans_service_uuid.uuid, 16);
    
    printf("\nService UUID: ");
    for(i=0;i<16;i++)printf("%2x ",trans_service->serv_uuid.uuid[i]);
    printf("\r\n");
    
	/*Characteristic Info for Transparent Tx*/

	/* handle stored here */
	trans_service->serv_chars[0].char_val_handle = 0;
	trans_service->serv_chars[0].uuid.type = AT_BLE_UUID_128;

	/* UUID : UUID_MCHP_TRANS_TX_16 Characteristic */
    memcpy(&trans_service->serv_chars[0].uuid.uuid,trans_tx_char_uuid.uuid, 16);
    
    printf("Char Tx UUID: ");
    for(i=0;i<16;i++)printf("%2x ",trans_service->serv_chars[0].uuid.uuid[i]);
    printf("\r\n");

	/* Properties */
	trans_service->serv_chars[0].properties = (AT_BLE_CHAR_WRITE_WITHOUT_RESPONSE | AT_BLE_CHAR_NOTIFY);

	trans_service->serv_chars[0].init_value = (uint8_t *)&trans_tx;
	trans_service->serv_chars[0].value_init_len = sizeof(uint16_t);

	trans_service->serv_chars[0].value_max_len = 0x200;
	
	/* Permissions */
	trans_service->serv_chars[0].value_permissions
							= AT_BLE_ATTR_WRITABLE_NO_AUTHN_NO_AUTHR;
	
	/* user defined name */
	trans_service->serv_chars[0].user_desc = NULL;
	trans_service->serv_chars[0].user_desc_len = 0;
	trans_service->serv_chars[0].user_desc_max_len = 0;
	/*user description permissions*/
	trans_service->serv_chars[0].user_desc_permissions = AT_BLE_ATTR_NO_PERMISSIONS;	
	/* client config permissions */
	trans_service->serv_chars[0].client_config_permissions = AT_BLE_ATTR_NO_PERMISSIONS;	
	/*server config permissions*/
	trans_service->serv_chars[0].server_config_permissions = AT_BLE_ATTR_NO_PERMISSIONS;
	/*user desc handles*/
	trans_service->serv_chars[0].user_desc_handle = 0;
	/*client config handles*/
	trans_service->serv_chars[0].client_config_handle = 0;
	/*server config handles*/
	trans_service->serv_chars[0].server_config_handle = 0;
	/* presentation format */
	trans_service->serv_chars[0].presentation_format = NULL;

    	/* Characteristic Info for Transparent Tx */
	trans_service->serv_chars[1].char_val_handle = 0; 
	trans_service->serv_chars[1].uuid.type = AT_BLE_UUID_128;
	/* UUID : Transparent Tx*/
    memcpy(&trans_service->serv_chars[1].uuid.uuid,trans_rx_char_uuid.uuid, 16);

    
	/* Properties */
	trans_service->serv_chars[1].properties = AT_BLE_CHAR_WRITE;

	trans_service->serv_chars[1].init_value = &trans_rx;

	trans_service->serv_chars[1].value_init_len = sizeof(uint8_t);
	trans_service->serv_chars[1].value_max_len = 0x200;

	/* permissions */
        trans_service->serv_chars[1].value_permissions
							= AT_BLE_ATTR_WRITABLE_NO_AUTHN_NO_AUTHR;
    
	/* user defined name */
	trans_service->serv_chars[1].user_desc = NULL;
	trans_service->serv_chars[1].user_desc_len = 0;
	trans_service->serv_chars[1].user_desc_max_len = 0;
	/*user description permissions*/
	trans_service->serv_chars[1].user_desc_permissions
		= AT_BLE_ATTR_NO_PERMISSIONS;
	/*client config permissions*/
	trans_service->serv_chars[1].client_config_permissions
		= AT_BLE_ATTR_NO_PERMISSIONS;
	/*server config permissions*/
	trans_service->serv_chars[1].server_config_permissions
		= AT_BLE_ATTR_NO_PERMISSIONS;
	/*user desc handles*/
	trans_service->serv_chars[1].user_desc_handle = 0;
	/*client config handles*/
	trans_service->serv_chars[1].client_config_handle = 0;
	/*server config handles*/
	trans_service->serv_chars[1].server_config_handle = 0;
	/* presentation format */
	trans_service->serv_chars[1].presentation_format = NULL;

	/* Characteristic Info for Trans Control */
	/* handle stored here */
	trans_service->serv_chars[2].char_val_handle = 0;
	trans_service->serv_chars[2].uuid.type = AT_BLE_UUID_128;
	/* UUID : Trans Control */
    memcpy(&trans_service->serv_chars[2].uuid.uuid,trans_ctrl_char_uuid.uuid, 16);

    
	/* Properties */
	trans_service->serv_chars[2].properties = (AT_BLE_CHAR_WRITE | AT_BLE_CHAR_NOTIFY);

	/* Initial Value */
	trans_service->serv_chars[2].init_value = &trans_ctrl;

	trans_service->serv_chars[2].value_init_len = sizeof(uint8_t);
	trans_service->serv_chars[2].value_max_len = 5;
	
	/* permissions */
	trans_service->serv_chars[2].value_permissions
							= AT_BLE_ATTR_NO_PERMISSIONS;
	/* user defined name */
	trans_service->serv_chars[2].user_desc = NULL;
	trans_service->serv_chars[2].user_desc_len = 0;
	trans_service->serv_chars[2].user_desc_max_len = 0;
	/*user description permissions*/
	trans_service->serv_chars[2].user_desc_permissions = AT_BLE_ATTR_NO_PERMISSIONS;
	/*client config permissions*/
	trans_service->serv_chars[2].client_config_permissions = AT_BLE_ATTR_NO_PERMISSIONS;
	/*server config permissions*/
	trans_service->serv_chars[2].server_config_permissions = AT_BLE_ATTR_NO_PERMISSIONS;
	/*user desc handles*/
	trans_service->serv_chars[2].user_desc_handle = 0;
	/*client config handles*/
	trans_service->serv_chars[2].client_config_handle = 0;
	/*server config handles*/
	trans_service->serv_chars[2].server_config_handle = 0;
	/* presentation format */
	trans_service->serv_chars[2].presentation_format = NULL;

}

/**@brief defining a initialized service 
 *
 * @param[in] trans_service gatt service information
 *
 * @return @ref AT_BLE_SUCCESS operation completed successfully
 * @return @ref AT_BLE_FAILURE Generic error.
 */
at_ble_status_t trans_service_primary_service_define(gatt_service_handler_t *trans_service)
{
	at_ble_status_t status = AT_BLE_SUCCESS;
    trans_service->serv_chars[0] = trans_chars[0];
    trans_service->serv_chars[1] = trans_chars[1];
    trans_service->serv_chars[2] = trans_chars[2];

	if (at_ble_primary_service_define(&trans_service_uuid, &trans_service->serv_handle,
			NULL, 0, trans_service->serv_chars, 3) != AT_BLE_SUCCESS) {
		printf("trans_init_service: failed to define the primary service!\r\n");
		status = AT_BLE_FAILURE;
	} else {
		printf("trans_init_service: primary service defined.\r\n");
	}
	
	return status;
}

/**@brief Function used to update trans tx characteristic value
 */
at_ble_status_t trans_update_tx_char_value (gatt_service_handler_t *trans_service, uint8_t* trans_tx_value, uint8_t len)
{
	at_ble_status_t status = AT_BLE_SUCCESS;
	/* Updating the att data base */
    //printf("...!Tx handle:0x%X\r\n",trans_service->serv_chars[0].char_val_handle);
	if ((status = at_ble_characteristic_value_set(trans_service->serv_chars[0].char_val_handle, trans_tx_value, 0, len)) != AT_BLE_SUCCESS){
		DBG_LOG("updating the characteristic failed:%d\r\n",status);
		return status;
	} else {
		//DBG_LOG("updating the characteristic value is successful\r\n");
	}

	if(trans_tx_notification_flag){
		/* sending notification to the peer about change in the battery level */ 
		if((status = at_ble_notification_send(ble_connected_dev_info[0].handle, trans_service->serv_chars[0].char_val_handle)) != AT_BLE_SUCCESS) {
			DBG_LOG("sending notification failed:%d\r\n",status);
			return status;
		}
		else {
			//DBG_LOG("sending notification successful\r\n");
			return status;
		}
	}

	return status;
}
/**@brief Function used to update trans tx characteristic value
 */
 at_ble_status_t trans_update_ctrl_char_value (gatt_service_handler_t *trans_service, uint8_t* trans_ctrl_value, uint8_t len)
{
	at_ble_status_t status = AT_BLE_SUCCESS;
	uint8_t tmp_trans_ctrl_val[5];
	uint16_t actualLen = 0;

	if(enable_credit_based_fc ==  false)
	{
		DBG_LOG("Credit based flow control is not enabled\r\n");
		return AT_BLE_FAILURE;
	}
	if ((status = at_ble_characteristic_value_get(trans_service->serv_chars[2].char_val_handle, tmp_trans_ctrl_val, 0, 5, actualLen)) != AT_BLE_SUCCESS)
        {
		printf("\nReading the characteristic failed%d\r\n",status);
		return status;
	} else {
		//printf("\nReading the characteristic value is successful, read length = %d\r\n", actualLen);
	}
	/* Updating the att data base */
	if ((status = at_ble_characteristic_value_set(trans_service->serv_chars[2].char_val_handle, trans_ctrl_value, 0, len)) != AT_BLE_SUCCESS){
		DBG_LOG("updating the characteristic failed %d\r\n",status);
		return status;
	} else {
		//DBG_LOG("updating the characteristic value is successful\r\n");
	}

	if(trans_ctrl_notification_flag){
		/* sending notification to the peer about change */ 
		if((status = at_ble_notification_send(ble_connected_dev_info[0].handle, trans_service->serv_chars[2].char_val_handle)) != AT_BLE_SUCCESS) {
			DBG_LOG("sending notification failed %d",status);
			return status;
		}
		else {
			//DBG_LOG("sending transparent ctrl notification successful, credit = %d\r\n", trans_ctrl_value[4]);
			return status;
		}
	}

	return status;
}

