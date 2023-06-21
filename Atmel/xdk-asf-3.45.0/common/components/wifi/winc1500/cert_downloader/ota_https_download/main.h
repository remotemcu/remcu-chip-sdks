/**
 * \file
 *
 * \brief Certificate Downloader via OTA (HTTPS) Example.
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

/** Wi-Fi AP Settings. */
#define MAIN_WLAN_SSID                       "DEMO_AP" /**< Destination SSID */
#define MAIN_WLAN_AUTH                       M2M_WIFI_SEC_WPA_PSK /**< Security manner */
#define MAIN_WLAN_PSK                        "12345678" /**< Password for Destination SSID */

/** IP address parsing. */
#define IPV4_BYTE(val, index)                ((val >> (index * 8)) & 0xFF)

/** Content URI for download. */
#define MAIN_HTTP_FILE_URL                   "https://192.168.43.34/"

#define MAIN_HTTP_PORT_NUMBER                (4443)

/** Maximum size for packet buffer. */
#define MAIN_BUFFER_MAX_SIZE                 (1446)
/** Maximum file name length. */
#define MAIN_MAX_FILE_NAME_LENGTH            (100)
#define CERTIFICATES_BUFFER_SIZE             (6000)

/** No of certificates to be written to WINC **/
#define NUM_OF_ROOT_TLS_CHAIN_CERTIFICATES  5

typedef enum {
	NOT_READY = 0, /*!< Not ready. */
	WIFI_CONNECTED = 0x01, /*!< Wi-Fi is connected. */
    HTTP_DOWNLOAD_INITIATED = 0x02, /*!< Start download is called */
	GET_REQUESTED = 0x04, /*!< GET request is sent. */
	DOWNLOADING = 0x08, /*!< Running to download. */
	COMPLETED = 0x10, /*!< Download completed. */
	CANCELED = 0x20, /*!< Download canceled. */
	ROOT_CERT_DOWNLOAD = 0x40, /*!< Root cert Download. */
	TLS_CERT_DOWNLOAD = 0x80 /*!< TLS cert Download. */
} download_state;

typedef enum {
	ROOT_CERT = 1, 
	TLS_RSA_CERT = 2, 
	TLS_ECC_CERT = 3, 
} cert_type_t;

typedef struct
{
	cert_type_t cert_type;
	uint8_t numOfChainCert;
	uint8_t *filename;
} certFileInfo;

/** Root Certificates to be uploaded */
/** Chain of TLS Certificates and private key to be uploaded */
certFileInfo root_tls_certs_name[NUM_OF_ROOT_TLS_CHAIN_CERTIFICATES]=
{{ROOT_CERT,0,(uint8_t*)"PROWL_Root.cer"},
{ROOT_CERT,0,(uint8_t*)"NMA_Root.cer"},
{TLS_RSA_CERT,2,(uint8_t*)"winc_rsa.key"},
{TLS_RSA_CERT,0,(uint8_t*)"winc_rsa.cer"},
{TLS_RSA_CERT,0,(uint8_t*)"WincRootCA.cer"}
};

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H_INCLUDED */
