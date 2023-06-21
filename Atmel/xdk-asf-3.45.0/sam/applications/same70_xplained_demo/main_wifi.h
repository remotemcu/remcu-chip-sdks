/**
 * \file
 *
 * \brief MAIN configuration.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

/** Using broadcast address for simplicity. */
#define MAIN_SERVER_PORT                (80)

/** Using IP address. */
#define IPV4_BYTE(val, index)           ((val >> (index * 8)) & 0xFF)

/** Send buffer of TCP socket. */
#define MAIN_PREFIX_BUFFER              "GET /data/2.5/weather?q="
//#define MAIN_PREFIX_BUFFER              "GET /data/2.5/forecast/city?id="
#define MAIN_POST_BUFFER                "&mode=xml&units=metric HTTP/1.1\r\nHost: api.openweathermap.org\r\nAccept: */*\r\n\r\n"

/** Wi-Fi Settings */
#define MAIN_WLAN_SSID        "AVRGUEST" /* < Destination SSID */
#define MAIN_WLAN_AUTH        M2M_WIFI_SEC_WPA_PSK /* < Security manner */
#define MAIN_WLAN_PSK         "MicroController" /* < Password for Destination SSID */

/** Weather information provider server. */
#define MAIN_WEATHER_SERVER_NAME        "api.openweathermap.org"

/** Input City Name. */
#define MAIN_CITY_NAME                  "Shanghai"
#define MAIN_APP_ID                     "&appid=ebea1368f9a2bdd172f7115ff8d0371d"
//#define MAIN_APP_ID                     "&appid=2de143494c0b295cca9337e1e96b00e0"

/** Receive buffer size. */
#define MAIN_WIFI_M2M_BUFFER_SIZE       1024

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H_INCLUDED */
