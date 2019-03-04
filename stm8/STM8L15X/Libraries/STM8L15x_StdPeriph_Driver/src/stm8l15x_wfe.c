/**
  ******************************************************************************
  * @file    stm8l15x_wfe.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    09/24/2010
  * @brief   This file provides all the WFE firmware functions.
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
#include "stm8l15x_wfe.h"

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

/** @addtogroup WFE_Public_Functions
  * @{
  */

/**
  * @brief  Deinitializes the WFE registers to their default reset value.
  * @param  None
  * @retval None
  */
void WFE_DeInit(void)
{
  WFE->CR1 = WFE_CRX_RESET_VALUE;
  WFE->CR2 = WFE_CRX_RESET_VALUE;
  WFE->CR3 = WFE_CRX_RESET_VALUE;
  WFE->CR4 = WFE_CRX_RESET_VALUE;
}

/**
  * @brief  Set the source that can generate the wake-up event.
  * @param  WFE_Source: The wake-up event source .
  *         This parameter can be a value of @ref WFE_Source_TypeDef enumeration
  * @param  NewState : The wake-up new state.
  *         This parameter can be a value of  @ref FunctionalState enumeration.
  * @retval None
  */
void WFE_WakeUpSourceEventCmd(WFE_Source_TypeDef WFE_Source, FunctionalState NewState)
{
  uint8_t register_index = 0;
  /* Check function parameters */
  assert_param(IS_WFE_SOURCE(WFE_Source));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* The mask is reversed in order to  */
  register_index = (uint8_t)((uint16_t)WFE_Source >> 0x08);

  if (NewState != DISABLE)
  {
    switch (register_index)
    {
      case 1:
        WFE->CR1 |= (uint8_t)WFE_Source;
        break;

      case 2:
        WFE->CR2 |= (uint8_t)WFE_Source;
        break;

      case 3:
        WFE->CR3 |= (uint8_t)WFE_Source;
        break;

      case 4:
        WFE->CR4 |= (uint8_t)WFE_Source;
        break;

      default:
        break;
    }
  }
  else
  {
    switch (register_index)
    {
      case 1:
        WFE->CR1 &= (uint8_t)(~(uint8_t)WFE_Source);
        break;

      case 2:
        WFE->CR2 &= (uint8_t)(~ (uint8_t)WFE_Source);
        break;

      case 3:
        WFE->CR3 &= (uint8_t)(~(uint8_t)WFE_Source);
        break;

      case 4:
        WFE->CR4 &= (uint8_t)(~(uint8_t)WFE_Source);
        break;

      default:
        break;
    }
  }
}

/**
  * @brief  Gets the status of the specified source event.
  * @param  WFE_Source: The wake-up event source.
  *         This parameter can be a value of @ref WFE_Source_TypeDef enumeration
  * @retval FunctionalState : Source Event state, ENABLE or DISABLE
  */
FunctionalState WFE_GetWakeUpSourceEventStatus(WFE_Source_TypeDef WFE_Source)
{
  FunctionalState status = DISABLE;
  /* Check function parameters */
  assert_param(IS_WFE_SOURCE(WFE_Source));

  switch (WFE_Source)
  {
    case WFE_Source_TIM2_EV0:
    case WFE_Source_TIM2_EV1:
    case WFE_Source_TIM1_EV0:
    case WFE_Source_TIM1_EV1:
    case WFE_Source_EXTI_EV0:
    case WFE_Source_EXTI_EV1:
    case WFE_Source_EXTI_EV2:
    case WFE_Source_EXTI_EV3:

      if ((WFE->CR1 & (uint8_t)WFE_Source) != (uint8_t)0x00)
      {
        /* The wake-up event source is enabled*/
        status = ENABLE;
      }
      else
      {
        /* The wake-up event source is disabled*/
        status = DISABLE;
      }
      break;

    case WFE_Source_EXTI_EV4:
    case WFE_Source_EXTI_EV5:
    case WFE_Source_EXTI_EV6:
    case WFE_Source_EXTI_EV7:
    case WFE_Source_EXTI_EVB_G:
    case WFE_Source_EXTI_EVD_H:
    case WFE_Source_EXTI_EVE_F:
    case WFE_Source_ADC1_COMP_EV:

      if ((WFE->CR2 & (uint8_t)WFE_Source) != (uint8_t)0x00)
      {
        /* The wake-up event source is enabled*/
        status = ENABLE;
      }
      else
      {
        /* The wake-up event source is disabled*/
        status = DISABLE;
      }
      break;
    case WFE_Source_TIM3_EV0:
    case WFE_Source_TIM3_EV1:
    case WFE_Source_TIM4_EV:
    case WFE_Source_SPI1_EV:
    case WFE_Source_I2C1_EV:
    case WFE_Source_USART1_EV:
    case WFE_Source_DMA1CH01_EV:
    case WFE_Source_DMA1CH23_EV:

      if ((WFE->CR3 & (uint8_t)WFE_Source) != (uint8_t)0x00)
      {
        /* The wake-up event source is enabled*/
        status = ENABLE;
      }
      else
      {
        /* The wake-up event source is disabled*/
        status = DISABLE;
      }
      break;

    case WFE_Source_TIM5_EV0:
    case WFE_Source_TIM5_EV1:
    case WFE_Source_AES_EV:
    case WFE_Source_SPI2_EV:
    case WFE_Source_USART2_EV:
    case WFE_Source_USART3_EV:
    case WFE_Source_RTC_CSS_EV:

      if ((WFE->CR4 & (uint8_t)WFE_Source) != (uint8_t)0x00)
      {
        /* The wake-up event source is enabled*/
        status = ENABLE;
      }
      else
      {
        /* The wake-up event source is disabled*/
        status = DISABLE;
      }
      break;
    default:
      break;
  }
  return status;
}

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
