/**
 *
 * \file
 *
 * \brief WINC1500 MQTT chat example.
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
 * This example demonstrates the use of the WINC1500 with the SAMD21 Xplained Pro
 * board to implement an MQTT based chat.
 * It uses the following hardware:
 * - the SAMD21 Xplained Pro.
 * - the WINC1500 on EXT1.
 *
 * \section files Main Files
 * - main.c : Initialize the WINC1500, connect to MQTT broker and chat with the other devices.
 * - mqtt.h : Implementation of MQTT 3.1
 *
 * \section usage Usage
 * -# Configure below code in the main.h for AP information to be connected.
 * \code
 *    #define MAIN_WLAN_SSID         "DEMO_AP"
 *    #define MAIN_WLAN_AUTH         M2M_WIFI_SEC_WPA_PSK
 *    #define MAIN_WLAN_PSK          "12345678"
 * \endcode
 * -# Build the program and download it into the board.
 * -# On the computer, open and configure a terminal application as the follows.
 * \code
 *    Baud Rate : 115200
 *    Data : 8bit
 *    Parity bit : none
 *    Stop bit : 1bit
 *    Flow control : none
 *    Line-Ending style : LF or CR+LF
 * \endcode
 * -# Start the application.
 * -# In the terminal window, First of all enter the user name through the terminal window.
 * -# And after the text of the following is displayed, please enjoy the chat.
 * -# Initialization operations takes a few minutes according to the network environment.
 * \code
 *    Preparation of the chat has been completed.
 * \endcode
 *
 * \section known_issue Known Issue
 * -# The user name cannot contain space (' ').
 * -# Cannot send more than 128 bytes.
 * -# User name must be unique. If someone uses the same user name, Which one will be disconnected.
 * -# USART interface has not error detection procedure. So sometimes serial input is broken.
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
#include "MQTTClient/Wrapper/mqtt.h"
#include "socket/include/socket.h"

/* Application instruction phrase. */
#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- WINC1500 Wi-Fi MQTT chat example --"STRING_EOL \
	"-- "BOARD_NAME " --"STRING_EOL	\
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

/** UART module for debug. */
static struct usart_module cdc_uart_module;

/** User name of chat. */
char mqtt_user[64] = "";

/* Instance of MQTT service. */
static struct mqtt_module mqtt_inst;

/* Receive buffer of the MQTT service. */
static unsigned char mqtt_read_buffer[MAIN_MQTT_BUFFER_SIZE];
static unsigned char mqtt_send_buffer[MAIN_MQTT_BUFFER_SIZE];

/** UART buffer. */
static char uart_buffer[MAIN_CHAT_BUFFER_SIZE];

/** Written size of UART buffer. */
static int uart_buffer_written = 0;

/** A buffer of character from the serial. */
static uint16_t uart_ch_buffer;

/** Prototype for MQTT subscribe Callback */
void SubscribeHandler(MessageData *msgData);

/**
 * \brief Callback of USART input.
 *
 * \param[in] module USART module structure.
 */
static void uart_callback(const struct usart_module *const module)
{
	/* If input string is bigger than buffer size limit, ignore the excess part. */
	if (uart_buffer_written < MAIN_CHAT_BUFFER_SIZE) {
		uart_buffer[uart_buffer_written++] = uart_ch_buffer & 0xFF;
	}
}

/**
 * \brief Callback to get the Wi-Fi status update.
 *
 * \param[in] msg_type type of Wi-Fi notification. Possible types are:
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
static void wifi_callback(uint8 msg_type, void *msg_data)
{
	tstrM2mWifiStateChanged *msg_wifi_state;
	uint8 *msg_ip_addr;

	switch (msg_type) {
	case M2M_WIFI_RESP_CON_STATE_CHANGED:
		msg_wifi_state = (tstrM2mWifiStateChanged *)msg_data;
		if (msg_wifi_state->u8CurrState == M2M_WIFI_CONNECTED) {
			/* If Wi-Fi is connected. */
			printf("Wi-Fi connected\r\n");
			m2m_wifi_request_dhcp_client();
		} else if (msg_wifi_state->u8CurrState == M2M_WIFI_DISCONNECTED) {
			/* If Wi-Fi is disconnected. */
			printf("Wi-Fi disconnected\r\n");
			m2m_wifi_connect((char *)MAIN_WLAN_SSID, sizeof(MAIN_WLAN_SSID),
					MAIN_WLAN_AUTH, (char *)MAIN_WLAN_PSK, M2M_WIFI_CH_ALL);
			/* Disconnect from MQTT broker. */
			/* Force close the MQTT connection, because cannot send a disconnect message to the broker when network is broken. */
			mqtt_disconnect(&mqtt_inst, 1);
		}

		break;

	case M2M_WIFI_REQ_DHCP_CONF:
		msg_ip_addr = (uint8 *)msg_data;
		printf("Wi-Fi IP is %u.%u.%u.%u\r\n",
				msg_ip_addr[0], msg_ip_addr[1], msg_ip_addr[2], msg_ip_addr[3]);
		/* Try to connect to MQTT broker when Wi-Fi was connected. */
		mqtt_connect(&mqtt_inst, main_mqtt_broker);
		break;

	default:
		break;
	}
}

/**
 * \brief Callback to get the Socket event.
 *
 * \param[in] Socket descriptor.
 * \param[in] msg_type type of Socket notification. Possible types are:
 *  - [SOCKET_MSG_CONNECT](@ref SOCKET_MSG_CONNECT)
 *  - [SOCKET_MSG_BIND](@ref SOCKET_MSG_BIND)
 *  - [SOCKET_MSG_LISTEN](@ref SOCKET_MSG_LISTEN)
 *  - [SOCKET_MSG_ACCEPT](@ref SOCKET_MSG_ACCEPT)
 *  - [SOCKET_MSG_RECV](@ref SOCKET_MSG_RECV)
 *  - [SOCKET_MSG_SEND](@ref SOCKET_MSG_SEND)
 *  - [SOCKET_MSG_SENDTO](@ref SOCKET_MSG_SENDTO)
 *  - [SOCKET_MSG_RECVFROM](@ref SOCKET_MSG_RECVFROM)
 * \param[in] msg_data A structure contains notification informations.
 */
static void socket_event_handler(SOCKET sock, uint8_t msg_type, void *msg_data)
{
	mqtt_socket_event_handler(sock, msg_type, msg_data);
}

/**
 * \brief Callback of gethostbyname function.
 *
 * \param[in] doamin_name Domain name.
 * \param[in] server_ip IP of server.
 */
static void socket_resolve_handler(uint8_t *doamin_name, uint32_t server_ip)
{
	mqtt_socket_resolve_handler(doamin_name, server_ip);
}

/**
 * \brief Callback to receive the subscribed Message.
 *
 * \param[in] msgData Data to be received.
 */

void SubscribeHandler(MessageData *msgData)
{
	/* You received publish message which you had subscribed. */
	/* Print Topic and message */
	printf("\r\n %.*s",msgData->topicName->lenstring.len,msgData->topicName->lenstring.data);
	printf(" >> ");
	printf("%.*s",msgData->message->payloadlen,(char *)msgData->message->payload);	
}

/**
 * \brief Callback to get the MQTT status update.
 *
 * \param[in] conn_id instance id of connection which is being used.
 * \param[in] type type of MQTT notification. Possible types are:
 *  - [MQTT_CALLBACK_SOCK_CONNECTED](@ref MQTT_CALLBACK_SOCK_CONNECTED)
 *  - [MQTT_CALLBACK_CONNECTED](@ref MQTT_CALLBACK_CONNECTED)
 *  - [MQTT_CALLBACK_PUBLISHED](@ref MQTT_CALLBACK_PUBLISHED)
 *  - [MQTT_CALLBACK_SUBSCRIBED](@ref MQTT_CALLBACK_SUBSCRIBED)
 *  - [MQTT_CALLBACK_UNSUBSCRIBED](@ref MQTT_CALLBACK_UNSUBSCRIBED)
 *  - [MQTT_CALLBACK_DISCONNECTED](@ref MQTT_CALLBACK_DISCONNECTED)
 *  - [MQTT_CALLBACK_RECV_PUBLISH](@ref MQTT_CALLBACK_RECV_PUBLISH)
 * \param[in] data A structure contains notification informations. @ref mqtt_data
 */
static void mqtt_callback(struct mqtt_module *module_inst, int type, union mqtt_data *data)
{
	switch (type) {
	case MQTT_CALLBACK_SOCK_CONNECTED:
	{
		/*
		 * If connecting to broker server is complete successfully, Start sending CONNECT message of MQTT.
		 * Or else retry to connect to broker server.
		 */
		if (data->sock_connected.result >= 0) {
			printf("\r\nConnecting to Broker...");
			mqtt_connect_broker(module_inst, 1, NULL, NULL, mqtt_user, NULL, NULL, 0, 0, 0);
		} else {
			printf("Connect fail to server(%s)! retry it automatically.\r\n", main_mqtt_broker);
			mqtt_connect(module_inst, main_mqtt_broker); /* Retry that. */
		}
	}
	break;

	case MQTT_CALLBACK_CONNECTED:
		if (data->connected.result == MQTT_CONN_RESULT_ACCEPT) {
			/* Subscribe chat topic. */
			mqtt_subscribe(module_inst, MAIN_CHAT_TOPIC "#", 0, SubscribeHandler);
			/* Enable USART receiving callback. */
			usart_enable_callback(&cdc_uart_module, USART_CALLBACK_BUFFER_RECEIVED);
			printf("Preparation of the chat has been completed.\r\n");
		} else {
			/* Cannot connect for some reason. */
			printf("MQTT broker decline your access! error code %d\r\n", data->connected.result);
		}

		break;

	case MQTT_CALLBACK_DISCONNECTED:
		/* Stop timer and USART callback. */
		printf("MQTT disconnected\r\n");
		usart_disable_callback(&cdc_uart_module, USART_CALLBACK_BUFFER_RECEIVED);
		break;
	}
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
	/* Register USART callback for receiving user input. */
	usart_register_callback(&cdc_uart_module, (usart_callback_t)uart_callback, USART_CALLBACK_BUFFER_RECEIVED);
	usart_enable(&cdc_uart_module);
}

/**
 * \brief Configure MQTT service.
 */
static void configure_mqtt(void)
{
	struct mqtt_config mqtt_conf;
	int result;

	mqtt_get_config_defaults(&mqtt_conf);
	/* To use the MQTT service, it is necessary to always set the buffer and the timer. */
	mqtt_conf.read_buffer = mqtt_read_buffer;
	mqtt_conf.read_buffer_size = MAIN_MQTT_BUFFER_SIZE;
	mqtt_conf.send_buffer = mqtt_send_buffer;
	mqtt_conf.send_buffer_size = MAIN_MQTT_BUFFER_SIZE;
	
	result = mqtt_init(&mqtt_inst, &mqtt_conf);
	if (result < 0) {
		printf("MQTT initialization failed. Error code is (%d)\r\n", result);
		while (1) {
		}
	}

	result = mqtt_register_callback(&mqtt_inst, mqtt_callback);
	if (result < 0) {
		printf("MQTT register callback failed. Error code is (%d)\r\n", result);
		while (1) {
		}
	}
}

/**
 * \brief Checking the USART buffer.
 *
 * Finding the new line character(\n or \r\n) in the USART buffer.
 * If buffer was overflowed, Sending the buffer.
 */
static void check_usart_buffer(char *topic)
{
	int i;

	/* Publish the input string when newline was received or input string is bigger than buffer size limit. */
	if (uart_buffer_written >= MAIN_CHAT_BUFFER_SIZE) {
		mqtt_publish(&mqtt_inst, topic, uart_buffer, MAIN_CHAT_BUFFER_SIZE, 0, 0);
		uart_buffer_written = 0;
	} else {
		for (i = 0; i < uart_buffer_written; i++) {
			/* Find newline character ('\n' or '\r\n') and publish the previous string . */
			if (uart_buffer[i] == 0x0d) {
				mqtt_publish(&mqtt_inst, topic, uart_buffer, (i > 0 && uart_buffer[i - 1] == 0x0a) ? i - 1 : i, 0, 0);
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
	char topic[strlen(MAIN_CHAT_TOPIC) + MAIN_CHAT_USER_NAME_SIZE + 1];

	/* Initialize the board. */
	system_init();

	/* Initialize the UART console. */
	configure_console();

	/* Output example information */
	printf(STRING_HEADER);

	/* Initialize the MQTT service. */
	configure_mqtt();

	/* Initialize the BSP. */
	nm_bsp_init();

	/* Setup user name first */
	printf("Enter the user name (Max %d characters)\r\n", MAIN_CHAT_USER_NAME_SIZE);
	scanf("%64s", mqtt_user);
	printf("User : %s\r\n", mqtt_user);
	sprintf(topic, "%s%s", MAIN_CHAT_TOPIC, mqtt_user);
	printf("\r\nTopic : %s",topic);
	/* Initialize Wi-Fi parameters structure. */
	memset((uint8_t *)&param, 0, sizeof(tstrWifiInitParam));

	/* Initialize Wi-Fi driver with data and status callbacks. */
	param.pfAppWifiCb = wifi_callback; /* Set Wi-Fi event callback. */
	ret = m2m_wifi_init(&param);
	if (M2M_SUCCESS != ret) {
		printf("main: m2m_wifi_init call error!(%d)\r\n", ret);
		while (1) { /* Loop forever. */
		}
	}

	/* Initialize socket interface. */
	socketInit();
	registerSocketCallback(socket_event_handler, socket_resolve_handler);

	/* Connect to router. */
	m2m_wifi_connect((char *)MAIN_WLAN_SSID, sizeof(MAIN_WLAN_SSID),
			MAIN_WLAN_AUTH, (char *)MAIN_WLAN_PSK, M2M_WIFI_CH_ALL);

	if (SysTick_Config(system_cpu_clock_get_hz() / 1000)) 
	{
		puts("ERR>> Systick configuration error\r\n");
		while (1);
	}
	
	while (1) {
		/* Handle pending events from network controller. */
		m2m_wifi_handle_events(NULL);
		/* Try to read user input from USART. */
		usart_read_job(&cdc_uart_module, &uart_ch_buffer);
		/* Checks the USART buffer. */
		check_usart_buffer(topic);
		if(mqtt_inst.isConnected)
			mqtt_yield(&mqtt_inst, 0);
	}
}
