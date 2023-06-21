/**
 * \file
 *
 * \brief Ethernet management for the standalone lwIP example.
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

#include <string.h>
#include "board.h"
#include "ethernet_sam.h"
#include "gmac.h"
#include "ethernet_phy.h"
#include "timer_mgt_sam.h"
#include "sysclk.h"
/* lwIP includes */
#include "lwip/sys.h"
#include "lwip/api.h"
#include "lwip/tcp.h"
#include "lwip/tcpip.h"
#include "lwip/memp.h"
#include "lwip/dhcp.h"
#include "lwip/dns.h"
#include "lwip/stats.h"
#include "lwip/init.h"
#include "lwip/ip_frag.h"
#if ((LWIP_VERSION) == ((1U << 24) | (3U << 16) | (2U << 8) | (LWIP_VERSION_RC)))
#include "netif/loopif.h"
#else
#include "lwip/inet.h"
#include "lwip/tcp_impl.h"
#endif
#include "netif/etharp.h"
#include "netif/sam4e_gmac.h"

#if defined(HTTP_RAW_USED)
#include "httpd.h"
#endif

//#define TRACE_DEBUG(...)     printf(__VA_ARGS__)
#define TRACE_DEBUG(...)

/** Global variable containing MAC Config (hw addr, IP, GW, ...) */
struct netif gs_net_if;
extern uint32_t g_ip_mode;
extern int8_t g_c_ipconfig[];

/** Timer for calling lwIP tmr functions without system */
typedef struct timers_info {
	uint32_t timer;
	uint32_t timer_interval;
	void (*timer_func)(void);
} timers_info_t;

/** LwIP tmr functions list */
static timers_info_t gs_timers_table[] = {
	{0, TCP_TMR_INTERVAL, tcp_tmr},
	{0, IP_TMR_INTERVAL, ip_reass_tmr},
	/* LWIP_ARP */
	{0, ARP_TMR_INTERVAL, etharp_tmr},
	/* LWIP_DHCP */
#if LWIP_DHCP
	{0, DHCP_COARSE_TIMER_MSECS, dhcp_coarse_tmr},
	{0, DHCP_FINE_TIMER_MSECS, dhcp_fine_tmr},
#endif
};

/**
 * \brief Process timing functions.
 */
static void timers_update(void)
{
	static uint32_t ul_last_time;
	uint32_t ul_cur_time, ul_time_diff, ul_idx_timer;
	timers_info_t *p_tmr_inf;

	ul_cur_time = sys_get_ms();
	if (ul_cur_time >= ul_last_time) {
		ul_time_diff = ul_cur_time - ul_last_time;
	} else {
		ul_time_diff = 0xFFFFFFFF - ul_last_time + ul_cur_time;
	}

	if (ul_time_diff) {
		ul_last_time = ul_cur_time;
		for (ul_idx_timer = 0;
			ul_idx_timer < (sizeof(gs_timers_table) / sizeof(timers_info_t));
			ul_idx_timer++) {
			p_tmr_inf = &gs_timers_table[ul_idx_timer];
			p_tmr_inf->timer += ul_time_diff;
			if (p_tmr_inf->timer > p_tmr_inf->timer_interval) {
				if (p_tmr_inf->timer_func) {
					p_tmr_inf->timer_func();
				}

				p_tmr_inf->timer -= p_tmr_inf->timer_interval;
			}
		}
	}
}

/**
 * \brief Set ethernet config.
 */
static void ethernet_configure_interface(void)
{
	struct ip_addr x_ip_addr, x_net_mask, x_gateway;

	if (g_ip_mode == 2) {
		x_ip_addr.addr = 0;
		x_net_mask.addr = 0;
	} else {
		/** Default ip addr */
		IP4_ADDR(&x_ip_addr, ETHERNET_CONF_IPADDR0, ETHERNET_CONF_IPADDR1,
				ETHERNET_CONF_IPADDR2, ETHERNET_CONF_IPADDR3);
	
		/** Default subnet mask */
		IP4_ADDR(&x_net_mask, ETHERNET_CONF_NET_MASK0, ETHERNET_CONF_NET_MASK1,
				ETHERNET_CONF_NET_MASK2, ETHERNET_CONF_NET_MASK3);
	
		/** Default gateway addr */
		IP4_ADDR(&x_gateway, ETHERNET_CONF_GATEWAY_ADDR0,
				ETHERNET_CONF_GATEWAY_ADDR1,
				ETHERNET_CONF_GATEWAY_ADDR2,
				ETHERNET_CONF_GATEWAY_ADDR3);
	}

	/** Add data to netif */
	if( NULL == netif_add(&gs_net_if, &x_ip_addr, &x_net_mask, &x_gateway, NULL,
			ethernetif_init, ethernet_input) ) {
		TRACE_DEBUG("ERROR");
		while(1);
	}
	/** Make it the default interface */
	netif_set_default(&gs_net_if);

	/** Setup callback function for netif status change */
	netif_set_status_callback(&gs_net_if, status_callback);

	/** Bring it up */
	if (g_ip_mode == 2) {
		/** DHCP mode*/
		if(ERR_OK != dhcp_start(&gs_net_if)) {
			TRACE_DEBUG("ERROR");
			while(1);
		}
	} else {
		/** Static mode*/
		netif_set_up(&gs_net_if);
	}
}

/**
 * \brief Create ethernet task, for ethernet management.
 */
void init_ethernet(void)
{
	/** Initialize lwIP */
	lwip_init();

	/** Set hw and IP parameters, initialize MAC too */
	ethernet_configure_interface();

#if defined(HTTP_RAW_USED)
	/** Bring up the web server */
	http_init();
#endif
}

/**
 *  \brief Status callback used to print address given by DHCP.
 *
 * \param netif Instance to network interface.
 */
void status_callback(struct netif *netif)
{
	if (netif_is_up(netif)) {
		TRACE_DEBUG("Network up");
		TRACE_DEBUG("IP=");
		strcat((char*)g_c_ipconfig,
				inet_ntoa(*(struct in_addr *)&(netif->ip_addr)));
		TRACE_DEBUG((char const*)g_c_ipconfig);
		g_ip_mode = 3;
	} else {
		TRACE_DEBUG("Network down");
	}
}

/**
 *  \brief Periodically retrigger timeout process.
 *  After managing the lwIP timers. trigger corresponding ethernet process.
 */
void ethernet_task(void)
{
	/* Run polling tasks */
	ethernetif_input(&gs_net_if);

	/* Run periodic tasks */
	timers_update();
}
