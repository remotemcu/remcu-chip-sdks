/**
 *
 * \file
 *
 * \brief
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
#ifndef M2M_WIFI_EX_H_INCLUDED
#define M2M_WIFI_EX_H_INCLUDED
#include <driver/include/m2m_wifi.h>

typedef void (*m2m_wifi_callback_t)(void *arg);

sint8 os_m2m_wifi_init(tstrWifiInitParam *param);
sint8 os_m2m_wifi_connect(char *pcSsid, uint8 u8SsidLen, uint8 u8SecType, void *pvAuthInfo, uint16 u16Ch);
sint8 os_m2m_wifi_enable_ap(tstrM2MAPConfig *ap);
sint8 m2m_wifi_request_callback_ex(m2m_wifi_callback_t callback, void *arg);
sint8 m2m_wifi_request_dhcp_client_ex(void);
sint8 m2m_wifi_enable_ap_ex(CONST tstrM2MAPConfig* pstrM2MAPConfig);
sint8 m2m_wifi_disable_ap_ex(void);

// Macros to alias all other APIs to the _ex versions.
#define m2m_wifi_download_mode_ex			m2m_wifi_download_mode
#define m2m_wifi_deinit_ex					m2m_wifi_deinit
#define m2m_wifi_handle_events_ex			m2m_wifi_handle_events
#define m2m_wifi_default_connect_ex			m2m_wifi_default_connect
#define m2m_wifi_disconnect_ex				m2m_wifi_disconnect
#define m2m_wifi_start_provision_mode_ex	m2m_wifi_start_provision_mode
#define m2m_wifi_stop_provision_mode_ex		m2m_wifi_stop_provision_mode
#define m2m_wifi_get_connection_info_ex		m2m_wifi_get_connection_info
#define m2m_wifi_wps_ex						m2m_wifi_wps
#define m2m_wifi_wps_disable_ex				m2m_wifi_wps_disable 
#define m2m_wifi_p2p_ex						m2m_wifi_p2p
#define m2m_wifi_p2p_disconnect_ex			m2m_wifi_p2p_disconnect
#define m2m_wifi_set_static_ip_ex			m2m_wifi_set_static_ip
#define m2m_wifi_request_dhcp_server_ex		m2m_wifi_request_dhcp_server
#define m2m_wifi_set_scan_options_ex		m2m_wifi_set_scan_options
#define m2m_wifi_set_scan_region_ex			m2m_wifi_set_scan_region
#define m2m_wifi_request_scan_ex			m2m_wifi_request_scan
#define m2m_wifi_get_num_ap_found_ex		m2m_wifi_get_num_ap_found
#define m2m_wifi_req_scan_result_ex			m2m_wifi_req_scan_result
#define m2m_wifi_req_curr_rssi_ex			m2m_wifi_req_curr_rssi
#define m2m_wifi_get_otp_mac_address_ex		m2m_wifi_get_otp_mac_address
#define m2m_wifi_get_mac_address_ex			m2m_wifi_get_mac_address
#define m2m_wifi_set_sleep_mode_ex			m2m_wifi_set_sleep_mode
#define m2m_wifi_request_sleep_ex			m2m_wifi_request_sleep
#define m2m_wifi_get_sleep_mode_ex			m2m_wifi_get_sleep_mode
#define m2m_wifi_req_client_ctrl_ex			m2m_wifi_req_client_ctrl
#define m2m_wifi_req_server_init_ex			m2m_wifi_req_server_init
#define m2m_wifi_set_device_name_ex			m2m_wifi_set_device_name
#define m2m_wifi_set_lsn_int_ex				m2m_wifi_set_lsn_int
#define m2m_wifi_enable_monitoring_mode_ex	m2m_wifi_enable_monitoring_mode
#define m2m_wifi_disable_monitoring_mode_ex	m2m_wifi_disable_monitoring_mode
#define m2m_wifi_send_wlan_pkt_ex			m2m_wifi_send_wlan_pkt
#define m2m_wifi_send_ethernet_pkt_ex		m2m_wifi_send_ethernet_pkt
#define m2m_wifi_set_sytem_time_ex			m2m_wifi_set_sytem_time
#define m2m_wifi_set_cust_InfoElement_ex	m2m_wifi_set_cust_InfoElement
#define m2m_wifi_enable_mac_mcast_ex		m2m_wifi_enable_mac_mcast
#define m2m_wifi_set_receive_buffer_ex		m2m_wifi_set_receive_buffer

sint8 os_m2m_wifi_download_mode(void);
sint8 os_m2m_wifi_deinit(void* arg);
sint8 os_m2m_wifi_default_connect(void);
sint8 os_m2m_wifi_disconnect(void);
sint8 os_m2m_wifi_start_provision_mode(tstrM2MAPConfig* pstrAPConfig, char* pcHttpServerDomainName, uint8 bEnableHttpRedirect);
sint8 os_m2m_wifi_stop_provision_mode(void);
sint8 os_m2m_wifi_get_connection_info(void);
sint8 os_m2m_wifi_set_mac_address(uint8* au8MacAddress);
sint8 os_m2m_wifi_wps(uint8 u8TriggerType, const char* pcPinNumber);
sint8 os_m2m_wifi_wps_disable(void);
sint8 os_m2m_wifi_p2p(uint8 u8Channel);
sint8 os_m2m_wifi_p2p_disconnect(void);
sint8 os_m2m_wifi_disable_ap(void);
sint8 os_m2m_wifi_ap_get_assoc_info(void);
sint8 os_m2m_wifi_set_static_ip(tstrM2MIPConfig* pstrStaticIPConf);
sint8 os_m2m_wifi_set_scan_options(uint8 u8NumOfSlot, uint8 u8SlotTime);
sint8 os_m2m_wifi_set_scan_region(uint8 ScanRegion);
sint8 os_m2m_wifi_request_scan(uint8 ch);
sint8 os_m2m_wifi_request_scan_ssid(uint8 ch, char* pcssid);
uint8 os_m2m_wifi_get_num_ap_found(void);
sint8 os_m2m_wifi_req_scan_result(uint8 index);
sint8 os_m2m_wifi_req_curr_rssi(void);
sint8 os_m2m_wifi_get_otp_mac_address(uint8* pu8MacAddr, uint8* pu8IsValid);
sint8 os_m2m_wifi_get_mac_address(uint8* pu8MacAddr);
sint8 os_m2m_wifi_set_sleep_mode(uint8 PsTyp, uint8 BcastEn);
sint8 os_m2m_wifi_request_sleep(uint32 u32SlpReqTime);
sint8 os_m2m_wifi_req_client_ctrl(uint8 cmd);
sint8 os_m2m_wifi_req_server_init(uint8 ch);
sint8 os_m2m_wifi_set_device_name(uint8* pu8DeviceName, uint8 u8DeviceNameLength);
sint8 os_m2m_wifi_set_lsn_int(tstrM2mLsnInt* pstrM2mLsnInt);
sint8 os_m2m_wifi_enable_monitoring_mode(tstrM2MWifiMonitorModeCtrl* pstrMtrCtrl, uint8* pu8PayloadBuffer, uint16 u16BufferSize, uint16 u16DataOffset);
sint8 os_m2m_wifi_disable_monitoring_mode(void);
sint8 os_m2m_wifi_send_wlan_pkt(uint8* pu8WlanPacket, uint16 u16WlanHeaderLength, uint16 u16WlanPktSize);
sint8 os_m2m_wifi_send_ethernet_pkt(uint8* pu8Packet, uint16 u16PacketSize);
sint8 os_m2m_wifi_set_sytem_time(uint32 u32UTCSeconds);
sint8 os_m2m_wifi_set_cust_InfoElement(uint8* pau8M2mCustInfoElement);
sint8 os_m2m_wifi_enable_mac_mcast(uint8* pu8MulticastMacAddress, uint8 u8AddRemove);
sint8 os_m2m_wifi_set_receive_buffer(void* pvBuffer, uint16 u16BufferLen);
sint8 os_m2m_wifi_set_control_ifc(uint8 u8IfcId);
sint8 os_m2m_wifi_send_ethernet_pkt_ifc1(uint8* pu8Packet, uint16 u16PacketSize);
uint8 os_m2m_wifi_get_sleep_mode(void);

#endif /* M2M_WIFI_EX_H_INCLUDED */
