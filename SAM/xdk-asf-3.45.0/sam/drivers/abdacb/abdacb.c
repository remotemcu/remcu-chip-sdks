/**
 * \file
 *
 * \brief ABDAC driver for SAM.
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

#include "abdacb.h"
#include "sysclk.h"
#include "sleepmgr.h"

/**
 * \internal
 * \brief ABDAC callback function pointer
 */
abdac_callback_t abdac_callback_pointer;

void abdac_get_config_defaults(struct abdac_config *const cfg)
{
	/* Sanity check arguments */
	Assert(cfg);

	/* Default configuration values */
	cfg->sample_rate_hz = ABDAC_SAMPLE_RATE_8000;
	cfg->data_word_format = ABDAC_DATE_16BIT;
	cfg->mono = false;
	cfg->cmoc = false;
}

status_code_t abdac_init(struct abdac_dev_inst *const dev_inst,
		Abdacb *const abdac, struct abdac_config *const cfg)
{
	/* Sanity check arguments */
	Assert(dev_inst);
	Assert(abdac);
	Assert(cfg);

	status_code_t status;

	dev_inst->hw_dev = abdac;
	dev_inst->cfg = cfg;

	/* Enable APB clock for AES */
	sysclk_enable_peripheral_clock(abdac);

	/* Initialize the AES with new configurations */
	status = abdac_set_config(dev_inst);

	/* Disable APB clock for AES */
	sysclk_disable_peripheral_clock(abdac);

	return status;
}

status_code_t abdac_enable(struct abdac_dev_inst *const dev_inst)
{
	uint32_t timeout = 0;

	sysclk_enable_peripheral_clock(dev_inst->hw_dev);
	sleepmgr_lock_mode(SLEEPMGR_ACTIVE);

	/* Enable the module. */
	dev_inst->hw_dev->ABDACB_CR |= ABDACB_CR_EN;

	while((abdac_is_busy(dev_inst)) && (timeout < ABDAC_BUSY_TIMEOUT)) {
		timeout++;
	}

	if (timeout == ABDAC_BUSY_TIMEOUT) {
		return ERR_TIMEOUT;
	}

	return STATUS_OK;

}

status_code_t abdac_disable(struct abdac_dev_inst *const dev_inst)
{
	uint32_t timeout = 0;

	while((abdac_is_busy(dev_inst)) && (timeout < ABDAC_BUSY_TIMEOUT)) {
		timeout++;
	}

	if (timeout == ABDAC_BUSY_TIMEOUT) {
		return ERR_TIMEOUT;
	}

	dev_inst->hw_dev->ABDACB_CR &= ~ABDACB_CR_EN;
	sleepmgr_unlock_mode(SLEEPMGR_ACTIVE);
	sysclk_enable_peripheral_clock(dev_inst->hw_dev);

	return STATUS_OK;
}

status_code_t abdac_set_config(struct abdac_dev_inst *const dev_inst)
{
	struct genclk_config gencfg;
	struct pll_config pcfg;
	uint32_t timeout = 0;

	while((abdac_is_busy(dev_inst)) && (timeout < ABDAC_BUSY_TIMEOUT)) {
		timeout++;
	}

	if (timeout == ABDAC_BUSY_TIMEOUT) {
		return ERR_TIMEOUT;
	}

	/* Set the GCLK according to the sample rate */
	genclk_config_defaults(&gencfg, ABDACB_GCLK_NUM);

	switch (dev_inst->cfg->sample_rate_hz) {
	case ABDAC_SAMPLE_RATE_8000:
		/* PLL0 CLK 64M */
		pll_config_init(&pcfg, PLL_SRC_OSC0, 3, 192000000 /
				BOARD_OSC0_HZ);
		pll_enable(&pcfg, 0);
		pll_wait_for_lock(0);
		/* GCLK 8M */
		genclk_enable_source(GENCLK_SRC_PLL0);
		genclk_config_set_source(&gencfg, GENCLK_SRC_PLL0);
		genclk_config_set_divider(&gencfg, 8);
		break;

	case ABDAC_SAMPLE_RATE_11025:
		/* PLL0 CLK 48M */
		pll_config_init(&pcfg, PLL_SRC_OSC0, 2, 96000000 /
				BOARD_OSC0_HZ);
		pll_enable(&pcfg, 0);
		pll_wait_for_lock(0);
		/* GCLK 12M */
		genclk_enable_source(GENCLK_SRC_PLL0);
		genclk_config_set_source(&gencfg, GENCLK_SRC_PLL0);
		genclk_config_set_divider(&gencfg, 4);
		break;

	case ABDAC_SAMPLE_RATE_12000:
		/* PLL0 CLK 48M */
		pll_config_init(&pcfg, PLL_SRC_OSC0, 2, 96000000 /
				BOARD_OSC0_HZ);
		pll_enable(&pcfg, 0);
		pll_wait_for_lock(0);
		/* GCLK 12M */
		genclk_enable_source(GENCLK_SRC_PLL0);
		genclk_config_set_source(&gencfg, GENCLK_SRC_PLL0);
		genclk_config_set_divider(&gencfg, 4);
		break;

	case ABDAC_SAMPLE_RATE_16000:
		/* PLL0 CLK 64M */
		pll_config_init(&pcfg, PLL_SRC_OSC0, 3, 192000000 /
				BOARD_OSC0_HZ);
		pll_enable(&pcfg, 0);
		pll_wait_for_lock(0);
		/* GCLK 16M */
		genclk_enable_source(GENCLK_SRC_PLL0);
		genclk_config_set_source(&gencfg, GENCLK_SRC_PLL0);
		genclk_config_set_divider(&gencfg, 4);
		break;

	case ABDAC_SAMPLE_RATE_22050:
		/* PLL0 CLK 48M */
		pll_config_init(&pcfg, PLL_SRC_OSC0, 2, 96000000 /
				BOARD_OSC0_HZ);
		pll_enable(&pcfg, 0);
		pll_wait_for_lock(0);
		/* GCLK 24M */
		genclk_enable_source(GENCLK_SRC_PLL0);
		genclk_config_set_source(&gencfg, GENCLK_SRC_PLL0);
		genclk_config_set_divider(&gencfg, 2);
		break;

	case ABDAC_SAMPLE_RATE_24000:
		/* PLL0 CLK 48M */
		pll_config_init(&pcfg, PLL_SRC_OSC0, 2, 96000000 /
				BOARD_OSC0_HZ);
		pll_enable(&pcfg, 0);
		pll_wait_for_lock(0);
		/* GCLK 24M */
		genclk_enable_source(GENCLK_SRC_PLL0);
		genclk_config_set_source(&gencfg, GENCLK_SRC_PLL0);
		genclk_config_set_divider(&gencfg, 2);
		break;

	case ABDAC_SAMPLE_RATE_32000:
		/* PLL0 CLK 64M */
		pll_config_init(&pcfg, PLL_SRC_OSC0, 3, 192000000 /
				BOARD_OSC0_HZ);
		pll_enable(&pcfg, 0);
		pll_wait_for_lock(0);
		/* GCLK 32M */
		genclk_enable_source(GENCLK_SRC_PLL0);
		genclk_config_set_source(&gencfg, GENCLK_SRC_PLL0);
		genclk_config_set_divider(&gencfg, 1);
		break;

	case ABDAC_SAMPLE_RATE_44100:
		/* PLL0 CLK 48M */
		pll_config_init(&pcfg, PLL_SRC_OSC0, 2, 96000000 /
				BOARD_OSC0_HZ);
		pll_enable(&pcfg, 0);
		pll_wait_for_lock(0);
		/* GCLK 48M */
		genclk_enable_source(GENCLK_SRC_PLL0);
		genclk_config_set_source(&gencfg, GENCLK_SRC_PLL0);
		genclk_config_set_divider(&gencfg, 1);
		break;

	case ABDAC_SAMPLE_RATE_48000:
		/* PLL0 CLK 48M */
		pll_config_init(&pcfg, PLL_SRC_OSC0, 2, 96000000 /
				BOARD_OSC0_HZ);
		pll_enable(&pcfg, 0);
		pll_wait_for_lock(0);
		/* GCLK 48M */
		genclk_enable_source(GENCLK_SRC_PLL0);
		genclk_config_set_source(&gencfg, GENCLK_SRC_PLL0);
		genclk_config_set_divider(&gencfg, 1);
		break;

	default:
		break;
	}

	genclk_enable(&gencfg, ABDACB_GCLK_NUM);

	/* Set the sampling rate related settings */
	dev_inst->hw_dev->ABDACB_CR |=
			ABDACB_CR_FS(dev_inst->cfg->sample_rate_hz) |
			ABDACB_CR_ALTUPR;

	/* Set the data word format */
	dev_inst->hw_dev->ABDACB_CR |=
			ABDACB_CR_DATAFORMAT(dev_inst->cfg->data_word_format);

	/* Set the mono mode */
	if (dev_inst->cfg->mono) {
		dev_inst->hw_dev->ABDACB_CR |= ABDACB_CR_MONO;
	} else {
		dev_inst->hw_dev->ABDACB_CR &= ~ABDACB_CR_MONO;
	}

	/* Set the common mode offset */
	if (dev_inst->cfg->cmoc) {
		dev_inst->hw_dev->ABDACB_CR |= ABDACB_CR_CMOC;
	} else {
		dev_inst->hw_dev->ABDACB_CR &= ~ABDACB_CR_CMOC;
	}

	timeout = 0;

	while((abdac_is_busy(dev_inst)) && (timeout < ABDAC_BUSY_TIMEOUT)) {
		timeout++;
	}

	if (timeout == ABDAC_BUSY_TIMEOUT) {
		return ERR_TIMEOUT;
	}

	return STATUS_OK;
}

status_code_t abdac_sw_reset(struct abdac_dev_inst *const dev_inst)
{
	uint32_t timeout = 0;

	while((abdac_is_busy(dev_inst)) && (timeout < ABDAC_BUSY_TIMEOUT)) {
		timeout++;
	}

	if (timeout == ABDAC_BUSY_TIMEOUT) {
		return ERR_TIMEOUT;
	}

	dev_inst->hw_dev->ABDACB_CR |= ABDACB_CR_SWRST;

	return STATUS_OK;
}

status_code_t abdac_swap_channels(struct abdac_dev_inst *const dev_inst)
{
	uint32_t timeout = 0;

	while((abdac_is_busy(dev_inst)) && (timeout < ABDAC_BUSY_TIMEOUT)) {
		timeout++;
	}

	if (timeout == ABDAC_BUSY_TIMEOUT) {
		return ERR_TIMEOUT;
	}

	if (dev_inst->hw_dev->ABDACB_CR & ABDACB_CR_SWAP) {
		dev_inst->hw_dev->ABDACB_CR &= ~ABDACB_CR_SWAP;
	} else {
		dev_inst->hw_dev->ABDACB_CR |= ABDACB_CR_SWAP;
	}

	return STATUS_OK;
}

status_code_t abdac_write_data0(struct abdac_dev_inst *const dev_inst,
		uint32_t data)
{
	uint32_t timeout = 0;

	while((abdac_is_busy(dev_inst)) && (timeout < ABDAC_BUSY_TIMEOUT)) {
		timeout++;
	}

	if (timeout == ABDAC_BUSY_TIMEOUT) {
		return ERR_TIMEOUT;
	}

	timeout = 0;

	while((!abdac_is_tx_ready(dev_inst)) && (timeout < ABDAC_BUSY_TIMEOUT)) {
		timeout++;
	}

	if (timeout == ABDAC_BUSY_TIMEOUT) {
		return ERR_TIMEOUT;
	}

	dev_inst->hw_dev->ABDACB_SDR0 = data;

	return STATUS_OK;
}

status_code_t abdac_write_data1(struct abdac_dev_inst *const dev_inst,
		uint32_t data)
{
	uint32_t timeout = 0;

	while((abdac_is_busy(dev_inst)) && (timeout < ABDAC_BUSY_TIMEOUT)) {
		timeout++;
	}

	if (timeout == ABDAC_BUSY_TIMEOUT) {
		return ERR_TIMEOUT;
	}

	timeout = 0;

	while((!abdac_is_tx_ready(dev_inst)) && (timeout < ABDAC_BUSY_TIMEOUT)) {
		timeout++;
	}

	if (timeout == ABDAC_BUSY_TIMEOUT) {
		return ERR_TIMEOUT;
	}

	dev_inst->hw_dev->ABDACB_SDR1 = data;

	return STATUS_OK;
}

void abdac_set_volume0(struct abdac_dev_inst *const dev_inst, bool mute,
		uint32_t volume)
{
	if (mute) {
		dev_inst->hw_dev->ABDACB_VCR0 = ABDACB_VCR0_MUTE
				| ABDACB_VCR0_VOLUME(volume);
	} else {
		dev_inst->hw_dev->ABDACB_VCR0 = ABDACB_VCR0_VOLUME(volume);
	}
}

void abdac_set_volume1(struct abdac_dev_inst *const dev_inst, bool mute,
		uint32_t volume)
{
	if (mute) {
		dev_inst->hw_dev->ABDACB_VCR1 = ABDACB_VCR1_MUTE
				| ABDACB_VCR1_VOLUME(volume);
	} else {
		dev_inst->hw_dev->ABDACB_VCR1 = ABDACB_VCR1_VOLUME(volume);
	}
}

void abdac_enable_interrupt(struct abdac_dev_inst *const dev_inst,
		abdac_interrupt_source_t source)
{
	switch (source) {
	case ABDAC_INTERRUPT_TXRDY:
		dev_inst->hw_dev->ABDACB_IER = ABDACB_IER_TXRDY;
		break;

	case ABDAC_INTERRUPT_TXUR:
		dev_inst->hw_dev->ABDACB_IER = ABDACB_IER_TXUR;
		break;

	default:
		break;
	}
}

void abdac_disable_interrupt(struct abdac_dev_inst *const dev_inst,
		abdac_interrupt_source_t source)
{
	switch (source) {
	case ABDAC_INTERRUPT_TXRDY:
		dev_inst->hw_dev->ABDACB_IDR = ABDACB_IDR_TXRDY;
		break;

	case ABDAC_INTERRUPT_TXUR:
		dev_inst->hw_dev->ABDACB_IDR = ABDACB_IDR_TXUR;
		break;

	default:
		break;
	}
}

void abdac_clear_interrupt_flag(struct abdac_dev_inst *const dev_inst,
		abdac_interrupt_source_t source)
{
	switch (source) {
	case ABDAC_INTERRUPT_TXRDY:
		dev_inst->hw_dev->ABDACB_SCR = ABDACB_SCR_TXRDY;
		break;

	case ABDAC_INTERRUPT_TXUR:
		dev_inst->hw_dev->ABDACB_SCR = ABDACB_SCR_TXUR;
		break;

	default:
		break;
	}
}

void abdac_set_callback(struct abdac_dev_inst *const dev_inst,
		abdac_interrupt_source_t source, abdac_callback_t callback,
		uint8_t irq_level)
{
	abdac_callback_pointer = callback;
	irq_register_handler((IRQn_Type)ABDACB_IRQn, irq_level);
	abdac_enable_interrupt(dev_inst, source);
}

/**
 * \brief The ABDACB interrupt handler.
 */
void ABDACB_Handler(void)
{
	if (abdac_callback_pointer) {
		abdac_callback_pointer();
	} else {
		Assert(false); /* Catch unexpected interrupt */
	}
}

