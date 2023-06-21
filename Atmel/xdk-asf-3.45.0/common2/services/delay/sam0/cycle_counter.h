/**
 * \file
 *
 * \brief ARM functions for busy-wait delay loops
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
#ifndef CYCLE_COUNTER_H_INCLUDED
#define CYCLE_COUNTER_H_INCLUDED

#include <compiler.h>
#include <clock.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @def F_CPU
 * @brief MCU Clock Frequency (Hertz)
 */
#ifndef F_CPU
#       define F_CPU system_gclk_gen_get_hz(0)
#endif

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

/**
 * \brief Delay loop to delay n number of cycles
 *
 * \note The function runs in internal RAM so that flash wait states
 *       will not affect the delay time.
 *
 * \param n Number of cycles
 */
void portable_delay_cycles(unsigned long n);

#define cpu_ms_2_cy(ms, f_cpu)  \
	(((uint64_t)(ms) * (f_cpu) + (uint64_t)(7e3-1ul)) / (uint64_t)7e3)
#define cpu_us_2_cy(us, f_cpu)  \
	(((uint64_t)(us) * (f_cpu) + (uint64_t)(7e6-1ul)) / (uint64_t)7e6)

#define delay_cycles               portable_delay_cycles

#define cpu_delay_s(delay) delay_cycles(cpu_ms_2_cy(1000 * delay, F_CPU))
#define cpu_delay_ms(delay) delay_cycles(cpu_ms_2_cy(delay, F_CPU))
#define cpu_delay_us(delay) delay_cycles(cpu_us_2_cy(delay, F_CPU))
//! @}


#ifdef __cplusplus
}
#endif

#endif /* CYCLE_COUNTER_H_INCLUDED */
