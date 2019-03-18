/**
 * \file
 *
 * \brief SAM TCC - Timer Counter for Control Applications Callback Driver
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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


#ifndef TCC_CALLBACK_H_INCLUDED
#define TCC_CALLBACK_H_INCLUDED

#include "tcc.h"
#include <system_interrupt.h>

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(__DOXYGEN__)
extern void *_tcc_instances[TCC_INST_NUM];
#endif


/**
 * \name Callback Management
 * {@
 */

enum status_code tcc_register_callback(
		struct tcc_module *const module,
		tcc_callback_t callback_func,
		const enum tcc_callback callback_type);

enum status_code tcc_unregister_callback(
		struct tcc_module *const module,
		const enum tcc_callback callback_type);

void tcc_enable_callback(
		struct tcc_module *const module,
		const enum tcc_callback callback_type);

void tcc_disable_callback(
		struct tcc_module *const module,
		const enum tcc_callback callback_type);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* TCC_CALLBACK_H_INCLUDED */
