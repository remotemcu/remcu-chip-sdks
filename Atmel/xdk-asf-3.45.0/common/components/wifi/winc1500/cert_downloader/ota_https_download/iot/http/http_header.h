/**
 * \file
 *
 * \brief HTTP header definitions.
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

/**
 * \addtogroup sam0_httpc_group
 * @{
 */

#ifndef HTTP_HEADER_H_INCLUDED
#define HTTP_HEADER_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define HTTP_HEADER_ACCEPT       	    ("Accept: ")
#define HTTP_HEADER_ACCEPT_CHARSET   	("Accept-Charset: ")
#define HTTP_HEADER_ACCEPT_ENCODING  	("Accept-Encoding: ")
#define HTTP_HEADER_ACCEPT_LANGUAGE  	("Accept-Language: ")
#define HTTP_HEADER_ACCEPT_RANGES    	("Accept-Ranges: ")
#define HTTP_HEADER_AGE              	("Age: ")
#define HTTP_HEADER_ALLOW	            ("Allow: ")
#define HTTP_HEADER_AUTHORIZATION    	("Authorization: ")
#define HTTP_HEADER_CACHE_CONTROL    	("Cache-Control: ")
#define HTTP_HEADER_CONNECTION       	("Connection: ")
#define HTTP_HEADER_CONTENT_ENCODING 	("Content-Encoding: ")
#define HTTP_HEADER_CONTENT_LANGUAGE 	("Content-Language: ")
#define HTTP_HEADER_CONTENT_LENGTH   	("Content-Length: ")
#define HTTP_HEADER_CONTENT_LOCATION 	("Content-Location: ")
#define HTTP_HEADER_CONTENT_MD5      	("Content-MD5: ")
#define HTTP_HEADER_CONTENT_RANGE        ("Content-Range: ")
#define HTTP_HEADER_CONTENT_TYPE         ("Content-Type: ")
#define HTTP_HEADER_DATE                 ("Date: ")
#define HTTP_HEADER_ETAG                 ("ETag: ")
#define HTTP_HEADER_EXPECT               ("Expect: ")
#define HTTP_HEADER_EXPIRES              ("Expires: ")
#define HTTP_HEADER_FROM                 ("From: ")
#define HTTP_HEADER_HOST                 ("Host: ")
#define HTTP_HEADER_IF_MATCH             ("If-Match: ")
#define HTTP_HEADER_IF_MODIFIED_SINCE	("If-Modified-Since: ")
#define HTTP_HEADER_IF_NONE_MATCH        ("If-None-Match: ")
#define HTTP_HEADER_IF_RANGE             ("If-Range: ")
#define HTTP_HEADER_IF_UNMODIFIED_SINCE	("If-Unmodified-Since: ")
#define HTTP_HEADER_LAST_MODIFIED        ("Last-Modified: ")
#define HTTP_HEADER_LOCATION             ("Location: ")
#define HTTP_HEADER_MAX_FORWARDS         ("Max-Forwards: ")
#define HTTP_HEADER_PRAGMA               ("Pragma: ")
#define HTTP_HEADER_PROXY_AUTHENTICATE	("Proxy-Authenticate: ")
#define HTTP_HEADER_PROXY_AUTHORIZATION  ("Proxy-Authorization: ")
#define HTTP_HEADER_RANGE                ("Range: ")
#define HTTP_HEADER_REFERER              ("Referer: ")
#define HTTP_HEADER_RETRY_AFTER          ("Retry-After: ")
#define HTTP_HEADER_SERVER               ("Server: ")
#define HTTP_HEADER_TE                   ("TE: ")
#define HTTP_HEADER_TRAILER              ("Trailer: ")
#define HTTP_HEADER_TRANSFER_ENCODING	("Transfer-Encoding: ")
#define HTTP_HEADER_UPGRADE              ("Upgrade: ")
#define HTTP_HEADER_USER_AGENT           ("User-Agent: ")
#define HTTP_HEADER_VARY                 ("Vary: ")
#define HTTP_HEADER_VIA                  ("Via: ")
#define HTTP_HEADER_WARNING              ("Warning: ")
#define HTTP_HEADER_WWW_AUTHENTICATE     ("WWW-Authenticate: ")

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* HTTP_HEADER_H_INCLUDED */
