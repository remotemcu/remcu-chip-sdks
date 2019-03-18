/**
* \file
*
* \brief BLE Manager declarations
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

#ifndef __BLE_MANAGER_H__
#define __BLE_MANAGER_H__



#include <asf.h>
#include <string.h>
#include <stddef.h>
#include "at_ble_api.h"
#include "ble_utils.h"
//Not for WINC3400
//#include "platform.h"

/**
@defgroup sdk Atmel BLE SDK

@{
*/

#ifndef BLE_DEVICE_ROLE
#define BLE_DEVICE_ROLE  BLE_PERIPHERAL
#endif

#if defined WIFI_PROVISIONING
#include "wifi_provisioning.h"
#define BLE_DEVICE_NAME				"ATMEL_BLE"
#endif /* WIFI_PROVISIONING */

#if defined PROXIMITY_REPORTER
#include "pxp_reporter.h"
#define BLE_DEVICE_NAME				"ATMEL-PXP"
#endif /* PROXIMITY_REPORTER */

#if defined PROXIMITY_MONITOR
#include "pxp_monitor.h"
#define BLE_DEVICE_NAME				"ATMEL-MON"
#endif /* PROXIMITY_MONITOR */

#if (BLE_DEVICE_ROLE == BLE_OBSERVER)
#include "ble_observer.h"
#define BLE_DEVICE_NAME				"ATMEL-OBS"
#endif /* BLE_DEVICE_ROLE == BLE_OBSERVER) */

#if defined ANP_CLIENT
#include "ancs_profile.h"
#define BLE_DEVICE_NAME				"ATMEL-ANCS"
#endif /* ANCS_CLIENT */

#if defined TIP_CLIENT
#include "time_info.h"
#define BLE_DEVICE_NAME				"ATMEL-TIP"
#endif /* TIP_CLIENT */

#if defined TRANSPARENT_SERVICE
#define BLE_DEVICE_NAME				"ATMEL-TRANS"
#endif

#if defined CSC_DEVICE
#include "cscp.h"
#define BLE_DEVICE_NAME				"ATMEL-CSC"
#endif /* CSC_DEVICE */

/** @brief default device name */
#ifndef BLE_DEVICE_NAME
#define BLE_DEVICE_NAME				"ATMEL-BLE"
#endif

/** @brief event timeout */
#define BLE_EVENT_TIMEOUT			(0)

/* Dummy BLE handler's for unused functions */
static inline void ble_dummy_handler(void *param)
{
	UNUSED(param);
	DBG_LOG_DEV("!:(:(");
}

/* Unused variable - remove compiler warning */
static inline at_ble_status_t BLE_UNUSED2_VAR(void *param1_var, void *param2_var)
{
	UNUSED(param1_var);
	UNUSED(param2_var);
	DBG_LOG_DEV("!!:(");
	return AT_BLE_SUCCESS;
}

/** @brief Observer related declarations */
#define LE_LIMITED_DISCOVERABLE_MODE  ((uint8_t) 1 << 0)
#define LE_GENERAL_DISCOVERABLE_MODE  ((uint8_t) 1 << 1)
#define BREDR_NOT_SUPPORTED			  ((uint8_t) 1 << 2)
#define	LE_BREDR_CAPABLE_CONTROLLER   ((uint8_t) 1 << 3)
#define LE_BREDR_CAPABLE_HOST		  ((uint8_t) 1 << 4)

/** @brief Length of Adv data types*/
#define APPEARANCE_SIZE					2
#define TX_POWER_LEVEL_SIZE				1
#define ADV_INTERVAL_SIZE				2

/** @brief Gap Advertisement Types */
typedef enum
{
	/// flags 
	FLAGS = 0x01,
	/// incomplete list of 16bits service uuids
	INCOMPLETE_LIST_16BIT_SERV_UUIDS,
	/// complete list of 16bits service uuids
	COMPLETE_LIST_16BIT_SERV_UUIDS,
	/// incomplete list of 32bits service uuids
	INCOMPLETE_LIST_32BIT_SERV_UUIDS,
	/// complete list of 32bits service uuids
	COMPLETE_LIST_32BIT_SERV_UUIDS,
	/// incomplete list of 128bits service uuids
	INCOMPLETE_LIST_128BIT_SERV_UUIDS,
	/// complete list of 128bits of service uuids
	COMPLETE_LIST_128BIT_SERV_UUIDS,
	/// shortened local name of the device 
	SHORTENED_LOCAL_NAME,
	/// complete local name of the device
	COMPLETE_LOCAL_NAME,
	/// TX power level
	TX_POWER_LEVEL,
	/// class of the device
	CLASS_OF_DEVICE = 0x0D,
	/// simple pairing hashing
	SIMPLE_PAIRING_HASHING,
	///simple pairing randomizer
	SIMPLE_PAIRING_RANDOMIZER,
	/// device id
	DEVICE_ID,
	/// security manager out of band flags
	SECURITY_MANAGER_OOB_FLAGS,
	/// slave connection interval range
	SLAVE_CONNECTION_INTERVAL_RANGE,
	/// list of 16bits service solicitation uuid 
	LIST_16BIT_SERV_SOLICITATION_UUIDS = 0x14,
	/// list of 128bits service solicitation uuids
	LIST_128BIT_SERV_SOLICITATION_UUIDS,
	///	service data
	SERVICE_DATA,
	/// public target address
	PUBLIC_TARGET_ADDRESS,
	/// random target address
	RANDOM_TARGET_ADDRESS,
	/// appearance
	APPEARANCE,
	///advertising interval
	ADVERTISING_INTERVAL,
	/// le bluetooth device address
	LE_BLUETOOTH_DEVICE_ADDRESS,
	/// le role
	LE_ROLE,
	/// simple pairing hashing c256
	SIMPLE_PAIRING_HASHING_C256,
	/// simple pairing randomizer r256
	SIMPLE_PAIRING_RANDOMIZER_R256,
	/// service data 32bits
	SERVICE_DATA_32BIT = 0x20,
	/// service data 128bits
	SERVICE_DATA_128BIT,
	/// le secure connection confirmation value
	LE_SECURE_CONNECTIONS_CONFIRMATION_VALUE,
	/// le secure connection random value
	LE_SECURE_CONNECTIONS_RANDOM_VALUE,
	/// threed information data
	THREED_INFORMATION_DATA = 0x3D,
	///manufacturer specific data
	MANUFACTURER_SPECIFIC_DATA = 0xFF
}gap_ad_type;

#if (BLE_DEVICE_ROLE == BLE_OBSERVER)
/* scan report handler */
#define BLE_SCAN_REPORT_HANDLER								ble_scan_report_handler
/* scan information handler */
#define BLE_SCAN_INFO_HANDLER(param)						ble_observer_scan_info_handler(param);\
															ble_scan_info_handler(param);
/* scan data handler */															
#define	BLE_SCAN_DATA_HANDLER								ble_observer_scan_data_handler
#endif /* (BLE_DEVICE_ROLE == BLE_OBSERVER) */

//Default number of charaterstics for a service is 1
#define TOTAL_CHARATERISTIC_NUM     1

#if defined HEART_RATE_SERVICE
#undef TOTAL_CHARATERISTIC_NUM
#define TOTAL_CHARATERISTIC_NUM     3
#endif

#if defined TRANSPARENT_SERVICE
#undef TOTAL_CHARATERISTIC_NUM
#define TOTAL_CHARATERISTIC_NUM     3
#endif

#if defined GLUCOSE_SERVICE
#undef TOTAL_CHARATERISTIC_NUM
#define TOTAL_CHARATERISTIC_NUM     4
#endif

/** @brief Service UUID's */

/* WiFi Con service UUID */
#define WIFI_CON_SERVICE_UUID					("\x1b\xc5\xd5\xa5\x02\x00\x89\x86\xe4\x11\x29\xd2\x01\x00\x88\x77")
/* WiFi Con State Characteristic UUID */
#define WIFI_CON_STATE_CHAR_UUID				("\x1b\xc5\xd5\xa5\x02\x00\x89\x86\xe4\x11\x29\xd2\x02\x00\x88\x77")
/* WiFi Con State Characteristic UUID */
#define WIFI_CON_APPARAM_CHAR_UUID				("\x1b\xc5\xd5\xa5\x02\x00\x89\x86\xe4\x11\x29\xd2\x03\x00\x88\x77")

/* WiFi Scan service UUID */
#define WIFI_SCAN_SERVICE_UUID					("\x1b\xc5\xd5\xa5\x02\x00\xa1\x85\xe4\x11\x24\xd2\x01\x00\x8c\xfb")
/* WiFi Scan Mode Characteristic UUID */
#define WIFI_SCAN_MODE_CHAR_UUID				("\x1b\xc5\xd5\xa5\x02\x00\xa1\x85\xe4\x11\x24\xd2\x02\x00\x8c\xfb")
/* WiFi Scan APcount Characteristic UUID */
#define WIFI_SCAN_APCOUNT_CHAR_UUID				("\x1b\xc5\xd5\xa5\x02\x00\xa1\x85\xe4\x11\x24\xd2\x03\x00\x8c\xfb")
/* WiFi Scan APdetails Characteristic UUID */
#define WIFI_SCAN_APDETAILS_CHAR_UUID			("\x1b\xc5\xd5\xa5\x02\x00\xa1\x85\xe4\x11\x24\xd2\x00\x01\x8c\xfb")

/** CSC Service UUID. */
#define CSC_SERVICE_UUID						("\x1b\xc5\xd5\xa5\x02\x00\xa6\x85\xe5\x11\x35\x39\xa0\xbb\x5a\xfd")

/** CSC Endpoint Characteristic UUID. */
#define CSC_ENDPOINT_CHAR_UUID					("\x1b\xc5\xd5\xa5\x02\x00\xa6\x85\xe5\x11\x35\x39\xa1\xbb\x5a\xfd")

#if 0
#define UUID_MCHP_PROPRIETARY_SERVICE_16				("\x55\xE4\x05\xD2\xAF\x9F\xA9\x8F\xE5\x4A\x7D\xFE\x43\x53\x53\x49")
#define UUID_MCHP_TRANS_TX_16							("\x16\x96\x24\x47\xC6\x23\x61\xBA\xD9\x4B\x4D\x1E\x43\x53\x53\x49")
#define UUID_MCHP_TRANS_RX_16							("\xB3\x9B\x72\x34\xBE\xEC\xD4\xA8\xF4\x43\x41\x88\x43\x53\x53\x49")
#define UUID_MCHP_TRANS_CTRL_16						("\x7e\x3b\x07\xff\x1c\x51\x49\x2f\xb3\x39\x8a\x4c\x43\x53\x53\x49")
#endif
#define UUID_MCHP_PROPRIETARY_SERVICE_16				0x55,0xE4,0x05,0xD2,0xAF,0x9F,0xA9,0x8F,0xE5,0x4A,0x7D,0xFE,0x43,0x53,0x53,0x49
#define UUID_MCHP_TRANS_TX_16							0x16,0x96,0x24,0x47,0xC6,0x23,0x61,0xBA,0xD9,0x4B,0x4D,0x1E,0x43,0x53,0x53,0x49
#define UUID_MCHP_TRANS_RX_16							0xB3,0x9B,0x72,0x34,0xBE,0xEC,0xD4,0xA8,0xF4,0x43,0x41,0x88,0x43,0x53,0x53,0x49
#define UUID_MCHP_TRANS_CTRL_16						0x7e,0x3b,0x07,0xff,0x1c,0x51,0x49,0x2f,0xb3,0x39,0x8a,0x4c,0x43,0x53,0x53,0x49

/* Immediate Alert service UUID  */
#define IMMEDIATE_ALERT_SERVICE_UUID			(0x1802)

/* Link Loss service UUID */
#define LINK_LOSS_SERVICE_UUID					(0x1803)

/* Tx Power service UUID */
#define TX_POWER_SERVICE_UUID					(0x1804)

/* Current time service UUID */
#define CURRENT_TIME_SERVICE_UUID				(0x1805)

/*Glucose service UUID*/
#define GLUCOSE_SERVICE_UUID				(0x1808)

/* Heart rate service UUID */
#define HEART_RATE_SERVICE_UUID				(0x180D)

/* device information service uuid */
#define DIS_SERVICE_UUID 						(0x180A)

/** battery service uuid */
#define BAT_SERVICE_UUID 						(0x180F)

/** Scan param service uuid */
#define SPS_SERVICE_UUID 						(0x1813)

/* Characteristics UUID's */
/* Alert Level Characteristic UUID */
#define ALERT_LEVEL_CHAR_UUID					(0x2A06)

/* Tx Power Level Characteristic UUID */
#define TX_POWER_LEVEL_CHAR_UUID				(0x2A07)

/** battery level characteristic uuid */
#define BAT_CHAR_BAT_LEVEL_UUID 				(0x2A19)

/** heart rate measurement characteristic uuid */
#define HEART_RATE_MEASUREMENT_CHAR_UUID	(0x2A37)

/** Body Sensor location characteristic uuid */
#define BODY_SENSOR_LOCATION_CHAR_UUID          (0x2A38)

/** Heart Rate Control Point characteristic uuid */
#define HEART_RATE_CONTROL_POINT_CHAR_UUID	(0x2A39)

/** Glucose measurement characteristic uuid */
#define GLUCOSE_MEASUREMENT_CHAR_UUID		(0x2A18)

/** Glucose measurement context characteristic uuid */
#define GLUCOSE_MEASUREMENT_CONTEXT_CHAR_UUID		(0x2A34)

/** Glucose feature characteristic uuid */
#define GLUCOSE_FEATURE_CHAR_UUID		(0x2A51)

/** Record Access Control Point characteristic uuid */
#define RECORD_ACCESS_CONTROL_POINT_CHAR_UUID		(0x2A52)

/* device information service characteristics uuids */
#define DIS_CHAR_SYSTEM_ID_UUID					(0x2A23)
#define DIS_CHAR_MODEL_NUMBER_UUID				(0x2A24)
#define DIS_CHAR_SERIAL_NUMBER_UUID				(0x2A25)
#define DIS_CHAR_FIRMWARE_REIVSION_UUID			(0x2A26)															
#define DIS_CHAR_HARDWARE_REVISION_UUID			(0x2A27)
#define DIS_CHAR_SOFTWARE_REVISION_UUID			(0x2A28)
#define DIS_CHAR_MANUFACTURER_NAME_UUID			(0x2A29)
#define DIS_CHAR_IEEE_REG_CERT_DATA_LIST_UUID	(0x2A2A)
/* Current Time char UUID */
#define CURRENT_TIME_CHAR_UUID					(0x2A2B)
/** scan refresh characteristic uuid */
#define SPS_CHAR_SCAN_REFRESH_UUID 				(0x2A31)
/** scan interval characteristic uuid */
#define SPS_CHAR_SCAN_INT_VALUE_UUID 			(0x2A4F)														
#define DIS_CHAR_PNP_ID_UUID					(0x2A50)



/* All GAP Connection Parameter defined */
#if ((BLE_DEVICE_ROLE == BLE_CENTRAL) || (BLE_DEVICE_ROLE == BLE_CENTRAL_AND_PERIPHERAL) || (BLE_DEVICE_ROLE == BLE_OBSERVER))
/** minimum connection interval */
#define GAP_CONN_INTERVAL_MIN			(20)        //Connection interval min 20ms
/** maximum connection interval */
#define GAP_CONN_INTERVAL_MAX			(40)		//Connection interval max 40ms
/** connection slave latency */
#define GAP_CONN_SLAVE_LATENCY			(0)
/** minimum length of local info parameters when using connection establishment proc */ 
#define GAP_CE_LEN_MIN					(0)
/** maximum length of local info parameters when using connection establishment proc */
#define GAP_CE_LEN_MAX					(0)
/** supervision time-out */
#define GAP_SUPERVISION_TIMOUT			(0x1f4)		// 500 for supervision time-out

/** number of connections */ 
#define GAP_CONNECT_PEER_COUNT			(1)
/** gatt discover start handle */ 
#define GATT_DISCOVERY_STARTING_HANDLE	(0x0001)
/** gatt discover end handle */
#define GATT_DISCOVERY_ENDING_HANDLE	(0xFFFF)

#define MAX_SCAN_DEVICE					(10)			  //Max number of scan device
#define SCAN_INTERVAL					(96)              //Scan interval 30ms in term of 625us
#define SCAN_WINDOW						(96)              //Scan window 30ms values in term of 625ms
#define SCAN_TIMEOUT					(0x0000)          //Timeout  Scan time-out, 0x0000 disables time-out
#define SCAN_TYPE						(AT_BLE_SCAN_ACTIVE)

#endif //((BLE_DEVICE_ROLE == BLE_CENTRAL) || (BLE_DEVICE_ROLE == BLE_CENTRAL_AND_PERIPHERAL) || (BLE_DEVICE_ROLE == BLE_OBSERVER))

/** maximum number of devices connected */
#define MAX_DEVICE_CONNECTED			(1)


#if ((BLE_DEVICE_ROLE == BLE_PERIPHERAL) || (BLE_DEVICE_ROLE == BLE_CENTRAL_AND_PERIPHERAL))

#if defined CSC_DEVICE
#define BLE_PROFILE_INIT(param)								csc_prf_init(param);\
															csc_prf_dev_adv();
#define BLE_ADDITIONAL_CONNECTED_STATE_HANDLER				csc_prf_connected_state_handler
#define BLE_CHARACTERISTIC_CHANGED							csc_prf_char_changed_handler
#define BLE_PRIMARY_SERVICE_FOUND_HANDLER					csc_prf_service_found_handler
#define BLE_CHARACTERISTIC_FOUND_HANDLER					csc_prf_characteristic_found_handler
#define BLE_DESCRIPTOR_FOUND_HANDLER						csc_prf_descriptor_found_handler
#define BLE_DISCOVERY_COMPLETE_HANDLER						csc_prf_discovery_complete_handler
#define BLE_NOTIFICATION_RECEIVED_HANDLER					csc_prf_notification_handler
#define BLE_ADDITIONAL_PAIR_DONE_HANDLER					csc_prf_write_notification_handler
#define BLE_ADDITIONAL_DISCONNECTED_STATE_HANDLER(param)	csc_prf_disconnect_event_handler(param);
#define BLE_ADDITIONAL_ENCRYPTION_CHANGED_HANDLER(param)    csc_prf_write_notification_handler(param);
#endif

#if defined WIFI_PROVISIONING
#define BLE_PROFILE_INIT							wifi_provision_init
#define BLE_CHARACTERISTIC_CHANGED					wifi_provision_char_changed_handler
#define BLE_SERVICE_CHANGED							wifi_provision_svc_changed_handler
#endif	/* WIFI_PROVISIONING	 */

#if defined PROXIMITY_REPORTER
#define BLE_PROFILE_INIT							pxp_reporter_init 
#define BLE_ADDITIONAL_CONNECTED_STATE_HANDLER		pxp_reporter_connected_state_handler
#define BLE_ADDITIONAL_DISCONNECTED_STATE_HANDLER	pxp_disconnect_event_handler
#define BLE_CHARACTERISTIC_CHANGED					pxp_reporter_char_changed_handler
#endif	/* PROXIMITY_REPORTER	 */

#define BLE_CONN_PARAM_UPDATE_DONE					ble_conn_param_update
#define	BLE_PAIR_REQUEST							ble_pair_request_handler
#define BLE_PAIR_KEY_REQUEST						ble_pair_key_request_handler

#define BLE_PAIR_DONE(param)						ble_pair_done_handler(param);\
													BLE_ADDITIONAL_PAIR_DONE_HANDLER(param);
													
#define BLE_ENCRYPTION_REQUEST						ble_encryption_request_handler

#define BLE_ENCRYPTION_STATUS_CHANGED(param)		ble_encryption_status_change_handler(param);\
													BLE_ADDITIONAL_ENCRYPTION_CHANGED_HANDLER(param);
#endif /* (BLE_DEVICE_ROLE == BLE_PERIPHERAL) */


#if ((BLE_DEVICE_ROLE == BLE_CENTRAL) || (BLE_DEVICE_ROLE == BLE_CENTRAL_AND_PERIPHERAL))
#define BLE_SCAN_REPORT_HANDLER						ble_scan_report_handler
#define BLE_SCAN_INFO_HANDLER						ble_scan_info_handler

/** @brief Function handlers for proximity monitor */
#if defined PROXIMITY_MONITOR
#define BLE_PROFILE_INIT							pxp_monitor_init
#define BLE_ADDITIONAL_CONNECTED_STATE_HANDLER		pxp_monitor_connected_state_handler
#define BLE_ADDITIONAL_DISCONNECTED_STATE_HANDLER	pxp_disconnect_event_handler																								
#define BLE_PRIMARY_SERVICE_FOUND_HANDLER			pxp_monitor_service_found_handler
#define BLE_DISCOVERY_COMPLETE_HANDLER				pxp_monitor_discovery_complete_handler
#define	BLE_SCAN_DATA_HANDLER						pxp_monitor_scan_data_handler
#define BLE_CHARACTERISTIC_READ_RESPONSE			pxp_monitor_characteristic_read_response
#define BLE_CHARACTERISTIC_FOUND_HANDLER			pxp_monitor_characteristic_found_handler
#endif /* PROXIMITY_MONITOR */

/** @brief initializing function handlers for ANP client*/
#ifdef ANP_CLIENT
#define BLE_PROFILE_INIT										anp_client_init
#define BLE_ADDITIONAL_CONNECTED_STATE_HANDLER(param)			anp_client_connected_state_handler(param);
#define BLE_ADDITIONAL_DISCONNECTED_STATE_HANDLER(param)		anp_client_disconnected_event_handler(param);
#define BLE_CHARACTERISTIC_WRITE_RESPONSE						anp_client_write_response_handler
#define BLE_CHARACTERISTIC_FOUND_HANDLER						anp_client_characteristic_found_handler
#define BLE_NOTIFICATION_RECEIVED_HANDLER						anp_client_notification_handler
#define BLE_DESCRIPTOR_FOUND_HANDLER							anp_client_descriptor_found_handler
#define	BLE_CHARACTERISTIC_CHANGED								anp_client_char_changed_handler

#define BLE_PRIMARY_SERVICE_FOUND_HANDLER						anp_client_service_found_handler
#define BLE_DISCOVERY_COMPLETE_HANDLER							anp_client_discovery_complete_handler
#define BLE_ADDITIONAL_PAIR_DONE_HANDLER(param)					anp_client_write_notification_handler(param)
#define BLE_ADDITIONAL_ENCRYPTION_CHANGED_HANDLER(param)		anp_client_write_notification_handler(param)
#endif /* ANP_CLIENT */

/** @brief initializing function handlers for TIP client*/
#ifdef TIP_CLIENT
#define BLE_PROFILE_INIT										time_info_init
#define BLE_ADDITIONAL_CONNECTED_STATE_HANDLER(param)			time_info_service_discover(param);
#define BLE_ADDITIONAL_DISCONNECTED_STATE_HANDLER(param)		time_info_disconnected_event_handler(param);
#define BLE_CHARACTERISTIC_FOUND_HANDLER						time_info_characteristic_found_handler
#define	BLE_CHARACTERISTIC_CHANGED								time_info_char_changed_handler

#define BLE_PRIMARY_SERVICE_FOUND_HANDLER						time_info_service_found_handler
#define BLE_DISCOVERY_COMPLETE_HANDLER							time_info_discovery_complete_handler
#define BLE_CHARACTERISTIC_READ_RESPONSE						time_info_characteristic_read_response
#endif /* TIP_CLIENT */

#endif /* ((BLE_DEVICE_ROLE == BLE_CENTRAL) || (BLE_DEVICE_ROLE == BLE_CENTRAL_AND_PERIPHERAL)) */

/* Common functions */
#define BLE_CONNECTED_STATE_HANDLER(param)			ble_connected_state_handler(param);\
													BLE_ADDITIONAL_CONNECTED_STATE_HANDLER(param);

#define BLE_DISCONNECTED_STATE_HANDLER(param)		ble_disconnected_state_handler(param);\
													BLE_ADDITIONAL_DISCONNECTED_STATE_HANDLER(param);

#ifndef BLE_SERVICE_CHANGED
#define BLE_SERVICE_CHANGED										ble_dummy_handler
#endif

#ifndef BLE_PROFILE_INIT
#define BLE_PROFILE_INIT										ble_dummy_handler
#endif

#ifndef BLE_ADDITIONAL_CONNECTED_STATE_HANDLER
#define BLE_ADDITIONAL_CONNECTED_STATE_HANDLER					ble_dummy_handler
#endif

#ifndef BLE_ADDITIONAL_DISCONNECTED_STATE_HANDLER
#define BLE_ADDITIONAL_DISCONNECTED_STATE_HANDLER				ble_dummy_handler
#endif

#ifndef BLE_CHARACTERISTIC_CHANGED
#define BLE_CHARACTERISTIC_CHANGED								ble_dummy_handler
#endif

#ifndef BLE_CONN_PARAM_UPDATE_DONE
#define BLE_CONN_PARAM_UPDATE_DONE								ble_dummy_handler
#endif

#ifndef BLE_PAIR_REQUEST
#define	BLE_PAIR_REQUEST										ble_dummy_handler
#endif

#ifndef BLE_PAIR_KEY_REQUEST
#define BLE_PAIR_KEY_REQUEST									ble_dummy_handler
#endif

#ifndef BLE_PAIR_DONE
#define BLE_PAIR_DONE											ble_dummy_handler
#endif
 
#ifndef BLE_ENCRYPTION_REQUEST
#define BLE_ENCRYPTION_REQUEST									ble_dummy_handler
#endif

#ifndef BLE_ENCRYPTION_STATUS_CHANGED
#define BLE_ENCRYPTION_STATUS_CHANGED							ble_dummy_handler
#endif
#ifndef BLE_SCAN_REPORT_HANDLER
#define BLE_SCAN_REPORT_HANDLER									ble_dummy_handler
#endif

#ifndef BLE_SCAN_DATA_HANDLER
#define BLE_SCAN_DATA_HANDLER(x,y)								BLE_UNUSED2_VAR(x, &y)
#endif

#ifndef BLE_SCAN_INFO_HANDLER
#define BLE_SCAN_INFO_HANDLER									ble_dummy_handler
#endif

#ifndef BLE_CHARACTERISTIC_WRITE_RESPONSE
#define BLE_CHARACTERISTIC_WRITE_RESPONSE						ble_dummy_handler
#endif

#ifndef BLE_ADDITIONAL_PAIR_DONE_HANDLER
#define BLE_ADDITIONAL_PAIR_DONE_HANDLER						ble_dummy_handler
#endif

#ifndef BLE_ADDITIONAL_ENCRYPTION_CHANGED_HANDLER
#define BLE_ADDITIONAL_ENCRYPTION_CHANGED_HANDLER				ble_dummy_handler
#endif

#ifndef BLE_NOTIFICATION_RECEIVED_HANDLER
#define BLE_NOTIFICATION_RECEIVED_HANDLER						ble_dummy_handler
#endif

#ifndef BLE_CHARACTERISTIC_READ_RESPONSE
#define BLE_CHARACTERISTIC_READ_RESPONSE						ble_dummy_handler
#endif

#ifndef BLE_DESCRIPTOR_FOUND_HANDLER
#define BLE_DESCRIPTOR_FOUND_HANDLER							ble_dummy_handler
#endif

#ifndef BLE_PRIMARY_SERVICE_FOUND_HANDLER
#define BLE_PRIMARY_SERVICE_FOUND_HANDLER						ble_dummy_handler
#endif

#ifndef BLE_DISCOVERY_COMPLETE_HANDLER
#define BLE_DISCOVERY_COMPLETE_HANDLER							ble_dummy_handler
#endif

#ifndef BLE_CHARACTERISTIC_FOUND_HANDLER
#define BLE_CHARACTERISTIC_FOUND_HANDLER						ble_dummy_handler
#endif

#ifndef BLE_PAIR_ENABLE
#define BLE_PAIR_ENABLE					(false)
#endif

/****************************************************************************************
*							        Structures                                     		*
****************************************************************************************/

/** @brief advertisement data element
*/
typedef struct adv_element
{
	/// length of the advertisement data
	uint8_t len;
	/// advertisement type
	uint8_t type;
	/// advertisement data
	uint8_t *data;
}adv_element_t;

/** @brief GATT services handles
*/
typedef struct gatt_service_handler
{
	/// service uuid
	at_ble_uuid_t	serv_uuid;
	/// service handle
	at_ble_handle_t	serv_handle;
	/// service characteristic
	at_ble_characteristic_t	serv_chars[TOTAL_CHARATERISTIC_NUM];
}gatt_service_handler_t;

/****************************************************************************************
*                                       Functions                                       *
****************************************************************************************/

/* Typedef for GAP event callbacks */
typedef void (*ble_gap_event_callback_t)(at_ble_handle_t);

/* Typedef for characteristic value changed event callback */
typedef at_ble_status_t (*ble_characteristic_changed_callback_t)(at_ble_characteristic_changed_t *);

/** @brief function to set the device name.
  *
  * @param[in] name name of the device.
  * @param[in] name_len length of the device name.
  *
  * @return @ref AT_BLE_SUCCESS operation completed successfully.
  * @return @ref AT_BLE_FAILURE Generic error.
  *
  */
at_ble_status_t ble_set_device_name(uint8_t *name, uint8_t name_len);

/** @brief function used to update the connection parameter.
  *
  * @param[in] conn_param_update @ref at_ble_conn_param_update_done_t parameters to be updated.
  *
  * @return none.
  *
  */
void ble_conn_param_update(at_ble_conn_param_update_done_t *conn_param_update);

/** @brief function called when the AT_BLE_PAIR_REQUEST event is received from stack.
  *
  * @param[in] pair_key @ref at_ble_pair_request_t details for the pairing request from the peer.
  *
  * @return none.
  *
  */
void ble_pair_request_handler(at_ble_pair_request_t *at_ble_pair_req);

/** @brief function called when the AT_BLE_PAIR_KEY_REQUEST event is received from stack.
  *
  * @param[in] pair_key @ref at_ble_pair_key_request_t key details for the pairing request.
  *
  * @return none.
  *
  */
void ble_pair_key_request_handler(at_ble_pair_key_request_t *pair_key);

/** @brief function called when the AT_BLE_PAIR_DONE event is received from stack.
  *
  * @param[in] pairing_params @ref at_ble_pair_done_t pair done information.
  *
  * @return @ref AT_BLE_SUCCESS operation completed successfully.
  * @return @ref AT_BLE_FAILURE Generic error.
  *
  */
at_ble_status_t ble_pair_done_handler(at_ble_pair_done_t *pairing_params);

/** @brief function called when the AT_BLE_ENCRYPTION_REQUEST event is received from stack.
  *
  * @param[in] encry_req encryption request from the peer device.
  *
  * @return none.
  *
  */
void ble_encryption_request_handler (at_ble_encryption_request_t *encry_req);

/** @brief function called when the AT_BLE_ENCRYPTION_STATUS_CHANGED event is received from stack.
  *
  * @param[in] encry_status changed encryption status.
  *
  * @return none.
  *
  */
void ble_encryption_status_change_handler(at_ble_encryption_status_changed_t *encry_status);

#if ((BLE_DEVICE_ROLE == BLE_CENTRAL) || (BLE_DEVICE_ROLE == BLE_CENTRAL_AND_PERIPHERAL) || (BLE_DEVICE_ROLE == BLE_OBSERVER))
/** @brief function requesting the device for the connection.
  *
  * @param[in] dev_addr address of the the peer device.
  *
  * @return @ref AT_BLE_SUCCESS operation completed successfully.
  * @return @ref AT_BLE_FAILURE Generic error.
  *
  */
at_ble_status_t gap_dev_connect(at_ble_addr_t dev_addr[]);

/** @brief function to start scan.
  *
  * @param[in] none.
  *
  * @return @ref AT_BLE_SUCCESS operation completed successfully.
  * @return @ref AT_BLE_FAILURE Generic error.
  *
  */
at_ble_status_t gap_dev_scan(void);

/** @brief function to handle the scan information.
  *
  * @param[in] scan_param scanned data.
  *
  * @return @ref AT_BLE_SUCCESS operation completed successfully.
  * @return @ref AT_BLE_FAILURE Generic error.
  *
  */
at_ble_status_t ble_scan_info_handler(at_ble_scan_info_t *scan_param);

/** @brief function to handle the scan status.
  *
  * @param[in] scan_report status of the scan.
  *
  * @return @ref AT_BLE_SUCCESS operation completed successfully.
  * @return @ref AT_BLE_FAILURE Generic error.
  *
  */
at_ble_status_t ble_scan_report_handler(at_ble_scan_report_t *scan_report);

/** @brief function parses the received advertising data for service and local name.
  *
  * @param[in] scan_info_data the received data.
  * @param[in] ble_service_uuid uuid to be searched in the received data.
  * @param[in] adv_type advertisement type
  *
  * @return @ref AT_BLE_SUCCESS operation completed successfully.
  * @return @ref AT_BLE_FAILURE Generic error.
  *
  */
uint8_t scan_info_parse(at_ble_scan_info_t *scan_info_data, at_ble_uuid_t *ble_service_uuid, uint8_t adv_type);

/** @brief function called when the AT_BLE_CHARACTERISTIC_FOUND event is received from stack.
  *
  * @param[in] characteristic_found @ref at_ble_characteristic_found_t information related to the characteristic found.
  *
  * @return none.
  *
  */
void ble_characteristic_found_handler(at_ble_characteristic_found_t *characteristic_found);
#endif

/** @brief function to handle the BLE event task.
  *
  * @param[in] none.
  *
  * @return @ref AT_BLE_SUCCESS operation completed successfully
  * @return @ref AT_BLE_FAILURE Generic error.
  *
  */
at_ble_status_t ble_event_task(void);

/** @brief function sets both device address and device name which are exposed to all other devices.
  *
  * @param[in] addr address to be set as a device address.
  *
  * @return none.
  *
  */
void ble_device_init(at_ble_addr_t *addr);

/** @brief function handling all the events from the stack, responsible
  * for calling the respective functions initialized for the events.
  *
  * @param[in] events events received from the stack @ref at_ble_events_t.
  * @param[in] event_params data received from stack for the respective event received.
  *
  * @return none.
  *
  */
void ble_event_manager(at_ble_events_t events , void *event_params);

/** @brief function called when the AT_BLE_DISCOVERY_COMPLETE event is received from the stack.
  *
  * @param[in]	discover_status status of the discovery.
  *
  * @return none.
  *
  */
void ble_discovery_complete_handler(at_ble_discovery_complete_t *discover_status);

/** @brief function called when the AT_BLE_DISCONNECTED event is received from the stack.
  *
  * @param[in] disconnect @ref at_ble_disconnected_t information about the disconnection.
  *
  * @return none.
  *
  */
void ble_disconnected_state_handler(at_ble_disconnected_t *disconnect);

/** @brief function to send slave security request.
  *
  * @param[in] conn_handle connection handle.
  *
  * @return @ref AT_BLE_SUCCESS operation completed successfully
  * @return @ref AT_BLE_FAILURE Generic error.
  *
  */
at_ble_status_t ble_send_slave_sec_request(at_ble_handle_t conn_handle);

/** @brief function called when the AT_BLE_CONNECTED event is received from the stack.
  *
  * @param[in] conn_params connection parameters @ref at_ble_connected_t.
  *
  * @return none.
  *
  */
void ble_connected_state_handler(at_ble_connected_t *conn_params);

/** @brief Register callback function, to be triggered when connected to the device.
  * 
  * @param[in] connected_cb_fn function called when disconnected from the device.
  *
  * @return none.
  *
  */
void register_ble_connected_event_cb(ble_gap_event_callback_t connected_cb_fn);

/** @brief Register callback function, to be triggered when disconnected from the peer device.
  * 
  * @param[in] disconnected_cb_fn function called when disconnected from the peer device.
  *
  * @return none.
  *
  */
void register_ble_disconnected_event_cb(ble_gap_event_callback_t disconnected_cb_fn);

/** @brief Register callback function, to be triggered when pairing procedure is completed.
  * 
  * @param[in] paired_cb_fn function called when pairing is completed.
  *
  * @return none.
  *
  */
void register_ble_paired_event_cb(ble_gap_event_callback_t paired_cb_fn);

/** @brief Register callback function, to be triggered when characteristic value is changed.
  * 
  * @param[in]  function called when characteristic value is changed.
  *
  * @return none.
  *
  */
void register_ble_characteristic_changed_cb(ble_characteristic_changed_callback_t char_changed_cb_fn);

/** @}*/

#endif /*__BLE_MANAGER_H__*/
