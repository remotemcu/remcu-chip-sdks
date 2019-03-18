/**
 *
 * \file
 *
 * \brief
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include <stdio.h>
#include <string.h>
#include "lwip/tcpip.h"
#include "lwip/dhcp.h"
#include "lwip/autoip.h"
#include "lwip/inet.h"
#include "netif/etharp.h"
#include <string.h>
#include "os/include/net_init.h"
#include "driver/include/m2m_wifi.h"
#include "driver/include/m2m_types.h"
#include "tinyservices.h"
#include "conf_tinyservices.h"

extern void app_network_up(uint8_t *ipv4_addr, uint8_t *ipv4_mask, uint8_t *ipv6_addr);
extern void app_network_down(void);
extern void socket_in_tcpip_task(void);
extern err_t wilc_netif_init(struct netif *netif);
extern struct netif wilc_netif_sta;
extern struct netif wilc_netif_c_mode;

static xTaskHandle net_tcpip_task;
static int net_started;
static xSemaphoreHandle net_start_sem;
#define NET_S_NET_UP			0x1
#define NET_S_DHCP_RUNNING		0x2
#define NET_S_AUTOIP_RUNNING	0x4
#define NET_S_DHCP_SVR_RUNNING	0x8
static uint32_t net_state_sta;
static uint32_t net_mode_sta;
static uint32_t net_state_c;
static uint32_t net_mode_c;

int random_number(void)
{
	return rand();
}

extern tpfAppWifiCb gpfAppWifiCb;
static void status_callback(struct netif *netif)
{
	if (netif_is_up(netif)) {
		tstrM2MIPConfig2 strIpConfig;
		strIpConfig.u8StaticIP = (uint8_t *)&netif->ip_addr;
		strIpConfig.u8SubnetMask = (uint8_t *)&netif->netmask;
#if LWIP_IPV6
		strIpConfig.u8StaticIPv6 = (uint8_t *)netif->ip6_addr;
#endif
		if (gpfAppWifiCb && (netif == &wilc_netif_sta)) {
			gpfAppWifiCb(NET_IF_REQ_DHCP_CONF, &strIpConfig);		
		}
	}
}

void net_add_wilc_netif(void)
{
	struct ip_addr ip_addr;
	ip_addr.addr = 0;

	/* Add WILC1000 STA interface. */
	netif_add(&wilc_netif_sta, &ip_addr, &ip_addr, &ip_addr, 0, wilc_netif_init, tcpip_input);
	netif_set_default(&wilc_netif_sta);
#if LWIP_IPV6
	netif_create_ip6_linklocal_address(&wilc_netif_sta, 1); /* Needed to sent data on the internet, not matching local netmask. */
#endif
#if LWIP_NETIF_STATUS_CALLBACK
	netif_set_status_callback(&wilc_netif_sta, status_callback);
#endif
	
	/* Add WILC1000 AP/WD interface. */
	struct ip_addr mask = SN_MASK_IP;
	struct ip_addr gateway = GW_ADDR_IP;
	ip_addr = AP_ADDR_IP;
	netif_add(&wilc_netif_c_mode, &ip_addr, &mask, &gateway, 0, wilc_netif_init, tcpip_input);
	net_set_mode(NET_IF_C, NET_MODE_AP | NET_MODE_USE_DHCP_SVR);	
}

void net_remove_wilc_netif(void)
{
	netif_remove(&wilc_netif_sta);
	netif_remove(&wilc_netif_c_mode);
}

int net_in_tcpip_task(void)
{
	return (net_tcpip_task == xTaskGetCurrentTaskHandle());	
}

static void tcpip_init_done(void *arg)
{
	net_tcpip_task = xTaskGetCurrentTaskHandle();
	xSemaphoreGive(net_start_sem);
}

static void net_interface_up_imp(uint32_t net_if)
{
	if (net_if == NET_IF_STA) {
		/* Bring up interface in lwIP. */
		if(use_static_IP == 1) {		
			netif_set_up(&wilc_netif_sta);
		}	
		netif_set_link_up(&wilc_netif_sta);
		net_state_sta |= NET_S_NET_UP;
		
		/* Interface 1 (STA). */
		if (net_mode_sta & NET_MODE_USE_DHCP) {
#if LWIP_DHCP
			dhcp_start(&wilc_netif_sta);
			net_state_sta |= NET_S_DHCP_RUNNING;
#endif
		} else if (net_mode_sta & NET_MODE_USE_LINK_LOCAL) {
#if LWIP_AUTOIP
			autoip_start(&wilc_netif_sta);
			net_state_sta |= NET_S_AUTOIP_RUNNING;
#endif
		}
	}
	else {
		/* Bring up interface in lwIP. */
		netif_set_link_up(&wilc_netif_c_mode);
		net_state_c |= NET_S_NET_UP;
		
		/* Interface 2 (Concurrent mode). */
		if (net_mode_c & NET_MODE_USE_DHCP_SVR) {
			netif_set_up(&wilc_netif_c_mode);
#if LWIP_UDP && LWIP_DHCP
			lwip_tiny_dhcpserver_start();
#endif
			net_state_c |= NET_S_DHCP_SVR_RUNNING;
		}
	}
}

static void net_interface_down_imp(uint32_t net_if)
{
	if (net_if == NET_IF_STA) {
		netif_set_link_down(&wilc_netif_sta);
		net_state_sta &= ~NET_S_NET_UP;
		net_mode_sta &= ~(NET_MODE_USE_DHCP | NET_MODE_AP);
		if (net_state_sta & NET_S_DHCP_RUNNING) {
#if LWIP_DHCP
			dhcp_stop(&wilc_netif_sta);
			net_state_sta &= ~NET_S_DHCP_RUNNING;
#endif
		}
		if (net_state_sta & NET_S_AUTOIP_RUNNING) {
#if LWIP_AUTOIP
			autoip_stop(&wilc_netif_sta);
			net_state_sta &= ~NET_S_AUTOIP_RUNNING;
#endif
		}
		netif_set_down(&wilc_netif_sta);
	}
	else {
		netif_set_link_down(&wilc_netif_c_mode);
		net_state_c &= ~NET_S_NET_UP;
		net_mode_c &= ~NET_MODE_AP;
		if (net_state_c & NET_S_DHCP_SVR_RUNNING) {
#if LWIP_UDP && LWIP_DHCP
			lwip_tiny_dhcpserver_stop();
#endif
			net_state_c &= ~NET_S_DHCP_SVR_RUNNING;
		}
		netif_set_down(&wilc_netif_c_mode);
	}
}

void net_interface_up(uint32_t net_if)
{
	net_interface_up_imp(net_if);
}

void net_interface_down(uint32_t net_if)
{
	net_interface_down_imp(net_if);
}

void net_set_mode(uint32_t net_if, uint32_t mode)
{
	if (net_if == NET_IF_STA) {
		net_mode_sta = mode;
		
		if ((mode & NET_MODE_USE_DHCP)) {
			if ((net_state_sta & (NET_S_DHCP_RUNNING | NET_S_NET_UP)) == NET_S_NET_UP) {
#if LWIP_DHCP
				dhcp_start(&wilc_netif_sta);
				net_state_sta |= NET_S_DHCP_RUNNING;
#endif
			}
			} else {
			if (net_state_sta & NET_S_DHCP_RUNNING) {
#if LWIP_DHCP
				dhcp_stop(&wilc_netif_sta);
				net_state_sta &= ~NET_S_DHCP_RUNNING;
#endif
			}
		}
	}
	else {
		net_mode_c = mode;
	}
}


int8_t net_set_interface_address(uint32_t net_if,ip_addr_t *ip_addr,ip_addr_t *ip_net_mask,ip_addr_t *ip_gw_addr)
{
	int8_t retVal = 0;
	
	if (net_if == NET_IF_STA) {
		netif_set_addr(&wilc_netif_sta,ip_addr,ip_net_mask,ip_gw_addr);
	}else if (net_if == NET_IF_C){
		netif_set_addr(&wilc_netif_c_mode,ip_addr,ip_net_mask,ip_gw_addr);
	}else{
		retVal = -1;
	}
	return retVal;
}


void net_init(void)
{
	if (!net_started) {
		net_started = 1;
		vSemaphoreCreateBinary(net_start_sem);
		xSemaphoreTake(net_start_sem, portMAX_DELAY);
		tcpip_init(tcpip_init_done, 0);
		xSemaphoreTake(net_start_sem, portMAX_DELAY);
		vSemaphoreDelete(net_start_sem);
	}
}
