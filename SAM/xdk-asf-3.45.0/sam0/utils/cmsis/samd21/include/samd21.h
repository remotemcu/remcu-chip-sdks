/**
 * \file
 *
 * \brief Top header file for SAMD21
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _SAMD21_
#define _SAMD21_

/**
 * \defgroup SAMD21_definitions SAMD21 Device Definitions
 * \brief SAMD21 CMSIS Definitions.
 */

#if   defined(__SAMD21E15A__) || defined(__ATSAMD21E15A__)
  #include "samd21e15a.h"
#elif defined(__SAMD21E16A__) || defined(__ATSAMD21E16A__)
  #include "samd21e16a.h"
#elif defined(__SAMD21E17A__) || defined(__ATSAMD21E17A__)
  #include "samd21e17a.h"
#elif defined(__SAMD21E18A__) || defined(__ATSAMD21E18A__)
  #include "samd21e18a.h"
#elif defined(__SAMD21G15A__) || defined(__ATSAMD21G15A__)
  #include "samd21g15a.h"
#elif defined(__SAMD21G16A__) || defined(__ATSAMD21G16A__)
  #include "samd21g16a.h"
#elif defined(__SAMD21G17A__) || defined(__ATSAMD21G17A__)
  #include "samd21g17a.h"
#elif defined(__SAMD21G17AU__) || defined(__ATSAMD21G17AU__)
  #include "samd21g17au.h"
#elif defined(__SAMD21G18A__) || defined(__ATSAMD21G18A__)
  #include "samd21g18a.h"
#elif defined (__SAMD21G18AU__) || defined(__ATSAMD21G18AU__)
  #include "samd21g18au.h"
#elif defined(__SAMD21J15A__) || defined(__ATSAMD21J15A__)
  #include "samd21j15a.h"
#elif defined(__SAMD21J16A__) || defined(__ATSAMD21J16A__)
  #include "samd21j16a.h"
#elif defined(__SAMD21J17A__) || defined(__ATSAMD21J17A__)
  #include "samd21j17a.h"
#elif defined(__SAMD21J18A__) || defined(__ATSAMD21J18A__)
  #include "samd21j18a.h"
#elif defined(__SAMD21E15B__) || defined(__ATSAMD21E15B__)
  #include "samd21e15b.h"
#elif defined(__SAMD21E15BU__) || defined(__ATSAMD21E15BU__)
  #include "samd21e15bu.h"
#elif defined(__SAMD21E15L__) || defined(__ATSAMD21E15L__)
  #include "samd21e15l.h"
#elif defined(__SAMD21E16B__) || defined(__ATSAMD21E16B__)
  #include "samd21e16b.h"
#elif defined(__SAMD21E16BU__) || defined(__ATSAMD21E16BU__)
  #include "samd21e16bu.h"
#elif defined(__SAMD21E16L__) || defined(__ATSAMD21E16L__)
  #include "samd21e16l.h"
#elif defined(__SAMD21G15B__) || defined(__ATSAMD21G15B__)
  #include "samd21g15b.h"
#elif defined(__SAMD21G15L__) || defined(__ATSAMD21G15L__)
  #include "samd21g15l.h"
#elif defined(__SAMD21G16B__) || defined(__ATSAMD21G16B__)
  #include "samd21g16b.h"
#elif defined(__SAMD21G16L__) || defined(__ATSAMD21G16L__)
  #include "samd21g16l.h"
#elif defined(__SAMD21J15B__) || defined(__ATSAMD21J15B__)
  #include "samd21j15b.h"
#elif defined(__SAMD21J16B__) || defined(__ATSAMD21J16B__)
  #include "samd21j16b.h"
#elif defined(__SAMD21E17D__) || defined(__ATSAMD21E17D__)
  #include "samd21e17d.h"
#elif defined(__SAMD21E17DU__) || defined(__ATSAMD21E17DU__)
  #include "samd21e17du.h"
#elif defined(__SAMD21E17L__) || defined(__ATSAMD21E17L__)
  #include "samd21e17l.h"
#elif defined(__SAMD21G17D__) || defined(__ATSAMD21G17D__)
  #include "samd21g17d.h"
#elif defined(__SAMD21G17L__) || defined(__ATSAMD21G17L__)
  #include "samd21g17l.h"
#elif defined(__SAMD21J17D__) || defined(__ATSAMD21J17D__)
  #include "samd21j17d.h"
#else
  #error Library does not support the specified device.
#endif

#endif /* _SAMD21_ */
