/**
 *
 * \file
 *
 * \brief WINC1500 Send Email Example.
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
 * board to send email using SMTP server.<br>
 * It uses the following hardware:
 * - the SAM Xplained Pro.
 * - the WINC1500 on EXT1.
 *
 * \section files Main Files
 * - main.c : Initialize the WINC1500 and send email.
 *
 * \section usage Usage
 * -# Configure below code in the main.h for AP information to be connected.
 * \code
 *    #define MAIN_WLAN_SSID                  "DEMO_AP"
 *    #define MAIN_WLAN_AUTH                  M2M_WIFI_SEC_WPA_PSK
 *    #define MAIN_WLAN_PSK                   "12345678"
 *
 *    #define MAIN_SENDER_RFC                 "<sender@gmail.com>"
 *    #define MAIN_RECIPIENT_RFC              "<recipient@gmail.com>"
 *    #define MAIN_TO_ADDRESS                 "recipient@gmail.com"
 *    #define MAIN_FROM_ADDRESS               "sender@gmail.com"
 *    #define MAIN_FROM_PASSWORD              "12345678"
 * \endcode
 *
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
 *    -- WINC1500 send email example --
 *    -- SAMD21_XPLAINED_PRO --
 *    -- Compiled: xxx xx xxxx xx:xx:xx --
 *    wifi_cb: M2M_WIFI_RESP_CON_STATE_CHANGED: CONNECTED
 *    wifi_cb: M2M_WIFI_REQ_DHCP_CONF: IP is xxx.xxx.xxx.xxx
 *    Host IP is 173.194.72.108
 *    Host Name is smtp.gmail.com
 *    Recipient email address is recipient@gmail.com
 *    main: Email was successfully sent.
 * \endcode
 *
 * \warning
 * \code
 *    For using the GMAIL, the root certificate must be installed.
 *    Download the root certificate using the root_certificate_downloader. (Refer to WINC1500 Software User Guide.)
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
#include "bsp/include/nm_bsp.h"
#include "driver/include/m2m_wifi.h"
#include "socket/include/socket.h"

#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- WINC1500 send email example --"STRING_EOL \
	"-- "BOARD_NAME " --"STRING_EOL	\
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

/** IP address of host. */
uint32_t gu32HostIp = 0;

uint8_t gu8SocketStatus = SocketInit;

/** SMTP information. */
uint8_t gu8SmtpStatus = SMTP_INIT;

/** SMTP email error information. */
int8_t gs8EmailError = MAIN_EMAIL_ERROR_NONE;

/** Send and receive buffer definition. */
char gcSendRecvBuffer[MAIN_SMTP_BUF_LEN];

/** Handler buffer definition. */
char gcHandlerBuffer[MAIN_SMTP_BUF_LEN];

/** Username basekey definition. */
char gcUserBasekey[128];

/** Password basekey definition. */
char gcPasswordBasekey[128];

/** Retry count. */
uint8_t gu8RetryCount = 0;

/** TCP client socket handler. */
static SOCKET tcp_client_socket = -1;

/** Wi-Fi status variable. */
static bool gbConnectedWifi = false;

/** Get host IP status variable. */
static bool gbHostIpByName = false;

extern void ConvertToBase64(char *pcOutStr, const char *pccInStr, int iLen);

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
 * \brief Creates and connects to an unsecure socket to be used for SMTP.
 *
 * \param[in] None.
 *
 * \return SOCK_ERR_NO_ERROR if success, -1 if socket create error, SOCK_ERR_INVALID if socket connect error.
 */
static int8_t smtpConnect(void)
{
	struct sockaddr_in addr_in;

	addr_in.sin_family = AF_INET;
	addr_in.sin_port = _htons(MAIN_GMAIL_HOST_PORT);
	addr_in.sin_addr.s_addr = gu32HostIp;

	/* Create secure socket */
	if (tcp_client_socket < 0) {
		tcp_client_socket = socket(AF_INET, SOCK_STREAM, SOCKET_FLAGS_SSL);
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
 * \brief Generates Base64 Key needed for authentication.
 *
 * \param[in] input is the string to be converted to base64.
 * \param[in] basekey1 is the base64 converted output.
 *
 * \return None.
 */
static void generateBase64Key(char *input, char *basekey)
{
	/* In case the input string needs to be modified before conversion, define */
	/*  new string to pass-through Use InputStr and *pIn */
	int16_t InputLen = strlen(input);
	char InputStr[128];
	char *pIn = (char *)InputStr;

	/* Generate Base64 string, right now is only the function input parameter */
	memcpy(pIn, input, InputLen);
	pIn += InputLen;

	/* to64frombits function */
	ConvertToBase64(basekey, (void *)InputStr, InputLen);
}

/**
 * \brief Sends an SMTP command and provides the server response.
 *
 * \param[in] socket is the socket descriptor to be used for sending.
 * \param[in] cmd is the string of the command.
 * \param[in] cmdpara is the command parameter.
 * \param[in] respBuf is a pointer to the SMTP response from the server.
 *
 * \return None.
 */
static void smtpSendRecv(long socket, char *cmd, char *cmdparam, char *respBuf)
{
	uint16_t sendLen = 0;
	memset(gcSendRecvBuffer, 0, sizeof(gcSendRecvBuffer));

	if (cmd != NULL) {
		sendLen = strlen(cmd);
		memcpy(gcSendRecvBuffer, cmd, strlen(cmd));
	}

	if (cmdparam != NULL) {
		memcpy(&gcSendRecvBuffer[sendLen], cmdparam, strlen(cmdparam));
		sendLen += strlen(cmdparam);
	}

	memcpy(&gcSendRecvBuffer[sendLen], cSmtpCrlf, strlen(cSmtpCrlf));
	sendLen += strlen(cSmtpCrlf);
	send(socket, gcSendRecvBuffer, sendLen, 0);

	if (respBuf != NULL) {
		memset(respBuf, 0, MAIN_SMTP_BUF_LEN);
		recv(socket, respBuf, MAIN_SMTP_BUF_LEN, 0);
	}
}

/**
 * \brief SMTP state handler.
 *
 * \param[in] None.
 *
 * \return MAIN_EMAIL_ERROR_NONE if success, MAIN_EMAIL_ERROR_FAILED if handler error.
 */
static int8_t smtpStateHandler(void)
{
	/* Check for acknowledge from SMTP server */
	switch (gu8SmtpStatus) {
	/* Send Introductory "HELO" to SMTP server */
	case SMTP_HELO:
		smtpSendRecv(tcp_client_socket, (char *)"HELO localhost", NULL, gcHandlerBuffer);
		break;

	/* Send request to server for authentication */
	case SMTP_AUTH:
		smtpSendRecv(tcp_client_socket, (char *)"AUTH LOGIN", NULL, gcHandlerBuffer);
		break;

	/* Handle Authentication with server username */
	case SMTP_AUTH_USERNAME:
		smtpSendRecv(tcp_client_socket, gcUserBasekey, NULL, gcHandlerBuffer);
		break;

	/* Handle Authentication with server password */
	case SMTP_AUTH_PASSWORD:
		smtpSendRecv(tcp_client_socket, gcPasswordBasekey, NULL, gcHandlerBuffer);
		break;

	/* Send source email to the SMTP server */
	case SMTP_FROM:
		smtpSendRecv(tcp_client_socket, (char *)cSmtpMailFrom, (char *)MAIN_SENDER_RFC, gcHandlerBuffer);
		break;

	/* Send the destination email to the SMTP server */
	case SMTP_RCPT:
		smtpSendRecv(tcp_client_socket, (char *)cSmtpRcpt, (char *)MAIN_RECIPIENT_RFC, gcHandlerBuffer);
		break;

	/* Send the "DATA" message to the server */
	case SMTP_DATA:
		smtpSendRecv(tcp_client_socket, (char *)cSmtpData, NULL, gcHandlerBuffer);
		break;

	/* Send actual Message, preceded by From, To and Subject */
	case SMTP_MESSAGE_SUBJECT:
		/* Start with E-Mail's "Subject:" field */
		smtpSendRecv(tcp_client_socket, (char *)cSmtpSubject, (char *)MAIN_EMAIL_SUBJECT, NULL);
		break;

	case SMTP_MESSAGE_TO:
		/* Add E-mail's "To:" field */
		printf("Recipient email address is %s\r\n", (char *)MAIN_TO_ADDRESS);
		smtpSendRecv(tcp_client_socket, (char *)cSmtpTo, (char *)MAIN_TO_ADDRESS, NULL);
		break;

	case SMTP_MESSAGE_FROM:
		/* Add E-mail's "From:" field */
		smtpSendRecv(tcp_client_socket, (char *)cSmtpFrom, (char *)MAIN_FROM_ADDRESS, NULL);
		break;

	case SMTP_MESSAGE_CRLF:
		/* Send CRLF */
		send(tcp_client_socket, (char *)cSmtpCrlf, strlen(cSmtpCrlf), 0);
		break;

	case SMTP_MESSAGE_BODY:
		/* Send body of message */
		smtpSendRecv(tcp_client_socket, (char *)MAIN_EMAIL_MSG, NULL, NULL);
		break;

	case SMTP_MESSAGE_DATAEND:
		/* End Message */
		smtpSendRecv(tcp_client_socket, (char *)cSmtpDataEnd, NULL, gcHandlerBuffer);
		break;

	case SMTP_QUIT:
		send(tcp_client_socket, (char *)cSmtpQuit, strlen(cSmtpQuit), 0);
		break;

	/* Error Handling for SMTP */
	case SMTP_ERROR:
		return MAIN_EMAIL_ERROR_FAILED;

	default:
		break;
	}
	return MAIN_EMAIL_ERROR_NONE;
}

/**
 * \brief Callback function of IP address.
 *
 * \param[in] hostName Domain name.
 * \param[in] hostIp Server IP.
 *
 * \return None.
 */
static void resolve_cb(uint8_t *hostName, uint32_t hostIp)
{
	gu32HostIp = hostIp;
	gbHostIpByName = true;
	printf("Host IP is %d.%d.%d.%d\r\n", (int)IPV4_BYTE(hostIp, 0), (int)IPV4_BYTE(hostIp, 1),
			(int)IPV4_BYTE(hostIp, 2), (int)IPV4_BYTE(hostIp, 3));
	printf("Host Name is %s\r\n", hostName);
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
	/* Check for socket event on TCP socket. */
	if (sock == tcp_client_socket) {
		switch (u8Msg) {
		case SOCKET_MSG_CONNECT:
		{
			tstrSocketConnectMsg *pstrConnect = (tstrSocketConnectMsg *)pvMsg;
			if (pstrConnect && pstrConnect->s8Error >= SOCK_ERR_NO_ERROR) {
				memset(gcHandlerBuffer, 0, MAIN_SMTP_BUF_LEN);
				recv(tcp_client_socket, gcHandlerBuffer, sizeof(gcHandlerBuffer), 0);
			} else {
				printf("SOCKET_MSG_CONNECT : connect error!\r\n");
				gu8SocketStatus = SocketError;
			}
		}
		break;

		case SOCKET_MSG_SEND:
		{
			switch (gu8SmtpStatus) {
			case SMTP_MESSAGE_SUBJECT:
				gu8SocketStatus = SocketConnect;
				gu8SmtpStatus = SMTP_MESSAGE_TO;
				break;

			case SMTP_MESSAGE_TO:
				gu8SocketStatus = SocketConnect;
				gu8SmtpStatus = SMTP_MESSAGE_FROM;
				break;

			case SMTP_MESSAGE_FROM:
				gu8SocketStatus = SocketConnect;
				gu8SmtpStatus = SMTP_MESSAGE_CRLF;
				break;

			case SMTP_MESSAGE_CRLF:
				gu8SocketStatus = SocketConnect;
				gu8SmtpStatus = SMTP_MESSAGE_BODY;
				break;

			case SMTP_MESSAGE_BODY:
				gu8SocketStatus = SocketConnect;
				gu8SmtpStatus = SMTP_MESSAGE_DATAEND;
				break;

			case SMTP_QUIT:
				gu8SocketStatus = SocketComplete;
				gu8SmtpStatus = SMTP_INIT;
				break;

			default:
				break;
			}
		}
		break;

		case SOCKET_MSG_RECV:
		{
			tstrSocketRecvMsg *pstrRecv = (tstrSocketRecvMsg *)pvMsg;

			if (gu8SocketStatus == SocketWaiting) {
				gu8SocketStatus = SocketConnect;
				switch (gu8SmtpStatus) {
				case SMTP_INIT:
					if (pstrRecv && pstrRecv->s16BufferSize > 0) {
						/* If buffer has 220 'OK' from server, set state to HELO */
						if (pstrRecv->pu8Buffer[0] == cSmtpCodeReady[0] &&
								pstrRecv->pu8Buffer[1] == cSmtpCodeReady[1] &&
								pstrRecv->pu8Buffer[2] == cSmtpCodeReady[2]) {
							gu8SmtpStatus = SMTP_HELO;
						} else {
							printf("No response from server.\r\n");
							gu8SmtpStatus = SMTP_ERROR;
							gs8EmailError = MAIN_EMAIL_ERROR_INIT;
						}
					} else {
						printf("SMTP_INIT : recv error!\r\n");
						gu8SmtpStatus = SMTP_ERROR;
						gs8EmailError = MAIN_EMAIL_ERROR_INIT;
					}

					break;

				case SMTP_HELO:
					if (pstrRecv && pstrRecv->s16BufferSize > 0) {
						/* If buffer has 220, set state to HELO */
						if (pstrRecv->pu8Buffer[0] == cSmtpCodeOkReply[0] &&
								pstrRecv->pu8Buffer[1] == cSmtpCodeOkReply[1] &&
								pstrRecv->pu8Buffer[2] == cSmtpCodeOkReply[2]) {
							gu8SmtpStatus = SMTP_AUTH;
						} else {
							printf("No response for HELO.\r\n");
							gu8SmtpStatus = SMTP_ERROR;
							gs8EmailError = MAIN_EMAIL_ERROR_HELO;
						}
					} else {
						printf("SMTP_HELO : recv error!\r\n");
						gu8SmtpStatus = SMTP_ERROR;
						gs8EmailError = MAIN_EMAIL_ERROR_HELO;
					}

					break;

				case SMTP_AUTH:
					if (pstrRecv && pstrRecv->s16BufferSize > 0) {
						/* Function handles authentication for all services */
						generateBase64Key((char *)MAIN_FROM_ADDRESS, gcUserBasekey);

						/* If buffer is 334, give username in base64 */
						if (pstrRecv->pu8Buffer[0] == cSmtpCodeAuthReply[0] &&
								pstrRecv->pu8Buffer[1] == cSmtpCodeAuthReply[1] &&
								pstrRecv->pu8Buffer[2] == cSmtpCodeAuthReply[2]) {
							gu8SmtpStatus = SMTP_AUTH_USERNAME;
						} else {
							printf("No response for authentication.\r\n");
							gu8SmtpStatus = SMTP_ERROR;
							gs8EmailError = MAIN_EMAIL_ERROR_AUTH;
						}
					} else {
						printf("SMTP_AUTH : recv error!\r\n");
						gu8SmtpStatus = SMTP_ERROR;
						gs8EmailError = MAIN_EMAIL_ERROR_AUTH;
					}

					break;

				case SMTP_AUTH_USERNAME:
					if (pstrRecv && pstrRecv->s16BufferSize > 0) {
						generateBase64Key((char *)MAIN_FROM_PASSWORD, gcPasswordBasekey);

						/* If buffer is 334, give password in base64 */
						if (pstrRecv->pu8Buffer[0] == cSmtpCodeAuthReply[0] &&
								pstrRecv->pu8Buffer[1] == cSmtpCodeAuthReply[1] &&
								pstrRecv->pu8Buffer[2] == cSmtpCodeAuthReply[2]) {
							gu8SmtpStatus = SMTP_AUTH_PASSWORD;
						} else {
							printf("No response for username authentication.\r\n");
							gu8SmtpStatus = SMTP_ERROR;
							gs8EmailError = MAIN_EMAIL_ERROR_AUTH_USERNAME;
						}
					} else {
						printf("SMTP_AUTH_USERNAME : recv error!\r\n");
						gu8SmtpStatus = SMTP_ERROR;
						gs8EmailError = MAIN_EMAIL_ERROR_AUTH_USERNAME;
					}

					break;

				case SMTP_AUTH_PASSWORD:
					if (pstrRecv && pstrRecv->s16BufferSize > 0) {
						if (pstrRecv->pu8Buffer[0] == cSmtpCodeAuthSuccess[0] &&
								pstrRecv->pu8Buffer[1] == cSmtpCodeAuthSuccess[1] &&
								pstrRecv->pu8Buffer[2] == cSmtpCodeAuthSuccess[2]) {
							/* Authentication was successful, set state to FROM */
							gu8SmtpStatus = SMTP_FROM;
						} else {
							printf("No response for password authentication.\r\n");
							gu8SmtpStatus = SMTP_ERROR;
							gs8EmailError = MAIN_EMAIL_ERROR_AUTH_PASSWORD;
						}
					} else {
						printf("SMTP_AUTH_PASSWORD : recv error!\r\n");
						gu8SmtpStatus = SMTP_ERROR;
						gs8EmailError = MAIN_EMAIL_ERROR_AUTH_PASSWORD;
					}

					break;

				case SMTP_FROM:
					if (pstrRecv && pstrRecv->s16BufferSize > 0) {
						/* If buffer has 250, set state to RCPT */
						if (pstrRecv->pu8Buffer[0] == cSmtpCodeOkReply[0] &&
								pstrRecv->pu8Buffer[1] == cSmtpCodeOkReply[1] &&
								pstrRecv->pu8Buffer[2] == cSmtpCodeOkReply[2]) {
							gu8SmtpStatus = SMTP_RCPT;
						} else {
							printf("No response for sender transmission.\r\n");
							gu8SmtpStatus = SMTP_ERROR;
							gs8EmailError = MAIN_EMAIL_ERROR_FROM;
						}
					} else {
						printf("SMTP_FROM : recv error!\r\n");
						gu8SmtpStatus = SMTP_ERROR;
						gs8EmailError = MAIN_EMAIL_ERROR_FROM;
					}

					break;

				case SMTP_RCPT:
					if (pstrRecv && pstrRecv->s16BufferSize > 0) {
						/* If buffer has 250, set state to DATA */
						if (pstrRecv->pu8Buffer[0] == cSmtpCodeOkReply[0] &&
								pstrRecv->pu8Buffer[1] == cSmtpCodeOkReply[1] &&
								pstrRecv->pu8Buffer[2] == cSmtpCodeOkReply[2]) {
							gu8SmtpStatus = SMTP_DATA;
						} else {
							printf("No response for recipient transmission.\r\n");
							gu8SmtpStatus = SMTP_ERROR;
							gs8EmailError = MAIN_EMAIL_ERROR_RCPT;
						}
					} else {
						printf("SMTP_RCPT : recv error!\r\n");
						gu8SmtpStatus = SMTP_ERROR;
						gs8EmailError = MAIN_EMAIL_ERROR_RCPT;
					}

					break;

				case SMTP_DATA:
					if (pstrRecv && pstrRecv->s16BufferSize > 0) {
						/* If buffer has 250, set state to DATA */
						if (pstrRecv->pu8Buffer[0] == cSmtpCodeIntermedReply[0] &&
								pstrRecv->pu8Buffer[1] == cSmtpCodeIntermedReply[1] &&
								pstrRecv->pu8Buffer[2] == cSmtpCodeIntermedReply[2]) {
							gu8SmtpStatus = SMTP_MESSAGE_SUBJECT;
						} else {
							printf("No response for data transmission.\r\n");
							gu8SmtpStatus = SMTP_ERROR;
							gs8EmailError = MAIN_EMAIL_ERROR_DATA;
						}
					} else {
						printf("SMTP_DATA : recv error!\r\n");
						gu8SmtpStatus = SMTP_ERROR;
						gs8EmailError = MAIN_EMAIL_ERROR_DATA;
					}

					break;

				case SMTP_MESSAGE_DATAEND:
					if (pstrRecv && pstrRecv->s16BufferSize > 0) {
						/* If buffer has 250, set state to DATA */
						if (pstrRecv->pu8Buffer[0] == cSmtpCodeOkReply[0] &&
								pstrRecv->pu8Buffer[1] == cSmtpCodeOkReply[1] &&
								pstrRecv->pu8Buffer[2] == cSmtpCodeOkReply[2]) {
							gu8SmtpStatus = SMTP_QUIT;
						} else {
							printf("No response for dataend transmission.\r\n");
							gu8SmtpStatus = SMTP_ERROR;
							gs8EmailError = MAIN_EMAIL_ERROR_MESSAGE;
						}
					} else {
						printf("SMTP_MESSAGE_DATAEND : recv error!\r\n");
						gu8SmtpStatus = SMTP_ERROR;
						gs8EmailError = MAIN_EMAIL_ERROR_MESSAGE;
					}

					break;

				default:
					break;
				}
			}
		}
		break;

		default:
			break;
		}
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
		if (pstrWifiState->u8CurrState == M2M_WIFI_CONNECTED) {
			printf("wifi_cb: M2M_WIFI_RESP_CON_STATE_CHANGED: CONNECTED\r\n");
			m2m_wifi_request_dhcp_client();
		} else if (pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED) {
			printf("wifi_cb: M2M_WIFI_RESP_CON_STATE_CHANGED: DISCONNECTED\r\n");
			gbConnectedWifi = false;
			gbHostIpByName = false;
			m2m_wifi_connect((char *)MAIN_WLAN_SSID, sizeof(MAIN_WLAN_SSID),
					MAIN_WLAN_AUTH, (char *)MAIN_WLAN_PSK, M2M_WIFI_CH_ALL);
		}

		break;
	}

	case M2M_WIFI_REQ_DHCP_CONF:
	{
		uint8_t *pu8IPAddress = (uint8_t *)pvMsg;
		/* Turn LED0 on to declare that IP address received. */
		printf("wifi_cb: M2M_WIFI_REQ_DHCP_CONF: IP is %u.%u.%u.%u\r\n",
				pu8IPAddress[0], pu8IPAddress[1], pu8IPAddress[2], pu8IPAddress[3]);
		gbConnectedWifi = true;

		/* Obtain the IP Address by network name */
		gethostbyname((uint8_t *)MAIN_GMAIL_HOST_NAME);
		break;
	}

	default:
	{
		break;
	}
	}
}

/**
 * \brief Close socket function.
 * \return None.
 */
static void close_socket(void)
{
	close(tcp_client_socket);
	tcp_client_socket = -1;
}

/**
 * \brief Retry SMTP server function.
 * \return None.
 */
static void retry_smtp_server(void)
{
	close_socket();
	gu8SocketStatus = SocketInit;
	gu8SmtpStatus = SMTP_INIT;
	gbHostIpByName = false;
	delay_ms(MAIN_WAITING_TIME);
	m2m_wifi_disconnect();
}

/**
 * \brief Main application function.
 *
 * Initialize system, UART console, network then start function of SMTP email client.
 *
 * \return Program return value.
 */
int main(void)
{
	tstrWifiInitParam param;
	int8_t ret;

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

	/* Initialize Socket module */
	socketInit();
	registerSocketCallback(socket_cb, resolve_cb);

	/* Connect to router. */
	m2m_wifi_connect((char *)MAIN_WLAN_SSID, sizeof(MAIN_WLAN_SSID),
			MAIN_WLAN_AUTH, (char *)MAIN_WLAN_PSK, M2M_WIFI_CH_ALL);

	while (1) {
		m2m_wifi_handle_events(NULL);

		if (gbConnectedWifi && gbHostIpByName) {
			if (gu8SocketStatus == SocketInit) {
				if (tcp_client_socket < 0) {
					gu8SocketStatus = SocketWaiting;
					if (smtpConnect() != SOCK_ERR_NO_ERROR) {
						gu8SocketStatus = SocketInit;
					}
				}
			} else if (gu8SocketStatus == SocketConnect) {
				gu8SocketStatus = SocketWaiting;
				if (smtpStateHandler() != MAIN_EMAIL_ERROR_NONE) {
					if (gs8EmailError == MAIN_EMAIL_ERROR_INIT) {
						gu8SocketStatus = SocketError;
					} else {
						close_socket();
						break;
					}
				}
			} else if (gu8SocketStatus == SocketComplete) {
				printf("main: Email was successfully sent.\r\n");
				ioport_set_pin_level(LED_0_PIN, false);
				close_socket();
				break;
			} else if (gu8SocketStatus == SocketError) {
				if (gu8RetryCount < MAIN_RETRY_COUNT) {
					gu8RetryCount++;
					printf("main: Waiting to connect server.(30 seconds)\r\n\r\n");
					retry_smtp_server();
				} else {
					printf("main: Failed retry to server. Press reset your board.\r\n");
					gu8RetryCount = 0;
					close_socket();
					break;
				}
			}
		}
	}

	return 0;
}
