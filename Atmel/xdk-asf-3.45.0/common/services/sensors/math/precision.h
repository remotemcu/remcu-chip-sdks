/**
 * \file
 *
 * \brief ASF Sensor API Numeric Precision
 *
 * This module defines numeric precision and the real-number representation
 * used in the Atmel Software Framework common sensor service.
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

#ifndef _MATH_PRECISION_H_
#define _MATH_PRECISION_H_

#include "fixed.h"

/**
 * \brief Scalar Value Format and Precision
 *
 * These types define a real number format and precision.  C/C++ source code
 * can be compiled with math libraries in single-precision floating point,
 * double-precision floating point, or fixed-point versions.
 *
 * The type \ref float_t always specifies a C/C++ floating-point type and is a
 * C99 standard type.  The \ref scalar type may be specified as a floating-point
 * or fixed-point type, where the available fixed-point types are \ref fixed_t
 * (C/C++) and type math::fixed (C++ only).
 *
 * Note that whenever the C++ math libraries - math::vector, math::matrix, &c.
 * - are built, \ref scalar must be an alias for float_t or math::fixed and
 * never \ref fixed_t.
 */

#if defined(__GNUC__) && !defined(FLT_EVAL_METHOD)
	typedef float float_t;          /**< clib (C99) floating-point format */
#endif

#if defined (MATH_FIXED_POINT)
# ifdef __cplusplus
	typedef math::fixed scalar;     /**< Fixed-point (C++) scalar type */
# else
	typedef fixed_t scalar;         /**< Fixed-point (C/C++) scalar type */
# endif
#else
	typedef float_t scalar;         /**< Floating-point scalar type */
#endif

typedef scalar scalar_t;

/** \brief scalar 3-dimensional vector */
typedef struct {
	scalar_t    x;
	scalar_t    y;
	scalar_t    z;
} vector3_t;

/** \brief Calculate a vector3_t dot-product */
static inline scalar_t vector3_dot_product(vector3_t const *v,
	vector3_t const *w)
{
	return ((v->x * w->x) + (v->y * w->y) + (v->z * w->z));
}

/** \brief Calculate a vector3_t magnitude */
static inline scalar_t vector3_magnitude(vector3_t const *v)
{
	return sqrt(vector3_dot_product(v,v));
}

/** \brief Scale a vector3_t value (scalar multiplication) */
static inline void vector3_scale(scalar_t s, vector3_t *v)
{
	v->x *= s; v->y *= s; v->z *= s;
}

#endif
