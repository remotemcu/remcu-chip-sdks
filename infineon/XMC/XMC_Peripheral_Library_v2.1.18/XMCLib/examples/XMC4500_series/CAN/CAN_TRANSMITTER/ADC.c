/*-----------------------------------------------------------------------------
 * Name:    ADC_XMC4500.c
 * Purpose: A/D Converter interface for Infineon XMC4500 Relax Kit
 * Rev.:    1.00
 *----------------------------------------------------------------------------*/

/* Copyright (c) 2013 - 2015 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/

#include "xmc_vadc.h" 
#include "Board_ADC.h"

#define ADC_RESOLUTION        12        /* Number of A/D converter bits       */

/**
  \fn          int32_t ADC_Initialize (void)
  \brief       Initialize Analog-to-Digital Converter
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
int32_t ADC_Initialize (void) {
		
	//Enable the VADC module
	XMC_SCU_RESET_DeassertPeripheralReset(XMC_SCU_PERIPHERAL_RESET_VADC);
  VADC->CLC       =   0;                     /* enable the VADC module clock  */
  VADC->GLOBCFG   = ((1UL << 15) |           /* enable DIVA write control     */
                     (6UL <<  0)  );         /* set DIVA to 6                 */
 	
  //Enable arbitration slot 02, priority set to 1     
	XMC_VADC_GROUP_BackgroundEnableArbitrationSlot(VADC_G0);	
	
	//Add a channel into the scan sequence Group 0 channel 0 (P14.1)
  XMC_VADC_GLOBAL_BackgroundAddChannelToSequence(VADC,0,1);
	
	VADC_G0->ARBCFG = ((3UL << 16) |          /* ANONS normal operation        */ 
                     (3UL <<  0)  );        /* ANONC normal operation        */
	VADC->BRSMR = ((1UL <<  0)); 				      /* ENGT = 01B                    */
	
  return 0;
}

/**
  \fn          int32_t ADC_Uninitialize (void)
  \brief       De-initialize Analog-to-Digital Converter
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
int32_t ADC_Uninitialize (void) {
  //Disable the VADC module
	XMC_SCU_RESET_AssertPeripheralReset(XMC_SCU_PERIPHERAL_RESET_VADC);
	return 0;
}

/**
  \fn          int32_t ADC_StartConversion (void)
  \brief       Start conversion
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
int32_t ADC_StartConversion (void) {	
  // Generates conversion request
  XMC_VADC_GLOBAL_BackgroundTriggerConversion(VADC);	
  return 0;
}

/**
  \fn          int32_t ADC_ConversionDone (void)
  \brief       Check if conversion finished
  \returns
   - \b  0: conversion finished
   - \b -1: conversion in progress
*/
int32_t ADC_ConversionDone (void) {
  XMC_VADC_GROUP_STATE_t status;
  status = XMC_VADC_GROUP_IsConverterBusy(VADC_G0);
  return ((status == XMC_VADC_GROUP_STATE_IDLE) ? 0 : -1);
}

/**
  \fn          int32_t ADC_GetValue (void)
  \brief       Get converted value
  \returns
   - <b> >=0</b>: converted value
   - \b -1: conversion in progress or failed
*/
int32_t ADC_GetValue (void) {
	//Return the result value of the result register
	if (ADC_ConversionDone() != 0) return -1;
  return (int32_t) XMC_VADC_GROUP_GetResult(VADC_G0,0);
}

/**
  \fn          uint32_t ADC_GetResolution (void)
  \brief       Get resolution of Analog-to-Digital Converter
  \returns     Resolution (in bits)
*/
uint32_t ADC_GetResolution (void) {
  return ADC_RESOLUTION;
}
