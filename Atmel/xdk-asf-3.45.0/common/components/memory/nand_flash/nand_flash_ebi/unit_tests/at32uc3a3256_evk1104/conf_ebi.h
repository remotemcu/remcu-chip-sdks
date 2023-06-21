/*****************************************************************************
 *
 * \file
 *
 * \brief CONF_EBI EBI/SMC driver for AVR32 UC3.
 *
 * \note The values defined in this file are device-specific. See the device
 *       datasheet for further information.
 *
 * Copyright (c) 2009-2018 Microchip Technology Inc. and its subsidiaries.
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
 ******************************************************************************/
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */


#ifndef _CONF_EBI_H_
#define _CONF_EBI_H_

#include "compiler.h"
#include "board.h"

#if (NF_SMC_USE_NCS == 3)
#define  SMC_USE_NCS3
#define  SMC_COMPONENT_CS3          NF_SMC_COMPONENT_CS
#else
#error This board is not supported
#endif

#define EBI_DATA_0                  NF_EBI_DATA_0
#define EBI_DATA_1                  NF_EBI_DATA_1
#define EBI_DATA_2                  NF_EBI_DATA_2
#define EBI_DATA_3                  NF_EBI_DATA_3
#define EBI_DATA_4                  NF_EBI_DATA_4
#define EBI_DATA_5                  NF_EBI_DATA_5
#define EBI_DATA_6                  NF_EBI_DATA_6
#define EBI_DATA_7                  NF_EBI_DATA_7

#define EBI_ADDR_21                 NF_EBI_ADDR_21
#define EBI_ADDR_22                 NF_EBI_ADDR_22

#define EBI_NANDOE                  NF_EBI_NANDOE
#define EBI_NANDWE                  NF_EBI_NANDWE

#endif  // _CONF_EBI_H_
