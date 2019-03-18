/**
 *
 * \file
 *
 * \brief This module contains WILC Coexistence APIs implementation.
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
 #include "common/include/nm_common.h"
 
#ifdef CONF_WILC_USE_3000_REV_A

#include "driver/include/m2m_coex.h"
#include "driver/include/m2m_wifi.h"
#include "driver/source/m2m_hif.h"
#include "nmasic.h"

extern tuCtrlStruct guCtrlStruct;

NMI_API sint8  m2m_coex_set_mode(tenuCoexMode enuCoexMode)
{
	sint8 ret = M2M_SUCCESS;
	tstrM2mCoexMode* pstrM2mCoexMode = &guCtrlStruct.strM2mCoexMode;
	tstrM2mCoexNullFramesMode* pstrM2mCoexNullFramesMode = &guCtrlStruct.strM2mCoexNullFramesMode;

	switch(enuCoexMode)
	{
		case M2M_COEX_MODE_WIFI:
			pstrM2mCoexMode->enuNmiCoexMode = NMI_COEX_MODE_WIFI;
			ret = hif_send(M2M_REQ_GRP_WIFI, M2M_WIFI_REQ_SET_COEX_MODE, (uint8*)pstrM2mCoexMode,sizeof(tstrM2mCoexMode), NULL, 0, 0);
			if(ret == M2M_SUCCESS)
			{
				pstrM2mCoexNullFramesMode->enuNmiCoexNullFramesMode = NMI_COEX_NULL_FRAMES_OFF;
				ret = hif_send(M2M_REQ_GRP_WIFI, M2M_WIFI_REQ_SET_COEX_NULL_FRAMES_MODE, (uint8*)pstrM2mCoexNullFramesMode,sizeof(tstrM2mCoexNullFramesMode), NULL, 0, 0);
			}			
			break;
		case M2M_COEX_MODE_BT:
			pstrM2mCoexMode->enuNmiCoexMode = NMI_COEX_MODE_BT;
			ret = hif_send(M2M_REQ_GRP_WIFI, M2M_WIFI_REQ_SET_COEX_MODE, (uint8*)pstrM2mCoexMode,sizeof(tstrM2mCoexMode), NULL, 0, 0);
			if(ret == M2M_SUCCESS)
			{
				pstrM2mCoexNullFramesMode->enuNmiCoexNullFramesMode = NMI_COEX_NULL_FRAMES_OFF;
				ret = hif_send(M2M_REQ_GRP_WIFI, M2M_WIFI_REQ_SET_COEX_NULL_FRAMES_MODE, (uint8*)pstrM2mCoexNullFramesMode,sizeof(tstrM2mCoexNullFramesMode), NULL, 0, 0);
			}			
			break;
		case M2M_COEX_MODE_COMBO:
			pstrM2mCoexMode->enuNmiCoexMode = NMI_COEX_MODE_COMBO;
			ret = hif_send(M2M_REQ_GRP_WIFI, M2M_WIFI_REQ_SET_COEX_MODE, (uint8*)pstrM2mCoexMode,sizeof(tstrM2mCoexMode), NULL, 0, 0);
			if(ret == M2M_SUCCESS)
			{
				pstrM2mCoexNullFramesMode->enuNmiCoexNullFramesMode = NMI_COEX_NULL_FRAMES_ON;
				ret = hif_send(M2M_REQ_GRP_WIFI, M2M_WIFI_REQ_SET_COEX_NULL_FRAMES_MODE, (uint8*)pstrM2mCoexNullFramesMode,sizeof(tstrM2mCoexNullFramesMode), NULL, 0, 0);
			}			
			break;
	}

	return ret;
}

#endif /* CONF_WILC_USE_3000 */

