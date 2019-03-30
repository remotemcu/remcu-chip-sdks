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
 * @date 04 Aug, 2017
 * @version 1.0.0
 *
 * @brief XMC4200 Application kit SCU HIB example
 *
 * The device starts showing the LED1 on, and will enter internal hibernate after ~5s, indicated by the RESET led. 
 * After ~30s a wakeup event from the RTC will trigger and restart the device. 
 * Additionaly the HIB_IO_0 button can be used to wake up the device before expiring the 30s.
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 *
 */

#include <xmc_gpio.h>
#include <xmc_scu.h>
#include <xmc_rtc.h>

#define LED1 P2_1

const XMC_RTC_CONFIG_t rtc_config =
{
  .alarm.seconds = 30U,
  .prescaler = 0x7fffU
};

const XMC_GPIO_CONFIG_t gpio_config =
{
  .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
  .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW
};

int main(void)
{
  // Check to see if hibernate domain is already active, which could mean
  // that the processor is waking from a hibernation.
  if (XMC_SCU_HIB_IsHibernateDomainEnabled() == true)
  {
    // Read the status bits to see what caused the wake.  Clear the wake
    // source so that the device can be put into hibernation again.
    XMC_SCU_HIB_EVENT_t event = XMC_SCU_HIB_GetEventStatus();
    XMC_SCU_HIB_ClearEventStatus(event);

    XMC_RTC_ClearEvent(XMC_RTC_EVENT_ALARM);

    XMC_SCU_HIB_ClearWakeupEventDetectionStatus();
    XMC_SCU_RESET_ClearDeviceResetReason();
  }
  else
  {
    XMC_SCU_HIB_EnableHibernateDomain();
    XMC_SCU_HIB_SetStandbyClockSource(XMC_SCU_HIB_STDBYCLKSRC_OSI);
    XMC_SCU_HIB_SetRtcClockSource(XMC_SCU_HIB_RTCCLKSRC_OSI);
  }

  XMC_RTC_Stop();

  // Do stuff
  XMC_GPIO_Init(LED1, &gpio_config);

  for(int i = 0; i < (SystemCoreClock / 2); ++i)
  {
    __NOP();
  }

  XMC_SCU_HIB_EnableEvent(XMC_SCU_HIB_EVENT_WAKEUP_ON_RTC);

  XMC_RTC_Init(&rtc_config);

  XMC_RTC_EnableHibernationWakeUp(XMC_RTC_WAKEUP_EVENT_ON_ALARM);

  XMC_RTC_Start();

  XMC_SCU_HIB_EnterHibernateStateEx(XMC_SCU_HIB_HIBERNATE_MODE_INTERNAL);

  while(1);
}
