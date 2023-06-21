/**
 * \file
 *
 * \brief IoT Cloud Demo.
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

/** Access point configuration for provisioning. */
#define DEMO_WLAN_AP_NAME                               "WINC1500_00:00"
#define DEMO_WLAN_AP_CHANNEL                            M2M_WIFI_CH_11
#define DEMO_WLAN_AP_WEP_INDEX                          (0)
#define DEMO_WLAN_AP_WEP_SIZE                           WEP_40_KEY_STRING_SIZE
#define DEMO_WLAN_AP_WEP_KEY                            "1234567890"
#define DEMO_WLAN_AP_SECURITY                           M2M_WIFI_SEC_OPEN
#define DEMO_WLAN_AP_MODE                               SSID_MODE_VISIBLE
#define DEMO_WLAN_AP_DOMAIN_NAME                        "atmelconfig.com"
#define DEMO_WLAN_AP_IP_ADDRESS                         {192, 168, 1, 1}

/** PubNub Settings. */
#define DEMO_PUBNUB_PUBLISH_KEY                         "demo"
#define DEMO_PUBNUB_SUBSCRIBE_KEY                       "demo"
#define DEMO_PUBNUB_CHANNEL						        "WINC1500_00:00"
#define DEMO_PUBNUB_PUBLISH_INTERVAL                    (3000)
#define DEMO_PUBNUB_SUBSCRIBE_INTERVAL                  (1000)

/** Android App related Settings. */
#define DEMO_ANDROID_REPORT_INTERVAL                    (1000)
#define DEMO_ANDROID_SENSOR_NAME                        "Temp1"
#define DEMO_ANDROID_SERVER_PORT                        (6666)

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H_INCLUDED */
