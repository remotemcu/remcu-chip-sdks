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

/**
 * \defgroup re200b_pir_sensor_group
 *
 * Low-level driver for the re200b pir sensor. This driver provides access to
 * the main features of the  re200b pir sensor.
 *
 * \{
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "re200b.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/** indicate if there's any comparison event triggered */
volatile uint32_t g_ul_compare_event_flag = false;

/** indicate type of comparison event(CMP_GREATER or CMP_LESS) */
static volatile e_cmp_res g_compare_result = CMP_EQUAL;

/**
 * \brief re200b_motion_detect_handler which allow to know comparison result
 * (CMP_GREATER or CMP_LESS)
 */
void re200b_motion_detect_handler(void)
{
	uint32_t ul_status;

	ul_status = acc_get_interrupt_status(ACC);

	/* Compare Output Interrupt */
	if ((ul_status & ACC_IER_CE) == ACC_IER_CE) {
		g_ul_compare_event_flag = true;

		if (acc_get_comparison_result(ACC)) {
			g_compare_result = CMP_GREATER;
		} else {
			g_compare_result = CMP_LESS;
		}
	}
}

/**
 * \brief Initialize re200b sensor in order to detect motion
 * \param ul_acc_minus ACC minus input, use ACC peripheral definition in header.
 * \param ul_acc_plus ACC plus input, use ACC peripheral definition in header.
 */
void re200b_motion_detect_init(uint32_t ul_acc_minus, uint32_t ul_acc_plus)
{
	pmc_enable_periph_clk(ID_ACC);

	/* Initialize ACC */
	acc_init(ACC, ul_acc_plus, ul_acc_minus, ACC_MR_EDGETYP_ANY, ACC_MR_INV_DIS);

	/* clear status */
	acc_get_interrupt_status(ACC);

	/* reset event flags */
	g_compare_result = CMP_EQUAL;
	g_ul_compare_event_flag = false;
}

/**
 * \brief Reset variable used in re200b sensor functions
 */
void re200b_motion_detect_reset(void)
{
	g_ul_compare_event_flag = false;
	g_compare_result = CMP_EQUAL;
}

/**
 * \brief Enable re200b pir sensor
 */
void re200b_motion_detect_enable(void)
{
	acc_enable(ACC);
	/* Enable compasion interrupt */
	acc_enable_interrupt(ACC);
	/* Enable ACC interrupt */
	NVIC_EnableIRQ(ACC_IRQn);
}

/**
 * \brief Disable re200b pir sensor
 */
void re200b_motion_detect_disable(void)
{
	NVIC_DisableIRQ(ACC_IRQn);
	acc_disable_interrupt(ACC);
	acc_disable(ACC);
}

/**
 * \brief return comparison result
 */
e_cmp_res re200b_motion_detect_get_compare_result(void)
{
	return g_compare_result;
}

/**
 * \brief Allow to know if a motion was detected
 *
 * \return 1 if motion is detected; 0 otherwise
 */
uint32_t re200b_motion_detection(void)
{
	return (g_ul_compare_event_flag && (g_compare_result == CMP_GREATER));
}

#ifdef __cplusplus
}
#endif

/**
 * \}
 */
