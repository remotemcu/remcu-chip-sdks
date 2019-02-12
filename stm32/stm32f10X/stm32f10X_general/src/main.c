#include <stm32f10x.h>

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#define USARTy                   USART1
#define USARTy_GPIO              GPIOA
#define USARTy_CLK               RCC_APB2Periph_USART1
#define USARTy_GPIO_CLK          RCC_APB2Periph_GPIOA
#define USARTy_RxPin             GPIO_Pin_10
#define USARTy_TxPin             GPIO_Pin_9
#define USARTy_Tx_DMA_Channel    DMA1_Channel4
#define USARTy_Tx_DMA_FLAG       DMA1_FLAG_TC4
#define USARTy_Rx_DMA_Channel    DMA1_Channel5
#define USARTy_Rx_DMA_FLAG       DMA1_FLAG_TC5
#define USARTy_DR_Base           0x40013804

#define USARTz                   USART2
#define USARTz_GPIO              GPIOA
#define USARTz_CLK               RCC_APB1Periph_USART2
#define USARTz_GPIO_CLK          RCC_APB2Periph_GPIOA
#define USARTz_RxPin             GPIO_Pin_3
#define USARTz_TxPin             GPIO_Pin_2
#define USARTz_Tx_DMA_Channel    DMA1_Channel7
#define USARTz_Tx_DMA_FLAG       DMA1_FLAG_TC7
#define USARTz_Rx_DMA_Channel    DMA1_Channel6
#define USARTz_Rx_DMA_FLAG       DMA1_FLAG_TC6
#define USARTz_DR_Base           0x40004404

const uint8_t * addrDMAbuf = (uint8_t *)0x20000000;
const size_t sizeDMAbuf = 0x100;

const char * message = "AddressIntercept PinTool UART DMA example";

void init(void);
void initPintoolClient();

int main()
{

  initPintoolClient();

  init();

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitTypeDef gpio;

  gpio.GPIO_Pin = GPIO_Pin_13;
  gpio.GPIO_Speed = GPIO_Speed_50MHz;
  gpio.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &gpio);

  const size_t _SIZE_MESSAGE = strlen(message);

  printf("sending message ");

  for (int i = 0; i < _SIZE_MESSAGE; i++) {
    /* Send one byte from USARTy to USARTz */
    USART_SendData(USARTy, message[i]);

    GPIO_SetBits(GPIOC, GPIO_Pin_13);

    /* Loop until USARTy DR register is empty */
    while (USART_GetFlagStatus(USARTy, USART_FLAG_TXE) == RESET)
      ;

    printf(".");
    fflush(stdout);

    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
  }
  printf("\n");

  printf("qty of sent bytes %d\n", strlen(message));

  const uint16_t rec = DMA_GetCurrDataCounter(USARTz_Rx_DMA_Channel);

  printf("qty of received byte using DMA : %d\n", sizeDMAbuf - rec);
  printf("read message from buffer DMA : ");
  const uint8_t *pM = (uint8_t *)pAddrSRAM;
  for (int r = 0; r < _SIZE_MESSAGE; r++) {
    printf("%c", pM[r]);
    fflush(stdout);
  }
  printf("\n");

  assert(strncmp(message, (const char *)pM, _SIZE_MESSAGE) == 0);

  printf("Received and sent bytes are equal!\n");

  return 0;
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{

    /* DMA clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  /* Enable GPIO clock */
  RCC_APB2PeriphClockCmd(USARTy_GPIO_CLK | USARTz_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);

  /* Enable USARTy Clock */
  RCC_APB2PeriphClockCmd(USARTy_CLK, ENABLE);

  /* Enable USARTz Clock */
  RCC_APB1PeriphClockCmd(USARTz_CLK, ENABLE);
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure USARTy Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = USARTy_RxPin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(USARTy_GPIO, &GPIO_InitStructure);

  /* Configure USARTz Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = USARTz_RxPin;
  GPIO_Init(USARTz_GPIO, &GPIO_InitStructure);

  /* Configure USARTy Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = USARTy_TxPin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(USARTy_GPIO, &GPIO_InitStructure);

  /* Configure USARTz Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = USARTz_TxPin;
  GPIO_Init(USARTz_GPIO, &GPIO_InitStructure);
}

/**
  * @brief  Configures the DMA.
  * @param  None
  * @retval None
  */
void DMA_Configuration(void)
{
  DMA_InitTypeDef DMA_InitStructure;

  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  /* USARTz RX DMA1 Channel (triggered by USARTz Rx event) Config */
  DMA_DeInit(USARTz_Rx_DMA_Channel);
  DMA_InitStructure.DMA_PeripheralBaseAddr = USARTz_DR_Base;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)addrDMAbuf;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = sizeDMAbuf;
  DMA_Init(USARTz_Rx_DMA_Channel, &DMA_InitStructure);
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */

void init(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
           this is done through SystemInit() function which is called from startup
           file (startup_stm32f10x_xx.s) before to branch to application main.
           To reconfigure the default setting of SystemInit() function, refer to
           system_stm32f10x.c file
         */
    USART_InitTypeDef USART_InitStructure;
      /* System Clocks Configuration */
      RCC_Configuration();

      /* Configure the GPIO ports */
      GPIO_Configuration();

      /* Configure the DMA */
      DMA_Configuration();

    /* USARTy and USARTz configuration ------------------------------------------------------*/
      /* USARTy and USARTz configured as follow:
            - BaudRate = 230400 baud
            - Word Length = 8 Bits
            - One Stop Bit
            - Even parity
            - Hardware flow control disabled (RTS and CTS signals)
            - Receive and transmit enabled
      */
      USART_InitStructure.USART_BaudRate = 230400;
      USART_InitStructure.USART_WordLength = USART_WordLength_8b;
      USART_InitStructure.USART_StopBits = USART_StopBits_1;
      USART_InitStructure.USART_Parity = USART_Parity_No; //USART_Parity_Even;
      USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
      USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

      /* Configure USARTy */
      USART_Init(USARTy, &USART_InitStructure);
      /* Configure USARTz */
      USART_Init(USARTz, &USART_InitStructure);

      /* Enable USARTz DMA Rx and TX request */
      USART_DMACmd(USARTz, USART_DMAReq_Rx, ENABLE);

      /* Enable USARTz RX DMA1 Channel */
      DMA_Cmd(USARTz_Rx_DMA_Channel, ENABLE);

      /* Enable the USARTy */
      USART_Cmd(USARTy, ENABLE);

      /* Enable the USARTz */
      USART_Cmd(USARTz, ENABLE);

}
