/**
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
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "application.h"
#include "FreeRTOS.h"
#include "osprintf.h"
#include "os/include/net_init.h"
#include "os/include/m2m_wifi_ex.h"
#include "lwip/def.h"
#include "at_cmd_handler/at_cmd_Handler.h"
#include "iperf/iperf.h"
#include "http_downloader/httpdownloader.h"
#include "ota_fw_update/ota_fw_update.h"
#include "lwip/sockets.h"
#include "lwip/api.h"
#include "lwip/netdb.h"
#include <string.h>
#include <stdio.h>

/** IP address parsing. */
#define IPV4_BYTE(val, index)                ((val >> (index * 8)) & 0xFF)
/** Convert a 2-byte integer (short) from the host representation to the Network byte order representation. */
#define _htons(A)   	(uint16)((((uint16) (A)) << 8) | (((uint16) (A)) >> 8))
#define STRING_EOL    "\r\n"
/*Split HTTP request into two to insert the host name*/
#define HTTP_REQUEST_PART1 "OPTIONS * HTTP/1.1"STRING_EOL \
			"User-Agent: atmel/1.0.2"STRING_EOL \
			"Host: "
#define HTTP_REQUEST_PART2	STRING_EOL"Connection: Keep-Alive"STRING_EOL \
			"Accept-Encoding: "STRING_EOL \
			"Accept-Charset: utf-8"STRING_EOL \
			STRING_EOL 
#define SEND_BUF_SIZE 256
#define RECV_BUF_SIZE 256
			
/** Message format definitions. */
typedef struct s_msg_wifi_product {
	uint8_t name[30];
} t_msg_wifi_product;

/** Message format declarations. */
static t_msg_wifi_product msg_wifi_product = {
	.name = MAIN_WIFI_M2M_PRODUCT_NAME
};
uint32_t local_ip;

xSemaphoreHandle at_cmd_task1_sem;

/** Firmware start event */
static xSemaphoreHandle firmware_start_sem = NULL;

extern uint8 u8DataSubType[AT_MAX_DATA_SUBTYPE];
extern uint8 u8ControlSubtype[AT_MAX_CONTROL_SUBTYPE];
extern uint8 u8MangmentSubtype[AT_MAX_MANGEMENT_SUBTYPE];
extern tstrMonstats gstrMonitorDataStats;
extern tstrMonstats gstrMonitorControlStats;
extern tstrMonstats gstrMonitorMangementStats;
static int npkt =0;
/**
 * \brief Callback to get the Wi-Fi status update.
 *
 * \param[in] u8MsgType type of Wi-Fi notification. Possible types are:
 *  - [M2M_WIFI_RESP_CON_STATE_CHANGED](@ref M2M_WIFI_RESP_CON_STATE_CHANGED)
 *  - [M2M_WIFI_REQ_DHCP_CONF](@ref M2M_WIFI_REQ_DHCP_CONF)
 * \param[in] pvMsg A pointer to a buffer containing the notification parameters
 * (if any). It should be casted to the correct data type corresponding to the
 * notification type.
 */
static void wifi_cb(uint8_t u8MsgType, void *pvMsg)
{
	uint8 au8CmdTxt[AT_MAX_CMD_LENGTH]={0};
	static uint8	u8ScanResultIdx = 0;
	switch (u8MsgType) {
		case M2M_WIFI_RESP_CON_STATE_CHANGED:
		{
			tstrM2mWifiStateChanged *pstrWifiState = (tstrM2mWifiStateChanged *)pvMsg;
			if (pstrWifiState->u8IfcId == STATION_INTERFACE) {
				if (pstrWifiState->u8CurrState == M2M_WIFI_CONNECTED) {
					M2M_INFO("Wifi State :: CONNECTED ::\r\n");
					if(use_static_IP == 1) {
						ip_addr_t ipaddr, netmask, gw;
						IP4_ADDR(&netmask, 255,255,255,0);
						ipaddr.addr = StaticIPcfg.u32StaticIP;
						gw.addr = StaticIPcfg.u32Gateway;
						net_set_interface_address(NET_IF_STA,&ipaddr,&netmask,&gw);
						m2m_wifi_request_static_client_ex();
						// net_interface_up should not be made common to DHCP & Static IP as use_static_IP = 1 is required inside.
						net_interface_up(NET_IF_STA); 
						use_static_IP = 0;
					}
					else {
						m2m_wifi_request_dhcp_client_ex();
						net_interface_up(NET_IF_STA);
					}

				} else if (pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED) {
					M2M_INFO("Wifi State :: DISCONNECTED ::\r\n");
					if(gstrAllStatus.u8Sta_status == SERVICE_IS_RUNNING) {
						gstrAllStatus.u8Sta_status = SERVICE_IS_STOPPED;
						//get_cmd_txt(AT_INDEX_DISCONN, (uint8 *)au8CmdTxt);
						AT_SEND_OK("DISCONN");
					}
					net_interface_down(NET_IF_STA);
				}
			}
			else if (pstrWifiState->u8IfcId == AP_INTERFACE) {
				uint8 isDeviceMac = 1;
				if (pstrWifiState->u8CurrState == M2M_WIFI_CONNECTED) {
					uint8 pu8MacAddr0[6], pu8MacAddr1[6];
					if(m2m_wifi_get_mac_address(pu8MacAddr0, pu8MacAddr1) != M2M_SUCCESS){ //failed get Device MAC
						osprintf("Failed to get Device MAC\r\n");
						osprintf("wifi_cb : M2M_WIFI_CONNECTED for MAC %02x:%02x:%02x:%02x:%02x:%02x\r\n", pstrWifiState->u8MAcAddr[0], pstrWifiState->u8MAcAddr[1],\
						pstrWifiState->u8MAcAddr[2], pstrWifiState->u8MAcAddr[3], pstrWifiState->u8MAcAddr[4], pstrWifiState->u8MAcAddr[5]);
						break;
					}
					//Check MAC with Device MAC
					for(int i=0; i<6; i++){
						if(pstrWifiState->u8MAcAddr[i] != pu8MacAddr0[i]){
							isDeviceMac = 0;
							break;
						}
					}
					
					if(!isDeviceMac) {
						osprintf("Station connected    %02x:%02x:%02x:%02x:%02x:%02x\r\n", pstrWifiState->u8MAcAddr[0], pstrWifiState->u8MAcAddr[1],\
						pstrWifiState->u8MAcAddr[2], pstrWifiState->u8MAcAddr[3], pstrWifiState->u8MAcAddr[4], pstrWifiState->u8MAcAddr[5]);
					}
					else  {
						osprintf("AP mode started.\r\n");
						gstrAllStatus.u8Ap_status = SERVICE_IS_RUNNING;
						AT_SEND_OK("AP_EN");
					}
				} else if (pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED) {
					osprintf("Station disconnected %02x:%02x:%02x:%02x:%02x:%02x\r\n", pstrWifiState->u8MAcAddr[0], pstrWifiState->u8MAcAddr[1],\
					pstrWifiState->u8MAcAddr[2], pstrWifiState->u8MAcAddr[3], pstrWifiState->u8MAcAddr[4], pstrWifiState->u8MAcAddr[5]);
				}
				break;
			}			
			else if (pstrWifiState->u8IfcId == P2P_INTERFACE) {
				if (pstrWifiState->u8CurrState == M2M_WIFI_CONNECTED) {
					osprintf("wifi_cb: P2P: M2M_WIFI_CONNECTED\r\n");
					osprintf("P2P connected %02x:%02x:%02x:%02x:%02x:%02x\r\n", pstrWifiState->u8MAcAddr[0], pstrWifiState->u8MAcAddr[1],\
					pstrWifiState->u8MAcAddr[2], pstrWifiState->u8MAcAddr[3], pstrWifiState->u8MAcAddr[4], pstrWifiState->u8MAcAddr[5]);
				}
				if(pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED) {
					osprintf("wifi_cb: P2P: M2M_WIFI_DISCONNECTED\r\n");
				}
			}	
			break;
		}

		case NET_IF_REQ_DHCP_CONF :
		{
			tstrM2MIPConfig2 *strIpConfig = pvMsg;
			uint16_t *a = (void *)strIpConfig->u8StaticIPv6;
			M2M_INFO("DHCP IP Address \"%u.%u.%u.%u\"\r\n",strIpConfig->u8StaticIP[0], strIpConfig->u8StaticIP[1],strIpConfig->u8StaticIP[2], strIpConfig->u8StaticIP[3]);
			AT_SEND_OK("");
			osprintf("wifi_cb: STA IPv6 addr: %04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x\r\n",
			htons(a[0]), htons(a[1]), htons(a[2]), htons(a[3]),
			htons(a[4]), htons(a[5]), htons(a[6]), htons(a[7]));
			gstrAllStatus.u8Sta_status = SERVICE_IS_RUNNING;
			local_ip = (uint32_t)(strIpConfig->u8StaticIP[0]<<24 | strIpConfig->u8StaticIP[1]<<16 | strIpConfig->u8StaticIP[2]<<8 | strIpConfig->u8StaticIP[3]);
		}
		break;
		case M2M_WIFI_RESP_CURRENT_RSSI:
		{
			/* This message type is triggered by "m2m_wifi_req_curr_rssi()" function. */
			int8_t *rssi = (int8_t *)pvMsg;
			osprintf("RSSI for the current connected AP (%d)\r\n", (int8_t)(*rssi));
			get_cmd_txt(AT_INDEX_RSSI, (uint8 *)au8CmdTxt);
			AT_SEND_OK(au8CmdTxt);
			break;
		}
		case M2M_WIFI_RESP_SCAN_DONE:
		{
			tstrM2mScanDone	*pstrInfo = (tstrM2mScanDone*)pvMsg;
			
			printf("Num of AP found %d\r\n",pstrInfo->u8NumofCh);
			if(pstrInfo->s8ScanState == M2M_SUCCESS)
			{
				u8ScanResultIdx = 0;
				if(pstrInfo->u8NumofCh >= 1)
				{
					printf("requesting result%d\r\n",u8ScanResultIdx);
					m2m_wifi_req_scan_result(u8ScanResultIdx);
					u8ScanResultIdx ++;
				}
				else
				{
					printf("No AP Found\n");
					//m2m_wifi_request_scan(M2M_WIFI_CH_ALL);
				}
			}
			else
			{
				printf("(ERR) Scan fail with error <%d>\n",pstrInfo->s8ScanState);
			}
		}
		break;
		
		case M2M_WIFI_RESP_SCAN_RESULT:
		{
			tstrM2mWifiscanResult		*pstrScanResult =(tstrM2mWifiscanResult*)pvMsg;
			uint8						u8NumFoundAPs = os_m2m_wifi_get_num_ap_found();
			
			printf(">>%02d RI %d SEC %d CH %02d BSSID %02X:%02X:%02X:%02X:%02X:%02X SSID %s\r\n",
			pstrScanResult->u8index,pstrScanResult->s8rssi,
			pstrScanResult->u8AuthType,
			pstrScanResult->u8ch,
			pstrScanResult->au8BSSID[0], pstrScanResult->au8BSSID[1], pstrScanResult->au8BSSID[2],
			pstrScanResult->au8BSSID[3], pstrScanResult->au8BSSID[4], pstrScanResult->au8BSSID[5],
			pstrScanResult->au8SSID);
			
			if(u8ScanResultIdx < u8NumFoundAPs)
			{
				// Read the next scan result
				m2m_wifi_req_scan_result(u8ScanResultIdx);
				u8ScanResultIdx ++;
			}
		}
		break;
		case M2M_WIFI_RESP_CONN_INFO:
		{
			tstrM2MConnInfo		*pstrConnInfo = (tstrM2MConnInfo*)pvMsg;
				
			osprintf("SSID  : %s\r\n",pstrConnInfo->acSSID);
			osprintf("RSSI  : %d\r\n",pstrConnInfo->s8RSSI);
			osprintf("SEC   : %d\r\n",pstrConnInfo->u8SecType);
			char u8Buf[72];
			sprintf(u8Buf,"GET_CONN_INFO,%s,%d,%d", pstrConnInfo->acSSID,pstrConnInfo->s8RSSI,pstrConnInfo->u8SecType);
			AT_SEND_OK(u8Buf);
		}
		break;
		case M2M_WIFI_RES_WPS:
		{
			tstrM2MWPSInfo *pstrWPS = (tstrM2MWPSInfo *)pvMsg;
			//printf("WPS Response -> SSID : %s, authtyp : %d pw : %s\r\n", pstrWPS->au8SSID, pstrWPS->u8AuthType, pstrWPS->au8PSK);
			if (pstrWPS->u8AuthType == 0) {
				printf("WPS is disabled or timed out\r\n");
			} else {
				vTaskDelay(1000);
				printf("Connecting to %s\r\n", pstrWPS->au8SSID);
				os_m2m_wifi_connect((char *)pstrWPS->au8SSID, (uint8)m2m_strlen(pstrWPS->au8SSID),
				pstrWPS->u8AuthType, (void *)pstrWPS->au8PSK, pstrWPS->u8Ch);
			}

			break;
		}
		case M2M_WIFI_REQ_P2P_AUTH:
		{
			tstrM2MP2pDevInfo *pstrP2PDevInfo = (tstrM2MP2pDevInfo *)pvMsg;
			if (pstrP2PDevInfo->u16CfgMethods & CONF_METHOD_KEYPAD) {
				osprintf("\r\nPlease enter P2P pin\r\n(Usage: P2P_PIN <pin-number displayed on phone>\r\n");
			}
			else if (pstrP2PDevInfo->u16CfgMethods & CONF_METHOD_DISPLAY){
				osprintf("\r\nPlease enter P2P pin on phone <12345678>\r\n");
					/* Set device name. */
					os_m2m_wifi_set_p2p_pin((uint8_t *)"12345678", 8);
			}
			else {
				osprintf("\r\nAllow pushbutton method\r\n");
				m2m_wifi_allow_p2p_connection();
			}
			break;
		}
		case M2M_WIFI_RESP_FIRMWARE_STRTED: {
			osprintf("Firmware Started Successfully\r\n");
			if (firmware_start_sem != NULL) {
				xSemaphoreGive(firmware_start_sem);
			}
		}
		break;		
		default:
		{
			break;
		}
	}
}

static void wifi_monitoring_cb(tstrM2MWifiRxPacketInfo *pstrWifiRxPacket, uint8 *pu8Payload, uint16 u16PayloadSize)
{
	if((pstrWifiRxPacket != NULL) && (u16PayloadSize != 0))
	{
		//M2M_INFO("*** MONITOR PACKET ***\r\n");
		if(pstrWifiRxPacket->u8FrameType == MANAGEMENT)
		{
			int i;
			gstrMonitorMangementStats.s32AnyDataFrame++;
			for(i=0;i<AT_MAX_MANGEMENT_SUBTYPE;i++)
			{
				if(u8MangmentSubtype[i] == pstrWifiRxPacket->u8FrameSubtype)
				{
					gstrMonitorMangementStats.strFilterSubtype[i].s32NumPkt++;
				}
			}
		}
		else if(pstrWifiRxPacket->u8FrameType == CONTROL)
		{
			int i;
			gstrMonitorControlStats.s32AnyDataFrame++;
			for(i=0;i<AT_MAX_CONTROL_SUBTYPE;i++)
			{
				if(u8ControlSubtype[i] == pstrWifiRxPacket->u8FrameSubtype)
				{
					gstrMonitorControlStats.strFilterSubtype[i].s32NumPkt++;
				}
			}
		}
		else if(pstrWifiRxPacket->u8FrameType == DATA_BASICTYPE)
		{
			int i;
			//M2M_INFO("***# DATA PACKET #***\r\n");
			//M2M_INFO("ST : %02X\r\n",pstrWifiRxPacket->u8FrameSubtype);
			gstrMonitorDataStats.s32AnyDataFrame++;
			for(i=0;i<AT_MAX_DATA_SUBTYPE;i++)
			{
				if(u8DataSubType[i] == pstrWifiRxPacket->u8FrameSubtype)
				{
					gstrMonitorDataStats.strFilterSubtype[i].s32NumPkt++;
				}
			}
		}

		if(pstrWifiRxPacket->u8FrameSubtype==0x08 || pstrWifiRxPacket->u8FrameSubtype==0x88)
		{
			//if(pstrWifiRxPacket->au8SrcMacAddress[5] == 0xC7 || pstrWifiRxPacket->au8DstMacAddress[5] == 0xC7)
			{
				M2M_INFO("SRC: %02X:%02X:%02X:%02X:%02X:%02X\t",
				pstrWifiRxPacket->au8SrcMacAddress[0],pstrWifiRxPacket->au8SrcMacAddress[1],pstrWifiRxPacket->au8SrcMacAddress[2],
				pstrWifiRxPacket->au8SrcMacAddress[3],pstrWifiRxPacket->au8SrcMacAddress[4],pstrWifiRxPacket->au8SrcMacAddress[5]);
				M2M_INFO("DST: %02X:%02X:%02X:%02X:%02X:%02X\r\n",
				pstrWifiRxPacket->au8DstMacAddress[0],pstrWifiRxPacket->au8DstMacAddress[1],pstrWifiRxPacket->au8DstMacAddress[2],
				pstrWifiRxPacket->au8DstMacAddress[3],pstrWifiRxPacket->au8DstMacAddress[4],pstrWifiRxPacket->au8DstMacAddress[5]);
			}
		}
		npkt++;
		if(npkt >= MON_MODE_MAX_PKT_COUNT)
		{
			os_m2m_wifi_disable_monitoring_mode();
			printf("Max packet count(%d) reached. Hence, stopping monitoring mode\r\n", npkt);
			print_monitoring_result();
			npkt=0;
		}
	}
}

void tcp_server()
{
#if LWIP_SOCKET == 1
	/** Socket for tcp */
	static sint8 tcp_socket = -1;
	/** Test buffer */
	static uint8_t gau8SocketTestBuffer[MAIN_WIFI_M2M_BUFFER_SIZE];
	tstrAt_cmd_content * at_server_cmd = (tstrAt_cmd_content *) &temp_cmd_content;
	int8_t ret, NewSocket, Received;
	uint16 portnum = 0;
	struct sockaddr_in addr;
	struct sockaddr_in remote_addr;
	/** tcp packet count */
	static uint8_t packetCnt = 0;
	portnum = atoi((char *)at_server_cmd->au8ParamsList[1]);
	printf("port num %d %d %s\r\n", portnum, at_server_cmd->u8NumOfParameters, (char*)at_server_cmd->au8Cmd);

	/* Initialize socket address structure. */
	addr.sin_family = AF_INET;
	addr.sin_port = htons(portnum);
	addr.sin_addr.s_addr = htonl(local_ip);
	
	/* Initialize,  create and connect socket in WILC module */
	tcp_socket= socket(AF_INET, SOCK_STREAM /*for tcp*/, 0/*flag*/);  //tcp socket creation

	if(tcp_socket < 0){
		printf("Failed to create TCP Server Socket !\r\n");
		return;
	}

	/* Connect socket. */
	ret = bind(tcp_socket, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));
	if(ret>=0){
		printf("TCP Server Socket Bind done !\r\n");
	}
	else{
		printf("TCP Server Socket Bind failed !\r\n");
		goto EXIT;
	}
	ret = listen(tcp_socket, 0);
	if(ret>=0){
		printf("TCP Server Socket in Listen mode !\r\n");
	} else {
		printf("TCP Server Socket not in Listen mode !\r\n");
		goto EXIT;
	}

	unsigned int len;
	NewSocket = accept(tcp_socket, (struct sockaddr*)&remote_addr, &len);

	if(NewSocket>=0){
		printf("TCP Server Socket is ready to accept data!\r\n");
	}
	else{
		printf("TCP Server - Accept failed!\r\n");
		goto EXIT;
	}
	
	while (1) {
		Received = recv(NewSocket, gau8SocketTestBuffer, MAIN_WIFI_M2M_BUFFER_SIZE, 0x00);
			
		if(Received>=0){
			printf("Number of packets received from TCP Client : %d !\r\n",Received);
		}
		else{
			printf("No packets received from TCP Client  !\r\n");
			goto EXIT;
		}
			
		/* Prepare next buffer reception. */
		printf("Received data : %s !\r\n",gau8SocketTestBuffer);
		if (++packetCnt >= MAIN_WIFI_M2M_PACKET_COUNT) {
			osprintf("TCP Server Test Complete!\r\n");
			goto EXIT;
		}
	}
EXIT:
	close(tcp_socket);
	return;
#endif
}
void tcp_client(){
#if LWIP_SOCKET == 1
	/** Socket for tcp */
	static sint8 tcp_socket = -1;
	tstrAt_cmd_content * at_server_cmd = (tstrAt_cmd_content *)&temp_cmd_content;
	int8_t ret;
	uint8 u8LoopCntr, *pu8Dat = NULL;
	uint16 portnum = 0;
	uint32_t ServerIP[4];
	struct sockaddr_in addr;
	/** tcp packet count */
	uint8_t packetCnt = 0;
	char * pServerIPTemp = (char *)at_server_cmd->au8ParamsList[1];
	pu8Dat = (uint8 *)strtok(pServerIPTemp,".");
	for(u8LoopCntr=0; u8LoopCntr<4; u8LoopCntr++) {
		ServerIP[u8LoopCntr] = atoi((const char *)pu8Dat);
		pu8Dat = (uint8 *)strtok(NULL,".");
	}
	portnum = atoi((char *)at_server_cmd->au8ParamsList[2]);
	printf("port num : %d\r\n", portnum);
	printf("Server IP : %2ld.%2ld.%2ld.%2ld\r\n", ServerIP[0], ServerIP[1], ServerIP[2], ServerIP[3]);

	/* Initialize socket address structure. */
	addr.sin_family = AF_INET;
	addr.sin_port = htons(portnum);
	addr.sin_addr.s_addr = htonl((uint32_t)(ServerIP[0]<<24 | ServerIP[1]<<16 | ServerIP[2]<<8 | ServerIP[3]));

	/* Create and connect client socket. */
	tcp_socket= socket(AF_INET, SOCK_STREAM /*for TCP*/, 0/*flag*/);  //tcp socket creation
	if(tcp_socket < 0){
		printf("Failed to create TCP client Socket !\r\n");
		return;
	}
	while (1) {
		ret = connect(tcp_socket, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
		if(ret >= 0){
			osprintf("Connected to server!\r\n");
		} else {
			osprintf("Failed to connect to TCP server!\r\n");
			goto EXIT;
		}
		
		ret = send(tcp_socket, &msg_wifi_product, sizeof(t_msg_wifi_product), 0);
		vTaskDelay(20);
		
		if ( ret >= 0 ) {
			packetCnt += 1;
			osprintf("Packets sent :%d last packet size %d\r\n",(packetCnt),ret);
		}
		if (packetCnt == MAIN_WIFI_M2M_PACKET_COUNT) {
			osprintf("TCP Client Test Complete!\n\r");
			goto EXIT;
		}
	}
EXIT:
	close(tcp_socket);
	return;
#endif
}

void udp_server(){
#if LWIP_SOCKET == 1
	/** Socket for tcp */
	static sint8 udp_socket = -1;
	tstrAt_cmd_content * at_server_cmd = (tstrAt_cmd_content *)&temp_cmd_content;
	int8_t ret, Received;
	uint16 portnum = 0;
	struct sockaddr_in addr;
	/** tcp packet count */
	static uint8_t packetCnt = 0;
	/** Test buffer */
	static uint8_t gau8SocketTestBuffer[MAIN_WIFI_M2M_BUFFER_SIZE] = {0,};
	
	portnum = atoi((char *)at_server_cmd->au8ParamsList[1]);

	/* Initialize socket address structure. */
	addr.sin_family = AF_INET;
	addr.sin_port = htons(portnum);
	addr.sin_addr.s_addr = htonl(local_ip);

	/* Initialize,  create and connect socket in WILC module */
	udp_socket= socket(AF_INET, SOCK_DGRAM /*for UDP*/, 0/*flag*/);  //UDP socket creation

	if(udp_socket>=0){
		osprintf("Created UDP server socket!\r\n");
	} else {
		osprintf("Failed to create UDP server socket !\r\n");
		return;
	}

	/* Socket bind in WILC */
	ret = bind(udp_socket, (struct sockaddr*)&addr, sizeof(addr));
	if(ret >= 0){
		osprintf("UDP socket bind done !\r\n");
	} else {
		osprintf("UDP socket bind failed !\r\n");
		goto EXIT;
	}

	packetCnt = 0;
	while (1) {
		Received = recv(udp_socket, gau8SocketTestBuffer, sizeof(gau8SocketTestBuffer), 0);
		if(Received > 0){
			gau8SocketTestBuffer[Received] = '\0';
			printf("Received : %s\r\n",(char *)gau8SocketTestBuffer);
			packetCnt++;
		} else {
			osprintf("No packets received from UDP Client  !\r\n");
			goto EXIT;
		}

		if (packetCnt >= MAIN_WIFI_M2M_PACKET_COUNT) {
			printf("UDP Server test Complete!\r\n");
			goto EXIT;
		}
	}
EXIT:	
	close(udp_socket);
	return;
#endif
}

void udp_client(){
#if LWIP_SOCKET == 1
	/** Socket for tcp */
	static sint8 udp_socket = -1;
	tstrAt_cmd_content * at_server_cmd = (tstrAt_cmd_content *)&temp_cmd_content;
	int8_t ret;
	uint8 u8LoopCntr, *pu8Dat = NULL;
	uint16 portnum = 0;
	uint32_t ServerIP[4];
	struct sockaddr_in addr;
	/** tcp packet count */
	uint8_t packetCnt = 0;
	
	pu8Dat = (uint8 *)strtok((char *)at_server_cmd->au8ParamsList[1],".");
	for(u8LoopCntr=0; u8LoopCntr<4; u8LoopCntr++) {
		ServerIP[u8LoopCntr] = atoi((const char *)pu8Dat);
		pu8Dat = (uint8 *)strtok(NULL,".");
	}
	portnum = atoi((char *)at_server_cmd->au8ParamsList[2]);

	/* Initialize socket address structure. */
	addr.sin_family = AF_INET;
	addr.sin_port = htons(portnum);
	addr.sin_addr.s_addr = htonl(ServerIP[0]<<24 | ServerIP[1]<<16 | ServerIP[2]<<8 | ServerIP[3]);
	/* Create and connect client socket. */
	udp_socket= socket(AF_INET, SOCK_DGRAM /*for UDP*/, 0/*flag*/);  //UDP socket creation
	if(udp_socket>=0){
		osprintf("Created UDP client socket!\r\n");
	} else {
		osprintf("Failed to create UDP client socket !\r\n");
		return;
	}

	while (1) {
		/* Send client frame. */
		ret = sendto(udp_socket, &msg_wifi_product, sizeof(t_msg_wifi_product), 0, (struct sockaddr *)&addr, sizeof(addr));
		vTaskDelay(20);

		if ( ret >= 0 ) {
			packetCnt += 1;
			osprintf("Packets sent : %d\r\n",(packetCnt));
		} else {
			osprintf("Failed to send udp packet!\n\r");
			goto EXIT;
		}
		if (packetCnt == MAIN_WIFI_M2M_PACKET_COUNT) {
			osprintf("UDP Client test completed!\n\r");
			goto EXIT;
		}
	}
EXIT:
	close(udp_socket);
	return;
#endif
}

void http_connection(char *host_name, uint16 port){
	struct sockaddr_in addr_in;
	sint8 sock;
	uint8_t buffer[SEND_BUF_SIZE];
	uint8_t recv_buffer[SEND_BUF_SIZE];
	int ret;
	int32_t bytes_received = 0;
	sock = socket(AF_INET, SOCK_STREAM, NETCONN_TCP);
	struct hostent* hostent_local = gethostbyname(host_name);
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = _htons(port);
	addr_in.sin_addr.s_addr = (*((in_addr_t *) *(hostent_local->h_addr_list)));
	osprintf("IP address of host %s is %d.%d.%d.%d\r\n\r\n", host_name,
		(int)IPV4_BYTE(addr_in.sin_addr.s_addr, 0), (int)IPV4_BYTE(addr_in.sin_addr.s_addr, 1),
		(int)IPV4_BYTE(addr_in.sin_addr.s_addr, 2), (int)IPV4_BYTE(addr_in.sin_addr.s_addr, 3));
	ret = connect(sock, (struct sockaddr *)&addr_in, sizeof(struct sockaddr_in));
	if(0 != ret){
		printf("socket creation failed\r\n");
		return;
	}else{
		printf("connection to %s is successful\r\n", host_name);
	}
	struct timeval tv;
	/*set socket timeout, to avoid waiting forever in recv*/
	tv.tv_sec = 20;
	tv.tv_usec = 0;
	if(setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,(struct timeval *)&tv,sizeof(tv)) < 0){
		osprintf("set opt timeout failed \r\n");
	}
	strcpy((char *)buffer, HTTP_REQUEST_PART1);
	strcat((char *)buffer, host_name);
	strcat((char *)buffer, HTTP_REQUEST_PART2);
		
	printf("sending test http request\r\n%s", buffer);
	//printf("%s", buffer);
	/*sending a HTTP request for checking*/
	ret = send(sock, (void*)buffer, SEND_BUF_SIZE, 0);
	if(ret < 0){
		printf("failed to send data\r\n");
		return;
	}
	bytes_received = recv(sock, recv_buffer, RECV_BUF_SIZE, 0);
	if(bytes_received > 0){
		printf("Response received\r\n");
		//printf("Received data :\r\n%s\r\n", recv_buffer);
	}else{
		printf("No response received\r\n");
	}
	/*close the socket*/
	close(sock);
	printf("Done\r\n");
}

/**
 * \brief AT commands main function.
 */
void wilc_task_1(void *argument)
{
	
	/* For firmware start event */
	firmware_start_sem = xSemaphoreCreateCounting(1, 0);
	
	/* Initialize the network stack. */
	net_init();
	/* Initialize the WILC driver. */
	tstrWifiInitParam param;
	memset(&param, 0, sizeof(param));
	param.pfAppWifiCb = wifi_cb;
	param.pfAppMonCb = wifi_monitoring_cb;
	os_m2m_wifi_init(&param);
	
	/* Antenna modes are defined in sta.h */
#ifdef MAC_ANTENNA_DIVERSITY
	m2m_wifi_set_antenna_mode(ANT_MODE, ANT_SWTCH_GPIO_CTRL_MODE, ANTENNA_GPIO_NUM_1, ANTENNA_GPIO_NUM_2);
#endif
	
	/* Make sure we received M2M_WIFI_RESP_FIRMWARE_STRTED event in wifi_cb */
	if (firmware_start_sem != NULL) {
		xSemaphoreTake(firmware_start_sem, portMAX_DELAY);
		vSemaphoreDelete(firmware_start_sem);
	}	
	
#ifdef AT_CMD_SEM 
	vSemaphoreCreateBinary(at_cmd_task1_sem);
	xSemaphoreTake(at_cmd_task1_sem, portMAX_DELAY);
#endif
	while(1) {
#ifdef AT_CMD_SEM 
		xSemaphoreTake(at_cmd_task1_sem, portMAX_DELAY);
#endif 

		if(strcmp((const char *)temp_cmd_content.au8Cmd,"IPCON") == 0){
			if(strcmp((const char *)temp_cmd_content.au8ParamsList[0],"UDP") == 0){
				// Command is of the type: AT+IPCON=2[UDP,LOCAL_PORT] or AP+IPCON=3[UDP,@IP,REMOTE_PORT]
				if(temp_cmd_content.u8NumOfParameters == 2){
					udp_server();
				}else {
					udp_client();
				}
			}
			else if(strcmp((const char *)temp_cmd_content.au8ParamsList[0],"TCP") == 0){
				// Command is of the type: AT+IPCON=2[TCP,LOCAL_PORT] or AP+IPCON=3[TCP,@IP,REMOTE_PORT]
				if(temp_cmd_content.u8NumOfParameters == 2){
					tcp_server();
				}else {
					tcp_client();
				}
			}
		} else if(strcmp((const char *)temp_cmd_content.au8Cmd,"IPERF") == 0){
			if(strcmp((const char *)temp_cmd_content.au8ParamsList[0],"UDP") == 0){
				// Command is of the type: AT+IPCON=2[UDP,LOCAL_PORT] or AP+IPCON=3[UDP,@IP,REMOTE_PORT]
				if(temp_cmd_content.u8NumOfParameters == 1){  //TODO : add local port option
					printf("iperf udp server\r\n");
					iperf_udp_server();
				}else {
					// Client mode
				}
			}
			else if(strcmp((const char *)temp_cmd_content.au8ParamsList[0],"TCP") == 0){
				// Command is of the type: AT+IPCON=2[TCP,LOCAL_PORT] or AP+IPCON=3[TCP,@IP,REMOTE_PORT]
				if(temp_cmd_content.u8NumOfParameters == 1){ //TODO : add local port option
					printf("iperf tcp server\r\n");
					iperf_tcp_server();
				}else {
					// Client mode
				}
			}
		} else if(strcmp((const char *)temp_cmd_content.au8Cmd,"HTTPCON") == 0){
			uint16 port_num = atoi((char *)temp_cmd_content.au8ParamsList[1]);
			char * host_name = (char *)pvPortMalloc(strlen((char *)temp_cmd_content.au8ParamsList[0]) + 1);
			strcpy(host_name, (char *)temp_cmd_content.au8ParamsList[0]);
			http_connection(host_name, port_num);
			vPortFree(host_name);
		} else if(strcmp((const char *)temp_cmd_content.au8Cmd,"PING") == 0){
			uint16 ping_num = atoi((char *)temp_cmd_content.au8ParamsList[1]);
			char * host_name = (char *)pvPortMalloc(strlen((char *)temp_cmd_content.au8ParamsList[0]) + 1);
			strcpy(host_name, (char *)temp_cmd_content.au8ParamsList[0]);
			//M2M_INFO("*** Host name = <%s> ***\r\n",host_name);
			ping_function(host_name, ping_num);
			vPortFree(host_name);
		} else if(strcmp((const char *)temp_cmd_content.au8Cmd,"FILE_DOWNLOAD") == 0){
			char * fileURL = (char *)pvPortMalloc(strlen((char *)temp_cmd_content.au8ParamsList[0]) + 1);
			strcpy(fileURL, (char *)temp_cmd_content.au8ParamsList[0]);
			http_downloader(fileURL);
			vPortFree(fileURL);
#if SAM4SD32
		} else if(strcmp((const char *)temp_cmd_content.au8Cmd,"OTA") == 0){
			char * bin_file_URL = (char *)pvPortMalloc(strlen((char *)temp_cmd_content.au8ParamsList[0]) + 1);
			strcpy(bin_file_URL, (char *)temp_cmd_content.au8ParamsList[0]);
			ota_firmware_update(bin_file_URL);
			vPortFree(bin_file_URL);
#endif		
		} 
	}
}
