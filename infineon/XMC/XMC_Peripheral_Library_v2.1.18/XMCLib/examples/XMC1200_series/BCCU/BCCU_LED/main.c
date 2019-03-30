/******************************************************************************
 * @file     Main.c
 * @brief    Easy Start project: changes the color in "inLight Colour LED Card".
 * @version  V1.0
 * @date     01 Dec 2014
 * @note
 * Copyright (C) 2014 Infineon Technologies AG. All rights reserved.
 ******************************************************************************
 * @par
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon’s microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *****************************************************************************/

#include <xmc_gpio.h>
#include <xmc_bccu.h>

/* Linear Walk Time: 7sec */
#define LINEAR_WALK_PRESCALER 214 //7Sec @ 32 MHz CPU Clock

#define R_LED1 P0_4
#define G_LED1 P0_11
#define B_LED1 P0_1

#define R_LED2 P0_5
#define G_LED2 P0_6
#define B_LED2 P0_7

#define R_LED3 P0_8
#define G_LED3 P0_9
#define B_LED3 P0_10


/* BCCU Configuration Handles */
/* --------------------------- */
XMC_BCCU_GLOBAL_CONFIG_t bccu_global_config =
{
  .fclk_ps = 0x40, //1MHz @PCLK=64MHz
  .dclk_ps = 0xdb, //292.237KHz @PCLK=64MHz
  .bclk_sel = XMC_BCCU_BCLK_MODE_NORMAL, //250KHz @PCLK=64MHz
  .maxzero_at_output = 0x3e8
};

XMC_BCCU_CH_CONFIG_t bccu_redch_config =
{
  .pack_thresh     = 0x2,
  .dim_sel         = 0x0, //DE0
  .flick_wd_en     = 0x1,
  .pack_offcnt_val = 0xf6,
  .pack_offcmp_lev = 0xff,
  .pack_oncmp_lev  = 0x27
};

XMC_BCCU_CH_CONFIG_t bccu_greench_config =
{
  .pack_thresh     = 0x2,
  .dim_sel         = 0x0, //DE0
  .flick_wd_en     = 0x1,
  .pack_offcnt_val = 0xf6,
  .pack_offcmp_lev = 0xff,
  .pack_oncmp_lev  = 0x27
};

XMC_BCCU_CH_CONFIG_t bccu_bluech_config =
{
  .pack_thresh     = 0x2,
  .dim_sel         = 0x0, //DE0
  .flick_wd_en     = 0x1,
  .pack_offcnt_val = 0xf6,
  .pack_offcmp_lev = 0xff,
  .pack_oncmp_lev  = 0x27
};

XMC_BCCU_DIM_CONFIG_t bccu_dim_config =
{
  .dim_div = 0x20
};

int main(void)
{
  XMC_GPIO_SetMode(R_LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1);
  XMC_GPIO_SetMode(G_LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1);
  XMC_GPIO_SetMode(B_LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT6);

  /* Switch off LED2 and LED3, control signals driving a zero */
  XMC_GPIO_SetMode(R_LED2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(G_LED2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(B_LED2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

  XMC_GPIO_SetMode(R_LED3, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(G_LED3, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(B_LED3, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	
  /* BCCU Configuration */
  XMC_BCCU_GlobalInit(BCCU0, &bccu_global_config);
  
  /* Red - CH0, Green - CH7, Blue - CH8 */
  XMC_BCCU_CH_Init(BCCU0_CH0, &bccu_redch_config);
  XMC_BCCU_CH_Init(BCCU0_CH7, &bccu_greench_config);
  XMC_BCCU_CH_Init(BCCU0_CH8, &bccu_bluech_config);
    
  /* Set 7Sec linear walk */
  XMC_BCCU_CH_SetLinearWalkPrescaler(BCCU0_CH0, LINEAR_WALK_PRESCALER);
  XMC_BCCU_CH_SetLinearWalkPrescaler(BCCU0_CH7, LINEAR_WALK_PRESCALER);
  XMC_BCCU_CH_SetLinearWalkPrescaler(BCCU0_CH8, LINEAR_WALK_PRESCALER);

  XMC_BCCU_DIM_Init(BCCU0_DE0, &bccu_dim_config);

  /* Enable RGB channels, dimming engine */
  XMC_BCCU_ConcurrentEnableChannels(BCCU0, 0x181);
  XMC_BCCU_EnableDimmingEngine(BCCU0, XMC_BCCU_CH_DIMMING_SOURCE_DE0);

  XMC_BCCU_CH_SetTargetIntensity(BCCU0_CH0, 0x555);
  XMC_BCCU_DIM_SetTargetDimmingLevel(BCCU0_DE0, 1024);
    
  /* Start linear walk at the same time */
  XMC_BCCU_ConcurrentStartLinearWalk(BCCU0, 0x181);
  XMC_BCCU_StartDimming(BCCU0, 0);

  /* 500 ms timer interrupt assuming that SystemCoreClock is 32 MHz (default) */
  SysTick_Config(SystemCoreClock >> 1UL);
  while(1)
  {
    /* Infinite loop */
  }
}


/* 500 ms interrupt */
void SysTick_Handler(void)
{
  static uint8_t step = 0;

  /* Change Slowly to Red */
  if (++step == 1) 
  {
    XMC_BCCU_CH_SetTargetIntensity(BCCU0_CH0, 4095);
    XMC_BCCU_CH_SetTargetIntensity(BCCU0_CH7, 0);
    XMC_BCCU_CH_SetTargetIntensity(BCCU0_CH8, 0);
    XMC_BCCU_ConcurrentStartLinearWalk(BCCU0, 0x181);
  }
  /* Change Slowly to Green */
  else if (step == 18) 
  {
    XMC_BCCU_CH_SetTargetIntensity(BCCU0_CH0, 0);
    XMC_BCCU_CH_SetTargetIntensity(BCCU0_CH7, 4095);
    XMC_BCCU_CH_SetTargetIntensity(BCCU0_CH8, 0);
    XMC_BCCU_ConcurrentStartLinearWalk(BCCU0, 0x181);
  }
  /* Change Slowly to Blue */
  else if (step == 34) 
  {
    XMC_BCCU_CH_SetTargetIntensity(BCCU0_CH0, 0);
    XMC_BCCU_CH_SetTargetIntensity(BCCU0_CH7, 0);
    XMC_BCCU_CH_SetTargetIntensity(BCCU0_CH8, 4095);
    XMC_BCCU_ConcurrentStartLinearWalk(BCCU0, 0x181);
  }
  /* Change Slowly to White */
  else if (step == 50) 
  {
    XMC_BCCU_CH_SetTargetIntensity(BCCU0_CH0, 1365);
    XMC_BCCU_CH_SetTargetIntensity(BCCU0_CH7, 1365);
    XMC_BCCU_CH_SetTargetIntensity(BCCU0_CH8, 1365);
    XMC_BCCU_ConcurrentStartLinearWalk(BCCU0, 0x181);
  }
  /* Dim Down Slowly to 0% */
  else if (step == 66) 
  {             
    /* dim down slowly to 0% */
    XMC_BCCU_DIM_SetTargetDimmingLevel(BCCU0_DE0, 0);
    XMC_BCCU_StartDimming(BCCU0, 0);
  }
  /* Dim Up Slowly to 25% */
  else if (step == 80) 
  {
    XMC_BCCU_DIM_SetTargetDimmingLevel(BCCU0_DE0, 1024);
    XMC_BCCU_StartDimming(BCCU0, 0);
  }
  else if (step == 94) 
  {
    step = 0;
  }
}

