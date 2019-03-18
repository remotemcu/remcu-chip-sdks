/**
 * \file
 *
 * \brief Include definitions for the mini ip.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _MINIIP_H_INCLUDED
#define _MINIIP_H_INCLUDED

#include <compiler.h>

/** Ethernet types */
#define ETH_PROT_IP             0x0800 /**< 2048  (0x0800) IPv4 */
#define ETH_PROT_ARP            0x0806 /**< 2054  (0x0806) ARP */
#define ETH_PROT_APPLETALK      0x8019 /**< 32923 (0x8019) Appletalk */
#define ETH_PROT_IPV6           0x86DD /**< 34525 (0x86DD) IPv6 */

/** ARP OP codes */
#define ARP_REQUEST             0x0001 /**< ARP Request packet */
#define ARP_REPLY               0x0002 /**< ARP Reply packet */

/** IP protocols code */
/* http://www.iana.org/assignments/protocol-numbers */
#define IP_PROT_ICMP            1
#define IP_PROT_IP              4
#define IP_PROT_TCP             6
#define IP_PROT_UDP             17

/** ICMP types */
/* http://www.iana.org/assignments/icmp-parameters */
#define ICMP_ECHO_REPLY         0x00 /**< Echo reply (used to ping) */
/* 1 and 2 Reserved */
#define ICMP_DEST_UNREACHABLE   0x03 /**< Destination Unreachable */
#define ICMP_SOURCE_QUENCH      0x04 /**< Source Quench */
#define ICMP_REDIR_MESSAGE      0x05 /**< Redirect Message */
#define ICMP_ALT_HOST_ADD       0x06 /**< Alternate Host Address */
/*  0x07 Reserved */
#define ICMP_ECHO_REQUEST       0x08 /**< Echo Request */
#define ICMP_ROUTER_ADV         0x09 /**< Router Advertisement */
#define ICMP_ROUTER_SOL         0x0A /**< Router Solicitation */
#define ICMP_TIME_EXC           0x0B /**< Time Exceeded */
#define ICMP_PARAM_PB           0x0C /**< Parameter Problem: Bad IP header */
#define ICMP_TIMESTAMP          0x0D /**< Timestamp */
#define ICMP_TIMESTAMP_REP      0x0E /**< Timestamp Reply */
#define ICMP_INFO_REQ           0x0F /**< Information Request */
#define ICMP_INFO_REPLY         0x10 /**< Information Reply */
#define ICMP_ADD_MASK_REQ       0x11 /**< Address Mask Request */
#define ICMP_ADD_MASK_REP       0x12 /**< Address Mask Reply */
/*  0x13 Reserved for security */
/*  0X14 through 0x1D Reserved for robustness experiment */
#define ICMP_TRACEROUTE         0x1E /**< Traceroute */
#define ICMP_DAT_CONV_ERROR     0x1F /**< Datagram Conversion Error */
#define ICMP_MOB_HOST_RED       0x20 /**< Mobile Host Redirect */
#define ICMP_W_A_Y              0x21 /**< Where-Are-You (originally meant for IPv6) */
#define ICMP_H_I_A              0x22 /**< Here-I-Am (originally meant for IPv6) */
#define ICMP_MOB_REG_REQ        0x23 /**< Mobile Registration Request */
#define ICMP_MOB_REG_REP        0x24 /**< Mobile Registration Reply */
#define ICMP_DOM_NAME_REQ       0x25 /**< Domain Name Request */
#define ICMP_DOM_NAME_REP       0x26 /**< Domain Name Reply */
#define ICMP_SKIP_ALGO_PROT     0x27 /**< SKIP Algorithm Discovery Protocol, Simple Key-Management for Internet Protocol */
#define ICMP_PHOTURIS           0x28 /**< Photuris, Security failures */
#define ICMP_EXP_MOBIL          0x29 /**< ICMP for experimental mobility protocols such as Seamoby [RFC4065] */
/* 0x2A through 0xFF Reserved */

/** Swap 2 bytes of a word */
#define SWAP16(x)   (((x & 0xff) << 8) | (x >> 8))

/** Ethernet header structure */
COMPILER_PACK_SET(1)
typedef struct ethernet_header {
	uint8_t et_dest[6];  /**< Destination node */
	uint8_t et_src[6];   /**< Source node */
	uint16_t et_protlen; /**< Protocol or length */
} ethernet_header_t, *p_ethernet_header_t;

/** ARP header structure */
COMPILER_PACK_SET(1)
typedef struct arp_header {
	uint16_t ar_hrd;   /**< Format of hardware address */
	uint16_t ar_pro;   /**< Format of protocol address */
	uint8_t ar_hln;    /**< Length of hardware address */
	uint8_t ar_pln;    /**< Length of protocol address */
	uint16_t ar_op;    /**< Operation */
	uint8_t ar_sha[6]; /**< Sender hardware address */
	uint8_t ar_spa[4]; /**< Sender protocol address */
	uint8_t ar_tha[6]; /**< Target hardware address */
	uint8_t ar_tpa[4]; /**< Target protocol address */
} arp_header_t, *p_arp_header_t;

/** IP Header structure */
COMPILER_PACK_SET(1)
typedef struct _IPheader {
	uint8_t ip_hl_v;   /**< Header length and version */
	uint8_t ip_tos;    /**< Type of service */
	uint16_t ip_len;   /**< Total length */
	uint16_t ip_id;    /**< Identification */
	uint16_t ip_off;   /**< Fragment offset field */
	uint8_t ip_ttl;    /**< Time to live */
	uint8_t ip_p;      /**< Protocol */
	uint16_t ip_sum;   /**< Checksum */
	uint8_t ip_src[4]; /**< Source IP address */
	uint8_t ip_dst[4]; /**< Destination IP address */
} ip_header_t, *p_ip_header_t;

/** ICMP echo header structure */
COMPILER_PACK_SET(1)
typedef struct icmp_echo_header {
	uint8_t type;   /**< Type of message */
	uint8_t code;   /**< Type subcode */
	uint16_t cksum; /**< 1's complement cksum of struct */
	uint16_t id;    /**< Identifier */
	uint16_t seq;   /**< Sequence number */
} icmp_echo_header_t, *p_icmp_echo_header_t;

/** Ethernet packet structure */
COMPILER_PACK_SET(1)
typedef struct eth_packet {
	ethernet_header_t eth_hdr;
	arp_header_t arp_hdr;
} eth_packet_t, *p_eth_packet_t;

COMPILER_PACK_RESET()

/** Ethernet header size */
#define ETH_HEADER_SIZE   (sizeof(ethernet_header_t))

/** Ethernet IP header size */
#define ETH_IP_HEADER_SIZE   (sizeof(ip_header_t))

#endif /* _MINIIP_H_INCLUDED */
