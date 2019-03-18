/**
 * \file
 *
 * \brief Driver for AT86RF230B transceiver.
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


#include "board.h"
#include "gpio.h"
#include "conf_at86rfx.h"
#include "at86rfx_driver.h"


/*
 * Mask used to extract TAL main state
 */
#define TAL_MAIN_STATE_MASK             (0x0F)

/*
 * Mask used to extract the TAL tx sub state
 */
#define TAL_TX_SUB_STATE_MASK           (0xF0)

/*
 * Global TAL variables
 * These variables are only to be used by the TAL internally.
 */

/**
 * Keep track of transceiver status
 */
static uint8_t trx_trac_status;

/**
 * Current state of the TAL state machine.
 */
static tal_state_t tal_state;

/**
 * Current state of the transceiver.
 */
static tal_trx_status_t tal_trx_status;


/**
 * \brief Initializes the transceiver
 *
 * This function is called to initialize the transceiver.
 *
 * \return TRX_SUCCESS if the transceiver state is changed to TRX_OFF and the
 *                     current device part no. and version no. are correct
 *         TRX_FAILURE otherwise
 */
static trx_retval_t trx_init(void);

/**
 * \brief Internal TAL reset function
 *
 * \return TRX_SUCCESS if the transceiver was successfully reset
 *         TRX_FAILURE otherwise
 */
static trx_retval_t internal_tal_reset(void);

/**
 * \brief Reset transceiver
 *
 * \return TRX_SUCCESS if the transceiver state is changed to TRX_OFF
 *         TRX_FAILURE otherwise
 */
static trx_retval_t trx_reset(void);

/**
 * \brief Switches the PLL on
 */
static void switch_pll_on(void);

/**
 * \brief Configures the transceiver
 *
 * This function is called to configure the transceiver after reset.
 */
static void trx_config(void);

/**
 * \brief Sets transceiver state
 *
 * \param trx_cmd needs to be one of the trx commands
 *
 * \return current trx state
 */
static tal_trx_status_t set_trx_state(trx_cmd_t trx_cmd);

/**
 * \brief Handle received frame interrupt
 *
 * This function handles transceiver interrupts for received frames and
 * uploads the frames from the trx.
 */
static void handle_received_frame_irq(void);

/**
 * \brief Handles interrupts issued due to end of transmission
 */
static void handle_tx_end_irq(void);

/**
 * \brief Implements the handling of the transmission end.
 *
 * This function handles the callback for the transmission end.
 */
static void tx_end_handling(void);


trx_retval_t tal_init(void)
{
	if (trx_init() != TRX_SUCCESS) {
		return TRX_FAILURE;
	}

	/*
	 * Do the reset stuff.
	 */
	if (internal_tal_reset() != TRX_SUCCESS) {
		return TRX_FAILURE;
	}

	/* clear pending irqs, dummy read */
	pal_trx_reg_read(RG_IRQ_STATUS);

	pal_trx_bit_write(SR_CCA_MODE, CCA_MODE_DEFAULT);
	pal_trx_bit_write(SR_MIN_BE, MINBE_DEFAULT);

	set_trx_state(CMD_RX_ON);

	return TRX_SUCCESS;
}

static trx_retval_t trx_init(void)
{
	tal_trx_status_t trx_status;
	uint8_t poll_counter = 0;

	/* Ensure control lines have correct levels. */
	RST_HIGH();
	SLP_TR_LOW();

	/* Wait typical time. */
	DELAY_US(P_ON_TO_CLKM_AVAILABLE);

	/* Apply reset pulse */
	RST_LOW();
	DELAY_US(RST_PULSE_WIDTH_US);
	RST_HIGH();

	/* Verify that TRX_OFF can be written */
	do {
		if (poll_counter == 0xFF) {
			return TRX_FAILURE;
		}
		poll_counter++;
		/* Check if AT86RF230 is connected; omit manufacturer id check */
	} while ((pal_trx_reg_read(RG_VERSION_NUM) != AT86RF230_REV_B) ||
			(pal_trx_reg_read(RG_PART_NUM) != AT86RF230));

	/* Set trx to off mode */
	pal_trx_reg_write(RG_TRX_STATE, CMD_TRX_OFF);

	/* Verify that the trx has reached TRX_OFF. */
	poll_counter = 0;
	do {
		trx_status = (tal_trx_status_t) pal_trx_bit_read(SR_TRX_STATUS);
		if (poll_counter == 0xFF) {
			return TRX_FAILURE;
		}
		poll_counter++;
	} while (trx_status != TRX_OFF);

	tal_trx_status = TRX_OFF;

	return TRX_SUCCESS;
}

static trx_retval_t internal_tal_reset(void)
{
	if (trx_reset() != TRX_SUCCESS) {
		return TRX_FAILURE;
	}

	/* Write the transceiver values except of the CSMA seed. */
	trx_config();

	/* Reset TAL state. */
	/* Reset TAL variables. */
	tal_state = TAL_IDLE;

	return TRX_SUCCESS;
}

static trx_retval_t trx_reset(void)
{
	tal_trx_status_t trx_status;
	uint8_t poll_counter = 0;

	/* trx might sleep, so wake it up */
	SLP_TR_LOW();
	DELAY_US(SLEEP_TO_TRX_OFF_US);

	/* Apply reset pulse */
	RST_LOW();
	DELAY_US(RST_PULSE_WIDTH_US);
	RST_HIGH();

	/* verify that trx has reached TRX_OFF */
	do {
		trx_status = (tal_trx_status_t) pal_trx_bit_read(SR_TRX_STATUS);
		poll_counter++;
		if (poll_counter > 250) {
			return TRX_FAILURE;
		}

	} while (trx_status != TRX_OFF);

	tal_trx_status = TRX_OFF;

	return TRX_SUCCESS;
}

static void switch_pll_on(void)
{
	trx_irq_reason_t irq_status;

	/*
	   * Check if trx is in TRX_OFF; only from PLL_ON the following procedure
	   * is applicable.
	 */
	if (pal_trx_bit_read(SR_TRX_STATUS) != TRX_OFF) {
		Assert("Switch PLL_ON failed, because trx is not in TRX_OFF" ==
				0);
		return;
	}

	/* use the IRQ status register checking for the actual PLL status */
	DISABLE_TRX_IRQ();
	/* allow PLL lock IRQ only */
	pal_trx_reg_write(RG_IRQ_MASK, TRX_IRQ_PLL_LOCK);
	/* clear PLL lock bit */
	pal_trx_reg_read(RG_IRQ_STATUS);

	/* Switch PLL on */
	pal_trx_reg_write(RG_TRX_STATE, CMD_PLL_ON);

	while (1) {
		irq_status = (trx_irq_reason_t) pal_trx_reg_read(RG_IRQ_STATUS);
		if (irq_status & TRX_IRQ_PLL_LOCK) {
			break;	// PLL is locked now
		}
	}
	CLEAR_TRX_IRQ();
	/* enable TRX_END interrupt */
	pal_trx_reg_write(RG_IRQ_MASK, TRX_IRQ_DEFAULT);
}

static void trx_config(void)
{
	uint16_t rand_value;

	/* Set pin driver strength */
	pal_trx_reg_write(RG_TRX_CTRL_0,
			((CLKM_2mA << 6) | (CLKM_2mA << 4) | CLKM_1MHz));

	/* 1 == frame pending bit is always set to 1 */
	pal_trx_bit_write(SR_AACK_SET_PD, PD_ACK_BIT_SET_ENABLE);
	/* enable auto crc */
	pal_trx_bit_write(SR_TX_AUTO_CRC_ON, TX_AUTO_CRC_ENABLE);
	/* enable TRX_END interrupt */
	pal_trx_reg_write(RG_IRQ_MASK, TRX_IRQ_DEFAULT);

	/* Once we have initialized a proper seed for rand(), we
	 * can now initialize the transceiver's CSMA seed. */

	/*
	 * Init the SEED value of the CSMA backoff algorithm.
	 */
	rand_value = (uint16_t) rand();
	pal_trx_reg_write(RG_CSMA_SEED_0, (uint8_t) rand_value);
	pal_trx_bit_write(SR_CSMA_SEED_1, (uint8_t) (rand_value >> 8));
}

static tal_trx_status_t set_trx_state(trx_cmd_t trx_cmd)
{
	tal_trx_status = (tal_trx_status_t) pal_trx_bit_read(SR_TRX_STATUS);

	/*
	 * State transition is handled among RX_ON and PLL_ON.
	 * These are the essential states required for a basic transmission
	 * and reception.
	 */
	switch (trx_cmd) {	/* new state */
	case CMD_PLL_ON:
		/* Handling PLL_ON state */
		switch (tal_trx_status) {
		case PLL_ON:
			/* Do nothing - maintain the previous state */
			break;

		case TRX_OFF:
			switch_pll_on();
			break;

		case RX_ON:
			pal_trx_reg_write(RG_TRX_STATE, CMD_PLL_ON);
			PAL_WAIT_1_US();
			break;

		default:
			Assert("state transition not handled" == 0);
			break;
		}
		break;

	case CMD_RX_ON:
		/* Handling the RX_ON state */
		switch (tal_trx_status) {
		case RX_ON:
			/* Do nothing - maintain the previous state */
			break;

		case PLL_ON:
			pal_trx_reg_write(RG_TRX_STATE, CMD_RX_ON);
			PAL_WAIT_1_US();
			break;

		case TRX_OFF:
			switch_pll_on();
			pal_trx_reg_write(RG_TRX_STATE, CMD_RX_ON);
			PAL_WAIT_1_US();
			break;

		default:
			Assert("state transition not handled" == 0);
			break;
		}
		break;

	default:
		Assert("trx command not handled" == 0);
		break;
	}

	/* Hold till the state transition is complete */
	do {
		tal_trx_status = (tal_trx_status_t)
				pal_trx_bit_read(SR_TRX_STATUS);
	} while (tal_trx_status == STATE_TRANSITION_IN_PROGRESS);

	return tal_trx_status;
}

void trx_irq_handler_cb(void)
{
	trx_irq_reason_t trx_irq_cause;

	trx_irq_cause = (trx_irq_reason_t) pal_trx_reg_read(RG_IRQ_STATUS);

	if (trx_irq_cause & TRX_IRQ_TRX_END) {
		/*
		 * TRX_END reason depends on if the trx is currently used for
		 * transmission or reception.
		 */
		if (tal_state == TAL_TX_AUTO) {
			handle_tx_end_irq();
		} else {	/* Other tal_state than TAL_TX_... */
			/* Handle rx interrupt. */
			handle_received_frame_irq();
		}
	}
}

static void handle_tx_end_irq(void)
{
	// Trx has handled the entire transmission incl. CSMA
	tal_state = TAL_TX_END;	// Further handling is done by tx_end_handling()

	/*
	 * After transmission has finished, switch receiver on again.
	 */
	set_trx_state(CMD_RX_ON);
}

void tx_frame_config(void)
{
	tal_trx_status_t trx_status;

	/* Set trx to PLL_ON state to initiate transmission procedure */
	do {
		trx_status = set_trx_state(CMD_PLL_ON);
	}
	while (trx_status != PLL_ON);

	tal_state = TAL_TX_AUTO;

	/* Toggle the SLP_TR pin triggering transmission. */
	SLP_TR_HIGH();
	WAIT_65_NS();
	SLP_TR_LOW();
}

static void handle_received_frame_irq(void)
{
	/* Actual frame length of received frame. */
	uint8_t phy_frame_len;

	uint8_t *rx_frame_ptr = at86rfx_rx_buffer;

	/* Perform FCS check for frame validation */
	if (CRC16_NOT_VALID == pal_trx_bit_read(SR_RX_CRC_VALID)) {
		return;
	}

	/* Get frame length from transceiver. */
	pal_trx_frame_read(&phy_frame_len, LENGTH_FIELD_LEN);

	/* Check for valid frame length. */
	if (phy_frame_len > PHY_MAX_LENGTH) {
		return;
	}

	/* Frame read from transceiver buffer. */
	pal_trx_frame_read(rx_frame_ptr, LENGTH_FIELD_LEN + phy_frame_len);

	/* Set flag indicating received frame to be handled. */
	at86rfx_frame_rx = true;

	set_trx_state(CMD_RX_ON);
}

void handle_tal_state(void)
{
	/* Handle the TAL state machines */
	if (tal_state != TAL_IDLE) {
		uint8_t tal_sub_state;

		tal_sub_state = tal_state & 0x0F;

		switch (tal_sub_state) {
		case TAL_IDLE:
			/* Do nothing, but fall through... */
		case TAL_TX_AUTO:
			/* Wait until state is changed to TAL_TX_END inside tx end ISR */
			break;

		case TAL_TX_END:
			tx_end_handling();
			break;

		default:
			Assert("tal_state is not handled" == 0);
			break;
		}
	}
}

static void tx_end_handling(void)
{
	tal_state = TAL_IDLE;

	/* call back function is called based on tx status */
	switch (trx_trac_status) {
	case TRAC_SUCCESS:
		AT86RFX_TX_STATUS_NOTIFY(AT86RFX_SUCCESS);
		break;

	case TRAC_CHANNEL_ACCESS_FAILURE:
		AT86RFX_TX_STATUS_NOTIFY(AT86RFX_CHANNEL_ACCESS_FAILURE);
		break;

	case TRAC_INVALID:
		AT86RFX_TX_STATUS_NOTIFY(AT86RFX_FAILURE);
		break;

	default:
		Assert("Unexpected tal_tx_state" == 0);
		AT86RFX_TX_STATUS_NOTIFY(AT86RFX_FAILURE);
		break;
	}
}
