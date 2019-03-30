/*
 * Copyright (C) 2014 Infineon Technologies AG. All rights reserved.
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
 * @date 05 Dec, 2014
 * @version 1.0.0
 *
 * @brief RTC demo example
 *
 * The RTC demo example programs the alarm to 1 minute after the start of the application
 * The triggered interrupt will stop blinking LED1 (P1.1) of RelaxKit
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 *
 */

#include <xmc_scu.h>
#include <xmc_rtc.h>
#include <xmc_gpio.h>

#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 500

#define LED1 P1_1

XMC_RTC_CONFIG_t rtc_config =
{
  .alarm.minutes = 1U,
  .prescaler = 0x7fffU
};

void alarm_handler(void)
{
	/* Stop SysTick timer */
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; 
  XMC_GPIO_SetOutputHigh(LED1);
}

void SCU_0_IRQHandler(void)
{
	XMC_SCU_IRQHandler(0);
}

void SysTick_Handler(void)
{
  static uint32_t ticks = 0;

  ticks++;
  if (ticks == TICKS_WAIT)
  {
	  XMC_GPIO_ToggleOutput(LED1);
	  ticks = 0;
  }
}

int main(void)
{
  XMC_SCU_HIB_EnableHibernateDomain();
	XMC_SCU_HIB_SetRtcClockSource(XMC_SCU_HIB_RTCCLKSRC_OSI);
	
  XMC_RTC_Init(&rtc_config);
  XMC_RTC_EnableEvent(XMC_RTC_EVENT_ALARM);
	
	XMC_SCU_INTERRUPT_SetEventHandler(XMC_SCU_INTERRUPT_EVENT_RTC_ALARM, alarm_handler);
  XMC_SCU_INTERRUPT_EnableEvent(XMC_SCU_INTERRUPT_EVENT_RTC_ALARM);
  
	NVIC_SetPriority(SCU_0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 63, 0));
  NVIC_EnableIRQ(SCU_0_IRQn);

	XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	
	SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);
	
  XMC_RTC_Start();

  while(1)
  {
	  /* Infinite loop */
  }
}
