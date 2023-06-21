/**
 * \file
 *
 * \brief WiFi Provisioning configuration.
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef WIFI_PROV_H_INCLUDED
#define WIFI_PROV_H_INCLUDED

#include "driver/include/m2m_wifi.h"
#include "driver/include/m2m_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Wi-Fi Settings */
#define PROV_WLAN_SOFTAP_SSID                    "WINC1500_PROV_HTTP" /* < SSID */
#define PROV_WLAN_CHANNEL                        (1) /* < Channel number */
#define PROV_WLAN_SSID_MODE                      SSID_MODE_VISIBLE
#if defined USE_WEP
#define PROV_WLAN_AUTH                           M2M_WIFI_SEC_WEP /* < Security manner */
#define PROV_WLAN_WEP_KEY_INDEX                  (1)
#define PROV_WLAN_WEP_SIZE                       WEP_40_KEY_STRING_SIZE
#define PROV_WLAN_WEP_KEY					     "1234567890" /* < Security Key in WEP Mode */
#else
#define PROV_WLAN_AUTH                           M2M_WIFI_SEC_OPEN /* < Security manner */
#endif
#define PROV_WEB_PAGE_WEP_KEY_INDEX				(1)

/** HTTP server defines */
#define HTTP_PORT								 443
#define RX_BUF_SZ							     SOCKET_BUFFER_MAX_LENGTH
#define POST_RESP							     "HTTP/1.1 201"

#define CERT_BUFFER_SIZE			1200
#define KEY_BUFFER_SIZE				1700
#define PRIVATE_KEY_MOD_EXP_SIZE	256

typedef enum {
	TLS = 1,
	MSCHAPV2
}enteprise_sec_method;

typedef struct{
    uint8 au8UserName[21];    // NULL terminated
//  uint8 au8PrivateKey_Mod[PRIVATE_KEY_MOD_EXP_SIZE];
// 	uint8 au8PrivateKey_Exp[PRIVATE_KEY_MOD_EXP_SIZE];
	uint8 au8Certificate[CERT_BUFFER_SIZE];
	uint8 au8KeyBuff[KEY_BUFFER_SIZE];
}tstr1xAuthTLSCredentials;

typedef struct{
	tstrM2MProvisionInfo httpProvParams;
	tstrM2mWifiWepParams httpWepParams;
	enteprise_sec_method sec_method;
	tstr1xAuthCredentials httpMsChapv2Params;
	tstrAuth1xTls httpTLSParams;
}wifiProvisionParams;

extern tstr1xAuthTLSCredentials tlsCredentials;

/**
 * \brief Wi-Fi Provisioning main application function.
 * This is a bocking function that wait for the user to connect to the @ref PROV_WLAN_SOFTAP_SSID
 * and provide the credentials in web page https://192.168.1.1/provisioning.html.
 * The user is expected to close all the open socket and perofrm @ref socketDeinit() and @ref m2m_wifi_deinit
 * before this function is called
 */
void wifi_ap_provision(wifiProvisionParams *provParams);

/**
 * \brief Wi-Fi Provisioning ap connect function.
 * This is a will connect to the AP with the credentials received in @ref wifiProvisionParams
 * The user is expected to perfom @ref m2m_wifi_init() before calling this api.
 */
void wifi_ap_connect(wifiProvisionParams *provParams);

#ifdef __cplusplus
}
#endif

#endif /* WIFI_PROV_H_INCLUDED*/
