/**
 * \file
 *
 * \brief Proximity Reporter Profile
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

/****************************************************************************************
*							        Includes	                                     	*
****************************************************************************************/
#include <asf.h>
#include <string.h>
#include "at_ble_api.h"
#include "ble_manager.h"
#include "pxp_reporter.h"
#include "immediate_alert.h"
#include "link_loss.h"
#include "tx_power.h"
#include "ble_utils.h"

/****************************************************************************************
*							        Globals	                                     		*
****************************************************************************************/

gatt_service_handler_t lls_handle;

#ifdef TX_POWER_SERVICE
gatt_service_handler_t txps_handle;
#endif

#ifdef IMMEDIATE_ALERT_SERVICE
gatt_service_handler_t ias_handle;
#endif

/** @brief led_state  the state of the led*/
//extern uint8_t pxp_led_state;

/** @brief Scan response data*/
uint8_t scan_rsp_data[SCAN_RESP_LEN] = {0x09, 0xff, 0x00, 0x06, 0xd6, 0xb2, 0xf0, 0x05, 0xf0, 0xf8};


/** @brief Alert value used for immediate alert service helps in pathloss */
uint8_t pathloss_alert_value = INVALID_IAS_PARAM ;

/** @brief Alert value used for Linkloss service*/
uint8_t linkloss_current_alert_level ;

/** @brief Callback handlers for linkloss and pathloss */
reporter_callback_t pathloss_cb;
reporter_callback_t linkloss_cb;
reporter_callback_t conn_update_cb;

/****************************************************************************************
*							        Implementation	                                     							*
****************************************************************************************/

/**
 * \brief Initializations of profile services based on pathloss option
*/
void pxp_service_init(void)
{
	/** Initializing the mandatory linkloss service of proximity reporter*/
	init_linkloss_service(&lls_handle);

	/** Initializing the optional services for pathloss feature of proximity reporter*/	
	#ifdef IMMEDIATE_ALERT_SERVICE
	init_immediate_alert_service(&ias_handle);
	#endif

	#ifdef TX_POWER_SERVICE
	init_tx_power_service(&txps_handle);
	#endif
}

/**
 * \brief registering the path loss handler of the application
*/
void register_pathloss_handler(reporter_callback_t pathloss_fn)
{
	pathloss_cb = pathloss_fn;
}

/**
 * \brief registering the linkloss handler of the appliation
*/
void register_linkloss_handler(reporter_callback_t linkloss_fn)
{
	linkloss_cb = linkloss_fn;
}

void register_conn_update_handler(reporter_callback_t conn_update_fn)
{
	conn_update_cb = conn_update_fn;
}
/**
* \Definition of profile services to the attribute data base based on pathloss
*/
at_ble_status_t pxp_service_define (void)
{
	DBG_LOG("This is Proximity Reporter");
	DBG_LOG("Proximity Reporter provides these services:");
	DBG_LOG("  -> Link Loss Service");	
	lls_primary_service_define(&lls_handle);
	
	#ifdef IMMEDIATE_ALERT_SERVICE
	ias_primary_service_define(&ias_handle);
	DBG_LOG("  -> Immediate Alert Service");
	#endif

	#ifdef TX_POWER_SERVICE
	txps_primary_service_define(&txps_handle);
	DBG_LOG("  -> Tx Power Service");
	#endif

	return AT_BLE_SUCCESS;
}

/**
* \Service Characteristic change handler function 
*/
at_ble_status_t pxp_reporter_char_changed_handler(at_ble_characteristic_changed_t *char_handle)
{
	int temp_val;
	at_ble_characteristic_changed_t change_params;
	memcpy((uint8_t *)&change_params, char_handle, sizeof(at_ble_characteristic_changed_t));

	
	temp_val = lls_set_alert_value(&change_params,&lls_handle);
	
	if (temp_val != INVALID_LLS_PARAM)
	{
		linkloss_current_alert_level = temp_val;
	}

#ifdef IMMEDIATE_ALERT_SERVICE
	pathloss_alert_value		 = ias_set_alert_value(&change_params,&ias_handle);
	if (pathloss_alert_value != INVALID_IAS_PARAM)
	{
		pathloss_cb(pathloss_alert_value);		
	}
#endif
	
	return AT_BLE_SUCCESS;
}

/**
* \Pxp reporter connected state handler function called after
*/
at_ble_status_t pxp_reporter_connected_state_handler(at_ble_connected_t *conn_params)
{

	at_ble_status_t status;

	conn_update_cb(conn_params->conn_status);
	
	if ((status = at_ble_characteristic_value_get(lls_handle.serv_chars->char_val_handle,&linkloss_current_alert_level,0,sizeof(int8_t),sizeof(int8_t))))
	{
		DBG_LOG("Read of alert value for link loss service failed:reason %x",status);
	}

#ifdef IMMEDIATE_ALERT_SERVICE	
	if ((status = at_ble_characteristic_value_get(ias_handle.serv_chars->char_val_handle,&pathloss_alert_value,0,sizeof(int8_t),sizeof(int8_t))))
	{
		DBG_LOG("Read of alert value for Immediate alert service failed:reason %x",status);
	}
#endif
	
	return AT_BLE_SUCCESS;
}

/**
* \Pxp reporter disconnected state handler function called after
*/
at_ble_status_t pxp_disconnect_event_handler(at_ble_disconnected_t *disconnect)
{
	linkloss_cb(linkloss_current_alert_level);
	
	at_ble_set_dev_config(AT_BLE_GAP_PERIPHERAL_SLV);
	
	if(at_ble_adv_start(AT_BLE_ADV_TYPE_UNDIRECTED, AT_BLE_ADV_GEN_DISCOVERABLE, NULL, AT_BLE_ADV_FP_ANY,
	APP_PXP_FAST_ADV, APP_PXP_ADV_TIMEOUT, 0) != AT_BLE_SUCCESS)
	{
		#ifdef DBG_LOG
		DBG_LOG("BLE Adv start Failed");
		#endif
	}
	else
	{
		DBG_LOG("BLE Device is in Advertising Mode");
	}
	return AT_BLE_SUCCESS;
}

/**
* \Pxp reporter advertisement initialization and adv start 
*/
void pxp_reporter_adv(void)
{
	uint8_t idx = 0;
	uint8_t adv_data [ PXP_ADV_DATA_NAME_LEN + LL_ADV_DATA_UUID_LEN   + (2*2)];
	
	adv_data[idx++] = LL_ADV_DATA_UUID_LEN + ADV_TYPE_LEN +  TXP_ADV_DATA_UUID_LEN + IAL_ADV_DATA_UUID_LEN ;
	adv_data[idx++] = LL_ADV_DATA_UUID_TYPE;

	/* Appending the UUID */
	adv_data[idx++] = (uint8_t)LINK_LOSS_SERVICE_UUID;
	adv_data[idx++] = (uint8_t)(LINK_LOSS_SERVICE_UUID >> 8);

	//Prepare ADV Data for TXP Service
	adv_data[idx++] = (uint8_t)TX_POWER_SERVICE_UUID;
	adv_data[idx++] = (uint8_t)(TX_POWER_SERVICE_UUID >> 8);

	//Prepare ADV Data for IAS Service
	adv_data[idx++] = (uint8_t)IMMEDIATE_ALERT_SERVICE_UUID;
	adv_data[idx++] = (uint8_t)(IMMEDIATE_ALERT_SERVICE_UUID >> 8);
	
	//Appending the complete name to the Ad packet
	adv_data[idx++] = PXP_ADV_DATA_NAME_LEN + ADV_TYPE_LEN;
	adv_data[idx++] = PXP_ADV_DATA_NAME_TYPE;
	
	memcpy(&adv_data[idx], PXP_ADV_DATA_NAME_DATA, PXP_ADV_DATA_NAME_LEN );
	idx += PXP_ADV_DATA_NAME_LEN ;
	
	/* Adding the advertisement data and scan response data */
	if(!(at_ble_adv_data_set(adv_data, idx, scan_rsp_data, SCAN_RESP_LEN) == AT_BLE_SUCCESS) )
	{
		#ifdef DBG_LOG
		DBG_LOG("Failed to set adv data");
		#endif
	}
	
	at_ble_set_dev_config(AT_BLE_GAP_PERIPHERAL_SLV);
	
	/* Start of advertisement */
	if(at_ble_adv_start(AT_BLE_ADV_TYPE_UNDIRECTED, AT_BLE_ADV_GEN_DISCOVERABLE, NULL, AT_BLE_ADV_FP_ANY, APP_PXP_FAST_ADV, APP_PXP_ADV_TIMEOUT, 0) == AT_BLE_SUCCESS)
	{
		#ifdef DBG_LOG
		DBG_LOG("BLE device is in Advertising Mode");
		DBG_LOG("Advertising Device Name: %s",PXP_ADV_DATA_NAME_DATA);
		#endif
	}	
	else
	{
		#ifdef DBG_LOG
		DBG_LOG("BLE Adv start Failed");
		#endif
	}
}

/**
* \Pxp reporter Initialization which initializes service,defines and start adv
*/
void pxp_reporter_init(void *param)
{
	/* pxp services initialization*/
	pxp_service_init();
	
	/* pxp services definition    */
	pxp_service_define();
	
	/* pxp services advertisement */
	pxp_reporter_adv();
}
