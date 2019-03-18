/**
 *
 * \file
 *
 * \brief WILC Network Interface Driver for lwIP.
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

#include <lwip/opt.h>
#include <lwip/def.h>
#include <lwip/mem.h>
#include <lwip/pbuf.h>
#include <lwip/sys.h>
#include <lwip/ethip6.h>
#include <lwip/stats.h>
#include <lwip/snmp.h>
#include <lwip/tcpip.h>
#include <netif/etharp.h>
#include <netif/include/wilc_netif.h>
#include <sysclk.h>
#include <string.h>
#include <semphr.h>
#include <os/include/m2m_wifi_ex.h>
#include <os/include/net_init.h>

void wilc_netif_tx_from_queue(hif_msg_t *msg);
void wilc_netif_rx_callback(uint8 msg_type, void * msg, void *ctrl_buf);
err_t wilc_netif_init(struct netif *netif);
void wilc_fill_callback_info(tstrEthInitParam *info);

/** Queue used by HIF task. */
extern xQueueHandle hif_queue;

/** Define those to better describe your network interface. */
#define IFNAME0 'e'
#define IFNAME1 'n'

/** Maximum transfer unit. */
#define NET_MTU  1500

/** Network link speed. */
#define NET_LINK_SPEED  100000000

#define WILC_TX_BUF_SIZE (PBUF_POOL_BUFSIZE - M2M_ETHERNET_HDR_OFFSET)
static uint8_t tx_buf[WILC_TX_BUF_SIZE] __attribute__ ((aligned (4)));
#define WILC_RX_BUF_SZ	(PBUF_POOL_BUFSIZE - M2M_ETHERNET_HDR_OFFSET)
static uint8_t rx_buf[WILC_RX_BUF_SZ] __attribute__ ((aligned (4)));
static struct pbuf *rx_first;
static struct pbuf *rx_last;

/** The netif for the WILC1000 in station mode. */
struct netif wilc_netif_sta;

/** The netif for the WILC1000 in concurrent (AP or WiFi Direct) mode. */
struct netif wilc_netif_c_mode;

/**
 * \brief Perform low level initialization of the netif driver.
 */
static void wilc_netif_low_level_init(struct netif *netif)
{
	static uint8_t mac0[6];
	static uint8_t mac1[6];

	/*STA - g_mac_1*/
	if(netif->num == 0)
	{
		m2m_wifi_get_mac_address(mac0, mac1);
		netif->hwaddr_len = sizeof(mac1);
		memcpy(netif->hwaddr, mac1, sizeof(mac1));
	}
	/*AP - g_mac*/
	else
	{
		netif->hwaddr_len = sizeof(mac0);
		memcpy(netif->hwaddr, mac0, sizeof(mac0));
	}

	netif->mtu = NET_MTU;
	netif->flags |= NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP
#if LWIP_IGMP
			| NETIF_FLAG_IGMP
#endif // LWIP_IGMP
	;
}

/**
 * \brief Send packet from lwIP to HIF task for processing.
 */
static err_t wilc_netif_tx(struct netif *netif, struct pbuf *p)
{
	struct pbuf *q = 0;
	hif_msg_t msg;
	uint8_t *bufptr = tx_buf;
	if (p->tot_len > WILC_TX_BUF_SIZE) {
		return ERR_BUF;
	}
	if (netif == &wilc_netif_sta)
		msg.id = MSG_TX_STA;
	else
		msg.id = MSG_TX_AP;


	pbuf_header(p, M2M_ETHERNET_HDR_OFFSET);


	if (p->tot_len == p->len) {
		msg.pbuf = (void *) p;
		msg.payload_size = p->len - ETH_PAD_SIZE - M2M_ETHERNET_HDR_OFFSET;
		msg.payload = p->payload;
	} else {
		for (q = p; q != NULL; q = q->next) {
			memcpy(bufptr, q->payload, q->len);
			bufptr += q->len;
		}
		msg.pbuf = NULL;
		msg.payload = tx_buf;
		msg.payload_size = (uint16_t)(bufptr - tx_buf - ETH_PAD_SIZE - M2M_ETHERNET_HDR_OFFSET);
	}

	if (msg.pbuf)
		pbuf_ref(p);
		
	xQueueSend(hif_queue, (void *)&msg, portMAX_DELAY); 

	LINK_STATS_INC(link.xmit);
	return ERR_OK;
}

/**
 * \brief Send pending packets to the WILC under HIF thread context.
 */
void wilc_netif_tx_from_queue(hif_msg_t *msg)
{
	struct pbuf *p = (struct pbuf *)msg->pbuf;
	uint32_t tries = 0;
	sint8 err;

	for (;;) {
		/* Try to send packet on corresponding interface. */
		if (msg->id == MSG_TX_STA) {
			err = m2m_wifi_send_ethernet_pkt((uint8*)(msg->payload), msg->payload_size, STATION_INTERFACE);
			} else {
			err = m2m_wifi_send_ethernet_pkt((uint8*)(msg->payload), msg->payload_size, AP_INTERFACE);
	    }
		if (M2M_SUCCESS == err) {
			break;
		} else {
			if (++tries == 100) {
				break;
			}
			vTaskDelay(1);
		}
	}

	/* Free packet after transmission. */
	if (p)
		pbuf_free(p);
}


/**
 * \brief Receive packets from the WILC under HIF thread context.
 */
void wilc_netif_rx_callback(uint8 msg_type, void * msg, void *ctrl_buf)
{
	struct pbuf *p;
	uint8_t *b;
	tstrM2MDataBufCtrl *ctrl = (tstrM2MDataBufCtrl *)ctrl_buf;
	uint16_t sz = ctrl->u16DataSize + ctrl->u8DataOffset;
	uint16_t rem = ctrl->u16RemainigDataSize;

	if (msg_type == M2M_WIFI_RESP_ETHERNET_RX_PACKET) {
		
		if (!rx_first) {
			rx_first = rx_last = pbuf_alloc(PBUF_RAW, WILC_RX_BUF_SZ, PBUF_POOL);
			if (rx_first == NULL) {
				LINK_STATS_INC(link.memerr);
				LINK_STATS_INC(link.drop);
				m2m_wifi_set_receive_buffer_ex(rx_buf, sizeof(rx_buf));
				return;
			}
			memcpy((uint8_t*) rx_first->payload, rx_buf, sz);
		}
		p = pbuf_alloc(PBUF_RAW, WILC_RX_BUF_SZ, PBUF_POOL);
		if (rx_first == rx_last) {
			rx_last->tot_len = sz + rem;
		}
		rx_last->len = sz;
		
		pbuf_header(rx_first, -(ctrl->u8DataOffset - ETH_PAD_SIZE));

		/* When packet is complete, send it to the right lwIP interface. */
		if (!rem) {
			err_t error;
			if (ctrl->u8IfcId == 1) {
				if (ERR_OK != (error = wilc_netif_sta.input(rx_first, &wilc_netif_sta))) {
					osprintf("STA error sending to stack %d.\r\n", error);
					pbuf_free(rx_first);
				}
			}
			else {
				if (ERR_OK != (error = wilc_netif_c_mode.input(rx_first, &wilc_netif_c_mode))) {
					osprintf("AP error sending to stack %d.\r\n", error);
					pbuf_free(rx_first);
				}
			}
			LINK_STATS_INC(link.recv);
			rx_first = p;			
		} else {
			if (!p) {
				if (rx_first)
					pbuf_free(rx_first);
				rx_first = 0;
				LINK_STATS_INC(link.memerr);
				LINK_STATS_INC(link.drop);
				/* Reload memory buffer for further incoming packets. */
				m2m_wifi_set_receive_buffer_ex(rx_buf, sizeof(rx_buf));
				return;
			} else {
				p->tot_len = rem;
				rx_last->next = p;
			}
		}
		rx_last = p;
		if (rx_first == rx_last) {
			if (rx_first) {
				b = (uint8_t*) p->payload;
			} else {
				b = rx_buf;
			}
		} else {
			b = p->payload;
		}
		/* Reload memory buffer for further incoming packets. */
		m2m_wifi_set_receive_buffer_ex(b, WILC_RX_BUF_SZ);
	}
}

#if LWIP_IGMP
static uint8_t wilc_netif_ipv4_mac_mcast[6] = {
	0x01, 0x00, 0x5e, 0x00, 0x00, 0x00
};
static err_t wilc_netif_ipv4_mac_filter(struct netif *netif, ip_addr_t *group, u8_t action)
{
	wilc_netif_ipv4_mac_mcast[3] = ((uint8_t *)group)[1] & 0x7f;
	wilc_netif_ipv4_mac_mcast[4] = ((uint8_t *)group)[2];
	wilc_netif_ipv4_mac_mcast[5] = ((uint8_t *)group)[3];
	m2m_wifi_enable_mac_mcast_ex(ipv4_mac_mcast, action);
	return 0;	
}
#endif

#if LWIP_IPV6_MLD
static uint8_t wilc_netif_ipv6_mac_mcast[6] = {
	0x33, 0x33, 0x00, 0x00, 0x00, 0x00
};
static err_t wilc_netif_ipv6_mac_filter(struct netif *netif, ip6_addr_t *group, u8_t action)
{
	memcpy(&wilc_netif_ipv6_mac_mcast[2], &group->addr[3], 4);
	m2m_wifi_enable_mac_mcast_ex(wilc_netif_ipv6_mac_mcast, action);
	return 0;
}
#endif

/**
 * \brief Initialize lwIP network interface.
 */
err_t wilc_netif_init(struct netif *netif)
{
#if LWIP_NETIF_HOSTNAME
	netif->hostname = "WILC";
#endif /* LWIP_NETIF_HOSTNAME */
#if LWIP_SNMP
	NETIF_INIT_SNMP(netif, snmp_ifType_ethernet_csmacd, NET_LINK_SPEED);
#endif /* LWIP_SNMP */
	netif->state = NULL;
	netif->name[0] = IFNAME0;
	netif->name[1] = IFNAME1;
	netif->output = etharp_output;
	netif->linkoutput = wilc_netif_tx;
#if LWIP_IPV6
	netif->output_ip6 = ethip6_output;
#endif
#if LWIP_IGMP
	netif->igmp_mac_filter = wilc_netif_ipv4_mac_filter;
#endif // #if LWIP_IGMP
#if LWIP_IPV6_MLD
	netif->mld_mac_filter = wilc_netif_ipv6_mac_filter;
#endif // #if LWIP_IPV6_MLD
	wilc_netif_low_level_init(netif);
	return ERR_OK;
}

/**
 * \brief Configure RX callback and buffer.
 */
void wilc_fill_callback_info(tstrEthInitParam *info)
{
	info->pfAppEthCb = wilc_netif_rx_callback;
	info->au8ethRcvBuf = rx_buf;
	info->u16ethRcvBufSize = sizeof(rx_buf);
}
