/**
 *
 * \file
 *
 * \brief AP Task.
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
#include "FreeRTOS.h"
#include "lwip/api.h"
#include "lwip/tcpip.h"
#include "osprintf.h"
#include "ap.h"
#include "sta.h"
#include "driver/include/m2m_types.h"
#include <string.h>
#include <stdio.h>

/** Using broadcast address for simplicity. */
#define HTTP_PORT						(80)

/** Delay on close error. */
#define webSHORT_DELAY					(10)

/*! Standard GET response. */
#define webHTTP_OK	"HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n"

/*! Format of the dynamic page that is returned on each connection. */
#define webHTML_START \
"<html>\
<head>\
</head>\
<BODY onLoad=\"window.setTimeout(&quot;location.href='index.html'&quot;,3000)\" bgcolor=\"#FFFFFF\" text=\"#2477E6\">\
\r\n - Atmel WILC3000 STA/AP and BT Weather Demo - \
<p><pre><br>System Information:<br>Page Hits = "

#define webHTML_END \
"\r\n</pre>\
\r\n</font></BODY>\
</html>"

/** Webpage hit counter. */
static uint32_t webpage_hit = 0;

/** Placeholder to convert from int to ASCII. */
static char cwebpage_hit[11];

/** Webpage to send to connected STA. */
static char webpage[1024];

extern char report[];
extern uint32_t sta_connected;
extern tstrM2MAPAssocInfo strApAssocInfo;

/**
 * \brief Core HTTP server function processing the request.
 *
 * \param pvParameters Netconn socket to use.
 */
static void http_request(struct netconn *conn)
{
	struct netbuf *rx_buf;
	char *str;
	static char tempWebpage[1024];
	uint16_t len;
	uint32_t i;

	while (netconn_recv(conn, &rx_buf) != ERR_OK) {
		vTaskDelay(webSHORT_DELAY);
	}

	if (rx_buf != NULL) {
		/* Where is the data? */
		netbuf_data(rx_buf, (void *)&str, &len);

		/* Is this a GET?  We don't handle anything else. */
		if ((NULL != str) && (!strncmp(str, "GET", 3 ))) {
			/* Write out the HTTP OK header. */
			netconn_write(conn, webHTTP_OK, (uint32_t)strlen(webHTTP_OK), NETCONN_COPY);

			/* Generate page header. */
			strcpy(webpage, webHTML_START);

			/* Append stats and task info. */
			webpage_hit++;
			sprintf(cwebpage_hit, "%d", (int)webpage_hit);
			strcat(webpage, cwebpage_hit);
			sprintf(cwebpage_hit, "%d", (int)strApAssocInfo.u8NoConnSta);
			strcat(webpage, "<br>Nb STA Connected = ");
			strcat(webpage, cwebpage_hit);
			if(strApAssocInfo.u8NoConnSta > 0) {
				strcat(webpage, "<table border=\"1\" bordercolor=\"#2477E6\" style=\"border-collapse:collapse;\"><tr><th>BSSID</th><th>RSSI</th></tr>");
				strcpy(tempWebpage, webpage);	
				for(i=0; i<strApAssocInfo.u8NoConnSta; i++) {
					sprintf(webpage, "%s <tr><td>%02x:%02x:%02x:%02x:%02x:%02x</td><td> %d</td></tr>",
						tempWebpage, 
						strApAssocInfo.astrM2MAssocEntryInfo[i].BSSID[0],
						strApAssocInfo.astrM2MAssocEntryInfo[i].BSSID[1],
						strApAssocInfo.astrM2MAssocEntryInfo[i].BSSID[2],
						strApAssocInfo.astrM2MAssocEntryInfo[i].BSSID[3],
						strApAssocInfo.astrM2MAssocEntryInfo[i].BSSID[4],
						strApAssocInfo.astrM2MAssocEntryInfo[i].BSSID[5],
						strApAssocInfo.astrM2MAssocEntryInfo[i].s8RSSI);
					}
				strcat(webpage, "</table>");
			}
			strcat(webpage, "<p><pre><br>Task          State  Priority  Stack	#<br>************************************************<br>");
			vTaskList((signed char *)webpage + strlen((char *)webpage));
			strcat(webpage, "<p><pre><p><pre><br><br>Weather Bulletin (via AP ");
			strcat(webpage, STA_WLAN_SSID);
			strcat(webpage, ")<br>************************************************<br>");
			strcat(webpage, report);

			/* ... Finally the page footer. */
			strcat(webpage, webHTML_END);
			if(strlen(webpage) > sizeof(webpage))
				osprint("ERROR: Webpage buffer exceeded maximum\r\n");

			/* Write out the dynamically generated page. */
			netconn_write(conn, webpage, strlen(webpage), NETCONN_COPY);
		}
		netbuf_delete(rx_buf);
	}

	netconn_close(conn);
	netconn_delete(conn);
}

/**
 * \brief AP task main function.
 */
void ap_task(void *argument)
{
	struct netconn *conn, *newconn;

	/* Just to avoid compiler warnings. */
	UNUSED(argument);
	
	/* Create a new TCP connection handle */
	conn = netconn_new(NETCONN_TCP);
	if (conn == NULL) {
		osprintf("ap_task: failed to create socket!\n");

		/* Delete the calling task. */
		vTaskDelete(NULL);
	}

	/* Bind to port 80 (HTTP) with default IP address. */
	netconn_bind(conn, NULL, HTTP_PORT);

	/* Put the connection into LISTEN state. */
	netconn_listen(conn);

	/* Handle HTTP requests. */
	while (1) {
		while (netconn_accept(conn, &newconn) != ERR_OK) {
			vTaskDelay( webSHORT_DELAY );
		}

		if (newconn != NULL) {
			http_request(newconn);
		}
	}
}
