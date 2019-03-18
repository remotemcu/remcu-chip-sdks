/**
 * \file
 *
 * \brief 32-bit CRC header.
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef CRC32_H
#define CRC32_H


#include <compiler.h>


/**
 * \defgroup common_services_crc32 CRC-32 calculation service
 *
 * See \ref common_services_crc32_quickstart.
 *
 * This service enables the user to calculate 32-bit CRC using the polynomial
 * defined in the IEEE 802.3 standard, with support for multiple data blocks
 * of arbitrary sizes, and any alignment in memory.
 *
 * @{
 */


//! Type to contain 32-bit CRC.
typedef uint32_t crc32_t;


#ifdef __cplusplus
extern "C" {
#endif

enum status_code crc32_recalculate(const void *data, size_t length, crc32_t *crc);

#ifdef __cplusplus
}
#endif


/**
 * \brief Calculate 32-bit CRC for initial block
 *
 * This function calculates the CRC for the specified data block, which may be
 * first of an arbitrary number of blocks.
 *
 * The actual calculation is done in \ref crc32_recalculate(), while this
 * function just sets up the initial CRC value.
 *
 * \param[in] data Address of data.
 * \param[in] length Length of data.
 * \param[out] crc Address of variable to store the calculated CRC in.
 *
 * \return Status of calculation.
 * \retval STATUS_OK if calculation succeeded.
 * \retval <other> if calculation failed somehow.
 *
 * \note To calculate the CRC of multiple blocks, use this function first, then
 * \ref crc32_recalculate() for the following blocks.
 */
static inline enum status_code crc32_calculate(const void *data, size_t length,
		crc32_t *crc)
{
	*crc = 0;

	return crc32_recalculate(data, length, crc);
}

/** @} */

/**
 * \page common_services_crc32_quickstart Quick Start Guide for CRC-32
 *
 * To use this service, the user must supply a \ref crc32_t "container" variable
 * for the CRC and call \ref crc32_calculate() with the parameters for the first
 * block in the dataset. For subsequent blocks, \ref crc32_recalculate() must be
 * used.
 *
 * \note The user may also initialize the container with a known CRC value and
 * use that as the "seed" for \ref crc32_recalculate().
 *
 *
 * \section common_services_crc32_quickstart_code Example Code
 *
\code
	uint8_t block1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	uint8_t block2[6] = {0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

	crc32_t my_crc;

	crc32_calculate(block1, sizeof(block1), &my_crc);
	crc32_recalculate(block2, sizeof(block2), &my_crc);
\endcode
 *
 */

#endif // CRC32_H