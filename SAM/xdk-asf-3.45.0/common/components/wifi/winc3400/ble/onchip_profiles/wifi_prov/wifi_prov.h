/**
 * \file
 *
 * \brief WiFi Provisioning Declarations
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

#ifndef __WIFIPROV_PROFI_H__
#define __WIFIPROV_PROFI_H__

#include <asf.h>
#include "wifiprov_api.h"
#include "driver/include/m2m_wifi.h"

#define	CREDENTIALS_NOT_VALID			0
#define CREDENTIALS_VALID				1

// states of WiFi provision state machine here
#define WIFI_PROV_IDLE					0xFF
#define WIFI_PROV_SUCCESS				0x00	// Should be same as what is in at_ble_wifiprov_complete_ind

//status to be returned to application
#define PROVISION_NULL					0x00
#define PROVISION_SUCCESS				0x10
#define PROVISION_FAILED				0x20

#define BLE_PROV_STATE_IDLE				0x00
#define BLE_PROV_STATE_IN_PROGRESS		0x01
#define BLE_PROV_STATE_SUCCESS			0x04
#define BLE_PROV_STATE_FAILED			0x80

typedef struct
{
	uint8_t sec_type;
	uint8_t ssid_length;
	uint8_t ssid[MAX_WIPROVTASK_SSID_LENGTH];
	uint8_t passphrase_length;
	uint8_t passphrase[MAX_WIPROVTASK_PASS_LENGTH];
} credentials;

//void ble_prov_process_event();
uint8_t ble_prov_start(void);
void ble_prov_stop(void);
uint8_t ble_prov_get_credentials(credentials *cred);
//Allows setting of localname in scan response
//Maximum length is 11 characters
void ble_prov_init(uint8_t* localname);
void ble_prov_scan_result(tstrM2mWifiscanResult* pstrScanResult, uint8_t resultsRemaining);
uint8_t ble_prov_get_provision_state(void);
#define ble_prov_wifi_con_update		wifiprov_wifi_con_update
void ble_prov_process_event(at_ble_events_t event, void* params);

#endif /* __WIFIPROV_PROFI_H__ */