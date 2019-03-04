/**
  ******************************************************************************
  * @file    stm8l15x_clk.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    09/24/2010
  * @brief   This file provides all the CLK firmware functions.
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

#include "stm8l15x_clk.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @addtogroup CLK_Private_Constants
  * @{
  */

__CONST uint8_t SYSDivFactor[5] =
  {
    1, 2, 4, 8, 16
  }
  ; /*!< Holds the different Master clock Divider factors */

/**
  * @}
  */

/**
  * @addtogroup CLK_Public_Functions
  * @{
  */

/**
  * @brief  Deinitializes the CLK peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void CLK_DeInit(void)
{
  CLK->ICKCR = CLK_ICKCR_RESET_VALUE;
  CLK->ECKCR = CLK_ECKCR_RESET_VALUE;
  CLK->CRTCR = CLK_CRTCR_RESET_VALUE;
  CLK->CBEEPR = CLK_CBEEPR_RESET_VALUE;
  CLK->SWR  = CLK_SWR_RESET_VALUE;
  CLK->SWCR = CLK_SWCR_RESET_VALUE;
  CLK->CKDIVR = CLK_CKDIVR_RESET_VALUE;
  CLK->PCKENR1 = CLK_PCKENR1_RESET_VALUE;
  CLK->PCKENR2 = CLK_PCKENR2_RESET_VALUE;
  CLK->PCKENR3 = CLK_PCKENR3_RESET_VALUE;
  CLK->CSSR = CLK_CSSR_RESET_VALUE;
  CLK->CCOR = CLK_CCOR_RESET_VALUE;
  CLK->HSITRIMR = CLK_HSITRIMR_RESET_VALUE;
  CLK->HSICALR = CLK_HSICALR_RESET_VALUE;
  CLK->HSIUNLCKR = CLK_HSIUNLCKR_RESET_VALUE;
  CLK->REGCSR = CLK_REGCSR_RESET_VALUE;
}

/**
  * @brief  Enables or disables the Internal High Speed oscillator (HSI).
  * @param  NewState : new state of HSI, value accepted ENABLE, DISABLE.
  * @retval None
  */
void CLK_HSICmd(FunctionalState NewState)
{

  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set HSION bit */
    CLK->ICKCR |= CLK_ICKCR_HSION;
  }
  else
  {
    /* Reset HSION bit */
    CLK->ICKCR &= (uint8_t)(~CLK_ICKCR_HSION);
  }
}

/**
  * @brief  Adjusts the Internal High Speed oscillator (HSI) calibration value.
  * @param  CLK_HSICalibrationValue : calibration trimming value.
  * @retval None
  */
void CLK_AdjustHSICalibrationValue(uint8_t CLK_HSICalibrationValue)
{
  /* two consecutive write access to HSIUNLCKR register to unlock HSITRIMR */
  CLK->HSIUNLCKR = 0xAC;
  CLK->HSIUNLCKR = 0x35;

  /* Store the new value */
  CLK->HSITRIMR = (uint8_t)CLK_HSICalibrationValue;
}

/**
  * @brief  Enables or disables the Internal Low Speed oscillator (LSI).
  * @param  NewState : new state of LSI, value accepted ENABLE, DISABLE.
  * @retval None
  */
void CLK_LSICmd(FunctionalState NewState)
{

  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set LSION bit */
    CLK->ICKCR |= CLK_ICKCR_LSION;
  }
  else
  {
    /* Reset LSION bit */
    CLK->ICKCR &= (uint8_t)(~CLK_ICKCR_LSION);
  }
}

/**
  * @brief  Configures the HSE Clock source.
  * @note   In case of Enabling HSE Bypass be sure
  *         that SWI, CKM and Clock RTC are not using HSE as clock source
  * @param  CLK_HSE : This parameter specifies the HSE clock configuarton.
  *         This parameter can be a value of @ref CLK_HSE_TypeDef.
  * @retval None
  */
void CLK_HSEConfig(CLK_HSE_TypeDef CLK_HSE)
{
  /* Check the parameters */
  assert_param(IS_CLK_HSE(CLK_HSE));

  /* Reset HSEON and HSEBYP bits before configuring the HSE ------------------*/
  /* Reset HSEON bit */
  CLK->ECKCR &= (uint8_t)~CLK_ECKCR_HSEON;

  /* Reset HSEBYP bit */
  CLK->ECKCR &= (uint8_t)~CLK_ECKCR_HSEBYP;

  /* Configure HSE */
  CLK->ECKCR |= (uint8_t)CLK_HSE;
}

/**
  * @brief  Configures the LSE Clock source.
  * @note   In case of Enabling LSE ByPass be sure that SWI, CKM
  *        and Clock RTC are not using LSE as clock source
  * @param  CLK_LSE : This parameter specifies the LSE clock configuarton.
  *         This parameter can be a value of @ref CLK_ConfigLSE_TypeDef.
  * @retval None
  */
void CLK_LSEConfig(CLK_LSE_TypeDef CLK_LSE)
{
  /* Check the parameters */
  assert_param(IS_CLK_LSE(CLK_LSE));

  /* Reset LSEON and LSEBYP bits before configuring the LSE ------------------*/
  /* Reset LSEON bit */
  CLK->ECKCR &= (uint8_t)~CLK_ECKCR_LSEON;

  /* Reset LSEBYP bit */
  CLK->ECKCR &= (uint8_t)~CLK_ECKCR_LSEBYP;

  /* Configure LSE */
  CLK->ECKCR |= (uint8_t)CLK_LSE;

}

/**
  * @brief  Configures the System clock (SYSCLK) source.
  * @param  CLK_SYSCLKSource : Specifies the new clock.
  *         This parameter can be a value of @ref CLK_SYSCLKSource_TypeDef.
  * @retval None
  */
void CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_TypeDef CLK_SYSCLKSource)
{
  /* check teh parameters */
  assert_param(IS_CLK_SOURCE(CLK_SYSCLKSource));

  /* Selection of the target clock source */
  CLK->SWR = (uint8_t)CLK_SYSCLKSource;
}

/**
  * @brief Configures the System clock (SYSCLK) dividers.
  * @param CLK_SYSCLKDiv : Specifies the system clock divider to apply.
  *        This parameter can be a value of @ref CLK_SYSCLKDiv_TypeDef.
  * @retval None
  */
void CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_TypeDef CLK_SYSCLKDiv)
{
  /* check the parameters */
  assert_param(IS_CLK_SYSTEM_DIVIDER(CLK_SYSCLKDiv));

  CLK->CKDIVR = (uint8_t)(CLK_SYSCLKDiv);
}
/**
  * @brief  Enables or disables the clock switch execution.
  * @param  NewState : new state of clock switch, value accepted ENABLE, DISABLE.
  * @retval None
  */
void CLK_SYSCLKSourceSwitchCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set SWEN bit */
    CLK->SWCR |= CLK_SWCR_SWEN;
  }
  else
  {
    /* Reset SWEN  bit */
    CLK->SWCR &= (uint8_t)(~CLK_SWCR_SWEN);
  }
}

/**
  * @brief  Returns the clock source used as system clock.
  * @param  None
  * @retval Clock used as System clock (SYSCLK) source.
  *         The returned value can be one of the following:
  *         - CLK_SYSCLKSource_HSI: HSI used as system clock
  *         - CLK_SYSCLKSource_LSI: LSI used as system clock
  *         - CLK_SYSCLKSource_HSE: HSE used as system clock
  *         - CLK_SYSCLKSource_LSE: LSE used as system clock
  */
CLK_SYSCLKSource_TypeDef CLK_GetSYSCLKSource(void)
{
  return ((CLK_SYSCLKSource_TypeDef)(CLK->SCSR));
}

/**
  * @brief  Enables the Clock Security System.
  * @note   Once CSS is enabled it cannot be disabled until the next reset.
  * @param  None
  * @retval None
  */
void CLK_ClockSecuritySystemEnable(void)
{
  /* Set CSSEN bit */
  CLK->CSSR |= CLK_CSSR_CSSEN;
}

/**
  * @brief  Enables the Clock Security System deglitcher system.
  * @param  None
  * @retval None
  */
void CLK_ClockSecuritySytemDeglitchCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set CSSDGON bit */
    CLK->CSSR |= CLK_CSSR_CSSDGON;
  }
  else
  {
    /* Reset CSSDGON  bit */
    CLK->CSSR &= (uint8_t)(~CLK_CSSR_CSSDGON);
  }
}
/**
  * @brief  Returns the frequency of the System clock (SYSCLK).
  * @param  None
  * @retval System clock (SYSCLK) frequency
  */
uint32_t CLK_GetClockFreq(void)
{
  uint32_t clockfrequency = 0;
  uint32_t sourcefrequency = 0;
  CLK_SYSCLKSource_TypeDef clocksource = CLK_SYSCLKSource_HSI;
  uint8_t tmp = 0, presc = 0;

  /* Get SYSCLK source. */
  clocksource = (CLK_SYSCLKSource_TypeDef)CLK->SCSR;

  if ( clocksource == CLK_SYSCLKSource_HSI)
  {
    sourcefrequency = HSI_VALUE;
  }
  else if ( clocksource == CLK_SYSCLKSource_LSI)
  {
    sourcefrequency = LSI_VALUE;
  }
  else if ( clocksource == CLK_SYSCLKSource_HSE)
  {
    sourcefrequency = HSE_VALUE;
  }
  else
  {
    clockfrequency = LSE_VALUE;
  }

  /* Get System clock divider factor*/
  tmp = (uint8_t)(CLK->CKDIVR & CLK_CKDIVR_CKM);
  presc = SYSDivFactor[tmp];

  /* Get System clock clcok frequency */
  clockfrequency = sourcefrequency / presc;

  return((uint32_t)clockfrequency);
}


/**
  * @brief  Enables or disables the specified CLK interrupts.
  * @param  CLK_IT : Specifies the interrupt sources.
  *         This parameter can be a value of @ref CLK_IT_TypeDef.
  * @param  NewState : New state of the Interrupt, value accepted ENABLE, DISABLE.
  * @retval None
  */
void CLK_ITConfig(CLK_IT_TypeDef CLK_IT, FunctionalState NewState)
{

  /* check the parameters */
  assert_param(IS_CLK_IT(CLK_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    if (CLK_IT == CLK_IT_SWIF)
    {
      /* Enable the clock switch interrupt */
      CLK->SWCR |= CLK_SWCR_SWIEN;
    }
    else if (CLK_IT == CLK_IT_LSECSSF)
    {
      /* Enable the CSS on LSE  interrupt */
      CSSLSE->CSR |= CSSLSE_CSR_CSSIE;
    }
    else
    {
      /* Enable the clock security system detection interrupt */
      CLK->CSSR |= CLK_CSSR_CSSDIE;
    }
  }
  else  /*(NewState == DISABLE)*/
  {
    if (CLK_IT == CLK_IT_SWIF)
    {
      /* Disable the clock switch interrupt */
      CLK->SWCR  &= (uint8_t)(~CLK_SWCR_SWIEN);
    }
    else if (CLK_IT == CLK_IT_LSECSSF)
    {
      /* Disable the CSS on LSE  interrupt */
      CSSLSE->CSR &= (uint8_t)(~CSSLSE_CSR_CSSIE);
    }
    else
    {
      /* Disable the clock security system detection interrupt */
      CLK->CSSR &= (uint8_t)(~CLK_CSSR_CSSDIE);
    }
  }
}

/**
  * @brief  Selects the clock source to output on CCO pin.
  * @param  CLK_CCOSource : Specifies the clock source.
  *         This parameter can be a value of @ref CLK_CCOSource_TypeDef.
  * @param  CLK_CCODiv : Specifies the clock source divider.
  *         This parameter can be a value of @ref CLK_CCODiv_TypeDef.
  * @retval None
  */
void CLK_CCOConfig(CLK_CCOSource_TypeDef CLK_CCOSource, CLK_CCODiv_TypeDef CLK_CCODiv)
{
  /* check teh parameters */
  assert_param(IS_CLK_OUTPUT(CLK_CCOSource));
  assert_param(IS_CLK_OUTPUT_DIVIDER(CLK_CCODiv));

  /* Selects the source provided on cco_ck output and its divider*/
  CLK->CCOR = (uint8_t)((uint8_t)CLK_CCOSource | (uint8_t)CLK_CCODiv);
}

/**
  * @brief  Configures the RTC clock source.
  * @param  CLK_RTCCLKSource : Specifies the RTC clock source.
  *         This parameter can be a value of @ref CLK_RTCCLKSource_TypeDef.
  * @param  CLK_RTCCLKDiv : Specifies the RTC clock source divider.
  *         This parameter can be a value of @ref CLK_RTCCLKDiv_TypeDef.
  * @retval None
  */
void CLK_RTCClockConfig(CLK_RTCCLKSource_TypeDef CLK_RTCCLKSource, CLK_RTCCLKDiv_TypeDef CLK_RTCCLKDiv)
{
  /* check the parameters */
  assert_param(IS_CLK_CLOCK_RTC(CLK_RTCCLKSource));
  assert_param(IS_CLK_CLOCK_RTC_DIV(CLK_RTCCLKDiv));

  /* Selects the source provided on to RTC and its divider*/
  CLK->CRTCR = (uint8_t)((uint8_t)CLK_RTCCLKSource | (uint8_t)CLK_RTCCLKDiv);
}

/**
  * @brief  Configures the BEEP clock source.
  * @param  CLK_BEEPCLKSource : Specifies the BEEP clock source.
  *         This parameter can be a value of @ref CLK_BEEPCLKSource_TypeDef.
  * @retval None
  */
void CLK_BEEPClockConfig(CLK_BEEPCLKSource_TypeDef CLK_BEEPCLKSource)
{
  /* check the parameters */
  assert_param(IS_CLK_CLOCK_BEEP(CLK_BEEPCLKSource));

  /* Selects the source provided to BEEP*/
  CLK->CBEEPR = (uint8_t)(CLK_BEEPCLKSource);

}

/**
  * @brief  Enables or disables the specified peripheral clock.
  * @param  CLK_Peripheral : This parameter specifies the peripheral clock to gate.
  *         This parameter can be a value of @ref CLK_Peripheral_TypeDef.
  * @param  NewState : New state of specified peripheral clock.
  *         This parameter can be a value of @ref FunctionalState.
  * @retval None
  */
void CLK_PeripheralClockConfig(CLK_Peripheral_TypeDef CLK_Peripheral, FunctionalState NewState)
{
  uint8_t reg = 0;

  /* Check the parameters */
  assert_param(IS_CLK_PERIPHERAL(CLK_Peripheral));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* get flag register */
  reg = (uint8_t)((uint8_t)CLK_Peripheral & (uint8_t)0xF0);

  if ( reg == 0x00)
  {
    if (NewState != DISABLE)
    {
      /* Enable the peripheral Clock */
      CLK->PCKENR1 |= (uint8_t)((uint8_t)1 << ((uint8_t)CLK_Peripheral & (uint8_t)0x0F));
    }
    else
    {
      /* Disable the peripheral Clock */
      CLK->PCKENR1 &= (uint8_t)(~(uint8_t)(((uint8_t)1 << ((uint8_t)CLK_Peripheral & (uint8_t)0x0F))));
    }
  }
  else if (reg == 0x10)
  {
    if (NewState != DISABLE)
    {
      /* Enable the peripheral Clock */
      CLK->PCKENR2 |= (uint8_t)((uint8_t)1 << ((uint8_t)CLK_Peripheral & (uint8_t)0x0F));
    }
    else
    {
      /* Disable the peripheral Clock */
      CLK->PCKENR2 &= (uint8_t)(~(uint8_t)(((uint8_t)1 << ((uint8_t)CLK_Peripheral & (uint8_t)0x0F))));
    }
  }
  else
  {
    if (NewState != DISABLE)
    {
      /* Enable the peripheral Clock */
      CLK->PCKENR3 |= (uint8_t)((uint8_t)1 << ((uint8_t)CLK_Peripheral & (uint8_t)0x0F));
    }
    else
    {
      /* Disable the peripheral Clock */
      CLK->PCKENR3 &= (uint8_t)(~(uint8_t)(((uint8_t)1 << ((uint8_t)CLK_Peripheral & (uint8_t)0x0F))));
    }
  }
}

/**
  * @brief  Configures clock during halt and active halt modes.
  * @param  CLK_Halt : Specifies the clock state and wake-up mode from halt way.
  *         This parameter can be a value of @ref CLK_Halt_TypeDef.
  * @param  NewState : Specifies the System clock (SYSCLK) state in active halt mode.
  *         This parameter can be ENABLE or DISABLE.
  * @retval None
  */
void CLK_HaltConfig(CLK_Halt_TypeDef CLK_Halt, FunctionalState NewState)
{
  /* check the parameters */
  assert_param(IS_CLK_HALT(CLK_Halt));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    CLK->ICKCR |= (uint8_t)(CLK_Halt);
  }
  else
  {
    CLK->ICKCR &= (uint8_t)(~CLK_Halt);
  }
}

/**
  * @brief  Configures the main voltage regulator
  * @param  NewState: specifies the MVR  state.
  *         This parameter can be one of the following values:
  *         - DISABLE: MVR disabled;
  *         - ENABLE:  MVR enabled.
  * @retval None
  */
void CLK_MainRegulatorCmd(FunctionalState NewState)
{
  /* check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Reset REGUOFF bit */
    CLK->REGCSR &= (uint8_t)(~CLK_REGCSR_REGOFF);
  }
  else
  {
    /* Set REGUOFF bit */
    CLK->REGCSR |= CLK_REGCSR_REGOFF;
  }
}

/**
  * @brief  Checks whether the specified CLK flag is set or not.
  * @param  CLK_FLAG : Flag to check. This parameter can be a value of @ref CLK_FLAG_TypeDef
  * @retval FlagStatus : status of the checked flag
  */
FlagStatus CLK_GetFlagStatus(CLK_FLAG_TypeDef CLK_FLAG)
{
  uint8_t reg = 0;
  uint8_t pos = 0;
  FlagStatus bitstatus = RESET;

  /* check the parameters */
  assert_param(IS_CLK_FLAGS(CLK_FLAG));

  /* get flag register */
  reg = (uint8_t)((uint8_t)CLK_FLAG & (uint8_t)0xF0);

  /* get flag position */
  pos = (uint8_t)((uint8_t)CLK_FLAG & (uint8_t)0x0F);

  if (reg == 0x00) /* The flag to check is in CRTC Rregister */
  {
    reg = CLK->CRTCR;
  }
  else if (reg == 0x10) /* The flag to check is in ICKCR register */
  {
    reg = CLK->ICKCR;
  }
  else if (reg == 0x20) /* The flag to check is in CCOR register */
  {
    reg = CLK->CCOR;
  }
  else if (reg == 0x30) /* The flag to check is in ECKCR register */
  {
    reg = CLK->ECKCR;
  }
  else if (reg == 0x40) /* The flag to check is in SWCR register */
  {
    reg = CLK->SWCR;
  }
  else if (reg == 0x50) /* The flag to check is in CSSR register */
  {
    reg = CLK->CSSR;
  }
  else if (reg == 0x70) /* The flag to check is in REGCSR register */
  {
    reg = CLK->REGCSR;
  }
  else if (reg == 0x80) /* The flag to check is in CSSLSE_CSRregister */
  {
    reg = CSSLSE->CSR;
  }
  else /* The flag to check is in CBEEPR register */
  {
    reg = CLK->CBEEPR;
  }


  if ((reg & (uint8_t)((uint8_t)1 << (uint8_t)pos)) != (uint8_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  /* Return the flag status */
  return((FlagStatus)bitstatus);
}

/**
  * @brief  Clears the CSS LSE Flag.
  * @param  None
  * @retval None
  */
void CLK_ClearFlag(void)
{

  /* Clear the clock security system on LSE  dtetction Flag */
  CSSLSE->CSR &= (uint8_t)(~CSSLSE_CSR_CSSF);
}

/**
  * @brief  Checks whether the specified CLK interrupt has is enabled or not.
  * @param  CLK_IT : specifies the CLK interrupt.
  *         This parameter can be a value of @ref CLK_IT_TypeDef
  * @retval ITStatus : state of CLK_IT (SET or RESET).
  */
ITStatus CLK_GetITStatus(CLK_IT_TypeDef CLK_IT)
{

  ITStatus bitstatus = RESET;

  /* check the parameters */
  assert_param(IS_CLK_IT(CLK_IT));

  if (CLK_IT == CLK_IT_SWIF)
  {
    /* Check the status of the clock switch interrupt */
    if ((CLK->SWCR & (uint8_t)CLK_IT) == (uint8_t)0x0C)
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }
  else if (CLK_IT == CLK_IT_LSECSSF)
  {
    /* Check the status of the clock security system on LSE interrupt */
    if ((CSSLSE->CSR & (uint8_t)CLK_IT) == (uint8_t)0x0C)
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }
  else /* CLK_IT == CLK_IT_CSSD */
  {
    /* Check the status of the security system detection interrupt */
    if ((CLK->CSSR & (uint8_t)CLK_IT) == (uint8_t)0x0C)
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }

  /* Return the CLK_IT status */
  return bitstatus;
}


/**
  * @brief  Clears the CLK’s interrupt pending bits.
  * @param  CLK_IT : specifies the interrupt pending bits.
  *         This parameter can be a value of CLK_IT_TypeDef
  * @retval None
  */
void CLK_ClearITPendingBit(CLK_IT_TypeDef CLK_IT)
{

  /* check the parameters */
  assert_param(IS_CLK_CLEAR_IT(CLK_IT));

  if ((uint8_t)((uint8_t)CLK_IT & (uint8_t)0xF0) == (uint8_t)0x20)
  {
    /* Clear the status of the clock security system on LSE interrupt */
    CSSLSE->CSR &= (uint8_t)(~CSSLSE_CSR_CSSF);
  }
  else
  {
    /* Clear the status of the clock switch interrupt */
    CLK->SWCR &= (uint8_t)(~CLK_SWCR_SWIF);
  }
}

/**
  * @brief  Enables the clock CSS on LSE.
  * @note   Once Enabled, only POR can Disable it.
  * @param  None
  * @retval None
  */
void CLK_LSEClockSecuritySystemEnable(void)
{
  /* Set CSSEN bit */
  CSSLSE->CSR |= CSSLSE_CSR_CSSEN;
}

/**
  * @brief  Enables RTC clock switch to LSI in case of LSE failure.
  * @note   Once Enabled, only POR can Disable it.
  * @param  None
  * @retval None
  */
void CLK_RTCCLKSwitchOnLSEFailureEnable(void)
{
  /* Set SWITCHEN bit */
  CSSLSE->CSR |= CSSLSE_CSR_SWITCHEN;
}


/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
