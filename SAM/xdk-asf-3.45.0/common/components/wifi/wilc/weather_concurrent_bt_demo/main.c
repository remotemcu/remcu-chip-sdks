/**
 *
 * \file
 *
 * \brief Weather concurrent and BT demo.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

/** \mainpage
 * \section intro Introduction
 * This example demonstrates the use of the WILC with the SAM Xplained Pro
 * board using WiFi concurrent mode STA/AP.
 * STA mode is used to connect to a home router with internet connection to
 * retrieve weather information. 
 * AP mode is used to allow any WiFi capable devices to connect to the WILC
 * and then access an embedded webserver to read weather information as well as
 * host MCU status (up to 7 connected stations at the same time).<br>
 *
 * To access the HTTP server connect with your laptop to WiFi network "WILC", then
 * open a browser at http://192.168.5.1<br>
 *
 * It uses the following hardware:
 * - the SAM Xplained Pro.
 * - the WILC on EXT1 (WINC can be used as well in bypass mode).
 * - WILC SD board can also be used connected to the SD Card Connector, with
 *   IRQ line connected to Ex1[9]
 *
 * \section files Main Files
 * - main.c : Initialize the FreeRTOS scheduler.
 * - sta.c : Enable STA and AP mode for WILC. Retrieve weather information via STA mode.
 * - ap.c : Enable HTTP server via AP mode.
 *
 * \section usage Usage
 * -# Configure below defines in sta.h to specify AP to connect to.
 * \code
 *    #define STA_WLAN_SSID         "DEMO_AP"
 *    #define STA_WLAN_AUTH         M2M_WIFI_SEC_WPA_PSK
 *    #define STA_WLAN_PSK          "12345678"
 *    #define STA_WEP_KEY_INDEX		M2M_WIFI_WEP_KEY_INDEX_1
 *    #define STA_WEP_KEY			"1234567890"
 *    #define STA_WEP_AUTH_TYPE		WEP_ANY
 * \endcode
  * -# Configure below defines in sta.h to specify WILC AP mode to start with.
  * \code
  *    #define AP_WLAN_SSID         "WILC1000_AP"
  *    #define AP_WLAN_AUTH         M2M_WIFI_SEC_WEP
  *    #define AP_WLAN_PSK          "12345678"
  *    #define AP_WEP_KEY_INDEX		M2M_WIFI_WEP_KEY_INDEX_1
  *    #define AP_WEP_KEY			"1234567890"
  *    #define AP_WEP_AUTH_TYPE		WEP_ANY
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
 *    -- Weather concurrent an BT demo --
 *    -- SAMXXX_XPLAINED_PRO --
 *    -- Compiled: Oct 19 2015 14:39:47 --
 *    
 *    wifi_cb: M2M_WIFI_CONNECTED
 *    wifi_cb: STA M2M_WIFI_REQ_DHCP_CONF
 *    wifi_cb: STA IPv4 addr: xxx.xxx.xxx.xxx
 *    wifi_cb: STA IPv6 addr: xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx
 *    wifi_cb: AP M2M_WIFI_CONNECTED xx-xx-xx-xx-xx-xx
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
#include "osprintf.h"
#include "driver/include/m2m_wifi.h"
#include "sta.h"
#include "ap.h"

#define TASK_STA_STACK_SIZE		(4096 / sizeof(portSTACK_TYPE))
#define TASK_STA_PRIORITY			(tskIDLE_PRIORITY + 1)
#define TASK_AP_STACK_SIZE		(1024 / sizeof(portSTACK_TYPE))
#define TASK_AP_PRIORITY			(tskIDLE_PRIORITY + 1)

#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- Weather concurrent and BT demo --"STRING_EOL \
		"-- "BOARD_NAME " --"STRING_EOL	\
		"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

/** SysTick counter to avoid busy wait delay. */
uint32_t ms_ticks = 0;

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
	M2M_ERR("ERROR: STACK OVERFLOW");
	M2M_ERR(pcTaskName);
	for (;;) {
	}
}
#endif

static uint32_t fault_addr;
void hard_fault(uint32_t *args, uint32_t lr);
void hard_fault(uint32_t *args, uint32_t lr)
{
	fault_addr = args[6];
	osprintf("Hard fault at address 0x%X\r\n", fault_addr);
	for (;;) {
	}
}

void HardFault_Handler(void)
{
	__asm(
		"  mov r0, #4          \n"
		"  mov r1, lr          \n"
		"  tst r0, r1          \n"
		"  beq using_msp       \n"
		"  mrs r0, psp         \n"
		"  b call_c            \n"
		"using_msp:            \n"
		"  mrs r0, msp         \n"
		"call_c:               \n"
		"  ldr r2, =hard_fault \n"
		"  bx r2               \n"
	);
}

/**
 * \brief Configure UART console (RTOS API).
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_STDIO_BAUDRATE,
#ifdef CONF_STDIO_CHAR_LENGTH
		.charlength = CONF_STDIO_CHAR_LENGTH,
#endif
		.paritytype = CONF_STDIO_PARITY,
#ifdef CONF_STDIO_STOP_BITS
		.stopbits = CONF_STDIO_STOP_BITS
#endif
	};

	/* Configure UART console. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	osprintf_init(CONF_STDIO_USART_MODULE, &uart_serial_options);
}

/**
 * \brief Main program function.
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
			
	/* Create main task. */
	xTaskCreate(ap_task, (signed char *)"WiFiAP", TASK_AP_STACK_SIZE, 0,
			TASK_AP_PRIORITY, 0);

	vTaskStartScheduler();
	
	while (1) {
	}

	return 0;
}
