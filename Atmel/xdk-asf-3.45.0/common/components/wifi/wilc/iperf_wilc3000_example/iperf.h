/**
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
#ifndef IPERF_H_INCLUDED
#define IPERF_H_INCLUDED

/** Wi-Fi Settings */
#define MAIN_WLAN_SSID        "DEMO_AP" /* < Destination SSID */
#define MAIN_WLAN_AUTH        M2M_WIFI_SEC_WPA_PSK /* < Security manner */
#define MAIN_WLAN_PSK         "12345678" /* < Password for Destination SSID */

#define WEP_KEY_INDEX            M2M_WIFI_WEP_KEY_INDEX_1
#define WEP_KEY                  "1234567890" //"01234567890123456789abcdef" /**< 10 digit or 26 digit key */
#define WEP_KEY_SIZE             sizeof(WEP_KEY)
#define WEP_AUTH_TYPE            WEP_ANY
#define WEP_CONN_PARAM           {WEP_KEY_INDEX, WEP_KEY_SIZE, WEP_KEY, WEP_AUTH_TYPE}

void iperf_tcp_task(void *argument);
void iperf_tcp_client_task(void *argument);
void iperf_udp_task(void *argument);

#define IPERF_WIFI_M2M_TX_TIME				(9999)

#define IPERF_WIFI_SERVER_PORT			    (5001)
#define IPERF_WIFI_TCP_BUFFER_SIZE			(1400)
#define IPERF_WIFI_UDP_BUFFER_SIZE			(1400)
#define SERVER_IP_ADDRESS					"192.168.1.102"
#define HEADER_VERSION1						0x80000000
#define UDP_RATE							40 * 1024 * 1024 // rate = 40 Mega
#define IPERF_SERVER_PORT					5001
#define IPERF_CLIENT_PORT					5001
#define NUM_THREADS							1
#define TEST_TIME							1000 // 10 sec

/** iPerf Settings */
#define HEADER_VERSION1						0x80000000
#define RUN_NOW								0x00000001

struct UDP_datagram {
	int32_t id;
	uint32_t tv_sec;
	uint32_t tv_usec;
};

/***************** Application types *******************/
#define AP_STA_CONCURRENCY  
/* AP and STA Concurrency - standard default configuration */

//#define P2P_AP_CONCURRENCY
//#define P2P_STA_CONCURRENCY
//#define STA_ONLY
//#define AP_ONLY
//#define P2P_ONLY


/***************** Antenna Selection/Diversity Testing *******************/

//#define MAC_ANTENNA_DIVERSITY

#ifdef MAC_ANTENNA_DIVERSITY

/* Antenna Switch mode - {ANTENNA1, ANTENNA2 or DIVERSITY} */
#define ANT_MODE (ANTENNA2)

/* 
 * Antenna GPIO ctrl - {ANT_SWTCH_GPIO_SINLGE, ANT_SWTCH_GPIO_DUAL
 * or ANT_SWTCH_GPIO_NONE} 
 */
#define ANT_SWTCH_GPIO_CTRL_MODE (ANT_SWTCH_GPIO_DUAL)

/* Antenna GPIO configuration */
#define ANTENNA_GPIO_NUM_1	(4)
#define ANTENNA_GPIO_NUM_2	(20)

#endif //MAC_ANTENNA_DIVERSITY
/*************************************************************************/

struct client_hdr {
    /*
     * flags is a bitmap for different options
     * the most significant bits are for determining
     * which information is available. So 1.7 uses
     * 0x80000000 and the next time information is added
     * the 1.7 bit will be set and 0x40000000 will be
     * set signifying additional information. If no
     * information bits are set then the header is ignored.
     * The lowest order diferentiates between dualtest and
     * tradeoff modes, wheither the speaker needs to start
     * immediately or after the audience finishes.
     */
    int32_t flags;
    int32_t numThreads;
    int32_t mPort;
    int32_t bufferlen;
    int32_t mWinBand;
    int32_t mAmount;
};

struct server_hdr {
    /*
     * flags is a bitmap for different options
     * the most significant bits are for determining
     * which information is available. So 1.7 uses
     * 0x80000000 and the next time information is added
     * the 1.7 bit will be set and 0x40000000 will be
     * set signifying additional information. If no 
     * information bits are set then the header is ignored.
     */
    int32_t flags;
    int32_t total_len1;
    int32_t total_len2;
    int32_t stop_sec;
    int32_t stop_usec;
    int32_t error_cnt;
    int32_t outorder_cnt;
    int32_t datagrams;
    int32_t jitter1;
    int32_t jitter2;
};

struct iperf_stats {
	uint32_t udp_rx_total_size;
	uint32_t udp_rx_total_pkt;
	uint32_t udp_rx_seq;
	uint32_t udp_rx_lost;
	uint32_t udp_rx_outorder;
	uint32_t udp_rx_start_sec;
	uint32_t udp_rx_start_usec;
	uint32_t udp_rx_end_sec;
	uint32_t udp_rx_end_usec;
};

#define rMillion 1000000

#define TimeDifference( left, right ) (left.tv_sec  - right.tv_sec) +   \
        (left.tv_usec - right.tv_usec) / ((double) rMillion)

#define TimeAdd( left, right )  do {                                    \
                                    left.tv_usec += right.tv_usec;      \
                                    if ( left.tv_usec > rMillion ) {    \
                                        left.tv_usec -= rMillion;       \
                                        left.tv_sec++;                  \
                                    }                                   \
                                    left.tv_sec += right.tv_sec;        \
                                } while ( 0 )

#endif // IPERF_H_INCLUDED
