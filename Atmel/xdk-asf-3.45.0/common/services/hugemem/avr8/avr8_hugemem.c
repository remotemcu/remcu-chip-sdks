/**
 * \file
 *
 * \brief Access to huge data memory with 8-bit AVR
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
#include "hugemem.h"
#include "compiler.h"
#include "conf_board.h"

#if defined(CONFIG_HAVE_HUGEMEM) || defined(__DOXYGEN__)
# if defined(__GNUC__) || defined(__DOXYGEN__)
uint_fast16_t hugemem_read16(const hugemem_ptr_t from)
{
	uint16_t value;

	asm(
		"movw r30, %A1 \n\t"
		"out %2, %C1 \n\t"
		"ld %A0, Z+ \n\t"
		"ld %B0, Z \n\t"
		"out %2, __zero_reg__ \n\t"
		: "=r"(value)
		: "r"(from), "i"(&RAMPZ)
		: "r30", "r31"
	);

	return value;
}

uint_fast32_t hugemem_read32(const hugemem_ptr_t from)
{
	uint32_t value;

	asm(
		"movw r30, %A1 \n\t"
		"out %2, %C1 \n\t"
		"ld %A0, Z+ \n\t"
		"ld %B0, Z+ \n\t"
		"ld %C0, Z+ \n\t"
		"ld %D0, Z \n\t"
		"out %2, __zero_reg__ \n\t"
		: "=r"(value)
		: "r"(from), "i"(&RAMPZ)
		: "r30", "r31"
	);

	return value;
}

void hugemem_read_block(void *to, const hugemem_ptr_t from, size_t size)
{
	// Ensure that the address range to copy to is within 64 kB boundary.
	Assert(((uint32_t)to + size) <= 0x10000);

	if (size > 0) {
		asm volatile(
			"movw r30, %A2 \n\t"
			"out %3, %C2 \n\t"
			"get_%=: \n\t"
			"ld __tmp_reg__, Z+ \n\t"
			"st X+, __tmp_reg__ \n\t"
			"sbiw %A1, 1 \n\t"
			"brne get_%= \n\t"
			"out %3, __zero_reg__ \n\t"
			: "+x"(to), "+w"(size)
			: "r"(from), "i"(&RAMPZ)
			: "r30", "r31"
		);
	}
}

void hugemem_write16(hugemem_ptr_t to, uint_fast16_t val)
{
	asm(
		"movw r30, %A0 \n\t"
		"out %2, %C0 \n\t"
		"st Z+, %A1 \n\t"
		"st Z, %B1 \n\t"
		"out %2, __zero_reg__ \n\t"
		:
		: "r"(to), "r"(val), "i"(&RAMPZ)
		: "r30", "r31"
	);
}

void hugemem_write32(hugemem_ptr_t to, uint_fast32_t val)
{
	asm(
		"movw r30, %A0 \n\t"
		"out %2, %C0 \n\t"
		"st Z+, %A1 \n\t"
		"st Z+, %B1 \n\t"
		"st Z+, %C1 \n\t"
		"st Z, %D1 \n\t"
		"out %2, __zero_reg__ \n\t"
		:
		: "r"(to), "r"(val), "i"(&RAMPZ)
		: "r30", "r31"
	);
}

void hugemem_write_block(hugemem_ptr_t to, const void *from, size_t size)
{
	// Ensure that the address range to copy from is within 64 kB boundary.
	Assert(((uint32_t)from + size) <= 0x10000);

	if (size > 0) {
		asm volatile(
			"movw r30, %A2 \n\t"
			"out %3, %C2 \n\t"
			"put_%=: \n\t"
			"ld __tmp_reg__, X+ \n\t"
			"st Z+, __tmp_reg__ \n\t"
			"sbiw %A1, 1 \n\t"
			"brne put_%= \n\t"
			"out %3, __zero_reg__ \n\t"
			: "+x"(from), "+w"(size)
			: "r"(to), "i"(&RAMPZ)
			: "r30", "r31"
		);
	}
}
# endif /* __GNUC__ */

# ifdef __ICCAVR__
void hugemem_read_block(void *to, const hugemem_ptr_t from, size_t size)
{
	uint8_t *to_ptr;
	uint8_t __huge *from_ptr;

	// Ensure that the address range to copy to is within 64 kB boundary.
	Assert(((uint32_t)to + size) <= 0x10000);

	to_ptr = (uint8_t *)to;
	from_ptr = (uint8_t __huge *)from;

	for (; size > 0; size--) {
		*to_ptr++ = *from_ptr++;
	}
}

void hugemem_write_block(hugemem_ptr_t to, const void *from, size_t size)
{
	uint8_t __huge *to_ptr;
	uint8_t *from_ptr;

	// Ensure that the address range to copy from is within 64 kB boundary.
	Assert(((uint32_t)from + size) <= 0x10000);

	to_ptr = (uint8_t __huge *)to;
	from_ptr = (uint8_t *)from;

	for (; size > 0; size--) {
		*to_ptr++ = *from_ptr++;
	}
}
# endif /* __ICCAVR__ */
#endif /* CONFIG_HAVE_HUGEMEM */
