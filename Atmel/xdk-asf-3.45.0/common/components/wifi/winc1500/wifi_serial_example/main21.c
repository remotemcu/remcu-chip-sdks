/**
 *
 * \file
 *
 * \brief WINC1500 Wi-Fi Serial example.
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
 * This example demonstrates how to emulate a serial port between two devices.
 * It reads input data from serial interface and sends it via Wi-Fi connection.
 * The EDBG interface will print out messages you typed or received, hence simulating
 * a chat application.
 * To run this example you need to prepare two pairs of SAMD21 Xplained Pro board with
 * WINC1500 extension (on EXT1 slot).
 *
 *
 * \section files Main Files
 * - main.c : Initialize device and USART interface. Create TCP sockets, send/receive messages and print out them on the EDBG interface.
 *
 * \section usage Usage
 * -# Configure below code in the main.h for AP to connect to.
 * \code
 *    #define MAIN_WLAN_SSID              "DEMO_AP"
 *    #define MAIN_WLAN_AUTH              M2M_WIFI_SEC_WPA_PSK
 *    #define MAIN_WLAN_PSK               "12345678"
 * \endcode
 * -# Build the program and download it into each board.
 * -# On the computer, open and configure a terminal application as the follows.
 * \code
 *    Baud Rate : 115200
 *    Data : 8bit
 *    Parity bit : none
 *    Stop bit : 1bit
 *    Flow control : none
 * \endcode
 * -# Start the application.
 * -# On the terminal window, the following text should appear:
 * \code
 *    -- WINC1500 Wi-Fi Serial example --
 *    -- SAMD21_XPLAINED_PRO --
 *    -- Compiled: xxx xx xxxx xx:xx:xx --
 *    Wi-Fi connected.
 *    Wi-Fi IP is xxx.xxx.xxx.xxx
 *    socket_cb: bind success.
 *    socket_cb: listen success.
 * \endcode
 * -# Check IP address of each board and execute connection on one device
 * by typing the below command on the terminal window with the other device's address.
 * Use prefix "<<" to execute local commands.
 * \code
 *    <<connect xxx.xxx.xxx.xxx
 * \endcode
 * -# If connected, the following text should appear:
 * \code
 *    [Local device]
 *    Connecting to [xxx.xxx.xxx.xxx] ...
 *    Socket connect success.
 *
 *    [Remote device]
 *    Socket accept success.
 * \endcode
 * -# Type messages on the terminal window and you will see the sent/received messages.
 * -# You can control LED on the remote device by typing the following command.
 * Use prefix ">>" to execute remote commands.
 * \code
 *    >>control ledon
 *    or
 *    >>control ledoff
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
#include "driver/include/m2m_wifi.h"
#include "socket/include/socket.h"

/** \name Strings for printing banner. */
/* \{ */
#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- WINC1500 Wi-Fi Serial example --"STRING_EOL \
	"-- "BOARD_NAME " --"STRING_EOL	\
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL
/* \} */

/** \name Macro for printing local/remote messages. */
/* \{ */
#define PRINT_LOCAL_MSG(msg) printf("[Local] %s\r\n", msg)     /**< Local message printing. */
#define PRINT_REMOTE_MSG(msg) printf("\t[Remote] %s\r\n", msg) /**< Remote message printing. */
/* \} */

/** \name Command indicator. */
/* \{ */
#define INDICATOR_STRING_LEN 2    /**< Length of command indicator string. */
#define LOCAL_CMD_INDICATOR "<<"  /**< Indicator string for local command. */
#define REMOTE_CMD_INDICATOR ">>" /**< Indicator string for remote command. */
/* \} */

/** Command handler function type. */
typedef void (*cmd_handler)(void *pMsg);

/** User command structure. */
struct user_cmd {
	const char *cmd_string;           /**< Pointer to the command string buffer. */
	void (*cmd_handler)(void *pMsg);  /**< Pointer to the command handler function. */
};

/** User command index. */
enum {
	CMD_ID_LOCAL_START = 0,
	CMD_ID_L_HELP = CMD_ID_LOCAL_START,     /**< Help command index. */
	CMD_ID_L_CONNECT,                       /**< Connect command index. */
	CMD_ID_L_DISCONNECT,                    /**< Close command index. */
	CMD_ID_LOCAL_END,
	CMD_ID_REMOTE_START = CMD_ID_LOCAL_END,
	CMD_ID_R_CONTROL = CMD_ID_REMOTE_START, /**< Control remote device command index. */
	CMD_ID_REMOTE_END,
	CMD_ID_MAX = CMD_ID_REMOTE_END
};

/** UART module for debug. */
static struct usart_module cdc_uart_module;

/** UART buffer. */
static char uart_buffer[MAIN_CHAT_BUFFER_SIZE];

/** Written size to UART buffer. */
static uint16_t uart_buffer_written = 0;

/** Buffer of a character from the serial. */
static uint16_t uart_ch_buffer;

/** Socket buffer definition. */
static uint8_t gau8SocketBuffer[MAIN_CHAT_BUFFER_SIZE];

/** TCP server socket. */
static SOCKET tcp_server_socket = -1;

/** TCP client socket. */
static SOCKET tcp_client_socket = -1;

/** Flag for sock connection state. */
static uint8_t tcp_connected = 0;

/** Wi-Fi connection state. */
static uint8_t wifi_connected = M2M_WIFI_DISCONNECTED;

/**
 * \brief Help command handler function. Print usage message.
 *
 * \param[in] pMsg Not used.
 */
void help_cmd_handler(void *pMsg);

/**
 * \brief Connection command handler function.
 * Retrieve IP address from the argument, create TCP client socket and connect to the remote device with the IP.
 *
 * \param[in] pMsg Pointer to the remote IP address string.
 */
void connect_cmd_handler(void *pMsg);

/**
 * \brief Socket close command handler function.
 * Close client socket.
 *
 * \param[in] pMsg Not used.
 */
void disconnect_cmd_handler(void *pMsg);

/**
 * \brief Remote control command handler function.
 *
 * \param[in] pMsg Pointer to the option string.
 */
void control_cmd_handler(void *pMsg);

/**
 * \brief Check whether the message is a command and execute the command handler function.
 *
 * \param[in] buffer Pointer to the input message buffer.
 * \param[in] remote If local device command then 0 otherwise 1.
 */
uint8_t parse_command(char *buffer, uint8_t remote);

/**
 * \brief Parse input message from serial interface.
 * Check whether the message is a command or send the message to the remote device.
 */
void handle_input_message(void);

/** User command list. */
static struct user_cmd cmd_list[CMD_ID_MAX] = {
	/* Local device command list. */
	{"help", help_cmd_handler},               /**< Help command. */
	{"connect", connect_cmd_handler},        /**< Connect command. */
	{"disconnect", disconnect_cmd_handler},  /**< disconnect command. */
	/* Remote device command list. */
	{"control", control_cmd_handler}     /**< Control remote device command. */
};

void help_cmd_handler(void *pMsg)
{
	printf("\r\n================================ Usage ================================");
	printf("\r\nLocal command. (Use \"<<\" indicator).");
	printf("\r\n  <<help\t\t\t\t:Print usage.");
	printf("\r\n  <<connect [ip_address]\t\t:Connect to a TCP server with the given ip_address.");
	printf("\r\n  <<disconnect\t\t\t:Close TCP client socket.");
	printf("\r\nRemote command. (Use \">>\" indicator).");
	printf("\r\n  >>control [ledon] [ledoff]\t:Control the remote device.");
	printf("\r\n=======================================================================\r\n");
}

void connect_cmd_handler(void *pMsg)
{
	char *arg = (char *)pMsg;
	uint32_t address;
	struct sockaddr_in addr;

	if (tcp_client_socket >= 0) {
		printf("Already connected to a remote device.\r\n");
		return;
	}

	/* Create TCP client socket. */
	if ((tcp_client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Failed to create TCP client socket.\r\n");
		return;
	}

	while (*arg == ' ') {
		arg++;
	}
	if ((address = nmi_inet_addr(arg)) == 0) {
		printf("Invalid IP address.\r\n");
		return;
	}

	/* Connect to the server. */
	printf("Connecting to [%s] ...\r\n", arg);
	addr.sin_family = AF_INET;
	addr.sin_port = _htons(MAIN_WIFI_M2M_SERVER_PORT);
	addr.sin_addr.s_addr = address; /* _htonl(address); */
	if (connect(tcp_client_socket, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) < 0) {
		printf("Failed to connect to the server.\r\n");
		close(tcp_client_socket);
		tcp_client_socket = 1;
		return;
	}
}

void disconnect_cmd_handler(void *pMsg)
{
	if (tcp_client_socket >= 0) {
		printf("Close client socket to disconnect.\r\n");
		close(tcp_client_socket);
		tcp_client_socket = -1;
	}

	tcp_connected = 0;
}

void control_cmd_handler(void *pMsg)
{
	char *arg = (char *)pMsg;

	while (*arg == ' ') {
		arg++;
	}

	if (!strcmp(arg, "ledon")) {
		port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
	} else if (!strcmp(arg, "ledoff")) {
		port_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);
	} else {
		printf("Not supported remote command!\r\n");
	}
}

uint8_t parse_command(char *buffer, uint8_t remote)
{
	char cmd_buf[MAIN_CHAT_BUFFER_SIZE];
	int i, i_st, i_ed;

	if (remote == 0) {
		i_st = CMD_ID_LOCAL_START;
		i_ed = CMD_ID_LOCAL_END;
	} else {
		i_st = CMD_ID_REMOTE_START;
		i_ed = CMD_ID_REMOTE_END;
	}

	for (i = 0; i < MAIN_CHAT_BUFFER_SIZE; i++) {
		if (buffer[i] == ' ' || buffer[i] == 0) {
			cmd_buf[i] = 0;
			break;
		}

		cmd_buf[i] = buffer[i];
	}

	for (i = i_st; i < i_ed; i++) {
		if (!strcmp(cmd_list[i].cmd_string, cmd_buf)) {
			cmd_list[i].cmd_handler(buffer + strlen(cmd_list[i].cmd_string) + 1);
			break;
		}
	}
	if (i == i_ed) {
		return CMD_ID_MAX;
	}

	return i;
}

void handle_input_message(void)
{
	int i, msg_len;

	if (uart_buffer_written == 0) {
		return;
	} else if (uart_buffer_written >= MAIN_CHAT_BUFFER_SIZE) {
		PRINT_LOCAL_MSG(uart_buffer);
		send(tcp_client_socket, uart_buffer, MAIN_CHAT_BUFFER_SIZE, 0);
		uart_buffer_written = 0;
	} else {
		for (i = 0; i < uart_buffer_written; i++) {
			/* Find newline character ('\n' or '\r\n') and publish the previous string . */
			if (uart_buffer[i] == '\n') {
				/* Remove LF and CR from uart buffer.*/
				if (uart_buffer[i - 1] == '\r') {
					msg_len = i - 1;
				} else {
					msg_len = i;
				}

				uart_buffer[msg_len] = 0;

				/* Check command for local device. */
				if (!strncmp(uart_buffer, LOCAL_CMD_INDICATOR, INDICATOR_STRING_LEN)) {
					parse_command(&uart_buffer[INDICATOR_STRING_LEN], 0);
					uart_buffer_written = 0;
					return;
				}

				/* Check command for remote device. */
				if (!strncmp(uart_buffer, REMOTE_CMD_INDICATOR, INDICATOR_STRING_LEN)) {
					if (tcp_connected == 1) {
						send(tcp_client_socket, &uart_buffer[0], msg_len + 1, 0);
					}

					uart_buffer_written = 0;
					return;
				}

				/* Print message on the local console and send it to the remote host. */
				if (tcp_connected == 1) {
					PRINT_LOCAL_MSG(uart_buffer);
					send(tcp_client_socket, uart_buffer, msg_len + 1, 0);
				} else {
					printf("[No Connection]%s\r\n", uart_buffer);
				}

				/* Move remain data to start of the buffer. */
				if (uart_buffer_written > i + 1) {
					memmove(uart_buffer, uart_buffer + i + 1, uart_buffer_written - i - 1);
					uart_buffer_written = uart_buffer_written - i - 1;
				} else {
					uart_buffer_written = 0;
				}

				break;
			}
		}
	}
}

/**
 * \brief Callback of USART input.
 *
 * \param[in] module USART module structure.
 */
static void uart_callback(const struct usart_module *const module)
{
	static uint8_t ignore_cnt = 0;
	if (ignore_cnt > 0) {
		ignore_cnt--;
		return;
	} else if (uart_ch_buffer == 0x1B) { /* Ignore escape and following 2 characters. */
		ignore_cnt = 2;
		return;
	} else if (uart_ch_buffer == 0x8) { /* Ignore backspace. */
		return;
	}

	/* If input string is bigger than buffer size limit, ignore the excess part. */
	if (uart_buffer_written < MAIN_CHAT_BUFFER_SIZE) {
		uart_buffer[uart_buffer_written++] = uart_ch_buffer & 0xFF;
	}
}

/**
 * \brief Callback to get the Socket event.
 *
 * \param[in] sock Socket descriptor.
 * \param[in] u8Msg Type of Socket notification. Possible types are:
 *  - [SOCKET_MSG_CONNECT](@ref SOCKET_MSG_CONNECT)
 *  - [SOCKET_MSG_BIND](@ref SOCKET_MSG_BIND)
 *  - [SOCKET_MSG_LISTEN](@ref SOCKET_MSG_LISTEN)
 *  - [SOCKET_MSG_ACCEPT](@ref SOCKET_MSG_ACCEPT)
 *  - [SOCKET_MSG_RECV](@ref SOCKET_MSG_RECV)
 *  - [SOCKET_MSG_SEND](@ref SOCKET_MSG_SEND)
 *  - [SOCKET_MSG_SENDTO](@ref SOCKET_MSG_SENDTO)
 *  - [SOCKET_MSG_RECVFROM](@ref SOCKET_MSG_RECVFROM)
 * \param[in] pvMsg A structure contains notification informations.
 */
static void socket_cb(SOCKET sock, uint8_t u8Msg, void *pvMsg)
{
	switch (u8Msg) {
	/* Socket bind. */
	case SOCKET_MSG_BIND:
	{
		tstrSocketBindMsg *pstrBind = (tstrSocketBindMsg *)pvMsg;
		if (pstrBind && pstrBind->status == 0) {
			printf("socket_cb: bind success.\r\n");
			listen(tcp_server_socket, 0);
		} else {
			printf("socket_cb: bind error!\r\n");
		}
	}
	break;

	/* Socket listen. */
	case SOCKET_MSG_LISTEN:
	{
		tstrSocketListenMsg *pstrListen = (tstrSocketListenMsg *)pvMsg;
		if (pstrListen && pstrListen->status == 0) {
			printf("socket_cb: listen success.\r\n");
			accept(tcp_server_socket, NULL, NULL);
		} else {
			printf("socket_cb: listen error!\r\n");
		}
	}
	break;

	/* Connect accept. */
	case SOCKET_MSG_ACCEPT:
	{
		tstrSocketAcceptMsg *pstrAccept = (tstrSocketAcceptMsg *)pvMsg;
		if (pstrAccept) {
			printf("socket_cb: accept success.\r\n");
			accept(tcp_server_socket, NULL, NULL);
			tcp_client_socket = pstrAccept->sock;
			tcp_connected = 1;
			recv(tcp_client_socket, gau8SocketBuffer, sizeof(gau8SocketBuffer), 0);
		} else {
			printf("socket_cb: accept error!\r\n");
			close(tcp_server_socket);
			tcp_server_socket = -1;
			tcp_connected = 0;
		}
	}
	break;

	/* Socket connected. */
	case SOCKET_MSG_CONNECT:
	{
		tstrSocketConnectMsg *pstrConnect = (tstrSocketConnectMsg *)pvMsg;
		if (pstrConnect && pstrConnect->s8Error >= 0) {
			printf("socket_cb: connect success.\r\n");
			tcp_connected = 1;
			recv(tcp_client_socket, gau8SocketBuffer, sizeof(gau8SocketBuffer), 0);
		} else {
			printf("socket_cb: connect error!\r\n");
			tcp_connected = 0;
		}
	}
	break;

	/* Message send. */
	case SOCKET_MSG_SEND:
	{
		recv(tcp_client_socket, gau8SocketBuffer, sizeof(gau8SocketBuffer), 0);
	}
	break;

	/* Message receive. */
	case SOCKET_MSG_RECV:
	{
		tstrSocketRecvMsg *pstrRecv = (tstrSocketRecvMsg *)pvMsg;
		if (pstrRecv && pstrRecv->s16BufferSize > 0) {
			if (!strncmp((char *)pstrRecv->pu8Buffer, REMOTE_CMD_INDICATOR, INDICATOR_STRING_LEN)) {
				parse_command((char *)(pstrRecv->pu8Buffer + INDICATOR_STRING_LEN), 1);
			} else {
				PRINT_REMOTE_MSG(pstrRecv->pu8Buffer);
			}
		} else {
			printf("socket_cb: recv error!\r\n");
			disconnect_cmd_handler(NULL);
			break;
		}

		recv(tcp_client_socket, gau8SocketBuffer, sizeof(gau8SocketBuffer), 0);
	}
	break;

	default:
		break;
	}
}

/**
 * \brief Callback to get the Wi-Fi status update.
 *
 * \param[in] msg_type Type of Wi-Fi notification. Possible types are:
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
 * \param[in] msg_data A pointer to a buffer containing the notification parameters
 * (if any). It should be casted to the correct data type corresponding to the
 * notification type. Existing types are:
 *  - tstrM2mWifiStateChanged
 *  - tstrM2MWPSInfo
 *  - tstrM2MP2pResp
 *  - tstrM2MAPResp
 *  - tstrM2mScanDone
 *  - tstrM2mWifiscanResult
 */
static void wifi_cb(uint8 msg_type, void *msg_data)
{
	switch (msg_type) {
	case M2M_WIFI_RESP_CON_STATE_CHANGED:
	{
		tstrM2mWifiStateChanged *msg_wifi_state = (tstrM2mWifiStateChanged *)msg_data;
		if (msg_wifi_state->u8CurrState == M2M_WIFI_CONNECTED) {
			/* If Wi-Fi is connected. */
			printf("Wi-Fi connected.\r\n");
			m2m_wifi_request_dhcp_client();
		} else if (msg_wifi_state->u8CurrState == M2M_WIFI_DISCONNECTED) {
			/* If Wi-Fi is disconnected. */
			printf("Wi-Fi disconnected!\r\n");
			wifi_connected = M2M_WIFI_DISCONNECTED;
			m2m_wifi_connect((char *)MAIN_WLAN_SSID, sizeof(MAIN_WLAN_SSID),
					MAIN_WLAN_AUTH, (char *)MAIN_WLAN_PSK, M2M_WIFI_CH_ALL);
		}
	}
	break;

	case M2M_WIFI_REQ_DHCP_CONF:
	{
		uint8 *pu8IPAddress = (uint8 *)msg_data;
		wifi_connected = M2M_WIFI_CONNECTED;
		printf("Wi-Fi IP is %u.%u.%u.%u\r\n", pu8IPAddress[0], pu8IPAddress[1], pu8IPAddress[2], pu8IPAddress[3]);
	}
	break;

	default:
		break;
	}
}

/**
 * \brief Configure UART console with callback function.
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
	/* Register USART callback for receiving user input. */
	usart_register_callback(&cdc_uart_module, (usart_callback_t)uart_callback, USART_CALLBACK_BUFFER_RECEIVED);
	usart_enable_callback(&cdc_uart_module, USART_CALLBACK_BUFFER_RECEIVED);
	usart_enable(&cdc_uart_module);
}

/**
 * \brief Main application function.
 *
 * Application entry point.
 * Initialize board and WINC1500 Wi-Fi module.
 * Read input data from serial interface and sent it to the remote device.
 *
 * \return program return value.
 */
int main(void)
{
	tstrWifiInitParam param;
	int8_t ret;

	/* Initialize the board. */
	system_init();

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

	/* Initialize socket interface. */
	socketInit();
	registerSocketCallback(socket_cb, NULL);

	/* Connect to router. */
	m2m_wifi_connect((char *)MAIN_WLAN_SSID, sizeof(MAIN_WLAN_SSID),
			MAIN_WLAN_AUTH, (char *)MAIN_WLAN_PSK, M2M_WIFI_CH_ALL);

	while (1) {
		if (wifi_connected == M2M_WIFI_CONNECTED && tcp_server_socket < 0) {
			struct sockaddr_in addr;

			/* Create TCP server socket. */
			if ((tcp_server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
				printf("Failed to create TCP server socket!\r\n");
				continue;
			}

			/* Initialize socket address structure and bind service. */
			addr.sin_family = AF_INET;
			addr.sin_port = _htons(MAIN_WIFI_M2M_SERVER_PORT);
			addr.sin_addr.s_addr = 0;
			bind(tcp_server_socket, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
		}

		/* Handle pending events from network controller. */
		m2m_wifi_handle_events(NULL);

		/* Try to read user input from EDBG. */
		usart_read_job(&cdc_uart_module, &uart_ch_buffer);

		/* Handle user message from EDBG. */
		handle_input_message();
	}

	return 0;
}
