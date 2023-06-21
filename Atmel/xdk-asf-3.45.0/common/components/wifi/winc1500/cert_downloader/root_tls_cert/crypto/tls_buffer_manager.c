/**
 * \file
 *
 * \brief Implementation for TLS buffer manager.
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

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
INCLUDES
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#include "tls_buffer_manager.h"


/**********************************************************************
Function
	TLS_BufferRead

Description
	
Return
	u16Read
***********************************************************************/
uint16 TLS_BufferRead(tstrTlsBuffer	*pstrTlsBuff, uint16 u16ReadByteCount, uint8 *pu8ReadBuffer)
{
	uint16	u16Read = 0;
	
	if(pstrTlsBuff != NULL)
	{
		if((u16ReadByteCount + pstrTlsBuff->u16ReadOffset) < pstrTlsBuff->u16BuffSz)
		{
			u16Read = u16ReadByteCount;
		}
		else
		{
			u16Read = pstrTlsBuff->u16BuffSz - pstrTlsBuff->u16ReadOffset;
		}

		if(pu8ReadBuffer != NULL)
			M2M_MEMCPY(pu8ReadBuffer, &pstrTlsBuff->pu8Buff[pstrTlsBuff->u16ReadOffset], u16Read);
		
		pstrTlsBuff->u16ReadOffset += u16Read;
	}
	return u16Read;
}

/**********************************************************************
Function
	TLS_BufferReadCurrEntry

Description
	Reads the current entry from TLS buffer
Return
	u16Read
***********************************************************************/
uint16 TLS_BufferReadCurrEntry(tstrTlsBuffer *pstrTlsBuff, uint16 u16ReadByteCount, uint8 **ppu8Buffer, BOOL_T bUpdateCursor)
{
	uint16	u16Read = 0;
	
	if(pstrTlsBuff != NULL)
	{
		uint16	u16nBytes = pstrTlsBuff->u16BuffSz - pstrTlsBuff->u16ReadOffset;
		*ppu8Buffer = &pstrTlsBuff->pu8Buff[pstrTlsBuff->u16ReadOffset];
		if(u16nBytes > u16ReadByteCount)
		{				
			u16Read = u16ReadByteCount;
		}
		else
		{
			u16Read = u16nBytes;
		}
		if(bUpdateCursor == BTRUE)
			pstrTlsBuff->u16ReadOffset += u16Read;
	}
	return u16Read;
}

/**********************************************************************
Function
	TLS_BufferSetPos

Description
	
Return
	None
***********************************************************************/
void TLS_BufferSetPos(tstrTlsBuffer *pstrTlsBuff, tstrTLSBufferPos *pstrNewPos)
{
	if(pstrTlsBuff != NULL)
	{
		pstrTlsBuff->u16ReadOffset = pstrNewPos->u16BuffOffset;
	}
}

/**********************************************************************
Function
	TLS_BufferGetPos

Description
	
Return
	None
***********************************************************************/
void TLS_BufferGetPos(tstrTlsBuffer *pstrTlsBuff, tstrTLSBufferPos *pstrCurrPos)
{
	if(pstrTlsBuff != NULL)
	{
		pstrCurrPos->u16BuffOffset = pstrTlsBuff->u16ReadOffset;
	}	
}
