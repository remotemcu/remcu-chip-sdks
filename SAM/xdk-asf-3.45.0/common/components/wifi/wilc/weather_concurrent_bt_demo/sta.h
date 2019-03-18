/**
 *
 * \file
 *
 * \brief STA Task.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/** Wi-Fi Settings - STA mode. */
#define STA_WLAN_SSID                L"DEMO_AP" /* < Destination SSID */
#define STA_WLAN_AUTH                M2M_WIFI_SEC_OPEN/* < Security manner */
#define STA_WLAN_PSK                 L"1234567890" /* < Password for Destination SSID */

/** WEP security setting for STA mode and/or AP mode */
#define WEP_KEY_INDEX            M2M_WIFI_WEP_KEY_INDEX_1
#define WEP_KEY                  "1234567890"
/**< 64 bit WEP key. In case of WEP64, 10 hexadecimal (base 16) characters (0-9 and A-F) ) */
/**< 128 bit WEP key. In case of WEP128, 26 hexadecimal (base 16) characters (0-9 and A-F) ) */
#define WEP_KEY_SIZE             sizeof(WEP_KEY)
#define WEP_AUTH_TYPE            WEP_ANY
#define WEP_CONN_PARAM           {WEP_KEY_INDEX, WEP_KEY_SIZE, WEP_KEY, WEP_AUTH_TYPE}
/* Note : In case of using WEP security on both STA and AP interfaces, the same
password should be used for both interfaces. In addition to that, the same
WEP authentication type (OPEN, SHARED, or ANY) should be used for both
STA and AP interfaces.*/

/** Wi-Fi Settings - AP mode. */
#define AP_WLAN_SSID                L"DEMO_AP" /* < WILC SSID */
#define AP_WLAN_AUTH                M2M_WIFI_SEC_OPEN/* < Security manner M2M_WIFI_SEC_OPEN, M2M_WIFI_SEC_WPA_PSK*/
#define AP_WLAN_PSK                 L"1234567890" /* < Password for WILC SSID */

/** Send buffer of TCP socket. */
#define STA_PREFIX_BUFFER            "GET /data/2.5/weather?q="
#define STA_POST_BUFFER              "&appid=c592e14137c3471fa9627b44f6649db4&mode=xml&units=metric HTTP/1.1\r\nHost: api.openweathermap.org\r\nAccept: */*\r\n\r\n"

/** Weather information provider server. */
#define STA_WEATHER_SERVER_NAME      "api.openweathermap.org"

void sta_task(void *argument);

#ifdef __cplusplus
}
#endif


/***************** Application types *******************/
#define AP_STA_CONCURRENCY  
/* AP and STA Concurrency - standard default configuration */

//#define P2P_AP_CONCURRENCY
//#define P2P_STA_CONCURRENCY
//#define STA_ONLY
//#define AP_ONLY
//#define P2P_ONLY


/***************** Antenna Selection/Diversity Testing *******************/

//#define MAC_ANTENNA_DIVERSITY

#ifdef MAC_ANTENNA_DIVERSITY

/* Antenna Switch mode - {ANTENNA1, ANTENNA2 or DIVERSITY} */
#define ANT_MODE (ANTENNA2)

/* 
 * Antenna GPIO ctrl - {ANT_SWTCH_GPIO_SINLGE, ANT_SWTCH_GPIO_DUAL
 * or ANT_SWTCH_GPIO_NONE} 
 */
#define ANT_SWTCH_GPIO_CTRL_MODE (ANT_SWTCH_GPIO_DUAL)

/* Antenna GPIO configuration */
#define ANTENNA_GPIO_NUM_1	(4)
#define ANTENNA_GPIO_NUM_2	(20)

#endif //MAC_ANTENNA_DIVERSITY
/*************************************************************************/

#endif /* APP_H_INCLUDED */
