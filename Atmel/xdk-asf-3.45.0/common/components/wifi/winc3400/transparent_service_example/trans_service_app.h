/**
 * \file
 *
 * \brief BLE Transparent Service Application Declarations
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
#ifndef __TRANS_SERVICE_APP_H__
#define __TRANS_SERVICE_APP_H__

#include <asf.h>
//#include "ble_manager.h"
#include "at_ble_api.h"

/****************************************************************************************
*							        Macros	                                     							*
****************************************************************************************/
/**@brief Keypad debounce time */
#define KEY_PAD_DEBOUNCE_TIME	(200)

/**@brief Application maximum transmit buffer size */
#define APP_TX_BUF_SIZE   (150)

/**@brief Enter button press to send data */
#define ENTER_BUTTON_PRESS (13)

/**@brief Entered backspace button */
#define BACKSPACE_BUTTON_PRESS (8)

/**@brief Space bar */
#define SPACE_BAR (32)

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
void ble_trans_service_init(void);

void ble_trans_service_process_event(at_ble_events_t event, at_ble_event_parameter_t* params);

at_ble_status_t ble_trans_update_value_on_btnpress(uint8_t* trans_tx_value, uint8_t len);

void ble_trans_service_send_buf(void);
#endif /* __TRANS_SERVICE_APP_H__ */