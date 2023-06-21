/**
 * \file
 *
 * \brief http_content configuration.
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

#include "driver/include/m2m_wifi.h"
#include "wifi_prov.h"
#include "bsp/include/nm_bsp.h"

#ifndef HTTP_CONTENT_H_INCLUDED
#define HTTP_CONTENT_H_INCLUDED

#define WIFI_PASSPHRASE_LEN			M2M_MAX_PSK_LEN    //< Maximum length of the passphrase
#define WIFI_SSID_LEN				M2M_MAX_SSID_LEN   //< Maximum length of the SSID

#define CERT_FOOTER					"-----END CERTIFICATE-----"
#define KEY_FOOTER					"-----END RSA PRIVATE KEY-----"

char *construct_http_response(int cid, char *req, int16_t req_sz, int16_t *sz, wifiProvisionParams *provInfo);
uint32 base64decode(char* src, uint32 len);
uint32 decodeLength(uint8* buff, uint8* lenBytes);
uint16_t get_content_length(char *req);

#endif /* HTTP_CONTENT_H_INCLUDED */
