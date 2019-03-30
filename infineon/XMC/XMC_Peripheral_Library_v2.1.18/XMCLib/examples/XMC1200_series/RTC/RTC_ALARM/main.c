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
 * @brief XMC1200Bot kit RTC demo example
 *
 * The RTC demo example programs the alarm to 1 minute after the start of the application
 * The triggered interrupt will switch off the LED connected to P0.6 of the bootkit
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 *
 */


#include "xmc_rtc.h"
#include "xmc_gpio.h"
#include "xmc_scu.h"

#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 500

#define LED P0_6

XMC_RTC_CONFIG_t rtc_config =
{
  .alarm.minutes = 1U,
  .prescaler = 0x7fffU
};

void SCU_1_IRQHandler(void)
{
  XMC_GPIO_ToggleOutput(LED);
}

int main(void)
{
  XMC_GPIO_SetMode(LED, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

  XMC_RTC_Init(&rtc_config);

  XMC_RTC_EnableEvent(XMC_RTC_EVENT_ALARM);
  XMC_SCU_INTERRUPT_EnableEvent(XMC_SCU_INTERRUPT_EVENT_RTC_ALARM);
  NVIC_SetPriority(SCU_1_IRQn, 3);
  NVIC_EnableIRQ(SCU_1_IRQn);

  XMC_RTC_Start();

  while(1)
  {
	  /* Infinite loop */
  }
}
