/**
 * \file
 *
 * \brief Graphical Widget toolkit
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

#include <stdint.h>
#include <stdlib.h>
#include <membag.h>
#include <string.h>
#include <wtk.h>

/**
 * \weakgroup wtk_group
 * @{
 */

/**
 * \brief Rescale 8-bit value.
 * \internal
 *
 * This function is used by, e.g., the slider widget for computing the slider
 * knob position from a given value and vice versa. It returns a value with the
 * same data width as the input, meaning \a value cannot exceed \a from_scale,
 * or overflows will occur.\par
 *
 * The formula is: \code new_value = (value / from_scale) * to_scale \endcode
 *
 * \param value Value to rescale.
 * \param from_scale Maximum of old scale for value.
 * \param to_scale Maximum of scale for new value.
 *
 * \return Rescaled 8-bit value.
 */
uint8_t wtk_rescale_value(uint8_t value, uint8_t from_scale, uint8_t to_scale)
{
	uint16_t new_value;

	Assert(to_scale > 0);
	Assert(from_scale > 0);
	Assert(value <= from_scale);

	new_value = value;
	new_value *= to_scale;
	new_value /= from_scale;

	return new_value;
}

/**
 * This function copies the string contents, including the zero terminator,
 * from source to destination. The caller is responsible for providing
 * memory for the destination string, either on the stack, static, or
 * dynamically allocated.
 *
 * \param dest Destination string.
 * \param source Source string, zero terminated.
 */
void wtk_copy_string(char *dest, char const *source)
{
	Assert(dest);
	Assert(source);

	/* Copy characters, including zero-terminator. */
	while (*source != '\0') {
		*dest = *source;
		++dest;
		++source;
	}

	/* Copy the terminating zero. */
	*dest = *source;
}

/** @} */
