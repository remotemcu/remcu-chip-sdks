/**
 *
 * \file
 *
 * \brief WINC1500 enterprise security connection with MSCHAPV2.
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
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
 * This example demonstrates the use of the WINC1500 with the SAMxx Xplained Pro board
 * to connect to a secured 802.1x enterprise network that supports MSCHAPV2 as phase 2 authentication.<br>
 * The following Enterprise security methods are supported by this example.
 * \code
  * - TTLSv0 with MSCHAPV2
 * - PEAPv0 with MSCHAPV2
 * - PEAPv1 with MSCHAPV2
 * \endcode
 *
 * This example require following hardware:
 * - the SAMXXX Xplained Pro.
 * - the WINC1500 on EXT1.
 *
 * \section files Main Files
 * - main.c : Initialize the WINC1500 and connect to network that support enterprise security
 * with MSCHAPV2 authentication protocol.
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
 * -# Prepare an AP that supports enterprise security with any of the following security method.
 * - TTLSv0 with MSCHAPV2
 * - PEAPv0 with MSCHAPV2
 * - PEAPv1 with MSCHAPV2
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
 * Modify MAIN_WLAN_SSID to wireless network name
 * \code
 *    #define MAIN_WLAN_SSID         "WINC1500_ENTERPRISE"
 *    #define MAIN_WLAN_802_1X_USR_NAME     "DEMO_USER"
 *    #define MAIN_WLAN_802_1X_PWD          "DemoPassword"
 * \endcode
 *
 * -# Build and run the application. If the device connected successfully, IP address which is assigned by DHCP will be displayed on the terminal program.
 * \code
 *    -- WINC1500 enterprise security connection with MSCHAPV2 example --
 *    -- SAMXXX_XPLAINED_PRO --
 *    -- Compiled: xxx xx 2018 hh:mm:ss --
 *    (APP)(INFO)Chip ID 1503a0
 *    (APP)(INFO)DriverVerInfo: 0x13301361
 *    (APP)(INFO)Firmware ver   : 19.6.1 Svnrev 16761
 *    (APP)(INFO)Firmware Build May 23 2018 Time 14:39:16
 *    (APP)(INFO)Firmware Min driver ver : 19.3.0
 *    (APP)(INFO)Driver ver: 19.6.1
 *    (APP)(INFO)Driver built at xxx  x 2018  hh:mm:ss
 *    Connecting to WINC1500_ENTERPRISE
 *            Username:DEMO_USER
 *    Wi-Fi connected
 *    Wi-Fi IP is 192.168.100.105
 *    Connection successfully completed.
 * \endcode
 *
 * \warning
 * \code
 *    For using the security enterprise network, the root certificate must be written to WINC1500.
 *    Download the root certificate using the root_certificate_downloader. (Refer to WINC1500 Software User Guide.)
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
#include "main.h"
#include <string.h>
#include "driver/include/m2m_wifi.h"
#include "driver/source/nmasic.h"

#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- WINC1500 enterprise security connection with MSCHAPV2 example --"STRING_EOL \
	"-- "BOARD_NAME " --"STRING_EOL	\
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

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
		}

		break;
	}

	case M2M_WIFI_REQ_DHCP_CONF:
	{
		uint8_t *pu8IPAddress = (uint8_t *)pvMsg;
		printf("Wi-Fi IP is %u.%u.%u.%u\r\n",
				pu8IPAddress[0], pu8IPAddress[1], pu8IPAddress[2], pu8IPAddress[3]);
		printf("Connection successfully completed.\r\n");
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
 * Connect AP using Enterprise Security - MSCHAPV2 
 *
 * \return program return value.
 */
int main(void)
{
	int8_t ret;
	tstrWifiInitParam param;
	tstrNetworkId networkId;
	tstrAuth1xMschap2 mschapv2_credential;

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

	networkId.pu8Bssid = NULL;
	networkId.pu8Ssid = (uint8 *)MAIN_WLAN_SSID;
	networkId.u8SsidLen = strlen(MAIN_WLAN_SSID);
	networkId.enuChannel = M2M_WIFI_CH_ALL;
	
	mschapv2_credential.pu8Domain = NULL;
	//mschapv2_credential.u16DomainLen = strlen(mschapv2_credential.pu8Domain);
	mschapv2_credential.pu8UserName = (uint8 *)MAIN_WLAN_802_1X_USR_NAME;
	mschapv2_credential.pu8Password = (uint8 *)MAIN_WLAN_802_1X_PWD;
	mschapv2_credential.u16UserNameLen = strlen(MAIN_WLAN_802_1X_USR_NAME);
	mschapv2_credential.u16PasswordLen = strlen(MAIN_WLAN_802_1X_PWD);
	mschapv2_credential.bUnencryptedUserName = false;
	mschapv2_credential.bPrependDomain = true;
	
	printf("Connecting to %s\r\n\tUsername:%s\r\n",networkId.pu8Ssid,mschapv2_credential.pu8UserName);
		
	m2m_wifi_connect_1x_mschap2( WIFI_CRED_SAVE_ENCRYPTED, &networkId, &mschapv2_credential);

	/* Infinite loop to handle a event from the WINC1500. */
	while (1) {
		while (m2m_wifi_handle_events(NULL) != M2M_SUCCESS) {
		}
	}

	return 0;
}
