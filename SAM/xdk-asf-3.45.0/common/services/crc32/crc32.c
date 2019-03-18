/**
 * \file
 *
 * \brief 32-bit CRC implementation.
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

#include "crc32.h"
#include <status_codes.h>


/**
 * Convenience typedef for words.
 *
 * \note This type has an architecture dependent size, and is used to optimize
 * the CRC algorithm with regards to the number of databus accesses.
 */
typedef unsigned int word_t;

/** Polynomial for 32-bit CRC in IEEE 802.3. */
#define CRC32_POLYNOMIAL     0xEDB88320UL

/** Convenience macro for inverting the CRC. */
#define COMPLEMENT_CRC(c)    ((c) ^ 0xffffffffUL)

/** Convenience macro for size of a word. */
#define WORD_SIZE            (sizeof(word_t))

/** Bitmask for word-aligning an address. */
#define WORD_ALIGNMENT_MASK  ~((uintptr_t)WORD_SIZE - 1)


/**
 * \internal
 * \brief Recalculate 32-bit CRC for bytes within a word
 *
 * \param[in] data Data to recalculate for.
 * \param[in] crc Initial/current CRC value.
 * \param[in] bytes Number of data bytes in word.
 *
 * \return New CRC value.
 *
 * \attention This implementation assumes a little-endian architecture.
 */
static inline crc32_t _crc32_recalculate_bytes_helper(word_t data,
		crc32_t crc, uint_fast8_t bytes)
{
	uint_fast8_t bit;

	crc ^= data;

	for (bit = 8 * bytes; bit > 0; bit--) {
		if (crc & 1) {
			crc = (crc >> 1) ^ CRC32_POLYNOMIAL;
		} else {
			crc >>= 1;
		}
	}

	return crc;
}

/**
 * \brief Recalculate 32-bit CRC for another block
 *
 * This function recalculates the CRC according to the polynomial
 * \ref CRC32_POLYNOMIAL for the specified data block and initial CRC value.
 *
 * To reduce the number of databus accesses and thus speed up the calculation,
 * the algorithm is tuned to work with words as much as possible.
 *
 * \param[in] data Address of data.
 * \param[in] length Length of data.
 * \param[in,out] crc Address of variable containing current CRC, and to store
 * recalculated CRC in.
 *
 * \return Status of calculation.
 * \retval STATUS_OK if calculation succeeded.
 * \retval <other> if calculation failed or could not be started.
 *
 * \note To calculate the CRC of multiple blocks, use \ref crc32_calculate()
 * first, then this function for the following blocks.
 *
 * \attention This implementation assumes a little-endian architecture.
 */
enum status_code crc32_recalculate(const void *data, size_t length, crc32_t *crc)
{
	const word_t *word_ptr =
			(word_t *)((uintptr_t)data & WORD_ALIGNMENT_MASK);
	size_t temp_length;
	crc32_t temp_crc = COMPLEMENT_CRC(*crc);
	word_t word;

	// Calculate for initial bytes to get word-aligned
	if (length < WORD_SIZE) {
		temp_length = length;
	} else {
		temp_length = ~WORD_ALIGNMENT_MASK & (WORD_SIZE - (uintptr_t)data);
	}

	if (temp_length) {
		length -= temp_length;

		word = *(word_ptr++);
		word >>= 8 * (WORD_SIZE - temp_length);
		temp_crc = _crc32_recalculate_bytes_helper(word, temp_crc, temp_length);
	}

	// Calculate for whole words, if any
	temp_length = length & WORD_ALIGNMENT_MASK;

	if (temp_length) {
		length -= temp_length;
		temp_length /= WORD_SIZE;

		while (temp_length--) {
			word = *(word_ptr++);
			temp_crc = _crc32_recalculate_bytes_helper(word, temp_crc, WORD_SIZE);
		}
	}

	// Calculate for tailing bytes
	if (length) {
		word = *word_ptr;
		word &= 0xffffffffUL >> (8 * (WORD_SIZE - length));
		temp_crc = _crc32_recalculate_bytes_helper(word, temp_crc, length);
	}

	*crc = COMPLEMENT_CRC(temp_crc);

	return STATUS_OK;
}