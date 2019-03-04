/**
  ******************************************************************************
  * @file    stm8l15x_adc.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    09/24/2010
  * @brief   This file provides all the ADC firmware functions.
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
#include "stm8l15x_adc.h"

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
    * @addtogroup ADC_Public_Functions
    * @{
    */

/**
  * @brief  Deinitializes the ADC peripheral registers to their default reset values.
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @retval None
  */
void ADC_DeInit(ADC_TypeDef* ADCx)
{
  /*  Set the Configuration registers to their reset values */
  ADCx->CR1 =  ADC_CR1_RESET_VALUE;
  ADCx->CR2 =  ADC_CR2_RESET_VALUE;
  ADCx->CR3 =  ADC_CR3_RESET_VALUE;

  /*  Set the status registers to their reset values */
  ADCx->SR =  (uint8_t)~ADC_SR_RESET_VALUE;

  /*  Set the High threshold registers to their reset values */
  ADCx->HTRH =  ADC_HTRH_RESET_VALUE;
  ADCx->HTRL =  ADC_HTRL_RESET_VALUE;

  /*  Set the low threshold registers to their reset values */
  ADCx->LTRH =  ADC_LTRH_RESET_VALUE;
  ADCx->LTRL =  ADC_LTRL_RESET_VALUE;

  /*  Set the channels sequence registers to their reset values */
  ADCx->SQR[0] =  ADC_SQR1_RESET_VALUE;
  ADCx->SQR[1] =  ADC_SQR2_RESET_VALUE;
  ADCx->SQR[2] =  ADC_SQR3_RESET_VALUE;
  ADCx->SQR[3] =  ADC_SQR4_RESET_VALUE;

  /*  Set the channels Trigger registers to their reset values */
  ADCx->TRIGR[0] =  ADC_TRIGR1_RESET_VALUE;
  ADCx->TRIGR[1] =  ADC_TRIGR2_RESET_VALUE;
  ADCx->TRIGR[2] =  ADC_TRIGR3_RESET_VALUE;
  ADCx->TRIGR[3] =  ADC_TRIGR4_RESET_VALUE;
}

/**
  * @brief  Initializes the specified ADC peripheral according to the specified parameters.
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @param  ADC_ConversionMode : specifies the ADC conversion mode,
  *         This parameter can be one of the @ref ADC_ConversionMode_TypeDef
  * @param  ADC_Resolution : specifies the ADC Data resolusion,
  *         This parameter can be one of the @ref ADC_Resolution_TypeDef
  * @param  ADC_Prescaler : specifies the ADC Prescaler,
  *         This parameter can be one of the @ref ADC_Prescaler_TypeDef
  * @retval None
  */
void ADC_Init(ADC_TypeDef* ADCx,
              ADC_ConversionMode_TypeDef ADC_ConversionMode,
              ADC_Resolution_TypeDef ADC_Resolution,
              ADC_Prescaler_TypeDef ADC_Prescaler)
{
  /* Check the parameters */
  assert_param(IS_ADC_CONVERSION_MODE(ADC_ConversionMode));
  assert_param(IS_ADC_RESOLUTION(ADC_Resolution));
  assert_param(IS_ADC_PRESCALER(ADC_Prescaler));

  /*clear CR1 register */
  ADCx->CR1 &= (uint8_t)~(ADC_CR1_CONT | ADC_CR1_RES);

  /* set the resolution and the conversion mode */
  ADCx->CR1 |= (uint8_t)((uint8_t)ADC_ConversionMode | (uint8_t)ADC_Resolution);

  /*clear CR2 register */
  ADCx->CR2 &= (uint8_t)~(ADC_CR2_PRESC );

  /* set the Prescaler */
  ADCx->CR2 |= (uint8_t) ADC_Prescaler;
}


/**
  * @brief  Enables or disables the selected ADC channel(s).
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @param  ADC_Channels: specifies the ADC channels to be initialized,
  *         This parameter can be a value of @ref ADC_Channel_TypeDef, or a combination
  *         of values as follows:
  *           - 1st combination : channels from ADC_Channel_0 to ADC_Channel_7
  *           - 2nd combination : channels from ADC_Channel_8 to ADC_Channel_15
  *           - 3rd combination : channels from ADC_Channel_16 to ADC_Channel_23
  * @param  NewState : new state of the specified ADC channel(s).
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ChannelCmd(ADC_TypeDef* ADCx,
                    ADC_Channel_TypeDef ADC_Channels,
                    FunctionalState NewState)
{
  uint8_t regindex = 0;
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  regindex = (uint8_t)((uint16_t)ADC_Channels >> 8);

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC channel(s). */
    ADCx->SQR[regindex] |= (uint8_t)(ADC_Channels);
  }
  else
  {
    /* Disable the selected ADC channel(s). */
    ADCx->SQR[regindex] &= (uint8_t)(~(uint8_t)(ADC_Channels));
  }
}

/**
  * @brief  Enables or disables the selected ADC peripheral.
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @param  NewState : new state of the specified ADC peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_Cmd(ADC_TypeDef* ADCx,
             FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the ADON bit to wake up the specified ADC from power down mode */
    ADCx->CR1 |= ADC_CR1_ADON;
  }
  else
  {
    /* Disable the selected ADC peripheral */
    ADCx->CR1 &= (uint8_t)~ADC_CR1_ADON;
  }
}

/**
  * @brief  Enables or disables the specified ADC interrupts.
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @param  ADC_IT : specifies the ADC interrupt sources to be enabled or disabled.
  *         This parameter can be any combination of the @ref ADC_IT_TypeDef
  * @param  NewState : new state of the specified ADC interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ITConfig(ADC_TypeDef* ADCx,
                  ADC_IT_TypeDef ADC_IT,
                  FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_ADC_IT(ADC_IT));

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC interrupts */
    ADCx->CR1 |= (uint8_t) ADC_IT;
  }
  else
  {
    /* Disable the selected ADC interrupts */
    ADCx->CR1 &= (uint8_t)(~ADC_IT);
  }
}

/**
  * @brief  Enables or disables the specified ADC DMA request.
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @param  NewState : new state of the specified ADC DMA transfer.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_DMACmd(ADC_TypeDef* ADCx,
                FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the specified ADC DMA request */
    ADCx->SQR[0] &= (uint8_t)~ADC_SQR1_DMAOFF;
  }
  else
  {
    /* Disable the specified ADC DMA request */
    ADCx->SQR[0] |= ADC_SQR1_DMAOFF;
  }
}

/**
  * @brief  Enables or disables the Temperature sensor internal reference.
  * @param  NewState : new state of the Temperature sensor internal reference.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_TempSensorCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /*Enable the Temperature sensor internal reference.*/
    ADC1->TRIGR[0] |= (uint8_t)(ADC_TRIGR1_TSON);
  }
  else
  {
    /*Disable the Temperature sensor internal reference.*/
    ADC1->TRIGR[0] &= (uint8_t)(~ADC_TRIGR1_TSON);
  }
}

/**
  * @brief  Enables or disables the Internal Voltage reference.
  * @param  NewState : new state of the Internal Voltage reference.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_VrefintCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Internal Voltage reference.*/
    ADC1->TRIGR[0] |= (uint8_t)(ADC_TRIGR1_VREFINTON);
  }
  else
  {
    /* Disable the Internal Voltage reference.*/
    ADC1->TRIGR[0] &= (uint8_t)(~ADC_TRIGR1_VREFINTON);
  }
}

/**
  * @brief  Starts ADC conversion, by software trigger.
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @retval None
  */
void ADC_SoftwareStartConv(ADC_TypeDef* ADCx)
{
  /*  Start the ADC software conversion */
  ADCx->CR1 |= ADC_CR1_START;
}

/**
  * @brief  Configures the sampling time for the selected ADC channel group.
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @param  ADC_GroupChannels : ADC channel group to configure.
  *         This parameter can be a value of @ref ADC_Group_TypeDef
  * @param  ADC_SamplingTime : Specifies the sample time value
  *         This parameter can be a value of @ref ADC_SamplingTime_TypeDef
  * @retval None
  */
void ADC_SamplingTimeConfig(ADC_TypeDef* ADCx,
                            ADC_Group_TypeDef ADC_GroupChannels,
                            ADC_SamplingTime_TypeDef ADC_SamplingTime)
{
  /* Check the parameters */
  assert_param(IS_ADC_GROUP(ADC_GroupChannels));
  assert_param(IS_ADC_SAMPLING_TIME_CYCLES(ADC_SamplingTime));

  if ( ADC_GroupChannels != ADC_Group_SlowChannels)
  {
    /* Configures the sampling time for the Fast ADC channel group. */
    ADCx->CR3 &= (uint8_t)~ADC_CR3_SMPT2;
    ADCx->CR3 |= (uint8_t)(ADC_SamplingTime << 5);
  }
  else
  {
    /* Configures the sampling time for the Slow ADC channel group. */
    ADCx->CR2 &= (uint8_t)~ADC_CR2_SMPT1;
    ADCx->CR2 |= (uint8_t)ADC_SamplingTime;
  }
}

/**
  * @brief  Configures the status of the Schmitt Trigger for the selected ADC channel(s).
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @param  ADC_Channels: specifies the ADC channels to be initialized,
  *         This parameter can be a value of @ref ADC_Channel_TypeDef enumeration.
  * @param  NewState : new state of the Schmitt Trigger
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_SchmittTriggerConfig(ADC_TypeDef* ADCx,
                              ADC_Channel_TypeDef ADC_Channels,
                              FunctionalState NewState)
{
  uint8_t regindex = 0;
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  regindex = (uint8_t)((uint16_t)ADC_Channels >> 8);

  if (NewState != DISABLE)
  {
    /* Enable the Schmitt Trigger for the selected ADC channel(s).*/
    ADCx->TRIGR[regindex] &= (uint8_t)(~(uint8_t)ADC_Channels);
  }
  else
  {
    /* Disable the Schmitt Trigger for the selected ADC channel(s).*/
    ADCx->TRIGR[regindex] |= (uint8_t)(ADC_Channels);
  }
}

/**
  * @brief  Configures the ADC conversion through external trigger.
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @param  ADC_ExtEventSelection : Specifies the external trigger.
  *         This parameter can be a value of @ref ADC_ExtEventSelection_TypeDef
  * @param  ADC_ExtTRGSensitivity : Specifies the external trigger sensitivity.
  *         This parameter can be a value of @ref ADC_ExtTRGSensitivity_TypeDef
  * @retval None
  */
void ADC_ExternalTrigConfig(ADC_TypeDef* ADCx,
                            ADC_ExtEventSelection_TypeDef ADC_ExtEventSelection,
                            ADC_ExtTRGSensitivity_TypeDef ADC_ExtTRGSensitivity)
{
  /* Check the parameters */
  assert_param(IS_ADC_EXT_EVENT_SELECTION(ADC_ExtEventSelection));
  assert_param(IS_ADC_EXT_TRG_SENSITIVITY(ADC_ExtTRGSensitivity));

  /*clear old config in CR2 register */
  ADCx->CR2 &= (uint8_t)~(ADC_CR2_TRIGEDGE | ADC_CR2_EXTSEL);

  /* set the External Trigger Edge Sensitivity  and the external event selection*/
  ADCx->CR2 |= (uint8_t)( (uint8_t)ADC_ExtTRGSensitivity | (uint8_t)ADC_ExtEventSelection);
}


/**
  * @brief  Returns the last ADC converted data.
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @retval The Data conversion value.
  */
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx)
{
  uint16_t tmpreg = 0;

  /* Get last ADC converted data.*/
  tmpreg = (uint16_t)(ADCx->DRH);
  tmpreg = (uint16_t)((uint16_t)((uint16_t)tmpreg << 8) | ADCx->DRL);

  /* Return the selected ADC conversion value */
  return (uint16_t)(tmpreg) ;
}


/**
  * @brief  Configures the channel to be checked by the Analog watchdog.
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @param  ADC_AnalogWatchdogSelection : Specifies the channel to be checked by
  *         by the Analog watchdog.
  *         This parameter can be a value of @ref ADC_AnalogWatchdogSelection_TypeDef
  * @retval None
  */
void ADC_AnalogWatchdogChannelSelect(ADC_TypeDef* ADCx,
                                     ADC_AnalogWatchdogSelection_TypeDef ADC_AnalogWatchdogSelection)
{
  /* Check the parameters */
  assert_param(IS_ADC_ANALOGWATCHDOG_SELECTION(ADC_AnalogWatchdogSelection));

  /*reset the CHSEL bits */
  ADCx->CR3 &= ((uint8_t)~ADC_CR3_CHSEL);

  /* Select the channel to be checked by the Analog watchdog.*/
  ADCx->CR3 |= (uint8_t)ADC_AnalogWatchdogSelection;
}

/**
  * @brief  Configures the high and low thresholds of the Analog watchdog.
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @param  HighThreshold: Analog watchdog High threshold value.
    *       This parameter must be a 12bit value.
  * @param  LowThreshold: Analog watchdog Low threshold value.
    *       This parameter must be a 12bit value.
  * @retval None
  */
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* ADCx,
                                        uint16_t HighThreshold,
                                        uint16_t LowThreshold)
{
  /* Check the parameters */
  assert_param(IS_ADC_THRESHOLD(HighThreshold));
  assert_param(IS_ADC_THRESHOLD(LowThreshold));

  /* Set the ADC high threshold */
  ADCx->HTRH = (uint8_t)(HighThreshold >> 8);
  ADCx->HTRL = (uint8_t)(HighThreshold);

  /* Set the ADC low threshold */
  ADCx->LTRH = (uint8_t)(LowThreshold >> 8);
  ADCx->LTRL = (uint8_t)(LowThreshold);
}

/**
  * @brief  Configures the Analog watchdog.
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @param  ADC_AnalogWatchdogSelection : Specifies the channel to be checked by
  *         by the Analog watchdog.
  *         This parameter can be a value of @ref ADC_AnalogWatchdogSelection_TypeDef
  * @param  HighThreshold: Analog watchdog High threshold value.
    *       This parameter must be a 12bit value.
  * @param  LowThreshold: Analog watchdog Low threshold value.
    *       This parameter must be a 12bit value.
  * @retval None
  */
void ADC_AnalogWatchdogConfig(ADC_TypeDef* ADCx,
                              ADC_AnalogWatchdogSelection_TypeDef ADC_AnalogWatchdogSelection,
                              uint16_t HighThreshold,
                              uint16_t LowThreshold)
{
  /* Check the parameters */
  assert_param(IS_ADC_ANALOGWATCHDOG_SELECTION(ADC_AnalogWatchdogSelection));
  assert_param(IS_ADC_THRESHOLD(HighThreshold));
  assert_param(IS_ADC_THRESHOLD(LowThreshold));

  /*Reset the CHSEL bits */
  ADCx->CR3 &= ((uint8_t)~ADC_CR3_CHSEL);

  /* Select the channel to be checked by the Analog watchdog.*/
  ADCx->CR3 |= (uint8_t)ADC_AnalogWatchdogSelection;

  /* Set the ADC high threshold */
  ADCx->HTRH = (uint8_t)(HighThreshold >> 8);
  ADCx->HTRL = (uint8_t)(HighThreshold);

  /* Set the ADC low threshold */
  ADCx->LTRH = (uint8_t)(LowThreshold >> 8);
  ADCx->LTRL = (uint8_t)LowThreshold;
}

/**
  * @brief  Checks whether the specified ADC flag is set or not.
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @param  ADC_FLAG: specifies the flag to check.
  *         This parameter can be a value of @ref ADC_FLAG_TypeDef
  * @retval The new state of ADC_FLAG (SET or RESET).
  */
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, ADC_FLAG_TypeDef ADC_FLAG)
{
  FlagStatus flagstatus = RESET;

  /* Check the parameters */
  assert_param(IS_ADC_GET_FLAG(ADC_FLAG));

  /* Check the status of the specified ADC flag */
  if ((ADCx->SR & ADC_FLAG) != (uint8_t)RESET)
  {
    /* ADC_FLAG is set */
    flagstatus = SET;
  }
  else
  {
    /* ADC_FLAG is reset */
    flagstatus = RESET;
  }

  /* Return the ADC_FLAG status */
  return  flagstatus;
}

/**
  * @brief  Clears the ADC's pending flags.
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @param  ADC_FLAG: specifies the flag to clear.
  *         This parameter can be a value of @ref ADC_FLAG_TypeDef
  * @retval None
  */
void ADC_ClearFlag(ADC_TypeDef* ADCx,
                   ADC_FLAG_TypeDef ADC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_ADC_CLEAR_FLAG(ADC_FLAG));

  /* Clear the selected ADC flags */
  ADCx->SR = (uint8_t)~ADC_FLAG;
}


/**
  * @brief  Checks whether the specified ADC interrupt has occurred or not.
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @param  ADC_IT: specifies the ADC interrupt source to check.
  *         This parameter can be a value of @ref ADC_IT_TypeDef
  * @retval Status of ADC_IT (SET or RESET).
  */
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx,
                         ADC_IT_TypeDef ADC_IT)
{
  ITStatus itstatus = RESET;
  uint8_t itmask = 0, enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_ADC_GET_IT(ADC_IT));

  /* Get the ADC IT index */
  itmask = (uint8_t)(ADC_IT >> 3);
  itmask =  (uint8_t)((uint8_t)((uint8_t)(itmask & (uint8_t)0x10) >> 2) | (uint8_t)(itmask & (uint8_t)0x03));

  /* Get the ADC_IT enable bit status */
  enablestatus = (uint8_t)(ADCx->CR1 & (uint8_t)ADC_IT) ;

  /* Check the status of the specified ADC interrupt */
  if (((ADCx->SR & itmask) != (uint8_t)RESET) && enablestatus)
  {
    /* ADC_IT is set */
    itstatus = SET;
  }
  else
  {
    /* ADC_IT is reset */
    itstatus = RESET;
  }

  /* Return the ADC_IT status */
  return  itstatus;
}

/**
  * @brief  Clears the ADC’s interrupt pending bits.
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @param  ADC_IT: specifies the ADC interrupt pending bit to clear.
  *         This parameter can be a value of @ref ADC_IT_TypeDef
  * @retval None
  */
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx,
                           ADC_IT_TypeDef ADC_IT)
{
  uint8_t itmask = 0;

  /* Check the parameters */
  assert_param(IS_ADC_IT(ADC_IT));

  /* Get the ADC IT index */
  itmask = (uint8_t)(ADC_IT >> 3);
  itmask =  (uint8_t)((uint8_t)(((uint8_t)(itmask & (uint8_t)0x10)) >> 2) | (uint8_t)(itmask & (uint8_t)0x03));

  /* Clear the selected ADC interrupt pending bits */
  ADCx->SR = (uint8_t)~itmask;
}

/**
    * @}
    */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
