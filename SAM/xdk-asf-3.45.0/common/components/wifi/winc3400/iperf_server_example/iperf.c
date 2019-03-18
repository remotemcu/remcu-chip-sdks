/**
 *
 * \file
 *
 * \brief WINC3400 iperf.
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

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "asf.h"
#include "iperf.h"
#include "driver/include/m2m_wifi.h"
#include "socket/include/socket.h"
#include "conf_winc.h"


/** SysTick counter to avoid busy wait delay. */
extern uint32_t ms_ticks;

/** Receive buffer definition. */
static uint8_t gau8SocketTestBuffer[IPERF_WIFI_UDP_BUFFER_SIZE];

/** Socket for TCP communication */
static SOCKET tcp_server_socket = -1;
static SOCKET tcp_client_socket = -1;

/** Socket for UDP communication */
static SOCKET udp_server_socket = -1;
static SOCKET udp_client_socket = -1;
uint32_t udp_r_opt = 0;
int32_t udp_id = 0;

/** Wi-Fi connection state */
static volatile uint8_t wifi_connected;

static uint32_t iperf_connected = 0, tcp_tx_on = 0;

static struct client_hdr iperf;

struct sockaddr_in tcp_client_addr;
struct sockaddr_in udp_client_addr;



static uint32_t start_time;

struct iperf_stats stats;

/**
 * \brief Prints a float variable with max numbers after decimal.
 *
 * \param f float
 * \param max uint32_t 
 * \return void
 */
static void print_float(float f, uint32_t max)
{
	uint32_t i = 0;
	uint32_t smax = max;
	
	i = (uint32_t)f;
	printf("%d.", (int)i);
	f -= i;
	while (f >= 0.0 && max--) {
		f *= 10;
		i = (uint32_t)f;
		printf("%d", (int)i);				
		f -= i;
	}
	if (smax == max) {
		printf("0");
	}
}

/**
 * \brief Convert an u32_t from host to network byte order.
 *
 * \param n uint32_t in host byte order
 * \return n in network byte order
 */
static uint32_t ntohl(uint32_t n)
{
  return ((n & 0xff) << 24) | ((n & 0xff00) << 8) | ((n & 0xff0000UL) >> 8) | ((n & 0xff000000UL) >> 24);
}

/**
 * \brief Callback to get the Data from socket.
 *
 * \param[in] sock socket handler.
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
static void iperf_socket_handler(SOCKET sock, uint8_t u8Msg, void *pvMsg)
{
	switch (u8Msg) {

		case SOCKET_MSG_BIND:
		{
			tstrSocketBindMsg *pstrBind = (tstrSocketBindMsg *)pvMsg;
			if (pstrBind && pstrBind->status == 0) {
				if (sock == tcp_server_socket) {			
					listen(tcp_server_socket, 0);
				}
				else if (sock == udp_server_socket) {
					recvfrom(udp_server_socket, gau8SocketTestBuffer, IPERF_WIFI_UDP_BUFFER_SIZE, 0);
				}
			} else {
				printf("iperf_socket_handler : bind error!\n");
				while (1);
			}
		}
		break;

		case SOCKET_MSG_LISTEN:
		{
			tstrSocketListenMsg *pstrListen = (tstrSocketListenMsg *)pvMsg;
			if (pstrListen && pstrListen->status == 0) {
				printf("------------------------------------------------------------\r\n");
				printf("Server listening on TCP/UDP port 5001\r\n");
				printf("TCP window size: ??? KByte\r\n");
				printf("------------------------------------------------------------\r\n");
				accept(tcp_server_socket, NULL, 0);
			} else {
				printf("iperf_socket_handler : listen error!\n");
				while (1);
			}
		}
		break;

		case SOCKET_MSG_ACCEPT:
		{
			tstrSocketAcceptMsg *pstrAccept = (tstrSocketAcceptMsg *)pvMsg;
			if (pstrAccept) {
				accept(tcp_server_socket, (struct sockaddr *)&pstrAccept->strAddr, NULL);
				tcp_client_socket = pstrAccept->sock;
				printf("[  %d] local 127.0.0.1 port %d connected with %lu.%lu.%lu.%lu port ??\n", (int) tcp_client_socket, pstrAccept->strAddr.sin_port,
						(pstrAccept->strAddr.sin_addr.s_addr & 0xFF), (pstrAccept->strAddr.sin_addr.s_addr & 0xFF00) >> 8,
						(pstrAccept->strAddr.sin_addr.s_addr & 0xFF0000) >> 16, (pstrAccept->strAddr.sin_addr.s_addr & 0xFF000000) >> 24);
				recv(tcp_client_socket, gau8SocketTestBuffer, sizeof(gau8SocketTestBuffer), 0);
				iperf_connected = 1;
			
				/* Prepare server for TX stage if any. */
				tcp_client_addr.sin_family = AF_INET;
				tcp_client_addr.sin_port = _htons(IPERF_WIFI_M2M_SERVER_PORT);
				tcp_client_addr.sin_addr.s_addr = pstrAccept->strAddr.sin_addr.s_addr;
			} else {
				printf("iperf_socket_handler : accept error!\n");
				while (1);
			}
		}
		break;

		case SOCKET_MSG_RECV:
		{
			tstrSocketRecvMsg *pstrRecv = (tstrSocketRecvMsg *)pvMsg;
		
			/* Check EOF. */
			if (pstrRecv == 0 || (pstrRecv && pstrRecv->s16BufferSize <= 0)) {
				close(tcp_client_socket);
				iperf_connected = 0;
								
				/* Prepare TX test if demanded (-r option). */
				if (ntohl(iperf.flags) & HEADER_VERSION1) {
					printf("------------------------------------------------------------\r\n");
					printf("Client connecting to %lu.%lu.%lu.%lu, TCP port 5001\r\n",
					(tcp_client_addr.sin_addr.s_addr & 0xFF), (tcp_client_addr.sin_addr.s_addr & 0xFF00) >> 8,
					(tcp_client_addr.sin_addr.s_addr & 0xFF0000) >> 16, (tcp_client_addr.sin_addr.s_addr & 0xFF000000) >> 24);
					printf("TCP window size: ??? KByte\r\n");
					printf("------------------------------------------------------------\r\n");
									
					if ((tcp_client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
						printf("iperf_socket_handler : failed to create TCP client socket error!\n");
						while (1);
					}
					m2m_wifi_handle_events(NULL);
					
					if (connect(tcp_client_socket, (struct sockaddr *)&tcp_client_addr, sizeof(struct sockaddr_in)) < 0) {
						printf("iperf_socket_handler : failed to create TCP client socket error!\n");
						while (1);
					}
				}
				else {
					printf("[  %d] done\n", (int) tcp_client_socket);
					tcp_client_socket = -1;
				}
				break;
			}

			/* Check iperf options in first packet only. */
			if (iperf_connected == 1) {
				memcpy(&iperf, gau8SocketTestBuffer, sizeof(struct client_hdr));
				/*printf("flags: %d\n", ntohl(iperf.flags));
				printf("numThreads: %d\n", ntohl(iperf.numThreads));
				printf("mPort: %d\n", ntohl(iperf.mPort));
				printf("bufferlen: %d\n", ntohl(iperf.bufferlen));
				printf("mWinBand: %d\n", ntohl(iperf.mWinBand));
				printf("mAmount: %d\n", ntohl(iperf.mAmount));    // To read actual value:  -mAmount / 100.0; */
				if (ntohl(iperf.flags) & RUN_NOW) {
					// --dualtest not implemented
					printf("iperf_socket_handler: Unsupported options -d, closing connection...\n");
					while (1);
				}
				iperf_connected += 1;
			}
		
			/* Reload data buffer. */
			recv(tcp_client_socket, gau8SocketTestBuffer, sizeof(gau8SocketTestBuffer), 0);
		}
		break;
		
		case SOCKET_MSG_CONNECT:
		{
			tstrSocketConnectMsg *pstrConnect = (tstrSocketConnectMsg *)pvMsg;
			if (pstrConnect && pstrConnect->s8Error >= 0) {
				printf("[  %d] local 127.0.0.1 port ?? connected with %lu.%lu.%lu.%lu port 5001\n", (int) tcp_client_socket,
						(tcp_client_addr.sin_addr.s_addr & 0xFF), (tcp_client_addr.sin_addr.s_addr & 0xFF00) >> 8,
						(tcp_client_addr.sin_addr.s_addr & 0xFF0000) >> 16, (tcp_client_addr.sin_addr.s_addr & 0xFF000000) >> 24);
				start_time = ms_ticks;
				tcp_tx_on = 1;
				send(tcp_client_socket, &gau8SocketTestBuffer, IPERF_WIFI_TCP_BUFFER_SIZE, 0);
			} else {
				printf("iperf_socket_handler: connect error!\n");
				while (1);
			}
		}
		break;

		case SOCKET_MSG_RECVFROM:
		{
			tstrSocketRecvMsg *pstrRx = (tstrSocketRecvMsg *)pvMsg;
			
			if (pstrRx->pu8Buffer && pstrRx->s16BufferSize) {
				struct UDP_datagram *pkt = (void *) gau8SocketTestBuffer;
				int32_t id = ntohl(pkt->id);
				if (id >= 0) {
					if (id == 0) {
						printf("[  %d] local 127.0.0.1 port 5001 connected with %lu.%lu.%lu.%lu port %d\n", (int) udp_server_socket,
								(pstrRx->strRemoteAddr.sin_addr.s_addr & 0xFF), (pstrRx->strRemoteAddr.sin_addr.s_addr & 0xFF00) >> 8,
								(pstrRx->strRemoteAddr.sin_addr.s_addr & 0xFF0000) >> 16, (pstrRx->strRemoteAddr.sin_addr.s_addr & 0xFF000000) >> 24,
								_htons(pstrRx->strRemoteAddr.sin_port));
						udp_client_addr.sin_family = AF_INET;
						udp_client_addr.sin_port = pstrRx->strRemoteAddr.sin_port;
						udp_client_addr.sin_addr.s_addr = pstrRx->strRemoteAddr.sin_addr.s_addr;
						stats.udp_rx_start_sec = ntohl(pkt->tv_sec);
						stats.udp_rx_start_usec = ntohl(pkt->tv_usec);
					}
					if (stats.udp_rx_seq != (uint32_t) id) {
						stats.udp_rx_lost += (uint32_t) id - stats.udp_rx_seq;
						stats.udp_rx_seq = id + 1;
					}
					else {
						stats.udp_rx_total_pkt += 1;
						stats.udp_rx_total_size += pstrRx->s16BufferSize;
						stats.udp_rx_seq += 1;
					}
				}
				else {
					pkt->id = _htonl(-id);
					stats.udp_rx_end_sec = ntohl(pkt->tv_sec);
					stats.udp_rx_end_usec = ntohl(pkt->tv_usec);
					uint32_t time_int = stats.udp_rx_end_sec - stats.udp_rx_start_sec;
					float bytes = (float)(stats.udp_rx_total_size) / (float)(1024 * 1024);
					float bandw = (float)(stats.udp_rx_total_size * 8) / (float)time_int / (float)(1024 * 1024);
					float ratio = (float)(stats.udp_rx_lost * 100) / (float)stats.udp_rx_seq;
					printf("[  %d]  0.0-%u.0 sec    ", (int) udp_server_socket, (unsigned int)time_int);
					print_float(bytes, 2);
					printf(" Mbytes    ");
					print_float(bandw, 2);
					printf(" Mbits/sec    %lu/ %lu (", stats.udp_rx_lost, stats.udp_rx_seq);
					print_float(ratio, 6);
					printf("%%)\n");

					/* Send report to client. NOT WORKING - WINC1500 too busy handling RX pkts. */
					struct server_hdr *hdr = (struct server_hdr *)(pkt + 1);
					if (ntohl(hdr->flags) & HEADER_VERSION1) {
						printf("------------------------------------------------------------\r\n");
						printf("Client connecting to %lu.%lu.%lu.%lu, UDP port 5001\r\n",
						(udp_client_addr.sin_addr.s_addr & 0xFF), (udp_client_addr.sin_addr.s_addr & 0xFF00) >> 8,
						(udp_client_addr.sin_addr.s_addr & 0xFF0000) >> 16, (udp_client_addr.sin_addr.s_addr & 0xFF000000) >> 24);
						printf("Sending %d byte datagrams\r\n", IPERF_WIFI_TCP_BUFFER_SIZE);
						printf("------------------------------------------------------------\r\n");
						printf("[  %d] local 127.0.0.1 port ??? connected with %lu.%lu.%lu.%lu port 5001\n", (int) udp_client_socket,
								(pstrRx->strRemoteAddr.sin_addr.s_addr & 0xFF), (pstrRx->strRemoteAddr.sin_addr.s_addr & 0xFF00) >> 8,
								(pstrRx->strRemoteAddr.sin_addr.s_addr & 0xFF0000) >> 16, (pstrRx->strRemoteAddr.sin_addr.s_addr & 0xFF000000) >> 24);
						udp_r_opt = 1;
						udp_id = 0;
						start_time = ms_ticks;
					}
					else {
						printf("[  %d] done. (reset board for further test)\n", (int) udp_server_socket);
					}
					/*hdr->flags        = _htonl( HEADER_VERSION1 );
					hdr->total_len1   = _htonl( (long) 0);
					hdr->total_len2   = _htonl( (long) (stats.udp_rx_total_size) );
					hdr->stop_sec     = _htonl( (long) 0);
					hdr->stop_usec    = _htonl( (long) 0);
					hdr->error_cnt    = _htonl( stats.udp_rx_lost );
					hdr->outorder_cnt = _htonl( 0 );
					hdr->datagrams    = _htonl( stats.udp_rx_total_pkt );
					hdr->jitter1      = _htonl( (long) 0 );
					hdr->jitter2      = _htonl( (long) 0 );
					sendto(udp_client_socket, &gau8SocketTestBuffer, 500, 0,
							(struct sockaddr *)&udp_client_addr, sizeof(udp_client_addr));*/
					
					udp_client_addr.sin_port = _htons(IPERF_WIFI_M2M_SERVER_PORT);
					break;
				}
				recvfrom(udp_server_socket, gau8SocketTestBuffer, sizeof(gau8SocketTestBuffer), 0);
			}
		}


		default:
			break;
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
static void iperf_wifi_cb(uint8_t u8MsgType, void *pvMsg)
{
	switch (u8MsgType) {
	case M2M_WIFI_RESP_CON_STATE_CHANGED:
	{
		tstrM2mWifiStateChanged *pstrWifiState = (tstrM2mWifiStateChanged *)pvMsg;
		if (pstrWifiState->u8CurrState == M2M_WIFI_CONNECTED) {
			printf("iperf_wifi_cb: M2M_WIFI_RESP_CON_STATE_CHANGED: CONNECTED\n");
			m2m_wifi_request_dhcp_client();
		} else if (pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED) {
			printf("iperf_wifi_cb: M2M_WIFI_RESP_CON_STATE_CHANGED: DISCONNECTED\n");
			wifi_connected = 0;
			m2m_wifi_connect((char *)IPERF_WIFI_M2M_WLAN_SSID, sizeof(IPERF_WIFI_M2M_WLAN_SSID),
				IPERF_WIFI_M2M_WLAN_AUTH, (char *)IPERF_WIFI_M2M_WLAN_PSK, M2M_WIFI_CH_ALL);
		}
	}
	break;

	case M2M_WIFI_REQ_DHCP_CONF:
	{
		uint8_t *pu8IPAddress = (uint8_t *)pvMsg;
		wifi_connected = 1;
		printf("iperf_wifi_cb: M2M_WIFI_REQ_DHCP_CONF: IP is %u.%u.%u.%u\n",
				pu8IPAddress[0], pu8IPAddress[1], pu8IPAddress[2], pu8IPAddress[3]);
	}
	break;

	default:
		break;
	}
}

/**
 * \brief iPerf main function.
 */
void iperf_start(void)
{
	tstrWifiInitParam param;
	int8_t ret;
	struct sockaddr_in addr;
	struct UDP_datagram *pkt = (void *) gau8SocketTestBuffer;

	/* Initialize the BSP. */
	nm_bsp_init();

	/* Initialize socket address structure. */
	addr.sin_family = AF_INET;
	addr.sin_port = _htons(IPERF_WIFI_M2M_SERVER_PORT);
	addr.sin_addr.s_addr = 0;

	/* Initialize WINC1500 Wi-Fi driver with data and status callbacks. */
	param.pfAppWifiCb = iperf_wifi_cb;
	ret = m2m_wifi_init(&param);
	if (M2M_SUCCESS != ret) {
		printf("iperf_start: m2m_wifi_init call error!\r\n");
		while (1);
	}

	/* Initialize socket module */
	socketInit();
	registerSocketCallback(iperf_socket_handler, NULL);

	/* Connect to router. */
	m2m_wifi_connect((char *)IPERF_WIFI_M2M_WLAN_SSID, sizeof(IPERF_WIFI_M2M_WLAN_SSID),
			IPERF_WIFI_M2M_WLAN_AUTH, (char *)IPERF_WIFI_M2M_WLAN_PSK, M2M_WIFI_CH_ALL);

	memset(&stats, 0, sizeof(stats));

	while (1) {
		/* Handle pending events from network controller. */
		m2m_wifi_handle_events(NULL);

		if (wifi_connected == M2M_WIFI_CONNECTED) {

			/* Open TCP server socket */
			if ((int)tcp_server_socket < 0) {
				if ((tcp_server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
					printf("iperf_start : failed to create TCP server socket error!\n");
					continue;
				}
				bind(tcp_server_socket, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
			}

			/* Open UDP server socket */
			if ((int)udp_server_socket < 0) {
				if ((udp_server_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
					printf("iperf_start : failed to create UDP server socket error!\n");
					continue;
				}
				bind(udp_server_socket, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
			}
			
			/* Open UDP client socket */
			if ((int)udp_client_socket < 0) {
				uint32 u32EnableCallbacks = 0;
				if ((udp_client_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
					printf("iperf_start : failed to create UDP client socket error!\n");
					continue;
				}
				setsockopt(udp_client_socket, SOL_SOCKET, SO_SET_UDP_SEND_CALLBACK, &u32EnableCallbacks, 0);
			}
			
			/* Handle UDP TX test. */
			if (udp_r_opt) {
				if (ms_ticks - start_time < IPERF_WIFI_M2M_TX_TIME) {
					pkt->id = ntohl(udp_id);
					sendto(udp_client_socket, &gau8SocketTestBuffer, IPERF_WIFI_TCP_BUFFER_SIZE, 0,
							(struct sockaddr *)&udp_client_addr, sizeof(udp_client_addr));
					udp_id += 1;
				}
				else {
					/* Send end of test 10 times to make sure remote host receives it. */
					udp_id = -udp_id;
					udp_r_opt = 0;
					for (uint32_t i = 0; i < 10; ++i) {
						sendto(udp_client_socket, &gau8SocketTestBuffer, IPERF_WIFI_TCP_BUFFER_SIZE, 0,
							(struct sockaddr *)&udp_client_addr, sizeof(udp_client_addr));
						m2m_wifi_handle_events(NULL);
					}
					printf("[  %d] done. (reset board for further test)\n", (int) udp_client_socket);
				}
			}

			/* Handle TCP TX Test. */
			if (tcp_tx_on) {
				if (ms_ticks - start_time < IPERF_WIFI_M2M_TX_TIME)
				{
					send(tcp_client_socket, &gau8SocketTestBuffer, IPERF_WIFI_TCP_BUFFER_SIZE, 0);
				} else {
					printf("[  %d] done\n", (int) tcp_client_socket);
					close(tcp_client_socket);
					tcp_client_socket = -1;
					tcp_tx_on = 0;
				}
			}
		}
	}
}
