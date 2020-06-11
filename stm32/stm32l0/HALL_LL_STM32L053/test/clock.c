#include "remcu.h"

#include "stm32l0xx_ll_gpio.h"
#include "stm32l0xx_ll_bus.h"
#include "stm32l0xx_ll_rcc.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int main(int argc, char** argv)
{

remcu_connect2OpenOCD("localhost", 6666, 3);

//remcu_setVerboseLevel(debug);

remcu_resetRemoteUnit(__HALT);


SystemInit();

/* Enable HSE oscillator */
  LL_RCC_HSE_EnableBypass();
  LL_RCC_HSE_Enable();
  while(LL_RCC_HSE_IsReady() != 1)
  {
  }


}