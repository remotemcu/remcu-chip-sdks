/**
 *
 * \file
 *
 * \brief WINC1500 Security Connection with WEP,WPA Security Example.
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
 * This example demonstrates the use of the WINC1500 with the SAM Xplained Pro board
 * to connect to a secured WEP, WPA network.<br>
 * It uses the following hardware:
 * - the SAM Xplained Pro.
 * - the WINC1500 on EXT1.
 *
 * \section files Main Files
 * - main.c : Initialize the WINC1500 and connect AP using Security mode WEP, WPA.
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
 * -# Prepare an AP that supports WEP and WPA/WPA2 Security and configure Wi-Fi Security.
 * For more information, please refer to manufacturer's manual.
 * -# To test WPA Security, Use case 2 in main function and modify MAIN_WLAN_PSK in source file "main.h".
 * \code
 * #define MAIN_WLAN_PSK         "12345678"
 * \endcode
 * -# To test WEP Security, Use case 1 in main function and select wep64_parameters or wep128_parameters as security parameters.
 * Modify MAIN_WLAN_DEVICE_NAME, MAIN_WLAN_WEP_KEY_INDEX and MAIN_WLAN_WEP_KEY_40 or MAIN_WLAN_WEP_KEY_104 in source file "main.h".
 * \code
 *    #define MAIN_WLAN_DEVICE_NAME      "DEMO_AP"
 *    #define MAIN_WLAN_WEP_KEY_INDEX    1
 *    #define MAIN_WLAN_WEP_KEY_40       "1234567890"
 *    #define MAIN_WLAN_WEP_KEY_104      "1234567890abcdef1234567890"
 * \endcode
 *
 * -# Run the application. If the device connected successfully, IP address which is assigned by DHCP will be displayed on the terminal program
 * \code
 *    -- WINC1500 security connection with WEP,WPA security example --
 *    -- SAMD21_XPLAINED_PRO --
 *    -- Compiled: xxx xx xxxx xx:xx:xx --
 *    Connecting to XXXXXX.
 *    Wi-Fi connected
 *    Wi-Fi IP is xxx.xxx.xxx.xxx
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

/** Security parameters for 64 bit WEP Encryption @ref m2m_wifi_connect */
tstrM2mWifiWepParams wep64_parameters = { MAIN_WLAN_WEP_KEY_INDEX, sizeof(MAIN_WLAN_WEP_KEY_40), MAIN_WLAN_WEP_KEY_40};
/** Security parameters for 128 bit WEP Encryption @ref m2m_wifi_connect */
tstrM2mWifiWepParams wep128_parameters = { MAIN_WLAN_WEP_KEY_INDEX, sizeof(MAIN_WLAN_WEP_KEY_104), MAIN_WLAN_WEP_KEY_104};

#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- WINC1500 security connection with WEP,WPA security example --"STRING_EOL \
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
 * Connect AP using Security mode WEP, WPA
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

	/* Case 1. Connect to AP with security type WEP. */
	/* m2m_wifi_connect((char *)MAIN_WLAN_DEVICE_NAME, strlen((char *)MAIN_WLAN_DEVICE_NAME), M2M_WIFI_SEC_WEP, &wep64_parameters, M2M_WIFI_CH_ALL); */

	/* Case 2. Connect to AP with security type WPA. */
	m2m_wifi_connect((char *)MAIN_WLAN_DEVICE_NAME, strlen((char *)MAIN_WLAN_DEVICE_NAME), M2M_WIFI_SEC_WPA_PSK, (char *)MAIN_WLAN_PSK, M2M_WIFI_CH_ALL);
	printf("Connecting to %s.\r\n", (char *)MAIN_WLAN_DEVICE_NAME);

	/* Infinite loop to handle a event from the WINC1500. */
	while (1) {
		while (m2m_wifi_handle_events(NULL) != M2M_SUCCESS) {
		}
	}

	return 0;
}
