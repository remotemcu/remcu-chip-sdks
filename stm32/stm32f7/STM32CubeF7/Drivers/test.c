#include "stm32f7xx_ll_gpio.h"
#include "stm32f7xx_ll_bus.h"
#include "stm32f7xx_ll_rcc.h"


int main(){
	/* Enable HSE clock */
  LL_RCC_HSE_EnableBypass();
  LL_RCC_HSE_Enable();
  while(LL_RCC_HSE_IsReady() != 1)
  {
  };
}