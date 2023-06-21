/**
 * \file
 *
 * \brief TWIS driver for SAM.
 *
 * This file defines a useful set of functions for the TWIS on SAM4L devices.
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

#include "twis.h"
#include "sleepmgr.h"

/** Define all error conditions */
#define TWIS_SR_ERROR (TWIS_SR_BUSERR \
		| TWIS_SR_SMBPECERR           \
		| TWIS_SR_SMBTOUT             \
		| TWIS_SR_ORUN                \
		| TWIS_SR_URUN)

twis_callback_t twis_callback_pointer[TWIS_INST_NUM];
struct twis_dev_inst *twis_instances[TWIS_INST_NUM];

/**
 * \internal
 * \brief Get TWIS channel number.
 *
 * \param twis  Base address of the TWIS
 *
 * \return      TWIS channel number
 */
static uint32_t twis_find_ch_num(Twis *const twis)
{
#if defined(ID_TWIS1)
	if (twis == TWIS1) {
		return 1;
	}
#endif
#if defined(ID_TWIS0)
	if (twis == TWIS0) {
		return 0;
	}
#endif

	return 0;
}

/**
 * \internal
 * \brief Configure the TWIS Module.
 *
 * \param dev_inst Device structure pointer
 * \param config   Configuration for the TWIS
 */
static void twis_set_config(struct twis_dev_inst *const dev_inst,
		struct twis_config *config)
{
	uint32_t reg = 0;

	reg = (config->ten_bit ? TWIS_CR_TENBIT : 0) |
			(config->smbus ? TWIS_CR_SMEN : 0) |
			(config->stretch_clk_data ? TWIS_CR_SODR : 0) |
			(config->stretch_clk_addr ? TWIS_CR_SOAM : 0) |
			(config->stretch_clk_hr ? TWIS_CR_STREN : 0) |
			(config->ack_general_call ? TWIS_CR_GCMATCH : 0) |
			(config->ack_slave_addr ? TWIS_CR_SMATCH : 0) |
			(config->enable_pec ? TWIS_CR_PECEN : 0) |
			(config->ack_smbus_host_header ? TWIS_CR_SMHH : 0) |
			(config->ack_smbus_default_addr ? TWIS_CR_SMDA : 0) |
			TWIS_CR_ADR(config->chip);

	dev_inst->hw_dev->TWIS_CR = reg;

	dev_inst->hw_dev->TWIS_TR = TWIS_TR_SUDAT(config->sudat) |
			TWIS_TR_EXP(config->exp) |
			TWIS_TR_TTOUT(config->ttouts) |
			TWIS_TR_TLOWS(config->tlows);
	dev_inst->hw_dev->TWIS_SRR = TWIS_SRR_DADRIVEL(config->fs_dadrivel) |
			TWIS_SRR_DASLEW(config->fs_daslew) |
			TWIS_SRR_FILTER(config->fs_filter);

	dev_inst->hw_dev->TWIS_HSTR = TWIS_HSTR_HDDAT(config->hddat);
	dev_inst->hw_dev->TWIS_HSSRR = TWIS_HSSRR_DADRIVEL(config->hs_dadrivel) |
			TWIS_HSSRR_DASLEW(config->hs_daslew) |
			TWIS_HSSRR_FILTER(config->hs_filter);
}

/**
 * \brief Get the TWIS master default configurations.
 *
 * Use to initialize the configuration structure to known default values. This
 * function should be called at the start of any TWIS initiation.
 *
 * The default configuration is as follows:
 * - 7-bit addressing
 * - Self address is 0x50.
 * - Normal mode
 * - Do not stretch clock on data byte reception
 * - Do not stretch clock on address match
 * - Stretch clock if RHR is full or THR is empty
 * - Do not acknowledge the general call address
 * - Acknowledge the specified slave address
 * - Disable packet error checking
 * - Do not acknowledge the SMBus host header
 * - Do not acknowledge the SMBus default address
 * - 0 data setup cycles in F/S mode and high speed mode
 * - Zero-initialization for slew rate setting in F/S mode and high speed mode
 * - Clock Prescaler is 0
 * - 0 SMBus TIMEOUT cycle
 * - 0 SMBus Low:Sext cycle
 *
 * \param cfg Pointer to configuration structure to be initiated.
 */
void twis_get_config_defaults(struct twis_config *const cfg)
{
	/*Sanity check argument. */
	Assert(cfg);

	cfg->ten_bit = false;
	cfg->chip = 0x50;
	cfg->smbus = false;
	cfg->stretch_clk_data = false;
	cfg->stretch_clk_addr = false;
	cfg->stretch_clk_hr = true;
	cfg->ack_general_call = false;
	cfg->ack_slave_addr = true;
	cfg->enable_pec = false;
	cfg->ack_smbus_host_header = false;
	cfg->ack_smbus_default_addr = false;
	cfg->sudat = 0;
	cfg->fs_filter = 0;
	cfg->fs_daslew = 0;
	cfg->fs_dadrivel = 0;
	cfg->hddat = 0;
	cfg->hs_filter = 0;
	cfg->hs_daslew = 0;
	cfg->hs_dadrivel = 0;
	cfg->exp = 0;
	cfg->ttouts = 0;
	cfg->tlows = 0;
}

/**
 * \brief Initialize the TWI Slave Module.
 *
 * \param dev_inst Device structure pointer
 * \param twis     Base address of the TWIS
 * \param config   Configuration for the TWIS
 *
 * \return Status of module initialization.
 * \retval STATUS_OK The data is written correctly.
 * \retval STATUS_ERR_DENIED Initialization failed due to the module was enable
 * before.
 * \retval STATUS_ERR_BUSY Initialization failed due to the module is busy with
 * transfer.
 */
enum status_code twis_init(struct twis_dev_inst *const dev_inst,
		Twis *const twis, struct twis_config *config)
{
	Assert(dev_inst);
	Assert(twis);
	Assert(config);

	if (twis->TWIS_SR & TWIS_SR_SEN) {
		return STATUS_ERR_DENIED;
	}

	if ((twis->TWIS_SR & (TWIS_SR_RXRDY | TWIS_SR_TXRDY)) == 0) {
		return STATUS_ERR_BUSY;
	}

	dev_inst->hw_dev = twis;
	twis_instances[twis_find_ch_num(twis)] = dev_inst;
	sysclk_enable_peripheral_clock(twis);
	/* Reset the TWIS module */
	twis->TWIS_CR = TWIS_CR_SWRST;
	twis_set_config(dev_inst, config);

	return STATUS_OK;
}

/**
 * \brief Set callback for TWIS
 *
 * \note Slave address match interrupt is enabled in default so that TWIS ISR
 * can work appropriately.
 *
 * \param dev_inst  Device structure pointer
 * \param source    Interrupt source
 * \param callback  Callback function pointer
 * \param irq_level Interrupt level
 */
void twis_set_callback(struct twis_dev_inst *const dev_inst,
		twis_interrupt_source_t source, twis_callback_t callback,
		uint8_t irq_level)
{
	Assert(dev_inst);
	Assert(dev_inst->hw_dev);
	Assert(callback);

	uint32_t i = twis_find_ch_num(dev_inst->hw_dev);
	twis_callback_pointer[i] = callback;
	if (!i) {
		irq_register_handler(TWIS0_IRQn, irq_level);
	} else if (i == 1) {
		irq_register_handler(TWIS1_IRQn, irq_level);
	}
	/* Enable the specified interrupt source */
	twis_enable_interrupt(dev_inst, source);
	/* Enable slave address match interrupt in default */
	if (source != TWIS_INTERRUPT_SLAVEADR_MATCH) {
		twis_enable_interrupt(dev_inst, TWIS_INTERRUPT_SLAVEADR_MATCH);
	}
}

/**
 * \brief Enable TWIS Module.
 *
 * \param dev_inst   Device structure pointer
 */
void twis_enable(struct twis_dev_inst *const dev_inst)
{
	Assert(dev_inst->hw_dev);

	sleepmgr_lock_mode(SLEEPMGR_SLEEP_1);
	dev_inst->hw_dev->TWIS_CR |= TWIS_CR_SEN;
}

/**
 * \brief Disable TWIS Module.
 *
 * \param dev_inst   Device structure pointer
 */
void twis_disable(struct twis_dev_inst *const dev_inst)
{
	Assert(dev_inst->hw_dev);

	dev_inst->hw_dev->TWIS_CR &= ~TWIS_CR_SEN;
	sleepmgr_unlock_mode(SLEEPMGR_SLEEP_1);
}

/**
 * \internal
 * \brief TWIS interrupt handler
 *
 * \param Base address of the TWIS
 */
static void twis_interrupt_handler(uint32_t ch)
{
	struct twis_dev_inst *dev_inst = twis_instances[ch];

	/* Get status and interrupt mask register values */
	uint32_t status  = twis_get_status(dev_inst);
	uint32_t enabled = twis_get_interrupt_mask(dev_inst);
	uint32_t pending = status & enabled;

	twis_clear_status(dev_inst, pending);

	/* An error has occurred, set only address match active and return */
	if (status & TWIS_SR_ERROR) {
		twis_disable_interrupt(dev_inst, TWIS_INTERRUPT_ALL);
		twis_clear_status(dev_inst, TWIS_INTERRUPT_ALL);
		twis_enable_interrupt(dev_inst, TWIS_INTERRUPT_SLAVEADR_MATCH);
		twis_callback_pointer[ch].stop();
		twis_callback_pointer[ch].error();
		return;
	}
	/* Check if the slave address match flag is raised */
	if (pending & TWIS_IER_SAM) {
		/* Ignore repeated start and transmission complete flags */
		if (pending & TWIS_SR_REP) {
			twis_clear_status(dev_inst, TWIS_SCR_REP);
		}
		if (pending & TWIS_SR_TCOMP) {
			twis_clear_status(dev_inst, TWIS_SCR_TCOMP);
		}
		/* Enable error handling */
		twis_enable_interrupt(dev_inst, TWIS_INTERRUPT_ERRORS);

		/* Check if the slave should be in receive or transmit mode */
		if (status & TWIS_SR_TRA) {
			/* Transmit mode */
			twis_clear_status(dev_inst, TWIS_SR_BTF);
			twis_enable_interrupt(dev_inst, TWIS_INTERRUPT_BYTE_TRANS_FINISHED);
			twis_enable_interrupt(dev_inst, TWIS_INTERRUPT_TRANS_COMP);
			dev_inst->hw_dev->TWIS_THR = twis_callback_pointer[ch].tx();
		} else {
			/* Receive mode */
			twis_enable_interrupt(dev_inst, TWIS_INTERRUPT_RX_BUFFER_READY);
			twis_enable_interrupt(dev_inst, TWIS_INTERRUPT_TRANS_COMP);
			twis_enable_interrupt(dev_inst, TWIS_INTERRUPT_RESTART_RECEIVED);
		}
	}

	/* Check if there is data ready to be read in the data receive register */
	if (pending & TWIS_IER_RXRDY) {
		/* Call user specific receive function */
		twis_callback_pointer[ch].rx(dev_inst->hw_dev->TWIS_RHR);
	}

	/* Check if the transmit ready flag is raised */
	if (pending & TWIS_SR_BTF) {
		if (status & TWIS_SR_NAK) {
			twis_disable_interrupt(dev_inst,
					TWIS_INTERRUPT_BYTE_TRANS_FINISHED);
			twis_clear_status(dev_inst, TWIS_SCR_BTF);
			twis_enable_interrupt(dev_inst, TWIS_INTERRUPT_TRANS_COMP);
			twis_enable_interrupt(dev_inst, TWIS_INTERRUPT_RESTART_RECEIVED);
			/* Clear the NAK */
			twis_clear_status(dev_inst, TWIS_SCR_NAK);
		} else {
			dev_inst->hw_dev->TWIS_THR = twis_callback_pointer[ch].tx();
		}
	}

	/* Check if the transmission complete or repeated start flags raised */
	if (pending & (TWIS_IER_TCOMP | TWIS_IER_REP)) {
		/* Clear transmit complete and repeated start flags */
		twis_clear_status(dev_inst, TWIS_SCR_NAK);
		/* Disable transmission ready interrupt */
		twis_disable_interrupt(dev_inst, TWIS_INTERRUPT_BYTE_TRANS_FINISHED);
		twis_disable_interrupt(dev_inst, TWIS_INTERRUPT_RX_BUFFER_READY);
		twis_disable_interrupt(dev_inst, TWIS_INTERRUPT_TRANS_COMP);
		twis_disable_interrupt(dev_inst, TWIS_INTERRUPT_RESTART_RECEIVED);
		/* Enable slave address match interrupt */
		twis_enable_interrupt(dev_inst, TWIS_INTERRUPT_SLAVEADR_MATCH);
		/* Call user specific stop function */
		twis_callback_pointer[ch].stop();
	}
}

/**
 * \brief Interrupt handler for TWIS0
 */
#if defined(ID_TWIS0)
void TWIS0_Handler(void)
{
	twis_interrupt_handler(0);
}
#endif

/**
 * \brief Interrupt handler for TWIS1
 */
#if defined(ID_TWIS1)
void TWIS1_Handler(void)
{
	twis_interrupt_handler(1);
}
#endif

