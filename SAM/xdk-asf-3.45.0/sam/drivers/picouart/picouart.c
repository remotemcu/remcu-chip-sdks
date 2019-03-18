/**
 * \file
 *
 * \brief PICOUART driver for SAM.
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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

#include "picouart.h"
#include "sysclk.h"
#include "sleepmgr.h"

/* define the source mode */
#define SOURCE_NONE 0
#define SOURCE_START_BIT_MODE 1
#define SOURCE_FULL_FRAME_MODE 2
#define SOURCE_CHARACTER_MATCH_MODE 3

void picouart_get_config_defaults(struct picouart_config *config)
{
	config->action = PICOUART_ACTION_WAKEUP_ON_FULLFRAME;
	config->match = 0;
}

status_code_t picouart_init(struct picouart_dev_inst *const dev_inst, 
		Picouart *hw_dev, struct picouart_config *config)
{
	dev_inst->dev_ptr = hw_dev;

	return picouart_set_config(dev_inst, config);
}

status_code_t picouart_set_config(struct picouart_dev_inst *const dev_inst,
		struct picouart_config *config)
{
	if(PM->PM_PBDMASK & (1 << SYSCLK_PICOUART)) {
		dev_inst->dev_ptr->PICOUART_CFG = config->action
					| PICOUART_CFG_MATCH(config->match);
	} else {
		sysclk_enable_peripheral_clock(dev_inst->dev_ptr);
		dev_inst->dev_ptr->PICOUART_CFG = config->action
					| PICOUART_CFG_MATCH(config->match);
		sysclk_disable_peripheral_clock(dev_inst->dev_ptr);
	}
	return STATUS_OK;
}

void picouart_enable(struct picouart_dev_inst *const dev_inst)
{
	sysclk_enable_peripheral_clock(PICOUART);
	sleepmgr_lock_mode(SLEEPMGR_BACKUP);
	dev_inst->dev_ptr->PICOUART_CR = PICOUART_CR_EN;
}

void picouart_disable(struct picouart_dev_inst *const dev_inst)
{
	dev_inst->dev_ptr->PICOUART_CR = PICOUART_CR_DIS;
	sysclk_disable_peripheral_clock(PICOUART);
	sleepmgr_unlock_mode(SLEEPMGR_BACKUP);
}

bool picouart_is_enabled(struct picouart_dev_inst *const dev_inst)
{
	return (dev_inst->dev_ptr->PICOUART_SR & PICOUART_SR_EN);
}

bool picouart_is_data_ready(struct picouart_dev_inst *const dev_inst)
{
	return (dev_inst->dev_ptr->PICOUART_SR & PICOUART_SR_DRDY);
}

status_code_t picouart_read(struct picouart_dev_inst *const dev_inst, 
	uint8_t *result)
{
	*result = dev_inst->dev_ptr->PICOUART_RHR;

	return STATUS_OK;
}

