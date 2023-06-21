/**
 *
 * \file
 *
 * \brief STA Task.
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

#include "asf.h"
#include "FreeRTOS.h"
#include "osprintf.h"
#include "sta.h"
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

/** Server host name. */
static char server_host_name[] = STA_WEATHER_SERVER_NAME;


/** Built up report to display on HTML page for connected STA. */
char report[512];

/** Number of STA connected. */
uint32_t sta_connected = 0;

/**
 * \brief Callback function of IP address.
 *
 * \param[in] hostName Domain name.
 * \param[in] hostIp Server IP.
 *
 * \return None.
 */
static void resolve_cb(const char *hostName, ip_addr_t *ipaddr, void *callback_arg)
{
	gu32HostIp = ipaddr->addr;
	gbHostIpByName = true;
}

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
		case M2M_WIFI_RESP_CON_STATE_CHANGED : {
			tstrM2mWifiStateChanged *ctx = (tstrM2mWifiStateChanged*)msg;
			if (ctx->u8CurrState == M2M_WIFI_CONNECTED) {
				osprintf("wifi_cb: M2M_WIFI_CONNECTED\n");
				net_interface_up(NET_IF_STA);
				m2m_wifi_request_dhcp_client_ex();
			}
			if(ctx->u8CurrState == M2M_WIFI_DISCONNECTED) {
				gbConnectedWifi = false;
				osprintf("wifi_cb: M2M_WIFI_DISCONNECTED\n");
				osprintf("wifi_cb: reconnecting...\n");
				net_interface_down(NET_IF_STA);
				os_m2m_wifi_connect((char *)STA_WLAN_SSID, sizeof(STA_WLAN_SSID),
						STA_WLAN_AUTH, (char *)STA_WLAN_PSK, M2M_WIFI_CH_ALL);
			}
		}
		break;

		case M2M_WIFI_REQ_DHCP_CONF : {
			tstrM2MIPConfig2 *strIpConfig = msg;
			static ip_addr_t resolve_addr;
			uint16_t *a = (void *)strIpConfig->u8StaticIPv6;

			osprintf("wifi_cb: STA M2M_WIFI_REQ_DHCP_CONF\n");
			osprintf("wifi_cb: STA IPv4 addr: %d.%d.%d.%d\n", strIpConfig->u8StaticIP[0], strIpConfig->u8StaticIP[1],
					strIpConfig->u8StaticIP[2], strIpConfig->u8StaticIP[3]);
			osprintf("wifi_cb: STA IPv6 addr: %04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x\n",
				htons(a[0]), htons(a[1]), htons(a[2]), htons(a[3]),
				htons(a[4]), htons(a[5]), htons(a[6]), htons(a[7]));
			gbConnectedWifi = true;

			/* Obtain the IP Address by network name. */
			dns_gethostbyname(server_host_name, &resolve_addr, resolve_cb, 0);
		}
		break;

		default:
		break;
	}
}


/**
 * \brief STA task main function.
 */
void sta_task(void *argument)
{
	/* Initialize the network stack. */
	net_init();
	
	/* Initialize the WILC1000 driver. */
	tstrWifiInitParam param;
	memset(&param, 0, sizeof(param));
	param.pfAppWifiCb = wifi_cb;
	os_m2m_wifi_init(&param);

	/* Enable AP mode. */
	tstrM2MAPConfig cfg;
	memset(&cfg, 0, sizeof(cfg));
	strcpy((char *)cfg.au8SSID, "WINC1500");
	cfg.u8ListenChannel = M2M_WIFI_CH_11;
	cfg.u8SecType = M2M_WIFI_SEC_OPEN;

	/* Connect to station. */

	os_m2m_wifi_connect((char *)STA_WLAN_SSID, sizeof(STA_WLAN_SSID),
			STA_WLAN_AUTH, (char *)STA_WLAN_PSK, M2M_WIFI_CH_ALL);
	while (1) {
		vTaskDelay(3000);
	}
}
