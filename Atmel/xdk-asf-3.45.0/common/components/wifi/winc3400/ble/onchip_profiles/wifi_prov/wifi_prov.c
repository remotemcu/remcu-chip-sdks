/**
 * \file
 *
 * \brief WiFi Provisioning Implementations
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
#include <asf.h>
#include "at_ble_api.h"
#include "wifi_prov.h"

#define CONF_BLE_PIN					{1,2,3,4,5,6}

static credentials provisioned_credentials;
static at_ble_wifiprov_complete_ind wifiprov_complete_ind = {.status = WIFI_PROV_IDLE};
static struct wifiprov_scanlist_ind ble_scan_list;
static uint8_t provision_state = 0;
static void init_credentials(void);
static void update_credentials(credentials new_creds);
	
static void init_credentials(void)
{
	M2M_INFO("Reset provision data\n");
	provisioned_credentials.sec_type = 0;
	provisioned_credentials.ssid_length = 0;
	m2m_memset(provisioned_credentials.ssid, 0, MAX_WIPROVTASK_SSID_LENGTH);
	provisioned_credentials.passphrase_length = 0;
	m2m_memset(provisioned_credentials.passphrase,0, MAX_WIPROVTASK_PASS_LENGTH);
}

static void update_credentials(credentials new_creds)
{
	M2M_INFO("Provisioned AP:\n");
	M2M_INFO("Sec type   : %d\n", new_creds.sec_type);
	M2M_INFO("SSID       : %s\n", new_creds.ssid);
	M2M_INFO("Passphrase : %s\n", new_creds.passphrase);

	provisioned_credentials.sec_type = new_creds.sec_type;
	provisioned_credentials.ssid_length = new_creds.ssid_length;
	m2m_memcpy(provisioned_credentials.ssid, new_creds.ssid, MAX_WIPROVTASK_SSID_LENGTH);
	provisioned_credentials.passphrase_length = new_creds.passphrase_length;
	m2m_memcpy(provisioned_credentials.passphrase,new_creds.passphrase, MAX_WIPROVTASK_PASS_LENGTH);
}

void ble_prov_process_event(at_ble_events_t event, void* params)
{
	switch (event)
	{
		case AT_BLE_WIFIPROV_SCAN_MODE_CHANGE_IND:
		{
			at_ble_wifiprov_scan_mode_change_ind_t *ind = (at_ble_wifiprov_scan_mode_change_ind_t *)params;
			#ifdef BLE_API_DBG
			M2M_INFO("AT_BLE_WIFIPROV_SCAN_MODE_CHANGE_IND :%x\n", ind->scanmode);
			#endif
			if (ind->scanmode == WIFIPROV_SCANMODE_SCANNING)
			{
				switch (ind->scanmode)
				{
					case WIFIPROV_SCANMODE_SCANNING:
					{
						m2m_memset((uint8 *)&ble_scan_list, 0, sizeof(ble_scan_list));
						m2m_wifi_request_scan(M2M_WIFI_CH_ALL);
						wifiprov_scan_mode_change_ind_send(WIFIPROV_SCANMODE_SCANNING);
						break;
					}
					default:
					break;
				}
			}
		}
		break;
		case AT_BLE_WIFIPROV_COMPLETE_IND:
		{
			m2m_memcpy((uint8 *)&wifiprov_complete_ind, params, sizeof(wifiprov_complete_ind));
			#ifdef BLE_API_DBG
			M2M_INFO("AT_BLE_WIFIPROV_COMPLETE_IND :%x\n", wifiprov_complete_ind.status);
			#endif
			if (wifiprov_complete_ind.status == WIFI_PROV_SUCCESS)
			{
				credentials temp_cred;
				temp_cred.sec_type = wifiprov_complete_ind.sec_type;
				temp_cred.passphrase_length = wifiprov_complete_ind.passphrase_length;
				m2m_memcpy(temp_cred.passphrase,wifiprov_complete_ind.passphrase,MAX_WIPROVTASK_PASS_LENGTH);
				temp_cred.ssid_length = wifiprov_complete_ind.ssid_length;
				m2m_memcpy(temp_cred.ssid,wifiprov_complete_ind.ssid,MAX_WIPROVTASK_SSID_LENGTH);
				update_credentials(temp_cred);
				// Return a successfully provisioned status
				provision_state = BLE_PROV_STATE_SUCCESS;
			}
			else
			{
				M2M_INFO("Provisioning Failed \n");
				wifiprov_complete_ind.status = WIFI_PROV_IDLE;
				provision_state = BLE_PROV_STATE_FAILED;
			}
			break;
		}
		default:
			break;
	}
}

uint8_t ble_prov_get_credentials(credentials *cred)
{
	uint8_t valid = CREDENTIALS_VALID;
	M2M_INFO("Retrieving ssid...\n");
	
	if (provisioned_credentials.ssid_length == 0)
	{
		M2M_INFO("   no valid ssid\n");
		valid = CREDENTIALS_NOT_VALID;
	}
	else
	{
		M2M_INFO("   have valid ssid\n");
		cred->sec_type = provisioned_credentials.sec_type;
		cred->ssid_length = provisioned_credentials.ssid_length;
		m2m_memcpy(cred->ssid,provisioned_credentials.ssid, MAX_WIPROVTASK_SSID_LENGTH);
		
		cred->passphrase_length = provisioned_credentials.passphrase_length;		
		if (cred->sec_type == M2M_WIFI_SEC_WEP)
		{
			// Convert WEP passphrase for m2m_wifi_connect friendly format.
			tstrM2mWifiWepParams *wepParams = (tstrM2mWifiWepParams *)cred->passphrase;
			m2m_memset((uint8 *)wepParams, 0, sizeof(tstrM2mWifiWepParams));
			wepParams->u8KeyIndx = M2M_WIFI_WEP_KEY_INDEX_1;
			wepParams->u8KeySz  = (m2m_strlen((uint8 *)provisioned_credentials.passphrase)==WEP_40_KEY_STRING_SIZE)?
			                              WEP_40_KEY_STRING_SIZE + 1:
										  WEP_104_KEY_STRING_SIZE + 1;
			m2m_memcpy((uint8*)(&wepParams->au8WepKey), provisioned_credentials.passphrase, wepParams->u8KeySz-1);
		}
		else
		{
			m2m_memcpy(cred->passphrase,provisioned_credentials.passphrase, MAX_WIPROVTASK_PASS_LENGTH);
		}
		valid = CREDENTIALS_VALID;
	}

	return valid;
}

uint8_t ble_prov_start(void)
{
	// Set bonding PIN and start provisioning
	uint8_t pin[6] = CONF_BLE_PIN;
	M2M_INFO("BLE provisioning started\r\n");
	if(AT_BLE_SUCCESS != wifiprov_start(pin, 6))
	{
		M2M_ERR("Failed to start BLE provisioning\n");
		provision_state = BLE_PROV_STATE_FAILED;
		return -1;
	}
	provision_state = BLE_PROV_STATE_IN_PROGRESS;
	return AT_BLE_SUCCESS;
}

void ble_prov_stop(void)
{
	if (wifiprov_complete_ind.status!=WIFI_PROV_IDLE)
	{
		wifiprov_disable();
		wifiprov_complete_ind.status = WIFI_PROV_IDLE;
		delay_ms(100); //wait for the ble prov to get stopped
	}
	provision_state = BLE_PROV_STATE_IDLE;	
}

void ble_prov_init(uint8_t* localname)
{
	provision_state = BLE_PROV_STATE_IDLE;
	init_credentials();
	
	// Setup the provisioning service
	if(AT_BLE_SUCCESS != wifiprov_configure_provisioning(localname))
	{
		M2M_ERR("Failed to configure BLE provisioning \n");
		return;
	}
	// Fill in the advertisement data
	if(AT_BLE_SUCCESS != wifiprov_create_db())
	{
		M2M_ERR("Failed to create BLE provisioning database \n");
		return;
	}
}

void ble_prov_scan_result(tstrM2mWifiscanResult* pstrScanResult, uint8_t resultsRemaining)
{
	if (ble_scan_list.num_valid < MAX_WIPROVTASK_AP_NUM && pstrScanResult->au8SSID[0])
	{
		uint8_t index = ble_scan_list.num_valid;
		ble_scan_list.scandetails[index].rssi = pstrScanResult->s8rssi;
		ble_scan_list.scandetails[index].sec_type = pstrScanResult->u8AuthType;
		m2m_memcpy(ble_scan_list.scandetails[index].ssid, pstrScanResult->au8SSID, sizeof(ble_scan_list.scandetails[index].ssid));
		ble_scan_list.num_valid++;
	}
	
	if (resultsRemaining==0)
	{
		wifiprov_scan_list_ind_send(&ble_scan_list);
	}
}

uint8_t ble_prov_get_provision_state(void)
{
	return	provision_state;
}