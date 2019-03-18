/**
 *
 * \file
 *
 * \brief Wireless Link Controller Driver.
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

#include <lwip/opt.h>
#include <lwip/tcpip.h>
#include "m2m_wifi_ex.h"
#include "net_init.h"
#include "os_hook.h"
#include "delay.h"
#include "driver/include/m2m_wifi.h"

static int wifi_netif_init = 0;

extern void winc_fill_callback_info(tstrEthInitParam *info);

struct init_params {
	struct params_dispatch dispatch;
	tstrWifiInitParam *init;
};
typedef sint8 (*func_void)(void);
typedef sint8 (*func_ptru8)(uint8*);
typedef sint8 (*func_uint8)(uint8);
typedef sint8 (*func_uint8_uint8)(uint8, uint8);

struct void_params {
	struct params_dispatch dispatch;
	func_void fn;
};

struct ptru8_params {
	struct params_dispatch dispatch;
	func_ptru8 fn;
	uint8 *arg;
};

struct uint_params {
	struct params_dispatch dispatch;
	func_uint8 fn;
	uint32 arg;
};

struct uint8_uint8_params {
	struct params_dispatch dispatch;
	func_uint8_uint8 fn;
	uint8 arg1;
	uint8 arg2;
};

#define OS_WIFI_NOTIFY(p) do { \
        if ((p)->dispatch.signal_semaphore) { \
        os_hook_notify();} \
    } while (0)

#define OS_WIFI_DISPATCH_WAIT(fn,p) do { \
        (p)->dispatch.retval = M2M_ERR_TIME_OUT; \
        os_hook_dispatch_wait((fn), &((p)->dispatch),(p)); \
    } while(0)

static void os_m2m_wifi_init_imp(void *pv)
{
	struct init_params *p = (struct init_params *)pv;

	/* Save tcpip task handle. */
	os_hook_set_handle(xTaskGetCurrentTaskHandle());

	/* Init low level. */
	nm_bsp_init();

	/* Register lwIP low level driver hook. */
	winc_fill_callback_info(&p->init->strEthInitParam);
	
	/* Init WINC1500 driver. */
	p->dispatch.retval = m2m_wifi_init(p->init);

	if (M2M_SUCCESS == p->dispatch.retval) {
		net_add_winc_netif();
		wifi_netif_init = 1;
	}

	if (p->dispatch.signal_semaphore) {
		os_hook_notify();
	}
}

sint8 os_m2m_wifi_init(tstrWifiInitParam *param)
{
	struct init_params params;
	params.init = param;
	params.dispatch.retval = M2M_ERR_TIME_OUT;

    /* Initialize the netif thread. */
	os_hook_init();
	os_hook_send_start(os_m2m_wifi_init_imp, &params.dispatch, &params);
	
	/* Give enough time to ensure FW is ready. */
	vTaskDelay(50);
	
	return params.dispatch.retval;
}

struct connect_params {
	struct params_dispatch dispatch;
	char *pcSsid;
	uint8 u8SsidLen;
	uint8 u8SecType;
	void *pvAuthInfo;
	uint16 u16Ch;
};

static void os_m2m_wifi_connect_imp(void *pv)
{
	struct connect_params *p = (struct connect_params *) pv;
	p->dispatch.retval = m2m_wifi_connect(p->pcSsid, p->u8SsidLen, p->u8SecType, p->pvAuthInfo, p->u16Ch);
	if (p->dispatch.signal_semaphore) {
		os_hook_notify();
	}
}

sint8 os_m2m_wifi_connect(char *pcSsid, uint8 u8SsidLen, uint8 u8SecType, void *pvAuthInfo, uint16 u16Ch)
{
	struct connect_params params;
	params.pcSsid = pcSsid;
	params.u8SsidLen = u8SsidLen;
	params.u8SecType = u8SecType;
	params.pvAuthInfo = pvAuthInfo;
	params.u16Ch = u16Ch;
	params.dispatch.retval = M2M_ERR_TIME_OUT;

	OS_WIFI_DISPATCH_WAIT(os_m2m_wifi_connect_imp, &params);
	delay_ms(200);
	return params.dispatch.retval;
}

struct connect_ap_params {
	struct params_dispatch dispatch;
	tstrM2MAPConfig *ap;
};

static void os_m2m_wifi_enable_ap_imp(void *pv)
{	
	struct connect_ap_params *p = (struct connect_ap_params *) pv;
	p->dispatch.retval = m2m_wifi_enable_ap(p->ap);
	if (p->dispatch.signal_semaphore) {
		os_hook_notify();
	}
}

sint8 os_m2m_wifi_enable_ap(tstrM2MAPConfig *ap)
{
	struct connect_ap_params params;
	params.ap = ap;
	params.dispatch.retval = M2M_ERR_TIME_OUT;

	OS_WIFI_DISPATCH_WAIT(os_m2m_wifi_enable_ap_imp, &params);
	if (!params.dispatch.retval) {
		net_interface_up(NET_IF_C);
	}
	delay_ms(200);
	return params.dispatch.retval;
}



sint8 m2m_wifi_request_callback_ex(m2m_wifi_callback_t callback, void *arg)
{
	return tcpip_callback_with_block(callback, arg, 0);
}

sint8 m2m_wifi_request_dhcp_client_ex(void)
{
	net_set_mode(NET_IF_STA, NET_MODE_USE_DHCP);
	return 0;
}

sint8 m2m_wifi_enable_ap_ex(CONST tstrM2MAPConfig* pstrM2MAPConfig)
{
	sint8 rc;
	rc = m2m_wifi_enable_ap(pstrM2MAPConfig);
	if (!rc) {
		net_interface_up(NET_IF_C);
	}
	return rc;
}

sint8 m2m_wifi_disable_ap_ex(void)
{
	net_set_mode(NET_IF_C, 0);
	return m2m_wifi_disable_ap();	
}

static void func_void_imp(void * pv)
{
	struct void_params *p = (struct void_params *)pv;
	if (p->fn) {
		p->dispatch.retval = p->fn();
		} else {
		p->dispatch.retval = M2M_ERR_FAIL;
	}

	OS_WIFI_NOTIFY(p);
}
static void func_uint_imp(void *pv)
{
	struct uint_params *p = (struct uint_params *)pv;
	if (p->fn) {
		p->dispatch.retval = p->fn(p->arg);
		} else {
		p->dispatch.retval = M2M_ERR_FAIL;
	}
	
	OS_WIFI_NOTIFY(p);
}

sint8 os_m2m_wifi_download_mode(void)
{
	struct void_params params;
	params.dispatch.retval = M2M_ERR_TIME_OUT;
	params.fn = m2m_wifi_download_mode;
	OS_WIFI_DISPATCH_WAIT(func_void_imp, &params);
	return params.dispatch.retval;
}

sint8 os_m2m_wifi_default_connect(void)
{
	struct void_params params;
	params.dispatch.retval = M2M_ERR_TIME_OUT;
	params.fn = m2m_wifi_default_connect;
	OS_WIFI_DISPATCH_WAIT(func_void_imp, &params);
	return params.dispatch.retval;
}


sint8 os_m2m_wifi_disconnect(void)
{
	struct void_params params;
	params.dispatch.retval = M2M_ERR_TIME_OUT;
	params.fn = m2m_wifi_disconnect;
	OS_WIFI_DISPATCH_WAIT(func_void_imp, &params);
	return params.dispatch.retval;
}

struct wifi_start_provision_mode_params {
	struct params_dispatch dispatch;
	tstrM2MAPConfig* pstrAPConfig;
	char* pcHttpServerDomainName;
	uint8 bEnableHttpRedirect;
};
static void os_m2m_wifi_start_provision_mode_imp(void *pv)
{
	struct wifi_start_provision_mode_params *p = (struct wifi_start_provision_mode_params *) pv;
	p->dispatch.retval = m2m_wifi_start_provision_mode(p->pstrAPConfig, p->pcHttpServerDomainName, p->bEnableHttpRedirect);
	OS_WIFI_NOTIFY(p);
}
sint8 os_m2m_wifi_start_provision_mode(tstrM2MAPConfig* pstrAPConfig, char* pcHttpServerDomainName, uint8 bEnableHttpRedirect)
{
	struct wifi_start_provision_mode_params params;
	params.pstrAPConfig = pstrAPConfig;
	params.pcHttpServerDomainName = pcHttpServerDomainName;
	params.bEnableHttpRedirect = bEnableHttpRedirect;
	OS_WIFI_DISPATCH_WAIT(os_m2m_wifi_start_provision_mode_imp, &params);
	return params.dispatch.retval;
}


sint8 os_m2m_wifi_stop_provision_mode(void)
{
	struct void_params params;
	params.dispatch.retval = M2M_ERR_TIME_OUT;
	params.fn = m2m_wifi_stop_provision_mode;
	OS_WIFI_DISPATCH_WAIT(func_void_imp, &params);
	return params.dispatch.retval;
}

sint8 os_m2m_wifi_get_connection_info(void)
{
	struct void_params params;
	params.dispatch.retval = M2M_ERR_TIME_OUT;
	params.fn = m2m_wifi_get_connection_info;
	OS_WIFI_DISPATCH_WAIT(func_void_imp, &params);
	return params.dispatch.retval;
}


struct wifi_set_mac_address_params {
	struct params_dispatch dispatch;
	uint8* au8MacAddress;
};
static void os_m2m_wifi_set_mac_address_imp(void *pv)
{
	struct wifi_set_mac_address_params *p = (struct wifi_set_mac_address_params *) pv;
	p->dispatch.retval = m2m_wifi_set_mac_address(p->au8MacAddress);
	OS_WIFI_NOTIFY(p);
}
sint8 os_m2m_wifi_set_mac_address(uint8* au8MacAddress)
{
	struct wifi_set_mac_address_params params;
	params.au8MacAddress = au8MacAddress;
	OS_WIFI_DISPATCH_WAIT(os_m2m_wifi_set_mac_address_imp, &params);
	return params.dispatch.retval;
}


struct wifi_wps_params {
	struct params_dispatch dispatch;
	uint8 u8TriggerType;
	const char* pcPinNumber;
};
static void os_m2m_wifi_wps_imp(void *pv)
{
	struct wifi_wps_params *p = (struct wifi_wps_params *) pv;
	p->dispatch.retval = m2m_wifi_wps(p->u8TriggerType, p->pcPinNumber);
	OS_WIFI_NOTIFY(p);
}
sint8 os_m2m_wifi_wps(uint8 u8TriggerType, const char* pcPinNumber)
{
	struct wifi_wps_params params;
	params.u8TriggerType = u8TriggerType;
	params.pcPinNumber = pcPinNumber;
	OS_WIFI_DISPATCH_WAIT(os_m2m_wifi_wps_imp, &params);
	return params.dispatch.retval;
}

sint8 os_m2m_wifi_wps_disable(void)
{
	struct void_params params;
	params.dispatch.retval = M2M_ERR_TIME_OUT;
	params.fn = m2m_wifi_wps_disable;
	OS_WIFI_DISPATCH_WAIT(func_void_imp, &params);
	return params.dispatch.retval;
}


sint8 os_m2m_wifi_p2p(uint8 u8Channel)
{
	struct uint_params params;
	params.dispatch.retval = M2M_ERR_TIME_OUT;
	params.arg = u8Channel;
	params.fn = m2m_wifi_p2p;
	OS_WIFI_DISPATCH_WAIT(func_uint_imp, &params);
	return params.dispatch.retval;
}


sint8 os_m2m_wifi_p2p_disconnect(void)
{
	struct void_params params;
	params.dispatch.retval = M2M_ERR_TIME_OUT;
	params.fn = m2m_wifi_p2p_disconnect;
	OS_WIFI_DISPATCH_WAIT(func_void_imp, &params);
	return params.dispatch.retval;
}


sint8 os_m2m_wifi_disable_ap(void)
{
	struct void_params params;
	params.dispatch.retval = M2M_ERR_TIME_OUT;
	params.fn = m2m_wifi_disable_ap;
	OS_WIFI_DISPATCH_WAIT(func_void_imp, &params);
	return params.dispatch.retval;
}


struct wifi_set_static_ip_params {
	struct params_dispatch dispatch;
	tstrM2MIPConfig* pstrStaticIPConf;
};
static void os_m2m_wifi_set_static_ip_imp(void *pv)
{
	struct wifi_set_static_ip_params *p = (struct wifi_set_static_ip_params *) pv;
	p->dispatch.retval = m2m_wifi_set_static_ip(p->pstrStaticIPConf);
	OS_WIFI_NOTIFY(p);
}
sint8 os_m2m_wifi_set_static_ip(tstrM2MIPConfig* pstrStaticIPConf)
{
	struct wifi_set_static_ip_params params;
	params.pstrStaticIPConf = pstrStaticIPConf;
	OS_WIFI_DISPATCH_WAIT(os_m2m_wifi_set_static_ip_imp, &params);
	return params.dispatch.retval;
}


struct wifi_set_scan_options_params {
	struct params_dispatch dispatch;
	uint8 u8NumOfSlot;
	uint8 u8SlotTime;
};
static void os_m2m_wifi_set_scan_options_imp(void *pv)
{
	struct wifi_set_scan_options_params *p = (struct wifi_set_scan_options_params *) pv;
	tstrM2MScanOption	ScanOpt;
	ScanOpt.u8NumOfSlot = p->u8NumOfSlot;
	ScanOpt.u8SlotTime = p->u8SlotTime;
	p->dispatch.retval = m2m_wifi_set_scan_options(&ScanOpt);
	OS_WIFI_NOTIFY(p);
}
sint8 os_m2m_wifi_set_scan_options(uint8 u8NumOfSlot, uint8 u8SlotTime)
{
	struct wifi_set_scan_options_params params;
	params.u8NumOfSlot = u8NumOfSlot;
	params.u8SlotTime = u8SlotTime;
	OS_WIFI_DISPATCH_WAIT(os_m2m_wifi_set_scan_options_imp, &params);
	return params.dispatch.retval;
}


sint8 os_m2m_wifi_set_scan_region(uint8 ScanRegion)
{
	struct uint_params params;
	params.dispatch.retval = M2M_ERR_TIME_OUT;
	params.arg = ScanRegion;
	params.fn = (func_uint8)(m2m_wifi_set_scan_region);
	OS_WIFI_DISPATCH_WAIT(func_uint_imp, &params);
	return params.dispatch.retval;
}


uint8 os_m2m_wifi_get_num_ap_found(void)
{
	struct void_params params;
	params.dispatch.retval = (int8_t)M2M_ERR_TIME_OUT;
	params.fn = (func_void)m2m_wifi_get_num_ap_found;
	OS_WIFI_DISPATCH_WAIT(func_void_imp, &params);
	return params.dispatch.retval;
}


sint8 os_m2m_wifi_req_scan_result(uint8 index)
{
	struct uint_params params;
	params.dispatch.retval = M2M_ERR_TIME_OUT;
	params.arg = index;
	params.fn = m2m_wifi_req_scan_result;
	OS_WIFI_DISPATCH_WAIT(func_uint_imp, &params);
	return params.dispatch.retval;
}


sint8 os_m2m_wifi_req_curr_rssi(void)
{
	struct void_params params;
	params.dispatch.retval = M2M_ERR_TIME_OUT;
	params.fn = m2m_wifi_req_curr_rssi;
	OS_WIFI_DISPATCH_WAIT(func_void_imp, &params);
	return params.dispatch.retval;
}


struct wifi_get_otp_mac_address_params {
	struct params_dispatch dispatch;
	uint8* pu8MacAddr;
	uint8* pu8IsValid;
};
static void os_m2m_wifi_get_otp_mac_address_imp(void *pv)
{
	struct wifi_get_otp_mac_address_params *p = (struct wifi_get_otp_mac_address_params *) pv;
	p->dispatch.retval = m2m_wifi_get_otp_mac_address(p->pu8MacAddr, p->pu8IsValid);
	OS_WIFI_NOTIFY(p);
}
sint8 os_m2m_wifi_get_otp_mac_address(uint8* pu8MacAddr, uint8* pu8IsValid)
{
	struct wifi_get_otp_mac_address_params params;
	params.pu8MacAddr = pu8MacAddr;
	params.pu8IsValid = pu8IsValid;
	OS_WIFI_DISPATCH_WAIT(os_m2m_wifi_get_otp_mac_address_imp, &params);
	return params.dispatch.retval;
}


struct wifi_get_mac_address_params {
	struct params_dispatch dispatch;
	uint8* pu8MacAddr;
};
static void os_m2m_wifi_get_mac_address_imp(void *pv)
{
	struct wifi_get_mac_address_params *p = (struct wifi_get_mac_address_params *) pv;
	p->dispatch.retval = m2m_wifi_get_mac_address(p->pu8MacAddr);
	OS_WIFI_NOTIFY(p);
}
sint8 os_m2m_wifi_get_mac_address(uint8* pu8MacAddr)
{
	struct wifi_get_mac_address_params params;
	params.pu8MacAddr = pu8MacAddr;
	OS_WIFI_DISPATCH_WAIT(os_m2m_wifi_get_mac_address_imp, &params);
	return params.dispatch.retval;
}


struct wifi_set_sleep_mode_params {
	struct params_dispatch dispatch;
	uint8 PsTyp;
	uint8 BcastEn;
};
static void os_m2m_wifi_set_sleep_mode_imp(void *pv)
{
	struct wifi_set_sleep_mode_params *p = (struct wifi_set_sleep_mode_params *) pv;
	p->dispatch.retval = m2m_wifi_set_sleep_mode(p->PsTyp, p->BcastEn);
	OS_WIFI_NOTIFY(p);
}
sint8 os_m2m_wifi_set_sleep_mode(uint8 PsTyp, uint8 BcastEn)
{
	struct wifi_set_sleep_mode_params params;
	params.PsTyp = PsTyp;
	params.BcastEn = BcastEn;
	OS_WIFI_DISPATCH_WAIT(os_m2m_wifi_set_sleep_mode_imp, &params);
	return params.dispatch.retval;
}


struct wifi_request_sleep_params {
	struct params_dispatch dispatch;
	uint32 u32SlpReqTime;
};
static void os_m2m_wifi_request_sleep_imp(void *pv)
{
	struct wifi_request_sleep_params *p = (struct wifi_request_sleep_params *) pv;
	p->dispatch.retval = m2m_wifi_request_sleep(p->u32SlpReqTime);
	OS_WIFI_NOTIFY(p);
}
sint8 os_m2m_wifi_request_sleep(uint32 u32SlpReqTime)
{
	struct wifi_request_sleep_params params;
	params.u32SlpReqTime = u32SlpReqTime;
	OS_WIFI_DISPATCH_WAIT(os_m2m_wifi_request_sleep_imp, &params);
	return params.dispatch.retval;
}


sint8 os_m2m_wifi_req_client_ctrl(uint8 cmd)
{
	struct uint_params params;
	params.dispatch.retval = M2M_ERR_TIME_OUT;
	params.arg = cmd;
	params.fn = m2m_wifi_req_client_ctrl;
	OS_WIFI_DISPATCH_WAIT(func_uint_imp, &params);
	return params.dispatch.retval;
}


sint8 os_m2m_wifi_req_server_init(uint8 ch)
{
	struct uint_params params;
	params.dispatch.retval = M2M_ERR_TIME_OUT;
	params.arg = ch;
	params.fn = m2m_wifi_req_server_init;
	OS_WIFI_DISPATCH_WAIT(func_uint_imp, &params);
	return params.dispatch.retval;
}


struct wifi_set_device_name_params {
	struct params_dispatch dispatch;
	uint8* pu8DeviceName;
	uint8 u8DeviceNameLength;
};
static void os_m2m_wifi_set_device_name_imp(void *pv)
{
	struct wifi_set_device_name_params *p = (struct wifi_set_device_name_params *) pv;
	p->dispatch.retval = m2m_wifi_set_device_name(p->pu8DeviceName, p->u8DeviceNameLength);
	OS_WIFI_NOTIFY(p);
}
sint8 os_m2m_wifi_set_device_name(uint8* pu8DeviceName, uint8 u8DeviceNameLength)
{
	struct wifi_set_device_name_params params;
	params.pu8DeviceName = pu8DeviceName;
	params.u8DeviceNameLength = u8DeviceNameLength;
	OS_WIFI_DISPATCH_WAIT(os_m2m_wifi_set_device_name_imp, &params);
	return params.dispatch.retval;
}


struct wifi_set_lsn_int_params {
	struct params_dispatch dispatch;
	tstrM2mLsnInt* pstrM2mLsnInt;
};
static void os_m2m_wifi_set_lsn_int_imp(void *pv)
{
	struct wifi_set_lsn_int_params *p = (struct wifi_set_lsn_int_params *) pv;
	p->dispatch.retval = m2m_wifi_set_lsn_int(p->pstrM2mLsnInt);
	OS_WIFI_NOTIFY(p);
}
sint8 os_m2m_wifi_set_lsn_int(tstrM2mLsnInt* pstrM2mLsnInt)
{
	struct wifi_set_lsn_int_params params;
	params.pstrM2mLsnInt = pstrM2mLsnInt;
	OS_WIFI_DISPATCH_WAIT(os_m2m_wifi_set_lsn_int_imp, &params);
	return params.dispatch.retval;
}


struct wifi_enable_monitoring_mode_params {
	struct params_dispatch dispatch;
	tstrM2MWifiMonitorModeCtrl* pstrMtrCtrl;
	uint8* pu8PayloadBuffer;
	uint16 u16BufferSize;
	uint16 u16DataOffset;
};
static void os_m2m_wifi_enable_monitoring_mode_imp(void *pv)
{
	struct wifi_enable_monitoring_mode_params *p = (struct wifi_enable_monitoring_mode_params *) pv;
	p->dispatch.retval = m2m_wifi_enable_monitoring_mode(p->pstrMtrCtrl, p->pu8PayloadBuffer, p->u16BufferSize, p->u16DataOffset);
	OS_WIFI_NOTIFY(p);
}
sint8 os_m2m_wifi_enable_monitoring_mode(tstrM2MWifiMonitorModeCtrl* pstrMtrCtrl, uint8* pu8PayloadBuffer, uint16 u16BufferSize, uint16 u16DataOffset)
{
	struct wifi_enable_monitoring_mode_params params;
	params.pstrMtrCtrl = pstrMtrCtrl;
	params.pu8PayloadBuffer = pu8PayloadBuffer;
	params.u16BufferSize = u16BufferSize;
	params.u16DataOffset = u16DataOffset;
	OS_WIFI_DISPATCH_WAIT(os_m2m_wifi_enable_monitoring_mode_imp, &params);
	return params.dispatch.retval;
}


sint8 os_m2m_wifi_disable_monitoring_mode(void)
{
	struct void_params params;
	params.dispatch.retval = M2M_ERR_TIME_OUT;
	params.fn = m2m_wifi_disable_monitoring_mode;
	OS_WIFI_DISPATCH_WAIT(func_void_imp, &params);
	return params.dispatch.retval;
}


struct wifi_send_wlan_pkt_params {
	struct params_dispatch dispatch;
	uint8* pu8WlanPacket;
	uint16 u16WlanHeaderLength;
	uint16 u16WlanPktSize;
};
static void os_m2m_wifi_send_wlan_pkt_imp(void *pv)
{
	struct wifi_send_wlan_pkt_params *p = (struct wifi_send_wlan_pkt_params *) pv;
	p->dispatch.retval = m2m_wifi_send_wlan_pkt(p->pu8WlanPacket, p->u16WlanHeaderLength, p->u16WlanPktSize);
	OS_WIFI_NOTIFY(p);
}
sint8 os_m2m_wifi_send_wlan_pkt(uint8* pu8WlanPacket, uint16 u16WlanHeaderLength, uint16 u16WlanPktSize)
{
	struct wifi_send_wlan_pkt_params params;
	params.pu8WlanPacket = pu8WlanPacket;
	params.u16WlanHeaderLength = u16WlanHeaderLength;
	params.u16WlanPktSize = u16WlanPktSize;
	OS_WIFI_DISPATCH_WAIT(os_m2m_wifi_send_wlan_pkt_imp, &params);
	return params.dispatch.retval;
}


struct wifi_send_ethernet_pkt_params {
	struct params_dispatch dispatch;
	uint8* pu8Packet;
	uint16 u16PacketSize;
};
static void os_m2m_wifi_send_ethernet_pkt_imp(void *pv)
{
	struct wifi_send_ethernet_pkt_params *p = (struct wifi_send_ethernet_pkt_params *) pv;
	p->dispatch.retval = m2m_wifi_send_ethernet_pkt(p->pu8Packet, p->u16PacketSize);
	OS_WIFI_NOTIFY(p);
}
sint8 os_m2m_wifi_send_ethernet_pkt(uint8* pu8Packet, uint16 u16PacketSize)
{
	struct wifi_send_ethernet_pkt_params params;
	params.pu8Packet = pu8Packet;
	params.u16PacketSize = u16PacketSize;
	OS_WIFI_DISPATCH_WAIT(os_m2m_wifi_send_ethernet_pkt_imp, &params);
	return params.dispatch.retval;
}

struct wifi_set_sytem_time_params {
	struct params_dispatch dispatch;
	uint32 u32UTCSeconds;
};
static void os_m2m_wifi_set_sytem_time_imp(void *pv)
{
	struct wifi_set_sytem_time_params *p = (struct wifi_set_sytem_time_params *) pv;
	p->dispatch.retval = m2m_wifi_set_system_time(p->u32UTCSeconds);
	OS_WIFI_NOTIFY(p);
}
sint8 os_m2m_wifi_set_sytem_time(uint32 u32UTCSeconds)
{
	struct wifi_set_sytem_time_params params;
	params.u32UTCSeconds = u32UTCSeconds;
	OS_WIFI_DISPATCH_WAIT(os_m2m_wifi_set_sytem_time_imp, &params);
	return params.dispatch.retval;
}


struct wifi_set_cust_InfoElement_params {
	struct params_dispatch dispatch;
	uint8* pau8M2mCustInfoElement;
};
static void os_m2m_wifi_set_cust_InfoElement_imp(void *pv)
{
	struct wifi_set_cust_InfoElement_params *p = (struct wifi_set_cust_InfoElement_params *) pv;
	p->dispatch.retval = m2m_wifi_set_cust_InfoElement(p->pau8M2mCustInfoElement);
	OS_WIFI_NOTIFY(p);
}
sint8 os_m2m_wifi_set_cust_InfoElement(uint8* pau8M2mCustInfoElement)
{
	struct wifi_set_cust_InfoElement_params params;
	params.pau8M2mCustInfoElement = pau8M2mCustInfoElement;
	OS_WIFI_DISPATCH_WAIT(os_m2m_wifi_set_cust_InfoElement_imp, &params);
	return params.dispatch.retval;
}


struct wifi_enable_mac_mcast_params {
	struct params_dispatch dispatch;
	uint8* pu8MulticastMacAddress;
	uint8 u8AddRemove;
};
static void os_m2m_wifi_enable_mac_mcast_imp(void *pv)
{
	struct wifi_enable_mac_mcast_params *p = (struct wifi_enable_mac_mcast_params *) pv;
	p->dispatch.retval = m2m_wifi_enable_mac_mcast(p->pu8MulticastMacAddress, p->u8AddRemove);
	OS_WIFI_NOTIFY(p);
}
sint8 os_m2m_wifi_enable_mac_mcast(uint8* pu8MulticastMacAddress, uint8 u8AddRemove)
{
	struct wifi_enable_mac_mcast_params params;
	params.pu8MulticastMacAddress = pu8MulticastMacAddress;
	params.u8AddRemove = u8AddRemove;
	OS_WIFI_DISPATCH_WAIT(os_m2m_wifi_enable_mac_mcast_imp, &params);
	return params.dispatch.retval;
}


struct wifi_set_receive_buffer_params {
	struct params_dispatch dispatch;
	void* pvBuffer;
	uint16 u16BufferLen;
};
static void os_m2m_wifi_set_receive_buffer_imp(void *pv)
{
	struct wifi_set_receive_buffer_params *p = (struct wifi_set_receive_buffer_params *) pv;
	p->dispatch.retval = m2m_wifi_set_receive_buffer(p->pvBuffer, p->u16BufferLen);
	OS_WIFI_NOTIFY(p);
}
sint8 os_m2m_wifi_set_receive_buffer(void* pvBuffer, uint16 u16BufferLen)
{
	struct wifi_set_receive_buffer_params params;
	params.pvBuffer = pvBuffer;
	params.u16BufferLen = u16BufferLen;
	OS_WIFI_DISPATCH_WAIT(os_m2m_wifi_set_receive_buffer_imp, &params);
	return params.dispatch.retval;
}

uint8 os_m2m_wifi_get_sleep_mode(void)
{
	struct void_params params;
	params.dispatch.retval = (int8_t)M2M_ERR_TIME_OUT;
	params.fn = (func_void)m2m_wifi_get_sleep_mode;
	OS_WIFI_DISPATCH_WAIT(func_void_imp, &params);
	return params.dispatch.retval;
}
