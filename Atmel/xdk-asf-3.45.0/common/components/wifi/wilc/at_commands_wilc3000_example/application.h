/**
 * \file
 *
 * \brief application configuration.
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

#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define MAIN_WIFI_M2M_BUFFER_SIZE		100
/** tcp MAX packet count */
#define MAIN_WIFI_M2M_PACKET_COUNT		1
#define MAIN_WIFI_M2M_PRODUCT_NAME		"WILC1000 : THE TEST MESSAGE"
#define MON_MODE_MAX_PKT_COUNT			700

void udp_server(void);
void udp_client(void);
void tcp_server(void);
void tcp_client(void);
void http_connection(char *host_name, unsigned short port);

void wilc_task_1(void *argument);

#ifdef __cplusplus
}
#endif

#endif /* APPLICATION_H_INCLUDED */
