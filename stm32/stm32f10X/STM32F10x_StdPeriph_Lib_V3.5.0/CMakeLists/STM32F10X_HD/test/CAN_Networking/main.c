/**
  ******************************************************************************
  * @file    CAN/Networking/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "remcu.h"
#include "stm32f10x.h"
#include "platform_config.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */
#if (defined(_WIN32) || defined(WIN32) || defined(WIN64) || defined(_WIN64))
  #define sleep _sleep
#endif
/** @addtogroup CAN_Networking
  * @{
  */ 


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define __CAN1_USED__
/* #define __CAN2_USED__*/

#ifdef  __CAN1_USED__
  #define CANx                       CAN1
  #define GPIO_CAN                   GPIO_CAN1
  #define GPIO_Remapping_CAN         GPIO_Remapping_CAN1
  #define GPIO_CAN                   GPIO_CAN1
  #define GPIO_Pin_CAN_RX            GPIO_Pin_CAN1_RX
  #define GPIO_Pin_CAN_TX            GPIO_Pin_CAN1_TX
#else /*__CAN2_USED__*/
  #define CANx                       CAN2
  #define GPIO_CAN                   GPIO_CAN2
  #define GPIO_Remapping_CAN             GPIO_Remap_CAN2
  #define GPIO_CAN                   GPIO_CAN2
  #define GPIO_Pin_CAN_RX            GPIO_Pin_CAN2_RX
  #define GPIO_Pin_CAN_TX            GPIO_Pin_CAN2_TX
#endif  /* __CAN1_USED__ */

#define KEY_PRESSED     0x01
#define KEY_NOT_PRESSED 0x00

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
CAN_InitTypeDef        CAN_InitStructure;
CAN_FilterInitTypeDef  CAN_FilterInitStructure;
CanTxMsg TxMessage;
uint8_t KeyNumber = 0x0;

/* Private function prototypes -----------------------------------------------*/
void CAN_Config(void);
void Init_RxMes(CanRxMsg *RxMessage);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
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

  if (port == 6666){
    remcu_connect2OpenOCD(host, 6666, 3);
  } else {
    remcu_connect2GDB(host, port, 3);
  }

  remcu_resetRemoteUnit(__HALT);
    //remcu_resetRemoteUnit(__RUN);
  //remcu_setVerboseLevel(__INFO);
  remcu_setVerboseLevel(debug);

  assert(remcu_isConnected());

  SystemInit();
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     
       
  /* CAN configuration */
  CAN_Config();
  
  //CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE);
  /* transmit */
  TxMessage.StdId=0x11;
  TxMessage.RTR=CAN_RTR_DATA;
  TxMessage.IDE=CAN_ID_STD;
  TxMessage.DLC=2;
  TxMessage.Data[0]=0xCA;
  TxMessage.Data[1]=0xFE;


  uint8_t TransmitMailbox = 0;
  TransmitMailbox=CAN_Transmit(CANx, &TxMessage);

int i = 0;
   while((CAN_TransmitStatus(CANx, TransmitMailbox) != CANTXOK) && (i != 0xF))
  {
    printf("CAN_TransmitStatus(CANx, TransmitMailbox) %d\n", CAN_TransmitStatus(CANx, TransmitMailbox));
    i++;
  }

  CanRxMsg RxMessage;

  i = 0;
  while((CAN_MessagePending(CANx, CAN_FIFO0) < 1) && (i != 0xF))
  {
    printf("(CAN_MessagePending(CANx, CAN_FIFO0) < 1) && (i != 0xF) %d\n", (CAN_MessagePending(CANx, CAN_FIFO0)));
    i++;
  }

  /* receive */
  RxMessage.StdId=0x00;
  RxMessage.IDE=CAN_ID_STD;
  RxMessage.DLC=0;
  RxMessage.Data[0]=0x00;
  RxMessage.Data[1]=0x00;
  CAN_Receive(CANx, CAN_FIFO0, &RxMessage);

  printf("RxMessage.StdId %x\n",RxMessage.StdId);

  assert(RxMessage.StdId==0x11);


  assert(RxMessage.IDE==CAN_ID_STD);


  assert(RxMessage.DLC==2);


  assert((RxMessage.Data[0]<<8|RxMessage.Data[1])==0xCAFE);

        return 0;
 
  /* Infinite loop */
  for(i= 1; i < 255; i++)
  {
        TxMessage.Data[0] = i;
        CAN_Transmit(CANx, &TxMessage);
        printf("CAN_Transmit %d\n", i);
        sleep(1);
      }
}

/**
  * @brief  Configures the CAN.
  * @param  None
  * @retval None
  */
void CAN_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* GPIO clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
#ifdef  __CAN1_USED__
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_CAN1, ENABLE);
#else /*__CAN2_USED__*/
  @
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_CAN1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_CAN2, ENABLE);
#endif  /* __CAN1_USED__ */
  /* Configure CAN pin: RX */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_CAN_RX;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIO_CAN, &GPIO_InitStructure);
  
  /* Configure CAN pin: TX */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_CAN_TX;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_CAN, &GPIO_InitStructure);
  
  GPIO_PinRemapConfig(GPIO_Remapping_CAN , ENABLE);
  
  /* CANx Periph clock enable */
#ifdef  __CAN1_USED__
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
#else /*__CAN2_USED__*/
  @
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
#endif  /* __CAN1_USED__ */
  
  
  /* CAN register init */
  CAN_DeInit(CANx);
  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  //CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack;
  
  /* CAN Baudrate = 1MBps*/
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
  CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
  CAN_InitStructure.CAN_Prescaler = 4*8; //4; //48 //1024
  printf("CAN_Init\n");
  assert(CAN_Init(CANx, &CAN_InitStructure) == CAN_InitStatus_Success);
  printf("----------\n");

  /* CAN filter init */
#ifdef  __CAN1_USED__
  CAN_FilterInitStructure.CAN_FilterNumber = 0;
#else /*__CAN2_USED__*/
  CAN_FilterInitStructure.CAN_FilterNumber = 14;
#endif  /* __CAN1_USED__ */
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
  
  /* Transmit */
  TxMessage.StdId = 0x321;
  TxMessage.ExtId = 0x01;
  TxMessage.RTR = CAN_RTR_DATA;
  TxMessage.IDE = CAN_ID_STD;
  TxMessage.DLC = 1;
}

/**
  * @brief  Initializes a Rx Message.
  * @param  CanRxMsg *RxMessage
  * @retval None
  */
void Init_RxMes(CanRxMsg *RxMessage)
{
  uint8_t i = 0;

  RxMessage->StdId = 0x00;
  RxMessage->ExtId = 0x00;
  RxMessage->IDE = CAN_ID_STD;
  RxMessage->DLC = 0;
  RxMessage->FMI = 0;
  for (i = 0;i < 8;i++)
  {
    RxMessage->Data[i] = 0x00;
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

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
