/**
 * \file
 *
 * \brief Top header file for SAML22
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

#ifndef _SAML22_
#define _SAML22_

/**
 * \defgroup SAML22_definitions SAML22 Device Definitions
 * \brief SAML22 CMSIS Definitions.
 */

#if   defined(__SAML22G16A__) || defined(__ATSAML22G16A__)
  #include "saml22g16a.h"
#elif defined(__SAML22G17A__) || defined(__ATSAML22G17A__)
  #include "saml22g17a.h"
#elif defined(__SAML22G18A__) || defined(__ATSAML22G18A__)
  #include "saml22g18a.h"
#elif defined(__SAML22J16A__) || defined(__ATSAML22J16A__)
  #include "saml22j16a.h"
#elif defined(__SAML22J17A__) || defined(__ATSAML22J17A__)
  #include "saml22j17a.h"
#elif defined(__SAML22J18A__) || defined(__ATSAML22J18A__)
  #include "saml22j18a.h"
#elif defined(__SAML22N16A__) || defined(__ATSAML22N16A__)
  #include "saml22n16a.h"
#elif defined(__SAML22N17A__) || defined(__ATSAML22N17A__)
  #include "saml22n17a.h"
#elif defined(__SAML22N18A__) || defined(__ATSAML22N18A__)
  #include "saml22n18a.h"
#else
  #error Library does not support the specified device.
#endif

#endif /* _SAML22_ */
