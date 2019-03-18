/**
 * \file
 *
 * \brief MAIN configuration.
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

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "driver/include/m2m_wifi.h"

/** Wi-Fi AP Settings. */
#define MAIN_M2M_AP_SEC                      M2M_WIFI_SEC_OPEN
#define MAIN_M2M_AP_WEP_KEY                  "1234567890"
#define MAIN_M2M_AP_SSID_MODE                SSID_MODE_VISIBLE

#define MAIN_HTTP_PROV_SERVER_DOMAIN_NAME    "atmelconfig.com"

#define MAIN_M2M_DEVICE_NAME                 "WINC1500_00:00"
#define MAIN_MAC_ADDRESS                     {0xf8, 0xf0, 0x05, 0x45, 0xD4, 0x84}

/** Using broadcast address for simplicity. */
#define MAIN_SERVER_PORT                    (80)

/** IP address parsing. */
#define IPV4_BYTE(val, index)               ((val >> (index * 8)) & 0xFF)

/** Send buffer of TCP socket. */
#define MAIN_PREFIX_BUFFER                  "GET /data/2.5/weather?q="
#define MAIN_POST_BUFFER                    "&appid=c592e14137c3471fa9627b44f6649db4&mode=xml&units=metric HTTP/1.1\r\nHost: api.openweathermap.org\r\nAccept: */*\r\n\r\n"

/** Weather information provider server. */
#define MAIN_WEATHER_SERVER_NAME            "api.openweathermap.org"

/** Input City Name. */
#define MAIN_CITY_NAME                      "paris"

/** Receive buffer size. */
#define MAIN_WIFI_M2M_BUFFER_SIZE           1400

#define MAIN_HEX2ASCII(x)                   (((x) >= 10) ? (((x) - 10) + 'A') : ((x) + '0'))

static tstrM2MAPConfig gstrM2MAPConfig = {
	MAIN_M2M_DEVICE_NAME, 1, 0, WEP_40_KEY_STRING_SIZE, MAIN_M2M_AP_WEP_KEY, (uint8_t)MAIN_M2M_AP_SEC, MAIN_M2M_AP_SSID_MODE
};

static CONST char gacHttpProvDomainName[] = MAIN_HTTP_PROV_SERVER_DOMAIN_NAME;

static uint8_t gau8MacAddr[] = MAIN_MAC_ADDRESS;
static int8_t gacDeviceName[] = MAIN_M2M_DEVICE_NAME;

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H_INCLUDED */
