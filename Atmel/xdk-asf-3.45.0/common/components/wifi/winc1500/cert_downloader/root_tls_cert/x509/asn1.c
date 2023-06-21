/**
 * \file
 *
 * \brief Implementation for ASN.1 Decoder for Distinguished Encoding Rules DER.
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

#include "asn1.h"

/*********************************************************************
Function
	ASN1_GetNextElement

Description
	

Return
	None

Author
	Ahmed Ezzat

Version
	1.0

Date
	7 March 2013
*********************************************************************/
TLS_API uint16 ASN1_GetNextElement
(
tstrAsn1Context 	*pstrAsn1Ctxt,
tstrAsn1Element 	*pstrElement
)
{
	uint16	u16ElemLength = 0;
	
	if((pstrElement != NULL) && (pstrAsn1Ctxt != NULL))
	{
		uint8	u8NLenBytes;

		do
		{
			u8NLenBytes = 0;
			
			/* Get the ASN.1 Element Tag. 
			*/
			TLS_BufferRead(pstrAsn1Ctxt->pstrTlsBuffer, 1, &pstrElement->u8Tag);

			/* Get the ASN.1 element length. 
			*/
			TLS_BufferRead(pstrAsn1Ctxt->pstrTlsBuffer, 1, (uint8*)&pstrElement->u32Length);
			pstrElement->u32Length &= 0xFF;
			if(pstrElement->u32Length & BIT7)
			{
				uint8	u8Idx;
				uint8	au8Tmp[4];

				/* Multiple Length octets. 
				*/
				u8NLenBytes = pstrElement->u32Length & 0x03;
				pstrElement->u32Length = 0;
				TLS_BufferRead(pstrAsn1Ctxt->pstrTlsBuffer, u8NLenBytes, au8Tmp);
				
				for(u8Idx = 0 ; u8Idx < u8NLenBytes ; u8Idx ++)
					pstrElement->u32Length  += 
						(uint32)(au8Tmp[u8Idx] << ((u8NLenBytes - u8Idx - 1) * 8));
			}
			u16ElemLength += u8NLenBytes + 2 + pstrElement->u32Length;	
		}while(pstrElement->u8Tag == ASN1_NULL);
	}
	return u16ElemLength;
}
/*********************************************************************
Function
	ASN1_GetNextElement

Description
	

Return
	None

Author
	Ahmed Ezzat

Version
	1.0

Date
	25 Feb 2015
*********************************************************************/
TLS_API uint16 ASN1_Read
(
tstrAsn1Context	*pstrAsn1Cxt,
uint32			u32ReadLength,
uint8			*pu8ReadBuffer
)
{
	uint16	u16Read = 0;

	if((pstrAsn1Cxt != NULL) && (u32ReadLength > 0))
	{
		u16Read = TLS_BufferRead(pstrAsn1Cxt->pstrTlsBuffer, u32ReadLength, pu8ReadBuffer);
	}
	return u16Read;
}
