/**
 * \file
 *
 * \brief Top header file for SAMR21
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _SAMR21_
#define _SAMR21_

/**
 * \defgroup SAMR21_definitions SAMR21 Device Definitions
 * \brief SAMR21 CMSIS Definitions.
 */

#if   defined(__SAMR21E16A__) || defined(__ATSAMR21E16A__)
  #include "samr21e16a.h"
#elif defined(__SAMR21E17A__) || defined(__ATSAMR21E17A__)
  #include "samr21e17a.h"
#elif defined(__SAMR21E18A__) || defined(__ATSAMR21E18A__)
  #include "samr21e18a.h"
#elif defined(__SAMR21E19A__) || defined(__ATSAMR21E19A__)
  #include "samr21e19a.h"
#elif defined(__SAMR21G16A__) || defined(__ATSAMR21G16A__)
  #include "samr21g16a.h"
#elif defined(__SAMR21G17A__) || defined(__ATSAMR21G17A__)
  #include "samr21g17a.h"
#elif defined(__SAMR21G18A__) || defined(__ATSAMR21G18A__)
  #include "samr21g18a.h"
#else
  #error Library does not support the specified device.
#endif

#endif /* _SAMR21_ */
