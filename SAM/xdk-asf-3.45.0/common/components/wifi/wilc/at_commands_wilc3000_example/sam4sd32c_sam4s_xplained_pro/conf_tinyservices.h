/**
 * \file
 *
 * \brief Tiny DHCP/DNS service configuration.
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

#ifndef CONF_TINYSERVICES_H_INCLUDED
#define CONF_TINYSERVICES_H_INCLUDED

/* Access Point's address in provisioning mode. */
#define AP_ADDR						192, 168, 5, 1
#define AP_ADDR_IP					_tiny_ip4_addr(AP_ADDR)

/** Default subnet mask in provisioning mode */
#define SN_MASK						255, 255, 255, 0
#define SN_MASK_IP					_tiny_ip4_addr(SN_MASK)

/** Default gateway in provisioning mode. */
#define GW_ADDR						192, 168, 5, 1
#define GW_ADDR_IP					_tiny_ip4_addr(GW_ADDR)

/** Default Domain Name supplied to the client by Tiny DHCP Server in provisioning mode. */
#define DOMAIN_NAME					"iot.com"
#define DOMAIN_NAME_LEN				(8)

/** Default Name Server supplied to the client by Tiny DHCP Server in provisioning mode. */
#define NAME_SERVER_HOST_NAME		"ns"
#define NAME_SERVER_FQDN			NAME_SERVER_HOST_NAME "." DOMAIN_NAME
#define NAME_SERVER_FQDN_LEN		(11)
#define HTTP_SRV_LOCAL_NAME			"smartconnect"

/** Default Renewal Time supplied to the client by Tiny DHCP Server in provisioning mode. */
#define SANE_RENEWAL_TIME			(ADAY_DNS_TTL)

/** Default Rebinding Time supplied to the client by Tiny DHCP Server in provisioning mode. */
#define SANE_REBINDING_TIME			(ADAY_DNS_TTL)

/** Default Lease Time supplied to the client by Tiny DHCP Server in provisioning mode. */
#define SANE_LEASE_TIME				(ADAY_DNS_TTL)

/** Default DNS Time To Live supplied to the client by Tiny DHCP Server in provisioning mode. */
#define SANE_DNS_TTL				(600)
#define TWOHOUR_DNS_TTL				(7200)
#define ADAY_DNS_TTL				(86400)

#endif /* CONF_TINYSERVICES_H_INCLUDED */
