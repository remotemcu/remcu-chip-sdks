/**
 * \file
 *
 * \brief Top header file for SAMC20
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

#ifndef _SAMC20_
#define _SAMC20_

/**
 * \defgroup SAMC20_definitions SAMC20 Device Definitions
 * \brief SAMC20 CMSIS Definitions.
 */

#if   defined(__SAMC20E15A__) || defined(__ATSAMC20E15A__)
  #include "samc20e15a.h"
#elif defined(__SAMC20E16A__) || defined(__ATSAMC20E16A__)
  #include "samc20e16a.h"
#elif defined(__SAMC20E17A__) || defined(__ATSAMC20E17A__)
  #include "samc20e17a.h"
#elif defined(__SAMC20E18A__) || defined(__ATSAMC20E18A__)
  #include "samc20e18a.h"
#elif defined(__SAMC20G15A__) || defined(__ATSAMC20G15A__)
  #include "samc20g15a.h"
#elif defined(__SAMC20G16A__) || defined(__ATSAMC20G16A__)
  #include "samc20g16a.h"
#elif defined(__SAMC20G17A__) || defined(__ATSAMC20G17A__)
  #include "samc20g17a.h"
#elif defined(__SAMC20G18A__) || defined(__ATSAMC20G18A__)
  #include "samc20g18a.h"
#elif defined(__SAMC20J15A__) || defined(__ATSAMC20J15A__)
  #include "samc20j15a.h"
#elif defined(__SAMC20J15AU__) || defined(__ATSAMC20J15AU__)
  #include "samc20j15au.h"
#elif defined(__SAMC20J16A__) || defined(__ATSAMC20J16A__)
  #include "samc20j16a.h"
#elif defined(__SAMC20J16AU__) || defined(__ATSAMC20J16AU__)
  #include "samc20j16au.h"
#elif defined(__SAMC20J17A__) || defined(__ATSAMC20J17A__)
  #include "samc20j17a.h"
#elif defined(__SAMC20J17AU__) || defined(__ATSAMC20J17AU__)
  #include "samc20j17au.h"
#elif defined(__SAMC20J18A__) || defined(__ATSAMC20J18A__)
  #include "samc20j18a.h"
#elif defined(__SAMC20J18AU__) || defined(__ATSAMC20J18AU__)
  #include "samc20j18au.h"
#else
  #error Library does not support the specified device.
#endif

#endif /* _SAMC20_ */
