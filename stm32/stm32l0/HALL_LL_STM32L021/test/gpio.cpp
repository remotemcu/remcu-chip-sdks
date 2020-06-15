#include "remcu.h"

#include "stm32l0xx_ll_gpio.h"
#include "stm32l0xx_ll_bus.h"
#include "stm32l0xx_ll_rcc.h"
#include "stm32l0xx_hal.h"


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

int main(int argc, char** argv)
{


  printf("-1\n");

remcu_connect2OpenOCD("localhost", 6666, 3);


  printf("0\n");

//remcu_setVerboseLevel(debug);

remcu_resetRemoteUnit(__HALT);

SystemInit();

/* This sample code shows how to use STM32L0xx GPIO HAL API to toggle PA5 Pin 
  (connected to LED2, on STM32L0xx_Nucleo board) in an infinite loop.
   To proceed, 3 steps are required: */
  
  /* STM32L0xx HAL library initialization:
       - Configure the Flash prefetch, Flash preread and Buffer caches
       - In the default implementation , SysTick timer is configured as main source 
         of time base. It is used to generate interrupts at 1ms basis.
       - Low Level Initialization
     */
  HAL_Init();

  printf("1\n");

    RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  /* Enable MSI Oscillator */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.MSICalibrationValue=0x00;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
  
  
  /* Select MSI as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);

LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

 GPIO_InitTypeDef  GPIO_InitStruct;  
/* -2- Configure PA.5 IO in output push-pull mode to
         drive external LEDs */
  GPIO_InitStruct.Pin = (GPIO_PIN_5);
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH  ;
  
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); 

  while (1)
  {
    //HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    printf("toogle\n");
    sleep(1);
    
  }
}