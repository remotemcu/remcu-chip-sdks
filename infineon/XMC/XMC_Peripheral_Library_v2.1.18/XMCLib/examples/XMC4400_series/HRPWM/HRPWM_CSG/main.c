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
********************************************************************************/

/**
 * @file
 * @date 25 Nov, 2014
 * @version 1.0.0
 *
 * @brief HRPWM CSG example
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 */

#include <xmc_dac.h>
#include <xmc_ccu8.h>
#include <xmc_scu.h>
#include <xmc_hrpwm.h>
#include <xmc_gpio.h>
#include <xmc4_gpio.h>

/*********************************************************************************************************************
 * MACROS
 ********************************************************************************************************************/
#define CCU8_SLICE         CCU80_CC80
#define CCU8_MODULE        CCU80
#define MODULE_NUMBER     (0U)
#define SLICE_NUMBER      (0U)
#define CAPCOM_MASK       (0x100U) /**< Only CCU80 */
#define DAC_CH0			      (0U)
#define PWM_OUT           P0_5

/*********************************************************************************************************************
 * GLOBAL DATA
 ********************************************************************************************************************/

/* Initialization data of the complete slice - It includes Timer and Capture init data */
XMC_CCU8_SLICE_COMPARE_CONFIG_t g_capcom_slice_object =
{
  .tc = 0x00000401,       /* 00 0000 0000 0100 0000 0001 */
  .psl = 0,
  .chc = 0,
  .prescaler_initval = 0,
  .dither_limit = 0,
  .float_limit = 0,
  .timer_concatenation = 0
};

/* Initialization data of the CSG unit */
const XMC_HRPWM_CSG_CONFIG_t csg0_init_config =
{
  .cmp_config = 
  {
    .cmp_input_sel = XMC_HRPWM_CSG_CMP_INPUT_CINA,      /**< Comparator input pin selection */
    .cmp_input_sw = XMC_HRPWM_CSG_LVL_SEL_DISABLED,     /**< Comparator input switching configuration */
    .cmp_ext_sw_enable = XMC_HRPWM_FUNC_STATUS_DISABLE, /**< Enable switching of input via external trigger. */
    .cmp_out_inv = XMC_HRPWM_FUNC_STATUS_DISABLE,       /**< Comparator output inversion enable*/
    .blanking_mode = XMC_HRPWM_CSG_EDGE_SEL_DISABLED,   /**< Blanking mode */
    .blank_ext_enable = XMC_HRPWM_FUNC_STATUS_DISABLE,  /**< Blanking via external trigger enable */
    .blanking_val = 60,                                 /**< blanking value, blanking time=blanking_val*module clk freq */
    .filter_enable = XMC_HRPWM_FUNC_STATUS_ENABLE,      /**< Comparator output filter enable */
    .filter_window = 0,                                 /**< Comparator output filter window */
		.filter_control = 0,                                /**< Comparator output filter control */
    .clamp_ctrl_lvl = XMC_HRPWM_CSG_LVL_SEL_DISABLED,   /**< Clamping control signal level selection */
    .clamp_level = 0,                                   /**< Output passive level value */
		.clamp_exit_sw_config = 1,                          /**< Clamped state exit software configuration */
		.clamp_enter_config = 0,                            /**< Clamping level enter configuration */
    .clamp_exit_config = 0                              /**< Clamping level exit configuration */
  },
  .dac_config = 
  {
    /* DSV1 is used as initial value and initial conversion trigger is generated */
    .start_mode = XMC_HRPWM_CSG_SWSM_DSV1_W_TRIGGER,
    .dac_dsv1 = 0x200,
    .dac_dsv2 = 0x200
  },
  .sgen_config = 
  {
    .ctrl_mode = 0,
    .prescaler_ext_start_mode = 0,  /* ignore prescaler*/
    .prescaler_ext_stop_mode = 0,
    .fixed_prescaler_enable = 0,    /* Fixed pre-scaler, 0:enabled, 1:disabled */
    .prescaler = 1,                 /* (120MHz / 4) / 2 = 15Mhz*/
    .ext_start_mode = 0,            /* ignore slope generation */
    .ext_stop_mode = 0,
    .slope_ref_val_mode = 0,
    .step_gain = 0,
    .static_mode_ist_enable = 1,
    .pulse_swallow_enable = 0,
    .pulse_swallow_win_mode = 0,
    .pulse_swallow_val = 0,
  }
};

/* CSG input config - DAC reference switch */
const XMC_HRPWM_CSG_INPUT_CONFIG_t dac_ref_switch_input =
{
  .mapped_input = XMC_HRPWM_CSG0_SC_HRPWM_C0O,  /* CSG0 output */
  .edge = XMC_HRPWM_CSG_EDGE_SEL_DISABLED,
  .level = XMC_HRPWM_CSG_LVL_SEL_LOW,
};

/* CSG input config - DAC conversion trigger */
const XMC_HRPWM_CSG_INPUT_CONFIG_t dac_conv_trigger_input =
{
  .mapped_input = XMC_HRPWM_CSG0_SC_CCU80_ST0,  /* CSG0 output */
  .edge = XMC_HRPWM_CSG_EDGE_SEL_BOTH_EDGE,
  .level = XMC_HRPWM_CSG_LVL_SEL_DISABLED,
};

/* Initialization data config for DAC module */
XMC_DAC_CH_CONFIG_t dac0_config =
{
  .output_scale = 0x0E,
  .output_offset = 31
};

const uint8_t pattern[] = XMC_DAC_PATTERN_TRIANGLE; // use DAC module to generate a triangle wave

/**
 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code.
 */
int main(void)
{

  /* Local variable which holds configuration of Event-0 and Event-1 */
  XMC_CCU8_SLICE_EVENT_CONFIG_t event0_config;
  XMC_CCU8_SLICE_EVENT_CONFIG_t event1_config;

  /* Port Pin configuration */
  XMC_GPIO_CONFIG_t config;

  uint32_t dsv1_value;
  uint32_t i;
  uint32_t frequency = 5000;
  uint32_t mask;

  /* Ensure fCCU reaches CCU80 */
  XMC_CCU8_SetModuleClock(CCU8_MODULE, XMC_CCU8_CLOCK_SCU);

  /* Enable CCU8 module */
  XMC_CCU8_EnableModule(CCU8_MODULE);
  XMC_CCU8_Init(CCU8_MODULE, XMC_CCU8_SLICE_MCMS_ACTION_TRANSFER_PR_CR);

  XMC_CCU8_SetModuleClock(CCU8_MODULE, XMC_CCU8_CLOCK_SCU);

  XMC_CCU8_SLICE_CompareInit(CCU8_SLICE, &g_capcom_slice_object);

  /* Start CCU8 prescalar and restore clocks to slices */
  XMC_CCU8_StartPrescaler(CCU8_MODULE);
  XMC_CCU8_EnableClock(CCU8_MODULE, SLICE_NUMBER);

  /* Program a very large value into CCU8 PR and CR */
  XMC_CCU8_SLICE_SetTimerPeriodMatch(CCU8_SLICE, 1200U);
  XMC_CCU8_SLICE_SetTimerCompareMatch(CCU8_SLICE,XMC_CCU8_SLICE_COMPARE_CHANNEL_1, 600U);

  /* Enable shadow transfer */
  XMC_CCU8_EnableShadowTransfer(CCU8_MODULE, 1U);

  /* API to initial DAC Module*/
  XMC_DAC_CH_Init(XMC_DAC0, DAC_CH0, &dac0_config);

  /* Initialise the HRPWM module, start HR generation */
  XMC_HRPWM_Init(HRPWM0);

  XMC_HRPWM_CSG_Init(HRPWM0_CSG0, &csg0_init_config);
  mask = 1;
  XMC_HRPWM_EnableComparatorShadowTransfer(HRPWM0, mask);
  XMC_HRPWM_CSG_DACRefValSwitchingConfig(HRPWM0_CSG0, &dac_ref_switch_input);

  /* start / stop of CCU8 timer controlled by CSG output*/
  /* Configure CCU8 slice Event-0 and map it to Input-I */
  event0_config.duration = XMC_CCU8_SLICE_EVENT_FILTER_DISABLED;
  event0_config.edge = XMC_CCU8_SLICE_EVENT_EDGE_SENSITIVITY_FALLING_EDGE;
  event0_config.mapped_input = XMC_CCU8_SLICE_INPUT_M;
  event0_config.level = XMC_CCU8_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH;
  XMC_CCU8_SLICE_ConfigureEvent(CCU8_SLICE, XMC_CCU8_SLICE_EVENT_0, &event0_config);

  /* Map Event-0 to Start function */
  XMC_CCU8_SLICE_StartConfig(CCU8_SLICE, XMC_CCU8_SLICE_EVENT_0, XMC_CCU8_SLICE_START_MODE_TIMER_START_CLEAR);

  /* Configure CCU8 slice Event-1 and map it to Input-I */
  event1_config.duration = XMC_CCU8_SLICE_EVENT_FILTER_DISABLED;
  event1_config.edge = XMC_CCU8_SLICE_EVENT_EDGE_SENSITIVITY_RISING_EDGE;
  event1_config.mapped_input = XMC_CCU8_SLICE_INPUT_M;
  event1_config.level = XMC_CCU8_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH;
  XMC_CCU8_SLICE_ConfigureEvent(CCU8_SLICE, XMC_CCU8_SLICE_EVENT_1, &event1_config);

  /* Map Event-1 to stop function */
  XMC_CCU8_SLICE_StopConfig(CCU8_SLICE, XMC_CCU8_SLICE_EVENT_1, XMC_CCU8_SLICE_END_MODE_TIMER_STOP_CLEAR);

  /* CSG DAC DSV1 variable initial value */
  dsv1_value = csg0_init_config.dac_config.dac_dsv1;

  /* IO ports configuration for CCU80 output pins*/
  config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3;
  config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE;
  XMC_GPIO_Init(PWM_OUT, &config);

  /* API to start a DAC channel to generate triangle wave*/
  XMC_DAC_CH_StartPatternMode(XMC_DAC0,
		                      DAC_CH0,
		                      &pattern[0],
		                      XMC_DAC_CH_PATTERN_SIGN_OUTPUT_DISABLED,
		                      XMC_DAC_CH_TRIGGER_INTERNAL,
		                      frequency);

  /* Start CCU 8 slice timer*/
  XMC_CCU8_SLICE_StartTimer(CCU8_SLICE);

  /* Start HRPWM CSG DAC and Comparator*/
  XMC_HRPWM_StartDac(HRPWM0, XMC_HRPWM_CSG_RUN_BIT_DAC0);
  XMC_HRPWM_StartComparator(HRPWM0, XMC_HRPWM_CSG_RUN_BIT_CMP0);

  mask = 1;
  while(1)
  {
    for(i = 0; i < 0xFFFF; ++i);   // delay

    // update CSG DAC DSV1 register.
	dsv1_value += 20;
	if(dsv1_value > 600)
	  dsv1_value = 160;

	XMC_HRPWM_CSG_UpdateDACRefDSV1(HRPWM0_CSG0,dsv1_value);
	XMC_HRPWM_EnableComparatorShadowTransfer(HRPWM0, mask);

  }
}


