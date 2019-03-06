/**************************************************************************//**
 * @file
 * @brief CMSIS Cortex-M3 Core Device Startup File for sky66107
 * @version 5.1.2
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Silicon Labs has no
 * obligation to support this Software. Silicon Labs is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Silicon Labs will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/
#include "em_device.h"

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

__weak void TIM1_IRQHandler(void)
{
  while(1);
}

__weak void TIM2_IRQHandler(void)
{
  while(1);
}

__weak void MGMT_IRQHandler(void)
{
  while(1);
}

__weak void BB_IRQHandler(void)
{
  while(1);
}

__weak void SLEEPTMR_IRQHandler(void)
{
  while(1);
}

__weak void SC1_IRQHandler(void)
{
  while(1);
}

__weak void SC2_IRQHandler(void)
{
  while(1);
}

__weak void SEC_IRQHandler(void)
{
  while(1);
}

__weak void MACTMR_IRQHandler(void)
{
  while(1);
}

__weak void MACTX_IRQHandler(void)
{
  while(1);
}

__weak void MACRX_IRQHandler(void)
{
  while(1);
}

__weak void ADC_IRQHandler(void)
{
  while(1);
}

__weak void IRQA_IRQHandler(void)
{
  while(1);
}

__weak void IRQB_IRQHandler(void)
{
  while(1);
}

__weak void IRQC_IRQHandler(void)
{
  while(1);
}

__weak void IRQD_IRQHandler(void)
{
  while(1);
}

__weak void DEBUG_IRQHandler(void)
{
  while(1);
}

__weak void SC3_IRQHandler(void)
{
  while(1);
}

__weak void SC4_IRQHandler(void)
{
  while(1);
}

__weak void USB_IRQHandler(void)
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
    (void *) TIM1_IRQHandler,         /*0  - TIM1 */
    (void *) TIM2_IRQHandler,         /*1  - TIM2 */
    (void *) MGMT_IRQHandler,         /*2  - MGMT */
    (void *) BB_IRQHandler,           /*3  - BB */
    (void *) SLEEPTMR_IRQHandler,     /*4  - SLEEPTMR */
    (void *) SC1_IRQHandler,          /*5  - SC1 */
    (void *) SC2_IRQHandler,          /*6  - SC2 */
    (void *) SEC_IRQHandler,          /*7  - SEC */
    (void *) MACTMR_IRQHandler,       /*8  - MACTMR */
    (void *) MACTX_IRQHandler,        /*9  - MACTX */
    (void *) MACRX_IRQHandler,        /*10 - MACRX */
    (void *) ADC_IRQHandler,          /*11 - ADC */
    (void *) IRQA_IRQHandler,         /*12 - IRQA */
    (void *) IRQB_IRQHandler,         /*13 - IRQB */
    (void *) IRQC_IRQHandler,         /*14 - IRQC */
    (void *) IRQD_IRQHandler,         /*15 - IRQD */
    (void *) DEBUG_IRQHandler,        /*16 - DEBUG */
    (void *) SC3_IRQHandler,          /*17 - SC3 */
    (void *) SC4_IRQHandler,          /*18 - SC4 */
    (void *) USB_IRQHandler,          /*19 - USB */

};
