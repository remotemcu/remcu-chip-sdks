/**
 * \file
 *
 * \brief IoT Cloud Demo.
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
 * This example demonstrates the use of the SAM Xplained Pro with I/O1 Xplained Pro
 * board to communicate with Atmel IoT Android app & PubNub cloud. <br>
 * It uses the following hardware:
 * - SAM Xplained Pro.
 * - the WINC1500 module on EXT1.
 *
 * \section files Main Files
 * - main.c : Initialize the SAM board and communicate with Android App & PubNub cloud.
 *
 * \section usage Usage
 * -# To connect the SAM board to the internet Access Point over Wi-Fi, the user must
 * -# provide credentials (typically SSID and passphrase). To do so, the user must enter 
 * -# provisioning mode by holding SW0 button down for at least 3s. Led0 will start to 
 * -# blink fast as soon as provisioning mode is activated. Finally two methods are
 * -# avalaible to input credentials:
 * -# - Using provisioning web page (user must connect to AP name WINC1500:XX_XX and
 * -#   open a browser to atmelconfig.com) 
 * -# - Using Android application (user must click on AP name WINC1500:XX_XX and fill up
 * -#   the credential popup)
 *
 * -# Provisioning AP name, sensor name and pubnub channel are all configured as
 * -# WINC1500:XX_XX where XX_XX is essentially the last four digits of the MAC address.
 * -# WINC1500 MAC address is printed on the sticker on top of the module.
 *
 * -# Credentials need only to be provided once, as they are stored in non volatile
 * -# memory inside the WINC1500. It is still possible to enter provisioning mode again
 * -# to connect to another Access Point by holding down the SW0 button for 3s.
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
 *    -- IoT Cloud Demo --
 *    -- SAMXXX_XPLAINED_PRO --
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
#include "demo.h"
#include "PubNub.h"

#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- IoT Cloud Demo --"STRING_EOL	\
	"-- "BOARD_NAME " --"STRING_EOL	\
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

#define IPV4_BYTE(val, index) ((val >> (index * 8)) & 0xFF)
#define HEX2ASCII(x) (((x) >= 10) ? (((x) - 10) + 'A') : ((x) + '0'))

/** Message format definitions. */
typedef struct s_msg_user_input {
    uint8_t channel;
	uint8_t security;
	char* password;
	char* SSID;
} t_msg_user_input;

typedef struct s_msg_temp_keepalive {
	uint8_t id0;
	uint8_t id1;
	uint8_t name[16];
	uint8_t type;
} t_msg_temp_keepalive;

typedef struct s_msg_temp_report {
	uint8_t id0;
	uint8_t id1;
	uint8_t name[16];
	uint16_t led;
	uint32_t temp;
	uint32_t light;
} t_msg_temp_report;

typedef struct s_msg_temp_prov {
	uint8_t id0;
	uint8_t id1;
	uint8_t ssid[64];
	uint8_t pass[64];
	uint8_t sec;
} t_msg_temp_prov;

/** Message format declarations. */
static t_msg_temp_keepalive msg_temp_keepalive =
{
	.id0 = 0,
	.id1 = 1,
	.type = 2,
};

static t_msg_temp_report msg_temp_report =
{
	.id0 = 0,
	.id1 = 2,
	.led = 0,
	.temp = 0,
};

typedef enum wifi_status {
	WifiStateInit,
	WifiStateWaitingProv,
	WifiStateConnecting,
	WifiStateConnected,
	WifiStateDisConnected
} wifi_status_t;

/** WiFi status variable. */
wifi_status_t gWifiState = WifiStateInit;

/** WiFi disconnect event counter. */
static uint32_t gu32disconnectCount = 0;

/** SysTick counter to avoid busy wait delay. */
volatile uint32_t gu32MsTicks = 0;

/** Global counter delay for timer. */
static uint32_t gu32publishDelay = 0;
static uint32_t gu32subscribeDelay = 0;

/* AP provisioning mode configuration. */
static tstrM2MAPConfig gstrM2MAPConfig = {
	DEMO_WLAN_AP_NAME,      /* Access Point Name. */
	DEMO_WLAN_AP_CHANNEL,   /* Channel to use. */
	DEMO_WLAN_AP_WEP_INDEX, /* Wep key index. */
	DEMO_WLAN_AP_WEP_SIZE,  /* Wep key size. */
	DEMO_WLAN_AP_WEP_KEY,   /* Wep key. */
	DEMO_WLAN_AP_SECURITY,  /* Security mode. */
	DEMO_WLAN_AP_MODE,      /* SSID visible. */
	DEMO_WLAN_AP_IP_ADDRESS /* DHCP server IP */
};

static const char gchHttpProvDomainName[] = DEMO_WLAN_AP_DOMAIN_NAME;
static char gs8DeviceName[] = DEMO_WLAN_AP_NAME;

static char gSSID[64] = { 0 };
static int gSecType = M2M_WIFI_SEC_WPA_PSK;
static char gPSK[64] = { 0 };

/** PubNub global variables. */
static const char PubNubPublishKey[] = DEMO_PUBNUB_PUBLISH_KEY;
static const char PubNubSubscribeKey[] = DEMO_PUBNUB_SUBSCRIBE_KEY;
static char PubNubChannel[] = DEMO_PUBNUB_CHANNEL;
static pubnub_t *pPubNubCfg;

/** Android app: global counter delay for android app report. */
static uint32_t gu32androidDelay = 0;

/** Android app: RX and TX socket descriptors. */
static SOCKET sock_rx_android = -1;
static SOCKET sock_tx_android = -1;

/** Android app: receive buffer definition. */
#define TEST_BUFFER_SIZE 1460
static uint8 gau8SocketTestBuffer[TEST_BUFFER_SIZE];

/** UART module for debug. */
struct adc_module adc_instance;

/** UART module for debug. */
static struct usart_module cdc_uart_module;
struct sockaddr_in addr;

static void setup_android_sockets(void)
{
	/* Initialize socket address structure. */
	addr.sin_family	= AF_INET;
	addr.sin_port = _htons(DEMO_ANDROID_SERVER_PORT);
	addr.sin_addr.s_addr = 0xffffffff;
	
	/* Close socket if previously opened. */
	close(sock_rx_android);
	close(sock_tx_android);
	sock_rx_android = -1;
	sock_tx_android = -1;

	/* Create socket for Android app. */
	if (sock_rx_android < 0) {
		if ((sock_rx_android = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
			puts("main: failed to create RX UDP client socket error!");
		}
		bind(sock_rx_android, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
	}
	if (sock_tx_android < 0) {
		if ((sock_tx_android = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
			puts("main: failed to create TX UDP client socket error!");
		}
	}
}

/**
 * \brief Get duration of the SW0 button pressed.
 *
 * \return number of ms the button has been pressed.
 */
static uint32_t button_press_duration(bool current_button_state)
{
	static bool previous_button_state = false;
	static int32_t button_press_start_ms = 0;

	/* Button has been pressed. */
	if (current_button_state == true && previous_button_state == false) {
		button_press_start_ms = gu32MsTicks;
	}
	/* Button has been released. */
	if (current_button_state == true && previous_button_state == true) {
		return gu32MsTicks - button_press_start_ms;
	}

	previous_button_state = current_button_state;
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
static void m2m_wifi_socket_handler(SOCKET sock, uint8_t u8Msg, void *pvMsg)
{	
	/* Android app: check for socket event on RX socket. */
	if (sock == sock_rx_android) {
		if (u8Msg == SOCKET_MSG_BIND) {
			tstrSocketBindMsg *pstrBind = (tstrSocketBindMsg *)pvMsg;
			if (pstrBind && pstrBind->status == 0) {
				/* Prepare next buffer reception. */
				recvfrom(sock, gau8SocketTestBuffer, TEST_BUFFER_SIZE, 0);
			}
			else {
				puts("m2m_wifi_socket_handler: bind error!");
			}
		}
		else if (u8Msg == SOCKET_MSG_RECVFROM) {
			tstrSocketRecvMsg *pstrRx = (tstrSocketRecvMsg *)pvMsg;
			if (pstrRx->pu8Buffer && pstrRx->s16BufferSize) {
				if (WifiStateWaitingProv == gWifiState) {
					/* Fetch provisioning data. */
					t_msg_temp_prov prov;
					memcpy(&prov, pstrRx->pu8Buffer, sizeof(t_msg_temp_prov));
					if (prov.id0 == 0 && prov.id1 == 3) {
						memcpy(gSSID, prov.ssid, strlen((char *)(prov.ssid)) + 1);
						gSecType = prov.sec;
						memcpy(gPSK, prov.pass, strlen((char *)(prov.pass)) + 1);
						m2m_wifi_stop_provision_mode();
						printf("m2m_wifi_socket_handler: Wi-Fi connecting to AP using Android app credentials:\r\n");
						printf("m2m_wifi_socket_handler:  - SSID: %s, SecType: %d, Key: %s\r\n\r\n", prov.ssid, prov.sec, prov.pass);
						gWifiState = WifiStateConnecting;
						m2m_wifi_connect((char *)prov.ssid, strlen((char *)prov.ssid), prov.sec, prov.pass, M2M_WIFI_CH_ALL);
					}
				}
				else {
					/* Check for server report and update led status if necessary. */
					t_msg_temp_report report;
					memcpy(&report, pstrRx->pu8Buffer, sizeof(t_msg_temp_report));
					if (report.id0 == 0 && report.id1 == 2 && (strcmp((char *)report.name, DEMO_ANDROID_SENSOR_NAME) == 0)) {
						puts("m2m_wifi_socket_handler: received Android app message.");
						port_pin_set_output_level(LED_0_PIN, report.led ? true : false);
						gu32androidDelay = 0;
					}
				}
			}

			/* Prepare next buffer reception. */
			recvfrom(sock, gau8SocketTestBuffer, TEST_BUFFER_SIZE, 0);
		}
	}
	/* PubNub: TCP handler. */
	else {
		handle_tcpip(sock, u8Msg, pvMsg);
	}
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
			gu32disconnectCount = 0;
		}
		else if (pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED) {
			printf("m2m_wifi_state: M2M_WIFI_RESP_CON_STATE_CHANGED: DISCONNECTED\r\n");
			if (++gu32disconnectCount > 3) {
				gWifiState = WifiStateWaitingProv;
				m2m_wifi_start_provision_mode((tstrM2MAPConfig *)&gstrM2MAPConfig,
						(char *)gchHttpProvDomainName, 1);
			}
			else if (WifiStateConnected == gWifiState || WifiStateConnecting == gWifiState) {
				m2m_wifi_connect(gSSID, strlen(gSSID), gSecType, (char *)gPSK, M2M_WIFI_CH_ALL);
			}
			if (WifiStateWaitingProv == gWifiState) {
				printf("m2m_wifi_state: Wi-Fi provisioning mode started:\r\n");
				printf("m2m_wifi_state:  - Connect your laptop/phone to Wi-Fi Access Point \"%s\".\r\n", gstrM2MAPConfig.au8SSID);
				printf("m2m_wifi_state:  - Open a browser to \"%s\" and enter credentials.\r\n\r\n", DEMO_WLAN_AP_DOMAIN_NAME);
			}
		}

		break;
	}

	case M2M_WIFI_REQ_DHCP_CONF:
	{
		uint8_t *pu8IPAddress = (uint8_t *)pvMsg;
		printf("m2m_wifi_state: M2M_WIFI_REQ_DHCP_CONF: IP is %u.%u.%u.%u\r\n",
				pu8IPAddress[0], pu8IPAddress[1], pu8IPAddress[2], pu8IPAddress[3]);
		if (gWifiState == WifiStateConnecting) {
			gWifiState = WifiStateConnected;
		}
		setup_android_sockets();
		break;
	}

	case M2M_WIFI_RESP_PROVISION_INFO:
	{
		tstrM2MProvisionInfo *pstrProvInfo = (tstrM2MProvisionInfo *)pvMsg;
		printf("m2m_wifi_state: M2M_WIFI_RESP_PROVISION_INFO:\r\n");
		port_pin_set_output_level(LED0_PIN, LED0_INACTIVE);
		if (pstrProvInfo->u8Status == M2M_SUCCESS) {
			memcpy(gSSID, pstrProvInfo->au8SSID, strlen((char *)(pstrProvInfo->au8SSID)) + 1);
			gSecType = pstrProvInfo->u8SecType;
			memcpy(gPSK, pstrProvInfo->au8Password, strlen((char *)(pstrProvInfo->au8Password)) + 1);
			printf("m2m_wifi_state: Wi-Fi connecting to AP using provided credentials:\r\n");
			printf("m2m_wifi_state:  - SSID: %s, SecType: %d, Key: %s\r\n\r\n", gSSID, gSecType, gPSK);
			gWifiState = WifiStateConnecting;
			m2m_wifi_connect(gSSID, strlen(gSSID), gSecType, gPSK, M2M_WIFI_CH_ALL);
		} else {
			printf("m2m_wifi_state: provision failed!\r\n");
			m2m_wifi_start_provision_mode((tstrM2MAPConfig *)&gstrM2MAPConfig,
					(char *)gchHttpProvDomainName, 1);
		}

		break;
	}
	
	case M2M_WIFI_RESP_DEFAULT_CONNECT:
	{
		tstrM2MDefaultConnResp *pstrResp = (tstrM2MDefaultConnResp *)pvMsg;
		printf("m2m_wifi_state: M2M_WIFI_RESP_DEFAULT_CONNECT.\r\n");
		if ((pstrResp->s8ErrorCode == M2M_DEFAULT_CONN_SCAN_MISMATCH) || 
				(pstrResp->s8ErrorCode == M2M_DEFAULT_CONN_EMPTY_LIST)) {
			
			/* Previously used AP not found, enter provisioning mode. */
			printf("m2m_wifi_state: Wi-Fi provisioning mode started:\r\n");
			printf("m2m_wifi_state:  - Connect your laptop/phone to Wi-Fi Access Point \"%s\".\r\n", gstrM2MAPConfig.au8SSID);
			printf("m2m_wifi_state:  - Open a browser to \"%s\" and enter credentials.\r\n\r\n", DEMO_WLAN_AP_DOMAIN_NAME);
			gWifiState = WifiStateWaitingProv;
			m2m_wifi_start_provision_mode((tstrM2MAPConfig *)&gstrM2MAPConfig,
					(char *)gchHttpProvDomainName, 1);
		}
		break;
	}

	default:
	{
		break;
	}
	}
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
	uint32_t led_toggle_delay = 0;
	char buf[512] = {0};
	sint8 ret;

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
	registerSocketCallback(m2m_wifi_socket_handler, socket_resolve_cb);

	/* Read MAC address to customize device name and AP name if enabled. */
	m2m_wifi_get_otp_mac_address(mac_addr, &u8IsMacAddrValid);
	if (!u8IsMacAddrValid) {
		printf("main: MAC address fuse bit has not been configured!\r\n");
		printf("main: Use m2m_wifi_set_mac_address() API to set MAC address via software.\r\n");
		while (1) {
		}
	}
	m2m_wifi_get_mac_address(mac_addr);
	set_dev_name_to_mac((uint8 *)gs8DeviceName, mac_addr);
	set_dev_name_to_mac((uint8 *)gstrM2MAPConfig.au8SSID, mac_addr);
	set_dev_name_to_mac((uint8 *)PubNubChannel, mac_addr);
	memcpy(msg_temp_keepalive.name ,gs8DeviceName,(uint8)m2m_strlen((uint8 *)gs8DeviceName));
	memcpy(msg_temp_report.name ,gs8DeviceName,(uint8)m2m_strlen((uint8 *)gs8DeviceName));
	m2m_wifi_set_device_name((uint8 *)gs8DeviceName, (uint8)m2m_strlen((uint8 *)gs8DeviceName));
	printf("\r\n");

	/* Initialize PubNub API. */
	printf("main: PubNub configured with following settings:\r\n");
	printf("main:  - Publish key: \"%s\", Subscribe key: \"%s\", Channel: \"%s\".\r\n\r\n",
	PubNubPublishKey, PubNubSubscribeKey, PubNubChannel);
	pPubNubCfg = pubnub_get_ctx(0);
	pubnub_init(pPubNubCfg, PubNubPublishKey, PubNubSubscribeKey);

	/* Connect to the previously used AP. */
	gWifiState = WifiStateConnecting;
	m2m_wifi_default_connect();

	while (1) {
		m2m_wifi_handle_events(NULL);

		/* If SW0 button is pressed for 3 seconds go back to web provisioning mode. */
		uint32_t sw0_pressed = button_press_duration(!port_pin_get_input_level(SW0_PIN));
		if (sw0_pressed > 3000 && gWifiState != WifiStateWaitingProv) {
			gWifiState = WifiStateWaitingProv;
			m2m_wifi_start_provision_mode((tstrM2MAPConfig *)&gstrM2MAPConfig,
					(char *)gchHttpProvDomainName, 1);
		}
		
		/* Toggle LED0 fast during web provisioning mode. */
		if (WifiStateWaitingProv == gWifiState && (gu32MsTicks - led_toggle_delay) > 60) {
			port_pin_toggle_output_level(LED0_PIN);
			led_toggle_delay = gu32MsTicks;		
		}

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
				if (gu32MsTicks - gu32subscribeDelay > DEMO_PUBNUB_SUBSCRIBE_INTERVAL) {
					gu32subscribeDelay = gu32MsTicks;
					printf("main: subscribe event, interval.\r\n");
					pubnub_subscribe(pPubNubCfg, PubNubChannel);
				}
			}

			/* PubNub: write (publish) event to the cloud. */
			if (gu32MsTicks - gu32publishDelay > DEMO_PUBNUB_PUBLISH_INTERVAL) {
				gu32publishDelay = gu32MsTicks;
				adc_start_conversion(&adc_instance);
				temperature = at30tse_read_temperature();
				adc_read(&adc_instance, &light);
				sprintf(buf, "{\"device\":\"%s\", \"temperature\":\"%d.%d\", \"light\":\"%d\", \"led\":\"%s\"}",
						gs8DeviceName,
						(int)temperature, (int)((int)(temperature * 100) % 100),
						(((4096 - light) * 100) / 4096),
						port_pin_get_output_level(LED0_PIN) ? "0" : "1");
				printf("main: publish event: {%s}\r\n", buf);
				close(pPubNubCfg->tcp_socket);
				pPubNubCfg->state = PS_IDLE;
				pPubNubCfg->last_result = PNR_IO_ERROR;
				pubnub_publish(pPubNubCfg, PubNubChannel, buf);
			}
			
			/* Android app report. */
			if (gu32MsTicks - gu32androidDelay > DEMO_ANDROID_REPORT_INTERVAL) {
				gu32androidDelay = gu32MsTicks;

				/* Send client discovery frame. */
				sendto(sock_tx_android, &msg_temp_keepalive, sizeof(t_msg_temp_keepalive), 0,
						(struct sockaddr *)&addr, sizeof(addr));
			
				/* Send client report. */
				msg_temp_report.temp = (uint32_t)(at30tse_read_temperature() * 100);
				msg_temp_report.light = (((4096 - light) * 100) / 4096);
				msg_temp_report.led = !port_pin_get_output_level(LED_0_PIN);
				ret = sendto(sock_tx_android, &msg_temp_report, sizeof(t_msg_temp_report), 0,
						(struct sockaddr *)&addr, sizeof(addr));

				if (ret == M2M_SUCCESS) {
					puts("main: sensor report sent");
				} else {
					puts("main: failed to send status report error!");
				}
			}

		}
	}

	return 0;
}
