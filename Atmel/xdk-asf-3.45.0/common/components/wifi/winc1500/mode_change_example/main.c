/**
 *
 * \file
 *
 * \brief WINC1500 Mode Change Example.
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
 * board to bring up as a station and then switch to an AP.<br>
 * It uses the following hardware:
 * - the SAM Xplained Pro.
 * - the WINC1500 on EXT1.
 *
 * \section files Main Files
 * - main.c : Initialize the WINC1500. For the first time, the device act as
 * station mode. Then switch to AP mode. For the details in each
 * mode, refer to the MODE_STA and MODE_AP example.
 *
 * \section usage Usage
 * -# Configure below code in the main.h for AP information.
 * \code
 *    #define MAIN_WLAN_SSID              "DEMO_AP"
 *    #define MAIN_WLAN_AUTH              M2M_WIFI_SEC_OPEN
 *    #define MAIN_WLAN_AP_CHANNEL        (6)
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
 *    -- WINC1500 mode change example --
 *    -- SAMD21_XPLAINED_PRO --
 *    -- Compiled: xxx xx xxxx xx:xx:xx --
 *    AP mode, start
 *    AP mode, end
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

#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- WINC1500 mode change example --"STRING_EOL \
	"-- "BOARD_NAME " --"STRING_EOL	\
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

#define HOLD_TIME_IN_MODE               (30000)
#define DELAY_FOR_MODE_CHANGE           (500)


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
 * \brief AP mode
 *
 * Initializes the AP mode for a while and terminate.
 */
static int8_t enable_disable_ap_mode(void)
{
	int8_t ret;
	tstrM2MAPConfig strM2MAPConfig;

	printf("AP mode, start\r\n");

	/* Configure AP. */
	memset(&strM2MAPConfig, 0x00, sizeof(tstrM2MAPConfig));
	strcpy((char *)&strM2MAPConfig.au8SSID, MAIN_WLAN_SSID);
	strM2MAPConfig.u8ListenChannel = MAIN_WLAN_AP_CHANNEL;
	strM2MAPConfig.u8SecType = MAIN_WLAN_AUTH;
	strM2MAPConfig.au8DHCPServerIP[0] = 0xC0; /* 192 */
	strM2MAPConfig.au8DHCPServerIP[1] = 0xA8; /* 168 */
	strM2MAPConfig.au8DHCPServerIP[2] = 0x01; /* 1 */
	strM2MAPConfig.au8DHCPServerIP[3] = 0x01; /* 1 */

	/* Start AP mode. */
	ret = m2m_wifi_enable_ap(&strM2MAPConfig);
	if (M2M_SUCCESS != ret) {
		return ret;
	}

	/* Keep in AP mode for a while. */
	nm_bsp_sleep(HOLD_TIME_IN_MODE);

	/* Stop AP mode. */
	ret = m2m_wifi_disable_ap();
	if (M2M_SUCCESS != ret) {
		return ret;
	}

	printf("AP mode, end\r\n");

	return ret;
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

	/* Initialize Wi-Fi parameters structure. */
	memset((uint8_t *)&param, 0, sizeof(tstrWifiInitParam));

	/* Initialize Wi-Fi driver with data and status callbacks. */
	ret = m2m_wifi_init(&param);
	if (M2M_SUCCESS != ret) {
		printf("main: m2m_wifi_init call error!(%d)\r\n", ret);
		while (1) {
		}
	}

	/**
	 * Station mode.
	 * Device started as station mode basically.
	 */
	if (1) {
	}

	/**
	 * AP mode.
	 * Turn On and off AP mode.
	 */
	ret = enable_disable_ap_mode();
	if (M2M_SUCCESS != ret) {
		printf("main: enable_disable_ap_mode call error!\r\n");
		while (1) {
		}
	}

	nm_bsp_sleep(DELAY_FOR_MODE_CHANGE);

	return 0;
}
