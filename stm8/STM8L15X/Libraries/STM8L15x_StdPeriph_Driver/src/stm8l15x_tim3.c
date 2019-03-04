/**
  ******************************************************************************
  * @file    stm8l15x_tim3.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    09/24/2010
  * @brief   This file provides all the TIM3 firmware functions.
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
#include "stm8l15x_tim3.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void TI1_Config(TIM3_ICPolarity_TypeDef TIM3_ICPolarity,
                       TIM3_ICSelection_TypeDef TIM3_ICSelection,
                       uint8_t TIM3_ICFilter);
static void TI2_Config(TIM3_ICPolarity_TypeDef TIM3_ICPolarity,
                       TIM3_ICSelection_TypeDef TIM3_ICSelection,
                       uint8_t TIM3_ICFilter);


/**
  * @addtogroup TIM3_Public_Functions
  * @{
  */

/**
  * @brief  Deinitializes the TIM3 peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void TIM3_DeInit(void)
{
  TIM3->CR1 = TIM_CR1_RESET_VALUE;
  TIM3->CR2 = TIM_CR2_RESET_VALUE;
  TIM3->SMCR = TIM_SMCR_RESET_VALUE;
  TIM3->ETR = TIM_ETR_RESET_VALUE;
  TIM3->IER = TIM_IER_RESET_VALUE;
  TIM3->SR2 = TIM_SR2_RESET_VALUE;

  /* Disable channels */
  TIM3->CCER1 = TIM_CCER1_RESET_VALUE;
  /* Configure channels as inputs: it is necessary if lock level is equal to 2 or 3 */
  TIM3->CCMR1 = 0x01;/* TIM3_ICxSource_TIxFPx */
  TIM3->CCMR2 = 0x01;/* TIM3_ICxSource_TIxFPx */

  /* Then reset channel registers: it also works if lock level is equal to 2 or 3 */
  TIM3->CCER1 = TIM_CCER1_RESET_VALUE;
  TIM3->CCMR1 = TIM_CCMR1_RESET_VALUE;
  TIM3->CCMR2 = TIM_CCMR2_RESET_VALUE;

  TIM3->CNTRH = TIM_CNTRH_RESET_VALUE;
  TIM3->CNTRL = TIM_CNTRL_RESET_VALUE;

  TIM3->PSCR = TIM_PSCR_RESET_VALUE;

  TIM3->ARRH = TIM_ARRH_RESET_VALUE;
  TIM3->ARRL = TIM_ARRL_RESET_VALUE;

  TIM3->CCR1H = TIM_CCR1H_RESET_VALUE;
  TIM3->CCR1L = TIM_CCR1L_RESET_VALUE;
  TIM3->CCR2H = TIM_CCR2H_RESET_VALUE;
  TIM3->CCR2L = TIM_CCR2L_RESET_VALUE;


  TIM3->OISR = TIM_OISR_RESET_VALUE;
  TIM3->EGR = 0x01;/* TIM_EGR_UG */
  TIM3->BKR = TIM_BKR_RESET_VALUE;
  TIM3->SR1 = TIM_SR1_RESET_VALUE;
}

/**
  * @brief  Initializes the TIM3 Time Base Unit according to the specified parameters.
  * @param  TIM3_Prescaler : This parameter can be any member of the @Ref TIM3_Prescaler_TypeDef enumeration.
  * @param  TIM3_CounterMode : This parameter can be any member of the @Ref TIM3_CounterMode_TypeDef enumeration.
  * @param  TIM3_Period : This parameter must be a value between 0x0000 and 0xFFFF.
  * @retval None
  */

void TIM3_TimeBaseInit(TIM3_Prescaler_TypeDef TIM3_Prescaler,
                       TIM3_CounterMode_TypeDef TIM3_CounterMode,
                       uint16_t TIM3_Period)
{

  assert_param(IS_TIM3_PRESCALER(TIM3_Prescaler));
  assert_param(IS_TIM3_COUNTER_MODE(TIM3_CounterMode));



  /* Set the Autoreload value */
  TIM3->ARRH = (uint8_t)(TIM3_Period >> 8) ;
  TIM3->ARRL = (uint8_t)(TIM3_Period);

  /* Set the Prescaler value */
  TIM3->PSCR = (uint8_t)(TIM3_Prescaler);

  /* Select the Counter Mode */
  TIM3->CR1 &= (uint8_t)((uint8_t)(~TIM_CR1_CMS)) & ((uint8_t)(~TIM_CR1_DIR));
  TIM3->CR1 |= (uint8_t)(TIM3_CounterMode);

  /* Generate an update event to reload the Prescaler value immediately */
  TIM3->EGR = TIM3_EventSource_Update;
}

/**
  * @brief Initializes the TIM3 Channel1 according to the specified parameters.
  * @param  TIM3_OCMode : This parameter can be any member of the @Ref TIM3_OCMode_TypeDef enumeration.
  * @param  TIM3_OutputState : This parameter can be any member of the @Ref TIM3_OutputState_TypeDef enumeration.
  * @param  TIM3_Pulse : This parameter must be a value between 0x0000 and 0xFFFF.
  * @param  TIM3_OCPolarity : This parameter can be any member of the @Ref TIM3_OCPolarity_TypeDef enumeration.
  * @param  TIM3_OCIdleState : This parameter can be any member of the @Ref TIM3_OCIdleState_TypeDef  enumeration.
  * @retval None
  */
void TIM3_OC1Init(TIM3_OCMode_TypeDef TIM3_OCMode,
                  TIM3_OutputState_TypeDef TIM3_OutputState,
                  uint16_t TIM3_Pulse,
                  TIM3_OCPolarity_TypeDef TIM3_OCPolarity,
                  TIM3_OCIdleState_TypeDef TIM3_OCIdleState)
{
  uint8_t tmpccmr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM3_OC_MODE(TIM3_OCMode));
  assert_param(IS_TIM3_OUTPUT_STATE(TIM3_OutputState));
  assert_param(IS_TIM3_OC_POLARITY(TIM3_OCPolarity));
  assert_param(IS_TIM3_OCIDLE_STATE(TIM3_OCIdleState));

  tmpccmr1 = TIM3->CCMR1;

  /* Disable the Channel 1: Reset the CCE Bit */
  TIM3->CCER1 &= (uint8_t)(~TIM_CCER1_CC1E);
  /* Reset the Output Compare Bits */
  tmpccmr1 &= (uint8_t)(~TIM_CCMR_OCM);

  /* Set the Ouput Compare Mode */
  tmpccmr1 |= (uint8_t)TIM3_OCMode;

  TIM3->CCMR1 = tmpccmr1;

  /* Set the Output State */
  if (TIM3_OutputState == TIM3_OutputState_Enable)
  {
    TIM3->CCER1 |= TIM_CCER1_CC1E;
  }
  else
  {
    TIM3->CCER1 &= (uint8_t)(~TIM_CCER1_CC1E);
  }

  /* Set the Output Polarity */
  if (TIM3_OCPolarity == TIM3_OCPolarity_Low)
  {
    TIM3->CCER1 |= TIM_CCER1_CC1P;
  }
  else
  {
    TIM3->CCER1 &= (uint8_t)(~TIM_CCER1_CC1P);
  }

  /* Set the Output Idle state */
  if (TIM3_OCIdleState == TIM3_OCIdleState_Set)
  {
    TIM3->OISR |= TIM_OISR_OIS1;
  }
  else
  {
    TIM3->OISR &= (uint8_t)(~TIM_OISR_OIS1);
  }

  /* Set the Pulse value */
  TIM3->CCR1H = (uint8_t)(TIM3_Pulse >> 8);
  TIM3->CCR1L = (uint8_t)(TIM3_Pulse);
}

/**
  * @brief  Initializes the TIM3 Channel2 according to the specified parameters.
  * @param  TIM3_OCMode : This parameter can be any member of the @Ref TIM3_OCMode_TypeDef enumeration.
  * @param  TIM3_OutputState : This parameter can be any member of the @Ref TIM3_OutputState_TypeDef enumeration.
  * @param  TIM3_Pulse : This parameter must be a value between 0x0000 and 0xFFFF.
  * @param  TIM3_OCPolarity : This parameter can be any member of the @Ref TIM3_OCPolarity_TypeDef enumeration.
  * @param  TIM3_OCIdleState : This parameter can be any member of the @Ref TIM3_OCIdleState_TypeDef  enumeration.
  * @retval None
  */
void TIM3_OC2Init(TIM3_OCMode_TypeDef TIM3_OCMode,
                  TIM3_OutputState_TypeDef TIM3_OutputState,
                  uint16_t TIM3_Pulse,
                  TIM3_OCPolarity_TypeDef TIM3_OCPolarity,
                  TIM3_OCIdleState_TypeDef TIM3_OCIdleState)
{
  uint8_t tmpccmr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM3_OC_MODE(TIM3_OCMode));
  assert_param(IS_TIM3_OUTPUT_STATE(TIM3_OutputState));
  assert_param(IS_TIM3_OC_POLARITY(TIM3_OCPolarity));
  assert_param(IS_TIM3_OCIDLE_STATE(TIM3_OCIdleState));

  tmpccmr2 = TIM3->CCMR2;

  /* Disable the Channel 2: Reset the CCE Bit */
  TIM3->CCER1 &= (uint8_t)(~TIM_CCER1_CC2E);

  /* Reset the Output Compare Bits */
  tmpccmr2 &= (uint8_t)(~TIM_CCMR_OCM);

  /* Set the Ouput Compare Mode */
  tmpccmr2 |= (uint8_t)TIM3_OCMode;

  TIM3->CCMR2 = tmpccmr2;

  /* Set the Output State */
  if (TIM3_OutputState == TIM3_OutputState_Enable)
  {
    TIM3->CCER1 |= TIM_CCER1_CC2E;
  }
  else
  {
    TIM3->CCER1 &= (uint8_t)(~TIM_CCER1_CC2E);
  }

  /* Set the Output Polarity */
  if (TIM3_OCPolarity == TIM3_OCPolarity_Low)
  {
    TIM3->CCER1 |= TIM_CCER1_CC2P;
  }
  else
  {
    TIM3->CCER1 &= (uint8_t)(~TIM_CCER1_CC2P);
  }


  /* Set the Output Idle state */
  if (TIM3_OCIdleState == TIM3_OCIdleState_Set)
  {
    TIM3->OISR |= TIM_OISR_OIS2;
  }
  else
  {
    TIM3->OISR &= (uint8_t)(~TIM_OISR_OIS2);
  }

  /* Set the Pulse value */
  TIM3->CCR2H = (uint8_t)(TIM3_Pulse >> 8);
  TIM3->CCR2L = (uint8_t)(TIM3_Pulse);
}

/**
  * @brief  Configures the Break feature, dead time, Lock level, the OSSI,
  * and the AOE(automatic output enable).
  * @param  TIM3_OSSIState : Off-State Selection for Idle mode states.
  *   This parameter can be any member of the @Ref TIM3_OSSIState_TypeDef enumeration.
  * @param  TIM3_LockLevel : Lock level.
  *   This parameter can be any member of the @Ref TIM3_LockLevel_TypeDef enumeration.
  * @param  TIM3_BreakState : Break Input enable/disable .
  *   This parameter can be any member of the @Ref TIM3_BreakState_TypeDef enumeration.
  * @param  TIM3_BreakPolarity : Break Polarity.
  *   This parameter can be any member of the @Ref TIM3_BreakPolarity_TypeDef enumeration.
  * @param  TIM3_AutomaticOutput : TIM3 AOE Bit Set/Reset .
  *   This parameter can be anymember of the @Ref TIM3_AutomaticOutput_TypeDef enumeration.
  * @retval None
  */
void TIM3_BKRConfig(TIM3_OSSIState_TypeDef TIM3_OSSIState,
                    TIM3_LockLevel_TypeDef TIM3_LockLevel,
                    TIM3_BreakState_TypeDef TIM3_BreakState,
                    TIM3_BreakPolarity_TypeDef TIM3_BreakPolarity,
                    TIM3_AutomaticOutput_TypeDef TIM3_AutomaticOutput)
{
  /* Check the parameters */
  assert_param(IS_TIM3_OSSI_STATE(TIM3_OSSIState));
  assert_param(IS_TIM3_LOCK_LEVEL(TIM3_LockLevel));
  assert_param(IS_TIM3_BREAK_STATE(TIM3_BreakState));
  assert_param(IS_TIM3_BREAK_POLARITY(TIM3_BreakPolarity));
  assert_param(IS_TIM3_AUTOMATIC_OUTPUT_STATE(TIM3_AutomaticOutput));



  /* Set the Lock level, the Break enable Bit and the Ploarity, the OSSI State,
  the dead time value and the Automatic Output Enable Bit */

  TIM3->BKR = (uint8_t)((uint8_t)((uint8_t)((uint8_t)((uint8_t)TIM3_OSSIState | (uint8_t)TIM3_LockLevel) | \
                                  (uint8_t)((uint8_t)TIM3_BreakState | (uint8_t)TIM3_BreakPolarity)) | \
                                  TIM3_AutomaticOutput));
}

/**
  * @brief  Initializes the TIM3 peripheral according to the specified parameters.
  * @param  TIM3_Channel : This parameter can be any member of the @Ref TIM3_Channel_TypeDef enumeration.
  * @param  TIM3_ICPolarity : This parameter can be any member of the @Ref TIM3_ICPolarity_TypeDef enumeration.
  * @param  TIM3_ICSelection : This parameter can be any member of the @Ref TIM3_ICSelection_TypeDef enumeration.
  * @param  TIM3_ICPrescaler : This parameter can be any member of the @Ref TIM3_ICPSC_TypeDef enumeration.
  * @param  TIM3_ICFilter : This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
void TIM3_ICInit(TIM3_Channel_TypeDef TIM3_Channel,
                 TIM3_ICPolarity_TypeDef TIM3_ICPolarity,
                 TIM3_ICSelection_TypeDef TIM3_ICSelection,
                 TIM3_ICPSC_TypeDef TIM3_ICPrescaler,
                 uint8_t TIM3_ICFilter)
{
  /* Check the parameters */
  assert_param(IS_TIM3_CHANNEL(TIM3_Channel));

  if (TIM3_Channel == TIM3_Channel_1)
  {
    /* TI1 Configuration */
    TI1_Config(TIM3_ICPolarity, TIM3_ICSelection, TIM3_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM3_SetIC1Prescaler(TIM3_ICPrescaler);
  }
  else /* if (TIM3_Channel == TIM3_Channel_2) */
  {
    /* TI2 Configuration */
    TI2_Config(TIM3_ICPolarity, TIM3_ICSelection, TIM3_ICFilter);
    /* Set the Input Capture Prescaler value */
    TIM3_SetIC2Prescaler(TIM3_ICPrescaler);
  }
}

/**
  * @brief  Configures the TIM3 peripheral in PWM Input Mode according to the
  * specified parameters.
  * @param  TIM3_Channel : This parameter can be any member of the @Ref TIM3_Channel_TypeDef enumeration.
  * @param  TIM3_ICPolarity : This parameter can be any member of the @Ref TIM3_ICPolarity_TypeDef enumeration.
  * @param  TIM3_ICSelection : This parameter can be any member of the @Ref TIM3_ICSelection_TypeDef enumeration.
  * @param  TIM3_ICPrescaler : This parameter can be any member of the @Ref TIM3_ICPSC_TypeDef enumeration.
  * @param  TIM3_ICFilter : This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
void TIM3_PWMIConfig(TIM3_Channel_TypeDef TIM3_Channel,
                     TIM3_ICPolarity_TypeDef TIM3_ICPolarity,
                     TIM3_ICSelection_TypeDef TIM3_ICSelection,
                     TIM3_ICPSC_TypeDef TIM3_ICPrescaler,
                     uint8_t TIM3_ICFilter)
{
  uint8_t icpolarity = TIM3_ICPolarity_Rising;
  uint8_t icselection = TIM3_ICSelection_DirectTI;

  /* Check the parameters */
  assert_param(IS_TIM3_CHANNEL(TIM3_Channel));

  /* Select the Opposite Input Polarity */
  if (TIM3_ICPolarity == TIM3_ICPolarity_Rising)
  {
    icpolarity = TIM3_ICPolarity_Falling;
  }
  else
  {
    icpolarity = TIM3_ICPolarity_Rising;
  }

  /* Select the Opposite Input */
  if (TIM3_ICSelection == TIM3_ICSelection_DirectTI)
  {
    icselection = TIM3_ICSelection_IndirectTI;
  }
  else
  {
    icselection = TIM3_ICSelection_DirectTI;
  }

  if (TIM3_Channel == TIM3_Channel_1)
  {
    /* TI1 Configuration */
    TI1_Config(TIM3_ICPolarity, TIM3_ICSelection, TIM3_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM3_SetIC1Prescaler(TIM3_ICPrescaler);

    /* TI2 Configuration */
    TI2_Config((TIM3_ICPolarity_TypeDef)icpolarity, (TIM3_ICSelection_TypeDef)icselection, TIM3_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM3_SetIC2Prescaler(TIM3_ICPrescaler);
  }
  else
  {
    /* TI2 Configuration */
    TI2_Config(TIM3_ICPolarity, TIM3_ICSelection, TIM3_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM3_SetIC2Prescaler(TIM3_ICPrescaler);

    /* TI1 Configuration */
    TI1_Config((TIM3_ICPolarity_TypeDef)icpolarity, (TIM3_ICSelection_TypeDef)icselection, TIM3_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM3_SetIC1Prescaler(TIM3_ICPrescaler);
  }
}

/**
  * @brief  Enables or disables the TIM3 peripheral.
  * @param NewState : The new state of the TIM3 peripheral.
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void TIM3_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* set or Reset the CEN Bit */
  if (NewState != DISABLE)
  {
    TIM3->CR1 |= TIM_CR1_CEN;
  }
  else
  {
    TIM3->CR1 &= (uint8_t)(~TIM_CR1_CEN);
  }
}

/**
  * @brief  Enables or disables the TIM3 peripheral Main Outputs.
  * @param NewState : The new state of the TIM3 peripheral.
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void TIM3_CtrlPWMOutputs(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the MOE Bit */

  if (NewState != DISABLE)
  {
    TIM3->BKR |= TIM_BKR_MOE ;
  }
  else
  {
    TIM3->BKR &= (uint8_t)(~TIM_BKR_MOE) ;
  }
}
/**
  * @brief  Enables or disables the specified TIM3 interrupts.
  * @param  TIM3_IT : Specifies the TIM3 interrupts sources to be enabled or disabled.
  *   This parameter can be any combination of the @ref TIM3_IT_TypeDef enumeration.
  * @param NewState : The new state of the TIM3 peripheral.
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void TIM3_ITConfig(TIM3_IT_TypeDef TIM3_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM3_IT(TIM3_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Interrupt sources */
    TIM3->IER |= (uint8_t)TIM3_IT;
  }
  else
  {
    /* Disable the Interrupt sources */
    TIM3->IER &= (uint8_t)(~(uint8_t)TIM3_IT);
  }
}

/**
  * @brief  Enables or disables the TIMx’s DMA Requests.
  * @param  TIM3_DMASources: specifies the DMA Request sources.
  *   This parameter can be any combination of the @ref TIM3_DMASource_TypeDef enumeration.
  * @param NewState: new state of the DMA Request sources. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM3_DMACmd(TIM3_DMASource_TypeDef TIM3_DMASource, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_TIM3_DMA_SOURCE(TIM3_DMASource));

  if (NewState != DISABLE)
  {
    /* Enable the DMA sources */
    TIM3->DER |= TIM3_DMASource;
  }
  else
  {
    /* Disable the DMA sources */
    TIM3->DER &= (uint8_t)~TIM3_DMASource;
  }
}
/**
  * @brief  Enables the TIM3 internal Clock.
  * @par Parameters:
  * None
  * @retval None
  */
void TIM3_InternalClockConfig(void)
{
  /* Disable slave mode to clock the prescaler directly with the internal clock */
  TIM3->SMCR &=  (uint8_t)(~TIM_SMCR_SMS);
}

/**
  * @brief  Configures the TIM3 External clock Mode1.
  * @param  TIM3_ExtTRGPrescaler : Specifies the external Trigger Prescaler.
  *   This parameter can be one of @ref TIM3_ExtTRGPSC_TypeDef enumeration.
  * @param  TIM3_ExtTRGPolarity : Specifies the external Trigger Polarity.
  *   This parameter can be one of @ref TIM3_ExtTRGPolarity_TypeDef enumeration.
  * @param ExtTRGFilter : Specifies the External Trigger Filter.
  *   This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TIM3_ETRClockMode1Config(TIM3_ExtTRGPSC_TypeDef TIM3_ExtTRGPrescaler,
                              TIM3_ExtTRGPolarity_TypeDef TIM3_ExtTRGPolarity,
                              uint8_t ExtTRGFilter)
{
  /* Configure the ETR Clock source */
  TIM3_ETRConfig(TIM3_ExtTRGPrescaler, TIM3_ExtTRGPolarity, ExtTRGFilter);

  /* Select the External clock mode1 */
  TIM3->SMCR &= (uint8_t)(~TIM_SMCR_SMS);
  TIM3->SMCR |= (uint8_t)(TIM3_SlaveMode_External1);

  /* Select the Trigger selection : ETRF */
  TIM3->SMCR &= (uint8_t)(~TIM_SMCR_TS);
  TIM3->SMCR |= (uint8_t)((TIM3_TRGSelection_TypeDef)TIM3_TRGSelection_ETRF);
}

/**
  * @brief  Configures the TIM3 External clock Mode2.
  * @param  TIM3_ExtTRGPrescaler : Specifies the external Trigger Prescaler.
  *   This parameter can be one of the @ref TIM3_ExtTRGPSC_TypeDef enumeration.
  * @param  TIM3_ExtTRGPolarity : Specifies the external Trigger Polarity.
  *   This parameter can be one of the @ref TIM3_ExtTRGPolarity_TypeDef enumeration.
  * @param ExtTRGFilter : Specifies the External Trigger Filter.
  *   This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TIM3_ETRClockMode2Config(TIM3_ExtTRGPSC_TypeDef TIM3_ExtTRGPrescaler,
                              TIM3_ExtTRGPolarity_TypeDef TIM3_ExtTRGPolarity,
                              uint8_t ExtTRGFilter)
{
  /* Configure the ETR Clock source */
  TIM3_ETRConfig(TIM3_ExtTRGPrescaler, TIM3_ExtTRGPolarity, ExtTRGFilter);

  /* Enable the External clock mode2 */
  TIM3->ETR |= TIM_ETR_ECE ;
}

/**
  * @brief  Configures the TIM3 External Trigger.
  * @param  TIM3_ExtTRGPrescaler : Specifies the external Trigger Prescaler.
  *   This parameter can be one of the @ref TIM3_ExtTRGPSC_TypeDef enumeration.
  * @param  TIM3_ExtTRGPolarity : Specifies the external Trigger Polarity.
  *   This parameter can be one of the @ref TIM3_ExtTRGPolarity_TypeDef enumeration.
  * @param ExtTRGFilter : Specifies the External Trigger Filter.
  *   This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TIM3_ETRConfig(TIM3_ExtTRGPSC_TypeDef TIM3_ExtTRGPrescaler,
                    TIM3_ExtTRGPolarity_TypeDef TIM3_ExtTRGPolarity,
                    uint8_t ExtTRGFilter)
{
  /* Check the parameters */
  assert_param(IS_TIM3_EXT_PRESCALER(TIM3_ExtTRGPrescaler));
  assert_param(IS_TIM3_EXT_POLARITY(TIM3_ExtTRGPolarity));
  assert_param(IS_TIM3_EXT_FILTER(ExtTRGFilter));

  /* Set the Prescaler, the Filter value and the Polarity */
  TIM3->ETR |= (uint8_t)((uint8_t)((uint8_t)TIM3_ExtTRGPrescaler | (uint8_t)TIM3_ExtTRGPolarity)
                         | (uint8_t)ExtTRGFilter);
}

/**
  * @brief  Configures the TIM3 Trigger as External Clock.
  * @param  TIM3_TIxExternalCLKSource : Specifies Trigger source.
  *   This parameter can be one of the @ref TIM3_TIxExternalCLK1Source_TypeDef enumeration.
  * @param  TIM3_ICPolarity : Specifies the TIx Polarity.
  *   This parameter can be @ref TIM3_ICPolarity_TypeDef enumeration.
  * @param ICFilter : Specifies the filter value.
  *   This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TIM3_TIxExternalClockConfig(TIM3_TIxExternalCLK1Source_TypeDef TIM3_TIxExternalCLKSource,
                                 TIM3_ICPolarity_TypeDef TIM3_ICPolarity,
                                 uint8_t ICFilter)
{
  /* Check the parameters */
  assert_param(IS_TIM3_TIXCLK_SOURCE(TIM3_TIxExternalCLKSource));
  assert_param(IS_TIM3_IC_POLARITY(TIM3_ICPolarity));
  assert_param(IS_TIM3_IC_FILTER(ICFilter));

  /* Configure the TIM3 Input Clock Source */
  if (TIM3_TIxExternalCLKSource == TIM3_TIxExternalCLK1Source_TI2)
  {
    TI2_Config(TIM3_ICPolarity, TIM3_ICSelection_DirectTI, ICFilter);
  }
  else
  {
    TI1_Config(TIM3_ICPolarity, TIM3_ICSelection_DirectTI, ICFilter);
  }

  /* Select the Trigger source */
  TIM3_SelectInputTrigger((TIM3_TRGSelection_TypeDef)TIM3_TIxExternalCLKSource);

  /* Select the External clock mode1 */
  TIM3->SMCR |= (uint8_t)(TIM3_SlaveMode_External1);
}

/**
  * @brief  Selects the TIM3 Input Trigger source.
  * @param  TIM3_InputTriggerSource : Specifies Input Trigger source.
  *   This parameter can be one of the @ref TIM3_TRGSelection_TypeDef enumeration.
  * @retval None
  */
void TIM3_SelectInputTrigger(TIM3_TRGSelection_TypeDef TIM3_InputTriggerSource)
{
  uint8_t tmpsmcr = 0;

  /* Check the parameters */
  assert_param(IS_TIM3_TRIGGER_SELECTION(TIM3_InputTriggerSource));

  tmpsmcr = TIM3->SMCR;

  /* Select the Tgigger Source */
  tmpsmcr &= (uint8_t)(~TIM_SMCR_TS);
  tmpsmcr |= (uint8_t)TIM3_InputTriggerSource;

  TIM3->SMCR = (uint8_t)tmpsmcr;
}

/**
  * @brief  Enables or Disables the TIM3 Update event.
  * @param NewState : The new state of the TIM3 peripheral Preload register.
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */

void TIM3_UpdateDisableConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the UDIS Bit */
  if (NewState != DISABLE)
  {
    TIM3->CR1 |= TIM_CR1_UDIS;
  }
  else
  {
    TIM3->CR1 &= (uint8_t)(~TIM_CR1_UDIS);
  }
}

/**
  * @brief  Selects the TIM3 Update Request Interrupt source.
  * @param  TIM3_UpdateSource : Specifies the Update source.
  *   This parameter can be one of the @ref TIM3_UpdateSource_TypeDef enumeration.
  * @retval None
  */
void TIM3_UpdateRequestConfig(TIM3_UpdateSource_TypeDef TIM3_UpdateSource)
{
  /* Check the parameters */
  assert_param(IS_TIM3_UPDATE_SOURCE(TIM3_UpdateSource));

  /* Set or Reset the URS Bit */
  if (TIM3_UpdateSource == TIM3_UpdateSource_Regular)
  {
    TIM3->CR1 |= TIM_CR1_URS ;
  }
  else
  {
    TIM3->CR1 &= (uint8_t)(~TIM_CR1_URS);
  }
}

/**
  * @brief  Enables or Disables the TIM’s Hall sensor interface.
  * @param NewState : The new state of the TIM3 Hall sensor interface.
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void TIM3_SelectHallSensor(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the TI1S Bit */
  if (NewState != DISABLE)
  {
    TIM3->CR2 |= TIM_CR2_TI1S;
  }
  else
  {
    TIM3->CR2 &= (uint8_t)(~TIM_CR2_TI1S);
  }
}

/**
  * @brief  Selects the TIM’s One Pulse Mode.
  * @param  TIM3_OPMode : Specifies the OPM Mode to be used.
  *   This parameter can be one of the @ref TIM3_OPMode_TypeDef enumeration.
  * @retval None
  */
void TIM3_SelectOnePulseMode(TIM3_OPMode_TypeDef TIM3_OPMode)
{
  /* Check the parameters */
  assert_param(IS_TIM3_OPM_MODE(TIM3_OPMode));

  /* Set or Reset the OPM Bit */
  if (TIM3_OPMode == TIM3_OPMode_Single)
  {
    TIM3->CR1 |= TIM_CR1_OPM ;
  }
  else
  {
    TIM3->CR1 &= (uint8_t)(~TIM_CR1_OPM);
  }
}

/**
  * @brief  Selects the TIM3 Trigger Output Mode.
  * @param  TIM3_TRGOSource : Specifies the Trigger Output source.
  *   This parameter can be one of the @ref TIM3_TRGOSource_TypeDef enumeration.
  * @retval None
  */
void TIM3_SelectOutputTrigger(TIM3_TRGOSource_TypeDef TIM3_TRGOSource)
{
  uint8_t tmpcr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM3_TRGO_SOURCE(TIM3_TRGOSource));

  tmpcr2 = TIM3->CR2;

  /* Reset the MMS Bits */
  tmpcr2 &= (uint8_t)(~TIM_CR2_MMS);

  /* Select the TRGO source */
  tmpcr2 |=  (uint8_t)TIM3_TRGOSource;

  TIM3->CR2 = tmpcr2;
}

/**
  * @brief  Selects the TIM3 Slave Mode.
  * @param  TIM3_SlaveMode : Specifies the TIM3 Slave Mode.
  *   This parameter can be one of the @ref TIM3_SlaveMode_TypeDef enumeration.
  * @retval None
  */
void TIM3_SelectSlaveMode(TIM3_SlaveMode_TypeDef TIM3_SlaveMode)
{
  uint8_t tmpsmcr = 0;

  /* Check the parameters */
  assert_param(IS_TIM3_SLAVE_MODE(TIM3_SlaveMode));

  tmpsmcr = TIM3->SMCR;

  /* Reset the SMS Bits */
  tmpsmcr &= (uint8_t)(~TIM_SMCR_SMS);

  /* Select the Slave Mode */
  tmpsmcr |= (uint8_t)TIM3_SlaveMode;

  TIM3->SMCR = tmpsmcr;
}

/**
  * @brief  Sets or Resets the TIM3 Master/Slave Mode.
  * @param NewState : The new state of the synchronization between TIM3 and its slaves (through TRGO).
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void TIM3_SelectMasterSlaveMode(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the MSM Bit */
  if (NewState != DISABLE)
  {
    TIM3->SMCR |= TIM_SMCR_MSM;
  }
  else
  {
    TIM3->SMCR &= (uint8_t)(~TIM_SMCR_MSM);
  }
}

/**
  * @brief  Configures the TIM3 Encoder Interface.
  * @param  TIM3_EncoderMode : Specifies the TIM3 Encoder Mode.
  *   This parameter can be one of the @ref TIM3_EncoderMode_TypeDef enumeration.
  * @param  TIM3_IC1Polarity : Specifies the IC1 Polarity.
  *   This parameter can be one of the @ref TIM3_ICPolarity_TypeDef enumeration.
  * @param  TIM3_IC2Polarity : Specifies the IC2 Polarity.
  *   This parameter can be one of the @ref TIM3_ICPolarity_TypeDef enumeration.
  * @retval None
  */
void TIM3_EncoderInterfaceConfig(TIM3_EncoderMode_TypeDef TIM3_EncoderMode,
                                 TIM3_ICPolarity_TypeDef TIM3_IC1Polarity,
                                 TIM3_ICPolarity_TypeDef TIM3_IC2Polarity)
{
  uint8_t tmpsmcr = 0;
  uint8_t tmpccmr1 = 0;
  uint8_t tmpccmr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM3_ENCODER_MODE(TIM3_EncoderMode));
  assert_param(IS_TIM3_IC_POLARITY(TIM3_IC1Polarity));
  assert_param(IS_TIM3_IC_POLARITY(TIM3_IC2Polarity));

  tmpsmcr = TIM3->SMCR;
  tmpccmr1 = TIM3->CCMR1;
  tmpccmr2 = TIM3->CCMR2;

  /* Set the encoder Mode */
  tmpsmcr &= (uint8_t)(TIM_SMCR_MSM | TIM_SMCR_TS)  ;
  tmpsmcr |= (uint8_t)TIM3_EncoderMode;

  /* Select the Capture Compare 1 and the Capture Compare 2 as input */
  tmpccmr1 &= (uint8_t)(~TIM_CCMR_CCxS);
  tmpccmr2 &= (uint8_t)(~TIM_CCMR_CCxS);
  tmpccmr1 |= TIM_CCMR_TIxDirect_Set;
  tmpccmr2 |= TIM_CCMR_TIxDirect_Set;

  /* Set the TI1 and the TI2 Polarities */
  if (TIM3_IC1Polarity == TIM3_ICPolarity_Falling)
  {
    TIM3->CCER1 |= TIM_CCER1_CC1P ;
  }
  else
  {
    TIM3->CCER1 &= (uint8_t)(~TIM_CCER1_CC1P) ;
  }

  if (TIM3_IC2Polarity == TIM3_ICPolarity_Falling)
  {
    TIM3->CCER1 |= TIM_CCER1_CC2P ;
  }
  else
  {
    TIM3->CCER1 &= (uint8_t)(~TIM_CCER1_CC2P) ;
  }

  TIM3->SMCR = tmpsmcr;
  TIM3->CCMR1 = tmpccmr1;
  TIM3->CCMR2 = tmpccmr2;
}

/**
  * @brief  Configures the TIM3 Prescaler.
  * @param Prescaler : Specifies the Prescaler Register value
  *   This parameter can be one of the @ref TIM3_Prescaler_TypeDef enumeration.
  * @param  TIM3_PSCReloadMode : Specifies the TIM3 Prescaler Reload mode.
  *   This parameter can be one of the @ref TIM3_PSCReloadMode_TypeDef enumeration.
  * @retval None
  */
void TIM3_PrescalerConfig(TIM3_Prescaler_TypeDef Prescaler,
                          TIM3_PSCReloadMode_TypeDef TIM3_PSCReloadMode)
{
  /* Check the parameters */
  assert_param(IS_TIM3_PRESCALER(Prescaler));
  assert_param(IS_TIM3_PRESCALER_RELOAD(TIM3_PSCReloadMode));

  /* Set the Prescaler value */
  TIM3->PSCR = (uint8_t)(Prescaler);

  /* Set or reset the UG Bit */
  if (TIM3_PSCReloadMode == TIM3_PSCReloadMode_Immediate)
  {
    TIM3->EGR |= TIM_EGR_UG ;
  }
  else
  {
    TIM3->EGR &= (uint8_t)(~TIM_EGR_UG) ;
  }
}

/**
  * @brief  Specifies the TIM3 Counter Mode to be used.
  * @param  TIM3_CounterMode : Specifies the Counter Mode to be used
  *   This parameter can be one of the @ref TIM3_CounterMode_TypeDef enumeration.
  * @retval None
  */
void TIM3_CounterModeConfig(TIM3_CounterMode_TypeDef TIM3_CounterMode)
{
  uint8_t tmpcr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM3_COUNTER_MODE(TIM3_CounterMode));

  tmpcr1 = TIM3->CR1;

  /* Reset the CMS and DIR Bits */
  tmpcr1 &= (uint8_t)((uint8_t)(~TIM_CR1_CMS) & (uint8_t)(~TIM_CR1_DIR));

  /* Set the Counter Mode */
  tmpcr1 |= (uint8_t)TIM3_CounterMode;

  TIM3->CR1 = tmpcr1;
}

/**
  * @brief  Forces the TIM3 Channel1 output waveform to active or inactive level.
  * @param  TIM3_ForcedAction : Specifies the forced Action to be set to the output waveform.
  *   This parameter can be one of the @ref TIM3_ForcedAction_TypeDef enumeration.
  * @retval None
  */
void TIM3_ForcedOC1Config(TIM3_ForcedAction_TypeDef TIM3_ForcedAction)
{
  uint8_t tmpccmr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM3_FORCED_ACTION(TIM3_ForcedAction));

  tmpccmr1 = TIM3->CCMR1;

  /* Reset the OCM Bits */
  tmpccmr1 &= (uint8_t)(~TIM_CCMR_OCM);

  /* Configure The Forced output Mode */
  tmpccmr1 |= (uint8_t)TIM3_ForcedAction;

  TIM3->CCMR1 = tmpccmr1;
}

/**
  * @brief  Forces the TIM3 Channel2 output waveform to active or inactive level.
  * @param  TIM3_ForcedAction : Specifies the forced Action to be set to the output waveform.
  *   This parameter can be one of the @ref TIM3_ForcedAction_TypeDef enumeration.
  * @retval None
  */
void TIM3_ForcedOC2Config(TIM3_ForcedAction_TypeDef TIM3_ForcedAction)
{
  uint8_t tmpccmr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM3_FORCED_ACTION(TIM3_ForcedAction));

  tmpccmr2 = TIM3->CCMR2;

  /* Reset the OCM Bits */
  tmpccmr2 &= (uint8_t)(~TIM_CCMR_OCM);

  /* Configure The Forced output Mode */
  tmpccmr2 |= (uint8_t)TIM3_ForcedAction;

  TIM3->CCMR2 = tmpccmr2;
}

/**
  * @brief  Enables or disables TIM3 peripheral Preload register on ARR.
  * @param NewState : The new state of the TIM3 peripheral Preload register.
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void TIM3_ARRPreloadConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the ARPE Bit */
  if (NewState != DISABLE)
  {
    TIM3->CR1 |= TIM_CR1_ARPE;
  }
  else
  {
    TIM3->CR1 &= (uint8_t)(~TIM_CR1_ARPE);
  }
}

/**
  * @brief  Enables or disables the TIM3 peripheral Preload Register on CCR1.
  * @param NewState : new state of the Capture Compare Preload register.
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void TIM3_OC1PreloadConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the OC1PE Bit */
  if (NewState != DISABLE)
  {
    TIM3->CCMR1 |= TIM_CCMR_OCxPE ;
  }
  else
  {
    TIM3->CCMR1 &= (uint8_t)(~TIM_CCMR_OCxPE) ;
  }
}

/**
  * @brief  Enables or disables the TIM3 peripheral Preload Register on CCR2.
  * @param NewState : The new state of the Capture Compare Preload register.
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void TIM3_OC2PreloadConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the OC2PE Bit */
  if (NewState != DISABLE)
  {
    TIM3->CCMR2 |= TIM_CCMR_OCxPE ;
  }
  else
  {
    TIM3->CCMR2 &= (uint8_t)(~TIM_CCMR_OCxPE) ;
  }
}

/**
  * @brief  Configures the TIM3 Capture Compare 1 Fast feature.
  * @param NewState : The new state of the Output Compare Fast Enable bit.
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void TIM3_OC1FastCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the OC1FE Bit */
  if (NewState != DISABLE)
  {
    TIM3->CCMR1 |= TIM_CCMR_OCxFE ;
  }
  else
  {
    TIM3->CCMR1 &= (uint8_t)(~TIM_CCMR_OCxFE) ;
  }
}

/**
  * @brief  Configures the TIM3 Capture Compare 2 Fast feature.
  * @param NewState : The new state of the Output Compare Fast Enable bit.
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */

void TIM3_OC2FastCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the OC2FE Bit */
  if (NewState != DISABLE)
  {
    TIM3->CCMR2 |= TIM_CCMR_OCxFE ;
  }
  else
  {
    TIM3->CCMR2 &= (uint8_t)(~TIM_CCMR_OCxFE) ;
  }
}

/**
  * @brief  Configures the TIM3 event to be generated by software.
  * @param  TIM3_EventSource : Specifies the event source.
  *   This parameter can be one of the @ref TIM3_EventSource_TypeDef enumeration.
  * @retval None
  */
void TIM3_GenerateEvent(TIM3_EventSource_TypeDef TIM3_EventSource)
{
  /* Check the parameters */
  assert_param(IS_TIM3_EVENT_SOURCE((uint8_t)TIM3_EventSource));

  /* Set the event sources */
  TIM3->EGR |= (uint8_t)TIM3_EventSource;
}

/**
  * @brief  Configures the TIM3 Channel 1 polarity.
  * @param  TIM3_OCPolarity : Specifies the OC1 Polarity.
  *   This parameter can be one of the @ref TIM3_OCPolarity_TypeDef enumeration.
  * @retval None
  */
void TIM3_OC1PolarityConfig(TIM3_OCPolarity_TypeDef TIM3_OCPolarity)
{
  /* Check the parameters */
  assert_param(IS_TIM3_OC_POLARITY(TIM3_OCPolarity));

  /* Set or Reset the CC1P Bit */
  if (TIM3_OCPolarity == TIM3_OCPolarity_Low)
  {
    TIM3->CCER1 |= TIM_CCER1_CC1P ;
  }
  else
  {
    TIM3->CCER1 &= (uint8_t)(~TIM_CCER1_CC1P) ;
  }
}

/**
  * @brief  Configures the TIM3 Channel 2 polarity.
  * @param  TIM3_OCPolarity : Specifies the OC2 Polarity.
  *   This parameter can be one of the @ref TIM3_OCPolarity_TypeDef enumeration.
  * @retval None
  */
void TIM3_OC2PolarityConfig(TIM3_OCPolarity_TypeDef TIM3_OCPolarity)
{
  /* Check the parameters */
  assert_param(IS_TIM3_OC_POLARITY(TIM3_OCPolarity));

  /* Set or Reset the CC2P Bit */
  if (TIM3_OCPolarity == TIM3_OCPolarity_Low)
  {
    TIM3->CCER1 |= TIM_CCER1_CC2P ;
  }
  else
  {
    TIM3->CCER1 &= (uint8_t)(~TIM_CCER1_CC2P) ;
  }
}

/**
  * @brief  Enables or disables the TIM3 Capture Compare Channel x.
  * @param  TIM3_Channel : Specifies the TIM3 Channel.
  *   This parameter can be one of @ref TIM3_Channel_TypeDef enumeration.
  * @param NewState : specifies the TIM3 Channel CCxE bit new state.
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void TIM3_CCxCmd(TIM3_Channel_TypeDef TIM3_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM3_CHANNEL(TIM3_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (TIM3_Channel == TIM3_Channel_1)
  {
    /* Set or Reset the CC1E Bit */
    if (NewState != DISABLE)
    {
      TIM3->CCER1 |= TIM_CCER1_CC1E ;
    }
    else
    {
      TIM3->CCER1 &= (uint8_t)(~TIM_CCER1_CC1E) ;
    }

  }
  else /* if (TIM3_Channel == TIM3_Channel_2) */
  {
    /* Set or Reset the CC2E Bit */
    if (NewState != DISABLE)
    {
      TIM3->CCER1 |= TIM_CCER1_CC2E;
    }
    else
    {
      TIM3->CCER1 &= (uint8_t)(~TIM_CCER1_CC2E) ;
    }
  }
}

/**
  * @brief  Selects the TIM3 Ouput Compare Mode. This function disables the
  * selected channel before changing the Ouput Compare Mode. User has to
  * enable this channel using TIM3_CCxCmd and TIM3_CCxNCmd functions.
  * @param  TIM3_Channel : Specifies the TIM3 Channel.
  *   This parameter can be one of the @ref TIM3_Channel_TypeDef enumeration
  * @param  TIM3_OCMode : Specifies the TIM3 Output Compare Mode.
  * This paramter can be one of the @ref TIM3_OCMode_TypeDef enumeration.
  * @retval None
  */
void TIM3_SelectOCxM(TIM3_Channel_TypeDef TIM3_Channel,
                     TIM3_OCMode_TypeDef TIM3_OCMode)
{
  /* Check the parameters */
  assert_param(IS_TIM3_CHANNEL(TIM3_Channel));
  assert_param(IS_TIM3_OCM(TIM3_OCMode));

  if (TIM3_Channel == TIM3_Channel_1)
  {
    /* Disable the Channel 1: Reset the CCE Bit */
    TIM3->CCER1 &= (uint8_t)(~TIM_CCER1_CC1E);

    /* Reset the Output Compare Bits */
    TIM3->CCMR1 &= (uint8_t)(~TIM_CCMR_OCM);

    /* Set the Ouput Compare Mode */
    TIM3->CCMR1 |= (uint8_t)TIM3_OCMode;
  }
  else /* if (TIM3_Channel == TIM3_Channel_2) */
  {
    /* Disable the Channel 2: Reset the CCE Bit */
    TIM3->CCER1 &= (uint8_t)(~TIM_CCER1_CC2E);

    /* Reset the Output Compare Bits */
    TIM3->CCMR2 &= (uint8_t)(~TIM_CCMR_OCM);

    /* Set the Ouput Compare Mode */
    TIM3->CCMR2 |= (uint8_t)TIM3_OCMode;
  }
}

/**
  * @brief  Sets the TIM3 Counter Register value.
  * @param  Counter : Specifies the Counter register new value.
  *   This parameter is between 0x0000 and 0xFFFF.
  * @retval None
  */
void TIM3_SetCounter(uint16_t Counter)
{
  /* Set the Counter Register value */
  TIM3->CNTRH = (uint8_t)(Counter >> 8);
  TIM3->CNTRL = (uint8_t)(Counter);
}

/**
  * @brief  Sets the TIM3 Autoreload Register value.
  * @param  Autoreload : Specifies the Autoreload register new value.
  *   This parameter is between 0x0000 and 0xFFFF.
  * @retval None
  */
void TIM3_SetAutoreload(uint16_t Autoreload)
{
  /* Set the Autoreload Register value */
  TIM3->ARRH = (uint8_t)(Autoreload >> 8);
  TIM3->ARRL = (uint8_t)(Autoreload);
}

/**
  * @brief  Sets the TIM3 Capture Compare1 Register value.
  * @param  Compare : Specifies the Capture Compare1 register new value.
  *   This parameter is between 0x0000 and 0xFFFF.
  * @retval None
  */
void TIM3_SetCompare1(uint16_t Compare)
{
  /* Set the Capture Compare1 Register value */
  TIM3->CCR1H = (uint8_t)(Compare >> 8);
  TIM3->CCR1L = (uint8_t)(Compare);
}

/**
  * @brief  Sets the TIM3 Capture Compare2 Register value.
  * @param  Compare : Specifies the Capture Compare2 register new value.
  *   This parameter is between 0x0000 and 0xFFFF.
  * @retval None
  */
void TIM3_SetCompare2(uint16_t Compare)
{
  /* Set the Capture Compare2 Register value */
  TIM3->CCR2H = (uint8_t)(Compare >> 8);
  TIM3->CCR2L = (uint8_t)(Compare);
}

/**
  * @brief  Sets the TIM3 Input Capture 1 prescaler.
  * @param  TIM3_IC1Prescaler : Specifies the Input Capture prescaler new value
  *   This parameter can be one of the @ref TIM3_ICPSC_TypeDef enumeration.
  * @retval None
  */
void TIM3_SetIC1Prescaler(TIM3_ICPSC_TypeDef TIM3_IC1Prescaler)
{
  uint8_t tmpccmr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM3_IC_PRESCALER(TIM3_IC1Prescaler));

  tmpccmr1 = TIM3->CCMR1;

  /* Reset the IC1PSC Bits */
  tmpccmr1 &= (uint8_t)(~TIM_CCMR_ICxPSC);

  /* Set the IC1PSC value */
  tmpccmr1 |= (uint8_t)TIM3_IC1Prescaler;

  TIM3->CCMR1 = tmpccmr1;
}

/**
  * @brief  Sets the TIM3 Input Capture 2 prescaler.
  * @param  TIM3_IC2Prescaler : Specifies the Input Capture prescaler new value
  *   This parameter can be one of the @ref TIM3_ICPSC_TypeDef enumeration.
  * @retval None
  */
void TIM3_SetIC2Prescaler(TIM3_ICPSC_TypeDef TIM3_IC2Prescaler)
{
  uint8_t tmpccmr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM3_IC_PRESCALER(TIM3_IC2Prescaler));

  tmpccmr2 = TIM3->CCMR2;

  /* Reset the IC2PSC Bits */
  tmpccmr2 &= (uint8_t)(~TIM_CCMR_ICxPSC);

  /* Set the IC2PSC value */
  tmpccmr2 |= (uint8_t)TIM3_IC2Prescaler;

  TIM3->CCMR2 = tmpccmr2;
}

/**
  * @brief  Gets the TIM3 Input Capture 1 value.
  * @param  None
  * @retval Capture Compare 1 Register value.
  */
uint16_t TIM3_GetCapture1(void)
{
  uint16_t tmpccr1 = 0;
  uint8_t tmpccr1l, tmpccr1h;

  tmpccr1h = TIM3->CCR1H;
  tmpccr1l = TIM3->CCR1L;

  tmpccr1 = (uint16_t)(tmpccr1l);
  tmpccr1 |= (uint16_t)((uint16_t)tmpccr1h << 8);
  /* Get the Capture 1 Register value */
  return ((uint16_t)tmpccr1);
}

/**
  * @brief  Gets the TIM3 Input Capture 2 value.
  * @param  None
  * @retval Capture Compare 2 Register value.
  */
uint16_t TIM3_GetCapture2(void)
{
  uint16_t tmpccr2 = 0;
  uint8_t tmpccr2l, tmpccr2h;

  tmpccr2h = TIM3->CCR2H;
  tmpccr2l = TIM3->CCR2L;

  tmpccr2 = (uint16_t)(tmpccr2l);
  tmpccr2 |= (uint16_t)((uint16_t)tmpccr2h << 8);
  /* Get the Capture 2 Register value */
  return ((uint16_t)tmpccr2);
}

/**
  * @brief  Gets the TIM3 Counter value.
  * @param  None
  * @retval Counter Register value.
  */
uint16_t TIM3_GetCounter(void)
{
  uint16_t tmpcnt = 0;
  uint8_t tmpcntrl, tmpcntrh;

  tmpcntrh = TIM3->CNTRH;
  tmpcntrl = TIM3->CNTRL;

  tmpcnt = (uint16_t)(tmpcntrl);
  tmpcnt |= (uint16_t)((uint16_t)tmpcntrh << 8);
  /* Get the Counter Register value */
  return ((uint16_t)tmpcnt);
}

/**
  * @brief  Gets the TIM3 Prescaler value.
  * @param  None
  * @retval TIM3_Prescaler_TypeDef : Prescaler Register value.
  */
TIM3_Prescaler_TypeDef TIM3_GetPrescaler(void)
{
  /* Get the Prescaler Register value */
  return ((TIM3_Prescaler_TypeDef)TIM3->PSCR);
}

/**
  * @brief  Selects the TIM3 peripheral Capture Compare DMA source.
  * @param  NewState: new state of the Capture Compare DMA source.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM3_SelectCCDMA(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the CCDS Bit */
    TIM3->CR2 |= TIM_CR2_CCDS;
  }
  else
  {
    /* Reset the CCDS Bit */
    TIM3->CR2 &= (uint8_t)(~TIM_CR2_CCDS);
  }
}

/**
  * @brief  Checks whether the specified TIM3 flag is set or not.
  * @param  TIM3_FLAG : Specifies the flag to check.
  *   This parameter can be one of the @ref TIM3_FLAG_TypeDef enumeration.
  * @retval FlagStatus : The new state of TIM3_FLAG.
  *   This parameter can be any of the @ref FlagStatus enumeration.
  */
FlagStatus TIM3_GetFlagStatus(TIM3_FLAG_TypeDef TIM3_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint8_t tim3_flag_l = 0, tim3_flag_h = 0;

  /* Check the parameters */
  assert_param(IS_TIM3_GET_FLAG(TIM3_FLAG));

  tim3_flag_l = (uint8_t)(TIM3->SR1 & (uint8_t)(TIM3_FLAG));
  tim3_flag_h = (uint8_t)(TIM3->SR2 & (uint8_t)((uint16_t)TIM3_FLAG >> 8));

  if ((uint8_t)(tim3_flag_l | tim3_flag_h) != 0)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return ((FlagStatus)bitstatus);
}

/**
  * @brief  Clears the TIM’s pending flags.
  * @param  TIM3_FLAG : Specifies the flag to clear.
  *   This parameter can be one of the @ref TIM3_FLAG_TypeDef enumeration.
  * @retval None
  */
void TIM3_ClearFlag(TIM3_FLAG_TypeDef TIM3_FLAG)
{
  /* Check the parameters */
  assert_param(IS_TIM3_CLEAR_FLAG((uint16_t)TIM3_FLAG));
  /* Clear the flags (rc_w0) clear this bit by writing 0. Writing ‘1’ has no effect*/
  TIM3->SR1 = (uint8_t)(~(uint8_t)(TIM3_FLAG));
  TIM3->SR2 = (uint8_t)(~(uint8_t)((uint16_t)TIM3_FLAG >> 8));
}

/**
  * @brief  Checks whether the TIM3 interrupt has occurred or not.
  * @param  TIM3_IT : Specifies the TIM3 interrupt source to check.
  *   This parameter can be one of the @ref TIM3_IT_TypeDef enumeration.
  * @retval ITStatus : The new state of the TIM3_IT.
  *   This parameter can be any of the @ref ITStatus enumeration.
  */

ITStatus TIM3_GetITStatus(TIM3_IT_TypeDef TIM3_IT)
{
  ITStatus bitstatus = RESET;

  uint8_t TIM3_itStatus = 0x0, TIM3_itEnable = 0x0;

  /* Check the parameters */
  assert_param(IS_TIM3_GET_IT(TIM3_IT));

  TIM3_itStatus = (uint8_t)(TIM3->SR1 & (uint8_t)TIM3_IT);

  TIM3_itEnable = (uint8_t)(TIM3->IER & (uint8_t)TIM3_IT);

  if ((TIM3_itStatus != (uint8_t)RESET) && (TIM3_itEnable != (uint8_t)RESET))
  {
    bitstatus = (ITStatus)SET;
  }
  else
  {
    bitstatus = (ITStatus)RESET;
  }
  return ((ITStatus)bitstatus);
}

/**
  * @brief  Clears the TIM's interrupt pending bits.
  * @param  TIM3_IT : Specifies the pending bit to clear.
  *   This parameter can be one of the @ref TIM3_IT_TypeDef enumeration.
  * @retval None
  */
void TIM3_ClearITPendingBit(TIM3_IT_TypeDef TIM3_IT)
{
  /* Check the parameters */
  assert_param(IS_TIM3_IT(TIM3_IT));

  /* Clear the IT pending Bit */
  TIM3->SR1 = (uint8_t)(~(uint8_t)TIM3_IT);
}

/**
  * @brief  Configure the TI1 as Input.
  * @param  TIM3_ICPolarity : The Input Polarity.
  *   This parameter can be one of the @ref TIM3_ICPolarity_TypeDef enumeration.
  * @param  TIM3_ICSelection : Specifies the input to be used.
  *   This parameter can be one of the @ref TIM3_ICSelection_TypeDef enumeration.
  * @param  TIM3_ICFilter : Specifies the Input Capture Filter.
  *   This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI1_Config(TIM3_ICPolarity_TypeDef TIM3_ICPolarity,
                       TIM3_ICSelection_TypeDef TIM3_ICSelection,
                       uint8_t TIM3_ICFilter)
{
  uint8_t tmpccmr1 = 0;
  uint8_t tmpicpolarity = TIM3_ICPolarity;
  tmpccmr1 = TIM3->CCMR1;

  /* Check the parameters */
  assert_param(IS_TIM3_IC_POLARITY(TIM3_ICPolarity));
  assert_param(IS_TIM3_IC_SELECTION(TIM3_ICSelection));
  assert_param(IS_TIM3_IC_FILTER(TIM3_ICFilter));

  /* Disable the Channel 1: Reset the CCE Bit */
  TIM3->CCER1 &=  (uint8_t)(~TIM_CCER1_CC1E);

  /* Select the Input and set the filter */
  tmpccmr1 &= (uint8_t)(~TIM_CCMR_CCxS) & (uint8_t)(~TIM_CCMR_ICxF);
  tmpccmr1 |= (uint8_t)(((uint8_t)(TIM3_ICSelection)) | ((uint8_t)(TIM3_ICFilter << 4)));

  TIM3->CCMR1 = tmpccmr1;

  /* Select the Polarity */
  if (tmpicpolarity == (uint8_t)(TIM3_ICPolarity_Falling))
  {
    TIM3->CCER1 |= TIM_CCER1_CC1P;
  }
  else
  {
    TIM3->CCER1 &= (uint8_t)(~TIM_CCER1_CC1P);
  }

  /* Set the CCE Bit */
  TIM3->CCER1 |=  TIM_CCER1_CC1E;
}

/**
  * @brief  Configure the TI2 as Input.
  * @param  TIM3_ICPolarity : The Input Polarity.
  *   This parameter can be one of the @ref TIM3_ICPolarity_TypeDef enumeration.
  * @param  TIM3_ICSelection : Specifies the input to be used.
  *   This parameter can be one of the @ref TIM3_ICSelection_TypeDef enumeration.
  * @param  TIM3_ICFilter : Specifies the Input Capture Filter.
  *   This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI2_Config(TIM3_ICPolarity_TypeDef TIM3_ICPolarity,
                       TIM3_ICSelection_TypeDef TIM3_ICSelection,
                       uint8_t TIM3_ICFilter)
{
  uint8_t tmpccmr2 = 0;
  uint8_t tmpicpolarity = TIM3_ICPolarity;

  /* Check the parameters */
  assert_param(IS_TIM3_IC_POLARITY(TIM3_ICPolarity));
  assert_param(IS_TIM3_IC_SELECTION(TIM3_ICSelection));
  assert_param(IS_TIM3_IC_FILTER(TIM3_ICFilter));

  tmpccmr2 = TIM3->CCMR2;

  /* Disable the Channel 2: Reset the CCE Bit */
  TIM3->CCER1 &=  (uint8_t)(~TIM_CCER1_CC2E);

  /* Select the Input and set the filter */
  tmpccmr2 &= (uint8_t)(~TIM_CCMR_CCxS) & (uint8_t)(~TIM_CCMR_ICxF);
  tmpccmr2 |= (uint8_t)(((uint8_t)(TIM3_ICSelection)) | ((uint8_t)(TIM3_ICFilter << 4)));

  TIM3->CCMR2 = tmpccmr2;

  /* Select the Polarity */
  if (tmpicpolarity == TIM3_ICPolarity_Falling)
  {
    TIM3->CCER1 |= TIM_CCER1_CC2P ;
  }
  else
  {
    TIM3->CCER1 &= (uint8_t)(~TIM_CCER1_CC2P) ;
  }

  /* Set the CCE Bit */
  TIM3->CCER1 |=  TIM_CCER1_CC2E;
}


/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
