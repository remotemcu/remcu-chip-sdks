/**
 * \file
 *
 * \brief Quad Serial Peripheral Interface (QSPI) driver for SAM.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef QSPI_H_INCLUDED
#define QSPI_H_INCLUDED

#include "compiler.h"
#include "string.h"
#include "status_codes.h"
#include <assert.h>
#include "sysclk.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

#ifndef QSPI_WPMR_WPKEY_PASSWD
#define QSPI_WPMR_WPKEY_PASSWD QSPI_WPMR_WPKEY((uint32_t) 0x515350)
#endif

/** QSPI chip select mode. */
enum qspi_cs_mode {
	QSPI_NOT_RELOADED = 0,
	QSPI_LASTXFER,
	QSPI_SYSTEMATICALLY,
};

/**
 * \brief Qspi enum types for QSPI modes.
 */
enum qspi_run_mode {
	spi_mode = QSPI_MR_SMM_SPI,
	mem_mode = QSPI_MR_SMM_MEMORY
};

/**
 * \brief Qspi frame structure for QSPI mode
 */
struct qspi_inst_frame_t {
	union _qspiinst_frame {
		uint32_t val;
		struct _qspiinst_frame_bitmap {
					/* Width of QSPI Addr , inst data */
			uint32_t b_width:3,
					/* Reserved */
					reserved0:1,
					/* Enable Inst */
					b_inst_en:1,
					/* Enable Address */
					b_addr_en:1,
					/* Enable Option */
					b_opt_en:1,
					/** Enable Data */
					b_data_en:1,
					/* Option Length */
					b_opt_len:2,
					/* Addrs Length */
					b_addr_len:1,
					/* Option Length */
					reserved1:1,
					/* Transfer type */
					b_tfr_type:2,
					/* Continoues read mode */
					b_continues_read:1,
					/* Reserved*/
					reserved2:1,
					/*< Unicast hash match */
					b_dummy_cycles:5,
					/* Reserved */
					reserved3:11;
		} bm;
	} inst_frame;
	uint32_t addr;
};

/**
 * \brief Qspi buffer structure
 */
struct qspi_buffer_t {
	/* Tx buffer size */
	uint32_t tx_data_size;
	/* Rx buffer size */
	uint32_t rx_data_size;
	/* Tx buffer */
	uint32_t *data_tx;
	/* Rx buffer */
	uint32_t *data_rx;
};

/**
 * \brief Qspi command structure
 */
struct qspi_mem_cmd_t {
	/* Qspi instruction code */
	uint8_t instruction;
	/* Qspi option code */
	uint8_t option;
};

/**
 * \brief Qspi driver structure
 */
struct qspid_t {
	/* QSPI Hw instance */
	Qspi *qspi_hw;
	/* Qspi command structure */
	struct qspi_mem_cmd_t qspi_command;
	/* Qspi buffer */
	struct qspi_buffer_t qspi_buffer;
	/* Qspi QSPI mode Frame register informations */
	struct qspi_inst_frame_t *qspi_frame;
};

/**
 * \brief Qspi config structure
 */
struct qspi_config_t {
	/* Qspi serial memory mode */
	enum qspi_run_mode  serial_memory_mode;
	/* Local loop back enable */
	bool loopback_en;
	/* Wait data read for transfer */
	bool wait_data_for_transfer;
	/* Chip select mode */
	enum qspi_cs_mode csmode;
	/* Numbers of bits per transfer */
	uint32_t bits_per_transfer;
	/* Minimum inactive QCS delay */
	uint32_t min_delay_qcs;
	/* Delay between consecutive transfers */
	uint32_t delay_between_ct;
	/* Qspi clock polarity */
	uint32_t clock_polarity;
	/* Qspi clock phase */
	uint32_t clock_phase;
	/* Qspi baudrate(Hz) */
	uint32_t baudrate;
	/* Qspi transfer delay */
	uint32_t transfer_delay;
	/* Scrambling/unscrambling enable */
	bool scrambling_en;
	/* Scrambling/unscrambling random value disable */
	bool scrambling_random_value_dis;
	/* Scrambling user key */
	uint32_t scrambling_user_key;
};

/**
 * \brief Qspi access modes
 */
enum qspi_access {
	/* Cmd access */
	QSPI_CMD_ACCESS  = 0,
	/* Read access */
	QSPI_READ_ACCESS,
	/* Write access */
	QSPI_WRITE_ACCESS
};

/**
 * \brief Enable loop back mode.
 *
 * \param qspi Pointer to an QSPI instance.
 */
static inline void qspi_enable_loopback(Qspi *qspi)
{
	qspi->QSPI_MR |= QSPI_MR_LLB;
}

/**
 * \brief Disable loop back mode.
 *
 * \param qspi Pointer to an QSPI instance.
 */
static inline void qspi_disable_loopback(Qspi *qspi)
{
	qspi->QSPI_MR &= (~QSPI_MR_LLB);
}

/**
 * \brief Enable QSPI interrupts.
 *
 * \param qspi Pointer to an QSPI instance.
 * \param sources Interrupts to be enabled.
 */
static inline void qspi_enable_interrupt(Qspi *qspi, uint32_t sources)
{
	qspi->QSPI_IER = sources;
}

/**
 * \brief Disable QSPI interrupts.
 *
 * \param qspi Pointer to an QSPI instance.
 * \param sources Interrupts to be disabled.
 */
static inline void qspi_disable_interrupt(Qspi *qspi, uint32_t sources)
{
	qspi->QSPI_IDR = sources;
}

/**
 * \brief Resets a QSPI peripheral.
 *
 * \param qspi  Pointer to a Qspi instance.
 */
static inline void qspi_reset(Qspi *qspi)
{
	assert(qspi);
	qspi->QSPI_CR = QSPI_CR_SWRST ;
}

/**
 * \brief Enables a QSPI peripheral.
 *
 * \param qspi  Pointer to a Qspi instance.
 */
static inline void qspi_enable(Qspi *qspi)
{
	assert(qspi);
	qspi->QSPI_CR = QSPI_CR_QSPIEN;
	while(!(qspi->QSPI_SR & QSPI_SR_QSPIENS));
}

/**
 * \brief Disables a QSPI peripheral.
 *
 * \param qspi  Pointer to a Qspi instance.
 */
static inline void qspi_disable(Qspi *qspi)
{
	assert(qspi);
	qspi->QSPI_CR = QSPI_CR_QSPIDIS ;
	while(qspi->QSPI_SR & QSPI_SR_QSPIENS);
}

/**
 * \brief Set qspi clock polarity.
 *
 * \param qspi  Pointer to a Qspi instance.
 * \param polarity Polarity to be set.
 */
static inline void qspi_set_clock_polarity(Qspi *qspi, uint32_t polarity)
{
	assert(qspi);
	if (polarity) {
		qspi->QSPI_SCR |= QSPI_SCR_CPOL;
	} else {
		qspi->QSPI_SCR &= (~QSPI_SCR_CPOL);
	}
}

/**
 * \brief Set qspi clock phase.
 *
 * \param qspi  Pointer to a Qspi instance.
 * \param phase Phase to be set.
 */
static inline void qspi_set_clock_phase(Qspi *qspi, uint32_t phase)
{
	assert(qspi);
	if (phase) {
		qspi->QSPI_SCR |= QSPI_SCR_CPHA;
	} else {
		qspi->QSPI_SCR &= (~QSPI_SCR_CPHA);
	}
}

/**
 * \brief Set qspi clock baudrate.
 *
 * \param qspi  Pointer to a Qspi instance.
 * \param baudrate   Baud rate to be set.
 * \return status Baud rate set result.
 */
static inline enum status_code qspi_set_baudrate(Qspi *qspi, uint32_t baudrate)
{
	assert(qspi);
	uint32_t scbr_value = sysclk_get_peripheral_hz() / baudrate - 1;

	if (scbr_value > 255) {
		return ERR_INVALID_ARG;
	}
	uint32_t mask = qspi->QSPI_SCR & (~QSPI_SCR_SCBR_Msk);
	qspi->QSPI_SCR = mask | QSPI_SCR_SCBR(scbr_value);
	return STATUS_OK;
}

/**
 * \brief Set qspi instruction addr.
 *
 * \param qspi  Pointer to a Qspi instance.
 * \param addr  Address to be set.
 */
static inline void qspi_set_instruction_addr(Qspi *qspi, uint32_t addr)
{
	assert(qspi);
	qspi->QSPI_IAR = QSPI_IAR_ADDR(addr);
}

/**
 * \brief Set qspi instruction code.
 *
 * \param qspi  Pointer to a Qspi instance.
 * \param instruction_code    Code to be set.
 */
static inline void qspi_set_instruction_code(Qspi *qspi, struct qspi_mem_cmd_t instruction_code)
{
	assert(qspi);
	qspi->QSPI_ICR = QSPI_ICR_INST(instruction_code.instruction) | QSPI_ICR_OPT(instruction_code.option);
}

/**
 * \brief Reads the Instruction frame of QSPI
 *
 * \param pQspi   Pointer to an Qspi instance.
 * \return status QSPI frame value.
 */
static inline uint32_t qspi_get_inst_frame(Qspi *qspi)
{
	assert(qspi);
	return qspi->QSPI_IFR;
}

/**
 * \brief Set qspi scrambling mode.
 *
 * \param qspi  Pointer to a Qspi instance.
 * \param mode  Mode to be set.
 */
static inline void qspi_set_scrambling_mode(Qspi *qspi, uint32_t scr_enable, uint32_t random_mode)
{
	assert(qspi);
	qspi->QSPI_SMR &= (~(QSPI_SMR_SCREN | QSPI_SMR_RVDIS));

	if (scr_enable) {
		qspi->QSPI_SMR |= QSPI_SMR_SCREN;
	} else {
		qspi->QSPI_SMR &= (~QSPI_SMR_SCREN);
	}

	if (random_mode) {
		qspi->QSPI_SMR |= QSPI_SMR_RVDIS;
	} else {
		qspi->QSPI_SMR &= (~QSPI_SMR_RVDIS);
	}
}

/**
 * \brief Set qspi scrambling key.
 *
 * \param qspi  Pointer to a Qspi instance.
 * \param mode  Mode to be set.
 * \return If write succeeded, return 0, else return 1.
 */
static inline uint32_t qspi_set_scrambing_key(Qspi *qspi, uint32_t key)
{
	assert(qspi);
	if (qspi->QSPI_WPMR & QSPI_WPMR_WPEN) {
		return 1;
	}
	qspi->QSPI_SKR = QSPI_SKR_USRK(key);

	return 0;
}

/**
 * \brief Enable write protection.
 *
 * \param qspi    Pointer to a Qspi instance.
 * \param enable  Enable or disable write protect.
 * \enable Protection status to be set.
 */
static inline void qspi_set_writeprotect(Qspi *qspi, uint32_t enable)
{
	assert(qspi);
	if (enable) {
		qspi->QSPI_WPMR |= (QSPI_WPMR_WPKEY_PASSWD | QSPI_WPMR_WPEN);
	} else {
		qspi->QSPI_WPMR &= (~(QSPI_WPMR_WPKEY_PASSWD | QSPI_WPMR_WPEN));
	}
}

/**
 * \brief Get write protection status.
 *
 * \param qspi  Pointer to a Qspi instance.
 * \return Write protection status.
 * \return status QSPI write protect status.
 */
static inline uint32_t qspi_get_writeprotect_status(Qspi *qspi)
{
	assert(qspi);
	return qspi->QSPI_WPSR;
}

enum status_code qspi_initialize(Qspi *qspi, struct qspi_config_t *qspi_config);
void qspi_get_config_default(struct qspi_config_t * qspi_config);
enum status_code qspi_read(Qspi *qspi, uint16_t *us_data, uint32_t num_of_bytes);
enum status_code qspi_write(Qspi *qspi, uint16_t *us_data, uint32_t num_of_bytes);
void qspi_set_instruction_frame(Qspi *qspi, struct qspi_inst_frame_t instruction_frame);

/** Functionality API -- Serial Memory Mode */
enum status_code qspi_flash_execute_command(struct qspid_t *qspid, enum qspi_access read_write);
enum status_code qspi_flash_access_memory(struct qspid_t *qspid, enum qspi_access read_write, uint8_t scramble_flag);

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \page sam_spi_quickstart Quick start guide for SAM QSPI driver
 *
 * This is the quick start guide for the \ref spi_group "SAM QSPI driver",
 * with step-by-step instructions on how to configure and use the driver in a
 * selection of use cases.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g.the main application function.
 *
 * \section spi_basic_use_case Basic use case of the QSPI driver
 * In this basic use case, the QSPI module are configured for:
 * - SPI mode
 * - Serial Memory Mode
 *
 * \subsection sam_spi_quickstart_prereq Prerequisites
 * -# \ref sysclk_group "System Clock Management (Sysclock)"
 *
 * \section spi_basic_use_case_setup Setup steps
 * \subsection spi_basic_use_case_setup_code Example code
 * Add to application C-file:
 * \code
		void qspi_get_config_default(qspi_config_t * qspi_config)
		{
			qspi_config->serial_memory = 1;
			qspi_config->loopback_en = false;
			qspi_config->wait_data_for_transfer = false;
			qspi_config->csmode = 1;
			qspi_config->bits_per_transfer = QSPI_MR_NBBITS_8_BIT;
			qspi_config->min_delay_qcs = 0;
			qspi_config->delay_between_ct = 0;
			qspi_config->clock_polarity = 0;
			qspi_config->clock_phase = 0;
			qspi_config->baudrate = 1000000;
			qspi_config->transfer_delay = 0x40;
			qspi_config->scrambling_en = false;
			qspi_config->scrambling_random_value_dis = false;
			qspi_config->scrambling_user_key = 0;
		}

		void qspi_initialize(Qspi *qspi, struct qspi_config_t *qspi_config)
		{
			qspi_disable(qspi);
			qspi_reset(qspi);
			qspi_set_config(qspi, qspi_config);
			qspi_enable(qspi);
		}
\endcode
 */
#endif /* QSPI_H_INCLUDED */
