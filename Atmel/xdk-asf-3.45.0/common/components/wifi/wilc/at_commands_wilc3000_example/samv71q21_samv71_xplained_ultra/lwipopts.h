/**
 * \file
 *
 * \brief LwIP configuration.
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

#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#include "compiler.h"
#include "FreeRTOS.h"

extern int random_number(void);
#define LWIP_RAND						random_number

/*
   -----------------------------------------------
   ---------- Platform specific locking ----------
   -----------------------------------------------
*/

/**
 * SYS_LIGHTWEIGHT_PROT==1: if you want inter-task protection for certain
 * critical regions during buffer allocation, deallocation and memory
 * allocation and deallocation.
 */

#define SYS_LIGHTWEIGHT_PROT			1

/*
   -----------------------------------------------
   -------------- LwIP API Support ---------------
   -----------------------------------------------
*/

/**
 * LWIP_NETCONN==1: Enable Netconn API (require to use api_lib.c)
 */
#define LWIP_NETCONN                    1

/**
 * LWIP_SOCKET==1: Enable Socket API (require to use sockets.c)
 */
#define LWIP_SOCKET                     1

#if LWIP_SOCKET
#define LWIP_TIMEVAL_PRIVATE			0   // set it to 0 to avoid timeval struct redefined build error, if LWIP_SOCKET is set
#endif
/**
 * LWIP_SO_RCVTIMEO==1: Enable recv timeout
 */
#define LWIP_SO_RCVTIMEO                1
/*
   ------------------------------------
   ---------- Memory options ----------
   ------------------------------------
*/

/**
 * MEM_LIBC_MALLOC==1: Use malloc/free/realloc provided by your C-library
 * instead of the lwip internal allocator. Can save code size if you
 * already use it.
 */
/* Use FreeRTOS heap instead. */
#define MEM_LIBC_MALLOC					1
#if MEM_LIBC_MALLOC
#define mem_malloc				pvPortMalloc
#define mem_free				vPortFree
#endif

/**
 * MEM_ALIGNMENT: should be set to the alignment of the CPU
 *    4 byte alignment -> #define MEM_ALIGNMENT 4
 *    2 byte alignment -> #define MEM_ALIGNMENT 2
 */
#define MEM_ALIGNMENT           		4

/**
 * MEMP_NUM_UDP_PCB: the number of UDP protocol control blocks. One
 * per active UDP "connection".
 * (requires the LWIP_UDP option)
 */
#define MEMP_NUM_UDP_PCB                8

/**
 * MEMP_NUM_TCP_PCB: the number of simultaneously active TCP connections.
 * (requires the LWIP_TCP option)
 */
#define MEMP_NUM_TCP_PCB                8

/**
 * MEMP_NUM_TCP_PCB_LISTEN: the number of listening TCP connections.
 * (requires the LWIP_TCP option)
 */
#define MEMP_NUM_TCP_PCB_LISTEN         1

/**
 * MEMP_NUM_TCP_SEG: the number of simultaneously queued TCP segments.
 * (requires the LWIP_TCP option)
 */
#define MEMP_NUM_TCP_SEG                64//27 //32

/**
 * MEMP_NUM_SYS_TIMEOUT: the number of simultaneously active timeouts.
 */
#define MEMP_NUM_SYS_TIMEOUT            12

/**
 * PBUF_POOL_SIZE: the number of buffers in the pbuf pool. 
 */
#define PBUF_POOL_SIZE                  24//8//20 MEMP_NUM_TCP_SEG

/**
 * PBUF_POOL_BUFSIZE: the size of each pbuf in the pbuf pool.
 */
#define PBUF_POOL_BUFSIZE               1610

/** ETH_PAD_SIZE: number of bytes added before the ethernet header to ensure
 * alignment of payload after that header. Since the header is 14 bytes long,
 * without this padding e.g. addresses in the IP header will not be aligned
 * on a 32-bit boundary, so setting this to 2 can speed up 32-bit-platforms.
 */
#define ETH_PAD_SIZE                    2

/**
 * MEMP_NUM_RAW_PCB: Number of raw connection PCBs
 * (requires the LWIP_RAW option)
 */
#define MEMP_NUM_RAW_PCB                1

/**
 * MEMP_NUM_NETBUF: the number of struct netbufs.
 * (only needed if you use the sequential API, like api_lib.c)
 */
#define MEMP_NUM_NETBUF                 8

/**
 * MEMP_NUM_NETCONN: the number of struct netconns.
 * (only needed if you use the sequential API, like api_lib.c)
 */
#define MEMP_NUM_NETCONN                16

/*
   ---------------------------------------
   ---------- IPv6 options ---------------
   ---------------------------------------
*/

/**
 * LWIP_IPV6==1: Enable IPv6
 */
#define LWIP_IPV6						1

/*
   ---------------------------------
   ---------- TCP options ----------
   ---------------------------------
*/

/**
 * LWIP_TCP==1: Turn on TCP.
 */
#define LWIP_TCP                        1

/**
 * TCP_MSS: TCP Maximum segment size.
 */
#define TCP_MSS                         1400

/**
 * TCP_WND: The size of a TCP window.  This must be at least 
 * (2 * TCP_MSS) for things to work well
 */
#define TCP_WND                         (8 * TCP_MSS)//(2 * TCP_MSS)//(4 * TCP_MSS)

/**
 * TCP_SND_BUF: TCP sender buffer space (bytes).
 * To achieve good performance, this should be at least 2 * TCP_MSS.
 */
#define TCP_SND_BUF                     TCP_WND//(4 * TCP_MSS)//TCP_WND

/**
 * TCP_SND_QUEUELEN: TCP sender buffer space (pbufs). This must be at least
 * as much as (2 * TCP_SND_BUF/TCP_MSS) for things to work.
 */
#define TCP_SND_QUEUELEN                ((6 * (TCP_SND_BUF) + (TCP_MSS - 1))/(TCP_MSS))//(4 * TCP_SND_BUF / TCP_MSS)

/*
   ---------------------------------
   ---------- UDP options ----------
   ---------------------------------
*/

/**
 * LWIP_UDP==1: Turn on UDP.
 */
#define LWIP_UDP                        1

/*
   ----------------------------------
   ---------- IGMP options ----------
   ----------------------------------
*/

/**
 * LWIP_IGMP==1: Turn on IGMP module. 
 */
#define LWIP_IGMP						0

/*
   ----------------------------------
   ---------- DNS options -----------
   ----------------------------------
*/

/**
 * LWIP_DNS==1: Turn on DNS module. UDP must be available for DNS
 * transport.
 */
#define LWIP_DNS						1

/*
   ----------------------------------
   ---------- DHCP options ----------
   ----------------------------------
*/

/**
 * LWIP_DHCP==1: Enable DHCP module.
 */
#define LWIP_DHCP						1

/*
   ------------------------------------
   ---------- AUTOIP options ----------
   ------------------------------------
*/

/**
 * LWIP_AUTOIP==1: Enable AUTOIP module.
 */
#define LWIP_AUTOIP					1

/**
 * LWIP_DHCP_AUTOIP_COOP==1: Allow DHCP and AUTOIP to be both enabled on
 * the same interface at the same time.
 */
#define LWIP_DHCP_AUTOIP_COOP           1

/*
   ------------------------------------
   ---------- Thread options ----------
   ------------------------------------
*/

/**
 * TCPIP_THREAD_NAME: The name assigned to the main tcpip thread.
 */
#define TCPIP_THREAD_NAME               "TCP/IP"

/**
 * TCPIP_THREAD_STACKSIZE: The stack size used by the main tcpip thread.
 * The stack size value itself is platform-dependent, but is passed to
 * sys_thread_new() when the thread is created.
 */
#define TCPIP_THREAD_STACKSIZE          (8192 / sizeof(portSTACK_TYPE))

/**
 * TCPIP_THREAD_PRIO: The priority assigned to the main tcpip thread.
 * The priority value itself is platform-dependent, but is passed to
 * sys_thread_new() when the thread is created.
 */
#define TCPIP_THREAD_PRIO               (configMAX_PRIORITIES - 1)

/**
 * TCPIP_MBOX_SIZE: The mailbox size for the tcpip thread messages
 * The queue size value itself is platform-dependent, but is passed to
 * sys_mbox_new() when tcpip_init is called.
 */
#define TCPIP_MBOX_SIZE                 6//64

/**
 * SLIPIF_THREAD_NAME: The name assigned to the slipif_loop thread.
 */
#define SLIPIF_THREAD_NAME              "slipif"

/**
 * SLIP_THREAD_STACKSIZE: The stack size used by the slipif_loop thread.
 * The stack size value itself is platform-dependent, but is passed to
 * sys_thread_new() when the thread is created.
 */
#define SLIPIF_THREAD_STACKSIZE         configMINIMAL_STACK_SIZE

/**
 * SLIPIF_THREAD_PRIO: The priority assigned to the slipif_loop thread.
 * The priority value itself is platform-dependent, but is passed to
 * sys_thread_new() when the thread is created.
 */
#define SLIPIF_THREAD_PRIO              1

/**
 * PPP_THREAD_NAME: The name assigned to the pppMain thread.
 */
#define PPP_THREAD_NAME                 "pppInputThread"

/**
 * PPP_THREAD_STACKSIZE: The stack size used by the pppMain thread.
 * The stack size value itself is platform-dependent, but is passed to
 * sys_thread_new() when the thread is created.
 */
#define PPP_THREAD_STACKSIZE            configMINIMAL_STACK_SIZE

/**
 * PPP_THREAD_PRIO: The priority assigned to the pppMain thread.
 * The priority value itself is platform-dependent, but is passed to
 * sys_thread_new() when the thread is created.
 */
#define PPP_THREAD_PRIO                 1

/**
 * DEFAULT_THREAD_NAME: The name assigned to any other lwIP thread.
 */
#define DEFAULT_THREAD_NAME             "lwIP"

/**
 * DEFAULT_THREAD_STACKSIZE: The stack size used by any other lwIP thread.
 * The stack size value itself is platform-dependent, but is passed to
 * sys_thread_new() when the thread is created.
 */
#define DEFAULT_THREAD_STACKSIZE        configMINIMAL_STACK_SIZE

/**
 * DEFAULT_THREAD_PRIO: The priority assigned to any other lwIP thread.
 * The priority value itself is platform-dependent, but is passed to
 * sys_thread_new() when the thread is created.
 */
#define DEFAULT_THREAD_PRIO             1

/**
 * DEFAULT_RAW_RECVMBOX_SIZE: The mailbox size for the incoming packets on a
 * NETCONN_RAW. The queue size value itself is platform-dependent, but is passed
 * to sys_mbox_new() when the recvmbox is created.
 */
#define DEFAULT_RAW_RECVMBOX_SIZE       6

/**
 * DEFAULT_UDP_RECVMBOX_SIZE: The mailbox size for the incoming packets on a
 * NETCONN_UDP. The queue size value itself is platform-dependent, but is passed
 * to sys_mbox_new() when the recvmbox is created.
 */
#define DEFAULT_UDP_RECVMBOX_SIZE       6

/**
 * DEFAULT_TCP_RECVMBOX_SIZE: The mailbox size for the incoming packets on a
 * NETCONN_TCP. The queue size value itself is platform-dependent, but is passed
 * to sys_mbox_new() when the recvmbox is created.
 */
#define DEFAULT_TCP_RECVMBOX_SIZE       6

/**
 * DEFAULT_ACCEPTMBOX_SIZE: The mailbox size for the incoming connections.
 * The queue size value itself is platform-dependent, but is passed to
 * sys_mbox_new() when the acceptmbox is created.
 */
#define DEFAULT_ACCEPTMBOX_SIZE         6

/*
   ------------------------------------------------
   ---------- Network Interfaces options ----------
   ------------------------------------------------
*/

/**
 * LWIP_NETIF_STATUS_CALLBACK==1: Support a callback function whenever an interface
 * changes its up/down status (i.e., due to DHCP IP acquisition)
 */
#define LWIP_NETIF_STATUS_CALLBACK      1

/*
   ----------------------------------------
   ---------- Statistics options ----------
   ----------------------------------------
*/

/**
 * LWIP_STATS==1: Enable statistics collection in lwip_stats.
 */
#define LWIP_STATS						1

/**
 * LWIP_STATS_DISPLAY==1: Compile in the statistics output functions.
 */
#define LWIP_STATS_DISPLAY				0

/**
 * LWIP_STATS_LARGE==1: Use 32 bits counter instead of 16.
 */
#define LWIP_STATS_LARGE				1

#if LWIP_STATS
#define LINK_STATS                      1
#define IP_STATS                        1
#define ICMP_STATS                      1
#define UDP_STATS                       1
#define TCP_STATS                       1
#define MEM_STATS                       1
#define MEMP_STATS                      1
#define PBUF_STATS                      1
#define SYS_STATS                       1
#endif

/*
   ---------------------------------------
   ---------- Debugging options ----------
   ---------------------------------------
*/

//#define LWIP_NOASSERT

#define LWIP_DEBUG
#define LWIP_DBG_MIN_LEVEL              LWIP_DBG_LEVEL_ALL
#define LWIP_DBG_TYPES_ON               LWIP_DBG_ON

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
