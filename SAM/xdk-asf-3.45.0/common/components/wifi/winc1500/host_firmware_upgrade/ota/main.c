/**
 *
 * \file
 *
 * \brief Host MCU OTA firmware upgrade example.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
/** \mainpage
 * \section intro Introduction
 * This example demonstrates the use of the WINC1500 with the SAM Xplained Pro
 * board to perform an Host MCU OTA Firmware upgrade.
 * It uses the following hardware:
 * - the SAM Xplained Pro.
 * - the WINC1500 on EXT1.
 *
 * \section files Main Files
 * - main.c : Initialize the WINC1500.
 *
 * \section usage Usage
 * -# You need to setup an HTTP server accessible via your Wi-Fi network. This HTTP
 * server must have the "host_mcu_ota.bin" OTA firmware accessible at this location:
 * http://SERVER_IP_ADDRESS/host_mcu_ota.bin
 *
 * Note: 
 * - The start address of the host OTA firmware file to be APP_START. 
 * - The OTA firmware should not contain the bootloader code.
 * - the server IP address must be set via the MAIN_HOST_OTA_URL macro from main.h file.
 *
 * -# Configure below code in the config main.h for AP to connect to.
 * \code
 *     #define MAIN_WLAN_SSID        "DEMO_AP"
 *     #define MAIN_WLAN_AUTH        M2M_WIFI_SEC_WPA_PSK
 *     #define MAIN_WLAN_PSK         "12345678"
 *     #define MAIN_OTA_URL          "https://192.168.43.34:4443/host_mcu_ota.bin"
 * \endcode
 *
 * -# Build the program
 * The bootloader code and application code are compiled separately. The factory code should
 * contain both bootloader code and application code. So, it is required to combine 
 * both the images (.hex) before programing on the board. Open Bootloader example
 * (HOST_FIRMWARE_UPGRADE_BOOTLOADER_EXAMPLE) from ASF. Compile and generate .hex file.
 * Combine application .hex (this project) and bootloader .hex using srec_cat 
 * (refer: https://sourceforge.net/projects/srecord/files/srecord/) and download the 
 * combined image into the board.
 * -# On the computer, open and configure a terminal application as the follows.
 *
 * \code
 *    Baud Rate : 115200
 *    Data : 8bit
 *    Parity bit : none
 *    Stop bit : 1bit
 *    Flow control : none
 * \endcode
 * -# Start the application.
 *
 * \endcode
 *
 * \section compinfo Compilation Information
 * This software was written for the GNU GCC compiler using Atmel Studio 6.2
 * Other compilers may or may not work.
 */

#include "asf.h"
#include "main.h"
#include <string.h>
#include "driver/include/m2m_ota.h"
#include "driver/include/m2m_wifi.h"
#include "driver/source/nmasic.h"
#include "driver/include/m2m_types.h"
#include "memory_flash.h"
#include "bootloader.h"

#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- WINC1500 NEW Host Firmware upgrade example --"STRING_EOL \
	"-- "BOARD_NAME " --"STRING_EOL	\
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL
#define TRIGGER_BOOTLAOAD (1)

/** Boot informations */
typedef struct regions_info {
	/** Firmware length in regions */
	uint32_t length;
	/** Software trigger to force action */
	uint32_t trigger;
	uint8_t padding[IFLASH_PAGE_SIZE-8];
} regions_info_t;

bool wifi_connected = false, host_ota_initiated = false;

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
 * \brief Info region data write to indicate new image availability.
 */
static void region_info_write(uint32_t u32Size)
{
	void *info_addr;
	regions_info_t info;

	info.length = u32Size;
	info.trigger = TRIGGER_BOOTLAOAD;

	memory_init();
	info_addr = (void *)INFO_ADDR_START;

	printf("Write info area ...\r\n");
	memory_unlock(info_addr, (void *)((uint32_t)info_addr + INFO_SIZE - 1));

	memory_erase(info_addr, INFO_SIZE);

	memory_write(info_addr, &info);

	memory_lock(info_addr, (void *)((uint32_t)info_addr + INFO_SIZE - 1));
	printf("Write info area done\r\n");
}

/**
 * \brief Initiate switch to new image.
 */
static void switch_image(uint32_t u32Size)
{
	/* Write info region with size of data and boot trigger */
	region_info_write(u32Size);

	printf("Reset the device...\r\n\n");
	/* Perform the software reset. */
	rstc_start_software_reset(RSTC);
}

/**
 * \brief Callback to get the Host update event.
 *
 * \param[in] u8Status type of Host OTA update status detail. Possible types are:
 * - [OTA_STATUS_SUCSESS](@ref OTA_STATUS_SUCSESS)
 * - [OTA_STATUS_FAIL](@ref OTA_STATUS_FAIL)
 * - [OTA_STATUS_INVAILD_ARG](@ref OTA_STATUS_INVAILD_ARG)
 * - [OTA_STATUS_INVAILD_RB_IMAGE](@ref OTA_STATUS_INVAILD_RB_IMAGE)
 * - [OTA_STATUS_INVAILD_FLASH_SIZE](@ref OTA_STATUS_INVAILD_FLASH_SIZE)
 * - [OTA_STATUS_AlREADY_ENABLED](@ref OTA_STATUS_AlREADY_ENABLED)
 * - [OTA_STATUS_UPDATE_INPROGRESS](@ref OTA_STATUS_UPDATE_INPROGRESS)
 * \param[in] u8Handler To find the file to read
 * \param[in] u32Size of downloaded file
 */

static void HostFileGetCallback(uint8 u8Status, uint8 u8Handler, uint32 u32Size)
{
	host_ota_initiated = false;

	if(OTA_STATUS_SUCCESS == u8Status)
	{
		/* File Get Successful */
		printf("HostFileGetCallback Success: u8Handler=%d\r\n", u8Handler);

		switch_image(u32Size);
	}
	else
	{
		/* File Get Failed */
		printf("HostFileGetCallback FAIL u8Status %d\r\n", u8Status);
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
			m2m_wifi_request_dhcp_client();
		} else if (pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED) {
			printf("Wi-Fi disconnected\r\n");

			/* Connect to defined AP. */
			m2m_wifi_connect((char *)MAIN_WLAN_SSID, sizeof(MAIN_WLAN_SSID), MAIN_WLAN_AUTH, (void *)MAIN_WLAN_PSK, M2M_WIFI_CH_ALL);
			wifi_connected = false;
		}

		break;
	}

	case M2M_WIFI_REQ_DHCP_CONF:
	{
		uint8_t *pu8IPAddress = (uint8_t *)pvMsg;
		printf("Wi-Fi connected\r\n");
		printf("Wi-Fi IP is %u.%u.%u.%u\r\n",
				pu8IPAddress[0], pu8IPAddress[1], pu8IPAddress[2], pu8IPAddress[3]);
		wifi_connected = true;
		break;
	}

	default:
	{
		break;
	}
	}
}

/**
 * \brief Callback to get the OTA update event.
 *
 * \param[in] u8OtaUpdateStatusType type of OTA update status notification. Possible types are:
 * - [DL_STATUS](@ref DL_STATUS)
 * - [SW_STATUS](@ref SW_STATUS)
 * - [RB_STATUS](@ref RB_STATUS)
 * \param[in] u8OtaUpdateStatus type of OTA update status detail. Possible types are:
 * - [OTA_STATUS_SUCSESS](@ref OTA_STATUS_SUCSESS)
 * - [OTA_STATUS_FAIL](@ref OTA_STATUS_FAIL)
 * - [OTA_STATUS_INVAILD_ARG](@ref OTA_STATUS_INVAILD_ARG)
 * - [OTA_STATUS_INVAILD_RB_IMAGE](@ref OTA_STATUS_INVAILD_RB_IMAGE)
 * - [OTA_STATUS_INVAILD_FLASH_SIZE](@ref OTA_STATUS_INVAILD_FLASH_SIZE)
 * - [OTA_STATUS_AlREADY_ENABLED](@ref OTA_STATUS_AlREADY_ENABLED)
 * - [OTA_STATUS_UPDATE_INPROGRESS](@ref OTA_STATUS_UPDATE_INPROGRESS)
 */
static void OtaUpdateCb(uint8_t u8OtaUpdateStatusType, uint8_t u8OtaUpdateStatus)
{
	host_ota_initiated = false;
	printf("OtaUpdateCb = %d\r\n",u8OtaUpdateStatus);
}

/**
 * \brief OTA notify callback.
 *
 * OTA notify callback typedef.
 */
static void OtaNotifCb(tstrOtaUpdateInfo *pv)
{
	printf("OtaNotifCb \r\n");
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
	param.pfAppWifiCb = wifi_cb;
	ret = m2m_wifi_init(&param);
	if (M2M_SUCCESS != ret) {
		printf("main: m2m_wifi_init call error!(%d)\r\n", ret);
		while (1) {
		}
	}

	/* Connect to defined AP. */
	m2m_wifi_connect((char *)MAIN_WLAN_SSID, sizeof(MAIN_WLAN_SSID), MAIN_WLAN_AUTH, (void *)MAIN_WLAN_PSK, M2M_WIFI_CH_ALL);

	/* Init ota function. */
	m2m_ota_init(OtaUpdateCb, OtaNotifCb);

	while (1) {
		/* Handle pending events from network controller. */
		while (m2m_wifi_handle_events(NULL) != M2M_SUCCESS) {
		}

		/* On button press initiates the host image download */
		if(!(ioport_get_pin_level(BUTTON_0_PIN)))
		{
			if(wifi_connected == true && host_ota_initiated == false )
			{
				/* Start Host OTA Firmware download. */
				m2m_ota_host_file_get((uint8_t *)MAIN_HOST_OTA_URL,HostFileGetCallback);
				host_ota_initiated = true;
			}
		}
	}

	return 0;
}
