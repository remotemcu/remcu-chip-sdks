/**
  ******************************************************************************
  * @file    stm8l15x_itc.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    09/24/2010
  * @brief   This file provides all the ITC firmware functions.
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
#include "stm8l15x_itc.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @addtogroup ITC_Private_Functions
  * @{
  */

/**
  * @brief  Utility function used to read CC register.
  * @param  None
  * @retval CPU CC register value
  */
uint8_t ITC_GetCPUCC(void)
{
#ifdef _COSMIC_
  _asm("push cc");
  _asm("pop a");
  return; /* Ignore compiler warning, the returned value is in A register */
#elif defined _RAISONANCE_ /* _RAISONANCE_ */
  return _getCC_();
#else /* _IAR_ */
  asm("push cc");
  asm("pop a");
  return 0;
#endif /* _COSMIC_*/
}

/**
  * @}
  */

/** @addtogroup ITC_Public_Functions
  * @{
  */

/**
  * @brief  Deinitializes the ITC registers to their default reset value.
  * @param  None
  * @retval None
 */
void ITC_DeInit(void)
{
  ITC->ISPR1 = ITC_SPRX_RESET_VALUE;
  ITC->ISPR2 = ITC_SPRX_RESET_VALUE;
  ITC->ISPR3 = ITC_SPRX_RESET_VALUE;
  ITC->ISPR4 = ITC_SPRX_RESET_VALUE;
  ITC->ISPR5 = ITC_SPRX_RESET_VALUE;
  ITC->ISPR6 = ITC_SPRX_RESET_VALUE;
  ITC->ISPR7 = ITC_SPRX_RESET_VALUE;
  ITC->ISPR8 = ITC_SPRX_RESET_VALUE;
}

/**
  * @brief  Gets the interrupt software priority bits (I1, I0) value from CPU CC register.
  * @param  None
  * @retval The interrupt software priority bits value.
 */
uint8_t ITC_GetSoftIntStatus(void)
{
  return ((uint8_t)(ITC_GetCPUCC() & CPU_SOFT_INT_DISABLED));
}

/**
  * @brief  Gets the software priority of the specified interrupt source.
  * @param  IRQn : Specifies the peripheral interrupt source.
  * @retval ITC_PriorityLevel_TypeDef : Specifies the software priority of the interrupt source.
 */
ITC_PriorityLevel_TypeDef ITC_GetSoftwarePriority(IRQn_TypeDef IRQn)
{
  uint8_t Value = 0;
  uint8_t Mask = 0;

  /* Check function parameters */
  assert_param(IS_ITC_IRQ(IRQn));

  /* Define the mask corresponding to the bits position in the SPR register */
  Mask = (uint8_t)(0x03U << ((IRQn % 4U) * 2U));

  switch (IRQn)
  {
    case FLASH_IRQn:
    case DMA1_CHANNEL0_1_IRQn:
    case DMA1_CHANNEL2_3_IRQn:
      Value = (uint8_t)(ITC->ISPR1 & Mask); /* Read software priority */
      break;

    case EXTIE_F_PVD_IRQn:
#ifdef STM8L15X_MD
    case RTC_IRQn:
    case EXTIB_IRQn:
    case EXTID_IRQn:
#elif defined (STM8L15X_HD) || defined (STM8L15X_MDP)
    case RTC_CSSLSE_IRQn:
    case EXTIB_G_IRQn:
    case EXTID_H_IRQn:
#endif  /* STM8L15X_MD */
      Value = (uint8_t)(ITC->ISPR2 & Mask); /* Read software priority */
      break;

    case EXTI0_IRQn:
    case EXTI1_IRQn:
    case EXTI2_IRQn:
    case EXTI3_IRQn:
      Value = (uint8_t)(ITC->ISPR3 & Mask); /* Read software priority */
      break;

    case EXTI4_IRQn:
    case EXTI5_IRQn:
    case EXTI6_IRQn:
    case EXTI7_IRQn:
      Value = (uint8_t)(ITC->ISPR4 & Mask); /* Read software priority */
      break;


    case SWITCH_CSS_BREAK_DAC_IRQn:
    case ADC1_COMP_IRQn:
#ifdef STM8L15X_MD
    case LCD_IRQn:
    case TIM2_UPD_OVF_TRG_BRK_IRQn:
#elif defined (STM8L15X_HD) || defined (STM8L15X_MDP)
    case LCD_AES_IRQn:
    case TIM2_UPD_OVF_TRG_BRK_USART2_TX_IRQn:
#endif  /* STM8L15X_MD */
      Value = (uint8_t)(ITC->ISPR5 & Mask); /* Read software priority */
      break;

    case TIM1_UPD_OVF_TRG_IRQn:
#ifdef STM8L15X_MD
    case TIM2_CC_IRQn:
    case TIM3_UPD_OVF_TRG_BRK_IRQn :
    case TIM3_CC_IRQn:
#elif defined (STM8L15X_HD) || defined (STM8L15X_MDP)
    case TIM2_CC_USART2_RX_IRQn:
    case TIM3_UPD_OVF_TRG_BRK_USART3_TX_IRQn :
    case TIM3_CC_USART3_RX_IRQn:
#endif  /* STM8L15X_MD */
      Value = (uint8_t)(ITC->ISPR6 & Mask); /* Read software priority */
      break;

    case TIM1_CC_IRQn:
    case TIM4_UPD_OVF_TRG_IRQn:
    case SPI1_IRQn:
#ifdef STM8L15X_MD
    case USART1_TX_IRQn:
#elif defined (STM8L15X_HD) || defined (STM8L15X_MDP)
    case USART1_TX_TIM5_UPD_OVF_TRG_BRK_IRQn:
#endif  /* STM8L15X_MD */
      Value = (uint8_t)(ITC->ISPR7 & Mask); /* Read software priority */
      break;

#ifdef STM8L15X_MD
    case USART1_RX_IRQn:
    case I2C1_IRQn:
#elif defined (STM8L15X_HD) || defined (STM8L15X_MDP)
    case USART1_RX_TIM5_CC_IRQn:
    case I2C1_SPI2_IRQn:
#endif  /* STM8L15X_MD */
      Value = (uint8_t)(ITC->ISPR8 & Mask); /* Read software priority */
      break;

    default:
      break;
  }

  Value >>= (uint8_t)((IRQn % 4u) * 2u);

  return((ITC_PriorityLevel_TypeDef)Value);

}

/**
  * @brief  Sets the software priority of the specified interrupt source.
  * @note   - The modification of the software priority is only possible when
  *         the interrupts are disabled.
  *         - The normal behavior is to disable the interrupt before calling
  *         this function, and re-enable it after.
  *         - The priority level 0 cannot be set (see product specification
  *         for more details).
  * @param  IRQn : Specifies the peripheral interrupt source.
  * @param  ITC_PriorityLevel : Specifies the software priority value to set,
  *         can be a value of @ref  ITC_PriorityLevel_TypeDef .
  * @retval None
  */
void ITC_SetSoftwarePriority(IRQn_TypeDef IRQn, ITC_PriorityLevel_TypeDef ITC_PriorityLevel)
{
  uint8_t Mask = 0;
  uint8_t NewPriority = 0;

  /* Check function parameters */
  assert_param(IS_ITC_IRQ(IRQn));
  assert_param(IS_ITC_PRIORITY(ITC_PriorityLevel));

  /* Check if interrupts are disabled */
  assert_param(IS_ITC_INTERRUPTS_DISABLED);

  /* Define the mask corresponding to the bits position in the SPR register */
  /* The mask is reversed in order to clear the 2 bits after more easily */
  Mask = (uint8_t)(~(uint8_t)(0x03U << ((IRQn % 4U) * 2U)));
  /* Define the new priority to write */
  NewPriority = (uint8_t)((uint8_t)(ITC_PriorityLevel) << ((IRQn % 4U) * 2U));

  switch (IRQn)
  {
    case FLASH_IRQn:
    case DMA1_CHANNEL0_1_IRQn:
    case DMA1_CHANNEL2_3_IRQn:
      ITC->ISPR1 &= Mask;
      ITC->ISPR1 |= NewPriority;
      break;

    case EXTIE_F_PVD_IRQn:
#ifdef STM8L15X_MD
    case RTC_IRQn:
    case EXTIB_IRQn:
    case EXTID_IRQn:
#elif defined (STM8L15X_HD) || defined (STM8L15X_MDP)
    case RTC_CSSLSE_IRQn:
    case EXTIB_G_IRQn:
    case EXTID_H_IRQn:
#endif  /* STM8L15X_MD */
      ITC->ISPR2 &= Mask;
      ITC->ISPR2 |= NewPriority;
      break;

    case EXTI0_IRQn:
    case EXTI1_IRQn:
    case EXTI2_IRQn:
    case EXTI3_IRQn:
      ITC->ISPR3 &= Mask;
      ITC->ISPR3 |= NewPriority;
      break;

    case EXTI4_IRQn:
    case EXTI5_IRQn:
    case EXTI6_IRQn:
    case EXTI7_IRQn:
      ITC->ISPR4 &= Mask;
      ITC->ISPR4 |= NewPriority;
      break;

    case SWITCH_CSS_BREAK_DAC_IRQn:
    case ADC1_COMP_IRQn:
#ifdef STM8L15X_MD
    case LCD_IRQn:
    case TIM2_UPD_OVF_TRG_BRK_IRQn:
#elif defined (STM8L15X_HD) || defined (STM8L15X_MDP)
    case LCD_AES_IRQn:
    case TIM2_UPD_OVF_TRG_BRK_USART2_TX_IRQn:
#endif  /* STM8L15X_MD */
      ITC->ISPR5 &= Mask;
      ITC->ISPR5 |= NewPriority;
      break;

    case TIM1_UPD_OVF_TRG_IRQn:
#ifdef STM8L15X_MD
    case TIM2_CC_IRQn:
    case TIM3_UPD_OVF_TRG_BRK_IRQn :
    case TIM3_CC_IRQn:
#elif defined (STM8L15X_HD) || defined (STM8L15X_MDP)
    case TIM2_CC_USART2_RX_IRQn:
    case TIM3_UPD_OVF_TRG_BRK_USART3_TX_IRQn :
    case TIM3_CC_USART3_RX_IRQn:
#endif  /* STM8L15X_MD */
      ITC->ISPR6 &= Mask;
      ITC->ISPR6 |= NewPriority;
      break;


    case TIM1_CC_IRQn:
    case TIM4_UPD_OVF_TRG_IRQn:
    case SPI1_IRQn:
#ifdef STM8L15X_MD
    case USART1_TX_IRQn:
#elif defined (STM8L15X_HD) || defined (STM8L15X_MDP)
    case USART1_TX_TIM5_UPD_OVF_TRG_BRK_IRQn:
#endif  /* STM8L15X_MD */
      ITC->ISPR7 &= Mask;
      ITC->ISPR7 |= NewPriority;
      break;

#ifdef STM8L15X_MD
    case USART1_RX_IRQn:
    case I2C1_IRQn:
#elif defined (STM8L15X_HD) || defined (STM8L15X_MDP)
    case USART1_RX_TIM5_CC_IRQn:
    case I2C1_SPI2_IRQn:
#endif  /* STM8L15X_MD */
      ITC->ISPR8 &= Mask;
      ITC->ISPR8 |= NewPriority;
      break;

    default:
      break;
  }
}

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
