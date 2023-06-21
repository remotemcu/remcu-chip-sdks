/**
 * \file
 *
 * \brief Access to huge data memory with 8-bit AVR
 *
 * Do not include this file directly, but rather <hugemem.h>.
 *
 * Copyright (c) 2009-2018 Microchip Technology Inc. and its subsidiaries.
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
#ifndef AVR8_HUGEMEM_H_INCLUDED
#define AVR8_HUGEMEM_H_INCLUDED

#include <stdlib.h>
#include "conf_board.h"

/**
 * \weakgroup hugemem_group
 * @{
 */

/**
 * \internal
 * \defgroup hugemem_avr8_group Hugemem implementation for 8-bit AVR.
 *
 * GCC does not have native support for 24-bit pointers, and therefore requires
 * custom assembly functions for this purpose. The implemented functions leave
 * RAMPZ cleared upon exit.\par
 *
 * If the chip does not support huge memory, i.e., \a CONFIG_HAVE_HUGEMEM is
 * not defined, a generic implementation will be used.
 */

#if defined(CONFIG_HAVE_HUGEMEM) || defined(__DOXYGEN__)
# if XMEGA && !(XMEGA_A1 || XMEGA_A1U)
#  error CONFIG_HAVE_HUGEMEM is not supported on XMEGA parts without EBI.
# endif
# if defined(__GNUC__) || defined(__DOXYGEN__)
#include <stdint.h>

#include "compiler.h"

typedef uint32_t hugemem_ptr_t;

#define HUGEMEM_NULL    0

static inline uint_fast8_t hugemem_read8(const hugemem_ptr_t from)
{
	uint8_t value;

	asm volatile(
		"movw r30, %A1 \n\t"
		"out %2, %C1 \n\t"
		"ld %0, Z \n\t"
		"out %2, __zero_reg__ \n\t"
		: "=r"(value)
		: "r"(from), "i"(&RAMPZ)
		: "r30", "r31"
	);

	return value;
}

uint_fast16_t hugemem_read16(const hugemem_ptr_t from);
uint_fast32_t hugemem_read32(const hugemem_ptr_t from);

static inline void hugemem_write8(hugemem_ptr_t to, uint_fast8_t val)
{
	asm volatile(
		"movw r30, %A0 \n\t"
		"out %2, %C0 \n\t"
		"st Z, %1 \n\t"
		"out %2, __zero_reg__ \n\t"
		:
		: "r"(to), "r"(val), "i"(&RAMPZ)
		: "r30", "r31"
	);
}

void hugemem_write16(hugemem_ptr_t to, uint_fast16_t val);
void hugemem_write32(hugemem_ptr_t to, uint_fast32_t val);

# elif defined(__ICCAVR__)
#include <stdint.h>

typedef void __huge *hugemem_ptr_t;

#define HUGEMEM_NULL    NULL

static inline uint_fast8_t hugemem_read8(const hugemem_ptr_t from)
{
	return *(volatile __huge uint8_t *)from;
}

static inline uint_fast16_t hugemem_read16(const hugemem_ptr_t from)
{
	return *(volatile __huge uint16_t *)from;
}

static inline uint_fast32_t hugemem_read32(const hugemem_ptr_t from)
{
	return *(volatile __huge uint32_t *)from;
}

static inline void hugemem_write8(hugemem_ptr_t to, uint_fast8_t val)
{
	*(__huge uint8_t *)to = val;
}

static inline void hugemem_write16(hugemem_ptr_t to, uint_fast16_t val)
{
	*(__huge uint16_t *)to = val;
}

static inline void hugemem_write32(hugemem_ptr_t to, uint_fast32_t val)
{
	*(__huge uint32_t *)to = val;
}
# endif /* __ICCAVR__ */

void hugemem_read_block(void *to, const hugemem_ptr_t from, size_t size);
void hugemem_write_block(hugemem_ptr_t to, const void *from, size_t size);

#else
# include <generic/hugemem.h>
#endif /* CONFIG_HAVE_HUGEMEM */
//@}

#endif /* AVR8_HUGEMEM_H */
