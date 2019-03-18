/**
* \file
*
* \brief Proximity Reporter Profile declarations
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


#ifndef __PXP_REPORTER_H__
#define __PXP_REPORTER_H__

#include "ble_manager.h"


/****************************************************************************************
*							        Includes	                                     							*
****************************************************************************************/


/****************************************************************************************
*							        Macros	                                     							*
****************************************************************************************/

/** @brief APP_PXP_FAST_ADV between 0x0020 and 0x4000 in 0.625 ms units (20ms to 10.24s). */
#define APP_PXP_FAST_ADV				(100) //100 ms

/** @brief APP_PXP_ADV_TIMEOUT Advertising time-out between 0x0001 and 0x3FFF in seconds, 0x0000 disables time-out.*/
#define APP_PXP_ADV_TIMEOUT				(1000) // 100 Secs

/** @brief scan_resp_len is the length of the scan response data */
#define SCAN_RESP_LEN					(10)

/** @brief ADV_DATA_LEN */
#define ADV_DATA_LEN					(18)

/** @brief ADV_TYPE_LEN */
#define ADV_TYPE_LEN					(0x01)

/** @brief LL_ADV_DATA_UUID_LEN the size of LL service uuid */
#define LL_ADV_DATA_UUID_LEN			(2)

/** @brief LL_ADV_DATA_UUID_TYPE the total sizeof LL service uuid*/
#define LL_ADV_DATA_UUID_TYPE			(0x03)

/** @brief TXP_ADV_DATA_UUID_LEN the size of TXP service uuid */
#define TXP_ADV_DATA_UUID_LEN			(2)

/** @brief TXP_ADV_DATA_UUID_TYPE the total sizeof TXP service uuid*/
#define TXP_ADV_DATA_UUID_TYPE			(0x03)

/** @brief IAL_ADV_DATA_UUID_LEN the size of IAL service uuid */
#define IAL_ADV_DATA_UUID_LEN			(2)

/** @brief IAL_ADV_DATA_UUID_TYPE the total sizeof IAL service uuid*/
#define IAL_ADV_DATA_UUID_TYPE			(0x03)

/** @brief PXP_ADV_DATA_NAME_LEN the  length of the device name */
#define PXP_ADV_DATA_NAME_LEN			(9)

/** @brief PXP_ADV_DATA_NAME_TYPE the gap ad data type */
#define PXP_ADV_DATA_NAME_TYPE			(0x09)

/* @brief PXP_ADV_DATA_NAME_DATA the actual name of device */
#define PXP_ADV_DATA_NAME_DATA			("ATMEL-PXP")

/* @brief call back handler type  */
typedef void (*reporter_callback_t)(uint8_t);


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
void pxp_reporter_init(void *param);

/** @brief Initialize the services of the profile
  * 
  * @param[in] void
  *
  * @pre Must be called before @ref pxp_service_define
  *
  * @return void
  */
void pxp_service_init(void);


/** @brief profile services definition to the attribute data base
  * 
  * @param[in] void
  *
  * @pre Must be called after ref pxp_service_init
  *
  * @return @ref AT_BLE_SUCCESS operation completed successfully
  * @return @ref AT_BLE_FAILURE Generic error.
  */
at_ble_status_t pxp_service_define (void);


/** @brief sets the advertisement data and starts advertisement
  * 
  * @param[in] void
  *
  * @pre Must be called after ref pxp_service_init
  *
  * @return void
  */
void pxp_reporter_adv(void);

/** @brief connection state handler
  * 
  * @param[in] at_ble_connected_t which includes the connection parameters like handle
  *
  * @pre Must be called when the device is connected
  *
  * @return @ref AT_BLE_SUCCESS operation completed successfully
  * @return @ref AT_BLE_FAILURE Generic error.
  */
extern at_ble_status_t pxp_reporter_connected_state_handler (at_ble_connected_t * conn_params);


/** @brief disconnection event handler
  * 
  * @param[in] at_ble_disconencted_t which includes the connection parameters like handle,reason for disconnection
  *
  * @pre Must be called when the device is disconnected
  *
  * @return @ref AT_BLE_SUCCESS operation completed successfully
  * @return @ref AT_BLE_FAILURE Generic error.
  */
at_ble_status_t pxp_disconnect_event_handler(at_ble_disconnected_t *disconnect);


/** @brief character changed handler
  * 
  * @param[in] at_ble_characteristic_changed_t which includes handle,new value
  *
  * @pre Must be called when character change event occurred
  *
  * @return @ref AT_BLE_SUCCESS operation completed successfully
  * @return @ref AT_BLE_FAILURE Generic error.
  */
at_ble_status_t pxp_reporter_char_changed_handler(at_ble_characteristic_changed_t *char_handle);

/**
* @brief function which register the application alerting function for pathloss to the profile
*
* @param[in] call back function of the application for pathloss
*
*/
void register_pathloss_handler(reporter_callback_t pathloss_fn);

/**
* @brief function which register the application alerting function for linkloss to the profile
*
* @param[in] call back function of the application for linkloss
*
*/
void register_linkloss_handler(reporter_callback_t linkloss_fn);

/**
* @brief function which register notification callback on BLE connection update
*
* @param[in] call back function of the application for connection_update.
*
*/
void register_conn_update_handler(reporter_callback_t conn_update_fn);
#endif


