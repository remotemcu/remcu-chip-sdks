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
#include <assert.h>

#include "device_defines.h"

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
int main(int argc, char** argv)
{
  printf("argc : %d\n", argc);

  if(argc < 3){
        printf("test requare 2 arguments: host and port\n");
        return -1;
    }
    const char * host = argv[1];
    printf("argv[1] : %s\n", argv[1]);
    printf("argv[2] : %s\n", argv[2]);
    const uint16_t port = (atoi(argv[2]) & 0xFFFF);
    printf("port : %d\n", port);

  if (port == 6666){
    remcu_connect2OpenOCD(host, 6666, 3);
  } else {
    remcu_connect2GDB(host, port, 3);
  }

remcu_resetRemoteUnit(__HALT);
//remcu_setVerboseLevel(LevelDebug::__INFO);
remcu_setVerboseLevel(__ERROR);

  assert(remcu_is_connected());

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