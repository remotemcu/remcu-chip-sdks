/**
 * \file
 *
 * \brief Top header file for SAMD11
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

#ifndef _SAMD11_
#define _SAMD11_

/**
 * \defgroup SAMD11_definitions SAMD11 Device Definitions
 * \brief SAMD11 CMSIS Definitions.
 */

#if   defined(__SAMD11C14A__) || defined(__ATSAMD11C14A__)
  #include "samd11c14a.h"
#elif defined(__SAMD11D14AM__) || defined(__ATSAMD11D14AM__)
  #include "samd11d14am.h"
#elif defined(__SAMD11D14AS__) || defined(__ATSAMD11D14AS__)
  #include "samd11d14as.h"
#elif defined(__SAMD11D14AU__) || defined(__ATSAMD11D14AU__)
  #include "samd11d14au.h"
#else
  #error Library does not support the specified device.
#endif

#endif /* _SAMD11_ */
