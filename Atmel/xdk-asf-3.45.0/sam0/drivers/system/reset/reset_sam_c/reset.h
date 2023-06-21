/**
 * \file
 *
 * \brief SAM C2x Reset functionality
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
#ifndef RESET_H_INCLUDED
#define RESET_H_INCLUDED

#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup asfdoc_sam0_system_group
 * @{
 */

/**
 * \brief Reset causes of the system.
 *
 * List of possible reset causes of the system.
 */
enum system_reset_cause {
	/** The system was last reset by a software reset */
	SYSTEM_RESET_CAUSE_SOFTWARE       = RSTC_RCAUSE_SYST,
	/** The system was last reset by the watchdog timer */
	SYSTEM_RESET_CAUSE_WDT            = RSTC_RCAUSE_WDT,
	/** The system was last reset because the external reset 
		line was pulled low */
	SYSTEM_RESET_CAUSE_EXTERNAL_RESET = RSTC_RCAUSE_EXT,
	/** The system was last reset by VDD brown out detector */
	SYSTEM_RESET_CAUSE_BODVDD         = RSTC_RCAUSE_BODVDD,
	/** The system was last reset by VDDCORE brown out detector */
	SYSTEM_RESET_CAUSE_BODCORE        = RSTC_RCAUSE_BODCORE,
	/** The system was last reset by the POR (Power on reset) */
	SYSTEM_RESET_CAUSE_POR            = RSTC_RCAUSE_POR,
};

/**
 * \name Reset Control
 * @{
 */

/**
 * \brief Reset the MCU.
 *
 * Resets the MCU and all associated peripherals and registers, except RTC,
 * OSC32KCTRL, RSTC, GCLK(if WRTLOCK is set) and I/O retention state of PM.
 *
 */
static inline void system_reset(void)
{
	NVIC_SystemReset();
}

/**
 * \brief Get the reset cause.
 *
 * Retrieves the cause of the last system reset.
 *
 * \return An enum value indicating the cause of the last system reset.
 */
static inline enum system_reset_cause system_get_reset_cause(void)
{
	return (enum system_reset_cause)RSTC->RCAUSE.reg;
}

/**
 * @}
 */

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* RESET_H_INCLUDED */
