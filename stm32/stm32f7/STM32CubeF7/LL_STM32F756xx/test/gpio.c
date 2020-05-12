#include "remcu.h"

#include "stm32f7xx_ll_gpio.h"
#include "stm32f7xx_ll_bus.h"
#include "stm32f7xx_ll_rcc.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int main(int argc, char** argv)
{

remcu_connect2OpenOCD("localhost", 6666, 3);

//remcu_setVerboseLevel(debug);

remcu_resetRemoteUnit(__HALT);


SystemInit();


/* Enable HSE clock */
  LL_RCC_HSE_EnableBypass();
  LL_RCC_HSE_Enable();
  while(LL_RCC_HSE_IsReady() != 1)
  {
  };
#if 0
  /* Set FLASH latency */
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_7);
#endif
  /* Enable PWR clock */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
#if 0
  /* Activation OverDrive Mode */
  LL_PWR_EnableOverDriveMode();
  while(LL_PWR_IsActiveFlag_OD() != 1)
  {
  };

  /* Activation OverDrive Switching */
  LL_PWR_EnableOverDriveSwitching();
  while(LL_PWR_IsActiveFlag_ODSW() != 1)
  {
  };
#endif
  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_8, 432, LL_RCC_PLLP_DIV_2);
  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  };

  /* Sysclk activation on the main PLL */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  };

  /* Set APB1 & APB2 prescaler */
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
#if 0
  /* Set systick to 1ms */
  SysTick_Config(216000000 / 1000);

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  SystemCoreClock = 216000000;
#endif

/* Enable the LED1 Clock */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);

  /* Configure IO in output push-pull mode to drive external LED1 */
  LL_GPIO_SetPinMode(GPIOD, LL_GPIO_PIN_11, LL_GPIO_MODE_OUTPUT);

  while(1)
  LL_GPIO_TogglePin(GPIOD, LL_GPIO_PIN_11);


}