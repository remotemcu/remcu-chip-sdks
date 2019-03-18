/**
 *
 * \file
 *
 * \brief WINC3400 BLE Application example code.
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
#include "driver/include/m2m_types.h"
#include "driver/include/m2m_wifi.h"
#include "at_ble_api.h"
#include "platform.h"
#include "m2m_ble.h"
#include "ble_manager.h"
//#define BLE_API_DBG 1


static tpfAppWifiCb gpfBleAppWifiCb = NULL;

 //Callback that takes a blob from the BLE API and writes it over the HIF
 void m2m_ble_api_write_func(uint8* msg, uint32 len)
 {
	 //Hooks into bottom of BLE API and receives serialised data ready to transmit over cor2cor
	 //DTODO could/should this be completely handle inside m2m_wifi and not exposed to app?
#ifdef BLE_API_DBG
	 M2M_INFO("BLE_API_SEND:%x:%x:%x:%x:%x:%x\n", len, msg[0], msg[1], msg[2], msg[3], msg[4]);
#endif
	 m2m_wifi_ble_api_send(msg, len);
 }

 //Platform specific wait function that is called by the BLE API when it is awaiting responses. We
 //need to ensure we handle incoming HIF events during this time to actually process the BLE response.
 static void m2m_ble_plf_wait_func(void)
 {
	 while (m2m_wifi_handle_events(NULL) != M2M_SUCCESS);
 }

 void m2m_ble_wifi_callback(uint8 u8MsgType, void * pvMsg)
 {
	 if (u8MsgType == M2M_WIFI_RESP_BLE_API_RECV)
	 {
		 tstrM2mBleApiMsg* rx = (tstrM2mBleApiMsg*)pvMsg;
#ifdef BLE_API_DBG
		 M2M_INFO("BLE_API_RECV:%x:%x:%x:%x:%x:%x\n", \
			rx->u16Len, rx->data[0], rx->data[1], rx->data[2], rx->data[3], rx->data[4]);
#endif
		 platform_receive(rx->data, rx->u16Len);
		 return;
	 }

	 if (gpfBleAppWifiCb) {
		 gpfBleAppWifiCb(u8MsgType, pvMsg);
	 }
 }

sint8 m2m_ble_init(void)
{
	 plf_params_t plf;

	 plf.ble_write_cb = m2m_ble_api_write_func;
	 plf.plf_wait_cb  = m2m_ble_plf_wait_func;

	 if (gpfBleAppWifiCb == NULL)
	 {
	 	 M2M_ERR("WiFi is not initialized yet\n");
	 	 return -1;
	 }
	 
	 if (at_ble_init((void*)&plf) != AT_BLE_SUCCESS)
	 {
		 M2M_ERR("Failed to initialise BLE API\n");
		 return -1;
	 }

	 return M2M_SUCCESS;
 }

sint8 m2m_ble_event_get(at_ble_events_t *event, at_ble_event_parameter_t* params)
{
	// if application is NOT BlueSDK profile,
	// Profile has own event handler for at_ble_event_get().
	if (at_ble_event_get(event, (uint8_t*)params, BLE_EVENT_TIMEOUT) != AT_BLE_SUCCESS)
	{
		*event = AT_BLE_UNDEFINED_EVENT;
	}

	// This stimulates BLE operation.
	// May be this can be moved into profile_process() instead...
	while (m2m_wifi_handle_events(NULL) != M2M_SUCCESS)
	{
		
	}
	

	return AT_BLE_SUCCESS;
}


sint8 m2m_ble_wifi_init(tstrWifiInitParam * param)
{
	gpfBleAppWifiCb = param->pfAppWifiCb;
	param->pfAppWifiCb = m2m_ble_wifi_callback;
#ifdef ETH_MODE
	param->strEthInitParam.pfAppWifiCb = m2m_ble_wifi_callback;
#endif
	return m2m_wifi_init(param);
}


