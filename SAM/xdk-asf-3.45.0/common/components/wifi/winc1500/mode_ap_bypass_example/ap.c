/**
 *
 * \file
 *
 * \brief AP Task.
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

#include "asf.h"
#include "FreeRTOS.h"
#include "osprintf.h"
#include "main.h"
#include "ap.h"
#include "lwip/ip.h"
#include "lwip/api.h"
#include "lwip/tcpip.h"
#include "lwip/dns.h"
#include "net_init.h"
#include "m2m_wifi_ex.h"
#include "tinyservices.h"
#include <string.h>
#include <stdio.h>

/** Using broadcast address for simplicity. */
#define HTTP_PORT					(80)

/** Delay on close error. */
#define webSHORT_DELAY				(10)

/** IP address of host. */
uint32_t gu32HostIp = 0;

/** Wi-Fi status variable. */
static volatile bool gbConnectedWifi = false;

/** Get host IP status variable. */
static volatile bool gbHostIpByName = false;


/** Built up report to display on HTML page for connected STA. */
char report[512];

/** Number of STA connected. */
uint32_t sta_connected = 0;

tstrWifiInitParam wifiInitparam;
/**
 * \brief Callback to get the Wi-Fi status update.
 *
 * \param[in] u8MsgType Type of Wi-Fi notification.
 * \param[in] pvMsg A pointer to a buffer containing the notification parameters.
 *
 * \return None.
 */
static void wifi_cb(uint8 msg_type, void *msg)
{
	switch (msg_type) {
	case M2M_WIFI_RESP_CON_STATE_CHANGED:
	{
		tstrM2mWifiStateChanged *pstrWifiState = (tstrM2mWifiStateChanged *)msg;
		if (pstrWifiState->u8CurrState == M2M_WIFI_CONNECTED) {
			printf("Station Connected\r\n");
		} else if (pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED) {
			printf("Station disconnected\r\n");
		}

		break;
	}

	case M2M_WIFI_REQ_DHCP_CONF:
	{
		uint8_t *pu8IPAddress = (uint8_t *)msg;
		printf("Station connected\r\n");
		printf("Station IP is %u.%u.%u.%u\r\n",
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
 * \brief STA task main function.
 */
void ap_task(void *argument)
{
	/* Initialize the network stack. */
	net_init();
	
	/* Initialize the WILC1000 driver. */
	memset(&wifiInitparam, 0, sizeof(wifiInitparam));
	wifiInitparam.pfAppWifiCb = wifi_cb;
	os_m2m_wifi_init(&wifiInitparam);


	/* Initialize AP mode parameters structure with SSID, channel and OPEN security type. */
	tstrM2MAPConfig strM2MAPConfig;
	memset(&strM2MAPConfig, 0x00, sizeof(tstrM2MAPConfig));
	strcpy((char *)&strM2MAPConfig.au8SSID, MAIN_WLAN_SSID);
	strM2MAPConfig.u8ListenChannel = MAIN_WLAN_CHANNEL;
	strM2MAPConfig.u8SecType = MAIN_WLAN_AUTH;

	/* The DHCP Server is at 192.168.5.1 in conf_tinyservices.h */
	/* The below config is ignored but is necessary to give as the validation fn will fail without it */
	strM2MAPConfig.au8DHCPServerIP[0] = 192;
	strM2MAPConfig.au8DHCPServerIP[1] = 168;
	strM2MAPConfig.au8DHCPServerIP[2] = 1;
	strM2MAPConfig.au8DHCPServerIP[3] = 1;

#ifdef USE_WEP
	strcpy((char *)&strM2MAPConfig.au8WepKey, MAIN_WLAN_WEP_KEY);
	strM2MAPConfig.u8KeySz = strlen(MAIN_WLAN_WEP_KEY);
	strM2MAPConfig.u8KeyIndx = MAIN_WLAN_WEP_KEY_INDEX;
#endif

	/* Bring up AP mode with parameters structure. */
	if (M2M_SUCCESS != os_m2m_wifi_enable_ap(&strM2MAPConfig)) {
		printf("main: m2m_wifi_enable_ap call error!\r\n");
		while (1) {
		}
	}

	printf("AP mode started. You can connect to %s.\r\n", (char *)MAIN_WLAN_SSID);

	while (1) {
		vTaskDelay(1000);
	}

}
