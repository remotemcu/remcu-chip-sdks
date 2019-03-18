/**
 *
 * \file
 *
 * \brief IOT QTouch Sensor Demo.
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

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "asf.h"
#include "demo.h"
#include "bsp/include/nm_bsp.h"
#include "driver/include/m2m_wifi.h"
#include "socket/include/socket.h"
#include "conf_winc.h"

/* Macros */

/**
 * \def GET_SENSOR_STATE(SENSOR_NUMBER)
 * \brief To get the sensor state that it is in detect or not
 * \param SENSOR_NUMBER for which the state to be detected
 * \return Returns either 0 or 1
 * If the bit value is 0, it is not in detect
 * If the bit value is 1, it is in detect
 * Alternatively, the individual sensor state can be directly accessed using
 * p_qm_measure_data->p_sensor_states[(SENSOR_NUMBER/8)] variable.
 */
 #define GET_MUTLCAP_SENSOR_STATE(SENSOR_NUMBER) p_mutlcap_measure_data-> \
	p_sensor_states[(SENSOR_NUMBER / \
	8)] & (1 << (SENSOR_NUMBER % 8))

/**
 * \def GET_ROTOR_SLIDER_POSITION(ROTOR_SLIDER_NUMBER)
 * \brief To get the rotor angle or slider position.
 * These values are valid only when the sensor state for
 * corresponding rotor or slider shows in detect.
 * \param ROTOR_SLIDER_NUMBER for which the position to be known
 * \return Returns rotor angle or sensor position
 */
#define GET_MUTLCAP_ROTOR_SLIDER_POSITION(ROTOR_SLIDER_NUMBER) \
	p_mutlcap_measure_data->p_rotor_slider_values[ \
		ROTOR_SLIDER_NUMBER]

/**
 * Discrete LED output pin definitions
 */
#ifdef LED_0_PIN
#undef LED_0_PIN
#define LED_0_PIN	PIN_PB00
#endif
#define LED_1_PIN       PIN_PB01
#define LED_2_PIN       PIN_PB02
#define LED_3_PIN       PIN_PB03
#define LED_4_PIN       PIN_PA05
#define LED_5_PIN       PIN_PA06
#define LED_6_PIN       PIN_PA04
#define LED_7_PIN       PIN_PA07
#if SAMD20
#define LED_8_PIN       PIN_PA22
#define LED_9_PIN       PIN_PA23
#elif SAMD21
#define LED_8_PIN       PIN_PB12
#define LED_9_PIN       PIN_PB13
#endif

/**
 * RGB LED output pin definitions
 */
#define LED_R_PIN       PIN_PB14
#define LED_G_PIN       PIN_PB15
#define LED_B_PIN       PIN_PA17

/**
 * RTC Interrupt timing definition
 */
#define TIME_PERIOD_1MSEC 33u
/**
 * Variables
 */
uint8_t rotor_state;
uint8_t rotor_position;
volatile uint8_t PWM_Count;
volatile uint16_t touch_time_counter = 0u;
struct rtc_module rtc_instance;

const uint8_t PWM_RGB_values[64][3] = {
	{20, 0, 0},
	{20, 0, 0},
	{19, 1, 0},
	{18, 2, 0},
	{17, 3, 0},
	{16, 4, 0},
	{15, 5, 0},
	{14, 6, 0},
	{13, 7, 0},
	{12, 8, 0},
	{11, 9, 0},
	{10, 10, 0},
	{9, 11, 0},
	{8, 12, 0},
	{7, 13, 0},
	{6, 14, 0},
	{5, 15, 0},
	{4, 16, 0},
	{3, 17, 0},
	{2, 18, 0},
	{1, 19, 0},
	{0, 20, 0},
	{0, 20, 0},
	{0, 19, 1},
	{0, 18, 2},
	{0, 17, 3},
	{0, 16, 4},
	{0, 15, 5},
	{0, 14, 6},
	{0, 13, 7},
	{0, 12, 8},
	{0, 11, 9},
	{0, 10, 10},
	{0, 9, 11},
	{0, 8, 12},
	{0, 7, 13},
	{0, 6, 14},
	{0, 5, 15},
	{0, 4, 16},
	{0, 3, 17},
	{0, 2, 18},
	{0, 1, 19},
	{0, 0, 20},
	{0, 0, 20},
	{1, 0, 19},
	{2, 0, 18},
	{3, 0, 17},
	{4, 0, 16},
	{5, 0, 15},
	{6, 0, 14},
	{7, 0, 13},
	{8, 0, 12},
	{9, 0, 11},
	{10, 0, 10},
	{11, 0, 9},
	{12, 0, 8},
	{13, 0, 7},
	{14, 0, 6},
	{15, 0, 5},
	{16, 0, 4},
	{17, 0, 3},
	{18, 0, 2},
	{19, 0, 1},
	{19, 0, 1}
};


static struct sockaddr_in remote_addr;
static uint32_t connected = 0;
static uint32_t delay_srv_keepalive = 0;
static uint32_t delay_clt_keepalive = 0;

/** Message format definitions. */
#define IMU_RX_TIMEOUT				8000
#define IMU_TX_KEEPALIVE_DELAY		1000

/* Configure and enable access point mode with provisioning page. */
tstrM2MAPConfig ap_config = {
	DEMO_WLAN_AP_NAME,			// Access Point Name.
	DEMO_WLAN_AP_CHANNEL,		// Channel to use.
	DEMO_WLAN_AP_WEP_INDEX,		// Wep key index.
	DEMO_WLAN_AP_WEP_SIZE,		// Wep key size.
	DEMO_WLAN_AP_WEP_KEY,		// Wep key.
	DEMO_WLAN_AP_SECURITY,		// Security mode.
	DEMO_WLAN_AP_MODE,			// SSID visible.
	DEMO_WLAN_AP_IP_ADDRESS     // Server IP address
};

typedef struct s_msg_user_input {
	uint8_t channel;
	uint8_t security;
	char* password;
	char* SSID;
} t_msg_user_input;

typedef struct s_msg_touch_keepalive {
	uint8_t id0;
	uint8_t id1;
	uint8_t name[9];
	uint8_t type;
} t_msg_touch_keepalive;

typedef struct s_msg_touch_report {
	uint8_t id0;
	uint8_t id1;
	uint8_t name[9];
	uint8_t b1_state;
	uint8_t b2_state;
	uint8_t sl_state;
	uint8_t sl_pos;
	uint8_t rot_state;
	uint8_t rot_position;
	uint8_t dummy_byte[3];
} t_msg_touch_report;

/** Message format declarations. */
static t_msg_touch_keepalive msg_touch_keepalive =
{
	.id0 = 0,
	.id1 = 1,
	.name = DEMO_PRODUCT_NAME,
	.type = 4,
};

static t_msg_touch_report msg_touch_report =
{
	.id0 = 0,
	.id1 = 6,
	.name = DEMO_PRODUCT_NAME,
};

/*Provisioning related definitions*/
uint8 gau8HttpProvServerIP[] = DEMO_WLAN_AP_IP_ADDRESS;
char gacHttpProvDomainName[] = DEMO_WLAN_AP_DOMAIN_NAME;
char user_credentials[108];
char provision_ssid[70];
char provision_pwd[30];
static t_msg_user_input user_data;

/** Receive buffer definition. */
#define TEST_BUFFER_SIZE 1460
static uint8 gau8SocketTestBuffer[TEST_BUFFER_SIZE];

/** RX and TX socket handlers. */
static SOCKET rx_socket = -1;
static SOCKET tx_socket = -1;

/** WiFi status variable. */
static volatile uint8 wifi_connected = 0;
static uint8 wifi_provisioned = 1;//Assuming we are already provisioned

/** Global counter delay for timer. */
static uint32_t delay = 0;
/** Global counters for LED toggling*/
static uint32_t toggle_led_ms = 0;

/** SysTick counter for non busy wait delay. */
extern uint32_t ms_ticks;

/*returns duration of the button pressed
returns -1 if the button has not been released*/
static int32_t button_press_duration(uint8_t button_state)
{
	static bool previous_button_state = false;
	static bool current_button_state = false;
	static int32_t button_press_start_ms = 0;
	int32_t button_press_duration_ms = -1;
	
	button_state == 2?(current_button_state = true):(current_button_state=false);
	
	/*Button has been pressed*/
	if(current_button_state == true && previous_button_state == false)
	{
		button_press_start_ms = ms_ticks;
	}
	/*Button has been released*/
	if(current_button_state == false && previous_button_state == true)
	{
		button_press_duration_ms = ms_ticks - button_press_start_ms;
	}
	previous_button_state = current_button_state;
	return button_press_duration_ms;
}

static void print_provisioning_details(void)
{
	printf("\r\nStarted as Access point %s\r\n",DEMO_WLAN_AP_NAME);
	puts("Enter \"atmelconfig.com\" in your browser and enter credentials in the served webpage\r\n");
	puts("Please press SW0 on D21 and enter credentials if the webpage is not served through above method\r\n");
}

static void parse_user_input(char* user_input)
{
	char* uinput;
	uinput = strtok (user_input,":");
	uinput != NULL ? (user_data.SSID = uinput) : (user_data.SSID = (char*)DEFAULT_SSID);
	uinput = strtok (NULL, ":");
	uinput != NULL ? (user_data.password = uinput) : (user_data.password = (char*)DEFAULT_PWD);
	uinput = strtok (NULL, ":");
	uinput != NULL ? (user_data.security = atoi(uinput)) : (user_data.security = DEFAULT_AUTH);
	uinput = strtok (NULL, ":");
	uinput != NULL ? (user_data.channel = atoi(uinput)-1) : (user_data.channel = DEFAULT_CHANNEL);
}

static uint32_t isSubStr(uint8_t *buf, uint32_t len, uint8_t *msg, uint32_t msglen)
{
	for (uint32_t i = 0, j = 0; i < len; ++i) {
		if (buf[i] == msg[j]) {
			j += 1;
			if (j == msglen)
			return 1;
		}
		else
		j = 0;
	}

	return 0;
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
static void m2m_wifi_socket_handler(SOCKET sock, uint8 u8Msg, void *pvMsg)
{
	/* Check for socket event on RX socket. */
	if (sock == rx_socket) {
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

				if (connected == 0) {
					/* Check for server report and update led status if necessary. */
					if (isSubStr(pstrRx->pu8Buffer, pstrRx->s16BufferSize, (uint8_t *)&msg_touch_keepalive, sizeof(t_msg_touch_keepalive))) {
						puts("m2m_wifi_socket_handler: handshake complete!");
						/* Stop broadcasting and only send to remote server. */
						remote_addr.sin_addr.s_addr = pstrRx->strRemoteAddr.sin_addr.s_addr;
						connected = 1;
						delay_srv_keepalive = ms_ticks;
					}
				}
				else {
					/* Detect server keep alive. */
					if (isSubStr(pstrRx->pu8Buffer, pstrRx->s16BufferSize, (uint8_t *)&msg_touch_keepalive, sizeof(t_msg_touch_keepalive))) {
						puts("m2m_wifi_socket_handler: got server keepalive");
						delay_srv_keepalive = ms_ticks;
					}
				}
				/* Prepare next buffer reception. */
				recvfrom(sock, gau8SocketTestBuffer, TEST_BUFFER_SIZE, 0);
			}
			else {
				if (pstrRx->s16BufferSize == SOCK_ERR_TIMEOUT) {
					/* Prepare next buffer reception. */
					recvfrom(sock, gau8SocketTestBuffer, TEST_BUFFER_SIZE, 0);
				}
			}
		}
	}
}

/**
* \brief Callback to get the WiFi status update.
*
* \param[in] u8MsgType type of WiFi notification. Possible types are:
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
static void m2m_wifi_state(uint8 u8MsgType, void *pvMsg)
{
	switch (u8MsgType) {
		case M2M_WIFI_RESP_CON_STATE_CHANGED: {
			tstrM2mWifiStateChanged *pstrWifiState = (tstrM2mWifiStateChanged*) pvMsg;
			if (pstrWifiState->u8CurrState == M2M_WIFI_CONNECTED) {
				puts("m2m_wifi_state: M2M_WIFI_RESP_CON_STATE_CHANGED: CONNECTED");
				m2m_wifi_get_connection_info();
				m2m_wifi_request_dhcp_client();
			}
			else if(pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED) {
				puts("m2m_wifi_state: M2M_WIFI_RESP_CON_STATE_CHANGED: DISCONNECTED");
				m2m_wifi_connect(user_data.SSID, strlen(user_data.SSID),
				user_data.security, user_data.password,user_data.channel);
				wifi_connected = 0;
			}
			break;
		}
		case M2M_WIFI_REQ_DHCP_CONF: {
			uint8 *pu8IPAddress = (uint8*) pvMsg;
			if(wifi_provisioned == 1){
				wifi_connected = 1;
			}
			printf("m2m_wifi_state: M2M_WIFI_REQ_DHCP_CONF: IP is %u.%u.%u.%u\n",
			pu8IPAddress[0], pu8IPAddress[1], pu8IPAddress[2], pu8IPAddress[3]);
			break;
		}
		case M2M_WIFI_RESP_DEFAULT_CONNECT: {
			tstrM2MDefaultConnResp *pstrResp = (tstrM2MDefaultConnResp*) pvMsg;
			if(pstrResp->s8ErrorCode == M2M_DEFAULT_CONN_SCAN_MISMATCH || 
			pstrResp->s8ErrorCode == M2M_DEFAULT_CONN_EMPTY_LIST)
			{
				/*If we didn't find previously provisioned Access point
				or we don't find any Access point around, we enter provisioning mode*/
				wifi_provisioned = 0; /*Also set provisioning to zero, as our assumption was incorrect*/
				m2m_wifi_start_provision_mode(&ap_config,gacHttpProvDomainName,1);
				print_provisioning_details();
			}
			break;
		}
		
		case M2M_WIFI_RESP_CONN_INFO: {
		tstrM2MConnInfo *pstrConnInfo = (tstrM2MConnInfo*)pvMsg;
		printf("Connected to %s\r\n",pstrConnInfo->acSSID);
		break;
		}
		
		case M2M_WIFI_RESP_PROVISION_INFO : {
			tstrM2MProvisionInfo *pstrProvInfo = (tstrM2MProvisionInfo*)pvMsg;

			if (pstrProvInfo->u8Status == M2M_SUCCESS) {
				wifi_provisioned = 1;
				m2m_wifi_connect((char*)pstrProvInfo->au8SSID,strlen((char*)pstrProvInfo->au8SSID),
				pstrProvInfo->u8SecType, pstrProvInfo->au8Password, M2M_WIFI_CH_ALL);
				//TODO: Not sure if this is needed, if we can retrieve this when disconnected
				//Copy the provisioned info into user_data, so we can connect back when disconnected
				strncpy(provision_ssid,(char*)pstrProvInfo->au8SSID,strlen((char*)pstrProvInfo->au8SSID));
				strncpy(provision_pwd,(char*)pstrProvInfo->au8Password,strlen((char*)pstrProvInfo->au8Password));
				user_data.SSID = provision_ssid;
				user_data.password = provision_pwd;
				user_data.security = pstrProvInfo->u8SecType;
				user_data.channel = M2M_WIFI_CH_ALL;
				
				printf("m2m_wifi_state: M2M_WIFI_RESP_PROVISION_INFO using SSID %s\n", pstrProvInfo->au8SSID);
				if (pstrProvInfo->u8SecType != M2M_WIFI_SEC_OPEN) {
					printf("m2m_wifi_state: M2M_WIFI_RESP_PROVISION_INFO using PSK %s\n", pstrProvInfo->au8Password);
				}
			}
			break;
		}
		default: {
			break;
		}
	}
}

static void rtc_overflow_callback(void)
{
	/* Do something on RTC overflow here */
	if(touch_time_counter == touch_time.measurement_period_ms)
	{
		touch_time.time_to_measure_touch = 1u;
		touch_time.current_time_ms = touch_time.current_time_ms +
		touch_time.measurement_period_ms;
		touch_time_counter = 0u;
	}
	else
	{
		touch_time_counter++;
	}


	// Update PWM counter
	if(PWM_Count < 20)
	{
		PWM_Count++;
	}
	else
	{
		PWM_Count = 0;
	}
		// If rotor is active
		if(rotor_state)
		{
			rotor_position = GET_MUTLCAP_ROTOR_SLIDER_POSITION(0);
			rotor_position = rotor_position >> 2u;
			if(PWM_Count < PWM_RGB_values[rotor_position][0])
			{
				port_pin_set_output_level(LED_R_PIN, 0);
			}
			else
			{
				port_pin_set_output_level(LED_R_PIN, 1);
			}

			if(PWM_Count < PWM_RGB_values[rotor_position][1])
			{
				port_pin_set_output_level(LED_G_PIN, 0);
			}
			else
			{
				port_pin_set_output_level(LED_G_PIN, 1);
			}

			if(PWM_Count < PWM_RGB_values[rotor_position][2])
			{
				port_pin_set_output_level(LED_B_PIN, 0);
			}
			else
			{
				port_pin_set_output_level(LED_B_PIN, 1);
			}
		}
		else
		{
			port_pin_set_output_level(LED_R_PIN, 1);
			port_pin_set_output_level(LED_G_PIN, 1);
			port_pin_set_output_level(LED_B_PIN, 1);
		}
}

/*! \brief Configure the RTC timer callback
 *
 */
static void configure_rtc_callbacks(void)
{
	/* register callback */
	rtc_count_register_callback(&rtc_instance,
			rtc_overflow_callback, RTC_COUNT_CALLBACK_OVERFLOW);
	/* Enable callback */
	rtc_count_enable_callback(&rtc_instance,RTC_COUNT_CALLBACK_OVERFLOW);
}

/*! \brief Configure the RTC timer count after which interrupts comes
 *
 */
static void configure_rtc_count(void)
{
	struct rtc_count_config config_rtc_count;
	rtc_count_get_config_defaults(&config_rtc_count);

	config_rtc_count.prescaler           = RTC_COUNT_PRESCALER_DIV_1;
	config_rtc_count.mode                = RTC_COUNT_MODE_16BIT;
	config_rtc_count.continuously_update = true;
	/* initialize rtc */
	rtc_count_init(&rtc_instance,RTC,&config_rtc_count);

	/* enable rtc */
	rtc_count_enable(&rtc_instance);
}

/*! \brief Initialize timer
 *
 */
static void timer_init(void)
{
	/* Configure and enable RTC */
	configure_rtc_count();

	/* Configure and enable callback */
	configure_rtc_callbacks();

	/* Set Timer Period */

	rtc_count_set_period(&rtc_instance,TIME_PERIOD_1MSEC);
}

/**
 * Port pin configuration / assignments
 */
static void configure_port_pins(void)
{
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);

	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(LED_0_PIN, &config_port_pin);
	port_pin_set_config(LED_1_PIN, &config_port_pin);
	port_pin_set_config(LED_2_PIN, &config_port_pin);
	port_pin_set_config(LED_3_PIN, &config_port_pin);
	port_pin_set_config(LED_4_PIN, &config_port_pin);
	port_pin_set_config(LED_5_PIN, &config_port_pin);
	port_pin_set_config(LED_6_PIN, &config_port_pin);
	port_pin_set_config(LED_7_PIN, &config_port_pin);
	port_pin_set_config(LED_8_PIN, &config_port_pin);
	port_pin_set_config(LED_9_PIN, &config_port_pin);
	port_pin_set_config(LED_R_PIN, &config_port_pin);
	port_pin_set_config(LED_G_PIN, &config_port_pin);
	port_pin_set_config(LED_B_PIN, &config_port_pin);

}

/**
* \brief Demo main function.
*/
void demo_start(void)
{
	tstrWifiInitParam winc_init_config;
	struct sockaddr_in local_addr;
	sint8 ret;
	uint16_t cnt = 0;
	uint8_t button1_state = 0;
	uint8_t button2_state = 0;
	uint8_t slider_state = 0;
	uint8_t slider_position = 0;

	/* Initialize socket address structure. */
	local_addr.sin_family	= AF_INET;
	local_addr.sin_port = _htons(DEMO_SERVER_PORT);
	local_addr.sin_addr.s_addr = 0xFFFFFFFF;
	
	/* Reset remote server address structure. */
	remote_addr.sin_family = AF_INET;
	remote_addr.sin_port = _htons(DEMO_SERVER_PORT);
	remote_addr.sin_addr.s_addr = 0xFFFFFFFF;
		
	/* Initialize WINC1500 hardware. */
	nm_bsp_init();
	
	/**
	 * Initialize timer.
	 */
	timer_init();

	/**
	 * Initialize QTouch library and configure touch sensors.
	 */
	touch_sensors_init();

	/**
	 * Configure port pins
	 */
	configure_port_pins();

	/**
	 * Turn off all extension board LEDs
	 */
	port_pin_set_output_level(LED_0_PIN, 1);
	port_pin_set_output_level(LED_1_PIN, 1);
	port_pin_set_output_level(LED_2_PIN, 1);
	port_pin_set_output_level(LED_3_PIN, 1);
	port_pin_set_output_level(LED_4_PIN, 1);
	port_pin_set_output_level(LED_5_PIN, 1);
	port_pin_set_output_level(LED_6_PIN, 1);
	port_pin_set_output_level(LED_7_PIN, 1);
	port_pin_set_output_level(LED_8_PIN, 1);
	port_pin_set_output_level(LED_9_PIN, 1);
	port_pin_set_output_level(LED_R_PIN, 1);
	port_pin_set_output_level(LED_G_PIN, 1);
	port_pin_set_output_level(LED_B_PIN, 1);

	PWM_Count = 0;
	
	/* Initialize WINC1500 driver with WiFi status callback. */
	winc_init_config.pfAppWifiCb = m2m_wifi_state;
	ret = m2m_wifi_init(&winc_init_config);
	if (M2M_SUCCESS != ret) {
		puts("demo_start: nm_drv_init call error!");
		while (1)
		;
	}
	
	/* Initialize Socket driver with socket status callback. */
	socketInit();
	registerSocketCallback(m2m_wifi_socket_handler, NULL);

	//Start the WINC to connect with previously provisioned AP
	m2m_wifi_default_connect();
	while (1) {
		
		/**
		 * Start touch sensor measurement, if touch_time.time_to_measure_touch flag is set by timer.
		 */
		touch_sensors_measure();

		if ((p_mutlcap_measure_data->measurement_done_touch == 1u)) {

			p_mutlcap_measure_data->measurement_done_touch = 0u;

			/**
			 * Get touch sensor states
			 */
			button1_state = GET_MUTLCAP_SENSOR_STATE(0);
			button2_state = GET_MUTLCAP_SENSOR_STATE(1);
			rotor_state = GET_MUTLCAP_SENSOR_STATE(2);
			slider_state = GET_MUTLCAP_SENSOR_STATE(3);
			
			if (button1_state) {
				port_pin_set_output_level(LED_8_PIN, 0);
			} else {
				
				port_pin_set_output_level(LED_8_PIN, 1);
			}

			if (button2_state) {
				port_pin_set_output_level(LED_9_PIN, 0);
			} else {
				port_pin_set_output_level(LED_9_PIN, 1);
			}

			/**
			 * Clear all slider controlled LEDs
			 */
			port_pin_set_output_level(LED_0_PIN, 1);
			port_pin_set_output_level(LED_1_PIN, 1);
			port_pin_set_output_level(LED_2_PIN, 1);
			port_pin_set_output_level(LED_3_PIN, 1);
			port_pin_set_output_level(LED_4_PIN, 1);
			port_pin_set_output_level(LED_5_PIN, 1);
			port_pin_set_output_level(LED_6_PIN, 1);
			port_pin_set_output_level(LED_7_PIN, 1);

					/**
			 * If slider is activated
			 */
			if(slider_state)
			{
				/**
				 * Parse slider position
				 */
				slider_position = GET_MUTLCAP_ROTOR_SLIDER_POSITION(1);
				slider_position = slider_position >> 5u;
				switch(slider_position)
				{
					case 0:
						port_pin_set_output_level(LED_0_PIN, 0);
						break;
					case 1:
						port_pin_set_output_level(LED_0_PIN, 0);
						port_pin_set_output_level(LED_1_PIN, 0);
						break;
					case 2:
						port_pin_set_output_level(LED_0_PIN, 0);
						port_pin_set_output_level(LED_1_PIN, 0);
						port_pin_set_output_level(LED_2_PIN, 0);
						break;
					case 3:
						port_pin_set_output_level(LED_0_PIN, 0);
						port_pin_set_output_level(LED_1_PIN, 0);
						port_pin_set_output_level(LED_2_PIN, 0);
						port_pin_set_output_level(LED_3_PIN, 0);
						break;
					case 4:
						port_pin_set_output_level(LED_0_PIN, 0);
						port_pin_set_output_level(LED_1_PIN, 0);
						port_pin_set_output_level(LED_2_PIN, 0);
						port_pin_set_output_level(LED_3_PIN, 0);
						port_pin_set_output_level(LED_4_PIN, 0);
						break;
					case 5:
						port_pin_set_output_level(LED_0_PIN, 0);
						port_pin_set_output_level(LED_1_PIN, 0);
						port_pin_set_output_level(LED_2_PIN, 0);
						port_pin_set_output_level(LED_3_PIN, 0);
						port_pin_set_output_level(LED_4_PIN, 0);
						port_pin_set_output_level(LED_5_PIN, 0);
						break;
					case 6:
						port_pin_set_output_level(LED_0_PIN, 0);
						port_pin_set_output_level(LED_1_PIN, 0);
						port_pin_set_output_level(LED_2_PIN, 0);
						port_pin_set_output_level(LED_3_PIN, 0);
						port_pin_set_output_level(LED_4_PIN, 0);
						port_pin_set_output_level(LED_5_PIN, 0);
						port_pin_set_output_level(LED_6_PIN, 0);
						break;
					case 7:
						port_pin_set_output_level(LED_0_PIN, 0);
						port_pin_set_output_level(LED_1_PIN, 0);
						port_pin_set_output_level(LED_2_PIN, 0);
						port_pin_set_output_level(LED_3_PIN, 0);
						port_pin_set_output_level(LED_4_PIN, 0);
						port_pin_set_output_level(LED_5_PIN, 0);
						port_pin_set_output_level(LED_6_PIN, 0);
						port_pin_set_output_level(LED_7_PIN, 0);
						break;
					default:
						port_pin_set_output_level(LED_0_PIN, 1);
						port_pin_set_output_level(LED_1_PIN, 1);
						port_pin_set_output_level(LED_2_PIN, 1);
						port_pin_set_output_level(LED_3_PIN, 1);
						port_pin_set_output_level(LED_4_PIN, 1);
						port_pin_set_output_level(LED_5_PIN, 1);
						port_pin_set_output_level(LED_6_PIN, 1);
						port_pin_set_output_level(LED_7_PIN, 1);
						break;
				}
			}
		}
		
		m2m_wifi_handle_events(NULL);
		
		/*Calculate duration of time the button was pressed
		If button was pressed and held for more than 10s we would enter provisioning mode
		short press would allow us to enter credentials from serial console*/
		int32_t button_pressed_duration_ms = button_press_duration(button2_state);
		if((button_pressed_duration_ms != -1 && button_pressed_duration_ms < 2000)
		 && !wifi_provisioned)
		{
			printf("Enter Credentials and press ENTER\r\n");
			printf("eg: <SSID>:<Password>:<SecurityType>:<WifiChannel>\r\n");
			printf("For Security\r\n");
			printf("Enter 1 for OPEN\r\n2 for WPA PSK\r\n");
			printf("3 for WEP\r\n4 for WPA/WPA2 Ent.\r\n"); 
            scanf("%[^\r]s",user_credentials);
			getc(stdin); //work around to clear out previous character
			parse_user_input(user_credentials);
			printf("\r\n");
			//Disable the AP mode
			m2m_wifi_disable_ap();
			delay_ms(250); //delay after disabling AP mode
			//Connect to the router using user supplied credentials
			m2m_wifi_connect(user_data.SSID, strlen(user_data.SSID),
			user_data.security, user_data.password,user_data.channel);
			wifi_provisioned = 1;
		}
		
		/*Force provisioning mode if the user presses SW0 for more than 10s*/
		if(button_pressed_duration_ms != -1 && (button_pressed_duration_ms > 10000))
		{
			wifi_provisioned = 0;
			wifi_connected = 0;
			
			m2m_wifi_start_provision_mode(&ap_config,gacHttpProvDomainName,1);
			print_provisioning_details();
		}
		
		if(!wifi_provisioned)
		{
			if(ms_ticks - toggle_led_ms >= 500)
			{
				toggle_led_ms = ms_ticks;
				//port_pin_toggle_output_level(LED_0_PIN);	
			}
		}
		
		if ((wifi_connected == 1)) {
			/* Open server socket. */
			if (rx_socket < 0) {
				if ((rx_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
					puts("demo_start: failed to create RX UDP client socket error!");
					continue;
				}
				bind(rx_socket, (struct sockaddr *)&local_addr, sizeof(struct sockaddr_in));
			}
			
			/* Open client socket. */
			if (tx_socket < 0) {
				uint32 u32EnableCallbacks = 0;
				if ((tx_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
					puts("demo_start: failed to create TX UDP client socket error!");
					continue;
				}
				setsockopt(tx_socket, SOL_SOCKET , SO_SET_UDP_SEND_CALLBACK, &u32EnableCallbacks, 0);
			}
			
			/* Check server keep alive status. */
			if ((ms_ticks - delay_srv_keepalive > IMU_RX_TIMEOUT) && connected) {
				puts("demo_start: connection lost with server!");
				connected = 0;
				remote_addr.sin_addr.s_addr = 0xFFFFFFFF;
			}
			
			/* Send client keep alive packet. */
			if (ms_ticks - delay_clt_keepalive > IMU_TX_KEEPALIVE_DELAY) {
				delay_clt_keepalive = ms_ticks;
				cnt = 0;
				printf("Sending keep alive..\r\n");
				do {
					ret = sendto(tx_socket, &msg_touch_keepalive, sizeof(t_msg_touch_keepalive), 0,
					(struct sockaddr *)&remote_addr, sizeof(remote_addr));
					m2m_wifi_handle_events(NULL);
					if(ret != M2M_SUCCESS){
						printf("Failed send cnt %d\r",cnt);
						cnt++;
						delay_us(500);
						}else{
						break;
					}
				}while(1);
			}
			
			/* Send IMU sensor information if possible. */
			if (connected && (ms_ticks - delay > DEMO_REPORT_INTERVAL))
			{
				delay = ms_ticks;
				msg_touch_report.b1_state = button1_state;
				msg_touch_report.b2_state = button2_state;
				msg_touch_report.sl_state = slider_state;
				msg_touch_report.sl_pos = slider_position;
				msg_touch_report.rot_position = rotor_position;
				msg_touch_report.rot_state = rotor_state;
				
				ret = sendto(tx_socket, &msg_touch_report, sizeof(t_msg_touch_report), 0,
				(struct sockaddr *)&remote_addr, sizeof(remote_addr));

				if (ret == M2M_SUCCESS) {
					//puts("demo_start: sensor report sent");
					} else {
					puts("demo_start: failed to send status report error!");
				}	
			}
		}
	}
}
