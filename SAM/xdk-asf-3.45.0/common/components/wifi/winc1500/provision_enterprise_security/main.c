/**
 *
 * \file
 *
 * \brief WINC1500 security connection with WPA/WPA2 enterprise.
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
 * This example demonstrates the use of the WINC1500 with the SAMD21 Xplained Pro
 * board to start Wi-Fi provisioning mode using simple HTTPS server implemented in SAMD21.
 * This example support provisioning in following Wi-Fi Security mode.
 * - Open
 * - WPA/WPA2 PSK
 * - WEP
 * - 802.1X Enterprise security
 * The following enterprise security methods are supported
 * - TTLSv0 with MSCHAPV2
 * - PEAPv0/1 with MSCHAPV2
 * - EAP with TLS
 * - PEAPv0/1 with TLS
 *  
 * It uses the following hardware:
 * - the SAMXXX Xplained Pro.
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
 * -# Prepare an AP that supports OPEN / WEP / WPA/WPA2 enterprise security.
 * -# For connecting to enterprise network, you need to know following things before configuring RADIUS server settings in the AP.
 * Ask your network administrator to get there information and configure it in the AP.
 * \code
 *    User name
 *    Password
 *    Name of wireless network
 *    Root certificate file
 *    TLS certificate and key (for TLS connection) 
 * \endcode
 *
 * -# Build and run the application. The WINC1500 will enumerate as a soft AP with SSID provided by the parameter PROV_WLAN_SOFTAP_SSID.
 * Connect Laptop / Mobile to the enumurated soft AP. Once the Wi-Fi Link is established, Open Google chrome or Firefox web browser and
 * open the web page https://192.168.1.1/provisioning.html and provide the credential of the AP to which WINC1500 has to connected and
 * click connect button.
 * If the device connected successfully, IP address which is assigned by DHCP will be displayed on the terminal program.
 * \code
 * -- WINC1500 provisioning for enterprise security example --
 *    -- SAMxxx_XPLAINED_PRO --
 * (APP)(INFO)Chip ID 1503a0
 * (APP)(INFO)DriverVerInfo: 0x13301361
 * (APP)(INFO)Firmware ver   : 19.6.1 Svnrev 16761
 * (APP)(INFO)Firmware Build May 23 2018 Time 14:39:16
 * (APP)(INFO)Firmware Min driver ver : 19.3.0
 * (APP)(INFO)Driver ver: 19.6.1
 * (APP)(INFO)Driver built at xxx  xx xxxx  xxxx
 * AP mode started. You can connect to WINC1500_PROV_HTTP.
 * prov_wifi_cb: M2M_WIFI_RESP_CON_STATE_CHANGED: CONNECTED
 * prov_wifi_cb: M2M_WIFI_REQ_DHCP_CONF: IP is 192.168.1.100
 * (APP)(INFO)Socket 0 session ID = 1
 * prov_socket_cb: bind success!
 * Credentials received...
 * (APP)(INFO)Sock to delete <1>
 * (APP)(INFO)Sock to delete <0>
 * prov_wifi_cb: M2M_WIFI_RESP_CON_STATE_CHANGED: DISCONNECTED
 * Credential received
 * Connecting to WINC1500_ENTERPRISE...(APP)(INFO)Chip ID 1503a0
 * (APP)(INFO)DriverVerInfo: 0x13301361
 * (APP)(INFO)Firmware ver   : 19.6.1 Svnrev 16761
 * (APP)(INFO)Firmware Build May 23 2018 Time 14:39:16
 * (APP)(INFO)Firmware Min driver ver : 19.3.0
 * (APP)(INFO)Driver ver: 19.6.1
 * (APP)(INFO)Driver built at xxx  xx xxxx  xxxx
 * Enterprise Security using xxxx - Connecting to xxxxx...
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
 * This software was written for the GNU GCC compiler using Atmel Studio 7
 * Other compilers may or may not work.
 * Provisiong web page has been tested in Google chrome and Firefox. The web page may not work perfectly in other browser.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com">Microchip</A>.\n
 */

#include "asf.h"
#include "wifi_prov.h"
#include "main.h"
#include "driver/include/m2m_wifi.h"
#include "socket/include/socket.h"

#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- WINC1500 provisioning for enterprise security example --"STRING_EOL \
	"-- "BOARD_NAME " --"STRING_EOL	\
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

static wifiProvisionParams wifiProvParam;
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
			m2m_wifi_request_dhcp_client();
		} else if (pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED) {
			printf("Wi-Fi disconnected\r\n");

			/* Connect to defined AP. */
			m2m_wifi_default_connect();
		}
		break;
	}

	case M2M_WIFI_REQ_DHCP_CONF:
	{
		uint8_t *pu8IPAddress = (uint8_t *)pvMsg;
		printf("Wi-Fi connected\r\n");
		printf("Wi-Fi IP is %u.%u.%u.%u\r\n",
				pu8IPAddress[0], pu8IPAddress[1], pu8IPAddress[2], pu8IPAddress[3]);

		printf("Connection successfully completed.");
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
 *
 * \return program return value.
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

	/* Start provisioning */
	wifi_ap_provision(&wifiProvParam);

	printf("Credential received\r\n");
	printf("Connecting to %s...", wifiProvParam.httpProvParams.au8SSID);

	/* Initialize Wi-Fi driver with data and status callbacks. */
	param.pfAppWifiCb = wifi_cb;
	ret = m2m_wifi_init(&param);
	if (M2M_SUCCESS != ret) {
		printf("main: m2m_wifi_init call error!(%d)\r\n", ret);
		while (1) {
		}
	}

	/* Connect to AP with the credentials received from provisioning web page*/
	wifi_ap_connect(&wifiProvParam);

	while (1) {
		/* Handle pending events from network controller. */
		m2m_wifi_handle_events(NULL);
		}
}
