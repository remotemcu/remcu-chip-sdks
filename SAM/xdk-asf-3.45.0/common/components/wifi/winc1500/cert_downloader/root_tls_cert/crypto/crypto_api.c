/**
 * \file
 *
 * \brief Certificate Deecoder/parser
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

#include "crypto.h"
#include "tls_buffer_manager.h"
#include <string.h>
#include <stdlib.h>
#include "root_tls_cert/x509/x509_cert.h"
#include "crypto_api.h"

typedef struct __tstrCryptoMemHdr{
	struct __tstrCryptoMemHdr	*pstrNext;
}tstrCryptoMemHdr;

void* CryptoInternalMalloc(void *hdl, uint32 u32AllocSz);

/**********************************************************************
Function
	CryptoInternalMalloc

Description
	Allocates memory for crypto operation.

Return
	None
***********************************************************************/
void* CryptoInternalMalloc(void *hdl, uint32 u32AllocSz)
{
	txtrX509CertInfo	*pstrCert	= (txtrX509CertInfo*)hdl;
	tstrCryptoMemHdr	*pstrNew;
	uint8				*pu8Alloc;

	pu8Alloc = (uint8*)malloc(WORD_ALIGN(u32AllocSz) + sizeof(tstrCryptoMemHdr));
	if(pu8Alloc != NULL)
	{
		pstrNew = (tstrCryptoMemHdr*)pu8Alloc;

		if(pstrCert->pvPrivate == NULL)
		{
			pstrNew->pstrNext	= NULL;
		}
		else
		{
			pstrNew->pstrNext	= (tstrCryptoMemHdr*)pstrCert->pvPrivate;
		}
		pstrCert->pvPrivate	= (void*)pstrNew;

		pu8Alloc += sizeof(tstrCryptoMemHdr);
	}
	return (uint8*)pu8Alloc;
}

/**********************************************************************
Function
	CryptoX509CertDecode

Description
	Crypto certificate decoding

Return
	Status
***********************************************************************/
sint8 CryptoX509CertDecode(uint8 *pu8X509CertBuf, uint16 u16X509CertBuffer, txtrX509CertInfo *pstrCert, uint8 bDumpCert)
{
	sint8			ret			= M2M_ERR_FAIL;
	tstrMemPool		strPool;
	tstrX509Cert	strX509Cer;
	tstrTlsBuffer	strX509Buff;

	strX509Buff.pu8Buff			= pu8X509CertBuf;
	strX509Buff.u16BuffSz		= u16X509CertBuffer;
	strX509Buff.u16ReadOffset	= 0;

	strPool.fpAlloc			= CryptoInternalMalloc;
	strPool.pvPoolHandle	= pstrCert;
	pstrCert->pvPrivate		= NULL;
	if(X509Cert_Decode(&strX509Buff, u16X509CertBuffer, &strPool, &strX509Cer , bDumpCert) == X509_SUCCESS)
	{
		pstrCert->u8SerialNumberLength	= strX509Cer.u8SerialNumberLength;
		memcpy(pstrCert->au8SerialNo, strX509Cer.au8SerialNo, sizeof(strX509Cer.au8SerialNo));
		memcpy(&pstrCert->strExpiryDate, &strX509Cer.strExpiryDate, sizeof(tstrSystemTime));
		memcpy(&pstrCert->strStartDate, &strX509Cer.strStartDate, sizeof(tstrSystemTime));
		memcpy(&pstrCert->strIssuer, &strX509Cer.strIssuer, sizeof(tstrX520Name));
		memcpy(&pstrCert->strSubject, &strX509Cer.strSubject, sizeof(tstrX520Name));
		if(strX509Cer.strPubKey.enuType == PUBKEY_ALG_RSA)
		{
			pstrCert->strPubKey.enuCertKeyType = X509_CERT_PUBKEY_RSA;
			memcpy(&pstrCert->strPubKey.strRsaPub, &strX509Cer.strPubKey.strRSAKey, sizeof(tstrRSAPubKey));
		}
		else if(strX509Cer.strPubKey.enuType == PUBKEY_ALG_ECC)
		{
			pstrCert->strPubKey.enuCertKeyType				= X509_CERT_PUBKEY_ECDSA;
			pstrCert->strPubKey.strEcdsaPub.u16CurveID		= strX509Cer.strPubKey.strEccKey.pstrCurve->enuType;
			pstrCert->strPubKey.strEcdsaPub.u16EcPointSz	= strX509Cer.strPubKey.strEccKey.strQ.u16Size;
			memcpy(&pstrCert->strPubKey.strEcdsaPub.au8EcPoint, &strX509Cer.strPubKey.strEccKey.strQ.X, pstrCert->strPubKey.strEcdsaPub.u16EcPointSz * 2);
		}
		ret = M2M_SUCCESS;
	}
	return ret;
}

/**********************************************************************
Function
	CryptoX509DeleteContext

Description
	Free the allocated memory for certificate decoding

Return
	None
***********************************************************************/
void CryptoX509DeleteContext(txtrX509CertInfo *pstrCert)
{
	tstrCryptoMemHdr	*pstrCur = (tstrCryptoMemHdr*)pstrCert->pvPrivate;
	tstrCryptoMemHdr	*pstrDel;

	while(pstrCur != NULL)
	{
		pstrDel = pstrCur;
		pstrCur = pstrCur->pstrNext;
		free(pstrDel);
	}
}
