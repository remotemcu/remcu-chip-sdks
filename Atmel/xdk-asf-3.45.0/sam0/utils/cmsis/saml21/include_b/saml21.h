/**
 * \file
 *
 * \brief Top header file for SAML21
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

#ifndef _SAML21_
#define _SAML21_

/**
 * \defgroup SAML21_definitions SAML21 Device Definitions
 * \brief SAML21 CMSIS Definitions.
 */

#if   defined(__SAML21E15B__) || defined(__ATSAML21E15B__)
  #include "saml21e15b.h"
#elif defined(__SAML21E16B__) || defined(__ATSAML21E16B__)
  #include "saml21e16b.h"
#elif defined(__SAML21E17B__) || defined(__ATSAML21E17B__)
  #include "saml21e17b.h"
#elif defined(__SAML21E18B__) || defined(__ATSAML21E18B__)
  #include "saml21e18b.h"
#elif defined(__SAML21G16B__) || defined(__ATSAML21G16B__)
  #include "saml21g16b.h"
#elif defined(__SAML21G17B__) || defined(__ATSAML21G17B__)
  #include "saml21g17b.h"
#elif defined(__SAML21G18B__) || defined(__ATSAML21G18B__)
  #include "saml21g18b.h"
#elif defined(__SAML21J16B__) || defined(__ATSAML21J16B__)
  #include "saml21j16b.h"
#elif defined(__SAML21J17B__) || defined(__ATSAML21J17B__)
  #include "saml21j17b.h"
#elif defined(__SAML21J18B__) || defined(__ATSAML21J18B__)
  #include "saml21j18b.h"
#else
  #error Library does not support the specified device.
#endif

#endif /* _SAML21_ */
