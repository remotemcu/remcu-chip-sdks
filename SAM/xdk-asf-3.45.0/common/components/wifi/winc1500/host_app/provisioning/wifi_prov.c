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
#include "wifi_prov.h"
#include "http_content.h"
#include "socket/include/socket.h"
#include "driver/include/m2m_wifi.h"
#include <string.h>

/** HTTP server globals */
static uint8_t rx_buf[RX_BUF_SZ];
tstr1xAuthTLSCredentials tlsCredentials;

/** Main app status */
typedef enum {
	APP_PROV_INIT,
	APP_PROV_WINC_CONNECTED,
	APP_PROV_START,
	APP_PROV_END,
	APP_PROV_AP_DISABLE,
	APP_PROV_DEINIT,
	APP_PROV_IDLE,
} prov_app_status;

wifiProvisionParams *httpProvInfo;

static volatile prov_app_status gu8AppStatus = APP_PROV_INIT;

/** Socket for TCP communication */
static SOCKET http_server_socket = -1;
static SOCKET tcp_client_socket  = -1;

static void html_handler(SOCKET sock, uint8_t *p, int16_t p_sz, wifiProvisionParams *provInfo)
{
	char *http_rsp;
	int16_t http_rsp_sz;
	http_rsp = construct_http_response(sock, (char *)p, p_sz, &http_rsp_sz, provInfo);
	if (http_rsp)
	{
		/* send response to HTTP GET or POST */
		if (!http_rsp_sz)
		{
			http_rsp_sz = strlen(http_rsp);
		}
		while (http_rsp_sz >=0)
		{		
			if (http_rsp_sz < SOCKET_BUFFER_MAX_LENGTH)
			{
				send(sock, http_rsp, http_rsp_sz, 0);
				break;
			}
			else
			{
				send(sock, http_rsp, SOCKET_BUFFER_MAX_LENGTH, 0);
				http_rsp_sz -= SOCKET_BUFFER_MAX_LENGTH;
				http_rsp = http_rsp + SOCKET_BUFFER_MAX_LENGTH;
			}
		}
	}
	
	/* did POST contain provision credentials? */
	if (!memcmp(http_rsp, POST_RESP, strlen(POST_RESP)))
	{
		printf("Credentials received...\r\n");
		
		gu8AppStatus = APP_PROV_END;
	}
}

/**
 * \brief Callback to get the Data from socket.
 *
 * \param[in] sock socFket handler.
 * \param[in] u8Msg socket event type. Possible values are:
 *  - SOCKET_MSG_BIND
 *  - SOCKET_MSG_LISTEN
 *  - SOCKET_MSG_ACCEPT
 *  - SOCKET_MSG_CONNECT
 *  - SOCKET_MSG_RECV
 *  - SOCKET_MSG_SEND
 *  - SOCKET_MSG_SENDTO
 *  - SOCKET_MSG_RECVFROM
 * \param[in] pvMsg is a pointer to message structure. Existing types are:
 *  - tstrSocketBindMsg
 *  - tstrSocketListenMsg
 *  - tstrSocketAcceptMsg
 *  - tstrSocketConnectMsg
 *  - tstrSocketRecvMsg
 */
static void prov_socket_cb(SOCKET sock, uint8_t u8Msg, void *pvMsg)
{
	switch (u8Msg) 
	{
		/* Socket bind */
		case SOCKET_MSG_BIND:
		{
			tstrSocketBindMsg *pstrBind = (tstrSocketBindMsg *)pvMsg;
			
			if (pstrBind && pstrBind->status == 0) 
			{
				printf("prov_socket_cb: bind success!\r\n");
				printf("Open webpage https://192.168.1.1/provisioning.html \r\n");
				listen(http_server_socket, 5);
			}
		}
		break;

		/* Socket listen */
		case SOCKET_MSG_LISTEN:
		{
			tstrSocketListenMsg *pstrListen = (tstrSocketListenMsg *)pvMsg;
			
			if (pstrListen && pstrListen->status == 0) 
			{
				/* accept client connection */
				accept(http_server_socket, NULL, NULL);
			}
		}
		break;

		/* Connect accept */
		case SOCKET_MSG_ACCEPT:
		{
			tstrSocketAcceptMsg *pstrAccept = (tstrSocketAcceptMsg *)pvMsg;
			
			if (pstrAccept && (pstrAccept->sock >= 0) /*&& tcp_client_socket < 0*/)
			{
				tcp_client_socket = pstrAccept->sock;
				
				/* receive HTTP request */
				recv(tcp_client_socket, rx_buf, sizeof(rx_buf), 0);
			}
		}
		break;

		/* Message receive */
		case SOCKET_MSG_RECV:
		{
			tstrSocketRecvMsg *msg = (tstrSocketRecvMsg *)pvMsg;
			if (msg->s16BufferSize > 0)
			{
				/* respond to HTTP GET or POST */
				html_handler(sock, msg->pu8Buffer, msg->s16BufferSize, httpProvInfo);
				recv(sock, rx_buf, sizeof(rx_buf), 0);
			}
		}
		break;
		
		/* Message send */
		case SOCKET_MSG_SEND:
		{
			/* prepare buffer for next receive */
			recv(sock, rx_buf, sizeof(rx_buf), 0);
		}
		break;

		default:
		{
			break;
		}
	}
}

/**
 * \brief Callback to get the Wi-Fi status update.
 *
 * \param[in] u8MsgType type of Wi-Fi notification. Possible types are:
 *  - [M2M_WIFI_RESP_CURRENT_RSSI](@ref M2M_WIFI_RESP_CURRENT_RSSI)
 *  - [M2M_WIFI_RESP_CON_STATE_CHANGED](@ref M2M_WIFI_RESP_CON_STATE_CHANGED)
 *  - [M2M_WIFI_RESP_CONNTION_STATE](@ref M2M_WIFI_RESP_CONNTION_STATE)
 *  - [M2M_WIFI_RESP_SCAN_DONE](@ref M2M_WIFI_RESP_SCAN_DONE)
 *  - [M2M_WIFI_RESP_SCAN_RESULT](@ref M2M_WIFI_RESP_SCAN_RESULT)
 *  - [M2M_WIFI_REQ_WPS](@ref M2M_WIFI_REQ_WPS)
 *  - [M2M_WIFI_RESP_IP_CONFIGURED](@ref M2M_WIFI_RESP_IP_CONFIGURED)
 *  - [M2M_WIFI_RESP_IP_CONFLICT](@ref M2M_WIFI_RESP_IP_CONFLICT)
 *  - [M2M_WIFI_RESP_P2P](@ref M2M_WIFI_RESP_P2P)
 *  - [M2M_WIFI_RESP_AP](@ref M2M_WIFI_RESP_AP)
 *  - [M2M_WIFI_RESP_CLIENT_INFO](@ref M2M_WIFI_RESP_CLIENT_INFO)
 * \param[in] pvMsg A pointer to a buffer containing the notification parameters
 * (if any). It should be casted to the correct data type corresponding to the
 * notification type. Existing types are:
 *  - tstrM2mWifiStateChanged
 *  - tstrM2MWPSInfo
 *  - tstrM2MP2pResp
 *  - tstrM2MAPResp
 *  - tstrM2mScanDone
 *  - tstrM2mWifiscanResult
 */
static void prov_wifi_cb(uint8_t u8MsgType, void *pvMsg)
{
	switch (u8MsgType) 
	{
		case M2M_WIFI_RESP_CON_STATE_CHANGED:
		{
			tstrM2mWifiStateChanged *pstrWifiState = (tstrM2mWifiStateChanged *)pvMsg;
		
			if (pstrWifiState->u8CurrState == M2M_WIFI_CONNECTED) 
			{
				printf("prov_wifi_cb: M2M_WIFI_RESP_CON_STATE_CHANGED: CONNECTED\r\n");
				gu8AppStatus = APP_PROV_WINC_CONNECTED;
			} 
			else if (pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED) 
			{
				printf("prov_wifi_cb: M2M_WIFI_RESP_CON_STATE_CHANGED: DISCONNECTED\r\n");
				if (gu8AppStatus == APP_PROV_AP_DISABLE)
				{
					gu8AppStatus = APP_PROV_DEINIT;
				}
			}
		}
		break;

		case M2M_WIFI_REQ_DHCP_CONF:
		{
			uint8_t *pu8IPAddress = (uint8_t *)pvMsg;
			printf("prov_wifi_cb: M2M_WIFI_REQ_DHCP_CONF: IP is %u.%u.%u.%u\r\n",
			pu8IPAddress[0], pu8IPAddress[1], pu8IPAddress[2], pu8IPAddress[3]);
		}
		break;

		default:
		{
			printf("In prov_wifi_cb() default case");
			break;
		}
	}
}

/**
 * \brief Wi-Fi Provisioning ap connect function.
 * This is a will connect to the AP with the credentials received in @ref wifiProvisionParams
 * The user is expected to perfom @ref m2m_wifi_init() before calling this api.
 */
void wifi_ap_connect(wifiProvisionParams *provParams)
{
	if (provParams->httpProvParams.u8SecType == M2M_WIFI_SEC_OPEN)
	{
		m2m_wifi_connect((char *)provParams->httpProvParams.au8SSID, strlen((char *)provParams->httpProvParams.au8SSID),
		provParams->httpProvParams.u8SecType, NULL, M2M_WIFI_CH_ALL);
	}
	else if (provParams->httpProvParams.u8SecType == M2M_WIFI_SEC_WPA_PSK)
	{
		printf("WPA2-PSK - Connecting to %s...\r\n",provParams->httpProvParams.au8SSID);
		m2m_wifi_connect((char *)provParams->httpProvParams.au8SSID, strlen((char *)provParams->httpProvParams.au8SSID),
		provParams->httpProvParams.u8SecType, (char *)provParams->httpProvParams.au8Password, M2M_WIFI_CH_ALL);
		
	}
	else if (provParams->httpProvParams.u8SecType == M2M_WIFI_SEC_WEP)
	{
		provParams->httpWepParams.u8KeyIndx = PROV_WEB_PAGE_WEP_KEY_INDEX;
		provParams->httpWepParams.u8KeySz = strlen((char *)provParams->httpProvParams.au8Password)+1;
		memcpy(provParams->httpWepParams.au8WepKey, provParams->httpProvParams.au8Password,
		provParams->httpWepParams.u8KeySz);

		m2m_wifi_connect((char *)provParams->httpProvParams.au8SSID,
		strlen((char *)provParams->httpProvParams.au8SSID), provParams->httpProvParams.u8SecType,
		(void *)&provParams->httpWepParams, M2M_WIFI_CH_ALL);
	}
	else if(provParams->httpProvParams.u8SecType == M2M_WIFI_SEC_802_1X)
	{
		if (provParams->sec_method == MSCHAPV2)
		{
			tstrNetworkId networkId;
			tstrAuth1xMschap2 mschapv2_credential;
			printf("Enterprise Security using MSCHAPV2 - Connecting to %s...\r\n",provParams->httpProvParams.au8SSID);

			networkId.pu8Bssid = NULL;
			networkId.pu8Ssid = (uint8 *)provParams->httpProvParams.au8SSID;
			networkId.u8SsidLen = m2m_strlen(provParams->httpProvParams.au8SSID);
			networkId.enuChannel = M2M_WIFI_CH_ALL;
			mschapv2_credential.pu8Domain = NULL;
			mschapv2_credential.pu8UserName = (uint8 *)provParams->httpMsChapv2Params.au8UserName;
			mschapv2_credential.pu8Password = (uint8 *)provParams->httpMsChapv2Params.au8Passwd;
			mschapv2_credential.u16UserNameLen = m2m_strlen(provParams->httpMsChapv2Params.au8UserName);
			mschapv2_credential.u16PasswordLen = m2m_strlen(provParams->httpMsChapv2Params.au8Passwd);
			mschapv2_credential.bUnencryptedUserName = false;
			mschapv2_credential.bPrependDomain = true;

			m2m_wifi_connect_1x_mschap2( WIFI_CRED_SAVE_ENCRYPTED, &networkId, &mschapv2_credential);
		}
		else if (provParams->sec_method == TLS)
		{
			printf("Enterprise Security using TLS - Connecting to %s...\r\n",provParams->httpProvParams.au8SSID);
			tstrNetworkId networkId;
			tstrAuth1xTls tls_credential;
			
			networkId.pu8Bssid = NULL;
			networkId.pu8Ssid = (uint8 *)provParams->httpProvParams.au8SSID;
			networkId.u8SsidLen = m2m_strlen(provParams->httpProvParams.au8SSID);
			networkId.enuChannel = M2M_WIFI_CH_ALL;
			
			tls_credential.pu8Domain = NULL;
			tls_credential.pu8UserName = (uint8 *)provParams->httpTLSParams.pu8UserName;
			tls_credential.pu8PrivateKey_Mod = (uint8 *)provParams->httpTLSParams.pu8PrivateKey_Mod;
			tls_credential.pu8PrivateKey_Exp = (uint8 *)provParams->httpTLSParams.pu8PrivateKey_Exp;
			tls_credential.pu8Certificate = (uint8 *)provParams->httpTLSParams.pu8Certificate;
			tls_credential.u16UserNameLen = m2m_strlen(provParams->httpTLSParams.pu8UserName);
			tls_credential.u16PrivateKeyLen = provParams->httpTLSParams.u16PrivateKeyLen;
			tls_credential.u16CertificateLen = provParams->httpTLSParams.u16CertificateLen;
			tls_credential.bUnencryptedUserName = true;
			tls_credential.bPrependDomain = true;

			m2m_wifi_connect_1x_tls(WIFI_CRED_SAVE_ENCRYPTED, &networkId, &tls_credential);
		}
	}
	else
	{
		printf("Provisioning web page data not received\r\n");
	}
}

/**
 * \brief Wi-Fi Provisioning main application function.
 * This is a bocking function that wait for the user to connect to the @ref PROV_WLAN_SOFTAP_SSID
 * and provide the credentials in web page https://192.168.1.1/provisioning.html.
 * The user is expected to close all the open socket and perofrm @ref socketDeinit() and @ref m2m_wifi_deinit
 * before this function is called
 */
void wifi_ap_provision(wifiProvisionParams *provParams)
{
	int8_t ret;
	struct sockaddr_in addr;
	tstrWifiInitParam param;
	tstrM2MAPConfig strM2MAPConfig;
	
	/* Initialize socket address structure. */
	addr.sin_family = AF_INET;
	addr.sin_port = _htons(HTTP_PORT);
	addr.sin_addr.s_addr = 0;

	/* Initialize Wi-Fi parameters structure. */
	memset((uint8_t *)&param, 0, sizeof(tstrWifiInitParam));

	/* Initialize Wi-Fi driver with data and status callbacks. */
	param.pfAppWifiCb = prov_wifi_cb;
	ret = m2m_wifi_init(&param);
	if (M2M_SUCCESS != ret) {
		printf("main: m2m_wifi_init call error!(%d)\r\n", ret);
		while (1) {}
	}

	socketInit();
	registerSocketCallback(prov_socket_cb, NULL);
  
	/* Initialize AP mode parameters structure with SSID, channel and OPEN security type. */
	memset(&strM2MAPConfig, 0x00, sizeof(tstrM2MAPConfig));
	strcpy((char *)&strM2MAPConfig.au8SSID, PROV_WLAN_SOFTAP_SSID);
	strM2MAPConfig.u8ListenChannel = PROV_WLAN_CHANNEL;
	strM2MAPConfig.u8SecType = PROV_WLAN_AUTH;

	strM2MAPConfig.au8DHCPServerIP[0] = 192;
	strM2MAPConfig.au8DHCPServerIP[1] = 168;
	strM2MAPConfig.au8DHCPServerIP[2] = 1;
	strM2MAPConfig.au8DHCPServerIP[3] = 1;
	//strM2MAPConfig.au8DHCPServerIP = PROV_WLAN_DHCP_SERVER_IP;

#if defined USE_WEP
	strcpy((char *)&strM2MAPConfig.au8WepKey, PROV_WLAN_WEP_KEY);
	strM2MAPConfig.u8KeySz = strlen(PROV_WLAN_WEP_KEY);
	strM2MAPConfig.u8KeyIndx = PROV_WLAN_WEP_KEY_INDEX;
#endif

	httpProvInfo = provParams;
	
	/* Bring up AP mode with parameters structure. */
	ret = m2m_wifi_enable_ap(&strM2MAPConfig);
	if (M2M_SUCCESS != ret) {
		printf("main: m2m_wifi_enable_ap call error!\r\n");
		while (1) {
		}
	}

	printf("AP mode started. You can connect to %s.\r\n", (char *)PROV_WLAN_SOFTAP_SSID);
	
	while (1)
	{
		m2m_wifi_handle_events(NULL);
		if (gu8AppStatus == APP_PROV_WINC_CONNECTED)
		{
			gu8AppStatus = APP_PROV_START;
			if (http_server_socket < 0)
			{
				/* Open TCP (HTTPS) server socket */
				if ((http_server_socket = socket(AF_INET, SOCK_STREAM, SOCKET_FLAGS_SSL)) < 0)
				{
					printf("main: failed to create server socket error!\r\n");
					continue;
				}

				/* Bind service*/
				bind(http_server_socket, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
			} 
		}
		else if (gu8AppStatus == APP_PROV_END)
		{
			/* close all sockets */
			close(tcp_client_socket);
			close(http_server_socket);
			http_server_socket =  -1;
			tcp_client_socket = -1;
					
			/* stop Soft AP mode */
			m2m_wifi_disable_ap();
			
			gu8AppStatus = APP_PROV_AP_DISABLE;
		}
		else if (gu8AppStatus == APP_PROV_DEINIT)
		{
			gu8AppStatus = APP_PROV_IDLE;
			socketDeinit();
			m2m_wifi_deinit(NULL);
			break;
		}
	}
}

