/**
 * \file
 *
 * \brief Top header file for SAMR35
 *
 * Copyright (c) 2018 Microchip Technology Inc.
 *
 * \asf_license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the Licence at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \asf_license_stop
 *
 */

#ifndef _SAMR35_
#define _SAMR35_

/**
 * \defgroup SAMR35_definitions SAMR35 Device Definitions
 * \brief SAMR35 CMSIS Definitions.
 */

#if   defined(__SAMR35J16A__) || defined(__ATSAMR35J16A__)
  #include "samr35j16a.h"
#elif defined(__SAMR35J16B__) || defined(__ATSAMR35J16B__)
  #include "samr35j16b.h"
#elif defined(__SAMR35J17A__) || defined(__ATSAMR35J17A__)
  #include "samr35j17a.h"
#elif defined(__SAMR35J17B__) || defined(__ATSAMR35J17B__)
  #include "samr35j17b.h"
#elif defined(__SAMR35J18A__) || defined(__ATSAMR35J18A__)
  #include "samr35j18a.h"
#elif defined(__SAMR35J18B__) || defined(__ATSAMR35J18B__)
  #include "samr35j18b.h"
#else
  #error Library does not support the specified device.
#endif

#endif /* _SAMR35_ */
