/*
** ###################################################################
**     Processors:          MKL33Z64VFT4
**                          MKL33Z32VFT4
**                          MKL33Z64VLH4
**                          MKL33Z32VLH4
**                          MKL33Z64VLK4
**                          MKL33Z32VLK4
**                          MKL33Z64VMP4
**                          MKL33Z32VMP4
**
**     Compilers:           Keil ARM C/C++ Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          GNU C Compiler - CodeSourcery Sourcery G++
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    KL33P80M48SF3RM, Rev.2, March 2015
**     Version:             rev. 1.1, 2015-03-11
**     Build:               b150319
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright (c) 2015 Freescale Semiconductor, Inc.
**     All rights reserved.
**
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2014-09-24)
**         Initial version.
**     - rev. 1.1 (2015-03-11)
**         Update Reference Manual information and add part numbers.
**
** ###################################################################
*/

/*!
 * @file MKL33Z644
 * @version 1.1
 * @date 2015-03-11
 * @brief Device specific configuration file for MKL33Z644 (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "fsl_device_registers.h"



/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

void SystemInit (void) {

#if (ACK_ISOLATION)
  if(PMC->REGSC &  PMC_REGSC_ACKISO_MASK) {
    PMC->REGSC |= PMC_REGSC_ACKISO_MASK; /* VLLSx recovery */
  }
#endif

#if (DISABLE_WDOG)
  /* SIM->COPC: ?=0,COPCLKSEL=0,COPDBGEN=0,COPSTPEN=0,COPT=0,COPCLKS=0,COPW=0 */
  SIM->COPC = (uint32_t)0x00u;
#endif /* (DISABLE_WDOG) */

#ifdef CLOCK_SETUP
  /* Power mode protection initialization */
#ifdef SMC_PMPROT_VALUE
  SMC->PMPROT = SMC_PMPROT_VALUE;
#endif

  /* System clock initialization */

  /* Set system prescalers and clock sources */
  SIM->CLKDIV1 = SYSTEM_SIM_CLKDIV1_VALUE;    /* Set system prescalers */
  SIM->SOPT1 = ((SIM->SOPT1) & (uint32_t)(~(SIM_SOPT1_OSC32KSEL_MASK))) | ((SYSTEM_SIM_SOPT1_VALUE) & (SIM_SOPT1_OSC32KSEL_MASK)); /* Set 32 kHz clock source (ERCLK32K) */
  SIM->SOPT2 = ((SIM->SOPT2) & (uint32_t)(~(
                 SIM_SOPT2_TPMSRC_MASK |
                 SIM_SOPT2_LPUART0SRC_MASK |
                 SIM_SOPT2_LPUART1SRC_MASK
                 ))) | ((SYSTEM_SIM_SOPT2_VALUE) & (
                 SIM_SOPT2_TPMSRC_MASK |
                 SIM_SOPT2_LPUART0SRC_MASK |
                 SIM_SOPT2_LPUART1SRC_MASK
                 ));   /* Select TPM, LPUARTs clock sources. */
#if (MCG_MODE == MCG_MODE_LIRC_2M || MCG_MODE == MCG_MODE_LIRC_8M || MCG_MODE == MCG_MODE_HIRC)
  /* Set MCG and OSC0 */
#if  (((OSC0_CR_VALUE) & OSC_CR_ERCLKEN_MASK) != 0x00U)
  /* SIM_SCGC5: PORTA=1 */
  SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
  /* PORTA_PCR3: ISF=0,MUX=0 */
  PORTA_PCR18 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  if (((MCG_C2_VALUE) & MCG_C2_EREFS0_MASK) != 0x00U) {
    PORTA_PCR19 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  }
#endif
  MCG->SC = MCG_SC_VALUE;              /* Set SC (internal reference clock divider) */
  MCG->MC = MCG_MC_VALUE;              /* Set MC (high-frequency IRC enable, second LIRC divider) */
  MCG->C1 = MCG_C1_VALUE;              /* Set C1 (clock source selection, int. reference enable etc.) */
  MCG->C2 = MCG_C2_VALUE;              /* Set C2 (ext. and int. reference clock selection) */
  OSC0->CR = OSC0_CR_VALUE;            /* Set OSC0_CR (OSCERCLK enable, oscillator capacitor load) */

#else /* MCG_MODE */
  /* Set MCG and OSC0 */
  /* SIM_SCGC5: PORTA=1 */
  SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
  /* PORTA_PCR3: ISF=0,MUX=0 */
  PORTA_PCR18 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  if (((MCG_C2_VALUE) & MCG_C2_EREFS0_MASK) != 0x00U) {
    PORTA_PCR19 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  }
  MCG->SC = MCG_SC_VALUE;              /* Set SC (internal reference clock divider) */
  MCG->C2 = MCG_C2_VALUE;              /* Set C2 (ext. and int. reference clock selection) */
  OSC0->CR = OSC0_CR_VALUE;            /* Set OSC0_CR (OSCERCLK enable, oscillator capacitor load) */
  MCG->C1 = MCG_C1_VALUE;              /* Set C1 (clock source selection, int. reference enable etc.) */
  MCG->MC = MCG_MC_VALUE;              /* Set MC (high-frequency IRC enable, second LIRC divider) */
  if (((MCG_C2_VALUE) & MCG_C2_EREFS0_MASK) != 0U) {
    while((MCG->S & MCG_S_OSCINIT0_MASK) == 0x00U) { /* Check that the oscillator is running */
    }
  }
#endif /* MCG_MODE */

  /* Common for all MCG modes */

#if (MCG_MODE == MCG_MODE_HIRC)
  while((MCG->S & MCG_S_CLKST_MASK) != 0x00U) { /* Wait until high internal reference clock is selected as MCG_Lite output */
  }
#elif (MCG_MODE == MCG_MODE_LIRC_2M || MCG_MODE == MCG_MODE_LIRC_8M)
  while((MCG->S & MCG_S_CLKST_MASK) != 0x04U) { /* Wait until low internal reference clock is selected as MCG_Lite output */
  }
#elif (MCG_MODE == MCG_MODE_EXT)
  while((MCG->S & MCG_S_CLKST_MASK) != 0x08U) { /* Wait until external reference clock is selected as MCG_Lite output */
  }
#endif
  if (((SMC_PMCTRL_VALUE) & SMC_PMCTRL_RUNM_MASK) == SMC_PMCTRL_RUNM(0x02U)) {
    SMC->PMCTRL = (uint8_t)((SMC_PMCTRL_VALUE) & (SMC_PMCTRL_RUNM_MASK)); /* Enable VLPR mode */
    while(SMC->PMSTAT != 0x04U) {      /* Wait until the system is in VLPR mode */
    }
  }
#endif
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {

  uint32_t MCGOUTClock;                                 /* Variable to store output clock frequency of the MCG module */
  uint16_t Divider;

  if ((MCG->S & MCG_S_CLKST_MASK) == 0x00U) {
    /* High internal reference clock is selected */
    MCGOUTClock = CPU_INT_FAST_CLK_HZ;                                  /* Fast internal reference clock selected */
  } else if ((MCG->S & MCG_S_CLKST_MASK) == 0x04U) {
    /* Internal reference clock is selected */
    Divider = (uint16_t)(0x01LU << ((MCG->SC & MCG_SC_FCRDIV_MASK) >> MCG_SC_FCRDIV_SHIFT));
    MCGOUTClock = (uint32_t) (CPU_INT_SLOW_CLK_HZ / Divider);           /* Slow internal reference clock 8MHz selected */
  } else if ((MCG->S & MCG_S_CLKST_MASK) == 0x08U) {
    /* External reference clock is selected */
    MCGOUTClock = CPU_XTAL_CLK_HZ;
  } else {
    /* Reserved value */
    return;
  } /* (!((MCG->S & MCG_S_CLKST_MASK) == 0x08U)) */
  SystemCoreClock = (MCGOUTClock / (0x01U + ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT)));

}
