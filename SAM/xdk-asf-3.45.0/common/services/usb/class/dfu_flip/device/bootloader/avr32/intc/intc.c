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

#include <avr32/io.h>
#include "compiler.h"
#include "intc.h"


//! Exception Vector Base Address.
extern void _evba;


void INTC_register_interrupt(__int_handler handler, unsigned int irq,
		unsigned int int_level)
{
	// Program the IPRX register of the IRQ group to set the interrupt priority
	// level and the interrupt vector offset that will be fetched by the core
	// interrupt system.
	AVR32_INTC.ipr[irq / AVR32_INTC_MAX_NUM_IRQS_PER_GRP] =
			((((U32) handler - (U32) & _evba) <<
					AVR32_INTC_IPR_AUTOVECTOR_OFFSET) &
			AVR32_INTC_IPR_AUTOVECTOR_MASK) | ((int_level <<
					AVR32_INTC_IPR_INTLEVEL_OFFSET) &
			AVR32_INTC_IPR_INTLEVEL_MASK);
}


/*! \brief Default interrupt handler.
 *
 * \note Taken and adapted from Newlib.
 */
#if (defined __GNUC__)
__attribute__((__interrupt__))
#elif (defined __ICCAVR32__)
__interrupt
#endif
void _unhandled_interrupt(void);
#if (defined __GNUC__)
__attribute__((__interrupt__))
#elif (defined __ICCAVR32__)
__interrupt
#endif
void _unhandled_interrupt(void)
{
	// Catch unregistered interrupts.
	while (true);
}
