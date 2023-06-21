/**
 * \file
 *
 * \brief Hamming ECC software implementation.
 *
 * This file contains a software Hamming ECC implementation.
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

#ifndef ECC_SW_H_INCLUDED
#define ECC_SW_H_INCLUDED

#include "compiler.h"

/**
 *  These are the possible errors when trying to verify a block of data encoded
 *  using a Hamming code:
 *
 *  \section Errors
 *   - HAMMING_ERROR_SINGLE_BIT
 *   - HAMMING_ERROR_ECC
 *   - HAMMING_ERROR_MULTIPLE_BITS
 */

/*  A single bit was incorrect but has been recovered. */
#define HAMMING_ERROR_SINGLE_BIT         1

/* The original code has been corrupted. */
#define HAMMING_ERROR_ECC               2

/* Multiple bits are incorrect in the data and they cannot be corrected. */
#define HAMMING_ERROR_MULTIPLE_BITS      3


void hamming_compute_256x(const uint8_t *puc_data, uint32_t dw_size,
		uint8_t *puc_code);
uint32_t hamming_verify_256x(uint8_t *puc_data, uint32_t dw_size,
		const uint8_t *puc_code);

#endif /* ECC_SW_H_INCLUDED */
