/**
* \file
*
* \brief WiFi Provisioning Profile declarations
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
#ifndef __WIFI_PROVISIONING_H__
#define __WIFI_PROVISIONING_H__
/****************************************************************************************
*                                     Includes                                          *
****************************************************************************************/
#include "ble_manager.h"
#include "driver/include/m2m_wifi.h"
#include "wifi_con.h"
#include "wifi_scan.h"
/****************************************************************************************
*                                       Macros                                         *
****************************************************************************************/
/** @brief provisioning state that the app can query */
#define WIFI_PROVISION_STATE_IDLE						(0x00)
#define WIFI_PROVISION_STATE_REQUESTING_SCAN			(0x01)
#define WIFI_PROVISION_STATE_WIFI_SCANNING				(0x02)
#define WIFI_PROVISION_STATE_IN_PROGRESS				(0x04)
#define WIFI_PROVISION_STATE_HAVE_CREDENTIAL			(0x08)
#define WIFI_PROVISION_STATE_FAILED						(0x10)
/** @brief BLE connected or otherwise */
#define BLE_IS_NOT_CONNECTED							(0)
#define BLE_IS_CONNECTED								(1)
/** @brief Scan response type Incomplete List of 128-bit Service Class UUIDs */
#define WIFI_PROVISION_SCP_TYPE_MORE_128_BIT_UUID		(0x06)
/** @brief WIFI_PROVISION_ADV_DATA_NAME_TYPE the gap ad data type */
#define WIFI_PROVISION_ADV_DATA_NAME_TYPE				(0x09)
/** @brief WIFI_PROVISION_ADV_DATA_NAME_LEN the  length of the device name */
#define WIFI_PROVISION_ADV_DATA_NAME_LEN				(11)
/* @brief WIFI_PROVISION_ADV_DATA_NAME_DATA the actual name of device */
#define WIFI_PROVISION_ADV_DATA_NAME_DATA				("3400-DEMO")
/** @brief advertisement or scan response length. */
#define WIFI_PROVISION_ADV_SCAN_RESP_LEN				(31)
/** @brief WIFI_PROVISION_FAST_ADV between 0x0020 and 0x4000 in 0.625 ms units (20ms to 10.24s). */
#define WIFI_PROVISION_FAST_ADV							(100) //100 ms
#define WIFI_PROVISION_ADV_TIMEOUT						(1000) // 100 Secs
/** @brief credentials provisioning status */
#define	CREDENTIALS_NOT_VALID							(0)
#define CREDENTIALS_VALID								(1)
/** @brief maximum number of APs in scan list given to remote device */
#define WIFI_PROVISION_MAX_AP_NUM						(15)
/** @brief maximum ssid length */
#define WIFI_PROVISION_MAX_SSID_LENGTH					(32)
/** @brief maximum pass phrase length */
#define WIFI_PROVISION_MAX_PASS_LENGTH					(63)
typedef struct _scanitem {
	uint8_t sec_type;
	uint8_t rssi;
	uint8_t ssid[WIFI_PROVISION_MAX_SSID_LENGTH];
} scanitem;
struct wifi_provision_scanlist
{
	uint8_t num_valid;
	scanitem scandetails[WIFI_PROVISION_MAX_AP_NUM];
};
typedef struct
{
	uint8_t sec_type;
	uint8_t ssid_length;
	uint8_t ssid[WIFI_PROVISION_MAX_SSID_LENGTH];
	uint8_t passphrase_length;
	uint8_t passphrase[WIFI_PROVISION_MAX_PASS_LENGTH];
} credentials;
typedef at_ble_status_t (*wifi_provision_scanning_callback_t)(void);
typedef void (*wifi_provision_u8_callback_t)(uint8_t);
typedef at_ble_status_t (*wifi_provision_cred_callback_t)(credentials *);

/** @brief scanning status: can be scanning or scan done when the AP list is refreshed */
enum
{
	WIFI_PROVISION_SCANMODE_SCANNING = 1,
	WIFI_PROVISION_SCANMODE_DONE,
};
/** @brief WiFi status;application can inform on this */
enum
{
	WIFI_CONNECTION_STATE_NOTSTARTED,
	WIFI_CONNECTION_STATE_PROVISIONFAILED,
	WIFI_CONNECTION_STATE_CONNECTING,
	WIFI_CONNECTION_STATE_PROVISIONED,
};
/****************************************************************************************
*							        Function Prototypes	                                     							*
****************************************************************************************/
/** @brief Initialize the profile, includes all initializations and start up routines of the profiles
  * 
  *
  * @param[in] void
  *
  * @pre Must be called after @ref ble_init
  *
  * @return void
  */
void wifi_provision_init(void *param);
/** @brief profile services definition to the attribute data base
  * 
  * @param[in] void
  *
  * @pre Must be called after ref wifi_provision_init
  *
  * @return @ref AT_BLE_SUCCESS operation completed successfully
  * @return @ref AT_BLE_FAILURE Generic error.
  */
at_ble_status_t wifi_provision_define (void);
/** @brief character changed handler
  * 
  * @param[in] at_ble_characteristic_changed_t which includes handle,new value
  *
  * @pre Must be called when character change event occurred
  *
  * @return @ref AT_BLE_SUCCESS operation completed successfully
  * @return @ref AT_BLE_FAILURE Generic error.
  */
uint8_t wifi_provision_char_changed_handler(at_ble_characteristic_changed_t *char_handle);
/** @brief start or restart provision and advertise and get scan list */
at_ble_status_t provision_start(void);
/** @brief ble stack indicate service client configuration change
  * @param[in] service change data
  */
uint8_t wifi_provision_svc_changed_handler(uint8_t *data);
/** @brief application periodically kicks wifi provision processing
  * @return wifi provision state
  */
uint8_t wifi_provision_processing(void);
/** @brief function for querying ble connect status
  * @return ble connected true or false
  */
uint8_t ble_is_connected(void);
/** @brief application updates wifi provisioning on wifi connect state
  * @param[in] wifi connect state
  */
void inform_wifi_connection_state(uint8_t s);
/** @brief application updates the wifi scan list
  * @param[in] wifi scanlist
  */
uint8_t wifi_provision_scanlist_receive(struct wifi_provision_scanlist *param);
/** @brief application to register the scanning function callback
  * @param[in] application's scanning function
  */
void register_wifi_provision_scanning_handler(wifi_provision_scanning_callback_t scanning_fn);
/** @brief application to register the credential update function callback
  * @param[in] application's credential function
  */
void register_wifi_provision_credentials_handler(wifi_provision_cred_callback_t credentials_fn);
/** @brief application updates ble has disconnected */
void ble_disconnected(void);
/** @brief application updates ble has connected */
void ble_connected(void);
/** @brief application requests ble be disconnected */
void disconnect_ble(void);
/** @brief application requests wif scanning */
void request_scan(void);
#endif //__WIFI_PROVISIONING_H__

