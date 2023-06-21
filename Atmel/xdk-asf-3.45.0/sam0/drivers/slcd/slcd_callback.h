/**
 *
 * \file
 *
 * \brief SAM Segment Liquid Crystal Display(SLCD) Controller.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef SLCD_CALLBACK_H_INCLUDED
#define SLCD_CALLBACK_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <compiler.h>
#include <system_interrupt.h>
/**
 * \addtogroup asfdoc_sam0_drivers_slcd_group
 *
 * @{
 */

/**
 * \brief SLCD callback type
 *
 * Enum SLCD callback type. 
 */
enum slcd_callback_type {
	/** Frame Counter 0 Overflow callback */
	SLCD_CALLBACK_FC0_OVERFLOW = 0,
	/** Frame Counter 1 Overflow callback */
	SLCD_CALLBACK_FC1_OVERFLOW,
	/** Frame Counter 2 Overflow callback */
	SLCD_CALLBACK_FC2_OVERFLOW,
	/** VLCD Ready Toggle callback */
	SLCD_CALLBACK_VLCD_READY,
	/** VLCD Status Toggle callback */
	SLCD_CALLBACK_VLCD_TOGGLE,
	/** Pump Run Status Toggle callback */
	SLCD_CALLBACK_PUMP_TOGGLE,
};

/** SLCD interrupt callback function type. */
typedef void (*slcd_callback_t)(enum slcd_callback_type type);

/** \internal Max number of callback type. */
#define SLCD_CALLBACK_TYPE_NUM 6

/** \name Callback Function
 * @{
 */

enum status_code slcd_register_callback(
	const slcd_callback_t callback,
	const enum slcd_callback_type type);

enum status_code slcd_unregister_callback(
	const slcd_callback_t callback,
	const enum slcd_callback_type type);

/**
 * \brief Enable an SLCD callback
 *
 * \param[in] type Callback source type
 *
 * \retval STATUS_OK  The function exited successfully
 * \retval STATUS_ERR_INVALID_ARG  If an invalid callback type was supplied
 */
static inline void slcd_enable_callback(const enum slcd_callback_type type)
{
	if (type < SLCD_CALLBACK_TYPE_NUM){
		SLCD->INTENSET.reg = 1 << type;
	}
}

/**
 * \brief Disable an SLCD callback
 *
 * \param[in]  type Callback source type
 *
 * \retval STATUS_OK  The function exited successfully
 * \retval STATUS_ERR_INVALID_ARG  If an invalid callback type was supplied
 */
static inline void slcd_disable_callback(const enum slcd_callback_type type)
{
	if (type < SLCD_CALLBACK_TYPE_NUM){
		SLCD->INTENCLR.reg = 1 << type;
	}
}

/** @} */

/** @} */
#ifdef __cplusplus
}
#endif

#endif  /* SLCD_CALLBACK_H_INCLUDED */
