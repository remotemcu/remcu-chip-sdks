/**
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

#include "lwip/api.h"
#include "iperf.h"
#include <string.h>

enum iperf_status
{
	E_WAITING = 0,
	E_CONNECTED,
	E_CLOSED
};

struct iperf_state {
	enum iperf_status status;
	struct client_hdr chdr;
	uint32_t flags;
};

uint8_t buffer[BUFSIZE];
struct iperf_state iperf;

struct iperf_stats stats;

static ip_addr_t udp_client_ip;
static uint32_t udp_client_port;
static uint32_t test_time;
static uint32_t test_tx;

static void iperf_udp_recv(struct netconn *conn)
{
	struct UDP_datagram *pkt;
	struct server_hdr *hdr;
	struct netbuf *nbuf = 0;
	struct netbuf *nbuf2 = 0;
	char *buf;
	char *buf2;
	u16_t buflen;
	int32_t datagramID;
	uint32_t done = 0;
	uint32_t started = 0;

	/* Read as much data as possible from the server. */
	while (!done && ERR_OK == netconn_recv(conn, &nbuf)) {

		/* Read packet iperf data. */
		netbuf_data(nbuf, (void**)&buf, &buflen);
		pkt = (void *)buf;
		datagramID = ntohl(pkt->id);
	
		if (datagramID >= 0) {
			/* Test is running. */
			if (started == 0) {
				/* First packet received, print IP address and initialize stats. */
				ip_addr_t *addr;
				addr = netbuf_fromaddr(nbuf);
				udp_client_port = netbuf_fromport(nbuf);
				udp_client_ip = *addr;
				osprintf("[  1] local 127.0.0.1 port 5001 connected with %u.%u.%u.%u port %ld\r\n",
						(addr->addr & 0xFF), (addr->addr & 0xFF00) >> 8,
						(addr->addr & 0xFF0000) >> 16, (addr->addr & 0xFF000000) >> 24,
						udp_client_port);
				stats.udp_rx_start_sec = ntohl(pkt->tv_sec);
				stats.udp_rx_start_usec = ntohl(pkt->tv_usec);
				started = 1;
				test_tx = 0;
			}
			/* Update stats. */
			if (stats.udp_rx_seq != (uint32_t) datagramID) {
				stats.udp_rx_lost += (uint32_t) datagramID - stats.udp_rx_seq;
				stats.udp_rx_seq = datagramID + 1;
				stats.udp_rx_outorder += 1;
			}
			else {
				stats.udp_rx_total_pkt += 1;
				stats.udp_rx_total_size += buflen;
				stats.udp_rx_seq += 1;
			}
		}
		else {
			/* UDP test is now over. */
			if (started) {
				pkt->id = htonl(datagramID);
				stats.udp_rx_end_sec = ntohl(pkt->tv_sec);
				stats.udp_rx_end_usec = ntohl(pkt->tv_usec);
				test_time = stats.udp_rx_end_sec - stats.udp_rx_start_sec;

				/* Copy packet and send report back. */
				nbuf2 = netbuf_new();
				buf2 = netbuf_alloc(nbuf2, buflen);
				memcpy(buf2, buf, buflen);
				netbuf_delete(nbuf);
				nbuf = nbuf2;
				pkt = (void *)buf2;
				hdr = (struct server_hdr *)(pkt + 1);
				if (ntohl(hdr->flags) & HEADER_VERSION1) {
					test_tx = 1;
				}
				hdr->flags        = htonl(HEADER_VERSION1);
				hdr->total_len1   = htonl(0);
				hdr->total_len2   = htonl(stats.udp_rx_total_size);
				if(stats.udp_rx_end_usec > stats.udp_rx_start_usec){
					hdr->stop_sec     = htonl(stats.udp_rx_end_sec - stats.udp_rx_start_sec);
					hdr->stop_usec    = htonl(stats.udp_rx_end_usec - stats.udp_rx_start_usec);
				}else{ // take carry from sec for usec subtraction
					hdr->stop_sec     = htonl((stats.udp_rx_end_sec - 1) - stats.udp_rx_start_sec);
					hdr->stop_usec    = htonl( (1000000 + stats.udp_rx_end_usec) - stats.udp_rx_start_usec);
				}
				hdr->error_cnt    = htonl(stats.udp_rx_lost);
				hdr->outorder_cnt = htonl(stats.udp_rx_outorder);
				hdr->datagrams    = htonl(stats.udp_rx_seq);
				hdr->jitter1      = htonl(0); // TODO: jitter not computed!
				hdr->jitter2      = htonl(0); // TODO: jitter not computed!

				/* Send report to client. */
				netconn_sendto(conn, nbuf2, &udp_client_ip, udp_client_port);
				osprintf("========= UDP receive status =========\r\n");
				osprintf("test run for %ld seconds\r\n",test_time);
				osprintf("%ld bytes(%f MB) received\r\n",stats.udp_rx_total_size, (float)stats.udp_rx_total_size/(float)(1024*1024));
				osprintf("%ld datagrams lost out of %ld datagrams\r\n",stats.udp_rx_lost, stats.udp_rx_seq);
				osprintf("%ld datagrams received out of order\r\n",stats.udp_rx_outorder);
				osprintf("======================================\r\n");
				vTaskDelay(1);
				done = 1;
			}
		}

		/* Free input resource. */
		netbuf_delete(nbuf);
	}
}

void print_test(const char* fn, uint8_t* ptr, int size);

static void iperf_udp_send(struct netconn *conn)
{
	struct UDP_datagram *pkt;
	struct server_hdr *hdr;
	struct netbuf *nbuf = 0;
	char *buf;
	int32_t datagramID = 0;
	uint32_t start_time = 0;
	
	/* Is -r option enabled? */
	if (test_tx) {
		osprintf("------------------------------------------------------------\r\n");
		osprintf("Client connecting to %u.%u.%u.%u, UDP port 5001\r\n",
				(udp_client_ip.addr & 0xFF), (udp_client_ip.addr & 0xFF00) >> 8,
				(udp_client_ip.addr & 0xFF0000) >> 16, (udp_client_ip.addr & 0xFF000000) >> 24);
		osprintf("Sending %d byte datagrams\r\n", IPERF_WIFI_UDP_BUFFER_SIZE);
		osprintf("------------------------------------------------------------\r\n");
		osprintf("[  1] local 127.0.0.1 port ??? connected with %u.%u.%u.%u port 5001\r\n",
				(udp_client_ip.addr & 0xFF), (udp_client_ip.addr & 0xFF00) >> 8,
				(udp_client_ip.addr & 0xFF0000) >> 16, (udp_client_ip.addr & 0xFF000000) >> 24);
				
		/* Reset packet header content. */
		pkt = (void *)buffer;
		memset(pkt, 0, sizeof(struct UDP_datagram));
		hdr = (struct server_hdr *)(pkt + 1);
		memset(hdr, 0, sizeof(struct server_hdr));
		hdr->flags        = htonl(HEADER_VERSION1);
		hdr->total_len1   = htonl(0);
		hdr->total_len2   = htonl(IPERF_WIFI_UDP_BUFFER_SIZE);

		start_time = xTaskGetTickCount();
		test_time = test_time * 1000; /* Convert to ticks. */

		while (1) {
			/* Send test packet with incremented ID. */
			if (xTaskGetTickCount() - start_time < test_time) {
				nbuf = netbuf_new();
				buf = netbuf_alloc(nbuf, IPERF_WIFI_UDP_BUFFER_SIZE);
				memcpy(buf, buffer, IPERF_WIFI_UDP_BUFFER_SIZE);
				pkt->id = ntohl(datagramID++);
				netconn_sendto(conn, nbuf, &udp_client_ip, IPERF_PORT);
				//print_test(__FUNCTION__, nbuf->p->payload, nbuf->p->len);
				netbuf_delete(nbuf);
			}
			/* Send test end with neg ID 10 times. */
			else {
				pkt->id = ntohl(-datagramID);
				for (uint32_t i = 0; i < 10; ++i) {
					nbuf = netbuf_new();
					buf = netbuf_alloc(nbuf, IPERF_WIFI_UDP_BUFFER_SIZE);
					memcpy(buf, buffer, IPERF_WIFI_UDP_BUFFER_SIZE);
					netconn_sendto(conn, nbuf, &udp_client_ip, IPERF_PORT);
					netbuf_delete(nbuf);
				}
				osprintf("========== UDP send status =========\r\n");
				osprintf("test run for %ld seconds\r\n", test_time / 1000);
				osprintf("sent %ld datagrams\r\n", datagramID);
				osprintf("sent %ld bytes(%f MB)\r\n", IPERF_WIFI_UDP_BUFFER_SIZE * datagramID , (float)(IPERF_WIFI_UDP_BUFFER_SIZE * datagramID)/(float)(1024 * 1024));
				osprintf("====================================\r\n");	
				break;
			}
		}
	}
}

/**
 * \brief iperf function using UDP server.
 */
void iperf_udp_server()
{
	struct netconn *udp_socket;
	uint32_t i, j;

	/* Fill send buffer with pattern. */
	for (i = 0, j = 0; i < BUFSIZE; ++i, ++j) {
		if (j > 9)
		j = 0;
		buffer[i] = '0' + j;
	}
	/* Create server socket. */
	if ((udp_socket = netconn_new(NETCONN_UDP)) == NULL) {
		osprintf("iperf_udp_task: could not create UDP socket!\n");
		return;
	}
	if (netconn_bind(udp_socket, NULL, IPERF_PORT) != ERR_OK) {
		osprintf("iperf_udp_task: could not bind TCP socket!\n");
		goto EXIT;
	}

	/* Clear UDP stats. */
	memset(&stats, 0, sizeof(struct iperf_stats));

	/* Receive as long as server is sending. */
	iperf_udp_recv(udp_socket);

	/* Send if required by client. */
	iperf_udp_send(udp_socket);
	vTaskDelay(100);  //wait for send completion	
	osprintf("[  1] done\r\n");
EXIT:	
	netconn_delete(udp_socket);
}

static void iperf_tcp_recv(struct netconn *conn)
{
	struct netbuf *inbuf = 0;
	char *buf;
	u16_t buflen;
	uint32_t received_bytes = 0;

	/* Read as much data as possible from the server. */
	while (ERR_OK == netconn_recv(conn, &inbuf)) {

		if (iperf.status == E_WAITING) {
			iperf.status = E_CONNECTED;

			/* Read data from netbuf to find iperf options. */
			netbuf_data(inbuf, (void**)&buf, &buflen);
			memcpy(&iperf.chdr, buf, sizeof(struct client_hdr));

			iperf.chdr.numThreads = ntohl(iperf.chdr.numThreads);
			iperf.chdr.mPort = ntohl(iperf.chdr.mPort);
			iperf.chdr.bufferlen = ntohl(iperf.chdr.bufferlen);
			iperf.chdr.mWinBand = ntohl(iperf.chdr.mWinBand);
			iperf.chdr.mAmount = -ntohl(iperf.chdr.mAmount) / 100 * 1000;

			iperf.flags = ntohl(iperf.chdr.flags);
			if (iperf.flags & RUN_NOW) {
				// --dualtest not implemented
				osprintf("Unsupported options -d, closing connection...\n");
				netbuf_delete(inbuf);
				break;
			}

		}
		received_bytes += inbuf->p->tot_len;
		/* Free input resource. */
		netbuf_delete(inbuf);
	}
	osprintf("========  TCP receive status =======\r\n");
	osprintf("Received data for %ld seconds\r\n", (uint32_t)iperf.chdr.mAmount/1000);
	osprintf("Received %ld bytes(%f MB)\r\n", received_bytes , (float)received_bytes/(float)(1024 * 1024));
	osprintf("====================================\r\n");
	/* Delete connection. */
	netconn_delete(conn);
	iperf.status = E_CLOSED;
}

static void iperf_tcp_send(ip_addr_t *local_ip, ip_addr_t *remote_ip)
{
	struct netconn *conn = netconn_new(NETCONN_TCP);
	uint32_t start_time = 0;
	uint32_t data_count = 0;
	osprintf("------------------------------------------------------------\r\n");
	osprintf("Client connecting to %s, TCP port 5001\r\n", ipaddr_ntoa(remote_ip));
	osprintf("TCP window size: %d Bytes\r\n", TCP_SND_BUF);
	osprintf("------------------------------------------------------------\r\n");

	if (ERR_OK != netconn_bind(conn, local_ip, 0)) {
		osprintf("iperf_tcp_send: bind failed\n");
		netconn_delete(conn);
		return;
	}
	if (ERR_OK != netconn_connect(conn, remote_ip, IPERF_PORT)) {
		osprintf("iperf_tcp_send: connect failed\n");
		netconn_delete(conn);
		return;
	}

	start_time = xTaskGetTickCount();

	/* Send as much data as possible to the server. */
	while (xTaskGetTickCount() - start_time < (uint32_t)iperf.chdr.mAmount) {
		if (ERR_OK != netconn_write(conn, buffer, BUFSIZE, NETCONN_NOCOPY)) {
			osprintf("iperf_tcp_send: write failed\n");
			break;
		}
		data_count++;
	}
	osprintf("========= TCP send status =========\r\n");
	osprintf("Sent data for %ld seconds\r\n", (uint32_t)iperf.chdr.mAmount/1000);
	osprintf("sent %ld bytes(%f MB)\r\n", BUFSIZE * data_count , (float)(BUFSIZE * data_count)/(float)(1024 * 1024));
	osprintf("===================================\r\n");
	/* Close connection. */
	netconn_close(conn);
	netconn_delete(conn);
	iperf.status = E_CLOSED;
}

/**
 * \brief iperf function using TCP server mode
 */
void iperf_tcp_server()
{
	struct netconn *tcp_socket;
	ip_addr_t local_ip;
	ip_addr_t remote_ip;
	u16_t port;
	uint32_t i, j;

	/* Fill send buffer with pattern. */
	for (i = 0, j = 0; i < BUFSIZE; ++i, ++j) {
		if (j > 9)
		j = 0;
		buffer[i] = '0' + j;
	}

	/* Create server socket. */
	if ((tcp_socket = netconn_new(NETCONN_TCP)) == NULL) {
		osprintf("iperf_tcp_task: could not create TCP socket!\n");
		return;
	}
	if (netconn_bind(tcp_socket, NULL, IPERF_PORT) != ERR_OK) {
		osprintf("iperf_tcp_task: could not bind TCP socket!\n");
		goto EXIT;
	}
	if (netconn_listen(tcp_socket) != ERR_OK) {
		osprintf("iperf_tcp_task: could not enter listen state for TCP socket!\n");
		goto EXIT;
	}

	osprintf("------------------------------------------------------------\r\n");
	osprintf("Server listening on TCP/UDP port 5001\r\n");
	osprintf("TCP window size: %d Bytes\r\n", TCP_WND);
	osprintf("------------------------------------------------------------\r\n");

	struct netconn *conn = 0;
	iperf.status = E_WAITING;

	while (netconn_accept(tcp_socket, &conn) != ERR_OK) {
		vTaskDelay(10);
	}

	if (conn) {
		/* Client connected print output. */
		netconn_getaddr(conn, &local_ip, &port, 1);
		osprintf("[  0] local %s port %d ", ipaddr_ntoa(&local_ip), port);
		netconn_getaddr(conn, &remote_ip, &port, 0);
		osprintf("connected with %s port %d\r\n", ipaddr_ntoa(&remote_ip), port);

		/* Test connection for receiving. */
		iperf_tcp_recv(conn);

		/* Test connection for sending. */
		if (iperf.flags & HEADER_VERSION1) {
			iperf_tcp_send(&local_ip, &remote_ip);
		}

		osprintf("[  0] done\r\n");
	}
EXIT:
	netconn_delete(tcp_socket);
}
