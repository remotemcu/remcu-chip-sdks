/**
 * \file
 *
 * \brief HMATRIX driver for SAM.
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

#include "hmatrixb.h"
#include "sysclk.h"
#include "sleepmgr.h"

/**
 * \defgroup sam_drivers_hmatrix_group HSB BUS Matrix (HMATRIX)
 *
 * \par Purpose
 *
 * The HSB Bus Matrix implements a multi-layer bus structure that enables
 * parallel access paths between multiple High Speed Bus (HSB) masters and
 * slaves in a system, which increases the overall bandwidth.
 *
 * @{
 */

void hmatrix_init(void)
{
	sysclk_enable_peripheral_clock(HMATRIX);
}

void hmatrix_enable(void)
{
	sysclk_enable_peripheral_clock(HMATRIX);
	sleepmgr_lock_mode(SLEEPMGR_SLEEP_1);
}

void hmatrix_disable(void)
{
	sysclk_disable_peripheral_clock(HMATRIX);
	sleepmgr_unlock_mode(SLEEPMGR_SLEEP_1);
}

void hmatrix_master_ch_set_config(const enum hmatrix_master_id master_id,
		struct hmatrix_master_ch_conf *const config)
{
	Hmatrixb *p_hmatrixb = HMATRIX;
	p_hmatrixb->HMATRIXB_MCFG[master_id].HMATRIXB_MCFG
			= config->burst_type;
}

void hmatrix_slave_ch_set_config(const enum hmatrix_slave_id slave_id,
		struct hmatrix_slave_ch_conf *const config)
{
	Hmatrixb *p_hmatrixb = HMATRIX;
	p_hmatrixb->HMATRIXB_SCFG[slave_id].HMATRIXB_SCFG
			= config->arbitration_type |
			HMATRIXB_SCFG_FIXED_DEFMSTR(config->fixed_def_master_number) |
			config->def_master_type |
			HMATRIXB_SCFG_SLOT_CYCLE(config->slot_cycle);
}

void hmatrix_set_slave_priority(enum hmatrix_slave_id slave_id,
		hmatrix_prs *p_prio)
{
	Hmatrixb *p_hmatrixb = HMATRIX;

	p_hmatrixb->HMATRIXB_PRS[slave_id].HMATRIXB_PRAS = p_prio->HMATRIXB_PRAS;
	p_hmatrixb->HMATRIXB_PRS[slave_id].HMATRIXB_PRBS = p_prio->HMATRIXB_PRBS;
}

void hmatrix_get_slave_priority(enum hmatrix_slave_id slave_id,
		hmatrix_prs *p_prio)
{
	Hmatrixb *p_hmatrixb = HMATRIX;

	p_prio->HMATRIXB_PRAS = p_hmatrixb->HMATRIXB_PRS[slave_id].HMATRIXB_PRAS;
	p_prio->HMATRIXB_PRBS = p_hmatrixb->HMATRIXB_PRS[slave_id].HMATRIXB_PRBS;
}

/* @} */
