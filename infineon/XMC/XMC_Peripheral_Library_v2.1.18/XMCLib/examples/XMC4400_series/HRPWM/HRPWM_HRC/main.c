/*******************************************************************************
 Copyright (c) 2014, Infineon Technologies AG                                 **
 All rights reserved.                                                         **
                                                                              **
 Redistribution and use in source and binary forms, with or without           **
 modification,are permitted provided that the following conditions are met:   **
                                                                              **
 *Redistributions of source code must retain the above copyright notice,      **
 this list of conditions and the following disclaimer.                        **
 *Redistributions in binary form must reproduce the above copyright notice,   **
 this list of conditions and the following disclaimer in the documentation    **
 and/or other materials provided with the distribution.                       **
 *Neither the name of the copyright holders nor the names of its contributors **
 may be used to endorse or promote products derived from this software without**
 specific prior written permission.                                           **
                                                                              **
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  **
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    **
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   **
 ARE  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE   **
 LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         **
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         **
 SUBSTITUTE GOODS OR  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    **
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      **
 CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)       **
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   **
 POSSIBILITY OF SUCH DAMAGE.                                                  **
                                                                              **
 To improve the quality of the software, users are encouraged to share        **
 modifications, enhancements or bug fixes with Infineon Technologies AG       **
 dave@infineon.com).                                                          **
                                                                              **
*******************************************************************************/

/**
 * @file
 * @date 16 Jan, 2015
 * @version 1.0.0
 *
 * @brief HRPWM demo example
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 */

#include <xmc_ccu8.h>
#include <xmc_scu.h>
#include <xmc_hrpwm.h>
#include <xmc_gpio.h>

/*********************************************************************************************************************
 * MACROS
 ********************************************************************************************************************/
#define CCU8_SLICE         CCU80_CC80
#define CCU8_MODULE        CCU80
#define MODULE_NUMBER     (0U)
#define SLICE_NUMBER      (0U)
#define CAPCOM_MASK       (0x100U) /**< Only CCU80 */
#define HROUT0_PIN        P0_5
#define HROUT1_PIN        P0_2


/*********************************************************************************************************************
 * GLOBAL DATA
 ********************************************************************************************************************/
/* Initialization data of the complete slice - It includes Timer and Capture init data */
XMC_CCU8_SLICE_COMPARE_CONFIG_t g_capcom_slice_object =
{
  .tc = 0x00000401,// 00 0000 0000 0100 0000 0001,
  .psl = 0,
  .chc = 0,
  .prescaler_initval = 0,
  .dither_limit = 0,
  .float_limit = 0,
  .timer_concatenation = 0
};


XMC_HRPWM_HRC_CONFIG_t hrc0_config =
{
  .hr_out0_inv_enable = 0,
  .hr_out1_inv_enable = 0,
  .hr_out0_trap_enable = (uint32_t)(XMC_HRPWM_FUNC_STATUS_DISABLE),
  .hr_out1_trap_enable = (uint32_t)(XMC_HRPWM_FUNC_STATUS_DISABLE),
  .hrc_shadow_xfer_linktoCCU8 = (uint32_t)(XMC_HRPWM_FUNC_STATUS_ENABLE),
  .dt_shadow_xfer_linktoCCU8 = (uint32_t)(XMC_HRPWM_FUNC_STATUS_ENABLE),
  .dt_enable = (uint32_t)(XMC_HRPWM_FUNC_STATUS_ENABLE),
  .dt_trigger_sel = 0,
  .hr_out0_passive_level_out = 0,
  .hr_out1_passive_level_out = 0
};

const XMC_HRPWM_HRC_SRC_CONFIG_t hrc0_source0 =
{
  .high_res_mode = XMC_HRPWM_HRC_HR_EDGE_SEL_BOTH,
  .set_config = XMC_HRPWM_HRC_SRC_INPUT_CCU,
  .clear_config = XMC_HRPWM_HRC_SRC_INPUT_CCU,
  .cmp_set = XMC_HRPWM_HRC_CMP_SEL_CSG0,
  .cmp_clear = XMC_HRPWM_HRC_CMP_SEL_CSG0,
  .timer_sel = XMC_HRPWM_HRC_TIMER_SEL_CCU_CC0,
  .set_edge_config = XMC_HRPWM_HRC_SRC_EDGE_SEL_RISING,
  .clear_edge_config = XMC_HRPWM_HRC_SRC_EDGE_SEL_FALLING,
  .src_trap_enable = XMC_HRPWM_FUNC_STATUS_DISABLE,
};

const XMC_HRPWM_HRC_SRC_CONFIG_t hrc0_source1 =
{
  .high_res_mode = XMC_HRPWM_HRC_HR_EDGE_SEL_BOTH,
  .set_config = XMC_HRPWM_HRC_SRC_INPUT_CCU,
  .clear_config = XMC_HRPWM_HRC_SRC_INPUT_CCU,
  .cmp_set = XMC_HRPWM_HRC_CMP_SEL_CSG0,
  .cmp_clear = XMC_HRPWM_HRC_CMP_SEL_CSG0,
  .timer_sel = XMC_HRPWM_HRC_TIMER_SEL_CCU_CC0,
  .set_edge_config = XMC_HRPWM_HRC_SRC_EDGE_SEL_RISING,
  .clear_edge_config = XMC_HRPWM_HRC_SRC_EDGE_SEL_FALLING,
  .src_trap_enable = XMC_HRPWM_FUNC_STATUS_DISABLE,
};

/**
 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the App initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */
int main(void)
{
  XMC_GPIO_CONFIG_t config;

  /* Ensure fCCU reaches CCU80 */
  XMC_CCU8_SetModuleClock(CCU8_MODULE, XMC_CCU8_CLOCK_SCU);

  /* Enable CCU8 module */
  XMC_CCU8_EnableModule(CCU8_MODULE);

  XMC_CCU8_Init(CCU8_MODULE, XMC_CCU8_SLICE_MCMS_ACTION_TRANSFER_PR_CR);

  XMC_CCU8_SetModuleClock(CCU8_MODULE, XMC_CCU8_CLOCK_SCU);

  XMC_CCU8_SLICE_CompareInit(CCU8_SLICE, &g_capcom_slice_object);

  /* Start the prescalar and restore clocks to slices */
  XMC_CCU8_StartPrescaler(CCU8_MODULE);
  XMC_CCU8_EnableClock(CCU8_MODULE, SLICE_NUMBER);

   /* Program a very large value into PR and CR */
  XMC_CCU8_SLICE_SetTimerPeriodMatch(CCU8_SLICE, 238U);
  XMC_CCU8_SLICE_SetTimerCompareMatch(CCU8_SLICE,XMC_CCU8_SLICE_COMPARE_CHANNEL_1, 227U);

  /* Enable shadow transfer */
  XMC_CCU8_EnableShadowTransfer(CCU8_MODULE, 1U);

  /* Initialise the HRPWM module, start HR generation */
  XMC_HRPWM_Init(HRPWM0);

  XMC_HRPWM_HRC_Init(HRPWM0_HRC0, &hrc0_config);   /* Initialise HRC Channel 0*/

  if (XMC_HRPWM_GetHRGenReadyStatus(HRPWM0) == XMC_HRPWM_HR_LOGIC_WORKING)
  {
	  XMC_HRPWM_EnableHighResolutionPath(HRPWM0, XMC_HRPWM_HR_PATH_HRC0);
    XMC_HRPWM_DisableLowResolutionPath(HRPWM0, XMC_HRPWM_LR_PATH_HRC0);
  }

  while (XMC_HRPWM_GetHRGenReadyStatus(HRPWM0) == XMC_HRPWM_HR_LOGIC_NOT_WORKING)
  {
    /* Wait until ready */
  }
  
  XMC_HRPWM_HRC_Set_HR_Source(HRPWM0_HRC0, XMC_HRPWM_HRC_SOURCE_1);  /* select Source 1 as HR path*/
  XMC_HRPWM_HRC_ConfigSourceSelect1(HRPWM0_HRC0, &hrc0_source1);   /* Configure Source 1*/
  XMC_HRPWM_EnableHighResolutionShadowTransfer(HRPWM0, XMC_HRPWM_HRC_SHADOW_TX_HRC0_VALUE);
  /* Set dead time*/
  XMC_HRPWM_HRC_SetDeadTimeRising(HRPWM0_HRC0, 2);
  XMC_HRPWM_HRC_SetDeadTimeFalling(HRPWM0_HRC0, 2);
  XMC_HRPWM_EnableHighResolutionShadowTransfer(HRPWM0, XMC_HRPWM_HRC_SHADOW_TX_HRC0_DT_VALUE);

  /* IO ports configuration for HRPWM output pins*/
  config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4;
  config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE;
  XMC_GPIO_Init(HROUT0_PIN, &config);

  config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4;
  XMC_GPIO_Init(HROUT1_PIN, &config);

  /* Enable compare match event */
  XMC_CCU8_SLICE_SetEvent(CCU8_SLICE, XMC_CCU8_SLICE_IRQ_ID_COMPARE_MATCH_UP_CH_1);
  XMC_CCU8_SLICE_EnableEvent(CCU8_SLICE,XMC_CCU8_SLICE_IRQ_ID_COMPARE_MATCH_UP_CH_1);
  /* Connect compare match event to SR1 */
  XMC_CCU8_SLICE_SetInterruptNode(CCU8_SLICE, XMC_CCU8_SLICE_IRQ_ID_COMPARE_MATCH_UP_CH_1, XMC_CCU8_SLICE_SR_ID_1);

  /* Enable IRQ */
  NVIC_SetPriority(CCU80_1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 63, 0));
  NVIC_EnableIRQ(CCU80_1_IRQn);

  XMC_CCU8_SLICE_StartTimer(CCU8_SLICE);

  while(1)
  {
  }

}

void CCU80_1_IRQHandler(void)
{
  static uint32_t cr1_value = 0U; /* HRC CR1 value */
  static uint32_t counter = 0U;

  counter++;
  if(counter > 100000)
  {
    counter = 0;
    cr1_value = cr1_value + 1;
    if (cr1_value > 54)
    {
      cr1_value = 54;
      XMC_HRPWM_HRC_SetCompare1(HRPWM0_HRC0, cr1_value);
      
      cr1_value = 0;
    }
    else
    {
      XMC_HRPWM_HRC_SetCompare1(HRPWM0_HRC0, cr1_value);
    }
    
    /* Trigger shadow transfer */
    XMC_CCU8_EnableShadowTransfer(CCU8_MODULE, 1U);

  }
}
