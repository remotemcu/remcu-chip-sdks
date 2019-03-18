/**
 *
 * \file
 *
 * \brief WINC Network Interface APIs
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
#ifndef NET_INIT_H_INCLUDED
#define NET_INIT_H_INCLUDED

#define NET_IF_STA				0x1
#define NET_IF_C				0x2

#define NET_MODE_USE_DHCP		0x1
#define NET_MODE_USE_STATIC		0x2
#define NET_MODE_AP				0x4
#define NET_MODE_USE_LINK_LOCAL	0x8
#define NET_MODE_USE_DHCP_SVR	0x10

typedef struct {
	uint8_t	*u8StaticIP;
	/*!< The static IP assigned to the device.
	*/
	uint8_t	*u8SubnetMask;
	/*!< Subnet mask for the local area network.
	*/
	uint8_t	*u8StaticIPv6;
} tstrM2MIPConfig2;

void net_init(void);
void net_set_mode(uint32_t net_if, uint32_t mode);
void net_interface_up(uint32_t net_if);
void net_interface_down(uint32_t net_if);
void net_add_winc_netif(void);
void net_remove_winc_netif(void);
int net_in_tcpip_task(void);

#endif /* NET_INIT_H_INCLUDED */
