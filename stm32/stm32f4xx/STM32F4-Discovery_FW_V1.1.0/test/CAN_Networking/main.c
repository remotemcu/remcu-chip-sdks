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
#include "stm32f4xx.h"


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup CAN_Networking
  * @{
  */ 


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
  #define CANx                       CAN1
  #define CAN_CLK                    RCC_APB1Periph_CAN1
  #define CAN_RX_PIN                 GPIO_Pin_0
  #define CAN_TX_PIN                 GPIO_Pin_1
  #define CAN_GPIO_PORT              GPIOD
  #define CAN_GPIO_CLK               RCC_AHB1Periph_GPIOD
  #define CAN_AF_PORT                GPIO_AF_CAN1
  #define CAN_RX_SOURCE              GPIO_PinSource0
  #define CAN_TX_SOURCE              GPIO_PinSource1 

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
  remcu_setVerboseLevel(debug);

  if (port == 6666){
    remcu_connect2OpenOCD(host, 6666, 3);
  } else {
    remcu_connect2GDB(host, port, 3);
  }

  remcu_resetRemoteUnit(__HALT);

  assert(remcu_is_connected());

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
    /* Transmit 
  TxMessage.StdId = 0x321;
  TxMessage.ExtId = 0x01;
  TxMessage.RTR = CAN_RTR_DATA;
  TxMessage.IDE = CAN_ID_STD;
  TxMessage.DLC = 1;
  */
  /* transmit */
  TxMessage.StdId=0x11;
  TxMessage.ExtId = 0x00;
  TxMessage.RTR=CAN_RTR_DATA;
  TxMessage.IDE=CAN_ID_STD;
  TxMessage.DLC=2;
  TxMessage.Data[0]=0xCA;
  TxMessage.Data[1]=0xFE;


  uint8_t TransmitMailbox = 0;
  TransmitMailbox = CAN_Transmit(CANx, &TxMessage);

int i = 0;
   while((CAN_TransmitStatus(CANx, TransmitMailbox) != CANTXOK))
  {
    printf("CAN_TransmitStatus(CANx, TransmitMailbox) %d\n", CAN_TransmitStatus(CANx, TransmitMailbox));

  }

  CanRxMsg RxMessage;

  i = 0;
  while((CAN_MessagePending(CANx, CAN_FIFO0) < 1))
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
  printf("RxMessage.DLC %x\n",RxMessage.DLC);  
  printf("RxMessage.Data[0] %x\n",RxMessage.Data[0]);
  printf("RxMessage.Data[1] %x\n",RxMessage.Data[1]);

}


void CAN_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* CAN GPIOs configuration **************************************************/

  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(CAN_GPIO_CLK, ENABLE);

  /* Connect CAN pins to AF9 */
  GPIO_PinAFConfig(CAN_GPIO_PORT, CAN_RX_SOURCE, CAN_AF_PORT);
  GPIO_PinAFConfig(CAN_GPIO_PORT, CAN_TX_SOURCE, CAN_AF_PORT); 
  
  /* Configure CAN RX and TX pins */
  GPIO_InitStructure.GPIO_Pin = CAN_RX_PIN | CAN_TX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(CAN_GPIO_PORT, &GPIO_InitStructure);

  /* CAN configuration ********************************************************/  
  /* Enable CAN clock */
  RCC_APB1PeriphClockCmd(CAN_CLK, ENABLE);

  RCC_ClocksTypeDef q;
  RCC_GetClocksFreq(&q);
  printf("PCLK1_Frequency : %d\n",q.PCLK1_Frequency);
  printf("HCLK_Frequency : %d\n",q.HCLK_Frequency);
  printf("SYSCLK_Frequency : %d\n",q.SYSCLK_Frequency);
  //printf("HCLK_Frequency : %d\n",q.HCLK_Frequency);
  
  
  /* CAN register init */
  CAN_DeInit(CANx);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  //CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack;
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    
  /* CAN Baudrate = 1 MBps (CAN clocked at 30 MHz) */
  CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
  //CAN_InitStructure.CAN_Prescaler = 2;
  CAN_InitStructure.CAN_Prescaler = 2*8;
  CAN_Init(CANx, &CAN_InitStructure);

  /* CAN filter init */
  CAN_FilterInitStructure.CAN_FilterNumber = 0;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
  
  /* Transmit Structure preparation */
  TxMessage.StdId = 0x321;
  TxMessage.ExtId = 0x01;
  TxMessage.RTR = CAN_RTR_DATA;
  TxMessage.IDE = CAN_ID_STD;
  TxMessage.DLC = 1;
  
  /* Enable FIFO 0 message pending Interrupt */
  //CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE);
}
/**
  * @brief  Configures the CAN.
  * @param  None
  * @retval None
  */

void CAN_Config1(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* CAN GPIOs configuration **************************************************/

  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(CAN_GPIO_CLK, ENABLE);

  /* Connect CAN pins to AF9 */
  GPIO_PinAFConfig(CAN_GPIO_PORT, CAN_RX_SOURCE, CAN_AF_PORT);
  GPIO_PinAFConfig(CAN_GPIO_PORT, CAN_TX_SOURCE, CAN_AF_PORT); 
  
  /* Configure CAN RX and TX pins */
  GPIO_InitStructure.GPIO_Pin = CAN_RX_PIN | CAN_TX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(CAN_GPIO_PORT, &GPIO_InitStructure);

  /* CAN configuration ********************************************************/  
  /* Enable CAN clock */
  RCC_APB1PeriphClockCmd(CAN_CLK, ENABLE);
  
  /* CAN register init */
  CAN_DeInit(CANx);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    
  /* CAN Baudrate = 1MBps (CAN clocked at 30 MHz) */
  CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
  CAN_InitStructure.CAN_Prescaler = 2;
  CAN_Init(CANx, &CAN_InitStructure);

  /* CAN filter init */
#ifdef  USE_CAN1
  CAN_FilterInitStructure.CAN_FilterNumber = 0;
#else /* USE_CAN2 */
  CAN_FilterInitStructure.CAN_FilterNumber = 14;
#endif  /* USE_CAN1 */
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
  
  /* Transmit Structure preparation 
  TxMessage.StdId = 0x321;
  TxMessage.ExtId = 0x01;
  TxMessage.RTR = CAN_RTR_DATA;
  TxMessage.IDE = CAN_ID_STD;
  TxMessage.DLC = 1;
  */
  /* Enable FIFO 0 message pending Interrupt */
  CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE);
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
