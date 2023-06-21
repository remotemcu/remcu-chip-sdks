/**
 *
 * \file
 *
 * \brief WINC1500 Power Save Mode Example.
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
 * board to set the PS (Power Save) mode.<br>
 * It uses the following hardware:
 * - the SAMD21 Xplained Pro.
 * - the WINC1500 on EXT1.
 *
 * \section files Main Files
 * - main.c : Initialize the WINC1500 and set PS Mode and the get RSSI for the connected AP.
 *
 * \section usage Usage
 * -# Configure below code in the config main.h for AP information to be connected.
 * \code
 *    #define MAIN_WLAN_SSID         "DEMO_AP"
 *    #define MAIN_WLAN_AUTH         M2M_WIFI_SEC_WPA_PSK
 *    #define MAIN_WLAN_PSK          "12345678"
 * \endcode
 * -# Configure below code in the config main.h for PowerSave mode.
 * \code
 *    #define MAIN_PS_SLEEP_MODE      M2M_PS_MANUAL
 * \endcode
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
 *    -- WINC1500 Power Save mode example --
 *    -- SAMD21_XPLAINED_PRO --
 *    -- Compiled: xxx xx xxxx xx:xx:xx --
 *
 *    Wi-Fi connected
 *    Wi-Fi IP is xxx.xxx.xxx.xxx
 *    RSSI for the current connected AP (-xx)
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
#include "driver/include/m2m_periph.h"
#include "driver/include/m2m_wifi.h"
#include "driver/source/nmasic.h"

#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- WINC1500 Power Save mode example --"STRING_EOL	\
	"-- "BOARD_NAME " --"STRING_EOL	\
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

/** Wi-Fi Sleep status. */
static uint8 gu8SleepStatus;
/** Instance of Timer module. */
struct tcc_module deep_sleep_tcc_module;
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
 * \brief Timer callback function for the Request RSSI.
 */
static void timer_callback(struct tcc_module *const module)
{
	m2m_wifi_req_curr_rssi();
}

/**
 * \brief Configure Timer module.
 */
static void configure_timer(void)
{
	/**
	 * Timer period is 1s = Prescaler(1024) * Period(46875) / Clock(48Mhz).
	 */
	struct tcc_config tcc_conf;
	tcc_get_config_defaults(&tcc_conf, TCC0);
	tcc_conf.counter.period = 46875;
	tcc_conf.counter.clock_prescaler = TCC_CLOCK_PRESCALER_DIV1024;

	tcc_init(&deep_sleep_tcc_module, TCC0, &tcc_conf);
	/* Register timer callback for the Request RSSI. */
	tcc_register_callback(&deep_sleep_tcc_module, timer_callback, TCC_CALLBACK_CHANNEL_3);
	tcc_enable(&deep_sleep_tcc_module);
}

/**
 * \brief Callback to get the Wi-Fi status update.
 *
 * \param[in] u8MsgType type of Wi-Fi notification. Possible types are:
 *  - [M2M_WIFI_RESP_CURRENT_RSSI](@ref M2M_WIFI_RESP_CURRENT_RSSI)
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
		gu8SleepStatus = MAIN_PS_WAKE;
		tstrM2mWifiStateChanged *pstrWifiState = (tstrM2mWifiStateChanged *)pvMsg;
		if (pstrWifiState->u8CurrState == M2M_WIFI_CONNECTED) {
			m2m_wifi_request_dhcp_client();
		} else if (pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED) {
			printf("Wi-Fi disconnected\r\n");

			/* Connect to defined AP. */
			m2m_wifi_connect((char *)MAIN_WLAN_SSID, sizeof(MAIN_WLAN_SSID), MAIN_WLAN_AUTH, (void *)MAIN_WLAN_PSK, M2M_WIFI_CH_ALL);
		}

		break;
	}

	case M2M_WIFI_REQ_DHCP_CONF:
	{
		uint8_t *pu8IPAddress = (uint8_t *)pvMsg;
		printf("Wi-Fi connected\r\n");
		printf("Wi-Fi IP is %u.%u.%u.%u\r\n",
				pu8IPAddress[0], pu8IPAddress[1], pu8IPAddress[2], pu8IPAddress[3]);
		gu8SleepStatus = MAIN_PS_REQ_SLEEP;
		tcc_enable_callback(&deep_sleep_tcc_module, TCC_CALLBACK_CHANNEL_3);
		break;
	}

	case M2M_WIFI_RESP_CURRENT_RSSI:
	{
		/* This message type is triggered by "m2m_wifi_req_curr_rssi()" function. */
		int8_t *rssi = (int8_t *)pvMsg;
		printf("RSSI for the current connected AP (%d)\r\n", (int8_t)(*rssi));
		gu8SleepStatus = MAIN_PS_REQ_SLEEP;
		break;
	}

	default:
	{
		break;
	}
	}
}

static void disable_pullups(void)
{
	uint32 pinmask;

	pinmask = (
	M2M_PERIPH_PULLUP_DIS_HOST_WAKEUP|
	M2M_PERIPH_PULLUP_DIS_GPIO_3|
	M2M_PERIPH_PULLUP_DIS_GPIO_5|
	M2M_PERIPH_PULLUP_DIS_SD_DAT0_SPI_TXD|
	M2M_PERIPH_PULLUP_DIS_GPIO_6);

	m2m_periph_pullup_ctrl(pinmask, 0);
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
	system_init();

	/* Initialize the UART console. */
	configure_console();
	printf(STRING_HEADER);

	/* Initialize the Timer. */
	configure_timer();

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

	/* Disable pullups */
	disable_pullups();

	/* Set defined sleep mode */
	if (MAIN_PS_SLEEP_MODE == M2M_PS_MANUAL) {
		printf("M2M_PS_MANUAL\r\n");
		m2m_wifi_set_sleep_mode(MAIN_PS_SLEEP_MODE, 1);
	} else if (MAIN_PS_SLEEP_MODE == M2M_PS_DEEP_AUTOMATIC) {
		printf("M2M_PS_DEEP_AUTOMATIC\r\n");
		tstrM2mLsnInt strM2mLsnInt;
		m2m_wifi_set_sleep_mode(M2M_PS_DEEP_AUTOMATIC, 1);
		strM2mLsnInt.u16LsnInt = M2M_LISTEN_INTERVAL;
		m2m_wifi_set_lsn_int(&strM2mLsnInt);
	} else {
		printf("M2M_PS_NO\r\n");
	}

	/* Connect to defined AP. */
	m2m_wifi_connect((char *)MAIN_WLAN_SSID, sizeof(MAIN_WLAN_SSID), MAIN_WLAN_AUTH, (void *)MAIN_WLAN_PSK, M2M_WIFI_CH_ALL);

	while (1) {
		/* Request sleep mode */
		if (gu8SleepStatus == MAIN_PS_REQ_SLEEP) {
			if (MAIN_PS_SLEEP_MODE == M2M_PS_MANUAL) {
				m2m_wifi_request_sleep(MAIN_REQUEST_SLEEP_TIME);
				gu8SleepStatus = MAIN_PS_SLEEP;
			}
		}

		while (m2m_wifi_handle_events(NULL) != M2M_SUCCESS) {
		}
	}

	return 0;
}
