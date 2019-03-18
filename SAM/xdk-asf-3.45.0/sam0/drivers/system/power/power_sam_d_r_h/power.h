/**
 * \file
 *
 * \brief SAM Power related functionality
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
#ifndef POWER_H_INCLUDED
#define POWER_H_INCLUDED

#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/* MCU revision number */
#define _SYSTEM_MCU_REVISION_D 3
#define _SYSTEM_MCU_REVISION_E 4

/**
 * \addtogroup asfdoc_sam0_system_group
 * @{
 */

/**
 * \brief Voltage references within the device.
 *
 * List of available voltage references (VREF) that may be used within the
 * device.
 */
enum system_voltage_reference {
	/** Temperature sensor voltage reference */
	SYSTEM_VOLTAGE_REFERENCE_TEMPSENSE,
	/** Bandgap voltage reference */
	SYSTEM_VOLTAGE_REFERENCE_BANDGAP,
};

/**
 * \brief Device sleep modes.
 *
 * List of available sleep modes in the device. A table of clocks available in
 * different sleep modes can be found in \ref asfdoc_sam0_system_module_overview_sleep_mode.
 */
enum system_sleepmode {
	/** IDLE 0 sleep mode */
	SYSTEM_SLEEPMODE_IDLE_0,
	/** IDLE 1 sleep mode */
	SYSTEM_SLEEPMODE_IDLE_1,
	/** IDLE 2 sleep mode */
	SYSTEM_SLEEPMODE_IDLE_2,
	/** Standby sleep mode */
	SYSTEM_SLEEPMODE_STANDBY,
};



/**
 * \name Voltage References
 * @{
 */

/**
 * \brief Enable the selected voltage reference
 *
 * Enables the selected voltage reference source, making the voltage reference
 * available on a pin as well as an input source to the analog peripherals.
 *
 * \param[in] vref  Voltage reference to enable
 */
static inline void system_voltage_reference_enable(
		const enum system_voltage_reference vref)
{
	switch (vref) {
		case SYSTEM_VOLTAGE_REFERENCE_TEMPSENSE:
			SYSCTRL->VREF.reg |= SYSCTRL_VREF_TSEN;
			break;

		case SYSTEM_VOLTAGE_REFERENCE_BANDGAP:
			SYSCTRL->VREF.reg |= SYSCTRL_VREF_BGOUTEN;
			break;

		default:
			Assert(false);
			return;
	}
}

/**
 * \brief Disable the selected voltage reference
 *
 * Disables the selected voltage reference source.
 *
 * \param[in] vref  Voltage reference to disable
 */
static inline void system_voltage_reference_disable(
		const enum system_voltage_reference vref)
{
	switch (vref) {
		case SYSTEM_VOLTAGE_REFERENCE_TEMPSENSE:
			SYSCTRL->VREF.reg &= ~SYSCTRL_VREF_TSEN;
			break;

		case SYSTEM_VOLTAGE_REFERENCE_BANDGAP:
			SYSCTRL->VREF.reg &= ~SYSCTRL_VREF_BGOUTEN;
			break;

		default:
			Assert(false);
			return;
	}
}

/**
 * @}
 */


/**
 * \name Device Sleep Control
 * @{
 */

/**
 * \brief Set the sleep mode of the device
 *
 * Sets the sleep mode of the device; the configured sleep mode will be entered
 * upon the next call of the \ref system_sleep() function.
 *
 * For an overview of which systems are disabled in sleep for the different
 * sleep modes, see \ref asfdoc_sam0_system_module_overview_sleep_mode.
 *
 * \param[in] sleep_mode  Sleep mode to configure for the next sleep operation
 *
 * \retval STATUS_OK               Operation completed successfully
 * \retval STATUS_ERR_INVALID_ARG  The requested sleep mode was invalid or not
 *                                 available
 */
static inline enum status_code system_set_sleepmode(
	const enum system_sleepmode sleep_mode)
{

#if (SAMD20 || SAMD21 || SAMR21)

	/* Get MCU revision */
	uint32_t rev = DSU->DID.reg;

	rev &= DSU_DID_REVISION_Msk;
	rev = rev >> DSU_DID_REVISION_Pos;

#if (SAMD20)
	if (rev < _SYSTEM_MCU_REVISION_E) {
		/* Errata 13140: Make sure that the Flash does not power all the way down
		 * when in sleep mode. */
		NVMCTRL->CTRLB.bit.SLEEPPRM = NVMCTRL_CTRLB_SLEEPPRM_DISABLED_Val;
	}
#endif

#if (SAMD21 || SAMR21)
	if (rev < _SYSTEM_MCU_REVISION_D) {
		/* Errata 13140: Make sure that the Flash does not power all the way down
		 * when in sleep mode. */
		NVMCTRL->CTRLB.bit.SLEEPPRM = NVMCTRL_CTRLB_SLEEPPRM_DISABLED_Val;
	}
#endif

#endif

	switch (sleep_mode) {
		case SYSTEM_SLEEPMODE_IDLE_0:
		case SYSTEM_SLEEPMODE_IDLE_1:
		case SYSTEM_SLEEPMODE_IDLE_2:
			SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
			PM->SLEEP.reg = sleep_mode;
			break;

		case SYSTEM_SLEEPMODE_STANDBY:
			SCB->SCR |=  SCB_SCR_SLEEPDEEP_Msk;
			break;

		default:
			return STATUS_ERR_INVALID_ARG;
	}

	return STATUS_OK;
}

/**
 * \brief Put the system to sleep waiting for interrupt
 *
 * Executes a device DSB (Data Synchronization Barrier) instruction to ensure
 * all ongoing memory accesses have completed, then a WFI (Wait For Interrupt)
 * instruction to place the device into the sleep mode specified by
 * \ref system_set_sleepmode until woken by an interrupt.
 */
static inline void system_sleep(void)
{
	__DSB();
	__WFI();
}

/**
 * @}
 */

/** @} */
#ifdef __cplusplus
}
#endif

#endif /* POWER_H_INCLUDED */
