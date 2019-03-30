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
 * @date 01 Aug, 2014
 * @version 0.1.0
 *
 * @brief Watchdog demo example
 *
 * Watchdog example in which the watchdog needs to be feed every second
 * The example feeds the watchdog 25 times (see blinking LED), after that the device goes into reset
 * since no more feeding occurs simulating a fault (see LED stays on).
 *
 * History <br>
 *
 * Version 0.1.0 Initial <br>
 *
 */

#include <xmc_wdt.h>
#include <xmc_scu.h>
#include <xmc_gpio.h>

#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 1000
#define MAX_NUM_FEEDS 25

#define LED1 P1_1

XMC_WDT_CONFIG_t wdt_config =
{
  .window_lower_bound = 30000,
  .window_upper_bound = 35000,
  .service_pulse_width = 255
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


int main(void)
{
  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

  if ((XMC_SCU_RESET_GetDeviceResetReason() & XMC_SCU_RESET_REASON_WATCHDOG) != 0)
  {
    XMC_GPIO_SetOutputHigh(LED1);

	  while(1)
	  {
	    /* Infinite loop */
	  }
  }

  /* Clear system reset status */
  /* Note: API will be added in the next release */
  SCU_RESET->RSTCLR |= SCU_RESET_RSTCLR_RSCLR_Msk;

  /* Use standby clock as watchdog clock source */
  XMC_SCU_HIB_EnableHibernateDomain();
  XMC_SCU_CLOCK_SetWdtClockSource(XMC_SCU_CLOCK_WDTCLKSRC_STDBY);
  XMC_SCU_CLOCK_EnableClock(XMC_SCU_CLOCK_WDT);

  XMC_WDT_Init(&wdt_config);

  XMC_WDT_Start();

  /* Feed the watchdog periodically every 1s */
  SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

  while(1)
  {
	/* Infinite loop */
  }
}
