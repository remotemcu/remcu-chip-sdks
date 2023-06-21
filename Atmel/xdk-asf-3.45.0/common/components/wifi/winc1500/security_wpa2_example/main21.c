/**
 *
 * \file
 *
 * \brief WINC1500 security connection with WPA/WPA2 enterprise.
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
 * This example demonstrates the use of the WINC1500 with the SAMD21 Xplained Pro board
 * to connect to a secured WPA/WPA2 (enterprise) network.<br>
 * It uses the following hardware:
 * - the SAMD21 Xplained Pro.
 * - the WINC1500 on EXT1.
 *
 * \section files Main Files
 * - main.c : Initialize the WINC1500 and connect AP using security WPA/WPA2 enterprise.
 *
 * \section usage Usage
 * -# Assemble the devices and connect to USB debug cable from PC.
 * -# On the computer, open and configure a terminal application as the follows.
 * \code
 *    Baud Rate : 115200
 *    Data : 8bit
 *    Parity bit : none
 *    Stop bit : 1bit
 *    Flow control : none
 * \endcode
 *
 * -# Prepare an AP that supports WPA/WPA2 enterprise security.
 * -# You need to know following things before configuring RADIUS server settings in the AP.
 * Ask your network administrator to get there information and configure it in the AP.
 * \code
 *    User name
 *    Password
 *    Name of wireless network
 *    Root certificate file
 * \endcode
 *
 * -# Modify MAIN_WLAN_802_1X_USR_NAME, MAIN_WLAN_802_1X_PWD to the name and the password, respectively.
 * Modify MAIN_WLAN_DEVICE_NAME to wireless network name
 * \code
 *    #define MAIN_WLAN_DEVICE_NAME         "DEMO_AP"
 *    #define MAIN_WLAN_802_1X_USR_NAME     "atmeluser"
 *    #define MAIN_WLAN_802_1X_PWD          "12345678"
 * \endcode
 *
 * -# Build and run the application. If the device connected successfully, IP address which is assigned by DHCP will be displayed on the terminal program.
 * \code
 *    -- WINC1500 security connection with WPA/WPA2 enterprise example --
 *    -- SAMD21_XPLAINED_PRO --
 *    -- Compiled: xxx xx xxxx xx:xx:xx --
 *    Wi-Fi connected
 *    Wi-Fi IP is xxx.xxx.xxx.xxx
 *    Connection successfully completed.
 * \endcode
 *
 * \warning
 * \code
 *    For using the security enterprise network, the root certificate must be installed.
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
#include "driver/include/m2m_wifi.h"
#include "driver/source/nmasic.h"

/** credential parameter for 802.1x */
static CONST tstr1xAuthCredentials gstrCred1x = { MAIN_WLAN_802_1X_USR_NAME, MAIN_WLAN_802_1X_PWD};

#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- WINC1500 security connection with WPA/WPA2 enterprise example --"STRING_EOL \
	"-- "BOARD_NAME " --"STRING_EOL	\
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

/** UART module for debug. */
static struct usart_module cdc_uart_module;

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
static void wifi_cb(uint8_t u8MsgType, void *pvMsg)
{
	switch (u8MsgType) {
	case M2M_WIFI_RESP_CON_STATE_CHANGED:
	{
		tstrM2mWifiStateChanged *pstrWifiState = (tstrM2mWifiStateChanged *)pvMsg;
		if (pstrWifiState->u8CurrState == M2M_WIFI_CONNECTED) {
			printf("Wi-Fi connected\r\n");
			m2m_wifi_request_dhcp_client();
		} else if (pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED) {
			printf("Wi-Fi disconnected\r\n");
			printf("Error code: %d",pstrWifiState->u8ErrCode);
		}

		break;
	}

	case M2M_WIFI_REQ_DHCP_CONF:
	{
		tstrM2MIPConfig *dhcpConf = (tstrM2MIPConfig *)pvMsg;
		uint8_t *pu8IPAddress = (uint8_t *)&dhcpConf->u32StaticIP;
		uint8_t *u32Gateway = (uint8_t *)&dhcpConf->u32Gateway;
		uint8_t *u32DNS = (uint8_t *)&dhcpConf->u32DNS;
		uint8_t *u32SubnetMask = (uint8_t *)&dhcpConf->u32SubnetMask;
		printf("Wi-Fi connected\r\n");
		printf("Wi-Fi IP is %u.%u.%u.%u\r\n",pu8IPAddress[0], pu8IPAddress[1], pu8IPAddress[2], pu8IPAddress[3]);
		printf("Gateway IP is %u.%u.%u.%u\r\n",u32Gateway[0], u32Gateway[1], u32Gateway[2], u32Gateway[3]);
		printf("DNS IP is %u.%u.%u.%u\r\n",u32DNS[0], u32DNS[1], u32DNS[2], u32DNS[3]);
		printf("Subnet mask IP is %u.%u.%u.%u\r\n",u32SubnetMask[0], u32SubnetMask[1], u32SubnetMask[2], u32SubnetMask[3]);
		break;
	}

	default:
	{
		break;
	}
	}
}

/**
 * \brief Main application function.
 *
 * Application entry point.
 * Initialize system, UART and board specific settings.
 * Connect AP using Security mode WPA/WPA2 enterprise
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
	printf("Username:%s\r\n",MAIN_WLAN_802_1X_USR_NAME);
	/* Connect to the enterprise network. */
	m2m_wifi_connect((char *)MAIN_WLAN_DEVICE_NAME, sizeof(MAIN_WLAN_DEVICE_NAME), M2M_WIFI_SEC_802_1X, (char *)&gstrCred1x, M2M_WIFI_CH_ALL);

	/* Infinite loop to handle a event from the WINC1500. */
	while (1) {
		while (m2m_wifi_handle_events(NULL) != M2M_SUCCESS) {
		}
	}

	return 0;
}
