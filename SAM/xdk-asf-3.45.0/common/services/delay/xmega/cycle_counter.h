/**
 * \file
 *
 * \brief AVR functions for busy-wait delay loops
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
#ifndef _CYCLE_COUNTER_H_
#define _CYCLE_COUNTER_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <compiler.h>

/**
 * @name Convenience functions for busy-wait delay loops
 *
 * @def delay_cycles
 * @brief Delay program execution for a specified number of CPU cycles.
 * @param n number of CPU cycles to wait
 *
 * @def cpu_delay_ms
 * @brief Delay program execution for a specified number of milliseconds.
 * @param delay number of milliseconds to wait
 * @param f_cpu CPU frequency in Hertz
 *
 * @def cpu_delay_us
 * @brief Delay program execution for a specified number of microseconds.
 * @param delay number of microseconds to wait
 * @param f_cpu CPU frequency in Hertz
 *
 * @def cpu_ms_2_cy
 * @brief Convert milli-seconds into CPU cycles.
 * @param ms number of milliseconds
 * @param f_cpu CPU frequency in Hertz
 * @return the converted number of CPU cycles
 *
 * @def cpu_us_2_cy
 * @brief Convert micro-seconds into CPU cycles.
 * @param ms number of microseconds
 * @param f_cpu CPU frequency in Hertz
 * @return the converted number of CPU cycles
 *
 * @{
 */
__always_optimize
static inline void __portable_avr_delay_cycles(unsigned long n)
{
	while (n) {
		barrier();
		n--;
	}
}

#if !defined(__DELAY_CYCLE_INTRINSICS__)
#	define delay_cycles            __portable_avr_delay_cycles
#	define cpu_ms_2_cy(ms, f_cpu)  (((uint64_t)(ms) * (f_cpu) / 6 + 999) / 1e3)
#	define cpu_us_2_cy(us, f_cpu)  (((uint64_t)(us) * (f_cpu) / 6 + 999999ul) / 1e6)
#else
#  if defined(__GNUC__)
#	define delay_cycles            __builtin_avr_delay_cycles
#  elif defined(__ICCAVR__)
#	define delay_cycles            __delay_cycles
#  endif
#	define cpu_ms_2_cy(ms, f_cpu)  (((uint64_t)(ms) * (f_cpu) + 999) / 1e3)
#	define cpu_us_2_cy(us, f_cpu)  (((uint64_t)(us) * (f_cpu) + 999999ul) / 1e6)
#endif

#define cpu_delay_ms(delay, f_cpu) delay_cycles((uint64_t)cpu_ms_2_cy(delay, f_cpu))
#define cpu_delay_us(delay, f_cpu) delay_cycles((uint64_t)cpu_us_2_cy(delay, f_cpu))
//! @}


#ifdef __cplusplus
}
#endif

#endif /* _CYCLE_COUNTER_H_ */
