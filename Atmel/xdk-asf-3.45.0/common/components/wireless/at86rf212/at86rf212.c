/**
 * \file
 *
 * \brief Driver for AT86RF212 transceiver.
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
 * Global TAL variables
 */

/*
 * Global TAL variables
 * These variables are only to be used by the TAL internally.
 */

/**
 * Keep track of transceiver status
 */
static trx_trac_status_t trx_trac_status;

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
 *                     current device part no. are correct
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
 * \brief Generates a 16-bit random number used as initial seed for srand()
 *
 * This function generates a 16-bit random number by means of using the
 * Random Number Generator from the transceiver.
 * The Random Number Generator generates 2-bit random values. These 2-bit
 * random values are concatenated to the required 16-bit random seed.
 * For further information please check the SWPM AT86RF212.
 *
 * The generated random 16-bit number is feed into function srand()
 * as initial seed.
 *
 * The transceiver state is initially set to RX_ON.
 * After the completion of the random seed generation, the
 * transceiver is set to TRX_OFF.
 *
 * As a prerequisite the Preamble Detector must not be disabled.
 * Since this function is called right after trx_reset(), the Preamble
 * Detector has its original value, i.e. it is enabled.
 * In case this function is used at a different point of time, having the
 * proper value set must be checked additionally.
 *
 * Also in case the function is called from a different state than TRX_OFF,
 * additional trx state handling is required, such as reading the original
 * value and restoring this state after finishing the sequence.
 * Since in our case the function is called from TRX_OFF, this is not required
 * here.
 */
static void generate_rand_seed(void);

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
	 * Generate random seed.
	 */
	if (internal_tal_reset() != TRX_SUCCESS) {
		return TRX_FAILURE;
	}

	/* Set the default CCA mode. */
	pal_trx_bit_write(SR_CCA_MODE, CCA_MODE_DEFAULT);

	/* Default configuration to perform auto CSMA-CA */
	pal_trx_reg_write(RG_CSMA_BE, ((MAXBE_DEFAULT << 4) | MINBE_DEFAULT));
	pal_trx_bit_write(SR_MAX_CSMA_RETRIES, MAX_CSMA_BACKOFFS_DEFAULT);

	/* Set the trx in promiscuous mode to receive all frame with CRC OK */
	pal_trx_bit_write(SR_AACK_PROM_MODE, PROM_MODE_ENABLE);

	/* Configuration to perform auto CRC for transmission */
	pal_trx_bit_write(SR_TX_AUTO_CRC_ON, TX_AUTO_CRC_ENABLE);

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
	DELAY_US(P_ON_TO_CLKM_AVAILABLE_TYP_US);

	/* Apply reset pulse */
	RST_LOW();
	DELAY_US(RST_PULSE_WIDTH_US);
	RST_HIGH();

	/* Verify that TRX_OFF can be written */
	do {
		/* Wait not more than max. value of TR1. */
		if (poll_counter == P_ON_TO_CLKM_ATTEMPTS) {
			return TRX_FAILURE;
		}
		/* Wait a short time interval. */
		DELAY_US(TRX_POLL_WAIT_TIME_US);
		poll_counter++;
		/* Check if AT86RF212 is connected; omit manufacturer id check */
	}
	while (pal_trx_reg_read(RG_PART_NUM) != PART_NUM_AT86RF212);

	/* Set trx to off mode */
	pal_trx_reg_write(RG_TRX_STATE, CMD_FORCE_TRX_OFF);

	/* Verify that the trx has reached TRX_OFF. */
	poll_counter = 0;
	do {
		/* Wait a short time interval. */
		DELAY_US(TRX_POLL_WAIT_TIME_US);

		trx_status = (tal_trx_status_t) pal_trx_bit_read(SR_TRX_STATUS);

		/* Wait not more than max attempts for state transition */
		if (poll_counter == SLEEP_TO_TRX_OFF_ATTEMPTS) {
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

	/*
	 * Generate a seed for the random number generator in function rand().
	 * This is required (for example) as seed for the CSMA-CA algorithm.
	 */
	generate_rand_seed();

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
	DELAY_US(SLEEP_TO_TRX_OFF_TYP_US);

	/* Apply reset pulse */
	RST_LOW();
	DELAY_US(RST_PULSE_WIDTH_US);
	RST_HIGH();

	/* verify that trx has reached TRX_OFF */
	do {
		/* Wait a short time interval. */
		DELAY_US(TRX_POLL_WAIT_TIME_US);

		trx_status = (tal_trx_status_t) pal_trx_bit_read(SR_TRX_STATUS);

		/* Wait not more than max. */
		if (poll_counter == SLEEP_TO_TRX_OFF_ATTEMPTS) {
			return TRX_FAILURE;
		}
		poll_counter++;
	} while (trx_status != TRX_OFF);

	tal_trx_status = TRX_OFF;

	return TRX_SUCCESS;
}

static void switch_pll_on(void)
{
	trx_irq_reason_t irq_status;
	uint8_t poll_counter = 0;

	/* Check if trx is in TRX_OFF; only from PLL_ON the following procedure is applicable */
	if (pal_trx_bit_read(SR_TRX_STATUS) != TRX_OFF) {
		Assert("Switch PLL_ON failed, because trx is not in TRX_OFF" ==
				0);
		return;
	}

	pal_trx_reg_read(RG_IRQ_STATUS);	/* clear PLL lock bit */

	/* Switch PLL on */
	pal_trx_reg_write(RG_TRX_STATE, CMD_PLL_ON);

	/* Check if PLL has been locked. */
	do {
		irq_status = (trx_irq_reason_t) pal_trx_reg_read(RG_IRQ_STATUS);

		if (irq_status & TRX_IRQ_PLL_LOCK) {
			return;	// PLL is locked now
		}

		/* Wait a time interval of typical value for state change. */
		DELAY_US(TRX_OFF_TO_PLL_ON_TIME_US);

		poll_counter++;
	} while (poll_counter < PLL_LOCK_ATTEMPTS);
}

static void trx_config(void)
{
	/* Set pin driver strength */
	pal_trx_bit_write(SR_PAD_IO_CLKM, PAD_CLKM_2_MA);
	pal_trx_bit_write(SR_CLKM_SHA_SEL, CLKM_SHA_DISABLE);
	pal_trx_bit_write(SR_CLKM_CTRL, CLKM_1MHZ);

	/* ACKs for data requests, indicate pending data */
	pal_trx_bit_write(SR_AACK_SET_PD, SET_PD);

	/* Enable buffer protection mode */
	pal_trx_bit_write(SR_RX_SAFE_MODE, RX_SAFE_MODE_ENABLE);

	/* Enable poll mode */
	pal_trx_bit_write(SR_IRQ_MASK_MODE, IRQ_MASK_MODE_ON);

	/* The TRX_END interrupt of the transceiver is enabled. */
	pal_trx_reg_write(RG_IRQ_MASK, TRX_IRQ_DEFAULT);
}

static tal_trx_status_t set_trx_state(trx_cmd_t trx_cmd)
{
	tal_trx_status = (tal_trx_status_t) pal_trx_bit_read(SR_TRX_STATUS);

	/*
	 * State transition is handled among FORCE_TRX_OFF, RX_ON and PLL_ON.
	 * These are the essential states required for a basic transmission
	 * and reception.
	 */
	switch (trx_cmd) {	/* requested state */
	case CMD_FORCE_TRX_OFF:
		/* Handling FORCE_TRX_OFF state */
		switch (tal_trx_status) {
		case TRX_OFF:
			/* Do nothing - maintain the previous state */
			break;

		default:
			pal_trx_reg_write(RG_TRX_STATE, CMD_FORCE_TRX_OFF);
			PAL_WAIT_1_US();
			break;
		}
		break;

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
	} while (trx_status != PLL_ON);

	tal_state = TAL_TX_AUTO;

	/* Toggle the SLP_TR pin triggering transmission. */
	SLP_TR_HIGH();
	WAIT_65_NS();
	SLP_TR_LOW();
}

static void generate_rand_seed(void)
{
	uint16_t seed = 0;
	uint8_t cur_random_val = 0;

	set_trx_state(CMD_RX_ON);

	/*
	 * We need to disable TRX IRQs while generating random values in RX_ON,
	 * we do not want to receive frames at this point of time at all.
	 */
	ENTER_TRX_REGION();

	/*
	 * The 16-bit random value is generated from various 2-bit random values.
	 */
	for (uint8_t i = 0; i < 8; i++) {
		/* Now we can safely read the 2-bit random number. */
		cur_random_val = pal_trx_bit_read(SR_RND_VALUE);
		seed = seed << 2;
		seed |= cur_random_val;
	}

	set_trx_state(CMD_FORCE_TRX_OFF);

	/*
	 * Now we need to clear potential pending TRX IRQs and
	 * enable the TRX IRQs again.
	 */
	pal_trx_reg_read(RG_IRQ_STATUS);
	CLEAR_TRX_IRQ();
	LEAVE_TRX_REGION();

	/* Set the seed for the random number generator. */
	srand(seed);
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
	switch (tal_state) {
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
