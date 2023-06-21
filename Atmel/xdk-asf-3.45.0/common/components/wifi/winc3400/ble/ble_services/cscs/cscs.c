/**
 * \file
 *
 * \brief Custom Serial Chat Service
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
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Atmel
 *Support</a>
 */

/**
 * \mainpage
 * \section preface Preface
 * This is the reference manual for the Custom Serial Chat Service
 */
/*- Includes ---------------------------------------------------------------*/
#include "stddef.h"
#include "stdio.h"
#include "string.h"
#include "at_ble_api.h"
#include "ble_manager.h"
#include "cscs.h"

csc_serv_t csc_inst;

/**
* \CSC service Configuration function
*/
at_ble_status_t csc_serv_init(uint8_t *buf, uint16_t len)
{
	/* Configure SPOG Service UUID info*/
	csc_inst.serv_uuid.type =	 AT_BLE_UUID_128;
	memcpy(&csc_inst.serv_uuid.uuid[0], CSC_SERVICE_UUID, CSC_UUID_128_LEN);
	
	/* Configure SPOG Service Handle*/
	csc_inst.serv_handle = 0;
	
	/*Configure SPOG Endpoint Characteristic*/
	csc_inst.endpoint_chars.uuid.type = AT_BLE_UUID_128;
	memcpy(&csc_inst.endpoint_chars.uuid.uuid[0], CSC_ENDPOINT_CHAR_UUID, CSC_UUID_128_LEN);
	csc_inst.endpoint_chars.properties = AT_BLE_CHAR_NOTIFY;	
	csc_inst.endpoint_chars.init_value = buf;
	csc_inst.endpoint_chars.value_init_len = len;
	csc_inst.endpoint_chars.value_max_len = len;
	/* Configure the CSC characteristic permission */
	csc_inst.endpoint_chars.value_permissions = (AT_BLE_ATTR_READABLE_REQ_AUTHN_NO_AUTHR | AT_BLE_ATTR_WRITABLE_REQ_AUTHN_NO_AUTHR);
	return(at_ble_primary_service_define(&csc_inst.serv_uuid, &csc_inst.serv_handle, NULL, 0, &csc_inst.endpoint_chars, 1));
}

/**
* \CSC service send data function
*/
at_ble_status_t csc_serv_send_data(uint16_t connhandle, uint8_t *databuf, uint16_t datalen)
{
	at_ble_status_t status;
	uint8_t value = 0;
	uint16_t length;
	length = sizeof(uint16_t);
	status = at_ble_characteristic_value_get(csc_inst.endpoint_chars.client_config_handle, &value, 0, length, sizeof(int8_t));
	if (status != AT_BLE_SUCCESS){
		DBG_LOG("at_ble_characteristic_value_get value get failed");
		return status;
	}
	if(value == 1){
		status = at_ble_characteristic_value_set(csc_inst.endpoint_chars.char_val_handle, databuf, 0, datalen);
		if (status != AT_BLE_SUCCESS){
			DBG_LOG("at_ble_characteristic_value_set value set failed");
			return status;
		}
		status = at_ble_notification_send(connhandle, csc_inst.endpoint_chars.char_val_handle);
		if (status != AT_BLE_SUCCESS){
			DBG_LOG("at_ble_notification_send  failed");
			return status;
		}
	}
	return status;
}
