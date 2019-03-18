/**
 *
 * \file
 *
 * \brief This module implements TLS Server Certificate Installation.
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

#include "root_tls_cert/crypto/crypto_api.h"
#include "pem.h"
#include "tls_srv_sec.h"
#include <stdlib.h>


/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
GLOBALS
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
static uint8					gpau8HexTable[]		= "0123456789abcdef";
static tstrTlsSrvSecHdr			*gpstrTlsSrvSecHdr	= NULL;

/**********************************************************************
Function
	Hex2String

Description
	Hex data to string conversion

Return
	None
***********************************************************************/
static void Hex2String(uint8 * pu8HexArray, uint32 u32Length, char * pcHexString)
{
	uint8 u8Temp;
	uint32 u32Idx;
	
	for(u32Idx = 0; u32Idx < u32Length; u32Idx ++)
	{
		u8Temp = (pu8HexArray[u32Idx] & 0xF0) >> 4;
		pcHexString[2*u32Idx] = gpau8HexTable[u8Temp]; 
		u8Temp = pu8HexArray[u32Idx] & 0x0F;
		pcHexString[2 * u32Idx+ 1] = gpau8HexTable[u8Temp]; 
	}
	pcHexString[2 * u32Length] = '\0';
}

/**********************************************************************
Function
	TlsSrvSecFopen

Description
	

Return
	
***********************************************************************/
static tstrTlsSrvSecFileHandle* TlsSrvSecFopen(char *pcFileName, tenuTlsSrvSecFileMode enuMode)
{
	tstrTlsSrvSecFileHandle	*pstrHandle = NULL;
	tstrTlsSrvSecFileEntry	*pstrEntry	= NULL;

	if(enuMode == FILE_MODE_WRITE)
	{
		uint32	u32Idx;
		for(u32Idx = 0; u32Idx < gpstrTlsSrvSecHdr->u32nEntries; u32Idx ++)
		{
			pstrEntry = &gpstrTlsSrvSecHdr->astrEntries[u32Idx];
			if(!memcmp(pstrEntry->acFileName, pcFileName, strlen(pcFileName)))
			{
				goto __END;
			}
		}

		if(gpstrTlsSrvSecHdr->u32nEntries < TLS_SRV_SEC_MAX_FILES)
		{
			pstrEntry = &gpstrTlsSrvSecHdr->astrEntries[gpstrTlsSrvSecHdr->u32nEntries ++];
			memcpy((uint8*)pstrEntry->acFileName, (uint8*)pcFileName, TLS_SRV_SEC_FILE_NAME_MAX);
			pstrEntry->u32FileAddr = gpstrTlsSrvSecHdr->u32NextWriteAddr;
		}
	}
	else if(enuMode == FILE_MODE_READ)
	{
		uint32	u32FileIdx;

		for(u32FileIdx = 0; u32FileIdx < gpstrTlsSrvSecHdr->u32nEntries; u32FileIdx ++)
		{
			if(!m2m_strncmp((uint8*)pcFileName, (uint8*)gpstrTlsSrvSecHdr->astrEntries[u32FileIdx].acFileName, 
				(uint16)M2M_MAX(strlen(pcFileName), strlen(gpstrTlsSrvSecHdr->astrEntries[u32FileIdx].acFileName))))
			{
				pstrEntry	= &gpstrTlsSrvSecHdr->astrEntries[u32FileIdx];
				break;
			}
		}
	}

	if(pstrEntry != NULL)
	{
		pstrHandle = (tstrTlsSrvSecFileHandle*)malloc(sizeof(tstrTlsSrvSecFileHandle));
		if(pstrHandle != NULL)
		{
			pstrHandle->u32Offset	= 0;
			pstrHandle->pstrFile	= pstrEntry;
		}
	}

__END:
	return pstrHandle;
}

/**********************************************************************
Function
	TlsSrvSecFwrite

Description
	

Return
	Status
***********************************************************************/
static sint8 TlsSrvSecFwrite(uint8 *pu8WriteBuff, uint16 u16BuffSize, tstrTlsSrvSecFileHandle *pstrHandle)
{
	sint8	ret = M2M_ERR_FAIL;
	if((pu8WriteBuff != NULL) && (pstrHandle != NULL))
	{
		uint32	u32WriteOffset = (pstrHandle->pstrFile->u32FileAddr - M2M_TLS_SERVER_FLASH_OFFSET) + pstrHandle->u32Offset;
		uint8	*pu8TlsSrvSec = (uint8*)gpstrTlsSrvSecHdr;

		memcpy(&pu8TlsSrvSec[u32WriteOffset], pu8WriteBuff, u16BuffSize);
		pstrHandle->u32Offset += u16BuffSize;
		ret = M2M_SUCCESS;
	}
	return ret;
}

/**********************************************************************
Function
	TlsSrvSecFclose

Description
	

Return
	None
***********************************************************************/
static void TlsSrvSecFclose(tstrTlsSrvSecFileHandle *pstrHandle)
{
	if(pstrHandle != NULL)
	{
		pstrHandle->pstrFile->u32FileSize = (uint16)pstrHandle->u32Offset;
		gpstrTlsSrvSecHdr->u32NextWriteAddr += WORD_ALIGN(pstrHandle->u32Offset);	
		free(pstrHandle);
	}
}

/**********************************************************************
Function
	ReadServerX509Chain

Description
	
Return
	None
***********************************************************************/
static sint8 ReadServerX509Chain(tstrBuff *pstrX509Chain, uint8 u8nCerts, tstrX509Entry **ppstrChainHead)
{
	sint8				ret = M2M_SUCCESS;
	uint8				u8Idx;
	txtrX509CertInfo	strX509;
	tstrX509Entry		*pstrHead = NULL, *pstrTail = NULL;
	tstrX509Entry		*pstrTarget, *pstrCurr, *pstrPrev;
	uint8				bIsIssuerFound;

	for(u8Idx = 0; u8Idx < u8nCerts; u8Idx ++)
	{
		if(CryptoX509CertDecode(pstrX509Chain[u8Idx].pu8Data, pstrX509Chain[u8Idx].u16BufferSize, &strX509, 0) == M2M_SUCCESS)
		{
			tstrX509Entry	*pstrNewX509 = (tstrX509Entry*)malloc(sizeof(tstrX509Entry));
			printf("\r\n>>>Found Certificate:\n");
			printf(">>>\t%s\n", strX509.strSubject.acCmnName);
			if(pstrNewX509 != NULL)
			{
				memcpy((uint8*)&pstrNewX509->strX509, (uint8*)&strX509, sizeof(txtrX509CertInfo));
				memcpy((uint8*)&pstrNewX509->strX509ASN1Buff, (uint8*)&pstrX509Chain[u8Idx], sizeof(tstrBuff));
				pstrNewX509->pstrNext	= NULL;

				if(pstrHead == NULL)
				{
					pstrHead = pstrNewX509;
					pstrTail = pstrNewX509;
				}
				else
				{
					pstrTail->pstrNext	= pstrNewX509;
					pstrTail			= pstrNewX509;
				}
			}
		}
		else
		{
		}
	}

	/* Sort the list.
	*/
	for(pstrTarget = pstrHead; pstrTarget != NULL; pstrTarget = pstrTarget->pstrNext)
	{
		if(pstrTarget->pstrNext != NULL)
		{
			pstrCurr = pstrTarget->pstrNext;
			if(m2m_memcmp(pstrTarget->strX509.strIssuer.au8NameSHA1, pstrCurr->strX509.strSubject.au8NameSHA1, CRYPTO_SHA1_DIGEST_SIZE))
			{
				pstrPrev		= pstrTarget;
				pstrCurr		= pstrCurr->pstrNext;
				bIsIssuerFound	= 0;

				for(; pstrCurr != NULL; pstrCurr = pstrCurr->pstrNext)
				{
					if(!m2m_memcmp(pstrTarget->strX509.strIssuer.au8NameSHA1, pstrCurr->strX509.strSubject.au8NameSHA1, CRYPTO_SHA1_DIGEST_SIZE))
					{
						if(pstrCurr == pstrTail)
						{
							pstrTail = pstrPrev;
						}
						pstrPrev->pstrNext		= pstrCurr->pstrNext;
						pstrCurr->pstrNext		= pstrTarget->pstrNext;
						pstrTarget->pstrNext	= pstrCurr;

						pstrPrev		= pstrCurr;
						bIsIssuerFound	= 1;
						break;
					}
					pstrPrev = pstrCurr;
				}

				if(!bIsIssuerFound)
				{
					pstrTail			= pstrTarget;
					pstrTail->pstrNext	= NULL;
					break;
				}
			}
		}
	}

	/*
		Remove Unrelated certificates.
	*/
	for(pstrCurr = pstrHead; pstrCurr != NULL; )
	{
		if(pstrCurr->pstrNext != NULL)
		{
			if(m2m_memcmp(pstrCurr->strX509.strIssuer.au8NameSHA1, pstrCurr->pstrNext->strX509.strSubject.au8NameSHA1, CRYPTO_SHA1_DIGEST_SIZE))
			{
				pstrTarget = pstrCurr->pstrNext;
				pstrCurr->pstrNext = pstrCurr->pstrNext->pstrNext;
				CryptoX509DeleteContext(&pstrTarget->strX509);
				free(pstrTarget);
			}
		}
		pstrCurr = pstrCurr->pstrNext;
	}

	*ppstrChainHead = pstrHead;
	return ret;
}

/**********************************************************************
Function
	ValidateKeyMaterial

Description
	
Return
	None
***********************************************************************/
static sint8 ValidateKeyMaterial(tstrRsaPrivateKey	*pstrPrivKey, txtrX509CertInfo *pstrServerCert)
{
	sint8	ret = M2M_SUCCESS;

	/* 
		Validate the private key matches the server certificate.
	*/
	if(pstrPrivKey != NULL)
	{
		if(memcmp(pstrServerCert->strPubKey.strRsaPub.pu8N, pstrPrivKey->pu8N, pstrPrivKey->u16NSize))
		{
			M2M_ERR("Private key does not match the certificate\n");
			ret = M2M_ERR_FAIL;
		}
	}

	if(ret == M2M_SUCCESS)
	{

		/* Add a new chain to the chain tracking file.
		*/

		/* Write the certificate individual files.
		*/

		/* Write the private key file.
		*/
	}
	return ret;
}

/**********************************************************************
Function
	RsaBuildServerX509CertChain

Description
	
Return
	None
***********************************************************************/
static sint8 RsaBuildServerX509CertChain(tstrX509Entry *pstrHead, tstrASN1RSAPrivateKey *pstrRsaPrivKey)
{
	sint8	ret = M2M_SUCCESS;

	if(pstrHead != NULL)
	{
		if(ValidateKeyMaterial(&pstrRsaPrivKey->strRsaPrivKey, &pstrHead->strX509) == M2M_SUCCESS)
		{
			char						acPrivFileName[TLS_SRV_SEC_FILE_NAME_MAX] = "PRIV_";
			tstrX509Entry				*pstrCurr = pstrHead;
			tstrTlsSrvSecFileHandle		*pstrHandle;

			/* Write the private key file.
			*/
			strcpy(&acPrivFileName[5], &pstrHead->acFileName[5]);  
			pstrHandle = TlsSrvSecFopen(acPrivFileName, FILE_MODE_WRITE);
			if(pstrHandle != NULL)
			{
				TlsSrvSecFwrite(pstrRsaPrivKey->pu8AllocPtr, pstrRsaPrivKey->u16KeyBufSz, pstrHandle);
				TlsSrvSecFclose(pstrHandle);
			}

			/* Write the chain holder file.
			*/
			pstrCurr = pstrHead;
			pstrHandle = TlsSrvSecFopen((char*)"RSA.lst", FILE_MODE_WRITE);
			if(pstrHandle != NULL)
			{
				TlsSrvSecFwrite((uint8*)acPrivFileName, TLS_SRV_SEC_FILE_NAME_MAX, pstrHandle);
				while(pstrCurr != NULL)
				{
					TlsSrvSecFwrite((uint8*)pstrCurr->acFileName, TLS_SRV_SEC_FILE_NAME_MAX, pstrHandle);
					pstrCurr = pstrCurr->pstrNext;
				}
				TlsSrvSecFclose(pstrHandle);
			}
		}
		else
		{
			M2M_ERR("Key material mismatch\n");
			ret = M2M_ERR_FAIL;
		}
	}
	else
	{
		ret = M2M_ERR_FAIL;
	}
	return ret;
}

/**********************************************************************
Function
	EcdsaBuildServerX509CertChain

Description
	
Return
	None
***********************************************************************/
static sint8 EcdsaBuildServerX509CertChain(tstrX509Entry *pstrHead)
{
	sint8	ret = M2M_SUCCESS;

	if(pstrHead != NULL)
	{
		if(ValidateKeyMaterial(NULL, &pstrHead->strX509) == M2M_SUCCESS)
		{
			tstrX509Entry				*pstrCurr = pstrHead;
			tstrTlsSrvSecFileHandle		*pstrHandle;

			/* Write the chain holder file.
			*/
			pstrCurr = pstrHead;
			pstrHandle = TlsSrvSecFopen((char*)"ECDSA.lst", FILE_MODE_WRITE);
			if(pstrHandle != NULL)
			{
				while(pstrCurr != NULL)
				{
					TlsSrvSecFwrite((uint8*)pstrCurr->acFileName, TLS_SRV_SEC_FILE_NAME_MAX, pstrHandle);
					pstrCurr = pstrCurr->pstrNext;
				}
				TlsSrvSecFclose(pstrHandle);
			}
		}
		else
		{
			M2M_ERR("Key material mismatch\n");
			ret = M2M_ERR_FAIL;
		}
	}
	else
	{
		ret = M2M_ERR_FAIL;
	}
	return ret;
}

/**********************************************************************
Function
	BuildServerX509CertChain

Description
	
Return
	None
***********************************************************************/
static sint8 BuildServerX509CertChain(tenuCertPubKeyType enuChainType, tstrX509Entry *pstrHead, tstrASN1RSAPrivateKey *pstrRsaPrivKey)
{
	sint8	ret = M2M_SUCCESS;

	tstrX509Entry				*pstrCurr		= pstrHead;
	tstrTlsSrvSecFileHandle		*pstrHandle;
	char						acCertFileName[TLS_SRV_SEC_FILE_NAME_MAX] = "CERT_";

	/* Write the server certificate chain files.
	*/
	while(pstrCurr != NULL)
	{
		Hex2String(pstrCurr->strX509.au8SerialNo, pstrCurr->strX509.u8SerialNumberLength, &acCertFileName[5]);
		pstrHandle = TlsSrvSecFopen(acCertFileName, FILE_MODE_WRITE);
		if(pstrHandle != NULL)
		{
			TlsSrvSecFwrite(pstrCurr->strX509ASN1Buff.pu8Data, pstrCurr->strX509ASN1Buff.u16BufferSize, pstrHandle);
			TlsSrvSecFclose(pstrHandle);
		}
		memcpy((uint8*)pstrCurr->acFileName, (uint8*)acCertFileName, TLS_SRV_SEC_FILE_NAME_MAX);
		pstrCurr = pstrCurr->pstrNext;
	}

	if(enuChainType == X509_CERT_PUBKEY_RSA)
	{
		ret = RsaBuildServerX509CertChain(pstrHead, pstrRsaPrivKey);
	}
	else if(enuChainType == X509_CERT_PUBKEY_ECDSA)
	{
		ret = EcdsaBuildServerX509CertChain(pstrHead);
	}
	else
	{
		ret = M2M_ERR_FAIL;
	}
	return ret;
}

/**********************************************************************
Function
	WriteTlsServerKeyMaterial

Description
	
Return
	None
***********************************************************************/
static sint8 WriteTlsServerKeyMaterial(uint8 *pu8PrivKey, uint32 u32PrivKeySz, tstrFileInfo *pstrCertChain, uint8 u8nCerts, uint32 *pu32SecSz)
{
	sint8					ret				= M2M_ERR_FAIL;
	uint8					u8Idx;
	uint32					u32Tmp;
	tstrASN1RSAPrivateKey	strRSAPrivKey;
	tstrX509Entry			*pstrServerCert	= NULL;
	tstrBuff				astrCertBuffs[20];

	for(u8Idx = 0; u8Idx < u8nCerts; u8Idx ++)
	{
		if(DecodeX509Certificate(pstrCertChain[u8Idx].pu8FileData, pstrCertChain[u8Idx].u32FileSz, &astrCertBuffs[u8Idx].pu8Data, &u32Tmp) == M2M_SUCCESS)
		{
			astrCertBuffs[u8Idx].u16BufferSize = (uint16)u32Tmp;
		}
		else
		{
			ret = M2M_ERR_FAIL;
			goto __ERR;
		}
	}

	ret = ReadServerX509Chain(astrCertBuffs, u8nCerts, &pstrServerCert);
	if(ret == M2M_SUCCESS)
	{
		tenuCertPubKeyType	enuCertType = pstrServerCert->strX509.strPubKey.enuCertKeyType;

		if(enuCertType == X509_CERT_PUBKEY_RSA)
		{
			memset(&strRSAPrivKey, 0, sizeof(tstrASN1RSAPrivateKey));
			ret = CryptoDecodeRsaPrivKey(pu8PrivKey, u32PrivKeySz, &strRSAPrivKey);
			if(ret != M2M_SUCCESS)
				goto __ERR;
		}
		else if(enuCertType == X509_CERT_PUBKEY_ECDSA)
		{
			ret = M2M_SUCCESS;
		}

		ret = BuildServerX509CertChain(enuCertType, pstrServerCert, &strRSAPrivKey);
		if(ret == M2M_SUCCESS)
		{
			if(pu32SecSz != NULL)
			{
				uint32	u32SecSz = sizeof(tstrTlsSrvSecHdr);
				for(u8Idx = 0; u8Idx < (uint8)gpstrTlsSrvSecHdr->u32nEntries; u8Idx ++)
				{
					u32SecSz += WORD_ALIGN(gpstrTlsSrvSecHdr->astrEntries[u8Idx].u32FileSize);
				}
				*pu32SecSz = u32SecSz;
			}
		}
	}
__ERR:
	{
		tstrX509Entry	*pstrCur = pstrServerCert;
		tstrX509Entry	*pstrDel;
		
		while(pstrCur != NULL)
		{
			pstrDel = pstrCur;
			pstrCur = pstrCur->pstrNext;
			CryptoX509DeleteContext(&pstrDel->strX509);
			free(pstrDel);
		}
	}
	return ret;
}

/**********************************************************************
Function
	TlsSrvSecWriteCertChain

Description
	
Return
	None
***********************************************************************/
sint8 TlsSrvSecWriteCertChain(uint8 *pu8PrivKey, uint32 u32PrivKeySz, tstrFileInfo *pstrCertChain, uint8 u8ChainDepth, uint8 *pu8TlsSrvSecBuff, uint32 *pu32SecSz, tenuWriteMode enuMode)
{
	sint8	ret					= M2M_ERR_FAIL;
	uint8	au8Pattern[]		= TLS_SRV_SEC_START_PATTERN;

	if((pu8TlsSrvSecBuff != NULL) && (pstrCertChain != NULL))
	{
		/*
			Initialize the write operation 
		*/
		if(enuMode == TLS_SRV_SEC_MODE_WRITE)
		{
			memset(pu8TlsSrvSecBuff, 0xFF, M2M_TLS_SERVER_FLASH_SIZE);
			gpstrTlsSrvSecHdr = (tstrTlsSrvSecHdr*)pu8TlsSrvSecBuff;
			memcpy(gpstrTlsSrvSecHdr->au8SecStartPattern, au8Pattern, TLS_SRV_SEC_START_PATTERN_LEN);
			gpstrTlsSrvSecHdr->u32nEntries		= 0;
			gpstrTlsSrvSecHdr->u32NextWriteAddr	= sizeof(tstrTlsSrvSecHdr) + M2M_TLS_SERVER_FLASH_OFFSET;
		}
		else if(enuMode == TLS_SRV_SEC_MODE_APPEND)
		{
			if(!memcmp(pu8TlsSrvSecBuff, au8Pattern, TLS_SRV_SEC_START_PATTERN_LEN))
			{
				gpstrTlsSrvSecHdr = (tstrTlsSrvSecHdr*)pu8TlsSrvSecBuff;
			}
			else
			{
				goto __ERR;
			}
		}
		else
		{
				goto __ERR;
		}

		/*
			Perform Writing
		*/
		ret = WriteTlsServerKeyMaterial(pu8PrivKey, u32PrivKeySz, pstrCertChain, u8ChainDepth, pu32SecSz);
	}
__ERR:
	return ret;
}
