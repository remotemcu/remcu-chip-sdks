/**
 * \file
 *
 * \brief Interface for the X509 Certificate parsing module.
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

#ifndef __X509_CERT_H__
#define __X509_CERT_H__

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
INCLUDES
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#include "root_tls_cert/crypto/crypto_types.h"
#include "asn1.h"
#include "root_tls_cert/crypto/crypto.h"
#include "root_tls_cert/crypto/tls_buffer_manager.h"

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
MACROS
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#define X509_SUCCESS								0
#define X509_FAIL									-1

#define X509_SERIAL_NO_MAX_SZ						(64)
/*!<
*/

#define X509_NAME_MAX_SZ							(64)
/*!<
*/


#define X509_STATUS_VALID							0
/*!<
	The X.509 certificate is valid.
*/


#define X509_STATUS_EXPIRED							1
/*!<
	The X.509 certificate is expired.
*/


#define X509_STATUS_REVOKED							2
/*!<
	The X.509 certificate is marked as revoked and should not
	be trusted.
*/


#define X509_STATUS_DECODE_ERR						4
/*!<
	Error decoding the certificate time.
*/


#define X509_CERT_DECODE(x509Buf, x509Sz, Pool, x509Out, dumpFlag, ret)	\
	do{\
		M2M_MEMSET((x509Out), 0, sizeof(tstrX509Cert));\
		OVLY_TLS_CLIENT_START;	\
		ret = X509Cert_Decode((x509Buf), (x509Sz), (Pool), (x509Out), dumpFlag);	\
		OVLY_TLS_CLIENT_END;	\
	}while(0)
/*!<
*/


/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
DATA TYPES
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/


/*!
@struct	\
	tstrX520Name

@brief
*/
typedef struct{
	char	acCmnName[X509_NAME_MAX_SZ];
	uint8	au8NameSHA1[SHA1_DIGEST_SIZE];
}tstrX520Name;


/*!
@typedef	\
	tpfMemPoolAllocFn
	
*/
typedef void* (*tpfMemPoolAllocFn)(void *pvHdl, uint32 u32AllocSz);


/*!
@struct	\
	tstrX509Cert

@brief
*/
typedef struct{
	void				*pvPoolHandle;
	tpfMemPoolAllocFn	fpAlloc;
}tstrMemPool;


/*!
@struct	\
	tstrX509Cert

@brief
*/
typedef struct{
	uint8				u8Version;
	/*!<
		X509 version. 
	*/
	tenuTlsSignAlg		enuSignAlg;
	/*!<
	*/
	tenuHashAlg			enuHashAlg;
	/*!<
	*/
	uint8				u8SerialNumberLength;
	/*!<
		X509 certificate serial number Length in bytes. 
	*/
	uint8				au8SerialNo[X509_SERIAL_NO_MAX_SZ];
	/*!<
		X509 certificate serial number. 
	*/
	tstrX520Name		strIssuer;
	/*!<
	*/
	tstrSystemTime		strStartDate;
	/*!<
	*/
	tstrSystemTime		strExpiryDate;
	/*!<
	*/
	tstrX520Name		strSubject;
	/*!<
	*/
	tstrPublicKey		strPubKey;
	/*!<
	*/
	uint8				*pu8Sig;
	/*!<
	*/
	uint16				u16SigSz;
	/*!<
	*/
	tstrMemPool			*pstrMemPool;
	/*!<
	*/
	uint8				*pu8Hash;
	/*!<
	*/
	uint16				u16HashSz;
	/*!<
	*/
	uint8				u8ValidityStatus;
	/*!<
	*/
}tstrX509Cert;

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
FUNCTION PROTOTYPES
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

sint8	X509Cert_Decode(tstrTlsBuffer * pstrX509Buffer, uint32 u32CertSize, tstrMemPool *pstrPool, tstrX509Cert * pstrCert, uint8 bDumpX509);
sint8	X509_DecodeEcdsaSignature(tstrAsn1Context * pstrX509Asn1Cxt, uint8 * pu8Sig, uint16 * pu16SigSz);
void	X509Cert_Dump(tstrX509Cert *pstrCert);

#endif /* __X509_CERT_H__ */
