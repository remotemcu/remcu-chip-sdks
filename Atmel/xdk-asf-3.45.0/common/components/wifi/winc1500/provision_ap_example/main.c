/**
 *
 * \file
 *
 * \brief WINC1500 AP provision example.
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

/** \mainpage
 * \section intro Introduction
 * This example demonstrates the use of the WINC1500 with the SAM Xplained Pro
 * board to start Wi-Fi provisioning mode.<br>
 * It uses the following hardware:
 * - the SAM Xplained Pro.
 * - the WINC1500 on EXT1.
 *
 * \section files Main Files
 * - main.c : Initialize the WINC1500 and start Provision Mode.
 *
 * \section usage Usage
 * -# Build the program and download it into the board.
 * -# On the computer, open and configure a terminal application as the follows.
 * \code
 *    Baud Rate : 115200
 *    Data : 8bit
 *    Parity bit : none
 *    Stop bit : 1bit
 *    Flow control : none
 * \endcode
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 * \code
 *    -- WINC1500 AP provision example --
 *    -- SAMD21_XPLAINED_PRO --
 *    -- Compiled: xxx xx xxxx xx:xx:xx --
 *    AP Provision mode started.
 *    On the android device, connect to WINC1500_PROVISION_AP then run setting app.
 *    socket_cb: Ready to listen.
 *    Wi-Fi connected. IP is xxx.xxx.xxx.xxx
 *    socket_cb: Client socket is created.
 *    Disable to AP
 *    Connecting to XXXXXX.
 *    wifi_cb: CONNECTED
 *    Wi-Fi connected. IP is xxx.xxx.xxx.xxx
 * \endcode
 *
 * \section compinfo Compilation Information
 * This software was written for the GNU GCC compiler using Atmel Studio 6.2
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com">Microchip</A>.\n
 */

#include "asf.h"
#include "main.h"
#include <string.h>
#include "common/include/nm_common.h"
#include "driver/include/m2m_wifi.h"
#include "socket/include/socket.h"

#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- WINC1500 AP provision example --"STRING_EOL \
	"-- "BOARD_NAME " --"STRING_EOL	\
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

/** IP address of host. */
uint32_t gu32HostIp = 0;
/** Receive buffer definition. */
static uint8_t gau8SocketTestBuffer[MAIN_WIFI_M2M_BUFFER_SIZE];
/** Socket for TCP communication */
static SOCKET tcp_server_socket = -1;
static SOCKET tcp_client_socket = -1;

/**
 * \brief Configure UART console.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate =		CONF_UART_BAUDRATE,
		.charlength =	CONF_UART_CHAR_LENGTH,
		.paritytype =	CONF_UART_PARITY,
		.stopbits =		CONF_UART_STOP_BITS,
	};

	/* Configure UART console. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief Callback function of TCP client socket.
 *
 * \param[in] sock socket handler.
 * \param[in] u8Msg Type of Socket notification
 * \param[in] pvMsg A structure contains notification informations.
 *
 * \return None.
 */
static void socket_cb(SOCKET sock, uint8_t u8Msg, void *pvMsg)
{
	switch (u8Msg) {
	/* Socket bind */
	case SOCKET_MSG_BIND:
	{
		tstrSocketBindMsg *pstrBind = (tstrSocketBindMsg *)pvMsg;
		if (pstrBind && pstrBind->status == 0) {
			listen(tcp_server_socket, 0);
		} else {
			printf("socket_cb: bind error!\r\n");
			close(tcp_server_socket);
			tcp_server_socket = -1;
		}
	}
	break;

	/* Socket listen */
	case SOCKET_MSG_LISTEN:
	{
		tstrSocketListenMsg *pstrListen = (tstrSocketListenMsg *)pvMsg;
		if (pstrListen && pstrListen->status == 0) {
			printf("socket_cb: Ready to listen.\r\n");
			accept(tcp_server_socket, NULL, NULL);
		} else {
			printf("socket_cb: listen error!\r\n");
			close(tcp_server_socket);
			tcp_server_socket = -1;
		}
	}
	break;

	/* Connect accept */
	case SOCKET_MSG_ACCEPT:
	{
		tstrSocketAcceptMsg *pstrAccept = (tstrSocketAcceptMsg *)pvMsg;
		if (pstrAccept) {
			accept(tcp_server_socket, NULL, NULL);
			tcp_client_socket = pstrAccept->sock;
			printf("socket_cb: Client socket is created.\r\n");
			recv(tcp_client_socket, gau8SocketTestBuffer, sizeof(gau8SocketTestBuffer), 0);
		} else {
			printf("socket_cb: accept error!\r\n");
			close(tcp_server_socket);
			tcp_server_socket = -1;
		}
	}
	break;

	/* Message receive */
	case SOCKET_MSG_RECV:
	{
		tstrSocketRecvMsg *pstrRecv = (tstrSocketRecvMsg *)pvMsg;
		tstrM2mWifiWepParams wep_parameters;
		
		if (pstrRecv && pstrRecv->s16BufferSize > 0) {
			char *p;

			p = strtok((char *)pstrRecv->pu8Buffer, ",");
			if (p != NULL && !strncmp(p, "apply", 5)) {
				char str_ssid[M2M_MAX_SSID_LEN], str_pw[M2M_MAX_PSK_LEN];
				uint8 sec_type = 0;

				p = strtok(NULL, ",");
				if (p) {
					strcpy(str_ssid, p);
				}

				p = strtok(NULL, ",");
				if (p) {
					sec_type = atoi(p);
				}

				p = strtok(NULL, ",");
				if (p) {
					strcpy(str_pw, p);
				}
				if(sec_type == M2M_WIFI_SEC_WEP){
					wep_parameters.u8KeyIndx=1;
					wep_parameters.u8KeySz = strlen(str_pw)+1;
					m2m_memcpy(wep_parameters.au8WepKey,str_pw,wep_parameters.u8KeySz);
				}
				printf("Disable to AP.\r\n");
				m2m_wifi_disable_ap();
				nm_bsp_sleep(500);
				printf("Connecting to %s.\r\n", (char *)str_ssid);
				if(sec_type == M2M_WIFI_SEC_WEP){
					m2m_wifi_connect((char *)str_ssid, strlen((char *)str_ssid), sec_type, &wep_parameters, M2M_WIFI_CH_ALL);
				}
				else
					m2m_wifi_connect((char *)str_ssid, strlen((char *)str_ssid), sec_type, str_pw, M2M_WIFI_CH_ALL);
				break;
			}
		} else {
			printf("socket_cb: recv error!\r\n");
			close(tcp_server_socket);
			tcp_server_socket = -1;
		}

		memset(gau8SocketTestBuffer, 0, sizeof(gau8SocketTestBuffer));
		recv(tcp_client_socket, gau8SocketTestBuffer, sizeof(gau8SocketTestBuffer), 0);
	}
	break;

	default:
		break;
	}
}

/**
 * \brief Callback to get the Wi-Fi status update.
 *
 * \param[in] u8MsgType type of Wi-Fi notification.
 * \param[in] pvMsg A pointer to a buffer containing the notification parameters
 *
 * \return None.
 */
static void wifi_cb(uint8_t u8MsgType, void *pvMsg)
{
	switch (u8MsgType) {
	case M2M_WIFI_RESP_CON_STATE_CHANGED:
	{
		tstrM2mWifiStateChanged *pstrWifiState = (tstrM2mWifiStateChanged *)pvMsg;
		if (pstrWifiState->u8CurrState == M2M_WIFI_CONNECTED) {
			printf("wifi_cb: CONNECTED\r\n");
			m2m_wifi_request_dhcp_client();
		} else if (pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED) {
			printf("wifi_cb: DISCONNECTED\r\n");
		}
	}
	break;

	case M2M_WIFI_REQ_DHCP_CONF:
	{
		uint8_t *pu8IPAddress = (uint8_t *)pvMsg;
		printf("Wi-Fi connected. IP is %u.%u.%u.%u\r\n",
				pu8IPAddress[0], pu8IPAddress[1], pu8IPAddress[2], pu8IPAddress[3]);
	}
	break;

	default:
		break;
	}
}

/**
 * \brief Main application function.
 *
 * Initialize system, UART console, network then start function of TCP socket.
 *
 * \return program return value.
 */
int main(void)
{
	tstrWifiInitParam param;
	int8_t ret;
	struct sockaddr_in addr;
	tstrM2MAPConfig strM2MAPConfig;

	/* Initialize the board. */
	sysclk_init();
	board_init();

	/* Initialize the UART console. */
	configure_console();
	printf(STRING_HEADER);

	/* Initialize the BSP. */
	nm_bsp_init();

	/* Initialize Wi-Fi parameters structure. */
	memset((uint8_t *)&param, 0, sizeof(tstrWifiInitParam));

	/* Initialize Wi-Fi driver with data and status callbacks. */
	param.pfAppWifiCb = wifi_cb;
	ret = m2m_wifi_init(&param);
	if (M2M_SUCCESS != ret) {
		printf("main: m2m_wifi_init call error!(%d)\r\n", ret);
		while (1) {
		}
	}

	/* Initialize socket address structure. */
	addr.sin_family = AF_INET;
	addr.sin_port = _htons((MAIN_WIFI_M2M_SERVER_PORT));
	addr.sin_addr.s_addr = 0;
	/* Initialize Socket module */
	socketInit();
	registerSocketCallback(socket_cb, NULL);

	/* Initialize AP mode parameters structure with SSID, channel and OPEN security type. */
	memset(&strM2MAPConfig, 0x00, sizeof(tstrM2MAPConfig));
	strcpy((char *)&strM2MAPConfig.au8SSID, MAIN_WLAN_SSID);
	strM2MAPConfig.u8ListenChannel = MAIN_WLAN_CHANNEL;
	strM2MAPConfig.u8SecType = MAIN_WLAN_AUTH;
	strM2MAPConfig.au8DHCPServerIP[0] = 0xC0; /* 192 */
	strM2MAPConfig.au8DHCPServerIP[1] = 0xA8; /* 168 */
	strM2MAPConfig.au8DHCPServerIP[2] = 0x01; /* 1 */
	strM2MAPConfig.au8DHCPServerIP[3] = 0x01; /* 1 */

	/* Bring up AP mode with parameters structure. */
	ret = m2m_wifi_enable_ap(&strM2MAPConfig);
	if (M2M_SUCCESS != ret) {
		printf("main: m2m_wifi_enable_ap call error!\r\n");
		while (1) {
		}
	}

	printf("AP Provision mode started.\r\nOn the android device, connect to %s then run setting app.\r\n", MAIN_WLAN_SSID);

	while (1) {
		m2m_wifi_handle_events(NULL);

		if (tcp_server_socket < 0) {
			/* Open TCP server socket */
			if ((tcp_server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
				printf("main: failed to create TCP server socket error!\r\n");
				continue;
			}

			/* Bind service*/
			bind(tcp_server_socket, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
		}
	}

	return 0;
}
