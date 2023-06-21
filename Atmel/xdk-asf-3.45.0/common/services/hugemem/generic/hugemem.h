/**
 * \file
 *
 * \brief Generic implementation of huge data memory access
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
#ifndef GENERIC_HUGEMEM_H_INCLUDED
#define GENERIC_HUGEMEM_H_INCLUDED

#include <stdint.h>
#include <string.h>

/**
 * \weakgroup hugemem_group
 * @{
 */

/**
 * \internal
 * \defgroup hugemem_generic_group Generic hugemem implementation.
 *
 * These functions are needed for code compatibility between 8- and 32-bit AVR,
 * as well as a different application configurations on 8-bit AVR, i.e., if huge
 * data memory is optional.
 */

typedef void * hugemem_ptr_t;

#define HUGEMEM_NULL    NULL

static inline uint8_t hugemem_read8(const hugemem_ptr_t from)
{
	return *(uint8_t *)from;
}

static inline uint16_t hugemem_read16(const hugemem_ptr_t from)
{
	return *(uint16_t *)from;
}

static inline uint32_t hugemem_read32(const hugemem_ptr_t from)
{
	return *(uint32_t *)from;
}

static inline void hugemem_read_block(void *to, const hugemem_ptr_t from,
		size_t size)
{
	memcpy(to, from, size);
}

static inline void hugemem_write8(hugemem_ptr_t to, uint8_t val)
{
	*(uint8_t *)to = val;
}

static inline void hugemem_write16(hugemem_ptr_t to, uint16_t val)
{
	*(uint16_t *)to = val;
}


static inline void hugemem_write32(hugemem_ptr_t to, uint32_t val)
{
	*(uint32_t *)to = val;
}

static inline void hugemem_write_block(hugemem_ptr_t to, const void *from,
		size_t size)
{
	memcpy(to, from, size);
}

//@}

#endif /* GENERIC_HUGEMEM_H */
