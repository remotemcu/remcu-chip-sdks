/**
* \file
*
* \brief BLE Utils declarations
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
/*
* Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
*/

#ifndef __BLE_UTILS_H__
#define __BLE_UTILS_H__

#include <asf.h>

#define BLE_CENTRAL					(0x01)
#define BLE_PERIPHERAL				(0x02)
#define BLE_CENTRAL_AND_PERIPHERAL	(0x03)
#define BLE_OBSERVER				(0x04)
#define BLE_BROADCASTER				(0x05)

#define DBG_LOG_CONT	printf

#define DBG_LOG		    printf("\r\n");\
						printf
						
#define UNUSED1(x) (void)(x)
#define UNUSED2(x,y) (void)(x),(void)(y)
#define UNUSED3(x,y,z) (void)(x),(void)(y),(void)(z)
#define UNUSED4(a,x,y,z) (void)(a),(void)(x),(void)(y),(void)(z)
#define UNUSED5(a,b,x,y,z) (void)(a),(void)(b),(void)(x),(void)(y),(void)(z)
#define UNUSED6(a,b,c,x,y,z) (void)(a),(void)(b),(void)(c),(void)(x),(void)(y),(void)(z)
#define UNUSED7(a,b,c,d,x,y,z) (void)(a),(void)(b),(void)(c),(void)(d),(void)(x),(void)(y),(void)(z)
#define UNUSED8(a,b,c,d,e,x,y,z) (void)(a),(void)(b),(void)(c),(void)(d),(void)(e),(void)(x),(void)(y),(void)(z)

#define VA_NUM_ARGS_IMPL(_1,_2,_3,_4,_5,_6,_7,_8, N,...) N
#define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL(__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1)

#define ALL_UNUSED_IMPL_(nargs) UNUSED ## nargs
#define ALL_UNUSED_IMPL(nargs) ALL_UNUSED_IMPL_(nargs)
#define ALL_UNUSED(...) ALL_UNUSED_IMPL( VA_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__ )

#define DBG_LOG_DEV		ALL_UNUSED

						
#define IEEE11073_EXPONENT						(0xFF000000)

#define IEEE754_MANTISA(val)					((uint32_t)(val * 10))

#define IEEE754_TO_IEEE11073_FLOAT(f_val)		(IEEE11073_EXPONENT | \
												IEEE754_MANTISA(f_val))

static inline uint32_t convert_ieee754_ieee11073_float(float f_val)
{
	uint32_t ieee11073_float;
	ieee11073_float = IEEE754_TO_IEEE11073_FLOAT(f_val);
	return (ieee11073_float);
}

#endif /*__BLE_UTILS_H__*/