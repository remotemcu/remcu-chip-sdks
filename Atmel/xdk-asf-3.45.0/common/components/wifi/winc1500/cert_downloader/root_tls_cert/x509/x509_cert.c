/**
 * \file
 *
 * \brief X.509 certificate module.
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

#include "x509_cert.h"
#include "root_tls_cert/crypto/crypto.h"

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 MACROS
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

/*======*======*======*======*======*
			X509 SUPPORTED VERSIONS
*======*======*======*======*======*/

#define X509_VER_1									0
#define X509_VER_2									1
#define X509_VER_3									2


/*======*======*======*======*======*
			X509 ENCODED FIELD IDs
*======*======*======*======*======*/

#define X509_VERSION								0xA0	
/*!< 
	Identifier of the version field  in the X.509 certificate 
	encoding. It is given in the ASN.1 syntax as    
	[0] EXPLICIT 
	Context-Specific class (10) | constructed (1) | 00000
*/


#define X509_SERIAL_NO								ASN1_INTEGER
/*!< 
	Identifier for the certificate serial num ber element.
*/

#define X509_SIGNATURE								ASN1_SEQUENCE
/*!< 
	Identifier for the Signature algorithm ID element. 
*/


#define X509_ISSUER									ASN1_SEQUENCE
/*!< 
	Identifier for the certificate ISSUER element. 
*/


#define X509_VALIDITY								ASN1_SEQUENCE
/*!< 
	Identifier for the certificate validity interval element.
*/


#define X509_SUBJECT								ASN1_SEQUENCE
/*!< 
	Identifier for the certificate SUBJECT information element. 
*/


#define X509_SUBJECT_KEY_INFO						ASN1_SEQUENCE
/*!< 
	Identifier for the publick key information element. 
*/

#define X509_ISSUER_UNIQUE_ID						0x81 
/*!< 
	Encoded value for the issuerUniqueID tag. It is defined as
	[1] IMPLICIT BIT STRING
	Context-Specific class (10) | primitive (0) | 00001
*/


#define X509_SUBJECT_UNIQUE_ID						0x82 
/*!< 
	Encoded value for the subjectUniqueID tag. It is defined as
	[2] IMPLICIT BIT STRING
	Context-Specific class (10) | primitive (0) | 00010
*/


#define X509_EXTENSIONS_ID							0xA3 
/*!< 
	Encoded value for the issuerUniqueID tag. It is defined as
	[3] EXPLICIT 
	Context-Specific class (10) | constructed (1) | 00011
*/


#define X509_UTC_TIME_LENGTH						0x0D
/*!<
	The UTC time for the X.509 encoding takes the format
	YYMMDDHHMMSSZ. Each digit is BCD encoded as ASCII digit.
*/


#define X509_GENERALIZED_TIME_LENGTH				0x0F
/*!<
	The UTC time for the X.509 encoding takes the format
	YYYYMMDDHHMMSSZ. Each digit is BCD encoded as ASCII digit.	
*/


#define GET_VAL(BUF, OFFSET)						(((BUF)[OFFSET] * 10) + ((BUF)[OFFSET + 1]))


/*======*======*======*======*======*
			NAME ATTRIBUTE IDs 
*======*======*======*======*======*/

#define ID_AT										85 , 0x04 , 
#define ID_AT_COMMONNAME							{ID_AT 3 }
#define ID_AT_SERIALNUMBER							{ID_AT 5 }
#define ID_AT_COUNTRYNAME							{ID_AT 6 }
#define ID_AT_ORGANIZATIONNAME						{ID_AT 10}
#define ID_AT_ORGANIZATIONALUNITNAME				{ID_AT 11}


#define X520_COMMON_NAME							1
#define X520_ORG_UNIT								2
#define X520_ORG									3



/*======*======*======*======*======*
			CERTIFICATE EXTENSION IDs
*======*======*======*======*======*/

#define ID_CE										85 , 29 ,
#define ID_CE_AUTHORITY_KEY_ID						{ID_CE 35}
#define ID_CE_SUBJECT_KEY_ID						{ID_CE 14}



/*======*======*======*======*======*
				RSA ALGORITHM IDs
*======*======*======*======*======*/

#define PKCS_1										0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0d, 0x01, 0x01	
/* 1.2.840.113549.1.1 */

#define RSA_ENCRYPTION								{PKCS_1, 1}						/* 1.2.840.113549.1.1		*/
#define MD5_WITH_RSA_ENCRYPTION 					{PKCS_1, 4}						/* 1.2.840.113549.1.1.4		*/
#define SHA1_WITH_RSA_ENCRYPTION 					{PKCS_1, 5}						/* 1.2.840.113549.1.1.5		*/
#define SHA224_WITH_RSA_ENCRYPTION					{PKCS_1, 14}					/* 1.2.840.113549.1.1.14	*/
#define SHA256_WITH_RSA_ENCRYPTION					{PKCS_1, 11}					/* 1.2.840.113549.1.1.11	*/
#define SHA384_WITH_RSA_ENCRYPTION					{PKCS_1, 12}					/* 1.2.840.113549.1.1.12	*/
#define SHA512_WITH_RSA_ENCRYPTION					{PKCS_1, 13}					/* 1.2.840.113549.1.1.13	*/


/*======*======*======*======*======*
			ECC ALGORITHM IDs
*======*======*======*======*======*/

#define ANSI_X9_62 									0x2A, 0x86, 0x48, 0xCE, 0x3D
/* 1.2.840.10045 */

#define ID_EC_SIG_TYPE								ANSI_X9_62, 0x04 
#define ECDSA_WITH_SHA1								{ID_EC_SIG_TYPE, 1}
#define ECDSA_WITH_SHA224							{ID_EC_SIG_TYPE, 3, 1}
#define ECDSA_WITH_SHA256							{ID_EC_SIG_TYPE, 3, 2}
#define ECDSA_WITH_SHA384							{ID_EC_SIG_TYPE, 3, 3}
#define ECDSA_WITH_SHA512							{ID_EC_SIG_TYPE, 3, 4}

#define ID_PUBLIC_KEY_TYPE							ANSI_X9_62, 02
#define ID_EC_PUBLIC_KEY							{ID_PUBLIC_KEY_TYPE, 1}

#define ELLIPTIC_CURVE								ANSI_X9_62, 3 
#define PRIME_CURVE									ELLIPTIC_CURVE, 1
#define EC_SECP256R1_OID							{PRIME_CURVE, 7}
#define EC_SECP384R1_OID							{0x2B, 0x81, 0x04, 0x00, 0x22}	/* 1.3.132.0.34 */
#define EC_SECP521R1_OID							{0x2B, 0x81, 0x04, 0x00, 0x23}	/* 1.3.132.0.35 */



#define X509_NUM_SUPPORTED_SEC_ALGORITHMS 			(sizeof(gastrSecAlgorithms)/sizeof(tstrX509AlgID))

#define ECC_NUM_SUPP_CURVES							((sizeof(gastrECCSuppList)) / (sizeof(tstrEllipticCurve)))


/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 DATA TYPES
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

/*======*======*======*======*======*======*
			X509 CERTIFICATE PARSING STATES
*======*======*======*======*======*======*/

/*!
@struct	\
	tenuCertParsingState
	
@brief	X.509 Certificate Parsing State Machine
*/
typedef enum{
	CERT_VERSION_PENDING,
	CERT_SERIAL_PENDING,
	CERT_SIGNATURE_PENDING,
	CERT_ISSUER_PENDING,
	CERT_VALIDITY_PENDING,
	CERT_SUBJECT_PENDING,
	CERT_SUBECTKEYINFO_PENDING,
	CERT_EXTENSIONS_PENDING
}tenuCertParsingState;


/*!
@struct	\
	tstrX520DistinguishedName
	
@brief
*/
typedef struct{
	uint8	u8Type;
	uint8	*pu8Name;
	uint8	u8Length;
}tstrX520DistinguishedName;


/*!
@struct	\
	tstrX509AlgID
	
@brief
*/
typedef struct{
	uint8	au8EncodedAlgID[16];
	uint8	u8AlgParam1;
	uint8	u8AlgParam2;
}tstrX509AlgID;


/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 GLOBALS
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

static tstrX509AlgID	gastrSecAlgorithms[] = 
{
	{RSA_ENCRYPTION					, PUBKEY_ALG_RSA	, 0						},
	{MD5_WITH_RSA_ENCRYPTION		, TLS_SIG_ALG_RSA	, HASH_ALG_MD5		},
	{SHA1_WITH_RSA_ENCRYPTION		, TLS_SIG_ALG_RSA	, HASH_ALG_SHA1		},
	{SHA224_WITH_RSA_ENCRYPTION		, TLS_SIG_ALG_RSA	, HASH_ALG_SHA224	},
	{SHA256_WITH_RSA_ENCRYPTION		, TLS_SIG_ALG_RSA	, HASH_ALG_SHA256	},
	{SHA384_WITH_RSA_ENCRYPTION		, TLS_SIG_ALG_RSA	, HASH_ALG_SHA384	},
	{SHA512_WITH_RSA_ENCRYPTION		, TLS_SIG_ALG_RSA	, HASH_ALG_SHA512	},
	{ID_EC_PUBLIC_KEY				, PUBKEY_ALG_ECC	, 0					},
	{EC_SECP256R1_OID				, EC_SECP256R1		, 0					},
	{EC_SECP384R1_OID				, EC_SECP384R1		, 0					},
	{EC_SECP521R1_OID				, EC_SECP521R1		, 0					},
	{ECDSA_WITH_SHA1				, TLS_SIG_ALG_ECDSA	, HASH_ALG_SHA1		},
	{ECDSA_WITH_SHA224				, TLS_SIG_ALG_ECDSA	, HASH_ALG_SHA224	},
	{ECDSA_WITH_SHA256 				, TLS_SIG_ALG_ECDSA	, HASH_ALG_SHA256	},
	{ECDSA_WITH_SHA384 				, TLS_SIG_ALG_ECDSA	, HASH_ALG_SHA384	},
	{ECDSA_WITH_SHA512 				, TLS_SIG_ALG_ECDSA	, HASH_ALG_SHA512	},
};
/*!<
*/
static tstrEllipticCurve	gastrECCSuppList[] = {
	{
		EC_SECP256R1,
		{
			{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0xFFFFFFFF},
			{0xFFFFFFFC, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0xFFFFFFFF},
			{0x27D2604B, 0x3BCE3C3E, 0xCC53B0F6, 0x651D06B0, 0x769886BC, 0xB3EBBD55, 0xAA3A93E7, 0x5AC635D8},
			{
				{
					0x6B, 0x17, 0xD1, 0xF2, 0xE1, 0x2C, 0x42, 0x47, 0xF8, 0xBC, 0xE6, 0xE5, 0x63, 0xA4, 0x40, 0xF2,
					0x77, 0x03, 0x7D, 0x81, 0x2D, 0xEB, 0x33, 0xA0, 0xF4, 0xA1, 0x39, 0x45, 0xD8, 0x98, 0xC2, 0x96
				},
				{
					0x4F, 0xE3, 0x42, 0xE2, 0xFE, 0x1A, 0x7F, 0x9B, 0x8E, 0xE7, 0xEB, 0x4A, 0x7C, 0x0F, 0x9E, 0x16,
					0x2B, 0xCE, 0x33, 0x57, 0x6B, 0x31, 0x5E, 0xCE, 0xCB, 0xB6, 0x40, 0x68, 0x37, 0xBF, 0x51, 0xF5
				},
				32
			}
		}
	}
};

sint8 Cert_DecodeTime(uint8 *pu8Time, tstrSystemTime *pstrTime);
sint8 Cert_CompareTime(tstrSystemTime *pstrT1, tstrSystemTime *pstrT2);
tstrEllipticCurve* ECC_GetCurveInfo(uint16 u16CurveID);
TLS_CLIENT_API sint8 Cert_DecodeX520Name(tstrAsn1Context *pstrX509Asn1Cxt, uint32 u32Size,
tstrX520Name 	*pstrName, tstrMemPool	*pstrMemPool);
TLS_CLIENT_API sint8 Cert_DecodeValidity(tstrAsn1Context *pstrX509Asn1Cxt, uint32 u32Size,
tstrX509Cert *pstrCer);
TLS_CLIENT_API sint8 Cert_DecodeTBSCertificate(tstrAsn1Context	*pstrX509Asn1Cxt,
uint16 			u16CertSize,tstrX509Cert 	*pstrCert);
TLS_CLIENT_API sint8 Cert_DecodeSubjectPubKey(tstrAsn1Context *pstrX509Asn1Cxt,
uint32 	u32Size, tstrMemPool *pstrMemPool,tstrPublicKey	*pstrPubKey);
TLS_CLIENT_API sint8 Cert_DecodeSignature(tstrAsn1Context	*pstrX509Asn1Cxt,
uint16 			u16SigSize,tstrX509Cert 	*pstrCert);
TLS_CLIENT_API sint8 Cert_DecodeRSAPubKey(tstrAsn1Context	*pstrX509Asn1Cxt,
tstrAsn1Element		*pstrKeyParam,tstrMemPool	*pstrMemPool,tstrRSAPublicKey	*pstrRsaPublicKey);
TLS_CLIENT_API sint8 Cert_DecodeECCPubKey(tstrAsn1Context	*pstrX509Asn1Cxt,
tstrAsn1Element		*pstrKeyParam,tstrMemPool	*pstrMemPool,tstrECPublicKey	*pstrEcdsaKey);
TLS_CLIENT_API sint8 Cert_DecodeDistinguishedName(tstrAsn1Context	*pstrX509Asn1Cxt,uint32	u32Size,
tstrX520DistinguishedName	*pstrDN);
TLS_CLIENT_API tstrX509AlgID* Cert_DecodeAlgID(tstrAsn1Context	*pstrX509Asn1Cxt,
uint32 			u32Size,tstrAsn1Element	*pstrParam);
sint8 Cert_ComputeTBSCertHash(tstrTlsBuffer *pstrCrtBuff, tstrTLSBufferPos *pstrTBSCrt, uint16 u16TBSSize, tstrX509Cert *pstrCert);

/*********************************************************************
Function
	ECC_GetCurve

Description
 

Return
	

Author
	Ahmed Ezzat

Version
	1.0

Date
	13 April 2016
*********************************************************************/
tstrEllipticCurve* ECC_GetCurveInfo(uint16 u16CurveID)
{
	uint8				u8Idx;
	tstrEllipticCurve	*pstrCurve = NULL;

	for(u8Idx = 0; u8Idx < ECC_NUM_SUPP_CURVES; u8Idx ++)
	{
		if(gastrECCSuppList[u8Idx].enuType == (tenuEcNamedCurve)u16CurveID)
		{
			pstrCurve = &gastrECCSuppList[u8Idx];
			break;
		}
	}
	return pstrCurve;
}
/*********************************************************************
Function
	Cert_DecodeAlgID

Description
	The function perform decoding to the data type "AlgorithmIdentifier" 

Return
	

Author
	Ahmed Ezzat

Version
	1.0

Date
	20 March 2013
*********************************************************************/
TLS_CLIENT_API tstrX509AlgID* Cert_DecodeAlgID
(
tstrAsn1Context	*pstrX509Asn1Cxt, 
uint32 			u32Size,
tstrAsn1Element	*pstrParam
)
{
/*
	AlgorithmIdentifier ::= SEQUENCE {
		algorithm 	OBJECT IDENTIFIER,
		parameters 	ANY DEFINED BY algorithm OPTIONAL 
	}
*/

	tstrX509AlgID	*pstrAlg = NULL;

	if(pstrX509Asn1Cxt != NULL)
	{
		tstrAsn1Element 	strElem;
		uint32				u32Offset = 0;
		
		u32Offset += ASN1_GetNextElement(pstrX509Asn1Cxt, &strElem);
		if(strElem.u8Tag == ASN1_OBJECT_IDENTIFIER)
		{
			if(strElem.u32Length <= 15)
			{
				uint8	u8Idx;
				uint8	au8AlgID[16];
				ASN1_Read(pstrX509Asn1Cxt, strElem.u32Length, au8AlgID);
				for(u8Idx = 0 ; u8Idx < X509_NUM_SUPPORTED_SEC_ALGORITHMS ; u8Idx ++)
				{
					if(!M2M_MEMCMP(au8AlgID, gastrSecAlgorithms[u8Idx].au8EncodedAlgID, strElem.u32Length))
					{
						pstrAlg = &gastrSecAlgorithms[u8Idx];
						break;
					}
				}
			}
			
			if((u32Offset + 2) < u32Size)
			{
				u32Offset += ASN1_GetNextElement(pstrX509Asn1Cxt, &strElem);
				if(pstrParam == NULL)
				{
					ASN1_Read(pstrX509Asn1Cxt, strElem.u32Length, NULL);
				}
				else
				{
					M2M_MEMCPY(pstrParam, &strElem, sizeof(tstrAsn1Element));
				}
			}
		}
	}
	return pstrAlg;
}
/*********************************************************************
Function
	Cert_DecodeX520Name

Description: 

Return
	None

Author
	Ahmed Ezzat

Version
	 	1.0

Date
	7 March 2013
*********************************************************************/
TLS_CLIENT_API sint8 Cert_DecodeDistinguishedName
(
tstrAsn1Context				*pstrX509Asn1Cxt,
uint32						u32Size,
tstrX520DistinguishedName	*pstrDN
)
{
	sint8		s8Ret = X509_FAIL;

	if((pstrX509Asn1Cxt != NULL) && (pstrDN != NULL))
	{
		tstrAsn1Element	strElem;

		ASN1_GetNextElement(pstrX509Asn1Cxt, &strElem);
		if(strElem.u8Tag == ASN1_OBJECT_IDENTIFIER)
		{
			uint8	au8CmnNameID[4] = ID_AT_COMMONNAME;
			uint8	au8TempID[16];
			
			pstrDN->u8Type = 0;
			ASN1_Read(pstrX509Asn1Cxt, strElem.u32Length, au8TempID);
			if(!M2M_MEMCMP(au8CmnNameID, au8TempID, strElem.u32Length))
				pstrDN->u8Type = X520_COMMON_NAME;
			
			if(ASN1_GetNextElement(pstrX509Asn1Cxt, &strElem) != ASN1_FAIL)
			{
				pstrDN->u8Length = (uint8)strElem.u32Length;
				ASN1_Read(pstrX509Asn1Cxt, strElem.u32Length, pstrDN->pu8Name);
				s8Ret = X509_SUCCESS;
			}				
		}
	}
	return s8Ret;
}
/*********************************************************************
Function
	Cert_DecodeX520Name

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
TLS_CLIENT_API sint8 Cert_DecodeX520Name
(
tstrAsn1Context	*pstrX509Asn1Cxt, 
uint32		 	u32Size, 
tstrX520Name 	*pstrName,
tstrMemPool	*pstrMemPool
)
{
/*
	Name ::= CHOICE { -- only one possibility for now --
		rdnSequence RDNSequence 
	}

	RDNSequence ::= SEQUENCE OF RelativeDistinguishedName
	
	RelativeDistinguishedName ::=
		SET SIZE (1..MAX) OF AttributeTypeAndValue
	
	AttributeTypeAndValue ::= SEQUENCE {
		type 	AttributeType,
		value 	AttributeValue 
	}
	
	AttributeType ::= OBJECT IDENTIFIER
	AttributeValue ::= ANY -- DEFINED BY AttributeType
	
	DirectoryString ::= CHOICE {
		teletexString 		TeletexString (SIZE (1..MAX)),
		printableString 	PrintableString (SIZE (1..MAX)),
		universalString 	UniversalString (SIZE (1..MAX)),
		utf8String 		UTF8String (SIZE (1..MAX)),
		bmpString 		BMPString (SIZE (1..MAX)) 
	}
*/
	sint8		s8Ret = X509_SUCCESS;
	
	if((pstrX509Asn1Cxt != NULL) && (pstrName != NULL))
	{
		tstrAsn1Element				strSetElem,strSeqElem;
		tstrX520DistinguishedName	strDN;
		tstrSha1Context				strSha1Cxt;
		uint16						u16Offset = 0;
		
		SHA1_INIT(&strSha1Cxt);

		pstrName->acCmnName[0] = 0;
		
		/* RelativeDistinguishedName 
		*/
		while(u16Offset < u32Size)
		{
			u16Offset += ASN1_GetNextElement(pstrX509Asn1Cxt, &strSetElem);
			if(strSetElem.u8Tag == ASN1_SET)
			{
				ASN1_GetNextElement(pstrX509Asn1Cxt, &strSeqElem);
				if(strSeqElem.u8Tag != ASN1_SEQUENCE)
				{
					s8Ret = X509_FAIL;
					break;
				}				
				strDN.pu8Name = (uint8*)pstrMemPool->fpAlloc(pstrMemPool->pvPoolHandle, strSeqElem.u32Length);
				if(strDN.pu8Name != NULL)
				{
					if(Cert_DecodeDistinguishedName(pstrX509Asn1Cxt, strSeqElem.u32Length, &strDN) != X509_SUCCESS)
					{
						s8Ret = X509_FAIL;
						break;
					}

					if(strDN.u8Length < X509_NAME_MAX_SZ)
					{
						if(strDN.u8Type == X520_COMMON_NAME)
						{
							M2M_MEMCPY(pstrName->acCmnName, strDN.pu8Name, strDN.u8Length);
							pstrName->acCmnName[strDN.u8Length] = '\0';
						}
						else if(pstrName->acCmnName[0] == 0)
						{
							if(strDN.u8Type == X520_ORG)
							{
								M2M_MEMCPY(pstrName->acCmnName, strDN.pu8Name, strDN.u8Length);
								pstrName->acCmnName[strDN.u8Length] = '\0';
							}
						}
					}
					SHA1_UPDATE(&strSha1Cxt, strDN.pu8Name, strDN.u8Length);
				}
			}
			else
				break;
		}
		SHA1_FINISH(&strSha1Cxt, pstrName->au8NameSHA1);
	}
	return s8Ret;
}
/*********************************************************************
Function
	Cert_DecodeRSAPubKey

Description


Return
	

Author
	Ahmed Ezzat

Version
	1.0

Date
	22 March 2013
*********************************************************************/
TLS_CLIENT_API sint8 Cert_DecodeRSAPubKey
(
tstrAsn1Context		*pstrX509Asn1Cxt,
tstrAsn1Element		*pstrKeyParam,
tstrMemPool		*pstrMemPool,
tstrRSAPublicKey	*pstrRsaPublicKey
)
{
/*
	RSAPublicKey ::= SEQUENCE {
		modulus 		INTEGER, -- n
		publicExponent 	INTEGER  -- e
	}
*/
	sint8	s8Ret = X509_FAIL;
	if((pstrX509Asn1Cxt != NULL) && (pstrRsaPublicKey != NULL) && (pstrKeyParam != NULL))
	{
		tstrAsn1Element	strElem;
		if(pstrKeyParam->u8Tag != ASN1_NULL)
		{
			ASN1_Read(pstrX509Asn1Cxt, pstrKeyParam->u32Length, NULL);
		}
		
		ASN1_GetNextElement(pstrX509Asn1Cxt, &strElem);
		if(strElem.u8Tag == ASN1_BIT_STRING)
		{
			ASN1_Read(pstrX509Asn1Cxt, 1, NULL);
		}

		ASN1_GetNextElement(pstrX509Asn1Cxt, &strElem);
		if(strElem.u8Tag == ASN1_SEQUENCE)
		{
			ASN1_GetNextElement(pstrX509Asn1Cxt, &strElem);
			if(strElem.u8Tag == ASN1_INTEGER)
			{
				pstrRsaPublicKey->pu8N = (uint8*)pstrMemPool->fpAlloc(pstrMemPool->pvPoolHandle, strElem.u32Length);
				if(pstrRsaPublicKey->pu8N != NULL)
				{
					ASN1_Read(pstrX509Asn1Cxt, strElem.u32Length, pstrRsaPublicKey->pu8N);
					while(*pstrRsaPublicKey->pu8N == 0)
					{
						pstrRsaPublicKey->pu8N ++;
						strElem.u32Length --;
					}
					pstrRsaPublicKey->u16NSize = (uint16)strElem.u32Length;
					
					ASN1_GetNextElement(pstrX509Asn1Cxt, &strElem);
					if(strElem.u8Tag == ASN1_INTEGER)
					{
						pstrRsaPublicKey->pu8E = (uint8*)pstrMemPool->fpAlloc(pstrMemPool->pvPoolHandle, strElem.u32Length);
						if(pstrRsaPublicKey->pu8E != NULL)
						{
							ASN1_Read(pstrX509Asn1Cxt, strElem.u32Length, pstrRsaPublicKey->pu8E);
							while(*pstrRsaPublicKey->pu8E == 0)
							{
								pstrRsaPublicKey->pu8E ++;
								strElem.u32Length --;
							}
							pstrRsaPublicKey->u16ESize = (uint16)strElem.u32Length;
							s8Ret = X509_SUCCESS;
						}
					}
				}
			}
		}
	}
	return s8Ret;
}
/*********************************************************************
Function
	Cert_DecodeECCPubKey

Description


Return
	

Author
	Ahmed Ezzat

Version
	1.0

Date
	21 Feb 2016
*********************************************************************/
TLS_CLIENT_API sint8 Cert_DecodeECCPubKey
(
tstrAsn1Context		*pstrX509Asn1Cxt, 
tstrAsn1Element		*pstrKeyParam,
tstrMemPool		*pstrMemPool,
tstrECPublicKey		*pstrEcdsaKey
)
{
	sint8	s8Ret = X509_FAIL;
	
	if((pstrX509Asn1Cxt != NULL) && (pstrEcdsaKey != NULL) && (pstrKeyParam != NULL) && (pstrMemPool != NULL))
	{
		tstrAsn1Element	strElem;
		uint8			u8PointFmt;

		if(pstrKeyParam->u8Tag == ASN1_OBJECT_IDENTIFIER)
		{
			uint8	u8Idx;
			uint8	au8EccNamedCurveID[16];
			
			ASN1_Read(pstrX509Asn1Cxt, pstrKeyParam->u32Length, au8EccNamedCurveID);
			for(u8Idx = 0 ; u8Idx < X509_NUM_SUPPORTED_SEC_ALGORITHMS ; u8Idx ++)
			{
				if(!M2M_MEMCMP(au8EccNamedCurveID, gastrSecAlgorithms[u8Idx].au8EncodedAlgID, pstrKeyParam->u32Length))
				{
					break;
				}
			}
			
			if(u8Idx == X509_NUM_SUPPORTED_SEC_ALGORITHMS) // For now, only secp256 is the only supported
			{
				TLS_ERR("X509 EC??\n");
				goto _END__;
			}
			
			pstrEcdsaKey->pstrCurve	= ECC_GetCurveInfo(gastrSecAlgorithms[u8Idx].u8AlgParam1);
		}
		else if(pstrKeyParam->u8Tag == ASN1_SEQUENCE)
		{
			goto _END__;
		}
		else if(pstrKeyParam->u8Tag == ASN1_NULL)
		{
			goto _END__;
		}
		
		ASN1_GetNextElement(pstrX509Asn1Cxt, &strElem);
		if(strElem.u8Tag == ASN1_BIT_STRING)
		{
			ASN1_Read(pstrX509Asn1Cxt, 1, NULL);
			ASN1_Read(pstrX509Asn1Cxt, 1, &u8PointFmt);
			if(u8PointFmt == 0x04)
			{
				strElem.u32Length -= 2;
				pstrEcdsaKey->strQ.u16Size = strElem.u32Length >> 1;
				ASN1_Read(pstrX509Asn1Cxt, strElem.u32Length >> 1, pstrEcdsaKey->strQ.X);
				ASN1_Read(pstrX509Asn1Cxt, strElem.u32Length >> 1, pstrEcdsaKey->strQ.Y);
				s8Ret = X509_SUCCESS;
			}
			else
			{
				TLS_ERR("Ecc Point Fmt<%X>??\n", u8PointFmt);
			}
		}		
	}
_END__:
	return s8Ret;
}
/*********************************************************************
Function
	Cert_DecodeSubjectPubKey

Description
	

Return
	

Author
	Ahmed Ezzat

Version
	1.0

Date
	7 March 2013
*********************************************************************/
TLS_CLIENT_API sint8 Cert_DecodeSubjectPubKey
(
tstrAsn1Context		*pstrX509Asn1Cxt, 
uint32 				u32Size, 
tstrMemPool		*pstrMemPool,
tstrPublicKey		*pstrPubKey
)
{
/*
	SubjectPublicKeyInfo ::= SEQUENCE {
		algorithm 			AlgorithmIdentifier,
		subjectPublicKey	BIT STRING 
	}
*/	
	sint8		s8Ret = X509_FAIL;

	if((pstrX509Asn1Cxt != NULL) && (pstrPubKey != NULL))
	{
		tstrAsn1Element	strElem;
		tstrAsn1Element	strPubKeyParam	= {0};
		uint16			u16Offset		= 0;

		u16Offset += ASN1_GetNextElement(pstrX509Asn1Cxt, &strElem);
		if((strElem.u8Tag == ASN1_SEQUENCE) && (u16Offset < u32Size))
		{
			tstrX509AlgID	*pstrPubKeyAlg;
			pstrPubKeyAlg = Cert_DecodeAlgID(pstrX509Asn1Cxt, strElem.u32Length, &strPubKeyParam);
			if(pstrPubKeyAlg != NULL)
			{
				pstrPubKey->enuType = (tenuPubKeyAlg)pstrPubKeyAlg->u8AlgParam1;
				if(pstrPubKey->enuType == PUBKEY_ALG_RSA)
				{
					s8Ret = Cert_DecodeRSAPubKey(pstrX509Asn1Cxt, &strPubKeyParam, pstrMemPool, &pstrPubKey->strRSAKey);
				}
				else if(pstrPubKey->enuType == PUBKEY_ALG_ECC)
				{
					s8Ret = Cert_DecodeECCPubKey(pstrX509Asn1Cxt, &strPubKeyParam, pstrMemPool, &pstrPubKey->strEccKey);
				}
				else
				{
					s8Ret = X509_FAIL;
				}
			}
		}
	}
	return s8Ret;
}
/*********************************************************************
Function
	Cert_DecodeValidity

Description
	

Return
	

Author
	Ahmed Ezzat

Version
	1.0

Date
	23 March 2013
*********************************************************************/
TLS_CLIENT_API sint8 Cert_DecodeValidity
(
tstrAsn1Context	*pstrX509Asn1Cxt, 
uint32 			u32Size,
tstrX509Cert	*pstrCer
)
{
/*
	Validity ::= SEQUENCE {
		notBefore 	Time,
		notAfter 		Time 
	}
*/
	sint8	s8Ret = X509_FAIL;

	if((pstrX509Asn1Cxt != 0) && (pstrCer != NULL))
	{
		tstrAsn1Element	strElem;
		uint8			au8Time[20];
		tstrSystemTime	strSysTime;

		pstrCer->u8ValidityStatus = X509_STATUS_DECODE_ERR;
		if(ASN1_GetNextElement(pstrX509Asn1Cxt, &strElem) != ASN1_INVALID)
		{
			/* Start time. */
			ASN1_Read(pstrX509Asn1Cxt, strElem.u32Length, au8Time);
			au8Time[strElem.u32Length] = '\0';
			Cert_DecodeTime(au8Time, &pstrCer->strStartDate);
			
			if(ASN1_GetNextElement(pstrX509Asn1Cxt, &strElem)  != ASN1_INVALID)
			{
				/* End time. */
				ASN1_Read(pstrX509Asn1Cxt, strElem.u32Length, au8Time);
				au8Time[strElem.u32Length] = '\0';
				Cert_DecodeTime(au8Time, &pstrCer->strExpiryDate);
				
				if(pstrCer->strExpiryDate.u16Year != 9999)
				{
					if(X509_GET_SYS_TIME(&strSysTime) == M2M_SUCCESS)
					{
						if(strSysTime.u16Year == 0)
						{
							pstrCer->u8ValidityStatus = X509_STATUS_EXPIRED;
						}
						else
						{
							if(Cert_CompareTime(&pstrCer->strStartDate, &strSysTime) > 0)
							{
								pstrCer->u8ValidityStatus = X509_STATUS_EXPIRED;
							}
							else
							{
								if(Cert_CompareTime(&pstrCer->strExpiryDate, &strSysTime) <= 0)
								{
									pstrCer->u8ValidityStatus = X509_STATUS_EXPIRED;
								}
								else
								{
									pstrCer->u8ValidityStatus = X509_STATUS_VALID;
								}
							}
						}
					}
					else
					{
						pstrCer->u8ValidityStatus = X509_STATUS_VALID;
					}
				}
				s8Ret = X509_SUCCESS;
			}
		}
	}
	return s8Ret;
}
/*********************************************************************
Function
	X509Cert_DecodeTBSCertificate

Description
	

Return
	

Author	
	Ahmed Ezzat

Version
	1.0

Date
	7 March 2013
*********************************************************************/
TLS_CLIENT_API sint8 Cert_DecodeTBSCertificate
(
tstrAsn1Context	*pstrX509Asn1Cxt, 
uint16 			u16CertSize, 
tstrX509Cert 	*pstrCert
)
{
/*
	TBSCertificate ::= SEQUENCE {
			version 			[0] 	Version DEFAULT v1,
			serialNumber				CertificateSerialNumber,
			signature					AlgorithmIdentifier,
			issuer						Name,
			validity					Validity,
			subject 					Name,
			subjectPublicKeyInfo		SubjectPublicKeyInfo,
			issuerUniqueID		[1]		IMPLICIT UniqueIdentifier OPTIONAL,
										-- If present, version MUST be v2 or v3
			subjectUniqueID 	[2] 	IMPLICIT UniqueIdentifier OPTIONAL,
										-- If present, version MUST be v2 or v3
			extensions			[3] 	Extensions OPTIONAL
										-- If present, version MUST be v3 -- 
		}
	
*/
	sint8		s8Ret = X509_SUCCESS;

	if((pstrX509Asn1Cxt != NULL) && (pstrCert != NULL))
	{
		uint16					u16ReadOffset = 0;
		tstrAsn1Element			strElement;
		tenuCertParsingState	enuCertState 	= CERT_VERSION_PENDING;
		
		/* Loop on the elements of the certificate until finishing. 
		*/
		while(u16ReadOffset < u16CertSize)
		{
			u16ReadOffset += ASN1_GetNextElement(pstrX509Asn1Cxt, &strElement);
			switch(enuCertState)
			{
			case CERT_VERSION_PENDING:
				/*
					version
				*/
				if(strElement.u8Tag == X509_VERSION)
				{
					/* The encoding of version is on the form 
							A0 03 02 01 ver
					*/
					if(strElement.u32Length < 3)
					{
						s8Ret = X509_FAIL;
					}
					ASN1_Read(pstrX509Asn1Cxt, 2, NULL);
					ASN1_Read(pstrX509Asn1Cxt, 1, &pstrCert->u8Version);
					enuCertState = CERT_SERIAL_PENDING;
				}
				else if(strElement.u8Tag == X509_SERIAL_NO)
				{
					uint32	u32DropLen = 0;
					
					/* The certificate version number is absent from the certificate.
					It will be set to the default value Version 1.0
					*/
					pstrCert->u8Version = X509_VER_1;

					/* The first field is the serial number. */
					if(strElement.u32Length > X509_SERIAL_NO_MAX_SZ)
					{
						strElement.u32Length = X509_SERIAL_NO_MAX_SZ;
						u32DropLen = strElement.u32Length - X509_SERIAL_NO_MAX_SZ;
					}
					
					pstrCert->u8SerialNumberLength = (uint8)strElement.u32Length;
					ASN1_Read(pstrX509Asn1Cxt, strElement.u32Length, pstrCert->au8SerialNo);
					ASN1_Read(pstrX509Asn1Cxt, u32DropLen, NULL);
					enuCertState = CERT_SIGNATURE_PENDING;
				}
				break;

			case CERT_SERIAL_PENDING:
				/*
					serialNumber
				*/
				if(strElement.u8Tag == X509_SERIAL_NO)
				{
					uint32	u32DropLen = 0;

					/* The first field is the serial number. */
					if(strElement.u32Length > X509_SERIAL_NO_MAX_SZ)
					{
						strElement.u32Length = X509_SERIAL_NO_MAX_SZ;
						u32DropLen = strElement.u32Length - X509_SERIAL_NO_MAX_SZ;
					}
					
					pstrCert->u8SerialNumberLength = (uint8)strElement.u32Length;
					ASN1_Read(pstrX509Asn1Cxt, strElement.u32Length, pstrCert->au8SerialNo);
					ASN1_Read(pstrX509Asn1Cxt, u32DropLen, NULL);
					enuCertState = CERT_SIGNATURE_PENDING;
				}
				break;

			case CERT_SIGNATURE_PENDING:
				/*
					signature
				*/
				if(strElement.u8Tag == X509_SIGNATURE)
				{
					tstrX509AlgID	*pstrSignHashAlg;
					pstrSignHashAlg = Cert_DecodeAlgID(pstrX509Asn1Cxt, strElement.u32Length, NULL);
					if(pstrSignHashAlg != NULL)
					{
						pstrCert->enuSignAlg	= (tenuTlsSignAlg)pstrSignHashAlg->u8AlgParam1;
						pstrCert->enuHashAlg	= (tenuHashAlg)pstrSignHashAlg->u8AlgParam2;
					}
					else
					{
						s8Ret = X509_FAIL;
					}
					enuCertState = CERT_ISSUER_PENDING;
				}
				break;

			case CERT_ISSUER_PENDING:
				/*
					issuer
				*/
				if(strElement.u8Tag == X509_ISSUER)
				{
					s8Ret = Cert_DecodeX520Name(pstrX509Asn1Cxt, strElement.u32Length, &pstrCert->strIssuer, pstrCert->pstrMemPool);
					enuCertState = CERT_VALIDITY_PENDING;
				}
				break;

			case CERT_VALIDITY_PENDING:
				/*
					validity
				*/
				if(strElement.u8Tag == X509_VALIDITY)
				{
					s8Ret = Cert_DecodeValidity(pstrX509Asn1Cxt, strElement.u32Length, pstrCert);
					enuCertState = CERT_SUBJECT_PENDING;
				}
				break;

			case CERT_SUBJECT_PENDING:
				/*
					subject
				*/
				if(strElement.u8Tag == X509_SUBJECT)
				{
					s8Ret = Cert_DecodeX520Name(pstrX509Asn1Cxt, strElement.u32Length , &pstrCert->strSubject, pstrCert->pstrMemPool);
					enuCertState = CERT_SUBECTKEYINFO_PENDING;
				}
				break;

			case CERT_SUBECTKEYINFO_PENDING:
				/*
					subjectPublicKeyInfo
				*/
				if(strElement.u8Tag == X509_SUBJECT_KEY_INFO)
				{
					s8Ret = Cert_DecodeSubjectPubKey(pstrX509Asn1Cxt, strElement.u32Length, pstrCert->pstrMemPool, &pstrCert->strPubKey);
					enuCertState = CERT_EXTENSIONS_PENDING;
				}
				break;

			case CERT_EXTENSIONS_PENDING:
				ASN1_Read(pstrX509Asn1Cxt, strElement.u32Length, NULL);
				break;
			}

			if(s8Ret != X509_SUCCESS)
				break;
		}
	}
	return s8Ret;
}
/*********************************************************************
Function
	Ecdsa_DecodeSignature

Description
	

Return
	

Author	
	Ahmed Ezzat

Version
	1.0

Date
	29 MAR 2016
*********************************************************************/
TLS_CLIENT_API sint8 X509_DecodeEcdsaSignature
(
tstrAsn1Context	*pstrX509Asn1Cxt,
uint8			*pu8Sig,
uint16			*pu16SigSz
)
{
	sint8		s8Ret = X509_FAIL;
	
	if((pstrX509Asn1Cxt != NULL) && (pu8Sig != NULL))
	{
		tstrAsn1Element	strElem;
		uint16			u16SigSz;
		uint16			u16TmpSz		= 0;
		uint8			u8LoopCount		= 2;
		
		u16TmpSz	= *pu16SigSz;
		u16SigSz 	= 0;
		ASN1_GetNextElement(pstrX509Asn1Cxt, &strElem);
		if((strElem.u8Tag == ASN1_SEQUENCE) && (strElem.u32Length <= u16TmpSz))
		{
			u16TmpSz = (uint16)strElem.u32Length;
			while(u8LoopCount)
			{
				ASN1_GetNextElement(pstrX509Asn1Cxt, &strElem);
				if((strElem.u8Tag == ASN1_INTEGER) && (strElem.u32Length < u16TmpSz))
				{
					strElem.u32Length --;
					u16SigSz += (uint16)strElem.u32Length;
					ASN1_Read(pstrX509Asn1Cxt, 1, pu8Sig);
					if(*pu8Sig != 0)
					{
						pu8Sig		++;
						u16SigSz	++;
					}
					ASN1_Read(pstrX509Asn1Cxt, strElem.u32Length, pu8Sig);
					pu8Sig += strElem.u32Length;
					s8Ret = X509_SUCCESS;
				}
				else
				{
					s8Ret = X509_FAIL;
					break;
				}
				u8LoopCount --;
			}
			*pu16SigSz = u16SigSz;
		}
	}
	return s8Ret;
}
/*********************************************************************
Function
	X509Cert_DecodeTBSCertificate

Description
	

Return
	

Author	
	Ahmed Ezzat

Version
	1.0

Date
	7 March 2013
*********************************************************************/
TLS_CLIENT_API sint8 Cert_DecodeSignature
(
tstrAsn1Context	*pstrX509Asn1Cxt, 
uint16 			u16SigSize, 
tstrX509Cert 	*pstrCert
)
{
	sint8		s8Ret = X509_FAIL;
	
	if((pstrX509Asn1Cxt != NULL) && (pstrCert != NULL))
	{
		tstrAsn1Element	strElem;
		
		ASN1_GetNextElement(pstrX509Asn1Cxt, &strElem);
		if((strElem.u8Tag == ASN1_BIT_STRING) && (strElem.u32Length < u16SigSize))
		{
			/* Jump one byte. 
			*/
			ASN1_Read(pstrX509Asn1Cxt, 1, NULL);
			strElem.u32Length --;
		
			/* Store the obtained signature. 
			*/
			pstrCert->pu8Sig = (uint8*)pstrCert->pstrMemPool->fpAlloc(pstrCert->pstrMemPool->pvPoolHandle, strElem.u32Length);
			if(pstrCert->pu8Sig != NULL)
			{
				if(pstrCert->enuSignAlg == TLS_SIG_ALG_ECDSA)
				{
					pstrCert->u16SigSz	= (uint16)strElem.u32Length;
					s8Ret = X509_DecodeEcdsaSignature(pstrX509Asn1Cxt, pstrCert->pu8Sig, &pstrCert->u16SigSz);					
				}
				else if(pstrCert->enuSignAlg == TLS_SIG_ALG_RSA)
				{
					/*
						RSA Signature.
					*/
					pstrCert->u16SigSz	= (uint16)strElem.u32Length;
					ASN1_Read(pstrX509Asn1Cxt, strElem.u32Length, pstrCert->pu8Sig);
					s8Ret = X509_SUCCESS;
				}
			}
		}		
	}
	return s8Ret;
}
/*********************************************************************
Function
	Cert_ComputeTBSCertHash

Description 

Return
	None

Author
	Ahmed Ezzat

Version
	1.0

Date
	12 April 2016
*********************************************************************/
sint8 Cert_ComputeTBSCertHash(tstrTlsBuffer *pstrCrtBuff, tstrTLSBufferPos *pstrTBSCrt, uint16 u16TBSSize, tstrX509Cert *pstrCert)
{
	sint8	ret = X509_FAIL;

	if((pstrCert != NULL) && (pstrTBSCrt != NULL))
	{
		tpfHash				fpHash;
		tstrShaHashContext	strHash;
		tstrTLSBufferPos	strTmpPos;
		uint8				*pu8TmpBuf;
		uint16				u16ReadSize;

		if(pstrCert->enuHashAlg < HASH_ALG_MAX)
		{
			fpHash = eastrTlsHashes[pstrCert->enuHashAlg].fpHash;
			pstrCert->u16HashSz	= eastrTlsHashes[pstrCert->enuHashAlg].u16HashSz;

			if(fpHash != NULL)
			{
				pstrCert->pu8Hash = (uint8*)pstrCert->pstrMemPool->fpAlloc(pstrCert->pstrMemPool->pvPoolHandle, pstrCert->u16HashSz);
				if(pstrCert->pu8Hash != NULL)
				{
					/* Save the current position of the certificate message buffer.
					*/
					TLS_BufferGetPos(pstrCrtBuff, &strTmpPos);
				
					/* Set the buffer to the start of the TBS certificate for Hash Calculation.
					*/
					TLS_BufferSetPos(pstrCrtBuff, pstrTBSCrt);
				
					fpHash(&strHash, SHA_FLAGS_INIT, NULL, 0, NULL);
					while(u16TBSSize > 0)
					{
						u16ReadSize = TLS_BufferReadCurrEntry(pstrCrtBuff, u16TBSSize, &pu8TmpBuf, BTRUE);
						u16TBSSize -= u16ReadSize;
						fpHash(&strHash, SHA_FLAGS_UPDATE, pu8TmpBuf, u16ReadSize, NULL);
					}
					fpHash(&strHash, SHA_FLAGS_FINISH, NULL, 0, pstrCert->pu8Hash);
				
					/* Reload the saved position of the certificate message buffer.
					*/
					TLS_BufferSetPos(pstrCrtBuff, &strTmpPos);
					ret = X509_SUCCESS;
				}
			}
		}		
	}
	return ret;
}
/*********************************************************************
Function
	X509Cert_Decode

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
TLS_CLIENT_API sint8 X509Cert_Decode
(	
tstrTlsBuffer	*pstrX509Buffer, 
uint32 			u32CertSize,
tstrMemPool	*pstrPool,
tstrX509Cert 	*pstrCert,
uint8			bDumpX509
)
{
/*

	Certificate ::= SEQUENCE {
		tbsCertificate 			TBSCertificate,
		signatureAlgorithm 		AlgorithmIdentifier,
		signature 				BIT STRING 
	}

*/
	sint8	s8Ret = X509_FAIL;
	
	if((pstrX509Buffer != NULL) && (pstrCert != NULL) && (pstrPool != NULL))
	{
		if(pstrPool->fpAlloc != NULL)
		{
			uint32				u32Offset		= 0;
			tstrTLSBufferPos	strTBSCert;
			tstrAsn1Element		strElement;
			uint16				u16TBSCertSize;
			tstrAsn1Context		strX509ASN1Cxt;
			tstrX509AlgID		*pstrSignHashAlg;

			/* Initialize the ASN1 Decoding operation. 
			*/
			strX509ASN1Cxt.pstrTlsBuffer	= pstrX509Buffer;
			pstrCert->pstrMemPool			= pstrPool;
			u32Offset += ASN1_GetNextElement(&strX509ASN1Cxt, &strElement);
			if((strElement.u8Tag == ASN1_SEQUENCE) && (strElement.u32Length < u32CertSize))
			{
				/* Maintain the TBS certificate start position because it shall be used later to calculate the certificate HASH
				*/
				TLS_BufferGetPos(pstrX509Buffer, &strTBSCert);
				u32Offset -= strElement.u32Length;
				
				/* tbsCertificate. 
				*/
				u16TBSCertSize = ASN1_GetNextElement(&strX509ASN1Cxt, &strElement);
				if((strElement.u8Tag == ASN1_SEQUENCE) && (strElement.u32Length < u32CertSize))
				{
					u32Offset += u16TBSCertSize;
					if(Cert_DecodeTBSCertificate(&strX509ASN1Cxt, (uint16)strElement.u32Length, pstrCert) == 0)
					{
						/* signatureAlgorithm.
						*/
						u32Offset += ASN1_GetNextElement(&strX509ASN1Cxt, &strElement);
						if((strElement.u8Tag == ASN1_SEQUENCE) && (u32Offset < u32CertSize))
						{
							/* Check if the signatureAlgorithm ID obtained in this element 
							matches the signature field of the TBS Certificate.
							*/
							pstrSignHashAlg = Cert_DecodeAlgID(&strX509ASN1Cxt, strElement.u32Length, NULL);
							if(pstrSignHashAlg != NULL)
							{
								if((pstrSignHashAlg->u8AlgParam1 == pstrCert->enuSignAlg) && (pstrSignHashAlg->u8AlgParam2 == pstrCert->enuHashAlg))
								{
									/* signature.
									*/
									s8Ret = Cert_DecodeSignature(&strX509ASN1Cxt, (uint16)(u32CertSize - u32Offset), pstrCert);
									if(s8Ret == X509_SUCCESS)
									{
										/* Compute the certificate hash.
										*/
										s8Ret = Cert_ComputeTBSCertHash(pstrX509Buffer, &strTBSCert, u16TBSCertSize, pstrCert);
									}
									if(bDumpX509)
										X509Cert_Dump(pstrCert);
								}
							}
						}
					}
				}
			}
		}
	}
	return s8Ret;
}
/*********************************************************************
Function
	Cert_DecodeTime

Description


Return
	None

Author
	Ahmed Ezzat

Version
	1.0

Date
	17 Aug 2014
*********************************************************************/
TLS_CLIENT_API sint8 Cert_DecodeTime(uint8 *pu8Time, tstrSystemTime *pstrTime)
{
	sint8		s8Ret = X509_FAIL;
	
	if(pu8Time != NULL)
	{
		uint8	u8TimeLength = (uint8)strlen((char*)pu8Time);
		uint8	au8Time[20];
		uint8	u8Idx;

		M2M_MEMCPY(au8Time, pu8Time, 20);
		
		if((u8TimeLength >= X509_UTC_TIME_LENGTH) && (u8TimeLength <= X509_GENERALIZED_TIME_LENGTH))
		{
			if(au8Time[u8TimeLength - 1] == 'Z')
			{
				for(u8Idx = 0; u8Idx < (u8TimeLength - 1); u8Idx ++)
				{
					au8Time[u8Idx] -= '0';
				}
				
				if(u8TimeLength == X509_UTC_TIME_LENGTH)
				{
					pstrTime->u16Year 	= (au8Time[0] * 10) + au8Time[1];
					pstrTime->u16Year 	+= (pstrTime->u16Year < 50 ? 2000 : 1900);
					u8Idx = 2;
				}
				else
				{
					pstrTime->u16Year 	= (au8Time[0] * 1000) + (au8Time[1] * 100) + (au8Time[2] * 10) + au8Time[3];
					u8Idx = 4;
				}
				pstrTime->u8Month 		= GET_VAL(au8Time, u8Idx);
				u8Idx += 2;
				
				pstrTime->u8Day 		= GET_VAL(au8Time, u8Idx);
				u8Idx += 2;

				pstrTime->u8Hour		= GET_VAL(au8Time, u8Idx);
				u8Idx += 2;
				
				pstrTime->u8Minute		= GET_VAL(au8Time, u8Idx);
				u8Idx += 2;
				
				pstrTime->u8Second		= GET_VAL(au8Time, u8Idx);
				
				s8Ret = X509_SUCCESS;
			}
		}
	}
	return s8Ret;
}
/*********************************************************************
Function
	Cert_DecodeTime

Description
	if Return value < 0 then it indicates T1 is less than T2.
	if Return value > 0 then it indicates T2 is less than T1.
	if Return value = 0 then it indicates T1 is equal to T2.
	
Return
	None

Author
	Ahmed Ezzat

Version
	1.0

Date
	17 Aug 2014
*********************************************************************/
sint8 Cert_CompareTime(tstrSystemTime *pstrT1, tstrSystemTime *pstrT2)
{
	sint8		s8Cmp = 1;
	
	if((pstrT1 != NULL) && (pstrT2 != NULL))
	{
		/* YEAR.
		*/
		if(pstrT1->u16Year == pstrT2->u16Year)
		{
			/* MONTH.
			*/
			if(pstrT1->u8Month == pstrT2->u8Month)
			{
				/* DAY
				*/
				if(pstrT1->u8Day == pstrT2->u8Day)
				{
					if(pstrT1->u8Hour == pstrT2->u8Hour)
					{
						if(pstrT1->u8Minute == pstrT2->u8Minute)
						{
							s8Cmp = pstrT1->u8Second - pstrT2->u8Second;
						}
						else
						{
							s8Cmp = pstrT1->u8Minute - pstrT2->u8Minute;
						}
					}
					else
					{
						s8Cmp = pstrT1->u8Hour - pstrT2->u8Hour;
					}
				}
				else
				{
					s8Cmp = pstrT1->u8Day - pstrT2->u8Day;
				}
			}
			else
			{
				s8Cmp = pstrT1->u8Month - pstrT2->u8Month;
			}
		}
		else
		{
			s8Cmp = pstrT1->u16Year - pstrT2->u16Year;
		}
	}
	return s8Cmp;
}
/*********************************************************************
Function
	X509Cert_Dump

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
TLS_CLIENT_API void X509Cert_Dump(tstrX509Cert *pstrCert)
{
	if(pstrCert != NULL)
	{
#ifdef X509_DUMP_ENABLE
		uint32	i;

		TLS_LOG("*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=\n");
		TLS_LOG("     CERTIFICATE <%s>\n", pstrCert->strSubject.acCmnName);
		TLS_LOG("*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=\n");
		
		TLS_LOG("VERSION                  %u\n",pstrCert->u8Version + 1);
		TLS_LOG("SERIAL NO                ");
		for(i = 0 ; i < pstrCert->u8SerialNumberLength ; i++)
		{
			TLS_LOG("%02X ", pstrCert->au8SerialNo[i]);
		}
		TLS_LOG("\n");
		
		TLS_LOG("SIGNATURE ALGORITHM      ");
		if(pstrCert->enuSignAlg == TLS_SIG_ALG_RSA)
		{
			TLS_LOG("RSA");
		}
		else if(pstrCert->enuSignAlg == TLS_SIG_ALG_ECDSA)
		{
			TLS_LOG("ECDSA");
		}
		TLS_LOG("\n");

		TLS_LOG("HASH ALGORITHM           ");
		if(pstrCert->enuHashAlg == HASH_ALG_SHA1)
		{
			TLS_LOG("SHA1");
		}
		else if(pstrCert->enuHashAlg == HASH_ALG_SHA224)
		{
			TLS_LOG("SHA224");
		}
		else if(pstrCert->enuHashAlg == HASH_ALG_SHA256)
		{
			TLS_LOG("SHA256");
		}
		else if(pstrCert->enuHashAlg == HASH_ALG_SHA1)
		{
			TLS_LOG("SHA384");
		}
		else if(pstrCert->enuHashAlg == HASH_ALG_SHA512)
		{
			TLS_LOG("SHA512");
		}
		TLS_LOG("\n");

		TLS_LOG("ISSUER                   ");
		if(strlen(pstrCert->strIssuer.acCmnName) != 0)
		{
			TLS_LOG("%s",pstrCert->strIssuer.acCmnName);
		}
		TLS_LOG("\n");

		TLS_LOG("SUBJECT                  ");
		if(strlen(pstrCert->strSubject.acCmnName) != 0)
		{
			TLS_LOG("%s",pstrCert->strSubject.acCmnName);
		}
		TLS_LOG("\n");

		TLS_LOG("Valid From               ");
		TLS_LOG("%d-%02d-%02d %02d:%02d:%02d\n",
				pstrCert->strStartDate.u16Year, pstrCert->strStartDate.u8Month, pstrCert->strStartDate.u8Day,
				pstrCert->strStartDate.u8Hour, pstrCert->strStartDate.u8Minute, pstrCert->strStartDate.u8Second);
			
		TLS_LOG("Valid to                 ");
		TLS_LOG("%d-%02d-%02d %02d:%02d:%02d\n",
				pstrCert->strExpiryDate.u16Year, pstrCert->strExpiryDate.u8Month, pstrCert->strExpiryDate.u8Day,
				pstrCert->strExpiryDate.u8Hour, pstrCert->strExpiryDate.u8Minute, pstrCert->strExpiryDate.u8Second);

		TLS_LOG("\n");
		if(pstrCert->strPubKey.enuType == PUBKEY_ALG_RSA)
		{
			TLS_LOG("PUBLIC KEY               RSA (%u bits)\n", pstrCert->strPubKey.strRSAKey.u16NSize * 8);
			M2M_DUMP_BUF("Modulus", pstrCert->strPubKey.strRSAKey.pu8N, pstrCert->strPubKey.strRSAKey.u16NSize);
			M2M_DUMP_BUF("Exponent", pstrCert->strPubKey.strRSAKey.pu8E, pstrCert->strPubKey.strRSAKey.u16ESize);			
		}
		else if(pstrCert->strPubKey.enuType == PUBKEY_ALG_ECC)
		{
			TLS_LOG("PUBLIC KEY\n\t");
			M2M_DUMP_BUF("ECDSA", pstrCert->strPubKey.strEccKey.strQ.X, (pstrCert->strPubKey.strEccKey.strQ.u16Size * 2)); 
		}

		TLS_LOG("\n");
		M2M_DUMP_BUF("SIGNATURE", pstrCert->pu8Sig, pstrCert->u16SigSz);
		TLS_LOG("*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=\n");
#else
		TLS_INFO("*=*=* X509 *=*=*\n");
		TLS_INFO("\tSubject <%s>\n", ((strlen(pstrCert->strSubject.acCmnName) != 0) ? pstrCert->strSubject.acCmnName	: " "));
		TLS_INFO("\tIssuer  <%s>\n",((strlen(pstrCert->strIssuer.acCmnName) != 0) ? pstrCert->strIssuer.acCmnName	: " "));
		TLS_INFO("\t<%d-%02d-%02d %02d:%02d:%02d> to <%d-%02d-%02d %02d:%02d:%02d>\n", \
				pstrCert->strStartDate.u16Year, pstrCert->strStartDate.u8Month, pstrCert->strStartDate.u8Day, \
				pstrCert->strStartDate.u8Hour, pstrCert->strStartDate.u8Minute, pstrCert->strStartDate.u8Second, \
				pstrCert->strExpiryDate.u16Year, pstrCert->strExpiryDate.u8Month, pstrCert->strExpiryDate.u8Day, \
				pstrCert->strExpiryDate.u8Hour, pstrCert->strExpiryDate.u8Minute, pstrCert->strExpiryDate.u8Second);
#endif
	}
}
