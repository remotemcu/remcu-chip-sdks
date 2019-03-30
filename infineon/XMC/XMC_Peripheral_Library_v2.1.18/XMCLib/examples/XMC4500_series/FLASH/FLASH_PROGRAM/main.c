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
 * @brief Flash demo example
 *
 * The LED1 (P1.1) of the RelaxKit is switched on.
 * The flash example erases the logical sector 11.
 * Then programs a page in the mentioned logical sector with a given data pattern.
 * Finally the demo code checks the whether the data is programmed correctly.
 * If data is not programmed correctly LED1 of the RelaxKit will blink,
 * otherwise the LED1 will switch off.
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 *
 */

#include "xmc_gpio.h"
#include "xmc_flash.h"

#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 500

#define LED1 P1_1

uint32_t data[XMC_FLASH_WORDS_PER_PAGE] =
{
  0x11111111U, 0x22222222U, 0x33333333U, 0x44444444U,
  0x55555555U, 0x66666666U, 0x77777777U, 0x88888888U,
  0x99999999U, 0xaaaaaaaaU, 0xbbbbbbbbU, 0xccccccccU,
  0xddddddddU, 0xeeeeeeeeU, 0xffffffffU, 0000000000U,
  0x11111111U, 0x22222222U, 0x33333333U, 0x44444444U,
  0x55555555U, 0x66666666U, 0x77777777U, 0x88888888U,
  0x99999999U, 0xaaaaaaaaU, 0xbbbbbbbbU, 0xccccccccU,
  0xddddddddU, 0xeeeeeeeeU, 0xffffffffU, 0000000000U,
  0x11111111U, 0x22222222U, 0x33333333U, 0x44444444U,
  0x55555555U, 0x66666666U, 0x77777777U, 0x88888888U,
  0x99999999U, 0xaaaaaaaaU, 0xbbbbbbbbU, 0xccccccccU,
  0xddddddddU, 0xeeeeeeeeU, 0xffffffffU, 0000000000U,
  0x11111111U, 0x22222222U, 0x33333333U, 0x44444444U,
  0x55555555U, 0x66666666U, 0x77777777U, 0x88888888U,
  0x99999999U, 0xaaaaaaaaU, 0xbbbbbbbbU, 0xccccccccU,
  0xddddddddU, 0xeeeeeeeeU, 0xffffffffU, 0000000000U
};

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
  const uint32_t *address;
  const uint32_t *ptr_data;
  uint32_t count;
  uint32_t status;

  /* LED1 will light during the program process */
  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetOutputHigh(LED1);

  XMC_FLASH_EraseSector(XMC_FLASH_SECTOR_11);
  XMC_FLASH_ProgramPage(XMC_FLASH_SECTOR_11, data);

  /* Check programming */
  address = XMC_FLASH_SECTOR_11;
  ptr_data = data;
  status = 0;
  for (count = 0; count < XMC_FLASH_WORDS_PER_PAGE; ++count)
  {
    if (*address != *ptr_data)
    {
      ++status;
    }
    ++address;
    ++ptr_data;
  }

  if (status == 0)
  {
    /* Blink LED to indicate success */
    SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);
  }

  while(1)
  {
	  /* Infinite loop */
  }
}
