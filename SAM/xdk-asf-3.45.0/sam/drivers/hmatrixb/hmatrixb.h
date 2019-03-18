/**
 * \file
 *
 * \brief HMATRIX driver for SAM.
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

#ifndef __HMATRIX_H_INCLUDED__
#define __HMATRIX_H_INCLUDED__

#include "compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

#define hmatrix_prs HmatrixbPrs

/** \brief HMATRIX master: undefined length burst type */
enum hmatrix_burst_type {
	HMATRIX_BURST_INFINITE_LENGTH = HMATRIXB_MCFG_ULBT(0),
	HMATRIX_BURST_SINGLE_ACCESS   = HMATRIXB_MCFG_ULBT(1),
	HMATRIX_BURST_FOUR_BEAT       = HMATRIXB_MCFG_ULBT(2),
	HMATRIX_BURST_EIGHT_BEAT      = HMATRIXB_MCFG_ULBT(3),
	HMATRIX_BURST_SIXTEEN_BEAT    = HMATRIXB_MCFG_ULBT(4)
};

/** \brief HMATRIX slave: default master type */
enum hmatrix_def_master_type {
	HMATRIX_DEFAULT_MASTER_NONE     = HMATRIXB_SCFG_DEFMSTR_TYPE(0),
	HMATRIX_DEFAULT_MASTER_PREVIOUS = HMATRIXB_SCFG_DEFMSTR_TYPE(1),
	HMATRIX_DEFAULT_MASTER_FIXED    = HMATRIXB_SCFG_DEFMSTR_TYPE(2)
};

/** \brief HMATRIX slave: arbitration type */
enum hmatrix_arbitration_type {
	HMATRIX_ARBITRATION_ROUND_ROBIN    = HMATRIXB_SCFG_ARBT_ROUND_ROBIN,
	HMATRIX_ARBITRATION_FIXED_PRIORITY = HMATRIXB_SCFG_ARBT_FIXED_PRIORITY
};

/** \brief Master identifier */
enum hmatrix_master_id {
	HMATRIX_MASTER_ID_CPU_IDCORE = HMATRIX_MASTER_CPU_IDCODE,
	HMATRIX_MASTER_ID_CPU_SYS    = HMATRIX_MASTER_CPU_SYS,
	HMATRIX_MASTER_ID_SMAP       = HMATRIX_MASTER_SMAP,
	HMATRIX_MASTER_ID_PDC        = HMATRIX_MASTER_PDCA,
	HMATRIX_MASTER_ID_USB        = HMATRIX_MASTER_USBC_MASTER,
	HMATRIX_MASTER_ID_CRCCU      = HMATRIX_MASTER_CRCCU,
	HMATRIX_MASTER_ID_NUM            /* number of Masters */
};

/** \brief Slave identifier */
enum hmatrix_slave_id {
	HMATRIX_SLAVE_ID_FLASH   = HMATRIX_SLAVE_FLASH,
	HMATRIX_SLAVE_ID_PBA     = HMATRIX_SLAVE_HTOP0,
	HMATRIX_SLAVE_ID_PBB     = HMATRIX_SLAVE_HTOP1,
	HMATRIX_SLAVE_ID_PBC     = HMATRIX_SLAVE_HTOP2,
	HMATRIX_SLAVE_ID_PBD     = HMATRIX_SLAVE_HTOP3,
	HMATRIX_SLAVE_ID_HRAMC0  = HMATRIX_SLAVE_HRAMC0,
	HMATRIX_SLAVE_ID_HRAMC1  = HMATRIX_SLAVE_HRAMC1,
	HMATRIX_SLAVE_ID_AES     = HMATRIX_SLAVE_AESA,
	HMATRIX_SLAVE_ID_NUM            /* number of Slaves */
};

/** \brief HMatrix Master Channel configuration structure.
 *
 *  Configuration structure for an HMatrix Master channel. This structure
 *  should be initialized by the \ref hmatrix_master_ch_get_config_defaults()
 *  function before being modified by the user application.
 */
struct hmatrix_master_ch_conf {
	enum hmatrix_burst_type        burst_type;
};

/** \brief HMatrix Slave Channel configuration structure.
 *
 *  Configuration structure for an HMatrix Slave channel. This structure
 *  should be initialized by the \ref hmatrix_slave_ch_get_config_defaults()
 *  function before being modified by the user application.
 */
struct hmatrix_slave_ch_conf {
	enum hmatrix_arbitration_type  arbitration_type;
	enum hmatrix_master_id         fixed_def_master_number;
	enum hmatrix_def_master_type   def_master_type;
	uint8_t                        slot_cycle;
};

/** \brief Initializes an HMatrix Master configuration structure to defaults.
 *
 *  Initializes a given HMatrix Master channel configuration structure to a
 *  set of known default values. This function should be called on all new
 *  instances of these configuration structures before being modified by the
 *  user application.
 *
 *  The default configuration is as follows:
 *   \li Master channel Undefined Length Burst type is split into a
 *       sixteen-beat burst, allowing re-arbitration at each sixteen-beat
 *       burst end
 *
 *  \param config    Configuration structure to initialize to default values
 */
static inline void hmatrix_master_ch_get_config_defaults(
		struct hmatrix_master_ch_conf *const config)
{
	/* Sanity check arguments */
	Assert(config);

	/* Default configuration values */
	config->burst_type      = HMATRIX_BURST_FOUR_BEAT;
}

/** \brief Initializes an HMatrix Slave configuration structure to defaults.
 *
 *  Initializes a given HMatrix Slave channel configuration structure to a
 *  set of known default values. This function should be called on all new
 *  instances of these configuration structures before being modified by the
 *  user application.
 *
 *  The default configuration is as follows:
 *   \li Slave channel arbitration is round robin
 *   \li Slave channel is configured on last default master
 *   \li Slave channel slot cycle is 16
 *
 *  \param config    Configuration structure to initialize to default values
 */
static inline void hmatrix_slave_ch_get_config_defaults(
		struct hmatrix_slave_ch_conf *const config)
{
	/* Sanity check arguments */
	Assert(config);

	/* Default configuration values */
	config->arbitration_type        = HMATRIX_ARBITRATION_ROUND_ROBIN;
	config->fixed_def_master_number = HMATRIX_MASTER_ID_CPU_IDCORE;
	config->def_master_type         = HMATRIX_DEFAULT_MASTER_PREVIOUS;
	config->slot_cycle              = 16;
}

/** \brief Writes an HMatrix Master channel configuration to the hardware module.
 *
 *  Writes out a given configuration of a HMatrix Master channel configuration to
 *  the hardware module.
 *
 *  \param[in] master_id  HMatrix Master channel to configure
 *  \param[in] config     Configuration settings for the HMatrix Master
 */
void hmatrix_master_ch_set_config(const enum hmatrix_master_id master_id,
		struct hmatrix_master_ch_conf *const config);

/** \brief Writes an HMatrix Slave channel configuration to the hardware module.
 *
 *  Writes out a given configuration of a HMatrix Slave channel configuration to
 *  the hardware module.
 *
 *  \param[in] slave_id  HMatrix Slave channel to configure
 *  \param[in] config    Configuration settings for the HMatrix Slave
 */
void hmatrix_slave_ch_set_config(const enum hmatrix_slave_id slave_id,
		struct hmatrix_slave_ch_conf *const config);

/** \brief Initializes the HMatrix.
 *
 *  Initializes the HMatrix ready for use. This setup the clock mask for the hMatrix.
 */
void hmatrix_init(void);

/** \brief Enables the HMatrix.
 *
 *  Setup the clock mask for the hMatrix.
 */
void hmatrix_enable(void);

/** \brief Disables the HMatrix.
 *
 *  Stop the clock mask for the hMatrix.
 */
void hmatrix_disable(void);

/**
 * \brief Set priority for the specified slave access.
 *
 * \param[in] slave_id Slave index.
 * \param[in] p_prio Pointer to the priority register sets.
 */
void hmatrix_set_slave_priority(enum hmatrix_slave_id slave_id,
		hmatrix_prs *p_prio);

/**
 * \brief Get priority for the specified slave access.
 *
 * \param[in] slave_id Slave index.
 * \param[in] p_prio Pointer to the priority register sets.
 */
void hmatrix_get_slave_priority(enum hmatrix_slave_id slave_id,
		hmatrix_prs *p_prio);

#ifdef __cplusplus
}
#endif

/**
 * \page sam_hmatrix_quick_start Quick Start Guide for the HMATRIX driver
 *
 * This is the quick start guide for the \ref sam_drivers_hmatrix_group, with
 * step-by-step instructions on how to configure and use the driver for
 * a specific use case.The code examples can be copied into e.g the main
 * application loop or any other function that will need to control the
 * HMATRIX module.
 *
 * \section hmatrix_qs_use_cases Use cases
 * - \ref hmatrix_basic "HMATRIX Basic Usage"
 *
 * \section hmatrix_basic HMATRIX Basic Usage
 *
 * This use case will demonstrate how to configurate the HMATRIX module to
 * set the slave with different default master type.
 *
 *
 * \section hmatrix_basic_setup Setup steps
 *
 * \subsection hmatrix_basic_prereq Prerequisites
 *
 * This module requires the following service
 * - \ref clk_group "Clock Management (Sysclock)"
 *
 * \subsection hmatrix_basic_setup_code Code
 *
 * Add this to the main loop or a setup function:
 *
 * \subsection hmatrix_basic_setup_workflow Workflow
 *
 * -# Enable the HMATRIX module
 *  - \code hmatrix_enable(); \endcode
 * -# Get the default slave channel setting
 *  - \code
	struct hmatrix_slave_ch_conf config;
	hmatrix_slave_ch_get_config_defaults(&config);
\endcode
 *
 * \section hmatrix_basic_usage Usage steps
 *
 * \subsection hmatrix_basic_usage_code Code
 *
 * -# We can set slave with Round-Robin arbitration and without default master
 *  - \code
	config.def_master_type = HMATRIX_DEFAULT_MASTER_NONE;
	hmatrix_slave_ch_set_config(ul_slave_id, &config);
\endcode
 * -# Or Set slave with Round-Robin arbitration and with last access master
 *  - \code
	config.def_master_type = HMATRIX_DEFAULT_MASTER_PREVIOUS;
	hmatrix_slave_ch_set_config(ul_slave_id, &config);
\endcode
 *
 * We can set priority of each master for one slave by
 * \code
	HmatrixbPrs prio;
	prio.HMATRIXB_PRAS = 0x00111111;
	prio.HMATRIXB_PRBS = 0x00000000;
	hmatrix_set_slave_priority(ul_slave_id, &prio);
\endcode
 *
 */

#endif /* __HMATRIX_H_INCLUDED__ */
