/**
  ******************************************************************************
  * @file    stm8l15x_dac.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    09/24/2010
  * @brief   This file provides all the DAC firmware functions.
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
#include "stm8l15x_dac.h"

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
    * @addtogroup DAC_Public_Functions
    * @{
    */

/**
  * @brief  Deinitializes the DAC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void DAC_DeInit(void)
{
  /*  Set Channel1  the Configuration registers to their reset values */
  DAC->CH1CR1 = DAC_CR1_RESET_VALUE;
  DAC->CH1CR2 = DAC_CR2_RESET_VALUE;

  /*  Set Channel2  the Configuration registers to their reset values */
  DAC->CH2CR1 = DAC_CR1_RESET_VALUE;
  DAC->CH2CR2 = DAC_CR2_RESET_VALUE;

  /*  Set the Software Trigger configuration registers to their reset values */
  DAC->SWTRIGR = DAC_SWTRIGR_RESET_VALUE;

  /*  Set the Status registers to their reset values */
  DAC->SR = (uint8_t)~DAC_SR_RESET_VALUE;

  /*  Set the Channel1 Data holding registers to their reset values */
  DAC->CH1RDHRH = DAC_RDHRH_RESET_VALUE;
  DAC->CH1RDHRL = DAC_RDHRL_RESET_VALUE;
  DAC->CH1LDHRH = DAC_LDHRH_RESET_VALUE;
  DAC->CH1LDHRL = DAC_LDHRL_RESET_VALUE;
  DAC->CH1DHR8 = DAC_DHR8_RESET_VALUE;

  /*  Set the Channel2 Data holding registers to their reset values */
  DAC->CH2RDHRH = DAC_RDHRH_RESET_VALUE;
  DAC->CH2RDHRL = DAC_RDHRL_RESET_VALUE;
  DAC->CH2LDHRH = DAC_LDHRH_RESET_VALUE;
  DAC->CH2LDHRL = DAC_LDHRL_RESET_VALUE;
  DAC->CH2DHR8 = DAC_DHR8_RESET_VALUE;

  /*  Set the Dual mode 12bit Right Data holding registers to their reset values */
  DAC->DCH1RDHRH = DAC_RDHRH_RESET_VALUE;
  DAC->DCH1RDHRL = DAC_RDHRL_RESET_VALUE;
  DAC->DCH2RDHRH = DAC_RDHRH_RESET_VALUE;
  DAC->DCH2RDHRL = DAC_RDHRL_RESET_VALUE;

  /*  Set the Dual mode 12bit Left Data holding registers to their reset values */
  DAC->DCH1LDHRH = DAC_LDHRH_RESET_VALUE;
  DAC->DCH1LDHRL = DAC_LDHRL_RESET_VALUE;
  DAC->DCH2LDHRH = DAC_LDHRH_RESET_VALUE;
  DAC->DCH2LDHRL = DAC_LDHRL_RESET_VALUE;

  /*  Set the Dual mode 8bit Data holding registers to their reset values */
  DAC->DCH1DHR8 = DAC_DHR8_RESET_VALUE;
  DAC->DCH2DHR8 = DAC_DHR8_RESET_VALUE;
}

/**
  * @brief  Initializes the DAC according to the specified parameters.
  * @param  DAC_Channel : the selected DAC channel from @ref DAC_Channel_TypeDef
  *         enumeration.
  * @param  DAC_Trigger : the selected DAC trigger from @ref DAC_Trigger_TypeDef
  *         enumeration.
  * @param  DAC_OutputBuffer : the status of DAC load Buffer from
  *         @ref DAC_OutputBuffer_TypeDef enumeration.
  * @retval None
  */
void DAC_Init(DAC_Channel_TypeDef DAC_Channel,
              DAC_Trigger_TypeDef DAC_Trigger,
              DAC_OutputBuffer_TypeDef DAC_OutputBuffer)
{
  uint8_t tmpreg = 0;
  uint16_t tmpreg2 = 0;

  /* Check the DAC parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_TRIGGER(DAC_Trigger));
  assert_param(IS_DAC_OUTPUT_BUFFER_STATE(DAC_OutputBuffer));

  /* Get the DAC CHxCR1 value */
  tmpreg2 =  (uint16_t)((uint8_t)((uint8_t)DAC_Channel << 1));
  tmpreg = *(uint8_t*)((uint16_t)(DAC_BASE + CR1_Offset + tmpreg2));

  /* Clear BOFFx, TENx, TSELx bits */
  tmpreg &= (uint8_t)~(DAC_CR1_BOFF | DAC_CR1_TEN | DAC_CR1_TSEL );

  /* Set BOFFx bit according to DAC_OutputBuffer value */
  tmpreg |= (uint8_t)(DAC_OutputBuffer);


  /* Configure for the selected DAC channel trigger*/
  if (DAC_Trigger != DAC_Trigger_None)
  {
    /* Set TSELx and TEN  bits according to DAC_Trigger value */
    tmpreg |= (uint8_t)(DAC_CR1_TEN | DAC_Trigger) ;
  }

  /* Write to DAC CHxCR1 */
  *(uint8_t*)((uint16_t)(DAC_BASE + CR1_Offset + tmpreg2)) = (uint8_t)tmpreg;
}

/**
  * @brief  Enables or disables DAC Wave Generation according to the specified
  *         parameters.
  * @param  DAC_Channel : the selected DAC channel from @ref DAC_Channel_TypeDef
  *         enumeration.
  * @param  DAC_Wave : the selected waveform from @ref DAC_Wave_TypeDef enumeration.
  * @retval None
  */
void DAC_WaveGenerationCmd(DAC_Channel_TypeDef DAC_Channel,
                           DAC_Wave_TypeDef DAC_Wave,
                           FunctionalState NewState)
{
  uint8_t tmpreg = 0;

  /* Check the DAC parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_WAVE(DAC_Wave));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Get the DAC CHxCR1 value & Clear WAVEN bits */
  tmpreg = (uint8_t)((*(uint8_t*)(uint16_t)(DAC_BASE + CR1_Offset + (uint8_t)((uint8_t)DAC_Channel << 1))) & (uint8_t)~(DAC_CR1_WAVEN));

  if (NewState != DISABLE)
  {
    tmpreg |= (uint8_t)(DAC_Wave);
  }

  /* Write to DAC CHxCR1 */
  (*(uint8_t*) (uint16_t)(DAC_BASE + CR1_Offset +  (uint8_t)((uint8_t)DAC_Channel << 1))) = tmpreg;

}


/**
  * @brief  Select DAC Noise Wave Generation LFSR according to the specified
  *         parameters.
  * @param  DAC_Channel : the selected DAC channel from @ref DAC_Channel_TypeDef
  *         enumeration.
  * @param  DAC_LFSRUnmask : the selected unmasked bit from
  *         @ref DAC_LFSRUnmask_TypeDef enumeration.
  * @retval None
  */
void DAC_NoiseWaveLFSR(DAC_Channel_TypeDef DAC_Channel, DAC_LFSRUnmask_TypeDef DAC_LFSRUnmask)
{
  uint8_t tmpreg = 0;
  uint16_t cr2addr = 0;

  /* Check the DAC parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(DAC_LFSRUnmask));

  /* Get the DAC CHxCR2 value  &  Clear MAMPx bits */
  cr2addr = (uint16_t)(DAC_BASE + CR2_Offset + (uint8_t)((uint8_t)DAC_Channel << 1));
  tmpreg = (uint8_t)((*(uint8_t*)(cr2addr)) & (uint8_t)~(DAC_CR2_MAMPx));

  /* Write to DAC CHxCR2 */
  (*(uint8_t*)(cr2addr)) = (uint8_t)( tmpreg | DAC_LFSRUnmask);
}
/**
  * @brief  Select DAC Triangle Wave Generation Amplitude according
  *         to the specified parameters.
  * @param  DAC_Channel : the selected DAC channel from
  *         @ref DAC_Channel_TypeDef enumeration.
  * @param  DAC_TriangleAmplitude : the selected Amplitude from
  *         @ref DAC_TriangleAmplitude_TypeDef enumeration.
  * @retval None
  */
void DAC_TriangleWaveAmplitude(DAC_Channel_TypeDef DAC_Channel, DAC_TriangleAmplitude_TypeDef DAC_TriangleAmplitude)
{
  uint8_t tmpreg = 0;
  uint16_t cr2addr = 0;

  /* Check the DAC parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(DAC_TriangleAmplitude));


  /* Get the DAC CHxCR2 value  &  Clear MAMPx bits */
  cr2addr = (uint16_t)(DAC_BASE + CR2_Offset + (uint8_t)((uint8_t)DAC_Channel << 1));
  tmpreg = (uint8_t)((*(uint8_t*)(cr2addr)) & (uint8_t)~(DAC_CR2_MAMPx));

  /* Write to DAC CHxCR2 */
  (*(uint8_t*)(cr2addr)) = (uint8_t)( tmpreg | DAC_TriangleAmplitude);
}
/**
  * @brief  Enables or disables the specified DAC channel.
  * @param  DAC_Channel : the selected DAC channel from
  *         @ref DAC_Channel_TypeDef enumeration.
  * @param  NewState : new state of the DAC channel.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_Cmd(DAC_Channel_TypeDef DAC_Channel, FunctionalState NewState)
{
  uint16_t cr1addr = 0;
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Find CHxCR1 register Address */
  cr1addr = DAC_BASE + CR1_Offset + (uint8_t)((uint8_t)DAC_Channel << 1);

  if (NewState != DISABLE)
  {
    /* Enable the selected DAC channel */
    (*(uint8_t*)(cr1addr)) |= DAC_CR1_EN;
  }
  else
  {
    /* Disable the selected DAC channel */
    (*(uint8_t*)(cr1addr)) &= (uint8_t) ~(DAC_CR1_EN);
  }
}

/**
  * @brief  Enables or disables the specified DAC interrupts.
  * @param  DAC_Channel : the selected DAC channel from
  *         @ref DAC_Channel_TypeDef enumeration.
  * @param  DAC_IT : the selected DAC interrupt from
  *         @ref DAC_IT_TypeDef enumeration.
  * @param  NewState : new state of the DAC interrupt .
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_ITConfig(DAC_Channel_TypeDef DAC_Channel, DAC_IT_TypeDef DAC_IT,
                  FunctionalState NewState)
{
  uint16_t cr2addr = 0;

  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_DAC_IT(DAC_IT));

  /* Find CHxCR2 register Address */
  cr2addr = DAC_BASE + CR2_Offset + (uint8_t)((uint8_t)DAC_Channel << 1);

  if (NewState != DISABLE)
  {
    /* Enable the selected DAC interrupts */
    (*(uint8_t*)(cr2addr)) |=  (uint8_t)(DAC_IT);
  }
  else
  {
    /* Disable the selected DAC interrupts */
    (*(uint8_t*)(cr2addr)) &= (uint8_t)(~(DAC_IT));
  }
}

/**
  * @brief  Enables or disables the specified DAC channel DMA request.
  * @param  DAC_Channel : the selected DAC channel from
  *         @ref DAC_Channel_TypeDef enumeration.
  * @param  NewState : new state of the selected DAC channel DMA request.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void DAC_DMACmd(DAC_Channel_TypeDef DAC_Channel, FunctionalState NewState)
{
  uint16_t cr2addr = 0;

  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Find CHxCR2 register Address */
  cr2addr = DAC_BASE + CR2_Offset + (uint8_t)((uint8_t)DAC_Channel << 1);

  if (NewState != DISABLE)
  {
    /* Enable the selected DAC channel DMA request */
    (*(uint8_t*)(cr2addr)) |= DAC_CR2_DMAEN;
  }
  else
  {
    /* Disable the selected DAC channel DMA request */
    (*(uint8_t*)(cr2addr)) &= (uint8_t)~(DAC_CR2_DMAEN);
  }
}

/**
  * @brief  Enables or disables the selected DAC channel software trigger.
  * @param  DAC_Channel : the selected DAC channel from
  *         @ref DAC_Channel_TypeDef enumeration.
  * @param  NewState : new state of the selected DAC channel software trigger.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void DAC_SoftwareTriggerCmd(DAC_Channel_TypeDef DAC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable software trigger for the selected DAC channel */
    DAC->SWTRIGR |= (uint8_t)(DAC_SWTRIGR_SWTRIG1 << DAC_Channel);
  }
  else
  {
    /* Disable software trigger for the selected DAC channel */
    DAC->SWTRIGR &= (uint8_t)~((uint8_t)(DAC_SWTRIGR_SWTRIG1 << DAC_Channel));
  }
}


/**
  * @brief  Enables or disables the dual channel DAC  software triggers.
  * @param  NewState : new state of the  DAC channels software triggers.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void DAC_DualSoftwareTriggerCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable software trigger for both DAC channels */
    DAC->SWTRIGR |= (DAC_SWTRIGR_SWTRIG1 | DAC_SWTRIGR_SWTRIG2) ;
  }
  else
  {
    /* Disable software trigger for both DAC channels */
    DAC->SWTRIGR &= (uint8_t)~(DAC_SWTRIGR_SWTRIG1 | DAC_SWTRIGR_SWTRIG2);
  }
}


/**
  * @brief  Set the specified data holding register value for DAC channel1.
  * @param  DAC_Align : Specifies the data alignement for DAC channel1 from
  *         @ref DAC_Align_TypeDef enumeration.
  * @param  DAC_Data : Data to be loaded in the selected data holding register.
  * @retval None.
  */
void DAC_SetChannel1Data(DAC_Align_TypeDef DAC_Align, uint16_t DAC_Data)
{
  /* Check the parameters */
  assert_param(IS_DAC_ALIGN(DAC_Align));

  if (DAC_Align != DAC_Align_8b_R)
  {
    /* Set the DAC channel1 selected data holding register */
    *(uint8_t*)((uint16_t)(DAC_BASE + CH1RDHRH_Offset + DAC_Align )) = (uint8_t)(((uint16_t)DAC_Data) >> 8);
    *(uint8_t*)((uint16_t)(DAC_BASE + CH1RDHRH_Offset + 1 + DAC_Align )) = (uint8_t)DAC_Data;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_DAC_DATA_08R(DAC_Data));

    /* Set the DAC channel1 selected data holding register */
    DAC->CH1DHR8 = (uint8_t)(DAC_Data);
  }
}

/**
  * @brief  Set the specified data holding register value for DAC channel2.
  * @param  DAC_Align : Specifies the data alignement for DAC channel2 from
  *         @ref DAC_Align_TypeDef enumeration.
  * @param  DAC_Data : Data to be loaded in the selected data holding register.
  * @retval None.
  */
void DAC_SetChannel2Data(DAC_Align_TypeDef DAC_Align, uint16_t DAC_Data)
{
  /* Check the parameters */
  assert_param(IS_DAC_ALIGN(DAC_Align));

  if (DAC_Align != DAC_Align_8b_R)
  {
    /* Set the DAC channel2 selected data holding register */
    *(uint8_t*)((uint16_t)(DAC_BASE + CH2RDHRH_Offset + DAC_Align )) = (uint8_t)(((uint16_t)DAC_Data) >> 8);
    *(uint8_t*)((uint16_t)(DAC_BASE + CH2RDHRH_Offset + 1 + DAC_Align )) = (uint8_t)DAC_Data;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_DAC_DATA_08R(DAC_Data));

    /* Set the DAC channel2 selected data holding register */
    DAC->CH2DHR8 = (uint8_t)(DAC_Data);
  }
}

/**
  * @brief  Set the specified data holding register value for DAC Dual channels data.
  * @param  DAC_Align : Specifies the data alignement for DAC channel2 from
  *         @ref DAC_Align_TypeDef enumeration.
  * @param  DAC_Data2 : Data to be loaded in the selected data holding register
  *         for channel 2.
  * @param  DAC_Data1 : Data to be loaded in the selected data holding register
  *         for channel 1.
  * @retval None.
  */
void DAC_SetDualChannelData(DAC_Align_TypeDef DAC_Align,
                            uint16_t DAC_Data2,
                            uint16_t DAC_Data1)
{
  uint16_t dchxrdhrhaddr = 0;

  /* Check the parameters */
  assert_param(IS_DAC_ALIGN(DAC_Align));

  if (DAC_Align != DAC_Align_8b_R)
  {
    /* Identify the DCHxRDHRH address*/
    dchxrdhrhaddr = (uint16_t)(DAC_BASE + DCH1RDHRH_Offset + DAC_Align);

    /* Set the DAC channels Dual data holding registers */
    *(uint8_t*)(uint16_t)dchxrdhrhaddr = (uint8_t)(((uint16_t)DAC_Data1) >> 8);
    *(uint8_t*)(uint16_t)(dchxrdhrhaddr + 1) = (uint8_t)DAC_Data1;
    *(uint8_t*)(uint16_t)(dchxrdhrhaddr + 2) = (uint8_t)(((uint16_t)DAC_Data2) >> 8);
    *(uint8_t*)(uint16_t)(dchxrdhrhaddr + 3) = (uint8_t)DAC_Data2;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_DAC_DATA_08R(DAC_Data1 | DAC_Data2));

    /* Set the DAC channels Dual data holding registers */
    DAC->DCH1DHR8 = (uint8_t)(DAC_Data1);
    DAC->DCH2DHR8 = (uint8_t)(DAC_Data2);
  }
}
/**
  * @brief  Returns the last data output value of the selected DAC channel.
  * @param  DAC_Channel : the selected DAC channel from @ref DAC_Channel_TypeDef
  *         enumeration.
  * @retval The selected DAC channel data output value.
  */
uint16_t DAC_GetDataOutputValue(DAC_Channel_TypeDef DAC_Channel)
{
  uint16_t outputdata = 0;
  uint16_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));

  if ( DAC_Channel ==  DAC_Channel_1)
  {
    /* Returns the DAC channel data output register value */
    tmp = (uint16_t)((uint16_t)DAC->CH1DORH << 8);
    outputdata = (uint16_t)(tmp | (DAC->CH1DORL));
  }
  else
  {
    /* Returns the DAC channel data output register value */
    tmp = (uint16_t)((uint16_t)DAC->CH2DORH << 8);
    outputdata = (uint16_t)(tmp | (DAC->CH2DORL));
  }

  /* return the selected DAC channel data output value.*/
  return (uint16_t)outputdata;
}
/**
  * @brief  Checks whether the specified DAC flag is set or not.
  * @param  DAC_Channel : the selected DAC channel from @ref DAC_Channel_TypeDef
  *         enumeration.
  * @param  DAC_FLAG : specifies the flag to check from @ref DAC_FLAG_TypeDef
  *         enumeration.
  * @retval FlagStatus The new state of DAC_FLAG (SET or RESET).
  */
FlagStatus DAC_GetFlagStatus(DAC_Channel_TypeDef DAC_Channel, DAC_FLAG_TypeDef DAC_FLAG)
{
  FlagStatus flagstatus = RESET;
  uint8_t flag = 0;

  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_FLAG(DAC_FLAG));

  flag = (uint8_t)(DAC_FLAG << DAC_Channel);

  /* Check the status of the specified DAC flag */
  if ((DAC->SR & flag ) != (uint8_t)RESET)
  {
    /* DAC FLAG is set */
    flagstatus = SET;
  }
  else
  {
    /* DAC FLAG is reset */
    flagstatus = RESET;
  }

  /* Return the DAC FLAG status */
  return  flagstatus;
}

/**
  * @brief  Clears the DAC channelx's pending flags.
  * @param  DAC_Channel : the selected DAC channel from @ref DAC_Channel_TypeDef
  *         enumeration.
  * @param  DAC_FLAG : specifies the flag to clear from @ref DAC_FLAG_TypeDef
  *         enumeration.
  * @retval None.
  */
void DAC_ClearFlag(DAC_Channel_TypeDef DAC_Channel, DAC_FLAG_TypeDef DAC_FLAG)
{
  uint8_t flag = 0;

  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_FLAG(DAC_FLAG));

  /* identify the selected flag*/
  flag = (uint8_t)(DAC_FLAG << DAC_Channel);

  /* Clear the selected DAC flag */
  DAC->SR = (uint8_t)(~flag);
}
/**
  * @brief  Checks whether the specified DAC interrupt has occurred or not.
  * @param  DAC_Channel : the selected DAC channel from @ref DAC_Channel_TypeDef
  *         enumeration.
  * @param  DAC_IT : specifies the DAC interrupt source to check from
  *         @ref DAC_IT_TypeDef enumeration.
  * @retval ITStatus The new state of DAC_IT (SET or RESET).
  */
ITStatus DAC_GetITStatus(DAC_Channel_TypeDef DAC_Channel, DAC_IT_TypeDef DAC_IT)
{
  ITStatus itstatus = RESET;
  uint8_t enablestatus = 0;
  uint8_t flagstatus = 0;
  uint8_t tempreg = 0;

  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_IT(DAC_IT));

  /* identify the status of the IT and its correspondent flag*/
  tempreg = *(uint8_t*)(uint16_t)(DAC_BASE + CR2_Offset + (uint8_t)((uint8_t)DAC_Channel << 2));
  enablestatus = (uint8_t)( tempreg & (uint8_t)((uint8_t)DAC_IT << DAC_Channel));
  flagstatus = (uint8_t)(DAC->SR & (uint8_t)(DAC_IT >> ((uint8_t)0x05 - DAC_Channel)));

  /* Check the status of the specified DAC interrupt */
  if (((flagstatus) != (uint8_t)RESET) && enablestatus)
  {
    /* DAC IT is set */
    itstatus = SET;
  }
  else
  {
    /* DAC IT is reset */
    itstatus = RESET;
  }

  /* Return the DAC IT status */
  return  itstatus;
}

/**
  * @brief   Clears the DAC channelx’s interrupt pending bits.
  * @param  DAC_Channel : the selected DAC channel from @ref DAC_Channel_TypeDef
  *         enumeration.
  * @param  DAC_IT : specifies the DAC interrupt pending bit to clear from
  *         @ref DAC_IT_TypeDef enumeration.
  * @retval None.
  */
void DAC_ClearITPendingBit(DAC_Channel_TypeDef DAC_Channel, DAC_IT_TypeDef DAC_IT)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_IT(DAC_IT));

  /* Clear the selected DAC interrupt pending bits */
  DAC->SR = (uint8_t)~(uint8_t)((uint8_t)DAC_IT >> (0x05 - DAC_Channel));
}

/**
    * @}
    */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
