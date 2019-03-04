/**
  ******************************************************************************
  * @file    stm8l15x_exti.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    09/24/2010
  * @brief   This file provides all the EXTI firmware functions.
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
#include "stm8l15x_exti.h"

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
  * @addtogroup EXTI_Public_Functions
  * @{
  */

/**
  * @brief  Deinitializes the EXTI registers to their default reset value.
  * @param  None
  * @retval None
  */
void EXTI_DeInit(void)
{
  EXTI->CR1 = EXTI_CR1_RESET_VALUE;
  EXTI->CR2 = EXTI_CR2_RESET_VALUE;
  EXTI->CR3 = EXTI_CR3_RESET_VALUE;
  EXTI->CR4 = EXTI_CR4_RESET_VALUE;
  EXTI->SR1 = 0xFF; /* Setting SR1 bits in order to clear flags */
  EXTI->SR2 = 0xFF; /* Setting SR2 bits in order to clear flags */
  EXTI->CONF1 = EXTI_CONF1_RESET_VALUE;
  EXTI->CONF2 = EXTI_CONF2_RESET_VALUE;
}

/**
  * @brief  Sets the external interrupt sensitivity of the selected port.
  * @note   - Global interrupts must be disabled before calling this function.
  * @note   - The modification of external interrupt sensitivity is only possible
  *         when the interrupts are disabled.
  *         - The normal behavior is to disable the interrupts before calling this
  *         function, and re-enable them after.
  * @param  EXTI_Port : The port number to access.
  *         This parameter can be a value of @ref EXTI_Port_TypeDef
  * @param  EXTI_Trigger : The external interrupt sensitivity value to set.
  *         This parameter can be a value of @ref EXTI_Trigger_TypeDef
  * @retval None
  */
void EXTI_SetPortSensitivity(EXTI_Port_TypeDef EXTI_Port,
                             EXTI_Trigger_TypeDef EXTI_Trigger)
{
  /* Check function parameters */
  assert_param(IS_EXTI_PORT(EXTI_Port));
  assert_param(IS_EXTI_TRIGGER(EXTI_Trigger));

  /* Ceck if selected port is in EXTI_CR3 register */
  if ((EXTI_Port & 0xF0) == 0x00)
  {
    /* Reset the trigger bits corresponding to EXTI_Port */
    EXTI->CR3 &= (uint8_t) (~(uint8_t)((uint8_t)0x03 << EXTI_Port));
    /* Write EXTI port trigger */
    EXTI->CR3 |= (uint8_t)((uint8_t)(EXTI_Trigger) << EXTI_Port);
  }
  else /* selected port is in EXTI_CR4 register */
  {
    /* Reset the trigger bits corresponding to EXTI_Port */
    EXTI->CR4 &= (uint8_t) (~(uint8_t)((uint8_t)0x03 << (EXTI_Port & 0x0F)));
    /* Write EXTI port trigger */
    EXTI->CR4 |= (uint8_t)(EXTI_Trigger << (EXTI_Port & 0x0F));
  }
}

/**
  * @brief  Sets the external interrupt sensitivity of the selected pin.
  * @note   - Global interrupts must be disabled before calling this function.
  * @note   - The modification of external interrupt sensitivity is only possible
  *         when he interrupts are disabled.
  *         - The normal behavior is to disable the interrupts before calling this
  *         function, and re-enable them after.
  * @param  EXTI_Pin : The pin to configure.
  *         This parameter can be a value of @ref EXTI_Pin_TypeDef
  * @param  EXTI_Trigger : The external interrupt sensitivity value to set.
  *         This parameter can be a value of @ref EXTI_Trigger_TypeDef
  * @retval None
  */
void EXTI_SetPinSensitivity(EXTI_Pin_TypeDef EXTI_Pin,
                            EXTI_Trigger_TypeDef EXTI_Trigger)
{

  /* Check function parameters */
  assert_param(IS_EXTI_PINNUM(EXTI_Pin));
  assert_param(IS_EXTI_TRIGGER(EXTI_Trigger));

  /* Clear port sensitivity bits */
  switch (EXTI_Pin)
  {
    case EXTI_Pin_0:
      EXTI->CR1 &=  (uint8_t)(~EXTI_CR1_P0IS);
      EXTI->CR1 |= (uint8_t)((uint8_t)(EXTI_Trigger) << EXTI_Pin);
      break;
    case EXTI_Pin_1:
      EXTI->CR1 &=  (uint8_t)(~EXTI_CR1_P1IS);
      EXTI->CR1 |= (uint8_t)((uint8_t)(EXTI_Trigger) << EXTI_Pin);
      break;
    case EXTI_Pin_2:
      EXTI->CR1 &=  (uint8_t)(~EXTI_CR1_P2IS);
      EXTI->CR1 |= (uint8_t)((uint8_t)(EXTI_Trigger) << EXTI_Pin);
      break;
    case EXTI_Pin_3:
      EXTI->CR1 &=  (uint8_t)(~EXTI_CR1_P3IS);
      EXTI->CR1 |= (uint8_t)((uint8_t)(EXTI_Trigger) << EXTI_Pin);
      break;
    case EXTI_Pin_4:
      EXTI->CR2 &=  (uint8_t)(~EXTI_CR2_P4IS);
      EXTI->CR2 |= (uint8_t)((uint8_t)(EXTI_Trigger) << ((uint8_t)EXTI_Pin & (uint8_t)0xEF));
      break;
    case EXTI_Pin_5:
      EXTI->CR2 &=  (uint8_t)(~EXTI_CR2_P5IS);
      EXTI->CR2 |= (uint8_t)((uint8_t)(EXTI_Trigger) << ((uint8_t)EXTI_Pin & (uint8_t)0xEF));
      break;
    case EXTI_Pin_6:
      EXTI->CR2 &=  (uint8_t)(~EXTI_CR2_P6IS);
      EXTI->CR2 |= (uint8_t)((uint8_t)(EXTI_Trigger) << ((uint8_t)EXTI_Pin & (uint8_t)0xEF));
      break;
    case EXTI_Pin_7:
      EXTI->CR2 &=  (uint8_t)(~EXTI_CR2_P7IS);
      EXTI->CR2 |= (uint8_t)((uint8_t)(EXTI_Trigger) << ((uint8_t)EXTI_Pin & (uint8_t)0xEF));
      break;
    default:
      break;
  }
}

/**
  * @brief  Selects the port interrupt selection.
  * @param  EXTI_Port : The port number to access.
  *         This parameter can be a value of @ref EXTI_Port_TypeDef
  * @retval None
  */
void EXTI_SelectPort(EXTI_Port_TypeDef EXTI_Port)
{
  /* Check function parameter */
  assert_param(IS_EXTI_PORT(EXTI_Port));

  if (EXTI_Port == EXTI_Port_B)
  {
    /* Select Port B by resetting PGBS bit in CONF2 register */
    EXTI->CONF2 &= (uint8_t) (~EXTI_CONF2_PGBS);
  }
  else if (EXTI_Port == EXTI_Port_D)
  {
    /* Select Port D by resetting PHDS bit in CONF2 register */
    EXTI->CONF2 &= (uint8_t) (~EXTI_CONF2_PHDS);
  }
  else if (EXTI_Port == EXTI_Port_E)
  {
    /* Select Port E by resetting PFES bit in CONF1 register */
    EXTI->CONF1 &= (uint8_t) (~EXTI_CONF1_PFES);
  }
  else if (EXTI_Port == EXTI_Port_F)
  {
    /* Select Port F by setting PFES bit in CONF1 register */
    EXTI->CONF1 |= (uint8_t) (EXTI_CONF1_PFES);
  }
  else if (EXTI_Port == EXTI_Port_G)
  {
    /* Select Port G by setting PGBS bit in CONF2 register */
    EXTI->CONF2 |= (uint8_t) (EXTI_CONF2_PGBS);
  }
  else /* EXTI_Port is EXTI_Port_H */
  {
    /* Select Port H by setting PHDS bit in CONF2 register */
    EXTI->CONF2 |= (uint8_t) (EXTI_CONF2_PHDS);
  }
}

/**
  * @brief  Configures the half port interrupt selection.
  * @note   - This function should be called once the port sensitivity configured,
  *         otherwise it will not have any effect on the port external interrupt.
  *         - This function should be called after EXTI_SelectPort() function which
  *         selects the port to be used otherwise ports are selected by default
  * @param  EXTI_HalfPort : The port part to access (MSB or LSB).
  *         This parameter can be a value of @ref EXTI_HalfPort_TypeDef
  * @param  NewState : The external interrupt new state.
  *         This parameter can be a value of @ref FunctionalState.
  * @retval None
  */
void EXTI_SetHalfPortSelection(EXTI_HalfPort_TypeDef EXTI_HalfPort,
                               FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_EXTI_HALFPORT(EXTI_HalfPort));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if ((EXTI_HalfPort & 0x80) == 0x00)
  {
    if (NewState != DISABLE)
    {
      /* Enable port interrupt selector */
      EXTI->CONF1 |= (uint8_t)EXTI_HalfPort;
    }
    else /*NewState == DISABLE */
    {
      /* Disable port interrupt selector */
      EXTI->CONF1 &= (uint8_t)(~(uint8_t)EXTI_HalfPort);
    }
  }
  else
  {
    if (NewState != DISABLE)
    {
      /* Enable port interrupt selector */
      EXTI->CONF2 |= (uint8_t)(EXTI_HalfPort & (uint8_t)0x7F);
    }
    else /*NewState == DISABLE */
    {
      /* Disable port interrupt selector */
      EXTI->CONF2 &= (uint8_t)(~(uint8_t) (EXTI_HalfPort & (uint8_t)0x7F));
    }
  }
}

/**
  * @brief  Gets the external interrupt sensitivity of the selected port.
  * @param  EXTI_Port : The port number to access.
  *         This parameter can be a value of @ref EXTI_Port_TypeDef
  * @retval EXTI_Trigger_TypeDef : The external interrupt sensitivity of the selected port.
  */
EXTI_Trigger_TypeDef EXTI_GetPortSensitivity(EXTI_Port_TypeDef EXTI_Port)
{
  uint8_t portsensitivity = 0;

  /* Check function parameters */
  assert_param(IS_EXTI_PORT(EXTI_Port));

  /* Check if selected port is in EXTI_CR3 */
  if ((EXTI_Port & 0xF0) == 0x00)
  {
    /* Get port sensitivity */
    portsensitivity = (uint8_t)((uint8_t)0x03 & (uint8_t)(EXTI->CR3 >> EXTI_Port));
  }
  /* selected port is in EXTI_CR4 */
  else
  {
    /* Get port sensitivity */
    portsensitivity = (uint8_t)((uint8_t)0x03 & (uint8_t)(EXTI->CR4 >> (EXTI_Port & 0x0F)));
  }

  return((EXTI_Trigger_TypeDef)portsensitivity);
}

/**
  * @brief  Gets the external interrupt sensitivity of the selected pin.
  * @param  EXTI_Pin : The pin number to access.
  *         This parameter can be a value of @ref EXTI_Pin_TypeDef
  * @retval EXTI_Trigger_TypeDef : The external interrupt sensitivity of the selected port.
  */
EXTI_Trigger_TypeDef EXTI_GetPinSensitivity(EXTI_Pin_TypeDef EXTI_Pin)
{
  uint8_t value = 0;

  /* Check function parameters */
  assert_param(IS_EXTI_PINNUM(EXTI_Pin));

  switch (EXTI_Pin)
  {
    case EXTI_Pin_0:
      value = (uint8_t)(EXTI->CR1 & EXTI_CR1_P0IS);
      break;
    case EXTI_Pin_1:
      value = (uint8_t)((uint8_t)(EXTI->CR1 & EXTI_CR1_P1IS) >> EXTI_Pin_1);
      break;
    case EXTI_Pin_2:
      value = (uint8_t)((uint8_t)(EXTI->CR1 & EXTI_CR1_P2IS) >> EXTI_Pin_2);
      break;
    case EXTI_Pin_3:
      value = (uint8_t)((uint8_t)(EXTI->CR1 & EXTI_CR1_P3IS) >> EXTI_Pin_3);
      break;
    case EXTI_Pin_4:
      value = (uint8_t)(EXTI->CR2 & EXTI_CR2_P4IS);
      break;
    case EXTI_Pin_5:
      value = (uint8_t)((uint8_t)(EXTI->CR2 & EXTI_CR2_P5IS) >> ((uint8_t)EXTI_Pin_5 & (uint8_t)0x0F));
      break;
    case EXTI_Pin_6:
      value = (uint8_t)((uint8_t)(EXTI->CR2 & EXTI_CR2_P6IS) >> ((uint8_t)EXTI_Pin_6 & (uint8_t)0x0F));
      break;
    case EXTI_Pin_7:
      value = (uint8_t)((uint8_t)(EXTI->CR2 & EXTI_CR2_P7IS) >> ((uint8_t)EXTI_Pin_7 & (uint8_t)0x0F));
      break;
    default:
      break;
  }
  return((EXTI_Trigger_TypeDef)value);
}

/**
  * @brief  Gets the external interrupt status.
  * @param  EXTI_IT : Specifies the interrupt to read.
  *         This parameter can be a value of @ref EXTI_IT_TypeDef
  * @retval ITStatus : The status of the specified interrupt.
  *         This parameter can be a value of @ref ITStatus.
  */
ITStatus EXTI_GetITStatus(EXTI_IT_TypeDef EXTI_IT)
{
  ITStatus status = RESET;
  /* Check function parameters */
  assert_param(IS_EXTI_ITPENDINGBIT(EXTI_IT));

  if (((uint16_t)EXTI_IT & (uint16_t)0xFF00) == 0x0100)
  {
    status = (ITStatus)(EXTI->SR2 & (uint8_t)((uint16_t)EXTI_IT & (uint16_t)0x00FF));
  }
  else
  {
    status = (ITStatus)(EXTI->SR1 & ((uint8_t)((uint16_t)EXTI_IT & (uint16_t)0x00FF)));
  }
  return((ITStatus)status);
}

/**
  * @brief  Clears the specified interrupt pending bit
  * @param  EXTI_IT : Specifies the interrupt to clear
  *         This parameter can be a value of @ref EXTI_IT_TypeDef
  * @retval None
  */
void EXTI_ClearITPendingBit(EXTI_IT_TypeDef EXTI_IT)
{
  uint16_t tempvalue = 0;

  /* Check function parameters */
  assert_param(IS_EXTI_ITPENDINGBIT(EXTI_IT));

  tempvalue = ((uint16_t)EXTI_IT & (uint16_t)0xFF00);

  if ( tempvalue == 0x0100)
  {
    EXTI->SR2 = (uint8_t)((uint16_t)EXTI_IT & (uint16_t)0x00FF);
  }
  else
  {
    EXTI->SR1 = (uint8_t) (EXTI_IT);
  }
}
/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
