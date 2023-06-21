/**
 * \file
 *
 * \brief SAM4L Liquid Crystal Display driver (LCDCA).
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

#include <lcdca.h>
#include <sysclk.h>
#include <sleepmgr.h>

/** \internal LCDCA callback function pointer. */
lcdca_callback_t lcdca_callback_pointer = NULL;

/**
 * \brief LCDCA clock initialization.
 */
void lcdca_clk_init(void)
{
	/* Enable APB clock for LCDCA */
	sysclk_enable_peripheral_clock(LCDCA);

	/* Switch LCD input to selected source clock */
#if (CONF_LCDCA_SOURCE_CLK == OSC_ID_OSC32)
	if (!osc_is_ready(OSC_ID_OSC32)) {
		osc_enable(OSC_ID_OSC32);
		osc_wait_ready(OSC_ID_OSC32);
	}
	bpm_set_clk32_source(BPM, BPM_CLK32_SOURCE_OSC32K);
#else
	if (!osc_is_ready(OSC_ID_RC32K)) {
		osc_enable(OSC_ID_RC32K);
		osc_wait_ready(OSC_ID_RC32K);
	}
	bpm_set_clk32_source(BPM, BPM_CLK32_SOURCE_RC32K);
#endif
}

/**
 * \brief Configure the LCDCA controller.
 *
 * \param[in] lcdca_cfg Pointer to an LCDCA configuration structure
 */
void lcdca_set_config(
		struct lcdca_config *lcdca_cfg)
{
	/* Validate parameters. */
	Assert(lcdca_cfg);
	
	/* Disable LCD controller and frame counter timer */
	LCDCA->LCDCA_CR = LCDCA_CR_DIS | LCDCA_CR_FC0DIS | LCDCA_CR_FC1DIS |
		LCDCA_CR_FC2DIS;
	/* Set new timer */
	LCDCA->LCDCA_TIM = LCDCA_TIM_FC2(lcdca_cfg->fc2) |
			LCDCA_TIM_FC1(lcdca_cfg->fc1) |
			LCDCA_TIM_FC0(lcdca_cfg->fc0) |
			LCDCA_TIM_CLKDIV(lcdca_cfg->lcd_clkdiv) |
			(uint32_t)lcdca_cfg->lcd_pres;

	/* Set basic configuration */
	LCDCA->LCDCA_CFG = LCDCA_CFG_NSU(lcdca_cfg->port_mask) |
			(lcdca_cfg->x_bias ? LCDCA_CFG_XBIAS : 0) |
			(lcdca_cfg->lp_wave ? 0 : LCDCA_CFG_WMOD) |
			LCDCA_CFG_DUTY(lcdca_cfg->duty_type);

	/* Set contrast */
	lcdca_set_contrast(lcdca_cfg->contrast);
}

/**
 * \brief Enable the LCDCA module.
 */
void lcdca_enable(void)
{
	sleepmgr_lock_mode(SLEEPMGR_RET);
	/* Enable all display memory */
	LCDCA->LCDCA_CFG &= ~LCDCA_CFG_BLANK;
	LCDCA->LCDCA_CR = LCDCA_CR_EN;
	/* Clear all display memory */
	LCDCA->LCDCA_CR = LCDCA_CR_CDM;
	/* Wait enable signal */
	while (!(LCDCA->LCDCA_SR & LCDCA_SR_EN)) {
	}
}

/**
 * \brief Disable the LCDCA module.
 */
void lcdca_disable(void)
{
	sleepmgr_unlock_mode(SLEEPMGR_RET);
	/* Disable all functions (blinking, FCx,...)  */
	lcdca_blink_disable();
	lcdca_automated_char_stop();
	lcdca_circular_shift_disable();
	LCDCA->LCDCA_CR = LCDCA_CR_FC0DIS | LCDCA_CR_FC1DIS | LCDCA_CR_FC2DIS;
	/* Turns OFF all LCD segments */
	LCDCA->LCDCA_CFG = LCDCA_CFG_BLANK;
	/* Disable the LCD module */
	LCDCA->LCDCA_CR = LCDCA_CR_DIS;
}

/**
 * \brief Set the LCDCA fine contrast.
 *
 * Transfer function: VLCD = 3.0V + (fcont[5:0] * 0.016V)
 *
 * \param[in] contrast Contrast value (range -32 to 31 inclusive)
 */
void lcdca_set_contrast(
		int8_t contrast)
{
	uint32_t cfg = LCDCA->LCDCA_CFG;
	uint32_t fcst_filed;
	int8_t fcst_val_msk = (LCDCA_CFG_FCST_Msk >> (LCDCA_CFG_FCST_Pos + 1));
	int8_t fcst_sign_msk = ((LCDCA_CFG_FCST_Msk >> LCDCA_CFG_FCST_Pos) + 1) >> 1;

	/* Clear previous contrast value */
	cfg &= ~LCDCA_CFG_FCST_Msk;
	/*
	 * Convert contrast value to the value in FCST field:
	 * FCST is a signed number (two's complement).
	 */
	fcst_filed = (contrast & fcst_val_msk);
	if (contrast < 0) {
		fcst_filed |= fcst_sign_msk;
	}
	/* Write new value */
	LCDCA->LCDCA_CFG = cfg | LCDCA_CFG_FCST(fcst_filed);
}

/**
 * \brief Set all bits in the LCDCA display memory high.
 */
void lcdca_set_display_memory(void)
{
	LCDCA->LCDCA_DRL0 = LCDCA_DRL0_DATA_Msk;
	LCDCA->LCDCA_DRH0 = LCDCA_DRH0_DATA_Msk;
	LCDCA->LCDCA_DRL1 = LCDCA_DRL1_DATA_Msk;
	LCDCA->LCDCA_DRH1 = LCDCA_DRH1_DATA_Msk;
	LCDCA->LCDCA_DRL2 = LCDCA_DRL2_DATA_Msk;
	LCDCA->LCDCA_DRH2 = LCDCA_DRH2_DATA_Msk;
	LCDCA->LCDCA_DRL3 = LCDCA_DRL3_DATA_Msk;
	LCDCA->LCDCA_DRH3 = LCDCA_DRH3_DATA_Msk;
}

/**
 * \brief Enable the specified LCDCA timer, and wait until it is running.
 *
 * \note The function \ref lcdca_enable() must be called prior to this function.
 *
 * \param[in] lcd_timer Timer number to be enabled
 */
void lcdca_enable_timer(
		uint8_t lcd_timer)
{
	if (lcd_timer == LCDCA_TIMER_FC0) {
		LCDCA->LCDCA_CR = LCDCA_CR_FC0EN;
		while (!(LCDCA->LCDCA_SR & LCDCA_SR_FC0S)) {
		}
	} else if (lcd_timer == LCDCA_TIMER_FC1) {
		LCDCA->LCDCA_CR = LCDCA_CR_FC1EN;
		while (!(LCDCA->LCDCA_SR & LCDCA_SR_FC1S)) {
		}
	} else if (lcd_timer == LCDCA_TIMER_FC2) {
		LCDCA->LCDCA_CR = LCDCA_CR_FC2EN;
		while (!(LCDCA->LCDCA_SR & LCDCA_SR_FC2S)) {
		}
	}
}

/**
 * \brief Disable the specified LCDCA timer.
 *
 * \param[in] lcd_timer Timer number to be disabled
 */
void lcdca_disable_timer(
		uint8_t lcd_timer)
{
	if (lcd_timer == LCDCA_TIMER_FC0) {
		LCDCA->LCDCA_CR = LCDCA_CR_FC0DIS;
	} else if (lcd_timer == LCDCA_TIMER_FC1) {
		LCDCA->LCDCA_CR = LCDCA_CR_FC1DIS;
	} else if (lcd_timer == LCDCA_TIMER_FC2) {
		LCDCA->LCDCA_CR = LCDCA_CR_FC2DIS;
	}
}

/**
 * \brief Set the LCDCA blink configuration.
 *
 * \param[in] blink_cfg Pointer to the LCD blink configuration structure
 */
void lcdca_blink_set_config(
		struct lcdca_blink_config *blink_cfg)
{
	/* Validate parameters. */
	Assert(blink_cfg);

	LCDCA->LCDCA_CR = LCDCA_CR_BSTOP;
	LCDCA->LCDCA_BCFG = LCDCA_BCFG_FCS(blink_cfg->lcd_blink_timer) |
			blink_cfg->lcd_blink_mode;
}

/**
 * \brief Start an LCDCA pixel/segment blinking.
 *
 * \param[in] pix_com Pixel/segment COMx coordinate
 * \param[in] pix_seg Pixel/segment SEGy coordinate (range 0 to 1 inclusive)
 */
void lcdca_set_blink_pixel(
		uint8_t pix_com,
		uint8_t pix_seg)
{
	/* Validate parameters. */
	Assert(pix_seg<=1);
	
	if (pix_seg == 0) {
		LCDCA->LCDCA_BCFG |= LCDCA_BCFG_BSS0(1 << pix_com);
	}

	if (pix_seg == 1) {
		LCDCA->LCDCA_BCFG |= LCDCA_BCFG_BSS1(1 << pix_com);
	}
}

/**
 * \brief Stop a specified LCDCA pixel/segment from blinking.
 *
 * \param[in] pix_com Pixel/segment COMx coordinate
 * \param[in] pix_seg Pixel/segment SEGy coordinate (range 0 to 1 inclusive)
 */
void lcdca_clear_blink_pixel(
		uint8_t pix_com,
		uint8_t pix_seg)
{
	/* Validate parameters. */
	Assert(pix_seg<=1);
	
	if (pix_seg == 0) {
		LCDCA->LCDCA_BCFG &= ~LCDCA_BCFG_BSS0(1 << pix_com);
	}

	if (pix_seg == 1) {
		LCDCA->LCDCA_BCFG &= ~LCDCA_BCFG_BSS1(1 << pix_com);
	}
}

/**
 * \brief Stop all LCDCA pixels/segments from blinking.
 */
void lcdca_clear_blink_all_pixel(void)
{
	uint32_t i;

	for (i = 0; i < LCDCA_MAX_NR_OF_COM; i++) {
		lcdca_clear_blink_pixel(i, 0);
		lcdca_clear_blink_pixel(i, 1);
	}
}

/**
 * \brief Configure the LCDCA automated display.
 *
 * \note The automated display is disabled.
 *
 * \param[in] ac_cfg Pointer to an automated display configuration structure
 */
void lcdca_automated_char_set_config(
		struct lcdca_automated_char_config *ac_cfg)
{
	/* Validate parameters. */
	Assert(ac_cfg);
	
	/* Clear register first */
	LCDCA->LCDCA_ACMCFG = 0;
	/* Write configuration then */
	LCDCA->LCDCA_ACMCFG = LCDCA_ACMCFG_FCS(ac_cfg->automated_timer) |
			(ac_cfg->automated_mode ? LCDCA_ACMCFG_MODE : 0) |
			(ac_cfg->dir_reverse ? LCDCA_ACMCFG_DREV : 0) |
			LCDCA_ACMCFG_TDG(ac_cfg->lcd_tdg) |
			LCDCA_ACMCFG_STSEG(ac_cfg->stseg) |
			LCDCA_ACMCFG_STEPS(ac_cfg->steps) |
			LCDCA_ACMCFG_DIGN(ac_cfg->dign);
}

/**
 * \brief Start the LCDCA automated display.
 *
 * \note This function also initializes and enables the PDCA channel
 * associated with the LCDCA module.
 *
 * \param[in] data  Data string buffer pointer
 * \param[in] width Data string length
 */
 void lcdca_automated_char_start(
		const uint8_t *data,
		size_t width)
{
	/* Validate parameters. */
	Assert(data);
	
	/* PDCA channel options */
	pdca_channel_config_t pdca_tx_configs;

	pdca_tx_configs.addr = (void *)data;
	pdca_tx_configs.pid = LCDCA_PDCA_ID_TX_ACM;
	pdca_tx_configs.size = width;
	pdca_tx_configs.r_addr = (void *)data;
	pdca_tx_configs.r_size = width;
	pdca_tx_configs.ring = true;
	pdca_tx_configs.etrig = false;
	pdca_tx_configs.transfer_size = PDCA_MR_SIZE_BYTE;

	/* Enable PDCA controller */
	pdca_enable(PDCA);

	/* Initialize PDCA channel with the pdca_options */
	pdca_channel_set_config(LCDCA_AUTOMATED_CHAR_DMA_CH, &pdca_tx_configs);

	/* Enable PDCA channel */
	pdca_channel_enable(LCDCA_AUTOMATED_CHAR_DMA_CH);

	/* Enable automated display */
	LCDCA->LCDCA_ACMCFG |= LCDCA_ACMCFG_EN;
}

/**
 * \brief LCDCA automated display reload.
 *
 * \param[in] data  Data string buffer pointer
 * \param[in] width Data string length
 */
 void lcdca_automated_char_reload(
		const uint8_t *data,
		size_t width)
{
	pdca_channel_write_reload(LCDCA_AUTOMATED_CHAR_DMA_CH, (void *)data, width);
}

/**
 * \brief Set the LCDCA circular shift configuration.
 *
 * \note The circular shift register is disabled.
 *
 * \param[in] cs_cfg Pointer to a circular shift configuration structure
 */
void lcdca_circular_shift_set_config(
		struct lcdca_circular_shift_config *cs_cfg)
{
	LCDCA->LCDCA_CR = LCDCA_CR_CSTOP;
	LCDCA->LCDCA_CSRCFG = LCDCA_CSRCFG_FCS(cs_cfg->lcd_csr_timer) |
			(cs_cfg->lcd_csr_dir) |
			LCDCA_CSRCFG_SIZE(cs_cfg->size) | LCDCA_CSRCFG_DATA(cs_cfg->data);
}

/**
 * \brief Send a sequence of ASCII bytes to the LCDCA via the digit decoder.
 *
 * \note If a NULL byte is encountered, or if the <i>width</i> count expires,
 * data will no longer be sent via the digit decoder and the function returns.
 *
 * \param[in] lcd_tdg   Type of digit decoder
 * \param[in] first_seg First SEG where the data will be written
 * \param[in] data      ASCII data buffer pointer
 * \param[in] width     Maximum number of data bytes
 * \param[in] dir       Direction (0 for left to right, otherwise right to left)
 */
 void lcdca_write_packet(
		uint8_t lcd_tdg, uint8_t first_seg,
		const uint8_t *data,
		size_t width,
		uint8_t dir)
{
	LCDCA->LCDCA_CMCFG = LCDCA_CMCFG_TDG(lcd_tdg)
			| LCDCA_CMCFG_STSEG(first_seg)
			| (dir ? LCDCA_CMCFG_DREV_LEFT : LCDCA_CMCFG_DREV_RIGHT);

	while (width--) {
		if (*data == '\0') {
			break; /* Stop on NULL char */
		}

		LCDCA->LCDCA_CMDR = (*data++);
	}
}

/**
 * \internal Get the LCDCA pixel/segment register from coordinates.
 *
 * Driver-internal function for getting the address of the register which
 * controls the state for the specified pixel coordinate pair.
 *
 * \param[in] pix_com Pixel/segment COMx coordinate
 *
 * \return The address of register controlling specified pixel.
 */
static uint64_t lcdca_get_pixel_register(
		uint8_t pix_com)
{
	uint64_t register_value = 0;

	switch (pix_com) {
	case 0:
		register_value = (uint64_t)LCDCA->LCDCA_DRL0;
		register_value |= ((uint64_t)LCDCA->LCDCA_DRH0 << 32);
		break;

	case 1:
		register_value = (uint64_t)LCDCA->LCDCA_DRL1;
		register_value |= ((uint64_t)LCDCA->LCDCA_DRH1 << 32);
		break;

	case 2:
		register_value = (uint64_t)LCDCA->LCDCA_DRL2;
		register_value |= ((uint64_t)LCDCA->LCDCA_DRH2 << 32);
		break;

	case 3:
		register_value = (uint64_t)LCDCA->LCDCA_DRL3;
		register_value |= ((uint64_t)LCDCA->LCDCA_DRH3 << 32);
		break;
	}
	return register_value;
}

/**
 * \brief Enable the specified pixel/segment in the LCDCA display memory.
 *
 * \param[in] pix_com Pixel/segment COMx coordinate
 * \param[in] pix_seg Pixel/segment SEGy coordinate
 */
 void lcdca_set_pixel(
		uint8_t pix_com,
		uint8_t pix_seg)
{
	if ((pix_com < LCDCA_MAX_NR_OF_COM) &&
			(pix_seg < LCDCA_MAX_NBR_OF_SEG)) {
		uint64_t register_value = lcdca_get_pixel_register(pix_com);

		register_value |= ((uint64_t)1 << pix_seg);
		switch (pix_com) {
		case 0:
			LCDCA->LCDCA_DRL0 = register_value;
			LCDCA->LCDCA_DRH0 = (register_value >> 32);
			break;

		case 1:
			LCDCA->LCDCA_DRL1 = register_value;
			LCDCA->LCDCA_DRH1 = (register_value >> 32);
			break;

		case 2:
			LCDCA->LCDCA_DRL2 = register_value;
			LCDCA->LCDCA_DRH2 = (register_value >> 32);
			break;

		case 3:
			LCDCA->LCDCA_DRL3 = register_value;
			LCDCA->LCDCA_DRH3 = (register_value >> 32);
			break;
		}
	}
}

/**
 * \brief Disable the specified pixel/segment in the LCDCA display memory.
 *
 * \param[in] pix_com Pixel/segment COMx coordinate
 * \param[in] pix_seg Pixel/segment SEGy coordinate
 */
 void lcdca_clear_pixel(uint8_t pix_com, uint8_t pix_seg)
{
	if ((pix_com < LCDCA_MAX_NR_OF_COM) &&
			(pix_seg < LCDCA_MAX_NBR_OF_SEG)) {
		uint64_t register_value = lcdca_get_pixel_register(pix_com);

		register_value &= ~((uint64_t)1 << pix_seg);
		switch (pix_com) {
		case 0:
			LCDCA->LCDCA_DRL0 = register_value;
			LCDCA->LCDCA_DRH0 = (register_value >> 32);
			break;

		case 1:
			LCDCA->LCDCA_DRL1 = register_value;
			LCDCA->LCDCA_DRH1 = (register_value >> 32);
			break;

		case 2:
			LCDCA->LCDCA_DRL2 = register_value;
			LCDCA->LCDCA_DRH2 = (register_value >> 32);
			break;

		case 3:
			LCDCA->LCDCA_DRL3 = register_value;
			LCDCA->LCDCA_DRH3 = (register_value >> 32);
			break;
		}
	}
}

/**
 * \brief Toggle the specified pixel/segment in the LCDCA display memory.
 *
 * \param[in] pix_com Pixel/segment COMx coordinate
 * \param[in] pix_seg Pixel/segment SEGy coordinate
 */
 void lcdca_toggle_pixel(
		uint8_t pix_com,
		uint8_t pix_seg)
{
	if ((pix_com < LCDCA_MAX_NR_OF_COM) &&
			(pix_seg < LCDCA_MAX_NBR_OF_SEG)) {
		uint64_t register_value = lcdca_get_pixel_register(pix_com);

		if (register_value & ((uint64_t)1 << pix_seg)) {
			lcdca_clear_pixel(pix_com, pix_seg);
		} else {
			lcdca_set_pixel(pix_com, pix_seg);
		}
	}
}

/**
 * \brief Get the specified pixel/segment state from the LCDCA display memory.
 *
 * \param[in] pix_com Pixel/segment COMx coordinate
 * \param[in] pix_seg Pixel/segment SEGy coordinate
 *
 * \return The pixel/segment value from the LCDCA display memory.
 */
 bool lcdca_get_pixel(
		uint8_t pix_com,
		uint8_t pix_seg)
{
	uint64_t register_value = lcdca_get_pixel_register(pix_com);
	return register_value & ((uint64_t)1 << pix_seg);
}

/**
 * \brief Set the callback for the LCDCA 'beginning of frame' interrupt.
 *
 * \param[in] callback  Pointer to an interrupt callback function
 * \param[in] irq_line  Interrupt line
 * \param[in] irq_level Interrupt priority level
 */
void lcdca_set_callback(
		lcdca_callback_t callback,
		uint8_t irq_line,
		uint8_t irq_level)
{
	lcdca_callback_pointer = callback;
	NVIC_ClearPendingIRQ((IRQn_Type)irq_line);
	NVIC_SetPriority((IRQn_Type)irq_line, irq_level);
	NVIC_EnableIRQ((IRQn_Type)irq_line);
	lcdca_enable_interrupt();
}

/**
 * \internal LCDCA interrupt handler.
 */
void LCDCA_Handler(void)
{
	/* Clear interrupt flags */
	lcdca_clear_status();

	/* Interrupt handler */
	if (lcdca_callback_pointer != NULL) {
		lcdca_callback_pointer();
	}
}
