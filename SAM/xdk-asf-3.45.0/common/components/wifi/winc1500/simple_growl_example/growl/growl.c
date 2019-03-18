/**
 * \file
 *
 * \brief Growl Client Interface.
 *
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

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
INCLUDES
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#include "growl/growl.h"
#include "socket/include/socket.h"
#include "common/include/nm_common.h"


/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
MACROS
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/


#define MAX_REGISTERED_EVENTS				1
#define GROWL_CONNECT_RETRY					3
#define GROWL_DNS_RETRY						3


#define PROWL_DOMAIN_NAME				"api.prowlapp.com"//"www.google.com.eg"//
#define PROWL_CLIENT_STRING_ID			"prowl"//"google"//
#define PROWL_API_KEY_SIZE				40

#define NMA_DOMAIN_NAME					"www.notifymyandroid.com"
#define NMA_CLIENT_STRING_ID			"notifymyandroid"
#define NMA_API_KEY_SIZE				48

#define GROWL_HTTP_PORT					80
#define GROWL_HTTPS_PORT				443
#define GROWL_MSG_SIZE					256


#define GROWL_STATE_IDLE						((uint8)0)
#define GROWL_STATE_REQ_PENDING					((uint8)1)
#define GROWL_STATE_WAITING_RESPONSE			((uint8)2)

#define GROWL_RX_TIMEOUT						(25 * 1000)

static void AppServerCb(uint8* pu8HostName, uint32 u32ServerIP);

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
PRIVATE DATA TYPES
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

/*!
@struct	\
	tstrNotification

@brief

*/
typedef struct{
	uint32	u32ServerIPAddress;
	uint16	u16Port;
	SOCKET	Socket;
	uint8	u8State;
	uint8	*pu8App;
	uint8	*pu8Event;
	uint8	*pu8Msg;
}tstrNotification;


/*####################################################################################
GLOBALS
####################################################################################*/

static volatile tstrNotification		gstrNotificationProwl;
static volatile tstrNotification		gstrNotificationNMA;
static CONST uint8 					gau8HexDigits[] = "0123456789abcdef";
static volatile uint8					*gau8PrwKey;
static volatile uint8					*gau8NmaKey;
static volatile uint8					au8Msg[GROWL_DESCRIPTION_MAX_LENGTH];



NMI_API uint16 Encode(uint8 	*pcStr, uint8 *pcEncoded);

NMI_API uint16 FormatMsg(uint8 u8clientName, uint8 *pu8Msg);

NMI_API uint8 GetResponseCode(uint8	*pu8Buffer,uint16 u16BufferSize);

/*********************************************************************
Function:

Description:

Return: None.

Author: Ahmed Ezzat

Version: 1.0

Date:
*********************************************************************/
uint16 Encode(uint8 *pcStr,uint8 *pcEncoded)
{
	uint8		*pcTmp = pcStr;
	uint8		*pcbuf = pcEncoded;
	uint16		u16Count = 0;

	while(*pcTmp)
	{
		if (
			((*pcTmp >= '0') && (*pcTmp <= '9'))		||
			((*pcTmp >= 'a') && (*pcTmp <= 'z')) 	||
			((*pcTmp >= 'A') && (*pcTmp <= 'Z')) 	||
			(*pcTmp == '-') ||
			(*pcTmp == '_') ||
			(*pcTmp == '.') ||
			(*pcTmp == '~')
			)
		{
			*pcbuf++ = *pcTmp;
		}
		else
		{
			*pcbuf++ = '%';
			*pcbuf++ = gau8HexDigits[(*pcTmp>> 4) & 0x0F];
			*pcbuf++ = gau8HexDigits[(*pcTmp & 0x0F)];
			u16Count += 2;
		}
		pcTmp++;
		u16Count ++;
	}
	return u16Count;
}
/*********************************************************************
Function:

Description:

Return: None.

Author: Ahmed Ezzat

Version: 1.0

Date:
*********************************************************************/
uint16 FormatMsg(uint8 u8clientName, uint8 *pu8Msg)
{
	uint16	u16Tmp;
	uint16	u16MsgOffset = 0;
	tstrNotification* strNotification;

	if (u8clientName == NMA_CLIENT)
	{
		strNotification = (tstrNotification*)(&gstrNotificationNMA);
		/* Put the start of the HTTP Request message. */
		u16Tmp = sizeof("GET /publicapi/notify?apikey=") - 1;
		m2m_memcpy(&pu8Msg[u16MsgOffset],(uint8*)"GET /publicapi/notify?apikey=",u16Tmp);
		u16MsgOffset += u16Tmp;

		/* Add the API Key to the message. */
		m2m_memcpy(&pu8Msg[u16MsgOffset],(uint8*)gau8NmaKey,NMA_API_KEY_SIZE);
		u16MsgOffset+= NMA_API_KEY_SIZE;
	}
	else if (u8clientName == PROWL_CLIENT)
	{
		strNotification = (tstrNotification*)(&gstrNotificationProwl);

		/* Put the start of the HTTP Request message. */
		u16Tmp = sizeof("GET /publicapi/add?apikey=") - 1;
		m2m_memcpy(&pu8Msg[u16MsgOffset],(uint8*)"GET /publicapi/add?apikey=",u16Tmp);
		u16MsgOffset += u16Tmp;

		/* Add the API Key to the message. */
		m2m_memcpy(&pu8Msg[u16MsgOffset],(uint8*)gau8PrwKey,PROWL_API_KEY_SIZE);
		u16MsgOffset+= PROWL_API_KEY_SIZE;
	}
	else
		return 0;

	/* Encode the Application name and append it to the message. */
	u16Tmp = sizeof("&application=") - 1;
	m2m_memcpy(&pu8Msg[u16MsgOffset],(uint8*)"&application=",u16Tmp);
	u16MsgOffset += u16Tmp;
	u16Tmp = Encode((uint8*)strNotification->pu8App,&pu8Msg[u16MsgOffset]);
	u16MsgOffset += u16Tmp;

	/* Encode the Event name and append it to the message. */
	u16Tmp = sizeof("&event=") - 1;
	m2m_memcpy(&pu8Msg[u16MsgOffset],(uint8*)"&event=",u16Tmp);
	u16MsgOffset += u16Tmp;
	u16Tmp = Encode((uint8*)strNotification->pu8Event,&pu8Msg[u16MsgOffset]);
	u16MsgOffset += u16Tmp;

	/* Encode the Description message and append it to the message. */
	u16Tmp = sizeof("&description=") - 1;
	m2m_memcpy(&pu8Msg[u16MsgOffset],(uint8*)"&description=",u16Tmp);
	u16MsgOffset += u16Tmp;
	u16Tmp = Encode((uint8*)strNotification->pu8Msg,&pu8Msg[u16MsgOffset]);
	u16MsgOffset += u16Tmp;

	u16Tmp = sizeof(" HTTP/1.1\r\nHost: ") - 1;
	m2m_memcpy(&pu8Msg[u16MsgOffset],(uint8*)" HTTP/1.1\r\nHost: ",u16Tmp);
	u16MsgOffset += u16Tmp;

	if (u8clientName == NMA_CLIENT)
	{
		u16Tmp = sizeof(NMA_DOMAIN_NAME) - 1;
		m2m_memcpy(&pu8Msg[u16MsgOffset],(uint8*)NMA_DOMAIN_NAME,u16Tmp);
		u16MsgOffset += u16Tmp;
	}
	else if (u8clientName == PROWL_CLIENT)
	{
		u16Tmp = sizeof(PROWL_DOMAIN_NAME) - 1;
		m2m_memcpy(&pu8Msg[u16MsgOffset],(uint8*)PROWL_DOMAIN_NAME,u16Tmp);
		u16MsgOffset += u16Tmp;

	}

	u16Tmp = sizeof("\r\n\r\n") - 1;
	m2m_memcpy(&pu8Msg[u16MsgOffset],(uint8*)"\r\n\r\n",u16Tmp);
	u16MsgOffset += u16Tmp;
	pu8Msg[u16MsgOffset] = '\0';
	u16MsgOffset ++;

	return u16MsgOffset;
}
/*********************************************************************
Function:

Description:

Return: None.

Author: Ahmed Ezzat

Version: 1.0

Date:
*********************************************************************/
uint8 GetResponseCode
(
 uint8	*pu8Buffer,
 uint16	u16BufferSize
)
{
	uint8	u8Code = 0xFF;
	if((pu8Buffer != NULL) && (u16BufferSize > 0))
	{
		uint16	u16Offset = 0;
		do
		{
			if(!m2m_memcmp(&pu8Buffer[u16Offset], (uint8*)"HTTP/1.1 ", 9))
			{
				u16Offset += 9;
				if(!m2m_memcmp(&pu8Buffer[u16Offset], (uint8*)"200", 3))
				{
					u8Code = 20;
				}
				else if(!m2m_memcmp(&pu8Buffer[u16Offset], (uint8*)"400", 3))
				{
					u8Code = 40;
				}
				else if(!m2m_memcmp(&pu8Buffer[u16Offset], (uint8*)"401", 3))
				{
					u8Code = 41;
				}
				else if(!m2m_memcmp(&pu8Buffer[u16Offset], (uint8*)"402", 3))
				{
					u8Code = 42;
				}
				else if(!m2m_memcmp(&pu8Buffer[u16Offset], (uint8*)"406", 3))
				{
					u8Code = 46;
				}
				else if(!m2m_memcmp(&pu8Buffer[u16Offset], (uint8*)"409", 3))
				{
					u8Code = 49;
				}
				else
				{
					u8Code = 50;
				}
				break;
			}
			u16Offset ++;
		}while(u16Offset < (u16BufferSize - 9));
	}
	return u8Code;
}
/*********************************************************************
Function:

Description:

Return: None.

Author: Ahmed Ezzat

Version: 1.0

Date:
*********************************************************************/
static void GROWL_APPSocketEventHandler(SOCKET sock, uint8 u8Msg, void * pvMsg)
{
	tstrNotification	*pstrNotification;
	uint8 				u8ClientID;

	if(sock == gstrNotificationNMA.Socket)
	{
		pstrNotification = (tstrNotification*)(&gstrNotificationNMA);
		u8ClientID = NMA_CLIENT;
	}
	else if(sock == gstrNotificationProwl.Socket)
	{
		pstrNotification = (tstrNotification*)(&gstrNotificationProwl);
		u8ClientID = PROWL_CLIENT;

	}
	else
	{
		return;
	}

	if(u8Msg == SOCKET_MSG_CONNECT)
	{
		static uint8			u8Retry = GROWL_CONNECT_RETRY;
		tstrSocketConnectMsg	*pstrConnect = (tstrSocketConnectMsg*)pvMsg;
		if(pstrConnect->s8Error == 0)
		{
			uint8	acBuffer[GROWL_MSG_SIZE];
			uint16	u16MsgSize;

			u16MsgSize = FormatMsg(u8ClientID, acBuffer);
			send(sock, acBuffer, u16MsgSize, 0);
			recv(pstrNotification->Socket, (void*)au8Msg,GROWL_DESCRIPTION_MAX_LENGTH, GROWL_RX_TIMEOUT);
			u8Retry = GROWL_CONNECT_RETRY;
		}
		else
		{
			if((u8Retry--) > 0)
			{
				M2M_DBG("Retry %s\n",(u8ClientID == NMA_CLIENT) ? "NMA" : "PROWL");
				if (u8ClientID == NMA_CLIENT)
					AppServerCb((uint8*)NMA_DOMAIN_NAME, pstrNotification->u32ServerIPAddress);
				else if (u8ClientID == PROWL_CLIENT)
					AppServerCb((uint8*)PROWL_DOMAIN_NAME, pstrNotification->u32ServerIPAddress);
			}
			else
			{
				M2M_DBG("%s Connection Failed\n",(u8ClientID == NMA_CLIENT) ? "NMA" : "PROWL");
				close(pstrNotification->Socket);
				pstrNotification->Socket = 0xFF;
				pstrNotification->u8State = GROWL_STATE_IDLE;
				GrowlCb(GROWL_ERR_CONN_FAILED,u8ClientID);
				u8Retry = GROWL_CONNECT_RETRY;
			}
		}
	}
	else if(u8Msg == SOCKET_MSG_RECV)
	{
		tstrSocketRecvMsg		*pstrRecvMsg = (tstrSocketRecvMsg*)pvMsg;
		static uint8			u8Error = 0xFF;
		uint8				    u8Reset = 1;

		if((pstrRecvMsg->pu8Buffer != NULL) && (pstrRecvMsg->s16BufferSize > 0))
		{
			if(u8Error == 0xFF)
			{
				u8Error = GetResponseCode(pstrRecvMsg->pu8Buffer,pstrRecvMsg->s16BufferSize);
			}
		}
		if((pstrRecvMsg->s16BufferSize > 0) && (pstrRecvMsg->u16RemainingSize != 0))
		{
			u8Reset = 0;
		}
		if(u8Reset)
		{
			close(pstrNotification->Socket);
			pstrNotification->Socket	= 0xFF;
			pstrNotification->u8State	= GROWL_STATE_IDLE;
			GrowlCb(u8Error,u8ClientID);
			u8Error = 0xFF;
		}
	}
	else if(u8Msg == SOCKET_MSG_SEND)
	{
		sint16	s16Sent = *((sint16*)pvMsg);
		if(s16Sent <= 0)
		{
			M2M_ERR("GROWL Send Error %d\n",s16Sent);
		}
	}
}
/*********************************************************************
Function:

Description:

Return: None.

Author: Ahmed Ezzat

Version: 1.0

Date:
*********************************************************************/
void NMI_GrowlInit(uint8 *pu8PrwKey,uint8 *pu8NmaKey)
{
	socketInit();
	registerSocketCallback(GROWL_APPSocketEventHandler, AppServerCb);
	if(pu8PrwKey)
	{
		gau8PrwKey = pu8PrwKey;
	}
	else
	{
		M2M_INFO("Prowl key Not Vaild\n");
	}
	if(pu8NmaKey)
	{

		gau8NmaKey = pu8NmaKey;
	}
	else
	{
		M2M_INFO("NMA key Not Vaild\n");
	}
	m2m_memset((uint8*)&gstrNotificationProwl, 0, sizeof(tstrNotification));
	m2m_memset((uint8*)&gstrNotificationNMA, 0, sizeof(tstrNotification));
	gstrNotificationProwl.Socket = 0xFF;
	gstrNotificationNMA.Socket = 0xFF;
}

void NMI_GrowldeInit(void)
{
	m2m_memset((uint8*)&gstrNotificationProwl, 0, sizeof(tstrNotification));
	m2m_memset((uint8*)&gstrNotificationNMA, 0, sizeof(tstrNotification));
	if(gstrNotificationProwl.Socket != 0xff)
	{
		close(gstrNotificationProwl.Socket);
	}
	if(gstrNotificationNMA.Socket != 0xff)
	{
		close(gstrNotificationNMA.Socket);
	}
	gstrNotificationProwl.Socket = 0xFF;
	gstrNotificationNMA.Socket = 0xFF;
}
/*********************************************************************
Function:

Description:

Return: None.

Author: Ahmed Ezzat

Version: 1.0

Date: 4 June 2012
*********************************************************************/
static void AppServerCb(uint8* pu8HostName, uint32 u32ServerIP)
{
	struct sockaddr_in		strAddr;
	tstrNotification		*pstrNotification = NULL;
	uint8					u8ClientID = 0;

	if(m2m_strstr(pu8HostName,(uint8*)NMA_CLIENT_STRING_ID))
	{
		pstrNotification = (tstrNotification*)(&gstrNotificationNMA);
		u8ClientID = NMA_CLIENT;
	}
	else if(m2m_strstr(pu8HostName,(uint8*)PROWL_CLIENT_STRING_ID))
	{
		pstrNotification = (tstrNotification*)(&gstrNotificationProwl);
		u8ClientID = PROWL_CLIENT;
	}

	if(u32ServerIP != 0)
	{

		if(pstrNotification->u32ServerIPAddress == 0)
		{
			pstrNotification->u32ServerIPAddress = u32ServerIP;
		}

		strAddr.sin_family = AF_INET;
		strAddr.sin_port = _htons(pstrNotification->u16Port);
		strAddr.sin_addr.s_addr = u32ServerIP;

		connect(pstrNotification->Socket, (struct sockaddr*)&strAddr, sizeof(struct sockaddr_in));
	}
	else
	{
		static uint8	u8Retry = GROWL_DNS_RETRY;
		if(u8Retry--)
		{
			M2M_DBG("Retry Resolving DNS\n");
			if(m2m_strstr(pu8HostName,(uint8*)NMA_CLIENT_STRING_ID))
				gethostbyname((uint8*)NMA_DOMAIN_NAME);
			else if(m2m_strstr(pu8HostName,(uint8*)PROWL_CLIENT_STRING_ID))
				gethostbyname((uint8*)PROWL_DOMAIN_NAME);

		}
		else
		{
			close(pstrNotification->Socket);
			pstrNotification->Socket = 0xFF;
			pstrNotification->u8State = GROWL_STATE_IDLE;
			u8Retry = GROWL_DNS_RETRY;
			M2M_DBG("Failed to Resolve DNS\n\r");
			GrowlCb(GROWL_ERR_RESOLVE_DNS,u8ClientID);
		}
	}
}
/*********************************************************************
Function:

Description:

Return: None.

Author: Ahmed Ezzat

Version: 1.0

Date: 4 June 2012
Note : it's required to keep the {pu8App,pu8Event,pu8Description} pointers const or global not temp val.
*********************************************************************/
sint8 NMI_GrowlSendNotification(uint8 u8ClientName, uint8 *pu8App, uint8 *pu8Event, uint8 *pu8Description,uint8 bUseSSL)
{
	sint8		retVal = 0;
	uint8		u8Flags = 0;

	if((u8ClientName > 0) && (pu8App != NULL) && (pu8Event != NULL) && (pu8Description != NULL))
	{
		tstrNotification* pstrNotification;
		if((u8ClientName == NMA_CLIENT))
		{
			if(gau8NmaKey == NULL)
			{
				M2M_INFO("NMA key Not Vaild\n");
				return -1;
			}
			pstrNotification = (tstrNotification*)(&gstrNotificationNMA);
		}
		else if((u8ClientName == PROWL_CLIENT))
		{
			if(gau8PrwKey == NULL)
			{
				M2M_INFO("Prowl key Not Vaild\n");
				return -1;
			}
			pstrNotification = (tstrNotification*)(&gstrNotificationProwl);
		}
		else
			return M2M_ERR_FAIL;

		if(pstrNotification->u8State == GROWL_STATE_IDLE)
		{
			if((m2m_strlen(pu8Description) < GROWL_DESCRIPTION_MAX_LENGTH) &&
				(m2m_strlen(pu8App) < GROWL_APPNAME_MAX_LENGTH) &&
				(m2m_strlen(pu8Event) < GROWL_EVENT_MAX_LENGTH))
			{
				pstrNotification->pu8App = pu8App;
				pstrNotification->pu8Event = pu8Event;
				pstrNotification->pu8Msg = pu8Description;
				pstrNotification->u16Port = GROWL_HTTP_PORT;

				/* Create Connection to the NMA Server. */
				if(bUseSSL)
				{
					u8Flags = SOCKET_FLAGS_SSL;
					pstrNotification->u16Port = GROWL_HTTPS_PORT;
				}

				pstrNotification->Socket = socket(AF_INET,SOCK_STREAM,u8Flags);
				if(pstrNotification->Socket >= 0)
				{
					pstrNotification->u8State = GROWL_STATE_REQ_PENDING;
					if(u8ClientName == NMA_CLIENT)
						gethostbyname((uint8*)NMA_DOMAIN_NAME);
					else if(u8ClientName == PROWL_CLIENT)
						gethostbyname((uint8*)PROWL_DOMAIN_NAME);
				}
				else
				{
					M2M_ERR("No sockets available for the current request\n");
					retVal = -1;
				}
			}
			else
			{
				M2M_ERR("Msg size is too long\n");
				retVal = -1;
			}
		}
		else
		{
			M2M_ERR("Another %s Request is pending\n",(u8ClientName == NMA_CLIENT) ? "NMA" : "PROWL");
			retVal = -1;
		}
	}
	else
	{
		retVal = -1;
	}
	return retVal;
}
