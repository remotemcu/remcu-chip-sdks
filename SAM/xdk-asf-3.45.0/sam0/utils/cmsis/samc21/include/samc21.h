/**
 * \file
 *
 * \brief Top header file for SAMC21
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

#ifndef _SAMC21_
#define _SAMC21_

/**
 * \defgroup SAMC21_definitions SAMC21 Device Definitions
 * \brief SAMC21 CMSIS Definitions.
 */

#if   defined(__SAMC21E15A__) || defined(__ATSAMC21E15A__)
  #include "samc21e15a.h"
#elif defined(__SAMC21E16A__) || defined(__ATSAMC21E16A__)
  #include "samc21e16a.h"
#elif defined(__SAMC21E17A__) || defined(__ATSAMC21E17A__)
  #include "samc21e17a.h"
#elif defined(__SAMC21E18A__) || defined(__ATSAMC21E18A__)
  #include "samc21e18a.h"
#elif defined(__SAMC21G15A__) || defined(__ATSAMC21G15A__)
  #include "samc21g15a.h"
#elif defined(__SAMC21G16A__) || defined(__ATSAMC21G16A__)
  #include "samc21g16a.h"
#elif defined(__SAMC21G17A__) || defined(__ATSAMC21G17A__)
  #include "samc21g17a.h"
#elif defined(__SAMC21G18A__) || defined(__ATSAMC21G18A__)
  #include "samc21g18a.h"
#elif defined(__SAMC21J15A__) || defined(__ATSAMC21J15A__)
  #include "samc21j15a.h"
#elif defined(__SAMC21J16A__) || defined(__ATSAMC21J16A__)
  #include "samc21j16a.h"
#elif defined(__SAMC21J17A__) || defined(__ATSAMC21J17A__)
  #include "samc21j17a.h"
#elif defined(__SAMC21J18A__) || defined(__ATSAMC21J18A__)
  #include "samc21j18a.h"
#else
  #error Library does not support the specified device.
#endif

#endif /* _SAMC21_ */
