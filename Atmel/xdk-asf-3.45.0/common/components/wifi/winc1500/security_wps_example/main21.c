/**
 *
 * \file
 *
 * \brief WINC1500 Security Connection with Wi-Fi Protected Setup(WPS) Example.
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
 * to connect to AP with WPS Security.<br>
 * It uses the following hardware:
 * - the SAMD21 Xplained Pro.
 * - the WINC1500 on EXT1.
 *
 * \section files Main Files
 * - main.c : Initialize the WINC1500 and connect AP using WPS.
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
 * -# Prepare an AP that supports Wi-Fi Protected Setup(WPS)
 *
 * -# To test WPS button method, Use case 1 in main function.
 * -# Configure below code in the main.h for WPS push button feature.
 * \code
 *    #define MAIN_WPS_PUSH_BUTTON_FEATURE              "true"
 * \endcode
 * -# Press WPS button at the AP. ( For more information, please refer to AP product documentation )
 * -# Run the application. The WINC1500 will be connected to the AP automatically without security information.
 * \code
 *    -- WINC1500 security connection with Wi-Fi Protected Setup(WPS) example --
 *    -- SAMD21_XPLAINED_PRO --
 *    -- Compiled: xxx xx xxxx xx:xx:xx --
 *    SW0 button pressed
 *    Device is connecting using WPS Push Button option
 *    Wi-Fi request WPS
 *    SSID : xxxxxx, authtyp : x pw : xxxxxxxx
 *    Request Wi-Fi connect
 *    Wi-Fi connected
 *    Wi-Fi IP is xxx.xxx.xxx.xxx
 * \endcode
 *
 * -# To test WPS PIN method, Use case 2 in main function.
 * -# Configure below code in the main.h for WPS PIN number and WPS push button feature.
 * \code
 *    #define WPS_PIN_NUMBER                            "12345670"
 *    #define MAIN_WPS_PUSH_BUTTON_FEATURE              "false"
 * \endcode
 * -# Enter WPS PIN number in the AP setup menu and start the AP. ( For more information, please refer to AP product documentation )
 * -# Run the application. The WINC1500 will be connected to the AP automatically without security information.
 * \code
 *    -- WINC1500 security connection with Wi-Fi Protected Setup(WPS) example --
 *    -- SAMD21_XPLAINED_PRO --
 *    -- Compiled: xxx xx xxxx xx:xx:xx --
 *    Wi-Fi request WPS
 *    SSID : xxxxxx, authtyp : x pw : xxxxxxxx
 *    Request Wi-Fi connect
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
#include "driver/include/m2m_wifi.h"
#include "driver/source/nmasic.h"

#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- WINC1500 security connection with Wi-Fi Protected Setup(WPS) example --"STRING_EOL \
	"-- "BOARD_NAME " --"STRING_EOL	\
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

/** UART module for debug. */
static struct usart_module cdc_uart_module;

static bool gbPressButton = false;

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
 * \brief button pressed callback function.
 */
static void btn_press(uint8_t btn, uint8_t press)
{
	if (MAIN_SW1 == btn) {
		if (press ==  0) {
			printf("SW0 button pressed\r\n");
			m2m_wifi_wps(WPS_PBC_TRIGGER, NULL);
			printf("Device is connecting using WPS Push Button option\r\n");
		}
	}
}

/**
 * \brief Initialize buttons driver.
 */
static void btn_init(void)
{
	if (port_pin_get_input_level(BUTTON_0_PIN) == BUTTON_0_ACTIVE) {
		btn_press(MAIN_SW1, 0);
		gbPressButton = true;
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
		break;
	}

	case M2M_WIFI_REQ_WPS:
	{
		tstrM2MWPSInfo *pstrWPS = (tstrM2MWPSInfo *)pvMsg;
		printf("Wi-Fi request WPS\r\n");
		printf("SSID : %s, authtyp : %d pw : %s\n", pstrWPS->au8SSID, pstrWPS->u8AuthType, pstrWPS->au8PSK);
		if (pstrWPS->u8AuthType == 0) {
			printf("WPS is not enabled OR Timedout\r\n");
			m2m_wifi_request_scan(M2M_WIFI_CH_ALL);
			/* WPS is not enabled by firmware OR WPS monitor timeout.*/
		} else {
			printf("Request Wi-Fi connect\r\n");
			m2m_wifi_connect((char *)pstrWPS->au8SSID, (uint8)m2m_strlen(pstrWPS->au8SSID),
					pstrWPS->u8AuthType, pstrWPS->au8PSK, pstrWPS->u8Ch);
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
 * \brief Main application function.
 *
 * Application entry point.
 * Initialize system, UART and board specific settings.
 * Connect AP using WPS.
 *
 * \return program return value.
 */
int main(void)
{
	tstrWifiInitParam param;
	int8_t ret;
	char devName[] = "WINC1500_WPS";

	/* Initialize the board. */
	system_init();

	/* Initialize the UART console. */
	configure_console();
	printf(STRING_HEADER);

	/* Initialize the BSP. */
	nm_bsp_init();

	/* Initialize Wi-Fi parameters structure. */
	memset((uint8_t *)&param, 0, sizeof(tstrWifiInitParam));
	param.pfAppWifiCb = wifi_cb;
	/* Initialize WINC1500 Wi-Fi driver with data and status callbacks. */
	ret = m2m_wifi_init(&param);
	if (M2M_SUCCESS != ret) {
		printf("main: m2m_wifi_init call error!(%d)\r\n", ret);
		while (1) {
		}
	}

	/* Device name must be set before enabling WPS mode. */
	m2m_wifi_set_device_name((uint8 *)devName, strlen(devName));

	if (!MAIN_WPS_PUSH_BUTTON_FEATURE) {
		/* case 2 WPS PIN method */
		m2m_wifi_wps(WPS_PIN_TRIGGER, (const char *)MAIN_WPS_PIN_NUMBER);
	}

	/* Infinite loop to handle a event from the WINC1500. */
	while (1) {
		m2m_wifi_handle_events(NULL);
		if (MAIN_WPS_PUSH_BUTTON_FEATURE) {
			/* case 1 WPS Push Button method. */
			if (!gbPressButton) {
				btn_init();
			}
		}
	}

	return 0;
}
