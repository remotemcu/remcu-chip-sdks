/* =========================================================================== *
 * Copyright (c) 2015-2017, Infineon Technologies AG                                *
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
 *                                                                                                                                                                                                                                                                                                                   *
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
 * ========================================================================== */

/**
 * @file
 * @date 15 April, 2017
 * @version 1.0.0
 *
 * @brief CCU4 concatenation demo example
 *
 * The example show how to concatenate to CCU4x slice timers.
 * The example provides an API (see timer.h) to treat both slices as a 32bit timer.
 * The timer has a resolution of 1/fCPU
 *
 * In the example LED1 toggles at a frequency of 1Hz (polling the timer) and LED2 toogles at a frequency of 2Hz (using the user callback)
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 *
 */

/*********************************************************************************************************************
 * HEADER FILES
 ********************************************************************************************************************/
#include "xmc_gpio.h"
#include "timer.h"

/*********************************************************************************************************************
 * MACROS
 ********************************************************************************************************************/
#define LED1 P5_9
#define LED2 P5_8

void timer_cb(void)
{
  XMC_GPIO_ToggleOutput(LED2);

  TIMER_Stop();
  TIMER_Clear();
  TIMER_Start(288000000U);
}

int main(void)
{
  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(LED2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

  TIMER_Init(0);

  TIMER_Start(288000000U);

  while(1U)
  {
    if (TIMER_GetTime() > 144000000U)
    {
      XMC_GPIO_SetOutputHigh(LED1);
    }
    else
    {
      XMC_GPIO_SetOutputLow(LED1);
    }
  }
}
