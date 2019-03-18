/**
 * \file
 *
 * \brief Top header file for SAMHA1
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

#ifndef _SAMHA1_
#define _SAMHA1_

/**
 * \defgroup SAMHA1_definitions SAMHA1 Device Definitions
 * \brief SAMHA1 CMSIS Definitions.
 */

#if   defined(__SAMHA1E14A__) || defined(__ATSAMHA1E14A__)
  #include "samha1e14a.h"
#elif defined(__SAMHA1E15A__) || defined(__ATSAMHA1E15A__)
  #include "samha1e15a.h"
#elif defined(__SAMHA1E16A__) || defined(__ATSAMHA1E16A__)
  #include "samha1e16a.h"
#elif defined(__SAMHA1E14AB__) || defined(__ATSAMHA1E14AB__)
  #include "samha1e14ab.h"
#elif defined(__SAMHA1E15AB__) || defined(__ATSAMHA1E15AB__)
  #include "samha1e15ab.h"
#elif defined(__SAMHA1E16AB__) || defined(__ATSAMHA1E16AB__)
  #include "samha1e16ab.h"
#elif defined(__SAMHA1G14A__) || defined(__ATSAMHA1G14A__)
  #include "samha1g14a.h"
#elif defined(__SAMHA1G15A__) || defined(__ATSAMHA1G15A__)
  #include "samha1g15a.h"
#elif defined(__SAMHA1G16A__) || defined(__ATSAMHA1G16A__)
  #include "samha1g16a.h"
#elif defined(__SAMHA1G14AB__) || defined(__ATSAMHA1G14AB__)
  #include "samha1g14ab.h"
#elif defined(__SAMHA1G15AB__) || defined(__ATSAMHA1G15AB__)
  #include "samha1g15ab.h"
#elif defined(__SAMHA1G16AB__) || defined(__ATSAMHA1G16AB__)
  #include "samha1g16ab.h"
#else
  #error Library does not support the specified device.
#endif

#endif /* _SAMHA1_ */
