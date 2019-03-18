/**
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
 

#include "at_cmd_Handler.h"
#include "driver/include/m2m_types.h"
#include "os/include/m2m_wifi_ex.h"
#include <string.h>
 
extern xSemaphoreHandle at_cmd_task1_sem;
#define ESCAPE_CHAR				27
#define ENABLED					1
#define DISABLED				0
#define SET_VAR_TO_1(var)		(var = 1)
#define RESET_VAR_TO_0(var)		(var = 0)
#define IS_VAR_IS_L1(var)		(var > 0)
#define IS_VAR_IS_L0(var)		(var == 0)
//#define DEBUG_CMD
#define MAX_RX_BUFFER_LENGTH		1
#define GET_CH_ENUM_VAL(ch)	(ch == 255 ? ch : ch-1)
//HTTP_RXInfo  gHTTPInfo;
uint8		 gHTTPport[AT_MAX_PARAM_LENGTH];
uint8		 gHTTPChecksum;
uint8		 gTLS;
//SOCKET		 gHTTPsock;
uint32		 gu32IPAddress;
//static uint32	gu32PingCount		= 0;
uint8		 gHostNameSNI[AT_MAX_HOST_NAME]="";

tstr_app_config gtstrApp_config;
static tstrAt_cmd_content		gstrAt_cmdContent;
static tstrAt_cmd_parse_chrs	gstrAt_cmd_parse_chrs = {"+","=","[","]",",","/?"};//,"*"};
//Header, numOfParams, encStart, encStop, paramSep, HelpSep AT+CFG=2[ECHO,1] or AT+CFG /?
static strAtCMD_Handler			gastrAtCMD_Handler[AT_MAX_COMMANDS_COUNT];
tpf_at_cmd_handler				pf_at_cmd_handler;

uint rx_pos = 0;

//struct uart_module		cdc_uart_module;
volatile uint8_t gau8Rx_buffer[MAX_RX_BUFFER_LENGTH];

static uint8	gau8DataBuffer[AT_MAX_RX_BUFF_SIZE]			={0};
volatile static uint8	gu8CmdStatus		= AT_CMD_STATUS_IDLE;
volatile static uint16	gu16Data_Index		= 0;
volatile static uint8	gu8IsrFired			= false;
volatile static uint8	gu8InvalidPrinted	= true;
volatile static uint8   escape_command		= false;
volatile static uint8   carriage_return 	= false;
volatile static uint8	gu8TO = 0;
/************************************************************************/
/* Note: if you want to add a new handler, add its CMD string           */
/*       in gaAt_CMD_Values_arr as last element and its handler function*/
/*	     gaAt_CMD_handler_fn also its number of parameters.             */
/* Also, Add its index in at_cmd_index@.h file							*/
/*                                                                      */
/* Please, Make sure of all indexes of handlers and their commands and  */
/*         everything else. (Its your own responsibility).              */
/************************************************************************/

/************************************************************************/
/* The following uncompilable code is template of handler function      */
/* Included Comment too                                                 */
/************************************************************************/
#if 0
/************************************************************************/
/* atCmd_NameOf_Handler Handler                                                      */
/************************************************************************/
sint8 atCmd_NameOf_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = AT_ERR_NO_ERROR;
	tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
	
	PRINT("atCmd_NameOf_Handler\r\n");
	if(gaAt_CMD_handler_fn[AT_INDEX_ofEvent_In_at_cmd_index__enum].noOfParamters != data->numOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	if(useStoredValue) {
		goto RUN;
	}
	/* Parsing and assignments */
RUN:
	/* Executive Code Here */
EXIT:
	return s8Ret;
}
#endif
static uint8	gau8DataBufferTemp[AT_MAX_RX_BUFF_SIZE]			={0};
static strAtCMD_Handler gaAt_CMD_handler_fn[AT_MAX_COMMANDS_COUNT]=	/*Handler and no of parameters */
{
	{"CFG"			,atCmd_AppConfig_Handler,2},
	{"LIST"			,atCmd_List_Handler,0},
	{"HELP"			,atCmd_Help_Handler,0},
	{"CONN"			,atCmd_Connect_Handler,5},
	/*{"DEF_CONN"		,atCmd_DefaultConnect_Handler,0},*/
	{"DISCONN"		,atCmd_DisConnect_Handler,0},
	{"PING"         ,atCmd_Ping, 2},/*
	{"GROWL_INIT"	,atCmd_InitGrowl_Handler,0},
	{"GROWL_SEND"	,atCmd_SendGrowl_Handler,5},
	{"NMA"			,atCmd_NMA_Handler,5},
	{"PROWL"		,atCmd_Prowl_Handler,5},
	{"GROWL_DEINIT"	,atCmd_DeinitGrowl_Handler,0},*/
	{"SCAN"			,atCmd_Scan_Handler,2},
	/*{"SCAN_SSIDLIST",atCmd_ScanSsidList_Handler,6},*/
	{"RSSI"			,atCmd_CurRSSI_Handler,0},
	{"AP_EN"		,atCmd_ApEnable_Handler,5},
	{"AP_DIS"		,atCmd_ApDisable_Handler,0},
	{"P2P_EN"		,atCmd_P2pEnable_Handler,3},
	{"P2P_PIN"		,atCmd_P2pPIN_Handler,1},
	{"P2P_DIS"		,atCmd_P2pDisable_Handler,0},
	/*{"PROV_EN"		,atCmd_ProvisionEnable_Handler,8},
	{"PROV_DIS"		,atCmd_ProvisionDisable_Handler,0},
	{"WDTEST_INIT"	,atCmd_WifiDirectInit_Handler,0},
	{"WDTEST_DEINIT",atCmd_WifiDirectDeinit_Handler,0},*/
	{"WPS_START"	,atCmd_WpsConnect_Handler,2},
	{"WPS_DIS"		,atCmd_WpsDisable_Handler,0},
	{"IPCON"		,atCmd_IPCon_Handler, 5},
	/*{"SDS"			,atCmd_SocketDataStream_Handler,5},
	{"DELCID"		,atCmd_DeleteCID_Handler, 1},*/
#if SAM4SD32
	{"OTA"			,atCmd_OTA_Handler, 1},
#endif
	/*{"GETVER"		,atCmd_GetVer_Handler, 0},*/
	{"RESET"		,atCmd_Reset_Handler, 0},
	{"MON_EN"		,atCmd_MonEn_Handler,7},
	{"MON_DIS"		,atCmd_MonDis_Handler,0},
	{"PS_MODE"		,atCmd_PsMode_Handler,1},
	{"STATIC_IP"	,atCmd_SetStaticIP_Handler, 2},
	{"GET_CONN_INFO", atCmd_GetConnInfo_Handler,0},
	/*{"SET_PWR_PRO", atCmd_SetPowerProfile_Handler,1},*/
	{"IPERF"		,atCmd_Iperf_Handler, 1},
	{"HTTPCON"	    ,atCmd_HTTPCon_Handler, 2},	
	{"FILE_DOWNLOAD", atCmd_FileDownload_Handler,1},
	/*{"SCAN_PASSIVE" ,atCmd_ScanPassive_Handler,2},
	{"EN_CERT_EXPCHK",atCmd_SslEnableCertExpirationCheck,1},
	{"TLS_CRL_RESET",atCmd_TlsCrlReset_Handler, 1},
	{"TLS_CRL_ADD"	,atCmd_TlsCrlAdd_Handler, 2},
	{"TLS_CRL_SEND" ,atCmd_TlsCrlSend_Handler, 0},
	{"TLS_SET_CS"	,atCmd_TLS_SetCipherSuite_Handler, 1},
	{"TLS_WCERT"	,atCmd_TLS_CertTransfer_Handler, 0},
	{"SSL_OPTIONS"  ,atCmd_SslGlobalOption_Handler,4},*/
	/*{"GET_TIME"		,atCmd_GetSysTime_Handler,0},*/
    {"TX_PWR"       ,atCmd_TxPwr_Handler,1},
	{"ANT_DIV"       ,atCmd_AntDiversity_Handler,2},
	{"CHIP_INFO"       ,atCmd_ChipInfo_Handler,0}	
};
static uint8 gaAt_CFG_Values_arr[AT_MAX_CFG_CMD_COUNT][AT_MAX_CMD_LENGTH]=
{
	"ECHO",
	"HINT"/*,
	"RST"*/
};

extern sint32	gu32IperfPacketCount;
extern uint8	gu8UDPIperfRX, gu8TCPIperfRX, gu8ReceivingUDP;

enum enum_scanlist {
	SCAN_LIST_CH=0,
	SCAN_LIST_NUM_SSID,
	SCAN_LIST_SSID0,
	SCAN_LIST_SSID1,
	SCAN_LIST_SSID2,
	SCAN_LIST_SSID3};
/************************************************************************/
/* Initialization of handler array                                      */
/************************************************************************/
void init_at_cmd_handler(strAtCMD_Handler *pstrAtCMD_Handler)
{
	uint8 u8LoopCntr=0;
	for(u8LoopCntr=0; u8LoopCntr<AT_MAX_COMMANDS_COUNT;u8LoopCntr++) {
		pstrAtCMD_Handler[u8LoopCntr] = gaAt_CMD_handler_fn[u8LoopCntr];
	}
}

/************************************************************************/
/* parsing incoming data                                                */
/************************************************************************/
sint8 parse_cmd(uint8 *data,tstrAt_cmd_content * strCmd, tstrAt_cmd_parse_chrs parseChrs)
{
	sint8 s8RetValue				= AT_ERR_NO_ERROR;
	uint8 u8NumOfColon				= 0;
	uint8 *pu8Tok					= NULL;
	uint8 *pu8TempPtrofEq			= NULL;
	uint8 *pu8TempPtrofLeftBrack	= NULL;
	uint8  param_offset				= 0;
	memcpy(gau8DataBufferTemp,data,strlen((const char *)data)+1);// size plus null terminator

	memset((char *)strCmd,0,sizeof(tstrAt_cmd_content));
	
	if(!memcmp(data, "HELP", strlen("HELP"))){
		printf("HELP COMMAND\r\n");
		memcpy(strCmd->au8Cmd, data, strlen("HELP"));
		goto EXIT;
	}

	if(memcmp(data, AT_HEADER, strlen(AT_HEADER))){	
		if ((*data) != ESCAPE_CHAR)
		{			
			printf("Invalid AT CMD \r\n");
			s8RetValue = AT_ERR_INVALID_CMD;
			goto EXIT;
		} else {
			pu8Tok = (uint8 *)strtok((char *)&data[1], (const char *)parseChrs.u8Num_ofParams_sep);//Ignore <ESC>
		}
	} else {
		pu8Tok = (uint8 *)strtok((char *)&data[3], (const char *)parseChrs.u8Num_ofParams_sep);//Get CMD after AT_CMD_HEADER
	}
	
	if(NULL != pu8Tok) {
		memcpy(strCmd->au8Cmd,pu8Tok,strlen((const char *)pu8Tok)); /*Get CMD string*/
	} else {
		printf("Invalid AT CMD \r\n");
		s8RetValue = AT_ERR_INVALID_CMD;
		goto EXIT;
	}
	
	if
	(
		(strlen((const char *)strCmd->au8Cmd) < AT_MIN_CMD_LENGTH) || 
		(strlen((const char *)strCmd->au8Cmd) > AT_MAX_CMD_LENGTH) 
	)
	{ /*Check length of CMD*/
		osprintf("cmd invalid length\r\n");
		s8RetValue = AT_ERR_CHR_NUM_OF_CMD;
		goto EXIT;
	}

	pu8TempPtrofEq			= (uint8 *)strstr((const char *)gau8DataBufferTemp, (const char *)parseChrs.u8Num_ofParams_sep);		/*Check if there is = or not*/
	pu8TempPtrofLeftBrack	= (uint8 *)strstr((const char *)gau8DataBufferTemp, (const char *)parseChrs.u8Params_enc_Start_sep);	/*check if there is [ or not*/

	if(pu8TempPtrofEq) 
	{
		if(!pu8TempPtrofLeftBrack) {
			s8RetValue = AT_ERR_NUM_OF_PARAMS;
			goto EXIT;
		}
	} else{
		if(pu8TempPtrofLeftBrack){
			s8RetValue = AT_ERR_NUM_OF_PARAMS;
			goto EXIT;
		}
	}

	if(!pu8TempPtrofEq) /*Check if there are parameters or not*/
	{/*if not set number of parameters = 0 and clear their buffer*/
		strCmd->u8NumOfParameters = 0;
		memset((char *)&strCmd->au8ParamsList[0],0,AT_MAX_PARAM_LENGTH);
		pu8TempPtrofEq	= (uint8 *)strstr((const char *)strCmd->au8Cmd, (const char *)parseChrs.u8Help_param_sep);		/*Check if this command is inquiry or not*/
		if(pu8TempPtrofEq) 
		{
			uint8 cntr = 0;
			while((strCmd->au8Cmd[cntr] != '/') && (strCmd->au8Cmd[cntr] != ' ')) { /*skip spaces and '/'*/
				cntr++;
				if(cntr >= AT_MAX_CMD_LENGTH){
					s8RetValue = AT_ERR_INVALID_CMD;
					goto EXIT;
				}
			}
			strCmd->au8Cmd[cntr]='\0';
			s8RetValue = AT_ERR_CMD_IS_INQUIRY;
		} else {
			/*printf("/? Not found\r\n");*/
		}
		goto EXIT;
	}

	/*Check place of = closer than [ by 1chr at least*/
	if((pu8TempPtrofEq+1) >= pu8TempPtrofLeftBrack){
		/*Invalid Number of parameters*/
		s8RetValue = AT_ERR_INVALID_CMD;
		goto EXIT;
	}

	/*If you are here, there are some parameters*/
	pu8Tok = (uint8 *)strtok(NULL, (const char *)parseChrs.u8Params_enc_Start_sep);/*get number of parameters*/
	if(NULL != pu8Tok) 	{
		strCmd->u8NumOfParameters = (unsigned char)atoi((const char *)pu8Tok);
	} else {
		/**/
	}

	pu8Tok = (uint8 *)strtok(NULL, (const char *)parseChrs.u8Params_enc_Start_sep);
	if(NULL != pu8Tok){
		/*If there are some parameters*/
		if(strCmd->u8NumOfParameters >= 1) 
		{
			if(parseChrs.u8Params_enc_End_sep[0] == pu8Tok[strlen((const char *)pu8Tok)-1]) {
				pu8Tok[strlen((const char *)pu8Tok)-1] = 0;
			} 
			else {
				s8RetValue = AT_ERR_INVALID_CMD;	/*but if there is no end of parameters enclosure, something is wrong*/
				goto EXIT;
			}
		} else {
			s8RetValue = AT_ERR_NUM_OF_PARAMS;	/*but if there is number, something is wrong*/
			goto EXIT;
		}
	} 
	else {
		/*If there are not any parameters*/
		if(0 == strCmd->u8NumOfParameters) 
		{	/*and if there is number of them but is zero*/
			s8RetValue = AT_ERR_NO_ERROR;			/*suppose it is OK*/
		} 
		else {
			s8RetValue = AT_ERR_NUM_OF_PARAMS;	/*but if there is number, something is wrong*/
		}
		goto EXIT;
	}

	pu8Tok = (uint8 *)strtok((char *)pu8Tok, (const char *)parseChrs.u8Params_sep);
	while(NULL != pu8Tok)
	{
		/* If any argument contains a ',' it will be back-slashed. It shouldn't be treated as
		   a parameter separator.
		*/
		memcpy(strCmd->au8ParamsList[u8NumOfColon]+param_offset,pu8Tok,strlen((const char *)pu8Tok));
		if(*(pu8Tok + strlen((const char *)pu8Tok)-1) == '\\')
		{
			param_offset += strlen((const char *)pu8Tok);
			/* Substitute the backslash for the comma */
			*(strCmd->au8ParamsList[u8NumOfColon]+param_offset-1) = 0x2c;
		}
		else
		{
			param_offset = 0;	
			u8NumOfColon++;
		}
		if(strCmd->u8NumOfParameters == u8NumOfColon){
			/* All expected parameters are received.
			*/
			break;
		}
		pu8Tok = (uint8 *)strtok(NULL, (const char *)parseChrs.u8Params_sep);
	}

	if(strCmd->u8NumOfParameters != u8NumOfColon) {
		s8RetValue = AT_ERR_NUM_OF_PARAMS;	/*but if there is number, something is wrong*/
		goto EXIT;
	}
EXIT:
	return s8RetValue;
}

sint8 get_index_cmdHandler(tstrAt_cmd_content *strCmd, strAtCMD_Handler *atCMD_Handler)
{
	sint8 ret = AT_ERR_NO_ERROR;
	uint8 loopCntr;
	uint8 cmdLength = strlen((const char *)strCmd->au8Cmd);

	for(loopCntr = 0; loopCntr<AT_MAX_COMMANDS_COUNT; loopCntr++) {
		if(cmdLength != strlen((const char *)atCMD_Handler[loopCntr].au8AtCMD))
			continue;
		if(!memcmp(strCmd->au8Cmd,atCMD_Handler[loopCntr].au8AtCMD,cmdLength)) {
			M2M_DBG("Searching for CMD handler...%s=%s[%d]\r\n",(const char *)strCmd->au8Cmd,(const char *)atCMD_Handler[loopCntr].au8AtCMD,loopCntr);
			ret  = loopCntr; 
			break;
		}
	}
	
	if(AT_MAX_COMMANDS_COUNT > loopCntr) {
		/*ret = pf_at_cmd_handler(strCmd);*/
	} else {
		ret = AT_ERR_NOT_REGISTERED_CMD;
	}

//EXIT:
	return ret;
}

void print_cmd_handler_arr(strAtCMD_Handler *astrAtCMD_Handler)
{
	uint8 loopCntr=0;
	printf("\r\n%-12s\t%-20s\t%s\r\n","#","CMD","Handler Ptr.");
	printf("-------------------------------------------------------\r\n");
	for(loopCntr=0; loopCntr<AT_MAX_COMMANDS_COUNT;loopCntr++) {
		printf("%02d%-10s\t%-20s\t%p\r\n",loopCntr+1," ",
		astrAtCMD_Handler[loopCntr].au8AtCMD,astrAtCMD_Handler[loopCntr].at_cmd_handler);
	}
}

void print_Handle_status(sint8 ret, uint8 * cmdTxt)
{
	if(AT_ERR_NO_ERROR == ret) {
		//PRINT("CMD sent Successfully.\r\n");
		/*(NOTE:)Send OK only if handling from callback succeeded*/
	} else {
		AT_SEND_ERROR(ret,cmdTxt);
		switch(ret){
			case AT_ERR_NOT_REGISTERED_CMD:{
				M2M_ERR("Not Registered AT-Command.\r\n");
				break;
			}//case AT_ERR_NOT_REGISTERED_CMD
			case AT_ERR_NOT_REGISTERED_CFG:{
				M2M_ERR("Not Registered CFG-Command.\r\n");
				break;
			}//case AT_ERR_NOT_REGISTERED_CMD
			case AT_ERR_INVALID_CMD:{
				M2M_ERR("Invalid CMD.\r\n");
				break;
			}//case AT_ERR_INVALID_CMD
			case AT_ERR_CHR_NUM_OF_CMD:{
				M2M_ERR("AT-CMD characters are not as excepected.\r\n");
				break;
			}//case AT_ERR_TOO_SHORT
			case AT_ERR_INVALID_OPERATION:{
				M2M_ERR("Invalid Operation to Handle.\r\n");
				break;
			}//case AT_ERR_INVALID_OPERATION
			case AT_ERR_NUM_OF_PARAMS:{
				M2M_ERR("Invalid number of Parameters.\r\n");
				break;
			}//case AT_ERR_NOT_EXPECTED_PARAMS
			case AT_ERR_INVALID_ARGUMENTS:{
				M2M_ERR("Invalid Arguments.\r\n");
				break;
			}//case AT_ERR_INVALID_ARGUMENTS
		}//switch(ret)
	}
}

void get_cmd_txt(uint8 ndx, uint8 *txt)
{
	if(ndx >= AT_MAX_COMMANDS_COUNT){
		txt=NULL;
		return;
	}
	//txt = gaAt_CMD_Values_arr[ndx];
	memcpy(txt,gaAt_CMD_handler_fn[ndx].au8AtCMD,strlen((const char *)gaAt_CMD_handler_fn[ndx].au8AtCMD));
}


//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/*    Application Runtime Configuration                                 */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* Runtime Configuration Handler                                        */
/************************************************************************/
sint8 atCmd_AppConfig_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = AT_ERR_NO_ERROR;
	tstr_app_config *ptstrApp_config=(tstr_app_config*)moreData;
	uint8 u8LoopCntr = 0, u8CfgCmdLength=0;
	
	PRINT("atCmd_AppConfig_Handler\r\n");
	if(gaAt_CMD_handler_fn[AT_INDEX_CONFIG].u8NoOfParameters != data->u8NumOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	
	u8CfgCmdLength = strlen((const char *)gaAt_CFG_Values_arr[u8LoopCntr]);
	for(u8LoopCntr = 0; u8LoopCntr<AT_MAX_CFG_CMD_COUNT; u8LoopCntr++) {
		if(strlen((const char *)data->au8ParamsList[0]) != u8CfgCmdLength) {
			continue;
		}
		if(!memcmp(data->au8ParamsList[0],gaAt_CFG_Values_arr[u8LoopCntr],u8CfgCmdLength)) {
			break;
		}
	}
	
//RUN:
	M2M_INFO("%02d: SET %s TO %s \r\n",u8LoopCntr,gaAt_CFG_Values_arr[u8LoopCntr],
		(atoi((const char *)data->au8ParamsList[1])?("ENABLED"):("DISABLED")));
		
	switch(u8LoopCntr)
	{
		case AT_CFG_INDEX_ECHO: {
			ptstrApp_config->u8Echo_status = atoi((const char *)data->au8ParamsList[1]);
			break;
		}
#		if 0	
		case AT_CFG_INDEX_RST: {
			ptstrApp_config->u8Restart_app = atoi((const char *)data->au8ParamsList[1]);
			break;
		}
#		endif
		case AT_CFG_INDEX_HINT: {
			ptstrApp_config->u8Disaply_hint = atoi((const char *)data->au8ParamsList[1]);
			break;
		}
		default: {
			s8Ret = AT_ERR_NOT_REGISTERED_CFG;
			break;
		}
	}
	
EXIT:
	if(AT_ERR_NO_ERROR == s8Ret) {
		AT_SEND_OK(gaAt_CFG_Values_arr[u8LoopCntr]);
	}
	
	return s8Ret;
}

//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* Handlers in Station Mode                                             */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* STATION related Enums, Stucts, and variables                         */
/************************************************************************/
enum enum_connIndexes{
	CONN_INDEX_SSID = 0,
	CONN_INDEX_SSID_LENGTH,
	CONN_INDEX_SEC_TYPE,
	CONN_INDEX_SEC_KEY,
	CONN_INDEX_CHANNEL
};
struct str_uart_conn
{
	uint8	ssid[32];
	uint8	ssidLen;
	uint8	secType;
	uint8	secKey[64];
	uint8	channel;
}gstrConn;
/************************************************************************/
/* Disconnect Handler                                                   */
/************************************************************************/
sint8 atCmd_DisConnect_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = AT_ERR_NO_ERROR;
	tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
	
	if(gaAt_CMD_handler_fn[AT_INDEX_DISCONN].u8NoOfParameters != data->u8NumOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	if(SERVICE_IS_STOPPED == status->u8Sta_status) {
		AT_SEND_OK(data->au8Cmd);
		printf("Already Disconnected\r\n");
		goto EXIT;
	}
	if(M2M_SUCCESS != (s8Ret=os_m2m_wifi_disconnect())) {
		s8Ret = AT_ERR_OPERATION_NOT_COMPELETED;
	}
	
	
EXIT:
	return s8Ret;
}
/************************************************************************/
/* Connect Handler                                                      */
/************************************************************************/
sint8 atCmd_Connect_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = M2M_ERR_FAIL;
	char * pu8Dat;
	tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
	
	PRINT("atCmd_Connect_Handler\r\n");
	if(gaAt_CMD_handler_fn[AT_INDEX_CONN].u8NoOfParameters != data->u8NumOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}

	if(SERVICE_IS_RUNNING == status->u8Sta_status) { /*WiFi is already connected to AP*/
		s8Ret = AT_ERR_INVALID_OPERATION;
		PRINT("Already connected\r\n");
		goto EXIT;
	}
	
	if(	(SERVICE_IS_RUNNING == status->u8Ap_status)&& /*Check if AP mode is running*/
		(SERVICE_IS_RUNNING == status->u8P2p_status)	/*Check if P2P mode is running*/
	){
		PRINT("AP/P2P already connected %d %d\r\n",status->u8Ap_status, status->u8P2p_status);
		s8Ret = AT_ERR_INVALID_OPERATION;
		goto EXIT;
	}
	
	/*Clear gstrConn first*/
	memset((char *)&gstrConn,0,sizeof(gstrConn));
	/*Get SSID*/
	memcpy(gstrConn.ssid,data->au8ParamsList[CONN_INDEX_SSID],strlen((const char *)data->au8ParamsList[CONN_INDEX_SSID]));
	/*Get SSID Length*/
	gstrConn.ssidLen = atoi((const char *)data->au8ParamsList[CONN_INDEX_SSID_LENGTH]);
	/*Get SEC Type*/
	gstrConn.secType = atoi((const char *)data->au8ParamsList[CONN_INDEX_SEC_TYPE]);
	/*Get SEC KEY*/
	memcpy(gstrConn.secKey,data->au8ParamsList[CONN_INDEX_SEC_KEY],strlen((const char *)data->au8ParamsList[CONN_INDEX_SEC_KEY]));
	/*Get CHANNEL*/
	gstrConn.channel = GET_CH_ENUM_VAL(atoi((const char *)data->au8ParamsList[CONN_INDEX_CHANNEL]));
	
	PRINT("\r>%s\r\n>%s\r\n>%d\r\n>%d\r\n>%d\r\n",
		gstrConn.ssid,
		gstrConn.secKey,
		gstrConn.ssidLen,
		gstrConn.secType,
		gstrConn.channel);
	
	if(M2M_WIFI_SEC_WEP == gstrConn.secType) {
		tstrM2mWifiWepParams wepParams;
		memset(&wepParams, 0, sizeof(wepParams));
		pu8Dat = strtok((char *)gstrConn.secKey,"*");
		wepParams.u8KeyIndx=atoi((const char *)pu8Dat);
		pu8Dat = strtok(NULL,"*");
		wepParams.u8KeySz=strlen((const char *)pu8Dat) + 1;
		memcpy(wepParams.au8WepKey,pu8Dat,strlen((const char *)pu8Dat));
		PRINT("WEP Key Index: %d\r\n"
				"WEP Key      : %s\r\n"
				"WEP Key Sz   : %d\r\n",wepParams.u8KeyIndx,wepParams.au8WepKey,wepParams.u8KeySz);
		s8Ret = os_m2m_wifi_connect((char *)gstrConn.ssid, gstrConn.ssidLen, gstrConn.secType, (void *)&wepParams, gstrConn.channel);
	} else if(M2M_WIFI_SEC_802_1X == gstrConn.secType) {
		tstr1xAuthCredentials enterParams;
		memset(&enterParams, 0, sizeof(enterParams));
		pu8Dat = strtok((char *)gstrConn.secKey,"*");
		memcpy(enterParams.au8UserName,pu8Dat,strlen((const char *)pu8Dat));
		pu8Dat = strtok(NULL,"*");
		memcpy(enterParams.au8Passwd,pu8Dat,strlen((const char *)pu8Dat));
		PRINT("Enterprise Username: %s\r\n"
		"Enterprise Password: %s\r\n",enterParams.au8UserName,enterParams.au8Passwd);
		s8Ret = os_m2m_wifi_connect((char *)gstrConn.ssid, gstrConn.ssidLen, gstrConn.secType, (void *)&enterParams, gstrConn.channel);
	}else if(M2M_WIFI_SEC_WPA_PSK == gstrConn.secType) {
		s8Ret = os_m2m_wifi_connect((char *)gstrConn.ssid, gstrConn.ssidLen, gstrConn.secType, (void *)gstrConn.secKey, gstrConn.channel);
	} 
	else {
		M2M_INFO("WPA key: %s",gstrConn.secKey);
		s8Ret = os_m2m_wifi_connect((char *)gstrConn.ssid, gstrConn.ssidLen, gstrConn.secType, (tuniM2MWifiAuth *)gstrConn.secKey, gstrConn.channel);
	}
EXIT:
	return s8Ret;
}


sint8 atCmd_SetStaticIP_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = M2M_SUCCESS;
	int parse_static[4];
	uint8 u8LoopCntr, *pu8Dat = NULL;

	PRINT("atCmd_SetStaticIP_Handler\r\n");
	
	if((data->u8NumOfParameters < gaAt_CMD_handler_fn[AT_INDEX_STATIC_IP].u8NoOfParameters)){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}

	pu8Dat = (uint8 *)strtok((char *)data->au8ParamsList[0],".");

	for(u8LoopCntr=0; u8LoopCntr<4; u8LoopCntr++) {
		if (((parse_static[u8LoopCntr] = atoi((const char *)pu8Dat)) == 0) && (*pu8Dat != 0x30))
		{
			s8Ret = AT_ERR_INVALID_ARGUMENTS;
			goto EXIT;
		}
		if(parse_static[u8LoopCntr]>255)
		{
			s8Ret = AT_ERR_INVALID_ARGUMENTS;
			goto EXIT;
		}
		pu8Dat = (uint8 *)strtok(NULL,".");
	}
	
	StaticIPcfg.u32StaticIP = htonl((uint32_t) (parse_static[0]<<24 | parse_static[1]<<16 | parse_static[2]<<8 | parse_static[3]));
	
	pu8Dat = (uint8 *)strtok((char *)data->au8ParamsList[1],".");

	for(u8LoopCntr=0; u8LoopCntr<4; u8LoopCntr++) {
		if (((parse_static[u8LoopCntr] = atoi((const char *)pu8Dat)) == 0) && (*pu8Dat != 0x30))
		{
			s8Ret = AT_ERR_INVALID_ARGUMENTS;
			goto EXIT;
		}
		if(parse_static[u8LoopCntr]>255)
		{
			s8Ret = AT_ERR_INVALID_ARGUMENTS;
			goto EXIT;
		}
		pu8Dat = (uint8 *)strtok(NULL,".");
	}	
	
	StaticIPcfg.u32Gateway = htonl((uint32_t) (parse_static[0]<<24 | parse_static[1]<<16 | parse_static[2]<<8 | parse_static[3]));// 0xFFFF0000;
	
	use_static_IP = 1;
	AT_SEND_OK(data->au8Cmd);
	
EXIT:
	return s8Ret;
}

sint8 atCmd_Iperf_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue){
	sint8 s8Ret;
	tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
	PRINT("atCmd_PIperf_Start\r\n");
	if(gaAt_CMD_handler_fn[AT_INDEX_IPERF].u8NoOfParameters != data->u8NumOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	if(	(SERVICE_IS_RUNNING != status->u8Ap_status) && (SERVICE_IS_RUNNING != status->u8Sta_status)){
		PRINT("Neither STA mode nor AP mode connected\r\n");
		s8Ret = AT_ERR_INVALID_OPERATION;
		goto EXIT;
	}
	if(strcmp((const char *)data->au8ParamsList[0],"UDP") != 0 && (strcmp((const char *)data->au8ParamsList[0],"TCP") != 0))
	{			
		osprintf("Invalid param %s, expecting UDP or TCP\r\n", (const char *)data->au8ParamsList[0]);
		s8Ret = AT_ERR_INVALID_ARGUMENTS;
		goto EXIT;
	}
	/*clear existing struct*/
	memset((tstrAt_cmd_content *)&temp_cmd_content , 0, sizeof(tstrAt_cmd_content));
	/*copy new command struct*/
	memcpy((tstrAt_cmd_content *)&temp_cmd_content ,data, sizeof(tstrAt_cmd_content));
#ifdef AT_CMD_SEM
	osprintf("IPERF give\r\n");
	xSemaphoreGive(at_cmd_task1_sem);
	osprintf("IPERF given\r\n");
#endif
	AT_SEND_OK(data->au8Cmd);
	s8Ret = AT_ERR_NO_ERROR;
EXIT:
	return s8Ret;
}

#if 0
/************************************************************************/
/* Default Connect Handler                                              */
/************************************************************************/
sint8 atCmd_DefaultConnect_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = AT_ERR_NO_ERROR;
	tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
	
	PRINT("atCmd_DefaultConnect_Handler\r\n");
	
	if(gaAt_CMD_handler_fn[AT_INDEX_DEF_CONN].u8NoOfParameters != data->u8NumOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	
	if(SERVICE_IS_RUNNING != status->u8Sta_status) {
		if(M2M_SUCCESS != (s8Ret=m2m_wifi_default_connect())) {
			s8Ret = AT_ERR_OPERATION_NOT_COMPELETED;
		}
	} else {
		s8Ret = AT_ERR_INVALID_OPERATION;
	}
	
EXIT:
	return s8Ret;
}
/************************************************************************/
/* Growl Related enums, structs, and variables                          */
/************************************************************************/
enum{
	GROWL_INDEX_CLIENT_ID = 0,
	GROWL_INDEX_APP_NAME,
	GROWL_INDEX_EVENT_NAME,
	GROWL_INDEX_DESC,
	GROWL_INDEX_CONN_TYPE
};
typedef struct{
	uint8 u8ClientName;
	uint8 pu8App[GROWL_APPNAME_MAX_LENGTH];
	uint8 pu8Event[GROWL_EVENT_MAX_LENGTH];
	uint8 pu8Description[GROWL_DESCRIPTION_MAX_LENGTH];
	uint8 bUseSSL;
}tstrGrowlNotification;

tstrGrowlNotification strNMA;
tstrGrowlNotification strProwl;
/************************************************************************/
/* Stop Growl Handler                                                   */
/************************************************************************/
sint8 atCmd_InitGrowl_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 ret = AT_ERR_NO_ERROR;
	tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
	
	if(gaAt_CMD_handler_fn[AT_INDEX_GROWL_INIT].u8NoOfParameters != data->u8NumOfParameters){
		ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	
	PRINT("atCmd_InitGrowl_Handler\r\n");
	
#	if (defined(NMA) || defined(PROWL)) && (defined(GROWL))
		NMI_GrowlInit((uint8*) PROWL_API_KEY, (uint8*) NMA_API_KEY);
#	endif
	status->u8Growl_status = SERVICE_IS_RUNNING;
	AT_SEND_OK(data->au8Cmd);
EXIT:
	return ret;
}
/************************************************************************/
/* Sending Growl Handler                                                */
/************************************************************************/
sint8 atCmd_SendGrowl_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 ret = AT_ERR_NO_ERROR;
	tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
	PRINT("atCmd_SendGrowl_Handler\r\n");
	
	if(gaAt_CMD_handler_fn[AT_INDEX_GROWL_SEND].u8NoOfParameters != data->u8NumOfParameters){
		ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}

	status->u8GrowlNumOfCBs = 2;
	
#	ifdef PROWL
		ret = atCmd_Prowl_Handler(data,NULL,0);
		if(AT_ERR_NO_ERROR != ret) goto EXIT;
#	endif
#	ifdef NMA
		ret = atCmd_NMA_Handler(data,NULL,0);
#	endif
EXIT:
	return ret;
}
/************************************************************************/
/* Sending NMA Handler                                                  */
/************************************************************************/
sint8 atCmd_NMA_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = AT_ERR_NO_ERROR;
	tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
	PRINT("atCmd_NMA_Handler\r\n");
	
	if(gaAt_CMD_handler_fn[AT_INDEX_NMA].u8NoOfParameters != data->u8NumOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	memset((uint8 *)&strNMA, 0, sizeof(strNMA));
	strNMA.u8ClientName = (atoi((const char *)data->au8ParamsList[GROWL_INDEX_CLIENT_ID]) & 0xF0)?
							((atoi((const char *)data->au8ParamsList[GROWL_INDEX_CLIENT_ID]) & 0xF0) >> 4):
							(atoi((const char *)data->au8ParamsList[GROWL_INDEX_CLIENT_ID]) & 0x0F);

	if(! strNMA.u8ClientName){
		s8Ret = AT_ERR_INVALID_ARGUMENTS;
		goto EXIT;
	} else {
		/**/
	}
	
	memcpy(strNMA.pu8App,data->au8ParamsList[GROWL_INDEX_APP_NAME],strlen((const char *)data->au8ParamsList[GROWL_INDEX_APP_NAME]));
	memcpy(strNMA.pu8Event,data->au8ParamsList[GROWL_INDEX_EVENT_NAME],strlen((const char *)data->au8ParamsList[GROWL_INDEX_EVENT_NAME]));
	memcpy(strNMA.pu8Description,data->au8ParamsList[GROWL_INDEX_DESC],strlen((const char *)data->au8ParamsList[GROWL_INDEX_DESC]));
	strNMA.bUseSSL=(atoi((const char *)data->au8ParamsList[GROWL_INDEX_CONN_TYPE]) & 0xF0)?
						((atoi((const char *)data->au8ParamsList[GROWL_INDEX_CONN_TYPE]) & 0xF0) >> 4):
						(atoi((const char *)data->au8ParamsList[GROWL_INDEX_CONN_TYPE]) & 0x0F);
	
	if(NULL != status) status->u8GrowlNumOfCBs = 1;
	
	PRINT("NMA with %d, %s, %s, %s, %d\r\n",
		strNMA.u8ClientName,strNMA.pu8App,strNMA.pu8Event,strNMA.pu8Description,strNMA.bUseSSL);
	if(M2M_SUCCESS != (s8Ret=NMI_GrowlSendNotification(strNMA.u8ClientName,(uint8*)strNMA.pu8App,
		(uint8*)strNMA.pu8Event,(uint8*)strNMA.pu8Description,strNMA.bUseSSL))) {
		s8Ret = AT_ERR_INVALID_ARGUMENTS;		
	}

EXIT:
	return s8Ret;
}
/************************************************************************/
/* Sending Prowl Handler                                                */
/************************************************************************/
sint8 atCmd_Prowl_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = AT_ERR_NO_ERROR;
	tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
	PRINT("atCmd_Prowl_Handler\r\n");
	
	if(gaAt_CMD_handler_fn[AT_INDEX_PROWL].u8NoOfParameters != data->u8NumOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
		
	strProwl.u8ClientName = (atoi((const char *)data->au8ParamsList[GROWL_INDEX_CLIENT_ID]) & 0x0F);
	if(! strProwl.u8ClientName){
		s8Ret = AT_ERR_INVALID_ARGUMENTS;
		goto EXIT;
	}else {
		/**/
	}
	
	memcpy(strProwl.pu8App,data->au8ParamsList[GROWL_INDEX_APP_NAME],strlen((const char *)data->au8ParamsList[GROWL_INDEX_APP_NAME]));
	memcpy(strProwl.pu8Event,data->au8ParamsList[GROWL_INDEX_EVENT_NAME],strlen((const char *)data->au8ParamsList[GROWL_INDEX_EVENT_NAME]));
	memcpy(strProwl.pu8Description,data->au8ParamsList[GROWL_INDEX_DESC],strlen((const char *)data->au8ParamsList[GROWL_INDEX_DESC]));
	strProwl.bUseSSL=(atoi((const char *)data->au8ParamsList[GROWL_INDEX_CONN_TYPE]) & 0x0F);

	if(NULL != status) status->u8GrowlNumOfCBs = 1;
	
	PRINT("PROWL with %d, %s, %s, %s, %d\r\n",
		strProwl.u8ClientName,strProwl.pu8App,strProwl.pu8Event,strProwl.pu8Description,strProwl.bUseSSL);
	if(M2M_SUCCESS != (s8Ret=NMI_GrowlSendNotification(strProwl.u8ClientName,(uint8*)strProwl.pu8App,
		(uint8*)strProwl.pu8Event,(uint8*)strProwl.pu8Description,strProwl.bUseSSL))) {
		s8Ret = AT_ERR_INVALID_ARGUMENTS;		
	}
	
EXIT:
	return s8Ret;
}
/************************************************************************/
/* Stop Growl Handler                                                   */
/************************************************************************/
sint8 atCmd_DeinitGrowl_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = AT_ERR_NO_ERROR;
	tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
	
	if(gaAt_CMD_handler_fn[AT_INDEX_GROWL_DEINIT].u8NoOfParameters != data->u8NumOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	
	PRINT("atCmd_DeInitGrowl_Handler\r\n");
	
#	if (defined(NMA) || defined(PROWL)) && (defined(GROWL))
		NMI_GrowldeInit();
#	endif
	status->u8Growl_status = SERVICE_IS_STOPPED;
	AT_SEND_OK(data->au8Cmd);
EXIT:
	return s8Ret;
}
#endif
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* Handlers in Access Point Mode                                        */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* Access Point related Enums, Stucts, and variables                    */
/************************************************************************/
enum{
	AP_INDEX_SSID = 0,
	AP_INDEX_SSID_VISIBLE_MODE,
	AP_INDEX_SEC_TYPE,
	AP_INDEX_SEC_KEY,
	AP_INDEX_CHANNEL,
	PROV_INDEX_SERVER_DOMAIN,
	PROV_INDEX_REDIRECT_STATE,
};
tstrM2MAPConfig gstrApConfig;
typedef struct{
	char	au8ServerDomain[252];
	uint8	bEnRedirect;
}tstrProv_Data;
tstrProv_Data	gtstrProv_Data;
/************************************************************************/
/* AP Disable Handler                                                   */
/************************************************************************/
sint8 atCmd_ApDisable_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = AT_ERR_NO_ERROR;
	tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
	PRINT("atCmd_ApDisable_Handler\r\n");
	
	if(gaAt_CMD_handler_fn[AT_INDEX_AP_DISABLE].u8NoOfParameters != data->u8NumOfParameters) {
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	
	if(SERVICE_IS_STOPPED != status->u8Ap_status){
		if(M2M_SUCCESS == (s8Ret=os_m2m_wifi_disable_ap())) {
			if(status->u8Ap_status != SERVICE_DEV_IS_CONNECTED) {
				status->u8Ap_status = SERVICE_IS_STOPPED;
				AT_SEND_OK(data->au8Cmd);
			} else {
				status->u8Ap_status = SERVICE_IS_UNDEFINED;
			}
		} else {
			s8Ret = AT_ERR_OPERATION_NOT_COMPELETED;
		}
	} else {
		s8Ret = AT_ERR_INVALID_OPERATION;
		PRINT("Already Stopped\r\n");
	}
EXIT:
	return s8Ret;
}
/************************************************************************/
/* AP Enable Handler                                                    */
/************************************************************************/
sint8 atCmd_ApEnable_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = AT_ERR_NO_ERROR;
	uint8 *pu8Dat = NULL;
	tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
	//uint8 u8LoopCntr = 0;
	
	PRINT("atCmd_ApEnable_Handler\r\n");
	
	if(1 == useStoredValue)
	{
		goto ENABLE_AP;
	}
	
	if(gaAt_CMD_handler_fn[AT_INDEX_AP_ENABLE].u8NoOfParameters != data->u8NumOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	
	if(SERVICE_IS_RUNNING == status->u8Ap_status) { /*Check if AP mode is running*/
		s8Ret = AT_ERR_INVALID_OPERATION;
		goto EXIT;
	}
	
	if(	(SERVICE_IS_RUNNING == status->u8P2p_status) && /*Check if P2P mode is running*/
		(SERVICE_IS_RUNNING == status->u8Sta_status)	/*Check if STA mode is running*/
	){
		s8Ret = AT_ERR_INVALID_OPERATION;
		goto EXIT;
	}	
	memset(&gstrApConfig, 0, sizeof(gstrApConfig));
	/*Get SSID*/
	memcpy(gstrApConfig.au8SSID,data->au8ParamsList[AP_INDEX_SSID],strlen((const char *)data->au8ParamsList[AP_INDEX_SSID]));
	gstrApConfig.au8SSID[strlen((const char *)data->au8ParamsList[AP_INDEX_SSID])] = 0;
	/*Get SSID BroadCast type: Hidden or Visible*/
	gstrApConfig.u8SsidHide = atoi((const char *)data->au8ParamsList[AP_INDEX_SSID_VISIBLE_MODE]);
	/*Get Listen Channel*/
	gstrApConfig.u8ListenChannel = GET_CH_ENUM_VAL(atoi((const char *)data->au8ParamsList[AP_INDEX_CHANNEL]));
	/*Get Security Type: OPEN or WEP*/
	gstrApConfig.u8SecType = atoi((const char *)data->au8ParamsList[AP_INDEX_SEC_TYPE]);
	
	/*If security type is OPEN, so bypass the incoming key and enable AP mode directly*/
	if(M2M_WIFI_SEC_WEP == gstrApConfig.u8SecType) {
		/*Get WEP Key Index*/
		pu8Dat = (uint8 *)strtok((char *)data->au8ParamsList[AP_INDEX_SEC_KEY],"*");
		gstrApConfig.uniAuth.strWepInfo.u8KeyIndx = (uint8)atoi((const char *)pu8Dat);
		/*Get WEP Key Password*/
		pu8Dat = (uint8 *)strtok(NULL,"*");
		strcpy((char *)gstrApConfig.uniAuth.strWepInfo.au8WepKey, (char *)pu8Dat);
		/*WEP Key size*/
		gstrApConfig.uniAuth.strWepInfo.u8KeySz = (uint8)strlen((const char *)pu8Dat) + 1; //including NULL terminator	
	}
	else if(M2M_WIFI_SEC_WPA_PSK == gstrApConfig.u8SecType)
	{
		uint8	*pu8WPAKey	= data->au8ParamsList[AP_INDEX_SEC_KEY];
		strcpy((char *)gstrApConfig.uniAuth.au8PSK, (char *)pu8WPAKey);
	}
	
	PRINT("\r>%s\r\n>%d\r\n>%d\r\n>%d\r\n",
		gstrApConfig.au8SSID,
		gstrApConfig.u8SsidHide,
		gstrApConfig.u8ListenChannel,
		gstrApConfig.u8SecType
	);
	if(M2M_WIFI_SEC_WEP == gstrApConfig.u8SecType)
	{
		PRINT("\r\n"
		"WEP Key Index: %d\r\n"
		"WEP Key      : %s\r\n"
		"WEP Key Sz   : %d\r\n",gstrApConfig.uniAuth.strWepInfo.u8KeyIndx ,gstrApConfig.uniAuth.strWepInfo.au8WepKey, gstrApConfig.uniAuth.strWepInfo.u8KeySz);
	}
	else if(M2M_WIFI_SEC_WPA_PSK == gstrApConfig.u8SecType)
	{
		PRINT("\r\n"
		"WPA Key      : %s\r\n",gstrApConfig.uniAuth.au8PSK);
	}
ENABLE_AP:
	if(M2M_SUCCESS != (s8Ret=os_m2m_wifi_enable_ap(&gstrApConfig)))
	{
		s8Ret = AT_ERR_INVALID_ARGUMENTS;
	}
EXIT:
	return s8Ret;
}
#if 0
/************************************************************************/
/* Provisioning Mode Disable Handler                                    */
/************************************************************************/
sint8 atCmd_ProvisionDisable_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = AT_ERR_NO_ERROR;
	tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
	PRINT("atCmd_ProvisionDisable_Handler\r\n");
	
	if(gaAt_CMD_handler_fn[AT_INDEX_PROV_DISABLE].u8NoOfParameters != data->u8NumOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	
	if(SERVICE_IS_STOPPED != status->u8Prov_status){
		if(M2M_SUCCESS == (s8Ret=m2m_wifi_stop_provision_mode())) {
			if(status->u8Prov_status != SERVICE_DEV_IS_CONNECTED) {
				status->u8Prov_status = SERVICE_IS_STOPPED;
				AT_SEND_OK(data->au8Cmd);
			} else {
				status->u8Prov_status = SERVICE_IS_UNDEFINED;
			}
		} else {
			s8Ret = AT_ERR_OPERATION_NOT_COMPELETED;
		}
	} else {
		s8Ret = AT_ERR_INVALID_OPERATION;
	}
	
EXIT:
	return s8Ret;
}
/************************************************************************/
/* Provisioning Mode Enable Handler                                     */
/************************************************************************/
sint8 atCmd_ProvisionEnable_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = AT_ERR_NO_ERROR;
	uint8 *pu8Dat = NULL;
	tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
	uint8 u8LoopCntr, u8DomainLength;
	
	PRINT("atCmd_ProvisionEnable_Handler\r\n");
	
	M2M_DBG("gaAt_CMD_handler_fn[AT_INDEX_PROV_ENABLE][1]=%d\r\ndata.numOfParameters=%d",
		gaAt_CMD_handler_fn[AT_INDEX_PROV_ENABLE].u8NoOfParameters ,data->u8NumOfParameters);
	
	if(gaAt_CMD_handler_fn[AT_INDEX_PROV_ENABLE].u8NoOfParameters != data->u8NumOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	
	/*Get SSID*/
	memcpy(gstrApConfig.au8SSID,data->au8ParamsList[AP_INDEX_SSID],strlen((const char *)data->au8ParamsList[AP_INDEX_SSID]));
	/*Get SSID BroadCast type: Hidden or Visible*/
	gstrApConfig.u8SsidHide = atoi((const char *)data->au8ParamsList[AP_INDEX_SSID_VISIBLE_MODE]);
	/*Get Listen Channel*/
	gstrApConfig.u8ListenChannel = GET_CH_ENUM_VAL(atoi((const char *)data->au8ParamsList[AP_INDEX_CHANNEL]));
	/*Get Security Type: OPEN or WEP*/
	gstrApConfig.u8SecType = atoi((const char *)data->au8ParamsList[AP_INDEX_SEC_TYPE]);
	
	/*If security type is OPEN, so bypass the incoming key and enable AP mode directly*/
	if(M2M_WIFI_SEC_WEP == gstrApConfig.u8SecType) {
		/*Get WEP Key Index*/
		pu8Dat = (uint8 *)strtok((char *)data->au8ParamsList[AP_INDEX_SEC_KEY],"*");
		gstrApConfig.u8KeyIndx=atoi((const char *)pu8Dat)-1;
		/*Get WEP Key Size*/
		pu8Dat = (uint8 *)strtok(NULL,"*");
		gstrApConfig.u8KeySz=strlen((const char *)pu8Dat);
		/*Get WEP Key Password*/
		memcpy(gstrApConfig.au8WepKey,pu8Dat,gstrApConfig.u8KeySz);
	}
	else if(M2M_WIFI_SEC_WPA_PSK == gstrApConfig.u8SecType){
		gstrApConfig.u8KeySz=strlen((const char *)data->au8ParamsList[AP_INDEX_SEC_KEY]);
		memcpy(gstrApConfig.au8Key,data->au8ParamsList[AP_INDEX_SEC_KEY],M2M_MAX_PSK_LEN);
	}
	
	/*pu8Dat = (uint8 *)strtok((char *)data->au8ParamsList[AP_INDEX_SERVER_IP],".");
	for(u8LoopCntr=0; u8LoopCntr<sizeof(gstrApConfig.au8DHCPServerIP); u8LoopCntr++) {
		gstrApConfig.au8DHCPServerIP[u8LoopCntr] = atoi((const char *)pu8Dat);
		pu8Dat = (uint8 *)strtok(NULL,".");
	}*/
	
	u8DomainLength = (sizeof(gtstrProv_Data.au8ServerDomain) <= sizeof(data->au8ParamsList[PROV_INDEX_SERVER_DOMAIN])?
					sizeof(gtstrProv_Data.au8ServerDomain) : sizeof(data->au8ParamsList[PROV_INDEX_SERVER_DOMAIN]));				
	memcpy(gtstrProv_Data.au8ServerDomain,data->au8ParamsList[PROV_INDEX_SERVER_DOMAIN],u8DomainLength);
	/* Get Redirect State*/
	gtstrProv_Data.bEnRedirect = atoi((const char *)data->au8ParamsList[PROV_INDEX_REDIRECT_STATE]);
	
	if(SERVICE_IS_RUNNING != status->u8Prov_status) {
		s8Ret = m2m_wifi_start_provision_mode(&gstrApConfig, gtstrProv_Data.au8ServerDomain, gtstrProv_Data.bEnRedirect);
		if(M2M_SUCCESS == s8Ret) {
			status->u8Prov_status = SERVICE_IS_RUNNING;
			AT_SEND_OK(data->au8Cmd);
		} else {
			
			M2M_DBG("Provisioning paramets:\r\n");
			M2M_DBG("Domain name: %s\r\n",gtstrProv_Data.au8ServerDomain);
			M2M_DBG("Redirect enable: %d\r\n",gtstrProv_Data.bEnRedirect);
			M2M_DBG("DHCPIP: [%d.%d.%d.%d]\r\n",gstrApConfig.au8DHCPServerIP[0],gstrApConfig.au8DHCPServerIP[1],
				gstrApConfig.au8DHCPServerIP[2],gstrApConfig.au8DHCPServerIP[3]);
			M2M_DBG("SSID: [%s] hidden: [%d]\r\nCh: [%d]\r\n", gstrApConfig.au8SSID,gstrApConfig.u8SsidHide,
				gstrApConfig.u8ListenChannel);
			M2M_DBG("Sec:%d Key:[%s] Sz: [%d] Ind:[%d]\r\n",gstrApConfig.u8SecType,gstrApConfig.au8WepKey,
				gstrApConfig.u8KeySz,gstrApConfig.u8KeyIndx);
			
			AT_SEND_ERROR(s8Ret, data->au8Cmd);
		}
	} else {
		s8Ret = AT_ERR_INVALID_OPERATION;
	}
	
EXIT:
	return s8Ret;
}
#endif

//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* Handlers in Peer-to-Peer Mode                                        */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* Peer-to-Peer related Enums, Stucts, and variables                    */
/************************************************************************/
enum{
	P2P_INDEX_CHANNEL = 0,	
	P2P_INDEX_TRIGGER,
	P2P_INDEX_CFG_METHODS,
};
tstrM2MP2PConnect gstrP2pConfig;
/************************************************************************/
/* P2P Disable Handler                                                  */
/************************************************************************/
sint8 atCmd_P2pDisable_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = AT_ERR_NO_ERROR;
	tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
	
	PRINT("atCmd_P2pDisable_Handler\r\n");
	if(gaAt_CMD_handler_fn[AT_INDEX_P2P_DISABLE].u8NoOfParameters != data->u8NumOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	
	if(SERVICE_IS_STOPPED != status->u8P2p_status){
		if(M2M_SUCCESS == (s8Ret=os_m2m_wifi_p2p_disconnect())) {
			if(status->u8P2p_status != SERVICE_DEV_IS_CONNECTED) {
				status->u8P2p_status = SERVICE_IS_STOPPED;
				AT_SEND_OK(data->au8Cmd);
			} else {
				status->u8P2p_status = SERVICE_IS_UNDEFINED;
			}
		} else {
			s8Ret = AT_ERR_OPERATION_NOT_COMPELETED;
		}
	} else {
		s8Ret = AT_ERR_INVALID_OPERATION;
	}
EXIT:
	return s8Ret;
}
/************************************************************************/
/* P2P Enable Handler                                                   */
/************************************************************************/
sint8 atCmd_P2pEnable_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = AT_ERR_NO_ERROR;
	uint8 u8InterfaceID = P2P_AP_CONCURRENCY_INTERFACE;
	tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
	
	PRINT("atCmd_P2pEnable_Handler\r\n");
	if(gaAt_CMD_handler_fn[AT_INDEX_P2P_ENABLE].u8NoOfParameters != data->u8NumOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	gstrP2pConfig.u8ListenChannel = GET_CH_ENUM_VAL(atoi((const char *)data->au8ParamsList[P2P_INDEX_CHANNEL]));
	gstrP2pConfig.enuTrigger = atoi((const char *)data->au8ParamsList[P2P_INDEX_TRIGGER]);
	gstrP2pConfig.u16WPS_CfgMethods = atoi((const char *)data->au8ParamsList[P2P_INDEX_CFG_METHODS]);
	if(SERVICE_IS_RUNNING == status->u8P2p_status) { /*Check if P2P mode is running*/
		s8Ret = AT_ERR_INVALID_OPERATION;
		goto EXIT;
	}
	
	if(	(SERVICE_IS_RUNNING == status->u8Ap_status) && /*Check if AP mode is running*/
		(SERVICE_IS_RUNNING == status->u8Sta_status)	/*Check if STA mode is running*/
	){
		s8Ret = AT_ERR_INVALID_OPERATION;
		goto EXIT;
	}
	if(SERVICE_IS_RUNNING == status->u8Sta_status) /*Check if STA mode is running*/
		u8InterfaceID = P2P_STA_CONCURRENCY_INTERFACE;
	
	/* Set device name. */
	os_m2m_wifi_set_device_name((uint8_t *)MAIN_WLAN_DEVICE_NAME, strlen(MAIN_WLAN_DEVICE_NAME));
	os_m2m_wifi_set_p2p_control_ifc(u8InterfaceID);
	osprintf("gstrP2pConfig.u8ListenChannel %d\r\n", gstrP2pConfig.u8ListenChannel);
	if(M2M_SUCCESS == (s8Ret=m2m_wifi_p2p(gstrP2pConfig.u8ListenChannel,gstrP2pConfig.enuTrigger,gstrP2pConfig.u16WPS_CfgMethods))) {
		status->u8P2p_status = SERVICE_IS_RUNNING;		
		AT_SEND_OK(data->au8Cmd);						
	} else {
		s8Ret = AT_ERR_INVALID_ARGUMENTS;
	}
	
EXIT:
	return s8Ret;
}
/************************************************************************/
/* P2P Enable Handler                                                   */
/************************************************************************/
sint8 atCmd_P2pPIN_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = AT_ERR_NO_ERROR;
	tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
	
	PRINT("atCmd_P2pEnable_Handler\r\n");
	if(gaAt_CMD_handler_fn[AT_INDEX_P2P_PIN_INPUT].u8NoOfParameters != data->u8NumOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	
	if(SERVICE_IS_RUNNING != status->u8P2p_status) { /*Check if P2P mode is running*/
		s8Ret = AT_ERR_INVALID_OPERATION;
		goto EXIT;
	}
	
	/* Set pin number */
	s8Ret = os_m2m_wifi_set_p2p_pin((uint8_t *)data->au8ParamsList[0], strlen(data->au8ParamsList[0]));
	//os_m2m_wifi_set_p2p_control_ifc(P2P_AP_CONCURRENCY_INTERFACE);
	osprintf("Pin Number %s\r\n", data->au8ParamsList[0]);

EXIT:
	return s8Ret;	
}
#if 0
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* Misc Handlers                                                        */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
uint32 gu32ScanStartTime = 0;
uint32 gu32DownloadFileTime = 0;
extern uint32 get_systicks();
void SetScanTimeStart()
{
	gu32ScanStartTime = get_systicks();
}
uint32 GetScanTimeStart()
{
	return gu32ScanStartTime;
}
uint32 SetDownloadStartTime()
{
	gu32DownloadFileTime =  get_systicks();
}
uint32 GetDownloadStartTime()
{
	return gu32DownloadFileTime;
}
#endif
/************************************************************************/
/* Scan Handler                                                         */
/************************************************************************/
sint8 atCmd_Scan_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	PRINT("atCmd_Scan_Handler\r\n");
	sint8 s8Ret = AT_ERR_NO_ERROR;
	uint16 channel =  GET_CH_ENUM_VAL(atoi((const char *)data->au8ParamsList[0]));

	PRINT("Scanning on channel %d\r\n",channel);
	
	//SetScanTimeStart();
	if(data->u8NumOfParameters == 1){
		s8Ret = os_m2m_wifi_request_scan(channel);
	}else if(data->u8NumOfParameters == 2){
		char * ssid = (char *)data->au8ParamsList[1];
		s8Ret = os_m2m_wifi_request_scan_ssid(channel,ssid);
	}else{
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
EXIT:
	return s8Ret;
}
#if 0
sint8 atCmd_ScanSsidList_Handler(tstrAt_cmd_content *data,void* moreData,uint8 useStoredValue)
{
	sint8 s8Ret = AT_ERR_NO_ERROR;
	uint8 u8Ch = M2M_WIFI_CH_6;
	uint8 u8NumSsid = 0;
	uint8* au8Ssid[4];
	uint8 au8SsidList[1+4*(1+32)] = {0};
	uint8 ind=0;
	int i=0;
	
	u8Ch = atoi((const char*) data->au8ParamsList[SCAN_LIST_CH]);
	u8NumSsid = atoi((const char*) data->au8ParamsList[SCAN_LIST_NUM_SSID]);
	au8Ssid[0] =  data->au8ParamsList[SCAN_LIST_SSID0];
	au8Ssid[1] =  data->au8ParamsList[SCAN_LIST_SSID1];
	au8Ssid[2] =  data->au8ParamsList[SCAN_LIST_SSID2];
	au8Ssid[3] =  data->au8ParamsList[SCAN_LIST_SSID3];

	au8SsidList[ind++] = u8NumSsid;
	for(i=0;i<u8NumSsid;i++)
	{
		uint8 SsidLen = strlen((const char*)au8Ssid[i]);
		au8SsidList[ind++] = SsidLen;
		memcpy(&au8SsidList[ind],au8Ssid[i],SsidLen);
		ind += SsidLen;
	}
	SetScanTimeStart();
	s8Ret = m2m_wifi_request_scan_ssid_list(u8Ch,au8SsidList);
	return s8Ret;
}
#endif
/************************************************************************/
/* RSSI Handler                                                         */
/************************************************************************/
sint8 atCmd_CurRSSI_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = AT_ERR_NO_ERROR;
	PRINT("atCmd_CurRSSI_Handler\r\n");
	
	if(gaAt_CMD_handler_fn[AT_INDEX_RSSI].u8NoOfParameters != data->u8NumOfParameters) {
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	if(M2M_SUCCESS != (s8Ret=os_m2m_wifi_req_curr_rssi())) {
		s8Ret = AT_ERR_OPERATION_NOT_COMPELETED;
	}

EXIT:
	return s8Ret;
}

/************************************************************************/
/* WPS Connect Handler                                                  */
/************************************************************************/
sint8 atCmd_WpsConnect_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue) {
	sint8 s8Ret = AT_ERR_NO_ERROR;

	PRINT("atCmd_WpsConnect_Handler\r\n");
	if(2 < data->u8NumOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	
	printf(">>Trigger Type %d\r\n",atoi((const char *)data->au8ParamsList[0]));
	printf(">>Pin Key      %s\r\n",data->au8ParamsList[1]);
	if(M2M_SUCCESS != (s8Ret=os_m2m_wifi_wps(atoi((const char *)data->au8ParamsList[0]),
		(const char *)(WPS_PIN_TRIGGER == atoi((const char *)data->au8ParamsList[0])?data->au8ParamsList[1]:NULL)))) {

		s8Ret = AT_ERR_INVALID_ARGUMENTS;		
	}
EXIT:
	return s8Ret;
}
/************************************************************************/
/* WPS Disable Handler                                                  */
/************************************************************************/
sint8 atCmd_WpsDisable_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue) {
	sint8 s8Ret = AT_ERR_NO_ERROR;
	
	PRINT("atCmd_WpsDisable_Handler\r\n");
	if(gaAt_CMD_handler_fn[AT_INDEX_WPS_DISABLE].u8NoOfParameters != data->u8NumOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}

	if(M2M_SUCCESS != (s8Ret=os_m2m_wifi_wps_disable())) {
		s8Ret = AT_ERR_INVALID_ARGUMENTS;
		AT_SEND_ERROR(AT_ERR_INVALID_ARGUMENTS, data->au8Cmd);
	} else {
		AT_SEND_OK(data->au8Cmd);
	}	
EXIT:
	return s8Ret;
}

#if 0
void PrintSockConnections(SockConnInfo *conn)
{
    SockConnInfo* tmp;
    uint8 i=1;
    tmp=conn;

    if (conn==NULL){
	    M2M_INFO("The list is empty");
    }
    else{
	    while(tmp->next_SockConn!=NULL){
		    M2M_INFO("CID: %d, sock:%d, port:%u, ip: %lx", tmp->u8CID, tmp->sock, tmp->u16port, tmp->addr);
		    i++;
		    tmp=tmp->next_SockConn;
	    }
		    M2M_INFO("CID: %d, sock:%d, port:%u, ip: %lx", tmp->u8CID, tmp->sock, tmp->u16port, tmp->addr);
    }	
	
}

uint8 GetCID(void){
	uint8 itmp,cid= -1;
	
	for (itmp = 0; itmp<MAX_SOCKET; itmp++)
	{
		if (sCID[itmp]!= 0xFF)
		{
			cid=sCID[itmp];
			sCID[itmp] = 0xFF;
			return cid;
		}
	}
	return 0xFF;
}

void FreeCID(uint8 cid){
	if (sCID[cid] == 0xFF)
	{
		sCID[cid] = cid;
	}
}

uint8 UpdateSockConn(SockConnInfo *conn, SOCKET csock, uint16 port, uint32 saddr) {
	conn->u8CID = GetCID();
	conn->sock = csock;
	conn->addr = saddr;
	conn->u16port = port;
	conn->next_SockConn = NULL;
	return conn->u8CID;
}

uint8 AddSockConn(SockConnInfo **conn, SOCKET csock, uint16 port, uint32 saddr) {
	SockConnInfo* tmp;

	if ((*conn)==NULL)
	{
		(*conn)=(SockConnInfo *)malloc(sizeof(SockConnInfo));
		return (UpdateSockConn((*conn), csock, port, saddr));
	}
	else
	{
		tmp=(*conn);
		while(tmp->next_SockConn != NULL)
		{
			tmp = tmp->next_SockConn;
		}
		tmp->next_SockConn=(SockConnInfo *)malloc(sizeof(SockConnInfo));
		return(UpdateSockConn(tmp->next_SockConn, csock, port, saddr));
	}	
}

void DeleteSockConn(SockConnInfo **conn, SOCKET csock){
    SockConnInfo* tmp;
    SockConnInfo* aux;
    SockConnInfo* pre_conn;

	if ((*conn)!=NULL)
	{
        if((*conn)->sock == csock)
		{
            tmp = (*conn)->next_SockConn;
			close((*conn)->sock);
			FreeCID((*conn)->u8CID);
            free(*conn);
            (*conn) = tmp;
        }
        else {
            pre_conn=(*conn);
            aux=(*conn)->next_SockConn;
            while(aux->sock != csock)
			{
                    pre_conn=aux;
                    aux = aux->next_SockConn;
            }
            tmp = aux->next_SockConn;
			close(aux->sock);
			FreeCID(aux->u8CID);			
            free(aux);
            pre_conn->next_SockConn = tmp;
        }
    }
}

SockConnInfo* RetrieveConnectionFromSocket(SockConnInfo **conn, uint8 sock){
	SockConnInfo* aux;

	if ((*conn)!=NULL)
	{
		if((*conn)->sock == sock)
			return (*conn);
		else {
			aux=(*conn)->next_SockConn;
			while(aux != NULL)
			{
				if(aux->sock != sock)
					aux = aux->next_SockConn;
				else
					return (aux);
			}

		}
	}
	return 0;
}

SockConnInfo* RetrieveConnectionFromCID(SockConnInfo **conn, uint8 cid){
	SockConnInfo* aux;

	if ((*conn)!=NULL)
	{
		if((*conn)->u8CID == cid)
			return (*conn);
		else {
			aux=(*conn)->next_SockConn;
			while(aux != NULL)
			{
				if(aux->u8CID != cid)
					aux = aux->next_SockConn;
				else
					return (aux);
			}

		}
	}
	return 0;
}
#endif
sint8 atCmd_HTTPCon_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8	s8Ret = AT_ERR_NO_ERROR;
	tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
	uint16 portnum = 0;
	PRINT("atCmd_HTTPCon_Handler\r\n");
	if(data->u8NumOfParameters != gaAt_CMD_handler_fn[AT_INDEX_HTTPCON].u8NoOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	if(	(SERVICE_IS_RUNNING != status->u8Ap_status) && (SERVICE_IS_RUNNING != status->u8Sta_status)){
		PRINT("Neither STA mode nor AP mode connected\r\n");
		s8Ret = AT_ERR_INVALID_OPERATION;
		goto EXIT;
	}
	// Port number can't contain letters
	if(atCmd_IsParameterNumericOnly((uint8*)&data->au8ParamsList[1])!= M2M_SUCCESS)
	{
		osprintf("Invalid port number\r\n");
		s8Ret = AT_ERR_INVALID_ARGUMENTS;
		goto EXIT;
	}
	portnum = atoi((char *)data->au8ParamsList[1]);
	if(portnum == 0)
	{
		osprintf("Invalid portnum 0\r\n");
		s8Ret = AT_ERR_INVALID_ARGUMENTS;
		goto EXIT;
	}
	/*clear existing struct*/
	memset((tstrAt_cmd_content *)&temp_cmd_content , 0, sizeof(tstrAt_cmd_content));
	/*copy new command struct*/
	memcpy((tstrAt_cmd_content *)&temp_cmd_content ,data, sizeof(tstrAt_cmd_content));
#ifdef AT_CMD_SEM
	xSemaphoreGive(at_cmd_task1_sem);
#endif
EXIT:
	return s8Ret;
}

sint8 atCmd_IsParameterNumericOnly(uint8* pData)
{
	uint8 *pu8tmp, u8itmp = 0;

	pu8tmp = pData;

	while(*(pu8tmp+u8itmp)!=NULL)
	{
		if(*(pu8tmp+u8itmp)<0x30 || *(pu8tmp+u8itmp)>0x39)
		{
			return M2M_ERR_FAIL;
		}
		u8itmp++;
	}
	return M2M_SUCCESS;
}

sint8 atCmd_IPCon_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue) 
{
	sint8 s8Ret = AT_ERR_NO_ERROR;
	uint8 u8LoopCntr, *pu8Dat = NULL;
	uint16 portnum = 0;
	int ServerIP[4];
	tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
	printf("atCmd_IPCon_Handler\r\n");
		
	if((data->u8NumOfParameters > gaAt_CMD_handler_fn[AT_INDEX_IPCON].u8NoOfParameters) || (data->u8NumOfParameters < 2)){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}

	if (data->u8NumOfParameters == 2) {
		// Command is of the type: AT+IPCON=2[UDP|TCP,LOCAL_PORT]
		// Port number can't contain letters
		if(atCmd_IsParameterNumericOnly((uint8*)&data->au8ParamsList[1])!= M2M_SUCCESS)
		{
			osprintf("Invalid port number\r\n");
			s8Ret = AT_ERR_INVALID_ARGUMENTS;
			goto EXIT;
		}
		portnum = atoi((char *)data->au8ParamsList[1]);

	} else {
		// Command is of the type: AP+IPCON=3[UDP|TCP,@IP,REMOTE_PORT]
		char pServerIPTemp[15];
		strcpy(pServerIPTemp,(char *) data->au8ParamsList[1]);
		pu8Dat = (uint8 *)strtok(pServerIPTemp,".");

		for(u8LoopCntr=0; u8LoopCntr<4; u8LoopCntr++) {
			// IP address can't contain letters
			if(atCmd_IsParameterNumericOnly(pu8Dat)!=M2M_SUCCESS)
			{
				s8Ret = AT_ERR_INVALID_ARGUMENTS;
				goto EXIT;
			}
			if(((ServerIP[u8LoopCntr] = atoi((const char *)pu8Dat)) == 0) && (*pu8Dat != 0x30))
			{
				s8Ret = AT_ERR_INVALID_ARGUMENTS;
				goto EXIT;
			}
			if(ServerIP[u8LoopCntr]>255)
			{
				s8Ret = AT_ERR_INVALID_ARGUMENTS;
				goto EXIT;
			}
			pu8Dat = (uint8 *)strtok(NULL,".");
		}
		// Port number can't contain letters		
		if(atCmd_IsParameterNumericOnly((uint8*)&data->au8ParamsList[2])!=M2M_SUCCESS)
		{
			s8Ret = AT_ERR_INVALID_ARGUMENTS;
			goto EXIT;
		}
		portnum = atoi((char *)data->au8ParamsList[2]);
	}

	if(portnum == 0)
	{
		osprintf("Invalid portnum 0\r\n");
		s8Ret = AT_ERR_INVALID_ARGUMENTS;
		goto EXIT;
	}

	if((SERVICE_IS_RUNNING != status->u8Sta_status) &&  (SERVICE_IS_RUNNING != status->u8Ap_status)) {
		s8Ret = AT_ERR_INVALID_OPERATION;
		printf("Error : Device not connected as STA/AP\r\n");
		goto EXIT;
	}
	
	if((strcmp((const char *)data->au8ParamsList[0],"UDP") != 0) && (strcmp((const char *)data->au8ParamsList[0],"TCP") != 0)) 
	{
		osprintf("Invalid argument : %s\r\n", (const char *)data->au8ParamsList[0]);
		s8Ret = AT_ERR_INVALID_ARGUMENTS;
		goto EXIT; 
	}
	/*clear existing struct*/
	memset((tstrAt_cmd_content *)&temp_cmd_content , 0, sizeof(tstrAt_cmd_content));
	/*copy new command struct*/
	memcpy((tstrAt_cmd_content *)&temp_cmd_content ,data, sizeof(tstrAt_cmd_content));
#ifdef AT_CMD_SEM 
	xSemaphoreGive(at_cmd_task1_sem);
#endif
	//sockCID = AddSockConn(&first_SockConn, sock, portnum, myaddr.sin_addr.s_addr);
#if 0		
	if(sockCID == 0xFF)
	{
		M2M_INFO("ERROR: Failed to add CID");
	}
	else if (strcmp((const char *)data->au8ParamsList[0],"UDP") == 0) {
		if (data->u8NumOfParameters == 3) {
			//PrintSockConnections(first_SockConn); 
		}
	}
#endif
EXIT:
	return s8Ret;	
}
#if 0
static uint8 MapToControlCharacter(uint8 *to_convert, volatile uint8 c_from, volatile uint8 c_to, uint8 total_len)
{
	uint8 converted[AT_MAX_PARAM_LENGTH];
	uint8 data_index, first, data_len, char_delete=0;
	uint8 *pu8Dat = NULL;
	uint8 len_toconvert = strlen((char *)(to_convert));
	
	data_len = total_len;
	memset(converted,0,sizeof(converted));
	
	if (len_toconvert>1)
	{
		first = 1;
		data_index = 0;
		//pu8Dat points to the first character after the delimiter or the beginning of the string (first time)
		// e.g. "XXX\rYYYY\rZZZ"
		pu8Dat = (uint8 *)strtok((char *)to_convert,"\\");
		
		if ((len_toconvert !=strlen((char *)(pu8Dat))))
		{
			while (pu8Dat != NULL)
			{
				/* 
					If the string to be converted contains "XX\r\" and, when first output from strtok being "XX" you have 
					substituted \r by CR (data_index=1), the next output from strtok will be just "r". This one needs to be 
					skipped	as it has already been accounted for. 
				*/
				if(!((strlen((char *)(pu8Dat))==1) && (*(pu8Dat) == c_from) && data_index))
				{
					/* From the example shown in the comment above, if pu8Dat points to XXX" and the next
					   character after the end of the string is the character you are looking for eg. r, it means you have
					   found a \r and the string that pu8Dat points to should be copied to converted.

					   However, if pu8Dat points to "rYYYY" and r is the character that you are looking for, r needs to be
					   skipped when copying to converted (char *)(pu8Dat+1).
					*/
					if((first && (*(pu8Dat+strlen((char *)(pu8Dat))+1) == c_from)) || (!first && *(pu8Dat) == c_from))
					{
						if(first)
						{
							first = 0;
							strcat((char *)converted,(char *)(pu8Dat));
						}
						else
							strcat((char *)converted,(char *)(pu8Dat+1));

						data_index = 1;
						
						/* 
							If we haven't finished converting the \character, add the ControlCharacter and update
							the number of characters that we have deleted so far (one for each \character) and update
							the total size that converted will held at the end of the routine
						*/
						 
						if((strlen((char *)(converted))+char_delete)<total_len)
						{
							converted[strlen((char *)(converted))] = c_to;
							data_len -=1;
							char_delete++;
						}
					}
					else
					{
						/* 
							If the character after the backlash is not the one we are looking for, put back the '\'
							to converted 
						*/
						converted[strlen((char *)(converted))] = 0x5c;
						strcat((char *)converted,(char *)(pu8Dat));
						data_index=0;
					}
				}
				// Look for the next output of strtok 
				pu8Dat = (uint8 *)strtok(NULL,"\\");
			}
		}
		else
			memcpy(converted,to_convert,len_toconvert);
	}
	else
		memcpy(converted,to_convert,len_toconvert);
	
	// overwrite to_convert with converted
	memset(to_convert,0,len_toconvert);
	memcpy(to_convert,converted,AT_MAX_PARAM_LENGTH);
	
	return data_len;
}

sint8 atCmd_SocketDataStream_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue) {
	sint8 s8Ret = AT_ERR_NO_ERROR;
	uint8 len_tosend = 0, data_offset, data_len, u8LoopCntr;
	uint8 *pu8Dat = NULL;
	int	DestIP[4];
	uint8 data_tosend[AT_MAX_PARAM_LENGTH];
	uint16 portnum = 0;
	struct sockaddr_in destaddr;
	SockConnInfo *pDestSockConn = NULL;
	
	PRINT("atCmd_SocketDataStream_Handler\r\n");
	
	if(data->u8NumOfParameters !=3  && data->u8NumOfParameters != 5 ){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}

	if (data->u8NumOfParameters == 3) {
		// Command is of the type: <ESC>SDS=3[CID,LEN,DATA]
		data_offset = 1;
	} else {
		// Command is of the type: <ESC>SDS=5[CID,IP_ADDRESS,PORT,LEN,DATA]
		data_offset = 3;
		pu8Dat = (uint8 *)strtok((char *)data->au8ParamsList[1],".");
		// Parse IP address of the destination
		for(u8LoopCntr=0; u8LoopCntr<4; u8LoopCntr++) {
			if(((DestIP[u8LoopCntr] = atoi((const char *)pu8Dat)) == 0) && (*pu8Dat != 0x30))
			{
				s8Ret = AT_ERR_INVALID_ARGUMENTS;
				goto EXIT;
			}
			if(DestIP[u8LoopCntr]>255)
			{
				s8Ret = AT_ERR_INVALID_ARGUMENTS;
				goto EXIT;
			}
			pu8Dat = (uint8 *)strtok(NULL,".");
		}
		
		portnum = atoi((char *)data->au8ParamsList[2]);
		
		if(portnum == 0)
		{
			s8Ret = AT_ERR_INVALID_ARGUMENTS;
			goto EXIT;		
		}
	}
	
	data_len = atoi((char *)data->au8ParamsList[data_offset]);
	
	memset(data_tosend,0,sizeof(data_tosend));	
	
	for(u8LoopCntr=0; u8LoopCntr<AT_MAX_PARAM_LENGTH; u8LoopCntr++) {
		data_tosend[u8LoopCntr] = data->au8ParamsList[data_offset+1][u8LoopCntr];
		if(data_tosend[u8LoopCntr] == 0)
			break;
		len_tosend++;
	}

	// Check: Length provided by the user has to be the same as the length of the string to be sent
	if (len_tosend != data_len)
	{
		s8Ret = AT_ERR_INVALID_ARGUMENTS;
		goto EXIT;
	}	

	// Map /r to carriage return
	len_tosend = MapToControlCharacter(data_tosend,(uint8)'r',(uint8)'\r',len_tosend);
	// Map /n to new line
	len_tosend = MapToControlCharacter(data_tosend,(uint8)'n',(uint8)'\n',len_tosend);		

	pDestSockConn = RetrieveConnectionFromCID(&first_SockConn, atoi((char *)data->au8ParamsList[0]));
	if(pDestSockConn==NULL)
	{
		s8Ret = AT_ERR_INVALID_ARGUMENTS;
		goto EXIT;
	}
	
	if(pDestSockConn->sock < TCP_SOCK_MAX)
	{
		// The socket is TCP
		if (gHTTPChecksum)
		{
			memset(&gHTTPInfo,0,sizeof(HTTP_RXInfo));
			SHA1_INIT(&gHTTPInfo.sha1_ctxt);
			gHTTPInfo.first_chunk = 1;
		}
		if(send(pDestSockConn->sock, data_tosend, len_tosend, 0) == M2M_SUCCESS)
			M2M_INFO("Message sent");
		else
			M2M_INFO("ERROR: Failed to send to socket %d", pDestSockConn->sock);
	}
	else
	{
		// The socket is UDP
		memset(&destaddr, 0, sizeof(destaddr));
		destaddr.sin_family = AF_INET;
		
		if (data->u8NumOfParameters == 3) {
			// Command is of the type: <ESC>SDS=3[CID,LEN,DATA]
			destaddr.sin_addr.s_addr = pDestSockConn->addr;
			destaddr.sin_port = _htons( pDestSockConn->u16port);
		} else {
			//Command is of the type: <ESC>SDS=5[CID,IP_ADDRESS,PORT,LEN,DATA]
			destaddr.sin_addr.s_addr = _htonl((uint32_t) (DestIP[0]<<24 | DestIP[1]<<16 | DestIP[2]<<8 | DestIP[3]));
			destaddr.sin_port = _htons(portnum);
		}

		if(sendto(pDestSockConn->sock, data_tosend, data_len, 0, (struct sockaddr *)&destaddr, sizeof(destaddr)) == M2M_SUCCESS)
		{
			M2M_INFO("Message sent");
			recvfrom(pDestSockConn->sock, gau8SocketTestBuffer, MAIN_WIFI_M2M_BUFFER_SIZE, 0);
		} else
			M2M_INFO("ERROR: Failed to send to socket %d", pDestSockConn->sock);
	}

EXIT:
return s8Ret;
}

sint8 atCmd_DeleteCID_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue) {
	sint8 s8Ret = AT_ERR_NO_ERROR;
	uint8 cid;
	SockConnInfo *pDestSockConn = NULL;
	
	PRINT("atCmd_DeleteCID_Handler\r\n");
	
	if(data->u8NumOfParameters != gaAt_CMD_handler_fn[AT_INDEX_DELCID].u8NoOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	
	cid = atoi((char *)data->au8ParamsList[0]);
	
	pDestSockConn = RetrieveConnectionFromCID(&first_SockConn, cid);
	
	if(pDestSockConn==NULL)
	{
		s8Ret = AT_ERR_INVALID_ARGUMENTS;
		goto EXIT;
	}	
	
	DeleteSockConn(&first_SockConn,pDestSockConn->sock);
	
	if (pDestSockConn->sock == gHTTPsock)
	{
		gHTTPsock = -1;
		memset(gHTTPport,0,AT_MAX_PARAM_LENGTH);
		gTLS = 0;
	}
	
	printf("Available CIDs:\n");	
	PrintSockConnections(first_SockConn);	

EXIT:
return s8Ret;	
}

sint8 atCmd_TLS_SetCipherSuite_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8  s8Ret = AT_ERR_NO_ERROR;
	uint32 CSBitmap = 0;

	if(data->u8NumOfParameters != gaAt_CMD_handler_fn[AT_INDEX_TLS_SET_CS].u8NoOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}

	CSBitmap = atoi((char *)data->au8ParamsList[0]);

	// Active the ECC cipher suites in the WINC
	s8Ret = m2m_ssl_set_active_ciphersuites(CSBitmap);

	if (s8Ret != M2M_SUCCESS)
	{
		M2M_ERR("m2m_ssl_set_active_ciphersuites() failed with ret=%d", s8Ret);
		goto EXIT;
	}

	EXIT:
	return s8Ret;
}

sint8 atCmd_TLS_CertTransfer_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8  s8Ret = AT_ERR_NO_ERROR;

	if(data->u8NumOfParameters != gaAt_CMD_handler_fn[AT_INDEX_TLS_WCERT].u8NoOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}

	s8Ret = eccTransferCertificates();

	if (s8Ret != M2M_SUCCESS)
	{
		M2M_ERR("eccTransferCertificates() failed with ret=%d", s8Ret);
		goto EXIT;
	}

	EXIT:
	return s8Ret;
}
#endif

#if SAM4SD32
sint8 atCmd_OTA_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue) {
	sint8 s8Ret = AT_ERR_NO_ERROR;
	tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
	PRINT("atCmd_OTA_Handler\r\n");
	
	if(data->u8NumOfParameters != gaAt_CMD_handler_fn[AT_INDEX_OTA].u8NoOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	if(	(SERVICE_IS_RUNNING != status->u8Ap_status) && (SERVICE_IS_RUNNING != status->u8Sta_status)){
		PRINT("Neither STA mode nor AP mode connected\r\n");
		s8Ret = AT_ERR_INVALID_OPERATION;
		goto EXIT;
	}
	
	/*clear existing struct*/
	memset((tstrAt_cmd_content *)&temp_cmd_content , 0, sizeof(tstrAt_cmd_content));
	/*copy new command struct*/
	memcpy((tstrAt_cmd_content *)&temp_cmd_content ,data, sizeof(tstrAt_cmd_content));
	#ifdef AT_CMD_SEM
	xSemaphoreGive(at_cmd_task1_sem);
	#endif
	AT_SEND_OK(data->au8Cmd);
	s8Ret = AT_ERR_NO_ERROR;

	EXIT:
	return s8Ret;
}
#endif

#if 0
sint8 atCmd_GetVer_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue) {
	sint8 s8Ret = AT_ERR_NO_ERROR;
	tstrM2mRev strM2mRev;
	PRINT("atCmd_GetVer_Handler\r\n");
	
	if(data->u8NumOfParameters != gaAt_CMD_handler_fn[AT_INDEX_GETVER].u8NoOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	
	M2M_INFO("Curr driver ver: %u.%u.%u\n", M2M_RELEASE_VERSION_MAJOR_NO, M2M_RELEASE_VERSION_MINOR_NO, M2M_RELEASE_VERSION_PATCH_NO);
	s8Ret = m2m_wifi_get_firmware_version(&strM2mRev);
	if(M2M_SUCCESS == s8Ret)
	{
		/* char acCmdRet[]="GET_VER"; */
		M2M_INFO("Firmware ver   : %u.%u.%u Svnrev %u\n", strM2mRev.u8FirmwareMajor, strM2mRev.u8FirmwareMinor, strM2mRev.u8FirmwarePatch,strM2mRev.u16FirmwareSvnNum);
		M2M_INFO("Min driver ver : %u.%u.%u\n", strM2mRev.u8DriverMajor, strM2mRev.u8DriverMinor, strM2mRev.u8DriverPatch);
		M2M_INFO("Curr driver ver: %u.%u.%u Svnrev %u \n", M2M_RELEASE_VERSION_MAJOR_NO, M2M_RELEASE_VERSION_MINOR_NO, M2M_RELEASE_VERSION_PATCH_NO,M2M_RELEASE_VERSION_SVN_VERSION);
		M2M_INFO("Firmware Build %s Time %s\n",strM2mRev.BuildDate,strM2mRev.BuildTime);
	}
	else
	{	
		AT_SEND_ERROR(s8Ret, "GETVER");
	}
	
	s8Ret = m2m_ota_get_firmware_version(&strM2mRev);
	if((s8Ret == M2M_SUCCESS)||(s8Ret == M2M_ERR_FW_VER_MISMATCH))
	{
		M2M_INFO("OTA Firmware ver   : %u.%u.%u Svnrev %u\n", strM2mRev.u8FirmwareMajor, strM2mRev.u8FirmwareMinor, strM2mRev.u8FirmwarePatch,strM2mRev.u16FirmwareSvnNum);
		M2M_INFO("OTA Min driver ver : %u.%u.%u\n", strM2mRev.u8DriverMajor, strM2mRev.u8DriverMinor, strM2mRev.u8DriverPatch);
		M2M_INFO("OTA Firmware Build %s Time %s\n",strM2mRev.BuildDate,strM2mRev.BuildTime);
	}
	
	if(s8Ret == M2M_ERR_INVALID)
	{
		M2M_INFO("OTA image NOT found\n");
		s8Ret = M2M_SUCCESS;
	}
		
	EXIT:
	return s8Ret;
}
#endif

sint8 atCmd_Reset_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue) {
	sint8 s8Ret = AT_ERR_NO_ERROR;

	PRINT("atCmd_Reset_Handler\r\n");
	
	if(data->u8NumOfParameters != gaAt_CMD_handler_fn[AT_INDEX_RESET].u8NoOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}

	NVIC_SystemReset();
	
	EXIT:
	return s8Ret;
}

/************************************************************************/
/* List Handler                                                         */
/************************************************************************/
sint8 atCmd_List_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue) {
	sint8 s8Ret = AT_ERR_NO_ERROR;
	uint8 u8LoopCntr = 0;
	
	printf("This is a list of all AT Commands supported even the configuration commands:\r\n");
	printf("%-2s\t%-10s\t%s\r\n","#","Command","#Parameters");
	
	printf("%02d\t%-10s\t%02d\r\n", (AT_INDEX_CONFIG+1), gaAt_CMD_handler_fn[AT_INDEX_CONFIG].au8AtCMD, gaAt_CMD_handler_fn[AT_INDEX_CONFIG].u8NoOfParameters);
	for(u8LoopCntr=0; u8LoopCntr<AT_MAX_CFG_CMD_COUNT; u8LoopCntr++) {	//Config. commands
		printf("\t%c)\t%-10s\r\n", (u8LoopCntr+'a'), gaAt_CFG_Values_arr[u8LoopCntr]);
	}
	printf("\r\n");
	for(u8LoopCntr=1; u8LoopCntr<AT_MAX_COMMANDS_COUNT; u8LoopCntr++) {	//main commands
		printf("%02d\t%-10s\t%02d\r\n", (u8LoopCntr+1), gaAt_CMD_handler_fn[u8LoopCntr].au8AtCMD, gaAt_CMD_handler_fn[u8LoopCntr].u8NoOfParameters);
	}
	printf("\r\n");
	return s8Ret;
}

/************************************************************************/
/* Help Handler                                                         */
/************************************************************************/
sint8 atCmd_Help_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue) {
	sint8 s8Ret = AT_ERR_NO_ERROR;
	
	PRINT("atCmd_Help_Handler\r\n");
	printf("%s  \r\n", "You can use AT Commands as the following forms:");
	printf("\t%s\r\n", "Without Parameters :AT+CMD<CR><LF>");
	printf("\t%s\r\n", "With Parameters    :AT+CMD=N[Param1,Param2,...,ParamN]<CR><LF>");
	
	printf("\r\n\tWhere <CR>\"Carriage Return\" -> (13)");
	printf("\r\n\t      <LF>\"Line Feed\"       -> (10)");
	printf("\r\n");
	
	printf("%s  \r\n", "Also, You can use \"AT+LIST\" to display all supported AT Commands");
	printf("%s  \r\n", "or type the AT Command without parameters followed by \"/?\" to view help about it.");
	printf("\t%s\r\n", "Examples : AT+CFG=2[ECHO,0]");
	printf("\t%s\r\n", "         : AT+LIST");
	printf("\t%s\r\n", "         : AT+CFG /?");
	printf("\t%s\r\n", "\r\n");
	return s8Ret;
}

/************************************************************************/
/* atCmd_Inquiries_Handler Handler                                      */
/************************************************************************/
sint8 atCmd_Inquiries_Handler(tstrAt_cmd_content *data, strAtCMD_Handler *pastrAtCMD_Handler)
{
	sint8 s8Ret = AT_ERR_NO_ERROR;
	uint8 u8LoopCntr;
	uint8 u8CmdLength = strlen((const char *)data->au8Cmd);
	//tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
	
	PRINT("atCmd_Inquiries_Handler\r\n");
	for(u8LoopCntr = 0; u8LoopCntr<AT_MAX_COMMANDS_COUNT; u8LoopCntr++) {
		if(!memcmp(data->au8Cmd, pastrAtCMD_Handler[u8LoopCntr].au8AtCMD, u8CmdLength)) {
			break;
		}
	}
	if(u8LoopCntr < AT_MAX_COMMANDS_COUNT) {
		printf("\r\n>>Description of [%s] command:\r\n", pastrAtCMD_Handler[u8LoopCntr].au8AtCMD);
	} else {
		printf("\r\n>>Invalid Command, You can use one of the following forms:\r\n");
	}
	switch(u8LoopCntr)
	{
		case AT_INDEX_CONFIG:
		{
			printf("%s  \r\n", "AT+CFG=2[CMD,VALUE]<CR><LF>");
			printf("\t%s\r\n", "This command used to set or reset some configuration for the host.");
			printf("\t%s\r\n", "where CMD   : is a command for configuration");
			printf("\t%s\r\n", "      VALUE : is the value for this command");
			printf("\t%s\r\n", "EX.: AT+CFG=2[ECHO,0], AT+CFG=2[ECHO,1] -> to Disable/Enable ECHO mode.");
			break;
		}
		case AT_INDEX_LIST:
		{
			printf("%s  \r\n", "AT+LIST<CR><LF>");
			printf("\t%s\r\n", "This command used to get a list of all AT Commands.");
			break;
		}
		case AT_INDEX_HELP:
		{
			printf("%s  \r\n", "AT+HELP<CR><LF>");
			printf("\t%s\r\n", "This command use to display how to write AT Command.");
			break;
		}
		case AT_INDEX_SCAN:
		{
			printf("%s  \r\n", "AT+SCAN=1[CHANNEL]<CR><LF>");
			printf("\t%s\r\n", "where CHANNEL : is channel number to scan on.");
			printf("\t%s\r\n", "                This value can be 1 -> 13.");
			printf("\t%s\r\n", "EX.: AT+SCAN=1[255] -> to scan over all channels at the same time.");
			break;
		}
		case AT_INDEX_CONN:
		{
			printf("%s  \r\n", "AT+CONN=5[SSID,SSID_LENGTH,SEC_TYPE,SEC_KEY,CHANNEL]<CR><LF>");
			printf("\t%s\r\n", "where SSID        : is Access Point you want to connect with.");
			printf("\t%s\r\n", "      SSID_LENGTH : number of characters of SSID");
			printf("\t%s\r\n", "      SEC_TYPE    : Type of Security of AP and has one of the following:");
			printf("\t%s\r\n", "          1       : OPEN");
			printf("\t%s\r\n", "          2       : WPA/WPA2");
			printf("\t%s\r\n", "          3       : WEP");
			printf("\t%s\r\n", "          4       : Enterprise");
			printf("\t%s\r\n", "      SEC_KEY     : Security key and will be in case of:");
			printf("\t%s\r\n", "          OPEN      : at least any character");
			printf("\t%s\r\n", "          WPA/WPA2  : any valid sequence of characters");
			printf("\t%s\r\n", "          WEP       : KEY_INDEX*KEY_VALUE ,where they areconcatenated with '*'");
			printf("\t%s\r\n", "          Enterprise: USRNAME*PASSWORD ,where they are concatenated with '*'");
			printf("\t%s\r\n", "      CHANNEL     : is channel number of the Access Point");
			
			printf("\t%s\r\n", "EX.: AT+CONN=5[DEMO_AP,7,1,NS,5]                  -> Connect to OPEN");
			printf("\t%s\r\n", "   : AT+CONN=5[DEMO_AP,7,2,1234567890,6]          -> Connect to WPA/WPA2");
			printf("\t%s\r\n", "   : AT+CONN=5[DEMO_AP,7,3,1*1234567890,7]        -> Connect to WEP");
			printf("\t%s\r\n", "   : AT+CONN=5[DEMO_AP,7,4,EntUser*EntPassword,8] -> Connect to Enterprise");
			break;
		}
		case AT_INDEX_AP_DISABLE:
		{
			printf("%s  \r\n", "AT+AP_DIS<CR><LF>");
			printf("\t%s\r\n", "This command use to disable Opened Access Point Mode.");
			break;
		}
		case AT_INDEX_AP_ENABLE:
		{
			printf("%s  \r\n", "AT+AP_EN=5[SSID,SSID_VISIBLE_MODE,SEC_TYPE,SEC_KEY,CHANNEL]<CR><LF>");
			printf("\t%s\r\n", "where SSID             : is Access Point you want to connect with.");
			printf("\t%s\r\n", "      SSID_VISIBLE_MODE: which means the SSI is visible or Hidden");
			printf("\t%s\r\n", "          0            : Visible SSID");
			printf("\t%s\r\n", "          1            : Hidden SSID");
			printf("\t%s\r\n", "      SEC_TYPE         : Type of Security of AP and has one of the following:");
			printf("\t%s\r\n", "          1            : OPEN");
			printf("\t%s\r\n", "          3            : WEP");
			printf("\t%s\r\n", "      SEC_KEY          : Security key and will be in case of:");
			printf("\t%s\r\n", "          OPEN         : at least any character");
			printf("\t%s\r\n", "          WEP          : KEY_INDEX*KEY_VALUE ,where they areconcatenated with '*'");
			printf("\t%s\r\n", "      CHANNEL          : is channel number of the Access Point");
			
			printf("\t%s\r\n", "EX.: AT+AP_EN=5[DEMO_AP,0,1,NS,5]            -> OPEN with Hidden SSID");
			printf("\t%s\r\n", "   : AT+AP_EN=5[DEMO_AP,1,3,1*1234567890,7]  -> WEP with visible SSID");
			break;
		}
		case AT_INDEX_DISCONN:
		{
			printf("%s  \r\n", "AT+DISCONN<CR><LF>");
			printf("\t%s\r\n", "This command use to disconnect your station from the connected access point");
			break;
		}
		/*case AT_INDEX_GROWL_INIT:
		{
			printf("%s  \r\n", "AT+GROWL_INIT<CR><LF>");
			printf("\t%s\r\n", "This command use to make initialization of growl application.");
			break;
		}
		case AT_INDEX_GROWL_SEND:
		{
			printf("%s  \r\n", "AT+GROWL_SEND=5[ID,APP_NAME,EVENT_NAME,DECREPTION_NAME,SSL_CONNECTION]<CR><LF>");
			printf("\t%s\r\n", "where ID             : is 1 Byte which has the value of NMA and Growl at the same time as:");
			printf("\t%s\r\n", "                       Bits(7:4) for NMA and Bits(3:0) for PROWL and both must have different values.");
			printf("\t%s\r\n", "      APP_NAME       : name of application");
			printf("\t%s\r\n", "      EVENT_NAME     : name of the event for application");
			printf("\t%s\r\n", "      DECREPTION_NAME: description of the application");
			printf("\t%s\r\n", "      SSL_CONNECTION : type of connection, also Bits(7:4) for NMA and Bits(3:0) for PROWL as follows:");
			printf("\t%s\r\n", "          0          : Normal Connection");
			printf("\t%s\r\n", "          1          : Secured Connection");
			printf("\t%s\r\n", "EX.: AT+GROWL_SEND=5[33,APP_NAME,APP_EVENT,APP_DESC,16]");
			printf("\t%s\r\n", "     33 -> Means: 1->for growl and 2->for NMA");
			printf("\t%s\r\n", "     16 -> Means: 0->for growl and 1->for NMA");
			break;
		}
		case AT_INDEX_NMA:
		{
			printf("%s  \r\n", "AT+NMA=5[ID,APP_NAME,EVENT_NAME,DECREPTION_NAME,SSL_CONNECTION]<CR><LF>");
			printf("\t%s\r\n", "where ID             : is 1 Byte which has the value of ID for NMA");
			printf("\t%s\r\n", "      APP_NAME       : name of application");
			printf("\t%s\r\n", "      EVENT_NAME     : name of the event for application");
			printf("\t%s\r\n", "      DECREPTION_NAME: description of the application");
			printf("\t%s\r\n", "      SSL_CONNECTION : type of connection");
			printf("\t%s\r\n", "          0          : Normal Connection");
			printf("\t%s\r\n", "          1          : Secured Connection");
			printf("\t%s\r\n", "EX.: AT+NMA=5[2,APP_NAME,APP_EVENT,APP_DESC,1]");
			break;
		}
		case AT_INDEX_PROWL:
		{
			printf("%s  \r\n", "AT+PROWL=5[ID,APP_NAME,EVENT_NAME,DECREPTION_NAME,SSL_CONNECTION]<CR><LF>");
			printf("\t%s\r\n", "where ID             : is 1 Byte which has the value of ID for PROWL");
			printf("\t%s\r\n", "      APP_NAME       : name of application");
			printf("\t%s\r\n", "      EVENT_NAME     : name of the event for application");
			printf("\t%s\r\n", "      DECREPTION_NAME: description of the application");
			printf("\t%s\r\n", "      SSL_CONNECTION : type of connection");
			printf("\t%s\r\n", "          0          : Normal Connection");
			printf("\t%s\r\n", "          1          : Secured Connection");
			printf("\t%s\r\n", "EX.: AT+PROWL=5[1,APP_NAME,APP_EVENT,APP_DESC,0]");
			break;
		}
		case AT_INDEX_GROWL_DEINIT:
		{
			printf("%s  \r\n", "AT+GROWL_DEINIT<CR><LF>");
			printf("\t%s\r\n", "This command use to disable growl application.");
			break;
		}*/
		case AT_INDEX_RSSI:
		{
			printf("%s  \r\n", "AT+RSSI<CR><LF>");
			printf("\t%s\r\n", "This command use to get RSSI of connected Access Point.");
			break;
		}
		case AT_INDEX_P2P_ENABLE:
		{
			printf("%s  \r\n", "AT+P2P_EN=1[CHANNEL]<CR><LF>");
			printf("\t%s\r\n", "where CHANNEL : is channel number to scan on.");
			printf("\t%s\r\n", "                This value can be 1 -> 13.");
			printf("\t%s\r\n", "EX.: AT+P2P_EN=1[6] -> to scan over all channels at the same time.");
			break;
		}
		case AT_INDEX_P2P_DISABLE:
		{
			printf("%s  \r\n", "AT+P2P_DIS<CR><LF>");
			printf("\t%s\r\n", "This command use to disable P2P Modes.");
			break;
		}
		/*case AT_INDEX_PROV_ENABLE:
		{
			printf("%s  \r\n", "AT+PROV_START=8[SSID,SSID_VISIBLE_MODE,SEC_TYPE,SEC_KEY,CHANNEL,SERVER_IP,SERVER_DOMAIN,REDIRECT_STATE]<CR><LF>");
			printf("\t%s\r\n", "where SSID             : is Access Point you want to connect with.");
			printf("\t%s\r\n", "      SSID_VISIBLE_MODE: which means the SSI is visible or Hidden");
			printf("\t%s\r\n", "          0            : Visible SSID");
			printf("\t%s\r\n", "          1            : Hidden SSID");
			printf("\t%s\r\n", "      SEC_TYPE         : Type of Security of AP and has one of the following:");
			printf("\t%s\r\n", "          1            : OPEN");
			printf("\t%s\r\n", "          3            : WEP");
			printf("\t%s\r\n", "      SEC_KEY          : Security key and will be in case of:");
			printf("\t%s\r\n", "          OPEN         : at least any character");
			printf("\t%s\r\n", "          WEP          : KEY_INDEX*KEY_VALUE ,where they areconcatenated with '*'");
			printf("\t%s\r\n", "      CHANNEL          : is channel number of the Access Point");
			printf("\t%s\r\n", "      SERVER_IP        : is an IP which the station can access through it");
			printf("\t%s\r\n", "                         where they are concatenated with '*'");
			printf("\t%s\r\n", "      SERVER_DOMAIN    : is a domain which the station can access through it");
			printf("\t%s\r\n", "      REDIRECT_STATE   : to allow redirection or not while typing any other domain or IP:");
			printf("\t%s\r\n", "          0            : Disable redirection");
			printf("\t%s\r\n", "          1            : Enable redirection");
			
			printf("\t%s\r\n", "EX.: AT+PROV_START=5[DEMO_AP,0,1,NS,5,192*168*1*1,test_domain.com,1]           -> OPEN with Hidden SSID");
			printf("\t%s\r\n", "   : AT+PROV_START=5[DEMO_AP,1,3,1*1234567890,7,192*168*0*1,test_domain.com,0] -> WEP with visible SSID");
			break;
		}
		case AT_INDEX_PROV_DISABLE:
		{
			printf("%s  \r\n", "AT+PROV_DIS<CR><LF>");
			printf("\t%s\r\n", "This command use to disable provisioning mode.");
			break;
		}*/
		case AT_INDEX_WPS_START:
		{
			printf("%s  \r\n", "AT+WPS_START=2[TRIGGER_TYPE,PIN_CODE]<CR><LF>");
			printf("\t%s\r\n", "where TRIGGER_TYPE : type of how to connect withing WPS:");
			printf("\t%s\r\n", "          0        : Using PIN Code");
			printf("\t%s\r\n", "          4        : Using Push Button");
			printf("\t%s\r\n", "      PIN_CODE     : The key in case of using TRIGGER_TYPE as PIN Code");
			printf("\t%s\r\n", "EX.: AT+WPS_START=1[4]");
			printf("\t%s\r\n", "   : AT+WPS_START=2[0,12345679]");
			break;
		}
		case AT_INDEX_WPS_DISABLE:
		{
			printf("%s  \r\n", "AT+WPS_DIS<CR><LF>");
			printf("\t%s\r\n", "This command use to disable WPS Mode.");
			break;
		}
		case AT_INDEX_IPCON:
		{
			printf("%s  \r\n", "There are three modes for this command:");
			printf("\t%s\r\n", "  1.- AT+IPCON=2[<PROTOCOL>,<LOCAL_PORT>]<CR><LF>");
			printf("\t%s\r\n", "      where PROTOCOL : TCP or UDP");			
			printf("\t%s\r\n", "      where PORT : Port of the listen socket to be created");
			printf("\t%s\r\n", "      EX. AT+IPCON=2[UDP,6666]");
			printf("\t%s\r\n", "  2.- AT+IPCON=3[<PROTOCOL>,<REMOTE_IP>,<REMOTE_PORT>]<CR><LF>");
			printf("\t%s\r\n", "      where REMOTE_IP : IP of the remote machine to connect to");
			printf("\t%s\r\n", "      where REMOTE_PORT : Port of the connection socket to connect to");
			printf("\t%s\r\n", "      EX. AT+IPCON=3[UDP,192.168.1.3,4444]");
			break;
		}
		case AT_FILEDOWNLOAD:
		{
			printf("\t%s\r\n", "   AT+FILE_DOWNLOAD=1[<FILE_URL>]<CR><LF>");
			printf("\t%s\r\n", "      where FILE_URL : HTTP URL of the file to be downloaded");
			printf("\t%s\r\n", "      EX. AT+FILE_DOWNLOAD=1[http://ww1.microchip.com/downloads/en/DeviceDoc/doc7529.pdf]");
			break;	
		}
		/*case AT_INDEX_SDS:
		{
			printf("%s  \r\n", "There are two modes for this command:");			
			printf("%s  \r\n", "  1.- <Esc>SDS=3[<CID>,<LEN>,<DATA>]");
			printf("\t%s\r\n", "      where CID : CID to send data to");
			printf("\t%s\r\n", "      where LEN: Length of the data to be send");
			printf("\t%s\r\n", "      where DATA: Data to be send");					
			printf("\t%s\r\n", "      EX. [1B]SDS=3[1,5,Hello]");							
			printf("%s  \r\n", "  2.- <Esc>SDS=5[<CID>,<REMOTE_IP>,<REMOTE_PORT>,<LEN>,<DATA>]");
			printf("\t%s\r\n", "      where CID : CID to send data to");
			printf("\t%s\r\n", "      where REMOTE_IP : IP of the remote machine to send data to");
			printf("\t%s\r\n", "      where REMOTE_PORT : Port of the remote machine to send data to");			
			printf("\t%s\r\n", "      where LEN: Length of the data to be send");
			printf("\t%s\r\n", "      where DATA: Data to be send");
			printf("\t%s\r\n", "      EX. [1B]SDS=5[0,192.168.1.3,4444,5,Hello]");													
			break;			
		}
		case AT_INDEX_DELCID:
		{
			printf("%s  \r\n", "AT+DELCID=1[<CID>]");
			printf("\t%s\r\n", "where CID : CID to delete");						
			break;			
		}*/
#if SAM4SD32		
		case AT_INDEX_OTA:
		{
			printf("%s  \r\n", "AT+OTA=1[<URL>]");
			printf("\t%s\r\n", "where URL : Full URL path to the OTA image");
			//printf("\t%s\r\n", "where \"ROLLBACK\" : Forces a OTA Rollback to the old image");
			break;
		}
#endif		
		/*case AT_INDEX_GETVER:
		{
			printf("%s  \r\n", "AT+GETVER");
			break;
		}*/
		case AT_INDEX_RESET:
		{
			printf("%s  \r\n", "AT+RESET");
			break;
		}
		case AT_INDEX_IPERF:
		{
			printf("%s  \r\n", "AT+IPERF=1[<PROTOCOL>]");
			printf("\t%s\r\n", "	where PROTOCOL : TCP or UDP");															
			break;
		}
		
		case AT_INDEX_HTTPCON:
		{
			printf("%s  \r\n", "AT+HTTPCON=4[<SERVERNAME>,<PORT>]");
			printf("\t%s\r\n", "      where SERVERNAME: The name of the server you want to stablish a connection to");
			printf("\t%s\r\n", "      where PORT      : The port to be used for the connection");			
			break;
		}
		case AT_TX_PWR:
		{
			printf("%s  \r\n", "AT+TX_PWR=1[TX_PWR_LEVEL]");
			printf("\t%s\r\n", "      where TX_PWR_LEVEL: 0dBm, 3dBm, 6dBm, 9dBm, 12dBm, 15dBm, 18dBm");
			break;
		}
		case AT_ANT_DIV:
		{
			printf("%s  \r\n", "AT+ANT_DIV=1[ANTENNA_SELECTION,ANT_SWTCH_GPIO_CTRL_MODE]");
			printf("\t%s\r\n", "      where ANTENNA_SELECTION: (1==ANTENNA1, 2==ANTENNA2, 3==DIVERSITY)");
			printf("\t%s\r\n", "      where ANT_SWTCH_GPIO_CTRL_MODE: (1 = ANT_SWTCH_GPIO_SINGLE, 2 = ANT_SWTCH_GPIO_DUAL or 3 = ANT_SWTCH_GPIO_NONE}");
			break;
		}
		case AT_CHIP_INFO:
		{
			printf("%s  \r\n", "AT+CHIP_INFO");
			break;
		}		
		/*case AT_TLS_CRL_RESET:
		{
			printf("%s  \r\n", "AT+TLS_CRL_RESET=1[<CRL_TYPE>]");
			printf("\t%s\r\n", "      where CRL_TYPE: 0 for none, 1 for CERT_HASH");	
			break;
		}
		case AT_TLS_CRL_ADD:
		{
			printf("%s  \r\n", "AT+TLS_CRL_ADD=1[<CERT_LEN>,<CERT_HASH>]");
			printf("\t%s\r\n", "      where CERT_LEN: Number of bytes for the hashed certificate");
			printf("\t%s\r\n", "      where CERT_HASH: Certificate hash in hexadecimal colon separated byte by byte");
			printf("\t%s\r\n", "      eg. e4:ae:c7:5e:43:4a:05:e7:08:5d:b9:1f:40:f6:91:1c:a2:91:eb:b4:2f:a2:8a:3e:e2:67:09:f8:e0:21:44:6b");						
			break;
		}	
		case AT_TLS_CRL_SEND:
		{
			printf("%s  \r\n", "AT+TLS_CRL_SEND");
			break;
		}
		case AT_INDEX_TLS_SET_CS:
		{
			M2M_PRINT("%s  \r\n", "AT+TLS_SET_CS=1[<CIPHER-SUITE>]");
			M2M_PRINT("\t%s\r\n", "where CIPHER-SUITE : is a 32-bit value indicating which cipher-suites should be enabled");
			break;
		}
		case AT_INDEX_TLS_WCERT:
		{
			M2M_PRINT("%s  \r\n", "AT+TLS_WCERT");
			break;
		}
		case AT_SSL_OPT:
		{
			M2M_PRINT("%s  \r\n\r\n", "AT+SSL_OPTIONS=4[<BYPASS_MODE>,<SESSION_CACHING>,<SERVER_NAME_CHECK>,<SNI_STRING>");
			M2M_PRINT("\t%s\r\n", "BYPASS_MODE: Set or Unset Bypass Mode");
			M2M_PRINT("\t%s\r\n", "\t0 : DISABLED");
			M2M_PRINT("\t%s\r\n", "\t1 : ENABLED");
			M2M_PRINT("\t%s\r\n", "SESSION_CACHING: Set or Unset Session Caching.");
			M2M_PRINT("\t%s\r\n", "\t0 : DISABLED");
			M2M_PRINT("\t%s\r\n", "\t1 : ENABLED");
			M2M_PRINT("\t%s\r\n", "SERVER_NAME_CHECK: Set or unset checking of server certificate name against SNI_STRING.");
			M2M_PRINT("\t%s\r\n", "\t0 : DISABLED");
			M2M_PRINT("\t%s\r\n", "\t1 : ENABLED");
			M2M_PRINT("\t%s\r\n", "SNI_STRING: Server name to be sent in the Client Hello SNI extension.");
			M2M_PRINT("\t\t%s\r\n\r\n", "Special case: If SNI_STRING begins with '0' then no SNI extension is sent.");
			M2M_PRINT("%s\r\n", "EXAMPLE: AT+SSL_OPTIONS=4[0,1,0,0]                                     -> Enable Session Caching");
			M2M_PRINT("%s\r\n", "\t     : AT+SSL_OPTIONS=4[0,0,0,hostname.com]            -> Server name sent in Client Hello SNI Extension");
			M2M_PRINT("%s\r\n", "\t     : AT+SSL_OPTIONS=4[0,0,1,hostname.com]            -> Enable checking of server name" );
			break;
		}*/
		default:	
		{
			printf("\tWithout parameters             : AT+cmd<CR><LF>\r\n");
			printf("\tUsing parameters               : AT+cmd=N[param1,param2,....,paramN]<CR><LF>\r\n");
			printf("\tTo display help use            : AT+cmd/?<CR><LF>\r\n");
			printf("\tTo display List of Commands use: AT+LIST<CR><LF>\r\n");
			printf("\r\n");
			printf("\tTo display Help use            : HELP<CR><LF>\r\n");
			s8Ret = AT_ERR_NOT_REGISTERED_CMD;
			break;
		}
	}
	printf("\r\n\tWhere <CR>\"Carriage Return\" -> (13)");
	printf("\r\n\t      <LF>\"Line Feed\"       -> (10)");
	printf("\r\n>>");
	return s8Ret;
}

static uint8 Ascii2Hex(uint8 u8AsciiChar)
{
	uint8	u8Hex = 0xFF;
	if((u8AsciiChar >= 'A') && (u8AsciiChar <= 'F'))
	{
		u8Hex = u8AsciiChar - 0x37;
	}
	else if((u8AsciiChar >= '0') && (u8AsciiChar <= '9'))
	{
		u8Hex = u8AsciiChar - 0x30;
	}
	else if((u8AsciiChar >= 'a') && (u8AsciiChar <= 'f'))
	{
		u8Hex = u8AsciiChar - 0x57;
	}
	return u8Hex;
}

static sint32 StrMac2Bin(char* ps8MacStr,char* ps8MacBin)
{
	sint32 ret = M2M_SUCCESS;
	if(ps8MacStr == NULL || ps8MacBin == NULL)
	{
		printf("NULL pointer\n");
		return M2M_ERR_FAIL;
	}
	
	if(memcmp("any",ps8MacStr,4))
	{
		uint32_t i=0;
		int ind =0;
		while(i<strlen(ps8MacStr))
		{
			if(ps8MacStr[i] != ':')
			{
				ps8MacBin[ind] = Ascii2Hex(ps8MacStr[i])<<4;
				i++;
				ps8MacBin[ind] |= Ascii2Hex(ps8MacStr[i]);
				M2M_DBG("%x",ps8MacBin[ind]);
				ind++;
			}else{
				M2M_DBG("-");
			}
			i++;
		}
		M2M_DBG("\r\n");
	}
	else
	{
		memset(ps8MacBin,0,6);
	}
	return ret;
}

uint8 u8DataSubType[AT_MAX_DATA_SUBTYPE] = {DATA, DATA_ACK, DATA_POLL, DATA_POLL_ACK, NULL_FRAME, CFACK, CFPOLL, CFPOLL_ACK, QOS_DATA, QOS_DATA_ACK, QOS_DATA_POLL, QOS_DATA_POLL_ACK, QOS_NULL_FRAME, QOS_CFPOLL, QOS_CFPOLL_ACK};
uint8 u8ControlSubtype[AT_MAX_CONTROL_SUBTYPE] = {PS_POLL, RTS, CTS, ACK, CFEND, CFEND_ACK, BLOCKACK_REQ, BLOCKACK};
uint8 u8MangmentSubtype[AT_MAX_MANGEMENT_SUBTYPE] = {ASSOC_REQ, ASSOC_RSP, REASSOC_REQ, REASSOC_RSP, PROBE_REQ, PROBE_RSP, BEACON, ATIM, DISASOC, AUTH, DEAUTH, ACTION};

tstrMonstats gstrMonitorDataStats;
tstrMonstats gstrMonitorControlStats;
tstrMonstats gstrMonitorMangementStats;

sint8 atCmd_MonEn_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 ret = AT_ERR_NO_ERROR;
	tstrM2MWifiMonitorModeCtrl strMonitorConf;
	char* pSrcMac = (char *)data->au8ParamsList[3];
	char* pDstMac = (char *)data->au8ParamsList[4];
	char* pBssidMac = (char *)data->au8ParamsList[5];
	int i;

	if(gaAt_CMD_handler_fn[AT_INDEX_MON_EN].u8NoOfParameters != data->u8NumOfParameters)
	{
		ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	memset(&strMonitorConf, 0, sizeof(tstrM2MWifiMonitorModeCtrl));
	strMonitorConf.u8ChannelID = (uint8)GET_CH_ENUM_VAL(atoi((char *)data->au8ParamsList[0]));
	
	if(memcmp(data->au8ParamsList[1],"0x",2) || strlen((char *)data->au8ParamsList[1])!=4)
	{
		ret = AT_ERR_INVALID_ARGUMENTS;
		goto EXIT;
	}
	strMonitorConf.u8FrameType =  Ascii2Hex(data->au8ParamsList[1][2])<<4;
	strMonitorConf.u8FrameType |=Ascii2Hex(data->au8ParamsList[1][3]);
	
	if(strMonitorConf.u8FrameType != MANAGEMENT && strMonitorConf.u8FrameType !=  CONTROL
		&& strMonitorConf.u8FrameType != DATA_BASICTYPE && strMonitorConf.u8FrameType !=255)
		{
			ret = AT_ERR_INVALID_ARGUMENTS;
			goto EXIT;
		}
	if(memcmp(data->au8ParamsList[2],"0x",2) || strlen((char *)data->au8ParamsList[2])!=4)
	{
		ret = AT_ERR_INVALID_ARGUMENTS;
		goto EXIT;
	}
	strMonitorConf.u8FrameSubtype =  Ascii2Hex(data->au8ParamsList[2][2])<<4;
	strMonitorConf.u8FrameSubtype |=Ascii2Hex(data->au8ParamsList[2][3]);


	if(StrMac2Bin(pSrcMac,(char*)strMonitorConf.au8SrcMacAddress)
		|| StrMac2Bin(pDstMac,(char*)strMonitorConf.au8DstMacAddress)
		|| StrMac2Bin(pBssidMac,(char*)strMonitorConf.au8BSSID))
		{
			ret = M2M_ERR_FAIL;
			goto EXIT;
		}
	strMonitorConf.u8EnRecvHdr = (uint8)atoi((char *)data->au8ParamsList[6]);
	
	M2M_DBG("ch : %d\r\nframetype : %d\r\nsubtype : %x\r\n",strMonitorConf.u8ChannelID,strMonitorConf.u8FrameType,strMonitorConf.u8FrameSubtype);
	M2M_DBG("src: %02X:%02X:%02X:%02X:%02X:%02X\r\n",strMonitorConf.au8SrcMacAddress[0],
		strMonitorConf.au8SrcMacAddress[1],strMonitorConf.au8SrcMacAddress[2],
		strMonitorConf.au8SrcMacAddress[3],strMonitorConf.au8SrcMacAddress[4],
		strMonitorConf.au8SrcMacAddress[5]);

	memset(&gstrMonitorDataStats,0,sizeof(gstrMonitorDataStats));
	memset(&gstrMonitorControlStats,0,sizeof(gstrMonitorControlStats));
	memset(&gstrMonitorMangementStats,0,sizeof(gstrMonitorMangementStats));
	
	if(strMonitorConf.u8FrameType == DATA_BASICTYPE)
	{
		gstrMonitorDataStats.s32Enabled = 1;
		for(i=0;i<AT_MAX_DATA_SUBTYPE;i++)
		{
			if(strMonitorConf.u8FrameSubtype==0xFF || u8DataSubType[i] == strMonitorConf.u8FrameSubtype)
			{
				gstrMonitorDataStats.strFilterSubtype[i].s8Enabled = 1;
			}
		}
	}
	else if(strMonitorConf.u8FrameType==CONTROL)
	{
		gstrMonitorControlStats.s32Enabled=1;
		for(i=0;i<AT_MAX_CONTROL_SUBTYPE;i++)
		{
			if(strMonitorConf.u8FrameSubtype==0xFF || u8ControlSubtype[i] == strMonitorConf.u8FrameSubtype)
			{
				gstrMonitorControlStats.strFilterSubtype[i].s8Enabled = 1;
			}
		}
	}
	else if(strMonitorConf.u8FrameType == MANAGEMENT)
	{
		gstrMonitorMangementStats.s32Enabled=1;
		for(i=0;i<AT_MAX_MANGEMENT_SUBTYPE;i++)
		{
			if(strMonitorConf.u8FrameSubtype==0xFF || u8MangmentSubtype[i]==strMonitorConf.u8FrameSubtype)
			{
				gstrMonitorMangementStats.strFilterSubtype[i].s8Enabled = 1;
			}
		}
	}
	ret = os_m2m_wifi_enable_monitoring_mode(&strMonitorConf);
	if(ret == M2M_SUCCESS)
	{
		AT_SEND_OK("MON_EN");
	}
	else
	{
		AT_SEND_ERROR(ret,"MON_EN");
	}
	
EXIT:
	return ret;
}
sint8 atCmd_MonDis_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 ret = AT_ERR_NO_ERROR;

	if(gaAt_CMD_handler_fn[AT_INDEX_MON_DIS].u8NoOfParameters != data->u8NumOfParameters)
	{
		ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	
	ret = os_m2m_wifi_disable_monitoring_mode();
	
	if(ret==M2M_SUCCESS)
	{
		print_monitoring_result();
		AT_SEND_OK("MON_DIS");
	}
	else
	{
		AT_SEND_ERROR(ret,"MON_DIS");
	}
	memset(&gstrMonitorDataStats,0,sizeof(gstrMonitorDataStats));
	memset(&gstrMonitorControlStats,0,sizeof(gstrMonitorControlStats));
	memset(&gstrMonitorMangementStats,0,sizeof(gstrMonitorMangementStats));
EXIT:
	return ret;
}
void print_monitoring_result(){
	int i =0;
	if(gstrMonitorDataStats.s32Enabled)
	{
		printf("******** Monitor <Data> ********\r\n");
		for(i=0;i<AT_MAX_DATA_SUBTYPE;i++)
		{
			printf("[0x%02X]: %ld\r\n",u8DataSubType[i],gstrMonitorDataStats.strFilterSubtype[i].s32NumPkt);
		}
		printf("Total: %ld\r\n",gstrMonitorDataStats.s32AnyDataFrame);
	}
	else if(gstrMonitorControlStats.s32Enabled)
	{
		printf("******** Monitor  <Control> ********\r\n");
		for(i=0;i<AT_MAX_CONTROL_SUBTYPE;i++)
		{
			printf("[0x%02X]: %ld\r\n",u8ControlSubtype[i],gstrMonitorControlStats.strFilterSubtype[i].s32NumPkt);
		}
		printf("Total: %ld\r\n",gstrMonitorDataStats.s32AnyDataFrame);
		
	}
	else if(gstrMonitorMangementStats.s32Enabled)
	{
		printf("******** Monitor <Mangement> ********\r\n");
		for(i=0;i<AT_MAX_MANGEMENT_SUBTYPE;i++)
		{
			printf("[0x%02X]: %ld\r\n",u8MangmentSubtype[i],gstrMonitorMangementStats.strFilterSubtype[i].s32NumPkt);
		}
		printf("Total: %ld\r\n",gstrMonitorMangementStats.s32AnyDataFrame);
	}
}



sint8 atCmd_PsMode_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 ret = AT_ERR_NO_ERROR;
	sint8 s8PsMode = 0;
	sint32 i;
	
	if(gaAt_CMD_handler_fn[AT_INDEX_PS_MODE].u8NoOfParameters != data->u8NumOfParameters)
	{
		ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	s8PsMode = atoi(data->au8ParamsList[0]);
	if(s8PsMode < M2M_NO_PS || s8PsMode > M2M_PS_DEEP_AUTOMATIC)
	{
		M2M_PRINT("Invalid PS type: Enter 0 for M2M_NO_PS, 1 for M2M_PS_DEEP_AUTOMATIC\n");
		ret = AT_ERR_INVALID_ARGUMENTS;
		goto EXIT;
	}

/*This (if) block has an effect only for WILC3000 when BLE is enabled.
		It does not have any effect for WILC1000 */
	if(uart_is_rx_ready(USART1))
	{	
		uart_read((Uart *)USART1, &data); // sometimes its called as CONF_UART
		if (s8PsMode == M2M_PS_DEEP_AUTOMATIC) {
			M2M_DBG("PS_MODE USART: assert\r\n");
			usart_start_tx_break(USART0); // also known as BOARD_USART
		}
		else if (s8PsMode == M2M_NO_PS) {
			M2M_DBG("PS_MODE USART: de-assert\r\n");
			usart_stop_tx_break(USART0);
		}
	}
	/* Execute command */
	ret = m2m_wifi_set_sleep_mode(s8PsMode,true);
	if(ret == AT_ERR_NO_ERROR)
	{
		sint8 s8Buf[20] = {0};
		sprintf(s8Buf,"PS_MODE:%d",s8PsMode);
		AT_SEND_OK(s8Buf);
	}
	else
	{
		AT_SEND_ERROR(ret,"PS_MODE");
	}
	
	EXIT:
	return ret;
}

sint8 atCmd_GetConnInfo_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	printf("atCmd_GetConnInfo_Handler\r\n");
	sint8 ret;
	ret = os_m2m_wifi_get_connection_info();
	return ret;
}

sint8 atCmd_ChipInfo_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	printf("atCmd_ChipInfo_Handler\r\n");

	sint8 s8Ret;
	uint8_t mac_addr[M2M_MAC_ADDRES_LEN];
	uint8_t read_mac_addr[M2M_MAC_ADDRES_LEN];
	uint8_t u8IsMacAddrValid;
	/** User define MAC Address. */
	const char main_user_define_mac_address[] = {0xf8, 0xf0, 0x05, 0x20, 0x0b, 0x09};
	const char main_user_define_mac_address1[] = {0xf8, 0xf0, 0x05, 0x20, 0x0b, 0x0A};
	
	/* Get MAC Address from OTP. */
	os_m2m_wifi_get_otp_mac_address( (uint8_t *)mac_addr, &u8IsMacAddrValid);
	if (!u8IsMacAddrValid) {
		osprintf("USER MAC Address : \r\n");

		/* Cannot find MAC Address from OTP. Set user define MAC address. */
		
		/* Also set the other MAC address to be locally modified, if required*/
		//main_user_define_mac_address1[0] = main_user_define_mac_address[0]^0x02;

		os_m2m_wifi_set_mac_address((uint8_t *)main_user_define_mac_address, (uint8_t *) main_user_define_mac_address1);
		} else {
		printf("OTP MAC Address : \r\n");
	}

	/* Get MAC Address. */
	os_m2m_wifi_get_mac_address((uint8_t *)mac_addr, (uint8_t *)read_mac_addr );

	/* Note - Address should be read from LSB to MSB */
	osprintf("%02X:%02X:%02X:%02X:%02X:%02X\r\n",
	mac_addr[0], mac_addr[1], mac_addr[2],
	mac_addr[3], mac_addr[4], mac_addr[5]);

	osprintf("%02X:%02X:%02X:%02X:%02X:%02X\r\n",
	read_mac_addr[0], read_mac_addr[1], read_mac_addr[2],
	read_mac_addr[3], read_mac_addr[4], read_mac_addr[5]);
	
	/* Display WILC1000 chip information. */
	osprintf("Chip ID : \r\t\t\t%x\r\n", (unsigned int)nmi_get_chipid());
	osprintf("RF Revision ID : \r\t\t\t%x\r\n", (unsigned int)nmi_get_rfrevid());
	osprintf("Done.\r\n\r\n");
		s8Ret = AT_ERR_NO_ERROR;
EXIT:
	return s8Ret;
	
}

#if 0
sint8 atCmd_SetPowerProfile_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret;
	uint8 u8PwrProfile = 0;
	u8PwrProfile = atoi((const char*)data->au8ParamsList[0]);
	s8Ret = m2m_wifi_set_power_profile(u8PwrProfile);
	return s8Ret;
}
extern void http_client_test_init(void);
extern void set_download_url(char*);

#endif
sint8 atCmd_FileDownload_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret;
	tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
	PRINT("atCmd_FileDownload_Handler\r\n");

	if(gaAt_CMD_handler_fn[AT_FILEDOWNLOAD].u8NoOfParameters != data->u8NumOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	if(	(SERVICE_IS_RUNNING != status->u8Ap_status) && (SERVICE_IS_RUNNING != status->u8Sta_status)){
		PRINT("Neither STA mode nor AP mode connected\r\n");
		s8Ret = AT_ERR_INVALID_OPERATION;
		goto EXIT;
	}
	/*clear existing struct*/
	memset((tstrAt_cmd_content *)&temp_cmd_content , 0, sizeof(tstrAt_cmd_content));
	/*copy new command struct*/
	memcpy((tstrAt_cmd_content *)&temp_cmd_content ,data, sizeof(tstrAt_cmd_content));
	#ifdef AT_CMD_SEM
	osprintf("HTTP Dwn give\r\n");
	xSemaphoreGive(at_cmd_task1_sem);
	osprintf("HTTP Dwn given\r\n");
	#endif
	AT_SEND_OK(data->au8Cmd);
	s8Ret = AT_ERR_NO_ERROR;
EXIT:
	return s8Ret;
}
#if 0
sint8 atCmd_ScanPassive_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = M2M_ERR_FAIL;
	uint8 u8ChNo = (uint8) atoi(data->au8ParamsList[0]);
	uint16 u16ScanTime = (uint16) atoi(data->au8ParamsList[1]);
	SetScanTimeStart();
	s8Ret = m2m_wifi_request_scan_passive(u8ChNo, u16ScanTime);
	
	return s8Ret;
}

sint8 atCmd_SslEnableCertExpirationCheck(tstrAt_cmd_content *data, void* moreData, uint8 useStoreValue)
{
	sint8 s8Ret = M2M_ERR_FAIL;
	uint8 u8ExpChkFlag = (uint8) atoi(data->au8ParamsList[0]);
	
	if(u8ExpChkFlag > 1)
	{
		s8Ret = AT_ERR_INVALID_ARGUMENTS;
		
	}
	else
	{
		s8Ret = sslEnableCertExpirationCheck(u8ExpChkFlag);
		if(AT_ERR_NO_ERROR == s8Ret)
		{
			AT_SEND_OK("EN_CERT_EXPCHK");
		}
		else
		{
			AT_SEND_ERROR(s8Ret,"EN_CERT_EXPCHK");
		}
	}
	
		
	return s8Ret;
}

static void pingCb(uint32 u32IPAddr, uint32 u32RTT, uint8 u8ERR)
{
	uint8 *pu8ERR_str[] = {"PING_ERR_SUCCESS","PING_ERR_DEST_UNREACH","PING_ERR_TIMEOUT"};
	M2M_INFO("(%u)Ping status %s\n", gu32PingCount, pu8ERR_str[u8ERR]);
	gu32PingCount --;
	if(gu32PingCount > 0)
	{
		m2m_ping_req(u32IPAddr, 0, pingCb);
	}
	else
	{
		M2M_INFO("Test Finished\n");
	}
	if(pu8ERR_str[u8ERR]=="PING_ERR_SUCCESS")
	{
		AT_SEND_OK("PING");
	}
	else
	{
		AT_SEND_ERROR(gu32PingCount,pu8ERR_str[u8ERR]);
	}
}

static void pingTestResolveCb(uint8* pu8DomainName, uint32 u32HostIP)
{
	if(u32HostIP != 0)
	{
		m2m_ping_req(u32HostIP, 0, pingCb);
	}
}
#endif
sint8 atCmd_Ping(tstrAt_cmd_content *data, void* moreData, uint8 useStoreValue)
{
	sint8	s8Ret = M2M_ERR_FAIL;
	ip_addr_t* u32PingDest;
	tstr_test_conn_status *status = (tstr_test_conn_status *)moreData;
		
	if(data->u8NumOfParameters != gaAt_CMD_handler_fn[AT_INDEX_PING].u8NoOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	if(	(SERVICE_IS_RUNNING != status->u8Ap_status) && (SERVICE_IS_RUNNING != status->u8Sta_status)){
		M2M_ERR("Neither STA mode nor AP mode connected\r\n");
		s8Ret = AT_ERR_INVALID_OPERATION;
		goto EXIT;
	}	
	uint8 u8count = 0, u8count_dot = 0;
	char *pcPingDest = data->au8ParamsList[0];
	M2M_INFO("Pinging Dest %s\n",pcPingDest);

	uint32 u32PingCount = (uint32) atoi(data->au8ParamsList[1]);
	if((pcPingDest != NULL))
	{

		s8Ret = AT_ERR_NO_ERROR;
		if((*pcPingDest >= '1') && (*pcPingDest <= '9'))
		{
			/*clear existing struct*/
		memset((tstrAt_cmd_content *)&temp_cmd_content , 0, sizeof(tstrAt_cmd_content));
			/*copy new command struct*/
		memcpy((tstrAt_cmd_content *)&temp_cmd_content ,data, sizeof(tstrAt_cmd_content));	
		#ifdef AT_CMD_SEM
		//M2M_INFO("\nGiving at_cmd_task1_sem for Ping");
			xSemaphoreGive(at_cmd_task1_sem);
		#endif
		}
		else
		{
			gethostbyname(pcPingDest);
		}
	}
EXIT:
	return s8Ret;
}
#if 0
static tstrTlsCrlInfo gCRL = {0};
sint8 atCmd_TlsCrlReset_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = AT_ERR_NO_ERROR;
	uint8 u8CertRevocType = atoi(data->au8ParamsList[0]);

	if(gaAt_CMD_handler_fn[AT_TLS_CRL_RESET].u8NoOfParameters != data->u8NumOfParameters)
	{
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}

	memset(&gCRL,0,sizeof(tstrTlsCrlInfo));
	gCRL.u8CrlType = u8CertRevocType;

	M2M_INFO("CRL has been reset");
	AT_SEND_OK(data->au8Cmd);

EXIT:
	return s8Ret;
}

/*
uint8 AsciiString2Hex(uint8 *pu8AsciiString)

Description:
	Converts colon-separated ascii string representing hex bytes into hex.
	Conversion is done in-place.

Params:
	pu8AsciiString	Zero-terminated ascii string. Must be colon-separated, with characters in the
						range [0-9,a-f,A-F]. 1 or 2 characters between each colon.

Return:
	Length of resulting hex buffer.
	0 if input string could not be processed.
*/
static uint8 AsciiString2Hex(uint8 *pu8AsciiString)
{
	uint8 *pu8Dat = (uint8 *)strtok((char *)pu8AsciiString,":");
	uint8 u8DataLen = 0;

	while (pu8Dat != NULL)
	{
		uint8 u8Hex = Ascii2Hex(*pu8Dat++);
		if(u8Hex == 0xff)
			return 0;
		if(*pu8Dat != 0)
		{
			uint8 u8Tmp = Ascii2Hex(*pu8Dat++);
			if(u8Tmp == 0xff)
				return 0;
			u8Hex = u8Hex * BASE_16 + u8Tmp;
		}
		if(*pu8Dat != 0)
			return 0;
		*(pu8AsciiString + u8DataLen) = u8Hex;
		u8DataLen++;
		// Look for the next output of strtok
		pu8Dat = (uint8 *)strtok(NULL,":");
	}

	return u8DataLen;
}

sint8 atCmd_TlsCrlAdd_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = AT_ERR_NO_ERROR;
	uint8 u8Index;
	uint8 u8DataLen = atoi(data->au8ParamsList[0]);	/* Data length specified by user */

	tstrTlsCrlEntry *pCrlEntry = gCRL.astrTlsCrl;

	if(gaAt_CMD_handler_fn[AT_TLS_CRL_ADD].u8NoOfParameters != data->u8NumOfParameters)
	{
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}

	if(u8DataLen > TLS_CRL_DATA_MAX_LEN)
	{
		s8Ret = AT_ERR_INVALID_ARGUMENTS;
		goto EXIT;
	}

	if(AsciiString2Hex(data->au8ParamsList[1]) != u8DataLen)
	{
		s8Ret = AT_ERR_INVALID_ARGUMENTS;
		goto EXIT;
	}

	for(u8Index=0; u8Index<TLS_CRL_MAX_ENTRIES; u8Index++)
	{
		if(pCrlEntry->u8DataLen == 0)
			break;
		pCrlEntry++;
	}

	if(u8Index == TLS_CRL_MAX_ENTRIES)
	{
		M2M_INFO("ERROR: No space to allocate another entry");
		s8Ret = M2M_ERR_FAIL;
		goto EXIT;
	}

	pCrlEntry->u8DataLen = u8DataLen;
	memcpy(pCrlEntry->au8Data, data->au8ParamsList[1], u8DataLen);

	M2M_INFO("New entry added to CRL");
	AT_SEND_OK(data->au8Cmd);

EXIT:
	return s8Ret;
}

sint8 atCmd_TlsCrlSend_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = M2M_ERR_FAIL;

	if(gaAt_CMD_handler_fn[AT_TLS_CRL_SEND].u8NoOfParameters != data->u8NumOfParameters)
	{
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}

	s8Ret = m2m_wifi_send_crl(&gCRL);
	M2M_INFO("CRL sent");

EXIT:
	return s8Ret;
}

sint8 atCmd_SslGlobalOption_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = M2M_ERR_FAIL;

	if(gaAt_CMD_handler_fn[AT_SSL_OPT].u8NoOfParameters != data->u8NumOfParameters)
	{
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
		
	memset(gHostNameSNI,0,AT_MAX_HOST_NAME);
	if (data->au8ParamsList[3][0] != '0')
		memcpy(gHostNameSNI,data->au8ParamsList[3],AT_MAX_HOST_NAME);
	
	gstrSslOptions.bIsBypassModeEnabled = atoi(data->au8ParamsList[0]);
	gstrSslOptions.bIsSessionCachingEnabled = atoi(data->au8ParamsList[1]);
	gstrSslOptions.bIsCertNameCheckEnabled = atoi(data->au8ParamsList[2]);

	AT_SEND_OK("SSL_OPTIONS");
	s8Ret = M2M_SUCCESS;	
EXIT:
	return s8Ret;
}

sint8 atCmd_GetSysTime_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	sint8 s8Ret = AT_ERR_NO_ERROR;

	if(data->u8NumOfParameters != gaAt_CMD_handler_fn[AT_INDEX_GETIME].u8NoOfParameters){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	
	if(m2m_wifi_get_sytem_time() != M2M_SUCCESS)
	{
		M2M_INFO("ERROR: Failed to request SysTime to the WINC");
		s8Ret = M2M_ERR_FAIL;
		goto EXIT;
	}
EXIT:
	return s8Ret;
}
#endif
sint8 atCmd_TxPwr_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	osprintf("atCmd_TxPwr_Handler\r\n");
    sint8 s8Ret = AT_ERR_NO_ERROR;
    uint8 pwr_val = 0;
    
    if(gaAt_CMD_handler_fn[AT_TX_PWR].u8NoOfParameters != data->u8NumOfParameters)
	{
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
    
    pwr_val = atoi((char *)data->au8ParamsList[0]);

    if ((pwr_val < TX_PWR_DBM_0) || (pwr_val > TX_PWR_DBM_18)) //TX power ppa to one of these values: 0dBm, 3dBm, 6dBm, 9dBm, 12dBm, 15dBm, 18dBm.
    {
        M2M_INFO("ERROR: Parameter must be between 0 and 18 inclusive (0dBm <<< 18dBm)");
        s8Ret = AT_ERR_INVALID_ARGUMENTS;
		goto EXIT;
    }

    m2m_wifi_set_tx_power(pwr_val);
    osprintf("TX power level (Range: 0dBm <<< 18dBm) set to %d", pwr_val);
         
EXIT:
    return s8Ret;
}

sint8 atCmd_AntDiversity_Handler(tstrAt_cmd_content *data, void* moreData, uint8 useStoredValue)
{
	osprintf("atCmd_AntDiversity_Handler\r\n");
	sint8 s8Ret = AT_ERR_NO_ERROR;
	uint8 ant_sel = 0;
	uint8 gpio_ctrl = 0;
	
	/* Check for ANTENNA_SELECTION and ANT_SWTCH_GPIO_CTRL_MODE parameters*/
	if(data->u8NumOfParameters != 2){
		s8Ret = AT_ERR_NUM_OF_PARAMS;
		goto EXIT;
	}
	
	ant_sel = atoi((const char *)data->au8ParamsList[0]);
	gpio_ctrl = atoi((const char *)data->au8ParamsList[1]);
	
	osprintf(">>ANTENNA_SELECTION: %d (0==ANTENNA1, 1==ANTENNA2, 2==DIVERSITY)\r\n",ant_sel);
	osprintf(">>ANT_SWTCH_GPIO_CTRL_MODE: %d (1 = ANT_SWTCH_GPIO_SINGLE, 2 = ANT_SWTCH_GPIO_DUAL or 0 = ANT_SWTCH_GPIO_NONE)\r\n",gpio_ctrl);
	/* ANTENNA_GPIO_NUM_1, ANTENNA_GPIO_NUM_2 set in at_cmd_Handler.h*/
	if(M2M_SUCCESS != (s8Ret= m2m_wifi_set_antenna_mode(ant_sel, gpio_ctrl, ANTENNA_GPIO_NUM_1, ANTENNA_GPIO_NUM_2))) {

		s8Ret = AT_ERR_INVALID_ARGUMENTS;
	}
	
	EXIT:
	return s8Ret;
}

void handle_data()
{
	uint8	u8RxChar = gau8Rx_buffer[0];
	gu8IsrFired = true;
	switch(gu8CmdStatus)
	{
		case AT_CMD_STATUS_IDLE:
		{
			switch(strlen((const char *)gau8DataBuffer))
			{
				case 0:
				{
					if (u8RxChar == ESCAPE_CHAR)
					{
						escape_command = true;
						break;
					}
					if(('A' != u8RxChar) && ('H' != u8RxChar))
					{
						goto INVALID_CH;
					}
					break;
				}//End case 0 of strlen(gau8DataBuffer)
				case 1:
				{
					if(!escape_command)
					{
						if(('T' != u8RxChar) && ('E' != u8RxChar))
						{
							goto INVALID_CH;
						}
					}
					break;
				}//End case 1 of strlen(gau8DataBuffer)
				case 2:
				{
					if(!escape_command)
					{
						if(('+' != u8RxChar) && ('L' != u8RxChar))
						{
							goto INVALID_CH;
						}
					}
					break;
				}//End case 2 of strlen(gau8DataBuffer)
				case 3:
				{
					if(!escape_command)
					{
						escape_command = false;
						if(('L' == gau8DataBuffer[2]) && ('P' != u8RxChar)) {
							goto INVALID_CH;
						}
					}
					break;
				}//End case 3 of strlen(gau8DataBuffer)
			}
			//Fill in Buffer
			switch(u8RxChar)
			{
				case '\r':
				carriage_return = true;
				case '\n':
				{
					if(carriage_return == true)
					{
						carriage_return = false;
						if(gu8CmdStatus != AT_CMD_STATUS_CHECK)
						{
							gu8CmdStatus = AT_CMD_STATUS_CHECK;
							RESET_VAR_TO_0(gu16Data_Index);
							if(0 == strlen((const char *)gau8DataBuffer))
							{
								gu8InvalidPrinted = false;
							}
						}
					}
					else
					{
						gau8DataBuffer[gu16Data_Index++] = u8RxChar;
					}
					goto EXIT;
				}
				default:
				{
					gau8DataBuffer[gu16Data_Index++] = u8RxChar;
					goto EXIT;
				}
			}
			break;
		}
		default:
		{
			/*Nothing*/
			goto EXIT;
		}
	}

	INVALID_CH:
	gu8InvalidPrinted = false;
	//	memset(gau8Rx_buffer, 0, MAX_RX_BUFFER_LENGTH);
	EXIT:
	//usart_read_buffer_job((struct usart_module *)uart_module, (uint8_t *)gau8Rx_buffer, 1);
	return;
}
/**
* \brief UART IRQ handler.
*
* Interrupt handler for UART. 
*
*/
void UART_Handler(void)
{
	/* Read UART Status. */
	uint32_t dw_status = uart_get_status(CONF_UART);

	if (dw_status & US_CSR_RXRDY) {
		uint32_t received_byte;
		uart_read(CONF_UART, (uint8_t *)&received_byte);
		//usart_write(CONF_UART, received_byte);
		gau8Rx_buffer[rx_pos/*++*/] = received_byte;
		handle_data();
		//rx_pos = 0;
	}
}

static sint8 init_m2m_app(void)
{
	memset((char *)&gstrAllStatus, 0, sizeof(tstr_test_conn_status));
	gstrAllStatus.u8Sta_status = SERVICE_IS_STOPPED;
	/*Default Configuration of APP*/
	gtstrApp_config.u8Echo_status  = ENABLED;
	gtstrApp_config.u8Disaply_hint = ENABLED;
	init_at_cmd_handler(gastrAtCMD_Handler);
	#ifdef DEBUG_CMD
	print_cmd_handler_arr(gastrAtCMD_Handler);
	#endif
	printf("CFG    State"
	"\r\n------------\r\n");
	printf("ECHO   %s \r\n",(gtstrApp_config.u8Echo_status)?("ENABLED"):("DISABLED"));
	printf("HINT   %s \r\n",(gtstrApp_config.u8Disaply_hint)?("ENABLED"):("DISABLED"));
	printf("------------\r\n\r\n");
	return M2M_SUCCESS;
}

static void start_m2m_app(void)
{
	sint8 s8Ret = -1;
	use_static_IP = 0; // By default code flow for static IP is disabled	
	uint8 *pu8Data = NULL;
	while (true)
	{
		if(gu8IsrFired)
		{
			/*nm_bsp_stop_timer();*/
			if(ENABLED == gtstrApp_config.u8Echo_status)
			{
				printf("%c",gau8Rx_buffer[0]);
			}
			if(!gu8InvalidPrinted)
			{
				if(gau8Rx_buffer[0] == '\n' || gau8Rx_buffer[0] == '\r'){
					printf("\r\n>>");
				}else {
					printf(":Invalid Input\r\n>>");
				}
				memset(gau8DataBuffer,0,sizeof(gau8DataBuffer));
				RESET_VAR_TO_0(gu16Data_Index);
				gu8InvalidPrinted = true;
			}
			gu8IsrFired = false;
			//nm_bsp_start_timer(timer_cb, USART_TIMEOUT_M_SEC);
		}
		/*else if(gu8TO)
		{
			printf("TimeOut Current Data Buffer <%s>\r\n",gau8DataBuffer);
			gu8TO = 0;
		}*/
		switch(gu8CmdStatus){
			case AT_CMD_STATUS_CHECK:
				PRINT("\r\n");
#				ifdef DEBUG_CMD
				PRINT("\r\n>>Received Data: %s\r\n",gau8DataBuffer);
#				endif
				memset((char *)&gstrAt_cmdContent, 0, sizeof(gstrAt_cmdContent));
				s8Ret = parse_cmd(gau8DataBuffer, &gstrAt_cmdContent, gstrAt_cmd_parse_chrs);
#				ifdef DEBUG_CMD
				PRINT(">>CMD           : %s\r\n",('\0' == gstrAt_cmdContent.au8Cmd[0])?(char *)"No CMD":(char *)gstrAt_cmdContent.au8Cmd);
				PRINT(">>#Parameters   : %d\r\n",gstrAt_cmdContent.u8NumOfParameters);
				for(uint8 u8LoopCntr=0; u8LoopCntr<AT_MAX_PARAMETERS_COUNT; u8LoopCntr++) {
					if(gstrAt_cmdContent.au8ParamsList[u8LoopCntr][0] == 0) {
						break;
					}
					PRINT("                       [%02u]: %s\r\n", u8LoopCntr+1, gstrAt_cmdContent.au8ParamsList[u8LoopCntr]);
				}
				PRINT("\r\n");
#				endif
				if((M2M_SUCCESS == s8Ret) || (AT_ERR_CMD_IS_INQUIRY == s8Ret)){
					gu8CmdStatus = AT_CMD_STATUS_RUN;
				} else {
					gu8CmdStatus = AT_CMD_STATUS_IDLE;
					AT_SEND_ERROR(s8Ret, "Handling Error");
					if(AT_ERR_NUM_OF_PARAMS == s8Ret) {
						if(ENABLED == gtstrApp_config.u8Disaply_hint) {
							atCmd_Inquiries_Handler(&gstrAt_cmdContent, gastrAtCMD_Handler);
						} else {
							M2M_ERR("CMD parameters are more or less than expectation\r\n");
						}
					} else if(AT_ERR_CHR_NUM_OF_CMD == s8Ret) {
						M2M_ERR("CMD characters are not as excepected\r\n");
					} else {
						M2M_ERR("Invalid CMD\r\n");
					}
					memset((char *)gau8DataBuffer, 0, sizeof(gau8DataBuffer));
				}
				break;
			case AT_CMD_STATUS_RUN:
				if(AT_ERR_CMD_IS_INQUIRY != s8Ret) {
					s8Ret = get_index_cmdHandler(&gstrAt_cmdContent, (strAtCMD_Handler *)&gastrAtCMD_Handler);
				}
				switch(s8Ret){
					case AT_INDEX_CONFIG:
						pu8Data = (uint8 *)&gtstrApp_config;
						break;
#					if 0
					case AT_INDEX_WDTEST_INIT:
						pu8Data = (uint8 *)&tcp_cb;
						gu8Sleep = PS_WAKE;
						break;
#					endif
					default:
						pu8Data = (uint8 *)&gstrAllStatus;
						break;
				}
				if((0 <= s8Ret) && (AT_ERR_CMD_IS_INQUIRY != s8Ret)) {
					/* TCP/UDP have variable number of parameters */
					if(gstrAt_cmdContent.u8NumOfParameters <= gastrAtCMD_Handler[s8Ret].u8NoOfParameters){
						s8Ret = gastrAtCMD_Handler[s8Ret].at_cmd_handler(&gstrAt_cmdContent, pu8Data, 0);
					} else {
						s8Ret = AT_ERR_NUM_OF_PARAMS;
					}
				} else if (AT_ERR_CMD_IS_INQUIRY == s8Ret) {
					s8Ret = atCmd_Inquiries_Handler(&gstrAt_cmdContent, gastrAtCMD_Handler);
				}
				print_Handle_status(s8Ret, gstrAt_cmdContent.au8Cmd);
				memset((char *)gau8DataBuffer, 0, sizeof(gau8DataBuffer));
				memset((char *)&gstrAt_cmdContent, 0, sizeof(gstrAt_cmdContent));
				gu8CmdStatus = AT_CMD_STATUS_IDLE;
				printf("\r\n>>");
				break;
			case AT_CMD_STATUS_IDLE:
				/* handle Nothing*/
				break;
			default:/*Corruption in memory*/
				M2M_ERR(">_< Unknown Command Status: %d >_< \r\n",gu8CmdStatus);
				memset((char *)gau8DataBuffer, 0, sizeof(gau8DataBuffer));
				memset((char *)&gstrAt_cmdContent, 0, sizeof(gstrAt_cmdContent));
				gu8CmdStatus = AT_CMD_STATUS_IDLE;
				break;
		}
	}
}

void cmd_handler(void *argument)
{
	vTaskDelay(1000); // wait for system init
	sint8 ret;
	ret = init_m2m_app();
	if(M2M_SUCCESS == ret) {
		AT_SEND_OK("Init");
		M2M_INFO("\rNow,You can send CMD or use HELP for help.\r\n>>");
		start_m2m_app();
	} else {
		M2M_ERR("\r\nFailed to initialize APP.");
		AT_SEND_ERROR(ret,"APP Init");
		while(1){
			/*Infinite Loop*/
		}
	}
}