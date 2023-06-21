/**
 * \file
 *
 * \brief Provision AP with BLE example.
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

/** \mainpage
 * \section intro Introduction
 * This example demonstrates how to provision Wi-Fi via BLE using the WINC3400
 * Wi-Fi/BLE module. <br>
 * It uses the following hardware:
 * - SAM Xplained Pro.
 * - the WIN3400 module on EXT1.
 * - thirdparty Android device.
 *
 * \section files Main Files
 * - main21.c : Initialize the SAM board and perform BLE provisioning.
 *
 * \section usage Usage
 * -# To connect the SAM board to the internet Access Point over Wi-Fi, the user must
 * -# provide credentials (SSID and passphrase) over BLE. As a first step, it is required
 * -# that the user install the Atmel BLE provision application available in the doc folder
 * -# (Atmel_BLE_prov.apk) on an Android device.
 * -# Then, power up the SAM board and run the Android application: perform a scan, select
 * -# an SSID and enter the passphrase.
 * -# Finally, press connect and enter the PIN code defined in CONF_BLE_PIN.
 *
 * -# Build the program and download it into the board.
 * -# On the computer, open and configure a terminal application as the follows.
 * \code
 *    Baud Rate : 115200
 *    Data : 8bit
 *    Parity bit : none
 *    Stop bit : 1bit
 *    Flow control : none
 * \endcode
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 * \code
 *    -- WINC3400 Provision AP with BLE example --
 *    -- SAMXXX_XPLAINED_PRO --
 *    -- Compiled: xxx  x xxxx xx:xx:xx --
 *    
 *    main: started WiFi.
 *    (APP)(INFO)Chip ID 3400d1
 *    (APP)(INFO)Curr driver ver: x.x.x
 *    (APP)(INFO)Curr driver HIF Level: (2) X.x
 *    (APP)(INFO)Fw HIF: 8101
 *    (APP)(INFO)Firmware HIF (2) : x.x
 *    (APP)(INFO)Firmware ver   : x.x.x
 *    (APP)(INFO)Firmware Build Apr xx 20xx Time xx:xx:xx
 *    (APP)(INFO)OTP MAC
 *    (APP)(INFO)MAC Address: xx:xx:xx:xx:xx:xx
 *    (APP)(INFO)M2M_NO_PS
 *    (APP)(INFO)POWER SAVE 0
 *    (APP)(INFO)Reset provision data
 *    (APP)(INFO)BLE provisioning started
 *    (APP)(INFO)Provisioned AP:
 *    (APP)(INFO)Sec type   : 2
 *    (APP)(INFO)SSID       : DEMO_AP
 *    (APP)(INFO)Passphrase : 12345678
 *    Provisioning data received
 *    (APP)(INFO)Retrieving ssid...
 *    (APP)(INFO)   have valid ssid
 *    WiFi Connect: using provisioned AP
 *    Wifi State :: CONNECTED ::
 *    DHCP IP Address :: 192.168.1.31 ::
 *    WiFi Connected
 *    Provisioning Completed
 * \endcode
 *
 * \section compinfo Compilation Information
 * This software was written for the GNU GCC compiler using Atmel Studio 6.2
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com">Microchip</A>.\n
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>
#include "bsp/include/nm_bsp_samd21_app.h"
#include "driver/include/m2m_wifi.h"
#include "driver/include/m2m_periph.h"
#include "main21.h"
#include "m2m_ble.h"
#include "at_ble_api.h"
#include "wifi_prov.h"

#include "utils/ble_utils.h"

#define STRING_HEADER "-- Wifi BLE Provisioning demo --\r\n" \
                      "-- "BOARD_NAME" --\r\n" \
                      "-- Compiled: "__DATE__" "__TIME__" --\r\n"

#define APP_STATE_IDLE								0
#define APP_STATE_WAITING_FOR_WIFI_DISCONNECTION	1
#define APP_STATE_PROVISIONING						2
#define APP_STATE_WAITING_FOR_WIFI_CONNECTION		3
#define APP_STATE_COMPLETED							4

static volatile uint8 gu8WiFiConnectionState = M2M_WIFI_UNDEF;
/*static volatile uint8 gu8BtnEvent;*/
static uint8 gu8ScanIndex;
static at_ble_event_parameter_t gu8BleParam __aligned(4);

static void app_wifi_init(tpfAppWifiCb wifi_cb_func)
{
	tstrWifiInitParam param;
	sint8 ret;
	uint8 mac_addr[6];
	uint8 u8IsMacAddrValid;
	sint8 deviceName[] = M2M_DEVICE_NAME;

#ifdef _STATIC_PS_
	nm_bsp_register_wake_isr(wake_cb, PS_SLEEP_TIME_MS);
#endif
	
	m2m_memset((uint8*)&param, 0, sizeof(param));
	param.pfAppWifiCb = wifi_cb_func;
#ifdef ETH_MODE
	param.strEthInitParam.pfAppEthCb = ethernet_demo_cb;
	param.strEthInitParam.au8ethRcvBuf = gau8ethRcvBuf;
	param.strEthInitParam.u16ethRcvBufSize = sizeof(gau8ethRcvBuf);
#endif
	ret = m2m_ble_wifi_init(&param);

	if (M2M_SUCCESS != ret)
	{
		M2M_ERR("Driver Init Failed <%d>\n",ret);
		M2M_ERR("Reseting\n");
		// Catastrophe - problem with booting. Nothing but to try and reset
		system_reset();

		while (1)
		{
		}
	}
	
	m2m_wifi_get_otp_mac_address(mac_addr, &u8IsMacAddrValid);
	if (!u8IsMacAddrValid) {
		uint8 DEFAULT_MAC[] = MAC_ADDRESS;
		M2M_INFO("Default MAC\n");
		m2m_wifi_set_mac_address(DEFAULT_MAC);
	} else {
		M2M_INFO("OTP MAC\n");
	}
	m2m_wifi_get_mac_address(mac_addr);
	M2M_INFO("MAC Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
	         mac_addr[0],mac_addr[1],mac_addr[2],
	         mac_addr[3],mac_addr[4],mac_addr[5]);
	

	/* Name must be in the format WINC3400_00:00 */
	{
		#define HEX2ASCII(x) (((x)>=10)? (((x)-10)+'A') : ((x)+'0'))

		uint16 len;
		len = m2m_strlen((uint8_t *) deviceName);
		if (len >= 5) {
			deviceName[len-1] = HEX2ASCII((mac_addr[5] >> 0) & 0x0f);
			deviceName[len-2] = HEX2ASCII((mac_addr[5] >> 4) & 0x0f);
			deviceName[len-4] = HEX2ASCII((mac_addr[4] >> 0) & 0x0f);
			deviceName[len-5] = HEX2ASCII((mac_addr[4] >> 4) & 0x0f);
		}
	}
	m2m_wifi_set_device_name((uint8*)deviceName, (uint8)m2m_strlen((uint8*)deviceName));

#ifdef _DYNAMIC_PS_
	{
		tstrM2mLsnInt strM2mLsnInt;
		M2M_INFO("M2M_PS_DEEP_AUTOMATIC\n");
		m2m_wifi_set_sleep_mode(M2M_PS_DEEP_AUTOMATIC, 1);
		strM2mLsnInt.u16LsnInt = M2M_LISTEN_INTERVAL;
		m2m_wifi_set_lsn_int(&strM2mLsnInt);
	}
#elif (defined _STATIC_PS_)
	M2M_INFO("M2M_PS_MANUAL\n");
	m2m_wifi_set_sleep_mode(M2M_PS_MANUAL, 1);
#else
	M2M_INFO("M2M_NO_PS\n");
	m2m_wifi_set_sleep_mode(M2M_NO_PS, 1);
#endif
}

static void timer_cb(void)
{
	printf(".");
}

static void app_wifi_handle_event(uint8 u8MsgType, void * pvMsg)
{
	if (u8MsgType == M2M_WIFI_RESP_CON_STATE_CHANGED){
		tstrM2mWifiStateChanged *pstrWifiState = (tstrM2mWifiStateChanged*) pvMsg;

		printf("\r\nWifi State :: %s ::\r\n", pstrWifiState->u8CurrState ? "CONNECTED" : "DISCONNECTED");
		if(pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED){
			gu8WiFiConnectionState = M2M_WIFI_DISCONNECTED;
		}
	}
	else if (u8MsgType == M2M_WIFI_REQ_DHCP_CONF){
		tstrM2MIPConfig* pstrM2MIpConfig = (tstrM2MIPConfig*) pvMsg;
		uint8 *pu8IPAddress = (uint8*) &pstrM2MIpConfig->u32StaticIP;
		
		printf("DHCP IP Address :: %u.%u.%u.%u ::\r\n",
			pu8IPAddress[0], pu8IPAddress[1], pu8IPAddress[2], pu8IPAddress[3]);
		printf("WiFi Connected\r\n");

		gu8WiFiConnectionState = M2M_WIFI_CONNECTED;
	
	}
	else if (u8MsgType == M2M_WIFI_RESP_SCAN_DONE){
		tstrM2mScanDone *pstrInfo = (tstrM2mScanDone*) pvMsg;

		if (gu8WiFiConnectionState != M2M_WIFI_CONNECTED){
			gu8ScanIndex = 0;
			
			if (pstrInfo->u8NumofCh >= 1){
				m2m_wifi_req_scan_result(gu8ScanIndex);
				gu8ScanIndex++;
			}
		}
	}
	else if (u8MsgType == M2M_WIFI_RESP_SCAN_RESULT){
		uint8 u8NumFoundAPs = m2m_wifi_get_num_ap_found();

		if (gu8WiFiConnectionState != M2M_WIFI_CONNECTED){
			tstrM2mWifiscanResult *pstrScanResult = (tstrM2mWifiscanResult*) pvMsg;

			ble_prov_scan_result(pstrScanResult, u8NumFoundAPs-gu8ScanIndex);
			if(gu8ScanIndex < u8NumFoundAPs){
				m2m_wifi_req_scan_result(gu8ScanIndex);
				gu8ScanIndex++;
			}
		}
	} 
}

// This is an example of using onchip_profile, ble_prov API.
static void app_ble_wifi_provisioning(void) 
{
	uint8_t app_state = APP_STATE_IDLE;
	uint8_t wifi_con_state = M2M_WIFI_UNDEF;
	/*uint8_t btn_event;*/
	at_ble_events_t ble_event;

	// Initialize BLE stack on 3400.
	m2m_ble_init();
	m2m_wifi_req_unrestrict_ble();
	ble_prov_init((uint8_t *)"WiFi Prov1");

	while (1)
	{
		if (m2m_ble_event_get(&ble_event, &gu8BleParam) == AT_BLE_SUCCESS)
		{
			ble_prov_process_event(ble_event, &gu8BleParam);
		}
		
		if (wifi_con_state != gu8WiFiConnectionState)
		{
			if (gu8WiFiConnectionState != M2M_WIFI_UNDEF)
			{
				ble_prov_wifi_con_update(
					gu8WiFiConnectionState ? WIFIPROV_CON_STATE_CONNECTED:
						                     WIFIPROV_CON_STATE_DISCONNECTED);
			}
			wifi_con_state = gu8WiFiConnectionState;
		}

		switch (app_state)
		{
			case APP_STATE_IDLE:
			{
				if (wifi_con_state == M2M_WIFI_CONNECTED)
				{
					m2m_wifi_disconnect();
					app_state = APP_STATE_WAITING_FOR_WIFI_DISCONNECTION;
				}
				else
				{
					gu8WiFiConnectionState = M2M_WIFI_UNDEF;
					if (ble_prov_start() == AT_BLE_SUCCESS)
					{
						app_state = APP_STATE_PROVISIONING;						
					}
				}
				break;
			}
			case APP_STATE_WAITING_FOR_WIFI_DISCONNECTION:
			{
				if (wifi_con_state == M2M_WIFI_DISCONNECTED)
				{
					if (ble_prov_start() == AT_BLE_SUCCESS)
					{
						app_state = APP_STATE_PROVISIONING;
						wifi_con_state = M2M_WIFI_UNDEF;
						gu8WiFiConnectionState = M2M_WIFI_UNDEF;
					}
				}
				break;
			}
			case APP_STATE_PROVISIONING:
			{
				// BLE requests are handled in ble_prv framework.
				// The application layer handles scan_result (handle ble_prov_scan_result)
				// Here we check if process has been completed.
				switch (ble_prov_get_provision_state())
				{
					case BLE_PROV_STATE_SUCCESS:
					{
						credentials mycred;
						printf("Provisioning data received\r\n");
						if (ble_prov_get_credentials(&mycred) == CREDENTIALS_VALID)
						{
							printf("Connecting to %s ",(char *)mycred.ssid);
							nm_bsp_start_timer(timer_cb, 1000);
							m2m_wifi_connect((char *)mycred.ssid, mycred.ssid_length,
							mycred.sec_type, mycred.passphrase, M2M_WIFI_CH_ALL);
							ble_prov_wifi_con_update(WIFIPROV_CON_STATE_CONNECTING);
							app_state = APP_STATE_WAITING_FOR_WIFI_CONNECTION;
						}
						else
						{
							ble_prov_stop();
							app_state = APP_STATE_IDLE;
						}
						break;
					}
					case BLE_PROV_STATE_FAILED:
					{
						ble_prov_stop();
						app_state = APP_STATE_IDLE;
						break;
					}
				}
				break;
			}
			case APP_STATE_WAITING_FOR_WIFI_CONNECTION:
			{
				if (wifi_con_state == M2M_WIFI_CONNECTED)
				{
					nm_bsp_stop_timer();
					printf("Provisioning Completed\r\n");
					ble_prov_wifi_con_update(WIFIPROV_CON_STATE_CONNECTED);
					app_state = APP_STATE_COMPLETED;
					wifi_con_state = M2M_WIFI_UNDEF;
					ble_prov_stop();
					//Re-init the BLE to put it into a default, known state.
					m2m_ble_init();
					//Now we have finished provisioning, we can place BLE in restricted mode to save power
					m2m_wifi_req_restrict_ble();
				}
				if (wifi_con_state == M2M_WIFI_DISCONNECTED)
				{
					nm_bsp_stop_timer();
					printf("WiFi Connect failed.\r\n");
					ble_prov_stop();
					ble_prov_wifi_con_update(WIFIPROV_CON_STATE_DISCONNECTED);
					app_state = APP_STATE_IDLE;
					wifi_con_state = M2M_WIFI_UNDEF;
				}
				break;
			}
			case APP_STATE_COMPLETED:
			{
				break;
			}			
		}
	}
}

int main (void)
{
	system_init();
	configure_console();
	puts(STRING_HEADER);

	nm_bsp_init();
	nm_bsp_app_init();	

	app_wifi_init(app_wifi_handle_event);
	app_ble_wifi_provisioning();
	
}
