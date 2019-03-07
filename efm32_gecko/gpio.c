/**************************************************************************//**
 * @file
 * @brief Simple LED Blink Demo for EFM32TG_STK3300
 * @version 5.1.2
 ******************************************************************************
 * @section License
 * <b>Copyright 2015 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/
#include <unistd.h>
#include <stdio.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "bsp.h"

#include "remcu.h"


struct {
  int   port;
  unsigned int        pin;
} ledArray1 = {.port = 3, .pin = 7};


/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{

  printf("# %d - %d\n\n", ledArray1.port , ledArray1.pin);

  remcu_connect2OpenOCD("localhost", 6666);
remcu_resetRemoteUnit(ResetType::__HALT);
remcu_setVerboseLevel(LevelDebug::__INFO);

/* Chip errata */
  CHIP_Init(); //nah

  /* Initialize LED driver */
  BSP_LedsInit();

  /* Infinite blink loop */
  while (1)
  {
    printf(" %d\n",BSP_LedToggle(0));
    //GPIO_PinModeSet(gpioPortD, 7,gpioModePushPull, 1);
    sleep(1);
  }
}