/**
 * \file
 *
 * \brief LwIP configuration.
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

#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

/* Include ethernet configuration first */
#include "conf_eth.h"

/*
   -----------------------------------------------
   -------------- LwIP API Support ---------------
   -----------------------------------------------
*/

/**
 * NO_SYS==1: Provides VERY minimal functionality. Otherwise,
 * use lwIP facilities.
 */
#define NO_SYS                		1
#define LWIP_RAW                  	1
#define LWIP_NETIF_STATUS_CALLBACK	1

/**
 * SYS_LIGHTWEIGHT_PROT==1: if you want inter-task protection for certain
 * critical regions during buffer allocation, deallocation and memory
 * allocation and deallocation.
 */
#define SYS_LIGHTWEIGHT_PROT        0

/* These are not available when using "NO_SYS" */
#define LWIP_NETCONN            	0
#define LWIP_SOCKET             	0

/* Enable DHCP support */
#define DHCP_USED

#define HTTP_RAW_USED

/*
   ------------------------------------
   ---------- Memory options ----------
   ------------------------------------
*/

/**
 * MEM_ALIGNMENT: should be set to the alignment of the CPU
 *    4 byte alignment -> #define MEM_ALIGNMENT 4
 *    2 byte alignment -> #define MEM_ALIGNMENT 2
 */
#define MEM_ALIGNMENT           		4

/**
 * MEM_SIZE: the size of the heap memory. If the application will send
 * a lot of data that needs to be copied, this should be set high.
 */
#define MEM_SIZE                		20 * 1024

/**
 * MEMP_NUM_TCP_PCB: the number of simulatenously active TCP connections.
 * (requires the LWIP_TCP option)
 */
#define MEMP_NUM_TCP_PCB                14

/**
 * MEMP_NUM_TCP_PCB_LISTEN: the number of listening TCP connections.
 * (requires the LWIP_TCP option)
 */
#define MEMP_NUM_TCP_PCB_LISTEN         1

/**
 * MEMP_NUM_NETBUF: the number of struct netbufs.
 * (only needed if you use the sequential API, like api_lib.c)
 */
#define MEMP_NUM_NETBUF                 0

/**
 * MEMP_NUM_NETCONN: the number of struct netconns.
 * (only needed if you use the sequential API, like api_lib.c)
 */
#define MEMP_NUM_NETCONN                0

/**
 * PBUF_POOL_SIZE: the number of buffers in the pbuf pool.
 */
#define PBUF_POOL_SIZE                  10

/**
 * PBUF_POOL_BUFSIZE: the size of each pbuf in the pbuf pool. The default is
 * designed to accomodate single full size TCP frame in one pbuf, including
 * TCP_MSS, IP header, and link header.
 */
// using default size !!! #define PBUF_POOL_BUFSIZE               512

/*
   ----------------------------------
   ---------- DHCP options ----------
   ----------------------------------
*/

#if defined(DHCP_USED)
/**
 * LWIP_DHCP==1: Enable DHCP module.
 */
#define LWIP_DHCP               1

#define DHCP_DOES_ARP_CHECK     1
#endif

/*
   ---------------------------------
   ---------- UDP options ----------
   ---------------------------------
*/

/**
 * LWIP_UDP==1: Turn on UDP.
 */
#define LWIP_UDP                1

/*
   ---------------------------------
   ---------- TCP options ----------
   ---------------------------------
*/

/**
 * LWIP_TCP==1: Turn on TCP.
 */
#define LWIP_TCP                1

/**
 * TCP_MSS: The maximum segment size controls the maximum amount of
 * payload bytes per packet. For maximum throughput, set this as
 * high as possible for your network (i.e. 1460 bytes for standard
 * ethernet).
 * For the receive side, this MSS is advertised to the remote side
 * when opening a connection. For the transmit size, this MSS sets
 * an upper limit on the MSS advertised by the remote host.
 */
#define TCP_MSS                 1500

/**
 * TCP_WND: The size of a TCP window.  This must be at least
 * (2 * TCP_MSS) for things to work well
 */
#define TCP_WND                 (2 * TCP_MSS)

/**
 * TCP_SND_BUF: TCP sender buffer space (bytes).
 * To achieve good performance, this should be at least 2 * TCP_MSS.
 */
#define TCP_SND_BUF             (2 * TCP_MSS)

/*
   ----------------------------------------
   ---------- Statistics options ----------
   ----------------------------------------
*/

#define LWIP_STATS 1
#define LWIP_STATS_DISPLAY 0
#define LWIP_STATS_LARGE 0

#if LWIP_STATS
#define LINK_STATS 1
#define IP_STATS   1
#define IPFRAG_STATS 0
#define ICMP_STATS 0
#define IGMP_STATS 0
#define UDP_STATS  0
#define TCP_STATS  1
#define MEM_STATS  1
#define MEMP_STATS 1
#define SYS_STATS  1
#endif

/*
   ---------------------------------------
   ---------- Debugging options ----------
   ---------------------------------------
*/

//#define LWIP_DEBUG						1

#define LWIP_NOASSERT

#define LWIP_DBG_MIN_LEVEL              LWIP_DBG_LEVEL_SEVERE
#define LWIP_DBG_TYPES_ON               LWIP_DBG_OFF
#define ETHARP_DEBUG                    LWIP_DBG_OFF
#define NETIF_DEBUG                     LWIP_DBG_OFF
#define PBUF_DEBUG                      LWIP_DBG_OFF
#define API_LIB_DEBUG                   LWIP_DBG_OFF
#define API_MSG_DEBUG                   LWIP_DBG_OFF
#define SOCKETS_DEBUG                   LWIP_DBG_OFF
#define ICMP_DEBUG                      LWIP_DBG_OFF
#define IGMP_DEBUG                      LWIP_DBG_OFF
#define INET_DEBUG                      LWIP_DBG_OFF
#define IP_DEBUG                        LWIP_DBG_OFF
#define IP_REASS_DEBUG                  LWIP_DBG_OFF
#define RAW_DEBUG                       LWIP_DBG_OFF
#define MEM_DEBUG                       LWIP_DBG_OFF
#define MEMP_DEBUG                      LWIP_DBG_OFF
#define SYS_DEBUG                       LWIP_DBG_OFF
#define TIMERS_DEBUG                    LWIP_DBG_OFF
#define TCP_DEBUG                       LWIP_DBG_OFF
#define TCP_INPUT_DEBUG                 LWIP_DBG_OFF
#define TCP_FR_DEBUG                    LWIP_DBG_OFF
#define TCP_RTO_DEBUG                   LWIP_DBG_OFF
#define TCP_CWND_DEBUG                  LWIP_DBG_OFF
#define TCP_WND_DEBUG                   LWIP_DBG_OFF
#define TCP_OUTPUT_DEBUG                LWIP_DBG_OFF
#define TCP_RST_DEBUG                   LWIP_DBG_OFF
#define TCP_QLEN_DEBUG                  LWIP_DBG_OFF
#define UDP_DEBUG                       LWIP_DBG_OFF
#define TCPIP_DEBUG                     LWIP_DBG_OFF
#define PPP_DEBUG                       LWIP_DBG_OFF
#define SLIP_DEBUG                      LWIP_DBG_OFF
#define DHCP_DEBUG                      LWIP_DBG_OFF
#define AUTOIP_DEBUG                    LWIP_DBG_OFF
#define SNMP_MSG_DEBUG                  LWIP_DBG_OFF
#define SNMP_MIB_DEBUG                  LWIP_DBG_OFF
#define DNS_DEBUG                       LWIP_DBG_OFF

// \note For a list of all possible lwIP configurations, check http://lwip.wikia.com/wiki/Lwipopts.h

#endif /* __LWIPOPTS_H__ */
