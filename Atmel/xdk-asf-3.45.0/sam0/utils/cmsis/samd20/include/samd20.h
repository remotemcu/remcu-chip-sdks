/**
 * \file
 *
 * \brief Header file for SAMD20
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _SAMD20_
#define _SAMD20_

/**
 * \defgroup SAMD20_definitions SAMD20 Device Definitions
 * \brief SAMD20 CMSIS Definitions.
 */

#if defined(__SAMD20E14__) || defined(__ATSAMD20E14__)
#include "samd20e14.h"
#elif defined(__SAMD20E15__) || defined(__ATSAMD20E15__)
#include "samd20e15.h"
#elif defined(__SAMD20E16__) || defined(__ATSAMD20E16__)
#include "samd20e16.h"
#elif defined(__SAMD20E17__) || defined(__ATSAMD20E17__)
#include "samd20e17.h"
#elif defined(__SAMD20E18__) || defined(__ATSAMD20E18__)
#include "samd20e18.h"
#elif defined(__SAMD20G14__) || defined(__ATSAMD20G14__)
#include "samd20g14.h"
#elif defined(__SAMD20G15__) || defined(__ATSAMD20G15__)
#include "samd20g15.h"
#elif defined(__SAMD20G16__) || defined(__ATSAMD20G16__)
#include "samd20g16.h"
#elif defined(__SAMD20G17__) || defined(__ATSAMD20G17__)
#include "samd20g17.h"
#elif defined(__SAMD20G17U__) || defined(__ATSAMD20G17U__)
#include "samd20g17u.h"
#elif defined(__SAMD20G18__) || defined(__ATSAMD20G18__)
#include "samd20g18.h"
#elif defined(__SAMD20G18U__) || defined(__ATSAMD20G18U__)
#include "samd20g18u.h"
#elif defined(__SAMD20J14__) || defined(__ATSAMD20J14__)
#include "samd20j14.h"
#elif defined(__SAMD20J15__) || defined(__ATSAMD20J15__)
#include "samd20j15.h"
#elif defined(__SAMD20J16__) || defined(__ATSAMD20J16__)
#include "samd20j16.h"
#elif defined(__SAMD20J17__) || defined(__ATSAMD20J17__)
#include "samd20j17.h"
#elif defined(__SAMD20J18__) || defined(__ATSAMD20J18__)
#include "samd20j18.h"
#elif defined(__SAMD20E14B__) || defined(__ATSAMD20E14B__)
#include "samd20e14b.h"
#elif defined(__SAMD20E15B__) || defined(__ATSAMD20E15B__)
#include "samd20e15b.h"
#elif defined(__SAMD20E16B__) || defined(__ATSAMD20E16B__)
#include "samd20e16b.h"
#elif defined(__SAMD20G14B__) || defined(__ATSAMD20G14B__)
#include "samd20g14b.h"
#elif defined(__SAMD20G15B__) || defined(__ATSAMD20G15B__)
#include "samd20g15b.h"
#elif defined(__SAMD20G16B__) || defined(__ATSAMD20G16B__)
#include "samd20g16b.h"
#elif defined(__SAMD20J14B__) || defined(__ATSAMD20J14B__)
#include "samd20j14b.h"
#elif defined(__SAMD20J15B__) || defined(__ATSAMD20J15B__)
#include "samd20j15b.h"
#elif defined(__SAMD20J16B__) || defined(__ATSAMD20J16B__)
#include "samd20j16b.h"
#else
  #error Library does not support the specified device.
#endif

#endif /* _SAMD20_ */
