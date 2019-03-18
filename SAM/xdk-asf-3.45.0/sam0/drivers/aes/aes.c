/**
 *
 * \file
 *
 * \brief SAM Advanced Encryption Standard driver.
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

#include <aes.h>
#include <system.h>

/**
 * \brief Initializes an AES configuration structure to defaults.
 *
 * Initializes the specified AES configuration structure to a set of
 * known default values.
 *
 * \note This function should be called to initialize <b>all</b> new instances of
 * AES configuration structures before they are further modified by the user
 * application.
 *
 *  The default configuration is as follows:
 *  - Data encryption
 *  - 128-bit AES key size
 *  - 128-bit cipher feedback size
 *  - Manual start mode
 *  - Electronic Codebook (ECB) mode
 *  - All countermeasures are enabled
 *  - XRO key is disabled
 *  - Key generation is disabled
 *  - Last output data mode is disabled
 *
 *  \param[out] config Pointer to an AES configuration structure
 */
void aes_get_config_defaults(
		struct aes_config *const config)
{

	/* Sanity check arguments */
	Assert(config);
	config->encrypt_mode = AES_ENCRYPTION;
	config->key_size = AES_KEY_SIZE_128;
	config->start_mode = AES_MANUAL_START;
	config->opmode= AES_ECB_MODE;
	config->cfb_size = AES_CFB_SIZE_128;
	config->ctype = AES_COUNTERMEASURE_TYPE_ALL;
	config->enable_xor_key = false;
	config->enable_key_gen = false;
	config->lod = false;
}

/**
 * \brief Initialize the AES module.
 *
 * \param[out] module  Pointer to the software instance struct
 * \param[in] hw Module hardware register base address pointer
 * \param[in] config  Pointer to an AES configuration structure
 */
void aes_init(
		struct aes_module *const module,
		Aes *const hw,
		struct aes_config *const config)
{
	/* Sanity check arguments */
	Assert(hw);
	Assert(config);
	Assert(module);

	/* Enable clock for AES */
	system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBC, MCLK_APBCMASK_AES);

	/* Perform a software reset */
	hw->CTRLA.reg = AES_CTRLA_SWRST;

	/* Initialize the AES with new configurations */
	aes_set_config(module,hw, config);
}

/**
 * \brief Enable the AES module.
 *
 * \param[in,out] module  Pointer to the software instance struct
 */
void aes_enable(struct aes_module *const module)
{
	Assert(module);
	Assert(module->hw);
	module->hw->CTRLA.reg |= AES_CTRLA_ENABLE;

}

/**
 * \brief Disable the AES module.
 * \param[in] module  Pointer to the software instance struct
 */
void aes_disable(struct aes_module *const module)
{
	Assert(module);
	Assert(module->hw);

	/* Disbale interrupt */
	module->hw->INTENCLR.reg = AES_INTENCLR_MASK;
	/* Clear interrupt flag */
	module->hw->INTFLAG.reg = AES_INTFLAG_MASK;

	module->hw->CTRLA.reg &= (~AES_CTRLA_ENABLE);
}

/**
 * \brief Configure the AES module.
 *
 * \param[out] module  Pointer to the software instance struct
 * \param[in] hw Module hardware register base address pointer
 * \param[in] config  Pointer to an AES configuration structure
 */
void aes_set_config(
		struct aes_module *const module,
		Aes *const hw,
		struct aes_config *const config)
{
	uint32_t ul_mode = 0;

	/* Validate arguments. */
	Assert(hw);
	Assert(config);
	Assert(module);

	module->opmode = config->opmode;
	module->hw = hw;
	module->key_size = config->key_size;
	module->cfb_size = config->cfb_size;

	ul_mode |= (config->encrypt_mode << AES_CTRLA_CIPHER_Pos)
			 | (config->start_mode << AES_CTRLA_STARTMODE_Pos)
			 | (config->key_size << AES_CTRLA_KEYSIZE_Pos)
			 | (config->opmode << AES_CTRLA_AESMODE_Pos)
			 | (config->cfb_size << AES_CTRLA_CFBS_Pos)
			 | (AES_CTRLA_CTYPE(config->ctype))
			 | (config->enable_xor_key << AES_CTRLA_XORKEY_Pos)
			 | (config->enable_key_gen << AES_CTRLA_KEYGEN_Pos)
			 | (config->lod << AES_CTRLA_LOD_Pos);
	if (hw->CTRLA.reg & AES_CTRLA_ENABLE) {
		aes_disable(module);
		hw->CTRLA.reg = ul_mode;
		aes_enable(module);
	} else {
		hw->CTRLA.reg = ul_mode;
	}
}

/**
 * \brief Write the 128/192/256-bit cryptographic key.
 *
 * \param[in] module  Pointer to the software instance struct
 * \param[in]  key Pointer to 4/6/8 contiguous 32-bit words
 *
 * \note The key size depends on the current AES configuration.
 */
void aes_write_key(
		struct aes_module *const module,
		const uint32_t *key)
{
	uint32_t i, key_length = 0;

	/* Validate arguments. */
	Assert(module);
	Assert(module->hw);
	Assert(key);

	switch (module->key_size) {
	case AES_KEY_SIZE_128:
		key_length = 4;
		break;

	case AES_KEY_SIZE_192:
		key_length = 6;
		break;

	case AES_KEY_SIZE_256:
		key_length = 8;
		break;

	default:
		break;
	}

	for (i = 0; i < key_length; i++) {
		module->hw->KEYWORD[i].reg = *key;
		key++;
	}
}

/**
 * \brief Write the initialization vector (for the CBC, CFB, OFB, CTR, and GCM
 * cipher modes).
 *
 * \param[in] module  Pointer to the software instance struct
 * \param[in] vector Pointer to four contiguous 32-bit words
 */
void aes_write_init_vector(
		struct aes_module *const module,
		const uint32_t *vector)
{
	uint32_t i;

	/* Validate arguments. */
	Assert(module);
	Assert(module->hw);
	Assert(module->opmode != AES_ECB_MODE);

	for (i = 0; i < 4; i++) {
		module->hw->INTVECTV[i].reg = *vector;
		vector++;
	}
}

/**
 * \brief Write the input data (four consecutive 32-bit words).
 *
 * \param[in] module  Pointer to the software instance struct
 * \param[in] input_data_buffer Pointer to an input data buffer
 */
void aes_write_input_data(
		struct aes_module *const module,
		const uint32_t *input_data_buffer)
{
	uint32_t i;

	/* Validate arguments. */
	Assert(module);
	Assert(module->hw);;
	Assert(input_data_buffer);

	module->hw->DATABUFPTR.reg = 0;
	if (module->opmode == AES_CFB_MODE
		&& module->cfb_size == AES_CFB_SIZE_64){
		for (i = 0; i < 2; i++) {
			module->hw->INDATA.reg = *input_data_buffer;
			input_data_buffer++;
		}
	} else if (module->opmode == AES_CFB_MODE
		&& (module->cfb_size == AES_CFB_SIZE_32 || module->cfb_size == AES_CFB_SIZE_16)){
		module->hw->INDATA.reg = *input_data_buffer;
	} else {
		for (i = 0; i < 4; i++) {
			module->hw->INDATA.reg = *input_data_buffer;
			input_data_buffer++;
		}
	}
}

/**
 * \brief Read the output data.
 *
 * \note The data buffer that holds the processed data must be large enough to hold
 * four consecutive 32-bit words.
 *
 * \param[in] module  Pointer to the software instance struct
 * \param[in] output_data_buffer Pointer to an output buffer
 */
void aes_read_output_data(
		struct aes_module *const module,
		uint32_t *output_data_buffer)
{
	uint32_t i;

	/* Validate arguments. */
	Assert(module);
	Assert(module->hw);
	Assert(output_data_buffer);

	module->hw->DATABUFPTR.reg = 0;
	if (module->opmode == AES_CFB_MODE
		&& module->cfb_size == AES_CFB_SIZE_64){
		for (i = 0; i < 2; i++) {
			*output_data_buffer = module->hw->INDATA.reg;
			output_data_buffer++;
		}
	} else if (module->opmode == AES_CFB_MODE
		&& (module->cfb_size == AES_CFB_SIZE_32 || module->cfb_size == AES_CFB_SIZE_16)){
		*output_data_buffer = module->hw->INDATA.reg;
	} else {
		for (i = 0; i < 4; i++) {
			*output_data_buffer = module->hw->INDATA.reg;
			output_data_buffer++;
		}
	}
}
