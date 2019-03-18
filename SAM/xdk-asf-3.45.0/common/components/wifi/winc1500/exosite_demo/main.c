/*
 * \file
 *
 * \brief WINC1500 Exosite Example.
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
 * This example demonstrates the use of the WINC1500 with the SAMD21 Xplained Pro
 * board to retrieve the chip information of the Wi-Fi module.<br>
 * It uses the following hardware:
 * - the SAMD21 Xplained Pro.
 * - the WINC1500 on EXT1.
 *
 * \section files Main Files
 * - main.c : Initialize the WINC1500 and retrieve information.
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
 *    -- WINC1500 chip information example --
 *    -- SAMD21_XPLAINED_PRO --
 *    -- Compiled: xxx xx xxxx xx:xx:xx --
 *    Chip ID :             xxxxxx
 *    RF Revision ID :      x
 *    Done.
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
#include "debug_conf.h"
#include "driver/include/m2m_wifi.h"
#include "driver/source/nmasic.h"
#include "socket/include/socket.h"

#include "tick_counter.h"
#include "io1_board.h"
#include "exosite_example.h"

#define MAIN_M2M_AP_SEC                      M2M_WIFI_SEC_OPEN
#define MAIN_M2M_AP_WEP_KEY                  "1234567890"
#define MAIN_M2M_AP_SSID_MODE                SSID_MODE_VISIBLE
#define MAIN_M2M_DHCP_SERVER_IP             {192, 168, 1, 1}

#define MAIN_HTTP_PROV_SERVER_DOMAIN_NAME    "atmelconfig.com"

#define MAIN_M2M_DEVICE_NAME                 "WINC1500_00:00"
#define MAIN_MAC_ADDRESS                     {0xf8, 0xf0, 0x05, 0x45, 0xD4, 0x84}

#define MAIN_EXOSITE_ACTIVATE_DATA_FORMAT	"vendor=%s&model=%s&sn=%s"
#define MAIN_CIK_KEY_STRING					"cik"
#define MAIN_LED_KEY_STRING					"led"

#define MAIN_RES_HTTP_CODE_200				200
#define MAIN_RES_HTTP_CODE_204				204
#define MAIN_RES_HTTP_CODE_401				401
#define MAIN_RES_HTTP_CODE_404				404
#define MAIN_RES_HTTP_CODE_409				409

#define MAIN_ACTIVITE_STATE					1
#define MAIN_SENSOR_DATA_TRANSLATE_STATE	0

#define HEX2ASCII(x) (((x) >= 10) ? (((x) - 10) + 'A') : ((x) + '0'))

/** state enum value for sequence*/
typedef enum {
	MAIN_NEED_TO_CHECK_AP_INFORMATION,		/* state before check the restored AP information in the chip */
	MAIN_CHECKING_AP_INFORMATION,			/* state to be checking the restored AP information in the chip */
	MAIN_NEED_HTTP_PROVISIONING,			/* state to need to do the HTTP Provisioning */ 
	MAIN_DOING_AP_HTTP_PROVISIONING,		/* state to The HTTP Provision mode */
	MAIN_AP_CONNECTION,						/* state to be connected AP after HTTP Provisioning */
}exosite_connect_state;


static tstrM2MAPConfig gstrM2MAPConfig = {
	MAIN_M2M_DEVICE_NAME,
	1,
	0,
	WEP_40_KEY_STRING_SIZE,
	MAIN_M2M_AP_WEP_KEY,
	MAIN_M2M_AP_SEC,
	MAIN_M2M_AP_SSID_MODE,
	MAIN_M2M_DHCP_SERVER_IP
};

/** Device name for AP mode. */
static sint8 gacDeviceName[] = MAIN_M2M_DEVICE_NAME;
/** Doname name for AP mode. */
static CONST char gacHttpProvDomainName[] = MAIN_HTTP_PROV_SERVER_DOMAIN_NAME;
/** If mac address in the board doesn't exist, used it. */
static uint8 gau8MacAddr[] = MAIN_MAC_ADDRESS;

/** AP Connection state. */
static exosite_connect_state ap_exosite_connection_state = MAIN_NEED_TO_CHECK_AP_INFORMATION;

/** UART module for debug. */
static struct usart_module cdc_uart_module;

/* Ext iot board information. */
static io1_board_info * p_board_info = NULL;

/** Exosite send state. */
static uint32_t exosite_translate_state;

/**
* \brief Copy MAC address to string. 
*/ 
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
 * \brief Callback to get the Wi-Fi status update.
 *
 * \param[in] u8MsgType type of Wi-Fi notification. Possible types are:
 *  - [M2M_WIFI_RESP_CON_STATE_CHANGED](@ref M2M_WIFI_RESP_CON_STATE_CHANGED)
 *  - [M2M_WIFI_REQ_DHCP_CONF](@ref M2M_WIFI_REQ_DHCP_CONF)
 * \param[in] pvMsg A pointer to a buffer containing the notification parameters
 * (if any). It should be casted to the correct data type corresponding to the
 * notification type.
 */
static void wifi_cb(uint8_t u8MsgType, void* pvMsg) 
{
	DEBUG(DEBUG_CONF_WIFI "call wifi_callback function" DEBUG_EOL);
	switch(u8MsgType) 
	{		
		case M2M_WIFI_RESP_CON_STATE_CHANGED:
		{
			tstrM2mWifiStateChanged *pstrWifiState = (tstrM2mWifiStateChanged *)pvMsg;
			
			DEBUG(DEBUG_CONF_WIFI "case M2M_WIFI_RESP_CON_STATE_CHANGED" DEBUG_EOL );
			if( pstrWifiState->u8CurrState == M2M_WIFI_CONNECTED)
			{
				m2m_wifi_request_dhcp_client();
			} 
			else if (pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED)
			{
				DEBUG(DEBUG_CONF_SOCKET"Wi-Fi disconnected"DEBUG_EOL);
			}
			break;
		}
		case M2M_WIFI_REQ_DHCP_CONF:
		{
			uint8_t *pu8IPAddress = (uint8_t*)pvMsg;
			DEBUG(DEBUG_CONF_WIFI "case M2M_WIFI_REQ_DHCP_CONF" DEBUG_EOL );
			DEBUG(DEBUG_CONF_WIFI "GET IP :is %u.%u.%u.%u" DEBUG_EOL, pu8IPAddress[0],pu8IPAddress[1],pu8IPAddress[2],pu8IPAddress[3]);
			ap_exosite_connection_state = MAIN_AP_CONNECTION;
			break;
		}
		case M2M_WIFI_RESP_DEFAULT_CONNECT:
		{
			tstrM2MDefaultConnResp *pstrDefConnInfo = (tstrM2MDefaultConnResp *)pvMsg;
			DEBUG(DEBUG_CONF_WIFI "M2M_WIFI_RESP_DEFAULT_CONNECT."DEBUG_EOL);
			if (pstrDefConnInfo->s8ErrorCode != M2M_SUCCESS) {
				ap_exosite_connection_state = MAIN_NEED_HTTP_PROVISIONING;
				DEBUG(DEBUG_CONF_WIFI "Set MAIN_NEED_HTTP_PROVISIONING mode "DEBUG_EOL);
			}
			else
			{
				ap_exosite_connection_state = MAIN_AP_CONNECTION;
				DEBUG(DEBUG_CONF_WIFI "Set MAIN_AP_CONNECTION mode "DEBUG_EOL);
				tick_counter_reset_timer(100);
			}
			break;		
		}
		case M2M_WIFI_RESP_PROVISION_INFO:
		{
			tstrM2MProvisionInfo *pstrProvInfo = (tstrM2MProvisionInfo *)pvMsg;
			DEBUG(DEBUG_CONF_WIFI "M2M_WIFI_RESP_PROVISION_INFO."DEBUG_EOL);

			if (pstrProvInfo->u8Status == M2M_SUCCESS) 
			{			
				m2m_wifi_connect((char *)pstrProvInfo->au8SSID, strlen((char *)pstrProvInfo->au8SSID), pstrProvInfo->u8SecType,
				pstrProvInfo->au8Password, M2M_WIFI_CH_ALL);
				DEBUG(DEBUG_CONF_WIFI "HTTP PROVISION Success."DEBUG_EOL);
			}
			else
			{
				DEBUG(DEBUG_CONF_WIFI "HTTP PROVISION  Failed."DEBUG_EOL);
				ap_exosite_connection_state = MAIN_NEED_HTTP_PROVISIONING;
			}
			break;
		}		
		default:
		{
			DEBUG(DEBUG_CONF_WIFI "call wifi_callback function msg type : %d" DEBUG_EOL, u8MsgType);
			break;
		}
	}
}

static void parsing_http_response_data(int response_code, char * response_data, int response_length)
{
	char buf[1024] = {0,};
	char *value_data_point = NULL;
	memcpy(buf, response_data,sizeof(char)*response_length);
	
	switch(response_code)
	{
		case MAIN_RES_HTTP_CODE_200:
		{
			if( response_length > 0)
			{
				if(!strncmp(buf, MAIN_LED_KEY_STRING, strlen(MAIN_LED_KEY_STRING)))
				{
					value_data_point = strstr(buf, "=");
					io1_board_set_led(*(++value_data_point)&0x0F);
					
				}
				else
				{
					value_data_point = buf;
					io1_board_save_cik_value_to_sd(value_data_point);
					DEBUG(DEBUG_CONF_EXOSITE"ACTIVATE Success"DEBUG_EOL);
				}
			}
		}
		break;
		case MAIN_RES_HTTP_CODE_204:
		//TODO:
		break;
		case MAIN_RES_HTTP_CODE_401:
		{
			//TODO:
			if( exosite_translate_state == MAIN_SENSOR_DATA_TRANSLATE_STATE)
			{
				DEBUG(DEBUG_CONF_EXOSITE"Stored cik key value is wrong. "DEBUG_EOL);
				DEBUG(DEBUG_CONF_EXOSITE"Stored cik key is reset."DEBUG_EOL);
				io1_board_reset_cik_value();
			}
		}
		break;
		case MAIN_RES_HTTP_CODE_404:
		//TODO:
		break;
		case MAIN_RES_HTTP_CODE_409:
		if( exosite_translate_state == MAIN_ACTIVITE_STATE)
		{
			DEBUG(DEBUG_CONF_EXOSITE"if the serial number is not enabled for activation."DEBUG_EOL);
			io1_board_reset_cik_value();
		}
		//TODO:
		break;
	}
}

/**
 * \brief Callback of the HTTP client.
 *
 * \param[in]  module_inst     Module instance of HTTP client module.
 * \param[in]  type            Type of event.
 * \param[in]  data            Data structure of the event. \refer http_client_data
 */
static void main_http_client_callback(struct http_client_module *module_inst, int type, union http_client_data *data)
{
	switch (type) {
	case HTTP_CLIENT_CALLBACK_SOCK_CONNECTED:
		DEBUG(DEBUG_CONF_EXOSITE"Exosite Server Connected"DEBUG_EOL);
		break;

	case HTTP_CLIENT_CALLBACK_REQUESTED:
		DEBUG(DEBUG_CONF_EXOSITE"Request complete"DEBUG_EOL);
		break;

	case HTTP_CLIENT_CALLBACK_RECV_RESPONSE:
		tick_counter_reset_timer(TICK_COUNTER_INTERVAL);
		parsing_http_response_data(data->recv_response.response_code, data->recv_response.content, data->recv_response.content_length);
		break;

	case HTTP_CLIENT_CALLBACK_DISCONNECTED:
		{
			tick_counter_reset_timer(TICK_COUNTER_INTERVAL);
			DEBUG(DEBUG_CONF_EXOSITE"Disconnected reason:%d"DEBUG_EOL, data->disconnected.reason);
			break;
		}
	}
}

/**
 * \brief Main application function.
 * Application entry point.
 * \return program return value.
 */
int main(void)
{
	tstrWifiInitParam param;
	int16_t ret;

	/* Initialize the board. */
	system_init();

	/* setting sleep mode. */
	system_set_sleepmode(SYSTEM_SLEEPMODE_IDLE_0);
	
	/* Initialize the UART console. */
	configure_console();
	DEBUG(DEBUG_EOL DEBUG_EOL DEBUG_STRING_HEADER);	
	DEBUG("\nPlease insert SD card in IO1_BOARD slot...\n\n");
	
	/* Initialize Io1 board. */
	io1_board_init();	
	
	/* Initialize Exosite. */
	exosite_example_init(main_http_client_callback);
	
	/* Initialize the BSP. */
	nm_bsp_init();
	
	/* Enable SysTick interrupt for non busy wait delay. */
	if (SysTick_Config(system_cpu_clock_get_hz() / 1000))
	{
		DEBUG("SysTick configuration error" DEBUG_EOL);
		while(1);
	}
	
	/* Initialize Wi-Fi parameters structure. */
	memset((uint8_t *)&param, 0, sizeof(tstrWifiInitParam));
	
	/* Initialize WINC1500 Wi-Fi driver with data and status callbacks. */
	param.pfAppWifiCb = wifi_cb;
	ret = m2m_wifi_init(&param);
	if (M2M_SUCCESS != ret) {
		DEBUG(DEBUG_CONF_WIFI "m2m_wifi_init call error!(%d)" DEBUG_EOL, ret);
		while (1) {
		}
	}	
	m2m_wifi_set_sleep_mode(M2M_PS_AUTOMATIC, 1);
	
	/* Initialize socket. */
	socketInit();
	registerSocketCallback(http_client_socket_event_handler, http_client_socket_resolve_handler);
	
	/* Get io1 board information from SD card. */
	p_board_info = io1_board_get_info();	
	if( !p_board_info ) 
		while(1);
	
	/* Connect using stored SSID and Password. */
	m2m_wifi_default_connect();	
	ap_exosite_connection_state = MAIN_CHECKING_AP_INFORMATION;
	
	for(;;system_sleep()) 
	{		
		/* Handle pending events from network controller. */
		ret = m2m_wifi_handle_events(NULL);		
		if( ret != M2M_SUCCESS ) 
		{	
			DEBUG(DEBUG_CONF_WIFI "wifi_handle_event error code :%d"DEBUG_EOL, ret);
		}
		
		/* Check Wi-Fi AP connection state. */
		if( ap_exosite_connection_state != MAIN_AP_CONNECTION) 
		{
			if( ap_exosite_connection_state == MAIN_NEED_TO_CHECK_AP_INFORMATION )
			{
				m2m_wifi_default_connect();
				ap_exosite_connection_state = MAIN_CHECKING_AP_INFORMATION;
				DEBUG(DEBUG_CONF_WIFI "m2m_wifi_default_connect start"DEBUG_EOL);
			}
			else if (ap_exosite_connection_state == MAIN_NEED_HTTP_PROVISIONING)
			{
				uint8_t mac_addr[6];
				uint8_t u8IsMacAddrValid;
				
				m2m_wifi_get_otp_mac_address(mac_addr, &u8IsMacAddrValid);
				if (!u8IsMacAddrValid) {
					m2m_wifi_set_mac_address(gau8MacAddr);
				}
				m2m_wifi_get_mac_address(gau8MacAddr);
				set_dev_name_to_mac((uint8_t *)gacDeviceName, gau8MacAddr);
				set_dev_name_to_mac((uint8_t *)gstrM2MAPConfig.au8SSID, gau8MacAddr);
				
				m2m_wifi_set_device_name((uint8_t *)gacDeviceName, (uint8_t)m2m_strlen((uint8_t *)gacDeviceName));
				
				m2m_wifi_start_provision_mode((tstrM2MAPConfig *)&gstrM2MAPConfig, (char *)gacHttpProvDomainName, 1);
				ap_exosite_connection_state = MAIN_DOING_AP_HTTP_PROVISIONING;
				DEBUG(DEBUG_CONF_WIFI "m2m_wifi_start_provision_mode start"DEBUG_EOL);
			}
			continue;
		}
		/* Check cik value & activation. */
		if( tick_counter_check_timer() )
		{	
			/* Check to activate state from cik. */
			if( !p_board_info->is_activate )
			{
				char activate_data[100] = {0,};
				sprintf(activate_data,MAIN_EXOSITE_ACTIVATE_DATA_FORMAT,p_board_info->board_vendor,p_board_info->board_id,p_board_info->board_sn);				
				if( exosite_example_activiate(activate_data) )
					exosite_translate_state = MAIN_ACTIVITE_STATE;
				
			}
			else
			{
				/* Send IO1 board data. */
				char send_buf[100] = {0,};
				int dTemp = 0;
				int dLight = 0;
				
				io1_board_prepare_to_get_info();
				dTemp = io1_board_get_temperature();
				dLight = io1_board_get_lightvalue();				
				sprintf(send_buf,"degree=%d&voltage=%d", (int)dTemp, (int)dLight);
				if( exosite_example_read_and_write(send_buf, (char*)p_board_info->cik) )
					exosite_translate_state = MAIN_SENSOR_DATA_TRANSLATE_STATE;
			}
		}
	}

	return 0;
}
