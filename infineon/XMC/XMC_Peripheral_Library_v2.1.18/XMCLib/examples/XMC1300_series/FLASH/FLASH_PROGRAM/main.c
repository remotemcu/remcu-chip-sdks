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
 * @brief XMC1300 Boot kit flash demo example
 *
 * This example uses the XMC1_flash Low Level Driver to perform flash erase, program and verify operation.
 * The correctness of the different operations can be monitored using the LEDs of the bootkit:
 * - A blinking LED means the flash step found an error.
 * - A lighting LED means the flash step is successful.
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 *
 */

#include <string.h>

#include <xmc_gpio.h>
#include <xmc_flash.h>

#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 500

#define XMC1300_SECTOR50_ADDR        (uint32_t *)0x10032000U
#define XMC1300_SECTOR50_PAGE00_ADDR (uint32_t *)0x10032000U
#define XMC1300_SECTOR50_PAGE01_ADDR (uint32_t *)0x10032100U

/* Pins showing the status of the different different flash operations performed in code below */
#define LED0 P0_0
#define LED1 P0_1
#define LED2 P0_6
#define LED3 P0_7
#define LED4 P0_8
#define LED5 P0_9

bool status0 = true;
bool status1 = true;
bool status2 = true;
bool status3 = true;
bool status4 = true;
bool status5 = true;

/* Periodic interrupt showing the status of the different flash operations performed in code below */
void SysTick_Handler(void)
{
  static uint32_t ticks = 0;

  ticks++;
  if (ticks == TICKS_WAIT)
  {
    if (status0 == false)
    {
      XMC_GPIO_ToggleOutput(LED0);
    }

    if (status1 == false)
    {
      XMC_GPIO_ToggleOutput(LED1);
    }

    if (status2 == false)
    {
      XMC_GPIO_ToggleOutput(LED2);
    }

    if (status3 == false)
    {
      XMC_GPIO_ToggleOutput(LED3);
    }

    if (status4 == false)
    {
      XMC_GPIO_ToggleOutput(LED4);
    }

    if (status5 == false)
    {
      XMC_GPIO_ToggleOutput(LED5);
    }

    ticks = 0;
  }
}

int main(void)
{
  uint32_t *address;
  uint32_t pBuffer[64];
  uint32_t rBuffer[16];
  uint32_t i;

  XMC_GPIO_SetMode(LED0, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(LED2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(LED3, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(LED4, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(LED5, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

  SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

  /* Initial Step: Create a Fibonacci sequence to buffer */
  pBuffer[0] = 0;
  pBuffer[1] = 1;
  for(i = 2; i < 64; ++i)
  {
    pBuffer[i] = pBuffer[i-1] + pBuffer[i-2];
  }

  /* 1st step: Erase sector */
  XMC_FLASH_EraseSector(XMC1300_SECTOR50_ADDR);
  if (XMC_FLASH_GetStatus() != XMC_FLASH_STATUS_OK)
  {
    status0 = false;
    while(1)
    {
      /* Stop sequence */
    }
  }

  /* 2nd step: Program page using the Fibonacci sequence */
  XMC_FLASH_ProgramPage(XMC1300_SECTOR50_PAGE00_ADDR, pBuffer);
  if ( XMC_FLASH_GetStatus() != XMC_FLASH_STATUS_OK)
  {
    status1 = false;
    while(1)
    {
      /* Stop sequence */
    }
  }

  /* 3rd step: Program 4 flash blocks using the first 16 elements of the Fibonacci sequence */
  XMC_FLASH_WriteBlocks(XMC1300_SECTOR50_PAGE01_ADDR, pBuffer, 4U , false);
  if ( XMC_FLASH_GetStatus() != XMC_FLASH_STATUS_OK)
  {
    status2 = true;
    while(1)
    {
      /* Stop sequence */
    }
  }

  /* 4th step: Verify the just programmed blocks */
  XMC_FLASH_VerifyBlocks(XMC1300_SECTOR50_PAGE01_ADDR, pBuffer, 4U);
  if ( XMC_FLASH_GetStatus() != XMC_FLASH_STATUS_OK)
  {
    status3 = true;
    while(1)
    {
      /* Stop sequence */
    }
  }

  /* 5th step: Read blocks and compare to original data */
  XMC_FLASH_ReadBlocks(XMC1300_SECTOR50_PAGE01_ADDR, rBuffer, 4U);

  if (memcmp(pBuffer, rBuffer, 4U * XMC_FLASH_BYTES_PER_BLOCK) != 0)
  {
    status4 = true;
    while(1)
    {
      /* Stop sequence */
    }
  }

  /* 6th step: Erase page and verify the contents of flash after erasing */
  XMC_FLASH_ErasePages(XMC1300_SECTOR50_PAGE00_ADDR, 2U);
  address = XMC1300_SECTOR50_PAGE00_ADDR;
  for (i = 0; i < 2U * XMC_FLASH_WORDS_PER_PAGE; i++)
  {
    if (XMC_FLASH_ReadWord(address) != 0xFFFFFFFFU)
    {
      status5 = false;
      break;
    }
    address++;
  }

  while(1)
  {
    /* Infinite loop */
  }

}
