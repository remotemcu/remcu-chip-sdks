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
 * @date 04 Jul, 2017
 * @version 1.0.0
 *
 * @brief Watchdog in prewarning mode demo example
 *
 * Watchdog example in which the watchdog needs to be feed every second
 * The example feeds the watchdog 10 times (see blinking LED1).
 * The first crossing of the upper bound triggers the an alarm
 * since pre-warning is enabled. The alarm signal is routed as request to the SCU,
 * where it is promoted to NMI in this example. In the NMI handler the LED2 is toggle.
 * Only the next overflow results a reset request.
 * After the reset the device checks the reason for the last reset.
 * If it was due to a failure to feed the WDT the LED1 will blink rapidly.
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 *
 */

#include <xmc_wdt.h>
#include <xmc_scu.h>
#include <xmc_gpio.h>

#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 1000
#define MAX_NUM_FEEDS 10

#define LED1 P5_9
#define LED2 P5_8

XMC_WDT_CONFIG_t wdt_config =
{
  .window_lower_bound = 30000,
  .window_upper_bound = 35000,
  .service_pulse_width = 255,
  .prewarn_mode = true
};

void SysTick_Handler(void)
{
  static uint32_t ticks = 0;
  static uint32_t feeds = 0;

  ticks++;
  if (ticks == TICKS_WAIT && feeds < MAX_NUM_FEEDS)
  {
    XMC_GPIO_ToggleOutput(LED1);
    XMC_WDT_Service();
    ticks = 0;
    feeds++;
  }
}

void NMI_Handler(void)
{
  XMC_GPIO_ToggleOutput(LED2);
}

int main(void)
{
  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(LED2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

  if ((XMC_SCU_RESET_GetDeviceResetReason() & XMC_SCU_RESET_REASON_WATCHDOG) != 0)
  {
	while(1)
	{
	  XMC_GPIO_ToggleOutput(LED1);
      for (int i= 0; i < 1000000; ++i)
      {
    	__NOP();
      }

	}
  }

  /* Clear system reset status */
  XMC_SCU_RESET_ClearDeviceResetReason();

  /* Use standby clock as watchdog clock source */
  XMC_SCU_HIB_EnableHibernateDomain();
  XMC_SCU_CLOCK_SetWdtClockSource(XMC_SCU_CLOCK_WDTCLKSRC_STDBY);
  XMC_SCU_CLOCK_EnableClock(XMC_SCU_CLOCK_WDT);

  /* Promote the prewarning alarm event to NMI */
  XMC_SCU_INTERRUPT_EnableEvent(XMC_SCU_INTERRUPT_EVENT_WDT_WARN);
  XMC_SCU_INTERRUPT_EnableNmiRequest(XMC_SCU_NMIREQ_WDT_WARN);

  XMC_WDT_Init(&wdt_config);

  XMC_WDT_Start();

  /* Feed the watchdog periodically every 1s */
  SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

  while(1)
  {
	/* Infinite loop */
  }
}
