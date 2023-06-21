/**
 * \file
 *
 * \brief HTTP File Downloader Configuration
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

#ifndef HTTPDOWNLOADER_H_INCLUDED
#define HTTPDOWNLOADER_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/** Content URI for download. */
//#define MAIN_HTTP_FILE_URL					 "http://www.microchip.com/images/doc7529.pdf"

/** Maximum size for packet buffer. */
#define MAIN_BUFFER_MAX_SIZE				 (1446)
/** Maximum file name length. */
#define MAIN_MAX_FILE_NAME_LENGTH            (250)
/** Maximum file extension length. */
#define MAIN_MAX_FILE_EXT_LENGTH             (8)
/** Output format with '0'. */
#define MAIN_ZERO_FMT(SZ)                    (SZ == 4) ? "%04d" : (SZ == 3) ? "%03d" : (SZ == 2) ? "%02d" : "%d"

typedef enum {
	NOT_READY = 0, /*!< Not ready. */
	STORAGE_READY = 0x01, /*!< Storage is ready. */
	WIFI_CONNECTED = 0x02, /*!< Wi-Fi is connected. */
	GET_REQUESTED = 0x04, /*!< GET request is sent. */
	DOWNLOADING = 0x08, /*!< Running to download. */
	COMPLETED = 0x10, /*!< Download completed. */
	CANCELED = 0x20 /*!< Download canceled. */
} download_state;

int http_downloader(char *);
void setFirmwareDownload(int);

#define SUCCESS							0
#define FAILURE							-1

#ifdef __cplusplus
}
#endif

#endif /* HTTPDOWNLOADER_H_INCLUDED */
