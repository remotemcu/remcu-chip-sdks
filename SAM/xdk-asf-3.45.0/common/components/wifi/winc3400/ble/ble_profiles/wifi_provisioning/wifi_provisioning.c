/**
 * \file
 *
 * \brief WiFi Provision Profile
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
*                                    Includes                                           *
****************************************************************************************/
#include <asf.h>
#include <string.h>
#include "at_ble_api.h"
#include "ble_manager.h"
#include "wifi_provisioning.h"
#include "ble_utils.h"
/****************************************************************************************
*                                     Globals                                           *
****************************************************************************************/
//#define PROVISION_PRINTF(...)			
//#define PROVISION_PRINTF_CONT(...)		
#define PROVISION_PRINTF(...)			do{printf("* "); printf(__VA_ARGS__);}while(0)
#define PROVISION_PRINTF_CONT(...)		do{printf(__VA_ARGS__);}while(0)
/** @brief APPARAM being 98 bytes long (will be received from the remote device in multiple messages) */
#define APPARAM_MULTIPART_LENGTH		(98)
/** @brief Position of various parameters within the 98 bytes */
#define APPARAM_MULTIPART_SECTYPE_POS	(0)  // 1 byte security type
#define APPARAM_MULTIPART_SSIDLEN_POS	(1)  // 1 byte ssid length
#define APPARAM_MULTIPART_SSID_POS		(2)  // ssid (max len 32) occupies bytes 2-33
#define APPARAM_MULTIPART_PASSLEN_POS	(34) // 1 byte passphrase length
#define APPARAM_MULTIPART_PASS_POS		(35) // passphrase (max len 63) occupies byte 35-97
#define NOTIFY_STATE_PROVISIONFAILED	(0)
#define NOTIFY_STATE_WIFICONNECTING		(1)
#define NOTIFY_STATE_PROVISIONEND		(2)
wificon_gatt_service_handler_t wificon_handle;
wifiscan_gatt_service_handler_t wifiscan_handle;
static uint8_t multi_part[APPARAM_MULTIPART_LENGTH];
/** @brief BLE connected or otherwise */
static uint8_t is_BLE_Connected;
/** @brief provisioning state */
static uint8_t wifi_provision_state;
/** @brief WiFi connection state that the app will inform on */
static uint8_t wifi_connection_state;
static uint8_t adv_scan_rsp_data[WIFI_PROVISION_ADV_SCAN_RESP_LEN];
/** @brief Callback handlers for connect and scan */
wifi_provision_scanning_callback_t scanning_cb;
wifi_provision_u8_callback_t provisioning_cb;
wifi_provision_cred_callback_t credentials_cb;
extern at_ble_connected_t ble_connected_dev_info[MAX_DEVICE_CONNECTED];
/****************************************************************************************
 *                                Static Functions                                      *
 ****************************************************************************************/
static at_ble_status_t start_advertise(void);
static void wifi_provision_service_init(void);
static at_ble_status_t prepare_advertisement(void);
static void wifi_provision_set_state(uint8_t s);
static at_ble_status_t wifi_provision_scanmode_update(uint8_t sm);
static uint8_t wifi_provision_get_state(void);
/**
* \brief start advertising wifi provision service
*/
static at_ble_status_t start_advertise(void)
{
	at_ble_status_t st = AT_BLE_SUCCESS;
    at_ble_set_dev_config(AT_BLE_GAP_PERIPHERAL_SLV);
	if(at_ble_adv_start(AT_BLE_ADV_TYPE_UNDIRECTED, AT_BLE_ADV_GEN_DISCOVERABLE, NULL, AT_BLE_ADV_FP_ANY,
	WIFI_PROVISION_FAST_ADV, WIFI_PROVISION_ADV_TIMEOUT, 0) == AT_BLE_SUCCESS)
	{
		PROVISION_PRINTF("BLE device is in Advertising Mode\n");
		PROVISION_PRINTF("Advertising Device Name: %s\n",WIFI_PROVISION_ADV_DATA_NAME_DATA);
	}
	else
	{
		PROVISION_PRINTF("BLE Adv start Failed\n");
		st = AT_BLE_FAILURE;
	}
	return st;
}
/**
 * \brief Initializations of profile services
*/
static void wifi_provision_service_init(void)
{
	init_wifi_con_service(&wificon_handle);	
	init_wifi_scan_service(&wifiscan_handle);
}
/**
* \brief prepare advertisement data
*/
static at_ble_status_t prepare_advertisement(void)
{
	at_ble_status_t st;
	uint8_t srp_idx;
	uint8_t adv_data[1]; // advertising data,length one
	//appending advertise data
	adv_data[0] = 0; //type = 0
	//appending wificon service UUID to scan response
	srp_idx = 0;
	adv_scan_rsp_data[srp_idx++] = 1 + WIFICON_UUID_128_LEN;
	adv_scan_rsp_data[srp_idx++] = WIFI_PROVISION_SCP_TYPE_MORE_128_BIT_UUID;
	memcpy(&adv_scan_rsp_data[srp_idx], WIFI_CON_SERVICE_UUID, WIFICON_UUID_128_LEN);
	srp_idx += WIFICON_UUID_128_LEN;
	//appending advertising data name to scan response
	adv_scan_rsp_data[srp_idx++] = 1 + strlen(WIFI_PROVISION_ADV_DATA_NAME_DATA);
	adv_scan_rsp_data[srp_idx++] = WIFI_PROVISION_ADV_DATA_NAME_TYPE;
	memcpy(&adv_scan_rsp_data[srp_idx], WIFI_PROVISION_ADV_DATA_NAME_DATA, strlen(WIFI_PROVISION_ADV_DATA_NAME_DATA));
	srp_idx += WIFI_PROVISION_ADV_DATA_NAME_LEN;
	if (srp_idx > WIFI_PROVISION_ADV_SCAN_RESP_LEN)
	{
		PROVISION_PRINTF("Error: advertisement data length overflow.\n");
		st = AT_BLE_FAILURE;
	}
	else
	{
		//setting the advertisement data and scan response data
		st = at_ble_adv_data_set(adv_data,1,adv_scan_rsp_data,srp_idx);		
		if(st != AT_BLE_SUCCESS)
		{
			PROVISION_PRINTF("Failed to set advertisement data.\n");
		}
	}
	return st;
}
/**
* \brief set the wifi provision state
*/
static void wifi_provision_set_state(uint8_t s)
{
	if (wifi_provision_state!=s)
	{
		wifi_provision_state = s;
		switch(s)
		{
			case WIFI_PROVISION_STATE_IDLE :
				PROVISION_PRINTF("Provision state_IDLE\n");
			break;
			case WIFI_PROVISION_STATE_REQUESTING_SCAN :
				PROVISION_PRINTF("Provision state_REQUESTING_SCAN.\n");
			break;
			case WIFI_PROVISION_STATE_WIFI_SCANNING :
				PROVISION_PRINTF("Provision state_WIFI_SCANNING.\n");
			break;
			case WIFI_PROVISION_STATE_IN_PROGRESS :
				PROVISION_PRINTF("Provision state_IN_PROGRESS.\n");
			break;
			case WIFI_PROVISION_STATE_HAVE_CREDENTIAL :
				PROVISION_PRINTF("Provision state_HAVE_CREDENTIAL.\n\n");
			break;
			case WIFI_PROVISION_STATE_FAILED :
				PROVISION_PRINTF_CONT("\n");
				PROVISION_PRINTF("Provision state_FAILED.\n");
			break;
		}
	}
}
/**
* \brief updating scan mode
*/
static at_ble_status_t wifi_provision_scanmode_update(uint8_t sm)
{
	at_ble_status_t st=wifiscan_update_scanmode_char_value(&wifiscan_handle,sm);
	return st;
}
/**
* \brief return provision state 
*/
static uint8_t wifi_provision_get_state(void)
{
	return	wifi_provision_state;
}
/****************************************************************************************
 *                                  Implementation                                      *
 ****************************************************************************************/
/**
* \brief application periodically kicks wifi provision processing
*/
uint8_t wifi_provision_processing(void)
{
	//Here is the place to put any WiFi Provision state checks and transitions needed
	
	//(1) Check if we are in a scan requesting state, if so get WiFi scanning going
	if (wifi_provision_get_state() == WIFI_PROVISION_STATE_REQUESTING_SCAN)
	{
		if (scanning_cb() == AT_BLE_SUCCESS)
		{
			wifi_provision_set_state(WIFI_PROVISION_STATE_WIFI_SCANNING);
			//if WiFi Scanning is started okay set the scan mode
			//characteristics to indicate scanning (if not already)
			wifi_provision_scanmode_update(WIFI_PROVISION_SCANMODE_SCANNING);
		}
		// if failed stay in requesting scan state		
	}
	// (x) Any other checks ? ...
	
	//In exit, return the WiFi Provision state to the application so it can
	//take any actions
	return (wifi_provision_get_state());
}

/**
 * \brief application to register the credential update function callback
*/
void register_wifi_provision_credentials_handler(wifi_provision_cred_callback_t credentials_fn)
{
	credentials_cb = credentials_fn;
}
/**
 * \brief application to register the scanning function callback
*/
void register_wifi_provision_scanning_handler(wifi_provision_scanning_callback_t scanning_fn)
{
	scanning_cb = scanning_fn;
}
/**
* \brief definition of WiFi Provision profile services
*/
at_ble_status_t wifi_provision_define (void)
{	
	at_ble_status_t service_define_status = wificon_primary_service_define(&wificon_handle);
	if (service_define_status == AT_BLE_SUCCESS)
	{
		service_define_status = wifiscan_primary_service_define(&wifiscan_handle);
	}
	if (service_define_status == AT_BLE_SUCCESS)
	{		
		printf("\n* This is WiFi Provisioning.\n");
	}
	else
	{
		printf("\n* WiFi Provisioning: Failed services setup!\n");
	}	
	return service_define_status;
}
/**
* \brief ble stack indicate service client configuration change
*/
uint8_t wifi_provision_svc_changed_handler(uint8_t *data)
{
	at_ble_status_t s = AT_BLE_SUCCESS;
	at_ble_handle_t h;
	//PROVISION_PRINTF("Serviced Change. Data:[0x%02x][0x%02x]\n",data[0], data[1]);
	// service change handle is one before the wificon service
	h = wificon_handle.serv_handle - 1;
	if (h > 0)
	{
		s = at_ble_characteristic_value_set(h, (uint8_t *) data, 0 , 2);
	}
	return s;
}
/**
* \brief service characteristic change handler function 
*/
uint8_t wifi_provision_char_changed_handler(at_ble_characteristic_changed_t *char_handle)
{
	uint8_t change_status;
		
	at_ble_characteristic_changed_t  p;
	memcpy(&p, char_handle, sizeof(at_ble_characteristic_changed_t));
	PROVISION_PRINTF("wifi_provisioning_characteristics_changed: ");
//	PROVISION_PRINTF_CONT("param->handle: %02x ", param.char_handle);
//	PROVISION_PRINTF_CONT("param->length: %02x ", param.char_len);
//	PROVISION_PRINTF_CONT("param->offset: %02x ", param.char_offset);
//	PROVISION_PRINTF_CONT("param->value : %u %u %u\n",param.char_new_value[0],param.char_new_value[1],param.char_new_value[2]);	

	/**************************************************************************
	*                A characteristic has changed...                          *
	*                Look for it in wificon service.                          *
	*                                                                         *
	**************************************************************************/
	
	// Check if char change is aimed at state client configuration
	change_status = wificon_char_change_state_client_cfg(&p,&wificon_handle);
	if (change_status == VALID_WIFICON_CHANGE_PARAM)
	{
		PROVISION_PRINTF_CONT("state characteristics: client_config is successful.\n");
	}
	else if (change_status == FAILED_WIFICON_CHANGE_PARAM)
	{
		PROVISION_PRINTF_CONT("state characteristics: client_config tried but failed.\n");
	}
		
	// Check if char change is aimed at apparam
	if (change_status == INVALID_WIFICON_CHANGE_PARAM)
	{
		change_status = wificon_char_change_apparam(&p,&wificon_handle);
		if (change_status == VALID_WIFICON_CHANGE_PARAM)
		{
			PROVISION_PRINTF("multi-part apparam: off:%u successful update.\n",p.char_offset);
	//		PROVISION_PRINTF_CONT("param->handle: %u ", p.char_handle);
	//		PROVISION_PRINTF_CONT("length: %u ", p.char_len);
	//		PROVISION_PRINTF_CONT("offset: %u ", p.char_offset);
	//		PROVISION_PRINTF_CONT(" first 3 values : [x%02x][x%02x][x%02x]\n",p.char_new_value[0],p.char_new_value[1],p.char_new_value[2]);
			if (p.char_offset == 0)
				memset(multi_part,0,APPARAM_MULTIPART_LENGTH);
			memcpy(&multi_part[p.char_offset],p.char_new_value,p.char_len);
			if (p.char_offset + p.char_len >= APPARAM_MULTIPART_LENGTH)
			{
				credentials cred;
				cred.sec_type = multi_part[APPARAM_MULTIPART_SECTYPE_POS];
				cred.ssid_length = (multi_part[APPARAM_MULTIPART_SSIDLEN_POS]> WIFI_PROVISION_MAX_SSID_LENGTH ? WIFI_PROVISION_MAX_SSID_LENGTH: multi_part[APPARAM_MULTIPART_SSIDLEN_POS]);
				memcpy(&cred.ssid, &multi_part[APPARAM_MULTIPART_SSID_POS], cred.ssid_length);
				cred.passphrase_length = (multi_part[APPARAM_MULTIPART_PASSLEN_POS]> WIFI_PROVISION_MAX_PASS_LENGTH ? WIFI_PROVISION_MAX_PASS_LENGTH: multi_part[APPARAM_MULTIPART_PASSLEN_POS]);
				memcpy(&cred.passphrase,  &multi_part[APPARAM_MULTIPART_PASS_POS], cred.passphrase_length);
				//PROVISION_PRINTF("\nReceive complete.\n");
				//PROVISION_PRINTF("\nSSID: %s\n",cred.ssid);
				//PROVISION_PRINTF("PASS: %s\n",cred.passphrase);
				//PROVISION_PRINTF("SECU: %u\n",cred.sec_type);
				if (AT_BLE_SUCCESS==credentials_cb(&cred))
					wifi_provision_set_state(WIFI_PROVISION_STATE_HAVE_CREDENTIAL);
				else
					wifi_provision_set_state(WIFI_PROVISION_STATE_FAILED);
			}
		}
		else if (change_status == FAILED_WIFICON_CHANGE_PARAM)
		{
			PROVISION_PRINTF("multi-part apparam: update tried but failed.\n");
		}
	}

	if (change_status == INVALID_WIFICON_CHANGE_PARAM)
	{
		
	/**************************************************************************
	*                A characteristic has changed...                          *
	*                Look for it in wifiscan service.                         *
	*                                                                         *
	**************************************************************************/
		//check if it is scanmode characteristics being changed
		change_status = wifiscan_char_change_scanmode(&p,&wifiscan_handle);
		if (change_status == VALID_WIFISCAN_CHANGE_PARAM)
		{
			PROVISION_PRINTF("scan mode characteristics: update is successful.\n");
			if (p.char_len == 1)
			{
				//if remote device changed scan mode to scanning
				//callback to application to request wifi scanning
				if (p.char_new_value[0] = WIFI_PROVISION_SCANMODE_SCANNING)
				{
					// Callback to application to request WiFi scanning
					wifi_provision_set_state(WIFI_PROVISION_STATE_REQUESTING_SCAN);
				}
			}
		}
		else if (change_status == FAILED_WIFISCAN_CHANGE_PARAM)
		{
			PROVISION_PRINTF("scan mode characteristics: update tried but failed.\n");
		}
	}
		
	return change_status;
}
/**
* \brief application requests wifi scanning
*/
void request_scan(void)
{
	wifi_provision_set_state(WIFI_PROVISION_STATE_REQUESTING_SCAN);
}
/**
* \brief start or restart provision and advertise and get scan list
*/
at_ble_status_t provision_start(void)
{
	at_ble_status_t st=AT_BLE_SUCCESS;
	wifi_connection_state = WIFI_CONNECTION_STATE_NOTSTARTED;
	if (BLE_IS_NOT_CONNECTED==ble_is_connected())
	{
		st=prepare_advertisement();
		if (st== AT_BLE_SUCCESS)
			st=start_advertise();
	}
	if (st== AT_BLE_SUCCESS)
		wifi_provision_set_state(WIFI_PROVISION_STATE_REQUESTING_SCAN);
	else
		wifi_provision_set_state(WIFI_PROVISION_STATE_IDLE);
	return st;
}
/**
* \brief application updates wifi provisioning on wifi connect state
*/
void inform_wifi_connection_state(uint8_t s)
{
	wifi_connection_state = s;
	switch(wifi_connection_state)
	{
		case WIFI_CONNECTION_STATE_PROVISIONED :
			wificon_connect_noti(&wificon_handle,NOTIFY_STATE_PROVISIONEND);
			PROVISION_PRINTF("WiFi state_SUCCESS.\n");
			wifi_provision_set_state(WIFI_PROVISION_STATE_IDLE);
		break;
		case WIFI_CONNECTION_STATE_PROVISIONFAILED :
			wificon_connect_noti(&wificon_handle,NOTIFY_STATE_PROVISIONFAILED);
			PROVISION_PRINTF("WiFi state_FAILED.\n");
			wifi_provision_set_state(WIFI_PROVISION_STATE_FAILED);
		break;
		case WIFI_CONNECTION_STATE_CONNECTING :
			wificon_connect_noti(&wificon_handle,NOTIFY_STATE_WIFICONNECTING);
			PROVISION_PRINTF("WiFi state_CONNECTING.\n");
		break;
	}
}
/**
* \brief application updates the wifi scan list 
*/
uint8_t wifi_provision_scanlist_receive(struct wifi_provision_scanlist *param)
{
	at_ble_status_t status;
	uint8_t num_ap_found;
	status = wifiscan_scanlist_receive(&wifiscan_handle, param, &num_ap_found);
	if (AT_BLE_SUCCESS == status)
	{
		status = wifi_provision_scanmode_update(WIFI_PROVISION_SCANMODE_DONE);
		PROVISION_PRINTF("Number of APs found: %u\n", num_ap_found);
	}
	
	if (status == AT_BLE_SUCCESS)
	{
		wifi_provision_set_state(WIFI_PROVISION_STATE_IN_PROGRESS);
	}
	else
	{
		wifi_provision_set_state(WIFI_PROVISION_STATE_REQUESTING_SCAN);
	}
	return status;
}
/**
* \brief function for querying ble connect status
*/
uint8_t ble_is_connected(void)
{
	return(is_BLE_Connected);

}
/**
* \brief initialise wifi provision profile, includes all initialisation and start up
*/
void wifi_provision_init(void *param)
{
	is_BLE_Connected=BLE_IS_NOT_CONNECTED;
	wifi_provision_service_init();
	wifi_provision_define();
	wifi_provision_set_state(WIFI_PROVISION_STATE_IDLE);
}
/**
* \ application updates ble has connected
*/
void ble_connected(void)
{
	PROVISION_PRINTF("BLE Connected.\n");
	is_BLE_Connected=BLE_IS_CONNECTED;
}
/**
* \ application updates ble has disconnected
*/
void ble_disconnected(void)
{
	PROVISION_PRINTF("BLE Disconnected.\n");
	if ((wifi_provision_get_state() == WIFI_PROVISION_STATE_IDLE) && (wifi_connection_state != WIFI_CONNECTION_STATE_PROVISIONFAILED))
	{
		PROVISION_PRINTF("Provisioning Complete.\n");
	}
	else
	{
		wifi_provision_set_state(WIFI_PROVISION_STATE_FAILED);
	}
	is_BLE_Connected=BLE_IS_NOT_CONNECTED;
}
/**
* \ brief application requests ble be disconnected
*/
void disconnect_ble(void)
{
	at_ble_disconnect(ble_connected_dev_info[0].handle,AT_BLE_TERMINATED_BY_USER);
	at_ble_adv_stop();
}
