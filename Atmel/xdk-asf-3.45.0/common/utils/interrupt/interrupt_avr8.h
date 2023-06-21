/**
 * \file
 *
 * \brief Global interrupt management for 8-bit AVR
 *
 * Copyright (c) 2010-2018 Microchip Technology Inc. and its subsidiaries.
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
#ifndef UTILS_INTERRUPT_INTERRUPT_H
#define UTILS_INTERRUPT_INTERRUPT_H

#include <compiler.h>
#include <parts.h>

/**
 * \weakgroup interrupt_group
 *
 * @{
 */

#ifdef ISR_CUSTOM_H
#  include ISR_CUSTOM_H
#else

/**
 * \def ISR
 * \brief Define service routine for specified interrupt vector
 *
 * Usage:
 * \code
	ISR(FOO_vect)
	{
	    ...
	}
\endcode
 *
 * \param vect Interrupt vector name as found in the device header files.
 */
#if defined(__DOXYGEN__)
#  define ISR(vect)
#elif defined(__GNUC__)
#  include <avr/interrupt.h>
#elif defined(__ICCAVR__)
#  define __ISR(x) _Pragma(#x)
#  define ISR(vect) __ISR(vector=vect) __interrupt void handler_##vect(void)
#endif
#endif // ISR_CUSTOM_H

#if XMEGA
/**
 * \brief Initialize interrupt vectors
 * Enables all interrupt levels, with vectors located in the application section
 * and fixed priority scheduling.
 */
#define irq_initialize_vectors() \
	PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
#elif MEGA_RF
#define irq_initialize_vectors()
#endif

#ifdef __GNUC__
#  define cpu_irq_enable()     sei()
#  define cpu_irq_disable()    cli()
#else
#  define cpu_irq_enable()     __enable_interrupt()
#  define cpu_irq_disable()    __disable_interrupt()
#endif

typedef uint8_t irqflags_t;

static inline irqflags_t cpu_irq_save(void)
{
	volatile irqflags_t flags = SREG;
	cpu_irq_disable();
	return flags;
}

static inline void cpu_irq_restore(irqflags_t flags)
{
	barrier();
	SREG = flags;
}

static inline bool cpu_irq_is_enabled_flags(irqflags_t flags)
{
#if XMEGA
#  ifdef __GNUC__
	return flags & CPU_I_bm;
#  else
	return flags & I_bm;
#  endif
#elif MEGA || TINY
	return flags & (1 << SREG_I);
#endif
}

#define cpu_irq_is_enabled()             cpu_irq_is_enabled_flags(SREG)

//! @}

/**
 * \weakgroup interrupt_deprecated_group
 * @{
 */
// Deprecated definitions.
#define Enable_global_interrupt()        cpu_irq_enable()
#define Disable_global_interrupt()       cpu_irq_disable()
#define Is_global_interrupt_enabled()    cpu_irq_is_enabled()
//! @}

#endif /* UTILS_INTERRUPT_INTERRUPT_H */
