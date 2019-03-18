/**
 * \file
 *
 * \brief BLE Battery Service Application Implementations
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
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Atmel
 *Support</a>
 */

/**
 * \mainpage
  * \section intro Introduction
 * This example demonstrates Wi-Fi provision via BLE using the WINC3400 
 * Wi-Fi/BLE module and Battery Profile <br>
 * It uses the following hardware:
 * - SAM Xplained Pro.
 * - the WINC3400 module on EXT1.
 * - thirdparty Android device.
 *
 * \section files Main Files
 * - battery_app.c : Initialize the SAM board and perform BLE provisioning and then starts Battery Profile
 *
 * \section usage Usage
 * -# To connect the SAM board to the internet Access Point over Wi-Fi, the user must
 * -# provide credentials (SSID and passphrase) over BLE. As a first step, it is required
 * -# that the user install the Atmel BLE provision application available with the example project 
 * -# provision_ap_with_ble_on_chip_profile_example (Atmel_BLE_prov.apk) on an Android device.
 * -# Then, power up the SAM board and run the Android application: perform a scan, select
 * -# an SSID and enter the passphrase.
 * -# Finally, press connect and enter the PIN code "123456".
 * -# If connection to AP is successful, WINC3400 BLE will start beaconing.
 * -# After Successful Wi-Fi connection, this application switch to BLE Battery profile.
 * -# It is required that the user install the ATMEL SMART application 
 * -# available in the Android Play store on to an any Android device.
 * -# Then run the Android application: perform a scan, select
 * -# "ATMEL-BAS" to get start with the Battery service.
 * -# The application show the level of Battery available in the connected Mobile.
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
 *  -- Wifi BLE Provisioning demo with Battery--
 *	-- SAMD21_XPLAINED_PRO --
 *	-- Compiled: xxx  x xxxx xx:xx:xx --

 *    (APP)(INFO)Chip ID 3400d1
 *    (APP)(INFO)Curr driver ver: x.x.x
 *    (APP)(INFO)Curr driver HIF Level: (2) X.x
 *    (APP)(INFO)Fw HIF: 8101
 *    (APP)(INFO)Firmware HIF (2) : x.x
 *    (APP)(INFO)Firmware ver   : x.x.x
 *    (APP)(INFO)Firmware Build <Month> DD YYYY Time xx:xx:xx
 *    (APP)(INFO)OTP MAC
 *    (APP)(INFO)MAC Address: xx:xx:xx:xx:xx:xx
 *    (APP)(INFO)M2M_NO_PS
 *    (APP)(INFO)POWER SAVE 0
 *	  (APP)(INFO)Reset provision data
 *	  (APP)(INFO)BLE provisioning started
 */
 
/*- Includes -----------------------------------------------------------------------*/
#include "battery_app.h"
#include "ble_manager.h"
#include "battery.h"
#if (defined __SAMD21J18A__) || (defined __SAMD21G18A__)
#include "bsp/include/nm_bsp_samd21_app.h"
#endif // #if (defined __SAMD21J18A__) || (defined __SAMD21G18A__)
#ifdef __SAMG55J19__
#include "bsp/include/nm_bsp_samg55_app.h"
#endif // #ifdef __SAMG55J19__
#ifdef __SAM4SD32C__
#include "bsp/include/nm_bsp_sam4s_app.h"
#endif //#ifdef __SAM4SD32C__
#if (defined __SAME70Q21__) || (defined __SAME70Q21B__)
#include "bsp/include/nm_bsp_same70_app.h"
#endif //#if (defined __SAME70Q21__) || (defined __SAME70Q21B__)

#include <asf.h>
#include "driver/include/m2m_wifi.h"
#include "driver/include/m2m_periph.h"
#include "m2m_ble.h"
#include "at_ble_api.h"
#include "wifi_prov.h"

extern uint32 nmi_inet_addr(char *pcIpAddr);


#define STRING_HEADER "-- Wifi BLE Provisioning demo with Battery--\r\n" \
                      "-- "BOARD_NAME" --\r\n" \
                      "-- Compiled: "__DATE__" "__TIME__" --\r\n"

#define APP_WIFI_PROV_DISPLAY_NAME  ("3400 DEMO")

#define APP_BTN_EVENT_BTN1_SHORT_PRESS              1
#define APP_BTN_EVENT_BTN1_LONG_PRESS               2
#define APP_BTN_EVENT_BTN2_SHORT_PRESS              4
#define APP_BTN_EVENT_BTN2_LONG_PRESS               8

#define APP_STATE_IDLE								0
#define APP_STATE_WAITING_FOR_WIFI_DISCONNECTION	1
#define APP_STATE_PROVISIONING						2
#define APP_STATE_WAITING_FOR_BUTTON_PRESS			3
#define APP_STATE_WAITING_FOR_WIFI_CONNECTION		4
#define APP_STATE_WAITING_FOR_PROFIFE_SWITCH		5
#define APP_STATE_COMPLETE							6


static volatile uint8 gu8WiFiConnectionState = M2M_WIFI_UNDEF;
static volatile uint8 gu8BtnEvent;
static uint8 gu8ScanIndex;
static at_ble_event_parameter_t gu8BleParam __aligned(4);

#define APP_BAS_FAST_ADV				(100) //100 ms
/** @brief APP_BAS_ADV_TIMEOUT Advertising time-out between 0x0001 and 0x3FFF in seconds, 0x0000 disables time-out.*/
#define APP_BAS_ADV_TIMEOUT				(1000) // 100 Secs
/** @brief scan_resp_len is the length of the scan response data */
#define SCAN_RESP_LEN					(10)
/** @brief ADV_DATA_LEN */
#define ADV_DATA_LEN					(18)
/** @brief ADV_TYPE_LEN */
#define ADV_TYPE_LEN					(0x01)
/** @brief BAS_ADV_DATA_UUID_LEN the size of  BAS service uuid */
#define BAS_ADV_DATA_UUID_LEN			(2)
/** @brief BAS_ADV_DATA_UUID_TYPE the total sizeof BAS service uuid*/
#define BAS_ADV_DATA_UUID_TYPE			(0x03)
/** @brief BAS_ADV_DATA_NAME_TYPE the gap ad data type */
#define BAS_ADV_DATA_NAME_TYPE			(0x09)
/* @brief BAS_ADV_DATA_NAME_DATA the actual name of device */
#define BAS_ADV_DATA_NAME_DATA			("ATMEL-BAS")
/** @brief BAS_ADV_DATA_NAME_LEN the length of the device name */
#define BAS_ADV_DATA_NAME_LEN			(9)

static const uint8_t SCAN_RESP_DATA[SCAN_RESP_LEN] = {0x09,0xff, 0x00, 0x06, 0xd6, 0xb2, 0xf0, 0x05, 0xf0, 0xf8};


#define BATTERY_UPDATE_INTERVAL	(188)
#define BATTERY_MAX_LEVEL		(100)


bool volatile timer_cb_done;
static uint8_t led_toggle;
static uint8_t battery_level;
static 	gatt_service_handler_t bas_service_handler;


static at_ble_status_t ble_bat_start_advertise(void)
{
	uint8_t idx = 0;
	uint8_t adv_data [ BAS_ADV_DATA_NAME_LEN + BAS_ADV_DATA_UUID_LEN   + (2*2)];
	
	adv_data[idx++] = BAS_ADV_DATA_UUID_LEN + ADV_TYPE_LEN;
	adv_data[idx++] = BAS_ADV_DATA_UUID_TYPE;

	/* Appending the UUID */
	adv_data[idx++] = (uint8_t)BAT_SERVICE_UUID;
	adv_data[idx++] = (uint8_t)(BAT_SERVICE_UUID >> 8);
	
	//Appending the complete name to the Ad packet
	adv_data[idx++] = BAS_ADV_DATA_NAME_LEN + ADV_TYPE_LEN;
	adv_data[idx++] = BAS_ADV_DATA_NAME_TYPE;
	
	memcpy(&adv_data[idx], BAS_ADV_DATA_NAME_DATA, BAS_ADV_DATA_NAME_LEN);
	idx += BAS_ADV_DATA_NAME_LEN;
	
	/* Adding the advertisement data and scan response data */
	if (at_ble_adv_data_set(adv_data, idx, SCAN_RESP_DATA, SCAN_RESP_LEN) != AT_BLE_SUCCESS)
	{
		DBG_LOG("Failed to set adv data");
		return AT_BLE_FAILURE;
	}
	
	at_ble_set_dev_config(AT_BLE_GAP_PERIPHERAL_SLV);
	
	/* Start of advertisement */
	if (at_ble_adv_start(AT_BLE_ADV_TYPE_UNDIRECTED, AT_BLE_ADV_GEN_DISCOVERABLE, NULL,
			AT_BLE_ADV_FP_ANY, APP_BAS_FAST_ADV, APP_BAS_ADV_TIMEOUT, 0) != AT_BLE_SUCCESS)
	{
		DBG_LOG("BLE Adv start Failed");
		return AT_BLE_FAILURE;
	}
	
	DBG_LOG("BLE Started Adv\n");
	return AT_BLE_SUCCESS;
}

static void ble_bat_handle_timer_event(void)
{
#if 0	
	if (led_toggle == true)
		port_pin_toggle_output_level(LED0_PIN);
	else
		port_pin_set_output_level(LED0_PIN, true);	// LED OFF
#endif
	timer_cb_done = true;
}

static void ble_bat_handle_paired_event(at_ble_handle_t conn_handle)
{
	timer_cb_done = false;
	nm_bsp_stop_timer();
	nm_bsp_start_timer(ble_bat_handle_timer_event, BATTERY_UPDATE_INTERVAL);
}

static void ble_bat_handle_disconnect_event(at_ble_handle_t conn_handle)
{
	timer_cb_done = false;
	nm_bsp_stop_timer();

	ble_bat_start_advertise();
}

// Update the service about battery status
static void ble_bat_process(void)
{
	if (timer_cb_done)
	{
		timer_cb_done = false;

		battery_level = (battery_level % BATTERY_MAX_LEVEL);
		
		// blinking when battery less than 60%
		led_toggle = (battery_level < 60)? true:false;
		
		/* send the notification and Update the battery level  */
		if (bat_update_char_value(&bas_service_handler, battery_level) == AT_BLE_SUCCESS)
		{
			DBG_LOG("Battery Level:%d%%", battery_level);
		}
		battery_level++;
	}
}

// Allows the main app to initialise the profile app including
// initialising services and callbacks
static void ble_bat_profile_init(void)
{
	timer_cb_done = false;
	led_toggle = false;
	battery_level = BATTERY_MAX_LEVEL;
	
	DBG_LOG("Initializing Battery Service Application");

	bat_init_service(&bas_service_handler, &battery_level);
	bat_primary_service_define(&bas_service_handler);

	register_ble_paired_event_cb(ble_bat_handle_paired_event);
	register_ble_disconnected_event_cb(ble_bat_handle_disconnect_event);

	ble_bat_start_advertise();
}

void ble_bat_init(void)
{
	ble_device_init(NULL);

	ble_bat_profile_init();
}

void ble_bat_process_event(at_ble_events_t event, at_ble_event_parameter_t *params)
{
	if (event != AT_BLE_UNDEFINED_EVENT)
	{
		// Feed the received event into BlueSDK stack.
		ble_event_manager(event, params);
	}
	
	ble_bat_process();
}

static void app_wifi_init(tpfAppWifiCb wifi_cb_func)
{
	tstrWifiInitParam param;
	uint32 pinmask = (
	M2M_PERIPH_PULLUP_DIS_HOST_WAKEUP|
	M2M_PERIPH_PULLUP_DIS_SD_CMD_SPI_SCK|
	M2M_PERIPH_PULLUP_DIS_SD_DAT0_SPI_TXD);

	sint8 ret;

	uint8 mac_addr[6];
	uint8 u8IsMacAddrValid;
	uint8 deviceName[] = M2M_DEVICE_NAME;

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
		//system_reset();

		while (1)
		{
		}
	}
	
	m2m_periph_pullup_ctrl(pinmask, 0);
	
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
		len = m2m_strlen(deviceName);
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
		M2M_INFO("M2M_PS_DEEP_AUTOMATIC\r\n");
		m2m_wifi_set_sleep_mode(M2M_PS_DEEP_AUTOMATIC, 1);
		strM2mLsnInt.u16LsnInt = M2M_LISTEN_INTERVAL;
		m2m_wifi_set_lsn_int(&strM2mLsnInt);
	}
#elif (defined _STATIC_PS_)
	M2M_INFO("M2M_PS_MANUAL\r\n");
	m2m_wifi_set_sleep_mode(M2M_PS_MANUAL, 1);
#else
	M2M_INFO("M2M_NO_PS\r\n");
	m2m_wifi_set_sleep_mode(M2M_NO_PS, 1);
#endif
}

static void app_wifi_handle_event(uint8 u8MsgType, void * pvMsg)
{
	if (u8MsgType == M2M_WIFI_RESP_CON_STATE_CHANGED)
	{
		tstrM2mWifiStateChanged *pstrWifiState = (tstrM2mWifiStateChanged*) pvMsg;

		M2M_INFO("Wifi State :: %s ::\n", pstrWifiState->u8CurrState ? "CONNECTED" : "DISCONNECTED");
		if(pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED)
		{
			gu8WiFiConnectionState = M2M_WIFI_DISCONNECTED;
		}
	}
	else if (u8MsgType == M2M_WIFI_REQ_DHCP_CONF)
	{
		tstrM2MIPConfig* pstrM2MIpConfig = (tstrM2MIPConfig*) pvMsg;
		uint8 *pu8IPAddress = (uint8*) &pstrM2MIpConfig->u32StaticIP;
		
		M2M_INFO("DHCP IP Address :: %u.%u.%u.%u ::\n",
			pu8IPAddress[0], pu8IPAddress[1], pu8IPAddress[2], pu8IPAddress[3]);
		M2M_INFO("WiFi Connected up to layer 3\r\n");

		gu8WiFiConnectionState = M2M_WIFI_CONNECTED;
	
	}
	else if (u8MsgType == M2M_WIFI_RESP_SCAN_DONE)
	{
		tstrM2mScanDone *pstrInfo = (tstrM2mScanDone*) pvMsg;

		if (gu8WiFiConnectionState != M2M_WIFI_CONNECTED)
		{
			gu8ScanIndex = 0;
			
			if (pstrInfo->u8NumofCh >= 1)
			{
				m2m_wifi_req_scan_result(gu8ScanIndex);
				gu8ScanIndex++;
			}
		}
	}
	else if (u8MsgType == M2M_WIFI_RESP_SCAN_RESULT)
	{
		uint8 u8NumFoundAPs = m2m_wifi_get_num_ap_found();

		if (gu8WiFiConnectionState != M2M_WIFI_CONNECTED)
		{
			tstrM2mWifiscanResult *pstrScanResult = (tstrM2mWifiscanResult*) pvMsg;

			ble_prov_scan_result(pstrScanResult, u8NumFoundAPs-gu8ScanIndex);
			if(gu8ScanIndex < u8NumFoundAPs)
			{
				m2m_wifi_req_scan_result(gu8ScanIndex);
				gu8ScanIndex++;
			}
		}
	}
	else if (u8MsgType == M2M_WIFI_RESP_CURRENT_RSSI)
	{
		sint8	*rssi = (sint8*)pvMsg;
		M2M_INFO("(%lu) rssi %d\n",NM_BSP_TIME_MSEC,*rssi);
	}
	else if(u8MsgType == M2M_WIFI_RESP_SET_GAIN_TABLE) {
		tstrM2MGainTableRsp *pstrRsp = (tstrM2MGainTableRsp *)pvMsg;
		M2M_ERR("Gain Table Load Fail %d\n", pstrRsp->s8ErrorCode);
	}    
}

static void app_button_press_callback(uint8 btn, uint8 press)
{
	if (SW1 == btn)
	{
		gu8BtnEvent = (!press) ? (APP_BTN_EVENT_BTN1_SHORT_PRESS) : (APP_BTN_EVENT_BTN1_LONG_PRESS);
	}
	else if (SW2 == btn)
	{
		gu8BtnEvent = (!press) ? (APP_BTN_EVENT_BTN2_SHORT_PRESS) : (APP_BTN_EVENT_BTN2_LONG_PRESS);
	}
}

// This is an example of using onchip_profile, ble_prov API.
static void app_ble_wifi_provisioning(void) 
{
	uint8_t app_state = APP_STATE_IDLE;
	uint8_t wifi_con_state = M2M_WIFI_UNDEF;
	uint8_t btn_event;
	at_ble_events_t ble_event;
	uint8_t display_name[] = APP_WIFI_PROV_DISPLAY_NAME;
	
	gu8BtnEvent = 0;

	// Initialize BLE stack on 3400.
	m2m_ble_init();
	ble_prov_init(display_name);	

	//M2M_INFO("Hold SW0 for 2 sec to start provisioning.\r\n");

	while (app_state != APP_STATE_COMPLETE)
	{
		//
		// Pump event to BLE application
		//
		if (m2m_ble_event_get(&ble_event, &gu8BleParam) == AT_BLE_SUCCESS)
		{
			ble_prov_process_event(ble_event, &gu8BleParam);
		}

#if 0
		//
		// Handle external (Button/WiFi) events for provisioning app.
		// This state machine runs until app_state becomes APP_STATE_COMPLETE.
		//
		btn_event = gu8BtnEvent;
		gu8BtnEvent = 0;

		if (btn_event == APP_BTN_EVENT_BTN1_LONG_PRESS && app_state != APP_STATE_IDLE)
		{
			M2M_INFO("Provisioning in process, aborting..\r\n");
			ble_prov_stop();

			M2M_INFO("Press button again to start provisioning\r\n");
			app_state = APP_STATE_IDLE;
			wifi_con_state = M2M_WIFI_UNDEF;
			btn_event = 0;
		}
#endif

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
				//if (btn_event == APP_BTN_EVENT_BTN1_LONG_PRESS)
				{
					//M2M_INFO("SW0 Long press\r\n");
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
						//M2M_INFO("Provisioning data received - press SW0 to attempt WiFi connect\r\n");
						//app_state = APP_STATE_WAITING_FOR_BUTTON_PRESS;
                                        M2M_INFO("Provisioning data received\r\n");
                                        credentials mycred;
										char def_ssid[32] = DEFAULT_SSID;

					    if (ble_prov_get_credentials(&mycred) != CREDENTIALS_VALID)
					    {
						    M2M_INFO("WiFi Connect: using default ssid");
						    m2m_wifi_connect(def_ssid, sizeof(DEFAULT_SSID),
							DEFAULT_AUTH, (void *) DEFAULT_KEY, M2M_WIFI_CH_ALL);
					    }
					    else
					    {
						    M2M_INFO("WiFi Connect: using provisioned AP");
						    m2m_wifi_connect((char *)mycred.ssid, mycred.ssid_length,
							mycred.sec_type, mycred.passphrase, M2M_WIFI_CH_ALL);
					    }

					    ble_prov_wifi_con_update(WIFIPROV_CON_STATE_CONNECTING);
						app_state = APP_STATE_WAITING_FOR_WIFI_CONNECTION;
						break;
					}
					case BLE_PROV_STATE_FAILED:
					{
						//M2M_INFO("Press button again to re-start provisioning\r\n");
						app_state = APP_STATE_IDLE;
					}
					break;
				}
				break;
			}
			case APP_STATE_WAITING_FOR_BUTTON_PRESS:
			{
				if (btn_event == APP_BTN_EVENT_BTN1_SHORT_PRESS)
				{
					credentials mycred;
					char def_ssid[32] = DEFAULT_SSID;

					if (ble_prov_get_credentials(&mycred) != CREDENTIALS_VALID)
					{
						M2M_INFO("WiFi Connect: using default ssid");
						m2m_wifi_connect(def_ssid, sizeof(DEFAULT_SSID),
							DEFAULT_AUTH, (void *) DEFAULT_KEY, M2M_WIFI_CH_ALL);
					}
					else
					{
						M2M_INFO("WiFi Connect: using provisioned AP");
						m2m_wifi_connect((char *)mycred.ssid, mycred.ssid_length,
							mycred.sec_type, mycred.passphrase, M2M_WIFI_CH_ALL);
					}

					ble_prov_wifi_con_update(WIFIPROV_CON_STATE_CONNECTING);
					app_state = APP_STATE_WAITING_FOR_WIFI_CONNECTION;
				}
				break;
			}
			case APP_STATE_WAITING_FOR_WIFI_CONNECTION:
			{
				if (wifi_con_state == M2M_WIFI_CONNECTED)
				{
					M2M_INFO("Provisioning Complete\r\n");
					//M2M_INFO("Press SW0 to switch BLE profile to Battery profile\r\n");	
					app_state = APP_STATE_WAITING_FOR_PROFIFE_SWITCH;
				}
				if (wifi_con_state == M2M_WIFI_DISCONNECTED)
				{
					ble_prov_wifi_con_update(WIFIPROV_CON_STATE_DISCONNECTED);
					M2M_INFO("WIFI Connect failed. Hold button SW0 again to restart provisioning\r\n");
					app_state = APP_STATE_IDLE;
					wifi_con_state = M2M_WIFI_UNDEF;
					btn_event = 0;
				}
				break;
			}
			case APP_STATE_WAITING_FOR_PROFIFE_SWITCH:
			{
				//if (btn_event == APP_BTN_EVENT_BTN1_SHORT_PRESS)
				{
					app_state = APP_STATE_COMPLETE;
				}
				break;
			}
		}
	}
}


// This is an example of using BlueSDK Profile.
static void app_ble_battery(void)
{
	at_ble_events_t ble_event;
	// Initialize BLE stack.
	m2m_ble_init();
	ble_bat_init();

	// Pump BLE event to BLE application.
	while (1)
	{
		if (m2m_ble_event_get(&ble_event, &gu8BleParam) == AT_BLE_SUCCESS) 
		{
		    if (ble_event) { printf("\nble_event=%d\n", ble_event); }
			ble_bat_process_event(ble_event, &gu8BleParam);
		}
	}
}

static void app_main(void)
{
	// Initialize WiFi interface first.
	// 3400 WiFi HIF is used to convey BLE API primitives. 
	app_wifi_init(app_wifi_handle_event);
	nm_bsp_btn_init(app_button_press_callback);
	//nm_bsp_sleep(2000);
	
	// Demo application using Onchip(AT_BLE API) profile.
	app_ble_wifi_provisioning();
	
	nm_bsp_sleep(2000);

	// Demo application using BlueSDK profile.
	app_ble_battery();
}

static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate =		CONF_UART_BAUDRATE,
		.charlength =	CONF_UART_CHAR_LENGTH,
		.paritytype =	CONF_UART_PARITY,
		.stopbits =		CONF_UART_STOP_BITS,
	};

	/* Configure UART console. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

int main (void)
{
	/* Initialize the SAM system. */
	sysclk_init();
	board_init();
	
	configure_console();
	puts(STRING_HEADER);

	if (SysTick_Config(F_CPU / 1000)) {
		puts("main: SysTick configuration error!");
		return 0;
	}
	
	nm_bsp_init();
	nm_bsp_app_init();	
	
	app_main();
}

