/**
 *
 * \file
 *
 * \brief AES software driver for SAM.
 *
 * This file defines a useful set of functions for the AES on SAM devices.
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

#include "aesa.h"
#include "sysclk.h"
#include "sleepmgr.h"
#include "conf_aesa.h"

/**
 * \internal
 * \brief AES callback function pointer
 */
aes_callback_t aes_callback_pointer;

/**
 * \brief Initializes a AES configuration structure to defaults.
 *
 *  Initializes a given AES configuration structure to a set of
 *  known default values. This function should be called on all new
 *  instances of these configuration structures before being modified by the
 *  user application.
 *
 *  The default configuration is as follows:
 *  - Encryption.
 *  - 128 key size.
 *  - Manual mode.
 *  - ECB mode.
 *  - Countermeasure.
 *
 *  \param cfg    Configuration structure to initialize to default values.
 */
void aes_get_config_defaults(struct aes_config *const cfg)
{
	/* Sanity check arguments */
	Assert(cfg);

	/* Default configuration values */
	cfg->encrypt_mode = AES_ENCRYPTION;
	cfg->key_size = AES_KEY_SIZE_128;
	cfg->dma_mode = AES_MANUAL_MODE;
	cfg->opmode = AES_ECB_MODE;
	cfg->cfb_size = AES_CFB_SIZE_128;
	cfg->countermeasure_mask = AES_COUNTERMEASURE_TYPE_ALL;
}

/**
 * \brief Initialize the AES module.
 *
 * \param dev_inst    Device structure pointer.
 * \param aesa         Base address of the AESA instance.
 * \param cfg         Pointer to AES configuration.
 *
 * \retval true if the initialization was successful.
 * \retval false if initialization failed.
 */
bool aes_init(struct aes_dev_inst *const dev_inst, Aesa *const aesa,
		struct aes_config *const cfg)
{
	/* Sanity check arguments */
	Assert(dev_inst);
	Assert(aesa);
	Assert(cfg);

	dev_inst->hw_dev = aesa;
	dev_inst->aes_cfg = cfg;

	/* Enable APB clock for AES */
	sysclk_enable_peripheral_clock(aesa);

	/* Initialize the AES with new configurations */
	aes_set_config(dev_inst);

	/* Disable APB clock for AES */
	sysclk_disable_peripheral_clock(aesa);

	return true;
}

/**
 * \brief Enable the AES.
 *
 * \param dev_inst Device structure pointer.
 *
 */
void aes_enable(struct aes_dev_inst *const dev_inst)
{
	struct genclk_config gencfg;

	sysclk_enable_peripheral_clock(dev_inst->hw_dev);
	sleepmgr_lock_mode(SLEEPMGR_SLEEP_0);
	dev_inst->hw_dev->AESA_CTRL = AESA_CTRL_ENABLE;
	genclk_config_defaults(&gencfg, AESA_GCLK_NUM);
	genclk_enable_source(CONFIG_AESA_GENERIC_SRC);
	genclk_config_set_source(&gencfg, CONFIG_AESA_GENERIC_SRC);
	genclk_config_set_divider(&gencfg, CONFIG_AESA_GENERIC_DIV);
	genclk_enable(&gencfg, AESA_GCLK_NUM);
}

/**
 * \brief Disable the AES.
 *
 * \param dev_inst Device structure pointer.
 *
 */
void aes_disable(struct aes_dev_inst *const dev_inst)
{
	dev_inst->hw_dev->AESA_CTRL &= ~AESA_CTRL_ENABLE;
	sysclk_disable_peripheral_clock(dev_inst->hw_dev);
	sleepmgr_unlock_mode(SLEEPMGR_SLEEP_0);
}

/**
 * \brief Write the 128/192/256bit cryptographic key.
 *
 * \param  dev_inst Device structure pointer.
 * \param  *p_key Pointer on 4/6/8 contiguous 32bit words.
 *
 * \note The key size depends on the AES configuration.
 *
 */
void aes_write_key(struct aes_dev_inst *const dev_inst,
		const uint32_t *p_key)
{
	uint32_t i, key_length = 0;

	switch ((dev_inst->hw_dev->AESA_MODE & AESA_MODE_KEYSIZE_Msk) >>
			AESA_MODE_KEYSIZE_Pos) {
	case 0: /* 128bit cryptographic key */
		key_length = 4;
		break;

	case 1: /* 192bit cryptographic key */
		key_length = 6;
		break;

	case 2: /* 256bit cryptographic key */
		key_length = 8;
		break;

	default:
		break;
	}

	for (i = 0; i < key_length; i++) {
		dev_inst->hw_dev->AESA_KEY[i].AESA_KEY = *p_key;
		p_key++;
	}
}

/**
 * \brief Write the initialization vector (for the CBC, CFB, OFB & CTR
 * cipher modes)
 *
 * \param  dev_inst Device structure pointer.
 * \param  *p_vector Pointer on 4 contiguous 32bit words.
 *
 */
void aes_write_initvector(struct aes_dev_inst *const dev_inst,
		const uint32_t *p_vector)
{
	uint32_t i;

	for (i = 0; i < 4; i++) {
		dev_inst->hw_dev->AESA_INITVECT[i].AESA_INITVECT = *p_vector;
		p_vector++;
	}
}

/**
 * \brief Set callback for AES
 *
 * \param dev_inst Device structure pointer.
 * \param source Interrupt source.
 * \param callback callback function pointer.
 * \param irq_level interrupt level.
 */
void aes_set_callback(struct aes_dev_inst *const dev_inst,
		aes_interrupt_source_t source, aes_callback_t callback,
		uint8_t irq_level)
{
	aes_callback_pointer = callback;
	irq_register_handler((IRQn_Type)AESA_IRQn, irq_level);
	aes_enable_interrupt(dev_inst, source);
}

/**
 * \brief The AES interrupt handler.
 */
void AESA_Handler(void)
{
	if (aes_callback_pointer) {
		aes_callback_pointer();
	} else {
		Assert(false); /* Catch unexpected interrupt */
	}
}

