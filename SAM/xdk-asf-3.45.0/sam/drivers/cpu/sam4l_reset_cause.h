/**
 * \file
 *
 * \brief Chip-specific reset cause functions
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
#ifndef SAM4L_RESET_CAUSE_H
#define SAM4L_RESET_CAUSE_H

#include "compiler.h"

/**
 * \defgroup group_sam4l_drivers_cpu SAM4L reset cause
 * \ingroup reset_cause_group
 *
 * Driver for CPU specific features. It provides functions for MCU Reset Cause.
 *
 * @{
 */

/**
 * \brief Chip-specific reset cause type capable of holding all chip reset
 * causes. Typically reflects the size of the reset cause register.
 */
typedef uint32_t        reset_cause_t;

//! \internal \name Chip-specific reset causes
//@{

//! \internal External reset cause
# define CHIP_RESET_CAUSE_EXTRST        PM_RCAUSE_EXT

//! \internal Brown-out detected on CPU power domain reset cause
# define CHIP_RESET_CAUSE_BOD_CPU       PM_RCAUSE_BOD

//! \internal Brown-out detected on I/O power domain reset cause
# define CHIP_RESET_CAUSE_BOD_IO        PM_RCAUSE_BOD33

//! \internal On-chip debug system reset cause
# define CHIP_RESET_CAUSE_OCD           PM_RCAUSE_OCDRST

//! \internal Power-on-reset reset cause
# define CHIP_RESET_CAUSE_POR           PM_RCAUSE_POR

//! \internal Power-on-reset on I/O power domain reset cause
# define CHIP_RESET_CAUSE_POR_IO        PM_RCAUSE_POR33

//! \internal Watchdog timeout reset cause
# define CHIP_RESET_CAUSE_WDT           PM_RCAUSE_WDT

//@}

static inline reset_cause_t reset_cause_get_causes(void)
{
	return (reset_cause_t)PM->PM_RCAUSE;
}

static inline void reset_cause_clear_causes(reset_cause_t causes)
{
	/**
	 * \note Reset causes are not clearable on SAM4L.
	 */
	 UNUSED(causes);
}

static inline void reset_do_soft_reset(void)
{
	while (1) {
		NVIC_SystemReset();
	}
}

//! @}

#endif /* SAM4L_RESET_CAUSE_H */
