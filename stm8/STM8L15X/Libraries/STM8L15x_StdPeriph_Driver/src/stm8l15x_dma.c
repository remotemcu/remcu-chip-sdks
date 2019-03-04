/**
  ******************************************************************************
  * @file    stm8l15x_dma.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    09/24/2010
  * @brief   This file provides all the DMA firmware functions.
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

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x_dma.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
    * @addtogroup DMA_Public_Functions
    * @{
    */

/**
  * @brief  Deinitializes the DMA Global & Status register to its default reset
  *         values.
  * @param  None
  * @retval None
  */
void DMA_GlobalDeInit(void)
{
  /* Disable the  DMA    */
  DMA1->GCSR &= (uint8_t)~(DMA_GCSR_GE);

  /* Reset DMA Channelx control register */
  DMA1->GCSR  = (uint8_t)DMA_GCSR_RESET_VALUE;
}

/**
  * @brief  Deinitializes the DMA Channelx registers to their default reset values.
  * @param  DMA_Channelx : selects the DMA Channelx where x can be 0 to 3
  * @retval None
  */
void DMA_DeInit(DMA_Channel_TypeDef* DMA_Channelx)
{
  /* Check the parameters */
  assert_param(IS_DMA_CHANNEL(DMA_Channelx));

  /* Disable the selected DMA Channelx */
  DMA_Channelx->CCR &= (uint8_t)~(DMA_CCR_CE);

  /* Reset DMA Channelx control register */
  DMA_Channelx->CCR  = DMA_CCR_RESET_VALUE;

  /* Reset DMA Channelx remaining bytes register */
  DMA_Channelx->CNBTR = DMA_CNBTR_RESET_VALUE;

  /* Reset DMA Channelx peripheral address register */
  if (DMA_Channelx == DMA1_Channel3)
  {
    DMA_Channelx->CPARH  = DMA_C3PARH_RESET_VALUE;
    DMA_Channelx->CM0EAR = DMA_C3M0EAR_RESET_VALUE;
  }
  else
  {
    DMA_Channelx->CPARH  = DMA_CPARH_RESET_VALUE;
  }
  DMA_Channelx->CPARL  = DMA_CPARL_RESET_VALUE;

  /* Reset DMA Channelx memory address register */
  DMA_Channelx->CM0ARH = DMA_CM0ARH_RESET_VALUE;
  DMA_Channelx->CM0ARL = DMA_CM0ARL_RESET_VALUE;

  /* Reset interrupt pending bits for DMA Channel */
  DMA_Channelx->CSPR = DMA_CSPR_RESET_VALUE;
}


/**
  * @brief  Initializes the DMA Channelx according to the specified parameters.
  * @param  DMA_Channelx : selects the DMA Channelx where x can be 0 to 3
  * @param  DMA_Memory0BaseAddr : Specifies  Memory 0 Base Address
  * @param  DMA_PeripheralMemory1BaseAddr : Specifies DMA channelx Peripheral Base
  *         Address (if data is from/to  peripheral) or DMA channelx Memory1 Base
  *         Address (if data is from Memory0 to Memory1).
  * @param  DMA_BufferSize : Specifies the size of the DMA channelx Buffer.
  *         This parameter must be a value greater than 0.
  * @param  DMA_DIR : Specifies the DMA channelx transfer direction.
  *         This parameter can be a value of @ref DMA_DIR_TypeDef.
  * @param  DMA_Mode : Specifies the DMA channelx mode.
  *         This parameter can be a value of @ref DMA_Mode_TypeDef
  * @param  DMA_MemoryIncMode : Specifies the DMA channelx memory
  *         Incrementation/Decrementation mode, this parameter can be a value of
  *         @ref DMA_MemoryIncMode_TypeDef.
  * @param  DMA_Priority : Specifies the DMA channelx priority.
  *         This parameter can be a value of @ref  DMA_Priority_TypeDef
  * @param  DMA_MemoryDataSize : Specifies the DMA channelx transfer Data size.
  *         This parameter can be a value of @ref DMA_MemoryDataSize_TypeDef.
  * @retval None
  */
void DMA_Init(DMA_Channel_TypeDef* DMA_Channelx,
              uint32_t DMA_Memory0BaseAddr,
              uint16_t DMA_PeripheralMemory1BaseAddr,
              uint8_t DMA_BufferSize,
              DMA_DIR_TypeDef DMA_DIR,
              DMA_Mode_TypeDef DMA_Mode,
              DMA_MemoryIncMode_TypeDef DMA_MemoryIncMode,
              DMA_Priority_TypeDef DMA_Priority,
              DMA_MemoryDataSize_TypeDef DMA_MemoryDataSize )
{
  /* Check the parameters */
  assert_param(IS_DMA_CHANNEL(DMA_Channelx));
  assert_param(IS_DMA_DIR(DMA_DIR));
  assert_param(IS_DMA_BUFFER_SIZE(DMA_BufferSize));
  assert_param(IS_DMA_MODE(DMA_Mode));
  assert_param(IS_DMA_MEMORY_INC_MODE(DMA_MemoryIncMode));
  assert_param(IS_DMA_PRIORITY(DMA_Priority));

  /*--------------------------- DMA Channelx CCR Configuration -----------------*/
  /* Disable the selected DMA Channelx */
  DMA_Channelx->CCR &= (uint8_t)~(DMA_CCR_CE);

  /* Reset DMA Channelx control register */
  DMA_Channelx->CCR  = DMA_CCR_RESET_VALUE;

  /* Set DMA direction & Mode & Incremantal Memory mode */
  DMA_Channelx->CCR |= (uint8_t)((uint8_t)((uint8_t)DMA_DIR | (uint8_t)DMA_Mode) | (uint8_t)DMA_MemoryIncMode);

  /*Clear old priority and memory data size  option */
  DMA_Channelx->CSPR &= (uint8_t)(~(uint8_t)(DMA_CSPR_PL | DMA_CSPR_16BM));

  /* Set old priority and memory data size  option */
  DMA_Channelx->CSPR |= (uint8_t)((uint8_t)DMA_Priority | (uint8_t)DMA_MemoryDataSize);

  /*--------------------------- DMA Channelx CNDTR Configuration ---------------*/
  /* Write to DMA Channelx CNDTR */
  DMA_Channelx->CNBTR = (uint8_t)DMA_BufferSize;

  /*--------------------------- DMA Channelx CPAR Configuration ----------------*/
  /* Write to DMA Channelx (0, 1 or 2)  Peripheral address  or  Write to DMA Channel 3 Memory 1 address  */
  DMA_Channelx->CPARH = (uint8_t)(DMA_PeripheralMemory1BaseAddr >> (uint8_t)8);
  DMA_Channelx->CPARL = (uint8_t)(DMA_PeripheralMemory1BaseAddr);

  /*--------------------------- DMA Channelx CMAR Configuration ----------------*/
  /* Write to DMA Channelx Memory address */
  if (DMA_Channelx == DMA1_Channel3)
  {
    DMA_Channelx->CM0EAR = (uint8_t)(DMA_Memory0BaseAddr >> (uint8_t)16);
  }
  DMA_Channelx->CM0ARH = (uint8_t)(DMA_Memory0BaseAddr >> (uint8_t)8);
  DMA_Channelx->CM0ARL = (uint8_t)(DMA_Memory0BaseAddr);

}

/**
  * @brief  Enables or disables All the DMA.
  * @param  NewState: new state of the DMA. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DMA_GlobalCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the  DMA      */
    DMA1->GCSR |= (uint8_t)DMA_GCSR_GE;
  }
  else
  {
    /* Disable the DMA */
    DMA1->GCSR &= (uint8_t)(~DMA_GCSR_GE);
  }
}

/**
  * @brief  Enables or disables the specified DMA Channelx.
  * @note   DMA_GlobalCmd function must be called first to enable or disable
  *         the global DMA.
  * @param  DMA_Channelx : selects the DMA Channelx where x can be 0 to 3
  * @param  NewState: new state of the DMA Channelx.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DMA_Cmd(DMA_Channel_TypeDef* DMA_Channelx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DMA_CHANNEL(DMA_Channelx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected DMA Channelx */
    DMA_Channelx->CCR |= DMA_CCR_CE;
  }
  else
  {
    /* Disable the selected DMA Channelx */
    DMA_Channelx->CCR &= (uint8_t)(~DMA_CCR_CE);
  }
}

/**
  * @brief  Enables or disables the specified DMA Channelx interrupts.
  * @param  DMA_Channelx : selects the DMA Channelx where x can be 0 to 3
  * @param  DMA_ITx: specifies the DMA interrupts sources to be enabled or disabled.
  *         This parameter can be any combination of values of @ref DMA_ITx_TypeDef.
  * @param  NewState: new state of the specified DMA interrupts.
    *       This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DMA_ITConfig(DMA_Channel_TypeDef* DMA_Channelx, DMA_ITx_TypeDef DMA_ITx,
                  FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DMA_CHANNEL(DMA_Channelx));
  assert_param(IS_DMA_CONFIG_ITX(DMA_ITx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected DMA interrupts */
    DMA_Channelx->CCR |= (uint8_t)(DMA_ITx);
  }
  else
  {
    /* Disable the selected DMA interrupts */
    DMA_Channelx->CCR &= (uint8_t)~(DMA_ITx);
  }
}

/**
  * @brief  Sets the Time out Value.
  * @param  DMA_TimeOut: an integer from 0 to 63
  *         If DMA_TimeOut = 0, TimeOut functionnality is disactived
  * @retval None
  */
void DMA_SetTimeOut(uint8_t DMA_TimeOut)
{
  /* Check the parameters */
  assert_param(IS_DMA_TIMEOUT(DMA_TimeOut));

  /* set the time out ,  GB and GE must be = 0 */
  DMA1->GCSR = 0;
  DMA1->GCSR = (uint8_t)(DMA_TimeOut << (uint8_t)2);
}
/**
  * @brief  Set the number of data units to transfer for DMA Channelx.
  * @param  DMA_Channelx : selects the DMA Channelx where x can be 0 to 3
  * @param  DMA_Counter :  The number of  data units to transfer,
  *         it can be any value from 0 to 255
  * @retval None
  */
void DMA_SetCurrDataCounter(DMA_Channel_TypeDef* DMA_Channelx, uint8_t DMA_Counter)
{
  /* Check the parameters */
  assert_param(IS_DMA_CHANNEL(DMA_Channelx));

  /*Set the number of data units for DMA Channelx */
  DMA_Channelx->CNBTR = DMA_Counter;
}

/**
  * @brief  Returns the number of remaining data units in the current DMA
  *         Channelx transfer.
  * @param  DMA_Channelx : selects the DMA Channelx where x can be 0 to 3
  * @retval The number of remaining data units in the current DMA Channelx
  */
uint8_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMA_Channelx)
{
  /* Check the parameters */
  assert_param(IS_DMA_CHANNEL(DMA_Channelx));

  /* Return the number of remaining data units for DMA Channelx */
  return ((uint8_t)(DMA_Channelx->CNBTR));
}

/**
  * @brief  Checks whether the specified DMA Channelx flag is set or not.
  * @param  DMA_FLAG: specifies the flag to check.
  *         This parameter can be a value of @ref DMA_FLAG_TypeDef
  * @retval FlagStatus: The status of DMA_FLAG (SET or RESET).
  */
FlagStatus DMA_GetFlagStatus(DMA_FLAG_TypeDef DMA_FLAG)
{
  FlagStatus flagstatus = RESET;
  DMA_Channel_TypeDef* DMA_Channelx =  DMA1_Channel0;
  uint8_t tmpgir1 = 0;
  uint8_t tmpgcsr = 0;

  /* Check the parameters */
  assert_param(IS_DMA_GET_FLAG(DMA_FLAG));

  /* Get flags registers values*/
  tmpgcsr = DMA1->GCSR;
  tmpgir1 = DMA1->GIR1;

  if (((uint16_t)DMA_FLAG & (uint16_t)0x0F00) != (uint16_t)RESET)
  {
    /* find  the used DMA  channel */
    if (((uint16_t)DMA_FLAG & 0x0100) != (uint16_t)RESET)
    {
      DMA_Channelx = DMA1_Channel0;
    }
    else if  (((uint16_t)DMA_FLAG & 0x0200) != (uint16_t)RESET)
    {
      DMA_Channelx = DMA1_Channel1;
    }
    else if  (((uint16_t)DMA_FLAG & 0x0400) != (uint16_t)RESET)
    {
      DMA_Channelx = DMA1_Channel2;
    }
    else
    {
      DMA_Channelx = DMA1_Channel3;
    }

    /*   Get the specified DMA Channelx flag status. */
    flagstatus = (FlagStatus)((uint8_t)(DMA_Channelx->CSPR) & (uint8_t)DMA_FLAG);
  }
  else if (((uint16_t)DMA_FLAG & 0x1000) != (uint16_t)RESET)
  {
    /*   Get the specified DMA Channelx flag status. */
    flagstatus = (FlagStatus)(tmpgir1 & (uint8_t)DMA_FLAG);
  }
  else /*if ((DMA_FLAG & DMA_FLAG_GB) != (uint16_t)RESET)*/
  {
    /*   Get the specified DMA Channelx flag status. */
    flagstatus = (FlagStatus)(tmpgcsr & DMA_GCSR_GB);
  }

  /*  Return the specified DMA Channelx flag status. */
  return (flagstatus);
}

/**
  * @brief  Clears the DMA Channels selected flags.
  * @param  DMA_FLAG: specifies the flag to clear.
  *         This parameter can be a value of (or a combination for the same DMA
  *         channel) of @ref DMA_FLAG_TypeDef
  * @retval None
  */
void DMA_ClearFlag(DMA_FLAG_TypeDef DMA_FLAG)
{
  DMA_Channel_TypeDef* DMA_Channelx =  DMA1_Channel0;

  /* Check the parameters */
  assert_param(IS_DMA_CLEAR_FLAG(DMA_FLAG));

  /* Identify  the used DMA  channel */
  if (((uint16_t)DMA_FLAG & (uint16_t)0x0100) != (uint16_t)RESET)
  {
    DMA_Channelx = DMA1_Channel0;
  }
  else
  {
    if (((uint16_t)DMA_FLAG & (uint16_t)0x0200) != (uint16_t)RESET)
    {
      DMA_Channelx = DMA1_Channel1;
    }
    else
    {
      if (((uint16_t)DMA_FLAG & (uint16_t)0x0400) != (uint16_t)RESET)
      {
        DMA_Channelx = DMA1_Channel2;
      }
      else
      {
        DMA_Channelx = DMA1_Channel3;
      }
    }
  }

  /*Clears the DMA flags.*/
  DMA_Channelx->CSPR &= (uint8_t)~(uint8_t)((uint8_t)DMA_FLAG & (uint8_t)0x06);
}

/**
  * @brief  Checks whether the specified DMA Channelx interrupt has occurred or not.
  * @param  DMA_IT: specifies the DMA interrupt source to check.
  *         This parameter can be a value of @ref DMA_IT_TypeDef
  * @retval ITStatus: The status of DMA_IT (SET or RESET).
  */
ITStatus DMA_GetITStatus(DMA_IT_TypeDef DMA_IT)
{
  ITStatus itstatus = RESET;
  uint8_t tmpreg = 0;
  uint8_t tmp2 = 0;
  DMA_Channel_TypeDef* DMA_Channelx =  DMA1_Channel0;

  /* Check the parameters */
  assert_param(IS_DMA_GET_IT(DMA_IT));

  /* Identify  the used DMA  channel */
  if ((DMA_IT & 0x10) != (uint8_t)RESET)
  {
    DMA_Channelx = DMA1_Channel0;
  }
  else
  {
    if  ((DMA_IT & 0x20) != (uint8_t)RESET)
    {
      DMA_Channelx = DMA1_Channel1;
    }
    else
    {
      if  ((DMA_IT & 0x40) != (uint8_t)RESET)
      {
        DMA_Channelx = DMA1_Channel2;
      }
      else
      {
        DMA_Channelx = DMA1_Channel3;
      }
    }
  }
  /*   Get the specified DMA Channelx interrupt status. */
  tmpreg =  DMA_Channelx->CSPR ;
  tmpreg &= DMA_Channelx->CCR ;
  tmp2 = (uint8_t)(DMA_IT & (uint8_t)(DMA_CCR_TCIE | DMA_CCR_HTIE));
  itstatus = (ITStatus)((uint8_t)tmpreg & (uint8_t)tmp2);

  /*   Return the specified DMA Channelx interrupt status. */
  return (itstatus);
}

/**
  * @brief  Clears the DMA Channelx’s interrupt pending bits.
  * @param  DMA_IT: specifies the DMA interrupt pending bit to clear.
  *         This parameter can be a value of (or a combination for the same
  *         DMA channel) of @ref DMA_IT_TypeDef
  * @retval None
  */
void DMA_ClearITPendingBit(DMA_IT_TypeDef DMA_IT)
{
  DMA_Channel_TypeDef* DMA_Channelx =  DMA1_Channel0;

  /* Check the parameters */
  assert_param(IS_DMA_CLEAR_IT(DMA_IT));
  /* Identify  the used DMA  channel */
  if ((DMA_IT & 0x10) != (uint8_t)RESET)
  {
    DMA_Channelx = DMA1_Channel0;
  }
  else
  {
    if ((DMA_IT & 0x20) != (uint8_t)RESET)
    {
      DMA_Channelx = DMA1_Channel1;
    }
    else
    {
      if ((DMA_IT & 0x40) != (uint8_t)RESET)
      {
        DMA_Channelx = DMA1_Channel2;
      }
      else
      {
        DMA_Channelx = DMA1_Channel3;
      }
    }
  }
  /*Clears the DMA Channelx’s interrupt pending bits*/
  DMA_Channelx->CSPR &= (uint8_t)~(uint8_t)(DMA_IT & (uint8_t)0x06);
}

/**
    * @}
    */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
