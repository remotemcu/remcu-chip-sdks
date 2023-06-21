/**
 * \file
 *
 * \brief Top header file for SAMHA0
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
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
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
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

#ifndef _SAMHA0_
#define _SAMHA0_

/**
 * \defgroup SAMHA0_definitions SAMHA0 Device Definitions
 * \brief SAMHA0 CMSIS Definitions.
 */

#if   defined(__SAMHA0E14AB__) || defined(__ATSAMHA0E14AB__)
  #include "samha0e14ab.h"
#elif defined(__SAMHA0E15AB__) || defined(__ATSAMHA0E15AB__)
  #include "samha0e15ab.h"
#elif defined(__SAMHA0E16AB__) || defined(__ATSAMHA0E16AB__)
  #include "samha0e16ab.h"
#elif defined(__SAMHA0G14AB__) || defined(__ATSAMHA0G14AB__)
  #include "samha0g14ab.h"
#elif defined(__SAMHA0G15AB__) || defined(__ATSAMHA0G15AB__)
  #include "samha0g15ab.h"
#elif defined(__SAMHA0G16AB__) || defined(__ATSAMHA0G16AB__)
  #include "samha0g16ab.h"
#else
  #error Library does not support the specified device.
#endif

#endif /* _SAMHA0_ */
