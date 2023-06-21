/**
 *
 * \file
 *
 * \brief IOT QTouch Sensor Demo.
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef DEMO_H_INCLUDED
#define DEMO_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/** Default SSID and passphrase of the network to connect to. */
#define DEFAULT_SSID						"default"
#define	DEFAULT_PWD							"default"
#define DEFAULT_AUTH						M2M_WIFI_SEC_WPA_PSK
#define DEFAULT_CHANNEL						M2M_WIFI_CH_ALL

/** Sensor name. */
#define DEMO_PRODUCT_NAME					"Touch"

/* Using broadcast address for simplicity. */
#define DEMO_SERVER_IP						"255.255.255.255"
#define DEMO_SERVER_PORT					(6666)
#define DEMO_REPORT_INTERVAL				(100)
#define DEMO_WLAN_AP_IP_ADDRESS				{192,168,1,10}
#define DEMO_WLAN_AP_DOMAIN_NAME			"atmelconfig.com"

#define DEMO_WLAN_AP_NAME					"WINC1500_TOUCH_MyAP"// Access Point Name.
#define DEMO_WLAN_AP_CHANNEL				1// Channel to use.
#define DEMO_WLAN_AP_WEP_INDEX				0// Wep key index.
#define DEMO_WLAN_AP_WEP_SIZE				WEP_40_KEY_STRING_SIZE// Wep key size.
#define DEMO_WLAN_AP_WEP_KEY				"1234567890"// Wep key.
#define DEMO_WLAN_AP_SECURITY				M2M_WIFI_SEC_OPEN// Security mode.
#define DEMO_WLAN_AP_MODE					0 //Visible

#define CREDENTIAL_ENTRY_BUTTON				PIN_PA15

void demo_start(void);

#ifdef __cplusplus
}
#endif

#endif /* DEMO_H_INCLUDED */
