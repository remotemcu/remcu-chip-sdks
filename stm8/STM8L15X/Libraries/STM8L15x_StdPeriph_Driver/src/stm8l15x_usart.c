/**
  ********************************************************************************
  * @file    stm8l15x_usart.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    09/24/2010
  * @brief   This file provides all the USART firmware functions.
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
#include "stm8l15x_usart.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/** @}
  * @addtogroup USART_Public_Functions
  * @{
  */

/**
  * @brief   Deinitializes the USART peripheral.
  * @param  USARTx : where x can be 1, 2 or 3 to select the specified USART peripheral.
  * @retval None
  */
void USART_DeInit(USART_TypeDef* USARTx)
{

  /* Clear the Idle Line Detected bit in the status rerister by a read
      to the USART_SR register followed by a Read to the USART_DR register */
  (void) USARTx->SR;
  (void) USARTx->DR;

  USARTx->BRR2 = USART_BRR2_RESET_VALUE;  /* Set USART_BRR2 to reset value 0x00 */
  USARTx->BRR1 = USART_BRR1_RESET_VALUE;  /* Set USART_BRR1 to reset value 0x00 */

  USARTx->CR1 = USART_CR1_RESET_VALUE;  /* Set USART_CR1 to reset value 0x00 */
  USARTx->CR2 = USART_CR2_RESET_VALUE;  /* Set USART_CR2 to reset value 0x00 */
  USARTx->CR3 = USART_CR3_RESET_VALUE;  /* Set USART_CR3 to reset value 0x00 */
  USARTx->CR4 = USART_CR4_RESET_VALUE;  /* Set USART_CR4 to reset value 0x00 */
}

/**
  * @brief  Initializes the USART according to the specified parameters.
  * @note   Configure in Push Pull or Open Drain mode the Tx pin by setting the
  *         correct I/O Port register according the product package and line
  *         configuration
  * @param  USARTx : where x can be 1 to select the specified USART peripheral.
  * @param  BaudRate : The baudrate.
  * @param  USART_WordLength : This parameter can be any of the
  *         @ref USART_WordLength_TypeDef enumeration.
  * @param  USART_StopBits : This parameter can be any of the
  *         @ref USART_StopBits_TypeDef enumeration.
  * @param  USART_Parity : This parameter can be any of the
  *         @ref USART_Parity_TypeDef enumeration.
  * @param  USART_Mode : This parameter can be any of the @ref USART_Mode_TypeDef values
  * @retval None
  */
void USART_Init(USART_TypeDef* USARTx, uint32_t BaudRate, USART_WordLength_TypeDef
                USART_WordLength, USART_StopBits_TypeDef USART_StopBits,
                USART_Parity_TypeDef USART_Parity,  USART_Mode_TypeDef USART_Mode)
{
  uint32_t BaudRate_Mantissa = 0;

  /* Check the parameters */
  assert_param(IS_USART_BAUDRATE(BaudRate));

  assert_param(IS_USART_WORDLENGTH(USART_WordLength));

  assert_param(IS_USART_STOPBITS(USART_StopBits));

  assert_param(IS_USART_PARITY(USART_Parity));

  assert_param(IS_USART_MODE(USART_Mode));

  /* Clear the word length and Parity Control bits */
  USARTx->CR1 &= (uint8_t)(~(USART_CR1_PCEN | USART_CR1_PS | USART_CR1_M));
  /* Set the word length bit according to USART_WordLength value */
  /* Set the Parity Control bit to USART_Parity value */
  USARTx->CR1 |= (uint8_t)((uint8_t)USART_WordLength | (uint8_t)USART_Parity);

  /* Clear the STOP bits */
  USARTx->CR3 &= (uint8_t)(~USART_CR3_STOP);
  /* Set the STOP bits number according to USART_StopBits value */
  USARTx->CR3 |= (uint8_t)USART_StopBits;

  /* Clear the LSB mantissa of USARTDIV */
  USARTx->BRR1 &= (uint8_t)(~USART_BRR1_DIVM);
  /* Clear the MSB mantissa of USARTDIV */
  USARTx->BRR2 &= (uint8_t)(~USART_BRR2_DIVM);
  /* Clear the Fraction bits of USARTDIV */
  USARTx->BRR2 &= (uint8_t)(~USART_BRR2_DIVF);

  BaudRate_Mantissa  = (uint32_t)(CLK_GetClockFreq() / BaudRate );
  /* Set the fraction of USARTDIV */
  USARTx->BRR2 = (uint8_t)((BaudRate_Mantissa >> (uint8_t)8) & (uint8_t)0xF0);
  /* Set the MSB mantissa of USARTDIV */
  USARTx->BRR2 |= (uint8_t)(BaudRate_Mantissa & (uint8_t)0x0F);
  /* Set the LSB mantissa of USARTDIV */
  USARTx->BRR1 = (uint8_t)(BaudRate_Mantissa >> (uint8_t)4);

  /* Disable the Transmitter and Receiver */
  USARTx->CR2 &= (uint8_t)~(USART_CR2_TEN | USART_CR2_REN);
  /* Set TEN and REN bits according to USART_Mode value */
  USARTx->CR2 |= (uint8_t)USART_Mode;
}

/**
  * @brief  Initializes the USART Clock according to the specified parameters.
  * @param  USARTx : where x can be 1 to select the specified USART peripheral.
  * @param  USART_Clock : This parameter can be any of the @ref USART_Clock_TypeDef
  *         enumeration.
  * @param  USART_CPOL : This parameter can be any of the @ref USART_CPOL_TypeDef
  *         enumeration.
  * @param  USART_CPHA : This parameter can be any of the @ref USART_CPHA_TypeDef
  *         enumeration.
  * @param  USART_LastBit : This parameter can be any of the @ref USART_LastBit_TypeDef
  *         enumeration.
  * @retval None
  */

void USART_ClockInit(USART_TypeDef* USARTx, USART_Clock_TypeDef USART_Clock,
                     USART_CPOL_TypeDef USART_CPOL, USART_CPHA_TypeDef USART_CPHA,
                     USART_LastBit_TypeDef USART_LastBit)
{
  /* Check the parameters */
  assert_param(IS_USART_CLOCK(USART_Clock));
  assert_param(IS_USART_CPOL(USART_CPOL));
  assert_param(IS_USART_CPHA(USART_CPHA));
  assert_param(IS_USART_LASTBIT(USART_LastBit));

  /* Clear the Clock Polarity, lock Phase, Last Bit Clock pulse */
  USARTx->CR3 &= (uint8_t)~(USART_CR3_CPOL | USART_CR3_CPHA | USART_CR3_LBCL);
  /* Set the Clock Polarity, lock Phase, Last Bit Clock pulse */
  USARTx->CR3 |= (uint8_t)((uint8_t)((uint8_t)(USART_CPOL | (uint8_t)USART_CPHA ) | USART_LastBit));

  if (USART_Clock != USART_Clock_Disable)
  {
    USARTx->CR3 |= (uint8_t)(USART_CR3_CLKEN); /* Set the Clock Enable bit */
  }
  else
  {
    USARTx->CR3 &= (uint8_t)(~USART_CR3_CLKEN); /* Clear the Clock Enable bit */
  }
}

/**
  * @brief  Enable the USART peripheral.
  * @param  USARTx : where x can be 1 to select the specified USART peripheral.
  * @param  NewState : The new state of the USART Communication.
  *         This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    USARTx->CR1 &= (uint8_t)(~USART_CR1_USARTD); /**< USART Enable */
  }
  else
  {
    USARTx->CR1 |= USART_CR1_USARTD;  /**< USART Disable (for low power consumption) */
  }
}

/**
  * @brief  Enables or disables the specified USART interrupts.
  * @param  USARTx : where x can be 1 to select the specified USART peripheral.
  * @param  USART_IT specifies the USART interrupt sources to be enabled or disabled.
  *         This parameter can be one of the following values:
  *         - USART_IT_TXE:  Tansmit Data Register empty interrupt
  *         - USART_IT_TC:   Transmission complete interrupt
  *         - USART_IT_RXNE: Receive Data register not empty interrupt
  *         - USART_IT_OR: Overrun error interrupt
  *         - USART_IT_IDLE: Idle line detection interrupt
  *         - USART_IT_ERR:  Error interrupt
  * @param  NewState new state of the specified USART interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_ITConfig(USART_TypeDef* USARTx, USART_IT_TypeDef USART_IT, FunctionalState NewState)
{
  uint8_t usartreg, itpos = 0x00;
  assert_param(IS_USART_CONFIG_IT(USART_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Get the USART register index */
  usartreg = (uint8_t)((uint16_t)USART_IT >> 0x08);
  /* Get the USART IT index */
  itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)USART_IT & (uint8_t)0x0F));

  if (NewState != DISABLE)
  {
    /**< Enable the Interrupt bits according to USART_IT mask */
    if (usartreg == 0x01)
    {
      USARTx->CR1 |= itpos;
    }
    else if (usartreg == 0x05)
    {
      USARTx->CR5 |= itpos;
    }
    /*uartreg =0x02*/
    else
    {
      USARTx->CR2 |= itpos;
    }
  }
  else
  {
    /**< Disable the interrupt bits according to USART_IT mask */
    if (usartreg == 0x01)
    {
      USARTx->CR1 &= (uint8_t)(~itpos);
    }
    else if (usartreg == 0x05)
    {
      USARTx->CR5 &= (uint8_t)(~itpos);
    }
    /*uartreg =0x02*/
    else
    {
      USARTx->CR2 &= (uint8_t)(~itpos);
    }
  }

}
/**
  * @brief  Enables or disables the USART’s Half Duplex communication.
  * @param  USARTx : where x can be 1 to select the specified USART peripheral.
  * @param  NewState new state of the USART Communication.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    USARTx->CR5 |= USART_CR5_HDSEL;  /**< USART Half Duplex Enable  */
  }
  else
  {
    USARTx->CR5 &= (uint8_t)~USART_CR5_HDSEL; /**< USART Half Duplex Disable */
  }
}

/**
  * @brief  Configures the USART’s IrDA interface.
  * @param  USARTx : where x can be 1 to select the specified USART peripheral.
  * @param  USART_IrDAMode specifies the IrDA mode.
  *         This parameter can be any of the @ref USART_IrDAMode_TypeDef values.
  * @retval None
  */
void USART_IrDAConfig(USART_TypeDef* USARTx, USART_IrDAMode_TypeDef USART_IrDAMode)
{
  assert_param(IS_USART_IRDAMODE(USART_IrDAMode));

  if (USART_IrDAMode != USART_IrDAMode_Normal)
  {
    USARTx->CR5 |= USART_CR5_IRLP;
  }
  else
  {
    USARTx->CR5 &= ((uint8_t)~USART_CR5_IRLP);
  }
}

/**
  * @brief  Enables or disables the USART’s IrDA interface.
  * @param  USARTx : where x can be 1 to select the specified USART peripheral.
  * @param  NewState new state of the IrDA mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState)
{

  /* Check parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the IrDA mode by setting the IREN bit in the CR3 register */
    USARTx->CR5 |= USART_CR5_IREN;
  }
  else
  {
    /* Disable the IrDA mode by clearing the IREN bit in the CR3 register */
    USARTx->CR5 &= ((uint8_t)~USART_CR5_IREN);
  }
}
/**
  * @brief  Enables or disables the USART Smart Card mode.
  * @param  USARTx: Select the USARTx peripheral.
  * @param  NewState: new state of the Smart Card mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the SC mode by setting the SCEN bit in the CR5 register */
    USARTx->CR5 |= USART_CR5_SCEN;
  }
  else
  {
    /* Disable the SC mode by clearing the SCEN bit in the CR5 register */
    USARTx->CR5 &= ((uint8_t)(~USART_CR5_SCEN));
  }
}

/**
  * @brief  Enables or disables NACK transmission.
  * @param  USARTx : where x can be 1 to select the specified USART peripheral.
  * @param  NewState: new state of the Smart Card mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the NACK transmission by setting the NACK bit in the CR5 register */
    USARTx->CR5 |= USART_CR5_NACK;
  }
  else
  {
    /* Disable the NACK transmission by clearing the NACK bit in the CR5 register */
    USARTx->CR5 &= ((uint8_t)~(USART_CR5_NACK));
  }
}
/**
  * @brief  Sets the specified USART guard time.
  * @note   SmartCard Mode should be Enabled
  * @param  USARTx : where x can be 1 to select the specified USART peripheral.
  * @param  USART_GuardTime: specifies the guard time.
  * @retval None
  */
void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime)
{
  /* Set the USART guard time */
  USARTx->GTR = USART_GuardTime;
}

/**
  * @brief  Sets the system clock prescaler.
  * @note   IrDA Low Power mode or smartcard mode should be enabled
  * @note   This function is related to SmartCard and IrDa mode.
  * @param  USARTx: Select the USARTx peripheral.
  * @param  USART_Prescaler: specifies the prescaler clock.
  *         This parameter can be one of the following values:
  *         @par IrDA Low Power Mode
  *         The clock source is diveded by the value given in the register (8 bits)
  *         - 0000 0000 Reserved
  *         - 0000 0001 divides the clock source by 1
  *         - 0000 0010 divides the clock source by 2
  *         - ...........................................................
  *        @par Smart Card Mode
  *        The clock source is diveded by the value given in the register
  *        (5 significant bits) multipied by 2
  *         - 0 0000 Reserved
  *         - 0 0001 divides the clock source by 2
  *         - 0 0010 divides the clock source by 4
  *         - 0 0011 divides the clock source by 6
  *         - ...........................................................
  * @retval None
  */
void USART_SetPrescaler(USART_TypeDef* USARTx, uint8_t USART_Prescaler)
{
  /* Load the USART prescaler value*/
  USARTx->PSCR = USART_Prescaler;
}

/**
  * @brief  Returns the most recent received data by the USART peripheral.
  * @param  USARTx : where x can be 1 to select the specified USART peripheral.
  * @retval The received data.
  */
uint8_t USART_ReceiveData8(USART_TypeDef* USARTx)
{
  return USARTx->DR;
}


/**
  * @brief  Returns the most recent received data by the USART peripheral.
  * @param  USARTx : where x can be 1 to select the specified USART peripheral.
  * @retval The received data.
  */
uint16_t USART_ReceiveData9(USART_TypeDef* USARTx)
{
  uint16_t temp = 0;

  temp = ((uint16_t)(((uint16_t)((uint16_t)USARTx->CR1 & (uint16_t)USART_CR1_R8)) << 1));
  return (uint16_t)( ((uint16_t)((uint16_t)USARTx->DR) | temp) & ((uint16_t)0x01FF));
}

/**
  * @brief  Determines if the USART is in mute mode or not.
  * @param  USARTx : where x can be 1 to select the specified USART peripheral.
  * @param  NewState : The new state of the USART mode.
  *         This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void USART_ReceiverWakeUpCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the mute mode USART by setting the RWU bit in the CR2 register */
    USARTx->CR2 |= USART_CR2_RWU;
  }
  else
  {
    /* Disable the mute mode USART by clearing the RWU bit in the CR1 register */
    USARTx->CR2 &= ((uint8_t)~USART_CR2_RWU);
  }
}

/**
  * @brief  Transmits break characters.
  * @param  USARTx : where x can be 1 to select the specified USART peripheral.
  * @retval None
  */
void USART_SendBreak(USART_TypeDef* USARTx)
{
  USARTx->CR2 |= USART_CR2_SBK;
}

/**
  * @brief  Transmits 8 bit data through the USART peripheral.
  * @param  Data: The data to transmit.
  * @retval None
  */
void USART_SendData8(USART_TypeDef* USARTx, uint8_t Data)
{
  /* Transmit Data */
  USARTx->DR = Data;
}

/**
  * @brief  Transmits 9 bit data through the USART peripheral.
  * @param  USARTx: Select the USARTx peripheral.
  * @param  Data : The data to transmit.
  *         This parameter should be lower than 0x1FF.
  * @retval None
  */
void USART_SendData9(USART_TypeDef* USARTx, uint16_t Data)
{
  assert_param(IS_USART_DATA_9BITS(Data));

  /* Clear the transmit data bit 8     */
  USARTx->CR1 &= ((uint8_t)~USART_CR1_T8);

  /* Write the transmit data bit [8]   */
  USARTx->CR1 |= (uint8_t)(((uint8_t)(Data >> 2)) & USART_CR1_T8);

  /* Write the transmit data bit [0:7] */
  USARTx->DR   = (uint8_t)(Data);
}

/**
  * @brief  Sets the address of the USART node.
  * @param  USARTx: Select the USARTx peripheral.
  * @param  Address : Indicates the address of the USART node.
  *         This parameter should be lower than 16
  * @retval None
  */
void USART_SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address)
{
  /* assert_param for USART_Address */
  assert_param(IS_USART_ADDRESS(USART_Address));

  /* Clear the USART address */
  USARTx->CR4 &= ((uint8_t)~USART_CR4_ADD);
  /* Set the USART address node */
  USARTx->CR4 |= USART_Address;
}

/**
  * @brief  Selects the USART WakeUp method.
  * @param  USART_WakeUp : Specifies the USART wakeup method.
  *         This parameter can be any of the @ref USART_WakeUp_TypeDef values
  * @retval None
  */
void USART_WakeUpConfig(USART_TypeDef* USARTx, USART_WakeUp_TypeDef USART_WakeUp)
{
  assert_param(IS_USART_WAKEUP(USART_WakeUp));

  USARTx->CR1 &= ((uint8_t)~USART_CR1_WAKE);
  USARTx->CR1 |= (uint8_t)USART_WakeUp;
}

/**
  * @brief  Enables or disables the USART DMA interface.
  * @param  USARTx : where x can be 1 to select the specified USART peripheral.
  * @param  USART_DMAReq Specifies the USART DMA transfer request to be enabled or disabled.
  *         This parameter can be any of the @ref USART_DMAReq_TypeDef enumeration.
  * @param  NewState Indicates the new state of the USART DMA request.
  *         This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void USART_DMACmd(USART_TypeDef* USARTx, USART_DMAReq_TypeDef USART_DMAReq,
                  FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_DMAREQ(USART_DMAReq));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the DMA transfer for selected requests by setting the DMAT and/or
       DMAR bits in the USART CR5 register */
    USARTx->CR5 |= (uint8_t) USART_DMAReq;
  }
  else
  {
    /* Disable the DMA transfer for selected requests by clearing the DMAT and/or
       DMAR bits in the USART CR5 register */
    USARTx->CR5 &= (uint8_t)~USART_DMAReq;
  }
}

/**
  * @brief  Checks whether the specified USART flag is set or not.
  * @param  USARTx: Select the USARTx peripheral.
  * @param  USART_FLAG specifies the flag to check.
  *         This parameter can be any of the @ref USART_FLAG_TypeDef enumeration.
  * @retval FlagStatus (SET or RESET)
  */
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, USART_FLAG_TypeDef USART_FLAG)
{
  FlagStatus status = RESET;

  /* Check parameters */
  assert_param(IS_USART_FLAG(USART_FLAG));

  if (USART_FLAG == USART_FLAG_SBK)
  {
    if ((USARTx->CR2 & (uint8_t)USART_FLAG) != (uint8_t)0x00)
    {
      /* USART_FLAG is set*/
      status = SET;
    }
    else
    {
      /* USART_FLAG is reset*/
      status = RESET;
    }
  }
  else
  {
    if ((USARTx->SR & (uint8_t)USART_FLAG) != (uint8_t)0x00)
    {
      /* USART_FLAG is set*/
      status = SET;
    }
    else
    {
      /* USART_FLAG is reset*/
      status = RESET;
    }
  }
  /* Return the USART_FLAG status*/
  return status;
}

/**
  * @brief  Clears the USARTx's pending flags.
  * @param  USARTx : where x can be 1 to select the specified USART peripheral.
  * @param  USART_FLAG: specifies the flag to clear.
  *         This parameter can be any combination of the following values:
  *         USART_FLAG_TC:   Transmission Complete flag.
  *         USART_FLAG_RXNE: Receive data register not empty flag.
  *
  * @Note
  *     - PE (Parity error), FE (Framing error), NE (Noise error), OR (OverRun error)
  *       and IDLE (Idle line detected) flags are cleared by software sequence: a read
  *       operation to USART_SR register (USART_GetFlagStatus())followed by a read
  *       operation to USART_DR register(USART_ReceiveData8() or USART_ReceiveData9()).
  *
  *     - RXNE flag can be also cleared by a read to the USART_DR register
  *       (USART_ReceiveData8()or USART_ReceiveData9()).
  *
  *     - TC flag can be also cleared by software sequence: a read operation to USART_SR
  *       register (USART_GetFlagStatus()) followed by a write operation to USART_DR
  *       register (USART_SendData8() or USART_SendData9()).
  *
  *     - TXE flag is cleared only by a write to the USART_DR register
  *       (USART_SendData8() or USART_SendData9()).
  *
  *     - SBK flag is cleared during the stop bit of break.
  *
  * @retval None
  */
void USART_ClearFlag(USART_TypeDef* USARTx, USART_FLAG_TypeDef USART_FLAG)
{
  /* Check the parameters */
  assert_param(IS_USART_CLEAR_FLAG(USART_FLAG));
  /*< Clear RXNE or TC flags */
  USARTx->SR = (uint8_t)((uint16_t)~((uint16_t)USART_FLAG));
}

/**
  * @brief  Checks whether the specified USART interrupt has occurred or not.
  * @param  USARTx : where x can be 1 to select the specified USART peripheral.
  * @param  USART_IT: Specifies the USART interrupt pending bit to check.
  *         This parameter can be one of the following values:
  *         - USART_IT_TXE: Transmit Data Register empty interrupt
  *         - USART_IT_TC: Transmission complete interrupt
  *         - USART_IT_RXNE: Receive Data register not empty interrupt
  *         - USART_IT_IDLE: Idle line detection interrupt
  *         - USART_IT_OR: OverRun Error interrupt
  *         - USART_IT_PE: Parity Error interrupt
  *         - USART_IT_FE: Frame Error interrupt
  *         - USART_IT_NF: Noise Flag Error interrupt
  * @retval ITStatus The new state of USART_IT (SET or RESET).
  */
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, USART_IT_TypeDef USART_IT)
{
  ITStatus pendingbitstatus = RESET;
  uint8_t temp = 0;
  uint8_t itpos = 0;
  uint8_t itmask1 = 0;
  uint8_t itmask2 = 0;
  uint8_t enablestatus = 0;

  /* Check parameters */
  assert_param(IS_USART_GET_IT(USART_IT));

  /* Get the USART IT index */
  itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)USART_IT & (uint8_t)0x0F));
  /* Get the USART IT index */
  itmask1 = (uint8_t)((uint8_t)USART_IT >> (uint8_t)4);
  /* Set the IT mask*/
  itmask2 = (uint8_t)((uint8_t)1 << itmask1);

  /* Check the status of the specified USART pending bit*/
  if (USART_IT == USART_IT_PE)
  {
    /* Get the USART_IT enable bit status*/
    enablestatus = (uint8_t)((uint8_t)USARTx->CR1 & itmask2);
    /* Check the status of the specified USART interrupt*/

    if (((USARTx->SR & itpos) != (uint8_t)0x00) && enablestatus)
    {
      /* Interrupt occurred*/
      pendingbitstatus = SET;
    }
    else
    {
      /* Interrupt not occurred*/
      pendingbitstatus = RESET;
    }
  }

  else if (USART_IT == USART_IT_OR)
  {
    /* Get the USART_IT enable bit status*/
    enablestatus = (uint8_t)((uint8_t)USARTx->CR2 & itmask2);
    /* Check the status of the specified USART interrupt*/

    temp = (uint8_t)(USARTx->CR5 & USART_CR5_EIE);

    if (( (USARTx->SR & itpos) != 0x00) && ((enablestatus || temp)))
    {
      /* Interrupt occurred*/
      pendingbitstatus = SET;
    }
    else
    {
      /* Interrupt not occurred*/
      pendingbitstatus = RESET;
    }
  }

  else
  {
    /* Get the USART_IT enable bit status*/
    enablestatus = (uint8_t)((uint8_t)USARTx->CR2 & itmask2);
    /* Check the status of the specified USART interrupt*/
    if (((USARTx->SR & itpos) != (uint8_t)0x00) && enablestatus)
    {
      /* Interrupt occurred*/
      pendingbitstatus = SET;
    }
    else
    {
      /* Interrupt not occurred*/
      pendingbitstatus = RESET;
    }
  }

  /* Return the USART_IT status*/
  return  pendingbitstatus;
}

/**
  * @brief  Clears the USARTx’s interrupt pending bits.
  * @param  USARTx : where x can be 1 to select the specified USART peripheral.
  * @param  USART_IT: specifies the interrupt pending bit to clear.
  *         This parameter can be one of the following values:
  *         USART_IT_RXNE: Receive Data register not empty interrupt.
  *         USART_IT_TC:   Transmission complete interrupt.
  *
  * @note
  *         - PE (Parity error), FE (Framing error), NE (Noise error),
  *         OR (OverRun error) and IDLE (Idle line detected) pending bits are
  *         cleared by software sequence: a read operation to USART_SR register
  *         (USART_GetITStatus()) followed by a read operation to USART_DR
  *         register (USART_ReceiveData8() or USART_ReceiveData9()).
  *
  *         - RXNE pending bit can be also cleared by a read to the USART_DR register
  *         (USART_ReceiveData8() or USART_ReceiveData9()).
  *
  *         - TC (Transmit complet) pending bit can be also cleared by software
  *         sequence: a read operation to USART_SR register (USART_GetITStatus())
  *         followed by a write operation to USART_DR register (USART_SendData8()
  *         or USART_SendData9()).
  *
  *         - TXE pending bit is cleared only by a write to the USART_DR register
  *         (USART_SendData8() or USART_SendData9()).
  *
  * @retval None
  */
void USART_ClearITPendingBit(USART_TypeDef* USARTx, USART_IT_TypeDef USART_IT)
{
  uint8_t bitpos = 0x00, itmask = 0x00;
  assert_param(IS_USART_CLEAR_IT(USART_IT));
  bitpos = (uint8_t)( (uint8_t)((uint8_t)USART_IT & (uint8_t)0xF0) >> 0x04);
  itmask = (uint8_t)( (uint8_t)0x01 << bitpos);
  /*< Clear RXNE or TC pending bit */
  USARTx->SR = (uint8_t)~itmask;
}


/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
