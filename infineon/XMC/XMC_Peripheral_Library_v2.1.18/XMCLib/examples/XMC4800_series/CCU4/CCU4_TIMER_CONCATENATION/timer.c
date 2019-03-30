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

/*********************************************************************************************************************
 * HEADER FILES
 ********************************************************************************************************************/
#include "xmc_gpio.h"
#include "timer.h"
#include "timer.h"

#include <xmc_scu.h>
#include <xmc_ccu4.h>

/*********************************************************************************************************************
 * API IMPLEMENTATION
 ********************************************************************************************************************/

/**
 * User timer callback
 */
__WEAK void timer_cb()
{

}

void CCU40_0_IRQHandler(void)
{
  timer_cb();
}

void TIMER_Init(uint32_t divider)
{
  XMC_CCU4_SLICE_COMPARE_CONFIG_t slice_config;

  XMC_CCU4_SLICE_EVENT_CONFIG_t event_config =
  {
    .mapped_input = CCU40_IN0_SCU_GSC40,
    .edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_RISING_EDGE
  };

  /* Init CCU4x module */
  XMC_CCU4_Init(CCU40, XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR);

  XMC_STRUCT_INIT(slice_config);

  slice_config.prescaler_initval = divider;
  XMC_CCU4_SLICE_CompareInit(CCU40_CC40, &slice_config);

  slice_config.timer_concatenation = true;
  XMC_CCU4_SLICE_CompareInit(CCU40_CC41, &slice_config);

  XMC_CCU4_SLICE_SetTimerPeriodMatch(CCU40_CC40, 0xffffU);
  XMC_CCU4_SLICE_SetTimerPeriodMatch(CCU40_CC41, 0xffffU);

  // Configure event to start synchronously the two slices
  XMC_CCU4_SLICE_ConfigureEvent(CCU40_CC40, XMC_CCU4_SLICE_EVENT_0, &event_config);
  XMC_CCU4_SLICE_ConfigureEvent(CCU40_CC41, XMC_CCU4_SLICE_EVENT_0, &event_config);

  XMC_CCU4_SLICE_StartConfig(CCU40_CC40, XMC_CCU4_SLICE_EVENT_0, XMC_CCU4_SLICE_START_MODE_TIMER_START);
  XMC_CCU4_SLICE_StartConfig(CCU40_CC41, XMC_CCU4_SLICE_EVENT_0, XMC_CCU4_SLICE_START_MODE_TIMER_START);

  // Configure event to stop synchronously the two slices
  event_config.edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_FALLING_EDGE;
  XMC_CCU4_SLICE_ConfigureEvent(CCU40_CC40, XMC_CCU4_SLICE_EVENT_1, &event_config);
  XMC_CCU4_SLICE_ConfigureEvent(CCU40_CC41, XMC_CCU4_SLICE_EVENT_1, &event_config);

  XMC_CCU4_SLICE_StopConfig(CCU40_CC40, XMC_CCU4_SLICE_EVENT_1, XMC_CCU4_SLICE_END_MODE_TIMER_STOP);
  XMC_CCU4_SLICE_StopConfig(CCU40_CC41, XMC_CCU4_SLICE_EVENT_1, XMC_CCU4_SLICE_END_MODE_TIMER_STOP);

  // Assign interrupt node and set priority
  XMC_CCU4_SLICE_SetInterruptNode(CCU40_CC41, XMC_CCU4_SLICE_IRQ_ID_COMPARE_MATCH_UP, XMC_CCU4_SLICE_SR_ID_0);

  NVIC_SetPriority(CCU40_0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 63, 0));
  NVIC_EnableIRQ(CCU40_0_IRQn);

  // Enable clock to both slices
  XMC_CCU4_EnableClock(CCU40, (uint8_t)0);
  XMC_CCU4_EnableClock(CCU40, (uint8_t)1);
}

void TIMER_Start(uint32_t ticks)
{
  XMC_CCU4_SLICE_SetTimerCompareMatch(CCU40_CC40, ticks & 0xffffU);
  XMC_CCU4_SLICE_SetTimerCompareMatch(CCU40_CC41, ticks >> 16U);

  XMC_CCU4_EnableShadowTransfer(CCU40, XMC_CCU4_SHADOW_TRANSFER_SLICE_0 | XMC_CCU4_SHADOW_TRANSFER_SLICE_1);

  XMC_CCU4_SLICE_EnableEvent(CCU40_CC41, XMC_CCU4_SLICE_IRQ_ID_COMPARE_MATCH_UP);

  /* Synchronous start of CCU4x timer slices */
  XMC_SCU_SetCcuTriggerHigh(XMC_SCU_CCU_TRIGGER_CCU40);
}

void TIMER_Stop(void)
{
  XMC_CCU4_SLICE_DisableEvent(CCU40_CC41, XMC_CCU4_SLICE_IRQ_ID_COMPARE_MATCH_UP);

  /* Synchronous stop of CCU4x timer slices */
  XMC_SCU_SetCcuTriggerLow(XMC_SCU_CCU_TRIGGER_CCU40);
}

void TIMER_Clear()
{
  XMC_CCU4_SLICE_ClearTimer(CCU40_CC40);
  XMC_CCU4_SLICE_ClearTimer(CCU40_CC41);
}

uint32_t TIMER_GetTime(void)
{
  uint32_t time_h = XMC_CCU4_SLICE_GetTimerValue(CCU40_CC41);
  uint32_t time_l = XMC_CCU4_SLICE_GetTimerValue(CCU40_CC40);

  while (XMC_CCU4_SLICE_GetTimerValue(CCU40_CC41) != time_h)
  {
	time_h = XMC_CCU4_SLICE_GetTimerValue(CCU40_CC41);
	time_l = XMC_CCU4_SLICE_GetTimerValue(CCU40_CC40);
  }

  return ((time_h << 16) | time_l);
}
