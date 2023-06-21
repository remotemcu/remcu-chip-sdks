/**
 * \file
 *
 * \brief Wi-Fi Provisioning API for Applications.
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

#ifndef WIFIPROV_API_H_
#define WIFIPROV_API_H_

#include "at_ble_api.h"

#define MAX_WIPROVTASK_AP_NUM         15
#define MAX_WIPROVTASK_SSID_LENGTH    32
#define MAX_WIPROVTASK_PASS_LENGTH    63

#define MAX_LOCALNAME_LENGTH 11

/*
 * msgs from APP to wifiprov
 *
 *
 */
/// Messages for WiFi Provisioning Profile
enum
{
	WIFIPROV_CONFIGURE_REQ = 0xDC00,
	WIFIPROV_CONFIGURE_CFM,
	/// Add WIFIPROV into the database
	WIFIPROV_CREATE_DB_REQ,
	/// Inform APP about DB creation status
	WIFIPROV_CREATE_DB_CFM,
	/// Start provisioning
	WIFIPROV_START_CMD,
	/// Disable provisioning (eg timeout, bonding fail or bad provisioning details)
	WIFIPROV_DISABLE_CMD,
	/// Provisioning complete (success or fail)
	WIFIPROV_COMPLETE_IND,
	/// Receiving scanlist from Wifi side
	WIFIPROV_SCANLIST_IND,
	/// Inform APP about_connection_state changes
	WIFIPROV_CONNECTION_STATE_CHANGE_IND,
	///  Inform App about Scan Mode changes
	WIFIPROV_SCAN_MODE_CHANGE_IND,
};

// When scan mode is used to send indication from App to the WiFi Prov profile,
// WIFIPROV_SCANMODE_SCANNING indicates Scanning is in progress
// WIFIPROV_SCANMODE_DONE indicates scanning is completed - note that this 
//	      				  indication should only be used when no scan results were obtained during the scan
// These result in the database being updated
// When scan mode is used to send indication from WiFi Prov profile to the App,
// WIFIPROV_SCANMODE_SCANNING request to start WiFi scanning and supply scan results
enum
{
	WIFIPROV_SCANMODE_SCANNING = 1,
	WIFIPROV_SCANMODE_DONE	// Scanning is indicated as 
};
typedef struct
{
    /// Scan Mode
    uint8_t scanmode;
}at_ble_wifiprov_scan_mode_change_ind_t;

//store the scan list and then later populate when creating the database
typedef struct _scanitem {
	uint8_t sec_type;
	uint8_t rssi;
	uint8_t ssid[MAX_WIPROVTASK_SSID_LENGTH];
} scanitem;

struct wifiprov_scanlist_ind
{
	uint8_t num_valid;
	scanitem scandetails[MAX_WIPROVTASK_AP_NUM];
};

at_ble_status_t wifiprov_scan_mode_change_ind_send(uint8_t scanmode);
at_ble_status_t wifiprov_scan_list_ind_send(struct wifiprov_scanlist_ind *param);

typedef struct 
{
	uint8_t status;
	uint8_t sec_type;
	uint8_t ssid_length;
	uint8_t ssid[MAX_WIPROVTASK_SSID_LENGTH];
	uint8_t passphrase_length;
	uint8_t passphrase[MAX_WIPROVTASK_PASS_LENGTH];
} at_ble_wifiprov_complete_ind;

void wifiprov_complete_ind_handler(uint8_t *data, at_ble_wifiprov_complete_ind *param);

enum
{
    WIFIPROV_CON_STATE_DISCONNECTED,
    WIFIPROV_CON_STATE_CONNECTING,
    WIFIPROV_CON_STATE_CONNECTED
};
at_ble_status_t wifiprov_wifi_con_update(uint8_t con_state);

//Localname must be a null terminated string
at_ble_status_t wifiprov_configure_provisioning(uint8_t* localname);
at_ble_status_t wifiprov_create_db(void);
at_ble_status_t wifiprov_start(uint8_t *pin, uint8_t len);
at_ble_status_t wifiprov_disable(void);

// Internal API
void wifiprov_scan_mode_change_ind_handler(uint8_t *data, at_ble_wifiprov_scan_mode_change_ind_t *param);
#endif // WIFIPROV_API_H_
