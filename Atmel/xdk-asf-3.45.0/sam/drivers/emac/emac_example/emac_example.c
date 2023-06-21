/**
 * \file
 *
 * \brief EMAC example for SAM.
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

/**
 * \mainpage EMAC Example
 *
 *  \section Purpose
 *
 *  This example uses the Ethernet MAC (EMAC) and the on-board Ethernet
 *  transceiver available on Atmel evaluation kits. It enables the device to
 *  respond to a ping command sent by a host computer.
 *
 *  \section Requirements
 *
 *  - SAM microcontrollers with EMAC feature.
 *  - On-board ethernet interface.
 *
 *  \section Description
 *
 *  Upon startup, the program will configure the EMAC with a default IP and
 *  MAC address and then ask the transceiver to auto-negotiate the best mode
 *  of operation. Once this is done, it will start to monitor incoming packets
 *  and process them whenever appropriate.
 *
 *  The basic will only answer to two kinds of packets:
 *
 *  - It will reply to ARP requests with its MAC address,
 *  - and to ICMP ECHO request so that the device can be PING'ed.
 *
 *  You may use 'ping' command to check if the board responds correctly to
 *  ping requests.
 *
 *  \section Usage
 *
 *  -# Build the program and download it into the evaluation board.
 *  -# On the computer, open and configure a terminal application
 *     (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *    - 115200 bauds
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# Connect an Ethernet cable between the evaluation board and the network.
 *      The board may be connected directly to a computer; in this case,
 *      make sure to use a cross/twisted wired cable such as the one provided
 *      with the evaluation kit.
 *  -# Start the application. It will display the following message on the terminal:
 *     \code
	-- EMAC Example --
	-- SAMxxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
	MAC 00:45:56:78:9a:bc
	IP 192.168.0.2
\endcode
 *  -# The program will then auto-negotiate the mode of operation and start
 *     receiving packets, displaying feedback on the terminal. To display additional
 *     information, press any key in the terminal application.
 *  -# To test if the board responds to ICMP ECHO requests, type the following
 *     command line in a shell:
 *      \code
	ping 192.168.0.2
\endcode
 *     Response to 'ping' cmd will appear in the shell.
 *
 *  \note
 *  Make sure the IP address of the device(EK board) and the computer are in the same network.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include <string.h>
#include "mini_ip.h"
#include "conf_eth.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

#define STRING_EOL    "\r"
#define STRING_HEADER "-- EMAC Example --\r" \
		"-- "BOARD_NAME" --\r" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/** The MAC address used for the test */
static uint8_t gs_uc_mac_address[] =
		{ ETHERNET_CONF_ETHADDR0, ETHERNET_CONF_ETHADDR1, ETHERNET_CONF_ETHADDR2,
			ETHERNET_CONF_ETHADDR3, ETHERNET_CONF_ETHADDR4, ETHERNET_CONF_ETHADDR5
};

/** The IP address used for test (ping ...) */
static uint8_t gs_uc_ip_address[] =
		{ ETHERNET_CONF_IPADDR0, ETHERNET_CONF_IPADDR1,
			ETHERNET_CONF_IPADDR2, ETHERNET_CONF_IPADDR3 };

/** The EMAC driver instance */
static emac_device_t gs_emac_dev;

/** Buffer for ethernet packets */
static volatile uint8_t gs_uc_eth_buffer[EMAC_FRAME_LENTGH_MAX];

/**
 * \brief Process & return the ICMP checksum.
 *
 * \param p_buff Pointer to the buffer.
 * \param ul_len The length of the buffered data.
 *
 * \return Checksum of the ICMP.
 */
static uint16_t emac_icmp_checksum(uint16_t *p_buff, uint32_t ul_len)
{
	uint32_t i, ul_tmp;

	for (i = 0, ul_tmp = 0; i < ul_len; i++, p_buff++) {

		ul_tmp += SWAP16(*p_buff);
	}
	ul_tmp = (ul_tmp & 0xffff) + (ul_tmp >> 16);

	return (uint16_t) (~ul_tmp);
}

/**
 * \brief Display the IP packet.
 *
 * \param p_ip_header Pointer to the IP header.
 * \param ul_size    The data size.
 */
static void emac_display_ip_packet(p_ip_header_t p_ip_header, uint32_t ul_size)
{
	printf("======= IP %4d bytes, HEADER ==========\n\r", (int)ul_size);
	printf(" IP Version        = v.%d", (p_ip_header->ip_hl_v & 0xF0) >> 4);
	printf("\n\r Header Length     = %d", p_ip_header->ip_hl_v & 0x0F);
	printf("\n\r Type of service   = 0x%x", p_ip_header->ip_tos);
	printf("\n\r Total IP Length   = 0x%X",
			(((p_ip_header->ip_len) >> 8) & 0xff) +
			(((p_ip_header->ip_len) << 8) & 0xff00));
	printf("\n\r ID                = 0x%X",
			(((p_ip_header->ip_id) >> 8) & 0xff) +
			(((p_ip_header->ip_id) << 8) & 0xff00));
	printf("\n\r Header Checksum   = 0x%X",
			(((p_ip_header->ip_sum) >> 8) & 0xff) +
			(((p_ip_header->ip_sum) << 8) & 0xff00));
	puts("\r Protocol          = ");

	switch (p_ip_header->ip_p) {
	case IP_PROT_ICMP:
		puts("ICMP");
		break;

	case IP_PROT_IP:
		puts("IP");
		break;

	case IP_PROT_TCP:
		puts("TCP");
		break;

	case IP_PROT_UDP:
		puts("UDP");
		break;

	default:
		printf("%d (0x%X)", p_ip_header->ip_p, p_ip_header->ip_p);
		break;
	}

	printf("\n\r IP Src Address    = %d:%d:%d:%d",
			p_ip_header->ip_src[0],
			p_ip_header->ip_src[1],
			p_ip_header->ip_src[2], p_ip_header->ip_src[3]);

	printf("\n\r IP Dest Address   = %d:%d:%d:%d",
			p_ip_header->ip_dst[0],
			p_ip_header->ip_dst[1],
			p_ip_header->ip_dst[2], p_ip_header->ip_dst[3]);
	puts("\n\r----------------------------------------\r");
}

/**
 * \brief Process the received ARP packet; change address and send it back.
 *
 * \param p_uc_data  The data to process.
 * \param ul_size The data size.
 */
static void emac_process_arp_packet(uint8_t *p_uc_data, uint32_t ul_size)
{
	uint32_t i;
	uint8_t ul_rc = EMAC_OK;

	p_ethernet_header_t p_eth = (p_ethernet_header_t) p_uc_data;
	p_arp_header_t p_arp = (p_arp_header_t) (p_uc_data + ETH_HEADER_SIZE);

	if (SWAP16(p_arp->ar_op) == ARP_REQUEST) {
		printf("-- IP  %d.%d.%d.%d\n\r",
				p_eth->et_dest[0], p_eth->et_dest[1],
				p_eth->et_dest[2], p_eth->et_dest[3]);

		printf("-- IP  %d.%d.%d.%d\n\r",
				p_eth->et_src[0], p_eth->et_src[1],
				p_eth->et_src[2], p_eth->et_src[3]);

		/* ARP reply operation */
		p_arp->ar_op = SWAP16(ARP_REPLY);

		/* Fill the destination address and source address */
		for (i = 0; i < 6; i++) {
			/* Swap ethernet destination address and ethernet source address */
			p_eth->et_dest[i] = p_eth->et_src[i];
			p_eth->et_src[i] = gs_uc_mac_address[i];
			p_arp->ar_tha[i] = p_arp->ar_sha[i];
			p_arp->ar_sha[i] = gs_uc_mac_address[i];
		}
		/* Swap the source IP address and the destination IP address */
		for (i = 0; i < 4; i++) {
			p_arp->ar_tpa[i] = p_arp->ar_spa[i];
			p_arp->ar_spa[i] = gs_uc_ip_address[i];
		}
		ul_rc = emac_dev_write(&gs_emac_dev, p_uc_data, ul_size, NULL);
		if (ul_rc != EMAC_OK) {
			printf("E: ARP Send - 0x%x\n\r", ul_rc);
		}
	}
}

/**
 * \brief Process the received IP packet; change address and send it back.
 *
 * \param p_uc_data  The data to process.
 * \param ul_size The data size.
 */
static void emac_process_ip_packet(uint8_t *p_uc_data, uint32_t ul_size)
{
	uint32_t i;
	uint32_t ul_icmp_len;
	int32_t ul_rc = EMAC_OK;

	/* avoid Cppcheck Warning */
	UNUSED(ul_size);

	p_ethernet_header_t p_eth = (p_ethernet_header_t) p_uc_data;
	p_ip_header_t p_ip_header = (p_ip_header_t) (p_uc_data + ETH_HEADER_SIZE);

	p_icmp_echo_header_t p_icmp_echo =
			(p_icmp_echo_header_t) ((int8_t *) p_ip_header +
			ETH_IP_HEADER_SIZE);
	printf("-- IP  %d.%d.%d.%d\n\r", p_eth->et_dest[0], p_eth->et_dest[1],
			p_eth->et_dest[2], p_eth->et_dest[3]);

	printf("-- IP  %d.%d.%d.%d\n\r",
			p_eth->et_src[0], p_eth->et_src[1], p_eth->et_src[2],
			p_eth->et_src[3]);
	switch (p_ip_header->ip_p) {
	case IP_PROT_ICMP:
		if (p_icmp_echo->type == ICMP_ECHO_REQUEST) {
			p_icmp_echo->type = ICMP_ECHO_REPLY;
			p_icmp_echo->code = 0;
			p_icmp_echo->cksum = 0;

			/* Checksum of the ICMP message */
			ul_icmp_len = (SWAP16(p_ip_header->ip_len) - ETH_IP_HEADER_SIZE);
			if (ul_icmp_len % 2) {
				*((uint8_t *) p_icmp_echo + ul_icmp_len) = 0;
				ul_icmp_len++;
			}
			ul_icmp_len = ul_icmp_len / sizeof(uint16_t);

			p_icmp_echo->cksum = SWAP16(
					emac_icmp_checksum((uint16_t *)p_icmp_echo, ul_icmp_len));
			/* Swap the IP destination  address and the IP source address */
			for (i = 0; i < 4; i++) {
				p_ip_header->ip_dst[i] =
						p_ip_header->ip_src[i];
				p_ip_header->ip_src[i] = gs_uc_ip_address[i];
			}
			/* Swap ethernet destination address and ethernet source address */
			for (i = 0; i < 6; i++) {
				/* Swap ethernet destination address and ethernet source address */
				p_eth->et_dest[i] = p_eth->et_src[i];
				p_eth->et_src[i] = gs_uc_mac_address[i];
			}
			/* Send the echo_reply */
			ul_rc = emac_dev_write(&gs_emac_dev, p_uc_data,
					SWAP16(p_ip_header->ip_len) + 14, NULL);
			if (ul_rc != EMAC_OK) {
				printf("E: ICMP Send - 0x%x\n\r", ul_rc);
			}
		}
		break;

	default:
		break;
	}
}

/**
 * \brief Process the received EMAC packet.
 *
 * \param p_uc_data  The data to process.
 * \param ul_size The data size.
 */
static void emac_process_eth_packet(uint8_t *p_uc_data, uint32_t ul_size)
{
	uint16_t us_pkt_format;

	p_ethernet_header_t p_eth = (p_ethernet_header_t) (p_uc_data);
	p_ip_header_t p_ip_header = (p_ip_header_t) (p_uc_data + ETH_HEADER_SIZE);
	ip_header_t ip_header;
	us_pkt_format = SWAP16(p_eth->et_protlen);

	switch (us_pkt_format) {
	/* ARP Packet format */
	case ETH_PROT_ARP:
		/* Process the ARP packet */
		emac_process_arp_packet(p_uc_data, ul_size);

		break;

	/* IP protocol frame */
	case ETH_PROT_IP:
		/* Backup the header */
		memcpy(&ip_header, p_ip_header, sizeof(ip_header_t));

		/* Process the IP packet */
		emac_process_ip_packet(p_uc_data, ul_size);

		/* Dump the IP header */
		emac_display_ip_packet(&ip_header, ul_size);
		break;

	default:
		printf("=== Default w_pkt_format= 0x%X===\n\r", us_pkt_format);
		break;
	}
}

/**
 *  \brief Configure UART console.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};
	
	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief EMAC interrupt handler.
 */
void EMAC_Handler(void)
{
	emac_handler(&gs_emac_dev);
}

/**
 *  \brief EMAC example entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint32_t ul_frm_size;
	volatile uint32_t ul_delay;
	emac_options_t emac_option;

	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	/* Initialize the console UART. */
	configure_console();

	puts(STRING_HEADER);

	/* Display MAC & IP settings */
	printf("-- MAC %x:%x:%x:%x:%x:%x\n\r",
			gs_uc_mac_address[0], gs_uc_mac_address[1], gs_uc_mac_address[2],
			gs_uc_mac_address[3], gs_uc_mac_address[4], gs_uc_mac_address[5]);

	printf("-- IP  %d.%d.%d.%d\n\r", gs_uc_ip_address[0], gs_uc_ip_address[1],
			gs_uc_ip_address[2], gs_uc_ip_address[3]);

	/* Reset PHY */
	rstc_set_external_reset(RSTC, 13); /* (2^(13+1))/32768 */
	rstc_reset_extern(RSTC);
	while (rstc_get_status(RSTC) & RSTC_SR_NRSTL) {
	};
	rstc_set_external_reset(RSTC, 0);  /* restore default */

	/* Wait for PHY to be ready (CAT811: Max400ms) */
	ul_delay = sysclk_get_cpu_hz() / 1000 / 3 * 400;
	while (ul_delay--);

	/* Enable EMAC clock */
	pmc_enable_periph_clk(ID_EMAC);

	/* Fill in EMAC options */
	emac_option.uc_copy_all_frame = 0;
	emac_option.uc_no_boardcast = 0;

	memcpy(emac_option.uc_mac_addr, gs_uc_mac_address, sizeof(gs_uc_mac_address));

	gs_emac_dev.p_hw = EMAC;

	/* Init EMAC driver structure */
	emac_dev_init(EMAC, &gs_emac_dev, &emac_option);

	/* Enable Interrupt */
	NVIC_EnableIRQ(EMAC_IRQn);

	/* Init MAC PHY driver */
	if (ethernet_phy_init(EMAC, BOARD_EMAC_PHY_ADDR, sysclk_get_cpu_hz())
					!= EMAC_OK) {
		puts("PHY Initialize ERROR!\r");
		return -1;
	}

	/* Auto Negotiate, work in RMII mode */
	if (ethernet_phy_auto_negotiate(EMAC, BOARD_EMAC_PHY_ADDR) != EMAC_OK) {

		puts("Auto Negotiate ERROR!\r");
		return -1;
	}

	/* Establish ethernet link */
	while (ethernet_phy_set_link(EMAC, BOARD_EMAC_PHY_ADDR, 1) != EMAC_OK) {
		puts("Set link ERROR!\r");
		return -1;
	}

	puts("Link detected. \r");

	while (1) {
		/* Process packets */
		if (EMAC_OK != emac_dev_read(&gs_emac_dev, (uint8_t *) gs_uc_eth_buffer,
						sizeof(gs_uc_eth_buffer), &ul_frm_size)) {
			continue;
		}

		if (ul_frm_size > 0) {
			/* Handle input frame */
			emac_process_eth_packet((uint8_t *) gs_uc_eth_buffer, ul_frm_size);
		}
	}
}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
