/* =========================================================================== *
 * Copyright (c) 2015-2017, Infineon Technologies AG                           *
 * All rights reserved.                                                        *
 *                                                                             *
 * Redistribution and use in source and binary forms, with or without          *
 * modification, are permitted provided that the following conditions are met: *
 * Redistributions of source code must retain the above copyright notice, this *
 * list of conditions and the following disclaimer. Redistributions in binary  *
 * form must reproduce the above copyright notice, this list of conditions and *
 * the following disclaimer in the documentation and/or other materials        *
 * provided with the distribution. Neither the name of the copyright holders   *
 * nor the names of its contributors may be used to endorse or promote         *
 * products derived from this software without specific prior written          *
 * permission.                                                                 *
 *                                                                             *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" *
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,       *
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      *
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR           *
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,       *
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,         *
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; *
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,    *
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR     *
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF      *
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                                  *
 * To improve the quality of the software, users are encouraged to share       *
 * modifications, enhancements or bug fixes with                               *
 * Infineon Technologies AG (dave@infineon.com).                               *
 *                                                                             *
 * =========================================================================== */

/**
 * @file
 * @date 15 April, 2017
 * @version 1.0.0
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 *
 */

#ifndef TIMER_H
#define TIMER_H

#include <xmc_common.h>

/**
 * Timer initialization
 *
 * @param divider The CCUx timer base frequency is fCPU. The user can use a divider to slow down it.
 *                divider alowed values: 0(2^0), 1(2^1), 2(2^2), 3(2^3), 4(2^4), 5(2^5), ..., 15(2^15)
 *
 */
void TIMER_Init(uint32_t divider);

/**
 * Timer start
 *
 * @param ticks After the given number of ticks is reached an ISR will be triggered
 *
 * The user can handle the event implementing timer_cb() function
 */
void TIMER_Start(uint32_t ticks);

/**
 * Timer stop
 */
void TIMER_Stop(void);

/**
 * Timer clear
 */
void TIMER_Clear(void);

/**
 * Timer get timer
 */
uint32_t TIMER_GetTime(void);

#endif
