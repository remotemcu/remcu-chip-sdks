/**************************************************************************//**
 * @file startup_efr32fg13p.c
 * @brief CMSIS Compatible EFR32FG13P startup file in C for IAR EWARM
 * @version 5.1.2
 ******************************************************************************
 * @section License
 * <b>Copyright 2017 Silicon Laboratories, Inc. http://www.silabs.com</b>
 ******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.@n
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.@n
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Silicon Laboratories, Inc.
 * has no obligation to support this Software. Silicon Laboratories, Inc. is
 * providing the Software "AS IS", with no express or implied warranties of any
 * kind, including, but not limited to, any implied warranties of
 * merchantability or fitness for any particular purpose or warranties against
 * infringement of any proprietary rights of a third party.
 *
 * Silicon Laboratories, Inc. will not be liable for any consequential,
 * incidental, or special damages, or any other relief, or for any claim by
 * any third party, arising from your use of this Software.
 *
 *****************************************************************************/

#include "em_device.h"        /* The correct device header file. */

#pragma language=extended
#pragma segment="CSTACK"

/* IAR start function */
extern void __iar_program_start(void);
/* CMSIS init function */
extern void SystemInit(void);

/* Auto defined by linker */
extern unsigned char CSTACK$$Limit;

__weak void Reset_Handler(void)
{
  SystemInit();
  __iar_program_start();
}

__weak void NMI_Handler(void)
{
  while(1);
}

__weak void HardFault_Handler(void)
{
  while(1);
}

__weak void MemManage_Handler(void)
{
  while(1);
}

__weak void BusFault_Handler(void)
{
  while(1);
}

__weak void UsageFault_Handler(void)
{
  while(1);
}

__weak void SVC_Handler(void)
{
  while(1);
}

__weak void DebugMon_Handler(void)
{
  while(1);
}

__weak void PendSV_Handler(void)
{
  while(1);
}

__weak void SysTick_Handler(void)
{
  while(1);
}


__weak void EMU_IRQHandler(void)
{
  while(1);
}

__weak void FRC_PRI_IRQHandler(void)
{
  while(1);
}

__weak void WDOG0_IRQHandler(void)
{
  while(1);
}

__weak void WDOG1_IRQHandler(void)
{
  while(1);
}

__weak void FRC_IRQHandler(void)
{
  while(1);
}

__weak void MODEM_IRQHandler(void)
{
  while(1);
}

__weak void RAC_SEQ_IRQHandler(void)
{
  while(1);
}

__weak void RAC_RSM_IRQHandler(void)
{
  while(1);
}

__weak void BUFC_IRQHandler(void)
{
  while(1);
}

__weak void LDMA_IRQHandler(void)
{
  while(1);
}

__weak void GPIO_EVEN_IRQHandler(void)
{
  while(1);
}

__weak void TIMER0_IRQHandler(void)
{
  while(1);
}

__weak void USART0_RX_IRQHandler(void)
{
  while(1);
}

__weak void USART0_TX_IRQHandler(void)
{
  while(1);
}

__weak void ACMP0_IRQHandler(void)
{
  while(1);
}

__weak void ADC0_IRQHandler(void)
{
  while(1);
}

__weak void IDAC0_IRQHandler(void)
{
  while(1);
}

__weak void I2C0_IRQHandler(void)
{
  while(1);
}

__weak void GPIO_ODD_IRQHandler(void)
{
  while(1);
}

__weak void TIMER1_IRQHandler(void)
{
  while(1);
}

__weak void USART1_RX_IRQHandler(void)
{
  while(1);
}

__weak void USART1_TX_IRQHandler(void)
{
  while(1);
}

__weak void LEUART0_IRQHandler(void)
{
  while(1);
}

__weak void PCNT0_IRQHandler(void)
{
  while(1);
}

__weak void CMU_IRQHandler(void)
{
  while(1);
}

__weak void MSC_IRQHandler(void)
{
  while(1);
}

__weak void CRYPTO0_IRQHandler(void)
{
  while(1);
}

__weak void LETIMER0_IRQHandler(void)
{
  while(1);
}

__weak void AGC_IRQHandler(void)
{
  while(1);
}

__weak void PROTIMER_IRQHandler(void)
{
  while(1);
}

__weak void PRORTC_IRQHandler(void)
{
  while(1);
}

__weak void RTCC_IRQHandler(void)
{
  while(1);
}

__weak void SYNTH_IRQHandler(void)
{
  while(1);
}

__weak void CRYOTIMER_IRQHandler(void)
{
  while(1);
}

__weak void RFSENSE_IRQHandler(void)
{
  while(1);
}

__weak void FPUEH_IRQHandler(void)
{
  while(1);
}

__weak void SMU_IRQHandler(void)
{
  while(1);
}

__weak void WTIMER0_IRQHandler(void)
{
  while(1);
}

__weak void USART2_RX_IRQHandler(void)
{
  while(1);
}

__weak void USART2_TX_IRQHandler(void)
{
  while(1);
}

__weak void I2C1_IRQHandler(void)
{
  while(1);
}

__weak void VDAC0_IRQHandler(void)
{
  while(1);
}

__weak void CSEN_IRQHandler(void)
{
  while(1);
}

__weak void LESENSE_IRQHandler(void)
{
  while(1);
}

__weak void CRYPTO1_IRQHandler(void)
{
  while(1);
}

__weak void TRNG0_IRQHandler(void)
{
  while(1);
}


/* With IAR, the CSTACK is defined via project options settings */
#pragma data_alignment=256
#pragma location = ".intvec"
const void * const __vector_table[]=  {
  &CSTACK$$Limit,
  (void *) Reset_Handler,           /*  1 - Reset (start instruction) */
  (void *) NMI_Handler,             /*  2 - NMI */
  (void *) HardFault_Handler,       /*  3 - HardFault */
  (void *) MemManage_Handler,
  (void *) BusFault_Handler,
  (void *) UsageFault_Handler,
  (void *) 0,
  (void *) 0,
  (void *) 0,
  (void *) 0,
  (void *) SVC_Handler,
  (void *) DebugMon_Handler,
  (void *) 0,
  (void *) PendSV_Handler,
  (void *) SysTick_Handler,
  (void *) EMU_IRQHandler,  /* 0 - EMU */
  (void *) FRC_PRI_IRQHandler,  /* 1 - FRC_PRI */
  (void *) WDOG0_IRQHandler,  /* 2 - WDOG0 */
  (void *) WDOG1_IRQHandler,  /* 3 - WDOG1 */
  (void *) FRC_IRQHandler,  /* 4 - FRC */
  (void *) MODEM_IRQHandler,  /* 5 - MODEM */
  (void *) RAC_SEQ_IRQHandler,  /* 6 - RAC_SEQ */
  (void *) RAC_RSM_IRQHandler,  /* 7 - RAC_RSM */
  (void *) BUFC_IRQHandler,  /* 8 - BUFC */
  (void *) LDMA_IRQHandler,  /* 9 - LDMA */
  (void *) GPIO_EVEN_IRQHandler,  /* 10 - GPIO_EVEN */
  (void *) TIMER0_IRQHandler,  /* 11 - TIMER0 */
  (void *) USART0_RX_IRQHandler,  /* 12 - USART0_RX */
  (void *) USART0_TX_IRQHandler,  /* 13 - USART0_TX */
  (void *) ACMP0_IRQHandler,  /* 14 - ACMP0 */
  (void *) ADC0_IRQHandler,  /* 15 - ADC0 */
  (void *) IDAC0_IRQHandler,  /* 16 - IDAC0 */
  (void *) I2C0_IRQHandler,  /* 17 - I2C0 */
  (void *) GPIO_ODD_IRQHandler,  /* 18 - GPIO_ODD */
  (void *) TIMER1_IRQHandler,  /* 19 - TIMER1 */
  (void *) USART1_RX_IRQHandler,  /* 20 - USART1_RX */
  (void *) USART1_TX_IRQHandler,  /* 21 - USART1_TX */
  (void *) LEUART0_IRQHandler,  /* 22 - LEUART0 */
  (void *) PCNT0_IRQHandler,  /* 23 - PCNT0 */
  (void *) CMU_IRQHandler,  /* 24 - CMU */
  (void *) MSC_IRQHandler,  /* 25 - MSC */
  (void *) CRYPTO0_IRQHandler,  /* 26 - CRYPTO0 */
  (void *) LETIMER0_IRQHandler,  /* 27 - LETIMER0 */
  (void *) AGC_IRQHandler,  /* 28 - AGC */
  (void *) PROTIMER_IRQHandler,  /* 29 - PROTIMER */
  (void *) PRORTC_IRQHandler,  /* 30 - PRORTC */
  (void *) RTCC_IRQHandler,  /* 31 - RTCC */
  (void *) SYNTH_IRQHandler,  /* 32 - SYNTH */
  (void *) CRYOTIMER_IRQHandler,  /* 33 - CRYOTIMER */
  (void *) RFSENSE_IRQHandler,  /* 34 - RFSENSE */
  (void *) FPUEH_IRQHandler,  /* 35 - FPUEH */
  (void *) SMU_IRQHandler,  /* 36 - SMU */
  (void *) WTIMER0_IRQHandler,  /* 37 - WTIMER0 */
  (void *) USART2_RX_IRQHandler,  /* 38 - USART2_RX */
  (void *) USART2_TX_IRQHandler,  /* 39 - USART2_TX */
  (void *) I2C1_IRQHandler,  /* 40 - I2C1 */
  (void *) VDAC0_IRQHandler,  /* 41 - VDAC0 */
  (void *) CSEN_IRQHandler,  /* 42 - CSEN */
  (void *) LESENSE_IRQHandler,  /* 43 - LESENSE */
  (void *) CRYPTO1_IRQHandler,  /* 44 - CRYPTO1 */
  (void *) TRNG0_IRQHandler,  /* 45 - TRNG0 */
  (void *) 0,                /* 46 - Reserved */

};
