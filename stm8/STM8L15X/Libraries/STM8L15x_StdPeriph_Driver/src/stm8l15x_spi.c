/**
  ******************************************************************************
  * @file    stm8l15x_spi.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    09/24/2010
  * @brief   This file provides all the SPI firmware functions.
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
#include "stm8l15x_spi.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @addtogroup SPI_Public_Functions
  * @{
  */

/**
  * @brief  Deinitializes the SPI peripheral registers to their default reset values.
  * @param  SPIx : where x can be 1 to select the specified SPI peripheral.
  * @param  None
  * @retval None
  */
void SPI_DeInit(SPI_TypeDef* SPIx)
{
  SPIx->CR1    = SPI_CR1_RESET_VALUE;
  SPIx->CR2    = SPI_CR2_RESET_VALUE;
  SPIx->CR3    = SPI_CR3_RESET_VALUE;
  SPIx->SR     = SPI_SR_RESET_VALUE;
  SPIx->CRCPR  = SPI_CRCPR_RESET_VALUE;
}

/**
  * @brief  Initializes the SPI according to the specified parameters.
  * @param  SPIx : where x can be 1 to select the specified SPI peripheral.
  * @param  SPI_FirstBit : This parameter can be any of the
  *         @ref SPI_FirstBit_TypeDef enumeration.
  * @param  SPI_BaudRatePrescaler : This parameter can be any of the
  *         @ref SPI_BaudRatePrescaler_TypeDef enumeration.
  * @param  SPI_Mode : This parameter can be any of the  @ref SPI_Mode_TypeDef
  *         enumeration.
  * @param  SPI_CPOL : This parameter can be any of the @ref SPI_CPOL_TypeDef
  *         enumeration.
  * @param  SPI_CPHA : This parameter can be any of the @ref SPI_CPHA_TypeDef
  *         enumeration.
  * @param  SPI_Data_Direction : This parameter can be any of the
  *         @ref SPI_DirectionMode_TypeDef enumeration.
  * @param  SPI_Slave_Management : This parameter can be any of the
  *         @ref SPI_NSS_TypeDef enumeration.
  * @param  CRCPolynomial : Configures the CRC polynomial.
  * @retval None
  */
void SPI_Init(SPI_TypeDef* SPIx, SPI_FirstBit_TypeDef SPI_FirstBit,
              SPI_BaudRatePrescaler_TypeDef SPI_BaudRatePrescaler,
              SPI_Mode_TypeDef SPI_Mode, SPI_CPOL_TypeDef SPI_CPOL,
              SPI_CPHA_TypeDef SPI_CPHA, SPI_DirectionMode_TypeDef SPI_Data_Direction,
              SPI_NSS_TypeDef SPI_Slave_Management, uint8_t CRCPolynomial)
{
  /* Check structure elements */
  assert_param(IS_SPI_FIRSTBIT(SPI_FirstBit));
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
  assert_param(IS_SPI_MODE(SPI_Mode));
  assert_param(IS_SPI_POLARITY(SPI_CPOL));
  assert_param(IS_SPI_PHASE(SPI_CPHA));
  assert_param(IS_SPI_DATA_DIRECTION(SPI_Data_Direction));
  assert_param(IS_SPI_SLAVEMANAGEMENT(SPI_Slave_Management));
  assert_param(IS_SPI_CRC_POLYNOMIAL(CRCPolynomial));

  /* Frame Format, BaudRate, Clock Polarity and Phase configuration */
  SPIx->CR1 = (uint8_t)((uint8_t)((uint8_t)SPI_FirstBit |
                                  (uint8_t)SPI_BaudRatePrescaler) |
                        (uint8_t)((uint8_t)SPI_CPOL |
                                  SPI_CPHA));

  /* Data direction configuration: BDM, BDOE and RXONLY bits */
  SPIx->CR2 = (uint8_t)((uint8_t)(SPI_Data_Direction) | (uint8_t)(SPI_Slave_Management));

  if (SPI_Mode == SPI_Mode_Master)
  {
    SPIx->CR2 |= (uint8_t)SPI_CR2_SSI;
  }
  else
  {
    SPIx->CR2 &= (uint8_t)~(SPI_CR2_SSI);
  }

  /* Master/Slave mode configuration */
  SPIx->CR1 |= (uint8_t)(SPI_Mode);

  /* CRC configuration */
  SPIx->CRCPR = (uint8_t)CRCPolynomial;
}

/**
  * @brief  Enables or disables the SPI peripheral.
  * @param  SPIx : where x can be 1 to select the specified SPI peripheral.
  * @param  NewState New state of the SPI peripheral.
  *         This parameter can be: ENABLE or DISABLE
  * @retval None
  */
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    SPIx->CR1 |= SPI_CR1_SPE; /* Enable the SPI peripheral*/
  }
  else
  {
    SPIx->CR1 &= (uint8_t)(~SPI_CR1_SPE); /* Disable the SPI peripheral*/
  }
}

/**
  * @brief  Enables or disables the specified interrupts.
  * @param  SPIx : where x can be 1 to select the specified SPI peripheral.
  * @param  SPI_IT Specifies the SPI interrupts sources to be enabled or disabled.
  * @param  NewState: The new state of the specified SPI interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_ITConfig(SPI_TypeDef* SPIx, SPI_IT_TypeDef SPI_IT, FunctionalState NewState)
{
  uint8_t itpos = 0;
  /* Check function parameters */
  assert_param(IS_SPI_CONFIG_IT(SPI_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Get the SPI IT index */
  itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)SPI_IT & (uint8_t)0x0F));

  if (NewState != DISABLE)
  {
    SPIx->CR3 |= itpos; /* Enable interrupt*/
  }
  else
  {
    SPIx->CR3 &= (uint8_t)(~itpos); /* Disable interrupt*/
  }
}
/**
  * @brief  Transmits a Data through the SPI peripheral.
  * @param  SPIx : where x can be 1 to select the specified SPI peripheral.
  * @param  Data : Byte to be transmitted.
  * @retval None
  */
void SPI_SendData(SPI_TypeDef* SPIx, uint8_t Data)
{
  SPIx->DR = Data; /* Write in the DR register the data to be sent*/
}

/**
  * @brief  Returns the most recent received data by the SPI peripheral.
  * @param  SPIx : where x can be 1 to select the specified SPI peripheral.
  * @retval The value of the received data.
  */
uint8_t SPI_ReceiveData(SPI_TypeDef* SPIx)
{
  return ((uint8_t)SPIx->DR); /* Return the data in the DR register*/
}

/**
  * @brief  Configures internally by software the NSS pin.
  * @param  SPIx : where x can be 1 to select the specified SPI peripheral.
  * @param  NewState Indicates the new state of the SPI Software slave management.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_NSSInternalSoftwareCmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    SPIx->CR2 |= SPI_CR2_SSI; /* Set NSS pin internally by software*/
  }
  else
  {
    SPIx->CR2 &= (uint8_t)(~SPI_CR2_SSI); /* Reset NSS pin internally by software*/
  }
}

/**
  * @brief  Enables the transmit of the CRC value.
  * @param  SPIx : where x can be 1 to select the specified SPI peripheral.
  * @retval None
  */
void SPI_TransmitCRC(SPI_TypeDef* SPIx)
{
  SPIx->CR2 |= SPI_CR2_CRCNEXT; /* Enable the CRC transmission*/
}

/**
  * @brief  Enables or disables the CRC value calculation of the transfered bytes.
  * @param  SPIx : where x can be 1 to select the specified SPI peripheral.
  * @param  NewState Indicates the new state of the SPI CRC value calculation.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_CalculateCRCCmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* SPI must be disable forcorrect operation od Hardware CRC calculation */
  SPI_Cmd(SPI1, DISABLE);

  if (NewState != DISABLE)
  {
    SPIx->CR2 |= SPI_CR2_CRCEN; /* Enable the CRC calculation*/
  }
  else
  {
    SPIx->CR2 &= (uint8_t)(~SPI_CR2_CRCEN); /* Disable the CRC calculation*/
  }
}

/**
  * @brief  Returns the transmit or the receive CRC register value.
  * @param  SPIx : where x can be 1 to select the specified SPI peripheral.
  * @param  SPI_CRC Specifies the CRC register to be read.
  * @retval The selected CRC register value.
  */
uint8_t SPI_GetCRC(SPI_TypeDef* SPIx, SPI_CRC_TypeDef SPI_CRC)
{
  uint8_t crcreg = 0;

  /* Check function parameters */
  assert_param(IS_SPI_CRC(SPI_CRC));

  if (SPI_CRC != SPI_CRC_RX)
  {
    crcreg = SPIx->TXCRCR;  /* Get the Tx CRC register*/
  }
  else
  {
    crcreg = SPIx->RXCRCR; /* Get the Rx CRC register*/
  }

  /* Return the selected CRC register status*/
  return crcreg;
}

/**
  * @brief  Reset the Rx CRCR and Tx CRCR registers.
  * @param  SPIx : where x can be 1 to select the specified SPI peripheral.
  * @retval None
  */
void SPI_ResetCRC(SPI_TypeDef* SPIx)
{
  /* Rx CRCR & Tx CRCR registers are reset when CRCEN (hardware calculation)
     bit in SPI_CR2 is written to 1 (enable) */
  SPI_CalculateCRCCmd(SPIx, ENABLE);

  /* Previous function disable the SPI */
  SPI_Cmd(SPIx, ENABLE);
}

/**
  * @brief  Returns the CRC Polynomial register value.
  * @param  SPIx : where x can be 1 to select the specified SPI peripheral.
  * @retval uint8_t The CRC Polynomial register value.
  */
uint8_t SPI_GetCRCPolynomial(SPI_TypeDef* SPIx)
{
  return SPIx->CRCPR; /* Return the CRC polynomial register */
}

/**
  * @brief  Selects the data transfer direction in bi-directional mode.
  * @param  SPIx : where x can be 1 to select the specified SPI peripheral.
  * @param  SPI_Direction Specifies the data transfer direction in bi-directional mode.
  * @retval None
  */
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, SPI_Direction_TypeDef SPI_Direction)
{
  /* Check function parameters */
  assert_param(IS_SPI_DIRECTION(SPI_Direction));

  if (SPI_Direction != SPI_Direction_Rx)
  {
    SPIx->CR2 |= SPI_CR2_BDOE; /* Set the Tx only mode*/
  }
  else
  {
    SPIx->CR2 &= (uint8_t)(~SPI_CR2_BDOE); /* Set the Rx only mode*/
  }
}
/**
  * @brief  Enables or disables the SPI DMA interface.
  * @param  SPIx : where x can be 1 to select the specified SPI peripheral.
  * @param  SPI_DMAReq Specifies the SPI DMA transfer request to be enabled or disabled.
  *         This parameter can be any of the @ref SPI_DMAReq_TypeDef enumeration.
  * @param  NewState Indicates the new state of the SPI DMA request.
  *         This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void SPI_DMACmd(SPI_TypeDef* SPIx, SPI_DMAReq_TypeDef SPI_DMAReq, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_SPI_DMAREQ(SPI_DMAReq));

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI DMA requests */
    SPIx->CR3 |= (uint8_t) SPI_DMAReq;
  }
  else
  {
    /* Disable the selected SPI DMA requests */
    SPIx->CR3 &= (uint8_t)~SPI_DMAReq;
  }
}
/**
  * @brief  Checks whether the specified SPI flag is set or not.
  * @param  SPIx : where x can be 1 to select the specified SPI peripheral.
  * @param  SPI_FLAG : Specifies the flag to check.
  *         This parameter can be any of the @ref SPI_FLAG_TypeDef enumeration.
  * @retval FlagStatus : Indicates the state of SPI_FLAG.
  *         This parameter can be any of the @ref FlagStatus enumeration.
  */

FlagStatus SPI_GetFlagStatus(SPI_TypeDef* SPIx, SPI_FLAG_TypeDef SPI_FLAG)
{
  FlagStatus status = RESET;
  /* Check parameters */
  assert_param(IS_SPI_FLAG(SPI_FLAG));

  /* Check the status of the specified SPI flag */
  if ((SPIx->SR & (uint8_t)SPI_FLAG) != (uint8_t)RESET)
  {
    status = SET; /* SPI_FLAG is set */
  }
  else
  {
    status = RESET; /* SPI_FLAG is reset*/
  }

  /* Return the SPI_FLAG status */
  return status;
}

/**
  * @brief  Clears the SPI flags.
  * @param  SPIx : where x can be 1 to select the specified SPI peripheral.
  * @param  SPI_FLAG : Specifies the flag to clear.
  *         This parameter can be one of the following values:
  *         - SPI_FLAG_CRCERR
  *         - SPI_FLAG_WKUP
  * @note   - OVR (OverRun Error) interrupt pending bit is cleared by software
  *         sequence:
  *         a read operation to SPI_DR register (SPI_ReceiveData()) followed by
  *         a read operation to SPI_SR register (SPI_GetFlagStatus()).
  *         - MODF (Mode Fault) interrupt pending bit is cleared by software sequence:
  *         a read/write operation to SPI_SR register (SPI_GetFlagStatus()) followed by
  *         a write operation to SPI_CR1 register (SPI_Cmd() to enable the SPI).
  * @retval None
  */
void SPI_ClearFlag(SPI_TypeDef* SPIx, SPI_FLAG_TypeDef SPI_FLAG)
{
  assert_param(IS_SPI_CLEAR_FLAG(SPI_FLAG));
  /* Clear the flag bit */
  SPIx->SR = (uint8_t)(~SPI_FLAG);
}

/**
  * @brief  Checks whether the specified interrupt has occurred or not.
  * @param  SPIx : where x can be 1 to select the specified SPI peripheral.
  * @param  SPI_IT: Specifies the SPI interrupt pending bit to check.
  *         This parameter can be one of the following values:
  *         - SPI_IT_CRCERR
  *         - SPI_IT_WKUP
  *         - SPI_IT_OVR
  *         - SPI_IT_MODF
  *         - SPI_IT_RXNE
  *         - SPI_IT_TXE
  * @retval ITStatus : Indicates the state of the SPI_IT.
  *         This parameter can be any of the @ref ITStatus enumeration.
  */
ITStatus SPI_GetITStatus(SPI_TypeDef* SPIx, SPI_IT_TypeDef SPI_IT)
{
  ITStatus pendingbitstatus = RESET;
  uint8_t itpos = 0;
  uint8_t itmask1 = 0;
  uint8_t itmask2 = 0;
  __IO uint8_t enablestatus = 0;
  assert_param(IS_SPI_GET_IT(SPI_IT));
  /* Get the SPI IT index */
  itpos = (uint8_t)((uint8_t)1 << ((uint8_t)SPI_IT & (uint8_t)0x0F));

  /* Get the SPI IT mask */
  itmask1 = (uint8_t)((uint8_t)SPI_IT >> (uint8_t)4);
  /* Set the IT mask */
  itmask2 = (uint8_t)((uint8_t)1 << itmask1);
  /* Get the SPI_IT enable bit status */
  enablestatus = (uint8_t)((uint8_t)SPIx->SR & itmask2);
  /* Check the status of the specified SPI interrupt */
  if (((SPIx->CR3 & itpos) != RESET) && enablestatus)
  {
    /* SPI_IT is set */
    pendingbitstatus = SET;
  }
  else
  {
    /* SPI_IT is reset */
    pendingbitstatus = RESET;
  }
  /* Return the SPI_IT status */
  return  pendingbitstatus;
}

/**
  * @brief  Clears the interrupt pending bits.
  * @param  SPIx : where x can be 1 to select the specified SPI peripheral.
  * @param  SPI_IT: Specifies the interrupt pending bit to clear.
  *         This parameter can be one of the following values:
  *         - SPI_IT_CRCERR
  *         - SPI_IT_WKUP
  * @note   - OVR (OverRun Error) interrupt pending bit is cleared by software sequence:
  *         a read operation to SPI_DR register (SPI_ReceiveData()) followed by
  *         a read operation to SPI_SR register (SPI_GetITStatus()).
  *         - MODF (Mode Fault) interrupt pending bit is cleared by software sequence:
  *         a read/write operation to SPI_SR register (SPI_GetITStatus()) followed by
  *         a write operation to SPI_CR1 register (SPI_Cmd() to enable the SPI).
  * @retval None
  */
void SPI_ClearITPendingBit(SPI_TypeDef* SPIx, SPI_IT_TypeDef SPI_IT)
{
  uint8_t itpos = 0;
  assert_param(IS_SPI_CLEAR_IT(SPI_IT));

  /* Clear  SPI_IT_CRCERR or SPI_IT_WKUP interrupt pending bits */

  /* Get the SPI pending bit index */
  itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)(SPI_IT & (uint8_t)0xF0) >> 4));
  /* Clear the pending bit */
  SPIx->SR = (uint8_t)(~itpos);

}
/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
