/**
  * @brief  Function to help to configure DMA transfer from ADC: retrieve the
  *         ADC register address from ADC instance and a list of ADC registers
  *         intended to be used (most commonly) with DMA transfer.
  * @note   These ADC registers are data registers:
  *         when ADC conversion data is available in ADC data registers,
  *         ADC generates a DMA transfer request.
  * @note   This macro is intended to be used with LL DMA driver, refer to
  *         function "LL_DMA_ConfigAddresses()".
  *         Example:
  *           LL_DMA_ConfigAddresses(DMA1,
  *                                  LL_DMA_CHANNEL_1,
  *                                  LL_ADC_DMA_GetRegAddr(ADC1, LL_ADC_DMA_REG_REGULAR_DATA),
  *                                  (uint32_t)&< array or variable >,
  *                                  LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
  * @note   For devices with several ADC: in multimode, some devices
  *         use a different data register outside of ADC instance scope
  *         (common data register). This macro manages this register difference,
  *         only ADC instance has to be set as parameter.
  * @rmtoll DR       RDATA          LL_ADC_DMA_GetRegAddr\n
  *         CDR      RDATA_MST      LL_ADC_DMA_GetRegAddr\n
  *         CDR      RDATA_SLV      LL_ADC_DMA_GetRegAddr
  * @param  ADCx ADC instance
  * @param  Register This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DMA_REG_REGULAR_DATA
  *         @arg @ref LL_ADC_DMA_REG_REGULAR_DATA_MULTI (1)
  *         
  *         (1) Available on devices with several ADC instances.
  * @retval ADC register address
  */

__STATIC_INLINE uint32_t LL_ADC_DMA_GetRegAddr(ADC_TypeDef *ADCx, uint32_t Register)
{
  register uint32_t data_reg_addr = 0U;
  
  if (Register == LL_ADC_DMA_REG_REGULAR_DATA)
  {
    /* Retrieve address of register DR */
    data_reg_addr = (uint32_t)&(ADCx->DR);
  }

  else /* (Register == LL_ADC_DMA_REG_REGULAR_DATA_MULTI) */
  {
    /* Retrieve address of register CDR */
    data_reg_addr = (uint32_t)&((__LL_ADC_COMMON_INSTANCE(ADCx))->CDR);
  }
  
  return data_reg_addr;
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_Common Configuration of ADC hierarchical scope: common to several ADC instances
  * @{
  */

/**
  * @brief  Set parameter common to several ADC: Clock source and prescaler.
  * @rmtoll CCR      ADCPRE         LL_ADC_SetCommonClock
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @param  CommonClock This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CLOCK_SYNC_PCLK_DIV2
  *         @arg @ref LL_ADC_CLOCK_SYNC_PCLK_DIV4
  *         @arg @ref LL_ADC_CLOCK_SYNC_PCLK_DIV6
  *         @arg @ref LL_ADC_CLOCK_SYNC_PCLK_DIV8
  * @retval None
  */

__STATIC_INLINE void LL_ADC_SetCommonClock(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t CommonClock)
{
  MODIFY_REG(ADCxy_COMMON->CCR, ADC_CCR_ADCPRE, CommonClock);
}


/**
  * @brief  Get parameter common to several ADC: Clock source and prescaler.
  * @rmtoll CCR      ADCPRE         LL_ADC_GetCommonClock
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CLOCK_SYNC_PCLK_DIV2
  *         @arg @ref LL_ADC_CLOCK_SYNC_PCLK_DIV4
  *         @arg @ref LL_ADC_CLOCK_SYNC_PCLK_DIV6
  *         @arg @ref LL_ADC_CLOCK_SYNC_PCLK_DIV8
  */

__STATIC_INLINE uint32_t LL_ADC_GetCommonClock(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(READ_BIT(ADCxy_COMMON->CCR, ADC_CCR_ADCPRE));
}

