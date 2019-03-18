/**
 *
 * \file
 *
 * \brief This module contains WILC common APIs declarations.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef _NM_COMMON_H_
#define _NM_COMMON_H_

#include "bsp/include/nm_bsp.h"

/* 
 * Enable computing PMK in host rather than in WILC.
 * WILC1000 has HW accelerator that speeds up the computation on the device.
 * WILC3000 doesn't HW accelerator, and with this option not defined, PMK will
 * be computed in the FW, which takes up to 5 secs.
 */
#ifdef CONF_WILC_USE_3000_REV_A
#define COMPUTE_PMK_IN_HOST
#endif
/* 
 * Default Tx mechanism is that the driver will wait in hif_send() till the FW
 * allocates memory for the packet. If memory is still not available it will fail
 * If INT_BASED_TX is defined, the driver would fail instantiously if no
 * memory was availble.
 * On the other hand, the driver will send an M2M_WIFI_RESP_PACKET_SENT
 * notification to the application when last tx packet was sent, and FW is
 * ready to receive new packets. In this mode the applicatino shouldn't attempt
 * sending a new packet unless the notification is received.
 */
//#define INT_BASED_TX

#define M2M_TIME_OUT_DELAY 10000

/*states*/
#define M2M_SUCCESS         ((sint8)0)
#define M2M_ERR_SEND		((sint8)-1)
#define M2M_ERR_RCV			((sint8)-2)
#define M2M_ERR_MEM_ALLOC	((sint8)-3)
#define M2M_ERR_TIME_OUT	((sint8)-4)
#define M2M_ERR_INIT        ((sint8)-5)
#define M2M_ERR_BUS_FAIL    ((sint8)-6)
#define M2M_NOT_YET			((sint8)-7)
#define M2M_ERR_FIRMWARE	((sint8)-8)
#define M2M_SPI_FAIL		((sint8)-9)
#define M2M_ERR_FIRMWARE_bURN	 ((sint8)-10)
#define M2M_ACK				((sint8)-11)
#define M2M_ERR_FAIL		((sint8)-12)
#define M2M_ERR_FW_VER_MISMATCH         ((sint8)-13)
#define M2M_ERR_SCAN_IN_PROGRESS         ((sint8)-14)

/*i2c MAASTER ERR*/
#define I2C_ERR_LARGE_ADDRESS 	  0xE1UL	/*the address exceed the max addressing mode in i2c flash*/
#define I2C_ERR_TX_ABRT 		  0xE2UL	/*NO ack from slave*/
#define I2C_ERR_OVER_SIZE 		  0xE3UL	/**/
#define ERR_PREFIX_NMIS		      0xE4UL	/*wrong first four byte in flash NMIS*/
#define ERR_FIRMEWARE_EXCEED_SIZE 0xE5UL	/*Total size of firmware exxed the max size 256k*/
/**/
#define PROGRAM_START		0x26961735UL
#define BOOT_SUCCESS		0x10add09eUL
#define BOOT_START		    0x12345678UL     


#define NBIT31				(0x80000000)
#define NBIT30				(0x40000000)
#define NBIT29				(0x20000000)
#define NBIT28				(0x10000000)
#define NBIT27				(0x08000000)
#define NBIT26				(0x04000000)
#define NBIT25				(0x02000000)
#define NBIT24				(0x01000000)
#define NBIT23				(0x00800000)
#define NBIT22				(0x00400000)
#define NBIT21				(0x00200000)
#define NBIT20				(0x00100000)
#define NBIT19				(0x00080000)
#define NBIT18				(0x00040000)
#define NBIT17				(0x00020000)
#define NBIT16				(0x00010000)
#define NBIT15				(0x00008000)
#define NBIT14				(0x00004000)
#define NBIT13				(0x00002000)
#define NBIT12				(0x00001000)
#define NBIT11				(0x00000800)
#define NBIT10				(0x00000400)
#define NBIT9				(0x00000200)
#define NBIT8				(0x00000100)
#define NBIT7				(0x00000080)
#define NBIT6				(0x00000040)
#define NBIT5				(0x00000020)
#define NBIT4				(0x00000010)
#define NBIT3				(0x00000008)
#define NBIT2				(0x00000004)
#define NBIT1				(0x00000002)
#define NBIT0				(0x00000001)


#define M2M_LOG_NONE									0
#define M2M_LOG_ERROR									1
#define M2M_LOG_INFO									2
#define M2M_LOG_REQ										3
#define M2M_LOG_DBG										4

#if (defined __APP_APS3_CORTUS__)
#define M2M_LOG_LEVEL									M2M_LOG_ERROR
#else
#define M2M_LOG_LEVEL									M2M_LOG_DBG
#endif

/**/
#if !((defined __MSP430FR5739)||(defined __MCF964548__))

#define M2M_ERR(...)
#define M2M_INFO(...)
#define M2M_REQ(...)
#define M2M_DBG(...)

#if (NM_DEBUG == 1)
#define M2M_PRINT(...)							do{NM_BSP_PRINTF(__VA_ARGS__);NM_BSP_PRINTF("\r");}while(0)
	#if (M2M_LOG_LEVEL >= M2M_LOG_ERROR)
	#undef M2M_ERR
	#define M2M_ERR(...)							do{NM_BSP_PRINTF("(APP)(ERR)[%s][%d]",__FUNCTION__,__LINE__); NM_BSP_PRINTF(__VA_ARGS__);NM_BSP_PRINTF("\r");}while(0)
		#if (M2M_LOG_LEVEL >= M2M_LOG_INFO)
		#undef M2M_INFO
		#define M2M_INFO(...)							do{NM_BSP_PRINTF("(APP)(INFO)"); NM_BSP_PRINTF(__VA_ARGS__);NM_BSP_PRINTF("\r");}while(0)
			#if (M2M_LOG_LEVEL >= M2M_LOG_REQ)
			#undef M2M_REQ
			#define M2M_REQ(...)							do{NM_BSP_PRINTF("(APP)(R)"); NM_BSP_PRINTF(__VA_ARGS__);NM_BSP_PRINTF("\r");}while(0)
				#if (M2M_LOG_LEVEL >= M2M_LOG_DBG)
				#undef M2M_DBG
				#define M2M_DBG(...)							do{NM_BSP_PRINTF("(APP)(DBG)[%s][%d]",__FUNCTION__,__LINE__); NM_BSP_PRINTF(__VA_ARGS__);NM_BSP_PRINTF("\r");}while(0)
				#endif
			#endif
		#endif
	#endif
#else
#define M2M_ERR(...)
#define M2M_DBG(...)
#define M2M_INFO(...)
#define M2M_PRINT(...)
#endif
#else
#if (!defined  __MCF964548__)||(!defined __SAMD21J18A__)
static void M2M_ERR(const char *_format, ...) //__attribute__ ((__format__ (M2M_ERR, 1, 2)))
{
}
static void M2M_DBG(const char *_format, ...) //__attribute__ ((__format__ (M2M_DBG, 1, 2)))
{
}
static void M2M_INFO(const char *_format, ...) // __attribute__ ((__format__ (M2M_INFO, 1, 2)))
{

}
static void M2M_PRINT(const char *_format, ...) // __attribute__ ((__format__ (M2M_INFO, 1, 2)))
{

}
static void NM_BSP_PRINTF(const char *_format, ...)
{
}
#endif
#endif

#define M2M_MAX(A,B)					((A) > (B) ? (A) : (B))
#define M2M_SEL(x,m1,m2,m3)				((x>1)?((x>2)?(m3):(m2)):(m1))
#define WORD_ALIGN(val) 				(((val) & 0x03) ? ((val) + 4 - ((val) & 0x03)) : (val))



#define DATA_PKT_OFFSET	4

#ifndef CONF_WILC_BIG_ENDIAN
#define BYTE_0(word)   					((uint8)(((word) >> 0 	) & 0x000000FFUL))
#define BYTE_1(word)  	 				((uint8)(((word) >> 8 	) & 0x000000FFUL))
#define BYTE_2(word)   					((uint8)(((word) >> 16) & 0x000000FFUL))
#define BYTE_3(word)   					((uint8)(((word) >> 24) & 0x000000FFUL))
#else
#define BYTE_0(word)   					((uint8)(((word) >> 24) & 0x000000FFUL))
#define BYTE_1(word)  	 				((uint8)(((word) >> 16) & 0x000000FFUL))
#define BYTE_2(word)   					((uint8)(((word) >> 8 	) & 0x000000FFUL))
#define BYTE_3(word)   					((uint8)(((word) >> 0 	) & 0x000000FFUL))
#endif


typedef enum{
	M2M_REQ_GRP_MAIN = 0, M2M_REQ_GRP_WIFI, M2M_REQ_GRP_HIF
}tenuM2mReqGrp;


typedef enum{
	M2M_REQ_CONFIG_PKT,
	M2M_REQ_DATA_PKT = NBIT7
}tenuM2mReqPkt;
#ifdef __cplusplus
     extern "C" {
 #endif
NMI_API void m2m_memcpy(uint8* pDst,uint8* pSrc,uint32 sz);
NMI_API void m2m_memset(uint8* pBuf,uint8 val,uint32 sz);
NMI_API uint16 m2m_strlen(uint8 * pcStr);
NMI_API sint8 m2m_memcmp(uint8 *pu8Buff1,uint8 *pu8Buff2 ,uint32 u32Size);
NMI_API uint8 m2m_strncmp(uint8 *pcS1, uint8 *pcS2, uint16 u16Len);
NMI_API uint8 * m2m_strstr(uint8 *pcIn, uint8 *pcStr);
NMI_API uint8 m2m_checksum(uint8* buf, int sz);

#ifdef __cplusplus
}
 #endif
#endif	/*_NM_COMMON_H_*/
