/**
*
* \file
*
* \brief WINC1500 Power Profiling APP.
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

/** \mainpage
* \section intro Introduction
* This example demonstrates the power profiling of WINC15x0 using SAMD21 as Host
* MCU. It demonstrates how switch to various low power modes of WINC and measure 
* the power consumed <br>
* It uses the following hardware:
* - the SAMD21 Xplained Pro.
* - the WINC1500 on EXT1.
*
* \section files Main Files
* - main.c : Configure and switch the WINC to various low power modes.
*
* \section usage Usage
* -# Configure below code in the main.h for AP to be connected.
* \code
*    #define MAIN_WLAN_SSID         "DEMO_AP"
*    #define MAIN_WLAN_AUTH         M2M_WIFI_SEC_WPA_PSK
*    #define MAIN_WLAN_PSK          "12345678"
* \endcode
* -# Configure below code in the main.h for for configuring server information.
* \code
*    #define TEST_SSL_TCP_IP		"192.168.1.122"   
*    #define TEST_SSL_SERVER_PORT	443				
*    #define TEST_TCP_SERVER_PORT	6666    
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
*    -- WINC1500 Power Profiling App --
*    -- SAMD21_XPLAINED_PRO --
*    -- Compiled: xxx xx xxxx xx:xx:xx --
*    *************** WINC1500 Power Modes Menu ***************
*    Select a Test for WINC1500 Power profile measurement
*    1.Power Down mode
*    2.WINC1500 Deep Sleep Modes
*            21. Power Save Deep Automatic(M2M_PS_DEEP_AUTOMATIC)
*            22. Doze Mode
*    3. On_Transmit_Power Modes Datasheet Table 8.1
*    4. On_Receive_Power Mode Datasheet Table 8.1
*    5.WINC1500 Connection Profiles
*    6.Sample Test App STA mode
*    7.Sample Test App AP mode
*    *********************************************************
* \endcode
*
* \warning
* \code
*    Refer to the power profiling appnote and make sure the setup is as per 
*    the recommendation.
* \endcode
*
* \section compinfo Compilation Information
* This software was written for the GNU GCC compiler using Atmel Studio 7.0
* Other compilers may or may not work.
*
* \section contactinfo Contact Information
* For further information, visit
* <A href="http://www.microchip.com">Microchip</A>.\n
*/

#include "asf.h"
#include "driver/include/m2m_wifi.h"
#include "socket/include/socket.h"
#include "driver/include/m2m_periph.h"
#include "driver/source/nmasic.h"
#include "main.h"
#include "string.h"

#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- WINC1500 Power Profiling App --"STRING_EOL \
"-- "BOARD_NAME " --"STRING_EOL	\
"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

#define DOZE_MODE 3

/** UART module for debug. */
static struct usart_module cdc_uart_module;

/** Client and Server socket handler. */
static SOCKET tcp_client_socket = -1;
static SOCKET udp_client_socket = -1;
static SOCKET udp_server_socket = -1;

/*SSL Data upload parameters*/
static uint8 fake_data[TX_PACKET_SIZE];
static uint32 send_cnt = 0;
static uint32 u32TotalBytesSent = 0;
static int menu_number = 0,ps_mode = 0,ssl_enable = 0;
static int listen_interval = 0, dtim = DEFAULT_DTIM_FLAG,transmit_pwr_mode;
static uint8_t wifi_connected;
static uint32_t gateway_ip = 0;
/** UDP packet count */
static uint32_t packetCnt = 0;
/** Test buffer */
static uint8_t gau8SocketTestBuffer[TEST_WINC_RECEIVE_BUFFER] = {0};
struct sockaddr_in addr;
bool curr_button_state = false,prev_button_state = false,tcp_connected = false,upload_completed = false;
bool udp_keep_alive_sent = false;
/** SysTick counter to avoid busy wait delay. */
volatile uint32_t ms_ticks = 0;
static uint32_t start_time = 0;
static app_states app_state = IDLE_STATE;
static void winc_init(void);
/* Structure initialized to configure WINC in AP mode */
static tstrM2MAPConfig gstrM2MAPConfig = {
	"WINC1500_POWERSAVE_AP",
	M2M_WIFI_CH_1,
	0,
	WEP_40_KEY_STRING_SIZE,
	"1234567890",
	M2M_WIFI_SEC_OPEN,
	SSID_MODE_VISIBLE,
	{192, 168, 1, 1}
};

/**
 * \brief SysTick handler used to measure precise delay. 
 *
 * \param[in] None
 *
 * \return None.
 */
void SysTick_Handler(void)
{
	ms_ticks++;
}

/**
* \brief Set the application status.
*
* \param[in] state State value to be set
*
* \return None.
*/
static void set_state(app_states state)
{
	app_state = state;
}

/**
* \brief Configure UART console.
*
* \param[in] None
*
* \return None.
*/
static void configure_console(void)
{
	struct usart_config usart_conf;

	usart_get_config_defaults(&usart_conf);
	usart_conf.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	usart_conf.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	usart_conf.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	usart_conf.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	usart_conf.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	usart_conf.baudrate    = 115200;

	stdio_serial_init(&cdc_uart_module, EDBG_CDC_MODULE, &usart_conf);
	usart_enable(&cdc_uart_module);
}

/**
* \brief Resets the timer.
*
* \param[in] None
*
* \return None.
*/
static void reset_start_time(void)
{
	start_time = ms_ticks;
}

/**
* \brief Creates and connects to an secure socket to be used for SSL.
*
* \param[in] None.
*
* \return SOCK_ERR_NO_ERROR if success, -1 if socket create error, SOCK_ERR_INVALID if socket connect error.
*/
static int8_t connect_to_server(char* ip_addr,int tcp_mode)
{
	struct sockaddr_in addr_in;

	addr_in.sin_family = AF_INET;
	addr_in.sin_port = tcp_mode == 1? (_htons(TEST_SSL_SERVER_PORT)):(_htons(TEST_TCP_SERVER_PORT));
	addr_in.sin_addr.s_addr = nmi_inet_addr(ip_addr);

	/* Create secure socket */
	if (tcp_client_socket < 0) {
		if(tcp_mode == 1)
		{
			tcp_client_socket = socket(AF_INET, SOCK_STREAM, SOCKET_FLAGS_SSL);	
		}
		else
		{
			tcp_client_socket = socket(AF_INET, SOCK_STREAM, 0);	
		}
	}

	/* Check if socket was created successfully */
	if (tcp_client_socket == -1) {
		printf("socket error.\r\n");
		close(tcp_client_socket);
		return -1;
	}

	/* If success, connect to socket */
	if (connect(tcp_client_socket, (struct sockaddr *)&addr_in, sizeof(struct sockaddr_in)) != SOCK_ERR_NO_ERROR) {
		printf("connect error.\r\n");
		return SOCK_ERR_INVALID;
	}

	/* Success */
	return SOCK_ERR_NO_ERROR;
}

/**
* \brief Handles Callback event for TCP client socket.
*
* \param[in] sock   Socket for which event callback is called
* \param[in] u8Msg  Event to be handled
* \param[in] *pvMsg Data related to the event
*
* \return None.
*/

static void handle_tcp_socket_cb(SOCKET sock, uint8_t u8Msg, void *pvMsg)
{
	switch (u8Msg)
	{
		case SOCKET_MSG_CONNECT:
		{
			tstrSocketConnectMsg *pstrConnect = (tstrSocketConnectMsg *)pvMsg;
			if (pstrConnect && pstrConnect->s8Error >= SOCK_ERR_NO_ERROR)
			{
				#if TCP_CONNECTION_TOGGLE
					port_pin_set_output_level(LED0_GPIO,true);
				#endif //TCP_CONNECTION_TOGGLE
				set_state(SOCKET_CONNECTION_STATE);
				tcp_connected = true;
				printf("Successfully connected.\r\n");
				recv(sock, fake_data,sizeof(fake_data), 0);
			}
			else
			{
				printf("Connect error!\r\n");
				printf("Please try pushing the button again\r\n");
				close(sock);
				tcp_client_socket = -1;
				tcp_connected = false;
			}
		}
		break;
		
		case SOCKET_MSG_SEND:
		{
			sint16 s16SentBytes = *((sint16*)pvMsg);
			
			if(s16SentBytes < 0)
			{
				printf("Socket (%d) Send Error: %d\r\n",sock , s16SentBytes);
			}
			else
			{
				#if TCP_UPLOAD_TOGGLE
					port_pin_set_output_level(LED0_GPIO,true);
				#endif //TCP_UPLOAD_TOGGLE
				printf("Uploaded %d bytes\r\n",s16SentBytes);
				u32TotalBytesSent += s16SentBytes;
			
				if(u32TotalBytesSent >= (TX_PACKET_SIZE*TEST_SSL_UPLOAD_SIZE))
				{
					u32TotalBytesSent = 0;
					printf("Upload Complete\r\n");
					upload_completed = true;
				}
				
			}
			
		}
		
		break;
		
		case SOCKET_MSG_RECV:
		{
			tstrSocketRecvMsg *pstrRecv = (tstrSocketRecvMsg *)pvMsg;
			
			if(pstrRecv->s16BufferSize < 0)
			{
				printf("Socket (%d) Error: %d\r\n",sock , pstrRecv->s16BufferSize);
				close(sock);
			}
		}
		break;
		
		default:
		break;
	}

}

/**
* \brief Handles Callback event for UDP client socket.
*
* \param[in] sock   Socket for which event callback is called
* \param[in] u8Msg  Event to be handled
* \param[in] *pvMsg Data related to the event
*
* \return None.
*/
static void handle_udp_client_socket_cb(SOCKET sock, uint8_t u8Msg, void *pvMsg)
{
	if(u8Msg == SOCKET_MSG_SENDTO)
	{
		udp_keep_alive_sent = true;
	}
}

/**
* \brief Handles Callback event for UDP server socket.
*
* \param[in] sock   Socket for which event callback is called
* \param[in] u8Msg  Event to be handled
* \param[in] *pvMsg Data related to the event
*
* \return None.
*/
static void handle_udp_serv_socket_cb(SOCKET sock, uint8_t u8Msg, void *pvMsg)
{
	if (u8Msg == SOCKET_MSG_BIND)
	{
		tstrSocketBindMsg *pstrBind = (tstrSocketBindMsg *)pvMsg;
		if (pstrBind && pstrBind->status == 0)
		{
			/* Prepare next buffer reception. */
			printf("socket_cb: bind success!\r\n");
			recvfrom(sock, gau8SocketTestBuffer, TEST_WINC_RECEIVE_BUFFER, 0);
		}
		else
		{
			printf("socket_cb: bind error!\r\n");
		}
	}
	else if (u8Msg == SOCKET_MSG_RECVFROM)
	{
		tstrSocketRecvMsg *pstrRx = (tstrSocketRecvMsg *)pvMsg;

		if (pstrRx->pu8Buffer && pstrRx->s16BufferSize)
		{
			packetCnt++;
			printf("socket_cb: received app message.(%lu)\r\n", packetCnt);
			/* Prepare next buffer reception. */
			recvfrom(sock, gau8SocketTestBuffer, TEST_WINC_RECEIVE_BUFFER, 0);
		}
		else
		{
			if (pstrRx->s16BufferSize == SOCK_ERR_TIMEOUT)
			{
				/* Prepare next buffer reception. */
				recvfrom(sock, gau8SocketTestBuffer, TEST_WINC_RECEIVE_BUFFER, 0);
			}
		}
	}
}


/**
* \brief Callback function for all socket events.
*
* \param[in] sock socket handler.
* \param[in] u8Msg Type of Socket notification
* \param[in] pvMsg A structure contains notification informations.
*
* \return None.
*/
static void socket_cb(SOCKET sock, uint8_t u8Msg, void *pvMsg)
{
	if(sock == udp_server_socket)
	{
		handle_udp_serv_socket_cb(sock,u8Msg,pvMsg);
	}
	if(sock == udp_client_socket)
	{
		handle_udp_client_socket_cb(sock,u8Msg,pvMsg);
	}
	if(sock == tcp_client_socket)
	{
		handle_tcp_socket_cb(sock,u8Msg,pvMsg);
	}
}

/**
* \brief Callback to get the Wi-Fi status update.
*
* \param[in] u8MsgType Type of Wi-Fi notification.
* \param[in] pvMsg A pointer to a buffer containing the notification parameters.
*
* \return None.
*/
static void wifi_cb(uint8_t u8MsgType, void *pvMsg)
{
	switch (u8MsgType) {
		case M2M_WIFI_RESP_CON_STATE_CHANGED:
		{
			tstrM2mWifiStateChanged *pstrWifiState = (tstrM2mWifiStateChanged *)pvMsg;
			if (pstrWifiState->u8CurrState == M2M_WIFI_CONNECTED) 
			{
				#if 1 //!AP_CONNECTION_TOGGLE
					printf("wifi_cb: M2M_WIFI_RESP_CON_STATE_CHANGED: CONNECTED\r\n");
				#endif	
			} 
			else if (pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED) 
			{
				printf("wifi_cb: M2M_WIFI_RESP_CON_STATE_CHANGED: DISCONNECTED\r\n");
				printf("Disconnected:%d",pstrWifiState->u8ErrCode);
				wifi_connected = M2M_WIFI_DISCONNECTED;
				/*If we get disconnected we close any socket that is open*/
				if(tcp_client_socket >= 0)
				{
					close(tcp_client_socket);
					tcp_client_socket = -1;
				}
				if(udp_client_socket >= 0)
				{
					close(udp_client_socket);
					udp_client_socket = -1;
				}
				if(udp_server_socket >= 0)
				{
					close(udp_server_socket);
					udp_server_socket = -1;
				}
				tcp_connected = false;
			}
			break;
		}

		case M2M_WIFI_REQ_DHCP_CONF:
		{
			#if AP_CONNECTION_TOGGLE
				port_pin_toggle_output_level(LED0_GPIO);
			#endif //AP_CONNECTION_TOGGLE
			set_state(WIFI_CONNECTION_STATE);
			wifi_connected = M2M_WIFI_CONNECTED;
			uint8_t *pu8IPAddress = (uint8_t *)pvMsg;
			tstrM2MIPConfig *connInfo = (tstrM2MIPConfig*)pvMsg;
			gateway_ip = connInfo->u32Gateway; 
			#if 1 //!AP_CONNECTION_TOGGLE			
				printf("wifi_cb: M2M_WIFI_REQ_DHCP_CONF: IP is %u.%u.%u.%u\r\n",
				pu8IPAddress[0], pu8IPAddress[1], pu8IPAddress[2], pu8IPAddress[3]);
			#endif //AP_CONNECTION_TOGGLE 
			break;
		}
		
		case M2M_WIFI_RESP_PROVISION_INFO:
		{
			tstrM2MProvisionInfo *pstrProvInfo = (tstrM2MProvisionInfo *)pvMsg;

			if (pstrProvInfo->u8Status == M2M_SUCCESS) {
				printf("wifi_cb: Provision Success\r\n");
			} 
			else 
			{
				printf("wifi_cb: Provision failed.\r\n");
			}
		}

		default:
		{
			break;
		}
	}
}

/**
* \brief Disables pull-ups for the pins in WINC which are used for communication with host MCU.
*
* \param[in] None
*
* \return None.
*/
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
* \brief Connect to a pre-configured AP and initialize the server address.
*
* \param[in] None
*
* \return None.
*/
static void test_init(void)
{
	/* Initialize socket address structure. */
	addr.sin_family = AF_INET;
	addr.sin_port = _htons(TEST_WINC_SERVER_PORT);
	addr.sin_addr.s_addr = nmi_inet_addr((char*)TEST_WINC_SERVER_IP);
	#if AP_CONNECTION_TOGGLE
		port_pin_toggle_output_level(LED0_GPIO);
	#endif //AP_CONNECTION_TOGGLE
	/* Connect to router. */
	m2m_wifi_connect((char *)TEST_WLAN_SSID, sizeof(TEST_WLAN_SSID), TEST_WLAN_AUTH, (char *)TEST_WLAN_PSK, M2M_WIFI_CH_1);
}

/**
* \brief Switch the WINC to provisioning mode.
*
* \param[in] tp test parameter
*
* \return None.
*/
static void run_provisioning(low_power_test_param* tp)
{
	m2m_wifi_start_provision_mode((tstrM2MAPConfig *)&gstrM2MAPConfig, (char *)"atmel.com", 1);
	printf("Provision Mode started.\r\nConnect to [%s] via AP[%s] and fill up the page.\r\n","atmel.com", gstrM2MAPConfig.au8SSID);

	while (1) {
		m2m_wifi_handle_events(NULL);
	}
}

/**
* \brief Run UDP server on WINC.
*
* \param[in] None
*
* \return None.
*/
static void run_udp_server(void)
{
	m2m_wifi_handle_events(NULL);
	if (wifi_connected == M2M_WIFI_CONNECTED)
	{
		/* Create socket for Rx UDP */
		if (udp_server_socket < 0)
		{
			if ((udp_server_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
			{
				printf("main : failed to create RX UDP Client socket error!\r\n");
			}
			else
			{
				/* Socket bind */
				bind(udp_server_socket, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
			}
		}
	}
}

/**
* \brief Run UDP client on WINC.
*
* \param[in] target_ip          IP address of the server
* \param[in] delay_btwn_packets delay between sending 2 packets
* \param[in] packet_size        size of each packet
*
* \return None.
*/
static void run_udp_client(uint32_t target_ip,uint32_t delay_btwn_packets,uint32_t packet_size)
{
	int8_t ret = 0;
	m2m_wifi_handle_events(NULL);
	if (wifi_connected == M2M_WIFI_CONNECTED) 
	{
		/* Create socket for Tx UDP */
		if (udp_client_socket < 0)
		{
			if ((udp_client_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
			{
				printf("main : failed to create TX UDP client socket error!\r\n");
			}
			else
			{
				set_state(SOCKET_CONNECTION_STATE);
			}
		}
		else
		{
			if(ms_ticks - start_time < delay_btwn_packets)
			{
				return;
			}
			start_time = ms_ticks;
			addr.sin_addr.s_addr = target_ip;
			/* Send client discovery frame. */
			sendto(udp_client_socket,gau8SocketTestBuffer, packet_size, 0, (struct sockaddr *)&addr, sizeof(addr));
			
			if (ret != M2M_SUCCESS) 
			{
				printf("Message failed\r\n");
			}
			else
			{
				udp_keep_alive_sent = true;
				//printf("Sent a UDP message\r\n");
			} 
		}
	}
}

/**
* \brief Function to set the desired low power mode to WINC and execute UDP server
*        in case of Auto deep sleep.
*
* \param[in] tp test parameter
*
* \return None.
*/
static void start_low_power_mode_test(low_power_test_param* tp)
{
	tstrM2mLsnInt strM2mLsnInt;

	m2m_wifi_enable_sntp(0);
	strM2mLsnInt.u16LsnInt = tp->listen_interval;	
	m2m_wifi_set_lsn_int(&strM2mLsnInt);
	m2m_wifi_set_sleep_mode(tp->ps_mode,tp->dtim);
	test_init();
	if(tp->ps_mode == M2M_PS_MANUAL)
	{
		while(1)
		{
			m2m_wifi_handle_events(NULL);
			if(wifi_connected == M2M_WIFI_CONNECTED)
			{
				wifi_connected = DOZE_MODE;
				m2m_wifi_request_sleep(30000);
			}
		}
	}
	else
	{
		while(1)
		{
			run_udp_server();
		}
	}
}
/**
* \brief Execute Transmission test by transmitting UDP frames continously.
*
* \param[in] tp test parameter
*
* \return None.
*/
static void start_transmission_test(low_power_test_param* tp)
{
	m2m_wifi_enable_sntp(0);
	test_init();
	while(1)
	{
		run_udp_client(gateway_ip,TX_DELAY_MS,TX_PACKET_SIZE);
	}
}

/**
* \brief Execute Reception test by receiving UDP frames in UDP server mode.
*
* \param[in] None
*
* \return None.
*/
static void start_receive_test(void)
{
	m2m_wifi_enable_sntp(0);
	test_init();
	while(1)
	{
		run_udp_server();
	}
}

/**
* \brief State machine to connect and exchange data with a TCP, SSL or a UDP server.
*
* \param[in] server_mode TCP(0), SSL(1) or UDP(2) server
* \param[in] tp          Test parameter
*
* \return None.
*/
static void execute_state_machine(int server_mode,low_power_test_param* tp)
{
	int ret = 0;
	tstrM2mLsnInt strM2mLsnInt;

	switch(app_state)
	{
		case IDLE_STATE:
			winc_init();
			m2m_wifi_enable_sntp(0);
			strM2mLsnInt.u16LsnInt = tp->listen_interval;
			m2m_wifi_set_lsn_int(&strM2mLsnInt);
			m2m_wifi_set_sleep_mode(tp->ps_mode,tp->dtim);
			test_init();
		break;
		case WIFI_CONNECTION_STATE:
			if(server_mode == 1 || server_mode == 0)
			{
				if (tcp_client_socket < 0)
				{
					#if TCP_CONNECTION_TOGGLE
						port_pin_set_output_level(LED0_GPIO,false);
					#endif //TCP_CONNECTION_TOGGLE
					if (connect_to_server((char*)TEST_SSL_TCP_IP,server_mode) != SOCK_ERR_NO_ERROR)
					{
						tcp_client_socket = -1;
						printf("Connection Failed\r\n");
						printf("Exiting App\r\n");
						while(1);
					}
				}	
			}
			else
			{
				printf("Setting up UDP\r\n");
				run_udp_client(nmi_inet_addr((char*)TEST_SSL_TCP_IP),0,TX_PACKET_SIZE);
				set_state(SOCKET_CONNECTION_STATE);
			}
		break;
		case SOCKET_CONNECTION_STATE:
			if(server_mode == 1 || server_mode == 0)
			{
				if(tcp_client_socket >= 0)
				{
					#if TCP_UPLOAD_TOGGLE
						port_pin_set_output_level(LED0_GPIO,false);
					#endif //TCP_UPLOAD_TOGGLE	
					ret = send(tcp_client_socket,fake_data,sizeof(fake_data),0);
					if(0 != ret)
					{
						printf("Send failed-%d\r\n",ret);
					}
					else
					{
						printf("Uploading Data..\r\n");
					}
				}
			}
			else
			{
				run_udp_client(nmi_inet_addr((char*)TEST_SSL_TCP_IP),0,TX_PACKET_SIZE);
			}
			
		break;
	}
}

/**
* \brief Execute profiling App
*
* \param[in] enable_ssl To connect to a secure server
* \param[in] tp         Test parameter
*
* \return None.
*/
static void run_profiling_app(int enable_ssl,low_power_test_param* tp)
{	
	while(1)
	{
		m2m_wifi_handle_events(NULL);
		curr_button_state = !port_pin_get_input_level(BUTTON_0_PIN);
		if ((prev_button_state == false) && (curr_button_state == true))
		{
			execute_state_machine(enable_ssl,tp);
		}
		prev_button_state = curr_button_state;
	}
}

/**
* \brief Execute Sample Test App - connect and transmit on button press
*
* \param[in] enable_ssl To connect to a secure server
* \param[in] tp         Test parameter
*
* \return None.
*/
static void run_sample_test_app(int enable_ssl,low_power_test_param* tp)
{
	tstrM2mLsnInt strM2mLsnInt;
	int8_t ret = 0;

	m2m_wifi_enable_sntp(0);
	strM2mLsnInt.u16LsnInt = tp->listen_interval;
	m2m_wifi_set_lsn_int(&strM2mLsnInt);
	m2m_wifi_set_sleep_mode(tp->ps_mode,tp->dtim);
	test_init();
	while(1)
	{
		m2m_wifi_handle_events(NULL);
		curr_button_state = !port_pin_get_input_level(BUTTON_0_PIN);
		//Detect only falling edges
		if ((prev_button_state == false) && (curr_button_state == true))
		{
			if (wifi_connected == M2M_WIFI_CONNECTED)
			{
				if (tcp_client_socket < 0) 
				{
					if (connect_to_server((char*)TEST_SSL_TCP_IP,enable_ssl) != SOCK_ERR_NO_ERROR) 
					{
						tcp_client_socket = -1;
						printf("Connection Failed\r\n");
						printf("Exiting App\r\n");
						while(1);
					}
				}
			}
		}
		prev_button_state = curr_button_state;
		if(tcp_client_socket >= 0 && tcp_connected)
		{
			if(send_cnt < TEST_SSL_UPLOAD_SIZE)
			{
				ret = send(tcp_client_socket,fake_data,sizeof(fake_data),0);
				if(0 != ret)
				{
					printf("Send failed-%d\r\n",ret);
				}
				else
				{
					send_cnt++;
					printf("Uploading Data..\r\n");
				}
			}
		}
		else if(wifi_connected == M2M_WIFI_CONNECTED)
		{
			/*If no tcp connection and is manual PS mode*/
			if(tp->ps_mode == M2M_PS_MANUAL)
			{
				//We send periodic udp messages(every 10s) to gateway to stay connected
				//This is only needed if we  setup a sleep period of WINC to higher than 10s
				//so that the AP doesn't disconnect us.
				run_udp_client(gateway_ip,10000,1);
				if(udp_keep_alive_sent == true)
				{
					udp_keep_alive_sent = false;
					if(tcp_client_socket <= -1)
					{
						m2m_wifi_request_sleep(60000);		
					}
				}
			}
		}
		if(upload_completed)
		{
			upload_completed = false;
			close(tcp_client_socket);
			tcp_client_socket = -1;
			tcp_connected = false;
			send_cnt = 0;
			m2m_wifi_request_sleep(60000);
			/*We will also prolong the UDP timer as we have just finished sending some 
			packets out*/
			reset_start_time();	
		}
	}
}

/**
* \brief Initialize WINC
*
* \param[in] None
*
* \return None.
*/
static void winc_init(void)
{
	tstrWifiInitParam param;
	int8_t ret;

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

	/* Initialize Socket module */
	socketInit();
	registerSocketCallback(socket_cb, NULL);
	disable_pullups();
}

/**
* \brief Main application function.
*
* Initialize system, UART console, WINC and start power profiling application.
*
* \return Program return value.
*/
int main(void)
{
	low_power_test_param test_param;

	/* Initialize the board. */
	system_init();

	/* Initialize the UART console. */
	configure_console();
	printf(STRING_HEADER);
	
	printf("\r\n");
	printf("*************** WINC1500 Power Modes Menu ***************\r\n");
	printf("Select a Test for WINC1500 Power profile measurement\r\n");
	printf("1.Power Down mode\r\n");
	printf("2.WINC1500 Deep Sleep Modes\r\n");
	printf("\t21. Power Save Deep Automatic(M2M_PS_DEEP_AUTOMATIC)\r\n");
	printf("\t22. Doze Mode\r\n");
	printf("3. On_Transmit_Power Modes Datasheet Table 8.1\r\n");
	printf("4. On_Receive_Power Mode Datasheet Table 8.1\r\n");
	printf("5.WINC1500 Connection Profiles\r\n");
	printf("6.Sample Test App STA mode\r\n");
	printf("7.Sample Test App AP mode\r\n");
	printf("*********************************************************\r\n");
	scanf("%d",&menu_number);
	printf("\r\n");

	if(menu_number != 5)
	{
		winc_init();
	}
	if(menu_number == 21)
	{
		printf("Select Listen Interval:");
		scanf("%d",&listen_interval);
		printf("\r\n");
		printf("LI:%d\r\n",listen_interval);
		printf("Do you want WINC to listen to DTIM(1. yes or 0. no):");
		scanf("%d",&dtim);
		printf("\r\n");
		printf("In this test, you could chose to run UDP script to analyze how WINC wakes up to receive packets\r\n");
	}
	if(menu_number == 3 || menu_number == 7)
	{
		if(menu_number == 7)
		{
			printf("The only Power save available in AP Mode is to control TX power\r\n");
		}
		printf("Select between three TX Powers\r\n");
		printf("1.TX_PWR_HIGH,2.TX_PWR_MED,3.TX_PWR_LOW\r\n");
		scanf("%d",&transmit_pwr_mode);
		printf("\r\n");
	}
	if(menu_number == 5)
	{
		printf("This App connects to\r\n");
		printf("\tAccess point on first button press\r\n");
		printf("\tConnects to server on second button press(if TCP or SSL)\r\n");
		printf("\tSends out a data packet on subsequent button presses\r\n");
		printf("\r\n");
		printf("Select 1.SSL enable,0.TCP,2.UDP:");
		scanf("%d",&ssl_enable);
		printf("\r\n");
		printf("Select Listen Interval:");
		scanf("%d",&listen_interval);
		printf("\r\n");
		printf("Do you want WINC to listen to DTIM(1. yes or 0. no):");
		scanf("%d",&dtim);
		printf("\r\n");
	}
	if(menu_number == 6)
	{
		printf("This App connects to a server and uploads data on a button press(SW0)\r\n");
		printf("Select 1.Manual or 2.Automatic PS mode:");
		scanf("%d",&ps_mode);
		printf("\r\n");
		printf("Select 1.SSL enable or 0.TCP:");
		scanf("%d",&ssl_enable);
		printf("\r\n");
		printf("Select Listen Interval:");
		scanf("%d",&listen_interval);
		printf("\r\n");
	}
	test_param.tx_pwr_mode = DEFAULT_TX_POWER;
	test_param.dtim        = dtim;
	test_param.listen_interval = listen_interval;

	switch(menu_number)
	{
		case 1:
			printf("Powering Down WINC1500\r\n");
			socketDeinit();
			m2m_wifi_deinit(NULL);
			nm_bsp_deinit();
			while(1);
		break;
		
		case 21:
			printf("Putting WINC in (M2M_PS_DEEP_AUTOMATIC)\r\n");
			test_param.ps_mode = M2M_PS_DEEP_AUTOMATIC;
			start_low_power_mode_test(&test_param);
			break;
		case 22:	
			printf("Putting WINC in Doze Mode for a minute\r\n");
			test_param.listen_interval = 1;
			test_param.ps_mode = M2M_PS_MANUAL;
			test_param.dtim = 0;
			/*Manual mode is used to keep the WINC connected to AP, but 
			keep it in low power mode possible while connected, so a DMM
			could be used to measure this sleep current*/
			start_low_power_mode_test(&test_param);
			break;
		case 3:
			printf("Entering Transmit Mode\r\n");
			test_param.tx_pwr_mode = transmit_pwr_mode;
			start_transmission_test(&test_param);
		break;
		
		case 4:
			printf("Entering Receive Mode\r\n");
			start_receive_test();
		break;
		
		case 5:
			test_param.ps_mode = M2M_PS_DEEP_AUTOMATIC;
			test_param.listen_interval = listen_interval;
			test_param.dtim            = dtim;
			run_profiling_app(ssl_enable,&test_param);
		break;
		
		case 6:
			test_param.ps_mode = (ps_mode == 1)? (M2M_PS_MANUAL) : (M2M_PS_DEEP_AUTOMATIC) ;
			test_param.listen_interval = listen_interval;
			test_param.dtim            = DEFAULT_DTIM_FLAG;
			run_sample_test_app(ssl_enable,&test_param);
		break;
		
		case 7:
			test_param.tx_pwr_mode = transmit_pwr_mode;
			run_provisioning(&test_param);
		break;
		
		default:
			printf("Option not supported\r\n");
			while(1);
		break;
	}
	return 0;
}
