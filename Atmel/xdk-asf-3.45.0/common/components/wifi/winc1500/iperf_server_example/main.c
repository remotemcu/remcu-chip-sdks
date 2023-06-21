/**
 * \file
 *
 * \brief WINC1500 Iperf Server Example.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */


/** \mainpage
 * \section intro Introduction
 * This example demonstrates the use of the WINC1500 with the SAM Xplained Pro
 * board to run Iperf server.<br>
 * It uses the following hardware:
 * - the SAM Xplained Pro.
 * - the WINC1500 on EXT1.
 *
 * \section files Main Files
 * - main.c : Initialize the WINC1500 and run Iperf server.
 *
 * \section usage Usage
 * -# Configure below code in the main.h for AP information to be connected.
 * \code
 *    #define MAIN_WLAN_SSID                    "DEMO_AP"
 *    #define MAIN_WLAN_AUTH                    M2M_WIFI_SEC_WPA_PSK
 *    #define MAIN_WLAN_PSK                     "12345678"
 *    #define MAIN_WIFI_M2M_PRODUCT_NAME        "NMCTemp"
 *    #define MAIN_WIFI_M2M_SERVER_IP           0xFFFFFFFF // "255.255.255.255"
 *    #define MAIN_WIFI_M2M_SERVER_PORT         (6666)
 *    #define MAIN_WIFI_M2M_REPORT_INTERVAL     (1000)
 * \endcode
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
 * -- WINC1500 IPERF server example --
 * -- SAMD21_XPLAINED_PRO --
 * -- Compiled: xxx xx xxxx xx:xx:xx --
 *  
 *  
 *  (APP)(INFO)Chip ID 1503a0
 *  (APP)(INFO)DriverVerInfo: xxxxxxxxx
 *  (APP)(INFO)Firmware ver   : xx.x.x Svnrev xxxxx
 *  (APP)(INFO)Firmware Build xxx xx xxxx Time xx:xx:xx
 *  (APP)(INFO)Firmware Min driver ver : xx.xx.x
 *  (APP)(INFO)Driver ver: xx.x.x
 *  (APP)(INFO)Driver built at xxx xx xxxx  xx:xx:xx
 *  iperf_wifi_cb: M2M_WIFI_RESP_CON_STATE_CHANGED: CONNECTED
 *  iperf_wifi_cb: M2M_WIFI_REQ_DHCP_CONF: IP is xxx.xxx.xxx.xxx
 *  (APP)(INFO)Socket 0 session ID = 1
 *  (APP)(INFO)Socket 7 session ID = 2
 *  (APP)(INFO)Socket 8 session ID = 3
 *  ------------------------------------------------------------
 *  Server listening on TCP/UDP port 5001
 *  TCP window size: ??? KByte
 *  ------------------------------------------------------------ 
 * \endcode
 * -# Start the application on client using command.
 * -# iperf -c <Server_IP_Address> -t <time_peroid> -i <time_interval> -r 
 *
 * \section compinfo Compilation Information
 * This software was written for the GNU GCC compiler using Atmel Studio 6.2
 * Other compilers may or may not work.
 *
 */

#include "asf.h"
#include <string.h>
#include "common/include/nm_common.h"
#include "driver/include/m2m_wifi.h"
#include "driver/include/m2m_periph.h"
#include "socket/include/socket.h"
#include "iperf.h"

#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- WINC1500 IPERF server example --"STRING_EOL \
	"-- "BOARD_NAME " --"STRING_EOL	\
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

/** Message format definitions. */
typedef struct s_msg_wifi_product {
	uint8_t name[1400];
} t_msg_wifi_product;

/** Wi-Fi connection state */
static volatile uint8_t wifi_connected;

uint32		 gu32IPAddress;
uint32		 clientIPAddress;
uint32_t	 tcp_serv_pack_recv = 0;
uint32_t	 udp_serv_pack_recv = 0;
SOCKET tcp_client_sock = -1;
SOCKET udp_server_sock = -1;
app_status iperf_app_stat = {0,0,0,0};

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

static void disable_pullups(void)
{
	uint32 pinmask;
	pinmask = (
	M2M_PERIPH_PULLUP_DIS_HOST_WAKEUP|
	M2M_PERIPH_PULLUP_DIS_SD_CMD_SPI_SCK|
	M2M_PERIPH_PULLUP_DIS_SD_DAT0_SPI_TXD);
	
	m2m_periph_pullup_ctrl(pinmask, 0);
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
		tstrM2MIPConfig* pstrM2MIpConfig = (tstrM2MIPConfig*) pvMsg;
		uint8 *pu8IPAddress = (uint8*) &pstrM2MIpConfig->u32StaticIP;

		wifi_connected = 1;
		gu32IPAddress = pstrM2MIpConfig->u32StaticIP;
		printf("iperf_wifi_cb: M2M_WIFI_REQ_DHCP_CONF: IP is %u.%u.%u.%u\n",
				pu8IPAddress[0], pu8IPAddress[1], pu8IPAddress[2], pu8IPAddress[3]);
		
		iperf_app_stat.tcp_server = MODE_INIT;
		iperf_app_stat.udp_server = MODE_INIT;
	}
	break;

	default:
		break;
	}
}

/**
 * \brief Main application function.
 *
 * Initialize system, UART console, network then test function of TCP client.
 *
 * \return program return value.
 */
int main(void)
{

	tstrWifiInitParam param;
	int8_t ret;
	tstrM2mLsnInt strM2mLsnInt;

	tstrIperfInit pstrIperfInit;

	/* Initialize the board. */
	sysclk_init();
	board_init();

	/* Initialize the UART console. */
	configure_console();
	
	/* Enable SysTick interrupt for non busy wait delay. */
	if (SysTick_Config(sysclk_get_cpu_hz() / 1000))	{
		puts("main: SysTick configuration error!");
		while (1);
	}

	/* Output example information. */
	puts(STRING_EOL);
	puts(STRING_HEADER);
	puts(STRING_EOL);

	/* Initialize the BSP. */
	ret = nm_bsp_init();
	if (ret != M2M_SUCCESS) {
		M2M_ERR("\r\nFailed to initialize BSP.");
		while(1);
	}

	ret = nm_bsp_app_init();
	if (ret != M2M_SUCCESS) {
		M2M_ERR("\r\nFailed to initialize BSP App.");
		while(1);
	}

	/* Initialize WINC1500 Wi-Fi driver with data and status callbacks. */
	param.pfAppWifiCb = iperf_wifi_cb;
	ret = m2m_wifi_init(&param);
	if (M2M_SUCCESS != ret) {
		printf("iperf_start: m2m_wifi_init call error!\r\n");
		while (1);
	}	
	
	/* Initialize socket module */
	socketInit();
	registerSocketCallback(IperfSocketEventHandler, NULL);

	IperfInit();

	/* Connect to router. */
	m2m_wifi_connect((char *)IPERF_WIFI_M2M_WLAN_SSID, sizeof(IPERF_WIFI_M2M_WLAN_SSID),
	IPERF_WIFI_M2M_WLAN_AUTH, (char *)IPERF_WIFI_M2M_WLAN_PSK, M2M_WIFI_CH_ALL);

	while (1) {
		/* Handle pending events from network controller. */
		m2m_wifi_handle_events(NULL);

		if ((iperf_app_stat.udp_server == MODE_INIT) || (iperf_app_stat.udp_server == MODE_FINISHED))
		{
			if (iperf_app_stat.udp_server == MODE_FINISHED)
			{
				IperfSocketClose(udp_server_sock);
				iperf_app_stat.udp_server = MODE_INIT;
				printf("\n\n\n------------------------------------------------------------\r\n");
				printf("Server listening on TCP/UDP port 5001\r\n");
				printf("TCP window size: 1 KByte\r\n");
				printf("------------------------------------------------------------\r\n");
				continue;
			}
			//printf("\n\nInit UDP server\r\n");
			iperf_app_stat.udp_server = MODE_INIT_DONE;
			pstrIperfInit.port = IPERF_WIFI_M2M_SERVER_PORT;
			pstrIperfInit.operating_mode = MODE_UDP_SERVER;
			IperfCreate(&pstrIperfInit, true);
		}
		else if (iperf_app_stat.udp_server == MODE_WAIT)
		{
			iperf_app_stat.udp_server = MODE_STOP;
			IperfSocketClose(udp_server_sock);
			printf("------------------------------------------------------------\r\n");
			printf("Client connecting to %lu.%lu.%lu.%lu, UDP port 5001\r\n",
			(udp_client_addr.sin_addr.s_addr & 0xFF), (udp_client_addr.sin_addr.s_addr & 0xFF00) >> 8,
			(udp_client_addr.sin_addr.s_addr & 0xFF0000) >> 16, (udp_client_addr.sin_addr.s_addr & 0xFF000000) >> 24);
			printf("Sending %d byte datagrams\r\n", IPERF_TX_BUFFER_SIZE);
			printf("------------------------------------------------------------\r\n");
			iperf_app_stat.udp_client = MODE_INIT;
		}
		else if (iperf_app_stat.udp_client == MODE_INIT) {
			iperf_app_stat.udp_client = MODE_INIT_DONE;
			pstrIperfInit.port = IPERF_WIFI_M2M_SERVER_PORT;
			pstrIperfInit.operating_mode = MODE_UDP_CLIENT;
			memcpy(&pstrIperfInit.ip,&udp_client_addr.sin_addr.s_addr,sizeof(in_addr));	
			if (udp_serv_pack_recv == 0) {
				printf("sending packet indefinitely\r\n");
				pstrIperfInit.packets_to_send = -1; // Send indefinitely
			} else {
				pstrIperfInit.packets_to_send = udp_serv_pack_recv;
			}
			pstrIperfInit.packet_len = IPERF_TX_BUFFER_SIZE;
			pstrIperfInit.tls = 0;
			IperfCreate(&pstrIperfInit, false);					
		}
		else if (iperf_app_stat.udp_client == MODE_STOP) {
			iperf_app_stat.udp_client = MODE_FINISHED;
			printf("\n\n\n------------------------------------------------------------\r\n");
			printf("Server listening on TCP/UDP port 5001\r\n");
			printf("TCP window size: 1 KByte\r\n");
			printf("------------------------------------------------------------\r\n");			
		}

		if ((iperf_app_stat.tcp_server == MODE_INIT) || (iperf_app_stat.tcp_server == MODE_FINISHED))
		{
			iperf_app_stat.tcp_server = MODE_INIT_DONE;
 			pstrIperfInit.port = IPERF_WIFI_M2M_SERVER_PORT;
 			pstrIperfInit.operating_mode = MODE_TCP_SERVER;
 			IperfCreate(&pstrIperfInit, true);			
		}
		if ((iperf_app_stat.tcp_client == MODE_INIT))
		{
			iperf_app_stat.tcp_client = MODE_INIT_DONE;
			pstrIperfInit.port = IPERF_WIFI_M2M_SERVER_PORT;
			pstrIperfInit.operating_mode = MODE_TCP_CLIENT;
			memcpy(&pstrIperfInit.ip,&clientIPAddress,sizeof(clientIPAddress));
			if (tcp_serv_pack_recv == 0) {
				printf("sending packet indefinitely\r\n");
				pstrIperfInit.packets_to_send = -1; // Send indefinitely
			} else {
				pstrIperfInit.packets_to_send = tcp_serv_pack_recv;
			}
			pstrIperfInit.packet_len = IPERF_TX_BUFFER_SIZE;
			pstrIperfInit.tls = 0;
			IperfCreate(&pstrIperfInit, false);
		}else if (iperf_app_stat.tcp_client == MODE_START) {
			iperf_app_stat.tcp_client = MODE_RUN;
			IperfTCP_Client_SendTestPacket();
		}
		IperfUpdate();
	}

}
