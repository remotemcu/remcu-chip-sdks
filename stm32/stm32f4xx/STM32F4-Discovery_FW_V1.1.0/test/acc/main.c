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
#include "device_defines.h"
#include "stm32f4xx.h"
#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "remcu.h"

#if (defined(_WIN32) || defined(WIN32) || defined(WIN64) || defined(_WIN64))
  #define sleep _sleep
#endif

/* Private function prototypes -----------------------------------------------*/
static void TIM_Config(void);

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
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
    //remcu_resetRemoteUnit(__RUN);
  //remcu_setVerboseLevel(__INFO);
  //remcu_setVerboseLevel(__ALL_LOG);

  assert(remcu_isConnected());

  SystemInit();

  uint8_t ctrl = 0;
  
  LIS302DL_InitTypeDef  LIS302DL_InitStruct;
  LIS302DL_InterruptConfigTypeDef LIS302DL_InterruptStruct;  
    
  /* Set configuration of LIS302DL*/
  LIS302DL_InitStruct.Power_Mode = LIS302DL_LOWPOWERMODE_ACTIVE;
  LIS302DL_InitStruct.Output_DataRate = LIS302DL_DATARATE_100;
  LIS302DL_InitStruct.Axes_Enable = LIS302DL_X_ENABLE | LIS302DL_Y_ENABLE | LIS302DL_Z_ENABLE;
  LIS302DL_InitStruct.Full_Scale = LIS302DL_FULLSCALE_2_3;
  LIS302DL_InitStruct.Self_Test = LIS302DL_SELFTEST_NORMAL;
  LIS302DL_Init(&LIS302DL_InitStruct);
    
  /* Set configuration of Internal High Pass Filter of LIS302DL*/
  LIS302DL_InterruptStruct.Latch_Request = LIS302DL_INTERRUPTREQUEST_LATCHED;
  LIS302DL_InterruptStruct.SingleClick_Axes = LIS302DL_CLICKINTERRUPT_Z_ENABLE;
  LIS302DL_InterruptStruct.DoubleClick_Axes = LIS302DL_DOUBLECLICKINTERRUPT_Z_ENABLE;
  LIS302DL_InterruptConfig(&LIS302DL_InterruptStruct);

  /* Required sleep for the MEMS Accelerometre: Turn-on time = 3/Output data Rate 
                                                             = 3/100 = 30ms */
  sleep(1);
  
  /* Configure Interrupt control register: enable Click interrupt1 */
  ctrl = 0x07;
  LIS302DL_Write(&ctrl, LIS302DL_CTRL_REG3_ADDR, 1);
  
  /* Enable Interrupt generation on click/double click on Z axis */
  ctrl = 0x70;
  LIS302DL_Write(&ctrl, LIS302DL_CLICK_CFG_REG_ADDR, 1);
  
  /* Configure Click Threshold on X/Y axis (10 x 0.5g) */
  ctrl = 0xAA;
  LIS302DL_Write(&ctrl, LIS302DL_CLICK_THSY_X_REG_ADDR, 1);
  
  /* Configure Click Threshold on Z axis (10 x 0.5g) */
  ctrl = 0x0A;
  LIS302DL_Write(&ctrl, LIS302DL_CLICK_THSZ_REG_ADDR, 1);
  
  /* Configure Time Limit */
  ctrl = 0x03;
  LIS302DL_Write(&ctrl, LIS302DL_CLICK_TIMELIMIT_REG_ADDR, 1);
    
  /* Configure Latency */
  ctrl = 0x7F;
  LIS302DL_Write(&ctrl, LIS302DL_CLICK_LATENCY_REG_ADDR, 1);
  
  /* Configure Click Window */
  ctrl = 0x7F;
  LIS302DL_Write(&ctrl, LIS302DL_CLICK_WINDOW_REG_ADDR, 1);
  
  uint8_t x, y, z;
  #define _SIZE_BUFFER_ACC 6
  uint8_t Buffer[_SIZE_BUFFER_ACC];
    
  while(1)
  {
    LIS302DL_Read(Buffer, LIS302DL_OUT_X_ADDR, _SIZE_BUFFER_ACC);
    /* Remove the offsets values from data */
    x = Buffer[0];
    y = Buffer[2];
    z = Buffer[4];

    printf("x : %d | y : %d | z : %d\n", x, y, z);
  }

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
