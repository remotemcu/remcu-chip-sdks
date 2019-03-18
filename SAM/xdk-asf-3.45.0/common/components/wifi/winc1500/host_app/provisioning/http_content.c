/**
 *
 * \file
 *
 * \brief This module contains WINC1500 Host MCU Provisioning implementation.
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

#include "asf.h"
#include "http_content.h"
#include "html_page_buf.h"
#include <string.h>

/* Response to the post request */
static const char resp_page_html[] =
"<!DOCTYPE html><html><head><title>WINC1500 Provisioning</title></head>"
"<body><h1>WINC1500 Provisioning Completed</h1>"
"</body></html>";

static char not_found_html[]=
"<html><head>"
"<title>404 Not Found</title>"
"</head><body>"
"<h1>Not Found</h1>"
"<p>The requested URL was not found on this WINC1500 server.</p>"
"<p>Try Connecting to <a href=\"https://192.168.1.1/provisioning.html\">WINC1500 Provisioning page</a></p>"
"</body></html>";

static uint16_t content_length = 0, content_recv_sz=0;
static uint8_t http_data_pending_flag = 0;
char *pHttpData, *pHttpDataNext;

static unsigned int get_token_value(const char *buf, const char *tok,
uint8_t *value, const uint16_t max_sz, const char term)
{
	uint8_t i = 0;
	
	/* search for token in string, then advance pointer */
	char *pch = strstr(buf, tok);
	pch += strlen(tok);
	
	/* clear out buffer before parsing credentials */
	memset(value, 0, max_sz);
	
	/* copy credentials into value buffer */
	while (i < (max_sz-1))
	{
		if ((*pch == term) || (*pch == 0)) {break;}
		value[i++] = *pch++;
	}
	
	/* add terminating 'nul' to string */
	value[i] = 0;
	
	return i;
}

static uint16_t get_tls_cert_value(char *buf, const char *tok,
uint8_t *value, unsigned int max_sz, const char *term)
{
	uint32_t pSz = 0;
	
	/* clear out buffer before parsing credentials */
	memset(value, 0, max_sz);
	
	/* search for token in string, then advance pointer */
	char *pch = strstr(buf, tok);
	pch += strlen(tok);
	
	char *pEnd = strstr(buf, term);
	pSz = (uint32_t)(pEnd - pch);
	if (pSz <= max_sz)
	{
		m2m_memcpy((uint8 *)value, (uint8 *)pch, pSz);
	}
	else
	{
		printf("Not enough buffer");
		return 0;
	}
	return pSz;
}

static char *get_resp_page(void)
{
	static char resp_page[200];
	char resp_page_header[70];

	sprintf(resp_page_header, "HTTP/1.1 201 OK\r\nContent-type: text/html\r\nContent-length: %d\r\n\r\n", strlen(resp_page_html));
	strcpy(resp_page, resp_page_header );
	strcat(resp_page, resp_page_html);
	return (char *)resp_page;
}

static char *post_main_page(char *req, wifiProvisionParams *provInfo)
{	
	char *pReqPtr;
	char secType[4];
	uint8_t *pBuff;
	uint32_t buffSz =0;
	
	asm("nop");
	/* strip out HTTP headers from response */
	pReqPtr = strstr(req, "NETWNAME_=");
	
	/* parse response for AP credentials */
	get_token_value(pReqPtr, "NETWNAME_=", (uint8_t *)provInfo->httpProvParams.au8SSID,
	WIFI_SSID_LEN, '\r');
	get_token_value(pReqPtr, "SECTYPE_=", (uint8_t *)&secType,
	sizeof(secType), '\r'  );
	provInfo->httpProvParams.u8SecType = atoi((char *)secType);

	if (provInfo->httpProvParams.u8SecType == M2M_WIFI_SEC_802_1X)
	{
		m2m_memset((uint8 *)secType, 0, sizeof(secType));
		get_token_value(pReqPtr, "SECMETHOD_=", (uint8_t *)&secType,
		sizeof(secType), '\r');
		provInfo->sec_method = atoi((char *)secType);
		if (provInfo->sec_method == TLS)
		{
			pBuff = (uint8_t *)&tlsCredentials.au8UserName;
			get_token_value(pReqPtr, "USRNAME_=", (uint8_t *)pBuff, sizeof(tlsCredentials.au8UserName), '\r');
			provInfo->httpTLSParams.pu8UserName = (uint8 *)pBuff;

			pBuff = (uint8_t *)&tlsCredentials.au8Certificate;
			buffSz = get_tls_cert_value(pReqPtr, "CSTR_=", (uint8_t *)pBuff, CERT_BUFFER_SIZE, CERT_FOOTER);
			buffSz = base64decode((char *)pBuff, buffSz);
			provInfo->httpTLSParams.pu8Certificate = pBuff;
			provInfo->httpTLSParams.u16CertificateLen = buffSz;
			
			pBuff = (uint8_t *)&tlsCredentials.au8KeyBuff;
			buffSz = get_tls_cert_value(pReqPtr, "KSTR_", pBuff, KEY_BUFFER_SIZE, KEY_FOOTER);
			buffSz = base64decode((char *)pBuff, buffSz);
			if (*pBuff == 0x30 && *(pBuff+1) == 0x82)
			{
				uint32 offset = 8;

				uint8 modulusLenBytes;
				pBuff += offset;
				uint32 modulusLen = decodeLength(pBuff, &modulusLenBytes);
				pBuff += modulusLenBytes + 1;
				uint8* modulus = pBuff;

				pBuff += 2 + modulusLen;
				uint8 pubExponentLenBytes;
				uint32 pubExponentLen = decodeLength(pBuff, &pubExponentLenBytes);
			
				pBuff += 2 + pubExponentLenBytes + 1 + pubExponentLen;
				uint8 privExponentLenBytes;
				uint32 privExponentLen = decodeLength(pBuff, &privExponentLenBytes);
				pBuff += privExponentLenBytes + 1;
				uint8* privExponent = pBuff;
			
				// Modulus contains an extra 0 byte at the beginning to make sure it's always a positive
				// integer when stored as a signed variable, but we don't want that extra byte for our stuff.
				modulus++;
				modulusLen--;

				if((modulusLen == 64 || modulusLen == 128 || modulusLen == 256) && modulusLen == privExponentLen)
				{
					provInfo->httpTLSParams.pu8PrivateKey_Mod = modulus;
					provInfo->httpTLSParams.pu8PrivateKey_Exp = privExponent;
					provInfo->httpTLSParams.u16PrivateKeyLen = privExponentLen;
				}
				else
				{
					printf("Bad private key file format (unsupported modulus or private key length)!\r\n");
				}
			}
			else
			{
				printf("Bad private key file format!\r\n");
			}

		}
		else if (provInfo->sec_method == MSCHAPV2)
		{
			get_token_value(pReqPtr, "USRNAME_=", (uint8_t *)provInfo->httpMsChapv2Params.au8UserName ,
			sizeof(provInfo->httpMsChapv2Params.au8UserName), '\r');
			get_token_value(pReqPtr, "PASSPHRASE_=", (uint8_t *)provInfo->httpMsChapv2Params.au8Passwd ,
			sizeof(provInfo->httpMsChapv2Params.au8Passwd), '\r');			
		}
	} else {
		get_token_value(pReqPtr, "PASSPHRASE_=", (uint8_t *)provInfo->httpProvParams.au8Password,
		WIFI_PASSPHRASE_LEN, '\r');
	}

	return (char *)get_resp_page();	
}

static char *not_found_html_page(char *req)
{
	static char not_found_page[500];
	static char not_found_header[80];

	sprintf(not_found_header, "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nContent-Length: %d\r\n\r\n", strlen(not_found_html));
	strcpy(not_found_page,not_found_header );
	strcat(not_found_page, not_found_html);
	return (char *)not_found_page;
}

static char *find_req_name(char *req, char *name){
	while (*req && *req != '/') {
		req++;	
	}
	if (!*req) {
		return 0;
	}
	req++;
	while (*req && *req != ' ') {
		*name++ = *req++;
	}
	*name = 0;
	return req;
}

uint16_t get_content_length(char *req)
{
	char *pReqPtr;
	char content_length_asci[6];
	uint16_t c_len = 0;

	/* strip out HTTP headers from response */
	pReqPtr = strstr(req, "Content-Length: ");
	get_token_value(pReqPtr, "Content-Length: ", (uint8_t *)content_length_asci,6, '\r');
	c_len = atoi(content_length_asci);
	return c_len;
}

char *construct_http_response(int cid, char *req, int16_t req_sz, int16_t *rsp_sz, wifiProvisionParams *provInfo)
{
	char name[32];
	char *http_data;
	*rsp_sz = 0;
	if (!strncmp(req, "GET", 3))
	{
		find_req_name(req, name);
		if (!strcmp(name, "provisioning.html"))
		{
			*rsp_sz = sizeof(html_buff);
			return (char *)html_buff;
		}
		else if (!strcmp(name, "logo.png"))
		{
			*rsp_sz = sizeof(logo_buff);
			return (char *)logo_buff;
		}
		else
		{
			return not_found_html_page(req);
		}
	}
	else if (!strncmp(req, "POST", 4))
	{
		char *rem = find_req_name(req, name);
		if (!strcmp(name, "s_index.html"))
		{
			content_length = get_content_length(req);
			http_data = strstr(req,"\r\n\r\n");
			http_data = http_data + strlen("\r\n\r\n");
			content_recv_sz = strlen(http_data);
			if (content_length <= content_recv_sz)
			{
				return post_main_page(rem, provInfo);
			}
			else if (http_data_pending_flag == false)
			{
				http_data_pending_flag = true;
				pHttpData = (char *)malloc(content_length);
				m2m_memcpy((uint8 *)pHttpData, (uint8 *)http_data, (uint32_t)content_recv_sz);
				pHttpDataNext = pHttpData+content_recv_sz;
			}
		}
	}
	else if (http_data_pending_flag == true)
	{
		if(content_length > content_recv_sz)
		{
			m2m_memcpy((uint8 *)pHttpDataNext, (uint8 *)req, (uint32_t)req_sz);
			content_recv_sz += req_sz;
			pHttpDataNext = pHttpDataNext + req_sz;
			if (content_length <= content_recv_sz)
			{
				http_data_pending_flag = false;
				post_main_page(pHttpData, provInfo);
				free(pHttpData);
				return (char *)get_resp_page();
			}
		}
		else
		{
			// To Do: unprocessed data??
			printf("*****Some Data received****\r\n");
			printf("%s",req);
		}
	}
	return 0;
}
