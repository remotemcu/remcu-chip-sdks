/**
 * \file
 *
 * \brief PubNub Example.
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
 * This example demonstrates the use of the SAMW25 Xplained Pro with I/O1 Xplained Pro
 * board to communicate with pubnub. <br>
 * It uses the following hardware:
 * - SAMW25 Xplained Pro.
 * - I/O1 Xplained Pro on EXT1.
 *
 * \section files Main Files
 * - main.c : Initialize the SAMW25 and communicate with PubNub cloud.
 *
 * \section usage Usage
 * -# To connect to the internet Access Point using hardcoded credentials
 * -# MAIN_ENABLE_WEB_PROVISIONING macro must be commented in main.h, then
 * -# set the following macro:
 * \code
 *    #define MAIN_WLAN_SSID     "SSID"
 *    #define MAIN_WLAN_AUTH     M2M_WIFI_SEC_WPA_PSK
 *    #define MAIN_WLAN_PSK      "PASSWORD"
 * \endcode
 *
 * -# Alternatively keep MAIN_ENABLE_WEB_PROVISIONING macro to enable the
 * -# Wi-Fi web provisioning and follow instruction displayed on UART.
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
 *    -- SAMW25 PubNub example --
 *    -- SAMW25_XPLAINED_PRO --
 *    -- Compiled: xxx xx xxxx xx:xx:xx --
 * \endcode
 *
 * -# Once the Wi-Fi is provisioned with internet access connect to PubNub
 * -# website http://www.pubnub.com and login with your account (free).
 * -# Start the application. Go to your Admin Portal and click on Debug Console.
 * -# From here:
 * -#  Enter Channel, Publish and Subscribe key as specified on the UART.
 * -#  Ensure SSL is enabled.
 * -#  Connect to the cloud by pressing the subscribe button.
 *
 * -# After reporting the first data to PubNub server, it is then possible to connect
 * -# to https://freeboard.io to configure a dashboard and to show reported data.
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
#include "common/include/nm_common.h"
#include "driver/include/m2m_wifi.h"
#include "socket/include/socket.h"
#include "main.h"
#include "PubNub.h"

#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- SAMW25 PubNub example --"STRING_EOL	\
	"-- "BOARD_NAME " --"STRING_EOL	\
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

#define IPV4_BYTE(val, index) ((val >> (index * 8)) & 0xFF)
#define HEX2ASCII(x) (((x) >= 10) ? (((x) - 10) + 'A') : ((x) + '0'))

typedef enum wifi_status {
	WifiStateInit,
	WifiStateWaitingProv,
	WifiStateConnecting,
	WifiStateConnected,
	WifiStateDisConnected
} wifi_status_t;

/** WiFi status variable. */
volatile wifi_status_t gWifiState = WifiStateInit;

/** SysTick counter to avoid busy wait delay. */
volatile uint32_t gu32MsTicks = 0;

/** Global counter delay for timer. */
static uint32_t gu32publishDelay = 0;
static uint32_t gu32subscribeDelay = 0;

/** PubNub global variables. */
static const char PubNubPublishKey[] = MAIN_PUBNUB_PUBLISH_KEY;
static const char PubNubSubscribeKey[] = MAIN_PUBNUB_SUBSCRIBE_KEY;
static char PubNubChannel[] = MAIN_PUBNUB_CHANNEL;
static pubnub_t *pPubNubCfg;

/** UART module for debug. */
struct adc_module adc_instance;

/** UART module for debug. */
static struct usart_module cdc_uart_module;

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
static void m2m_tcp_socket_handler(SOCKET sock, uint8_t u8Msg, void *pvMsg)
{
	handle_tcpip(sock, u8Msg, pvMsg);
}

/**
 * \brief Callback of gethostbyname function.
 *
 * \param[in] doamin_name Domain name.
 * \param[in] server_ip IP of server.
 */
static void socket_resolve_cb(uint8_t *hostName, uint32_t hostIp)
{
	printf("socket_resolve_cb: %s resolved with IP %d.%d.%d.%d\r\n",
			hostName,
			(int)IPV4_BYTE(hostIp, 0), (int)IPV4_BYTE(hostIp, 1),
			(int)IPV4_BYTE(hostIp, 2), (int)IPV4_BYTE(hostIp, 3));
	handle_dns_found((char *)hostName, hostIp);
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
static void m2m_wifi_state(uint8_t u8MsgType, void *pvMsg)
{
	switch (u8MsgType) {
	case M2M_WIFI_RESP_CON_STATE_CHANGED:
	{
		tstrM2mWifiStateChanged *pstrWifiState = (tstrM2mWifiStateChanged *)pvMsg;
		if (pstrWifiState->u8CurrState == M2M_WIFI_CONNECTED) {
			printf("m2m_wifi_state: M2M_WIFI_RESP_CON_STATE_CHANGED: CONNECTED\r\n");
		} else if (pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED) {
			printf("m2m_wifi_state: M2M_WIFI_RESP_CON_STATE_CHANGED: DISCONNECTED\r\n");
			if (WifiStateConnected == gWifiState) {
				gWifiState = WifiStateDisConnected;
				m2m_wifi_connect((char *)MAIN_WLAN_SSID, sizeof(MAIN_WLAN_SSID),
						MAIN_WLAN_AUTH, (char *)MAIN_WLAN_PSK, M2M_WIFI_CH_ALL);
			}
		}

		break;
	}

	case M2M_WIFI_REQ_DHCP_CONF:
	{
		uint8_t *pu8IPAddress = (uint8_t *)pvMsg;
		printf("m2m_wifi_state: M2M_WIFI_REQ_DHCP_CONF: IP is %u.%u.%u.%u\r\n",
				pu8IPAddress[0], pu8IPAddress[1], pu8IPAddress[2], pu8IPAddress[3]);
		gWifiState = WifiStateConnected;

		break;
	}

	default:
	{
		break;
	}
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
	usart_enable(&cdc_uart_module);
}

static void set_dev_name_to_mac(uint8 *name, uint8 *mac_addr)
{
	/* Name must be in the format WINC1500_00:00 */
	uint16 len;

	len = m2m_strlen(name);
	if (len >= 5) {
		name[len - 1] = HEX2ASCII((mac_addr[5] >> 0) & 0x0f);
		name[len - 2] = HEX2ASCII((mac_addr[5] >> 4) & 0x0f);
		name[len - 4] = HEX2ASCII((mac_addr[4] >> 0) & 0x0f);
		name[len - 5] = HEX2ASCII((mac_addr[4] >> 4) & 0x0f);
	}
}

static void configure_button_led(void)
{
	struct port_config pin_conf;
	port_get_config_defaults(&pin_conf);
	pin_conf.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(LED0_PIN, &pin_conf);
	port_pin_set_output_level(LED0_PIN, LED0_INACTIVE);
}

static void configure_light_sensor(void)
{
	struct adc_config config_adc;
	adc_get_config_defaults(&config_adc);

	config_adc.gain_factor = ADC_GAIN_FACTOR_DIV2;
	config_adc.clock_prescaler = ADC_CLOCK_PRESCALER_DIV512;
	config_adc.reference = ADC_REFERENCE_INTVCC1;
	config_adc.positive_input = ADC_POSITIVE_INPUT_PIN0;
	config_adc.resolution = ADC_RESOLUTION_12BIT;
	config_adc.clock_source = GCLK_GENERATOR_0;
	adc_init(&adc_instance, ADC, &config_adc);
	adc_enable(&adc_instance);
}

/*
 * \brief SysTick handler used to measure precise delay.
 */
void SysTick_Handler(void)
{
	gu32MsTicks++;
}

/**
 * \brief Main application function.
 *
 * Initialize board and WINC1500 Wi-Fi module.
 * Publish and subscribe event to pubnub.
 *
 * \return program return value.
 */
int main(void)
{
	tstrWifiInitParam wifiInitParam;
	int8_t s8InitStatus;
	uint8 mac_addr[6];
	uint8 u8IsMacAddrValid;
	double temperature = 0;
	uint16_t light = 0;
	char buf[256] = {0};

	/* Initialize the board. */
	system_init();

	/* Initialize the UART console. */
	configure_console();

	/* Output example information. */
	printf(STRING_HEADER);

	/* Initialize the delay driver. */
	delay_init();

	/* Enable SysTick interrupt for non busy wait delay. */
	if (SysTick_Config(system_cpu_clock_get_hz() / 1000)) {
		puts("main: SysTick configuration error!");
		while (1) {
		}
	}

	/* Initialize the Temperature Sensor. */
	at30tse_init();

	/* Initialize the Light Sensor. */
	configure_light_sensor();

	/* Initialize the Button/LED. */
	configure_button_led();

	/* Initialize the Wi-Fi BSP. */
	nm_bsp_init();

	/* Initialize Wi-Fi parameters structure. */
	memset((uint8_t *)&wifiInitParam, 0, sizeof(tstrWifiInitParam));
	wifiInitParam.pfAppWifiCb = m2m_wifi_state;

	/* Initialize WINC1500 Wi-Fi driver with data and status callbacks. */
	s8InitStatus = m2m_wifi_init(&wifiInitParam);
	if (M2M_SUCCESS != s8InitStatus) {
		printf("main: m2m_wifi_init call error!\r\n");
		while (1) {
		}
	}

	/* Initialize Socket API. */
	socketInit();
	registerSocketCallback(m2m_tcp_socket_handler, socket_resolve_cb);

	/* Read MAC address to customize device name and AP name if enabled. */
	m2m_wifi_get_otp_mac_address(mac_addr, &u8IsMacAddrValid);
	if (!u8IsMacAddrValid) {
		printf("main: MAC address fuse bit has not been configured!\r\n");
		printf("main: Use m2m_wifi_set_mac_address() API to set MAC address via software.\r\n");
		while (1) {
		}
	}
	m2m_wifi_get_mac_address(mac_addr);
	set_dev_name_to_mac((uint8 *)PubNubChannel, mac_addr);
	printf("\r\n");

	/* Initialize PubNub API. */
	printf("main: PubNub configured with following settings:\r\n");
	printf("main:  - Publish key: \"%s\", Subscribe key: \"%s\", Channel: \"%s\".\r\n\r\n",
	PubNubPublishKey, PubNubSubscribeKey, PubNubChannel);
	pPubNubCfg = pubnub_get_ctx(0);
	pubnub_init(pPubNubCfg, PubNubPublishKey, PubNubSubscribeKey);

	/* Connect to AP using Wi-Fi settings from main.h. */
	printf("main: Wi-Fi connecting to AP using hardcoded credentials...\r\n");
	m2m_wifi_connect((char *)MAIN_WLAN_SSID, sizeof(MAIN_WLAN_SSID),
			MAIN_WLAN_AUTH, (char *)MAIN_WLAN_PSK, M2M_WIFI_CH_ALL);

	while (1) {
		m2m_wifi_handle_events(NULL);

		/* Device is connected to AP. */
		if (gWifiState == WifiStateConnected) {
			/* PubNub: read event from the cloud. */
			if (pPubNubCfg->state == PS_IDLE) {
				/* Subscribe at the beginning and re-subscribe after every publish. */
				if ((pPubNubCfg->trans == PBTT_NONE) ||
				    (pPubNubCfg->trans == PBTT_PUBLISH && pPubNubCfg->last_result == PNR_OK)) {
					printf("main: subscribe event, PNR_OK\r\n");
					pubnub_subscribe(pPubNubCfg, PubNubChannel);				
				}

				/* Process any received messages from the channel we subscribed. */
				while (1) {
					char const *msg = pubnub_get(pPubNubCfg);
					if (NULL == msg) {
						/* No more message to process. */
						break;
					}

					if (0 == (strncmp(&msg[2], "led", strlen("led")))) {
						/* LED control message. */
						printf("main: received LED control message: %s\r\n", msg);
						if (0 == (strncmp(&msg[8], "on", strlen("on")))) {
							port_pin_set_output_level(LED0_PIN, LED0_ACTIVE);
						} else if (0 == (strncmp(&msg[8], "off", strlen("off")))) {
							port_pin_set_output_level(LED0_PIN, LED0_INACTIVE);
						}
					} else {
						/* Any other type of JSON message. */
						printf("main: received message: %s\r\n", msg);
					}
				}

				/* Subscribe to receive pending messages. */
				if (gu32MsTicks - gu32subscribeDelay > MAIN_PUBNUB_SUBSCRIBE_INTERVAL) {
					gu32subscribeDelay = gu32MsTicks;
					printf("main: subscribe event, interval.\r\n");
					pubnub_subscribe(pPubNubCfg, PubNubChannel);
				}
			}

			/* Publish the temperature measurements periodically. */
			if (gu32MsTicks - gu32publishDelay > MAIN_PUBNUB_PUBLISH_INTERVAL) {
				gu32publishDelay = gu32MsTicks;
				adc_start_conversion(&adc_instance);
				temperature = at30tse_read_temperature();
				adc_read(&adc_instance, &light);
				sprintf(buf, "{\"device\":\"%s\", \"temperature\":\"%d.%d\", \"light\":\"%d\", \"led\":\"%s\"}",
						PubNubChannel,
						(int)temperature, (int)((int)(temperature * 100) % 100),
						(((4096 - light) * 100) / 4096),
						port_pin_get_output_level(LED0_PIN) ? "0" : "1");
				printf("main: publish event: {%s}\r\n", buf);
				close(pPubNubCfg->tcp_socket);
				pPubNubCfg->tcp_socket = -1;
				pPubNubCfg->state = PS_IDLE;
				pPubNubCfg->last_result = PNR_IO_ERROR;
				pubnub_publish(pPubNubCfg, PubNubChannel, buf);
			}
		}
	}

	return 0;
}
