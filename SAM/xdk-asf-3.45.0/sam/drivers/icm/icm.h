/**
 * \file
 *
 * \brief SAM Integrity Check Monitor (ICM).
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
#ifndef ICM_H_INCLUDED
#define ICM_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "compiler.h"
#include "status_codes.h"

/**
 * \defgroup group_sam_drivers_icm Integrity Check Monitor Controller (ICM)
 *
 * This is a driver for configuring, enabling/disabling and use of the on-chip ICM.
 *
 * \section dependencies Dependencies
 *
 * The ICM module depends on the following modules:
 * - \ref sysclk_group for ICM clock control.
 * - \ref interrupt_group for enabling or disabling interrupts.
 * - \ref sleepmgr_group to unlock ICM
 * @{
 */

/** The SHA Algorithm definition */
enum icm_algo {
	ICM_SHA_1 = 0,
	ICM_SHA_224 = 4,
	ICM_SHA_256 = 1,
};

/** The region number definition */
enum icm_region_num {
	ICM_REGION_NUM_0 = 0,
	ICM_REGION_NUM_1,
	ICM_REGION_NUM_2,
	ICM_REGION_NUM_3,
	_ICM_NUM_OF_REGION,
};

/** ICM interrupt source type */
enum icm_interrupt_source {
	ICM_INTERRUPT_RHC = 0,
	ICM_INTERRUPT_RDM,
	ICM_INTERRUPT_RBE,
	ICM_INTERRUPT_RWC,
	ICM_INTERRUPT_REC,
	ICM_INTERRUPT_RSU,
	ICM_INTERRUPT_URAD,
	_ICM_NUM_OF_INTERRUPT_SOURCE,
	ICM_INTERRUPT_ALL = 0x1FFFFFFF,
};

/**
 * Basic configuration for ICM.
 */
struct icm_config {
	/** Write back operation is forbidden(true) or permitted(false) */
	bool is_write_back;
	/** End of monitoring is forbidden(true) or permitted(false) */
	bool is_dis_end_mon;
	/** Secondary List Branching is forbidden(true) or permitted(false) */
	bool is_sec_list_branch;
	/**
	 * Control the burden of ICM system bus. The number of system clock
	 * cycles between the end of the current processing and the next block
	 * is set to 2^bbc.
	 */
	uint8_t bbc;
	/** Enable(true) or Disable(false) Automatic Switch To Compare Digest mode*/
	bool is_auto_mode;
	/** Enable(true) or Disable(false) Dual Input Buffer */
	bool is_dual_buf;
	/** The Initial Hash Value is set by user(true) or provided by hash standard(false) */
	bool is_user_hash;
	/** User SHA Algorithm */
	enum icm_algo ualgo;
	/**
	 * The value of the HPROT AHB signal when the ICM module performs a read operation
	 * in the Region Hash Area.
	 */
	uint8_t hash_area_val;
	/**
	 * The value of the HPROT AHB signal when the ICM module performs a read operation
	 * in the Region Descriptor Area.
	 */
	uint8_t des_area_val;
};

/**
 *  ICM region descriptor in secondary list.
 */
struct icm_region_descriptor_sec_list {
	/** The first byte address of the region */
	uint32_t start_addr;
	uint32_t reserved;
	/**
	 * The number of blocks(512 bits) transferred from the memory to the SHA engine.
	 * Transfer size = (tran_size + 1) * 512bits
	 * The maxium size is 65536.
	 */
	uint32_t tran_size;
	/** The address of next region descriptor in secondary list */
	struct icm_region_descriptor_sec_list *next_addr;
};

/**
 *  ICM region descriptor in main list.
 */
struct icm_region_descriptor_main_list {
	/** The first byte address of the region */
	uint32_t start_addr;
	/** The configuration value of the region */
	struct rcfg {
		/** Compare Digest(true) or Write Back Digest(false) */
		uint32_t is_compare_mode:1;
		/**
		 * The next region descriptor address loaded is the current region
		 * identifier descriptor address incremented by 0x10(false) or is ICM_DSCR(true).
		 */
		uint32_t is_wrap:1;
		/** The current descriptor terminates the monitoring(true) or not(false) */
		uint32_t is_end_mon:1;
		uint32_t reserved1:1;
		/** Enable(true) or Disable(false) Region Hash Completed Interrupt */
		uint32_t reg_hash_int_en:1;
		/** Enable(true) or Disable(false) Digest Mismatch Interrupt */
		uint32_t dig_mis_int_en:1;
		/** Enable(true) or Disable(false) Bus Error Interrupt */
		uint32_t bus_err_int_en:1;
		/** Enable(true) or Disable(false) Wrap Condition Interrupt */
		uint32_t wrap_con_int_en:1;
		/** Enable(true) or Disable(false) End Bit Condition Interrupt */
		uint32_t ebit_con_int_en:1;
		/** Enable(true) or Disable(false) Monitoring Status Updated Condition Interrupt */
		uint32_t status_upt_con_int_en:1;
		/** SHA processing runtime is the longest(true) one or shortest(false) one */
		uint32_t is_pro_dly:1;
		uint32_t reserved2:1;
		/** SHA Algorithm */
		uint32_t algo:3;
		uint32_t reserved3:9;
		/** The value of HPROT AHB signal when the ICM retrieves the memory region */
		uint32_t mem_reg_val:6;
		uint32_t reserved4:2;
	}cfg;
	/**
	 * The number of blocks(512 bits) transferred from the memory to the SHA engine.
	 * Transfer size = (tran_size + 1) * 512bits
	 * The maxium size is 65536.
	 */
	uint32_t tran_size;
	/** The address of next region descriptor in secondary list */
	struct icm_region_descriptor_sec_list *next_addr;
};

/**
 * \brief Interrupt event callback function type
 *
 * The interrupt handler can be configured to do a function callback,
 * the callback function must match the icm_callback_t type.
 *
 */
typedef void (*icm_callback_t)(uint8_t);

/**
 * \brief Initialize ICM with specified configuration.
 *
 * \param p_icm Pointer to an ICM instance.
 * \param icm_cfg  Pointer to ICM Configuration.
 */
void icm_init(Icm *p_icm, struct icm_config *icm_cfg);

/**
 * \brief Enable ICM.
 *
 * \param p_icm Pointer to an ICM instance.
 */
void icm_enable(Icm *p_icm);

/**
 * \brief Disable ICM.
 *
 * \param p_icm Pointer to an ICM instance.
 */
void icm_disable(Icm *p_icm);

/**
 * \brief  Enable Region Monitoring.
 *
 * \param p_icm Pointer to an ICM instance.
 * \param reg_num  The region number(0 ~ 3)
 */
static inline void icm_region_enable_monitor(Icm *p_icm,
		enum icm_region_num reg_num)
{
	p_icm->ICM_CTRL = ICM_CTRL_RMEN(1 << reg_num);
}

/**
 * \brief  Disable Region Monitoring.
 *
 * \param p_icm Pointer to an ICM instance.
 * \param reg_num  The region number(0 ~ 3)
 */
static inline void icm_region_disable_monitor(Icm *p_icm,
		enum icm_region_num reg_num)
{
	p_icm->ICM_CTRL = ICM_CTRL_RMDIS(1 << reg_num);
}

/**
 * \brief  Recompute internal hash.
 *
 * This function is available only when Region monitoring is disabled.
 *
 * \param p_icm Pointer to an ICM instance.
 * \param reg_num  The region number(0 ~ 3)
 */
status_code_t icm_region_recompute_hash(Icm *p_icm,
		enum icm_region_num reg_num);

/**
 * \brief Reset ICM.
 *
 * \param p_icm Pointer to an ICM instance.
 */
static inline void icm_reset(Icm *p_icm)
{
	p_icm->ICM_CTRL = ICM_CTRL_SWRST;
}

/**
 * \brief Get the ICM status.
 *
 * \param p_icm Pointer to an ICM instance.
 *
 * \return return bit OR of the ICM status register.
 */
static inline uint32_t icm_get_status(Icm *p_icm)
{
	return p_icm->ICM_SR;
}

/**
 * \brief ICM interrupt callback function
 *
 * This function allows the caller to set and change the interrupt callback
 * function. Without setting a callback function the interrupt handler in the
 * driver will only clear the interrupt flags.
 *
 * \param p_icm Pointer to an ICM instance.
 * \param callback Reference to a callback function.
 * \param reg_num  The region number(0 ~ 3)
 * \param interrupt_source  Interrupt source.
  * \param irq_level interrupt level.
 */
void icm_set_callback(Icm *p_icm, icm_callback_t callback,
		enum icm_region_num reg_num, enum icm_interrupt_source interrupt_source,
		uint8_t irq_level);

/**
 * \brief ICM enable interrupt.
 *
 * \param p_icm Pointer to an ICM instance.
 * \param ul_sources Interrupt sources to be enabled.
 */
static inline void icm_enable_interrupt(Icm *p_icm, uint32_t ul_sources)
{
	p_icm->ICM_IER = ul_sources;
}

/**
 * \brief ICM disable interrupt.
 *
 * \param p_icm Pointer to an ICM instance.
 * \param ul_sources Interrupt sources to be disabled.
 */
static inline void icm_disable_interrupt(Icm *p_icm, uint32_t ul_sources)
{
	p_icm->ICM_IDR = ul_sources;
}

/**
 * \brief Get ICM interrupt mask.
 *
 * \param p_icm Pointer to an ICM instance.
 *
 * \return The interrupt mask value.
 */
static inline uint32_t icm_get_interrupt_mask(Icm *p_icm)
{
	return p_icm->ICM_IMR;
}

/**
 * \brief Get ICM interrupt status.
 *
 * \param p_icm Pointer to an ICM instance.
 *
 * \return The interrupt status value.
 */
static inline uint32_t icm_get_interrupt_status(Icm *p_icm)
{
	return p_icm->ICM_ISR;
}

/**
 * \brief Get ICM Undefined Register Access Trace.
 *
 * \param p_icm Pointer to an ICM instance.
 *
 * \return The trace value.
 */
static inline uint32_t icm_get_urat(Icm *p_icm)
{
	return p_icm->ICM_UASR;
}

/**
 * \brief Set Descriptor Area Start Address.
 *
 * \param p_icm Pointer to an ICM instance.
 * \param addr  The start address value
 *
 */
static inline void icm_set_reg_des_addr(Icm *p_icm, uint32_t addr)
{
	p_icm->ICM_DSCR = addr;
}

/**
 * \brief Set Hash Area Start Address.
 *
 * \param p_icm Pointer to an ICM instance.
 * \param addr  The start address value
 *
 */
static inline void icm_set_hash_area_addr(Icm *p_icm, uint32_t addr)
{

	p_icm->ICM_HASH = addr;
}

/**
 * \brief Set hash algorithm.
 *
 * \param p_icm Pointer to an ICM instance.
 * \param algo   The hash algorithm type.
 */
void icm_set_algo(Icm *p_icm, enum icm_algo algo);

/**
 * \brief Set Initial Hash Value.
 *
 * \param p_icm Pointer to an ICM instance.
 * \param p_value  The hash value array.
 */
void icm_set_hash_value(Icm *p_icm, uint32_t *p_value);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

/**
 * \page sam_drivers_icm_quick_start Quick Start Guide for the ICM driver
 *
 * This is the quick start guide for the \ref group_sam_drivers_icm, with
 * step-by-step instructions on how to configure and use the driver for
 * a specific use case.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section icm_qs_use_cases Use cases
 * - \ref icm_basic
 *
 * \section icm_basic ICM basic usage
 *
 * This use case will demonstrate how to configure and use of the on-chip
 * ICM controller to check the integrity of internal SRAM. The region descriptor
 * structure address in main list must be 64 byte alignment and in secondary list
 * must be 4 byte alignment. The hash area start address must be 128 byte alignment.
.*
 * \section icm_basic_setup Setup steps
 *
 * \subsection icm_basic_prereq Prerequisites
 *
 * This module requires the following service
 * - \ref clk_group
 * - \ref sleepmgr_group
 *
 * \subsection icm_basic_setup_code Setup Code Example
 *
 * Add this to the main loop or a setup function:
 * \code
	   uint32_t message_sha[] = {
	   0x80636261,
	   0x00000000,
	   0x00000000,
	   0x00000000,
	   0x00000000,
	   0x00000000,
	   0x00000000,
	   0x00000000,
	   0x00000000,
	   0x00000000,
	   0x00000000,
	   0x00000000,
	   0x00000000,
	   0x00000000,
	   0x00000000,
	   0x18000000
	};

	   COMPILER_ALIGNED(128)
	   uint32_t output_sha[0x20];

	   // Set region descriptor value
	   COMPILER_ALIGNED(64)
	   struct icm_region_descriptor reg_descriptor;

	   reg_descriptor.start_addr = (uint32_t)message_sha;
	   reg_descriptor.cfg.is_compare_mode = false;
	   reg_descriptor.cfg.is_wrap = false;
	   reg_descriptor.cfg.is_end_mon = true;
	   reg_descriptor.cfg.reg_hash_int_en = false;
	   reg_descriptor.cfg.dig_mis_int_en = false;
	   reg_descriptor.cfg.bus_err_int_en = false;
	   reg_descriptor.cfg.wrap_con_int_en = false;
	   reg_descriptor.cfg.ebit_con_int_en = false;
	   reg_descriptor.cfg.status_upt_con_int_en = false;
	   reg_descriptor.cfg.is_pro_dly = false;
	   reg_descriptor.cfg.mem_reg_val = 0;
	   reg_descriptor.cfg.algo = ICM_SHA_1;
	   reg_descriptor.tran_size = 0;
	   reg_descriptor.next_addr = 0;

	   // Initialize ICM with specified value
	   struct icm_config icm_cfg;
	   icm_cfg.is_write_back= false;
	   icm_cfg.is_dis_end_mon = false;
	   icm_cfg.is_sec_list_branch = true;
	   icm_cfg.bbc = 0;
	   icm_cfg.is_auto_mode = false;
	   icm_cfg.is_dual_buf = false;
	   icm_cfg.is_user_hash = false;
	   icm_cfg.ualgo = ICM_SHA_1;
	   icm_cfg.hash_area_val = 0;
	   icm_cfg.des_area_val = 0;
	   icm_init(ICM, &icm_cfg);

	   // Set region descriptor start addres
	   icm_set_reg_des_addr(ICM, &reg_descriptor);

	   // Set hash area start addres
	   icm_set_hash_area_addr(ICM, output_sha);

	   // Enable ICM
	   icm_enable(ICM);

	   // Check region hash is completed
	   while(!(icm_get_interrupt_status(ICM) & 1));

	   if((output_sha[0] == 0x363E99A9) && \
	           (output_sha[1] == 0x6A810647) && \
	           (output_sha[2] == 0x71253EBA) && \
	           (output_sha[3] == 0x6CC25078) && \
	           (output_sha[4] == 0x9DD8D09C))
	       printf( " ICM SHA1 TEST PASS \n\r");

\endcode
 */
#endif /* ICM_H_INCLUDED */
