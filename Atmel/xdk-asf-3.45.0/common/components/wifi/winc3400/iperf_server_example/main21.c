/**
 *
 * \file
 *
 * \brief WINC3400 Iperf Server Example.
 *
 * Copyright (c) 2017-2018 Microchip Technology Inc. and its subsidiaries.
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
 * This example demonstrates the use of the WINC3400 with the SAMD21 Xplained Pro
 * board to run Iperf server.<br>
 * It uses the following hardware:
 * - the SAMD21 Xplained Pro.
 * - the WINC3400 on EXT1.
 *
 * \section files Main Files
 * - main.c : Initialize the WINC3400 and run Iperf server.
 *
 * \section usage Usage
 * -# Configure below code in the main.h for AP information to be connected.
 * \code
 *    #define MAIN_WLAN_SSID                    "DEMO_AP"
 *    #define MAIN_WLAN_AUTH                    M2M_WIFI_SEC_WPA_PSK
 *    #define MAIN_WLAN_PSK                     "12345678"
 *    #define MAIN_WIFI_M2M_PRODUCT_NAME        "NMCTemp"
 *    #define MAIN_WIFI_M2M_SERVER_IP           0xFFFFFFFF // "255.255.255.255"
 *    #define MAIN_WIFI_M2M_SERVER_PORT         (6666)
 *    #define MAIN_WIFI_M2M_REPORT_INTERVAL     (1000)
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
 * -- WINC3400 IPERF server example --
 * -- SAMD21_XPLAINED_PRO --
 * -- Compiled: xxx xx xxxx xx:xx:xx --
 *  
 *  
 *  (APP)(INFO)Chip ID 1503a0
 *  (APP)(INFO)DriverVerInfo: xxxxxxxxx
 *  (APP)(INFO)Firmware ver   : x.x.x
 *  iperf_wifi_cb: M2M_WIFI_RESP_CON_STATE_CHANGED: CONNECTED
 *  iperf_wifi_cb: M2M_WIFI_REQ_DHCP_CONF: IP is xxx.xxx.xxx.xxx
 *  (APP)(INFO)Socket 0 session ID = 1
 *  (APP)(INFO)Socket 7 session ID = 2
 *  (APP)(INFO)Socket 8 session ID = 3
 *  ------------------------------------------------------------
 *  Server listening on TCP/UDP port 5001
 *  TCP window size: ??? KByte
 *  ------------------------------------------------------------ 
 * \endcode
 * -# Start the application on client using command.
 * -# iperf -c <Server_IP_Address> -t <time_peroid> -i >time_interval> -r 
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
#include <string.h>
#include "common/include/nm_common.h"
#include "driver/include/m2m_wifi.h"
#include "socket/include/socket.h"
#include "iperf.h"

#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- WINC3400 Iperf server example --"STRING_EOL \
	"-- "BOARD_NAME " --"STRING_EOL	\
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

/** Message format definitions. */
typedef struct s_msg_wifi_product {
	uint8_t name[1400];
} t_msg_wifi_product;

/** UART module for debug. */
static struct usart_module cdc_uart_module;

/** SysTick counter to avoid busy wait delay. */
volatile uint32_t ms_ticks = 0;

void SysTick_Handler(void)
{
	ms_ticks++;
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
 * \brief Main application function.
 *
 * Initialize system, UART console, network then test function of TCP client.
 *
 * \return program return value.
 */
int main(void)
{

	/* Initialize the board. */
	system_init();

	/* Initialize the UART console. */
	configure_console();
	
	/* Enable SysTick interrupt for non busy wait delay. */
	if (SysTick_Config(120000000 / 1000)) {
		puts("main: SysTick configuration error!");
		while (1);
	}

	/* Output example information. */
	puts(STRING_EOL);
	puts(STRING_HEADER);
	puts(STRING_EOL);

	/* Start the demo task. */
	iperf_start();

	return 0;
}
