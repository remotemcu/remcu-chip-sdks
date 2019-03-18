/**
 * \file
 *
 * \brief Optimized INTC driver for bootloader on AVR UC3.
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

#ifndef _INTC_H_
#define _INTC_H_

#include "compiler.h"


//! Maximal number of interrupt request lines per group.
#define AVR32_INTC_MAX_NUM_IRQS_PER_GRP             32

//! Number of interrupt priority levels.
#define AVR32_INTC_NUM_INT_LEVELS   (1 << AVR32_INTC_IPR_INTLEVEL_SIZE)


#ifdef __AVR32_ABI_COMPILER__   // Automatically defined when compiling for AVR32, not when assembling.

/*! \brief Registers an interrupt handler.
 *
 * \param handler   Interrupt handler to register.
 * \param irq       IRQ of the interrupt handler to register.
 * \param int_level Interrupt priority level to assign to the group of this IRQ.
 *
 * \warning The interrupt handler must manage the `rete' instruction, what can
 *          be done thanks to pure assembly, inline assembly or the
 *          `__attribute__((__interrupt__))' C function attribute.
 *
 * \warning If several interrupt handlers of a same group are registered, all
 *          interrupts of this group will fetch the last interrupt handler
 *          registered for this group with the last registered interrupt
 *          priority level.
 *
 * \note Taken and adapted from Newlib.
 */
extern void INTC_register_interrupt(__int_handler handler, unsigned int irq,
		unsigned int int_level);

#endif // __AVR32_ABI_COMPILER__


#endif // _INTC_H_
