/*
 * Copyright (C) 2015 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

/**
 * @file
 * @date 09 October, 2015
 * @version 1.0.0
 *
 * @brief DAC demo example
 *
 *  This example demonstrate two of five DAC configurations.
 *  It generates an analog sine wave on DAC0 Output and
 *  a static analog value on DAC1 Output.
 *  e.g. XMC45/48  P14.8 (DAC0),  P14.9 (DAC1)
 *
 *  To change the frequency and amplitude the function DAC_Update() is called
 *  periodically. DAC_Update() only has to be called to change frequency or
 *  amplitude not for basic sine wave generation.
 *
 *  The value in beats[index] defines after how many function calls
 *  the frequency and amplitude will be updated. The value in melody[index]
 *  defines the new frequency and if the amplitude have to be set to minimum.
 *
 *  After program start, the two analog values can be displayed via oscilloscope
 *  e.g. XMC44/45  P14.8 (DAC0),  P14.9 (DAC1).
 *   DAC0 (P14.8) is a static value of 1.4V
 *   DAC1 (P14.9) is a sine wave with changing frequency
 *
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 *
 */


#include <xmc_dac.h>
#include <xmc_scu.h>

#define R 		         (20000U)
#define ARRAY_SIZE 	     (48U)
#define TICKS_PER_SECOND (100U)


const uint16_t melody[ARRAY_SIZE] =
{
  660U,	R,	660U,	R, 	660U,	R, 	510U,	R,
  660U, R, 	770U,	R,	380U,	R, 	510U,	R,
  380U,	R, 	320U,	R, 	440U,	R, 	480U,   R,
  450U,	R,	430U,	R,	380U,	R,	660U,	R,
  760U,	R,	860U,	R,	700U,   R, 	760U,	R,
  660U, R,	520U,	R,	580U,	R,	480U,	R
};


const uint16_t beats[ARRAY_SIZE] =
{
  10U, 15U, 10U, 30U, 10U, 30U,	10U, 10U,
  10U, 30U, 10U, 55U, 10U, 57U, 10U, 45U,
  10U, 40U,	10U, 50U, 10U, 30U,	 8U, 33U,
  10U, 15U,	10U, 30U, 10U, 20U,	 8U, 20U,
  5U,  15U,	10U, 30U,  8U, 15U,	 5U, 35U,
  8U,  30U,	 8U, 15U,  8U, 15U,	 8U, 50U
};


XMC_DAC_CH_CONFIG_t const ch_config0=
{
  .output_offset	= 0U,
  .data_type 		= XMC_DAC_CH_DATA_TYPE_SIGNED,
  .output_scale 	= XMC_DAC_CH_OUTPUT_SCALE_MUL_64,
  .output_negation = XMC_DAC_CH_OUTPUT_NEGATION_DISABLED,
};

XMC_DAC_CH_CONFIG_t const ch_config1=
{
  .output_offset	= 0U,
  .data_type 		= XMC_DAC_CH_DATA_TYPE_SIGNED,
  .output_scale 	= XMC_DAC_CH_OUTPUT_SCALE_NONE,
  .output_negation = XMC_DAC_CH_OUTPUT_NEGATION_DISABLED,
};

const uint8_t pattern[] = XMC_DAC_PATTERN_SINE;

void DacUpdate(void);

void SysTick_Handler(void)
{
  DacUpdate();
}

int main(void)
{
  /* API to initial DAC Module*/
  XMC_DAC_CH_Init(XMC_DAC0, 0U, &ch_config0);
  XMC_DAC_CH_Init(XMC_DAC0, 1U, &ch_config1);

  /* API to initial DAC in Pattern mode. When using a predefined pattern a type cast avoid warnings */
  XMC_DAC_CH_StartPatternMode(XMC_DAC0, 0U, pattern, XMC_DAC_CH_PATTERN_SIGN_OUTPUT_DISABLED, XMC_DAC_CH_TRIGGER_INTERNAL, 500U);

  /* API to initial DAC in SingleValue mode */
  XMC_DAC_CH_StartSingleValueMode(XMC_DAC0, 1U);

  /* API to write a value into DAC Output */
  XMC_DAC_CH_Write(XMC_DAC0, 1, 0x1ffU);

  /* System timer configuration */
  SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

  while(1)
  {
  }
}


/*------------------------------------------------------------------------------------------------------------------
 * void DacUpdate(void)
 *
 * Updates the DAC frequency after beats[index] function calls.
 * New frequency value is  melody[index].
 *
 * e.g.:
 * 	index=0, beats[index]= 10, melody[index] =660 and Dac_Update is called after 10ms:
 * 	Sine wave with 660Hz will be displayed for 100ms.
 *
 * If melody[index] =R, frequency is shifted out of audible area and amplitude is set to minimum.
 *
 * ------------------------------------------------------------------------------------------------------------------*/
void DacUpdate(void)
{
  static uint8_t function_calls = 0;
  static uint8_t index = 0;

  function_calls++;

  /* check if function_call limit is reached.*/
  if (function_calls >= beats[index])
  {
    function_calls = 0;
    index++;

    /* avoid array overflow.*/
    if(index >= ARRAY_SIZE)
    {
      index = 0;
    }

    /* update frequency */
    XMC_DAC_CH_SetPatternFrequency(XMC_DAC0, 0, melody[index]);

  }
}

