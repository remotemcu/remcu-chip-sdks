/**
 * \file
 *
 * \brief MAIN configuration.
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

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/** Wi-Fi Settings */
#define MAIN_WLAN_SSID                          "DEMO_AP" /**< Destination SSID */
#define MAIN_WLAN_AUTH                          M2M_WIFI_SEC_WPA_PSK /**< Security manner */
#define MAIN_WLAN_PSK                           "12345678" /**< Password for Destination SSID */

/** Using NTP server information */
#define MAIN_WORLDWIDE_NTP_POOL_HOSTNAME        "pool.ntp.org"
#define MAIN_ASIA_NTP_POOL_HOSTNAME             "asia.pool.ntp.org"
#define MAIN_EUROPE_NTP_POOL_HOSTNAME           "europe.pool.ntp.org"
#define MAIN_NAMERICA_NTP_POOL_HOSTNAME         "north-america.pool.ntp.org"
#define MAIN_OCEANIA_NTP_POOL_HOSTNAME          "oceania.pool.ntp.org"
#define MAIN_SAMERICA_NTP_POOL_HOSTNAME         "south-america.pool.ntp.org"
#define MAIN_SERVER_PORT_FOR_UDP                (123)
#define MAIN_DEFAULT_ADDRESS                    0xFFFFFFFF /* "255.255.255.255" */
#define MAIN_DEFAULT_PORT                       (6666)
#define MAIN_WIFI_M2M_BUFFER_SIZE               1460

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H_INCLUDED */
