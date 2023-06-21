/**
 * \file
 *
 * \brief SDRAM controller (SDRAMC) driver for SAM.
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

#ifndef SDRAMC_H_INCLUDED
#define SDRAMC_H_INCLUDED

#include  "compiler.h"
#include "sleepmgr.h"
/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/* SDRAM memory type */
typedef struct sdramc_memory_dev {
	/** Block 1 address */
	uint32_t ul_bk1;	/* Block1 is at the bit Bk+Row+Column+M0. */
	/** SDRAM mode */
	uint32_t ul_mode;
	union sdramc_cr {
		/** SDRAMC configuration */
		uint32_t ul_cfg;
		struct sdramc_cr_bm {
			/** Number of Column Bits */
			uint32_t ul_column_bits : 2,
			/** Number of Row Bits */
			ul_row_bits : 2,
			/** Number of Banks */
			ul_banks : 1,
			/** CAS Latency */
			ul_cas : 2,
			/** Data Bus Width */
			ul_data_bus_width : 1,
			/** Write Recovery Delay */
			ul_write_recovery_delay : 4,
			/** Row Cycle Delay and Row Refresh Cycle */
			ul_row_cycle_delay_row_fefresh_cycle : 4,
			/** Row Precharge Delay */
			ul_row_precharge_delay : 4,
			/** Row to Column Delay */
			ul_row_column_delay : 4,
			/** Active to Precharge Delay */
			ul_active_precharge_delay : 4,
			/** Exit from Self Refresh to Active Delay */
			ul_exit_self_refresh_active_delay : 4;
		} sdramc_cr_bm_t;
	} cr;
} sdramc_memory_dev_t;

/**
 * \brief Initialize the SDRAM controller.
 *
 * \param p_sdram  Pointer to the sdram memory structure.
 * \param ul_clk  SDRAM clock frequency.
 */
void sdramc_init(sdramc_memory_dev_t *p_sdram, uint32_t ul_clk);

/**
 * \brief De-initialize the SDRAM controller.
 */
void sdramc_deinit( void );

/**
 * \brief Set the SDRAM in self-refresh mode.
 */
static inline void sdram_enter_self_refresh(void)
{
	sleepmgr_unlock_mode(SLEEPMGR_ACTIVE);
	SDRAMC->SDRAMC_LPR |= SDRAMC_LPR_LPCB_SELF_REFRESH;
}

/**
 * \brief Exit from the SDRAM self-refresh mode, and inhibit self-refresh mode.
 */
static inline void sdram_exit_self_refresh(void)
{
	sleepmgr_lock_mode(SLEEPMGR_ACTIVE);
	SDRAMC->SDRAMC_LPR &= ~SDRAMC_LPR_LPCB_SELF_REFRESH;
}

/**
 * \brief Set the SDRAM in power down mode.
 */
static inline void sdram_enter_power_down(void)
{
	sleepmgr_unlock_mode(SLEEPMGR_ACTIVE);
	SDRAMC->SDRAMC_LPR |= SDRAMC_LPR_LPCB_POWER_DOWN;
}

/**
 * \brief Exit from the SDRAM power down mode, and inhibit power down mode.
 */
static inline void sdram_exit_power_down(void)
{
	sleepmgr_lock_mode(SLEEPMGR_ACTIVE);
	SDRAMC->SDRAMC_LPR &= ~SDRAMC_LPR_LPCB_POWER_DOWN;
}

/**
 * \brief Enter SDRAM deep power down mode.
 *
 * \note This mode is unique to low-power SDRAM.
 */
static inline void sdram_enter_deep_power_down(void)
{
	sleepmgr_unlock_mode(SLEEPMGR_ACTIVE);
	SDRAMC->SDRAMC_LPR |= SDRAMC_LPR_LPCB_DEEP_POWER_DOWN;
}

#if !(SAM3XA)
/**
 * \brief Unaligned access is supported.
 */
static inline void sdram_enable_unaligned_support(void)
{
	SDRAMC->SDRAMC_CFR1 |= SDRAMC_CFR1_UNAL;
}

/**
 * \brief Unaligned access is not supported.
 */
static inline void sdram_disable_unaligned_support(void)
{
	SDRAMC->SDRAMC_CFR1 &= ~SDRAMC_CFR1_UNAL;
}

/**
 * \brief Off-chip Memory Scrambling is enabled.
 * \param ul_key1  Key Part 1.
 * \param ul_key2  Key Part 2.
 */
static inline void sdram_enable_scrambling(uint32_t ul_key1, uint32_t ul_key2)
{
	SDRAMC->SDRAMC_OCMS |= SDRAMC_OCMS_SDR_SE;
	SDRAMC->SDRAMC_OCMS_KEY1 = ul_key1;
	SDRAMC->SDRAMC_OCMS_KEY2 = ul_key2;
}

/**
 * \brief Off-chip Memory Scrambling is disabled.
 */
static inline void sdram_disable_scrambling(void)
{
	SDRAMC->SDRAMC_OCMS &= ~SDRAMC_OCMS_SDR_SE;
}

#endif

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \page sam_sdramc_quickstart Quickstart guide for SDRAMC driver.
 *
 * This is the quickstart guide for the \ref sam_drivers_sdramc_group
 * "SDRAM Controller", with step-by-step instructions on how to configure
 * and use the driver in a selection of use cases.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section sdramc_basic_use_case Basic use case
 * In the basic use case, the SDMRAC driver are configured for:
 * - SDRAM component MT48C16M16A2 is used
 * - Write/Read access to the MT48C16M16A2
 *
 * \section sdramc_basic_use_case_setup Setup steps
 *
 * \subsection sdramc_basic_use_case_setup_prereq Prerequisites
 * -# \ref sysclk_group "System Clock Management (sysclock)"
 * -# \ref sam_drivers_pio_group "Parallel Input/Output Controller (pio)" 
 * -# \ref sam_drivers_pmc_group "Power Management Controller (pmc)"
 *
 * \subsection sdramc_basic_use_case_setup_code Example code
 * The macro of CONF_BOARD_SDRAMC must be added to the project:
 * \code
	#define CONF_BOARD_SDRAMC
\endcode
 *
 * A speicific sdramc device must be defined.
 * \code

	 const sdramc_memory_dev_t SDRAM_MICRON_MT48LC16M16A2 = {
	   24,
	   0,
	   {
	     SDRAMC_CR_NC_COL9      |
	     SDRAMC_CR_NR_ROW13     |
	     SDRAMC_CR_NB_BANK4     |
	     SDRAMC_CR_CAS_LATENCY2 |
	     SDRAMC_CR_DBW          |
	     SDRAMC_CR_TWR(2)       |
	     SDRAMC_CR_TRC_TRFC(9)  |
	     SDRAMC_CR_TRP(3)       |
	     SDRAMC_CR_TRCD(3)      |
	     SDRAMC_CR_TRAS(6)      |
	     SDRAMC_CR_TXSR(10)
	   },
	 };
\endcode
 *
 * Add to application C-file:
 * \code
	 sysclk_init();
	 board_init();
	 sdramc_init((sdramc_memory_dev_t *)&SDRAM_MICRON_MT48LC16M16A2,
	            sysclk_get_cpu_hz());

\endcode
 *
 * \subsection sdramc_basic_use_case_setup_flow Workflow
 * -# Enable the PINs for SDRAMC:
 * \code
	#define CONF_BOARD_SDRAMC
\endcode
 * -# Initialize the SDRAM device:
 * - \code
	const sdramc_memory_dev_t SDRAM_MICRON_MT48LC16M16A2 = {
\endcode
 *  -#  Block1 is at the bit 24, 1(M0)+9(Col)+13(Row)+1(BK1):
 *   - \code
	24,
\endcode
 *  -#  Set SDRAMC to normal mode 0:
 *   - \code
	0,
\endcode
 *  -#  MT48LC16M16A2 has 9 column bits:
 *   - \code
	SDRAMC_CR_NC_COL9      |
\endcode
 *  -#  MT48LC16M16A2 has 13 row bits:
 *   - \code
	SDRAMC_CR_NR_ROW13     |
\endcode
  *  -#  MT48LC16M16A2 has 4 banks:
 *   - \code
	SDRAMC_CR_NB_BANK4     |
\endcode
 *  -#  Set CAS latency to 2 cycles:
 *   - \code
	SDRAMC_CR_CAS_LATENCY2 |
\endcode
 *  -#  The data bus width of MT48LC16M16A2 is 16 bits:
 *   - \code
	SDRAMC_CR_DBW          |
\endcode
 *  -#  Set Write Recovery Delay to 2 cycles:
 *   - \code
	SDRAMC_CR_TWR(2)       |
\endcode
 *  -#  Set Row Cycle Delay and Row Refresh Cycle to 9 cycles:
 *   - \code
	SDRAMC_CR_TRC_TRFC(9)  |
\endcode
 *  -#  Set Row Precharge Delay to 3 cycles:
 *   - \code
	SDRAMC_CR_TRP(3)       |
\endcode
 *  -#  Set Row to Column Delay to 3 cycles:
 *   - \code
	SDRAMC_CR_TRCD(3)      |
\endcode
 *  -#  Set Active to Precharge Delay to 6 cycles:
 *   - \code
	SDRAMC_CR_TRAS(6)      |
\endcode
 *  -#  Set Exit from Self Refresh to Active Delay to 10 cycles:
 *   - \code
	SDRAMC_CR_TXSR(10)
\endcode
 * -# Enable system clock:
 * - \code sysclk_init(); \endcode
 * -# Enable PIO configurations for SDRMAC:
 * - \code board_init(); \endcode
 * -# Initialize MT48LC16M16A2 device:
 * - \code
	sdramc_init((sdramc_memory_dev_t *)&SDRAM_MICRON_MT48LC16M16A2,
	          sysclk_get_cpu_hz());
\endcode
 *
 * \section sdramc_basic_use_case_usage Usage steps
 * \subsection sdramc_basic_use_case_usage_code Example code
 * Add to, e.g., main loop in application C-file:
 * \code
	    uint32_t *pul = (uint32_t *)BOARD_SDRAM_ADDR;

	    pul[0] = 0xdeadbeef;
	    if (pul[0] == 0xdeadbeef) {
	        LED_On(LED0_GPIO);
	    }
\endcode
 *
 * \subsection sdramc_basic_use_case_usage_flow Workflow
 * -#  Set the pointer to the SDRAMC address:
 *   - \code
	uint32_t *pul = (uint32_t *)BOARD_SDRAM_ADDR;
\endcode
 * -#  Write the specific data to the SDRAMC space:
 *   - \code
	pul[0] = 0xdeadbeef;
\endcode
 * -#  Read the data, if matched the specific data, turn on the LED0:
 *   - \code
	 if (pul[0] == 0xdeadbeef) {
	     LED_On(LED0_GPIO);
		}
\endcode
 */

#endif /* SDRAMC_H_INCLUDED */
