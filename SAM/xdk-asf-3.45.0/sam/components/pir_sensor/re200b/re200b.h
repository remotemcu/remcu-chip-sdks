/**
 * \file
 *
 * \brief API driver for re200b pir sensor component.
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

#ifndef RE200B_H_INCLUDED
#define RE200B_H_INCLUDED

#include "compiler.h"
#include "board.h"
#include "acc.h"
#include "pmc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * enumeration of different result for acc comparison
 */
typedef enum _e_cmp_res {
	CMP_EQUAL, /*!< equal comparison ( inp=inn) */
	CMP_GREATER, /*!< greater comparison ( inp>inn) */
	CMP_LESS /*!< equal comparison ( inp<inn) */
} e_cmp_res;

void re200b_motion_detect_handler(void);
void re200b_motion_detect_init(uint32_t ul_acc_minus, uint32_t ul_acc_plus);
void re200b_motion_detect_reset(void);
void re200b_motion_detect_enable(void);
void re200b_motion_detect_disable(void);
e_cmp_res re200b_motion_detect_get_compare_result(void);
uint32_t re200b_motion_detection(void);

#ifdef __cplusplus
}
#endif

#endif /* RE200B_H_INCLUDED */
