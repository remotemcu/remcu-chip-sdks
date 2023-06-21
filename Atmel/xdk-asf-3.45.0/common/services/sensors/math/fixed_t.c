/**
 * \file
 *
 * \brief ASF Sensor API fixed point math operations
 *
 * This header defines types and operations that support basic fixed-point
 * arithmetic operations.  The \p fixed_t type is a signed 32-bit value that
 * is stored and operated on using integer operations.  The number of
 * fractional bits operated on will be context-specific.
 *
 * The conversion functions and some of the arithmetic functions require
 * a \a Q parameter specifying the number of fractional bits in the operands.
 * Arithmetic functions that do not require the \a Q parameter assume that
 * both operands have the same \a Q format (the same number of fractional bits).
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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

#include "fixed_t.h"

#if defined(__GNUC__)
#  define clzll(n)  __builtin_clzll(n)
#endif

#if defined(__GNUC__) && defined(__AVR__)
#  define log2(x)   (log(x) / log(2))
#endif


/** \brief signed fixed-point range
 *
 * Given a signed fixed-point format \p Qm.f, where \a f represents the number
 * of fractional bits and \a m the number of integer bits, this routine
 * calculates the the number of integer bits \a m required to represent real
 * data types in the interval [\p x_min, \p x_max].
 *
 * The \p x_min and \p x_max interval endpoints are the smallest and largest
 * integer portions, respectively, of the numbers that must be represented in
 * fixed-point.
 *
 * \param   x_min   The smallest signed integer portion of a real type.
 * \param   x_max   The largest signed integer portion of a real type.
 *
 * \return  The required number of integer bits required for
 *          a fixed-point implementation.
 */
int fixed_range(double x_min, double x_max)
{
	const double a = fmax(fabs (x_min), fabs(x_max));
	return (int) (ceil(log2(a + 1)) + 1);
}

/** \brief signed fixed-point resolution
 *
 * Given a signed fixed-point format \p Qm.f, where \a f represents the number
 * of fractional bits and \a m the number of integer bits, this routine
 * calculates the the number of fractional bits \a f required to represent
 * real data types with resolution \f[ \epsilon = \frac{1}{2^{f}} \f].  For
 * example, a signed variable \a A = 3.141 requires \epsilon <= 0.001.
 *
 * \param   epsilon     The required resolution of the fixed-point number.
 *
 * \return  The required number of fractional bits required for
 *          a fixed-point implementation.
 */
int fixed_resolution(double epsilon)
{
	return (int)(epsilon ? ceil (log2(1 / epsilon)) : 0);
}

/** \brief Calculate the square root of an integer
 *
 * This routine calculates the integer square root, \a isqrt(), of a positive
 * integer argument \a n:
 * \f[
 *          isqrt(n) = \lfloor n^{1/2} \rfloor
 * \f]
 * The computed value is the largest positive integer \a m with a square
 * that is less than or equal to the given integer \a n such that
 * \f$ m^{2} \le n \f$.
 *
 * \param   f   A fixed-point value.  Negative values will be computed using
 *              the unsigned magnitude without reporting a domain error.
 * \param   Q   The number of fractional bits in parameter \a f.
 *
 * \return  The integer square root.
 */
fixed_t fixed_sqrt(fixed_t f, int Q)
{
	uint64_t n = (uint64_t) f << Q;
	uint64_t m = 0;

	if (n) {
		int32_t  bshft = (63 - clzll (n)) >> 1;
		uint64_t b = 1LL << bshft;

		do  {
			const uint64_t temp = (m + m + b) << bshft;

			if (n >= temp) {
				m += b;
				n -= temp;
			}

			b >>= 1;

		} while (bshft--);
	}

	return (fixed_t) m;
}
