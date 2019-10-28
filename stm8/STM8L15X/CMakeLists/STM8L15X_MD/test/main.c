/**
  ******************************************************************************
  * @file    main.c
  * @author  Microcontroller Division
  * @version V1.2.0
  * @date    09/2010
  * @brief   Main program body
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */
 
#include <stdlib.h>
//#include <unistd.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
/* Includes ------------------------------------------------------------------*/
#include "device_defines.h"
#include "stm8l15x.h"
#include "stm8l_discovery_lcd.h"
#include "discover_board.h"

#include "remcu.h"

#if (defined(_WIN32) || defined(WIN32) || defined(WIN64) || defined(_WIN64))
  #define sleep _sleep
#else
#include <unistd.h>
#endif

/**
  * @brief main entry point.
  * @par Parameters None
  * @retval void None
  * @par Required preconditions: None
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
//remcu_setVerboseLevel(LevelDebug::__INFO);
remcu_setVerboseLevel(__ERROR);

  assert(remcu_isConnected());

/* Init I/O ports */
 
/* USER button init: GPIO set in input interrupt active mode */
  GPIO_Init( BUTTON_GPIO_PORT, USER_GPIO_PIN, GPIO_Mode_In_FL_IT);
	
/* Green led init: GPIO set in output */
  GPIO_Init( LED_GREEN_PORT, LED_GREEN_PIN, GPIO_Mode_Out_PP_High_Fast);
	
/* Blue led init: GPIO set in output */
  GPIO_Init( LED_BLUE_PORT, LED_BLUE_PIN, GPIO_Mode_Out_PP_High_Fast);
	
/* Counter enable: GPIO set in output for enable the counter */
  GPIO_Init( CTN_GPIO_PORT, CTN_CNTEN_GPIO_PIN, GPIO_Mode_Out_OD_HiZ_Slow);
	
/* Wake up counter: for detect end of counter GPIO set in input interupt active mode */
  GPIO_Init( WAKEUP_GPIO_PORT, ICC_WAKEUP_GPIO_PIN, GPIO_Mode_In_FL_IT);	

  /* Initializes the LCD glass */
  LCD_GLASS_Init();

  LCD_GLASS_DisplayString("Hi ALL");


  while (1)
  {

    GPIO_SetBits(LED_BLUE_PORT, LED_BLUE_PIN);
    GPIO_SetBits(LED_GREEN_PORT, LED_GREEN_PIN);
    sleep(1);

    GPIO_ResetBits(LED_BLUE_PORT, LED_BLUE_PIN);
    GPIO_ResetBits(LED_GREEN_PORT, LED_GREEN_PIN);

    sleep(1);
  }

}		

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
