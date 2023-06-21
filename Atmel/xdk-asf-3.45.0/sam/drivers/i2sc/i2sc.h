/**
 *
 * \file
 *
 * \brief I2S driver for SAM.
 *
 * This file defines a useful set of functions for the I2S on SAM devices.
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

#ifndef I2S_H_INCLUDED
#define I2S_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup group_sam_drivers_i2sc I2SC - Inter-IC Sound Controller
 *
 * Driver for the I2SC - Inter-IC Sound Controller module.
 * I2SC provides a 5-wire, bidirectional, synchronous, digital audio
 * link with off-chip audio devices: ISDI, ISDO, IWS, ISCK and IMCK pins.
 *
 * \{
 */

#include "compiler.h"
#include "status_codes.h"

#define I2S_RETRY_VALUE   10000

/** Supported number of channels */
enum i2s_number_of_channels {
	I2S_CHANNEL_MONO = 0,
	I2S_CHANNEL_STEREO
};

/** Supported Master Clock to Sample Frequency (fs) Ratio */
enum i2s_fs_rate {
	I2S_FS_RATE_32  = 0,
	I2S_FS_RATE_64  = 1,
	I2S_FS_RATE_96  = 2,
	I2S_FS_RATE_128 = 3,
	I2S_FS_RATE_192 = 5,
	I2S_FS_RATE_256 = 7,
	I2S_FS_RATE_384 = 11,
	I2S_FS_RATE_512 = 15,
	I2S_FS_RATE_768 = 23,
	I2S_FS_RATE_1024 = 31,
	I2S_FS_RATE_1536 = 47,
	I2S_FS_RATE_2048 = 63,
};

/** Data format */
enum i2s_data_format {
	I2S_DATA_32BIT = 0,
	I2S_DATA_24BIT,
	I2S_DATA_20BIT,
	I2S_DATA_18BIT,
	I2S_DATA_16BIT,
	I2S_DATA_16BIT_COMPACT,
	I2S_DATA_8BIT,
	I2S_DATA_8BIT_COMPACT,
};

/** DMA channel usage for I2S transfer */
enum i2s_dma_channel {
	I2S_ONE_DMA_CHANNEL_FOR_BOTH_CHANNELS = 0,
	I2S_ONE_DMA_CHANNEL_FOR_ONE_CHANNEL,
};

/**
 * Configuration setting structure.
 * \note the parameters need to be calculated throgh system clock MCK,
 * audio data sample rate and the data format by the user.
 */
struct i2s_config {
	/* Number of bits per sample. */
	enum i2s_data_format data_format;

	/* Master Clock to Sample Frequency (fs) Ratio. */
	enum i2s_fs_rate fs_ratio;

	/* Number of channels for Tx */
	enum i2s_number_of_channels tx_channels;

	/* Number of channels for Rx */
	enum i2s_number_of_channels rx_channels;

	/* DMA channel usage for I2S transmission */
	enum i2s_dma_channel tx_dma;

	/* DMA channel usage for I2S reception */
	enum i2s_dma_channel rx_dma;

	/* 1 for loopback, 0 for normal. */
	bool loopback;

	/* 1 for master mode, 0 for slave mode. */
	bool master_mode;

	/* 1 for master clock generated, 0 for no master clock. */
	bool master_clock_enable;

	/**
	 * I2SMCK Master clock output frequency is Selected Clock
	 * divided by (IMCKDIV + 1), and master_clock_divide should not be 0.
	 */
	uint8_t master_clock_divide;

	/* 1 for previous sample, 0 for zero sample. */
	bool transmit_mode_underrun;

	/* 1 for 24 bit, 0 for 32. */
	bool slot_length_24;
};

struct i2s_dev_inst {
	/* Base Address of the I2SC module */
	I2sc *hw_dev;

	/* Pointer to I2S configuration structure. */
	struct i2s_config *cfg;
};

typedef void (*i2s_callback_t)(void);

/**
 * \brief Get the default I2S module configuration:
 * Data format: 32 bits
 * Sample frequecny ratio: 1024
 * Tx channel: Stereo
 * Rx channel: Stereo
 * DMA for Tx: 1 DMA channel for 1 I2S Tx channel
 * DMA for Rx: 1 DMA channel for 1 I2S Rx channel
 * Loopback: No
 * Master mode: Yes
 * Master clock enable: Yes
 * Transmit data in underrun: Yes
 * Slot length is 24: No
 *
 * \param cfg         Pointer to I2S configuration.
 */
static inline void i2s_get_config_defaults(struct i2s_config *const cfg)
{
	/* Sanity check arguments */
	Assert(cfg);

	cfg->data_format = I2S_DATA_32BIT;
	cfg->fs_ratio = I2S_FS_RATE_1024;
	cfg->tx_channels = I2S_CHANNEL_STEREO;
	cfg->rx_channels = I2S_CHANNEL_STEREO;
	cfg->tx_dma = I2S_ONE_DMA_CHANNEL_FOR_ONE_CHANNEL;
	cfg->rx_dma = I2S_ONE_DMA_CHANNEL_FOR_ONE_CHANNEL;
	cfg->loopback = false;
	cfg->master_mode = true;
	cfg->master_clock_enable = true;
	cfg->master_clock_divide = 1;
	cfg->transmit_mode_underrun= true;
	cfg->slot_length_24 = false;
}

enum status_code i2s_init(struct i2s_dev_inst *const dev_inst, I2sc *i2sc,
		struct i2s_config *const cfg);

/**
 * \brief Resets the I2S module
 *
 * \param dev_inst    Device structure pointer.
 */
static inline void i2s_reset(struct i2s_dev_inst *dev_inst)
{
	dev_inst->hw_dev->I2SC_CR = I2SC_CR_SWRST;
}

/**
 * \brief Enable the I2S module in transmission
 *
 * \param dev_inst    Device structure pointer.
 */
static inline void i2s_enable_transmission(struct i2s_dev_inst *dev_inst)
{
	dev_inst->hw_dev->I2SC_CR = I2SC_CR_TXEN;
}

/**
 * \brief Disable the I2S module in transmission
 *
 * \param dev_inst    Device structure pointer.
 */
static inline void i2s_disable_transmission(struct i2s_dev_inst *dev_inst)
{
	dev_inst->hw_dev->I2SC_CR = I2SC_CR_TXDIS;
}

/**
 * \brief Enable the I2S module in reception
 *
 * \param dev_inst    Device structure pointer.
 */
static inline void i2s_enable_reception(struct i2s_dev_inst *dev_inst)
{
	dev_inst->hw_dev->I2SC_CR = I2SC_CR_RXEN;
}

/**
 * \brief Disable the I2S module in reception
 *
 * \param dev_inst    Device structure pointer.
 */
static inline void i2s_disable_reception(struct i2s_dev_inst *dev_inst)
{
	dev_inst->hw_dev->I2SC_CR = I2SC_CR_RXDIS;
}

/**
 * \brief Enable the clocks for the I2S module
 *
 * \param dev_inst    Device structure pointer.
 */
static inline void i2s_enable_clocks(struct i2s_dev_inst *dev_inst)
{
	dev_inst->hw_dev->I2SC_CR = I2SC_CR_CKEN;
}

/**
 * \brief Disable the clocks for the I2S module
 *
 * \param dev_inst    Device structure pointer.
 */
static inline void i2s_disable_clocks(struct i2s_dev_inst *dev_inst)
{
	dev_inst->hw_dev->I2SC_CR = I2SC_CR_CKDIS;
}

/**
 * \brief Get the I2S status value.
 *
 * \param dev_inst    Device structure pointer.
 *
 * \return Status value
 */
static inline uint32_t i2s_get_status(struct i2s_dev_inst *dev_inst)
{
	return dev_inst->hw_dev->I2SC_SR;
}

/** I2S interrupt source */
typedef enum i2s_interrupt_source {
	I2S_INTERRUPT_RXRDY = 0,
	I2S_INTERRUPT_RXOR,
	I2S_INTERRUPT_TXRDY,
	I2S_INTERRUPT_TXUR,
	I2S_INTERRUPT_ENDRX,
	I2S_INTERRUPT_ENDTX,
	I2S_INTERRUPT_RXBUFF,
	I2S_INTERRUPT_TXBUFE,
	_I2S_INTERRUPT_SOURCE_NUM,
} i2s_interrupt_source_t;

void i2s_set_callback(struct i2s_dev_inst *const dev_inst,
		i2s_interrupt_source_t source, i2s_callback_t callback,
		uint8_t irq_level);

void i2s_clear_status(struct i2s_dev_inst *const dev_inst,
		i2s_interrupt_source_t source);
void i2s_enable_interrupt(struct i2s_dev_inst *const dev_inst,
		i2s_interrupt_source_t source);
void i2s_disable_interrupt(struct i2s_dev_inst *const dev_inst,
		i2s_interrupt_source_t source);

/**
 * \brief Get the I2S interrupts mask value.
 *
 * \param dev_inst    Device structure pointer.
 *
 * \return Interrupt mask value
 */
static inline uint32_t i2s_get_interrupt_mask(
		struct i2s_dev_inst *const dev_inst)
{
	return dev_inst->hw_dev->I2SC_IMR;
}

void i2s_enable(struct i2s_dev_inst *const dev_inst);
void i2s_disable(struct i2s_dev_inst *const dev_inst);

enum status_code i2s_write(struct i2s_dev_inst *dev_inst, uint32_t data);
enum status_code i2s_read(struct i2s_dev_inst *dev_inst, uint32_t *data);
#if defined(PDC_I2SC) || defined(PDC_I2SC0) || defined(PDC_I2SC1)
Pdc *i2s_get_pdc_base(struct i2s_dev_inst *const dev_inst);
#endif
/**
 * \}
 */

#ifdef __cplusplus
}
#endif

/**
 * \page sam_i2sc_quick_start Quick Start Guide for the SAMG53/SAMG54 I2S driver
 *
 * This is the quickstart guide for the \ref group_sam_drivers_i2sc
 * "SAMG53 Inter-IC Sound Controller driver", with step-by-step instructions
 * on how to configure and use the driver in a selection of use cases.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section i2sc_basic_use_case Basic use case
 * This use case will demonstrate how to initialize the I2S module to
 * master in loopback mode.
 *
 * \subsection i2sc_quickstart_prereq Prerequisites
 * -# \ref sysclk_group "System Clock Management (Sysclock)"
 *
 * \section i2sc_basic_use_case_setup Clock setup steps
 * \subsection i2sc_basic_use_case_setup_code Example code
 *
 * Add the following code in the application C-file:
 * \code
	sysclk_init();
\endcode
 *
 * \subsection i2sc_basic_use_case_setup_flow Workflow
 * -# Initialize the system clock.
 * \code sysclk_init(); \endcode
 *
 * \section i2sc_basic_use_case_usage Usage steps
 * \subsection i2sc_basic_use_case_usage_code Example code
 * Add to, e.g., main loop in application C-file:
 * \code
	struct i2s_config config;
	struct i2s_dev_inst dev_inst;
	config.data_format = I2S_DATE_16BIT;
	config.fs_ratio = I2S_FS_RATE_256;
	config.loopback = true;
	i2s_init(&dev_inst, I2SC, &config);
	i2s_enable(&dev_inst);
\endcode
 *
 * \subsection i2sc_basic_use_case_usage_flow Workflow
 * -# Initialize the module with given configuration
 * \code
	struct i2s_config config;
	struct i2s_dev_inst dev_inst;
	config.data_format = I2S_DATE_16BIT;
	config.fs_ratio = I2S_FS_RATE_256;
	config.loopback = true;
	i2s_init(&dev_inst, I2SC, &config);
\endcode
 * -# Enable the module
 * \code  i2s_enable(&dev_inst); \endcode
 * -# Enable transmission, reception and clocks
 * \code
	i2s_enable_transmission(&dev_inst);
	i2s_enable_clocks(&dev_inst);
	i2s_enable_reception(&dev_inst);
\endcode
 * -# Use write/read function to access the data
 * \code
	i2s_write(&dev_inst, data);
	i2s_read(&dev_inst, &data);
\endcode
 */
#endif  /* I2S_H_INCLUDED */
