/**
 *
 * \file
 *
 * \brief WINC1500 Weather Client in ByPass Mode Example.
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
 * This example demonstrates the use of the WINC1500 with the SAM Xplained Pro
 * board to behave as a station.<br>
 * It uses the following hardware:
 * - the SAM Xplained Pro.
 * - the WINC1500 on EXT1.
 *
 * \section files Main Files
 * - main.c : Initialize the WINC1500 and connect AP as a station mode.
 *
 * \section usage Usage
 * -# Configure below code in the config main.h for AP information to be connected.
 * \code
 *    #define STA_WLAN_SSID         "DEMO_AP"
 *    #define STA_WLAN_AUTH         M2M_WIFI_SEC_WPA_PSK
 *    #define STA_WLAN_PSK          "12345678"
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
 *    -- WINC1500 Weather Client in ByPass mode example --
 *    -- SAMG55_XPLAINED_PRO --
 *    -- Compiled: xxx xx xxxx xx:xx:xx --
 *
 *    (APP)(INFO)Chip ID xxxxxx
 *    (APP)(INFO)DriverVerInfo: 0xaaaaaaaa
 *    (APP)(INFO)Firmware ver   : xx.x.x xxxxxx xxxxx
 *    (APP)(INFO)Firmware Build xxx xx xxxx xx:xx:xx
 *    (APP)(INFO)Firmware Min driver ver : xx.x.x
 *    (APP)(INFO)Driver ver: xx.x.x
 *    (APP)(INFO)Driver built at xxx xx xxxx xx:xx:xx
 *    wifi_cb: M2M_WIFI_CONNECTED
 *    Wi-Fi IP is x.x.x.x
 *    wifi_cb: STA M2M_WIFI_REQ_DHCP_CONF
 *    wifi_cb: STA IPv4 addr: x.x.x.x
 *    wifi_cb: STA IPv6 addr: xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx
 *    Retrieving weather for yyyyy 
 *    report received
 *    City: yyyyy
 *    Temperature: xxx
 *    Conditions: xxxxxxx
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
#include "osprintf.h"
#include "sta.h"

#define TASK_STA_STACK_SIZE		(4096 / sizeof(portSTACK_TYPE))
#define TASK_STA_PRIORITY			(tskIDLE_PRIORITY + 1)
#define TASK_AP_STACK_SIZE		(1024 / sizeof(portSTACK_TYPE))
#define TASK_AP_PRIORITY			(tskIDLE_PRIORITY + 1)

#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- WINC1500 Weather Client in ByPass Mode example --"STRING_EOL \
	"-- "BOARD_NAME " --"STRING_EOL	\
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

void fatal(int code, const char *msg);
void fatal(int code, const char *msg)
{
	for (;;) {
	}
}

#if configUSE_MALLOC_FAILED_HOOK
void vApplicationMallocFailedHook(void);
void vApplicationMallocFailedHook(void)
{
	for (;;) {
	}
}
#endif

#if configCHECK_FOR_STACK_OVERFLOW
void vApplicationStackOverflowHook(xTaskHandle pxTask, signed char *pcTaskName);
void vApplicationStackOverflowHook(xTaskHandle pxTask, signed char *pcTaskName)
{
	for (;;) {
	}
}
#endif

static uint32_t fault_addr;
void hard_fault(uint32_t *args, uint32_t lr);
void hard_fault(uint32_t *args, uint32_t lr)
{
	fault_addr = args[6];
	for (;;) {
	}
}

/**
 * \brief Configure UART console.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate =		115200,
		.charlength =	US_MR_CHRL_8_BIT,
		.paritytype =	US_MR_PAR_NO,
		.stopbits =		US_MR_NBSTOP_1_BIT,
	};

	/* Configure UART console. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	osprintf_init(CONSOLE_UART, &uart_serial_options);	
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
	/* Initialize the board. */
	sysclk_init();
	board_init();

	/* Initialize the UART console. */
	configure_console();
	puts(STRING_HEADER);

	/* Create main task. */
	xTaskCreate(sta_task, (signed char *)"WiFiSTA", TASK_STA_STACK_SIZE, 0,
			TASK_STA_PRIORITY, 0);

	vTaskStartScheduler();

	while (1) {
	}

	return 0;
}
