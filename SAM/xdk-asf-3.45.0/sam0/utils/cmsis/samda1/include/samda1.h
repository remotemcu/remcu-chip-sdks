/**
 * \file
 *
 * \brief Top header file for SAMDA1
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

#ifndef _SAMDA1_
#define _SAMDA1_

/**
 * \defgroup SAMDA1_definitions SAMDA1 Device Definitions
 * \brief SAMDA1 CMSIS Definitions.
 */

#if   defined(__SAMDA1E14A__) || defined(__ATSAMDA1E14A__)
  #include "samda1e14a.h"
#elif defined(__SAMDA1E15A__) || defined(__ATSAMDA1E15A__)
  #include "samda1e15a.h"
#elif defined(__SAMDA1E16A__) || defined(__ATSAMDA1E16A__)
  #include "samda1e16a.h"
#elif defined(__SAMDA1G14A__) || defined(__ATSAMDA1G14A__)
  #include "samda1g14a.h"
#elif defined(__SAMDA1G15A__) || defined(__ATSAMDA1G15A__)
  #include "samda1g15a.h"
#elif defined(__SAMDA1G16A__) || defined(__ATSAMDA1G16A__)
  #include "samda1g16a.h"
#elif defined(__SAMDA1J14A__) || defined(__ATSAMDA1J14A__)
  #include "samda1j14a.h"
#elif defined(__SAMDA1J15A__) || defined(__ATSAMDA1J15A__)
  #include "samda1j15a.h"
#elif defined(__SAMDA1J16A__) || defined(__ATSAMDA1J16A__)
  #include "samda1j16a.h"
#elif defined(__SAMDA1E14B__) || defined(__ATSAMDA1E14B__)
  #include "samda1e14b.h"
#elif defined(__SAMDA1E15B__) || defined(__ATSAMDA1E15B__)
  #include "samda1e15b.h"
#elif defined(__SAMDA1E16B__) || defined(__ATSAMDA1E16B__)
  #include "samda1e16b.h"
#elif defined(__SAMDA1G14B__) || defined(__ATSAMDA1G14B__)
  #include "samda1g14b.h"
#elif defined(__SAMDA1G15B__) || defined(__ATSAMDA1G15B__)
  #include "samda1g15b.h"
#elif defined(__SAMDA1G16B__) || defined(__ATSAMDA1G16B__)
  #include "samda1g16b.h"
#elif defined(__SAMDA1J14B__) || defined(__ATSAMDA1J14B__)
  #include "samda1j14b.h"
#elif defined(__SAMDA1J15B__) || defined(__ATSAMDA1J15B__)
  #include "samda1j15b.h"
#elif defined(__SAMDA1J16B__) || defined(__ATSAMDA1J16B__)
  #include "samda1j16b.h"
#else
  #error Library does not support the specified device.
#endif

#endif /* _SAMDA1_ */
