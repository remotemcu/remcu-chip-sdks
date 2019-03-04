/**
  ******************************************************************************
  * @file    stm8l15x_TIM5.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    09/24/2010
  * @brief   This file provides all the TIM5 firmware functions.
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
#include "stm8l15x_TIM5.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void TI1_Config(TIM5_ICPolarity_TypeDef TIM5_ICPolarity,
                       TIM5_ICSelection_TypeDef TIM5_ICSelection,
                       uint8_t TIM5_ICFilter);
static void TI2_Config(TIM5_ICPolarity_TypeDef TIM5_ICPolarity,
                       TIM5_ICSelection_TypeDef TIM5_ICSelection,
                       uint8_t TIM5_ICFilter);


/**
  * @addtogroup TIM5_Public_Functions
  * @{
  */

/**
  * @brief  Deinitializes the TIM5 peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void TIM5_DeInit(void)
{
  TIM5->CR1 = TIM_CR1_RESET_VALUE;
  TIM5->CR2 = TIM_CR2_RESET_VALUE;
  TIM5->SMCR = TIM_SMCR_RESET_VALUE;
  TIM5->ETR = TIM_ETR_RESET_VALUE;
  TIM5->IER = TIM_IER_RESET_VALUE;
  TIM5->SR2 = TIM_SR2_RESET_VALUE;

  /* Disable channels */
  TIM5->CCER1 = TIM_CCER1_RESET_VALUE;
  /* Configure channels as inputs: it is necessary if lock level is equal to 2 or 3 */
  TIM5->CCMR1 = 0x01;/*TIM5_ICxSource_TIxFPx */
  TIM5->CCMR2 = 0x01;/*TIM5_ICxSource_TIxFPx */

  /* Then reset channel registers: it also works if lock level is equal to 2 or 3 */
  TIM5->CCER1 = TIM_CCER1_RESET_VALUE;
  TIM5->CCMR1 = TIM_CCMR1_RESET_VALUE;
  TIM5->CCMR2 = TIM_CCMR2_RESET_VALUE;

  TIM5->CNTRH = TIM_CNTRH_RESET_VALUE;
  TIM5->CNTRL = TIM_CNTRL_RESET_VALUE;

  TIM5->PSCR = TIM_PSCR_RESET_VALUE;

  TIM5->ARRH = TIM_ARRH_RESET_VALUE;
  TIM5->ARRL = TIM_ARRL_RESET_VALUE;

  TIM5->CCR1H = TIM_CCR1H_RESET_VALUE;
  TIM5->CCR1L = TIM_CCR1L_RESET_VALUE;
  TIM5->CCR2H = TIM_CCR2H_RESET_VALUE;
  TIM5->CCR2L = TIM_CCR2L_RESET_VALUE;


  TIM5->OISR = TIM_OISR_RESET_VALUE;
  TIM5->EGR = 0x01;/* TIM_EGR_UG */
  TIM5->BKR = TIM_BKR_RESET_VALUE;
  TIM5->SR1 = TIM_SR1_RESET_VALUE;
}

/**
  * @brief  Initializes the TIM5 Time Base Unit according to the specified  parameters.
  * @param  TIM5_Prescaler : This parameter can be any member of the @Ref TIM5_Prescaler_TypeDef enumeration.
  * @param  TIM5_CounterMode : This parameter can be any member of the @Ref TIM5_CounterMode_TypeDef enumeration.
  * @param  TIM5_Period : This parameter must be a value between 0x0000 and 0xFFFF.
  * @retval None
  */

void TIM5_TimeBaseInit(TIM5_Prescaler_TypeDef TIM5_Prescaler,
                       TIM5_CounterMode_TypeDef TIM5_CounterMode,
                       uint16_t TIM5_Period)
{

  assert_param(IS_TIM5_PRESCALER(TIM5_Prescaler));
  assert_param(IS_TIM5_COUNTER_MODE(TIM5_CounterMode));



  /* Set the Autoreload value */
  TIM5->ARRH = (uint8_t)(TIM5_Period >> 8) ;
  TIM5->ARRL = (uint8_t)(TIM5_Period);

  /* Set the Prescaler value */
  TIM5->PSCR = (uint8_t)(TIM5_Prescaler);

  /* Select the Counter Mode */
  TIM5->CR1 &= (uint8_t)((uint8_t)(~TIM_CR1_CMS)) & ((uint8_t)(~TIM_CR1_DIR));
  TIM5->CR1 |= (uint8_t)(TIM5_CounterMode);

  /* Generate an update event to reload the Prescaler value immediately */
  TIM5->EGR = TIM5_EventSource_Update;
}

/**
  * @brief  Initializes the TIM5 Channel1 according to the specified parameters.
  * @param  TIM5_OCMode : This parameter can be any member of the @Ref TIM5_OCMode_TypeDef enumeration.
  * @param  TIM5_OutputState : This parameter can be any member of the @Ref TIM5_OutputState_TypeDef enumeration.
  * @param  TIM5_Pulse : This parameter must be a value between 0x0000 and 0xFFFF.
  * @param  TIM5_OCPolarity : This parameter can be any member of the @Ref TIM5_OCPolarity_TypeDef enumeration.
  * @param  TIM5_OCIdleState : This parameter can be any member of the @Ref TIM5_OCIdleState_TypeDef  enumeration.
  * @retval None
  */
void TIM5_OC1Init(TIM5_OCMode_TypeDef TIM5_OCMode,
                  TIM5_OutputState_TypeDef TIM5_OutputState,
                  uint16_t TIM5_Pulse,
                  TIM5_OCPolarity_TypeDef TIM5_OCPolarity,
                  TIM5_OCIdleState_TypeDef TIM5_OCIdleState)
{
  uint8_t tmpccmr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM5_OC_MODE(TIM5_OCMode));
  assert_param(IS_TIM5_OUTPUT_STATE(TIM5_OutputState));
  assert_param(IS_TIM5_OC_POLARITY(TIM5_OCPolarity));
  assert_param(IS_TIM5_OCIDLE_STATE(TIM5_OCIdleState));

  tmpccmr1 = TIM5->CCMR1;

  /* Disable the Channel 1: Reset the CCE Bit */
  TIM5->CCER1 &= (uint8_t)(~TIM_CCER1_CC1E);
  /* Reset the Output Compare Bits */
  tmpccmr1 &= (uint8_t)(~TIM_CCMR_OCM);

  /* Set the Ouput Compare Mode */
  tmpccmr1 |= (uint8_t)TIM5_OCMode;

  TIM5->CCMR1 = tmpccmr1;

  /* Set the Output State */
  if (TIM5_OutputState == TIM5_OutputState_Enable)
  {
    TIM5->CCER1 |= TIM_CCER1_CC1E;
  }
  else
  {
    TIM5->CCER1 &= (uint8_t)(~TIM_CCER1_CC1E);
  }

  /* Set the Output Polarity */
  if (TIM5_OCPolarity == TIM5_OCPolarity_Low)
  {
    TIM5->CCER1 |= TIM_CCER1_CC1P;
  }
  else
  {
    TIM5->CCER1 &= (uint8_t)(~TIM_CCER1_CC1P);
  }

  /* Set the Output Idle state */
  if (TIM5_OCIdleState == TIM5_OCIdleState_Set)
  {
    TIM5->OISR |= TIM_OISR_OIS1;
  }
  else
  {
    TIM5->OISR &= (uint8_t)(~TIM_OISR_OIS1);
  }

  /* Set the Pulse value */
  TIM5->CCR1H = (uint8_t)(TIM5_Pulse >> 8);
  TIM5->CCR1L = (uint8_t)(TIM5_Pulse);
}

/**
  * @brief  Initializes the TIM5 Channel2 according to the specified parameters.
  * @param  TIM5_OCMode : This parameter can be any member of the @Ref TIM5_OCMode_TypeDef enumeration.
  * @param  TIM5_OutputState : This parameter can be any member of the @Ref TIM5_OutputState_TypeDef enumeration.
  * @param  TIM5_Pulse : This parameter must be a value between 0x0000 and 0xFFFF.
  * @param  TIM5_OCPolarity : This parameter can be any member of the @Ref TIM5_OCPolarity_TypeDef enumeration.
  * @param  TIM5_OCIdleState : This parameter can be any member of the @Ref TIM5_OCIdleState_TypeDef  enumeration.
  * @retval None
  */
void TIM5_OC2Init(TIM5_OCMode_TypeDef TIM5_OCMode,
                  TIM5_OutputState_TypeDef TIM5_OutputState,
                  uint16_t TIM5_Pulse,
                  TIM5_OCPolarity_TypeDef TIM5_OCPolarity,
                  TIM5_OCIdleState_TypeDef TIM5_OCIdleState)
{
  uint8_t tmpccmr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM5_OC_MODE(TIM5_OCMode));
  assert_param(IS_TIM5_OUTPUT_STATE(TIM5_OutputState));
  assert_param(IS_TIM5_OC_POLARITY(TIM5_OCPolarity));
  assert_param(IS_TIM5_OCIDLE_STATE(TIM5_OCIdleState));

  tmpccmr2 = TIM5->CCMR2;

  /* Disable the Channel 2: Reset the CCE Bit */
  TIM5->CCER1 &= (uint8_t)(~TIM_CCER1_CC2E);

  /* Reset the Output Compare Bits */
  tmpccmr2 &= (uint8_t)(~TIM_CCMR_OCM);

  /* Set the Ouput Compare Mode */
  tmpccmr2 |= (uint8_t)TIM5_OCMode;

  TIM5->CCMR2 = tmpccmr2;

  /* Set the Output State */
  if (TIM5_OutputState == TIM5_OutputState_Enable)
  {
    TIM5->CCER1 |= TIM_CCER1_CC2E;
  }
  else
  {
    TIM5->CCER1 &= (uint8_t)(~TIM_CCER1_CC2E);
  }

  /* Set the Output Polarity */
  if (TIM5_OCPolarity == TIM5_OCPolarity_Low)
  {
    TIM5->CCER1 |= TIM_CCER1_CC2P;
  }
  else
  {
    TIM5->CCER1 &= (uint8_t)(~TIM_CCER1_CC2P);
  }


  /* Set the Output Idle state */
  if (TIM5_OCIdleState == TIM5_OCIdleState_Set)
  {
    TIM5->OISR |= TIM_OISR_OIS2;
  }
  else
  {
    TIM5->OISR &= (uint8_t)(~TIM_OISR_OIS2);
  }

  /* Set the Pulse value */
  TIM5->CCR2H = (uint8_t)(TIM5_Pulse >> 8);
  TIM5->CCR2L = (uint8_t)(TIM5_Pulse);
}

/**
  * @brief  Configures the Break feature, dead time, Lock level, the OSSI,
  * and the AOE(automatic output enable).
  * @param  TIM5_OSSIState : Off-State Selection for Idle mode states.
  *   This parameter can be any member of the @Ref TIM5_OSSIState_TypeDef enumeration.
  * @param  TIM5_LockLevel : Lock level.
  *   This parameter can be any member of the @Ref TIM5_LockLevel_TypeDef enumeration.
  * @param  TIM5_BreakState : Break Input enable/disable .
  *   This parameter can be any member of the @Ref TIM5_BreakState_TypeDef enumeration.
  * @param  TIM5_BreakPolarity : Break Polarity.
  *   This parameter can be any member of the @Ref TIM5_BreakPolarity_TypeDef enumeration.
  * @param  TIM5_AutomaticOutput : TIM5 AOE Bit Set/Reset .
  *   This parameter can be anymember  of the @Ref TIM5_AutomaticOutput_TypeDef enumeration.
  * @retval None
  */
void TIM5_BKRConfig(TIM5_OSSIState_TypeDef TIM5_OSSIState,
                    TIM5_LockLevel_TypeDef TIM5_LockLevel,
                    TIM5_BreakState_TypeDef TIM5_BreakState,
                    TIM5_BreakPolarity_TypeDef TIM5_BreakPolarity,
                    TIM5_AutomaticOutput_TypeDef TIM5_AutomaticOutput)

{
  /* Check the parameters */
  assert_param(IS_TIM5_OSSI_STATE(TIM5_OSSIState));
  assert_param(IS_TIM5_LOCK_LEVEL(TIM5_LockLevel));
  assert_param(IS_TIM5_BREAK_STATE(TIM5_BreakState));
  assert_param(IS_TIM5_BREAK_POLARITY(TIM5_BreakPolarity));
  assert_param(IS_TIM5_AUTOMATIC_OUTPUT_STATE(TIM5_AutomaticOutput));



  /* Set the Lock level, the Break enable Bit and the Ploarity, the OSSI State,
  the dead time value and the Automatic Output Enable Bit */
  TIM5->BKR = (uint8_t)((uint8_t)((uint8_t)((uint8_t)((uint8_t)TIM5_OSSIState | (uint8_t)TIM5_LockLevel) | \
                                  (uint8_t)((uint8_t)TIM5_BreakState | (uint8_t)TIM5_BreakPolarity)) | \
                                  TIM5_AutomaticOutput));
}

/**
  * @brief  Initializes the TIM5 peripheral according to the specified parameters.
  * @param  TIM5_Channel : This parameter can be any member of the @Ref TIM5_Channel_TypeDef enumeration.
  * @param  TIM5_ICPolarity : This parameter can be any member of the @Ref TIM5_ICPolarity_TypeDef enumeration.
  * @param  TIM5_ICSelection : This parameter can be any member of the @Ref TIM5_ICSelection_TypeDef enumeration.
  * @param  TIM5_ICPrescaler : This parameter can be any member of the @Ref TIM5_ICPSC_TypeDef enumeration.
  * @param  TIM5_ICFilter : This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
void TIM5_ICInit(TIM5_Channel_TypeDef TIM5_Channel,
                 TIM5_ICPolarity_TypeDef TIM5_ICPolarity,
                 TIM5_ICSelection_TypeDef TIM5_ICSelection,
                 TIM5_ICPSC_TypeDef TIM5_ICPrescaler,
                 uint8_t TIM5_ICFilter)
{
  /* Check the parameters */
  assert_param(IS_TIM5_CHANNEL(TIM5_Channel));

  if (TIM5_Channel == TIM5_Channel_1)
  {
    /* TI1 Configuration */
    TI1_Config(TIM5_ICPolarity, TIM5_ICSelection, TIM5_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM5_SetIC1Prescaler(TIM5_ICPrescaler);
  }
  else /* if (TIM5_Channel == TIM5_Channel_2) */
  {
    /* TI2 Configuration */
    TI2_Config(TIM5_ICPolarity, TIM5_ICSelection, TIM5_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM5_SetIC2Prescaler(TIM5_ICPrescaler);
  }
}

/**
  * @brief  Configures the TIM5 peripheral in PWM Input Mode according to the
  * specified parameters.
  * @param  TIM5_Channel : This parameter can be any member of the @Ref TIM5_Channel_TypeDef enumeration.
  * @param  TIM5_ICPolarity : This parameter can be any member of the @Ref TIM5_ICPolarity_TypeDef enumeration.
  * @param  TIM5_ICSelection : This parameter can be any member of the @Ref TIM5_ICSelection_TypeDef enumeration.
  * @param  TIM5_ICPrescaler : This parameter can be any member of the @Ref TIM5_ICPSC_TypeDef enumeration.
  * @param  TIM5_ICFilter : This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
void TIM5_PWMIConfig(TIM5_Channel_TypeDef TIM5_Channel,
                     TIM5_ICPolarity_TypeDef TIM5_ICPolarity,
                     TIM5_ICSelection_TypeDef TIM5_ICSelection,
                     TIM5_ICPSC_TypeDef TIM5_ICPrescaler,
                     uint8_t TIM5_ICFilter)
{
  uint8_t icpolarity = TIM5_ICPolarity_Rising;
  uint8_t icselection = TIM5_ICSelection_DirectTI;

  /* Check the parameters */
  assert_param(IS_TIM5_CHANNEL(TIM5_Channel));

  /* Select the Opposite Input Polarity */
  if (TIM5_ICPolarity == TIM5_ICPolarity_Rising)
  {
    icpolarity = TIM5_ICPolarity_Falling;
  }
  else
  {
    icpolarity = TIM5_ICPolarity_Rising;
  }

  /* Select the Opposite Input */
  if (TIM5_ICSelection == TIM5_ICSelection_DirectTI)
  {
    icselection = TIM5_ICSelection_IndirectTI;
  }
  else
  {
    icselection = TIM5_ICSelection_DirectTI;
  }

  if (TIM5_Channel == TIM5_Channel_1)
  {
    /* TI1 Configuration */
    TI1_Config(TIM5_ICPolarity, TIM5_ICSelection,
               TIM5_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM5_SetIC1Prescaler(TIM5_ICPrescaler);

    /* TI2 Configuration */
    TI2_Config((TIM5_ICPolarity_TypeDef)icpolarity, (TIM5_ICSelection_TypeDef)icselection, TIM5_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM5_SetIC2Prescaler(TIM5_ICPrescaler);
  }
  else
  {
    /* TI2 Configuration */
    TI2_Config(TIM5_ICPolarity, TIM5_ICSelection,
               TIM5_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM5_SetIC2Prescaler(TIM5_ICPrescaler);

    /* TI1 Configuration */
    TI1_Config((TIM5_ICPolarity_TypeDef)icpolarity, (TIM5_ICSelection_TypeDef)icselection, TIM5_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM5_SetIC1Prescaler(TIM5_ICPrescaler);
  }
}

/**
  * @brief  Enables or disables the TIM5 peripheral.
  * @param  NewState : The new state of the TIM5 peripheral.
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void TIM5_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* set or Reset the CEN Bit */
  if (NewState != DISABLE)
  {
    TIM5->CR1 |= TIM_CR1_CEN;
  }
  else
  {
    TIM5->CR1 &= (uint8_t)(~TIM_CR1_CEN);
  }
}

/**
  * @brief  Enables or disables the TIM5 peripheral Main Outputs.
  * @param  NewState : The new state of the TIM5 peripheral.
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void TIM5_CtrlPWMOutputs(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the MOE Bit */

  if (NewState != DISABLE)
  {
    TIM5->BKR |= TIM_BKR_MOE ;
  }
  else
  {
    TIM5->BKR &= (uint8_t)(~TIM_BKR_MOE) ;
  }
}

/**
  * @brief  Enables or disables the specified TIM5 interrupts.
  * @param  TIM5_IT : Specifies the TIM5 interrupts sources to be enabled or disabled.
  *   This parameter can be any combination of the @ref TIM5_IT_TypeDef enumeration.
  * @param  NewState : The new state of the TIM5 peripheral.
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void TIM5_ITConfig(TIM5_IT_TypeDef TIM5_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM5_IT(TIM5_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Interrupt sources */
    TIM5->IER |= (uint8_t)TIM5_IT;
  }
  else
  {
    /* Disable the Interrupt sources */
    TIM5->IER &= (uint8_t)(~(uint8_t)TIM5_IT);
  }
}

/**
  * @brief  Enables or disables the TIM5 DMA Requests.
  * @param  TIM5_DMASources: specifies the DMA Request sources.
  *   This parameter can be any combination of  @ref TIM5_DMASource_TypeDef enumeration.
  * @param  NewState: new state of the DMA Request sources.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM5_DMACmd( TIM5_DMASource_TypeDef TIM5_DMASource, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_TIM5_DMA_SOURCE(TIM5_DMASource));

  if (NewState != DISABLE)
  {
    /* Enable the DMA sources */
    TIM5->DER |= TIM5_DMASource;
  }
  else
  {
    /* Disable the DMA sources */
    TIM5->DER &= (uint8_t)(~TIM5_DMASource);
  }
}

/**
  * @brief  Enables the TIM5 internal Clock.
  * @par Parameters:
  * None
  * @retval None
  */
void TIM5_InternalClockConfig(void)
{
  /* Disable slave mode to clock the prescaler directly with the internal clock */
  TIM5->SMCR &=  (uint8_t)(~TIM_SMCR_SMS);
}

/**
  * @brief  Configures the TIM5 External clock Mode1.
  * @param  TIM5_ExtTRGPrescaler : Specifies the external Trigger Prescaler.
  *   This parameter can be one of @ref TIM5_ExtTRGPSC_TypeDef enumeration.
  * @param  TIM5_ExtTRGPolarity : Specifies the external Trigger Polarity.
  *   This parameter can be one of @ref TIM5_ExtTRGPolarity_TypeDef enumeration.
  * @param  ExtTRGFilter : Specifies the External Trigger Filter.
  *   This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TIM5_ETRClockMode1Config(TIM5_ExtTRGPSC_TypeDef TIM5_ExtTRGPrescaler,
                              TIM5_ExtTRGPolarity_TypeDef TIM5_ExtTRGPolarity,
                              uint8_t ExtTRGFilter)
{
  /* Configure the ETR Clock source */
  TIM5_ETRConfig(TIM5_ExtTRGPrescaler, TIM5_ExtTRGPolarity, ExtTRGFilter);

  /* Select the External clock mode1 */
  TIM5->SMCR &= (uint8_t)(~TIM_SMCR_SMS);
  TIM5->SMCR |= (uint8_t)(TIM5_SlaveMode_External1);

  /* Select the Trigger selection : ETRF */
  TIM5->SMCR &= (uint8_t)(~TIM_SMCR_TS);
  TIM5->SMCR |= (uint8_t)((TIM5_TRGSelection_TypeDef)TIM5_TRGSelection_ETRF);
}

/**
  * @brief  Configures the TIM5 External clock Mode2.
  * @param  TIM5_ExtTRGPrescaler : Specifies the external Trigger Prescaler.
  *   This parameter can be one of the @ref TIM5_ExtTRGPSC_TypeDef enumeration.
  * @param  TIM5_ExtTRGPolarity : Specifies the external Trigger Polarity.
  *   This parameter can be one of the @ref TIM5_ExtTRGPolarity_TypeDef enumeration.
  * @param  ExtTRGFilter : Specifies the External Trigger Filter.
  *   This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TIM5_ETRClockMode2Config(TIM5_ExtTRGPSC_TypeDef TIM5_ExtTRGPrescaler,
                              TIM5_ExtTRGPolarity_TypeDef TIM5_ExtTRGPolarity,
                              uint8_t ExtTRGFilter)
{
  /* Configure the ETR Clock source */
  TIM5_ETRConfig(TIM5_ExtTRGPrescaler, TIM5_ExtTRGPolarity, ExtTRGFilter);

  /* Enable the External clock mode2 */
  TIM5->ETR |= TIM_ETR_ECE ;
}

/**
  * @brief  Configures the TIM5 External Trigger.
  * @param  TIM5_ExtTRGPrescaler : Specifies the external Trigger Prescaler.
  *   This parameter can be one of the @ref TIM5_ExtTRGPSC_TypeDef enumeration.
  * @param  TIM5_ExtTRGPolarity : Specifies the external Trigger Polarity.
  *   This parameter can be one of the @ref TIM5_ExtTRGPolarity_TypeDef enumeration.
  * @param  ExtTRGFilter : Specifies the External Trigger Filter.
  *   This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TIM5_ETRConfig(TIM5_ExtTRGPSC_TypeDef TIM5_ExtTRGPrescaler,
                    TIM5_ExtTRGPolarity_TypeDef TIM5_ExtTRGPolarity,
                    uint8_t ExtTRGFilter)
{
  /* Check the parameters */
  assert_param(IS_TIM5_EXT_PRESCALER(TIM5_ExtTRGPrescaler));
  assert_param(IS_TIM5_EXT_POLARITY(TIM5_ExtTRGPolarity));
  assert_param(IS_TIM5_EXT_FILTER(ExtTRGFilter));

  /* Set the Prescaler, the Filter value and the Polarity */
  TIM5->ETR |= (uint8_t)((uint8_t)((uint8_t)TIM5_ExtTRGPrescaler | (uint8_t)TIM5_ExtTRGPolarity)
                         | (uint8_t)ExtTRGFilter);
}

/**
  * @brief  Configures the TIM5 Trigger as External Clock.
  * @param  TIM5_TIxExternalCLKSource : Specifies Trigger source.
  *   This parameter can be one of the @ref TIM5_TIxExternalCLK1Source_TypeDef enumeration.
  * @param  TIM5_ICPolarity : Specifies the TIx Polarity.
  *   This parameter can be @ref TIM5_ICPolarity_TypeDef enumeration.
  * @param  ICFilter : Specifies the filter value.
  *   This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TIM5_TIxExternalClockConfig(TIM5_TIxExternalCLK1Source_TypeDef TIM5_TIxExternalCLKSource,
                                 TIM5_ICPolarity_TypeDef TIM5_ICPolarity,
                                 uint8_t ICFilter)
{
  /* Check the parameters */
  assert_param(IS_TIM5_TIXCLK_SOURCE(TIM5_TIxExternalCLKSource));
  assert_param(IS_TIM5_IC_POLARITY(TIM5_ICPolarity));
  assert_param(IS_TIM5_IC_FILTER(ICFilter));

  /* Configure the TIM5 Input Clock Source */
  if (TIM5_TIxExternalCLKSource == TIM5_TIxExternalCLK1Source_TI2)
  {
    TI2_Config(TIM5_ICPolarity, TIM5_ICSelection_DirectTI, ICFilter);
  }
  else
  {
    TI1_Config(TIM5_ICPolarity, TIM5_ICSelection_DirectTI, ICFilter);
  }

  /* Select the Trigger source */
  TIM5_SelectInputTrigger((TIM5_TRGSelection_TypeDef)TIM5_TIxExternalCLKSource);

  /* Select the External clock mode1 */
  TIM5->SMCR |= (uint8_t)(TIM5_SlaveMode_External1);
}

/**
  * @brief  Selects the TIM5 Input Trigger source.
  * @param  TIM5_InputTriggerSource : Specifies Input Trigger source.
  *   This parameter can be one of the @ref TIM5_TRGSelection_TypeDef enumeration.
  * @retval None
  */
void TIM5_SelectInputTrigger(TIM5_TRGSelection_TypeDef TIM5_InputTriggerSource)
{
  uint8_t tmpsmcr = 0;

  /* Check the parameters */
  assert_param(IS_TIM5_TRIGGER_SELECTION(TIM5_InputTriggerSource));

  tmpsmcr = TIM5->SMCR;

  /* Select the Tgigger Source */
  tmpsmcr &= (uint8_t)(~TIM_SMCR_TS);
  tmpsmcr |= (uint8_t)TIM5_InputTriggerSource;

  TIM5->SMCR = (uint8_t)tmpsmcr;
}

/**
  * @brief  Enables or Disables the TIM5 Update event.
  * @param  NewState : The new state of the TIM5 peripheral Preload register.
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */

void TIM5_UpdateDisableConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the UDIS Bit */
  if (NewState != DISABLE)
  {
    TIM5->CR1 |= TIM_CR1_UDIS;
  }
  else
  {
    TIM5->CR1 &= (uint8_t)(~TIM_CR1_UDIS);
  }
}

/**
  * @brief  Selects the TIM5 Update Request Interrupt source.
  * @param  TIM5_UpdateSource : Specifies the Update source.
  *   This parameter can be one of the @ref TIM5_UpdateSource_TypeDef enumeration.
  * @retval None
  */
void TIM5_UpdateRequestConfig(TIM5_UpdateSource_TypeDef TIM5_UpdateSource)
{
  /* Check the parameters */
  assert_param(IS_TIM5_UPDATE_SOURCE(TIM5_UpdateSource));

  /* Set or Reset the URS Bit */
  if (TIM5_UpdateSource == TIM5_UpdateSource_Regular)
  {
    TIM5->CR1 |= TIM_CR1_URS ;
  }
  else
  {
    TIM5->CR1 &= (uint8_t)(~TIM_CR1_URS);
  }
}

/**
  * @brief  Enables or Disables the TIM’s Hall sensor interface.
  * @param  NewState : The new state of the TIM5 Hall sensor interface.
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void TIM5_SelectHallSensor(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the TI1S Bit */
  if (NewState != DISABLE)
  {
    TIM5->CR2 |= TIM_CR2_TI1S;
  }
  else
  {
    TIM5->CR2 &= (uint8_t)(~TIM_CR2_TI1S);
  }
}

/**
  * @brief  Selects the TIM’s One Pulse Mode.
  * @param  TIM5_OPMode : Specifies the OPM Mode to be used.
  *   This parameter can be one of the @ref TIM5_OPMode_TypeDef enumeration.
  * @retval None
  */
void TIM5_SelectOnePulseMode(TIM5_OPMode_TypeDef TIM5_OPMode)
{
  /* Check the parameters */
  assert_param(IS_TIM5_OPM_MODE(TIM5_OPMode));

  /* Set or Reset the OPM Bit */
  if (TIM5_OPMode == TIM5_OPMode_Single)
  {
    TIM5->CR1 |= TIM_CR1_OPM ;
  }
  else
  {
    TIM5->CR1 &= (uint8_t)(~TIM_CR1_OPM);
  }
}

/**
  * @brief  Selects the TIM5 Trigger Output Mode.
  * @param  TIM5_TRGOSource : Specifies the Trigger Output source.
  *   This parameter can be one of the @ref TIM5_TRGOSource_TypeDef enumeration.
  * @retval None
  */
void TIM5_SelectOutputTrigger(TIM5_TRGOSource_TypeDef TIM5_TRGOSource)
{
  uint8_t tmpcr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM5_TRGO_SOURCE(TIM5_TRGOSource));

  tmpcr2 = TIM5->CR2;

  /* Reset the MMS Bits */
  tmpcr2 &= (uint8_t)(~TIM_CR2_MMS);

  /* Select the TRGO source */
  tmpcr2 |=  (uint8_t)TIM5_TRGOSource;

  TIM5->CR2 = tmpcr2;
}

/**
  * @brief  Selects the TIM5 Slave Mode.
  * @param  TIM5_SlaveMode : Specifies the TIM5 Slave Mode.
  *   This parameter can be one of the @ref TIM5_SlaveMode_TypeDef enumeration.
  * @retval None
  */
void TIM5_SelectSlaveMode(TIM5_SlaveMode_TypeDef TIM5_SlaveMode)
{
  uint8_t tmpsmcr = 0;

  /* Check the parameters */
  assert_param(IS_TIM5_SLAVE_MODE(TIM5_SlaveMode));

  tmpsmcr = TIM5->SMCR;

  /* Reset the SMS Bits */
  tmpsmcr &= (uint8_t)(~TIM_SMCR_SMS);

  /* Select the Slave Mode */
  tmpsmcr |= (uint8_t)TIM5_SlaveMode;

  TIM5->SMCR = tmpsmcr;
}

/**
  * @brief  Sets or Resets the TIM5 Master/Slave Mode.
  * @param  NewState : The new state of the synchronization between TIM5 and its slaves (through TRGO).
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void TIM5_SelectMasterSlaveMode(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the MSM Bit */
  if (NewState != DISABLE)
  {
    TIM5->SMCR |= TIM_SMCR_MSM;
  }
  else
  {
    TIM5->SMCR &= (uint8_t)(~TIM_SMCR_MSM);
  }
}

/**
  * @brief  Configures the TIM5 Encoder Interface.
  * @param  TIM5_EncoderMode : Specifies the TIM5 Encoder Mode.
  *   This parameter can be one of the @ref TIM5_EncoderMode_TypeDef enumeration.
  * @param  TIM5_IC1Polarity : Specifies the IC1 Polarity.
  *   This parameter can be one of the @ref TIM5_ICPolarity_TypeDef enumeration.
  * @param  TIM5_IC2Polarity : Specifies the IC2 Polarity.
  *   This parameter can be one of the @ref TIM5_ICPolarity_TypeDef enumeration.
  * @retval None
  */
void TIM5_EncoderInterfaceConfig(TIM5_EncoderMode_TypeDef TIM5_EncoderMode,
                                 TIM5_ICPolarity_TypeDef TIM5_IC1Polarity,
                                 TIM5_ICPolarity_TypeDef TIM5_IC2Polarity)
{
  uint8_t tmpsmcr = 0;
  uint8_t tmpccmr1 = 0;
  uint8_t tmpccmr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM5_ENCODER_MODE(TIM5_EncoderMode));
  assert_param(IS_TIM5_IC_POLARITY(TIM5_IC1Polarity));
  assert_param(IS_TIM5_IC_POLARITY(TIM5_IC2Polarity));

  tmpsmcr = TIM5->SMCR;
  tmpccmr1 = TIM5->CCMR1;
  tmpccmr2 = TIM5->CCMR2;

  /* Set the encoder Mode */
  tmpsmcr &= (uint8_t)(TIM_SMCR_MSM | TIM_SMCR_TS)  ;
  tmpsmcr |= (uint8_t)TIM5_EncoderMode;

  /* Select the Capture Compare 1 and the Capture Compare 2 as input */
  tmpccmr1 &= (uint8_t)(~TIM_CCMR_CCxS);
  tmpccmr2 &= (uint8_t)(~TIM_CCMR_CCxS);
  tmpccmr1 |= TIM_CCMR_TIxDirect_Set;
  tmpccmr2 |= TIM_CCMR_TIxDirect_Set;

  /* Set the TI1 and the TI2 Polarities */
  if (TIM5_IC1Polarity == TIM5_ICPolarity_Falling)
  {
    TIM5->CCER1 |= TIM_CCER1_CC1P ;
  }
  else
  {
    TIM5->CCER1 &= (uint8_t)(~TIM_CCER1_CC1P) ;
  }

  if (TIM5_IC2Polarity == TIM5_ICPolarity_Falling)
  {
    TIM5->CCER1 |= TIM_CCER1_CC2P ;
  }
  else
  {
    TIM5->CCER1 &= (uint8_t)(~TIM_CCER1_CC2P) ;
  }

  TIM5->SMCR = tmpsmcr;
  TIM5->CCMR1 = tmpccmr1;
  TIM5->CCMR2 = tmpccmr2;
}

/**
  * @brief  Configures the TIM5 Prescaler.
  * @param  Prescaler : Specifies the Prescaler Register value
  *   This parameter can be one of the @ref TIM5_Prescaler_TypeDef enumeration.
  * @param  TIM5_PSCReloadMode : Specifies the TIM5 Prescaler Reload mode.
  *   This parameter can be one of the @ref TIM5_PSCReloadMode_TypeDef enumeration.
  * @retval None
  */
void TIM5_PrescalerConfig(TIM5_Prescaler_TypeDef Prescaler,
                          TIM5_PSCReloadMode_TypeDef TIM5_PSCReloadMode)
{
  /* Check the parameters */
  assert_param(IS_TIM5_PRESCALER(Prescaler));
  assert_param(IS_TIM5_PRESCALER_RELOAD(TIM5_PSCReloadMode));

  /* Set the Prescaler value */
  TIM5->PSCR = (uint8_t)(Prescaler);

  /* Set or reset the UG Bit */
  if (TIM5_PSCReloadMode == TIM5_PSCReloadMode_Immediate)
  {
    TIM5->EGR |= TIM_EGR_UG ;
  }
  else
  {
    TIM5->EGR &= (uint8_t)(~TIM_EGR_UG) ;
  }
}

/**
  * @brief  Specifies the TIM5 Counter Mode to be used.
  * @param  TIM5_CounterMode : Specifies the Counter Mode to be used
  *   This parameter can be one of the @ref TIM5_CounterMode_TypeDef enumeration.
  * @retval None
  */
void TIM5_CounterModeConfig(TIM5_CounterMode_TypeDef TIM5_CounterMode)
{
  uint8_t tmpcr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM5_COUNTER_MODE(TIM5_CounterMode));

  tmpcr1 = TIM5->CR1;

  /* Reset the CMS and DIR Bits */
  tmpcr1 &= (uint8_t)((uint8_t)(~TIM_CR1_CMS) & (uint8_t)(~TIM_CR1_DIR));

  /* Set the Counter Mode */
  tmpcr1 |= (uint8_t)TIM5_CounterMode;

  TIM5->CR1 = tmpcr1;
}

/**
  * @brief  Forces the TIM5 Channel1 output waveform to active or inactive level.
  * @param  TIM5_ForcedAction : Specifies the forced Action to be set to the output waveform.
  *   This parameter can be one of the @ref TIM5_ForcedAction_TypeDef enumeration.
  * @retval None
  */
void TIM5_ForcedOC1Config(TIM5_ForcedAction_TypeDef TIM5_ForcedAction)
{
  uint8_t tmpccmr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM5_FORCED_ACTION(TIM5_ForcedAction));

  tmpccmr1 = TIM5->CCMR1;

  /* Reset the OCM Bits */
  tmpccmr1 &= (uint8_t)(~TIM_CCMR_OCM);

  /* Configure The Forced output Mode */
  tmpccmr1 |= (uint8_t)TIM5_ForcedAction;

  TIM5->CCMR1 = tmpccmr1;
}

/**
  * @brief  Forces the TIM5 Channel2 output waveform to active or inactive level.
  * @param  TIM5_ForcedAction : Specifies the forced Action to be set to the output waveform.
  *   This parameter can be one of the @ref TIM5_ForcedAction_TypeDef enumeration.
  * @retval None
  */
void TIM5_ForcedOC2Config(TIM5_ForcedAction_TypeDef TIM5_ForcedAction)
{
  uint8_t tmpccmr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM5_FORCED_ACTION(TIM5_ForcedAction));

  tmpccmr2 = TIM5->CCMR2;

  /* Reset the OCM Bits */
  tmpccmr2 &= (uint8_t)(~TIM_CCMR_OCM);

  /* Configure The Forced output Mode */
  tmpccmr2 |= (uint8_t)TIM5_ForcedAction;

  TIM5->CCMR2 = tmpccmr2;
}

/**
  * @brief  Enables or disables TIM5 peripheral Preload register on ARR.
  * @param  NewState : The new state of the TIM5 peripheral Preload register.
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void TIM5_ARRPreloadConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the ARPE Bit */
  if (NewState != DISABLE)
  {
    TIM5->CR1 |= TIM_CR1_ARPE;
  }
  else
  {
    TIM5->CR1 &= (uint8_t)(~TIM_CR1_ARPE);
  }
}

/**
  * @brief  Enables or disables the TIM5 peripheral Preload Register on CCR1.
  * @param  NewState : The new state of the Capture Compare Preload register.
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void TIM5_OC1PreloadConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the OC1PE Bit */
  if (NewState != DISABLE)
  {
    TIM5->CCMR1 |= TIM_CCMR_OCxPE ;
  }
  else
  {
    TIM5->CCMR1 &= (uint8_t)(~TIM_CCMR_OCxPE) ;
  }
}

/**
  * @brief  Enables or disables the TIM5 peripheral Preload Register on CCR2.
  * @param  NewState : The new state of the Capture Compare Preload register.
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void TIM5_OC2PreloadConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the OC2PE Bit */
  if (NewState != DISABLE)
  {
    TIM5->CCMR2 |= TIM_CCMR_OCxPE ;
  }
  else
  {
    TIM5->CCMR2 &= (uint8_t)(~TIM_CCMR_OCxPE) ;
  }
}

/**
  * @brief  Configures the TIM5 Capture Compare 1 Fast feature.
  * @param  NewState : The new state of the Output Compare Fast Enable bit.
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void TIM5_OC1FastCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the OC1FE Bit */
  if (NewState != DISABLE)
  {
    TIM5->CCMR1 |= TIM_CCMR_OCxFE ;
  }
  else
  {
    TIM5->CCMR1 &= (uint8_t)(~TIM_CCMR_OCxFE) ;
  }
}

/**
  * @brief  Configures the TIM5 Capture Compare 2 Fast feature.
  * @param  NewState : The new state of the Output Compare Fast Enable bit.
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */

void TIM5_OC2FastCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the OC2FE Bit */
  if (NewState != DISABLE)
  {
    TIM5->CCMR2 |= TIM_CCMR_OCxFE ;
  }
  else
  {
    TIM5->CCMR2 &= (uint8_t)(~TIM_CCMR_OCxFE) ;
  }
}

/**
  * @brief  Configures the TIM5 event to be generated by software.
  * @param  TIM5_EventSource : Specifies the event source.
  *   This parameter can be one of the @ref TIM5_EventSource_TypeDef enumeration.
  * @retval None
  */
void TIM5_GenerateEvent(TIM5_EventSource_TypeDef TIM5_EventSource)
{
  /* Check the parameters */
  assert_param(IS_TIM5_EVENT_SOURCE((uint8_t)TIM5_EventSource));

  /* Set the event sources */
  TIM5->EGR |= (uint8_t)TIM5_EventSource;
}

/**
  * @brief  Configures the TIM5 Channel 1 polarity.
  * @param  TIM5_OCPolarity : Specifies the OC1 Polarity.
  *   This parameter can be one of the @ref TIM5_OCPolarity_TypeDef enumeration.
  * @retval None
  */
void TIM5_OC1PolarityConfig(TIM5_OCPolarity_TypeDef TIM5_OCPolarity)
{
  /* Check the parameters */
  assert_param(IS_TIM5_OC_POLARITY(TIM5_OCPolarity));

  /* Set or Reset the CC1P Bit */
  if (TIM5_OCPolarity == TIM5_OCPolarity_Low)
  {
    TIM5->CCER1 |= TIM_CCER1_CC1P ;
  }
  else
  {
    TIM5->CCER1 &= (uint8_t)(~TIM_CCER1_CC1P) ;
  }
}

/**
  * @brief  Configures the TIM5 Channel 2 polarity.
  * @param  TIM5_OCPolarity : Specifies the OC2 Polarity.
  *   This parameter can be one of the @ref TIM5_OCPolarity_TypeDef enumeration.
  * @retval None
  */
void TIM5_OC2PolarityConfig(TIM5_OCPolarity_TypeDef TIM5_OCPolarity)
{
  /* Check the parameters */
  assert_param(IS_TIM5_OC_POLARITY(TIM5_OCPolarity));

  /* Set or Reset the CC2P Bit */
  if (TIM5_OCPolarity == TIM5_OCPolarity_Low)
  {
    TIM5->CCER1 |= TIM_CCER1_CC2P ;
  }
  else
  {
    TIM5->CCER1 &= (uint8_t)(~TIM_CCER1_CC2P) ;
  }
}

/**
  * @brief  Enables or disables the TIM5 Capture Compare Channel x.
  * @param  TIM5_Channel : Specifies the TIM5 Channel.
  *   This parameter can be one of @ref TIM5_Channel_TypeDef enumeration.
  * @param  NewState : Specifies the TIM5 Channel CCxE bit new state.
  *   This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void TIM5_CCxCmd(TIM5_Channel_TypeDef TIM5_Channel,
                 FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM5_CHANNEL(TIM5_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (TIM5_Channel == TIM5_Channel_1)
  {
    /* Set or Reset the CC1E Bit */
    if (NewState != DISABLE)
    {
      TIM5->CCER1 |= TIM_CCER1_CC1E ;
    }
    else
    {
      TIM5->CCER1 &= (uint8_t)(~TIM_CCER1_CC1E) ;
    }

  }
  else /* if (TIM5_Channel == TIM5_Channel_2) */
  {
    /* Set or Reset the CC2E Bit */
    if (NewState != DISABLE)
    {
      TIM5->CCER1 |= TIM_CCER1_CC2E;
    }
    else
    {
      TIM5->CCER1 &= (uint8_t)(~TIM_CCER1_CC2E) ;
    }
  }
}

/**
  * @brief  Selects the TIM5 Ouput Compare Mode. This function disables the
  * selected channel before changing the Ouput Compare Mode. User has to
  * enable this channel using TIM5_CCxCmd and TIM5_CCxNCmd functions.
  * @param  TIM5_Channel : Specifies the TIM5 Channel.
  *   This parameter can be one of the @ref TIM5_Channel_TypeDef enumeration
  * @param  TIM5_OCMode : Specifies the TIM5 Output Compare Mode.
  *   This parameter can be one of the @ref TIM5_OCMode_TypeDef enumeration.
  * @retval None
  */
void TIM5_SelectOCxM(TIM5_Channel_TypeDef TIM5_Channel,
                     TIM5_OCMode_TypeDef TIM5_OCMode)
{
  /* Check the parameters */
  assert_param(IS_TIM5_CHANNEL(TIM5_Channel));
  assert_param(IS_TIM5_OCM(TIM5_OCMode));

  if (TIM5_Channel == TIM5_Channel_1)
  {
    /* Disable the Channel 1: Reset the CCE Bit */
    TIM5->CCER1 &= (uint8_t)(~TIM_CCER1_CC1E);

    /* Reset the Output Compare Bits */
    TIM5->CCMR1 &= (uint8_t)(~TIM_CCMR_OCM);

    /* Set the Ouput Compare Mode */
    TIM5->CCMR1 |= (uint8_t)TIM5_OCMode;
  }
  else /* if (TIM5_Channel == TIM5_Channel_2) */
  {
    /* Disable the Channel 2: Reset the CCE Bit */
    TIM5->CCER1 &= (uint8_t)(~TIM_CCER1_CC2E);

    /* Reset the Output Compare Bits */
    TIM5->CCMR2 &= (uint8_t)(~TIM_CCMR_OCM);

    /* Set the Ouput Compare Mode */
    TIM5->CCMR2 |= (uint8_t)TIM5_OCMode;
  }
}

/**
  * @brief  Sets the TIM5 Counter Register value.
  * @param  Counter : Specifies the Counter register new value.
  *   This parameter is between 0x0000 and 0xFFFF.
  * @retval None
  */
void TIM5_SetCounter(uint16_t Counter)
{

  /* Set the Counter Register value */
  TIM5->CNTRH = (uint8_t)(Counter >> 8);
  TIM5->CNTRL = (uint8_t)(Counter);
}

/**
  * @brief  Sets the TIM5 Autoreload Register value.
  * @param  Autoreload : Specifies the Autoreload register new value.
  *   This parameter is between 0x0000 and 0xFFFF.
  * @retval None
  */
void TIM5_SetAutoreload(uint16_t Autoreload)
{
  /* Set the Autoreload Register value */
  TIM5->ARRH = (uint8_t)(Autoreload >> 8);
  TIM5->ARRL = (uint8_t)(Autoreload);
}

/**
  * @brief  Sets the TIM5 Capture Compare1 Register value.
  * @param  Compare : Specifies the Capture Compare1 register new value.
  *   This parameter is between 0x0000 and 0xFFFF.
  * @retval None
  */
void TIM5_SetCompare1(uint16_t Compare)
{
  /* Set the Capture Compare1 Register value */
  TIM5->CCR1H = (uint8_t)(Compare >> 8);
  TIM5->CCR1L = (uint8_t)(Compare);
}

/**
  * @brief  Sets the TIM5 Capture Compare2 Register value.
  * @param  Compare : Specifies the Capture Compare2 register new value.
  *   This parameter is between 0x0000 and 0xFFFF.
  * @retval None
  */
void TIM5_SetCompare2(uint16_t Compare)
{
  /* Set the Capture Compare2 Register value */
  TIM5->CCR2H = (uint8_t)(Compare >> 8);
  TIM5->CCR2L = (uint8_t)(Compare);
}

/**
  * @brief  Sets the TIM5 Input Capture 1 prescaler.
  * @param  TIM5_IC1Prescaler : Specifies the Input Capture prescaler new value
  *   This parameter can be one of the @ref TIM5_ICPSC_TypeDef enumeration.
  * @retval None
  */
void TIM5_SetIC1Prescaler(TIM5_ICPSC_TypeDef TIM5_IC1Prescaler)
{
  uint8_t tmpccmr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM5_IC_PRESCALER(TIM5_IC1Prescaler));

  tmpccmr1 = TIM5->CCMR1;

  /* Reset the IC1PSC Bits */
  tmpccmr1 &= (uint8_t)(~TIM_CCMR_ICxPSC);

  /* Set the IC1PSC value */
  tmpccmr1 |= (uint8_t)TIM5_IC1Prescaler;

  TIM5->CCMR1 = tmpccmr1;
}

/**
  * @brief  Sets the TIM5 Input Capture 2 prescaler.
  * @param  TIM5_IC2Prescaler : Specifies the Input Capture prescaler new value
  *   This parameter can be one of the @ref TIM5_ICPSC_TypeDef enumeration.
  * @retval None
  */
void TIM5_SetIC2Prescaler(TIM5_ICPSC_TypeDef TIM5_IC2Prescaler)
{
  uint8_t tmpccmr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM5_IC_PRESCALER(TIM5_IC2Prescaler));

  tmpccmr2 = TIM5->CCMR2;

  /* Reset the IC2PSC Bits */
  tmpccmr2 &= (uint8_t)(~TIM_CCMR_ICxPSC);

  /* Set the IC2PSC value */
  tmpccmr2 |= (uint8_t)TIM5_IC2Prescaler;

  TIM5->CCMR2 = tmpccmr2;
}

/**
  * @brief  Gets the TIM5 Input Capture 1 value.
  * @param  None
  * @retval Capture Compare 1 Register value.
  */
uint16_t TIM5_GetCapture1(void)
{
  uint16_t tmpccr1 = 0;
  uint8_t tmpccr1l, tmpccr1h;

  tmpccr1h = TIM5->CCR1H;
  tmpccr1l = TIM5->CCR1L;

  tmpccr1 = (uint16_t)(tmpccr1l);
  tmpccr1 |= (uint16_t)((uint16_t)tmpccr1h << 8);
  /* Get the Capture 1 Register value */
  return ((uint16_t)tmpccr1);
}

/**
  * @brief  Gets the TIM5 Input Capture 2 value.
  * @param  None
  * @retval Capture Compare 2 Register value.
  */
uint16_t TIM5_GetCapture2(void)
{
  uint16_t tmpccr2 = 0;
  uint8_t tmpccr2l, tmpccr2h;

  tmpccr2h = TIM5->CCR2H;
  tmpccr2l = TIM5->CCR2L;

  tmpccr2 = (uint16_t)(tmpccr2l);
  tmpccr2 |= (uint16_t)((uint16_t)tmpccr2h << 8);
  /* Get the Capture 2 Register value */
  return ((uint16_t)tmpccr2);
}

/**
  * @brief  Gets the TIM5 Counter value.
  * @param  None
  * @retval Counter Register value.
  */
uint16_t TIM5_GetCounter(void)
{
  uint16_t tmpcnt = 0;
  uint8_t tmpcntrl, tmpcntrh;

  tmpcntrh = TIM5->CNTRH;
  tmpcntrl = TIM5->CNTRL;

  tmpcnt = (uint16_t)(tmpcntrl);
  tmpcnt |= (uint16_t)((uint16_t)tmpcntrh << 8);
  /* Get the Counter Register value */
  return ((uint16_t)tmpcnt);
}

/**
  * @brief  Gets the TIM5 Prescaler value.
  * @param  None
  * @retval TIM5_Prescaler_TypeDef : Prescaler Register value.
  */
TIM5_Prescaler_TypeDef TIM5_GetPrescaler(void)
{
  /* Get the Prescaler Register value */
  return ((TIM5_Prescaler_TypeDef)TIM5->PSCR);
}

/**
  * @brief  Selects the TIM5 peripheral Capture Compare DMA source.
  * @param   NewState: new state of the Capture Compare DMA source.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM5_SelectCCDMA(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the CCDS Bit */
    TIM5->CR2 |= TIM_CR2_CCDS;
  }
  else
  {
    /* Reset the CCDS Bit */
    TIM5->CR2 &= (uint8_t)(~TIM_CR2_CCDS);
  }
}

/**
  * @brief  Checks whether the specified TIM5 flag is set or not.
  * @param  TIM5_FLAG : Specifies the flag to check.
  *   This parameter can be one of the @ref TIM5_FLAG_TypeDef enumeration.
  * @retval FlagStatus : The new state of TIM5_FLAG.
  *   This parameter can be any of the @ref FlagStatus enumeration.
  */
FlagStatus TIM5_GetFlagStatus(TIM5_FLAG_TypeDef TIM5_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint8_t tim5_flag_l = 0, tim5_flag_h = 0;

  /* Check the parameters */
  assert_param(IS_TIM5_GET_FLAG(TIM5_FLAG));

  tim5_flag_l = (uint8_t)(TIM5->SR1 & (uint8_t)(TIM5_FLAG));
  tim5_flag_h = (uint8_t)(TIM5->SR2 & (uint8_t)((uint16_t)TIM5_FLAG >> 8));

  if ((uint8_t)(tim5_flag_l | tim5_flag_h) != 0)
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
  * @param  TIM5_FLAG : Specifies the flag to clear.
  *   This parameter can be one of the @ref TIM5_FLAG_TypeDef enumeration.
  * @retval None
  */
void TIM5_ClearFlag(TIM5_FLAG_TypeDef TIM5_FLAG)
{
  /* Check the parameters */
  assert_param(IS_TIM5_CLEAR_FLAG((uint16_t)TIM5_FLAG));
  /* Clear the flags (rc_w0) clear this bit by writing 0. Writing ‘1’ has no effect*/
  TIM5->SR1 = (uint8_t)(~(uint8_t)(TIM5_FLAG));
  TIM5->SR2 = (uint8_t)(~(uint8_t)((uint16_t)TIM5_FLAG >> 8));
}

/**
  * @brief  Checks whether the TIM5 interrupt has occurred or not.
  * @param  TIM5_IT : Specifies the TIM5 interrupt source to check.
  *   This parameter can be one of the @ref TIM5_IT_TypeDef enumeration.
  * @retval ITStatus : The new state of the TIM5_IT.
  *   This parameter can be any of the @ref ITStatus enumeration.
  */
ITStatus TIM5_GetITStatus(TIM5_IT_TypeDef TIM5_IT)
{
  ITStatus bitstatus = RESET;

  uint8_t TIM5_itStatus = 0x0, TIM5_itEnable = 0x0;

  /* Check the parameters */
  assert_param(IS_TIM5_GET_IT(TIM5_IT));

  TIM5_itStatus = (uint8_t)(TIM5->SR1 & (uint8_t)TIM5_IT);

  TIM5_itEnable = (uint8_t)(TIM5->IER & (uint8_t)TIM5_IT);

  if ((TIM5_itStatus != (uint8_t)RESET ) && (TIM5_itEnable != (uint8_t)RESET))
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
  * @param  TIM5_IT : Specifies the pending bit to clear.
  *   This parameter can be one of the @ref TIM5_IT_TypeDef enumeration.
  * @retval None
  */
void TIM5_ClearITPendingBit(TIM5_IT_TypeDef TIM5_IT)
{
  /* Check the parameters */
  assert_param(IS_TIM5_IT(TIM5_IT));

  /* Clear the IT pending Bit */
  TIM5->SR1 = (uint8_t)(~(uint8_t)TIM5_IT);
}

/**
  * @brief  Configure the TI1 as Input.
  * @param  TIM5_ICPolarity : The Input Polarity.
  *   This parameter can be one of the @ref TIM5_ICPolarity_TypeDef enumeration.
  * @param  TIM5_ICSelection : Specifies the input to be used.
  *   This parameter can be one of the @ref TIM5_ICSelection_TypeDef enumeration.
  * @param  TIM5_ICFilter : Specifies the Input Capture Filter.
  *   This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI1_Config(TIM5_ICPolarity_TypeDef TIM5_ICPolarity, \
                       TIM5_ICSelection_TypeDef TIM5_ICSelection, \
                       uint8_t TIM5_ICFilter)
{
  uint8_t tmpccmr1 = 0;
  uint8_t tmpicpolarity = TIM5_ICPolarity;
  tmpccmr1 = TIM5->CCMR1;

  /* Check the parameters */
  assert_param(IS_TIM5_IC_POLARITY(TIM5_ICPolarity));
  assert_param(IS_TIM5_IC_SELECTION(TIM5_ICSelection));
  assert_param(IS_TIM5_IC_FILTER(TIM5_ICFilter));

  /* Disable the Channel 1: Reset the CCE Bit */
  TIM5->CCER1 &=  (uint8_t)(~TIM_CCER1_CC1E);

  /* Select the Input and set the filter */
  tmpccmr1 &= (uint8_t)(~TIM_CCMR_CCxS) & (uint8_t)(~TIM_CCMR_ICxF);
  tmpccmr1 |= (uint8_t)(((uint8_t)(TIM5_ICSelection)) | ((uint8_t)(TIM5_ICFilter << 4)));

  TIM5->CCMR1 = tmpccmr1;

  /* Select the Polarity */
  if (tmpicpolarity == (uint8_t)(TIM5_ICPolarity_Falling))
  {
    TIM5->CCER1 |= TIM_CCER1_CC1P;
  }
  else
  {
    TIM5->CCER1 &= (uint8_t)(~TIM_CCER1_CC1P);
  }

  /* Set the CCE Bit */
  TIM5->CCER1 |=  TIM_CCER1_CC1E;
}

/**
  * @brief  Configure the TI2 as Input.
  * @param  TIM5_ICPolarity : The Input Polarity.
  *   This parameter can be one of the @ref TIM5_ICPolarity_TypeDef enumeration.
  * @param  TIM5_ICSelection : Specifies the input to be used.
  *   This parameter can be one of the @ref TIM5_ICSelection_TypeDef enumeration.
  * @param  TIM5_ICFilter : Specifies the Input Capture Filter.
  *   This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI2_Config(TIM5_ICPolarity_TypeDef TIM5_ICPolarity,
                       TIM5_ICSelection_TypeDef TIM5_ICSelection,
                       uint8_t TIM5_ICFilter)
{
  uint8_t tmpccmr2 = 0;
  uint8_t tmpicpolarity = TIM5_ICPolarity;

  /* Check the parameters */
  assert_param(IS_TIM5_IC_POLARITY(TIM5_ICPolarity));
  assert_param(IS_TIM5_IC_SELECTION(TIM5_ICSelection));
  assert_param(IS_TIM5_IC_FILTER(TIM5_ICFilter));

  tmpccmr2 = TIM5->CCMR2;

  /* Disable the Channel 2: Reset the CCE Bit */
  TIM5->CCER1 &=  (uint8_t)(~TIM_CCER1_CC2E);

  /* Select the Input and set the filter */
  tmpccmr2 &= (uint8_t)(~TIM_CCMR_CCxS) & (uint8_t)(~TIM_CCMR_ICxF);
  tmpccmr2 |= (uint8_t)(((uint8_t)(TIM5_ICSelection)) | ((uint8_t)(TIM5_ICFilter << 4)));

  TIM5->CCMR2 = tmpccmr2;

  /* Select the Polarity */
  if (tmpicpolarity == TIM5_ICPolarity_Falling)
  {
    TIM5->CCER1 |= TIM_CCER1_CC2P ;
  }
  else
  {
    TIM5->CCER1 &= (uint8_t)(~TIM_CCER1_CC2P) ;
  }

  /* Set the CCE Bit */
  TIM5->CCER1 |=  TIM_CCER1_CC2E;
}
/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
