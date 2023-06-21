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

#ifndef __NMI_GROWL_H__
#define __NMI_GROWL_H__

#include "common/include/nm_common.h"

#define PROWL_CLIENT					1
#define NMA_CLIENT						2

#define GROWL_EVENT_MAX_LENGTH			16
#define GROWL_DESCRIPTION_MAX_LENGTH	72
#define GROWL_APPNAME_MAX_LENGTH		16

/* Possible Error codes could be returned by the nma server. */
#define GROWL_SUCCESS					20			/*!< NMA notification sent successfully. Actual returned code = "200". */

#define GROWL_ERR_BAD_REQUEST			40			/*!< The sent notification has a format error. Actual returned code = "400". */
#define GROWL_ERR_NOT_AUTHORIZED		41			/*!< The API Key supplied with the request is invalid. Actual returned code = "401". */
#define GROWL_ERR_NOT_ACCEPTED			42			/*!< Maximum number of API calls per hour exceeded. Actual returned code = "402". */
#define GROWL_ERR_API_EXCEED			46			/*!< Actual returned code = "4069". */
#define GROWL_ERR_NOT_APPROVED			49			/*!< Actual returned code = "409". */
#define GROWL_ERR_SERVER_ERROR			50			/*!< Internal server error. Actual returned code = "500". */

#define GROWL_ERR_LOCAL_ERROR			30			/*!< An error occured on the m2m device due to internal problem. */

#define GROWL_ERR_CONN_FAILED			10			/*AFTER NUMBER OF ITERATION*/
#define GROWL_ERR_RESOLVE_DNS 			11

#define GROWL_RETRY						12

/*!
*  @typedef			tpfNmaResponseCallback
*  @brief				Callback invoked when the Nma notification response is received from the the NMA server.
*  @param [in]		u8ResponseCode
*						Response status code. It may be one of the following:
*						NMA_SUCCESS
*						NMA_ERR_BAD_REQUEST
*						NMA_ERR_NOT_AUTHORIZED
*						NMA_ERR_NOT_ACCEPTED
*						NMA_ERR_SERVER_ERROR
*  @author			Ahmed Ezzat
*  @date				2 Aug 2012
*  @version			1.0
*/

#ifdef __cplusplus
extern "C"
{
#endif

/*!
*  @fn				void NMI_GrowlInit(void)
*  @brief
*  @author			Dina El Sissy
*  @date			2 Jan 2013
*  @version			1.0
*/
NMI_API void NMI_GrowlInit(uint8 *pu8PrwKey,uint8 *pu8NmaKey);

/*!
*  @fn				sint8 NMI_SendNotification(char	*pcApp,char *pcEvent, char *pcDescription)
*  @brief			Send a specific notification to a Registered Nma device.
*  @param [in]		client
*						The name of teh Growl Client NMA or Prowl.
*  @param [in]		pcApp
*						Application which generate the notification.
*  @param [in]		pcEvent
*						Event triggered the notification.
*  @param [in]		pcDescription
*						Message describes the event happened.
*  @author			Ahmed Ezzat
*  @date			16 July 2012
*  @version			1.0
*/
NMI_API sint8 NMI_GrowlSendNotification
(
	uint8					u8ClientName,
	uint8					*pu8App,
	uint8					*pu8Event,
	uint8					*pu8Description,
	uint8					bUseSSL
);

NMI_API void GrowlCb(uint8 u8Code, uint8 u8ClientID);
NMI_API void NMI_GrowldeInit(void);

#ifdef __cplusplus
}
#endif

#endif /* __NMI_GROWL_H__ */
