/**
 * \file
 *
 * \brief BLE Battery Service Application Declarations
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
#ifndef __BATTERY_APP_H__
#define __BATTERY_APP_H__

#include <asf.h>
//#include "ble_manager.h"
#include "at_ble_api.h"

#define M2M_DEVICE_NAME				"WINC3400_00:00"
#define MAC_ADDRESS					{0xf8, 0xf0, 0x05, 0x45, 0xD4, 0x84}
/***********************************************************************
* DEFAULT SSID CREDENTIALS CONFIGURATIONS OF THE PEER ACCESS POINT *
************************************************************************/
#define DEFAULT_SSID				"DEMO_AP"
#define DEFAULT_AUTH				M2M_WIFI_SEC_WPA_PSK
#define	DEFAULT_KEY					"12345678"

#define WEP_KEY_INDEX				M2M_WIFI_WEP_KEY_INDEX_1
#define WEP_KEY						"1234567890"
#define WEP_KEY_SIZE				sizeof(WEP_KEY)


#define WEP_CONN_PARAM     { WEP_KEY_INDEX, WEP_KEY_SIZE, WEP_KEY}

#define AUTH_CREDENTIALS   { M2M_802_1X_USR_NAME, M2M_802_1X_PWD }

// Allows the main app to initialise the profile app including
// initialising services and callbacks
void ble_bat_init(void);
// Update the service about battery status
//void ble_batt_process(void);
void ble_bat_process_event(at_ble_events_t event, at_ble_event_parameter_t* params);
#endif /* __BATTERY_APP_H__ */