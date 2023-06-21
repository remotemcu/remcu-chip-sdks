/**
 * \file
 *
 * \brief PDCA driver for SAM4L.
 *
 * This file defines a useful set of functions for the PDCA interface on SAM4L
 * devices.
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

#include "pdca.h"
#include "sysclk.h"
#include "sleepmgr.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \defgroup sam_drivers_pdca_group Peripheral DMA Controller (PDC)
 *
 * See \ref sam_pdca_quickstart.
 *
 * The Peripheral DMA Controller (PDC) transfers data between on-chip serial
 * peripherals and the on- and/or off-chip memories. The link between the PDC and
 * a serial peripheral is operated by the AHB to ABP bridge.
 *
 * @{
 */

/**
 * \internal
 * \brief PDCA private data for each channel
 */
pdca_callback_t pdca_callback_pointer[PDCA_NUMBER_OF_CHANNELS];

/**
 * \brief Get PDCA channel handler
 *
 * \param pdca_ch_number  PDCA channel
 *
 * \return channel handled or PDCA_INVALID_ARGUMENT
 */
volatile PdcaChannel *pdca_channel_get_handler(pdca_channel_num_t
		pdca_ch_number)
{
	if (pdca_ch_number >= PDCA_NUMBER_OF_CHANNELS)
		pdca_ch_number = 0;

	/* Get the correct channel pointer */
	volatile PdcaChannel *pdca_channel =
			&(PDCA->PDCA_CHANNEL[pdca_ch_number]);

	return pdca_channel;
}

/**
 * \brief Write PDCA channel configuration to hardware
 *
 * \param pdca_ch_number PDCA channel
 * \param cfg Pointer to a PDCA channel config
 */
void pdca_channel_set_config(pdca_channel_num_t pdca_ch_number,
		const pdca_channel_config_t *cfg)
{
	/* Get the correct channel pointer */
	volatile PdcaChannel *pdca_channel =
			pdca_channel_get_handler(pdca_ch_number);

	pdca_channel->PDCA_MAR = (uint32_t) cfg->addr;
	pdca_channel->PDCA_TCR = cfg->size;
	pdca_channel->PDCA_PSR = cfg->pid;
	pdca_channel->PDCA_MARR = (uint32_t) cfg->r_addr;
	pdca_channel->PDCA_TCRR = cfg->r_size;
	if (cfg->etrig == true) {
		pdca_channel->PDCA_MR |= PDCA_MR_ETRIG;
	} else {
		pdca_channel->PDCA_MR &= ~PDCA_MR_ETRIG;
	}
	if (cfg->ring == true) {
		pdca_channel->PDCA_MR |= PDCA_MR_RING;
	} else {
		pdca_channel->PDCA_MR &= ~PDCA_MR_RING;
	}
	pdca_channel->PDCA_MR |= PDCA_MR_SIZE(cfg->transfer_size);
	pdca_channel->PDCA_CR |= PDCA_CR_ECLR;
}

/**
 * \brief Disable the PDCA module
 *
 * \param pdca Base address of the PDCA module
 */
void pdca_disable(Pdca *pdca)
{
	sysclk_disable_peripheral_clock(pdca);
	sleepmgr_unlock_mode(SLEEPMGR_BACKUP);
}

/**
 * \brief Disable the PDCA module
 *
 * \param pdca Base address of the PDCA module
 */
void pdca_enable(Pdca *pdca)
{
	sysclk_enable_peripheral_clock(pdca);
	sleepmgr_lock_mode(SLEEPMGR_BACKUP);
}

/**
 * \brief Set callback for given PDCA channel
 *
 * \param pdca_ch_number PDCA channel number
 * \param callback callback function pointer
 * \param irq_line  interrupt line.
 * \param irq_level interrupt level.
 * \param pdca_channel_interrupt_mask Interrupts to be enabled.
 */
void pdca_channel_set_callback(pdca_channel_num_t pdca_ch_number,
		pdca_callback_t callback, uint8_t irq_line, uint8_t irq_level,
		const pdca_channel_interrupt_mask_t pdca_channel_interrupt_mask)
{
	pdca_callback_pointer[pdca_ch_number] = callback;
	irq_register_handler((IRQn_Type) irq_line, irq_level);
	pdca_channel_enable_interrupt(pdca_ch_number,
			pdca_channel_interrupt_mask);
}

/**
 * \brief Write PDCA channel load values to hardware.
 *
 * \param pdca_ch_number PDCA channel
 * \param addr  address where data to load are stored
 * \param size size of the data block to load
 */
void pdca_channel_write_load(pdca_channel_num_t pdca_ch_number,
		volatile void *addr, uint32_t size)
{
	/* Get the correct channel pointer */
	volatile PdcaChannel *pdca_channel =
			pdca_channel_get_handler(pdca_ch_number);

	pdca_channel->PDCA_MAR = (uint32_t) addr;
	pdca_channel->PDCA_TCR = size;
	pdca_channel->PDCA_CR = PDCA_CR_ECLR;
}

/**
 * \brief Write PDCA channel reload values to hardware.
 *
 * \param pdca_ch_number PDCA channel
 * \param addr  address where data to load are stored
 * \param size size of the data block to load
 */
void pdca_channel_write_reload(pdca_channel_num_t pdca_ch_number,
		volatile void *addr, uint32_t size)
{
	/* Get the correct channel pointer */
	volatile PdcaChannel *pdca_channel =
			pdca_channel_get_handler(pdca_ch_number);

	pdca_channel->PDCA_MARR = (uint32_t) addr;
	pdca_channel->PDCA_TCRR = size;
	pdca_channel->PDCA_CR = PDCA_CR_ECLR;
}

/**
 * \brief Read PDCA channel load values from hardware.
 *
 * \param pdca_ch_number PDCA channel
 *
 * \return size of the data block to load
 */
uint32_t pdca_channel_read_load_size(pdca_channel_num_t pdca_ch_number)
{
	/* get the correct channel pointer */
	volatile PdcaChannel *pdca_channel =
			pdca_channel_get_handler(pdca_ch_number);

	return pdca_channel->PDCA_TCR;
}

/**
 * \brief Read PDCA channel reload values from hardware.
 *
 * \param pdca_ch_number PDCA channel
 *
 * \return size of the data block to reload
 */
uint32_t pdca_channel_read_reload_size(pdca_channel_num_t pdca_ch_number)
{
	/* get the correct channel pointer */
	volatile PdcaChannel *pdca_channel =
			pdca_channel_get_handler(pdca_ch_number);

	return pdca_channel->PDCA_TCRR;
}

/**
 * \brief Check if PDCA channel is enabled
 *
 * \param pdca_ch_number PDCA channel number to query
 *
 * \retval true PDCA channel is enabled
 * \retval false PDCA channel is disabled
 */
bool pdca_channel_is_enabled(pdca_channel_num_t pdca_ch_number)
{
	/* Get the correct channel pointer */
	volatile PdcaChannel *pdca_channel =
			pdca_channel_get_handler(pdca_ch_number);
	uint32_t status = pdca_channel->PDCA_SR;

	if ((status & PDCA_SR_TEN) == PDCA_SR_TEN) {
		return true;
	} else {
		return false;
	}
}

/**
 * \brief Get the PDCA channel transfer enable status
 *
 * \param pdca_ch_number PDCA channel
 *
 * \return 1 if channel transfer is enabled, else 0
 */
enum pdca_channel_status
		pdca_get_channel_status(pdca_channel_num_t pdca_ch_number)
{
	/* Get the correct channel pointer */
	volatile PdcaChannel *pdca_channel =
			pdca_channel_get_handler(pdca_ch_number);
	uint32_t status = pdca_channel->PDCA_SR;
	uint32_t intflag = pdca_channel->PDCA_ISR;

	if ((status & PDCA_SR_TEN) == PDCA_SR_TEN) {
		if ((intflag & PDCA_ISR_TERR) == PDCA_ISR_TERR) {
			return PDCA_CH_TRANSFER_ERROR;
		} else if ((intflag & PDCA_ISR_TRC) == PDCA_ISR_TRC) {
			return PDCA_CH_TRANSFER_COMPLETED;
		} else if ((intflag & PDCA_ISR_RCZ) == PDCA_ISR_RCZ) {
			return PDCA_CH_COUNTER_RELOAD_IS_ZERO;
		}
		return PDCA_CH_BUSY;
	} else {
		return PDCA_CH_FREE;
	}
}

/**
 * \brief Disable the PDCA for the given channel
 *
 * \param pdca_ch_number PDCA channel
 */
void pdca_channel_disable(pdca_channel_num_t pdca_ch_number)
{
	/* Get the correct channel pointer */
	volatile PdcaChannel *pdca_channel =
			pdca_channel_get_handler(pdca_ch_number);

	/* Disable transfer */
	pdca_channel->PDCA_CR = PDCA_CR_TDIS;

}

/**
 * \brief Enable the PDCA for the given channel
 *
 * \param pdca_ch_number PDCA channel
 */
void pdca_channel_enable(pdca_channel_num_t pdca_ch_number)
{
	/* Get the correct channel pointer */
	volatile PdcaChannel *pdca_channel =
			pdca_channel_get_handler(pdca_ch_number);

	/* Enable transfer */
	pdca_channel->PDCA_CR = PDCA_CR_TEN;
}

/**
 * \brief Clear transfer error for the given channel
 *
 * \param pdca_ch_number PDCA channel
 */
void pdca_channel_clear_error(pdca_channel_num_t pdca_ch_number)
{
	/* Get the correct channel pointer */
	volatile PdcaChannel *pdca_channel =
			pdca_channel_get_handler(pdca_ch_number);

	/* Enable transfer */
	pdca_channel->PDCA_CR = PDCA_CR_ECLR;
}

/**
 * \brief Disable PDCA  interrupt
 *
 * \param pdca_ch_number PDCA channel
 * \param pdca_channel_interrupt_mask Interrupts to be disabled.
 */
void pdca_channel_disable_interrupt(pdca_channel_num_t pdca_ch_number,
		const pdca_channel_interrupt_mask_t pdca_channel_interrupt_mask)
{
	/* Get the correct channel pointer */
	volatile PdcaChannel *pdca_channel =
			pdca_channel_get_handler(pdca_ch_number);

	pdca_channel->PDCA_IDR = pdca_channel_interrupt_mask;
}

/**
 * \brief Enable PDCA transfer error interrupt
 *
 * \param pdca_ch_number PDCA channel
 * \param pdca_channel_interrupt_mask Interrupts to be enabled.
 */
void pdca_channel_enable_interrupt(pdca_channel_num_t pdca_ch_number,
		const pdca_channel_interrupt_mask_t pdca_channel_interrupt_mask)
{
	/* Get the correct channel pointer */
	volatile PdcaChannel *pdca_channel =
			pdca_channel_get_handler(pdca_ch_number);

	pdca_channel->PDCA_IER = pdca_channel_interrupt_mask;
}

/**
 * \brief Get PDCA interrupt mask
 *
 * \param pdca_ch_number PDCA channel
 */
pdca_channel_interrupt_mask_t
		pdca_channel_get_interrupt_mask(pdca_channel_num_t pdca_ch_number)
{
	/* Get the correct channel pointer */
	volatile PdcaChannel *pdca_channel =
			pdca_channel_get_handler(pdca_ch_number);

	return pdca_channel->PDCA_IMR;
}

/**
 * \internal
 * \brief Common PDCA channel interrupt handler
 *
 * Calls the channel callback with the channel status code. The following
 * status codes are possible:
 * - DMA_CH_TRANSFER_COMPLETED: Transfer completed successfully
 * - DMA_CH_TRANSFER_ERROR: Fault in transfer
 *
 * The optional callback used by the interrupt handler is set by the
 * pdca_channel_set_callback() function.
 *
 * \param pdca_ch_number PDCA channel number to handle interrupt for
 */
static void pdca_channel_interrupt(const pdca_channel_num_t pdca_ch_number)
{
	enum pdca_channel_status status;

	status = pdca_get_channel_status(pdca_ch_number);

	if (pdca_callback_pointer[pdca_ch_number]) {
		pdca_callback_pointer[pdca_ch_number] (status);
	} else {
		Assert(false); /* Catch unexpected interrupt */
	}
}

/**
 * \brief Interrupt handler for PDCA channel 0.
 */
void PDCA_0_Handler(void)
{
	pdca_channel_interrupt(0);
}

/**
 * \brief Interrupt handler for PDCA channel 1.
 */
void PDCA_1_Handler(void)
{
	pdca_channel_interrupt(1);
}

/**
 * \brief Interrupt handler for PDCA channel 2.
 */
void PDCA_2_Handler(void)
{
	pdca_channel_interrupt(2);
}

/**
 * \brief Interrupt handler for PDCA channel 3.
 */
void PDCA_3_Handler(void)
{
	pdca_channel_interrupt(3);
}

/**
 * \brief Interrupt handler for PDCA channel 4.
 */
void PDCA_4_Handler(void)
{
	pdca_channel_interrupt(4);
}

/**
 * \brief Interrupt handler for PDCA channel 5.
 */
void PDCA_5_Handler(void)
{
	pdca_channel_interrupt(5);
}

/**
 * \brief Interrupt handler for PDCA channel 6.
 */
void PDCA_6_Handler(void)
{
	pdca_channel_interrupt(6);
}

/**
 * \brief Interrupt handler for PDCA channel 7.
 */
void PDCA_7_Handler(void)
{
	pdca_channel_interrupt(7);
}

/**
 * \brief Interrupt handler for PDCA channel 8.
 */
void PDCA_8_Handler(void)
{
	pdca_channel_interrupt(8);
}

/**
 * \brief Interrupt handler for PDCA channel 9.
 */
void PDCA_9_Handler(void)
{
	pdca_channel_interrupt(9);
}

/**
 * \brief Interrupt handler for PDCA channel 10.
 */
void PDCA_10_Handler(void)
{
	pdca_channel_interrupt(10);
}

/**
 * \brief Interrupt handler for PDCA channel 11.
 */
void PDCA_11_Handler(void)
{
	pdca_channel_interrupt(11);
}

/**
 * \brief Interrupt handler for PDCA channel 12.
 */
void PDCA_12_Handler(void)
{
	pdca_channel_interrupt(12);
}

/**
 * \brief Interrupt handler for PDCA channel 13.
 */
void PDCA_13_Handler(void)
{
	pdca_channel_interrupt(13);
}

/**
 * \brief Interrupt handler for PDCA channel 14.
 */
void PDCA_14_Handler(void)
{
	pdca_channel_interrupt(14);
}

/**
 * \brief Interrupt handler for PDCA channel 15.
 */
void PDCA_15_Handler(void)
{
	pdca_channel_interrupt(15);
}


//@}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
