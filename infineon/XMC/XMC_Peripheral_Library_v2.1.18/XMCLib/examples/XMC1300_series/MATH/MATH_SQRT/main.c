/*
 * Copyright (C) 2014-2017 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

/**
 * @file
 * @date 07 Aug, 2017
 * @version 1.0.0
 *
 * @brief XMC1300 Boot MATH coprocessor SQRT example
 *
 * The example demonstrates the usage of the CORDIC coprocessor to calculate the square root of a number
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 *
 */


#include <xmc_common.h>
#include "xmc_math.h"
#include <math.h>

__STATIC_INLINE float q15_to_float(int16_t a) { return (float)a / 0x8000; }
__STATIC_INLINE float q31_to_float(int32_t a) { return (float)a / 0x80000000; }
__STATIC_INLINE int32_t float_to_q15(float a) { return (int16_t)((a * 0x8000) + 0.5); }
__STATIC_INLINE int32_t float_to_q31(float a) { return (int32_t)((a * 0x80000000) + 0.5); }

int main(void)
{
  int32_t a;
  float b, c;
  float error;

  a = XMC_MATH_CORDIC_Q31_Sqrt(float_to_q31(0.1F));
  b = q31_to_float(a);

  c = sqrtf(0.1F);
  error = b - c;

  /* avoid compiler warning */
  (void)error;

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1)
  {
  }
}
