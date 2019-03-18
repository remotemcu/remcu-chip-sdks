/**
 *
 * \file
 *
 * \brief WINC1500 Simple Growl Example.
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
 * This example demonstrates the use of the WINC1500 with the SAM Xplained Pro.
 * It basically transmits a notification from the WINC1500 Wi-Fi module (based on a
 * certain trigger) to a public remote server which in turn sends back a notification
 * to a specific phone application.<br>
 * The initiated notification from the WINC1500 device is directed to a certain
 * subscriber on the server.<br>
 * The supported applications are PROWL (for iPhone notifications) and NMA (for
 * ANDROID notifications).<br>
 * It uses the following hardware:
 * - the SAM Xplained Pro.
 * - the WINC1500 on EXT1.
 *
 * \section files Main Files
 * - main.c : Initialize growl and send notification message.
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
 *    -- WINC1500 simple growl example --
 *    -- SAMXXX_XPLAINED_PRO --
 *    -- Compiled: xxx xx xxxx xx:xx:xx --
 *    Provision Mode started.
 *    Connect to [atmelconfig.com] via AP[WINC1500_xx:xx] and fill up the page
 *    Wi-Fi connected
 *    Wi-Fi IP is xxx.xxx.xxx.xxx
 *    wifi_cb: M2M_WIFI_RESP_PROVISION_INFO.
 *    Wi-Fi connected
 *    Wi-Fi IP is xxx.xxx.xxx.xxx
 *    send Growl message
 *    Growl CB : 20
 * \endcode
 *
 * This application supports sending GROWL notifications to the following servers.
 * -# PROWL for iOS push notifications (https://www.prowlapp.com/).
 * -# NMA for Android push notifications (http://www.notifymyandroid.com/).
 *
 * In order to enable the GROWL application (for sending notifications), apply the following instructions.
 * -# Create a NMA account at http://www.notifymyandroid.com/ and create an API key. Copy the obtained key string in the file
 *  main.h in the MACRO NMA_API_KEY as the following.
 * -# Create a PROWL account at https://www.prowlapp.com/ and create an API key. Copy the obtained API key string in the file
 *  main.h in the MACRO PROWL_API_KEY as the following.<br>
 *	#define NMA_API_KEY      "f8bd3e7c9c5c10183751ab010e57d8f73494b32da73292f6"<br>
 *	#define PROWL_API_KEY    "117911f8a4f2935b2d84abc934be9ff77d883678"
 *
 * \warning
 * \code
 *    For using the growl, the root certificate must be installed.
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
#include "growl/growl.h"

#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- WINC1500 simple growl example --"STRING_EOL \
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
 * \brief Send a specific notification to a registered Android(NMA) or IOS(PROWL)
 */
static int growl_send_message_handler(void)
{
	printf("send Growl message \r\n");
	/* NMI_GrowlSendNotification(PROWL_CLIENT, (uint8_t*)"Growl_Sample", (uint8_t*)"Growl_Event", (uint8_t*)msg_for_growl,PROWL_CONNECTION_TYPE); // send by PROWL */
	NMI_GrowlSendNotification(NMA_CLIENT, (uint8_t *)"Growl_Sample", (uint8_t *)"Growl_Event", (uint8_t *)"growl_test", NMA_CONNECTION_TYPE);           /* send by NMA */

	return 0;
}

static void set_dev_name_to_mac(uint8_t *name, uint8_t *mac_addr)
{
	/* Name must be in the format WINC1500_00:00 */
	uint16 len;

	len = m2m_strlen(name);
	if (len >= 5) {
		name[len - 1] = MAIN_HEX2ASCII((mac_addr[5] >> 0) & 0x0f);
		name[len - 2] = MAIN_HEX2ASCII((mac_addr[5] >> 4) & 0x0f);
		name[len - 4] = MAIN_HEX2ASCII((mac_addr[4] >> 0) & 0x0f);
		name[len - 5] = MAIN_HEX2ASCII((mac_addr[4] >> 4) & 0x0f);
	}
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

		if (gbRespProvInfo) {
			/** init growl */
			NMI_GrowlInit((uint8_t *)PROWL_API_KEY, (uint8_t *)NMA_API_KEY);
			growl_send_message_handler();
		}

		break;
	}

	case M2M_WIFI_RESP_PROVISION_INFO:
	{
		tstrM2MProvisionInfo *pstrProvInfo = (tstrM2MProvisionInfo *)pvMsg;
		printf("wifi_cb: M2M_WIFI_RESP_PROVISION_INFO.\r\n");

		if (pstrProvInfo->u8Status == M2M_SUCCESS) {
			m2m_wifi_connect((char *)pstrProvInfo->au8SSID, strlen((char *)pstrProvInfo->au8SSID), pstrProvInfo->u8SecType,
					pstrProvInfo->au8Password, M2M_WIFI_CH_ALL);
			gbRespProvInfo = true;
		} else {
			printf("wifi_cb: Provision failed.\r\n");
		}

		break;
	}

	default:
	{
		break;
	}
	}
}

/**
 * \brief Growl notification callback.
 *	Pointer to a function delivering growl events.
 *
 *  \param	[u8Code] Possible error codes could be returned by the nma server and refer to the comments in the growl.h.
 *  - [20] GROWL_SUCCESS (@ref GROWL_SUCCESS)
 *  - [40] GROWL_ERR_BAD_REQUEST (@ref GROWL_ERR_BAD_REQUEST)
 *  - [41] GROWL_ERR_NOT_AUTHORIZED (@ref GROWL_ERR_NOT_AUTHORIZED)
 *  - [42] GROWL_ERR_NOT_ACCEPTED (@ref GROWL_ERR_NOT_ACCEPTED)
 *  - [46] GROWL_ERR_API_EXCEED (@ref GROWL_ERR_API_EXCEED)
 *  - [49] GROWL_ERR_NOT_APPROVED (@ref GROWL_ERR_NOT_APPROVED)
 *  - [50] GROWL_ERR_SERVER_ERROR (@ref GROWL_ERR_SERVER_ERROR)
 *  - [30] GROWL_ERR_LOCAL_ERROR (@ref GROWL_ERR_LOCAL_ERROR)
 *  - [10] GROWL_ERR_CONN_FAILED (@ref GROWL_ERR_CONN_FAILED)
 *  - [11] GROWL_ERR_RESOLVE_DNS (@GROWL_ERR_RESOLVE_DNS GROWL_RETRY)
 *  - [12] GROWL_RETRY (@ref GROWL_RETRY)
 *	\param	[u8ClientID] client id returned by the nma server.
 */
void GrowlCb(uint8_t u8Code, uint8_t u8ClientID)
{
	printf("Growl CB : %d \r\n", u8Code);
}

/**
 * \brief Main application function.
 *
 * \return program return value.
 */
int main(void)
{
	tstrWifiInitParam param;
	int8_t ret;

	uint8_t mac_addr[6];
	uint8_t u8IsMacAddrValid;

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

	m2m_wifi_get_otp_mac_address(mac_addr, &u8IsMacAddrValid);
	if (!u8IsMacAddrValid) {
		m2m_wifi_set_mac_address(gau8MacAddr);
	}

	m2m_wifi_get_mac_address(gau8MacAddr);

	set_dev_name_to_mac((uint8_t *)gacDeviceName, gau8MacAddr);
	set_dev_name_to_mac((uint8_t *)gstrM2MAPConfig.au8SSID, gau8MacAddr);
	m2m_wifi_set_device_name((uint8_t *)gacDeviceName, (uint8_t)m2m_strlen((uint8_t *)gacDeviceName));
	gstrM2MAPConfig.au8DHCPServerIP[0] = 0xC0; /* 192 */
	gstrM2MAPConfig.au8DHCPServerIP[1] = 0xA8; /* 168 */
	gstrM2MAPConfig.au8DHCPServerIP[2] = 0x01; /* 1 */
	gstrM2MAPConfig.au8DHCPServerIP[3] = 0x01; /* 1 */

	m2m_wifi_start_provision_mode((tstrM2MAPConfig *)&gstrM2MAPConfig, (char *)gacHttpProvDomainName, 1);
	printf("Provision Mode started.\r\nConnect to [%s] via AP[%s] and fill up the page.\r\n", MAIN_HTTP_PROV_SERVER_DOMAIN_NAME, gstrM2MAPConfig.au8SSID);

	while (1) {
		/* Handle pending events from network controller. */
		while (m2m_wifi_handle_events(NULL) != M2M_SUCCESS) {
		}
	}

	return 0;
}
