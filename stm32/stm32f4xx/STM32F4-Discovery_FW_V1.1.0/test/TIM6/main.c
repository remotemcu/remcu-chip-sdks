/**
  ******************************************************************************
  * @file    DAC/DAC_SignalsGeneration/main.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    13-April-2012
  * @brief   Main program body.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "remcu.h"

#include "stm32f4xx.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#if (defined(_WIN32) || defined(WIN32) || defined(WIN64) || defined(_WIN64))
  #define sleep _sleep
#endif

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(int argc, char** argv)
{
  printf("argc : %d\n", argc);

  if(argc < 4){
        printf("test requare 2 arguments: host, port and verbose level\n");
        printf("optional 3-d arg: testOpenocd(bool)\n");
        return -1;
    }
    const char * host = argv[1];
    printf("argv[1] : %s\n", argv[1]);
    printf("argv[2] : %s\n", argv[2]);
    const uint16_t port = (atoi(argv[2]) & 0xFFFF);
    printf("port : %d\n", port);
    const uint8_t debug = (atoi(argv[3]) & 0xF);
    printf("debug : %d\n", debug);

    remcu_setVerboseLevel(debug);


  if (port == 6666){
    remcu_connect2OpenOCD(host, 6666, 3);
  } else {
    remcu_connect2GDB(host, port, 3);
  }

  remcu_resetRemoteUnit(__HALT);
    //remcu_resetRemoteUnit(__RUN);
  //remcu_setVerboseLevel(__ALL_LOG);

  assert(remcu_is_connected());

  SystemInit();

  TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
  /* TIM6 Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
  
  /* --------------------------------------------------------
  TIM3 input clock (TIM6CLK) is set to 2 * APB1 clock (PCLK1), 
  since APB1 prescaler is different from 1.   
    TIM6CLK = 2 * PCLK1  
    TIM6CLK = HCLK / 2 = SystemCoreClock /2 
          
  TIM6 Update event occurs each TIM6CLK/256 

  Note: 
   SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f2xx.c file.
   Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
   function to update SystemCoreClock variable value. Otherwise, any configuration
   based on this variable will be incorrect.    

  ----------------------------------------------------------- */
  /* Time base configuration */
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;          
  TIM_TimeBaseStructure.TIM_Prescaler = 2;       
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;    
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

  /* TIM6 TRGO selection */
  //TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);
  
  /* TIM6 enable counter */
  TIM_Cmd(TIM6, ENABLE);

  printf("get_TIM_CR1 : %x", get_TIM_CR1(TIM6));

  assert(get_TIM_CR1(TIM6) != 0);

  while(1){
    printf("%d\n", TIM_GetCounter(TIM6));
    sleep(1);
  }


}

/**             
  * @brief  TIM6 Configuration
  * @note   TIM6 configuration is based on APB1 frequency
  * @note   TIM6 Update event occurs each TIM6CLK/256   
  * @param  None
  * @retval None
  */
void TIM6_Config(void)
{
  TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
  /* TIM6 Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
  
  /* --------------------------------------------------------
  TIM3 input clock (TIM6CLK) is set to 2 * APB1 clock (PCLK1), 
  since APB1 prescaler is different from 1.   
    TIM6CLK = 2 * PCLK1  
    TIM6CLK = HCLK / 2 = SystemCoreClock /2 
          
  TIM6 Update event occurs each TIM6CLK/256 

  Note: 
   SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f2xx.c file.
   Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
   function to update SystemCoreClock variable value. Otherwise, any configuration
   based on this variable will be incorrect.    

  ----------------------------------------------------------- */
  /* Time base configuration */
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;          
  TIM_TimeBaseStructure.TIM_Prescaler = 2;       
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;    
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

  /* TIM6 TRGO selection */
  TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);
  
  /* TIM6 enable counter */
  TIM_Cmd(TIM6, ENABLE);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
