/**
 * \file
 *
 * \brief MAIN configuration.
 *
 * Copyright (c) 2017-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/** Wi-Fi Settings */
#define TEST_WLAN_SSID                  "Demo_AP"  /*Destination SSID */
#define TEST_WLAN_AUTH                  M2M_WIFI_SEC_WPA_PSK  /*Security Type*/
#define TEST_WLAN_PSK                   "password"  /* Password for SSID */
/*Server or Client IP settings*/
#define TEST_WINC_RECEIVE_BUFFER          1460    /*Receive Buffer for WINC1500*/
#define TEST_WINC_SERVER_PORT			  6666    /*WINC1500 Listen Port or destination port if UDP is used*/
#define TEST_WINC_SERVER_IP			      "255.255.255.255" /*WINC1500 Listen IP address*/
#define TEST_SSL_TCP_IP					  "192.168.1.122"   /*SSL or TCP IP address of the server*/
#define TEST_SSL_SERVER_PORT			  443				/*SSL server port number*/
#define TEST_TCP_SERVER_PORT			  6666              /*TCP server port number*/
/*Default Profile Settings*/
#define TX_PACKET_SIZE					  64				/*Packet size used in profiling*/
#define TX_DELAY_MS						  100				/*Delay between packets in TX profiling*/
#define DEFAULT_TX_POWER				  TX_PWR_HIGH		/*Default TX power mode in the test*/
#define DEFAULT_RX_POWER			      PWR_HIGH			/*Default RX sensitivity mode in the test*/
#define DEFAULT_DTIM_FLAG                 1
#define TEST_SSL_UPLOAD_SIZE			  1	                /*Number of time "TX_PACKET_SIZE" bytes are sent out*/

//Only one can be enabled at a time, probe on PB30 on SAMD21 Xplained Pro
#define AP_CONNECTION_TOGGLE              1 
#define TCP_CONNECTION_TOGGLE             0
#define TCP_UPLOAD_TOGGLE				  0

typedef struct{
	uint8_t			   dtim;
	uint16_t		   listen_interval;
	tenuPowerSaveModes ps_mode;
	tenuM2mTxPwrLevel  tx_pwr_mode;
	tenuM2mPwrMode	   rx_pwr_mode;
}low_power_test_param;

typedef enum{
	IDLE_STATE = 0,
	WIFI_CONNECTION_STATE,
	SOCKET_CONNECTION_STATE
}app_states;

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H_INCLUDED */
