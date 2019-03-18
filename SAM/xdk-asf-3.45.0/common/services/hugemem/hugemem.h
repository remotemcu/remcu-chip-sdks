/**
 * \file
 *
 * \brief Huge data memory space access
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
#ifndef HUGEMEM_H_INCLUDED
#define HUGEMEM_H_INCLUDED

#include <stdint.h>
#include <stddef.h>

#if defined(__AVR32__) || defined(__ICCAVR32__)
# include <generic/hugemem.h>
#elif defined(__AVR__) || defined (__ICCAVR__)
# include <avr8/hugemem.h>
#else
# error Unknown architecture passed to hugemem interface.
# error Expected __AVR32__ or __AVR__.
#endif

/**
 * \defgroup hugemem_group Data in Huge Data Memory Space
 *
 * Due to shortcomings of the GCC compiler for 8-bit AVR, custom functions are
 * needed for access to data beyond the 64 kB boundary, i.e., addresses that
 * are larger than 16-bit.
 *
 * The definition of huge memory space can differ between architectures, so the
 * implementation is architecture specific.
 *
 * This module supplies functions for copying a number of bytes between huge
 * and 64 kB data memory space, and is needed solely for code compatibility
 * across compilers.
 *
 * @{
 */

/**
 * \typedef hugemem_ptr_t
 *
 * \brief Type to use for pointers to huge memory.
 */

/**
 * \def HUGEMEM_NULL
 *
 * \brief Hugemem null pointer, similar to NULL, but works across different
 * platforms.
 */

/**
 * \fn uint_fast8_t hugemem_read8(const hugemem_ptr_t from)
 *
 * \brief Read 8-bit value stored at huge memory address \a from.
 */

/**
 * \fn uint_fast16_t hugemem_read16(const hugemem_ptr_t from)
 *
 * \brief Read 16-bit value stored at huge memory address \a from.
 */

/**
 * \fn void hugemem_read_block(void *to, const hugemem_ptr_t from, size_t size)
 *
 * \brief Read \a size bytes from huge memory address \a from into buffer at
 * address \a to.
 */

/**
 * \fn uint_fast32_t hugemem_read32(const hugemem_ptr_t from)
 *
 * \brief Read 32-bit value stored at huge memory address \a from.
 */

/**
 * \fn void hugemem_write8(hugemem_ptr_t to, uint_fast8_t val)
 *
 * \brief Write 8-bit value \a val to huge memory address \a to.
 */

/**
 * \fn void hugemem_write16(hugemem_ptr_t to, uint_fast16_t val)
 *
 * \brief Write 16-bit value \a val to huge memory address \a to.
 */

/**
 * \fn void hugemem_write32(hugemem_ptr_t to, uint_fast32_t val)
 *
 * \brief Write 32-bit value \a val to huge memory address \a to.
 */

/**
 * \fn void hugemem_write_block(hugemem_ptr_t to, const void *from, size_t size)
 *
 * \brief Write \a size bytes from buffer at address \a from to huge memory
 * address \a to.
 */

//@}

#endif /* HUGEMEM_H_INCLUDED */
