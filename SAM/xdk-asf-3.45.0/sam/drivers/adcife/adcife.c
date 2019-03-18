/**
 * \file
 *
 * \brief Analog-to-Digital Converter interface driver for SAM4L.
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

#include "adcife.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \defgroup sam_drivers_adcife_group Analog-to-digital Converter (ADC)
 *
 * See \ref sam_adcife_quickstart.
 *
 * Driver for the Analog-to-digital Converter. This driver provides access to the main
 * features of the ADC controller.
 *
 * @{
 */

adc_callback_t adc_callback_pointer;

/**
 * \brief Initialize the ADC module.
 *
 * \param dev_inst    Device structure pointer.
 * \param adc         Base address of the ADC instance.
 * \param cfg         Pointer to AES configuration.
 *
 * \retval true if the initialization was successful.
 * \retval false if initialization failed.
 */
status_code_t adc_init(struct adc_dev_inst *const dev_inst, Adcife *const adc,
		struct adc_config *const cfg)
{
	/* Sanity check arguments */
	Assert(dev_inst);
	Assert(adc);
	Assert(cfg);

	dev_inst->hw_dev = adc;
	dev_inst->adc_cfg = cfg;

	/* Enable APB clock for ADC */
	sysclk_enable_peripheral_clock(adc);

	/* Initialize the ADC with new configurations */
	adc_set_config(dev_inst, cfg);

	/* Disable APB clock for ADC */
	sysclk_disable_peripheral_clock(adc);

	return STATUS_OK;
}

/**
 * \brief Configure ADC with specified value.
 *
 * \param dev_inst    Device structure pointer.
 * \param cfg         Pointer to ADC configuration.
 *
 */
void adc_set_config(struct adc_dev_inst *const dev_inst,
		struct adc_config *cfg)
{
	/*  Reset the controller. */
	dev_inst->hw_dev->ADCIFE_CR = ADCIFE_CR_SWRST;

	dev_inst->hw_dev->ADCIFE_CFG = ADCIFE_CFG_REFSEL(cfg->refsel) |
			ADCIFE_CFG_SPEED(cfg->speed) |
			ADCIFE_CFG_PRESCAL(cfg->prescal);
	if (cfg->clksel) {
		dev_inst->hw_dev->ADCIFE_CFG |= ADCIFE_CFG_CLKSEL;
	} else {
		genclk_enable_config(ADCIFE_GCLK_NUM, CONFIG_ADC_GENERIC_SRC,
			CONFIG_ADC_GENERIC_DIV);
	}
	dev_inst->hw_dev->ADCIFE_TIM = ADCIFE_TIM_ENSTUP |
			ADCIFE_TIM_STARTUP(cfg->start_up);
}

/**
 * \brief Configure ADC channel with specified value.
 *
 * \param dev_inst    Device structure pointer.
 * \param cfg         Pointer to ADC Channel configuration.
 *
 */
void adc_ch_set_config(struct adc_dev_inst *const dev_inst,
		struct adc_ch_config *cfg)
{
	dev_inst->hw_dev->ADCIFE_SEQCFG =
		(*(uint32_t *)(cfg->seq_cfg));

	adc_configure_wm_mode(dev_inst, cfg->window_mode);
	adc_configure_wm_threshold(dev_inst, cfg->low_threshold,
			cfg->high_threshold);
}

/**
 * \brief Configure ADC sequencer support multi-channel mode.
 *
 * \param cfg   Pointer to ADC multi-channel mode configuration.
 */
void adc_pdca_set_config(struct adc_pdca_config *cfg)
{
	/* Enable PDCA module clock */
	pdca_enable(PDCA);

	/* PDCA channel options */
	pdca_channel_config_t PDCA_TX_CONFIGS = {
		/* memory address */
		.addr = (void *)cfg->cdma_cfg,
		/* select peripheral */
		.pid = ADCIFE_PDCA_ID_TX,
		/* transfer counter */
		.size = cfg->wm == true ? (cfg->nb_channels)*2 : cfg->nb_channels,
		/* next memory address */
		.r_addr = NULL,
		/* next transfer counter */
		.r_size = 0,
		/* select size of the transfer */
		.transfer_size = PDCA_MR_SIZE_WORD
	};
	pdca_channel_config_t PDCA_RX_CONFIGS = {
		/* memory address */
		.addr = (void *)cfg->buffer,
		/* select peripheral */
		.pid = ADCIFE_PDCA_ID_RX,
		/* transfer counter */
		.size = cfg->nb_channels,
		/* next memory address */
		.r_addr = NULL,
		/* next transfer counter */
		.r_size = 0,
		/* select size of the transfer */
		.transfer_size = PDCA_MR_SIZE_HALF_WORD
	};
	/* Init PDCA channel with the pdca_options. */
	pdca_channel_set_config(cfg->pdc_tx_channel, &PDCA_TX_CONFIGS);
	pdca_channel_set_config(cfg->pdc_rx_channel, &PDCA_RX_CONFIGS);
	/* Enable PDCA channel */
	pdca_channel_enable(cfg->pdc_tx_channel);
	pdca_channel_enable(cfg->pdc_rx_channel);
}

/**
 * \brief Enable ADC module.
 *
 * \param dev_inst    Device structure pointer.
 *
 */
status_code_t adc_enable(struct adc_dev_inst *const dev_inst)
{
	uint32_t timeout = ADC_NUM_OF_ATTEMPTS;
	sysclk_enable_peripheral_clock(dev_inst->hw_dev);
	sleepmgr_lock_mode(SLEEPMGR_SLEEP_1);

	dev_inst->hw_dev->ADCIFE_CR = ADCIFE_CR_EN;
	while (!(dev_inst->hw_dev->ADCIFE_SR & ADCIFE_SR_EN)) {
		if (!timeout--) {
			return ERR_TIMEOUT;
		}
	}

	dev_inst->hw_dev->ADCIFE_CR = ADCIFE_CR_REFBUFEN | ADCIFE_CR_BGREQEN;

	return STATUS_OK;
}

/**
 * \brief Disable ADC module.
 *
 * \param dev_inst    Device structure pointer.
 *
 */
void adc_disable(struct adc_dev_inst *const dev_inst)
{
	dev_inst->hw_dev->ADCIFE_CR = ADCIFE_CR_DIS | ADCIFE_CR_REFBUFDIS |
			ADCIFE_CR_BGREQDIS;
	sysclk_disable_peripheral_clock(dev_inst->hw_dev);
	sleepmgr_unlock_mode(SLEEPMGR_SLEEP_1);
}

/**
 * \brief Set callback for ADC
 *
 * \param dev_inst    Device structure pointer.
 * \param source  interrupt source.
 * \param callback callback function pointer.
 * \param irq_line  interrupt line.
 * \param irq_level interrupt level.
 */
void adc_set_callback(struct adc_dev_inst *const dev_inst,
		adc_interrupt_source_t source, adc_callback_t callback,
		uint8_t irq_line, uint8_t irq_level)
{
	adc_callback_pointer = callback;
	irq_register_handler((IRQn_Type) irq_line, irq_level);
	adc_enable_interrupt(dev_inst, source);
}

/**
 * \internal
 * \brief Common ADCIFE interrupt handler
 *
 * The optional callback used by the interrupt handler is set by the
 * adcife_set_callback() function.
 */
static void adc_interrupt(void)
{
	if (adc_callback_pointer) {
		adc_callback_pointer();
	}
}

/**
 * \brief Interrupt handler for ADCIFE interrupt.
 */
void ADCIFE_Handler(void)
{
	adc_interrupt();
}

//@}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
