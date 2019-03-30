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
 * @date 18 Feb, 2015
 * @version 1.0.0
 *
 * @brief USB demo example
 *
 * The example implements a Generic HID Class application.
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 *
 */
#include "GenericHID.h"

/* Clock configuration */
/* fPLL = 288MHz */
/* fSYS = 144MHz */
/* fUSB = 48MHz */
const XMC_SCU_CLOCK_CONFIG_t clock_config =
{
  .syspll_config.p_div = 2,
  .syspll_config.n_div = 48,
  .syspll_config.k_div = 1,
  .syspll_config.mode = XMC_SCU_CLOCK_SYSPLL_MODE_NORMAL,
  .syspll_config.clksrc = XMC_SCU_CLOCK_SYSPLLCLKSRC_OSCHP,
  .enable_oschp = true,
  .calibration_mode = XMC_SCU_CLOCK_FOFI_CALIBRATION_MODE_FACTORY,
  .fsys_clksrc = XMC_SCU_CLOCK_SYSCLKSRC_PLL,
  .fsys_clkdiv = 2,
  .fcpu_clkdiv = 1,
  .fccu_clkdiv = 1,
  .fperipheral_clkdiv = 1
};

void SystemCoreClockSetup(void)
{
  /* Setup settings for USB clock */
  XMC_SCU_CLOCK_Init(&clock_config);

  XMC_SCU_CLOCK_SetUsbClockDivider(6);
  XMC_SCU_CLOCK_SetUsbClockSource(XMC_SCU_CLOCK_USBCLKSRC_SYSPLL);
  XMC_SCU_CLOCK_EnableClock(XMC_SCU_CLOCK_USB);

  SystemCoreClockUpdate();
}

/**
 * Main program entry point. This routine configures the hardware required by
 * the application, then enters a loop to run the application tasks in sequence.
 */
int main(void)
{
  XMC_GPIO_SetMode(LED1,XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(LED2,XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  USB_Init();

  while (1)
  {
	HID_Device_USBTask(&Generic_HID_Interface);
  }

}

