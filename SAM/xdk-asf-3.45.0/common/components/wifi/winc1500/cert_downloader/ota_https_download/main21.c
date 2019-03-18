/**
 *
 * \file
 *
 * \brief Certificate Downloader via OTA(HTTPS) Example.
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
 * This example demonstrates how to connect to an HTTPS server and download
 * a root/tls certificates using HTTPS client. Then sends the certificates to 
 * WINC SPI flash from host <br>
 * It uses the following hardware:
 * - the SAM Xplained Pro.
 * - the WINC1500 on EXT1.
 *
 * \section files Main Files
 * - main.c : WINC1500 Wi-Fi module, then download 
 * a certificate file using HTTPS client and then writes into WINC SPI flash.
 *
 * \section usage Usage
 * -# Configure below code in the main.h for AP information to be connected.
 * \code
 *    #define MAIN_WLAN_SSID         "DEMO_AP"
 *    #define MAIN_WLAN_AUTH         M2M_WIFI_SEC_WPA_PSK
 *    #define MAIN_WLAN_PSK          "12345678"
 * \endcode
 *
 * -# Provide HTTPS URL macro with partial URL (exclude the certificate .cer 
 * file name in the main.h file.
 * \code
 *    #define MAIN_HTTP_FILE_URL                   "https://192.168.43.34/"
 * \endcode
 * -# Provide number of tls/root certificates .cer to be downloaded
 * \code
 *    #define NUM_OF_ROOT_TLS_CHAIN_CERTIFICATES      5
 * \endcode
 * -# Provide certificate file name list in root_tls_certs_name
 *
 * -# Build the program and download it into the board.
 * -# On the computer, open and configure a terminal application as following.
 * \code
 *    Baud Rate : 115200
 *    Data : 8bit
 *    Parity bit : none
 *    Stop bit : 1bit
 *    Flow control : none
 * \endcode
 *
 * -# Start the application.
 * -# In the terminal window, the following text should appear:<br>
 *
 * \code
 * -- Certificate downloader via OTA (HTTPS) example --
 * -- SAMD21_XPLAINED_PRO --
 * -- Compiled: Aug 22 2017 18:05:18 --
 *	(APP)(INFO)Chip ID 1503a0
 *	(APP)(INFO)DriverVerInfo: 0x13521352
 * 	(APP)(INFO)Firmware ver   : 19.5.3 Svnrev 15136
 *	(APP)(INFO)Firmware Build Jun 19 2017 Time 17:38:42
 *	(APP)(INFO)Firmware Min driver ver : 19.3.0
 *	(APP)(INFO)Driver ver: 19.5.2
 *	(APP)(INFO)Driver built at Aug 22 2017  15:35:28
 *	main: connecting to WiFi AP DEMO_AP...
 *	wifi_cb: M2M_WIFI_CONNECTED
 *	wifi_cb: IP address is 192.168.43.210
 *	start_download: sending HTTP request...
 *	(APP)(INFO)Socket 0 session ID = 1
 *	http_client_callback: HTTP client socket connected.
 *	http_client_callback: request completed.
 *	http_client_callback: received response 200
 *	store_file_packet: received[804]
 *	store_file_packet_complete: file downloaded successfully.
 *	(APP)(INFO)Sock to delete <0>
 *	http_client_callback: disconnection reason:0
 *	 >> De-init WINC device to enter into download mode
 *	(APP)(INFO)Chip ID 1503a0
 *	>> WINC entered into download mode
 *	---> Start Certificate Upload on WINC
 *
 *	>>>Found Certificate:
 *						 >>>
 *
 *	>Start erasing...
 *	Done
 *
 *	> Writing the Root Certificate to SPI flash...
 *	--- Root Certificate written to SPI flash ---
 *
 *
 *	>>>Found Certificate:
 *						 >>>        AddTrust External CA Root
 *
 *	>Start erasing...
 *	Done
 *
 *	> Writing the Root Certificate to SPI flash...
 *	--- Root Certificate written to SPI flash ---
 *  >> All the certificates written
 * main: please re-init WINC to start wifi operations.
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

#include <errno.h>
#include "asf.h"
#include "main.h"
#include "stdio_serial.h"
#include "driver/include/m2m_wifi.h"
#include "socket/include/socket.h"
#include "iot/http/http_client.h"
#include "root_tls_cert/root_setup.h"
#include "root_tls_cert/tls_setup.h"
#include "programmer/programmer_apis.h"

#define STRING_EOL                      "\r\n"
#define STRING_HEADER                   "-- Certificate downloader via OTA (HTTPS) example --"STRING_EOL \
	"-- "BOARD_NAME " --"STRING_EOL	\
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

/** File download processing state. */
static download_state down_state = NOT_READY;
/** Http content length. */
static uint32_t http_file_size = 0;
/** Receiving content length. */
static uint32_t received_file_size = 0;
/** Certificates size. */
static uint32_t total_size = 0, cert_start_idx=0;
/** Stores all the certificates. */
static uint8_t certificate_bufer[CERTIFICATES_BUFFER_SIZE];

/** UART module for debug. */
static struct usart_module cdc_uart_module;

/** Instance of Timer module. */
struct sw_timer_module swt_module_inst;

/** Instance of HTTP client module. */
struct http_client_module http_client_module_inst;

/** http URL **/
static char http_url[MAIN_MAX_FILE_NAME_LENGTH];

tstrFileInfo root_tls_certs[NUM_OF_ROOT_TLS_CHAIN_CERTIFICATES];
static uint8 cert_idx = 0;
static sint8 burn_certificates(void);

/**
 * \brief Checking the USART buffer.
 *
 * Finding the new line character(\n or \r\n) in the USART buffer.
 * If buffer was overflowed, Sending the buffer.
 */


/**
 * \brief Initialize download state to not ready.
 */
static void init_state(void)
{
	down_state = NOT_READY;
}

/**
 * \brief Clear state parameter at download processing state.
 * \param[in] mask Check download_state.
 */
static void clear_state(download_state mask)
{
	down_state &= ~mask;
}

/**
 * \brief Add state parameter at download processing state.
 * \param[in] mask Check download_state.
 */
static void add_state(download_state mask)
{
	down_state |= mask;
}

/**
 * \brief File download processing state check.
 * \param[in] mask Check download_state.
 * \return true if this state is set, false otherwise.
 */

static inline bool is_state_set(download_state mask)
{
	return ((down_state & mask) != 0);
}

/**
 * \brief Start file download via HTTP connection.
 */
static void start_download(void)
{
	if (!is_state_set(WIFI_CONNECTED)) {
		printf("start_download: Wi-Fi is not connected.\r\n");
		return;
	}

	if (is_state_set(GET_REQUESTED)) {
		printf("start_download: request is sent already.\r\n");
		return;
	}

	if (is_state_set(DOWNLOADING)) {
		printf("start_download: running download already.\r\n");
		return;
	}

	/* Send the HTTP request. */
	printf("start_download: sending HTTP request...\r\n");
	http_client_module_inst.config.port = MAIN_HTTP_PORT_NUMBER;
	http_client_send_request(&http_client_module_inst, http_url, HTTP_METHOD_GET, NULL, NULL);
}

/**
 * \brief Complete file received.
 * \param[in] data Packet data.
 * \param[in] length Packet data length.
 */
static void store_file_packet_complete(void)
{
	printf("store_file_packet_complete: file downloaded successfully.\r\n");
	add_state(COMPLETED);
	clear_state(HTTP_DOWNLOAD_INITIATED);
	root_tls_certs[cert_idx].pu8FileData = &certificate_bufer[cert_start_idx];
	root_tls_certs[cert_idx].u32FileSz = received_file_size;
	cert_start_idx += received_file_size;
	cert_idx++;
}

/**
 * \brief Store received packet to file.
 * \param[in] data Packet data.
 * \param[in] length Packet data length.
 */
static void store_file_packet(char *data, uint32_t length)
{
	if ((data == NULL) || (length < 1)) {
		printf("store_file_packet: empty data.\r\n");
		return;
	}

	if (!is_state_set(DOWNLOADING)) {
		received_file_size = 0;
		add_state(DOWNLOADING);
	}

	if (data != NULL) {
		for(uint16_t idx=0;idx<length;idx++)
		  certificate_bufer[total_size++] = data[idx];
        received_file_size = received_file_size+length;

		printf("store_file_packet: received[%lu]\r\n", (unsigned long)length);
		if (received_file_size >= http_file_size) {
		  store_file_packet_complete();
		}
	}
}

/**
 * \brief Callback of the HTTP client.
 *
 * \param[in]  module_inst     Module instance of HTTP client module.
 * \param[in]  type            Type of event.
 * \param[in]  data            Data structure of the event. \refer http_client_data
 */
static void http_client_callback(struct http_client_module *module_inst, int type, union http_client_data *data)
{
	switch (type) {
	case HTTP_CLIENT_CALLBACK_SOCK_CONNECTED:
		printf("http_client_callback: HTTP client socket connected.\r\n");
		break;

	case HTTP_CLIENT_CALLBACK_REQUESTED:
		printf("http_client_callback: request completed.\r\n");
		add_state(GET_REQUESTED);
		break;

	case HTTP_CLIENT_CALLBACK_RECV_RESPONSE:
		printf("http_client_callback: received response %u\r\n",
				(unsigned int)data->recv_response.response_code);
		if ((unsigned int)data->recv_response.response_code == 200) {
			http_file_size = data->recv_response.content_length;
			received_file_size = 0;
		} 
		else {
			add_state(CANCELED);
			return;
		}
		if (data->recv_response.content_length <= MAIN_BUFFER_MAX_SIZE) {
			store_file_packet(data->recv_response.content, data->recv_response.content_length);
			add_state(COMPLETED);
		}
		break;

	case HTTP_CLIENT_CALLBACK_RECV_CHUNKED_DATA:
		store_file_packet(data->recv_chunked_data.data, data->recv_chunked_data.length);
		if (data->recv_chunked_data.is_complete) {
			add_state(COMPLETED);
		}

		break;

	case HTTP_CLIENT_CALLBACK_RECV_NO_CONTENT_LENGTH_DATA:
	    if(data->recv_chunked_data.is_complete)
		   store_file_packet_complete();
		else if ((unsigned int)data->recv_response.response_code == 200) {
			printf("http_client_callback: received response %u\r\n",
				(unsigned int)data->recv_response.response_code);
			http_file_size = 0xFFFFFFFF;  // There is no content length received
			received_file_size = 0;
		}
        break;

	case HTTP_CLIENT_CALLBACK_DISCONNECTED:
		printf("http_client_callback: disconnection reason:%d\r\n", data->disconnected.reason);

		/* If disconnect reason is equal to -ECONNRESET(-104),
		 * It means the server has closed the connection (timeout).
		 * This is normal operation.
		 */
		if (data->disconnected.reason == -ECONNRESET) {
		  add_state(CANCELED);
		}
		if (data->disconnected.reason == -EAGAIN) {
			/* Server has not responded. Retry immediately. */
			if (is_state_set(DOWNLOADING)) {
				clear_state(DOWNLOADING);
			}

			if (is_state_set(GET_REQUESTED)) {
				clear_state(GET_REQUESTED);
			}

			start_download();
		}

		break;
	}
}

/**
 * \brief Callback to get the data from socket.
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
static void socket_cb(SOCKET sock, uint8_t u8Msg, void *pvMsg)
{
	http_client_socket_event_handler(sock, u8Msg, pvMsg);
}

/**
 * \brief Callback for the gethostbyname function (DNS Resolution callback).
 * \param[in] pu8DomainName Domain name of the host.
 * \param[in] u32ServerIP Server IPv4 address encoded in NW byte order format. If it is Zero, then the DNS resolution failed.
 */
static void resolve_cb(uint8_t *pu8DomainName, uint32_t u32ServerIP)
{
	printf("resolve_cb: %s IP address is %d.%d.%d.%d\r\n\r\n", pu8DomainName,
			(int)IPV4_BYTE(u32ServerIP, 0), (int)IPV4_BYTE(u32ServerIP, 1),
			(int)IPV4_BYTE(u32ServerIP, 2), (int)IPV4_BYTE(u32ServerIP, 3));
	http_client_socket_resolve_handler(pu8DomainName, u32ServerIP);
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
static void wifi_cb(uint8_t u8MsgType, void *pvMsg)
{
	switch (u8MsgType) {
	case M2M_WIFI_RESP_CON_STATE_CHANGED:
	{
		tstrM2mWifiStateChanged *pstrWifiState = (tstrM2mWifiStateChanged *)pvMsg;
		if (pstrWifiState->u8CurrState == M2M_WIFI_CONNECTED) {
			printf("wifi_cb: M2M_WIFI_CONNECTED\r\n");
			m2m_wifi_request_dhcp_client();
		} else if (pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED) {
			printf("wifi_cb: M2M_WIFI_DISCONNECTED\r\n");
			clear_state(WIFI_CONNECTED);
			if (is_state_set(DOWNLOADING)) {
				clear_state(DOWNLOADING);
			}

			if (is_state_set(GET_REQUESTED)) {
				clear_state(GET_REQUESTED);
			}

			m2m_wifi_connect((char *)MAIN_WLAN_SSID, sizeof(MAIN_WLAN_SSID),
					MAIN_WLAN_AUTH, (char *)MAIN_WLAN_PSK, M2M_WIFI_CH_ALL);
		}

		break;
	}

	case M2M_WIFI_REQ_DHCP_CONF:
	{
		uint8_t *pu8IPAddress = (uint8_t *)pvMsg;
		printf("wifi_cb: IP address is %u.%u.%u.%u\r\n",
				pu8IPAddress[0], pu8IPAddress[1], pu8IPAddress[2], pu8IPAddress[3]);
		add_state(WIFI_CONNECTED);
		break;
	}

	default:
		break;
	}
}

/**
 * \brief Program certificates to WINC1500 memory.
 */
static sint8 burn_certificates(void)
{
	sint8	ret = 0;

	printf(">> De-init WINC device to enter into download mode\r\n");
	m2m_wifi_deinit(NULL);

    if(0 != m2m_wifi_download_mode()) {
		printf("Unable to initialize bus, Press RESET button to try again.\r\n");
		while(1);
	}

	printf(">> WINC entered into download mode\r\n");

	printf("---> Start Certificate Upload on WINC\r\n");

	for (uint8 idx=0; idx < NUM_OF_ROOT_TLS_CHAIN_CERTIFICATES; idx++)
	{
	   /* Write the Root certificates to WINC */
	   if(root_tls_certs_name[idx].cert_type == ROOT_CERT)			
	     ret += WriteRootCertificate(root_tls_certs[idx].pu8FileData,root_tls_certs[idx].u32FileSz);

	   /* Write the TLS RSA based certificates to WINC */
       if(root_tls_certs_name[idx].cert_type == TLS_RSA_CERT)
	   { 
       	 ret += WriteTlsCertificate(root_tls_certs[idx].pu8FileData,root_tls_certs[idx].u32FileSz,
		 &root_tls_certs[idx+1],root_tls_certs_name[idx].numOfChainCert);
		 idx = idx + root_tls_certs_name[idx].numOfChainCert;
	   }

	   /* Write the TLS ECC based certificates to WINC */
       if(root_tls_certs_name[idx].cert_type == TLS_ECC_CERT)
       {
	       ret += WriteTlsCertificate(NULL,0,&root_tls_certs[idx],root_tls_certs_name[idx].numOfChainCert);
		   idx = idx + root_tls_certs_name[idx].numOfChainCert -1;
       }
    }

	return ret;
}

/**
 * \brief initiate https download and write the cerficates to WINC.
 */
static uint8 certificate_download(void)
{
	/* Initiate certificate download from server */
	if (is_state_set(WIFI_CONNECTED) && !is_state_set(HTTP_DOWNLOAD_INITIATED))
	{
		if(cert_idx >= NUM_OF_ROOT_TLS_CHAIN_CERTIFICATES)
		{
		    if (burn_certificates() != M2M_SUCCESS)
			  printf(">> ERROR in Writing the certificates\r\n");
            else
			  printf(">> All the certificates written\r\n");
			  
			return 1;
		}
     	/* append certificate file name with URL */
	    strcpy(http_url,MAIN_HTTP_FILE_URL);
		strncat(http_url,(char*)root_tls_certs_name[cert_idx].filename,strlen((char*)root_tls_certs_name[cert_idx].filename));

		add_state(HTTP_DOWNLOAD_INITIATED);
	    clear_state(GET_REQUESTED);
		clear_state(DOWNLOADING);

		start_download();
	}
	return 0;
}

/**
 * \brief Configure UART console.
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
 * \brief Configure Timer module.
 */
static void configure_timer(void)
{
	struct sw_timer_config swt_conf;
	sw_timer_get_config_defaults(&swt_conf);

	sw_timer_init(&swt_module_inst, &swt_conf);
	sw_timer_enable(&swt_module_inst);
}

/**
 * \brief Configure HTTP client module.
 */
static void configure_http_client(void)
{
	struct http_client_config httpc_conf;
	int ret;

	http_client_get_config_defaults(&httpc_conf);

	httpc_conf.recv_buffer_size = MAIN_BUFFER_MAX_SIZE;
	httpc_conf.timer_inst = &swt_module_inst;
	httpc_conf.tls = 1;

	ret = http_client_init(&http_client_module_inst, &httpc_conf);
	if (ret < 0) {
		printf("configure_http_client: HTTP client initialization failed! (res %d)\r\n", ret);
		while (1) {
		} /* Loop forever. */
	}

	http_client_register_callback(&http_client_module_inst, http_client_callback);
}

/**
 * \brief Main application function.
 *
 * Application entry point.
 *
 * \return program return value.
 */
int main(void)
{
	tstrWifiInitParam param;
	int8_t ret;
	init_state();

	/* Initialize the board. */
	system_init();

	/* Initialize the UART console. */
	configure_console();
	printf(STRING_HEADER);

	/* Initialize the Timer. */
	configure_timer();

	/* Initialize the HTTP client service. */
	configure_http_client();

	/* Initialize the BSP. */
	nm_bsp_init();

	/* Initialize Wi-Fi parameters structure. */
	memset((uint8_t *)&param, 0, sizeof(tstrWifiInitParam));

	/* Initialize Wi-Fi driver with data and status callbacks. */
	param.pfAppWifiCb = wifi_cb;
	ret = m2m_wifi_init(&param);
	if (M2M_SUCCESS != ret) {
		printf("main: m2m_wifi_init call error! (res %d)\r\n", ret);
		while (1) {
		}
	}

	/* Initialize socket module. */
	socketInit();
	/* Register socket callback function. */
	registerSocketCallback(socket_cb, resolve_cb);

	/* Connect to router. */
	printf("main: connecting to WiFi AP %s...\r\n", (char *)MAIN_WLAN_SSID);
	m2m_wifi_connect((char *)MAIN_WLAN_SSID, sizeof(MAIN_WLAN_SSID), MAIN_WLAN_AUTH, (char *)MAIN_WLAN_PSK, M2M_WIFI_CH_ALL);

	while (!is_state_set(CANCELED)) {
		/* Handle pending events from network controller. */
		m2m_wifi_handle_events(NULL);
		/* Checks the timer timeout. */
		sw_timer_task(&swt_module_inst);
		/* Initiate certificate download from server */
		if(certificate_download())
		{
		  printf("main: please re-init WINC to start wifi operations.\r\n");
		  break;
		}
	}

	if(is_state_set(CANCELED))
	  printf("main: certificates download is terminated by server\r\n");

	while (1) {
	} /* Loop forever. */

	return 0;
}
